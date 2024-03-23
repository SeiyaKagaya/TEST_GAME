//=============================================
//
//テレビのギミック[TV.h]
//Auther Matsuda Towa
//
//=============================================
#include "TV.h"
#include "input.h"
#include "Player.h"
#include "Player2.h"
#include "keyinfo.h"

//=============================================
//グローバル変数
//=============================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTV = NULL;
LPDIRECT3DTEXTURE9 g_pTextureTV = {}; //テクスチャポインタ
//D3DXVECTOR3 g_movefield; //移動量
D3DXMATRIX	g_mtxWorldTV;
TV_VISION g_TV_VISION;

//=============================================
//初期化処理
//=============================================
void InitTV(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TV.png",
		&g_pTextureTV
	);

	//お湯の初期設定
	g_TV_VISION.pos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_TV_VISION.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_TV_VISION.fWide = TVVISION_WIDE;
	g_TV_VISION.fHeight = TVVISION_HEIGHT;
	g_TV_VISION.fTexU = TV_TEX_MOVE;
	g_TV_VISION.bUse = false;
	g_TV_VISION.bOn = false;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffTV, NULL);

	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffTV->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_TV_VISION.pos.x - g_TV_VISION.fWide, g_TV_VISION.pos.y + g_TV_VISION.fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_TV_VISION.pos.x + g_TV_VISION.fWide, g_TV_VISION.pos.y + g_TV_VISION.fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_TV_VISION.pos.x - g_TV_VISION.fWide, g_TV_VISION.pos.y - g_TV_VISION.fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_TV_VISION.pos.x + g_TV_VISION.fWide, g_TV_VISION.pos.y - g_TV_VISION.fHeight, 0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャの座標指定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_TV_VISION.fTexU, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_TV_VISION.fTexU, 1.0f);

	g_pVtxBuffTV->Unlock();
}

//=============================================
//終了処理
//=============================================
void UninitTV(void)
{
	//テクスチャの破棄
	if (g_pTextureTV != NULL)
	{
		g_pTextureTV->Release();
		g_pTextureTV = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTV != NULL)
	{
		g_pVtxBuffTV->Release();
		g_pVtxBuffTV = NULL;
	}
}

//=============================================
//更新処理
//=============================================
void UpdateTV(void)
{
	if (g_TV_VISION.bOn == true)
	{
		if (g_TV_VISION.nWhichPlayer == 0)
		{
			Player* pPlayer = GetPlayer();
			if (GetJoypadTrigger(JOYKEY_UP, g_TV_VISION.nWhichPlayer) == true)
			{
				if(pPlayer->nHaveRemocon>0)
				{
					g_TV_VISION.nSelectChannel++;

					if (g_TV_VISION.nSelectChannel >= NUM_CHANNEL)
					{
						g_TV_VISION.nSelectChannel = 0;
					}
				}
				else if (pPlayer->nHaveRemocon <= 0)
				{
					SetKeyinfo(NOT_HAVE_REMOCON, g_TV_VISION.nWhichPlayer);
				}
			}
			if (GetJoypadTrigger(JOYKEY_DOWN, g_TV_VISION.nWhichPlayer) == true)
			{
				if (pPlayer->nHaveRemocon > 0)
				{
					g_TV_VISION.nSelectChannel--;

					if (g_TV_VISION.nSelectChannel < 0)
					{
						g_TV_VISION.nSelectChannel = NUM_CHANNEL - 1;
					}
				}
				else if (pPlayer->nHaveRemocon <= 0)
				{
					SetKeyinfo(NOT_HAVE_REMOCON, g_TV_VISION.nWhichPlayer);
				}
			}
		}
		else if (g_TV_VISION.nWhichPlayer == 1)
		{
			Player_2P* pPlayer2 = GetPlayer_2P();
			if (GetJoypadTrigger(JOYKEY_UP, g_TV_VISION.nWhichPlayer) == true)
			{
				if (pPlayer2->nHaveRemocon > 0)
				{
					g_TV_VISION.nSelectChannel++;

					if (g_TV_VISION.nSelectChannel >= NUM_CHANNEL)
					{
						g_TV_VISION.nSelectChannel = 0;
					}
				}
				else if (pPlayer2->nHaveRemocon <= 0)
				{
					SetKeyinfo(NOT_HAVE_REMOCON, g_TV_VISION.nWhichPlayer);
				}
			}
			if (GetJoypadTrigger(JOYKEY_DOWN, g_TV_VISION.nWhichPlayer) == true)
			{
				if (pPlayer2->nHaveRemocon > 0)
				{
					g_TV_VISION.nSelectChannel--;

					if (g_TV_VISION.nSelectChannel < 0)
					{
						g_TV_VISION.nSelectChannel = NUM_CHANNEL - 1;
					}
				}
				else if (pPlayer2->nHaveRemocon <= 0)
				{
					SetKeyinfo(NOT_HAVE_REMOCON, g_TV_VISION.nWhichPlayer);
				}
			}
		}

		VERTEX_3D* pVtx;

		//頂点バッファをロックし頂点情報へのポインタを取得
		g_pVtxBuffTV->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャの座標指定
		pVtx[0].tex = D3DXVECTOR2(g_TV_VISION.fTexU * g_TV_VISION.nSelectChannel, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_TV_VISION.fTexU * (g_TV_VISION.nSelectChannel + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_TV_VISION.fTexU * g_TV_VISION.nSelectChannel, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_TV_VISION.fTexU * (g_TV_VISION.nSelectChannel + 1), 1.0f);

		g_pVtxBuffTV->Unlock();
	}
}

//=============================================
//描画処理
//=============================================
void DrawTV(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	if (g_TV_VISION.bUse == true && g_TV_VISION.bOn == true)
	{
		//マトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorldTV);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_TV_VISION.rot.y, g_TV_VISION.rot.x, g_TV_VISION.rot.z);

		D3DXMatrixMultiply(&g_mtxWorldTV, &g_mtxWorldTV, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_TV_VISION.pos.x, g_TV_VISION.pos.y, g_TV_VISION.pos.z);

		D3DXMatrixMultiply(&g_mtxWorldTV, &g_mtxWorldTV, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldTV);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffTV, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTV);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


		//テクスチャを戻す
		pDevice->SetTexture(0, NULL);
	}
}

//=============================================
//テレビの操作処理
//=============================================
void TVController(int nWhichPlayer)
{
	if (nWhichPlayer == 0)
	{
		Player* pPlayer = GetPlayer();
		g_TV_VISION.nWhichPlayer = nWhichPlayer;
		if (pPlayer->nHaveRemocon > 0)
		{
			g_TV_VISION.bOn = g_TV_VISION.bOn ? false : true;
		}
		else if (pPlayer->nHaveRemocon <= 0)
		{
			SetKeyinfo(NOT_HAVE_REMOCON,nWhichPlayer);
		}
	}
	else if (nWhichPlayer == 1)
	{
		Player_2P* pPlayer2 = GetPlayer_2P();
		g_TV_VISION.nWhichPlayer = nWhichPlayer;
		if (pPlayer2->nHaveRemocon > 0)
		{
			g_TV_VISION.bOn = g_TV_VISION.bOn ? false : true;
		}
		else if (pPlayer2->nHaveRemocon <= 0)
		{
			SetKeyinfo(NOT_HAVE_REMOCON,nWhichPlayer);
		}
	}
}

//=============================================
//テレビの画面セット処理
//=============================================
void SetTVVision(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWide, float fHeight)
{
	if (g_TV_VISION.bUse == false)
	{
		g_TV_VISION.pos = pos;
		g_TV_VISION.rot = rot;
		g_TV_VISION.fWide = fWide;
		g_TV_VISION.fHeight = fHeight;
		g_TV_VISION.bUse = true;
		g_TV_VISION.bOn = false;
	}
}

//=============================================
//チャンネル切り替え
//=============================================
void SelectChannel(int nSelectChannel)
{
}

//=============================================
//テレビの情報取得
//=============================================
TV_VISION* GetTVPos(void)
{
	return &g_TV_VISION;
}
