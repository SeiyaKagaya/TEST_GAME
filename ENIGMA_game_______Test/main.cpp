//============================================================================================
//
//プレイヤーを操作し敵を倒す処理[main.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "main.h"
#include "input.h"

#include "title.h"
#include "game.h"
#include "result.h"
#include "Tutorial.h"
#include "fade.h"
#include "sound.h"
#include "camera.h"
#include "player.h"
#include "gamefade.h"
#include "text.h"
#include "menu.h"
#include "Film.h"
#include "MenuFrame.h"

//グローバル変数
LPDIRECT3D9 g_pD3D = NULL;//direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;//direct#dデバイスへのポインタ
LPD3DXFONT g_pFont = NULL;//フォントへのポインタ


//LPD3DXFONT g_pFont_Comment[MAXFONT] = {};//フォントへのポインタ




//MODE g_mode = MODE_TITLE;//現在のモード(初期にtitle画面を使用)

MODE g_mode = MODE_TITLE;//現在のモード(初期にゲーム画面を使用)-----------------------------デバッグ仕様
MODE g_OldMode = MODE_TITLE;//過去のモード(初期にゲーム画面を使用)------
bool g_mesh = false;								//ワイヤーフレーム切り替え用
float g_fFogDensity;	//フォグ密度指定用


int g_nCountFPS = 0;//FPSカウンタ


// グローバル変数
LARGE_INTEGER g_startTime;
LARGE_INTEGER g_endTime;

//デルタタイム関係(全く未完)
double g_frequency;


D3DVIEWPORT9 g_fullScreen_Viewport;//全画面ビューポート


bool bClearFrag = false;//Clearフラグ

bool g_isFullscreen = false;			// ウィンドウを切り替えるためのフラグ
RECT g_windowRect;						// ウィンドウを切り替えるための変数

//===================================
//メイン関数
//===================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)//いつも同じ書き方

{
	DWORD dwCurrentTime;//現在時刻
	DWORD dwExecLastTime;//最後に処理した時刻

	DWORD dwFrameCount;//フレームカウント
	DWORD dwFPSLastTime;//最後にFPSを計測した時刻


	HWND hWnd;	//ウィンドウハンドル（識別子）
	MSG msg;	//メッセージを格納する変数

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();




	//ウィンドウ表示
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,							//ウィンドウのスタイル
		WindowProc,							//ウィンドウのプロージャ
		0,									//0にする（通常は使用せず）
		0,									//0にする（通常は使用せず）
		hInstance,							//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),		//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),			//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			//クライント領域の表示色
		NULL,								//メニューバー
		CLASS_NAME,							//ウィンドウクラスの定義
		LoadIcon(NULL,IDI_APPLICATION)		//ファイルのアイコン
	};

	RECT rect = { 0,0,SCREEN_WIDE,SCREEN_HEIGHT };//画面サイズの構造体

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定サイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを作成
	hWnd = CreateWindowEx(0,	//拡張ウィンドウスタイル
		CLASS_NAME,				//ウィンドウクラスの名前
		WINDOW_NAME,			//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,	//ウィンドウスタイル
		0,//CW_USEDEFAULT,			//ウィンドウ左上X座標///-----------------------------言われたらもとに戻す
		0,//CW_USEDEFAULT,			//ウィンドウ左上Y座標
		(rect.right - rect.left),//幅　
		(rect.bottom - rect.top),//高さ
		//SCREEN_WIDE,			//ウィンドウ左上幅
		//SCREEN_HEIGHT,			//ウィンドウ左上高さ
		NULL,					//親ウィンドウのハンドル
		NULL,					//メニューハンドル｜拡張子ウィンドウID
		hInstance,				//インスタンスハンドル
		NULL);					//ウィンドウ作成データ


	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化が失敗した場合
		return-1;//できなかったらここで終わり
	}

	//分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;//初期化
	dwExecLastTime = timeGetTime();//現在時刻を取得（保存）

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);//ウィンドウの表示状態を設定
	UpdateWindow(hWnd);        //クライアント領域を更新

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windowsの処理                          
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取たらメッセージループを抜ける
				break;
			}
			else
			{
				//メッセージ
				TranslateMessage(&msg);//仮想キーメッセージを文字メッセージを変換


				DispatchMessage(&msg); //ウィンドウプロージャーへメッセージを放出
			}
		}
		else
		{//directXの処理

			dwCurrentTime = timeGetTime();//現在時刻を取得
			

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;//FPSを測定した時刻を保存
				dwFrameCount = 0;//フレームカウントをクリア
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))//描画速度を設定//--------------------------------------------------------
			{//60分の一秒経過
				dwExecLastTime = dwCurrentTime;//処理開始の時刻(現在時刻)で保存

				dwFrameCount++;//フレームカウントを加算

				//更新処理
				Update();
				//描画処理
				Draw();
			}
		}
	}

	//終了処理----------------------------------------------------------------------
	timeEndPeriod(1);//分解能を戻す
	Uninit();
	
	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}
//=======================================
//ウィンドウプロシージャー
//=======================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	int nID;//返り値を格納

	switch (uMsg)
	{
		
	case WM_CREATE:	//ウィンドウ生成のメッセージ
		break;
	///-----------------------------------------------------------各ボタン操作での反応
	case WM_COMMAND: //コマンド発行のメッセージ

		break;

	case WM_CLOSE: //閉じるボタン押した時のメッセージ

		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
		if (nID == IDYES)
		{
			//ウィンドウ破棄
			DestroyWindow(hWnd);
		}
		else
		{//NOの時
			return 0;//0を返さないと終了してしまう
		}
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN://キー押下のメッセージ(ESC)
		switch (wParam)
		{
		case VK_ESCAPE://escapeボタン
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{
				//ウィンドウを破棄する
				DestroyWindow(hWnd);
			}
			break;

		case VK_F11:
			ToggleFullscreen(hWnd);
			break;

		}
		break;

	case WM_LBUTTONDOWN://マウス左クリック
		//ウィンドウフォーカスを合わせる
		SetFocus(hWnd);
		break;

	case WM_DESTROY: //ウィンドウ破棄のメッセージ
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	}


	return DefWindowProc(hWnd, uMsg, wParam, lParam);//規定の値を返す
}
//=============================
//デバイスの取得
//=============================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//=============================
//初期化処理
//=============================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindows)
{
	//----------------------------------------------------------------------------------------------------------------------------------ここから共通
	//画面全体のときのビューポート
	g_fullScreen_Viewport.X = 0;//ビューポートの開始位置-X
	g_fullScreen_Viewport.Y = 0;//ビューポートの開始位置-Y

	g_fullScreen_Viewport.Width = SCREEN_WIDE;//ビューポートの幅
	g_fullScreen_Viewport.Height = SCREEN_HEIGHT;//ビューポートの高さ

	//ビューポートの深度設定
	g_fullScreen_Viewport.MinZ = 0.0f;
	g_fullScreen_Viewport.MaxZ = 1.0f;

	D3DDISPLAYMODE d3ddm;//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;//プレゼンテーションパラメータ
	
	//direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定[決まった形]
	ZeroMemory(&d3dpp, sizeof(d3dpp));//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDE;//ゲーム画面サイズ横
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//ゲーム画面サイズ縦
	d3dpp.BackBufferFormat = d3ddm.Format;//バックバッファの形式
	d3dpp.BackBufferCount = 1;//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//ダブルバッファの切り替え（映像信号に同期）
	d3dpp.EnableAutoDepthStencil = TRUE;//デプスバッファとステンシルバッファを作成

	//d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//デパスバッファとして16ビットを使う----------------------------------------------------------------------
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;//デパスバッファとして24ビットを使う----------------------------------------------------------------------



	d3dpp.Windowed = bWindows;//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//インターバル

	//direct3Dデバイスの生成（描画処理と頂点処理をハードウェアで行う）
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		//direct３Dデバイスの生成（描画処理はハードウェア、頂点処理はCPUで行う）
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
		{
			//direct３Dデバイスの生成（描画処理と頂点処理はCPUで行う）
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定//-----------------------------------------------------------------
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//カリングの設定

	//アルファブランドの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);				//フォグ設定有効
	//g_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//フォグカラー
	//g_pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);		//フォグモード

	//g_fFogDensity = 0.003f;				//フォグ密度値
	//g_pD3DDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&g_fFogDensity));	//密度指定


	//------------------------------------------------------------------------------------------

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);


	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);




	//デバッグ表示用のフォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&g_pFont);


	//UIComment表示用のフォントの生成
	//MSゴシック
	//デバイス,文字高さ,文字幅,フォントスタイル,ミップマップのレベル
	//,斜体にするかどうか,
	//文字セット,
	//出力精度,
	//出力品質,
	//フォントピッチとファミリ,
	//フォント名,
	//フォントポインタ
	
	
	/*D3DXCreateFont(g_pD3DDevice, 50, 0, FW_HEAVY, 1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_TT_ONLY_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		TEXT("ＭＳ 明朝"),
		&g_pFont_Comment);*/



	////---------------------------------------------------------------------------------------fontのテスト
	//	//フォントの読み込み///
	//LPCSTR font_path = "data\\FONT\\DokiDokiFantasia.otf"; // どきどきファンタジアというフォントを使用可能に
	//if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) 
	//{
	//}
	//else 
	//{
	//	// フォント読込エラー処理
	//	MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	//}
	////------------------------------------読み込めてる
	



	//	TEXT("data\\FONT\\HGRSMP.TTF"),



	//InitFont(g_pD3DDevice);



	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//コントローラー初期化
	InitJoypad();
//
//	//サウンドの初期化処理
	InitSound(hWnd);

	//テキストの初期化
	InitText();


////----------------------------------------------------------------------------------------------------------------------------------ここまで共通
//
	//モード設定
	Setmode(g_mode);

	//フェードの初期化処理
	InitFade(MODE(FADE_NONE));


	//特別
	//InitPlayer();

	


	//各種オブジェクトの初期化処理
	return S_OK;
}
//=============================
//終了処理
//=============================
void Uninit(void)
{
	//各種オブジェクトの終了処理
	 
	//特別
	//UninitPlayer();

	//フェードの終了処理
	UninitFade();
	//タイトル画面の終了処理
	UninitTitle();
	//ゲーム画面の終了処理
	UninitGame();
	//リザルト画面の終了処理
	UninitResult();
	//チュートリアル画面の終了処理
	UninitTutorial();
	//メニュー画面の終了処理
	UninitMenuFrame();

	UninitSound();

	UninitText();

	////----------------------------------------------------------------------------------------------------------------------------------ここから共通

	//キーボードの終了処理
	UninitKeyboard();
	UninitJoypad();

	//direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	//デバッグ表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
	


	//for (int i = 0; i < MAXFONT; i++)
	//{
	//	//UIComment表示用フォントの破棄
	//	if (g_pFont_Comment[i] != NULL)
	//	{
	//		g_pFont_Comment[i]->Release();
	//		g_pFont_Comment[i] = NULL;
	//	}
	//}
	//UninitFont();

	//----------------------------------------------------------------------------------------------------------------------------------ここまで共通

}
//=============================
//更新処理
//=============================
void Update(void)
{
	//各種オブジェクトの更新処理 

	//UpdatePlayer();
		
	// デルタタイムの初期化
	InitializeDeltaTimer();

	// デルタタイムの取得
//	double deltaTime = GetDeltaTimer();
	//どう使うか問題





	//----------------------------------------------------------------------------------------------------------------------------------ここから共通
	//フェードの更新処理
	UpdateFade();

	//キーボードの更新処理
	UpdateKeyboard();

	if (GetkeyboardTrigger(DIK_F4) == true)//-----------------メッシュ表示系
	{
		g_mesh = !g_mesh;
		if (g_mesh == false)
		{
			//元の状態
			g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
		else if (g_mesh == true)
		{
			//ワイヤーフレームモードの状態
			g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
	}

	//コントローラー
	UpdateJoypad();
	////----------------------------------------------------------------------------------------------------------------------------------ここまで共通

	switch (g_mode)
	{
	case MODE_TITLE://タイトル画面
	
		UpdateTitle();
		break;

	case MODE_GAME://ゲーム画面
	
		UpdateGame();
		//UpdateAllScoreManagement();//スコア管理もここで
		UpdateFade();
		break;

	case MODE_RESULT://リザルト画面
		UpdateResult();
		break;
	
	case MODE_TUTORIAL://チュートリアル画面
		UpdateTutorial();
		break;

	case MODE_MENU://メニュー画面
		UpdateMenuFrame();
		break;

	}


}
//=============================
//描画処理
//=============================
void Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//これ大事
	//画面クリア(バックバッファ＆Zバッファのクリア)
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);


	//ZバッハZテストをしないと向こう側にあっても描画(木の貫通や、爆発半分になる問題解決)
	

	//描画段階
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

		//DrawPlayer();

		


		//各オブジェクトの描画処理


		switch (g_mode)
		{
		case MODE_TITLE://タイトル画面
			
		//ビューポートをもとに戻す
			pDevice->SetViewport(&g_fullScreen_Viewport);//ビューポートの設定

			DrawTitle();
			break;

		case MODE_GAME://ゲーム画面

			DrawGame();
			
			//テスト---------------------------------------------------------------------------------
			//DrawComentUI("テストーー！", D3DXVECTOR3(100.0f, 500.0f, 0.0f), 200, FONT_DOKIDOKI);

			//ビューポートをもとに戻す
			//pDevice->SetViewport(&g_fullScreen_Viewport);//ビューポートの設定

			
			
			break;

		case MODE_RESULT://リザルト画面
			//ビューポートをもとに戻す
			pDevice->SetViewport(&g_fullScreen_Viewport);//ビューポートの設定

			DrawResult();
			break;
		
		case MODE_TUTORIAL://チュートリアル画面
			//ビューポートをもとに戻す
			pDevice->SetViewport(&g_fullScreen_Viewport);//ビューポートの設定

			DrawTutorial();
			break;

		case MODE_MENU://メニュー画面
		//ビューポートをもとに戻す
			pDevice->SetViewport(&g_fullScreen_Viewport);//ビューポートの設定

			DrawMenuFrame();
			break;
		}
			
	//	DrawFPS();
#if _DEBUG
			DrawDebugText();
#endif
		


	//	DrawTextSet(D3DXVECTOR3(900.0f, 0.0f, 0.0f), 30, FONT_DOKIDOKI, D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f),"テストーFPS%d", g_nCountFPS);


		
		DrawFade();//フェード

		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//=============================
//モードの設定処理
//=============================
void Setmode(MODE g_ModeNext)
{
	//現在の画面(モード)の設定処理
	switch (g_mode)
	{
	case MODE_TITLE://タイトル画面
		UninitTitle();
		break;

	case MODE_GAME://ゲーム画面
		UninitGame();
		break;

	case MODE_RESULT://リザルト画面
		UninitResult();
		break;

	case MODE_TUTORIAL://チュートリアル画面
		UninitTutorial();
		break;

	case MODE_MENU://メニュー画面
		UninitMenuFrame();
		break;

	}
	g_OldMode = g_mode;
	g_mode = g_ModeNext;//現在の画面(モード)を切り替える

	//現在の画面(モード)の初期化処理

	switch (g_ModeNext)
	{
	case MODE_TITLE://タイトル画面
		InitTitle();
		break;

	case MODE_GAME://ゲーム画面

		//InitAllScoreManagement();//スコア管理もここで

		bClearFrag = false;

		// デルタタイムの初期化
		InitializeDeltaTimer();

		InitGame();

		break;

	case MODE_RESULT://リザルト画面
		InitResult();
		break;

	case MODE_TUTORIAL://チュートリアル画面
		InitTutorial();
		break;

	case MODE_MENU://メニュー画面
		InitMenuFrame();
		break;
	}




}
//=============================
//モードの取得
//=============================
MODE GetMode(void)
{
	return g_mode;
}
//=============================
//モードの取得
//=============================
MODE GetOldMode(void)
{
	return g_OldMode;
}
//=============================
//全画面用ビューポート取得
//=============================
D3DVIEWPORT9 GetViewPort(void)
{
	return g_fullScreen_Viewport;
}

//=============================
// デルタタイムを初期化
//=============================
void InitializeDeltaTimer(void) 
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	g_frequency = 1.0 / frequency.QuadPart;

	QueryPerformanceCounter(&g_startTime);
}
//=============================
// デルタタイムを取得
//=============================
double GetDeltaTimer(void) 
{
	QueryPerformanceCounter(&g_endTime);
	double delta = (g_endTime.QuadPart - g_startTime.QuadPart) * g_frequency;

	g_startTime = g_endTime;

	return delta;
}
//=============================
// ウィンドウをフルスクリーンに変える処理
//=============================
void ToggleFullscreen(HWND hWnd)
{
	// 現在のウィンドウスタイルを取得
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// ウィンドウモードに切り替え
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// フルスクリーンモードに切り替え
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}

////=============================
////FPS表示処理
////=============================
//void DrawFPS(void)
//{
//	RECT rect = { 0,0,SCREEN_WIDE,SCREEN_HEIGHT};
//	char aStr[1024];
//	//文字列に代入
//	wsprintf(&aStr[0], "FPS:%d", g_nCountFPS);
//
//	//テキストの描画
//	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 15, 15, 255));
//
//}
//=============================
//デバッグコメント表示処理
//=============================
void DrawDebugText(void)
{
	RECT rect = { 0,0,SCREEN_WIDE,SCREEN_HEIGHT};
//	char aStr[1024];

	Camera* pCamera;
	pCamera = GetCamera();//とりあえず

	Player* pPlayer;
	pPlayer = GetPlayer();

	////プレイヤー向き
	//int yRot = pPlayer[0].rot.y * 100;

	////カメラ向き
	//int CameraRot = pCamera[0].rot.y * 100;

	////カメラ位置
	//int fXdate = pCamera[0].posV.x;
	//int fYdate = pCamera[0].posV.y;
	//int fZdate = pCamera[0].posV.z;

	//プレーヤー位置
	int Xpos = pPlayer->pos.x;
	int Ypos = pPlayer->pos.y;
	int Zpos = pPlayer->pos.z;

	//文字列に代入
	//wsprintf(&aStr[0], "F4-メッシュ表示\n\nカメラ角度:%d\nプレイヤー座標\nX:%d/Y:%d/Z:%d\nプレイヤーの角度:%d\n++カメラ座標++\nX座標:%d\nY座標:%d\nZ座標:%d\n+---------+\n--プレイヤー操作--\n左スティック--移動\n右スティック--カメラ操作\nAボタン--飛翔\n\nP:デバッグ用ポーズ\nO:Resultへ", CameraRot, Xpos, Ypos, Zpos, yRot, fXdate, fYdate, fZdate);

	////文字列に代入
	//wsprintf(&aStr[0],"フレーム--%d\nキー %d", pPlayer->NowFrameCntDOWN,pPlayer->NowKeyCntDOWN);

	////テキストの描画
	//g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 55, 55, 255));



	//DrawTextSet(D3DXVECTOR3(750.0f, 0.0f, 0.0f), 0, FONT_AKABARASINDELERA, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), "フレーム--%d", pPlayer->NowFrameCntDOWN);
	DrawTextSet(D3DXVECTOR3(950.0f, 670.0f, 0.0f), 0, FONT_AKABARASINDELERA, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), "１Pの位置--,%d,%d,%d", Xpos, Ypos, Zpos);

}

//=============================
//Clearフラグ立てる処理
//=============================
void GameClearFragOn(void)
{
	bClearFrag = true;
}
//=============================
//Clearフラグ取得処理
//=============================
bool GetGameClearFrag(void)
{
	return bClearFrag;
}



















//-----------------------------------------------------------------------------テスト
//
//ID3DXSprite* g_pSprite = NULL;
//LPDIRECT3DTEXTURE9 g_pFontTexture = NULL;
//
//
//
////=============================
////フォント初期化
////=============================
//void InitFont(LPDIRECT3DDEVICE9 g_pD3DDevice)
//{
//	// フォントのテクスチャ作成
//	D3DXCreateTextureFromFile(g_pD3DDevice, "data\\FONT\\DokiDokiFantasia.otf", &g_pFontTexture);
//
//	// フォント作成
//	D3DXCreateFont(g_pD3DDevice, 30, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET,
//		OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, "Arial", &g_pFont_Comment);
//
//	// スプライト作成
//	D3DXCreateSprite(g_pD3DDevice, &g_pSprite);
//}
////=============================
////フォント終了処理
////=============================
//void UninitFont()
//{
//	if (g_pFontTexture)
//		g_pFontTexture->Release();
//
//	if (g_pFont_Comment)
//		g_pFont_Comment->Release();
//
//	if (g_pSprite)
//		g_pSprite->Release();
//}
////=============================
////コメント描画
////=============================
//void RenderFrame(LPDIRECT3DDEVICE9 g_pD3DDevice)
//{
//	// フォント描画のための設定
//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
//
//	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
//	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//
//	// フォント描画
//	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
//	g_pSprite->Draw(g_pFontTexture, NULL, NULL, NULL, 0xFFFFFFFF);
//	RenderText("テスト!", 100, 100);
//	g_pSprite->End();
//}
////=============================
////レンダーテキストセット
////=============================
//void RenderText(const char* text, int x, int y)
//{
//	RECT rc = { x, y, 0, 0 };
//
//	g_pFont_Comment->DrawText(g_pSprite, text, -1, &rc, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
//}