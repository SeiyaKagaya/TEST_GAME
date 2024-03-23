//============================================================================================
//
//タイトル表示する処理[title.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "title.h"


#include "player.h"
#include "input.h"
#include "fade.h"

#include "text.h"

#include "sound.h"


#define NUM_TITLE	(3)//title画面の表示数

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitle[NUM_TITLE] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//頂点バッファへのポリゴン
Title g_Title[NUM_TITLE];//タイトルの情報
D3DXCOLOR g_colorfade[NUM_TITLE];
TITLESTATE g_TitleState;//フェード時の識別

bool g_nSkipCnt = false;//Enterで始めれるかどうか
bool g_nButtonCnt = false;//ボタン押せチカチカのやつ

//=============================
//タイトル画面の初期化処理
//=============================
void InitTitle(void)
{
	int nCntTitle = 0;


	g_nSkipCnt = false;
	g_nButtonCnt = false;

	g_TitleState = TITLE_BG;

	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\titleBG.png", &g_pTextureTitle[0]);	//タイトル背景
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\titlespell.png", &g_pTextureTitle[1]);	//ゲームの名前
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pressA.png", &g_pTextureTitle[2]);//ボタン押せ

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 12, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		g_colorfade[nCntTitle] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		//g_colorfade[nCntTitle].a = 0.0f;

		g_Title[nCntTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;//値は固定
		pVtx[1].rhw = 1.0f;//値は固定
		pVtx[2].rhw = 1.0f;//値は固定
		pVtx[3].rhw = 1.0f;//値は固定]

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//頂点座標の更新-----------------------------------
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//テクスチャ座標を設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	PlaySound(SOUND_LABEL_BGM000);
}
//=============================
//タイトル画面の終了処理
//=============================
void UninitTitle(void)
{
	StopSound(SOUND_LABEL_BGM000);

	int nCntTitle = 0;

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		//テクスチャの破棄
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}
//=============================
//タイトル画面の更新処理
//=============================
void UpdateTitle(void)
{
	int nCntTitle = 0;

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		if (nCntTitle == TITLE_BG)
		{//タイトル背景のとき
			g_Title[nCntTitle].pos = D3DXVECTOR3(SCREEN_WIDE / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);

			//頂点座標の更新-----------------------------------
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDE, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDE, SCREEN_HEIGHT, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			if (g_TitleState == TITLE_BG)
			{//背景
				if (g_colorfade[nCntTitle].a < 1.0f)
				{
					g_colorfade[nCntTitle].a += 0.03f;	//ポリゴンを不透明にしていく
				}
				if (g_colorfade[nCntTitle].a >= 1.0f)
				{
					g_colorfade[nCntTitle].a = 1.0f;
					g_TitleState = TITLE_NAME;//名前フェードのタイミング
				}
			}

		}
		else if (nCntTitle == TITLE_NAME)
		{//タイトル名のとき
			g_Title[nCntTitle].pos = D3DXVECTOR3(SCREEN_WIDE * 0.7f, SCREEN_HEIGHT * 0.5f, 0.0f);

			//頂点座標の更新-----------------------------------
			pVtx[0].pos = D3DXVECTOR3(g_Title[nCntTitle].pos.x - 200.0f, g_Title[nCntTitle].pos.y - 200.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Title[nCntTitle].pos.x + 200.0f, g_Title[nCntTitle].pos.y - 200.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Title[nCntTitle].pos.x - 200.0f, g_Title[nCntTitle].pos.y + 200.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Title[nCntTitle].pos.x + 200.0f, g_Title[nCntTitle].pos.y + 200.0f, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			if (g_TitleState == TITLE_NAME)
			{//タイトル文字
				if (g_colorfade[nCntTitle].a < 1.0f)
				{
					g_colorfade[nCntTitle].a += 0.005f;	//ポリゴンを不透明にしていく
				}
				if (g_colorfade[nCntTitle].a >= 1.0f)
				{
					g_colorfade[nCntTitle].a = 1.0f;
					g_TitleState = TITLE_PRESSENTER;
				}
			}
		}
		else if (nCntTitle == TITLE_PRESSENTER)
		{//ボタン押せのとき
			g_Title[nCntTitle].pos = D3DXVECTOR3(SCREEN_WIDE * 0.75f, SCREEN_HEIGHT * 0.9f, 0.0f);


			//頂点座標の更新-----------------------------------
			pVtx[0].pos = D3DXVECTOR3(g_Title[nCntTitle].pos.x - 320.0f, g_Title[nCntTitle].pos.y - 40.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Title[nCntTitle].pos.x + 320.0f, g_Title[nCntTitle].pos.y - 40.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Title[nCntTitle].pos.x - 320.0f, g_Title[nCntTitle].pos.y + 40.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Title[nCntTitle].pos.x + 320.0f, g_Title[nCntTitle].pos.y + 40.0f, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			if (g_TitleState == TITLE_PRESSENTER)
			{//ボタン押せ
				if (g_colorfade[nCntTitle].a < 1.0f)
				{
					g_colorfade[nCntTitle].a += 0.02f;	//ポリゴンを不透明にしていく
				}
				if (g_colorfade[nCntTitle].a >= 1.0f)
				{
					g_colorfade[nCntTitle].a = 1.0f;
					g_TitleState = TITLE_PRESSLOOP;
				}
			}
		}

		if (g_TitleState == TITLE_PRESSLOOP)
		{//ボタンおせループ
			g_nSkipCnt = true;//画面変遷可能へ

			g_colorfade[0].a = 1.0f;
			g_colorfade[1].a = 1.0f;

			if (nCntTitle == TITLE_PRESSENTER)
			{//ボタン押せのとき
				if (g_nButtonCnt == false)
				{
					g_colorfade[nCntTitle].a -= 0.01f;	//ポリゴンを透明にしていく

					if (g_colorfade[nCntTitle].a <= 0.5f)
					{
						g_colorfade[nCntTitle].a = 0.5f;
						g_nButtonCnt = true;
					}
				}
				else if (g_nButtonCnt == true)
				{
					g_colorfade[nCntTitle].a += 0.01f;	//ポリゴンを不透明にしていく

					if (g_colorfade[nCntTitle].a >= 1.0f)
					{
						g_colorfade[nCntTitle].a = 1.0f;
						g_nButtonCnt = false;
					}
				}
			}

		}

		//テクスチャ座標を設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下


		if (nCntTitle == TITLE_PRESSENTER)
		{//ボタン押せのとき
		//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorfade[nCntTitle].a);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorfade[nCntTitle].a);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorfade[nCntTitle].a);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorfade[nCntTitle].a);
		}
		else
		{
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorfade[nCntTitle].a);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorfade[nCntTitle].a);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorfade[nCntTitle].a);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorfade[nCntTitle].a);
		}

		pVtx += 4;
	}

	if (GetkeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A, 0) == true || GetJoypadTrigger(JOYKEY_A, 1) == true)
	{//決定キー(Enterキー)が押された
		PlaySound(SOUND_LABEL_SE_DECISION);

		if (g_nSkipCnt == false)
		{//まだ画面動いてる中
			g_TitleState = TITLE_PRESSLOOP;
		}
		else if (g_nSkipCnt == true)
		{
			//	PlaySound(SOUND_LABEL_SE_ENTER001);
			SetFade(MODE_MENU);
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}
//=============================
//タイトル画面の描画処理
//=============================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();//----------------書き換え済み

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);//-------書き換え済み

	int nCntTitle = 0;

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCntTitle]);//---------書き換え済み

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類//----------書き換え済み
			nCntTitle * 4,//描画する最初の頂点インデックス
			2);//描画するプリミティブ数

		
		//テクスチャを戻す
		pDevice->SetTexture(0, NULL);
	}
}
