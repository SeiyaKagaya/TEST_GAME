//=========================================================
//
//簡易モーションモデル表示する処理[simple_motion_model.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "simple_motion_model.h"
#include "enemy.h"
#include "keyinfo.h"
#include "sound.h"

//-------------------------------------------
//マクロ定義
//-------------------------------------------
#define LEVER_ACTIONZONE_RADIUS	(120.0f) //お風呂のギミック判定
#define NUM_ROOM	(3) //部屋数
#define LIVING_SPAWN_POS	(D3DXVECTOR3(3675.0f,120.0f,-1923.0f))
#define BASEMENT_SPAWN_POS	(D3DXVECTOR3(-904.0f,20.0f,-1205.0f))
#define BATHROOM_SPAWN_POS	(D3DXVECTOR3(3235.0f,20.0f,-600.0f))

//グローバル変数宣言
bool g_bKeyspawn = false; 
bool g_bKeyspawnTtl = false;

//モデル構造体
typedef struct
{
	const char* pFilePass;	// MODELファイルパス
	SIMPLEMOTIONMODEL MyNum;//自分番号（index）
	SIMPLEMOTIONMODEL ParentNum;//親番号(index).自分を自分と番号に
	SIMPLEMODEL SinpleModel;//posなど
} SIMPLEMODELINFO;



//-------------------------------------------
//　　"ファイルパス","自分(index)"."親(index)"
//-------------------------------------------
SIMPLEMODELINFO g_ModelInfo[SIMPLEMOTIONMODEL_MAX] =
{							//自分-----------------親
	{"data\\MODEL\\key1.x",SIMPLEMOTIONMODEL_Test1,SIMPLEMOTIONMODEL_Test1},//テストのため書き換え必須
	{"data\\MODEL\\key2.x",SIMPLEMOTIONMODEL_Test2,SIMPLEMOTIONMODEL_Test1},
	{"data\\MODEL\\leverroot.x",SIMPLEMOTIONMODEL_LEVER_RED_ROOT,SIMPLEMOTIONMODEL_LEVER_RED_ROOT},
	{"data\\MODEL\\leverroot.x",SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT,SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT},
	{"data\\MODEL\\leverred.x",SIMPLEMOTIONMODEL_LEVER_RED_LEVER,SIMPLEMOTIONMODEL_LEVER_RED_ROOT},
	{"data\\MODEL\\leverblue.x",SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER,SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT},

	{"data\\MODEL\\leverroot.x",SIMPLEMOTIONMODEL_LEVER_RED_ROOT2,SIMPLEMOTIONMODEL_LEVER_RED_ROOT2},
	{"data\\MODEL\\leverroot.x",SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT2,SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT2},
	{"data\\MODEL\\leverred.x",SIMPLEMOTIONMODEL_LEVER_RED_LEVER2,SIMPLEMOTIONMODEL_LEVER_RED_ROOT2},
	{"data\\MODEL\\leverblue.x",SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER2,SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT2},

};

///-------------------------------------------------------------------------モデル
LPD3DXMESH g_pMeshSimpleModel[SIMPLEMOTIONMODEL_MAX] = {};//メッシュ(頂点情報)へのポインタ

LPD3DXBUFFER g_pBuffMatSimpleModel[SIMPLEMOTIONMODEL_MAX] = {};//マテリアルへのポインタ

DWORD dwNumMatSimpleModel[SIMPLEMOTIONMODEL_MAX] = {};//マテリアルの数


//=============================
//簡易モーションモデル初期化処理
//=============================
void InitSimpleModel(void)
{
	for (int SimpleModel = 0; SimpleModel < SIMPLEMOTIONMODEL_MAX; SimpleModel++)//各パーツ本体
	{
		g_ModelInfo[SimpleModel].SinpleModel.bUse = false;
		g_ModelInfo[SimpleModel].SinpleModel.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ModelInfo[SimpleModel].SinpleModel.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}


	g_bKeyspawn = false;
	g_bKeyspawnTtl = false;


	//ここから初期値セット
	//SetSimpleModel(SIMPLEMOTIONMODEL_Test1, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//SetSimpleModel(SIMPLEMOTIONMODEL_Test2, D3DXVECTOR3(30.0f, 40.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	//赤レバー
	SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_RED_ROOT, D3DXVECTOR3(-1180.0f, 100.0f, -1000.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));		//本体
	SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_RED_LEVER, D3DXVECTOR3(0.0f, 0.0f, 8.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//レバー
	
	//チュートリアルレバー赤
	SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_RED_ROOT2, D3DXVECTOR3(2700.0f, 100.0f, 2530.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//本体
	SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_RED_LEVER2, D3DXVECTOR3(0.0f, 0.0f, 8.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//レバー

	//チュートリアルレバー青
	SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT2, D3DXVECTOR3(3300.0f, 100.0f, 1070.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));	//本体
	SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER2, D3DXVECTOR3(0.0f, 0.0f, 8.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//レバー
	//チュートリアルレバー青のアクションゾーン設置
	SetActionZone(D3DXVECTOR3(3300.0f, 100.0f, 1000.0f), LEVER_ACTIONZONE_RADIUS, ACTION_TYPE_LEVER_TUTORIAL2, D3DXCOLOR(1.0f, 0.0f, 0.3f, 0.8f));


	//レバー1のアクションゾーン設置
	SetActionZone(D3DXVECTOR3(-1180.0f, 100.0f, -1000.0f), LEVER_ACTIONZONE_RADIUS, ACTION_TYPE_LEVER_1, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f));
	
	//チュートリアルレバー赤のアクションゾーン設置
	SetActionZone(D3DXVECTOR3(2700.0f, 100.0f, 2530.0f), LEVER_ACTIONZONE_RADIUS, ACTION_TYPE_LEVER_TUTORIAL1, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f));
	
	int fSetRandom = ((float)rand() / RAND_MAX) * (NUM_ROOM - 1); //地下室を除いたに部屋でランダム

	if (fSetRandom == 0)
	{
		//青レバー
		SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT, D3DXVECTOR3(3553.0f, 100.0f, -130.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));	//本体
		SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER, D3DXVECTOR3(0.0f, 0.0f, 8.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//レバー
		//レバー2のアクションゾーン設置
		SetActionZone(D3DXVECTOR3(3553.0f, 100.0f, -126.0f), LEVER_ACTIONZONE_RADIUS, ACTION_TYPE_LEVER_2, D3DXCOLOR(1.0f, 0.0f, 0.3f, 0.8f));
	}
	if (fSetRandom == 1)
	{
		//青レバー
		SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT, D3DXVECTOR3(2928.0f, 200.0f, -2530.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));	//本体
		SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER, D3DXVECTOR3(0.0f, 0.0f, 8.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//レバー
		//レバー2のアクションゾーン設置
		SetActionZone(D3DXVECTOR3(2928.0f, 200.0f, -2524.0f), LEVER_ACTIONZONE_RADIUS, ACTION_TYPE_LEVER_2, D3DXCOLOR(1.0f, 0.0f, 0.3f, 0.8f));
	}

}
//=============================
//簡易モーションモデル終了処理
//=============================
void UninitSimpleModel(void)
{
	for (int SimpleModel = 0; SimpleModel < SIMPLEMOTIONMODEL_MAX; SimpleModel++)
	{
		//メッシュの破棄
		if (g_pMeshSimpleModel[SimpleModel] != NULL)
		{
			g_pMeshSimpleModel[SimpleModel]->Release();
			g_pMeshSimpleModel[SimpleModel] = NULL;
		}
		//マテリアルの破棄
		if (g_pBuffMatSimpleModel[SimpleModel] != NULL)
		{
			g_pBuffMatSimpleModel[SimpleModel]->Release();
			g_pBuffMatSimpleModel[SimpleModel] = NULL;
		}
	}
}
//=============================
//簡易モーションモデル更新処理
//=============================
void UpdateSimpleModel(void)
{
	//*********ここでものに合わせて処理を追加


	//for (int SimpleModel = 0; SimpleModel < SIMPLEMOTIONMODEL_MAX; SimpleModel++)
	//{

	//}
}
//=============================
//簡易モーションモデル描画処理
//=============================
void DrawSimpleModel(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxParent;//計算用マトリックス

	D3DMATERIAL9 matDef;//現在のマテリアル保存用(一時退避)

	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ
	
	
	for (int SimpleModel = 0; SimpleModel < SIMPLEMOTIONMODEL_MAX; SimpleModel++)
	{
		if (g_ModelInfo[SimpleModel].SinpleModel.bUse == true)
		{


			//モデルの位置
		//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_ModelInfo[SimpleModel].SinpleModel.mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ModelInfo[SimpleModel].SinpleModel.rot.y, g_ModelInfo[SimpleModel].SinpleModel.rot.x, g_ModelInfo[SimpleModel].SinpleModel.rot.z);

			D3DXMatrixMultiply(&g_ModelInfo[SimpleModel].SinpleModel.mtxWorld, &g_ModelInfo[SimpleModel].SinpleModel.mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_ModelInfo[SimpleModel].SinpleModel.pos.x, g_ModelInfo[SimpleModel].SinpleModel.pos.y, g_ModelInfo[SimpleModel].SinpleModel.pos.z);

			D3DXMatrixMultiply(&g_ModelInfo[SimpleModel].SinpleModel.mtxWorld, &g_ModelInfo[SimpleModel].SinpleModel.mtxWorld, &mtxTrans);

			//親子関係
			if (g_ModelInfo[SimpleModel].ParentNum == g_ModelInfo[SimpleModel].MyNum)
			{//自分が親
				//プレイヤーとかける
			//	D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &g_Player.mtxWorld);
			}
			else
			{
				//自分の親のマトリックスかけてる
				D3DXMatrixMultiply(&g_ModelInfo[SimpleModel].SinpleModel.mtxWorld, &g_ModelInfo[SimpleModel].SinpleModel.mtxWorld, &g_ModelInfo[g_ModelInfo[SimpleModel].ParentNum].SinpleModel.mtxWorld);

			}

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_ModelInfo[SimpleModel].SinpleModel.mtxWorld);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatSimpleModel[SimpleModel]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)dwNumMatSimpleModel[SimpleModel]; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, NULL);//今回は設定しない

				//モデル(パーツ)の描画
				g_pMeshSimpleModel[SimpleModel]->DrawSubset(nCntMat);

				//保存してたマテリアルを戻す
		//		pDevice->SetMaterial(&matDef);
			}

			//保存してたマテリアルを戻す
			pDevice->SetMaterial(&matDef);

			//テクスチャを戻す
			pDevice->SetTexture(0, NULL);
		}
	}
}

//=============================
//レバーON処理
//=============================
void LaverOn(void)
{
	if (g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_RED_LEVER].SinpleModel.rot.x > -1.75f)
	{
		g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_RED_LEVER].SinpleModel.rot.x -= 0.1f;
	}

	if (g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER].SinpleModel.rot.x > -1.75f)
	{
		g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER].SinpleModel.rot.x -= 0.1f;
	}
	if (g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER].SinpleModel.rot.x <= -1.75f
		&& g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_RED_LEVER].SinpleModel.rot.x <= -1.75f
		&& g_bKeyspawn == false)
	{
		g_bKeyspawn = true;
		PlaySound(SOUND_LABEL_SE_LEVER);
		SpawnKey();
	}
}

//=============================
//チュートリアルレバーON処理
//=============================
void LaverOnTtl(void)
{
	if (g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_RED_LEVER2].SinpleModel.rot.x > -1.75f)
	{
		g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_RED_LEVER2].SinpleModel.rot.x -= 0.1f;
	}

	if (g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER2].SinpleModel.rot.x > -1.75f)
	{
		g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER2].SinpleModel.rot.x -= 0.1f;
	}
	if (g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER2].SinpleModel.rot.x <= -1.75f
		&& g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_RED_LEVER2].SinpleModel.rot.x <= -1.75f
		&& g_bKeyspawnTtl == false)
	{
		g_bKeyspawnTtl = true;
		PlaySound(SOUND_LABEL_SE_LEVER);
		SpawnKeyTtl();
	}
}


//=============================
//キースポーン処理
//=============================
void SpawnKey(void)
{
	int fRandomSpawn = ((float)rand() / RAND_MAX) * NUM_ROOM;
	if (fRandomSpawn == 0)
	{
		SetModel(LIVING_SPAWN_POS,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_KEY1);

		SetKeyinfo(SPAWNPLACE_LIVING,-1);
	}
	if (fRandomSpawn == 1)
	{
		SetModel(BASEMENT_SPAWN_POS,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_KEY1);

		SetKeyinfo(SPAWNPLACE_BASEMENT,-1);
	}
	if (fRandomSpawn == 2)
	{
		SetModel(BATHROOM_SPAWN_POS,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_KEY1);

		SetKeyinfo(SPAWNPLACE_BATHROOM,-1);
	}
	//SetModel(D3DXVECTOR3(-904.0f,
	//	20.0f,
	//	-1205.0f),
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_KEY1);



	SetModel_Enemy(D3DXVECTOR3(-655.0f,
		0.0f,
		-1141.0f),
		D3DXVECTOR3(0.0f, 3.14f, 0.0f));
}

//=============================
//チュートリアルキースポーン処理
//=============================
void SpawnKeyTtl(void)
{

	//2800,50,2200--3200,50,1900--2800,50,1600
		SetModel(D3DXVECTOR3(2800.0f,50.0f,2200.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_KEY1);
		SetModel(D3DXVECTOR3(3200.0f,50.0f,1900.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_KEY2);
		SetModel(D3DXVECTOR3(2800.0f,50.0f,1600.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_KEY3);

		//SetKeyinfo(SPAWNPLACE_LIVING, -1);
}


//=============================
//簡易モーションモデル設定処理
//=============================
void SetSimpleModel(SIMPLEMOTIONMODEL SetUpName_Index,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//***親自身は自分の位置。子はオフセット値を記入
	
	if (g_ModelInfo[SetUpName_Index].SinpleModel.bUse == false)
	{
		g_ModelInfo[SetUpName_Index].SinpleModel.bUse = true;
		g_ModelInfo[SetUpName_Index].SinpleModel.pos = pos;
		g_ModelInfo[SetUpName_Index].SinpleModel.rot = rot;


		//Xファイルの読み込み
		D3DXLoadMeshFromX(g_ModelInfo[SetUpName_Index].pFilePass,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatSimpleModel[SetUpName_Index],
			NULL,
			&dwNumMatSimpleModel[SetUpName_Index],
			&g_pMeshSimpleModel[SetUpName_Index]);
	}
	else
	{
		//エラー
	}
}

//=============================
//鍵スポーンしたか取得
//=============================
bool GetSpawnKey_Lever(void)
{
	return g_bKeyspawn;
}

//=============================
//チュートリアルで鍵スポーンしたか取得
//=============================
bool GetSpawnKey_Leverttl(void)
{
	return g_bKeyspawnTtl;
}