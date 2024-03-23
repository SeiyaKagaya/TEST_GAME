//============================================================================================
//
//アイテムUI表示する処理[result.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "item.h"
#include "itemUI.h"
#include "game.h"
#include "particle.h"
#include "input.h"
#include "player.h"
#include "camera.h"
#include "player2.h"
#include "text.h"


//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureItem_UI[ITEMTEXUINUM] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem_UI = NULL;//頂点バッファへのポリゴン

ITEM_UI g_ItemUI[MAXITEMUI];

int g_ItemNum = 0;//アイテム所持数
int g_PointNum[2] = {};//ポインターの位置番号

int g_ItemNum2 = 0;//アイテム所持数


//描画可能か(アップデートで変動・描画で使用)
bool g_DrawOK[3] = {};//三番目だけ常にture

//=============================
//アイテムUIの初期化処理
//=============================
void InitItem_UI(void)
{
	g_ItemNum = 0;
	g_PointNum[0] = 0;
	g_PointNum[1] = 0;



	g_ItemNum2 = 0;
	
	g_DrawOK[0] = false;
	g_DrawOK[1] = false;
	g_DrawOK[2] = true;

	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	int nCntItem_UI;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\frame.png", &g_pTextureItem_UI[0]);//枠
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\frameselect.png", &g_pTextureItem_UI[1]);//ポインター

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_dish.png", &g_pTextureItem_UI[2]);		//皿
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_remocon.png", &g_pTextureItem_UI[3]);	//リモコン
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_vegetable.png", &g_pTextureItem_UI[4]);//野菜
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_soup.png", &g_pTextureItem_UI[5]);//スープ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\key000.png", &g_pTextureItem_UI[6]);//

	
	//アイテムUIの情報の初期化(いわゆる初期地点)
	for (nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	{
		g_ItemUI[nCntItem_UI].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ItemUI[nCntItem_UI].nItemType = ITEMTYPE_MAX;
		g_ItemUI[nCntItem_UI].UItype = ITEM_UI_TYPE_MAX;
		g_ItemUI[nCntItem_UI].PlayerNum = -1;
		g_ItemUI[nCntItem_UI].PosNum = -1;
		g_ItemUI[nCntItem_UI].bUse = false;//使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAXITEMUI, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffItem_UI, NULL);

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem_UI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	{
		//頂点座標の更新-----------------------------------
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;//値は固定
		pVtx[1].rhw = 1.0f;//値は固定
		pVtx[2].rhw = 1.0f;//値は固定
		pVtx[3].rhw = 1.0f;//値は固定

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

		pVtx += 4;//頂点のポインタを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffItem_UI->Unlock();

	SetItem_UI(D3DXVECTOR3(ITEMUISIZE + 10.0f, 460.0f, 0), ITEM_UI_TYPE_POINTER, ITEMTYPE_MAX, -1, 1);//ポインター初期位置

	SetItem_UI(D3DXVECTOR3(ITEMUISIZE + 650.0f, 460.0f, 0), ITEM_UI_TYPE_POINTER, ITEMTYPE_MAX, -1, 2);//ポインター初期位置

		//表示場所の設定
	for (int SetCnt = 0; SetCnt < MAXGETITEM; SetCnt++)
	{
		SetItem_UI(D3DXVECTOR3(ITEMUISIZE + 10.0f + (ITEMUISIZE * 2.1f * SetCnt), 460.0f, 0), ITEM_UI_TYPE_FRAME, ITEMTYPE_MAX, -1, 1);//枠
	}
	//表示場所の設定
	for (int SetCnt2 = 0; SetCnt2 < MAXGETITEM; SetCnt2++)
	{
		SetItem_UI(D3DXVECTOR3(ITEMUISIZE + 640.0f + (ITEMUISIZE * 2.1f * SetCnt2) + 10.0f, 460.0f, 0), ITEM_UI_TYPE_FRAME, ITEMTYPE_MAX, -1, 2);//枠
	}


	SetItem_UI(D3DXVECTOR3(SCREEN_WIDE-100.0f, 35.0f, 0), ITEM_UI_TYPE_KEYUI, ITEMTYPE_MAX, -1, -1);//鍵--プレイヤーなし

}
//=============================
//アイテムUIの終了処理
//=============================
void UninitItem_UI(void)
{
	for (int i = 0; i < ITEMTEXUINUM; i++)
	{
		//テクスチャの破棄
		if (g_pTextureItem_UI[i] != NULL)
		{
			g_pTextureItem_UI[i]->Release();
			g_pTextureItem_UI[i] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffItem_UI != NULL)
	{
		g_pVtxBuffItem_UI->Release();
		g_pVtxBuffItem_UI = NULL;
	}
}
//=============================
//アイテムUIの更新処理
//=============================
void UpdateItem_UI(bool Player1InputOK, bool Player2InputOK)
{
	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem_UI->Lock(0, 0, (void**)&pVtx, 0);

	g_DrawOK[0] = Player1InputOK;
	g_DrawOK[1] = Player2InputOK;


	if (Player1InputOK==true)
	{
	InPutControllerITEM_UI(0);//入力

	}

	if (Player2InputOK == true)
	{
		InPutControllerITEM_UI(1);//入力
	}


	//アイテム序列１
	//----------------------------------------------------------------------------------------------------------------------------------------------
	bool bSetOK = false;
	int EscapeIndex[3] = {};
	bool EscapebUse[3] = {};

	for (int nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	{
		if (g_ItemUI[nCntItem_UI].bUse == true)
		{
			if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_MAINBODY)
			{//UI本体
				if (g_ItemUI[nCntItem_UI].PlayerNum == 1)
				{//プレイヤー1
					if (g_ItemUI[nCntItem_UI].PosNum == 0)
					{
						EscapeIndex[0] = nCntItem_UI;
						EscapebUse[0] = true;

						bSetOK = true;
					}
					else if (g_ItemUI[nCntItem_UI].PosNum == 1)
					{
						EscapeIndex[1] = nCntItem_UI;
						EscapebUse[1] = true;

						bSetOK = true;
					}
					else if (g_ItemUI[nCntItem_UI].PosNum == 2)
					{
						EscapeIndex[2] = nCntItem_UI;
						EscapebUse[2] = true;

						bSetOK = true;
					}
				}
			}
		}
	}

	if (EscapebUse[2] == true)
	{
		if (EscapebUse[1] == false)
		{
			g_ItemUI[EscapeIndex[2]].PosNum = 1;
			//上書き
			EscapebUse[1] = true;
			EscapeIndex[1] = EscapeIndex[2];

		}
	}
	if (EscapebUse[1] == true)
	{
		if (EscapebUse[0] == false)
		{
			g_ItemUI[EscapeIndex[1]].PosNum = 0;
			//上書き...一応
			EscapebUse[0] = true;
			EscapeIndex[0] = EscapeIndex[1];
		}
	}
	//if (EscapebUse[0] == true)
	//{
	if (bSetOK == true)
	{
		for (int i = 0; i < 3; i++)
		{
			//if (g_ItemUI[i].UItype == ITEM_UI_TYPE_MAINBODY)
			//{
			g_ItemUI[EscapeIndex[i]].pos = D3DXVECTOR3(ITEMUISIZE + 10.0f + (ITEMUISIZE * 2.1f * g_ItemUI[EscapeIndex[i]].PosNum), 460.0f, 0);
			//}
		}
	}
	//}
	//----------------------------------------------------------------------------------------------------------------------------------------------

	//アイテム序列２
	//----------------------------------------------------------------------------------------------------------------------------------------------
	bool bSetOK2 = false;
	int EscapeIndex2[3] = {};
	bool EscapebUse2[3] = {};

	for (int nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	{
		if (g_ItemUI[nCntItem_UI].bUse == true)
		{
			if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_MAINBODY)
			{//UI本体
				if (g_ItemUI[nCntItem_UI].PlayerNum == 2)
				{//プレイヤー1
					if (g_ItemUI[nCntItem_UI].PosNum == 0)
					{
						EscapeIndex2[0] = nCntItem_UI;
						EscapebUse2[0] = true;

						bSetOK2 = true;
					}
					else if (g_ItemUI[nCntItem_UI].PosNum == 1)
					{
						EscapeIndex2[1] = nCntItem_UI;
						EscapebUse2[1] = true;

						bSetOK2 = true;
					}
					else if (g_ItemUI[nCntItem_UI].PosNum == 2)
					{
						EscapeIndex2[2] = nCntItem_UI;
						EscapebUse2[2] = true;

						bSetOK2 = true;
					}
				}
			}
		}
	}

	if (EscapebUse2[2] == true)
	{
		if (EscapebUse2[1] == false)
		{
			g_ItemUI[EscapeIndex2[2]].PosNum = 1;
			//上書き
			EscapebUse2[1] = true;
			EscapeIndex2[1] = EscapeIndex2[2];

		}
	}
	if (EscapebUse2[1] == true)
	{
		if (EscapebUse2[0] == false)
		{
			g_ItemUI[EscapeIndex2[1]].PosNum = 0;
			//上書き...一応
			EscapebUse2[0] = true;
			EscapeIndex2[0] = EscapeIndex2[1];
		}
	}
//	if (EscapebUse2[0] == true)
//	{
	if (bSetOK2 == true)
	{
		for (int i = 0; i < 3; i++)
		{
			//if (g_ItemUI[i].UItype == ITEM_UI_TYPE_MAINBODY)
			//{
			g_ItemUI[EscapeIndex2[i]].pos = D3DXVECTOR3(ITEMUISIZE + 640.0f + 10.0f + (ITEMUISIZE * 2.1f * g_ItemUI[EscapeIndex2[i]].PosNum), 460.0f, 0);
			//}
		}
	}
	//}
	//----------------------------------------------------------------------------------------------------------------------------------------------

	for (int nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	{
		if (g_ItemUI[nCntItem_UI].bUse == true)
		{//アイテムUIが使用されている

			if (g_ItemUI[nCntItem_UI].PlayerNum == 1)
			{//プレイヤー1
				if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_POINTER)
				{//ポインターのとき
					g_ItemUI[nCntItem_UI].pos = D3DXVECTOR3(ITEMUISIZE + 10.0f + (ITEMUISIZE * 2.1f * g_PointNum[0]), 460.0f, 0);

				}
			}
			else if (g_ItemUI[nCntItem_UI].PlayerNum == 2)
			{//プレイヤー2
				if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_POINTER)
				{//ポインターのとき
					g_ItemUI[nCntItem_UI].pos = D3DXVECTOR3(ITEMUISIZE + 650.0f + (ITEMUISIZE * 2.1f * g_PointNum[1]), 460.0f, 0);

				}
			}
		}

		if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_POINTER)
		{//ポインターのとき
						//頂点座標の更新-----------------------------------
			pVtx[0].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE * 1.1f, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE * 1.1f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE * 1.1f, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE * 1.1f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE * 1.1f, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE * 1.1f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE * 1.1f, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE * 1.1f, 0.0f);

		}
		else if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_MAINBODY)
		{//ポインターのとき
						//頂点座標の更新-----------------------------------
			pVtx[0].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE * 0.7f, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE * 0.7f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE * 0.7f, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE * 0.7f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE * 0.7f, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE * 0.7f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE * 0.7f, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE * 0.7f, 0.0f);

		}
		else if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_KEYUI)
		{
			//頂点座標の更新-----------------------------------
			pVtx[0].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE2 - 10.0f, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE2 - 10.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE2 - 10.0f, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE2 - 10.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE2 - 10.0f, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE2 - 10.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE2 - 10.0f, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE2 - 10.0f, 0.0f);
		}
		else
		{
		//頂点座標の更新-----------------------------------
			pVtx[0].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE, 0.0f);
		}

		pVtx += 4;//頂点のポインタを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffItem_UI->Unlock();
}
//=============================
//アイテムUIの描画処理
//=============================
void DrawItem_UI(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	int nCntItem_UI = 0;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffItem_UI, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);//-------書き換え済み
	for (nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	{
		if (g_ItemUI[nCntItem_UI].bUse == true)
		{//アイテムUIが使用されている
			if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_FRAME || g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_POINTER)
			{//枠かポインターの時



			//列挙をintに
				int EscapeNum = static_cast<int>(g_ItemUI[nCntItem_UI].UItype);

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureItem_UI[EscapeNum]);//---------書き換え済み
			}
			else if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_MAINBODY)
			{//アイテム自体

					//列挙をintに
				int EscapeNum2 = static_cast<int>(g_ItemUI[nCntItem_UI].nItemType);

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureItem_UI[EscapeNum2 + 2]);//---------書き換え済み
			}
			else if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_KEYUI)
			{//アイテム自体

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureItem_UI[6]);//---------書き換え済み
			}




			if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_KEYUI)
			{//アイテム自体
				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
					nCntItem_UI * 4,//描画する最初の頂点インデックス
					2);//描画するプリミティブ数
			}
			else
			{
				if (g_DrawOK[g_ItemUI[nCntItem_UI].PlayerNum - 1] == true)
				{
					//ポリゴンの描画
					pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
						nCntItem_UI * 4,//描画する最初の頂点インデックス
						2);//描画するプリミティブ数
				}
			}
		
			//テクスチャを戻す
			pDevice->SetTexture(0, NULL);
		}
	}


	//DrawTextSet(D3DXVECTOR3(110.0f, 460.0f, 0.0f), 25, FONT_AKABARASINDELERA, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), "1所持数%dポインタ位置%d",g_ItemNum,g_PointNum[0]);

	//DrawTextSet(D3DXVECTOR3(110.0f, 560.0f, 0.0f), 25, FONT_AKABARASINDELERA, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), "2所持数%dポインタ位置%d", g_ItemNum2, g_PointNum[1]);
}
//=============================
//アイテムUIの設定処理
//=============================
void SetItem_UI(D3DXVECTOR3 pos, ITEM_UI_TYPE ItemUIType, ITEMTYPE ItemType, int PosNum, int PlayerNum)
{//他のところでも呼ぶ可能性があるのでこのままのほうが便利

	VERTEX_2D* pVtx;//頂点情報のポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem_UI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	{
		if (g_ItemUI[nCntItem_UI].bUse == false)
		{//アイテムUIが使用されていない

			g_ItemUI[nCntItem_UI].bUse = true;//使用してるにする

			g_ItemUI[nCntItem_UI].pos = pos;
			g_ItemUI[nCntItem_UI].UItype = ItemUIType;
			g_ItemUI[nCntItem_UI].nItemType = ItemType;
			g_ItemUI[nCntItem_UI].PosNum = PosNum;
			g_ItemUI[nCntItem_UI].PlayerNum = PlayerNum;

			if (ItemUIType == ITEM_UI_TYPE_KEYUI)
			{
				//頂点座標の更新-----------------------------------
				pVtx[0].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE2, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE2, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE2, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE2, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE2, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE2, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE2, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE2, 0.0f);
			}
			else
			{
				//頂点座標の更新-----------------------------------
				pVtx[0].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE, 0.0f);
			}
			
			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 225, 200);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);

			break;
		}
		pVtx += 4;//ポインタを４つ進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffItem_UI->Unlock();
}

//=============================
//鍵取得数描画
//=============================
void DrawHaveKey(int nHaveKey)
{
	DrawTextSet(D3DXVECTOR3(SCREEN_WIDE - 85.0f, -5.0f, 0), 65, FONT_AKABARASINDELERA, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "%d", nHaveKey);
}

//=============================
//アイテム取得できるか処理
//=============================
void GetItem_FromUI(int ItemIndex,int PlayerNum)
{
	ITEM* pItem;
	pItem = GetItem();
	if (PlayerNum == 1)
	{
		Player* pPlayer = GetPlayer();
		if (g_ItemNum < MAXGETITEM)
		{//最大数に達していない

			SetItem_UI(D3DXVECTOR3(ITEMUISIZE + 10.0f + (ITEMUISIZE * 2.1f * g_ItemNum), 460.0f, 0), ITEM_UI_TYPE_MAINBODY, pItem[ItemIndex].ItemType, g_ItemNum, 1);//アイテム

			pItem[ItemIndex].bUse = false;

			g_ItemNum++;

			if (pItem[ItemIndex].ItemType == ITEMTYPE_DISH)//御札
			{
				SetParticle(pItem[ItemIndex].pos, 30.0f, 42, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.35f));
				pPlayer->nHaveDish++;
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_REMOCON)//回復アイテム
			{
				SetParticle(pItem[ItemIndex].pos, 30.0f, 42, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.35f));
				pPlayer->nHaveRemocon++;
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_VEGETABLE)//絵馬(鍵だし??)
			{
				SetParticle(pItem[ItemIndex].pos, 30.0f, 42, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f));
				pPlayer->nHaveVegetable++;

			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_SOUP)//スープ(鍵だし??)
			{
				SetParticle(pItem[ItemIndex].pos, 30.0f, 42, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f));
				pPlayer->nHaveSoup++;

			}
		}
		else
		{
			//取得できない演出
			if (pItem[ItemIndex].ItemType == ITEMTYPE_DISH)//御札
			{
				SetParticle(pItem[ItemIndex].pos, 40.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.55f));
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_REMOCON)//回復アイテム
			{
				SetParticle(pItem[ItemIndex].pos, 40.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.55f));
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_VEGETABLE)//絵馬(鍵だし??)
			{
				SetParticle(pItem[ItemIndex].pos, 40.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.55f));
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_SOUP)//スープ(鍵だし??)
			{
				SetParticle(pItem[ItemIndex].pos, 40.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.55f));

			}
		}
	}
	else if (PlayerNum == 2)
	{
		Player_2P* pPlayer2 = GetPlayer_2P();

		if (g_ItemNum2 < MAXGETITEM)
		{//最大数に達していない

			SetItem_UI(D3DXVECTOR3(ITEMUISIZE + 640.0f + (ITEMUISIZE * 2.1f * g_ItemNum2)+10.0f, 460.0f, 0), ITEM_UI_TYPE_MAINBODY, pItem[ItemIndex].ItemType, g_ItemNum2, 2);//アイテム

			pItem[ItemIndex].bUse = false;

			g_ItemNum2++;

			if (pItem[ItemIndex].ItemType == ITEMTYPE_DISH)//御札
			{
				SetParticle(pItem[ItemIndex].pos, 30.0f, 42, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.35f));
				pPlayer2->nHaveDish++;
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_REMOCON)//回復アイテム
			{
				SetParticle(pItem[ItemIndex].pos, 30.0f, 42, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.35f));
				pPlayer2->nHaveRemocon++;
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_VEGETABLE)//絵馬(鍵だし??)
			{
				SetParticle(pItem[ItemIndex].pos, 30.0f, 42, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f));
				pPlayer2->nHaveVegetable++;
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_SOUP)//スープ(鍵だし??)
			{
				SetParticle(pItem[ItemIndex].pos, 30.0f, 42, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f));
				pPlayer2->nHaveSoup++;

			}

		}
		else
		{
			//取得できない演出
			if (pItem[ItemIndex].ItemType == ITEMTYPE_DISH)//御札
			{
				SetParticle(pItem[ItemIndex].pos, 40.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.55f));
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_REMOCON)//回復アイテム
			{
				SetParticle(pItem[ItemIndex].pos, 40.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.55f));
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_VEGETABLE)//絵馬(鍵だし??)
			{
				SetParticle(pItem[ItemIndex].pos, 40.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.55f));
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_SOUP)//絵馬(鍵だし??)
			{
				SetParticle(pItem[ItemIndex].pos, 40.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.55f));
			}
		}
	}
}






//=============================
//コントローラー入力反映処理(アイテムUI)
//=============================
void InPutControllerITEM_UI(int PlayerNum)
{
//	XINPUT_STATE joykeystate;

	//ショイパットの状態を取得
//	DWORD dwResult = XInputGetState(PlayerNum, &joykeystate);

	//カーソル操作
	if (GetJoypadTrigger(JOYKEY_LEFT, PlayerNum) == true)
	{//Aがおされた(左)

		if (PlayerNum == 0)
		{
			if (g_PointNum[0] > 0)
			{//通常
				g_PointNum[0]--;
			}
			else
			{//上に戻る
				g_PointNum[0] = MAXGETITEM - 1;
			}
		}
		else if (PlayerNum == 1)
		{
			if (g_PointNum[1] > 0)
			{//通常
				g_PointNum[1]--;
			}
			else
			{//上に戻る
				g_PointNum[1] = MAXGETITEM - 1;
			}
		}

	}
	else if (GetJoypadTrigger(JOYKEY_RIGHT, PlayerNum) == true)
	{//Dがおされた(右)
		if (PlayerNum == 0)
		{
			if (g_PointNum[0] < MAXGETITEM - 1)
			{//通常
				g_PointNum[0]++;
			}
			else
			{//下に戻る
				g_PointNum[0] = 0;
			}
		}
		else if (PlayerNum == 1)
		{
			if (g_PointNum[1] < MAXGETITEM - 1)
			{//通常
				g_PointNum[1]++;
			}
			else
			{//下に戻る
				g_PointNum[1] = 0;
			}
		}
	}

	//アイテムドロップ
	if(GetJoypadTrigger(JOYKEY_UP, PlayerNum) == true|| GetJoypadTrigger(JOYKEY_DOWN, PlayerNum) == true)
	{//Wがおされた(上.下)
		Camera* pCamera;
		pCamera = GetCamera();

		Player* pPlayer;
		pPlayer = GetPlayer();

		for (int nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
		{
			if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_MAINBODY)
			{//UI本体
				if (g_ItemUI[nCntItem_UI].PlayerNum == PlayerNum+1)
				{

					if (g_ItemUI[nCntItem_UI].PosNum == g_PointNum[PlayerNum])
					{//位置一致
						View* pViewMtx = GetView();
						View2* pViewMtx2 = GetView_2P();

						D3DXVECTOR3 EscMove;
						D3DXVECTOR3 EscPos2;

						if (PlayerNum == 0)
						{
							EscPos2 = D3DXVECTOR3(pViewMtx[2].ViewPosMtx._41, pViewMtx[2].ViewPosMtx._42, pViewMtx[2].ViewPosMtx._43);
						}
						else if (PlayerNum == 1)
						{
							EscPos2 = D3DXVECTOR3(pViewMtx2[2].ViewPosMtx._41, pViewMtx2[2].ViewPosMtx._42, pViewMtx2[2].ViewPosMtx._43);

						}

						float Xdate = 0.0f;
						float Zdate = 0.0f;

						Zdate = -1.0f;


						float Angle = atan2f(Xdate, Zdate);//これが方角


						//------これはWW

						EscMove.x = sinf(Angle - pCamera[PlayerNum].rot.y - (1.0f * D3DX_PI)) * ITEMMOVESPEED_UI;//三角関数利用して移動の長さを代入
						EscMove.z = cosf(Angle - pCamera[PlayerNum].rot.y - (1.0f * D3DX_PI)) * ITEMMOVESPEED_UI;//三角関数利用して移動の長さを代入
						EscMove.y = 2.0f;

						SetItem2(EscPos2, EscMove, g_ItemUI[nCntItem_UI].nItemType, 15);


						g_ItemUI[nCntItem_UI].PosNum = -1;//一応リセット
						g_ItemUI[nCntItem_UI].bUse = false;

						if (PlayerNum == 0)
						{
					//		Player* pPlayer = GetPlayer();
							if (g_ItemUI[nCntItem_UI].nItemType == ITEMTYPE_DISH)
							{
								pPlayer->nHaveDish--;
							}
							if (g_ItemUI[nCntItem_UI].nItemType == ITEMTYPE_REMOCON)
							{
								pPlayer->nHaveRemocon--;
							}
							if (g_ItemUI[nCntItem_UI].nItemType == ITEMTYPE_VEGETABLE)
							{
								pPlayer->nHaveVegetable--;
							}
							if (g_ItemUI[nCntItem_UI].nItemType == ITEMTYPE_SOUP)
							{
								pPlayer->nHaveSoup--;
							}
							g_ItemNum--;
						}
						else if (PlayerNum == 1)
						{
							Player_2P* pPlayer2 = GetPlayer_2P();
							if (g_ItemUI[nCntItem_UI].nItemType == ITEMTYPE_DISH)
							{
								pPlayer2->nHaveDish--;
							}
							if (g_ItemUI[nCntItem_UI].nItemType == ITEMTYPE_REMOCON)
							{
								pPlayer2->nHaveRemocon--;
							}
							if (g_ItemUI[nCntItem_UI].nItemType == ITEMTYPE_VEGETABLE)
							{
								pPlayer2->nHaveVegetable--;
							}
							if (g_ItemUI[nCntItem_UI].nItemType == ITEMTYPE_SOUP)
							{
								pPlayer2->nHaveSoup--;
							}
							g_ItemNum2--;
						}

						break;
					}
				}
			}
		}


	}
	
	////アイテム使用
	//if (GetJoypadTrigger(JOYKEY_DOWN, PlayerNum) == true)
	//{//Sがおされた(下)
	//	
	//	for (int nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	//	{
	//		if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_MAINBODY)
	//		{//UI本体
	//			if (g_ItemUI[nCntItem_UI].PlayerNum == PlayerNum+1)
	//			{
	//				if (PlayerNum == 0)
	//				{

	//					if (g_ItemUI[nCntItem_UI].PosNum == g_PointNum[PlayerNum])
	//					{//位置一致
	//						g_ItemUI[nCntItem_UI].PosNum = -1;//一応リセット
	//						g_ItemUI[nCntItem_UI].bUse = false;

	//						g_ItemNum--;

	//						break;
	//					}
	//				}
	//				else if (PlayerNum == 1)
	//				{

	//					if (g_ItemUI[nCntItem_UI].PosNum == g_PointNum[PlayerNum])
	//					{//位置一致
	//						g_ItemUI[nCntItem_UI].PosNum = -1;//一応リセット
	//						g_ItemUI[nCntItem_UI].bUse = false;

	//						g_ItemNum2--;

	//						break;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}



	
}

//================================================
//アイテム削除関数
//================================================
void DeleteItem_UI(int PlayerNum, ITEMTYPE ItemType)
{
	for (int nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	{
		if (g_ItemUI[nCntItem_UI].bUse == true)
		{
			if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_MAINBODY)
			{//UI本体
				if (g_ItemUI[nCntItem_UI].PlayerNum == PlayerNum + 1)
				{
					if (g_ItemUI[nCntItem_UI].PlayerNum == 1)
					{
						Player* pPlayer = GetPlayer();
						if (g_ItemUI[nCntItem_UI].nItemType == ItemType)
						{
							//g_ItemUI[nCntItem_UI].PosNum = -1;//一応リセット
							g_ItemUI[nCntItem_UI].bUse = false;
							g_ItemUI[nCntItem_UI].PosNum = -1;

							if (ItemType == ITEMTYPE_DISH)
							{
								pPlayer->nHaveDish--;
							}
							if (ItemType == ITEMTYPE_VEGETABLE)
							{
								pPlayer->nHaveVegetable--;
							}
							if (ItemType == ITEMTYPE_SOUP)
							{
								pPlayer->nHaveSoup--;
							}
							if (ItemType == ITEMTYPE_REMOCON)
							{
								pPlayer->nHaveRemocon--;
							}
							g_ItemNum--;
							break;
						}
					}
					else if (g_ItemUI[nCntItem_UI].PlayerNum == 2)
					{
						Player_2P* pPlayer2 = GetPlayer_2P();
						if (g_ItemUI[nCntItem_UI].nItemType == ItemType)
						{
							//g_ItemUI[nCntItem_UI].PosNum = -1;//一応リセット
							g_ItemUI[nCntItem_UI].bUse = false;
							g_ItemUI[nCntItem_UI].PosNum = -1;

							if (ItemType == ITEMTYPE_DISH)
							{
								pPlayer2->nHaveDish--;
							}
							if (ItemType == ITEMTYPE_VEGETABLE)
							{
								pPlayer2->nHaveVegetable--;
							}
							if (ItemType == ITEMTYPE_SOUP)
							{
								pPlayer2->nHaveSoup--;
							}
							if (ItemType == ITEMTYPE_REMOCON)
							{
								pPlayer2->nHaveRemocon--;
							}
							g_ItemNum2--;
							break;
						}
					}
				}
			}
		}
	}
}
