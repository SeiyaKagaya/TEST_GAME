//============================================================================================
//
//タイムリミットを表示する処理[limittime.cpp]
// Author seiya kagaya
//
//============================================================================================
#include"limittime.h"
#include "game.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureLimitTime = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLimitTime = NULL;//頂点バッファへのポリゴン
LimitTime g_aLimitTime[LIMITTIME_NUM];//タイムリミットの情報
NowTime g_Nowtime;//現在の残り時間を格納
D3DXVECTOR3 g_posLimitTime;//タイムリミットの位置

//タイムリミットの値を宣言
int g_nLimitTimeScore = 0;//タイムリミットの値（グローバルで現在のタイムリミット合算値を格納）

//タイムリミットの値を宣言
int g_nLimitTime=0;
//Looopカウント
int g_nLimitCnt = 0;


//=============================
//タイムリミットの初期化処理
//=============================
void InitLimitTime(void)
{
	//タイムリミットの値を代入
	 g_nLimitTimeScore = g_Nowtime.NowTime;//タイムリミットの値（グローバルで現在のタイムリミット合算値を格納）

	 g_nLimitTime = g_Nowtime.NowTime;

	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	int nCntLimitTime;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number000.png", &g_pTextureLimitTime);//--------書き換え済み

	g_posLimitTime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置初期化

	//タイムリミットの情報の初期化(いわゆる初期地点)
	for (nCntLimitTime = 0; nCntLimitTime < LIMITTIME_NUM; nCntLimitTime++)
	{
		g_aLimitTime[nCntLimitTime].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLimitTime[nCntLimitTime].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLimitTime[nCntLimitTime].bUse = false;//使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * LIMITTIME_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffLimitTime, NULL);

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLimitTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLimitTime = 0; nCntLimitTime < LIMITTIME_NUM; nCntLimitTime++)
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
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 225, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標を設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / LIMITTIME_DIVISIONUMBER);//左下
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f / LIMITTIME_DIVISIONUMBER);//右下

		pVtx += 4;//頂点のポインタを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffLimitTime->Unlock();

	//表示場所の設定
	for (int SetCnt = 0; SetCnt <= LIMITTIME_NUM; SetCnt++)
	{
		SetUpLimitTime(D3DXVECTOR3(SCREEN_WIDE - 600.0f - (LIMITTIMEPOS_SPAN * SetCnt), SCREEN_HEIGHT - 700.0f, 0), 0);//１桁//------------8桁
	}

}
//=============================
//タイムリミットの終了処理
//=============================
void UninitLimitTime(void)
{
	//テクスチャの破棄
	if (g_pTextureLimitTime != NULL)
	{
		g_pTextureLimitTime->Release();
		g_pTextureLimitTime = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffLimitTime != NULL)
	{
		g_pVtxBuffLimitTime->Release();
		g_pVtxBuffLimitTime = NULL;
	}
}
//=============================
//タイムリミットの更新処理
//=============================
void UpdateLimitTime(void)
{
	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLimitTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLimitTime = 0; nCntLimitTime < LIMITTIME_NUM; nCntLimitTime++)
	{
		if (g_nLimitTimeScore < ((ENDFRAME / 60) / 3))
		{//残り3分の１

			pVtx[0].col = D3DCOLOR_RGBA(255, 55, 55, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 55, 55, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 25, 25, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 25, 25, 255);
		}
		else if (g_nLimitTimeScore < ((ENDFRAME/60) / 2))
		{//半分切った
			pVtx[0].col = D3DCOLOR_RGBA(255, 241, 55, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 241, 55, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 241, 25, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 241, 25, 255);
		}
		else
		{//通常時

			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		pVtx += 4;//頂点のポインタを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffLimitTime->Unlock();
}
//=============================
//タイムリミットの描画処理
//=============================
void DrawLimitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	int nCntLimitTime=0;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLimitTime, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);//-------書き換え済み

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLimitTime);//---------書き換え済み

	for (nCntLimitTime = 0; nCntLimitTime < LIMITTIME_NUM; nCntLimitTime++)
	{
		if (g_aLimitTime[nCntLimitTime].bUse == true)
		{//タイムリミットが使用されている
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				nCntLimitTime * 4,//描画する最初の頂点インデックス
				2);//描画するプリミティブ数

			
			
		}
	}
//テクスチャを戻す
			pDevice->SetTexture(0, NULL);
}
//=============================
//タイムリミットの設定処理
//=============================
void SetUpLimitTime(D3DXVECTOR3 pos, int nLimitTime)
{//他のところでも呼ぶ可能性があるのでこのままのほうが便利

	VERTEX_2D* pVtx;//頂点情報のポインタ

	int nCntLimitTime = 0;//とりま固定（初期化と同義）

	int aPosTexU[LIMITTIME_NUM];//各行の数値を格納

	int nESCdata=0;//一時避難用の変数

	g_nLimitCnt++;//インクリメント

	if (g_nLimitCnt % 60 == 0)
	{

		g_nLimitTimeScore--;//表示する数値を減らす
	}

	nLimitTime = g_nLimitTimeScore;//一時避難

	for (nCntLimitTime = 0; nCntLimitTime < LIMITTIME_NUM; nCntLimitTime++)//桁をばらして各行の数値を代入//-------------------初期値算出にaddの数値加算処理も入ってる
	{
		nESCdata = g_nLimitTimeScore % 10;//剰余算でのあまり(一番下の値を取得)
		g_nLimitTimeScore /= 10;//本体を10で割り入れる(一番下の値消す)
		aPosTexU[nCntLimitTime] = nESCdata;//一番下の値を代入
	}

	g_nLimitTimeScore = nLimitTime;//バラされてしまったのでもとに戻す

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLimitTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLimitTime = 0; nCntLimitTime < LIMITTIME_NUM; nCntLimitTime++)
	{
		if (g_aLimitTime[nCntLimitTime].bUse == false)
		{//タイムリミットが使用されていない

			g_aLimitTime[nCntLimitTime].bUse = true;//使用してるにする

			g_aLimitTime[nCntLimitTime].pos = pos;

			//頂点座標の更新-----------------------------------
			pVtx[0].pos = D3DXVECTOR3(g_aLimitTime[nCntLimitTime].pos.x - LIMITTIME_POSX, g_aLimitTime[nCntLimitTime].pos.y - LIMITTIME_POSY, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLimitTime[nCntLimitTime].pos.x + LIMITTIME_POSX, g_aLimitTime[nCntLimitTime].pos.y - LIMITTIME_POSY, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLimitTime[nCntLimitTime].pos.x - LIMITTIME_POSX, g_aLimitTime[nCntLimitTime].pos.y + LIMITTIME_POSY, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLimitTime[nCntLimitTime].pos.x + LIMITTIME_POSX, g_aLimitTime[nCntLimitTime].pos.y + LIMITTIME_POSY, 0.0f);

			for (int nCntCheck = 0; nCntCheck < LIMITTIME_NUM; nCntCheck++)
			{
				//テクスチャ座標を設定//理解に苦慮。要復習
				pVtx[0].tex = D3DXVECTOR2((1.0f / LIMITTIME_DIVISIONUMBER) * aPosTexU[nCntCheck], 0.0f);//左上
				pVtx[1].tex = D3DXVECTOR2((1.0f / LIMITTIME_DIVISIONUMBER) * aPosTexU[nCntCheck] + (1.0f / LIMITTIME_DIVISIONUMBER), 0.0f);//右上
				pVtx[2].tex = D3DXVECTOR2((1.0f / LIMITTIME_DIVISIONUMBER) * aPosTexU[nCntCheck], 1.0f);//左下
				pVtx[3].tex = D3DXVECTOR2((1.0f / LIMITTIME_DIVISIONUMBER) * aPosTexU[nCntCheck] + (1.0f / LIMITTIME_DIVISIONUMBER), 1.0f);//右下
			}
			break;
		}
		pVtx += 4;//ポインタを４つ進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffLimitTime->Unlock();
}
//=============================
//タイムリミット加算処理
//=============================
void SubLimitTime(void)
{
	VERTEX_2D* pVtx;//頂点情報のポインタ

	int paPosTexU[LIMITTIME_NUM] = {};//各行の数値を格納
	int nESCdata=0;//一時避難用の変数
	int nLimitTime=0;//合計タイムリミット一時避難

	g_nLimitCnt++;//インクリメント

	if (g_nLimitCnt % 60 == 0)
	{
		g_nLimitTimeScore--;//表示する数値を減らす
	}

	nLimitTime = g_nLimitTimeScore;//一時避難

	for (int nCntLimitTime = 0; nCntLimitTime < LIMITTIME_NUM; nCntLimitTime++)//桁をばらして各行の数値を代入
	{
		nESCdata = g_nLimitTimeScore % 10;//剰余算でのあまり(一番下の値を取得)
		g_nLimitTimeScore /= 10;//本体を10で割り入れる(一番下の値消す)
		paPosTexU[nCntLimitTime] = nESCdata;//一番下の値を代入
	}

	g_nLimitTimeScore = nLimitTime;//バラされてしまったのでもとに戻す

	g_Nowtime.NowTime = g_nLimitTimeScore;//こっちにもコピーしとく

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLimitTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCheck = 0; nCntCheck < LIMITTIME_NUM; nCntCheck++)
	{
		//テクスチャ座標を設定//理解に苦慮。要復習
		pVtx[0].tex = D3DXVECTOR2((1.0f / LIMITTIME_DIVISIONUMBER) * paPosTexU[nCntCheck], 0.0f);//左上
		pVtx[1].tex = D3DXVECTOR2((1.0f / LIMITTIME_DIVISIONUMBER) * paPosTexU[nCntCheck] + (1.0f / LIMITTIME_DIVISIONUMBER), 0.0f);//右上
		pVtx[2].tex = D3DXVECTOR2((1.0f / LIMITTIME_DIVISIONUMBER) * paPosTexU[nCntCheck], 1.0f);//左下
		pVtx[3].tex = D3DXVECTOR2((1.0f / LIMITTIME_DIVISIONUMBER) * paPosTexU[nCntCheck] + (1.0f / LIMITTIME_DIVISIONUMBER), 1.0f);//右下

		pVtx += 4;//ポインタを４つ進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffLimitTime->Unlock();
}
//=============================
//現在の時間取得処理
//=============================
NowTime* GetNowTime(void)
{
	return &g_Nowtime;
}
