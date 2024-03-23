//=========================================================
//
//ポーズ画面で使う変数、宣言、構造体[password.cpp]
// Author matsuda towa
//
//=========================================================
#include "password.h"
#include "moneyboxdigit.h"
#include "moneybox.h"
#include "input.h"
#include "keyinfo.h"
#include "sound.h"

//=========================================================
//グローバル変数
//=========================================================
LPDIRECT3DTEXTURE9 g_pTexturePassword = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPassword = NULL;//頂点バッファへのポリゴン
PASSWORD g_aPassword[NUM_DIGIT];	//ポーズ構造体の情報

//=============================================
//壁のテクスチャの種類
//=============================================
static const char* PASSWORD_TEX_NAME =
{
	"data\\TEXTURE\\mark.png",
};

void InitPassword(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

//デバイスの取得
	pDevice = GetDevice();

//	int nCntPause = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		PASSWORD_TEX_NAME,
		&g_pTexturePassword
	);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_DIGIT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPassword, NULL);

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassword->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPos = 0; nCntPos < NUM_DIGIT; nCntPos++)
	{
		switch (nCntPos)
		{
		case 0:
			g_aPassword[nCntPos].pos = D3DXVECTOR3(PASSWORD_FIRSTPOS_1P, (SCREEN_HEIGHT / 1.25f), 0.0f);
			break;
		case 1:
			g_aPassword[nCntPos].pos = D3DXVECTOR3(PASSWORD_FIRSTPOS_1P + PASSWORD_ADDPOS, (SCREEN_HEIGHT / 1.25f), 0.0f);
			break;
		case 2:
			g_aPassword[nCntPos].pos = D3DXVECTOR3(PASSWORD_FIRSTPOS_1P + PASSWORD_ADDPOS * nCntPos , (SCREEN_HEIGHT / 1.25f), 0.0f);
			break;
		case 3:
			g_aPassword[nCntPos].pos = D3DXVECTOR3(PASSWORD_FIRSTPOS_1P + PASSWORD_ADDPOS * nCntPos, (SCREEN_HEIGHT / 1.25f), 0.0f);
			break;
		}

		g_aPassword[nCntPos].nType = PASSWORDTYPE_EYE;

		g_aPassword[nCntPos].Type = PASSWORDTYPE_EYE;
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{


		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aPassword[nCnt].pos.x - PASSWORD_WIDE , g_aPassword[nCnt].pos.y - PASSWORD_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPassword[nCnt].pos.x + PASSWORD_WIDE, g_aPassword[nCnt].pos.y - PASSWORD_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aPassword[nCnt].pos.x - PASSWORD_WIDE, g_aPassword[nCnt].pos.y + PASSWORD_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPassword[nCnt].pos.x + PASSWORD_WIDE, g_aPassword[nCnt].pos.y + PASSWORD_HEIGHT, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テキスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(TEX_ADD, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(TEX_ADD, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPassword->Unlock();
}

void UninitPassword(void)
{

	//テクスチャの破棄
	if (g_pTexturePassword != NULL)
	{
		g_pTexturePassword->Release();
		g_pTexturePassword = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPassword != NULL)
	{
		g_pVtxBuffPassword->Release();
		g_pVtxBuffPassword = NULL;
	}
}

void UpdatePassword(void)
{

}

void DrawPassword(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();//----------------書き換え済み

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPassword, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);//-------書き換え済み

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePassword);//---------書き換え済み
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類//----------書き換え済み
			nCnt * 4,//描画する最初の頂点インデックス
			2);//描画するプリミティブ数
		
	
	}
	//テクスチャを戻す
		pDevice->SetTexture(0, NULL);
}

void SetPassword(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	MONEYBOX* pMoneybox = GetMoneybox();

	if (pMoneybox->WhichPlayer == false)
	{//1Pの時
		VERTEX_2D* pVtx;//頂点情報のポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffPassword->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntPos = 0; nCntPos < NUM_DIGIT; nCntPos++)
		{
			switch (nCntPos)
			{
			case 0:
				g_aPassword[nCntPos].pos = D3DXVECTOR3(PASSWORD_FIRSTPOS_1P + 53.0f, (SCREEN_HEIGHT / 1.25f), 0.0f);
				break;
			case 1:
				g_aPassword[nCntPos].pos = D3DXVECTOR3(PASSWORD_FIRSTPOS_1P + 53.0f + PASSWORD_ADDPOS, (SCREEN_HEIGHT / 1.25f), 0.0f);
				break;
			case 2:
				g_aPassword[nCntPos].pos = D3DXVECTOR3(PASSWORD_FIRSTPOS_1P + 53.0f + PASSWORD_ADDPOS * nCntPos, (SCREEN_HEIGHT / 1.25f), 0.0f);
				break;
			case 3:
				g_aPassword[nCntPos].pos = D3DXVECTOR3(PASSWORD_FIRSTPOS_1P + 53.0f + PASSWORD_ADDPOS * nCntPos, (SCREEN_HEIGHT / 1.25f), 0.0f);
				break;
			}

		}

		for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
		{


			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aPassword[nCnt].pos.x - PASSWORD_WIDE, g_aPassword[nCnt].pos.y - PASSWORD_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPassword[nCnt].pos.x + PASSWORD_WIDE, g_aPassword[nCnt].pos.y - PASSWORD_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPassword[nCnt].pos.x - PASSWORD_WIDE, g_aPassword[nCnt].pos.y + PASSWORD_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPassword[nCnt].pos.x + PASSWORD_WIDE, g_aPassword[nCnt].pos.y + PASSWORD_HEIGHT, 0.0f);

			pVtx += 4;
		}
		//頂点バッファをアンロックする
		g_pVtxBuffPassword->Unlock();
	}
	else if (pMoneybox->WhichPlayer == true)
	{//2Pの時
		VERTEX_2D* pVtx;//頂点情報のポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffPassword->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntPos = 0; nCntPos < NUM_DIGIT; nCntPos++)
		{
			switch (nCntPos)
			{
			case 0:
				g_aPassword[nCntPos].pos = D3DXVECTOR3(PASSWORD_FIRSTPOS_2P + 53.0f, (SCREEN_HEIGHT / 1.25f), 0.0f);
				break;
			case 1:
				g_aPassword[nCntPos].pos = D3DXVECTOR3(PASSWORD_FIRSTPOS_2P + 53.0f + PASSWORD_ADDPOS, (SCREEN_HEIGHT / 1.25f), 0.0f);
				break;
			case 2:
				g_aPassword[nCntPos].pos = D3DXVECTOR3(PASSWORD_FIRSTPOS_2P + 53.0f + PASSWORD_ADDPOS * nCntPos, (SCREEN_HEIGHT / 1.25f), 0.0f);
				break;
			case 3:
				g_aPassword[nCntPos].pos = D3DXVECTOR3(PASSWORD_FIRSTPOS_2P + 53.0f + PASSWORD_ADDPOS * nCntPos, (SCREEN_HEIGHT / 1.25f), 0.0f);
				break;
			}
		}

		for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
		{


			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aPassword[nCnt].pos.x - PASSWORD_WIDE, g_aPassword[nCnt].pos.y - PASSWORD_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPassword[nCnt].pos.x + PASSWORD_WIDE, g_aPassword[nCnt].pos.y - PASSWORD_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPassword[nCnt].pos.x - PASSWORD_WIDE, g_aPassword[nCnt].pos.y + PASSWORD_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPassword[nCnt].pos.x + PASSWORD_WIDE, g_aPassword[nCnt].pos.y + PASSWORD_HEIGHT, 0.0f);


			pVtx += 4;
		}
		//頂点バッファをアンロックする
		g_pVtxBuffPassword->Unlock();
	}
}

void ChangePassword1P(D3DXCOLOR col, int nSelectDigit)
{
	int nVtx = nSelectDigit * 4; //選択されてる頂点

	XINPUT_STATE joykeystate;

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassword->Lock(0, 0, (void**)&pVtx, 0);


	DWORD dwResult = XInputGetState(0, &joykeystate);
	if (dwResult == ERROR_SUCCESS)
	{
		if (GetkeyboardTrigger(DIK_W) == true 
			|| GetJoypadTrigger(JOYKEY_UP, 0) == true 
			|| GetkeyboardTrigger(DIK_UP))
		{//Wがおされた(上)
			g_aPassword[nSelectDigit].nType--;
			PlaySound(SOUND_LABEL_SE_DIAL);
			if (g_aPassword[nSelectDigit].nType < 0)
			{
				g_aPassword[nSelectDigit].nType = NUM_PASSWORD - 1;
			}
		}
		else if (GetkeyboardTrigger(DIK_S) == true 
			|| GetJoypadTrigger(JOYKEY_DOWN, 0) == true 
			|| GetkeyboardTrigger(DIK_DOWN))
		{//Sがおされた(下)
			g_aPassword[nSelectDigit].nType++;
			PlaySound(SOUND_LABEL_SE_DIAL);
			if (g_aPassword[nSelectDigit].nType >= NUM_PASSWORD)
			{
				g_aPassword[nSelectDigit].nType = 0;
			}
		}

		if (GetkeyboardTrigger(DIK_RETURN) == true
			|| GetJoypadTrigger(JOYKEY_A, 0) == true)
		{
			if (g_aPassword[0].Type == PASSWORDTYPE_LEAF
				&& g_aPassword[1].Type == PASSWORDTYPE_HAND
				&& g_aPassword[2].Type == PASSWORDTYPE_EYE
				&& g_aPassword[3].Type == PASSWORDTYPE_GRAVE)
			{
				CorrectMoneyboxDigit();
			}
			else
			{
				MistakeMoneyboxDigit();
				SetKeyinfo(MISSMONEYBOX, 0);
			}
		}

	}
	else
	{//コントローラーがなかったとき
		if (GetkeyboardTrigger(DIK_W) == true || GetkeyboardTrigger(DIK_UP))
		{//Wがおされた(上)
			g_aPassword[nSelectDigit].nType--;
			PlaySound(SOUND_LABEL_SE_DIAL);
			if (g_aPassword[nSelectDigit].nType < 0)
			{
				g_aPassword[nSelectDigit].nType = NUM_PASSWORD - 1;
			}
		}
		else if (GetkeyboardTrigger(DIK_S) == true || GetkeyboardTrigger(DIK_DOWN))
		{//Sがおされた(下)
			g_aPassword[nSelectDigit].nType++;
			PlaySound(SOUND_LABEL_SE_DIAL);
			if (g_aPassword[nSelectDigit].nType >= NUM_PASSWORD)
			{
				g_aPassword[nSelectDigit].nType = 0;
			}
		}
	}
	switch (g_aPassword[nSelectDigit].nType)
	{
	case 0:
		g_aPassword[nSelectDigit].Type = PASSWORDTYPE_EYE;
		//テキスチャの座標設定
		pVtx[nVtx].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[nVtx + 1].tex = D3DXVECTOR2(TEX_ADD, 0.0f);
		pVtx[nVtx + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[nVtx + 3].tex = D3DXVECTOR2(TEX_ADD, 1.0f);
		break;
	case 1:
		g_aPassword[nSelectDigit].Type = PASSWORDTYPE_HAND;
		//テキスチャの座標設定
		pVtx[nVtx].tex = D3DXVECTOR2(TEX_ADD, 0.0f);
		pVtx[nVtx + 1].tex = D3DXVECTOR2(TEX_ADD * 2.0f, 0.0f);
		pVtx[nVtx + 2].tex = D3DXVECTOR2(TEX_ADD, 1.0f);
		pVtx[nVtx + 3].tex = D3DXVECTOR2(TEX_ADD * 2.0f, 1.0f);
		break;
	case 2:
		g_aPassword[nSelectDigit].Type = PASSWORDTYPE_LEAF;
		//テキスチャの座標設定
		pVtx[nVtx].tex = D3DXVECTOR2(TEX_ADD * 2.0f, 0.0f);
		pVtx[nVtx + 1].tex = D3DXVECTOR2(TEX_ADD * 3.0f, 0.0f);
		pVtx[nVtx + 2].tex = D3DXVECTOR2(TEX_ADD * 2.0f, 1.0f);
		pVtx[nVtx + 3].tex = D3DXVECTOR2(TEX_ADD * 3.0f, 1.0f);
		break;
	case 3:
		g_aPassword[nSelectDigit].Type = PASSWORDTYPE_HEART;
		//テキスチャの座標設定
		pVtx[nVtx].tex = D3DXVECTOR2(TEX_ADD * 3.0f, 0.0f);
		pVtx[nVtx + 1].tex = D3DXVECTOR2(TEX_ADD * 4.0f, 0.0f);
		pVtx[nVtx + 2].tex = D3DXVECTOR2(TEX_ADD * 3.0f, 1.0f);
		pVtx[nVtx + 3].tex = D3DXVECTOR2(TEX_ADD * 4.0f, 1.0f);
		break;
	case 4:
		g_aPassword[nSelectDigit].Type = PASSWORDTYPE_GRAVE;
		//テキスチャの座標設定
		pVtx[nVtx].tex = D3DXVECTOR2(TEX_ADD * 4.0f, 0.0f);
		pVtx[nVtx + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[nVtx + 2].tex = D3DXVECTOR2(TEX_ADD * 4.0f, 1.0f);
		pVtx[nVtx + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
		break;
	}
}

void ChangePassword2P(D3DXCOLOR col, int nSelectDigit)
{
	int nVtx = nSelectDigit * 4; //選択されてる頂点

	XINPUT_STATE joykeystate;

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPassword->Lock(0, 0, (void**)&pVtx, 0);


	DWORD dwResult = XInputGetState(0, &joykeystate);
	if (dwResult == ERROR_SUCCESS)
	{
		if (GetkeyboardTrigger(DIK_W) == true
			|| GetJoypadTrigger(JOYKEY_UP, 1) == true
			|| GetkeyboardTrigger(DIK_UP))
		{//Wがおされた(上)
			g_aPassword[nSelectDigit].nType--;
			PlaySound(SOUND_LABEL_SE_DIAL);
			if (g_aPassword[nSelectDigit].nType < 0)
			{
				g_aPassword[nSelectDigit].nType = NUM_PASSWORD - 1;
			}
		}
		else if (GetkeyboardTrigger(DIK_S) == true
			|| GetJoypadTrigger(JOYKEY_DOWN, 1) == true
			|| GetkeyboardTrigger(DIK_DOWN))
		{//Sがおされた(下)
			g_aPassword[nSelectDigit].nType++;
			PlaySound(SOUND_LABEL_SE_DIAL);
			if (g_aPassword[nSelectDigit].nType >= NUM_PASSWORD)
			{
				g_aPassword[nSelectDigit].nType = 0;
			}
		}

		if (GetkeyboardTrigger(DIK_RETURN) == true
			|| GetJoypadTrigger(JOYKEY_A, 1) == true)
		{
			if (g_aPassword[0].Type == PASSWORDTYPE_LEAF
				&& g_aPassword[1].Type == PASSWORDTYPE_HAND
				&& g_aPassword[2].Type == PASSWORDTYPE_EYE
				&& g_aPassword[3].Type == PASSWORDTYPE_GRAVE)
			{
				CorrectMoneyboxDigit();
			}
			else
			{
				MistakeMoneyboxDigit();
				SetKeyinfo(MISSMONEYBOX, 1);
			}
		}

	}
	else
	{//コントローラーがなかったとき
		if (GetkeyboardTrigger(DIK_W) == true || GetkeyboardTrigger(DIK_UP))
		{//Wがおされた(上)
			g_aPassword[nSelectDigit].nType--;
			PlaySound(SOUND_LABEL_SE_DIAL);
			if (g_aPassword[nSelectDigit].nType < 0)
			{
				g_aPassword[nSelectDigit].nType = NUM_PASSWORD - 1;
			}
		}
		else if (GetkeyboardTrigger(DIK_S) == true || GetkeyboardTrigger(DIK_DOWN))
		{//Sがおされた(下)
			g_aPassword[nSelectDigit].nType++;
			PlaySound(SOUND_LABEL_SE_DIAL);
			if (g_aPassword[nSelectDigit].nType >= NUM_PASSWORD)
			{
				g_aPassword[nSelectDigit].nType = 0;
			}
		}
	}
	switch (g_aPassword[nSelectDigit].nType)
	{
	case 0:
		g_aPassword[nSelectDigit].Type = PASSWORDTYPE_EYE;
		//テキスチャの座標設定
		pVtx[nVtx].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[nVtx + 1].tex = D3DXVECTOR2(TEX_ADD, 0.0f);
		pVtx[nVtx + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[nVtx + 3].tex = D3DXVECTOR2(TEX_ADD, 1.0f);
		break;
	case 1:
		g_aPassword[nSelectDigit].Type = PASSWORDTYPE_HAND;
		//テキスチャの座標設定
		pVtx[nVtx].tex = D3DXVECTOR2(TEX_ADD, 0.0f);
		pVtx[nVtx + 1].tex = D3DXVECTOR2(TEX_ADD * 2.0f, 0.0f);
		pVtx[nVtx + 2].tex = D3DXVECTOR2(TEX_ADD, 1.0f);
		pVtx[nVtx + 3].tex = D3DXVECTOR2(TEX_ADD * 2.0f, 1.0f);
		break;
	case 2:
		g_aPassword[nSelectDigit].Type = PASSWORDTYPE_LEAF;
		//テキスチャの座標設定
		pVtx[nVtx].tex = D3DXVECTOR2(TEX_ADD * 2.0f, 0.0f);
		pVtx[nVtx + 1].tex = D3DXVECTOR2(TEX_ADD * 3.0f, 0.0f);
		pVtx[nVtx + 2].tex = D3DXVECTOR2(TEX_ADD * 2.0f, 1.0f);
		pVtx[nVtx + 3].tex = D3DXVECTOR2(TEX_ADD * 3.0f, 1.0f);
		break;
	case 3:
		g_aPassword[nSelectDigit].Type = PASSWORDTYPE_HEART;
		//テキスチャの座標設定
		pVtx[nVtx].tex = D3DXVECTOR2(TEX_ADD * 3.0f, 0.0f);
		pVtx[nVtx + 1].tex = D3DXVECTOR2(TEX_ADD * 4.0f, 0.0f);
		pVtx[nVtx + 2].tex = D3DXVECTOR2(TEX_ADD * 3.0f, 1.0f);
		pVtx[nVtx + 3].tex = D3DXVECTOR2(TEX_ADD * 4.0f, 1.0f);
		break;
	case 4:
		g_aPassword[nSelectDigit].Type = PASSWORDTYPE_GRAVE;
		//テキスチャの座標設定
		pVtx[nVtx].tex = D3DXVECTOR2(TEX_ADD * 4.0f, 0.0f);
		pVtx[nVtx + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[nVtx + 2].tex = D3DXVECTOR2(TEX_ADD * 4.0f, 1.0f);
		pVtx[nVtx + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
		break;
	}
}