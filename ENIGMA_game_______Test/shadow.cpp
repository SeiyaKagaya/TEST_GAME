//=========================================================
//
//polygonを表示する処理[shadow.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "shadow.h"
#include "player.h"
#include <stdio.h>

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL; //頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;       //テクスチャへのポインタ

//D3DXVECTOR3 g_Shadow[nCnt].pos;	//位置
//D3DXVECTOR3 g_Shadow[nCnt].rot;	//向き
//D3DXMATRIX g_Shadow[nCnt].mtxWorld;//ワールドマトリックス


Shadow g_Shadow[MAX_SHADOW];


//=============================
//影の初期化処理
//=============================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\shadow000.jpg", &g_pTextureShadow);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffShadow, NULL);
	
	VERTEX_3D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	
	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{

		g_Shadow[nCnt].pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//位置
		g_Shadow[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き

		//g_Shadow[nCnt].mtxWorld= D3DXMATRIX(0.0f,0.0f,0.0f);//ワールドマトリックス
		g_Shadow[nCnt].bUse = false;

		g_Shadow[nCnt].ShadowSize = SHADOWSIZE_PLAYER;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標を設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下


		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffShadow->Unlock();
}
//=============================
//影の終了処理
//=============================
void UninitShadow(void)
{
	//テクスチャの破棄
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}
//=============================
//影の更新処理
//=============================
void UpdateShadow(void)
{
	float nPosSize=0.0f;

	VERTEX_3D* pVtx;//頂点情報へのポインタ

//頂点バッファをロックし、頂点情報へのポインタを取得
    	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{

		if (g_Shadow[nCnt].ShadowSize == SHADOWSIZE_PLAYER)
		{
			nPosSize = SHADOW_SIZE_PLAYER;
		}
		else if (g_Shadow[nCnt].ShadowSize == SHADOWSIZE_ITEM)
		{
			nPosSize = SHADOW_SIZE_BULLET;
		}
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-nPosSize, 0.0f, nPosSize);
		pVtx[1].pos = D3DXVECTOR3(nPosSize, 0.0f, nPosSize);
		pVtx[2].pos = D3DXVECTOR3(-nPosSize, 0.0f, -nPosSize);
		pVtx[3].pos = D3DXVECTOR3(nPosSize, 0.0f, -nPosSize);


		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffShadow->Unlock();

}
//=============================
//影の描画処理
//=============================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_Shadow[nCnt].bUse == true)
		{
			//ライトを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			////Zの比較変更
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			////Zバッファに書き込まない
			//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			//アルファブレンディングを減算合成に設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Shadow[nCnt].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCnt].rot.y, g_Shadow[nCnt].rot.x, g_Shadow[nCnt].rot.z);

			D3DXMatrixMultiply(&g_Shadow[nCnt].mtxWorld, &g_Shadow[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCnt].pos.x, g_Shadow[nCnt].pos.y, g_Shadow[nCnt].pos.z);

			D3DXMatrixMultiply(&g_Shadow[nCnt].mtxWorld, &g_Shadow[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCnt].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定

			pDevice->SetTexture(0, g_pTextureShadow);

			//影の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				nCnt * 4,//描画する最初の頂点インデックス
				2);//描画するプリミティブ数

				//アルファブレンディングをもとに戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

						//ライトを有効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			////Zの比較変更
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			////Zバッファに書き込まない
			//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

			//テクスチャを戻す
			pDevice->SetTexture(0, NULL);
		}
	}


}
//=============================
//影の設定処理
//=============================
int SetShadow(void)
{
	int nCntShadow = -1;

	VERTEX_3D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_Shadow[nCnt].bUse == false)
		{
			g_Shadow[nCnt].bUse = true;
			nCntShadow = nCnt;
			break;
		}
		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffShadow->Unlock();

	return nCntShadow;
}
//=============================
//影の位置設定処理
//=============================
void SetPositionShadow(int nldShadow, D3DXVECTOR3 pos, SHADOWSIZE ShadowSize)
{
	//指定した影の位置を設定
	g_Shadow[nldShadow].pos = pos;
	g_Shadow[nldShadow].pos.y += 1.0f;
	g_Shadow[nldShadow].ShadowSize = ShadowSize;

}
//=============================
//影の個人の終了処理
//=============================
void EndProcessShadow(int nldShadow)
{
	g_Shadow[nldShadow].bUse = false;
}