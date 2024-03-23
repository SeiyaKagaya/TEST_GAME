//============================================================================================
//
//enter表示する処理[pressenter.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "main.h"
#include "pressenter.h"
#include "input.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePressEnter = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPressEnter = NULL;//頂点バッファへのポリゴン
PressEnter g_PressEnter;
D3DXCOLOR g_colorfade2;

bool g_nButtonCnt2=false;

//=============================
//タイトル画面の初期化処理
//=============================
void InitPressEnter(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pressA.png", &g_pTexturePressEnter);//--------書き換え済み

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPressEnter, NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

	g_PressEnter.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_colorfade2 = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	g_nButtonCnt2 = false;

	//頂点座標の更新-----------------------------------
	pVtx[0].pos = D3DXVECTOR3(g_PressEnter.pos.x - 380.0f, g_PressEnter.pos.y - 29.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_PressEnter.pos.x + 380.0f, g_PressEnter.pos.y - 29.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_PressEnter.pos.x - 380.0f, g_PressEnter.pos.y + 29.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_PressEnter.pos.x + 380.0f, g_PressEnter.pos.y + 29.0f, 0.0f);

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

	//頂点バッファをアンロックする
	g_pVtxBuffPressEnter->Unlock();
}
//=============================
//タイトル画面の終了処理
//=============================
void UninitPressEnter(void)
{
	//テクスチャの破棄
	if (g_pTexturePressEnter != NULL)
	{
		g_pTexturePressEnter->Release();
		g_pTexturePressEnter = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPressEnter != NULL)
	{
		g_pVtxBuffPressEnter->Release();
		g_pVtxBuffPressEnter = NULL;
	}
}
//=============================
//タイトル画面の更新処理
//=============================
void UpdatePressEnter(void)
{
	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

	g_PressEnter.pos = D3DXVECTOR3(SCREEN_WIDE - 270.0f, SCREEN_HEIGHT - 30.0f, 0.0f);

	//頂点座標の更新-----------------------------------
	pVtx[0].pos = D3DXVECTOR3(g_PressEnter.pos.x - 250.0f, g_PressEnter.pos.y - 20.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_PressEnter.pos.x + 250.0f, g_PressEnter.pos.y - 20.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_PressEnter.pos.x - 250.0f, g_PressEnter.pos.y + 20.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_PressEnter.pos.x + 250.0f, g_PressEnter.pos.y + 20.0f, 0.0f);

	if (g_nButtonCnt2 == false)
	{
		g_colorfade2.a -= 0.022f;	//ポリゴンを不透明にしていく

		if (g_colorfade2.a <= 0.0f)
		{
			g_colorfade2.a = 0.0f;
			g_nButtonCnt2 = true;
		}
	}
	else if (g_nButtonCnt2 == true)
	{
		g_colorfade2.a += 0.022f;	//ポリゴンを不透明にしていく

		if (g_colorfade2.a >= 1.0f)
		{
			g_colorfade2.a = 1.0f;
			g_nButtonCnt2 = false;
		}
	}

	//テクスチャ座標を設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_colorfade2.a);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_colorfade2.a);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_colorfade2.a);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_colorfade2.a);

	//頂点バッファをアンロックする
	g_pVtxBuffPressEnter->Unlock();
}
//=============================
//タイトル画面の描画処理
//=============================
void DrawPressEnter(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();//----------------書き換え済み

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPressEnter, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);//-------書き換え済み

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePressEnter);//---------書き換え済み

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類//----------書き換え済み
		0,//描画する最初の頂点インデックス
		2);//描画するプリミティブ数

	
	//テクスチャを戻す
	pDevice->SetTexture(0, NULL);

}