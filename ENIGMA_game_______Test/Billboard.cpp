//=========================================================
//
//アイテムを表示する処理[billboard.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "Billboard.h"
//#include "sound.h"
#include "input.h"
#include "game.h"

//マクロ定義
#define MAXSIZE	(15.0f)	//ビルボードサイズ

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBill = NULL; //頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_apTextureBill[BILLTYPE_MAX] = {};       //テクスチャへのポインタ
BILL g_aBill[NUMBILL];

//=============================
//アイテムの初期化処理
//=============================
void InitBill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_dish.png", &g_apTextureBill[0]);		//皿
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_remocon.png", &g_apTextureBill[1]);	//リモコン
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_vegetable.png", &g_apTextureBill[2]);//野菜
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_soup.png", &g_apTextureBill[3]);		//スープ

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * NUMBILL, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBill, NULL);

	VERTEX_3D* pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBill->Lock(0, 0, (void**)&pVtx, 0);

	for (int nBill = 0; nBill < NUMBILL; nBill++)
	{
		g_aBill[nBill].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置
		g_aBill[nBill].nType = BILLTYPE_DISH;
		g_aBill[nBill].bUse = false;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-MAXSIZE, MAXSIZE * 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(MAXSIZE, MAXSIZE * 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-MAXSIZE, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(MAXSIZE, 0, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBuffBill->Unlock();

}
//=============================
//アイテムの終了処理
//=============================
void UninitBill(void)
{
	//StopSound(SOUND_LABEL_SE_SHOT);
	//StopSound(SOUND_LABEL_SE_EXPLOSIONBOMB);
	//テクスチャの破棄
	for (int i = 0; i < BILLTYPE_MAX; i++)
	{
		if (g_apTextureBill[i] != NULL)
		{
			g_apTextureBill[i]->Release();
			g_apTextureBill[i] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBill != NULL)
	{
		g_pVtxBuffBill->Release();
		g_pVtxBuffBill = NULL;
	}
}
//=============================
//アイテムの更新処理
//=============================
void UpdateBill(void)
{
	//VERTEX_3D* pVtx;//頂点情報へのポインタ

	////頂点バッファをロックし、頂点情報へのポインタを取得
	//g_pVtxBuffBill->Lock(0, 0, (void**)&pVtx, 0);

	//for (int nBill = 0; nBill < NUMBILL; nBill++)
	//{

	//	pVtx += 4;
	//}
	////頂点バッファのアンロック
	//g_pVtxBuffBill->Unlock();

}
//=============================
//アイテムの描画処理
//=============================
void DrawBill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX  mtxTrans;//計算用マトリックス
	D3DXMATRIX mtxView;//ビューマトリックスの取得

	for (int nBill = 0; nBill < NUMBILL; nBill++)
	{
		if (g_aBill[nBill].bUse == true)
		{
			//ライトを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			////Zの比較変更
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			////Zバッファに書き込まない
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBill[nBill].mtxWorldBill);

			//向きを反映
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBill[nBill].rotItem.y, g_aBill[nBill].rotItem.x, g_aBill[nBill].rotItem.z);

			//D3DXMatrixMultiply(&g_aBill[nBill].mtxWorldBill, &g_aBill[nBill].mtxWorldBill, &mtxRot);

					//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBill[nBill].pos.x, g_aBill[nBill].pos.y, g_aBill[nBill].pos.z);

			D3DXMatrixMultiply(&g_aBill[nBill].mtxWorldBill, &g_aBill[nBill].mtxWorldBill, &mtxTrans);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_aBill[nBill].mtxWorldBill, NULL, &mtxView);//逆行鉄を求める

			g_aBill[nBill].mtxWorldBill._41 = 0.0f;
			g_aBill[nBill].mtxWorldBill._42 = 0.0f;
			g_aBill[nBill].mtxWorldBill._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBill[nBill].pos.x, g_aBill[nBill].pos.y, g_aBill[nBill].pos.z);

			D3DXMatrixMultiply(&g_aBill[nBill].mtxWorldBill, &g_aBill[nBill].mtxWorldBill, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBill[nBill].mtxWorldBill);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBill, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);


			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureBill[g_aBill[nBill].nType]);

			////アルファブレンディングを加算合成に設定
			//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


			//アイテムの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				nBill * 4,//描画する最初の頂点インデックス
				2);//描画するプリミティブ数


			////アルファブレンディングをもとに戻す
			//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


			//ライトを有効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			////Zの比較変更
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			////Zバッファに書き込まない
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);


			//テクスチャを戻す
			pDevice->SetTexture(0, NULL);
		}
	}
}

//=============================
//アイテムの設定処理
//=============================
void SetBill(D3DXVECTOR3 Pos, int nType)
{
	VERTEX_3D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBill->Lock(0, 0, (void**)&pVtx, 0);

	for (int nBill = 0; nBill < NUMBILL; nBill++)
	{
		if (g_aBill[nBill].bUse == false)
		{
			g_aBill[nBill].pos = Pos;//位置
			g_aBill[nBill].nType = nType;
			g_aBill[nBill].bUse = true;
			break;
		}
		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffBill->Unlock();
}