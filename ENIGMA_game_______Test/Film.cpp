//==============================
//
// フィルム動かす[Film.cpp]
// Author:Kaito Hondo
//
//==============================

#include "main.h"
#include "Film.h"

//マクロ定義
#define TATE_FILM	(100.0)
#define YOKO_FILM	(SCREEN_WIDE + 100.0)

// グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureFILM[NUM_FILMTEXTURE] = {};	// テクスチャ（1枚分）へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFILM = NULL;	// 頂点バッファへのポインタ
FILM g_aFilm[NUM_FILM];
float g_aPosTexU[NUM_FILM];						// テクスチャ座標の開始位置（U値）
float g_aPosTexV[NUM_FILM];						// テクスチャ座標の開始位置（V値）
float g_fLengthFilm;	//対角線の長さ
float g_fAngleFilm;	//対角線の角度


//==============================================================
// 背景の初期化処理
//==============================================================
void InitFILM(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntFILM;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, FILM_TEXTURE4, &g_apTextureFILM[0]);


	//対角線の長さを算出
	g_fLengthFilm = sqrtf(YOKO_FILM * YOKO_FILM + TATE_FILM * TATE_FILM) * 0.5f;

	//対角線の角度を算出
	g_fAngleFilm = atan2f(YOKO_FILM, TATE_FILM);


	// テクスチャ座標の開始位置（V値）の初期化
	for (nCntFILM = 0; nCntFILM < NUM_FILM; nCntFILM++)
	{
		g_aPosTexV[nCntFILM] = 0.0f;
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_FILM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffFILM, NULL);

	VERTEX_2D* pVtx;

	// 頂点バッファをロックし、頂点データへのポインタを獲得
	g_pVtxBuffFILM->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFILM = 0; nCntFILM < NUM_FILM; nCntFILM++)
	{
		g_aFilm[nCntFILM].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFilm[nCntFILM].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFilm[nCntFILM].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFilm[nCntFILM].texX = 0.0f;
		g_aFilm[nCntFILM].bUse = false;


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

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;// 頂点データのポインタを４つ分進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffFILM->Unlock();

	SetFILM(D3DXVECTOR3(SCREEN_WIDE * 0.8, SCREEN_HEIGHT * 0.2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, (D3DX_PI * -0.25)), -0.001f);
	SetFILM(D3DXVECTOR3(SCREEN_WIDE * 0.9, SCREEN_HEIGHT * 0.2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, (D3DX_PI * +0.40)), -0.001f);
	SetFILM(D3DXVECTOR3(SCREEN_WIDE * 0.1, SCREEN_HEIGHT * 0.9, 0.0f), D3DXVECTOR3(0.0f, 0.0f, (D3DX_PI * -0.25)), +0.001f);

}

//==============================================================
// 背景の終了処理
//==============================================================
void UninitFILM(void)
{
	int nCount;

	// テクスチャの破棄
	for (nCount = 0; nCount < NUM_FILMTEXTURE; nCount++)
	{
		if (g_apTextureFILM[nCount] != NULL)
		{
			g_apTextureFILM[nCount]->Release();
			g_apTextureFILM[nCount] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffFILM != NULL)
	{
		g_pVtxBuffFILM->Release();
		g_pVtxBuffFILM = NULL;
	}
}

//==============================================================
// 背景の更新処理
//==============================================================
void UpdateFILM(void)
{
	int nCntFILM;
	VERTEX_2D* pVtx;

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFILM->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFILM = 0; nCntFILM < NUM_FILM; nCntFILM++)
	{
		g_aPosTexU[nCntFILM] += g_aFilm[nCntFILM].texX;

		pVtx[0].pos.x = g_aFilm[nCntFILM].pos.x + sinf(g_aFilm[nCntFILM].rot.z - (D3DX_PI - g_fAngleFilm)) * g_fLengthFilm;
		pVtx[0].pos.y = g_aFilm[nCntFILM].pos.y + cosf(g_aFilm[nCntFILM].rot.z - (D3DX_PI - g_fAngleFilm)) * g_fLengthFilm;
		pVtx[1].pos.x = g_aFilm[nCntFILM].pos.x + sinf(g_aFilm[nCntFILM].rot.z + (D3DX_PI - g_fAngleFilm)) * g_fLengthFilm;
		pVtx[1].pos.y = g_aFilm[nCntFILM].pos.y + cosf(g_aFilm[nCntFILM].rot.z + (D3DX_PI - g_fAngleFilm)) * g_fLengthFilm;
		pVtx[2].pos.x = g_aFilm[nCntFILM].pos.x + sinf(g_aFilm[nCntFILM].rot.z - g_fAngleFilm) * g_fLengthFilm;
		pVtx[2].pos.y = g_aFilm[nCntFILM].pos.y + cosf(g_aFilm[nCntFILM].rot.z - g_fAngleFilm) * g_fLengthFilm;
		pVtx[3].pos.x = g_aFilm[nCntFILM].pos.x + sinf(g_aFilm[nCntFILM].rot.z + g_fAngleFilm) * g_fLengthFilm;
		pVtx[3].pos.y = g_aFilm[nCntFILM].pos.y + cosf(g_aFilm[nCntFILM].rot.z + g_fAngleFilm) * g_fLengthFilm;


		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntFILM], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntFILM] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntFILM], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntFILM] + 1.0f, 1.0f);

		g_aFilm[nCntFILM].pos += g_aFilm[nCntFILM].move;

		pVtx += 4;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffFILM->Unlock();
}

//==============================================================
// 背景の描画処理
//==============================================================
void DrawFILM(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntFILM;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFILM, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntFILM = 0; nCntFILM < NUM_FILM; nCntFILM++)
	{
		if (g_aFilm[nCntFILM].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureFILM[0]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntFILM * 4,
				2);
		}
	}
}

//=======================================
//フィルムの設定処理
//=======================================
void SetFILM(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float texX)
{
	VERTEX_3D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFILM->Lock(0, 0, (void**)&pVtx, 0);

	for (int nFilm = 0; nFilm < NUM_FILM; nFilm++)
	{
		if (g_aFilm[nFilm].bUse == false)
		{
			g_aFilm[nFilm].pos = pos;	//位置
			g_aFilm[nFilm].rot = rot;	//向き
			g_aFilm[nFilm].texX = texX;
			g_aFilm[nFilm].bUse = true;
			break;
		}
		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffFILM->Unlock();
}
