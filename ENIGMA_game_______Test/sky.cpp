//=========================================================
//
//地面を表示する処理[sky.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "sky.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSky = NULL; //頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureSky = NULL;       //テクスチャへのポインタ

//インデックスバッファへのポインタ------------------------------------------------------NEW
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSky = NULL;

D3DXVECTOR3 g_posSky;	//位置
D3DXVECTOR3 g_rotSky;	//向き

D3DXMATRIX g_mtxWorldSky;//ワールドマトリックス

//D3DXVECTOR3 pos;


#define POSSIZE		(2000.0f)//本体のサイズ///--------------------後に二方向化

#define SKY_CELL_NUM_X	(16)//横のセル数(セル数)
#define SKY_CELL_NUM_Y	(6)//奥のセル数(セル数)


#define NUMVERTEX	((SKY_CELL_NUM_X + 1) * (SKY_CELL_NUM_Y + 1))//頂点数

// 三角形ストリップでの描画を前提とするため、インデックス数とポリゴン数の計算

#define NUMINDEX (2 * (SKY_CELL_NUM_X + 1) * SKY_CELL_NUM_Y + (SKY_CELL_NUM_Y - 1)) // インデックス数

// 縮退ポリゴン用頂点を含んだインデックス数
#define NUMINDEX_WITH_DEGENERATE (NUMINDEX + 2 * (SKY_CELL_NUM_Y - 1))

// ポリゴン数(プリミティブ数)
#define NUMPOLYGON (SKY_CELL_NUM_X * SKY_CELL_NUM_Y * 2) // ポリゴン数

// 縮退ポリゴンの数を含んだポリゴン数
#define NUMPOLYGON_WITH_DEGENERATE (NUMPOLYGON + SKY_CELL_NUM_Y - 1)


//半径
#define RADIUS	(2100.0f)//次々倍率上がる

//=============================
//地面の初期化処理
//=============================
void InitSky(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sky000.jpg", &g_pTextureSky);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * NUMVERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffSky, NULL);


	//インデックスバッファの生成//------------------------------------------------------------------------------------------------------------NEW
	pDevice->CreateIndexBuffer(sizeof(WORD) * NUMINDEX_WITH_DEGENERATE,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSky,
		NULL);

	g_posSky = D3DXVECTOR3(0.0f, RADIUS*1.1f, -100.0f);	//位置
	g_rotSky = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き


	VERTEX_3D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSky->Lock(0, 0, (void**)&pVtx, 0);

	//インデックス関係//----------------------------------------------------NEW
	WORD* pIdx;

	//インデックスバッファをロック
	g_pIdxBuffSky->Lock(0, 0, (void**)&pIdx, 0);

	int nIndexNUM = 0;

	for (int nCnt2 = 0; nCnt2 < (SKY_CELL_NUM_Y); nCnt2++)
	{//Z方向

		for (int nCnt = 0; nCnt < SKY_CELL_NUM_X + 1; nCnt++)
		{//X方向
			pIdx[nIndexNUM] = nCnt + ((nCnt2 + 1) * (SKY_CELL_NUM_X + 1));
			nIndexNUM++;
			pIdx[nIndexNUM] = nCnt + (nCnt2 * (SKY_CELL_NUM_X + 1));
			nIndexNUM++;
		}


		if (nCnt2 != (SKY_CELL_NUM_Y - 1))
		{//最終行じゃないとき(一歩前じゃない)
			//縮退ポリゴン
			pIdx[nIndexNUM] = (nCnt2 * (SKY_CELL_NUM_X + 1)) + SKY_CELL_NUM_X;//縮退右上
			nIndexNUM++;

			pIdx[nIndexNUM] = (nCnt2 * (SKY_CELL_NUM_X + 1)) + ((SKY_CELL_NUM_X + 1) * 2);//縮退
			nIndexNUM++;
		}

	}


	//int test = pIdx[0];//確認用
	//int test2 = pIdx[1];
	//int test3 = pIdx[2];
	//int test4 = pIdx[3];
	//int test5 = pIdx[4];
	//int test6 = pIdx[5];
	//int test7 = pIdx[6];
	//int test8 = pIdx[7];
	//int test9 = pIdx[8];
	//int test10 = pIdx[9];
	//int test11 = pIdx[10];
	//int test12 = pIdx[11];
	//int test13 = pIdx[12];
	//int test14 = pIdx[13];

	//int test15 = pIdx[14];
	//int test16 = pIdx[15];
	//int test17 = pIdx[16];
	//int test18 = pIdx[17];

	//int test19 = pIdx[18];
	//int test20 = pIdx[19];

	//int test21 = pIdx[20];
	//int test22 = pIdx[21];

	//int test23 = pIdx[22];
	//int test24 = pIdx[23];

		//--仮で直値//-------------------------------------
	//pIdx[0] = 3;
	//pIdx[1] = 0;
	//pIdx[2] = 4;
	//pIdx[3] = 1;
	//pIdx[4] = 5;
	//pIdx[5] = 2;
	//pIdx[6] = 2;//折返し＝縮退ポリゴン
	//pIdx[7] = 6;//見えない三角形エリア
	//pIdx[8] = 6;//
	//pIdx[9] = 3;
	//pIdx[10] = 7;
	//pIdx[11] = 4;
	//pIdx[12] = 8;
	//pIdx[13] = 5;



	// 頂点座標の設定---------------------------------------------------------------------------OK
	for (int nCntY = 0; nCntY <= SKY_CELL_NUM_Y; nCntY++)//縦
	{
		for (int nCntX = 0; nCntX <= SKY_CELL_NUM_X; nCntX++)//横
		{
			int nIndex = nCntY * (SKY_CELL_NUM_X + 1) + nCntX; // 頂点のインデックス


			pVtx[nIndex].pos.x = g_posSky.x + (sinf((0.1252 * nCntX) * D3DX_PI) * (RADIUS * nCntY));

			pVtx[nIndex].pos.z = g_posSky.z + (cosf((0.1252f * nCntX) * D3DX_PI) * (RADIUS * nCntY));

			pVtx[nIndex].pos.y = g_posSky.y - (nCntY - SKY_CELL_NUM_Y / 2.0f) * POSSIZE;






			pVtx[nIndex].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[nIndex].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}











	// テクスチャ座標の設定//------------------------------------------------------------------------OK
	for (int nCntY = 0; nCntY <= SKY_CELL_NUM_Y; nCntY++)
	{
		for (int nCntX = 0; nCntX <= SKY_CELL_NUM_X; nCntX++)
		{
			int vtxIndex = nCntY * (SKY_CELL_NUM_X + 1) + nCntX; // 頂点のインデックス

		// 以下の行を変更
			pVtx[vtxIndex].tex.x = static_cast<float>(nCntX) / SKY_CELL_NUM_X;
			pVtx[vtxIndex].tex.y = static_cast<float>(nCntY) / SKY_CELL_NUM_Y;
		}
	}



	//----------------------------------------------------------------------------------------------------------------------------



	//// 頂点座標の設定
	//for (int nCntY = 0; nCntY <= SKY_CELL_NUM_Y; nCntY++)
	//{
	//	for (int nCntX = 0; nCntX <= SKY_CELL_NUM_X; nCntX++)
	//	{
	//		int nIndex = nCntY * (SKY_CELL_NUM_X + 1) + nCntX; // 頂点のインデックス

	//		pVtx[nIndex].pos.x = g_posSky.x + (nCntX - SKY_CELL_NUM_X / 2.0f) * POSSIZE;//OK
	//		pVtx[nIndex].pos.y = g_posSky.y;
	//		pVtx[nIndex].pos.z = g_posSky.z - (nCntY - SKY_CELL_NUM_Y / 2.0f) * POSSIZE;


	//		pVtx[nIndex].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//		pVtx[nIndex].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	}
	//}

	////テクスチャ座標を設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上--
	//pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);//右上--

	//pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);//左上--
	//pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	//pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);//右上--

	//pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);//左下--
	//pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);//左下--
	//pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);//右下--



	////--仮で直値
	//pIdx[0] = 3;
	//pIdx[1] = 0;
	//pIdx[2] = 4;
	//pIdx[3] = 1;
	//pIdx[4] = 5;
	//pIdx[5] = 2;
	//pIdx[6] = 2;//折返し＝縮退ポリゴン
	//pIdx[7] = 6;//見えない三角形エリア
	//pIdx[8] = 6;//
	//pIdx[9] = 3;
	//pIdx[10] = 7;
	//pIdx[11] = 4;
	//pIdx[12] = 8;
	//pIdx[13] = 5;




	g_pIdxBuffSky->Unlock();

	//頂点バッファのアンロック
	g_pVtxBuffSky->Unlock();
}
//=============================
//地面の終了処理
//=============================
void UninitSky(void)
{
	//テクスチャの破棄
	if (g_pTextureSky != NULL)
	{
		g_pTextureSky->Release();
		g_pTextureSky = NULL;
	}

	//インデックスバッファの開放//--------------------New
	if (g_pIdxBuffSky != NULL)
	{
		g_pIdxBuffSky->Release();
		g_pIdxBuffSky = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSky != NULL)
	{
		g_pVtxBuffSky->Release();
		g_pVtxBuffSky = NULL;
	}
}
//=============================
//地面の更新処理
//=============================
void UpdateSky(void)
{
	//何もなし
	g_rotSky.y += 0.0001f;

	if (g_rotSky.y > 3.14f)
	{
		g_rotSky.y = -3.14f;
	}
	else if (g_rotSky.y < -3.14f)
	{
		g_rotSky.y = 3.14f;
	}


}
//=============================
//地面の描画処理
//=============================
void DrawSky(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldSky);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotSky.y, g_rotSky.x, g_rotSky.z);

	D3DXMatrixMultiply(&g_mtxWorldSky, &g_mtxWorldSky, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posSky.x, g_posSky.y, g_posSky.z);

	D3DXMatrixMultiply(&g_mtxWorldSky, &g_mtxWorldSky, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldSky);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSky, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定//--------------------------------------New
	pDevice->SetIndices(g_pIdxBuffSky);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureSky);



	////ポリゴンの描画
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, NUMVERTEX, 0, NUMINDEX);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, NUMVERTEX, 0, NUMINDEX_WITH_DEGENERATE);

	//地面の描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
	//	0,//描画する最初の頂点インデックス
	//	2);//描画するプリミティブ数

	
	//テクスチャを戻す
	pDevice->SetTexture(0, NULL);
}