//=========================================================
//
//地面を表示する処理[meshfield.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "meshfield.h"
//#include "field.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL; //頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;       //テクスチャへのポインタ

//インデックスバッファへのポインタ------------------------------------------------------NEW
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;

D3DXVECTOR3 g_posMeshField;	//位置
D3DXVECTOR3 g_rotMeshField;	//向き

D3DXMATRIX g_mtxWorldMeshField;//ワールドマトリックス

//D3DXVECTOR3 pos;


#define POSSIZE		(100.0f)//本体のサイズ///--------------------後に二方向化

#define MESH_CELL_NUM_X	(201)//横のセル数(セル数)
#define MESH_CELL_NUM_Z	(201)//奥のセル数(セル数)


#define NUMVERTEX	((MESH_CELL_NUM_X + 1) * (MESH_CELL_NUM_Z + 1))//頂点数

// 三角形ストリップでの描画を前提とするため、インデックス数とポリゴン数の計算

#define NUMINDEX (2 * (MESH_CELL_NUM_X + 1) * MESH_CELL_NUM_Z + (MESH_CELL_NUM_Z - 1)) // インデックス数

// 縮退ポリゴン用頂点を含んだインデックス数
#define NUMINDEX_WITH_DEGENERATE (NUMINDEX + 2 * (MESH_CELL_NUM_Z - 1))

// ポリゴン数(プリミティブ数)
#define NUMPOLYGON (MESH_CELL_NUM_X * MESH_CELL_NUM_Z * 2) // ポリゴン数

// 縮退ポリゴンの数を含んだポリゴン数
#define NUMPOLYGON_WITH_DEGENERATE (NUMPOLYGON + MESH_CELL_NUM_Z - 1)


D3DXVECTOR3 EscapePvtxNor[NUMVERTEX] = {};//法線保存先
//D3DXVECTOR3 EscapePvtxPos2[NUMVERTEX] = {};


int g_MaXpIdx = 0;//巡る順番の最大数

//=============================
//地面の初期化処理
//=============================
void InitMeshField(void)
{
	for (int i=0; i < NUMVERTEX; i++)
	{
		EscapePvtxNor[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}



	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\map001.jpg", &g_pTextureMeshField);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * NUMVERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMeshField, NULL);


	//インデックスバッファの生成//------------------------------------------------------------------------------------------------------------NEW
	pDevice->CreateIndexBuffer(sizeof(WORD) * NUMINDEX_WITH_DEGENERATE,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	g_posMeshField = D3DXVECTOR3(0.0f, -0.5f, 0.0f);	//位置
	g_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き


	VERTEX_3D* pVtx;//頂点情報へのポインタ

	


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	//インデックス関係//----------------------------------------------------NEW
	WORD* pIdx;

	//インデックスバッファをロック
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIndex = 0; nCntIndex < NUMVERTEX; nCntIndex++)
	{
		pVtx[nCntIndex].pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	}

	int nIndexNUM = 0;

	for (int nCnt2 = 0; nCnt2 < (MESH_CELL_NUM_Z); nCnt2++)
	{//Z方向

		for (int nCnt = 0 ; nCnt < MESH_CELL_NUM_X + 1; nCnt++)
		{//X方向
			pIdx[nIndexNUM] = nCnt + ((nCnt2 + 1) * (MESH_CELL_NUM_X + 1));
			nIndexNUM++;
			pIdx[nIndexNUM] = nCnt + (nCnt2 * (MESH_CELL_NUM_X + 1));
			nIndexNUM++;
		}


		if (nCnt2 != (MESH_CELL_NUM_Z - 1))//縮退ポリゴン
		{//最終行じゃないとき(一歩前じゃない)
			//縮退ポリゴン
			pIdx[nIndexNUM] = (nCnt2* (MESH_CELL_NUM_X+1)) + MESH_CELL_NUM_X;//縮退右上
			nIndexNUM++;

			pIdx[nIndexNUM] = (nCnt2 * (MESH_CELL_NUM_X + 1)) + ((MESH_CELL_NUM_X+1)*2);//縮退
			nIndexNUM++;
		}
		
	}

	g_MaXpIdx = nIndexNUM;


	// 頂点座標の設定---------------------------------------------------------------------------OK
	for (int nCntZ = 0; nCntZ <= MESH_CELL_NUM_Z; nCntZ++)//縦Z
	{
		for (int nCntX = 0; nCntX <= MESH_CELL_NUM_X; nCntX++)//横X
		{
			int nIndex = nCntZ * (MESH_CELL_NUM_X + 1) + nCntX; // 頂点のインデックス

			pVtx[nIndex].pos.x = g_posMeshField.x + (nCntX - MESH_CELL_NUM_X / 2.0f) * POSSIZE;

			if (nIndex % 4 == 0)
			{//高低差
				pVtx[nIndex].pos.y = g_posMeshField.y+ DIFF_IN_HEIGHT;

				//後々きえる
				pVtx[nIndex].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			}
			else
			{
				pVtx[nIndex].pos.y = g_posMeshField.y;
				//後々きえる
				pVtx[nIndex].nor = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
			}

			pVtx[nIndex].pos.z = g_posMeshField.z - (nCntZ - MESH_CELL_NUM_Z / 2.0f) * POSSIZE;



			//後々きえる
		//	pVtx[nIndex].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			pVtx[nIndex].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}





	//法線
//	CalculateNormals();



//	メッシュフィールドの法線。未だうまく行かずとりあえず直接値を入れて高低差を視認できるようにした

	


	// テクスチャ座標の設定//------------------------------------------------------------------------OK
	for (int nCntZ = 0; nCntZ <= MESH_CELL_NUM_Z; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= MESH_CELL_NUM_X; nCntX++)
		{
			int vtxIndex = nCntZ * (MESH_CELL_NUM_X + 1) + nCntX; // 頂点のインデックス

		// 以下の行を変更
			pVtx[vtxIndex].tex.x = static_cast<float>(nCntX) / MESH_CELL_NUM_X;
			pVtx[vtxIndex].tex.y = static_cast<float>(nCntZ) / MESH_CELL_NUM_Z;
		}
	}

	//いらないポリを非表示....
	int nIndexNUM4 = 0;
	for (int nCnt2 = 0; nCnt2 < (MESH_CELL_NUM_Z); nCnt2++)
	{//Z方向

		if (nCnt2 != (MESH_CELL_NUM_Z - 1))//縮退ポリゴン
		{//最終行じゃないとき(一歩前じゃない)

		 //縮退ポリゴン
			//pIdx[nIndexNUM4] = (nCnt2 * (MESH_CELL_NUM_X + 1)) + MESH_CELL_NUM_X;//縮退右上

			pVtx[nIndexNUM4].tex.x = 0.0f;
			pVtx[nIndexNUM4].tex.y = 0.0f;
			nIndexNUM4++;

			//pIdx[nIndexNUM4] = (nCnt2 * (MESH_CELL_NUM_X + 1)) + ((MESH_CELL_NUM_X + 1) * 2);//縮退
			pVtx[nIndexNUM4].tex.x = 0.0f;
			pVtx[nIndexNUM4].tex.y = 0.0f;
			nIndexNUM4++;
		}

	}




	g_pIdxBuffMeshField->Unlock();

	//頂点バッファのアンロック
	g_pVtxBuffMeshField->Unlock();

}
//=============================
//地面の終了処理
//=============================
void UninitMeshField(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	//インデックスバッファの開放//--------------------New
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}
}
//=============================
//地面の更新処理
//=============================
void UpdateMeshField(void)
{
	//何もなし
}
//=============================
//地面の描画処理
//=============================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定//--------------------------------------New
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshField);



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

//=============================
//法線の計算処理
//=============================
void CalculateNormals(void)
{
	//これが一番明るくなる法線
	//pVtx[nCntIndex2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//メッシュフィールドの法線作成手順

	//①
	//----メッシュを構成するすべてのポリゴン(*縮退ポリゴンは除く)に対して
	//----1.　外積、正規化を行い面法線ベクトルを作成
	//----2.　1.の法線ベクトルをポリゴンを構成する3つの頂点枚毎に配列に保持----(保持先)EscapePvtxNor[nCnt];

	//②
	//----メッシュを構成するすべての頂点に対して以下を実行
	//----1.　①で保持したすべての面法線ベクトルを加算
	//----2.　1.のベクトルを正規化
 //----3.　頂点データの法線ベクトル(pVtx[nCnt].nor)に、2.のベクトルを設定

	VERTEX_3D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	//インデックス関係//----------------------------------------------------NEW
	WORD* pIdx;

	//インデックスバッファをロック
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);


	//各頂点法線計算
	
	//int EscapeCnt = 0;
	//平面ベクトル
	////for (int nCntIndex = 0; nCntIndex < NUMVERTEX; nCntIndex ++)
	////{
	////	//法線計算する

	////	D3DXVECTOR3 EscapeVtxPos1 = pVtx[pIdx[nCntIndex]].pos - pVtx[pIdx[nCntIndex + 1]].pos;
	////	D3DXVECTOR3 EscapeVtxPos2 = pVtx[pIdx[nCntIndex + 2]].pos - pVtx[pIdx[nCntIndex + 1]].pos;

	////	D3DXVECTOR3 EscapeNOR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	D3DXVec3Cross(&EscapeNOR, &EscapeVtxPos1, &EscapeVtxPos2);

	////	D3DXVECTOR3 NOR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	D3DXVec3Normalize(&NOR, &EscapeNOR);

	////	//全頂点
	////	EscapePvtxNor[nCntIndex] = NOR;//-------------------------------頂点の数分三角があるので順番どおり保持--1//頂点法線--pIdxの巡る順番
	////	//EscapeCnt++;
	////}

	//////int EscapeCnt2 = 0;
	////for (int nCntIndex2 = 0; nCntIndex2 < NUMVERTEX; nCntIndex2++)
	////{
	////	D3DXVECTOR3 EscapeNOR = (EscapePvtxNor[pIdx[nCntIndex2]] + EscapePvtxNor[pIdx[nCntIndex2 + 1]] + EscapePvtxNor[pIdx[nCntIndex2 + 2]]);

	////	D3DXVECTOR3 NOR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);



	////	int nCntIndex3 = 0;
	////	for (pIdx[nCntIndex3] = 0; nCntIndex3 < g_MaXpIdx; nCntIndex3++)
	////	{
	////		if (pVtx[pIdx[nCntIndex2 + 1]].pos == pVtx[pIdx[nCntIndex3]].pos)
	////		{
	////			if (pIdx[nCntIndex2 + 1] != pIdx[nCntIndex3])
	////			{//自分自身じゃない時
	////				if (pIdx[nCntIndex2 + 1] > pIdx[nCntIndex3])
	////				{//自分自身じゃない時
	////					EscapeNOR += pVtx[pIdx[nCntIndex3]].pos;
	////				}
	////			}

	////		}


	////	}


	////	D3DXVec3Normalize(&NOR, &EscapeNOR);




	////	//全頂点
	////	EscapePvtxNor[nCntIndex2] = NOR;//-------------------------------頂点の数分三角があるので順番どおり保持--2--再計算後各頂点法線
	////	//EscapeCnt2++;

	////	pVtx[nCntIndex2].nor = NOR;
	////}






	
	for (int nCntIndex = 0; nCntIndex < NUMVERTEX - 2; nCntIndex++)
	{

		if (nCntIndex % (MESH_CELL_NUM_Z - 1) == 1)//縮退ポリゴン--法線計算しない
		{//最終行じゃないとき(一歩前じゃない)

		}
		else
		{//法線計算する

			D3DXVECTOR3 EscapeVtxPos1 = pVtx[nCntIndex + 1].pos - pVtx[nCntIndex].pos;
			D3DXVECTOR3 EscapeVtxPos2 = pVtx[nCntIndex + 2].pos - pVtx[nCntIndex].pos;

			D3DXVECTOR3 EscapeNOR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


			D3DXVec3Cross(&EscapeNOR, &EscapeVtxPos1, &EscapeVtxPos2);

			D3DXVECTOR3 NOR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			D3DXVec3Normalize(&NOR, &EscapeNOR);

			EscapePvtxNor[nCntIndex] = NOR;//-------------------------------頂点の数分三角があるので順番どおり保持--1//平面法線

		}
	}
	 
	
	//各頂点法線計算
	for (int nCntIndex = 0; nCntIndex < NUMVERTEX - 2; nCntIndex++)
	{
		D3DXVECTOR3 EscapeNOR = (EscapePvtxNor[nCntIndex] + EscapePvtxNor[nCntIndex + 1] + EscapePvtxNor[nCntIndex + 2]);
		D3DXVECTOR3 NOR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		D3DXVec3Normalize(&NOR, &EscapeNOR);

		int test;
		test = 2;

		EscapePvtxNor[nCntIndex] = NOR;//-------------------------------頂点の数分三角があるので順番どおり保持--2--再計算後各頂点法線
	}

	for (int nCntIndex = 0; nCntIndex < NUMVERTEX - 2; nCntIndex++)
	{
		pVtx[nCntIndex].nor = EscapePvtxNor[nCntIndex];//-------------------------------頂点の数分三角があるので順番どおり保持--2--再計算後各頂点法線

	}


	g_pIdxBuffMeshField->Unlock();

	//頂点バッファのアンロック
	g_pVtxBuffMeshField->Unlock();
}