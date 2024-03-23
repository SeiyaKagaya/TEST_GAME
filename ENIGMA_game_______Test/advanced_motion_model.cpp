//=========================================================
//
//高度モーションモデル表示する処理[advanced_motion_model.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "advanced_motion_model.h"
#include "input.h"
#include <stdio.h>//ヘッダーファイルをインクルード
#include <string.h>//文字列を扱う変数
#include "game.h"




ADMODEL g_AdvancedModel[MODEL_AD_TYPE_MAX];//プレイヤー全体

///-------------------------------------------------------------------------モデル
LPD3DXMESH g_pMeshModel_AD[MODEL_AD_TYPE_MAX][MAX_PARTS_AD] = {};//メッシュ(頂点情報)へのポインタ

LPD3DXBUFFER g_pBuffMatModel_AD[MODEL_AD_TYPE_MAX][MAX_PARTS_AD] = {};//マテリアルへのポインタ

DWORD dwNumMatModel_AD[MODEL_AD_TYPE_MAX][MAX_PARTS_AD] = {};//マテリアルの数

//PDIRECT3DTEXTURE9 g_apTextureModel_AD[MODEL_AD_TYPE_MAX][MAX_PARTS_AD][NUM_TEXTURE_AD] = {}; //テクスチャポインタ

MODEL_AD g_Model3[MODEL_AD_TYPE_MAX];//モデル全体
//--------------------------------------------------------------------------

//モデル構造体--------------------------------
typedef struct
{
	const char* pFilePass;	// MODELファイルパス
	MODELADTYPE MyNume;//自分番号（index）
} MODELADINFO;





//-------------------------------------------
//　　"モーションファイルパス","自分(index)"
//-------------------------------------------
MODELADINFO g_ModelMotionInfo[MODEL_AD_TYPE_MAX] =
{							//自分-----------------親
	{"data\\motionEnigma.txt",MODEL_AD_TYPE_Test1},//テストのため書き換え必須
	{"data\\motionEnigma.txt",MODEL_AD_TYPE_Test2},
};
//**************************
//   2/20　　テクスチャは正常動作しない！！！！！メモリリークがおきる！
//**************************



//各モーションのモデル数
int g_nEscapeCntModel[MODEL_AD_TYPE_MAX] = {};
char g_cModelFileName[MODEL_AD_TYPE_MAX][MAX_PARTS_AD][MAX_WORD2_AD] = {};//パス格納



//=============================
//高度モーションモデル初期化処理
//=============================
void InitAdvancedModel(void)
{
	for (int ModelNum = 0; ModelNum < MODEL_AD_TYPE_MAX; ModelNum++)
	{
		g_nEscapeCntModel[ModelNum] = 0;

		//とりあえずパーツの数(後にtxtで)だけ回す

		//g_AdvancedModel.NowMotionUP = MOTIONTYPE_AD_MAX;
		g_AdvancedModel[ModelNum].NowMotionDOWN = MOTIONTYPE_AD_MAX;

		g_AdvancedModel[ModelNum].OldMotionDOWN = MOTIONTYPE_AD_MAX;

		g_AdvancedModel[ModelNum].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);	//位置


		g_AdvancedModel[ModelNum].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き

		g_AdvancedModel[ModelNum].PARENT = -1;//親子関係

		g_AdvancedModel[ModelNum].JumpFrame = 0;

		g_AdvancedModel[ModelNum].bUse = false;;
		g_AdvancedModel[ModelNum].JumpNow = false;
		g_AdvancedModel[ModelNum].JumpOld = false;

		g_AdvancedModel[ModelNum].NowFrameCntDOWN = 0;
		g_AdvancedModel[ModelNum].NowKeyCntDOWN = 0;

		g_AdvancedModel[ModelNum].NowFrameCntUP = 0;
		g_AdvancedModel[ModelNum].NowKeyCntUP = 0;
		g_AdvancedModel[ModelNum].MotionLoopStop = false;
		g_AdvancedModel[ModelNum].MotionBrend = false;

		g_AdvancedModel[ModelNum].BrendCnt = 0;
		g_AdvancedModel[ModelNum].EscapeMotion = MOTIONTYPE_AD_BREND;

		//-------------------------------------------------モデル系
		g_Model3[ModelNum].nMaxMotionCnt = 0;
		g_Model3[ModelNum].nMaxPartsCnt = 0;
		g_Model3[ModelNum].nMaxLoadPartsCnt = 0;

		for (int nCntParts = 0; nCntParts < MAX_PARTS_AD; nCntParts++)//各パーツ本体
		{
			g_Model3[ModelNum].ModelParts[nCntParts].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model3[ModelNum].ModelParts[nCntParts].Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_Model3[ModelNum].ModelParts[nCntParts].StartPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model3[ModelNum].ModelParts[nCntParts].StartRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_Model3[ModelNum].ModelParts[nCntParts].PEARENT = 0;
			g_Model3[ModelNum].ModelParts[nCntParts].INDEX = 0;

			g_Model3[ModelNum].ModelParts[nCntParts].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model3[ModelNum].ModelParts[nCntParts].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_Model3[ModelNum].ModelParts[nCntParts].calculationExecution = false;
			//mtxはおいておく
		}

		for (int nMotionCnt = 0; nMotionCnt < MAX_MONITORS; nMotionCnt++)//各モーションデータ
		{
			g_Model3[ModelNum].Motion[nMotionCnt].nNumKey = 0;
			g_Model3[ModelNum].Motion[nMotionCnt].nLoop = 0;
			g_Model3[ModelNum].Motion[nMotionCnt].Motiontype = MOTIONTYPE_AD_MAX;


			for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)//各モーション中の各パーツの各キー内のデータ
			{
				g_Model3[ModelNum].Motion[nMotionCnt].KeyData[nCntKey].nSplitFrame = 0;

				for (int nCntParts = 0; nCntParts < MAX_PARTS_AD; nCntParts++)//各モーション中の各パーツデータ
				{
					g_Model3[ModelNum].Motion[nMotionCnt].KeyData[nCntKey].PartsData[nCntParts].CorrectionPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					g_Model3[ModelNum].Motion[nMotionCnt].KeyData[nCntKey].PartsData[nCntParts].CorrectionRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}
		}

		////////ここでセット
		//SetModel_AD(MODEL_AD_TYPE_Test1, D3DXVECTOR3(-50.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
		//LoadXfire_AdModel(MODEL_AD_TYPE_Test1);
		//
		//SetModel_AD(MODEL_AD_TYPE_Test2, D3DXVECTOR3(-50.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
		//LoadXfire_AdModel(MODEL_AD_TYPE_Test2);
	}
}
//=============================
//モデルの終了処理
//=============================
void UninitAdvancedModel(void)
{
	for (int ModelNum = 0; ModelNum < MODEL_AD_TYPE_MAX; ModelNum++)
	{


		for (int nCntModel = 0; nCntModel < MAX_PARTS_AD; nCntModel++)
		{
			// メッシュの破棄
			if (g_pMeshModel_AD[ModelNum][nCntModel] != NULL)
			{
				g_pMeshModel_AD[ModelNum][nCntModel]->Release();
				g_pMeshModel_AD[ModelNum][nCntModel] = NULL; // 解放後に NULL を設定
			}

			// マテリアルの破棄
			if (g_pBuffMatModel_AD[ModelNum][nCntModel] != NULL)
			{
				g_pBuffMatModel_AD[ModelNum][nCntModel]->Release();
				g_pBuffMatModel_AD[ModelNum][nCntModel] = NULL; // 解放後に NULL を設定
			}

			//for (int nCntTex = 0; nCntTex < NUM_TEXTURE_AD; nCntTex++)
			//{
			//	// テクスチャの破棄
			//	if (g_apTextureModel_AD[ModelNum][nCntModel][nCntTex] != NULL)
			//	{
			//		g_apTextureModel_AD[ModelNum][nCntModel][nCntTex]->Release();
			//		g_apTextureModel_AD[ModelNum][nCntModel][nCntTex] = NULL; // 解放後に NULL を設定
			//	}
			//}

		}
	}



}

//=============================
//モデルの更新処理
//=============================
void UpdateAdvancedModel(void)
{
	for (int ModelNum = 0; ModelNum < MODEL_AD_TYPE_MAX; ModelNum++)
	{
		D3DXMATRIX mtxRot, mtxTrans, mtxParent;//計算用マトリックス	


		//とりあえず待機
		g_AdvancedModel[ModelNum].NowMotionDOWN = MOTIONTYPE_AD_STANDBY;



		//上下のモーション
		LowerBodyMotion3(ModelNum);
		//	UpperBodyMotion();

		//前回のモーションデータを更新
		//g_AdvancedModel[ModelNum].OldMotionUP = g_AdvancedModel[ModelNum].NowMotionUP;
		g_AdvancedModel[ModelNum].OldMotionDOWN = g_AdvancedModel[ModelNum].NowMotionDOWN;


		//----------パーツ
		for (int nCnt = 0; nCnt < g_Model3[ModelNum].nMaxPartsCnt; nCnt++)
		{//パーツ分回す
			//モデルの位置
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model3[ModelNum].ModelParts[nCnt].Rot.y, g_Model3[ModelNum].ModelParts[nCnt].Rot.x, g_Model3[ModelNum].ModelParts[nCnt].Rot.z);

			D3DXMatrixMultiply(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Model3[ModelNum].ModelParts[nCnt].Pos.x, g_Model3[ModelNum].ModelParts[nCnt].Pos.y, g_Model3[ModelNum].ModelParts[nCnt].Pos.z);

			D3DXMatrixMultiply(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &mtxTrans);

			//親子関係
			if (g_Model3[ModelNum].ModelParts[nCnt].PEARENT == -1)
			{
				//プレイヤーとかける
				D3DXMatrixMultiply(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_AdvancedModel[ModelNum].mtxWorld);
			}
			else
			{
				//自分の親のマトリックス欠けてる
				D3DXMatrixMultiply(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[g_Model3[ModelNum].ModelParts[nCnt].PEARENT].mtxWorld);

			}
		}
	}
}
//=============================
//モデルの描画処理
//=============================
void DrawAdvancedModel(void)
{
	for (int ModelNum = 0; ModelNum < MODEL_AD_TYPE_MAX; ModelNum++)
	{
		if (g_AdvancedModel[ModelNum].bUse == true)
		{
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			D3DXMATRIX mtxRot, mtxTrans, mtxParent;//計算用マトリックス

			D3DMATERIAL9 matDef;//現在のマテリアル保存用(一時退避)

			D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

			//キャラ全体の基準(親の親)
				//---------------------------------------------------------------------------------------------------プレイヤーの位置のみ
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_AdvancedModel[ModelNum].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_AdvancedModel[ModelNum].rot.y, g_AdvancedModel[ModelNum].rot.x, g_AdvancedModel[ModelNum].rot.z);

			D3DXMatrixMultiply(&g_AdvancedModel[ModelNum].mtxWorld, &g_AdvancedModel[ModelNum].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_AdvancedModel[ModelNum].pos.x, g_AdvancedModel[ModelNum].pos.y, g_AdvancedModel[ModelNum].pos.z);

			D3DXMatrixMultiply(&g_AdvancedModel[ModelNum].mtxWorld, &g_AdvancedModel[ModelNum].mtxWorld, &mtxTrans);



			for (int nCnt = 0; nCnt < g_Model3[ModelNum].nMaxPartsCnt; nCnt++)
			{
				//---------------------------------------------------------------------------------------------------モデルの位置

				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld);

				//向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model3[ModelNum].ModelParts[nCnt].Rot.y, g_Model3[ModelNum].ModelParts[nCnt].Rot.x, g_Model3[ModelNum].ModelParts[nCnt].Rot.z);

				D3DXMatrixMultiply(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &mtxRot);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_Model3[ModelNum].ModelParts[nCnt].Pos.x, g_Model3[ModelNum].ModelParts[nCnt].Pos.y, g_Model3[ModelNum].ModelParts[nCnt].Pos.z);

				D3DXMatrixMultiply(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &mtxTrans);


				//親子関係
				if (g_Model3[ModelNum].ModelParts[nCnt].PEARENT == -1)
				{
					//プレイヤーとかける
					D3DXMatrixMultiply(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_AdvancedModel[ModelNum].mtxWorld);
				}
				else
				{
					//自分の親のマトリックス欠けてる
					D3DXMatrixMultiply(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[g_Model3[ModelNum].ModelParts[nCnt].PEARENT].mtxWorld);
				}

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld);

				//現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				//マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_pBuffMatModel_AD[ModelNum][nCnt]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)dwNumMatModel_AD[ModelNum][nCnt]; nCntMat++)
				{
					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//テクスチャの設定
					pDevice->SetTexture(0, NULL);//今回は設定しない
					//テクスチャの設定
				//	pDevice->SetTexture(0, g_apTextureModel_AD[ModelNum][nCnt][nCntMat]);

					//モデル(パーツ)の描画
					g_pMeshModel_AD[ModelNum][nCnt]->DrawSubset(nCntMat);

					//保存してたマテリアルを戻す
				//	pDevice->SetMaterial(&matDef);
				}
			}
			//保存してたマテリアルを戻す
			pDevice->SetMaterial(&matDef);

			//テクスチャを戻す
			pDevice->SetTexture(0, NULL);
		}
	}
}
//=============================
//プレイヤー情報取得処理
//=============================
ADMODEL* GetAdvancedModel(int Index)
{
	return &g_AdvancedModel[Index];
}

//=============================
//プレイヤーメッシュ情報取得処理
//=============================
LPD3DXMESH* GetMesh_AdvancedModel(int Index)
{
	return &g_pMeshModel_AD[Index][0];
}

//=============================
//変換処理2D--------------------------めちゃ大事
//=============================
void ConversionAdvancedModelRot2(int Index, float fRot, int nCnt)
{
	//ケツにf
	//fmodfとは+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//fmod関数は主に浮動小数点数の誤差を考慮しつつ、剰余を計算するために使用されます。
	//通常、整数での剰余演算子% と同じような働きをしますが、
	//整数の剰余演算子は整数同士の演算に特化しており、浮動小数点数には対応していません。
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//fabsfとは+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//浮動小数点数の絶対値を計算するために使用されます。
	//ここでは、EscapeRotDiff2 の絶対値が D3DX_PI を超えているかどうかを判定しています
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// 角度を範囲内に収める
	fRot = fmodf(fRot + D3DX_PI, 2 * D3DX_PI) - D3DX_PI;

	// 角度の差分
	float rotDiff = fRot - g_AdvancedModel[Index].rot.y;

	// 差分が範囲外なら補正---------------------------------------------------------------近いうちちゃんと内容調べる
	if (fabsf(rotDiff) > D3DX_PI)
	{
		rotDiff = (rotDiff < 0) ? (rotDiff + 2 * D3DX_PI) : (rotDiff - 2 * D3DX_PI);
	}

	g_AdvancedModel[Index].rot.y += rotDiff * 0.1f;

	if (g_AdvancedModel[Index].rot.y > D3DX_PI)
	{
		g_AdvancedModel[Index].rot.y -= (2.0f * D3DX_PI);
	}
	else if (g_AdvancedModel[Index].rot.y < -D3DX_PI)
	{
		g_AdvancedModel[Index].rot.y += (2.0f * D3DX_PI);
	}

}
//=============================
//変換処理3D--------------------------めちゃ大事
//=============================
D3DXVECTOR3 ConversionAdvancedModelRot3(D3DXVECTOR3 fRot, int nCnt)
{

	//ケツにf
	//fmodfとは+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//fmod関数は主に浮動小数点数の誤差を考慮しつつ、剰余を計算するために使用されます。
	//通常、整数での剰余演算子% と同じような働きをしますが、
	//整数の剰余演算子は整数同士の演算に特化しており、浮動小数点数には対応していません。
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//fabsfとは+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//浮動小数点数の絶対値を計算するために使用されます。
	//ここでは、EscapeRotDiff2 の絶対値が D3DX_PI を超えているかどうかを判定しています
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// 角度を範囲内に収める
	fRot.x = fmodf(fRot.x + D3DX_PI, 2 * D3DX_PI) - D3DX_PI;
	fRot.y = fmodf(fRot.y + D3DX_PI, 2 * D3DX_PI) - D3DX_PI;
	fRot.z = fmodf(fRot.z + D3DX_PI, 2 * D3DX_PI) - D3DX_PI;

	float rotDiff = fRot.x;
	float rotDiff2 = fRot.y;
	float rotDiff3 = fRot.z;

	//関数の外でで角度補正

	return D3DXVECTOR3(rotDiff, rotDiff2, rotDiff3);

}
//===================================
//Xfireよみこみ
//===================================
void LoadXfire_AdModel(int Index)//OFFセットでの情報からモデル読み込み
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < g_Model3[Index].nMaxLoadPartsCnt; nCnt++)
	{
		//ファイルの読み込み----------------------
		D3DXLoadMeshFromX(&g_cModelFileName[Index][nCnt][0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatModel_AD[Index][nCnt],
			NULL,
			&dwNumMatModel_AD[Index][nCnt],
			&g_pMeshModel_AD[Index][nCnt]);

		//D3DXMATERIAL* pMat;

		////マテリアルデータへのポインタを取得
		//pMat = (D3DXMATERIAL*)g_pBuffMatModel_AD[Index][nCnt]->GetBufferPointer();

		//for (int nCntMat = 0; nCntMat < (int)dwNumMatModel_AD[Index][nCnt]; nCntMat++)
		//{
		//	if (pMat[nCntMat].pTextureFilename != NULL)
		//	{
		//		//テクスチャの読み込み
		//		D3DXCreateTextureFromFile(pDevice,
		//			pMat[nCntMat].pTextureFilename,
		//			&g_apTextureModel_AD[Index][nCnt][nCntMat]
		//		);
		//	}
		//}


	}
}
//===================================
//テキストからキャラの情報を読み込む処理----------------------------------------------------------------
//===================================
void LoadSet3(int Index)
{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	FILE* pFile;//ファイルポインタを宣言


	char aString[MAX_WORD2_AD];	//読み込む最大文字数

	int nModelNum;//モデル
	nModelNum = 0;



	int nfirstEscapePartsCnt;//はじめに使うパーツカウント
	nfirstEscapePartsCnt = 0;

	int nMotionCnt;//モーションカウント
	nMotionCnt = 0;

	int KeyCnt;//キーカウント
	KeyCnt = 0;


	int nKeyPartsCnt;//各キーの中でのパーツカウント
	nKeyPartsCnt = 0;

	//char cModelFileName[MAX_PARTS_AD][MAX_WORD2_AD] = {};//とりあえず20でファイル名を管理

	pFile = fopen(g_ModelMotionInfo[Index].pFilePass, "r");

	if (pFile != NULL)
	{//ファイルが開いたら
		while (1)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "END_SCRIPT") == 0)
			{//最後にきたら
				fclose(pFile);
				break;
			}
			else if (strcmp(&aString[0], "NUM_MODEL") == 0)
			{//モデル数が来たら
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%d", &g_Model3[Index].nMaxLoadPartsCnt);//モデル数格納

			}
			else if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
			{//各モデルのパーツのパスが来たら
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%s", &g_cModelFileName[Index][nModelNum][0]);//ファイルパス



				////ファイルの読み込み----------------------
				//D3DXLoadMeshFromX(&g_cModelFileName[Index][nModelNum][0],
				//	D3DXMESH_SYSTEMMEM,
				//	pDevice,
				//	NULL,
				//	&g_pBuffMatModel_AD[Index][g_nEscapeCntModel[Index]],
				//	NULL,
				//	&dwNumMatModel_AD[Index][g_nEscapeCntModel[Index]],
				//	&g_pMeshModel_AD[Index][g_nEscapeCntModel[Index]]);

				//D3DXMATERIAL* pMat;

				////マテリアルデータへのポインタを取得
				//pMat = (D3DXMATERIAL*)g_pBuffMatModel_AD[Index][g_nEscapeCntModel[Index]]->GetBufferPointer();

				//for (int nCntMat = 0; nCntMat < (int)dwNumMatModel_AD[Index][g_nEscapeCntModel[Index]]; nCntMat++)
				//{
				//	if (pMat[nCntMat].pTextureFilename != NULL)
				//	{
				//		//テクスチャの読み込み
				//		D3DXCreateTextureFromFile(pDevice,
				//			pMat[nCntMat].pTextureFilename,
				//			&g_apTextureModel_AD[Index][nCntMat]
				//		);
				//	}
				//}

				nModelNum++;
			}
			else if (strcmp(&aString[0], "CHARACTERSET") == 0)
			{//キャラセットがきたら
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "END_CHARACTERSET") == 0)
					{
						//nCnt++;
						break;
					}
					else if (strcmp(&aString[0], "NUM_PARTS") == 0)
					{//Parts数が来たら
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &g_Model3[Index].nMaxPartsCnt);


					}
					else if (strcmp(&aString[0], "PARTSSET") == 0)
					{//Parts設定が来たら
						while (1)
						{
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "END_PARTSSET") == 0)
							{//Parts数エンドが来たら

								nfirstEscapePartsCnt++;
								break;
							}
							else if (strcmp(&aString[0], "INDEX") == 0)
							{//インデックスが来たら
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &g_Model3[Index].ModelParts[nfirstEscapePartsCnt].INDEX);

							}
							else if (strcmp(&aString[0], "PARENT") == 0)
							{//親が来たら
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &g_Model3[Index].ModelParts[nfirstEscapePartsCnt].PEARENT);
							}
							else if (strcmp(&aString[0], "POS") == 0)
							{//POSが来たら
								fscanf(pFile, "%s", &aString[0]);

								fscanf(pFile, "%f %f %f", &g_Model3[Index].ModelParts[nfirstEscapePartsCnt].Pos.x, &g_Model3[Index].ModelParts[nfirstEscapePartsCnt].Pos.y, &g_Model3[Index].ModelParts[nfirstEscapePartsCnt].Pos.z);

								//保存
								g_Model3[Index].ModelParts[nfirstEscapePartsCnt].StartPos = g_Model3[Index].ModelParts[nfirstEscapePartsCnt].Pos;

							}
							else if (strcmp(&aString[0], "ROT") == 0)
							{//ROTが来たら
								fscanf(pFile, "%s", &aString[0]);

								fscanf(pFile, "%f %f %f", &g_Model3[Index].ModelParts[nfirstEscapePartsCnt].Rot.x, &g_Model3[Index].ModelParts[nfirstEscapePartsCnt].Rot.y, &g_Model3[Index].ModelParts[nfirstEscapePartsCnt].Rot.z);

								//保存
								g_Model3[Index].ModelParts[nfirstEscapePartsCnt].StartRot = g_Model3[Index].ModelParts[nfirstEscapePartsCnt].Rot;
							}
						}

					}
				}
			}
			else if (strcmp(&aString[0], "MOTIONSET") == 0)
			{//MOTIONセットが来たら
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "END_MOTIONSET") == 0)
					{//エンドMOTIONセット

						g_Model3[Index].Motion[nMotionCnt].Motiontype = nMotionCnt;
						nMotionCnt++;//モーションインクリメント

						if (g_Model3[Index].nMaxMotionCnt <= nMotionCnt)
						{
							g_Model3[Index].nMaxMotionCnt = nMotionCnt;//モーション数は最大のみ
						}

						KeyCnt = 0;//キー番号リセット

						break;
					}
					else if (strcmp(&aString[0], "LOOP") == 0)
					{//ループ数が来たら
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &g_Model3[Index].Motion[nMotionCnt].nLoop);
					}
					else if (strcmp(&aString[0], "NUM_KEY") == 0)//----------------最大キー数に応用
					{//キーの数が来たら
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &g_Model3[Index].Motion[nMotionCnt].nNumKey);
					}
					else if (strcmp(&aString[0], "KEYSET") == 0)
					{//KEYセットが来たら
						while (1)
						{
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "END_KEYSET") == 0)
							{//エンドKEYセット

								KeyCnt++;//キーインクリメント
								nKeyPartsCnt = 0;//パーツ番号もリセット
								break;

							}
							else if (strcmp(&aString[0], "FRAME") == 0)
							{//フレームの数が来たら
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &g_Model3[Index].Motion[nMotionCnt].KeyData[KeyCnt].nSplitFrame);//-----------------------------------下記と同じ//わけないと、飛ばされたときに認識できない

							}
							else if (strcmp(&aString[0], "KEY") == 0)
							{//KEYが来たら

								while (1)
								{
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "FRAME") == 0)
									{//フレームの数が来たら
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%d", &g_Model3[Index].Motion[nMotionCnt].KeyData[KeyCnt].nSplitFrame);///------------------------上記と同じ

									}

									else if (strcmp(&aString[0], "END_KEY") == 0)
									{//エンドKEY

										nKeyPartsCnt++;//パーツインクリメント
										break;
									}
									else if (strcmp(&aString[0], "POS") == 0)
									{//POS数が来たら
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%f %f %f", &g_Model3[Index].Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.x, &g_Model3[Index].Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.y, &g_Model3[Index].Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.z);///------------------------Keyごとかつパーツごとで変動

									}
									else if (strcmp(&aString[0], "ROT") == 0)
									{//ROT数が来たら
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%f %f %f", &g_Model3[Index].Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.x, &g_Model3[Index].Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.y, &g_Model3[Index].Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.z);///------------------------Keyごとかつパーツごとで変動
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
//-----------------------------------------------------------モーション後にCPP化ける...かも
//===================================
//下半身モーション//腰
//===================================
void LowerBodyMotion3(int Index)
{
	if (g_AdvancedModel[Index].NowMotionDOWN != g_AdvancedModel[Index].OldMotionDOWN)
	{//前回のモーションと違う時
	//-------------------------------リセット動作

		g_AdvancedModel[Index].NowKeyCntDOWN = 0;
		g_AdvancedModel[Index].NowFrameCntDOWN = 0;
		g_AdvancedModel[Index].EscapeMotion = g_AdvancedModel[Index].NowMotionDOWN;
		g_AdvancedModel[Index].BrendCnt = 0;
		for (int i = 0; i < MAX_PARTS_AD; i++)
		{//リセット

			g_Model3[Index].ModelParts[i].calculationExecution = false;
			g_Model3[Index].ModelParts[i].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model3[Index].ModelParts[i].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_AdvancedModel[Index].MotionLoopStop = false;



		}
		g_AdvancedModel[Index].MotionBrend = true;
	}




	if (g_AdvancedModel[Index].MotionBrend == true)
	{//モーションブレンド--無し


#if 0
		for (int nCntParts = 0; nCntParts < g_Model3[Index].nMaxPartsCnt; nCntParts++)
		{//パーツ分回る

				//ROT系
			if (g_Model3[Index].ModelParts[nCntParts].calculationExecution == false)
			{
				//CorrectionPos,CorrectionRotはあくまで、OFFSETをStart地点とした補正量なので、
				D3DXVECTOR3 TargetRot;
				TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				TargetRot = g_Model3[Index].ModelParts[nCntParts].StartRot + g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionRot;

				g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionAdvancedModelRot3(TargetRot - g_Model3[Index].ModelParts[nCntParts].Rot, 0));

				g_Model3[Index].ModelParts[nCntParts].calculationExecution = true;
			}

			g_Model3[Index].ModelParts[nCntParts].Rot += g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionRotMove;

			//POS系
			//--------------------------------------------------------------------------------
			if (g_Model3[Index].ModelParts[nCntParts].PEARENT == -1)
			{//自分がすべての親の時
				D3DXVECTOR3 TargetPos;
				TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				//初期位置から見た地点を補正した、目標地点の算出
				TargetPos = g_Model3[Index].ModelParts[nCntParts].StartPos + g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionPos;

				//現在の位置から、上で算出した目標地点までの差分計算
				g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Model3[Index].ModelParts[nCntParts].Pos);

				//POSの更新
				g_Model3[Index].ModelParts[nCntParts].Pos += g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionPosMove;
				//------------------------------------------------------------------------------------
			}
		}

		g_AdvancedModel[Index].MotionBrend = false;

		g_AdvancedModel[Index].NowKeyCntDOWN++;//キーを進める

		for (int nCntParts = 0; nCntParts < g_Model3[Index].nMaxPartsCnt; nCntParts++)
		{//パーツ分回る
			g_Model3[Index].ModelParts[nCntParts].calculationExecution = false;
			g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		}


#else // 1

		if (g_AdvancedModel[Index].BrendCnt < BRENDFLAME_AD)
		{
			for (int nCntParts = 0; nCntParts < g_Model3[Index].nMaxPartsCnt; nCntParts++)
			{//パーツ分回る

					//ROT系
				if (g_Model3[Index].ModelParts[nCntParts].calculationExecution == false)
				{
					//CorrectionPos,CorrectionRotはあくまで、OFFSETをStart地点とした補正量なので、
					D3DXVECTOR3 TargetRot;
					TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					TargetRot = g_Model3[Index].ModelParts[nCntParts].StartRot + g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionRot;

					g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionAdvancedModelRot3(TargetRot - g_Model3[Index].ModelParts[nCntParts].Rot, 0) / BRENDFLAME_AD);

					g_Model3[Index].ModelParts[nCntParts].calculationExecution = true;
				}

				g_Model3[Index].ModelParts[nCntParts].Rot += g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionRotMove;

				//POS系
				//--------------------------------------------------------------------------------
				if (g_Model3[Index].ModelParts[nCntParts].PEARENT == -1)
				{//自分がすべての親の時
					D3DXVECTOR3 TargetPos;
					TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					//初期位置から見た地点を補正した、目標地点の算出
					TargetPos = g_Model3[Index].ModelParts[nCntParts].StartPos + g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionPos;

					//現在の位置から、上で算出した目標地点までの差分計算
					g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Model3[Index].ModelParts[nCntParts].Pos) / BRENDFLAME_AD;

					//POSの更新
					g_Model3[Index].ModelParts[nCntParts].Pos += g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionPosMove;
					//------------------------------------------------------------------------------------
				}
			}

		}
		g_AdvancedModel[Index].BrendCnt++;

		if (g_AdvancedModel[Index].BrendCnt >= BRENDFLAME_AD)
		{
			g_AdvancedModel[Index].BrendCnt = 0;

			g_AdvancedModel[Index].MotionBrend = false;

			g_AdvancedModel[Index].NowKeyCntDOWN++;//キーを進める

			for (int nCntParts = 0; nCntParts < g_Model3[Index].nMaxPartsCnt; nCntParts++)
			{//パーツ分回る
				g_Model3[Index].ModelParts[nCntParts].calculationExecution = false;
				g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			}
		}
#endif



	}
	else
	{


		// 本動作------------------------------------------------------------------------------------------------------------------
		if (g_AdvancedModel[Index].MotionLoopStop == false)
		{
			if (g_AdvancedModel[Index].NowFrameCntDOWN < g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[g_AdvancedModel[Index].NowKeyCntDOWN /*- 1*/].nSplitFrame)
			{//分割フレームの分回る
				if (g_AdvancedModel[Index].NowKeyCntDOWN < g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].nNumKey)
				{//キーの分回る

					for (int nCntParts = 0; nCntParts < g_Model3[Index].nMaxPartsCnt; nCntParts++)
					{//パーツ分回る
					//	if (nCntParts == 0 || (nCntParts >= 9 && nCntParts <= 14))
					//	{
							//ROT系
						if (g_Model3[Index].ModelParts[nCntParts].calculationExecution == false)
						{
							//CorrectionPos,CorrectionRotはあくまで、OFFSETをStart地点とした補正量なので、
							D3DXVECTOR3 TargetRot;
							TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

							if (g_AdvancedModel[Index].NowKeyCntDOWN != g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].nNumKey - 1)
							{//最後キーじゃない
								TargetRot = g_Model3[Index].ModelParts[nCntParts].StartRot + g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[g_AdvancedModel[Index].NowKeyCntDOWN + 1].PartsData[nCntParts].CorrectionRot;
							}
							else if (g_AdvancedModel[Index].NowKeyCntDOWN == g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].nNumKey - 1)
							{//最後キーのとき
								TargetRot = g_Model3[Index].ModelParts[nCntParts].StartRot + g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionRot;
							}
							g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionAdvancedModelRot3(TargetRot - g_Model3[Index].ModelParts[nCntParts].Rot, 0)) / g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[g_AdvancedModel[Index].NowKeyCntDOWN].nSplitFrame;

							g_Model3[Index].ModelParts[nCntParts].calculationExecution = true;
						}

						g_Model3[Index].ModelParts[nCntParts].Rot += g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionRotMove;

						//POS系
						//--------------------------------------------------------------------------------
						if (g_Model3[Index].ModelParts[nCntParts].PEARENT == -1)
						{//自分がすべての親の時
							D3DXVECTOR3 TargetPos;
							TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
							if (g_AdvancedModel[Index].NowKeyCntDOWN != g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].nNumKey - 1)
							{//最後キーじゃない
							//初期位置から見た地点を補正した、目標地点の算出
								TargetPos = g_Model3[Index].ModelParts[nCntParts].StartPos + g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[g_AdvancedModel[Index].NowKeyCntDOWN + 1].PartsData[nCntParts].CorrectionPos;
							}
							else if (g_AdvancedModel[Index].NowKeyCntDOWN == g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].nNumKey - 1)
							{//最後キーのとき
							//初期位置から見た地点を補正した、目標地点の算出
								TargetPos = g_Model3[Index].ModelParts[nCntParts].StartPos + g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionPos;
							}
							//現在の位置から、上で算出した目標地点までの差分計算
							g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Model3[Index].ModelParts[nCntParts].Pos) / g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[g_AdvancedModel[Index].NowKeyCntDOWN].nSplitFrame;

							//POSの更新
							g_Model3[Index].ModelParts[nCntParts].Pos += g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionPosMove;
							//------------------------------------------------------------------------------------
						}
						//	}
					}
				}
				g_AdvancedModel[Index].NowFrameCntDOWN++;//フレーム進める
			}
			else
			{//フレーム数超えた
				g_AdvancedModel[Index].NowFrameCntDOWN = 0;//フレームリセット

				g_AdvancedModel[Index].NowKeyCntDOWN++;//キーを進める

				for (int i = 0; i < MAX_PARTS_AD; i++)
				{//リセット
					g_Model3[Index].ModelParts[i].calculationExecution = false;
				}

				if (g_AdvancedModel[Index].NowKeyCntDOWN == g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].nNumKey)
				{//キーが、最大キーを超えた時

					g_AdvancedModel[Index].NowFrameCntDOWN = 0;//フレームリセット
					g_AdvancedModel[Index].NowKeyCntDOWN = 0;//キーリセット

					if (g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].nLoop == 0)
					{//ループしない
						if (g_AdvancedModel[Index].NowMotionDOWN == MOTIONTYPE_AD_JUMP)
						{
							g_AdvancedModel[Index].MotionLoopStop = true;
						}
						else
						{//飛翔以外
							//待機にする
							g_AdvancedModel[Index].NowMotionDOWN = MOTIONTYPE_AD_STANDBY;//待機状態に戻す
							//ブレンド挟む
							if (g_AdvancedModel[Index].MotionBrend == false)
							{
								g_AdvancedModel[Index].NowKeyCntDOWN = 0;
								g_AdvancedModel[Index].NowFrameCntDOWN = 0;
								g_AdvancedModel[Index].EscapeMotion = g_AdvancedModel[Index].NowMotionDOWN;
								g_AdvancedModel[Index].BrendCnt = 0;
								for (int i = 0; i < MAX_PARTS_AD; i++)
								{//リセット

									g_Model3[Index].ModelParts[i].calculationExecution = false;
									g_Model3[Index].ModelParts[i].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
									g_Model3[Index].ModelParts[i].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
									g_AdvancedModel[Index].MotionLoopStop = false;

									g_AdvancedModel[Index].MotionBrend = true;

								}
							}
						}
					}
					else
					{//ループ

					}

				}
			}
		}
	}

}


//===================================
//モデル取得処理
//===================================
MODEL_AD* GetAdModel(int Index)
{
	return &g_Model3[Index];
}


//===================================
//セット
//===================================
void SetModel_AD(MODELADTYPE ModelName, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{

	g_AdvancedModel[ModelName].pos = pos;	//位置
	g_AdvancedModel[ModelName].rot = rot;	//向き
	g_AdvancedModel[ModelName].bUse = true;

	LoadSet3(ModelName);//---------------------------------------------------------こいつがロード

}
