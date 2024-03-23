//=============================================
//
//お風呂のギミック[eyetrap.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "eyetrap.h"
#include "sound.h"

//=============================================
//壁のテクスチャの種類
//=============================================
static const char* EyeTrap_TEX_NAME =
{
	"data\\TEXTURE\\trap000.png",
};

//=========================================================
//グローバル変数
//=========================================================
LPDIRECT3DTEXTURE9 g_pTextureEyeEyeTrap = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEyeEyeTrap = NULL;//頂点バッファへのポリゴン
EyeTrap g_EyeTrap[NUM_TRAP];	//ポーズ構造体の情報

//=============================================
//トラップの初期化
//=============================================
void InitEyeTrap(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

//デバイスの取得
	pDevice = GetDevice();

	//	int nCntPause = 0;

		//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		EyeTrap_TEX_NAME,
		&g_pTextureEyeEyeTrap
	);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TRAP, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffEyeEyeTrap, NULL);

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEyeEyeTrap->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntTrap = 0; nCntTrap < NUM_TRAP; nCntTrap++)
	{
		g_EyeTrap[nCntTrap].bUse = false;
		if (nCntTrap == 0)
		{
			g_EyeTrap[nCntTrap].fAlpha = INIT_A_VALUE;
			g_EyeTrap[nCntTrap].nBlindCnt = 0;
			g_EyeTrap[nCntTrap].pos = D3DXVECTOR3(SCREEN_WIDE / 4.0f, SCREEN_HEIGHT / 3.0f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_EyeTrap[nCntTrap].pos.x - SCREEN_WIDE / 4.0f, g_EyeTrap[nCntTrap].pos.y - SCREEN_HEIGHT / 3.5f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_EyeTrap[nCntTrap].pos.x + SCREEN_WIDE / 4.0f, g_EyeTrap[nCntTrap].pos.y - SCREEN_HEIGHT / 3.5f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_EyeTrap[nCntTrap].pos.x - SCREEN_WIDE / 4.0f, g_EyeTrap[nCntTrap].pos.y + SCREEN_HEIGHT / 3.5f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_EyeTrap[nCntTrap].pos.x + SCREEN_WIDE / 4.0f, g_EyeTrap[nCntTrap].pos.y + SCREEN_HEIGHT / 3.5f, 0.0f);
		}
		else if (nCntTrap == 1)
		{
			g_EyeTrap[nCntTrap].fAlpha = INIT_A_VALUE;
			g_EyeTrap[nCntTrap].nBlindCnt = 0;
			g_EyeTrap[nCntTrap].pos = D3DXVECTOR3(SCREEN_WIDE / 1.35f, SCREEN_HEIGHT / 3.0f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_EyeTrap[nCntTrap].pos.x - SCREEN_WIDE / 4.0f, g_EyeTrap[nCntTrap].pos.y - SCREEN_HEIGHT / 3.5f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_EyeTrap[nCntTrap].pos.x + SCREEN_WIDE / 4.0f, g_EyeTrap[nCntTrap].pos.y - SCREEN_HEIGHT / 3.5f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_EyeTrap[nCntTrap].pos.x - SCREEN_WIDE / 4.0f, g_EyeTrap[nCntTrap].pos.y + SCREEN_HEIGHT / 3.5f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_EyeTrap[nCntTrap].pos.x + SCREEN_WIDE / 4.0f, g_EyeTrap[nCntTrap].pos.y + SCREEN_HEIGHT / 3.5f, 0.0f);
		}
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nCntTrap].fAlpha);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nCntTrap].fAlpha);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nCntTrap].fAlpha);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nCntTrap].fAlpha);

		//テキスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	g_pVtxBuffEyeEyeTrap->Unlock();
}

//=============================================
//トラップの終了
//=============================================
void UninitEyeTrap(void)
{
	//テクスチャの破棄
	if (g_pTextureEyeEyeTrap != NULL)
	{
		g_pTextureEyeEyeTrap->Release();
		g_pTextureEyeEyeTrap = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffEyeEyeTrap != NULL)
	{
		g_pVtxBuffEyeEyeTrap->Release();
		g_pVtxBuffEyeEyeTrap = NULL;
	}

}

//=============================================
//トラップの更新
//=============================================
void UpdateEyeTrap(void)
{
	for (int nCnt = 0; nCnt < NUM_TRAP; nCnt++)
	{
		if (g_EyeTrap[nCnt].bUse == true)
		{
			g_EyeTrap[nCnt].nBlindCnt++;
			if (g_EyeTrap[nCnt].nBlindCnt >= BLIND_TIME)
			{
				VERTEX_2D* pVtx;//頂点情報のポインタ

				//頂点バッファをロックし、頂点情報へのポインタを取得
				g_pVtxBuffEyeEyeTrap->Lock(0, 0, (void**)&pVtx, 0);

				g_EyeTrap[nCnt].fAlpha -= 0.1f;
				int nVtx = nCnt * 4;
				//頂点カラーの設定
				pVtx[nVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nCnt].fAlpha);
				pVtx[nVtx + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nCnt].fAlpha);
				pVtx[nVtx + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nCnt].fAlpha);
				pVtx[nVtx + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nCnt].fAlpha);

				if (g_EyeTrap[nCnt].fAlpha <= 0.0f)
				{
					g_EyeTrap[nCnt].fAlpha = 0.0f;
					g_EyeTrap[nCnt].nBlindCnt = 0;
					g_EyeTrap[nCnt].bUse = false;
				}
			}

		}
	}
	g_pVtxBuffEyeEyeTrap->Unlock();

}

//=============================================
//トラップの描画
//=============================================
void DrawEyeTrap(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

//デバイスの取得
	pDevice = GetDevice();//----------------書き換え済み

	for (int nCntTrap = 0; nCntTrap < NUM_TRAP; nCntTrap++)
	{
		if (g_EyeTrap[nCntTrap].bUse == true)
		{
			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEyeEyeTrap, 0, sizeof(VERTEX_2D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);//-------書き換え済み

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEyeEyeTrap);//---------書き換え済み

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類//----------書き換え済み
				4*nCntTrap,//描画する最初の頂点インデックス
				2);//描画するプリミティブ数
			
			//テクスチャを戻す
			pDevice->SetTexture(0, NULL);
		}
	}
}

//=============================================
//トラップの設定
//=============================================
void SetEyeTrap(int nPlayer)
{
	if (g_EyeTrap[nPlayer].bUse == false)
	{
		PlaySound(SOUND_LABEL_SE_EYETRAP);
		g_EyeTrap[nPlayer].nBlindCnt = 0;
		g_EyeTrap[nPlayer].bUse = true;
		g_EyeTrap[nPlayer].fAlpha = INIT_A_VALUE;
		int nVtx = nPlayer * 4;
		VERTEX_2D* pVtx;//頂点情報のポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffEyeEyeTrap->Lock(0, 0, (void**)&pVtx, 0);
		//頂点カラーの設定
		pVtx[nVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nPlayer].fAlpha);
		pVtx[nVtx + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nPlayer].fAlpha);
		pVtx[nVtx + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nPlayer].fAlpha);
		pVtx[nVtx + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nPlayer].fAlpha);
		g_pVtxBuffEyeEyeTrap->Unlock();

	}
}

//=============================================
//トラップの取得
//=============================================
EyeTrap* GetEyeTrap(void)
{
	return &g_EyeTrap[0];
}
