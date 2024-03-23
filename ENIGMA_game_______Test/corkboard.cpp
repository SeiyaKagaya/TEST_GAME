//==============================
//
// メニューのコルクボード[corkboard.cpp]
// Author:Kaito Hondo
//
//==============================

#include "main.h"
#include "corkboard.h"


// マクロ定義
#define NUM_CORKBOARD	(1)// 背景の数

// グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureCorkboard[NUM_CORKBOARD] = {};	// テクスチャ（３枚分）へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCorkboard = NULL;	// 頂点バッファへのポインタ

// 背景の初期化処理
void InitCorkboard(void)
{

	LPDIRECT3DDEVICE9 pDevice;
	int nCntCorkboard;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, Corkboard_TEXTURE, &g_apTextureCorkboard[0]);


	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_CORKBOARD, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffCorkboard, NULL);

	VERTEX_2D* pVtx;

	// 頂点バッファをロックし、頂点データへのポインタを獲得
	g_pVtxBuffCorkboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCorkboard = 0; nCntCorkboard < NUM_CORKBOARD; nCntCorkboard++)
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
	g_pVtxBuffCorkboard->Unlock();
}

// 背景の終了処理
void UninitCorkboard(void)
{
	int nCount;

	// テクスチャの破棄
	for (nCount = 0; nCount < NUM_CORKBOARD; nCount++)
	{

		if (g_apTextureCorkboard[nCount] != NULL)
		{
			g_apTextureCorkboard[nCount]->Release();
			g_apTextureCorkboard[nCount] = NULL;
		}
	}
	// 頂点バッファの破棄
	if (g_pVtxBuffCorkboard != NULL)
	{
		g_pVtxBuffCorkboard->Release();
		g_pVtxBuffCorkboard = NULL;
	}
}

// 背景の更新処理
void UpdateCorkboard(void)
{

}

// 背景の描画処理
void DrawCorkboard(void)
{

	LPDIRECT3DDEVICE9 pDevice;
	int nCntCorkboard;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCorkboard, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntCorkboard = 0; nCntCorkboard < NUM_CORKBOARD; nCntCorkboard++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_apTextureCorkboard[nCntCorkboard]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntCorkboard * 4, 2);

	}
}