//=============================================
//
//マップエディター[Model.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "model.h"
#include "input.h"
#include "camera.h"
#include "TV.h"
//#include "field.h"
#include "shadow.h"
#include "bathgimmick.h"
#include "Actionzone.h"
#include "particle.h"

//=============================================
//マクロ定義
//=============================================
#define DAMPING_COEFFICIENT	(0.2f) //抵抗力
#define MAX_MODEL	(256) //モデルの最大数 
#define MODEL_SHADOW_RADIUS	(40.0f)
#define BATH_ACTIONZONE_RADIUS	(120.0f)	//お風呂のギミック判定
#define KEYPARTICLERADIUS		(100.0f)	//鍵に付随するパーティクルの半径

//=============================================
//グローバル変数
//=============================================
LPDIRECT3DTEXTURE9 g_apTextureModel[NUM_MODEL][NUM_TEXTURE] = {}; //テクスチャポインタ
MAPOBJECT g_aModel[MAX_MODEL];

//=============================================
//モデルの種類
//=============================================
static const char* MODEL_NAME[NUM_MODEL] =
{
	"data\\MODEL\\bath.x",
	"data\\MODEL\\cactus.x",
	"data\\MODEL\\cardboard.x",
	"data\\MODEL\\Cupboard.x",
	"data\\MODEL\\desk.x",
	"data\\MODEL\\door.x",
	"data\\MODEL\\flower pot.x",
	"data\\MODEL\\garage.x",
	"data\\MODEL\\key1.x",
	"data\\MODEL\\key2.x",
	"data\\MODEL\\key3.x",
	"data\\MODEL\\kitchen.x",
	"data\\MODEL\\metalshelf.x",
	"data\\MODEL\\microwaveoven.x",
	"data\\MODEL\\pot.x",
	"data\\MODEL\\refrigerator.x",
	"data\\MODEL\\slidedoor.x",
	"data\\MODEL\\sofa.x",
	"data\\MODEL\\stairs.x",
	"data\\MODEL\\swollencactus.x",
	"data\\MODEL\\toilet.x",
	"data\\MODEL\\TV.x",
	"data\\MODEL\\TVstand.x",
	"data\\MODEL\\Washbasin.x",
	"data\\MODEL\\cube.x",
	"data\\MODEL\\safe.x",
	"data\\MODEL\\escapedoor.x",
	"data\\MODEL\\Button.x",

};

//=============================================
//ポリゴンの初期化処理
//=============================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntType = 0; nCntType < NUM_MODEL; nCntType++)
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX(MODEL_NAME[nCntType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aModel[nCntType].pBuffMat,
			NULL,
			&g_aModel[nCntType].nNumMat,
			&g_aModel[nCntType].pMesh);

		D3DXMATERIAL* pMat; //マテリアルポインタ
		pMat = (D3DXMATERIAL*)g_aModel[nCntType].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntType].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_apTextureModel[nCntType][nCntMat]
				);
			}
		}
	}

//	int nNumVtx; //頂点数
//	DWORD sizeFVF; //頂点フォーマットのサイズ
//	BYTE* pVtxBuff; //頂点バッファのポインタ

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{

		g_aModel[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //モデルの初期位置
		g_aModel[nCnt].Minpos = D3DXVECTOR3(100000.0f, 1000000.0f, 1000000.0f); //モデルの最小位置
		g_aModel[nCnt].Maxpos = D3DXVECTOR3(-10000.0f, -1000000.0f, -100000.0f); //モデルの最大位置
		g_aModel[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //初期の方向
		g_aModel[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //初期の移動速度
		g_aModel[nCnt].nShadow = -1;
		g_aModel[nCnt].nType = MODELTYPE_BATH;
		g_aModel[nCnt].bUse = false;
		g_aModel[nCnt].bCollision = false;



		//------------------------------------------------------------------------------------------これダメ
	////	頂点数の取得
	//	nNumVtx = g_aModel[g_aModel[nCnt].nType].pMesh->GetNumVertices();
	////	頂点フォーマットのサイズを取得
	//	sizeFVF = D3DXGetFVFVertexSize(g_aModel[g_aModel[nCnt].nType].pMesh->GetFVF());

	//	//頂点バッファのロック
	//	g_aModel[g_aModel[nCnt].nType].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	//	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	//	{
	//		//頂点座標の代入
	//		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

	//		if (vtx.x > g_aModel[nCnt].Maxpos.x)
	//		{
	//			g_aModel[nCnt].Maxpos.x = vtx.x;
	//		}
	//		if (vtx.x < g_aModel[nCnt].Minpos.x)
	//		{
	//			g_aModel[nCnt].Minpos.x = vtx.x;
	//		}

	//		if (vtx.y > g_aModel[nCnt].Maxpos.y)
	//		{
	//			g_aModel[nCnt].Maxpos.y = vtx.y;
	//		}
	//		if (vtx.y < g_aModel[nCnt].Minpos.y)
	//		{
	//			g_aModel[nCnt].Minpos.y = vtx.y;
	//		}

	//		if (vtx.z > g_aModel[nCnt].Maxpos.z)
	//		{
	//			g_aModel[nCnt].Maxpos.z = vtx.z;
	//		}
	//		if (vtx.z < g_aModel[nCnt].Minpos.z)
	//		{
	//			g_aModel[nCnt].Minpos.z = vtx.z;
	//		}

	//		// 次の頂点に進む
	//		pVtxBuff += sizeFVF;

	//	}

	//	g_aModel[g_aModel[nCnt].nType].pMesh->UnlockVertexBuffer();



	}
}

//=============================================
//ポリゴンの終了処理
//=============================================
void UninitModel(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		//		if (g_aModel[nCnt].bUse == true)
		//		{
					//メッシュの破棄
		if (g_aModel[nCnt].pMesh != NULL)
		{
			g_aModel[nCnt].pMesh->Release();
			g_aModel[nCnt].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_aModel[nCnt].pBuffMat != NULL)
		{
			g_aModel[nCnt].pBuffMat->Release();
			g_aModel[nCnt].pBuffMat = NULL;
		}

		for (int nCntTex = 0; nCntTex < (int)g_aModel[nCnt].nNumMat; nCntTex++)
		{
			// テクスチャの破棄
			if (g_apTextureModel[nCnt][nCntTex] != NULL)
			{
				g_apTextureModel[nCnt][nCntTex]->Release();
				g_apTextureModel[nCnt][nCntTex] = NULL; // 解放後に NULL を設定
			}
		}
		//		}
	}
}

//=============================================
//ポリゴンの更新処理
//=============================================
void UpdateModel(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == true)
		{
			if (g_aModel[nCnt].nType == MODELTYPE_KEY1)
			{
				SetParticle(g_aModel[nCnt].pos, KEYPARTICLERADIUS, 12, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.04f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_KEY2)
			{
				SetParticle(g_aModel[nCnt].pos, KEYPARTICLERADIUS, 12, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.04f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_KEY3)
			{
				SetParticle(g_aModel[nCnt].pos, KEYPARTICLERADIUS, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.04f));
			}

		}
	}
	
}

//=============================================
//ポリゴンの描画処理
//=============================================
void DrawModel(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DMATERIAL9 matDef; //現在のマテリアルの保存
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	//現在を取得
	pDevice->GetMaterial(&matDef);

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == true)
		{
			//マトリックスの初期化
			D3DXMatrixIdentity(&g_aModel[nCnt].mtxWorld);

			//αテストを有効
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCnt].rot.y, g_aModel[nCnt].rot.x, g_aModel[nCnt].rot.z);

			D3DXMatrixMultiply(&g_aModel[nCnt].mtxWorld, &g_aModel[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCnt].pos.x, g_aModel[nCnt].pos.y, g_aModel[nCnt].pos.z);

			D3DXMatrixMultiply(&g_aModel[nCnt].mtxWorld, &g_aModel[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCnt].mtxWorld);

			D3DXMATERIAL* pMat; //マテリアル

			pMat = (D3DXMATERIAL*)g_aModel[g_aModel[nCnt].nType].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aModel[g_aModel[nCnt].nType].nNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureModel[g_aModel[nCnt].nType][nCntMat]);

				//パーツの設定
				g_aModel[g_aModel[nCnt].nType].pMesh->DrawSubset(nCntMat);
			}
			//αテストを無効に
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

			//保存してたマテリアルを戻す
			pDevice->SetMaterial(&matDef);

			//テクスチャを戻す
			pDevice->SetTexture(0, NULL);
		}
	}
}

//=============================================
//ポリゴンの設定
//=============================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ModelType nType)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == false)
		{
			g_aModel[nCnt].pos = pos;
			g_aModel[nCnt].rot = rot;
			g_aModel[nCnt].nType = nType;


			if (g_aModel[nCnt].nType == MODELTYPE_BATH)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS, ACTION_TYPE_BATH, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_DESK)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS, ACTION_TYPE_DESK, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.7f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_KEY1)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS + 20.0f, ACTION_TYPE_KEY_1, D3DXCOLOR(0.5f, 0.5f, 0.0f, 0.7f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_KEY2)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS + 20.0f, ACTION_TYPE_KEY_2, D3DXCOLOR(0.5f, 1.0f, 1.0f, 0.7f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_KEY3)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS + 20.0f, ACTION_TYPE_KEY_3, D3DXCOLOR(1.0f, 0.5f, 1.0f, 0.7f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_KITCHEN)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS, ACTION_TYPE_KITCHEN, D3DXCOLOR(0.5f, 0.6f, 1.0f, 0.7f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_TV)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS, ACTION_TYPE_TV, D3DXCOLOR(0.0f, 0.5f, 0.0f, 0.7f));
				SetTVVision(D3DXVECTOR3(g_aModel[nCnt].pos.x - 17.0f, g_aModel[nCnt].pos.y + 28.0f, g_aModel[nCnt].pos.z)
					, g_aModel[nCnt].rot
					, TVVISION_WIDE
					, TVVISION_HEIGHT);
			}
            if (g_aModel[nCnt].nType == MODELTYPE_SAFE)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS, ACTION_TYPE_MONEYBOX, D3DXCOLOR(0.0f, 0.5f, 0.0f, 0.7f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_CUPBOARD)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS, ACTION_TYPE_CUPBOARD, D3DXCOLOR(0.0f, 0.5f, 0.0f, 0.7f));
			}

			/*if (g_aModel[nCnt].nType == MODELTYPE_BUTTON)
			{
				g_aModel[nCnt].bCollision = false;
			}*/
			//SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS, ACTION_TYPE_MAX, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f));



			g_aModel[nCnt].Minpos = D3DXVECTOR3(100000.0f, 1000000.0f, 100000.0f); //モデルの最小位置
			g_aModel[nCnt].Maxpos = D3DXVECTOR3(-10000.0f, -1000000.0f, -100000.0f); //モデルの最大位置

			int nNumVtx; //頂点数
			DWORD sizeFVF; //頂点フォーマットのサイズ
			BYTE* pVtxBuff; //頂点バッファのポインタ

			//頂点数の取得
			nNumVtx = g_aModel[g_aModel[nCnt].nType].pMesh->GetNumVertices();
			//頂点フォーマットのサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(g_aModel[g_aModel[nCnt].nType].pMesh->GetFVF());

			//頂点バッファのロック
			g_aModel[g_aModel[nCnt].nType].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				//頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				// 座標変換行列を作成
				D3DXMATRIXA16 matRotation;
				D3DXMatrixRotationYawPitchRoll(&matRotation, rot.y, rot.x, rot.z);

				// 頂点座標を回転
				D3DXVec3TransformCoord(&vtx, &vtx, &matRotation);

				if (vtx.x > g_aModel[nCnt].Maxpos.x)
				{
					g_aModel[nCnt].Maxpos.x = vtx.x;
				}
				if (vtx.x < g_aModel[nCnt].Minpos.x)
				{
					g_aModel[nCnt].Minpos.x = vtx.x;
				}

				if (vtx.y > g_aModel[nCnt].Maxpos.y)
				{
					g_aModel[nCnt].Maxpos.y = vtx.y;
				}
				if (vtx.y < g_aModel[nCnt].Minpos.y)
				{
					g_aModel[nCnt].Minpos.y = vtx.y;
				}

				if (vtx.z > g_aModel[nCnt].Maxpos.z)
				{
					g_aModel[nCnt].Maxpos.z = vtx.z;
				}
				if (vtx.z < g_aModel[nCnt].Minpos.z)
				{
					g_aModel[nCnt].Minpos.z = vtx.z;
				}

				// 次の頂点に進む
				pVtxBuff += sizeFVF;
			}

			g_aModel[g_aModel[nCnt].nType].pMesh->UnlockVertexBuffer();

			g_aModel[nCnt].bUse = true;

			if (g_aModel[nCnt].nType == MODELTYPE_KEY1
				|| g_aModel[nCnt].nType == MODELTYPE_KEY2
				|| g_aModel[nCnt].nType == MODELTYPE_KEY3)
			{//鍵のみ当たり判定削除
				g_aModel[nCnt].bCollision = false;
			}
			else
			{
				g_aModel[nCnt].bCollision = true;
			}
			break;
		}
	}
}
//=============================================
//鍵取得
//=============================================
void GetKey(ModelType nType)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == true && g_aModel[nCnt].nType == nType)
		{
			g_aModel[nCnt].bUse = false;
		}
	}
}
//=============================================
//ポリゴンの情報取得
//=============================================
MAPOBJECT* GetMapObject(void)
{
	return &g_aModel[0];
}

//=============================================
//当たり判定除外処理
//=============================================
void ExclusionCollision(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == true)
		{
			if (g_aModel[nCnt].nType== MODELTYPE_STAIRS)
			{
				g_aModel[nCnt].bCollision = false;
			}
			if (g_aModel[nCnt].nType == MODELTYPE_BUTTON)
			{
				g_aModel[nCnt].bCollision = false;
			}
		}
	}



	//ここで記載されたものは当たり判定を除外される
	for (int nCnt = 2; nCnt < 23; nCnt++)
	{
		g_aModel[nCnt].bCollision = false;
	}
	for (int nCnt = 35; nCnt < 54; nCnt++)
	{
		g_aModel[nCnt].bCollision = false;
	}

	////どれかを当たり判定蘇生させてでかい判定にする------------------------------
	////12--ダンボール１
	g_aModel[11].Minpos = D3DXVECTOR3(-211.0f, 0.0f, -31.0f);
	g_aModel[11].Maxpos = D3DXVECTOR3(211.0f, 153.0f, 31.0f);
	g_aModel[11].bCollision = true;
	////38--ダンボール2
	g_aModel[37].Minpos = D3DXVECTOR3(-31.0f, 0.0f, -90.0f);
	g_aModel[37].Maxpos = D3DXVECTOR3(31.0f, 153.0f, 90.0f);

	g_aModel[37].bCollision = true;
	//47--ダンボール3
	g_aModel[46].Minpos = D3DXVECTOR3(-31.0f, 0.0f, -90.0f);
	g_aModel[46].Maxpos = D3DXVECTOR3(31.0f, 153.0f, 90.0f);
	g_aModel[46].bCollision = true;
	//36--シャッター
	g_aModel[35].Minpos = D3DXVECTOR3(-280.0f, 0.0f, -45.0f);
	g_aModel[35].Maxpos = D3DXVECTOR3(280.0f, 410.0f, -35.0f);
	g_aModel[35].bCollision = true;
}