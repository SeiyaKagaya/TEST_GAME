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
#include "icon.h"
#include "fade.h"
#include "Film.h"
#include "MenuFrame.h"
#include "menu.h"

#define NUM_ICONTEXTURE	(2)			//メニューのテクスチャ数
#define NUM_ICONUI		(3)			//メニューの表示ポリゴンの数
#define NUM_SELECTUI	(3)			//選択肢の数
#define MAX_WIDE		(200)		//横幅
#define MAX_HEIGH		(40)		//縦幅
#define MAXICONSIZE		(520.0f)	//アイコンの端から端までの最大サイズ
#define MINICONSIZE		(000.1f)	//アイコンの端から端までの最小サイズ
#define ROLLICONSPEED	(040.0f)		//アイコンが選択されたときのサイズ変更のスピード(f/1)

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureIcon[NUM_ICONTEXTURE] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffIcon = NULL;//頂点バッファへのポリゴン
ICON g_aIcon[NUM_ICONUI];	//メニュー構造体の情報

int g_Icon = 0;//メニュー情報
bool bMagColorIcon = false;
float fChangeColorIcon = 1.3f;

//=============================
//メニュー初期化処理
//=============================
void InitIcon(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//メニュー情報の初期化
	g_Icon = START_ICON_GAME;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\IconFrame.png", &g_pTextureIcon[0]);//--------書き換え済み//とりあえず
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\IconSpell.png", &g_pTextureIcon[1]);//--------書き換え済み

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_ICONUI, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffIcon, NULL);

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffIcon->Lock(0, 0, (void**)&pVtx, 0);

	int nCountIcon = 0;

	for (nCountIcon = 0; nCountIcon < NUM_ICONUI; nCountIcon++)
	{
		g_aIcon[nCountIcon].pos = D3DXVECTOR3(SCREEN_WIDE / 2, SCREEN_HEIGHT / 2, 0.0f);
		g_aIcon[nCountIcon].texX = MINICONSIZE;
		g_aIcon[nCountIcon].bUse = false;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aIcon[nCountIcon].pos.x - MAX_WIDE, g_aIcon[nCountIcon].pos.y - MAX_HEIGH, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aIcon[nCountIcon].pos.x + MAX_WIDE, g_aIcon[nCountIcon].pos.y - MAX_HEIGH, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aIcon[nCountIcon].pos.x - MAX_WIDE, g_aIcon[nCountIcon].pos.y + MAX_HEIGH, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aIcon[nCountIcon].pos.x + MAX_WIDE, g_aIcon[nCountIcon].pos.y + MAX_HEIGH, 0.0f);

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
	g_pVtxBuffIcon->Unlock();
}
//=============================
//メニュー終了処理
//=============================
void UninitIcon(void)
{
	int nCountIcon = 0;

	for (nCountIcon = 0; nCountIcon < NUM_ICONTEXTURE; nCountIcon++)
	{
		//テクスチャの破棄
		if (g_pTextureIcon[nCountIcon] != NULL)
		{
			g_pTextureIcon[nCountIcon]->Release();
			g_pTextureIcon[nCountIcon] = NULL;
		}
		//頂点バッファの破棄
		if (g_pVtxBuffIcon != NULL)
		{
			g_pVtxBuffIcon->Release();
			g_pVtxBuffIcon = NULL;
		}
	}
}
//=============================
//メニュー更新処理
//=============================
void UpdateIcon(void)
{
	XINPUT_STATE joykeystate;

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffIcon->Lock(0, 0, (void**)&pVtx, 0);

	int nCountIcon = 0;

	DWORD dwResult = XInputGetState(0, &joykeystate);

	//if (dwResult == ERROR_SUCCESS)
	//{
	//	//if (GetkeyboardTrigger(DIK_W) == true || GetJoypadTrigger(JOYKEY_UP, 0) == true || GetJoypadTrigger(JOYKEY_UP, 1) == true || joykeystate.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || GetkeyboardTrigger(DIK_UP))
	//	//{//Wがおされた(上)
	//	//	if (g_Icon > START_ICON_GAME)
	//	//	{//ゲームスタートに到達するまではマイナスする
	//		//	g_Icon--;
	//	//	}
	//	//	else
	//	//	{//ゲームスタートより下に行こうとしたら一番下(タイトル)に戻る
	//	//		g_Icon = START_ICON_TITLE;
	//	//	}

	//	//}
	//	//else if (GetkeyboardTrigger(DIK_S) == true || GetJoypadTrigger(JOYKEY_DOWN, 0) == true || GetJoypadTrigger(JOYKEY_DOWN, 1) == true || joykeystate.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || GetkeyboardTrigger(DIK_DOWN))
	//	//{//Sがおされた(下)
	//	//	if (g_Icon < START_ICON_TITLE)
	//	//	{//タイトルに到達するまでプラスする
	//	//		g_Icon++;
	//	//	}
	//	//	else
	//	//	{//タイトルより上に行こうとしたら一番上(ゲームスタート)に戻る
	//	//		g_Icon = START_ICON_GAME;
	//	//	}
	//	//}
	//	
	//}
	//else
	//{//コントローラーがなかったとき
	//	if (GetkeyboardTrigger(DIK_W) == true || GetkeyboardTrigger(DIK_UP))
	//	{//Wがおされた(上)
	//		if (g_Icon > START_ICON_GAME)
	//		{
	//			g_Icon--;
	//		}
	//		else
	//		{//ゲームスタートより下に行こうとしたら一番下(タイトル)に戻る
	//			g_Icon = START_ICON_TITLE;
	//		}
	//	}
	//	else if (GetkeyboardTrigger(DIK_S) == true || GetkeyboardTrigger(DIK_DOWN))
	//	{//Sがおされた(下)
	//		if (g_Icon < START_ICON_TITLE)
	//		{
	//			g_Icon++;
	//		}
	//		else
	//		{//タイトルより上に行こうとしたら一番上(ゲームスタート)に戻る
	//			g_Icon = START_ICON_GAME;
	//		}
	//	}
	//}

	g_Icon = GetMenu1()-1;

	for (nCountIcon = 0; nCountIcon < NUM_ICONUI; nCountIcon++)
	{
		if (nCountIcon == START_ICON_GAME)
		{
			g_aIcon[nCountIcon].pos = D3DXVECTOR3(SCREEN_WIDE * 0.05, SCREEN_HEIGHT / 3.0f, 0.0f);// ここで文字の位置変える
		}
		else if (nCountIcon == START_ICON_TUTORIAL)
		{
			g_aIcon[nCountIcon].pos = D3DXVECTOR3(SCREEN_WIDE * 0.05, SCREEN_HEIGHT / 1.75f, 0.0f);

		}
		else if (nCountIcon == START_ICON_TITLE)
		{
			g_aIcon[nCountIcon].pos = D3DXVECTOR3(SCREEN_WIDE * 0.05, SCREEN_HEIGHT / 1.23f, 0.0f);
		}

		if (nCountIcon == g_Icon)
		{//対象のとき
			if (g_aIcon[nCountIcon].texX < MAXICONSIZE - ROLLICONSPEED + 1.0f)
			{
				g_aIcon[nCountIcon].texX += ROLLICONSPEED;
			}

			g_aIcon[nCountIcon].bUse = true;
		}
		else
		{
			g_aIcon[nCountIcon].texX = MINICONSIZE;
			g_aIcon[nCountIcon].bUse = false;
		}

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aIcon[nCountIcon].pos.x,							g_aIcon[nCountIcon].pos.y - (MAX_HEIGH * fChangeColorIcon), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aIcon[nCountIcon].pos.x + g_aIcon[nCountIcon].texX, g_aIcon[nCountIcon].pos.y - (MAX_HEIGH * fChangeColorIcon), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aIcon[nCountIcon].pos.x,							g_aIcon[nCountIcon].pos.y + (MAX_HEIGH * fChangeColorIcon), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aIcon[nCountIcon].pos.x + g_aIcon[nCountIcon].texX, g_aIcon[nCountIcon].pos.y + (MAX_HEIGH * fChangeColorIcon), 0.0f);


		//決定キー(ENTER)が押されたかどうか
		if (GetkeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_A, 0) || GetJoypadTrigger(JOYKEY_A, 1) || GetkeyboardTrigger(DIK_RETURN))
		{
			if (g_Icon == START_ICON_GAME)
			{
				SetFade(MODE_GAME);
			}
			else if (g_Icon == START_ICON_TUTORIAL)
			{
				SetFade(MODE_TUTORIAL);
			}
			else if (g_Icon == START_ICON_TITLE)
			{
				SetFade(MODE_TITLE);
			}
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffIcon->Unlock();
}
//=============================
//メニュー描画処理
//=============================
void DrawIcon(void)
{

	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();//----------------書き換え済み

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffIcon, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);//-------書き換え済み

	int nCountIcon = 0;

	for (nCountIcon = 0; nCountIcon < NUM_ICONUI; nCountIcon++)
	{
		if (g_aIcon[nCountIcon].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureIcon[0]);//---------書き換え済み

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類//----------書き換え済み
				nCountIcon * 4,//描画する最初の頂点インデックス
				2);//描画するプリミティブ数
		}
	}

	//DrawIconFrame();

	//// 背景の描画処理
	//DrawFILM();
}

int GetIcon(void)
{
	return g_Icon;
}
