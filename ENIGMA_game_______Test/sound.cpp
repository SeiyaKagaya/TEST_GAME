//=============================================================================
//
// サウンド処理 [sound.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "sound.h"

//*****************************************************************************
// サウンド情報の構造体定義
//*****************************************************************************
typedef struct
{
	const char* pFilename;	// ファイル名
	int nCntLoop;		// ループカウント
} SOUNDINFO;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
IXAudio2* g_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
IXAudio2MasteringVoice* g_pMasteringVoice = NULL;			// マスターボイス
IXAudio2SourceVoice* g_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
BYTE* g_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

// サウンドの情報
SOUNDINFO g_aSoundInfo[SOUND_LABEL_MAX] =
{
	{"data/SOUND/BGM/Title000.wav", -1},	 // タイトルBGM//-1がループ/0が一回きり
	{"data/SOUND/BGM/Clear000.wav", -1},	 // クリアBGM
	{"data/SOUND/BGM/GameOver000.wav", -1},	 // ゲームオーバーBGM
	{"data/SOUND/BGM/Eniguma000.wav", -1},	 // エニグマBGM
	{"data/SOUND/BGM/Menu000.wav", -1},	 // エニグマBGM
	{"data/SOUND/SE/Playerwalk.wav",-1},//着地
	{"data/SOUND/SE/digitchange.wav",0},//ダイヤル
	{"data/SOUND/SE/open.wav",0},//金庫オープン
	{"data/SOUND/SE/notopen.wav",0},//金庫notオープン
	{"data/SOUND/SE/water.wav",0},//流す
	{"data/SOUND/SE/lever.wav",0},//レバー
	{"data/SOUND/SE/cook.wav",0},//クック
	{"data/SOUND/SE/button.wav",0},//ボタン
	{"data/SOUND/SE/movecursor.wav",0},//Cursorムーブ
	{"data/SOUND/SE/decision.wav",0},//決定
	{"data/SOUND/SE/pause.wav",0},//ポーズ
	{"data/SOUND/SE/eyetrap.wav",0},//視野
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSound(HWND hWnd)
{
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&g_pXAudio2, 0);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// マスターボイスの生成
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		if (g_pXAudio2 != NULL)
		{
			// XAudio2オブジェクトの開放
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// サウンドデータの初期化
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
		hFile = CreateFile(g_aSoundInfo[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// ファイルポインタを先頭に移動
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVEファイルのチェック
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		if (dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// フォーマットチェック
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// オーディオデータ読み込み
		hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		g_apDataAudio[nCntSound] = (BYTE*)malloc(g_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, g_apDataAudio[nCntSound], g_aSizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// ソースボイスの生成
		hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[nCntSound], &(wfx.Format));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// バッファの値設定
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = g_aSizeAudio[nCntSound];
		buffer.pAudioData = g_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = g_aSoundInfo[nCntSound].nCntLoop;

		// オーディオバッファの登録
		g_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// ファイルをクローズ
		CloseHandle(hFile);
	}

	//TestSoundmain();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSound(void)
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (g_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			g_apSourceVoice[nCntSound]->Stop(0);

			// ソースボイスの破棄
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;

			// オーディオデータの開放
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}

	// マスターボイスの破棄
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;

	if (g_pXAudio2 != NULL)
	{
		// XAudio2オブジェクトの開放
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}

	// COMライブラリの終了処理
	CoUninitialize();
}

//=============================================================================
// セグメント再生(再生中なら停止)
//=============================================================================
HRESULT PlaySound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = g_aSoundInfo[label].nCntLoop;

	// 状態取得
	g_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		g_apSourceVoice[label]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// 再生
	g_apSourceVoice[label]->Start(0);

	return S_OK;
}

//=============================================================================
// セグメント停止(ラベル指定)
//=============================================================================
void StopSound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	g_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		g_apSourceVoice[label]->FlushSourceBuffers();
	}
}

//=============================================================================
// セグメント停止(全て)
//=============================================================================
void StopSound(void)
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (g_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			g_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}

//=============================================================================
// チャンクのチェック
//=============================================================================
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

//=============================================================================
// チャンクデータの読み込み
//=============================================================================
HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}



////=============================================================================
//// 音源再生しているか判別処理-----Author seiya kagaya 
////=============================================================================
//bool SaundPlayJudge(SOUND_LABEL label)
//{//再生中でtrue　再生してないでfalse
//	XAUDIO2_VOICE_STATE xa2state;
//	XAUDIO2_BUFFER buffer;
//
//	// バッファの値設定
//	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
//	buffer.AudioBytes = g_aSizeAudio[label];
//	buffer.pAudioData = g_apDataAudio[label];
//	buffer.Flags = XAUDIO2_END_OF_STREAM;
//	buffer.LoopCount = g_aSoundInfo[label].nCntLoop;
//	// 状態取得
//	g_apSourceVoice[label]->GetState(&xa2state);
//	if (xa2state.BuffersQueued != 0)
//	{// 再生中
//		return true;
//	}
//	else
//	{//再生してない
//		return false;
//	}
//}










//
//#include <windows.h>
//#include <stdio.h>
//#include <mmdeviceapi.h>
//#include <functiondiscoverykeys_devpkey.h>
//
//int TestSoundmain(void)
//{
//	HRESULT hr;
//	IMMDeviceEnumerator* pEnumerator = NULL;
//	IMMDeviceCollection* pDeviceCollection = NULL;
//	IMMDevice* pDevice = NULL;
//	IPropertyStore* pPropertyStore = NULL;
//
//	//// COM ライブラリの初期化
//	//hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
//	//if (FAILED(hr)) {
//	//	printf("COM ライブラリの初期化に失敗しました。HRESULT = 0x%x\n", hr);
//	//	return 1;
//	//}
//
//	// IMMDeviceEnumerator オブジェクトの作成
//	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
//	if (FAILED(hr)) {
//		printf("IMMDeviceEnumerator オブジェクトの作成に失敗しました。HRESULT = 0x%x\n", hr);
//		CoUninitialize();
//		return 1;
//	}
//	// オーディオエンドポイントの列挙
//	hr = pEnumerator->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &pDeviceCollection);
//	if (FAILED(hr)) {
//		printf("オーディオエンドポイントの列挙に失敗しました。HRESULT = 0x%x\n", hr);
//		pEnumerator->Release();
//		CoUninitialize();
//		return 1;
//	}
//
//	UINT deviceCount;
//	hr = pDeviceCollection->GetCount(&deviceCount);
//	if (FAILED(hr)) {
//		printf("デバイス数の取得に失敗しました。HRESULT = 0x%x\n", hr);
//		pDeviceCollection->Release();
//		pEnumerator->Release();
//		CoUninitialize();
//		return 1;
//	}
//
//	// デバイスの取得
//	for (UINT i = 0; i < deviceCount; ++i) {
//		hr = pDeviceCollection->Item(i, &pDevice);
//		if (FAILED(hr)) {
//			printf("デバイスの取得に失敗しました。HRESULT = 0x%x\n", hr);
//			continue;
//		}
//
//		// デバイスのプロパティ ストアの取得
//		hr = pDevice->OpenPropertyStore(STGM_READ, &pPropertyStore);
//		if (FAILED(hr)) {
//			printf("デバイスのプロパティ ストアの取得に失敗しました。HRESULT = 0x%x\n", hr);
//			pDevice->Release();
//			continue;
//		}
//
//		// プロパティの取得例 (デバイス名の取得)
//		PROPVARIANT varName;
//		PropVariantInit(&varName);
//		hr = pPropertyStore->GetValue(PKEY_Device_FriendlyName, &varName);
//		if (SUCCEEDED(hr)) {
//			if (varName.vt == VT_LPWSTR) {
//				wprintf(L"オーディオ デバイス名 %d: %s\n", i + 1, varName.pwszVal);
//			}
//			else {
//				printf("オーディオ デバイス名の取得に失敗しました。\n");
//			}
//			PropVariantClear(&varName);
//		}
//		else {
//			printf("オーディオ デバイス名の取得に失敗しました。HRESULT = 0x%x\n", hr);
//		}
//
//		// 解放
//		pPropertyStore->Release();
//		pDevice->Release();
//	}
//
//	// 解放
//	pDeviceCollection->Release();
//	pEnumerator->Release();
//	CoUninitialize();
//
//	return 0;
//}