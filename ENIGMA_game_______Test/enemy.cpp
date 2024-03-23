//=========================================================
//
// 敵の処理[enemy.cpp]
// Author seiya kagaya
//
//=========================================================
#include "enemy.h"
#include "stage.h"
#include "player.h"
#include "player2.h"
#include "particle.h"
#include "result.h"
#include "hitcollision_mistake_prevention.h"
#include "model.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "eyetrap.h"
#include "enemy_view.h"
#include <stdio.h>//ヘッダーファイルをインクルード
#include <string.h>//文字列を扱う変数
#include "game.h"


//=========================================================
//グローバル変数
//=========================================================
ENEMYMODEL g_Enemy;//プレイヤー全体

///-------------------------------------------------------------------------モデル
LPD3DXMESH g_pMeshModel_Enemy[MAX_PARTS_ENEMY] = {};//メッシュ(頂点情報)へのポインタ

LPD3DXBUFFER g_pBuffMatModel_Enemy[MAX_PARTS_ENEMY] = {};//マテリアルへのポインタ

DWORD dwNumMatModel_Enemy[MAX_PARTS_ENEMY] = {};//マテリアルの数

LPDIRECT3DTEXTURE9 g_apTextureModel_Enemy[NUM_TEXTURE_ENEMY] = {}; //テクスチャポインタ

MODEL_ENEMY g_Enemy3;//モデル全体
//--------------------------------------------------------------------------

//=============================
//エネミー初期化処理
//=============================
void InitEnemy(void)
{
	//g_ENEMYvancedModel.NowMotionUP = MOTIONTYPE_ENEMY_MAX;
	g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_MAX;

	g_Enemy.OldMotionDOWN = MOTIONTYPE_ENEMY_MAX;

	g_Enemy.pos = D3DXVECTOR3(-50.0f, 0.0f, -500.0f);	//位置
	g_Enemy.MinPos = D3DXVECTOR3(g_Enemy.pos + ENEMYMIN);	//位置
	g_Enemy.MaxPos = D3DXVECTOR3(g_Enemy.pos + ENEMYMAX);	//位置

	g_Enemy.oldPos = g_Enemy.pos;	//過去の位置

	g_Enemy.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き

	g_Enemy.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//歩行スピード

	g_Enemy.ActionPattern = ACTIONPATTERN_ENEMY_WALK;

	ActionEnemy(g_Enemy.ActionPattern, -1);

	g_Enemy.rotmove = 0.0f;

	g_Enemy.PARENT = -1;//親子関係

	g_Enemy.nPlayerIdx = -1;

	g_Enemy.JumpFrame = 0;

	g_Enemy.bUse = false;;
	g_Enemy.JumpNow = false;
	g_Enemy.JumpOld = false;

	g_Enemy.NowFrameCntDOWN = 0;
	g_Enemy.NowKeyCntDOWN = 0;

	g_Enemy.NowFrameCntUP = 0;
	g_Enemy.NowKeyCntUP = 0;
	g_Enemy.MotionLoopStop = false;
	g_Enemy.MotionBrend = false;

	g_Enemy.BrendCnt = 0;
	g_Enemy.EscapeMotion = MOTIONTYPE_ENEMY_BREND;

	//-------------------------------------------------モデル系
	g_Enemy3.nMaxMotionCnt = 0;
	g_Enemy3.nMaxPartsCnt = 0;
	g_Enemy3.nMaxLoadPartsCnt = 0;

	for (int nCntParts = 0; nCntParts < MAX_PARTS_ENEMY; nCntParts++)//各パーツ本体
	{
		g_Enemy3.ModelParts[nCntParts].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy3.ModelParts[nCntParts].Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Enemy3.ModelParts[nCntParts].StartPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy3.ModelParts[nCntParts].StartRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Enemy3.ModelParts[nCntParts].PEARENT = 0;
		g_Enemy3.ModelParts[nCntParts].INDEX = 0;

		g_Enemy3.ModelParts[nCntParts].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy3.ModelParts[nCntParts].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Enemy3.ModelParts[nCntParts].calculationExecution = false;
	}
	for (int nMotionCnt = 0; nMotionCnt < MAX_MONITORS; nMotionCnt++)//各モーションデータ
	{
		g_Enemy3.Motion[nMotionCnt].nNumKey = 0;
		g_Enemy3.Motion[nMotionCnt].nLoop = 0;
		g_Enemy3.Motion[nMotionCnt].Motiontype = MOTIONTYPE_ENEMY_MAX;


		for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)//各モーション中の各パーツの各キー内のデータ
		{
			g_Enemy3.Motion[nMotionCnt].KeyData[nCntKey].nSplitFrame = 0;

			for (int nCntParts = 0; nCntParts < MAX_PARTS_ENEMY; nCntParts++)//各モーション中の各パーツデータ
			{
				g_Enemy3.Motion[nMotionCnt].KeyData[nCntKey].PartsData[nCntParts].CorrectionPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Enemy3.Motion[nMotionCnt].KeyData[nCntKey].PartsData[nCntParts].CorrectionRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}

	//ここでセット
	SetModel_Enemy(D3DXVECTOR3(-50.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
}

//=============================
//エネミー終了処理
//=============================
void UninitEnemy(void)
{
	for (int nCntModel = 0; nCntModel < MAX_PARTS_ENEMY; nCntModel++)
	{
		//メッシュの破棄
		if (g_pMeshModel_Enemy[nCntModel] != NULL)
		{
			g_pMeshModel_Enemy[nCntModel]->Release();
			g_pMeshModel_Enemy[nCntModel] = NULL;
		}
		//マテリアルの破棄
		if (g_pBuffMatModel_Enemy[nCntModel] != NULL)
		{
			g_pBuffMatModel_Enemy[nCntModel]->Release();
			g_pBuffMatModel_Enemy[nCntModel] = NULL;
		}
	}
	for (int nNumTex = 0; nNumTex < NUM_TEXTURE_ENEMY; nNumTex++)
	{
		if (g_apTextureModel_Enemy[nNumTex] != NULL)
		{
			g_apTextureModel_Enemy[nNumTex]->Release();
			g_apTextureModel_Enemy[nNumTex] = NULL;
		}
	}
}

//=============================
//エネミー更新処理
//=============================
void UpdateEnemy(void)
{
	if (g_Enemy.bUse == true)
	{
		D3DXMATRIX mtxRot, mtxTrans, mtxParent;//計算用マトリックス	


		//	//とりあえず待機
		//g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_STANDBY;

		//int Random = ((float)rand() / RAND_MAX) * 2;
		//if (Random == 0)
		//{
		//	g_Enemy.move = D3DXVECTOR3(-5.0f, 0.0f, 0.0f);
		//}
		//else if (Random == 1)
		//{
		//	g_Enemy.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//}


		//古いposを代入
		g_Enemy.oldPos = g_Enemy.pos;

		if (g_Enemy.ActionPattern == ACTIONPATTERN_ENEMY_CHASE)
		{
			if (g_Enemy.nPlayerIdx == 0)
			{
				Player* pPlayer = GetPlayer();
				float PlayerLength_x = pPlayer->pos.x - g_Enemy.pos.x; //プレイヤーとの距離計算
				float PlayerLength_z = pPlayer->pos.z - g_Enemy.pos.z; //プレイヤーとの距離計算
				float fLength = sqrtf(PlayerLength_x * PlayerLength_x + PlayerLength_z * PlayerLength_z);
				if (fLength > 800.0f)
				{
					//振動ストップ
					for (int nCnt = 0; nCnt < 2; nCnt++)
					{
						VibrationLeft(0, nCnt);
						VibrationRight(0, nCnt);
					}
					ActionEnemy(ACTIONPATTERN_ENEMY_WALK, -1);
				}
				if (fLength < 30.0f)
				{
					SetEyeTrap(g_Enemy.nPlayerIdx);
					//SetFade(MODE_RESULT);
				}
				float fAngle = atan2f(PlayerLength_x, PlayerLength_z);
				g_Enemy.rot.y = (fAngle - (1.0f * D3DX_PI));
				g_Enemy.move.x += sinf(fAngle) * 0.08f;
				g_Enemy.move.z += cosf(fAngle) * 0.08f;
			}
			if (g_Enemy.nPlayerIdx == 1)
			{
				Player_2P* pPlayer_2P = GetPlayer_2P();
				//プレイヤー追従処理
				float PlayerLength_x = pPlayer_2P->pos.x - g_Enemy.pos.x; //プレイヤーとの距離計算
				float PlayerLength_z = pPlayer_2P->pos.z - g_Enemy.pos.z; //プレイヤーとの距離計算
				float fLength = sqrtf(PlayerLength_x * PlayerLength_x + PlayerLength_z * PlayerLength_z);
				if (fLength > 800.0f)
				{
					VibrationLeft(0, g_Enemy.nPlayerIdx);
					VibrationRight(0, g_Enemy.nPlayerIdx);
					ActionEnemy(ACTIONPATTERN_ENEMY_WALK, -1);
				}
				if (fLength < 30.0f)
				{
					SetEyeTrap(g_Enemy.nPlayerIdx);
					//SetFade(MODE_GAMEOVER);
				}
				float fAngle = atan2f(PlayerLength_x, PlayerLength_z);
				g_Enemy.rot.y = (fAngle - (1.0f * D3DX_PI));
				g_Enemy.move.x += sinf(fAngle) * 0.08f;
				g_Enemy.move.z += cosf(fAngle) * 0.08f;
			}

		}
		//位置を更新
		g_Enemy.pos += g_Enemy.move;

		//if (g_Enemy.move != D3DXVECTOR3(0.0f,0.0f,0.0f))
		//{
		//	g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_MOVE;
		//}
		//else if (g_Enemy.move == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		//{
		//	g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_MOVE;
		//}
		//上下のモーション
		LowerBodyEnemy3();
		//	UpperBodyMotion();

		//前回のモーションデータを更新
		//g_Enemy.OldMotionUP = g_Enemy.NowMotionUP;
		g_Enemy.OldMotionDOWN = g_Enemy.NowMotionDOWN;


		//----------パーツ
		for (int nCnt = 0; nCnt < g_Enemy3.nMaxPartsCnt; nCnt++)
		{//パーツ分回す
			//モデルの位置
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy3.ModelParts[nCnt].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy3.ModelParts[nCnt].Rot.y, g_Enemy3.ModelParts[nCnt].Rot.x, g_Enemy3.ModelParts[nCnt].Rot.z);

			D3DXMatrixMultiply(&g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Enemy3.ModelParts[nCnt].Pos.x, g_Enemy3.ModelParts[nCnt].Pos.y, g_Enemy3.ModelParts[nCnt].Pos.z);

			D3DXMatrixMultiply(&g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[nCnt].mtxWorld, &mtxTrans);

			//親子関係
			if (g_Enemy3.ModelParts[nCnt].PEARENT == -1)
			{
				//プレイヤーとかける
				D3DXMatrixMultiply(&g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy.mtxWorld);
			}
			else
			{
				//自分の親のマトリックス欠けてる
				D3DXMatrixMultiply(&g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[g_Enemy3.ModelParts[nCnt].PEARENT].mtxWorld);

			}
		}

		//--------------------------------------------------------------------------------------------------------------------------------------------------//当たり判定ここから
		//プレイヤーのサイズ
		g_Enemy.MinPos = D3DXVECTOR3(g_Enemy.pos + ENEMYMIN);
		g_Enemy.MaxPos = D3DXVECTOR3(g_Enemy.pos + ENEMYMAX);

		MAPOBJECT* pMapObject;
		pMapObject = GetMapObject();

		for (int i = 0; i < MAX_MODEL; i++)
		{
			if (pMapObject[i].bUse == true)
			{
				if (pMapObject[i].bCollision == true)
				{
					D3DXVECTOR3 ModelMin = D3DXVECTOR3(pMapObject[i].pos + pMapObject[i].Minpos);
					D3DXVECTOR3 ModelMax = D3DXVECTOR3(pMapObject[i].pos + pMapObject[i].Maxpos);

					//判定
					BoxCollisionEnemy(g_Enemy.MinPos, g_Enemy.MaxPos, ModelMin, ModelMax);
				}
			}
		}

		//----------------------------------------------------------------------------壁、床接触
		STAGE* pStage;
		pStage = GetStage();
		for (int nWall = 0; nWall < NUMSTAGE; nWall++)
		{
			if (pStage[nWall].bUse == true)
			{
				if (pStage[nWall].bCollision == true)
				{
					D3DXVECTOR3 StageMin = D3DXVECTOR3(pStage[nWall].posStage + pStage[nWall].MinPos);
					D3DXVECTOR3 StageMax = D3DXVECTOR3(pStage[nWall].posStage + pStage[nWall].MaxPos);

					//プレイヤー同士当たり判定
					BoxCollisionEnemy(g_Enemy.MinPos, g_Enemy.MaxPos, StageMin, StageMax);
				}
			}
		}

		//当たり判定抜け防止/-----------------------------------------------------------------------------------------------------------------------------------------
		COLLISION_PRE* pColisionPre;
		pColisionPre = GetCollision_Pre();

		for (int i = 0; i < MAXCOLLISION_PRE; i++)
		{
			if (pColisionPre[i].bUse == true)
			{

				D3DXVECTOR3 ColisionPreMin = D3DXVECTOR3(pColisionPre[i].pos + pColisionPre[i].Min);
				D3DXVECTOR3 ColisionPreMax = D3DXVECTOR3(pColisionPre[i].pos + pColisionPre[i].Max);

				//プレイヤー同士当たり判定
				BoxCollisionEnemy(g_Enemy.MinPos, g_Enemy.MaxPos, ColisionPreMin, ColisionPreMax);

			}
		}
	}
}

//===================================
//エネミー行動処理
//===================================
void ActionEnemy(ACTIONPATTERN_ENEMY ActionPattern, int PlayerIdx)
{
	g_Enemy.ActionPattern = ActionPattern;
	g_Enemy.nPlayerIdx = PlayerIdx;

	if (ActionPattern == ACTIONPATTERN_ENEMY_STANDBY)
	{//静止状態
		g_Enemy.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_STANDBY;
	}
	else if (ActionPattern == ACTIONPATTERN_ENEMY_WALK)
	{
		int nTurn = ((float)rand() / RAND_MAX) * 4;
		int nMoveX = MAX_ENEMY_SPEED;
		int nMoveZ = MAX_ENEMY_SPEED;
		if (nTurn == 0)
		{
			nMoveX *= -1;
		}
		if (nTurn == 1)
		{
			nMoveZ *= -1;
		}
		if (nTurn == 2)
		{
			nMoveX *= -1;
			nMoveZ *= -1;
		}

		float Angle = atan2f((float)nMoveX, (float)nMoveZ);//方角
		g_Enemy.rot.y = (Angle - (1.0f * D3DX_PI));

		g_Enemy.move = D3DXVECTOR3((float)nMoveX, 0.0f, (float)nMoveZ);
		g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_MOVE;

	}
	else if (ActionPattern == ACTIONPATTERN_ENEMY_SPAWN)
	{
		g_Enemy.pos += g_Enemy.move;
		g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_MOVE;
	}
	else if (ActionPattern == ACTIONPATTERN_ENEMY_CHASE)
	{
		if (PlayerIdx == 0)
		{
			Player* pPlayer = GetPlayer();
			float PlayerLength_x = pPlayer->pos.x - g_Enemy.pos.x; //プレイヤーとの距離計算
			float PlayerLength_z = pPlayer->pos.z - g_Enemy.pos.z; //プレイヤーとの距離計算
		//	float fLength = sqrtf(PlayerLength_x * PlayerLength_x + PlayerLength_z * PlayerLength_z);
			float fAngle = atan2f(PlayerLength_x, PlayerLength_z);
			g_Enemy.rot.y = (fAngle - (1.0f * D3DX_PI));
			g_Enemy.move.x += sinf(fAngle) * 0.09f;
			g_Enemy.move.z += cosf(fAngle) * 0.09f;
			VibrationLeft(0, 1);
			VibrationRight(0, 1);
			VibrationLeft(25535, 0);
			VibrationRight(25535, 0);
		}
		if (PlayerIdx == 1)
		{
			Player_2P* pPlayer_2P = GetPlayer_2P();
			//プレイヤー追従処理
			float PlayerLength_x = pPlayer_2P->pos.x - g_Enemy.pos.x; //プレイヤーとの距離計算
			float PlayerLength_z = pPlayer_2P->pos.z - g_Enemy.pos.z; //プレイヤーとの距離計算
		//	float fLength = sqrtf(PlayerLength_x * PlayerLength_x + PlayerLength_z * PlayerLength_z);
			float fAngle = atan2f(PlayerLength_x, PlayerLength_z);
			g_Enemy.rot.y = (fAngle - (1.0f * D3DX_PI));
			g_Enemy.move.x += sinf(fAngle) * 0.05f;
			g_Enemy.move.z += cosf(fAngle) * 0.05f;
			VibrationLeft(0, 0);
			VibrationRight(0, 0);
			VibrationLeft(25535, 1);
			VibrationRight(25535, 1);
		}


		g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_MOVE;
	}
	LowerBodyEnemy3();

}

//=============================
//エネミー描画処理
//=============================
void DrawEnemy(void)
{
	if (g_Enemy.bUse == true)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXMATRIX mtxRot, mtxTrans, mtxParent;//計算用マトリックス

		D3DMATERIAL9 matDef;//現在のマテリアル保存用(一時退避)

		D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

		//キャラ全体の基準(親の親)
			//---------------------------------------------------------------------------------------------------プレイヤーの位置のみ
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Enemy.mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy.rot.y, g_Enemy.rot.x, g_Enemy.rot.z);

		D3DXMatrixMultiply(&g_Enemy.mtxWorld, &g_Enemy.mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Enemy.pos.x, g_Enemy.pos.y, g_Enemy.pos.z);

		D3DXMatrixMultiply(&g_Enemy.mtxWorld, &g_Enemy.mtxWorld, &mtxTrans);



		for (int nCnt = 0; nCnt < g_Enemy3.nMaxPartsCnt; nCnt++)
		{
			//---------------------------------------------------------------------------------------------------モデルの位置

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy3.ModelParts[nCnt].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy3.ModelParts[nCnt].Rot.y, g_Enemy3.ModelParts[nCnt].Rot.x, g_Enemy3.ModelParts[nCnt].Rot.z);

			D3DXMatrixMultiply(&g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Enemy3.ModelParts[nCnt].Pos.x, g_Enemy3.ModelParts[nCnt].Pos.y, g_Enemy3.ModelParts[nCnt].Pos.z);

			D3DXMatrixMultiply(&g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[nCnt].mtxWorld, &mtxTrans);


			//親子関係
			if (g_Enemy3.ModelParts[nCnt].PEARENT == -1)
			{
				//プレイヤーとかける
				D3DXMatrixMultiply(&g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy.mtxWorld);
			}
			else
			{
				//自分の親のマトリックス欠けてる
				D3DXMatrixMultiply(&g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[g_Enemy3.ModelParts[nCnt].PEARENT].mtxWorld);
			}

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy3.ModelParts[nCnt].mtxWorld);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatModel_Enemy[nCnt]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)dwNumMatModel_Enemy[nCnt]; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, NULL);//今回は設定しない
				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureModel_Enemy[nCntMat]);

				//モデル(パーツ)の描画
				g_pMeshModel_Enemy[nCnt]->DrawSubset(nCntMat);

				//保存してたマテリアルを戻す
				pDevice->SetMaterial(&matDef);
			}
		}

	}
}

//=============================
//エネミー情報取得処理
//=============================
ENEMYMODEL* GetEnemy(void)
{
	return &g_Enemy;
}

//===================================
//モデル取得処理
//===================================
MODEL_ENEMY* GetEnemyModel(void)
{
	return &g_Enemy3;
}

//=============================
//エネミーメッシュ情報取得処理
//=============================
LPD3DXMESH* GetMesh_Enemy(void)
{
	return &g_pMeshModel_Enemy[0];
}

//=============================
//変換処理2D--------------------------めちゃ大事
//=============================
void ConversionEnemyRot2(float fRot, int nCnt)
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
	float rotDiff = fRot - g_Enemy.rot.y;

	// 差分が範囲外なら補正---------------------------------------------------------------近いうちちゃんと内容調べる
	if (fabsf(rotDiff) > D3DX_PI)
	{
		rotDiff = (rotDiff < 0) ? (rotDiff + 2 * D3DX_PI) : (rotDiff - 2 * D3DX_PI);
	}

	g_Enemy.rot.y += rotDiff * 0.1f;

	if (g_Enemy.rot.y > D3DX_PI)
	{
		g_Enemy.rot.y -= (2.0f * D3DX_PI);
	}
	else if (g_Enemy.rot.y < -D3DX_PI)
	{
		g_Enemy.rot.y += (2.0f * D3DX_PI);
	}
}

//=============================
//変換処理3D--------------------------めちゃ大事
//=============================
D3DXVECTOR3 ConversionEnemyRot3(D3DXVECTOR3 fRot, int nCnt)
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
//テキストからキャラの情報を読み込む処理----------------------------------------------------------------
//===================================
void LoadSetEnemy3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	FILE* pFile;//ファイルポインタを宣言


	char aString[MAX_WORD2_ENEMY];	//読み込む最大文字数

	int nModelNum;//モデル
	nModelNum = 0;

	int nEscapeCntModel;//モデル数
	nEscapeCntModel = 0;

	int nfirstEscapePartsCnt;//はじめに使うパーツカウント
	nfirstEscapePartsCnt = 0;

	int nMotionCnt;//モーションカウント
	nMotionCnt = 0;

	int KeyCnt;//キーカウント
	KeyCnt = 0;


	int nKeyPartsCnt;//各キーの中でのパーツカウント
	nKeyPartsCnt = 0;

	char cModelFileName[MAX_PARTS_ENEMY][MAX_WORD2_ENEMY] = {};//とりあえず20でファイル名を管理

	pFile = fopen(ENEMY_FILE_NAME, "r");

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
				fscanf(pFile, "%d", &g_Enemy3.nMaxLoadPartsCnt);//モデル数格納

			}
			else if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
			{//各モデルのパーツのパスが来たら
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%s", &cModelFileName[0]);//ファイルパス

				//ファイルの読み込み----------------------
				D3DXLoadMeshFromX(cModelFileName[0],
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel_Enemy[nEscapeCntModel],
					NULL,
					&dwNumMatModel_Enemy[nEscapeCntModel],
					&g_pMeshModel_Enemy[nEscapeCntModel]);

				D3DXMATERIAL* pMat;

				//マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_pBuffMatModel_Enemy[nEscapeCntModel]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)dwNumMatModel_Enemy[nEscapeCntModel]; nCntMat++)
				{
					if (pMat[nCntMat].pTextureFilename != NULL)
					{
						//テクスチャの読み込み
						D3DXCreateTextureFromFile(pDevice,
							pMat[nCntMat].pTextureFilename,
							&g_apTextureModel_Enemy[nCntMat]
						);
					}
				}

				//----------------------------------------

				nEscapeCntModel++;//モデル格納後インクリ

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
						fscanf(pFile, "%d", &g_Enemy3.nMaxPartsCnt);


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
								fscanf(pFile, "%d", &g_Enemy3.ModelParts[nfirstEscapePartsCnt].INDEX);

							}
							else if (strcmp(&aString[0], "PARENT") == 0)
							{//親が来たら
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &g_Enemy3.ModelParts[nfirstEscapePartsCnt].PEARENT);
							}
							else if (strcmp(&aString[0], "POS") == 0)
							{//POSが来たら
								fscanf(pFile, "%s", &aString[0]);

								fscanf(pFile, "%f %f %f", &g_Enemy3.ModelParts[nfirstEscapePartsCnt].Pos.x, &g_Enemy3.ModelParts[nfirstEscapePartsCnt].Pos.y, &g_Enemy3.ModelParts[nfirstEscapePartsCnt].Pos.z);

								//保存
								g_Enemy3.ModelParts[nfirstEscapePartsCnt].StartPos = g_Enemy3.ModelParts[nfirstEscapePartsCnt].Pos;

							}
							else if (strcmp(&aString[0], "ROT") == 0)
							{//ROTが来たら
								fscanf(pFile, "%s", &aString[0]);

								fscanf(pFile, "%f %f %f", &g_Enemy3.ModelParts[nfirstEscapePartsCnt].Rot.x, &g_Enemy3.ModelParts[nfirstEscapePartsCnt].Rot.y, &g_Enemy3.ModelParts[nfirstEscapePartsCnt].Rot.z);

								//保存
								g_Enemy3.ModelParts[nfirstEscapePartsCnt].StartRot = g_Enemy3.ModelParts[nfirstEscapePartsCnt].Rot;
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

						g_Enemy3.Motion[nMotionCnt].Motiontype = nMotionCnt;
						nMotionCnt++;//モーションインクリメント

						if (g_Enemy3.nMaxMotionCnt <= nMotionCnt)
						{
							g_Enemy3.nMaxMotionCnt = nMotionCnt;//モーション数は最大のみ
						}

						KeyCnt = 0;//キー番号リセット

						break;
					}
					else if (strcmp(&aString[0], "LOOP") == 0)
					{//ループ数が来たら
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &g_Enemy3.Motion[nMotionCnt].nLoop);
					}
					else if (strcmp(&aString[0], "NUM_KEY") == 0)//----------------最大キー数に応用
					{//キーの数が来たら
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &g_Enemy3.Motion[nMotionCnt].nNumKey);
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
								fscanf(pFile, "%d", &g_Enemy3.Motion[nMotionCnt].KeyData[KeyCnt].nSplitFrame);//-----------------------------------下記と同じ//わけないと、飛ばされたときに認識できない

							}
							else if (strcmp(&aString[0], "KEY") == 0)
							{//KEYが来たら

								while (1)
								{
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "FRAME") == 0)
									{//フレームの数が来たら
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%d", &g_Enemy3.Motion[nMotionCnt].KeyData[KeyCnt].nSplitFrame);///------------------------上記と同じ

									}

									else if (strcmp(&aString[0], "END_KEY") == 0)
									{//エンドKEY

										nKeyPartsCnt++;//パーツインクリメント
										break;
									}
									else if (strcmp(&aString[0], "POS") == 0)
									{//POS数が来たら
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%f %f %f", &g_Enemy3.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.x, &g_Enemy3.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.y, &g_Enemy3.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.z);///------------------------Keyごとかつパーツごとで変動

									}
									else if (strcmp(&aString[0], "ROT") == 0)
									{//ROT数が来たら
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%f %f %f", &g_Enemy3.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.x, &g_Enemy3.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.y, &g_Enemy3.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.z);///------------------------Keyごとかつパーツごとで変動
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

//===================================
//下半身モーション//腰
//===================================
void LowerBodyEnemy3(void)
{
	if (g_Enemy.NowMotionDOWN != g_Enemy.OldMotionDOWN)
	{//前回のモーションと違う時
	//-------------------------------リセット動作g
		if (g_Enemy.MotionBrend == false)
		{
			g_Enemy.NowKeyCntDOWN = 0;
			g_Enemy.NowFrameCntDOWN = 0;
			g_Enemy.EscapeMotion = g_Enemy.NowMotionDOWN;
			g_Enemy.BrendCnt = 0;
			for (int i = 0; i < MAX_PARTS_ENEMY; i++)
			{//リセット

				g_Enemy3.ModelParts[i].calculationExecution = false;
				g_Enemy3.ModelParts[i].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Enemy3.ModelParts[i].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Enemy.MotionLoopStop = false;

				g_Enemy.MotionBrend = true;

			}
		}
	}
	if (g_Enemy.MotionBrend == true)
	{//モーションブレンド--無し
		if (g_Enemy.BrendCnt < BRENDFLAME_ENEMY)
		{
			for (int nCntParts = 0; nCntParts < g_Enemy3.nMaxPartsCnt; nCntParts++)
			{//パーツ分回る

					//ROT系
				if (g_Enemy3.ModelParts[nCntParts].calculationExecution == false)
				{
					//CorrectionPos,CorrectionRotはあくまで、OFFSETをStart地点とした補正量なので、
					D3DXVECTOR3 TargetRot;
					TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					TargetRot = g_Enemy3.ModelParts[nCntParts].StartRot + g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionRot;

					g_Enemy3.ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionEnemyRot3(TargetRot - g_Enemy3.ModelParts[nCntParts].Rot, 0) / BRENDFLAME_ENEMY);

					g_Enemy3.ModelParts[nCntParts].calculationExecution = true;
				}

				g_Enemy3.ModelParts[nCntParts].Rot += g_Enemy3.ModelParts[nCntParts].CorrectCorrectionRotMove;

				//POS系
				//--------------------------------------------------------------------------------
				if (g_Enemy3.ModelParts[nCntParts].PEARENT == -1)
				{//自分がすべての親の時
					D3DXVECTOR3 TargetPos;
					TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					//初期位置から見た地点を補正した、目標地点の算出
					TargetPos = g_Enemy3.ModelParts[nCntParts].StartPos + g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionPos;

					//現在の位置から、上で算出した目標地点までの差分計算
					g_Enemy3.ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Enemy3.ModelParts[nCntParts].Pos) / BRENDFLAME_ENEMY;

					//POSの更新
					g_Enemy3.ModelParts[nCntParts].Pos += g_Enemy3.ModelParts[nCntParts].CorrectCorrectionPosMove;
					//------------------------------------------------------------------------------------
				}
			}

		}
		g_Enemy.BrendCnt++;

		if (g_Enemy.BrendCnt >= BRENDFLAME_ENEMY)
		{
			g_Enemy.BrendCnt = 0;

			g_Enemy.MotionBrend = false;

			g_Enemy.NowKeyCntDOWN++;//キーを進める

			for (int nCntParts = 0; nCntParts < g_Enemy3.nMaxPartsCnt; nCntParts++)
			{//パーツ分回る
				g_Enemy3.ModelParts[nCntParts].calculationExecution = false;
				g_Enemy3.ModelParts[nCntParts].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Enemy3.ModelParts[nCntParts].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			}
		}
	}
	else
	{

		// 本動作------------------------------------------------------------------------------------------------------------------
		if (g_Enemy.MotionLoopStop == false)
		{
			if (g_Enemy.NowKeyCntDOWN == 0)
			{//0番目のキー＝＝データズレで認識できない
				if (g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy.NowKeyCntDOWN - 1].nSplitFrame == 0)
				{//分割フレーム数が0＝＝ズレ以外ありえない
					g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy.NowKeyCntDOWN - 1].nSplitFrame = g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy3.Motion[g_Enemy.NowMotionDOWN].nNumKey - 1].nSplitFrame;
					//	g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy.NowKeyCntDOWN - 1].nSplitFrame = 5;
				}

			}

			if (g_Enemy.NowFrameCntDOWN < g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy.NowKeyCntDOWN - 1].nSplitFrame)
			{//分割フレームの分回る
				if (g_Enemy.NowKeyCntDOWN < g_Enemy3.Motion[g_Enemy.NowMotionDOWN].nNumKey)
				{//キーの分回る
					if (g_Enemy.NowKeyCntDOWN == 12)
					{
						if (g_Enemy.NowMotionDOWN == MOTIONTYPE_ENEMY_ATTACK)
						{
							int test;

							test = 1111;
						}
					}

					for (int nCntParts = 0; nCntParts < g_Enemy3.nMaxPartsCnt; nCntParts++)
					{//パーツ分回る
					//	if (nCntParts == 0 || (nCntParts >= 9 && nCntParts <= 14))
					//	{
							//ROT系
						if (g_Enemy3.ModelParts[nCntParts].calculationExecution == false)
						{
							//CorrectionPos,CorrectionRotはあくまで、OFFSETをStart地点とした補正量なので、
							D3DXVECTOR3 TargetRot;
							TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

							TargetRot = g_Enemy3.ModelParts[nCntParts].StartRot + g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy.NowKeyCntDOWN].PartsData[nCntParts].CorrectionRot;

							g_Enemy3.ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionEnemyRot3(TargetRot - g_Enemy3.ModelParts[nCntParts].Rot, 0)) / g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy.NowKeyCntDOWN - 1].nSplitFrame;

							g_Enemy3.ModelParts[nCntParts].calculationExecution = true;
						}

						g_Enemy3.ModelParts[nCntParts].Rot += g_Enemy3.ModelParts[nCntParts].CorrectCorrectionRotMove;

						//POS系
						//--------------------------------------------------------------------------------
						if (g_Enemy3.ModelParts[nCntParts].PEARENT == -1)
						{//自分がすべての親の時
							D3DXVECTOR3 TargetPos;
							TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

							//初期位置から見た地点を補正した、目標地点の算出
							TargetPos = g_Enemy3.ModelParts[nCntParts].StartPos + g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy.NowKeyCntDOWN].PartsData[nCntParts].CorrectionPos;

							//現在の位置から、上で算出した目標地点までの差分計算
							g_Enemy3.ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Enemy3.ModelParts[nCntParts].Pos) / g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy.NowKeyCntDOWN - 1].nSplitFrame;

							//POSの更新
							g_Enemy3.ModelParts[nCntParts].Pos += g_Enemy3.ModelParts[nCntParts].CorrectCorrectionPosMove;
							//------------------------------------------------------------------------------------
						}
						//	}
					}
				}
				g_Enemy.NowFrameCntDOWN++;//フレーム進める
			}
			else
			{//フレーム数超えた
				g_Enemy.NowFrameCntDOWN = 0;//フレームリセット

				g_Enemy.NowKeyCntDOWN++;//キーを進める

				for (int i = 0; i < MAX_PARTS_ENEMY; i++)
				{//リセット
					g_Enemy3.ModelParts[i].calculationExecution = false;
				}

				if (g_Enemy.NowKeyCntDOWN == g_Enemy3.Motion[g_Enemy.NowMotionDOWN].nNumKey)
				{//キーが、最大キーを超えた時

					g_Enemy.NowFrameCntDOWN = 0;//フレームリセット
					g_Enemy.NowKeyCntDOWN = 0;//キーリセット

					if (g_Enemy3.Motion[g_Enemy.NowMotionDOWN].nLoop == 0)
					{//ループしない
						if (g_Enemy.NowMotionDOWN == MOTIONTYPE_ENEMY_JUMP)
						{
							g_Enemy.MotionLoopStop = true;
						}
						else
						{//飛翔以外
							//待機にする
							g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_STANDBY;//待機状態に戻す
							//ブレンド挟む
							if (g_Enemy.MotionBrend == false)
							{
								g_Enemy.NowKeyCntDOWN = 0;
								g_Enemy.NowFrameCntDOWN = 0;
								g_Enemy.EscapeMotion = g_Enemy.NowMotionDOWN;
								g_Enemy.BrendCnt = 0;
								for (int i = 0; i < MAX_PARTS_ENEMY; i++)
								{//リセット

									g_Enemy3.ModelParts[i].calculationExecution = false;
									g_Enemy3.ModelParts[i].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
									g_Enemy3.ModelParts[i].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
									g_Enemy.MotionLoopStop = false;

									g_Enemy.MotionBrend = true;

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
//エネミー設定処理
//===================================
void SetModel_Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	if (g_Enemy.bUse == false)
	{
		g_Enemy.pos = pos;	//位置
		g_Enemy.rot = rot;	//向き
		g_Enemy.bUse = true;
		g_Enemy.move = D3DXVECTOR3(0.0f, 0.0f, MAX_ENEMY_SPEED);
		g_Enemy.MotionBrend = true;
		g_Enemy.OldMotionDOWN = MOTIONTYPE_ENEMY_MAX;
		g_Enemy.ActionPattern = ACTIONPATTERN_ENEMY_SPAWN;
		g_Enemy.TargetMotion = MOTIONTYPE_ENEMY_MOVE;
		g_Enemy.NowKeyCntDOWN = 0;
		ActionEnemy(g_Enemy.ActionPattern, -1);
		SetEnemy_View(D3DXVECTOR3(g_Enemy.pos)
			, 250.0f
			, true
			, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.4f));
		LoadSetEnemy3();//---------------------------------------------------------こいつがロード
		LowerBodyEnemy3();
	}
}
