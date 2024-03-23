//=============================================
//
//お風呂のギミック[steam.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "steam.h"
#include "bathgimmick.h"

//=============================================
//グローバル変数
//=============================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSteam = NULL;
LPDIRECT3DTEXTURE9 g_pTextureSteam = NULL; //テクスチャポインタ
D3DXMATRIX	g_mtxWorldSteam;
Steam g_aSteam[MAX_STEAM];

void InitSteam(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Steam.png",
		&g_pTextureSteam
	);

	for (int nCnt = 0; nCnt < MAX_STEAM; nCnt++)
	{
		g_aSteam[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //プレイヤーの初期位置
		g_aSteam[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //ムーブ値
		g_aSteam[nCnt].nLife = STEAM_LIFE; //ライフ
		g_aSteam[nCnt].bUse = false;
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_STEAM, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffSteam, NULL);

	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffSteam->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_STEAM; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aSteam[nCnt].pos.x - STEAM_WIDE, g_aSteam[nCnt].pos.y + STEAM_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aSteam[nCnt].pos.x + STEAM_WIDE, g_aSteam[nCnt].pos.y + STEAM_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aSteam[nCnt].pos.x - STEAM_WIDE, g_aSteam[nCnt].pos.y - STEAM_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aSteam[nCnt].pos.x + STEAM_WIDE, g_aSteam[nCnt].pos.y - STEAM_HEIGHT, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);

		//テクスチャの座標指定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	g_pVtxBuffSteam->Unlock();
}

void UninitSteam(void)
{
	//テクスチャの破棄
	if (g_pTextureSteam != NULL)
	{
		g_pTextureSteam->Release();
		g_pTextureSteam = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSteam != NULL)
	{
		g_pVtxBuffSteam->Release();
		g_pVtxBuffSteam = NULL;
	}
}

void UpdateSteam(void)
{
	//デバイスの取得
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_STEAM; nCnt++)
	{
		if (g_aSteam[nCnt].bUse == true)
		{
			g_aSteam[nCnt].pos += g_aSteam[nCnt].move;

			g_aSteam[nCnt].nLife--;

			if (g_aSteam[nCnt].nLife <= 0)
			{
				g_aSteam[nCnt].bUse = false;
			}

		}
	}
}

void DrawSteam(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxTrans; //計算用マトリックス

	D3DXMATRIX mtxView; //ビューマトリックス取得用

	for (int nCnt = 0; nCnt < MAX_STEAM; nCnt++)
	{
		if (g_aSteam[nCnt].bUse == true)
		{
			//zの比較方法変更
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			//zバッファに書き込まない
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			//αテストを有効
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			//マトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldSteam);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンの正面をカメラに向ける
			D3DXMatrixInverse(&g_mtxWorldSteam, NULL, &mtxView);

			g_mtxWorldSteam._41 = 0.0f;
			g_mtxWorldSteam._42 = 0.0f;
			g_mtxWorldSteam._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aSteam[nCnt].pos.x, g_aSteam[nCnt].pos.y, g_aSteam[nCnt].pos.z);

			D3DXMatrixMultiply(&g_mtxWorldSteam, &g_mtxWorldSteam, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldSteam);

			//αブレンディングを加算合成に設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffSteam, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureSteam);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);

			//αテストを無効に
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

			//zの比較方法変更
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			//zバッファに書き込まない
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

			//αブレンディングを元に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			
			//テクスチャを戻す
			pDevice->SetTexture(0, NULL);
		}
	}
}

void SetSteam(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col)
{
	//デバイスの取得
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffSteam->Lock(0, 0, (void**)&pVtx, 0);

	float fVertex;

	fVertex = (float)(rand() % 629 - 314) / 60.0f;

	for (int nCnt = 0; nCnt < MAX_STEAM; nCnt++)
	{
		if (g_aSteam[nCnt].bUse == false)
		{
			g_aSteam[nCnt].pos = pos;
			g_aSteam[nCnt].nLife = STEAM_LIFE; //ライフ
			g_aSteam[nCnt].move.x = sinf(fVertex) * (STEAM_SPEED / 3.0f);
			g_aSteam[nCnt].move.z = cosf(fVertex) * (STEAM_SPEED / 3.0f);
			g_aSteam[nCnt].move.y = STEAM_SPEED;

			int nVtx = nCnt * 4; //頂点座標の指定
			//頂点カラーの設定
			pVtx[nVtx].col = col;
			pVtx[nVtx + 1].col = col;
			pVtx[nVtx + 2].col = col;
			pVtx[nVtx + 3].col = col;

			//g_aSteam[nCnt].move.x = sinf(fVertex) * fMove;
			//g_aSteam[nCnt].move.y = cosf(fVertex) * fMove;
			g_aSteam[nCnt].bUse = true;

			break; //forを抜ける
		}
	}
	g_pVtxBuffSteam->Unlock();

}

void OffSteam(void)
{
	for (int nCnt = 0; nCnt < MAX_STEAM; nCnt++)
	{
		if (g_aSteam[nCnt].bUse == true)
		{
			g_aSteam[nCnt].bUse = false;
		}
	}
}
