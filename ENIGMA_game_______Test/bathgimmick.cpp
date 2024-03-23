//=============================================
//
//お風呂のギミック[bathgimmick.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "bathgimmick.h"
#include "steam.h"
#include "model.h"
#include "eyetrap.h"
#include "item.h"
#include "itemUI.h"
#include "keyinfo.h"
#include "sound.h"
//=============================================
//グローバル変数
//=============================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBathGimmick = NULL;
LPDIRECT3DTEXTURE9 g_pTextureBathGimmick = NULL; //テクスチャポインタ
//D3DXVECTOR3 g_movefield; //移動量
D3DXMATRIX	g_mtxWorldBathGimmick;
BathWater g_BathWater;
bool g_bChange; //前後スポーン切り替え

//=============================================
//初期化
//=============================================
void InitBathGimmick(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bathwater.jpg",
		&g_pTextureBathGimmick
	);

	//お湯の初期設定
	g_BathWater.pos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_BathWater.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BathWater.nType = GREEN_WATER;
	g_BathWater.nSteamSpawnCnt = 0;
	g_BathWater.nRunPlayer = -1; //どちらのプレイヤーでもない状態
	g_BathWater.fWide = BATHWATER_WIDE;
	g_BathWater.fDepth = BATHWATER_DEPTH;
	g_BathWater.bItemSpawn = false;
	g_BathWater.bUse = false;
	g_BathWater.bRun = false;

	g_bChange = false;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBathGimmick, NULL);

	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBathGimmick->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_BathWater.pos.x - g_BathWater.fWide, 0.0f, g_BathWater.pos.z + g_BathWater.fDepth);
	pVtx[1].pos = D3DXVECTOR3(g_BathWater.pos.x + g_BathWater.fWide, 0.0f, g_BathWater.pos.z + g_BathWater.fDepth);
	pVtx[2].pos = D3DXVECTOR3(g_BathWater.pos.x - g_BathWater.fWide, 0.0f, g_BathWater.pos.z - g_BathWater.fDepth);
	pVtx[3].pos = D3DXVECTOR3(g_BathWater.pos.x + g_BathWater.fWide, 0.0f, g_BathWater.pos.z - g_BathWater.fDepth);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(50, 200, 50, 255);
	pVtx[1].col = D3DCOLOR_RGBA(50, 200, 50, 255);
	pVtx[2].col = D3DCOLOR_RGBA(50, 200, 50, 255);
	pVtx[3].col = D3DCOLOR_RGBA(50, 200, 50, 255);

	//テクスチャの座標指定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffBathGimmick->Unlock();
}

//=============================================
//終了
//=============================================
void UninitBathGimmick(void)
{
	//テクスチャの破棄
	if (g_pTextureBathGimmick != NULL)
	{
		g_pTextureBathGimmick->Release();
		g_pTextureBathGimmick = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBathGimmick != NULL)
	{
		g_pVtxBuffBathGimmick->Release();
		g_pVtxBuffBathGimmick = NULL;
	}
}

//=============================================
//更新
//=============================================
void UpdateBathGimmick(void)
{
	float Random=0;
	if (g_bChange == true)
	{
		Random = ((float)rand() / RAND_MAX) * 30.0f;
	}

	if (g_bChange == false)
	{
		 Random = ((float)rand() / RAND_MAX) * -30.0f;
	}

	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBathGimmick->Lock(0, 0, (void**)&pVtx, 0);


	if (g_BathWater.bUse == true)
	{
		g_BathWater.nSteamSpawnCnt++;
		if (g_BathWater.nSteamSpawnCnt >= SPAWN_STEAM)
		{
			for (int nUseCnt = 0; nUseCnt < USE_STEAM; nUseCnt++)
			{
				if (g_BathWater.nType == GREEN_WATER)
				{
					SetSteam(D3DXVECTOR3(g_BathWater.pos.x + Random,
						g_BathWater.pos.y,
						g_BathWater.pos.z + Random), 
						D3DXVECTOR3(0.0f, STEAM_SPEED, 0.0f),
						D3DXCOLOR(0.3f,1.0f,0.3f,0.75f));

					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(50, 200, 50, 255);
					pVtx[1].col = D3DCOLOR_RGBA(50, 200, 50, 255);
					pVtx[2].col = D3DCOLOR_RGBA(50, 200, 50, 255);
					pVtx[3].col = D3DCOLOR_RGBA(50, 200, 50, 255);

				}
				else if (g_BathWater.nType == BATH_WATER)
				{
					SetSteam(D3DXVECTOR3(g_BathWater.pos.x + Random,
						g_BathWater.pos.y,
						g_BathWater.pos.z + Random),
						D3DXVECTOR3(0.0f, STEAM_SPEED, 0.0f),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f));

					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				}
			}
			g_BathWater.nSteamSpawnCnt = 0;
			g_bChange = g_bChange ? false : true;
		}
	}

	if (g_BathWater.bRun == true)
	{//お湯の座標を下げる
		if (g_BathWater.bUse == true)
		{
				if (g_BathWater.nType == GREEN_WATER)
				{//風呂が草の時
					g_BathWater.bRun = false;
					SetEyeTrap(g_BathWater.nRunPlayer);
					return;
				}
				else if (g_BathWater.nType == BATH_WATER)
				{//風呂が正常の時
					if (g_BathWater.pos.y == 40.0f)
					{
						PlaySound(SOUND_LABEL_SE_WATER);
					}
					if (g_BathWater.pos.y >= 0)
					{
						g_BathWater.pos.y -= RUNWATER_SPEED;
					}
					else
					{
						SetKeyinfo(TAKE_A_BATH,g_BathWater.nRunPlayer);
						SetItem(D3DXVECTOR3(3000.0f, 200.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_REMOCON);
						g_BathWater.bItemSpawn = true;
						g_BathWater.bUse = false;
					}
				
					//湯気をオフに
					OffSteam();
				}
			
		}
	}
	g_pVtxBuffBathGimmick->Unlock();
}

//=============================================
//描画
//=============================================
void DrawBathGimmick(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	if (g_BathWater.bUse == true)
	{
		//マトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorldBathGimmick);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_BathWater.rot.y, g_BathWater.rot.x, g_BathWater.rot.z);

		D3DXMatrixMultiply(&g_mtxWorldBathGimmick, &g_mtxWorldBathGimmick, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_BathWater.pos.x, g_BathWater.pos.y, g_BathWater.pos.z);

		D3DXMatrixMultiply(&g_mtxWorldBathGimmick, &g_mtxWorldBathGimmick, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBathGimmick);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffBathGimmick, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBathGimmick);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


		//テクスチャを戻す
		pDevice->SetTexture(0, NULL);
	}
}

//=============================================
//お湯の設置
//=============================================
void SetBathWater(D3DXVECTOR3 pos, D3DXVECTOR3 rot , float fWide, float fDepth, WATER_TYPE nType)
{
	if (g_BathWater.bUse == false)
	{
		g_BathWater.pos = pos;
		g_BathWater.rot = rot;
		g_BathWater.fWide = fWide;
		g_BathWater.fDepth = fDepth;
		g_BathWater.nType = nType;
		g_BathWater.nRunPlayer = -1; //どっちのプレイヤーでもない状態
		g_BathWater.bUse = true;
		g_BathWater.bRun = false;
	}
}

//=============================================
//お湯を流す
//=============================================
void RunWater(int nPlayer)
{
	if (g_BathWater.bUse == true)
	{
		g_BathWater.nRunPlayer = nPlayer;
		g_BathWater.bRun = true;
	}
}

//=============================================
//お湯の情報取得
//=============================================
BathWater* GetBathGimmick(void)
{
	return &g_BathWater;
}
