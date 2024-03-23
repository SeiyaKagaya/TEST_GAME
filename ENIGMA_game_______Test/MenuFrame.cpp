//==============================
//
// メニュー[MenuFrame.cpp]
// Author:Kaito Hondo
//
//==============================

#include "main.h"
#include "MenuFrame.h"
#include "menu.h"
#include "Film.h"
#include "corkboard.h"
#include "Icon.h"

// マクロ定義
#define NUM_MENUFRAME	(1)// 背景の数

// グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureMenuFrame[NUM_MENUFRAME] = {};	// テクスチャ（1枚分）へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMenuFrame = NULL;	// 頂点バッファへのポインタ

// 背景の初期化処理
void InitMenuFrame(void)
{
	// 背景の初期化処理
	InitFILM();

	InitIcon();

	InitMenu();

	InitCorkboard();


	LPDIRECT3DDEVICE9 pDevice;
	int nCntMenuFrame;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MenuFrame_TEXTURE, &g_apTextureMenuFrame[0]);


	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_MENUFRAME, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMenuFrame, NULL);

	VERTEX_2D* pVtx;

	// 頂点バッファをロックし、頂点データへのポインタを獲得
	g_pVtxBuffMenuFrame->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMenuFrame = 0; nCntMenuFrame < NUM_MENUFRAME; nCntMenuFrame++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDE, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDE, SCREEN_HEIGHT, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

		//テキスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;// 頂点データのポインタを４つ分進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffMenuFrame->Unlock();
}

// 背景の終了処理
void UninitMenuFrame(void)
{
	// 背景の終了処理
	UninitFILM();

	UninitIcon();

	UninitMenu();

	UninitCorkboard();


	int nCount;

	// テクスチャの破棄
	for (nCount = 0; nCount < NUM_MENUFRAME; nCount++)
	{

		if (g_apTextureMenuFrame[nCount] != NULL)
		{
			g_apTextureMenuFrame[nCount]->Release();
			g_apTextureMenuFrame[nCount] = NULL;
		}
	}
	// 頂点バッファの破棄
	if (g_pVtxBuffMenuFrame != NULL)
	{
		g_pVtxBuffMenuFrame->Release();
		g_pVtxBuffMenuFrame = NULL;
	}
}

// 背景の更新処理
void UpdateMenuFrame(void)
{
	UpdateFILM();

	UpdateIcon();

	UpdateMenu();

	UpdateCorkboard();

}

// 背景の描画処理
void DrawMenuFrame(void)
{

	LPDIRECT3DDEVICE9 pDevice;
	int nCntMenuFrame;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMenuFrame, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntMenuFrame = 0; nCntMenuFrame < NUM_MENUFRAME; nCntMenuFrame++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_apTextureMenuFrame[nCntMenuFrame]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntMenuFrame * 4,
			2);

	}

	// 背景の描画処理
	DrawFILM();

	DrawIcon();

	DrawMenu();

	DrawCorkboard();

}