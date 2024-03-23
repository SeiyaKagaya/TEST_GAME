//==================================================
//
//フェードに関する処理[fade.cpp]
// Author seiya kagaya
//
//==================================================
#include "main.h"
#include "fade.h"
//#include "sound.h"

//グローバル変数宣言
FADE g_fade;
D3DXCOLOR g_colorfade;
MODE g_ModeNext;
//LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;       //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL; //頂点バッファへのポインタ

int g_fadeCnt = 0;//ゲーム画面への移行時かすかに色が残る問題を対策

//=============================
//フェードの初期化処理
//=============================
void InitFade(MODE mode_next)
{
	LPDIRECT3DDEVICE9 pDevice;  //デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	//変数の初期化
	g_colorfade.a = 1.0f;

	g_fade = FADE_IN;
	
	g_fadeCnt = 0;

	VERTEX_2D* pVtx;  //頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDE, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDE, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffFade->Unlock();
}
//=============================
//フェードの終了処理
//=============================
void UninitFade(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}
//=============================
//フェードの更新処理
//=============================
void UpdateFade(void)
{
	VERTEX_2D* pVtx;  //頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//フェードイン状態

			g_colorfade.a -= 0.05f;	//ポリゴンを透明にしていく

			if (g_colorfade.a <= 0.0f)
			{
				g_colorfade.a = 0.0f;

				g_fade = FADE_NONE;	//何もしていない状態
			}
		}
		else if (g_fade == FADE_OUT)
		{//フェードアウト状態
			g_colorfade.a += 0.1f;	//ポリゴンを不透明にしていく

			if (g_colorfade.a >= 1.2f)
			{
				g_colorfade.a = 1.2f;

				g_fadeCnt++;//モード移行カウンター

				g_fade = FADE_IN;	//フェードイン状態
			}

			if (g_fadeCnt == 1)
			{//色が薄く残る問題を解決
				//モード設定(次の画面に移行)
				Setmode(g_ModeNext);
				g_fadeCnt = 0;
			}
		}

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDE, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDE, SCREEN_HEIGHT, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorfade.a);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorfade.a);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorfade.a);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorfade.a);
	}
	//頂点バッファのアンロック
	g_pVtxBuffFade->Unlock();
}
//=============================
//フェードの描画処理
//=============================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

//	if (g_fade != FADE_NONE)
//	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
//	}
}
//=============================
//フェードの設定処理
//=============================
void SetFade(MODE mode_next)
{
	if (g_fade == FADE_NONE)
	{
		g_colorfade.a = 0.0f;
		g_fadeCnt = 0;
		g_colorfade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);			//黒いポリゴン(透明)にしておく
		g_fade = FADE_OUT;											//フェードアウト状態に
		g_ModeNext = mode_next;										//次の画面(モード)を設定

	}
}
//=============================
//フェードの取得処理
//=============================
FADE GetFade(void)
{
	return g_fade;
}
