//============================================================================================
//
//タイトル表示する処理[screenui.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "screenui.h"
#include "text.h"


//#include "player.h"
#//include "input.h"
//#include "fade.h"
//#include "sound.h"




//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureScreenUI[NUM_UI] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScreenUI = NULL;//頂点バッファへのポリゴン
ScreenUI g_ScreenUI[MAX_UI];//タイトルの情報
//D3DXCOLOR g_colorfade[NUM_UI];
SCREENUISTATE g_ScreenUIState;//フェード時の識別

ScreenState g_ScreenState[MAX_UI];

//=============================
//スクリーンUIの初期化処理
//=============================
void InitScreenUI(void)
{
	for (int i = 0; i < MAX_UI; i++)
	{
		g_ScreenState[i].MoneyBox_bUse = false;
		g_ScreenState[i].TV_bUse = false;
	}

	int nCntScreenUI = 0;

	g_ScreenUIState = SCREENUI_MAX;

	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\yoko.png", &g_pTextureScreenUI[0]);	//十字キー
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Watch.png", &g_pTextureScreenUI[1]);	//時計
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\start.png", &g_pTextureScreenUI[2]);	//START

			//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4* MAX_UI, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffScreenUI, NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScreenUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScreenUI = 0; nCntScreenUI < MAX_UI; nCntScreenUI++)
	{
		g_ScreenUI[nCntScreenUI].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ScreenUI[nCntScreenUI].bUse = false;
		g_ScreenUI[nCntScreenUI].type = SCREENUI_MAX;

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
	g_pVtxBuffScreenUI->Unlock();

	SetScreenUI(D3DXVECTOR3(85.0f, 550.0f, 0.0f), SCREENUI_CROSS_0);
	SetScreenUI(D3DXVECTOR3(SCREEN_WIDE / 2.0f + 85.0f, 550.0f, 0.0f), SCREENUI_CROSS_1);

	SetScreenUI(D3DXVECTOR3(SCREEN_WIDE / 2.0f - 85.0f, SCREEN_HEIGHT - 697.0f, 0.0f), SCREENUI_WATCH);

	SetScreenUI(D3DXVECTOR3(20.0f, 700.0f, 0.0f), SCREENUI_START);
	SetScreenUI(D3DXVECTOR3(SCREEN_WIDE / 2.0f + 20.0f, 700.0f, 0.0f), SCREENUI_START);
}
//=============================
//スクリーンUIの終了処理
//=============================
void UninitScreenUI(void)
{
	//StopSound(SOUND_LABEL_BGM000);

	int nCntScreenUI = 0;

	for (nCntScreenUI = 0; nCntScreenUI < NUM_UI; nCntScreenUI++)
	{
		//テクスチャの破棄
		if (g_pTextureScreenUI[nCntScreenUI] != NULL)
		{
			g_pTextureScreenUI[nCntScreenUI]->Release();
			g_pTextureScreenUI[nCntScreenUI] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffScreenUI != NULL)
	{
		g_pVtxBuffScreenUI->Release();
		g_pVtxBuffScreenUI = NULL;
	}
}
//=============================
//スクリーンUIの更新処理
//=============================
void UpdateScreenUI(void)
{
	int nCntScreenUI = 0;

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScreenUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScreenUI = 0; nCntScreenUI < MAX_UI; nCntScreenUI++)
	{
		if (g_ScreenUI[nCntScreenUI].bUse == true)
		{
			if (g_ScreenUI[nCntScreenUI].type == SCREENUI_CROSS_0)
			{//十字きー
			//	g_ScreenUI[nCntScreenUI].pos = D3DXVECTOR3(SCREEN_WIDE / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
			}
			else if (g_ScreenUI[nCntScreenUI].type == SCREENUI_CROSS_1)
			{//時計のとき
			//	g_ScreenUI[nCntScreenUI].pos = D3DXVECTOR3((SCREEN_WIDE / 2.0f) - 90.0f, SCREEN_HEIGHT - 700.0f, 0.0f);
			}
			else if (g_ScreenUI[nCntScreenUI].type == SCREENUI_WATCH)
			{//時計のとき

			}

			pVtx += 4;
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffScreenUI->Unlock();
}
//=============================
//スクリーンUIの描画処理
//=============================
void DrawScreenUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();//----------------書き換え済み

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScreenUI, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);//-------書き換え済み

	int nCntScreenUI = 0;
	int TexNum = 0;
	for (nCntScreenUI = 0; nCntScreenUI < MAX_UI; nCntScreenUI++)
	{
		if (g_ScreenUI[nCntScreenUI].bUse == true)
		{
			if (g_ScreenUI[nCntScreenUI].type == SCREENUI_CROSS_0 || g_ScreenUI[nCntScreenUI].type == SCREENUI_CROSS_1)
			{//
				TexNum = 0;
			}
			else if (g_ScreenUI[nCntScreenUI].type == SCREENUI_WATCH)
			{//時計のとき
				TexNum = 1;
			}
			else if (g_ScreenUI[nCntScreenUI].type == SCREENUI_START)
			{//時計のとき
				TexNum = 2;
			}
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureScreenUI[TexNum]);//---------書き換え済み

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類//----------書き換え済み
				nCntScreenUI * 4,//描画する最初の頂点インデックス
				2);//描画するプリミティブ数
		}
		
	}

	//テクスチャを戻す
	pDevice->SetTexture(0, NULL);




	if (g_ScreenState[0].MoneyBox_bUse==true)
	{
		//左画面
		DrawTextSet(D3DXVECTOR3(4.0f, 525.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), "ダイヤル\n   選択");//左

		DrawTextSet(D3DXVECTOR3(4.0f, 503.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(0.7f, 0.7f, 1.0f, 1.0f), "ダイヤル回転");//上
	}
	else if(g_ScreenState[0].TV_bUse == true)
	{
		DrawTextSet(D3DXVECTOR3(4.0f, 503.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(0.7f, 0.7f, 1.0f, 1.0f), "チャンネル切換");//上
	}
	else
	{
		//左画面
		DrawTextSet(D3DXVECTOR3(4.0f, 525.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), "アイテム\n   選択");//左

		DrawTextSet(D3DXVECTOR3(4.0f, 503.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(0.7f, 0.7f, 1.0f, 1.0f), "アイテム使用");//上
	}

	if (g_ScreenState[1].MoneyBox_bUse == true)
	{
		//右画面
		DrawTextSet(D3DXVECTOR3(4.0f + (SCREEN_WIDE / 2.0f), 525.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), "ダイヤル\n   選択");//左

		DrawTextSet(D3DXVECTOR3(4.0f + (SCREEN_WIDE / 2.0f), 503.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(0.7f, 0.7f, 1.0f, 1.0f), "ダイヤル回転");//上
	}
	else if (g_ScreenState[1].TV_bUse == true)
	{

		DrawTextSet(D3DXVECTOR3(4.0f + (SCREEN_WIDE / 2.0f), 503.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(0.7f, 0.7f, 1.0f, 1.0f), "チャンネル切換");//上

	}
	else
	{
		//右画面
		DrawTextSet(D3DXVECTOR3(4.0f + (SCREEN_WIDE / 2.0f), 525.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), "アイテム\n   選択");//左

		DrawTextSet(D3DXVECTOR3(4.0f + (SCREEN_WIDE / 2.0f), 503.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(0.7f, 0.7f, 1.0f, 1.0f), "アイテム使用");//上

	}



	for (int i = 0; i < MAX_UI; i++)
	{
		g_ScreenState[i].MoneyBox_bUse = false;
		g_ScreenState[i].TV_bUse = false;
	}

	DrawTextSet(D3DXVECTOR3(32.0f, 688.0f, 0.0f), 22, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), " :ポーズ");//左
	DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.0f + 32.0f, 688.0f, 0.0f), 22, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), " :ポーズ");//上
}
//=============================
//スクリーンUIの設定処理
//=============================
void SetScreenUI(D3DXVECTOR3 pos, SCREENUISTATE UItype)
{
	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScreenUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScreenUI = 0; nCntScreenUI < MAX_UI; nCntScreenUI++)
	{
		if (g_ScreenUI[nCntScreenUI].bUse == false)
		{
			g_ScreenUI[nCntScreenUI].pos = pos;
			g_ScreenUI[nCntScreenUI].bUse = true;
			g_ScreenUI[nCntScreenUI].type = UItype;

			if (g_ScreenUI[nCntScreenUI].type == SCREENUI_CROSS_0)
			{//
				//頂点座標の更新-----------------------------------
				pVtx[0].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x - CROSSSIZE, g_ScreenUI[nCntScreenUI].pos.y - CROSSSIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x + CROSSSIZE, g_ScreenUI[nCntScreenUI].pos.y - CROSSSIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x - CROSSSIZE, g_ScreenUI[nCntScreenUI].pos.y + CROSSSIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x + CROSSSIZE, g_ScreenUI[nCntScreenUI].pos.y + CROSSSIZE, 0.0f);

			}
			else if (g_ScreenUI[nCntScreenUI].type == SCREENUI_CROSS_1)
			{//
				//頂点座標の更新-----------------------------------
				pVtx[0].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x - CROSSSIZE, g_ScreenUI[nCntScreenUI].pos.y - CROSSSIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x + CROSSSIZE, g_ScreenUI[nCntScreenUI].pos.y - CROSSSIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x - CROSSSIZE, g_ScreenUI[nCntScreenUI].pos.y + CROSSSIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x + CROSSSIZE, g_ScreenUI[nCntScreenUI].pos.y + CROSSSIZE, 0.0f);

			}
			else if (g_ScreenUI[nCntScreenUI].type == SCREENUI_WATCH)
			{//時計のとき
				//頂点座標の更新-----------------------------------
				pVtx[0].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x - WATCHSIZE, g_ScreenUI[nCntScreenUI].pos.y - WATCHSIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x + WATCHSIZE, g_ScreenUI[nCntScreenUI].pos.y - WATCHSIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x - WATCHSIZE, g_ScreenUI[nCntScreenUI].pos.y + WATCHSIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x + WATCHSIZE, g_ScreenUI[nCntScreenUI].pos.y + WATCHSIZE, 0.0f);				
			}
			else if (g_ScreenUI[nCntScreenUI].type == SCREENUI_START)
			{//ボタン
				//頂点座標の更新-----------------------------------
				pVtx[0].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x - STARTSIZE, g_ScreenUI[nCntScreenUI].pos.y - STARTSIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x + STARTSIZE, g_ScreenUI[nCntScreenUI].pos.y - STARTSIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x - STARTSIZE, g_ScreenUI[nCntScreenUI].pos.y + STARTSIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x + STARTSIZE, g_ScreenUI[nCntScreenUI].pos.y + STARTSIZE, 0.0f);
			}


			//テクスチャ座標を設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			break;
		}

		pVtx += 4;//ポインタを４つ進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffScreenUI->Unlock();
}
//=============================
//スクリーンUIの取得処理
//=============================
ScreenState* GetScreenState(void)
{
	return &g_ScreenState[0];
}