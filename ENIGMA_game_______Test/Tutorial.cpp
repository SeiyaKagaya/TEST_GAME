//============================================================================================
//
//チュートリアル表示する処理[tutorial.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "main.h"
#include "input.h"
#include "Tutorial.h"
#include "fade.h"
#include "pressenter.h"
#include"text.h"
#include "sound.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTutorial = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;//頂点バッファへのポリゴン

//=============================
//タイトル画面の初期化処理
//=============================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial.png", &g_pTextureTutorial);//--------書き換え済み

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTutorial, NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTutorial->Unlock();

	InitPressEnter();

	//PlaySound(SOUND_LABEL_SE_INJET);
}
//=============================
//タイトル画面の終了処理
//=============================
void UninitTutorial(void)
{
	//StopSound(SOUND_LABEL_SE_INJET);
	
	//テクスチャの破棄
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}
	//頂点バッファの破棄
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}
	
	//ボタン押せ専用
	UninitPressEnter();
}
//=============================
//タイトル画面の更新処理
//=============================
void UpdateTutorial(void)
{
	if (GetkeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A,0) == true || GetJoypadTrigger(JOYKEY_A, 1) == true)
	{//決定キー(Enterキー)が押された
		PlaySound(SOUND_LABEL_SE_DECISION);

		//PlaySound(SOUND_LABEL_SE_ENTER001);
		
		//モード設定(フェードの後にゲーム画面移行)
		SetFade(MODE_GAME);
	}
	UpdatePressEnter();
}
//=============================
//タイトル画面の描画処理
//=============================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();//----------------書き換え済み

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);//-------書き換え済み

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTutorial);//---------書き換え済み

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類//----------書き換え済み
		0,//描画する最初の頂点インデックス
		2);//描画するプリミティブ数

	
	//テクスチャを戻す
	pDevice->SetTexture(0, NULL);

	DrawPressEnter();
}