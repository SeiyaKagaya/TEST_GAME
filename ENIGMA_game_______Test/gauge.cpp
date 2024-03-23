//=============================================
//
//STGtest[gauge.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "gauge.h"
#include "text.h"

//=============================================
//グローバル変数
//=============================================
LPDIRECT3DTEXTURE9 g_pTextureGauge = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL; //頂点バッファへのポインタ
Gauge g_aGauge[CNT_GAUGE]; //ゲージの情報

//=============================================
//ゲージの初期化処理
//=============================================
void InitGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge.png", &g_pTextureGauge);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * CNT_GAUGE, D3DUSAGE_WRITEONLY, 4, D3DPOOL_MANAGED, &g_pVtxBuffGauge, NULL);

	VERTEX_2D* pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < CNT_GAUGE; nCnt++)
	{
		g_aGauge[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge[nCnt].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aGauge[nCnt].Length_X = 0.0f;
		g_aGauge[nCnt].Length_Y = 0.0f;
		g_aGauge[nCnt].MaxLength_X = 0.0f;
		g_aGauge[nCnt].type = GAUGETYPE_MAX;
		g_aGauge[nCnt].Cnt_X = 0;
		g_aGauge[nCnt].MaxCnt_X = 0;
		g_aGauge[nCnt].DrawOK = false;
		g_aGauge[nCnt].bUse = false;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x, g_aGauge[nCnt].pos.y - g_aGauge[nCnt].Length_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x - g_aGauge[nCnt].Length_X, g_aGauge[nCnt].pos.y - g_aGauge[nCnt].Length_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x, g_aGauge[nCnt].pos.y + g_aGauge[nCnt].Length_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x - g_aGauge[nCnt].Length_X, g_aGauge[nCnt].pos.y + g_aGauge[nCnt].Length_Y, 0.0f);

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

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffGauge->Unlock();
}

//=============================================
//ゲージの終了処理
//=============================================
void UninitGauge(void)
{
	//テクスチャの破棄
	if (g_pTextureGauge != NULL)
	{
		g_pTextureGauge->Release();
		g_pTextureGauge = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffGauge != NULL)
	{
		g_pVtxBuffGauge->Release();
		g_pVtxBuffGauge = NULL;
	}
}

//=============================================
//ゲージの更新処理
//=============================================
void UpdateGauge(void)
{
	VERTEX_2D* pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < CNT_GAUGE; nCnt++)
	{
		if (g_aGauge[nCnt].bUse == true)
		{
			if (g_aGauge[nCnt].type == GAUGETYPE_MAINBODY_1P || g_aGauge[nCnt].type == GAUGETYPE_MAINBODY_2P)
			{//本体
				//補正

				float	CorrectionValue = 0.0f;
				if (g_aGauge[nCnt].Cnt_X != 0)
				{
					CorrectionValue = g_aGauge[nCnt].MaxLength_X / (float)g_aGauge[nCnt].MaxCnt_X;//あまりを求める
				}

				//補正後の長さ
				g_aGauge[nCnt].Length_X = CorrectionValue * (float)g_aGauge[nCnt].Cnt_X;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x, g_aGauge[nCnt].pos.y - g_aGauge[nCnt].Length_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x + g_aGauge[nCnt].Length_X, g_aGauge[nCnt].pos.y - g_aGauge[nCnt].Length_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x, g_aGauge[nCnt].pos.y + g_aGauge[nCnt].Length_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x + g_aGauge[nCnt].Length_X, g_aGauge[nCnt].pos.y + g_aGauge[nCnt].Length_Y, 0.0f);
			}
			else
			{//枠
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x - FRANE_MAG_X, g_aGauge[nCnt].pos.y - g_aGauge[nCnt].Length_Y - FRANE_MAG_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x + FRANE_MAG_X + g_aGauge[nCnt].MaxLength_X, g_aGauge[nCnt].pos.y - g_aGauge[nCnt].Length_Y - FRANE_MAG_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x - FRANE_MAG_X, g_aGauge[nCnt].pos.y + g_aGauge[nCnt].Length_Y + FRANE_MAG_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x + FRANE_MAG_X + g_aGauge[nCnt].MaxLength_X, g_aGauge[nCnt].pos.y + g_aGauge[nCnt].Length_Y + FRANE_MAG_Y, 0.0f);
			}
			//頂点カラーの設定
			pVtx[0].col = g_aGauge[nCnt].Col;
			pVtx[1].col = g_aGauge[nCnt].Col;
			pVtx[2].col = g_aGauge[nCnt].Col;
			pVtx[3].col = g_aGauge[nCnt].Col;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffGauge->Unlock();
}

//=============================================
//ゲージの描画処理
//=============================================
void DrawGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCnt = 0; nCnt < CNT_GAUGE; nCnt++)
	{
		if (g_aGauge[nCnt].bUse == true)
		{
			if (g_aGauge[nCnt].DrawOK == true)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureGauge);


				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					nCnt * 4,
					2);

				if (g_aGauge[nCnt].type == GAUGETYPE_FRAME_1P || g_aGauge[nCnt].type == GAUGETYPE_FRAME_2P)
				{
					DrawTextSet(D3DXVECTOR3(g_aGauge[nCnt].pos.x - 0.0f, g_aGauge[nCnt].pos.y - 37.0f, 0.0f), 22, FONT_GENSIN, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), "お料理ゲージ");
				}
			}

		}
		g_aGauge[nCnt].DrawOK = false;
	}
}

//=============================================
//ゲージの設定ポジション処理
//=============================================
//-----------------------位置------------色-----------Yの長さ---------X値としての最大値---Xの最大の長さ----------------タイプ
void SetGauge(D3DXVECTOR3 pos, D3DXCOLOR Col, float Length_Y, int MaxCnt_X, float MaxLength_X, GaugeType type)
{
	VERTEX_2D* pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < CNT_GAUGE; nCnt++)
	{
		if (g_aGauge[nCnt].bUse == false)
		{
			g_aGauge[nCnt].pos = pos;
			g_aGauge[nCnt].Col = Col;
			g_aGauge[nCnt].Length_Y = Length_Y;
			g_aGauge[nCnt].type = type;
			g_aGauge[nCnt].MaxCnt_X = MaxCnt_X;
			g_aGauge[nCnt].MaxLength_X = MaxLength_X;
			g_aGauge[nCnt].bUse = true;
			g_aGauge[nCnt].DrawOK = false;
			break;
		}

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffGauge->Unlock();
}

//==========================================
//ゲージの取得
//==========================================
Gauge* GetGauge(void)
{
	return &g_aGauge[0];
}