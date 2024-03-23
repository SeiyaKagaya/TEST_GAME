//=========================================================
//
//アイテムを表示する処理[billboard.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "item.h"
//#include "sound.h"
#include "input.h"
//#include "shadow.h"
#include "player.h"
#include "particle.h"
#include "stage.h"
#include "hitcollision_mistake_prevention.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL; //頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureItem[ITEMTYPE_MAX] = {};       //テクスチャへのポインタ
ITEM g_Item[NUMITEM];//制作中　構造体

int g_nldShadow4 = -1;

//=============================
//アイテムの初期化処理
//=============================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_dish.png", &g_pTextureItem[0]);		//皿
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_remocon.png", &g_pTextureItem[1]);	//リモコン
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_vegetable.png", &g_pTextureItem[2]);//野菜
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_soup.png", &g_pTextureItem[3]);		//スープ

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * NUMITEM, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffItem, NULL);

	VERTEX_3D* pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nItem = 0; nItem < NUMITEM; nItem++)
	{
		g_Item[nItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置
		g_Item[nItem].oldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置
		g_Item[nItem].bGetNO = false;
		g_Item[nItem].nStayGetCnt = 0;
		g_Item[nItem].bUse = false;
		g_Item[nItem].nfloatCnt = 0;
		g_Item[nItem].move = D3DXVECTOR3(0.2f, 0.1f, 1.0f) * ITEMMOVESPEED_LOCK;
		g_Item[nItem].bRetentionl = false;
		g_Item[nItem].ItemType = ITEMTYPE_DISH;

		//影設定
		g_Item[nItem].nShadowNum = -1;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-ITEMSIZE, ITEMSIZE*2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(ITEMSIZE, ITEMSIZE*2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-ITEMSIZE, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(ITEMSIZE, 0, 0.0f);

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
	g_pVtxBuffItem->Unlock();

	int randVeg = RandSelect(3);
	//int randVeg = ((float)rand() / RAND_MAX) * 3;

	switch (randVeg)
	{
	case 0:
		SetItem(D3DXVECTOR3(-600.0f, 200.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_VEGETABLE);
		break;
	case 1:
		SetItem(D3DXVECTOR3(-280.0f, 200.0f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_VEGETABLE);
		break;
	case 2:
		SetItem(D3DXVECTOR3(-1000.0f, 200.0f, -60.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_VEGETABLE);
		break;
	default:
		break;
	}
}
//=============================
//アイテムの終了処理
//=============================
void UninitItem(void)
{
	//StopSound(SOUND_LABEL_SE_SHOT);
	//StopSound(SOUND_LABEL_SE_EXPLOSIONBOMB);
	//テクスチャの破棄
	for (int i = 0; i < ITEMTYPE_MAX; i++)
	{
		if (g_pTextureItem[i] != NULL)
		{
			g_pTextureItem[i]->Release();
			g_pTextureItem[i] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}
//=============================
//アイテムの更新処理
//=============================
void UpdateItem(void)
{
	VERTEX_3D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nItem = 0; nItem < NUMITEM; nItem++)
	{
		if (g_Item[nItem].bUse == true)
		{
			if (g_Item[nItem].bGetNO == true)
			{
				if (g_Item[nItem].nStayGetCnt > 0)
				{
					g_Item[nItem].nStayGetCnt--;
				}

				if (g_Item[nItem].nStayGetCnt <= 0)
				{
					g_Item[nItem].bGetNO = false;
				}
			}

			g_Item[nItem].oldPos = g_Item[nItem].pos;
			//位置を更新
			g_Item[nItem].pos += g_Item[nItem].move;
		
			//-------------------------------------------------------------ふわふわ浮遊
			g_Item[nItem].nfloatCnt++;
			
			if (g_Item[nItem].nfloatCnt > 50)
			{
				if (g_Item[nItem].bfloatRot==false)
				{//下降に切り替え
					g_Item[nItem].nfloatCnt = 0;
					g_Item[nItem].bfloatRot = true;
				}
				else if (g_Item[nItem].bfloatRot == true)
				{//上昇に切り替え
					g_Item[nItem].nfloatCnt = 0;
					g_Item[nItem].bfloatRot = false;

					if (g_Item[nItem].pos.y <= g_Item[nItem].HitPosY)
					{//下限に接触
						g_Item[nItem].pos.y = g_Item[nItem].HitPosY + 0.1f;
						g_Item[nItem].bRetentionl = true;
					}
					else
					{//滞留解除

						g_Item[nItem].bRetentionl = false;
					}
				}
			}


			if (g_Item[nItem].bRetentionl == true)
			{//滞留状態
				if (g_Item[nItem].bfloatRot == true)
				{//下降
					g_Item[nItem].pos.y -= 0.5f;

					if (g_Item[nItem].pos.y <= g_Item[nItem].HitPosY)
					{//下限に接触
						g_Item[nItem].pos.y = g_Item[nItem].HitPosY + 0.1f;
					}
				}
				else if (g_Item[nItem].bfloatRot == false)
				{//上昇
					g_Item[nItem].pos.y += 0.5f;
				}
			}
			else
			{//滞留じゃない
				//重力
				if (g_Item[nItem].pos.y > g_Item[nItem].HitPosY)
				{//空中(地上ではない)の時
					//重力
					g_Item[nItem].move.y -= (GRAVITY * 0.29f);
				}
				else
				{//地上
					g_Item[nItem].bRetentionl = true;//滞留状態に移行
					g_Item[nItem].pos.y = g_Item[nItem].HitPosY + 0.1f;
				}
			}


			//判定サイズ
			D3DXVECTOR3 ItemMin = D3DXVECTOR3(g_Item[nItem].pos + ITEMMIN);
			D3DXVECTOR3 ItemMax = D3DXVECTOR3(g_Item[nItem].pos + ITEMMAX);



			//----------------------------------------------------------------------------モデル接触
			MAPOBJECT* pMapObject;
			pMapObject = GetMapObject();

			for (int i = 0; i < MAX_MODEL; i++)
			{
				if (pMapObject[i].bUse == true)
				{
					if (pMapObject[i].bCollision == true)
					{
						D3DXVECTOR3 ModelMin = D3DXVECTOR3(pMapObject[i].pos + pMapObject[i].Minpos);
						D3DXVECTOR3 ModelMax = D3DXVECTOR3(pMapObject[i].pos + pMapObject[i].Maxpos);

						//当たり判定
						BoxCollisionFromItem(ItemMin, ItemMax, ModelMin, ModelMax, nItem);
					}
				}
			}

			//----------------------------------------------------------------------------壁、床接触
			STAGE* pStage;
			pStage = GetStage();
			for (int nWall = 0; nWall < NUMSTAGE; nWall++)
			{
				if (pStage[nWall].bUse == true)
				{
					if (pStage[nWall].bCollision == true)
					{
						D3DXVECTOR3 StageMin = D3DXVECTOR3(pStage[nWall].posStage + pStage[nWall].MinPos);
						D3DXVECTOR3 StageMax = D3DXVECTOR3(pStage[nWall].posStage + pStage[nWall].MaxPos);

						//当たり判定
						BoxCollisionFromItem(ItemMin, ItemMax, StageMin, StageMax, nItem);
					}
				}
			}




			//当たり判定抜け防止/-----------------------------------------------------------------------------------------------------------------------------------------
			COLLISION_PRE* pColisionPre;
			pColisionPre = GetCollision_Pre();

			for (int i = 0; i < MAXCOLLISION_PRE; i++)
			{
				if (pColisionPre[i].bUse == true)
				{

					D3DXVECTOR3 ColisionPreMin = D3DXVECTOR3(pColisionPre[i].pos + pColisionPre[i].Min);
					D3DXVECTOR3 ColisionPreMax = D3DXVECTOR3(pColisionPre[i].pos + pColisionPre[i].Max);

					//当たり判定
					BoxCollisionFromItem(ItemMin, ItemMax, ColisionPreMin, ColisionPreMax, nItem);

				}
			}











			
			//-------------------------------------------------------------ふわふわ浮遊ここまで

			//移動量を更新(疑似慣性で減衰)
			g_Item[nItem].move.x += (0.0f - g_Item[nItem].move.x) * DAMPING_RATIO;
			g_Item[nItem].move.y += (0.0f - g_Item[nItem].move.y) * DAMPING_RATIO;
			g_Item[nItem].move.z += (0.0f - g_Item[nItem].move.z) * DAMPING_RATIO;



			//if (g_Item[nItem].ItemType == ITEMTYPE_DISH)//皿
			//{
			//	SetParticle(g_Item[nItem].pos, 30.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.04f));
			//}
			//else if (g_Item[nItem].ItemType == ITEMTYPE_REMOCON)//リモコン
			//{
			//	SetParticle(g_Item[nItem].pos, 30.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.04f));
			//}
			//else if (g_Item[nItem].ItemType == ITEMTYPE_VEGETABLE)//野菜
			//{
				SetParticle(g_Item[nItem].pos, 30.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.04f));
			//}

			//--------------------------------寿命
			if (g_Item[nItem].pos.y < 0.0f)
			{

			}
		}
		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffItem->Unlock();

}
//=============================
//アイテムの描画処理
//=============================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX  mtxTrans;//計算用マトリックス
	D3DXMATRIX mtxView;//ビューマトリックスの取得

	for (int nItem = 0; nItem < NUMITEM; nItem++)
	{
		if (g_Item[nItem].bUse == true)
		{
			//ライトを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			////Zの比較変更
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			////Zバッファに書き込まない
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Item[nItem].mtxWorldItem);

			//向きを反映
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Item[nItem].rotItem.y, g_Item[nItem].rotItem.x, g_Item[nItem].rotItem.z);

			//D3DXMatrixMultiply(&g_Item[nItem].mtxWorldItem, &g_Item[nItem].mtxWorldItem, &mtxRot);

					//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Item[nItem].pos.x, g_Item[nItem].pos.y, g_Item[nItem].pos.z);

			D3DXMatrixMultiply(&g_Item[nItem].mtxWorldItem, &g_Item[nItem].mtxWorldItem, &mtxTrans);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_Item[nItem].mtxWorldItem, NULL, &mtxView);//逆行鉄を求める

			g_Item[nItem].mtxWorldItem._41 = 0.0f;
			g_Item[nItem].mtxWorldItem._42 = 0.0f;
			g_Item[nItem].mtxWorldItem._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Item[nItem].pos.x, g_Item[nItem].pos.y, g_Item[nItem].pos.z);

			D3DXMatrixMultiply(&g_Item[nItem].mtxWorldItem, &g_Item[nItem].mtxWorldItem, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Item[nItem].mtxWorldItem);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);


			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureItem[g_Item[nItem].ItemType]);

			////アルファブレンディングを加算合成に設定
			//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


			//アイテムの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				nItem * 4,//描画する最初の頂点インデックス
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
//アイテムの取得処理
//=============================
ITEM* GetItem(void)
{
	return &g_Item[0];
}

////=============================
////アイテムカウントの取得処理
////=============================
//ITEMCNT* GetItemCnt_1P(void)
//{
//	return &g_ItemCnt_1P[0];
//}
////=============================
////アイテムカウントの取得処理
////=============================
//ITEMCNT* GetItemCnt_2P(void)
//{
//	return &g_ItemCnt_2P[0];
//}

//=============================
//アイテムの設定処理
//=============================
void SetItem(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, ITEMTYPE Type)
{
	VERTEX_3D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nItem = 0; nItem < NUMITEM; nItem++)
	{
		if (g_Item[nItem].bUse == false)
		{
			g_Item[nItem].pos = Pos;//位置
			g_Item[nItem].move = Rot;
			g_Item[nItem].move *= ITEMMOVESPEED_LOCK;
				
			// 幅、高さ後ほど
			g_Item[nItem].ItemType = Type;
			g_Item[nItem].bUse = true;
			//g_Item[nItem].nLife = 200;
			break;
		}
		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffItem->Unlock();
}


//=============================
//アイテムの取得制限付き設定処理
//=============================
void SetItem2(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, ITEMTYPE Type, int NoGetCnt)
{
	VERTEX_3D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nItem = 0; nItem < NUMITEM; nItem++)
	{
		if (g_Item[nItem].bUse == false)
		{
			g_Item[nItem].pos = Pos;//位置
			g_Item[nItem].move = Rot;
			g_Item[nItem].move *= ITEMMOVESPEED_LOCK;

			// 幅、高さ後ほど
			g_Item[nItem].ItemType = Type;
			g_Item[nItem].bUse = true;
			g_Item[nItem].bGetNO = true;
			g_Item[nItem].nStayGetCnt = NoGetCnt;

			break;
		}
		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffItem->Unlock();
}