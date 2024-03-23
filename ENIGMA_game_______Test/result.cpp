//============================================================================================
//
//リザルト表示する処理[result.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "result.h"
#include "pressenter.h"
#include "game.h"
#include"text.h"

#include"sound.h"

//マクロ定義
#define NUM_TEX	(2)	//リザルトで使うテクスチャの種類

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureResult[NUM_TEX] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;//頂点バッファへのポリゴン

bool g_ClearFrag = false;

//=============================
//リザルト画面の初期化処理
//=============================
void InitResult(void)
{	
	g_ClearFrag = false;

	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Result000.png", &g_apTextureResult[0]);//--------書き換え済み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Result001.png", &g_apTextureResult[1]);//--------書き換え済み

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffResult, NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の更新-----------------------------------
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDE, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDE, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;//値は固定
	pVtx[1].rhw = 1.0f;//値は固定
	pVtx[2].rhw = 1.0f;//値は固定
	pVtx[3].rhw = 1.0f;//値は固定

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標を設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下





	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();



	InitPressEnter();

	g_ClearFrag = GetGameClearFrag();//ここでClearか判別//----------------------------------------これを利用してif判別

	PlaySound(SOUND_LABEL_BGM001);
}
//=============================
//リザルト画面の終了処理
//=============================
void UninitResult(void)
{
	for (int nCnt = 0; nCnt < NUM_TEX; nCnt++)
	{
		//テクスチャの破棄
		if (g_apTextureResult[nCnt] != NULL)
		{
			g_apTextureResult[nCnt]->Release();
			g_apTextureResult[nCnt] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}


	UninitPressEnter();
	
	StopSound();
}
//=============================
//リザルト画面の更新処理
//=============================
void UpdateResult(void)
{





	UpdatePressEnter();

	if (GetkeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A,0) == true || GetJoypadTrigger(JOYKEY_A, 1) == true)
	{//決定キー(Enterキー)が押された
	
		PlaySound(SOUND_LABEL_SE_DECISION);

		//PlaySound(SOUND_LABEL_SE_ENTER000);
		
		SetFade(MODE_TITLE);
	}
}
//=============================
//リザルト画面の描画処理
//=============================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();//----------------書き換え済み

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);//-------書き換え済み

	//for (int nCnt = 0; nCnt < NUM_TEX; nCnt++)
	{
		if (g_ClearFrag == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureResult[0]);//---------書き換え済み

		}
		else
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureResult[1]);//---------書き換え済み
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類//----------書き換え済み
			0,//描画する最初の頂点インデックス
			2);//描画するプリミティブ数
	}
	
	//テクスチャを戻す
	pDevice->SetTexture(0, NULL);
	DrawPressEnter();
}