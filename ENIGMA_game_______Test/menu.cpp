//=========================================================
//
//メニュー画面の処理関係[menu.cpp]
// Author kaito hondo
//
//=========================================================
#include "main.h"
#include "Tutorial.h"
#include "input.h"
#include "game.h"
#include "menu.h"
#include "fade.h"
#include "Film.h"
#include "MenuFrame.h"
#include"sound.h"
#include "sound.h"

#define NUM_MENUTEXTURE	(3)			//メニューのテクスチャ数
#define NUM_MENUUI		(4)			//メニューの表示ポリゴンの数
#define NUM_SELECTUI	(3)			//選択肢の数
#define MAX_WIDE		(200)		//横幅
#define MAX_HEIGH		(30)		//縦幅
#define MAX_MAG			(1.3f)		//選択時の最大倍率
#define MIN_MAG			(1.2f)		//選択時の最小倍率
#define CHANGEVALUE		(0.001f)	//選択時の拡縮倍率

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureMenu[NUM_MENUTEXTURE] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMenu = NULL;//頂点バッファへのポリゴン
MENU g_aMenu[NUM_MENUUI];	//メニュー構造体の情報

int g_Menu = 0;//メニュー情報
bool bMagColor = false;
float fChangeColor = 1.0f;
bool g_InputLock2[2] = {};
//=============================
//メニュー初期化処理
//=============================
void InitMenu(void)
{
	//InitMenuFrame();

	//// 背景の初期化処理
	//InitFILM();

	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

//	int nCntMenu = 0;

	//メニュー情報の初期化
	g_Menu = START_MENU_GAME;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\MenuFrameBG.png", &g_pTextureMenu[0]);//--------書き換え済み//とりあえず
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\MenuSpell.png", &g_pTextureMenu[1]);//--------書き換え済み

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_MENUUI, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMenu, NULL);

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMenu->Lock(0, 0, (void**)&pVtx, 0);

	int nCountMenu = 0;

	for (nCountMenu = 0; nCountMenu < NUM_MENUUI; nCountMenu++)
	{
		g_aMenu[nCountMenu].pos = D3DXVECTOR3(SCREEN_WIDE / 2, SCREEN_HEIGHT / 2, 0.0f);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x - MAX_WIDE, g_aMenu[nCountMenu].pos.y - MAX_HEIGH, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x + MAX_WIDE, g_aMenu[nCountMenu].pos.y - MAX_HEIGH, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x - MAX_WIDE, g_aMenu[nCountMenu].pos.y + MAX_HEIGH, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x + MAX_WIDE, g_aMenu[nCountMenu].pos.y + MAX_HEIGH, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffMenu->Unlock();

	g_InputLock2[0] = false;//-が下0がニュートラ+が上
	g_InputLock2[1] = false;
	PlaySound(SOUND_LABEL_BGM004);
}
//=============================
//メニュー終了処理
//=============================
void UninitMenu(void)
{
	StopSound(SOUND_LABEL_BGM004);
	//UninitMenuFrame();

	//// 背景の終了処理
	//UninitFILM();

	int nCountMenu = 0;

	for (nCountMenu = 0; nCountMenu < NUM_MENUTEXTURE; nCountMenu++)
	{
		//テクスチャの破棄
		if (g_pTextureMenu[nCountMenu] != NULL)
		{
			g_pTextureMenu[nCountMenu]->Release();
			g_pTextureMenu[nCountMenu] = NULL;
		}
		//頂点バッファの破棄
		if (g_pVtxBuffMenu != NULL)
		{
			g_pVtxBuffMenu->Release();
			g_pVtxBuffMenu = NULL;
		}
	}
}
//=============================
//メニュー更新処理
//=============================
void UpdateMenu(void)
{
	//UpdateMenuFrame();

	//UpdateFILM();

	XINPUT_STATE joykeystate;

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMenu->Lock(0, 0, (void**)&pVtx, 0);

	int nCountMenu = 0;
	int EscapeInput = 0;
	DWORD dwResult = XInputGetState(0, &joykeystate);

	if (dwResult == ERROR_SUCCESS)
	{
		if (GetkeyboardTrigger(DIK_W) == true || GetJoypadTrigger(JOYKEY_UP, 0) == true || GetJoypadTrigger(JOYKEY_UP, 1) == true || GetkeyboardTrigger(DIK_UP))
		{//Wがおされた(上)
			PlaySound(SOUND_LABEL_SE_CURSOLMOVE);
			if (g_Menu > START_MENU_GAME)
			{//ゲームスタートに到達するまではマイナスする
				g_Menu--;
			}
			else
			{//ゲームスタートより下に行こうとしたら一番下(タイトル)に戻る
				g_Menu = START_MENU_TITLE;
			}

		}
		else if (GetkeyboardTrigger(DIK_S) == true || GetJoypadTrigger(JOYKEY_DOWN, 0) == true || GetJoypadTrigger(JOYKEY_DOWN, 1) == true|| GetkeyboardTrigger(DIK_DOWN))
		{//Sがおされた(下)
			PlaySound(SOUND_LABEL_SE_CURSOLMOVE);
			if (g_Menu < START_MENU_TITLE)
			{//タイトルに到達するまでプラスする
				g_Menu++;
			}
			else
			{//タイトルより上に行こうとしたら一番上(ゲームスタート)に戻る
				g_Menu = START_MENU_GAME;
			}
		}

		for (int i = 0; i < 2; i++)
		{
			dwResult = XInputGetState(i, &joykeystate);

			if (joykeystate.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{//Wがおされた(上)
				if (g_InputLock2[i] == false)
				{
					PlaySound(SOUND_LABEL_SE_CURSOLMOVE);
					g_InputLock2[i] = true;
					//if (g_Menu < START_MENU_TITLE)
					//{//タイトルに到達するまでプラスする
					//	g_Menu++;
					//}
					//else
					//{//タイトルより上に行こうとしたら一番上(ゲームスタート)に戻る
					//	g_Menu = START_MENU_GAME;
					//}
					if (g_Menu > START_MENU_GAME)
					{//ゲームスタートに到達するまではマイナスする
						g_Menu--;
					}
					else
					{//ゲームスタートより下に行こうとしたら一番下(タイトル)に戻る
						g_Menu = START_MENU_TITLE;
					}
				}
			}
			else if (joykeystate.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{//Sがおされた(下)
				if (g_InputLock2[i] == false)
				{
					PlaySound(SOUND_LABEL_SE_CURSOLMOVE);

					g_InputLock2[i] = true;
					//if (g_Menu > START_MENU_GAME)
					//{//ゲームスタートに到達するまではマイナスする
					//	g_Menu--;
					//}
					//else
					//{//ゲームスタートより下に行こうとしたら一番下(タイトル)に戻る
					//	g_Menu = START_MENU_TITLE;
					//}


					if (g_Menu < START_MENU_TITLE)
					{//タイトルに到達するまでプラスする
						g_Menu++;
					}
					else
					{//タイトルより上に行こうとしたら一番上(ゲームスタート)に戻る
						g_Menu = START_MENU_GAME;
					}
				}	
			}
			else
			{
				g_InputLock2[i] = false;
			}
		}



	}
	else
	{//コントローラーがなかったとき
		if (GetkeyboardTrigger(DIK_W) == true || GetkeyboardTrigger(DIK_UP))
		{//Wがおされた(上)
			if (g_Menu > START_MENU_GAME)
			{
				g_Menu--;
			}
			else
			{//ゲームスタートより下に行こうとしたら一番下(タイトル)に戻る
				g_Menu = START_MENU_TITLE;
			}
		}
		else if (GetkeyboardTrigger(DIK_S) == true || GetkeyboardTrigger(DIK_DOWN))
		{//Sがおされた(下)
			if (g_Menu < START_MENU_TITLE)
			{
				g_Menu++;
			}
			else
			{//タイトルより上に行こうとしたら一番上(ゲームスタート)に戻る
				g_Menu = START_MENU_GAME;
			}
		}
	}

	for (nCountMenu = 0; nCountMenu < NUM_MENUUI; nCountMenu++)
	{
		if (nCountMenu == START_MENU_BG)
		{
			g_aMenu[nCountMenu].pos = D3DXVECTOR3(SCREEN_WIDE / 2, SCREEN_HEIGHT / 2, 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x - (SCREEN_WIDE / 2), g_aMenu[nCountMenu].pos.y - (SCREEN_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x + (SCREEN_WIDE / 2), g_aMenu[nCountMenu].pos.y - (SCREEN_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x - (SCREEN_WIDE / 2), g_aMenu[nCountMenu].pos.y + (SCREEN_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x + (SCREEN_WIDE / 2), g_aMenu[nCountMenu].pos.y + (SCREEN_HEIGHT / 2), 0.0f);
		}
		else if (nCountMenu == START_MENU_GAME)
		{
			g_aMenu[nCountMenu].pos = D3DXVECTOR3(SCREEN_WIDE / 4, SCREEN_HEIGHT / 3.0f, 0.0f);// ここで文字の位置変える

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x - (MAX_WIDE * 1), g_aMenu[nCountMenu].pos.y - (MAX_HEIGH * 1), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x + (MAX_WIDE * 1), g_aMenu[nCountMenu].pos.y - (MAX_HEIGH * 1), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x - (MAX_WIDE * 1), g_aMenu[nCountMenu].pos.y + (MAX_HEIGH * 1), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x + (MAX_WIDE * 1), g_aMenu[nCountMenu].pos.y + (MAX_HEIGH * 1), 0.0f);

			//テキスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.00f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.00f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.25f);

		}
		else if (nCountMenu == START_MENU_TUTORIAL)
		{
			g_aMenu[nCountMenu].pos = D3DXVECTOR3(SCREEN_WIDE / 4, SCREEN_HEIGHT / 1.75f, 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x - (MAX_WIDE * 1), g_aMenu[nCountMenu].pos.y - (MAX_HEIGH * 1), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x + (MAX_WIDE * 1), g_aMenu[nCountMenu].pos.y - (MAX_HEIGH * 1), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x - (MAX_WIDE * 1), g_aMenu[nCountMenu].pos.y + (MAX_HEIGH * 1), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x + (MAX_WIDE * 1), g_aMenu[nCountMenu].pos.y + (MAX_HEIGH * 1), 0.0f);

			//テキスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.25f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.25f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.50f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.50f);
		}
		else if (nCountMenu == START_MENU_TITLE)
		{
			g_aMenu[nCountMenu].pos = D3DXVECTOR3(SCREEN_WIDE / 4, SCREEN_HEIGHT / 1.23f, 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x - (MAX_WIDE * 1), g_aMenu[nCountMenu].pos.y - (MAX_HEIGH * 1), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x + (MAX_WIDE * 1), g_aMenu[nCountMenu].pos.y - (MAX_HEIGH * 1), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x - (MAX_WIDE * 1), g_aMenu[nCountMenu].pos.y + (MAX_HEIGH * 1), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x + (MAX_WIDE * 1), g_aMenu[nCountMenu].pos.y + (MAX_HEIGH * 1), 0.0f);

			//テキスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.50f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.50f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.75f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.75f);

		}

		if (bMagColor == false)
		{
			fChangeColor += CHANGEVALUE;
			if (fChangeColor >= MAX_MAG)
			{
				bMagColor = true;
			}
		}
		else
		{
			fChangeColor -= CHANGEVALUE;
			if (fChangeColor <= MIN_MAG)
			{
				bMagColor = false;
			}
		}

		if (nCountMenu == g_Menu)
		{//対象のとき
			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(180, 180, 180, 255);
			pVtx[1].col = D3DCOLOR_RGBA(180, 180, 180, 255);
			pVtx[2].col = D3DCOLOR_RGBA(180, 180, 180, 255);
			pVtx[3].col = D3DCOLOR_RGBA(180, 180, 180, 255);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x - (MAX_WIDE * fChangeColor), g_aMenu[nCountMenu].pos.y - (MAX_HEIGH * fChangeColor), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x + (MAX_WIDE * fChangeColor), g_aMenu[nCountMenu].pos.y - (MAX_HEIGH * fChangeColor), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x - (MAX_WIDE * fChangeColor), g_aMenu[nCountMenu].pos.y + (MAX_HEIGH * fChangeColor), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMenu[nCountMenu].pos.x + (MAX_WIDE * fChangeColor), g_aMenu[nCountMenu].pos.y + (MAX_HEIGH * fChangeColor), 0.0f);
		}
		else
		{
			if (nCountMenu != START_MENU_BG)
			{
				//頂点カラーの設定--全体
				pVtx[0].col = D3DCOLOR_RGBA(130, 80, 80, 255);
				pVtx[1].col = D3DCOLOR_RGBA(130, 80, 80, 255);
				pVtx[2].col = D3DCOLOR_RGBA(130, 80, 80, 255);
				pVtx[3].col = D3DCOLOR_RGBA(130, 80, 80, 255);
			}
		}

		//決定キー(ENTER)が押されたかどうか
		if (GetkeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_A, 0) || GetJoypadTrigger(JOYKEY_A, 1) || GetkeyboardTrigger(DIK_RETURN))
		{
			PlaySound(SOUND_LABEL_SE_DECISION);

			if (g_Menu == START_MENU_GAME)
			{
				SetFade(MODE_GAME);
			}
			else if (g_Menu == START_MENU_TUTORIAL)
			{
				SetFade(MODE_TUTORIAL);
			}
			else if (g_Menu == START_MENU_TITLE)
			{
				SetFade(MODE_TITLE);
			}
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffMenu->Unlock();
}
//=============================
//メニュー描画処理
//=============================
void DrawMenu(void)
{

	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();//----------------書き換え済み

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMenu, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);//-------書き換え済み

	int nCountMenu = 0;

	for (nCountMenu = 0; nCountMenu < NUM_MENUUI; nCountMenu++)
	{
		switch (nCountMenu)
		{
		case START_MENU_BG:
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureMenu[0]);//---------書き換え済み
			break;
		default:
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureMenu[1]);//---------書き換え済み
			break;
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類//----------書き換え済み
			nCountMenu * 4,//描画する最初の頂点インデックス
			2);//描画するプリミティブ数
	}

	//DrawMenuFrame();

	//// 背景の描画処理
	//DrawFILM();
}

int GetMenu1(void)
{
	return g_Menu;
}
