//=========================================================
//
//ポーズ動きの処理関係[pause.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "input.h"
#include "game.h"
#include "pause.h"
#include "fade.h"
#include "text.h"
#include "sound.h"

#define NUM_PAUSEUI (4)//ポーズの表示ポリゴンの数
#define NUM_SELECTUI	(3)//選択肢の数
#define MAX_WIDE				(256)//横幅
#define MAX_H				(30)//縦幅

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePause[NUM_PAUSEUI] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;//頂点バッファへのポリゴン
PAUSE g_aPause[NUM_PAUSEUI];	//ポーズ構造体の情報

int g_Pause=0;//ポーズ情報

bool g_InputLock[2] = {};

//=============================
//ポーズ初期化処理
//=============================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

//	int nCntPause = 0;

	//ポーズ情報の初期化
	g_Pause = PAUSE_MENU_CONTINUE;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pauseframe.png", &g_pTexturePause[0]);//--------書き換え済み//とりあえず
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Pause000.png", &g_pTexturePause[1]);//--------書き換え済み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Pause001.png", &g_pTexturePause[2]);//--------書き換え済み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Pause002.png", &g_pTexturePause[3]);//--------書き換え済み

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PAUSEUI, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPause, NULL);

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	int nCountPause = 0;

	for (nCountPause = 0; nCountPause < NUM_PAUSEUI; nCountPause++)
	{
		g_aPause[nCountPause].pos = D3DXVECTOR3(SCREEN_WIDE / 2, SCREEN_HEIGHT / 2, 0.0f);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - MAX_WIDE, g_aPause[nCountPause].pos.y - MAX_H, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + MAX_WIDE, g_aPause[nCountPause].pos.y - MAX_H, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - MAX_WIDE, g_aPause[nCountPause].pos.y + MAX_H, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + MAX_WIDE, g_aPause[nCountPause].pos.y + MAX_H, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 55, 55, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 55, 55, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 55, 55, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 55, 55, 255);

		//テキスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
	
	g_InputLock[0] = false;//-が下0がニュートラ+が上
	g_InputLock[1] = false;
}
//=============================
//ポーズ終了処理
//=============================
void UninitPause(void)
{
	int nCountPause = 0;

	for (nCountPause = 0; nCountPause < NUM_PAUSEUI; nCountPause++)
	{
		//テクスチャの破棄
		if (g_pTexturePause[nCountPause] != NULL)
		{
			g_pTexturePause[nCountPause]->Release();
			g_pTexturePause[nCountPause] = NULL;
		}
		//頂点バッファの破棄
		if (g_pVtxBuffPause != NULL)
		{
			g_pVtxBuffPause->Release();
			g_pVtxBuffPause = NULL;
		}
	}
}
//=============================
//ポーズ更新処理
//=============================
void UpdatePause(void)
{
	XINPUT_STATE joykeystate;

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	int nCountPause = 0;

	DWORD dwResult = XInputGetState(0, &joykeystate);

	

	if (dwResult == ERROR_SUCCESS)
	{
		if (GetkeyboardTrigger(DIK_W) == true || GetJoypadTrigger(JOYKEY_UP,0) == true || GetJoypadTrigger(JOYKEY_UP, 1) == true || GetkeyboardTrigger(DIK_UP))
		{//Wがおされた(上)
			PlaySound(SOUND_LABEL_SE_CURSOLMOVE);

			if (g_Pause > PAUSE_MENU_CONTINUE)
			{
				g_Pause--;
			}
		}
		else if (GetkeyboardTrigger(DIK_S) == true || GetJoypadTrigger(JOYKEY_DOWN ,0) == true || GetJoypadTrigger(JOYKEY_DOWN, 1) == true || GetkeyboardTrigger(DIK_DOWN))
		{//Sがおされた(下)
			PlaySound(SOUND_LABEL_SE_CURSOLMOVE);

			if (g_Pause < PAUSE_MENU_QUIT)
			{
				g_Pause++;
			}
		}

		for (int i = 0; i < 2; i++)
		{
			dwResult = XInputGetState(i, &joykeystate);
	
			if (joykeystate.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{//Wがおされた(上)
				PlaySound(SOUND_LABEL_SE_CURSOLMOVE);

				if (g_InputLock[i] == false)
				{
					g_InputLock[i] = true;
					if (g_Pause > PAUSE_MENU_CONTINUE)
					{
						g_Pause--;
					}
				}

			}
			else if (joykeystate.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{//Sがおされた(下)
				PlaySound(SOUND_LABEL_SE_CURSOLMOVE);

				if (g_InputLock[i] == false)
				{
					g_InputLock[i] = true;
					if (g_Pause < PAUSE_MENU_QUIT)
					{
						g_Pause++;
					}
				}
			}
			else
			{
				g_InputLock[i] = false;
			}
			
		}


	}
	else
	{//コントローラーがなかったとき
		if (GetkeyboardTrigger(DIK_W) == true || GetkeyboardTrigger(DIK_UP))
		{//Wがおされた(上)
			if (g_Pause > PAUSE_MENU_CONTINUE)
			{
				g_Pause--;
			}
		}
		else if (GetkeyboardTrigger(DIK_S) == true || GetkeyboardTrigger(DIK_DOWN))
		{//Sがおされた(下)
			if (g_Pause < PAUSE_MENU_QUIT)
			{
				g_Pause++;
			}
		}
	}

	for (nCountPause = 0; nCountPause < NUM_PAUSEUI; nCountPause++)
	{

		//頂点カラーの設定--全体
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 240);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 240);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 240);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 240);

		if (nCountPause == 0)
		{
			g_aPause[nCountPause].pos = D3DXVECTOR3(SCREEN_WIDE / 2, SCREEN_HEIGHT / 2, 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - (SCREEN_WIDE / 2), g_aPause[nCountPause].pos.y - (SCREEN_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + (SCREEN_WIDE / 2), g_aPause[nCountPause].pos.y - (SCREEN_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - (SCREEN_WIDE / 2), g_aPause[nCountPause].pos.y + (SCREEN_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + (SCREEN_WIDE / 2), g_aPause[nCountPause].pos.y + (SCREEN_HEIGHT / 2), 0.0f);
		}
		else if (nCountPause == PAUSE_MENU_CONTINUE)
		{
			g_aPause[nCountPause].pos = D3DXVECTOR3(SCREEN_WIDE / 2, SCREEN_HEIGHT / 3.5f, 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - (MAX_WIDE * 1), g_aPause[nCountPause].pos.y - (MAX_H * 1), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + (MAX_WIDE * 1), g_aPause[nCountPause].pos.y - (MAX_H * 1), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - (MAX_WIDE * 1), g_aPause[nCountPause].pos.y + (MAX_H * 1), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + (MAX_WIDE * 1), g_aPause[nCountPause].pos.y + (MAX_H * 1), 0.0f);
		}
		else if (nCountPause == PAUSE_MENU_RETRY)
		{
			g_aPause[nCountPause].pos = D3DXVECTOR3(SCREEN_WIDE / 2, SCREEN_HEIGHT / 2.4f, 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - (MAX_WIDE * 1), g_aPause[nCountPause].pos.y - (MAX_H * 1), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + (MAX_WIDE * 1), g_aPause[nCountPause].pos.y - (MAX_H * 1), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - (MAX_WIDE * 1), g_aPause[nCountPause].pos.y + (MAX_H * 1), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + (MAX_WIDE * 1), g_aPause[nCountPause].pos.y + (MAX_H * 1), 0.0f);
		}
		else if (nCountPause == PAUSE_MENU_QUIT)
		{
			g_aPause[nCountPause].pos = D3DXVECTOR3(SCREEN_WIDE / 2, SCREEN_HEIGHT / 1.8f, 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - (MAX_WIDE * 1), g_aPause[nCountPause].pos.y - (MAX_H * 1), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + (MAX_WIDE * 1), g_aPause[nCountPause].pos.y - (MAX_H * 1), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - (MAX_WIDE * 1), g_aPause[nCountPause].pos.y + (MAX_H * 1), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + (MAX_WIDE * 1), g_aPause[nCountPause].pos.y + (MAX_H * 1), 0.0f);
		}

		if (nCountPause == g_Pause)
		{//対象のとき
			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 55, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 55, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 55, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 55, 255, 255);
		}

		//決定キー(ENTER)が押されたかどうか
		if (GetkeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_A,0) || GetJoypadTrigger(JOYKEY_A, 1) || GetkeyboardTrigger(DIK_RETURN))
		{
			PlaySound(SOUND_LABEL_SE_DECISION);

			if (g_Pause == PAUSE_MENU_CONTINUE)
			{
				ReleasePause();
			}
			else if (g_Pause == PAUSE_MENU_RETRY)
			{
				SetFade(MODE_GAME);
			}
			else if (g_Pause == PAUSE_MENU_QUIT)
			{
				SetFade(MODE_TITLE);
			}
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
}
//=============================
//ポーズ描画処理
//=============================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();//----------------書き換え済み

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);//-------書き換え済み
	
	int nCountPause = 0;

	for (nCountPause = 0; nCountPause < NUM_PAUSEUI; nCountPause++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePause[nCountPause]);//---------書き換え済み

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類//----------書き換え済み
			nCountPause *4,//描画する最初の頂点インデックス
			2);//描画するプリミティブ数

		
		
	}
	if (g_Pause == PAUSE_MENU_CONTINUE)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.8f, SCREEN_HEIGHT / 1.3f, 0.0f), 60, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "ゲームに戻る");
	}
	else if (g_Pause == PAUSE_MENU_RETRY)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.8f, SCREEN_HEIGHT / 1.3f, 0.0f), 60, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "最初からプレイ");
	}
	else if (g_Pause == PAUSE_MENU_QUIT)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.8f, SCREEN_HEIGHT / 1.3f, 0.0f), 60, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "タイトルに戻る");
	}
//テクスチャを戻す
		pDevice->SetTexture(0, NULL);
}
