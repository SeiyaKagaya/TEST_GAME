//=========================================================
//
//モデルを表示する処理[player.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "player.h"
#include "player2.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "line.h"
#include "transfergate.h"
#include "Actionzone.h"
#include "enemy_view.h"
#include "enemy.h"
#include "bathgimmick.h"
#include "menu.h"
#include "sound.h"

//#include "sound.h"

#include <stdio.h>//ヘッダーファイルをインクルード
#include <string.h>//文字列を扱う変数
#include "game.h"
#include "item.h"
#include "stage.h"
#include "hitcollision_mistake_prevention.h"



Player g_Player;//プレイヤー全体

///-------------------------------------------------------------------------モデル
LPD3DXMESH g_pMeshModel[MAX_PARTS] = {};//メッシュ(頂点情報)へのポインタ

LPD3DXBUFFER g_pBuffMatModel[MAX_PARTS] = {};//マテリアルへのポインタ

DWORD dwNumMatModel[MAX_PARTS] = {};//マテリアルの数

MODEL g_Model;//モデル全体
//--------------------------------------------------------------------------

LPDIRECT3DTEXTURE9 g_apTexture_1P[MAX_PARTS][NUM_TEXTURE_1P] = {}; //テクスチャポインタ

//各モーションのモデル数
char g_PlayerFileName[MAX_PARTS][MAX_WORD2][MAX_WORD] = {};//パス格納


//追尾注視点
View g_View[4];


int g_Cnt = 0;//テスト。


bool g_test = false;

//=============================
//モデルの初期化処理
//=============================
void InitPlayer(void)
{
	g_Cnt = 0;

	for (int i=0; i < 4; i++)
	{
		//注視点
		if (i==0)
		{
			g_View[i].ViewPos = D3DXVECTOR3(0.0f,0.0f,0.0f);

		}
		else if(i == 1)
		{
			g_View[i].ViewPos = VIEWPOS;
		}
		else if (i == 2)
		{
			g_View[i].ViewPos = ITEMDROPPOS;
		}
		else if (i == 3)
		{
			g_View[i].ViewPos = SPEECHPOS;
		}

		g_View[i].ViewRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	g_Player.nldShadow = -4;//影

	//とりあえずパーツの数(後にtxtで)だけ回す

//	g_Player.NowMotionUP = MOTIONTYPE_1P_MAX;
	g_Player.NowMotionDOWN = MOTIONTYPE_1P_MAX;

//	g_Player.OldMotionUP = MOTIONTYPE_1P_MAX;
	g_Player.OldMotionDOWN = MOTIONTYPE_1P_MAX;

	g_Player.fRotDest = D3DX_PI;

	g_Player.nLife = MAXLIFE;


	//メニューからどのモードを選んだか取得
	int MenutoGame = GetMenu1();

	if (MenutoGame == START_MENU_GAME)
	{//メニューで「ゲームスタート」を選んだ場合
		g_Player.pos = D3DXVECTOR3(3300.0f, 104.5f, -2000.0f);	//位置
	}
	else
	{//それ以外(チュートリアルを選んだ場合)
		g_Player.pos = D3DXVECTOR3(3000.0f, 10.0f, 2500.0f);	//位置
	}



	g_Player.oldPos = g_Player.pos;	//位置

	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き

	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//

	g_Player.PlayerState = PLAYERSTATE_1P_NOMAL;
	g_Player.PlayerStateCnt = 0;

	g_Player.rotmove = 0.0f;
	g_Player.PARENT = -1;//親子関係

	g_Player.JumpFrame = 0;

	g_Player.bUse = false;
	g_Player.JumpNow = false;
	g_Player.JumpOld = false;

	g_Player.bMoneyBoxGimmick = false;
	g_Player.bTvGimmick = false;
	g_Player.nHaveRemocon = 0;
	g_Player.nHaveDish = 0;
	g_Player.nHaveVegetable = 0;
	g_Player.nHaveSoup= 0;

	g_Player.NowFrameCntDOWN = 0;
	g_Player.NowKeyCntDOWN = 0;

	g_Player.NowFrameCntUP = 0;
	g_Player.NowKeyCntUP = 0;
	g_Player.MotionLoopStop = false;
	g_Player.MotionBrend = false;
	g_Player.bAction = false;
	g_Player.BrendCnt = 0;
	g_Player.EscapeMotion = MOTIONTYPE_1P_BREND;
	g_Player.bTransparent = false;
	g_Player.CrossRoadNow = false;
	//-------------------------------------------------モデル系
	g_Model.nMaxMotionCnt = 0;
	g_Model.nMaxPartsCnt = 0;
	g_Model.nMaxLoadPartsCnt = 0;

	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)//各パーツ本体
	{
		g_Model.ModelParts[nCntParts].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model.ModelParts[nCntParts].Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Model.ModelParts[nCntParts].StartPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model.ModelParts[nCntParts].StartRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Model.ModelParts[nCntParts].PEARENT = 0;
		g_Model.ModelParts[nCntParts].INDEX = 0;

		g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Model.ModelParts[nCntParts].calculationExecution = false;

		//mtxはおいておく
	}

	for (int nMotionCnt = 0; nMotionCnt < MAX_MONITORS; nMotionCnt++)//各モーションデータ
	{
		g_Model.Motion[nMotionCnt].nNumKey = 0;
		g_Model.Motion[nMotionCnt].nLoop = 0;
		g_Model.Motion[nMotionCnt].Motiontype = MOTIONTYPE_1P_MAX;


		for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)//各モーション中の各パーツの各キー内のデータ
		{
			g_Model.Motion[nMotionCnt].KeyData[nCntKey].nSplitFrame = 0;

			for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)//各モーション中の各パーツデータ
			{
				g_Model.Motion[nMotionCnt].KeyData[nCntKey].PartsData[nCntParts].CorrectionPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Model.Motion[nMotionCnt].KeyData[nCntKey].PartsData[nCntParts].CorrectionRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}

	//影を設定
	g_Player.nldShadow = SetShadow();

	LoadSet();//---------------------------------------------------------こいつがロード
	LoadXfire_Player();
	

	int test;
	test = 0;
}
//=============================
//モデルの終了処理
//=============================
void UninitPlayer(void)
{

	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{
		for (int nCntTex = 0; nCntTex < NUM_TEXTURE_1P; nCntTex++)
		{
			// テクスチャの破棄
			if (g_apTexture_1P[nCntModel][nCntTex] != NULL)
			{
				g_apTexture_1P[nCntModel][nCntTex]->Release();
				g_apTexture_1P[nCntModel][nCntTex] = NULL; // 解放後に NULL を設定
	
			}
		}

		// メッシュの破棄
		if (g_pMeshModel[nCntModel] != NULL)
		{
			g_pMeshModel[nCntModel]->Release();
			g_pMeshModel[nCntModel] = NULL;
		}
		// マテリアルの破棄
		if (g_pBuffMatModel[nCntModel] != NULL)
		{
			g_pBuffMatModel[nCntModel]->Release();
			g_pBuffMatModel[nCntModel] = NULL;
		}
	}
}
//=============================
//モデルの更新処理
//=============================
void UpdatePlayer(void)
{


	//g_Player.bUse = true;

	if (g_Player.bUse == true)
	{
		//プレイヤー２のサイズ
		Player_2P* pPlayer2;
		pPlayer2 = GetPlayer_2P();
		D3DXMATRIX mtxRot, mtxTrans, mtxParent;//計算用マトリックス

		XINPUT_STATE joykeystate;

		//ショイパットの状態を取得
		DWORD dwResult = XInputGetState(0, &joykeystate);

		g_Player.JumpNow = false;
		g_Player.bLandingNow = false;
		g_Player.bAction = false;
		g_test = false;

		//---------------------------------------------------------------------------------------------------------ここで腰を相手に向ける
	//	bool calculated = false;//腰傾けたか

		//腰の角度
	//	float minYAngle = -0.5f; // 下側の角度の限界
	//	float maxYAngle = 0.5f;  // 上側の角度の限界

		//-----------------------------------------------------------------------------------入力ここから
		if (CheckInputMove2() == -1)
		{//移動入力なし
			if (pPlayer2->NowMotionDOWN != MOTIONTYPE_2P_MOVE)
			{
				StopSound(SOUND_LABEL_SE_WALK);
			}
			if (g_Player.NowMotionDOWN != MOTIONTYPE_1P_STANDBY && g_Player.NowMotionDOWN != MOTIONTYPE_1P_JUMP && g_Player.NowMotionDOWN != MOTIONTYPE_1P_RANDING && g_Player.NowMotionDOWN != MOTIONTYPE_1P_ATTACK)//------------------------
			{//モーション変動
				g_Player.NowMotionDOWN = MOTIONTYPE_1P_STANDBY;
			}

			//		if (g_Player.NowMotionUP != MOTIONTYPE_1P_ATTACK)
			//		{//モーション変動
			//			g_Player.NowMotionUP = MOTIONTYPE_1P_STANDBY;
			//		}
		}

		if (CheckInputMove2() == 0)
		{//移動入力あり
			if (dwResult == ERROR_SUCCESS)
			{//キーボード/コントローラー入力反映(移動)
				InPutControllerPlayer();
			}
			else
			{//キーボード入力反映(移動)
				InPutKeyboardPlayer();
			}

		}
		//攻撃系入力
		InputKeyAttack();

		//古いposを代入
		g_Player.oldPos = g_Player.pos;

		//位置を更新
		g_Player.pos += g_Player.move;


		//--------------------------------------------------------------------------------------------------------------------------------------------------//当たり判定ここから
		//プレイヤーのサイズ
		D3DXVECTOR3 PlayerMin = D3DXVECTOR3(g_Player.pos + PLAYERMIN);
		D3DXVECTOR3 PlayerMax = D3DXVECTOR3(g_Player.pos + PLAYERMAX);

		D3DXVECTOR3 PlayerMin_2P = D3DXVECTOR3(pPlayer2->pos + PLAYERMIN_2P);
		D3DXVECTOR3 PlayerMax_2P = D3DXVECTOR3(pPlayer2->pos + PLAYERMAX_2P);

		//プレイヤー同士当たり判定
		BoxCollisionPlayer(PlayerMin, PlayerMax, PlayerMin_2P, PlayerMax_2P, 1);

		//エネミー
		ENEMYMODEL* pEnemy;
		pEnemy = GetEnemy();
		BoxCollisionKill(PlayerMin, PlayerMax, pEnemy->MinPos, pEnemy->MaxPos, 1);


		//アイテム------------------------------------------------------------------------------------------------------------------------------------------------
		ITEM* pItem;
		pItem = GetItem();

		for (int ItemCnt = 0; ItemCnt < NUMITEM; ItemCnt++)
		{
			if (pItem[ItemCnt].bUse == true)
			{
				if (pItem[ItemCnt].bGetNO == false)
				{
					BoxCollisionItem(PlayerMin, PlayerMax, pItem[ItemCnt].pos, 1, ItemCnt);
				}
			}
		}

		//転移門/-----------------------------------------------------------------------------------------------------------------------------------------
		TRANSFERGATE* pTransferGate;
		pTransferGate = GetTransferGate();

		for (int nCntGate = 0; nCntGate < MAXGATE; nCntGate++)
		{
			if (pTransferGate[nCntGate].bUse == true)
			{
				D3DXVECTOR3 GateMin = D3DXVECTOR3(pTransferGate[nCntGate].pos + pTransferGate[nCntGate].GateMin);
				D3DXVECTOR3 GateMax = D3DXVECTOR3(pTransferGate[nCntGate].pos + pTransferGate[nCntGate].GateMax);

				BoxCollisionGate(PlayerMin, PlayerMax, GateMin, GateMax, 0, pTransferGate[nCntGate].nGateIndex, pTransferGate[nCntGate].nParentIndex);

				//	break;
			}
		}


		//----------------------------------------------------------------------------モデル接触
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
					BoxCollisionPlayer(PlayerMin, PlayerMax, ModelMin, ModelMax, 1);
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
					BoxCollisionPlayer(PlayerMin, PlayerMax, StageMin, StageMax, 1);
				}
			}
		}


		

		//敵の視野/-----------------------------------------------------------------------------------------------------------------------------------------
		ENEMYVIEW* pEnemyView;
		pEnemyView = GetEnemy_View();

		for (int nCntZone = 0; nCntZone < MAX_ENEMYVIEW; nCntZone++)
		{
			if (pEnemyView[nCntZone].bUse == true && pEnemyView[nCntZone].bFollowEnemy == true)
			{

				SphereEnemyView(g_Player.pos, 0, nCntZone);
				//	break;
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
				BoxCollisionPlayer(PlayerMin, PlayerMax, ColisionPreMin, ColisionPreMax, 1);

			}
		}








		////--------------------------------------------------------------------------------------------------------------------------------------------------//当たり判定ここまで

		if (g_Player.pos.y <= 0.0f)
		{//地面-0以下にしない
			g_Player.bLandingNow = true;
		}

		if (g_Player.bLandingNow == false)
		{//空中
			//移動量を更新(疑似慣性で減衰)
			g_Player.move.x += (0.0f - g_Player.move.x) * DAMPING_RATIO2;
			g_Player.move.y += (0.0f - g_Player.move.y) * DAMPING_RATIO2;
			g_Player.move.z += (0.0f - g_Player.move.z) * DAMPING_RATIO2;
		}
		else
		{//地上
			//移動量を更新(疑似慣性で減衰)
			g_Player.move.x += (0.0f - g_Player.move.x) * DAMPING_RATIO;
			g_Player.move.y += (0.0f - g_Player.move.y) * DAMPING_RATIO;
			g_Player.move.z += (0.0f - g_Player.move.z) * DAMPING_RATIO;
		}


		//重力
		if (g_Player.pos.y > 0.0f)
		{//空中(地上ではない)の時

			//重力
			g_Player.move.y -= GRAVITY;

			if (g_Player.bLandingNow == false)
			{//ジャンプで無い
				g_Player.NowMotionDOWN = MOTIONTYPE_1P_JUMP;
			}
		}
		else
		{//地上
			g_Player.pos.y = 0.0f;

			if (g_Player.NowMotionDOWN == MOTIONTYPE_1P_JUMP)
			{//飛んでるときに着地
				g_Player.NowMotionDOWN = MOTIONTYPE_1P_RANDING;
			}
		}

		//////侵入不可エリア(限界エリア)----------------------
		////if (g_Player.pos.x > MAXMAREA)
		////{
		////	g_Player.pos.x = (MAXMAREA - 1.0f);
		////}
		////else if (g_Player.pos.x < -MAXMAREA)
		////{
		////	g_Player.pos.x = -(MAXMAREA - 1.0f);
		////}

		////if (g_Player.pos.z > MAXMAREA)
		////{
		////	g_Player.pos.z = (MAXMAREA - 1.0f);
		////}
		////else if (g_Player.pos.z < -MAXMAREA)
		////{
		////	g_Player.pos.z = -(MAXMAREA - 1.0f);
		////}

		//影
		SetPositionShadow(g_Player.nldShadow, g_Player.pos, SHADOWSIZE_PLAYER);

		//上下のモーション
		LowerBodyMotion();
		
			//前回のモーションデータを更新
			//g_Player.OldMotionUP = g_Player.NowMotionUP;
		g_Player.OldMotionDOWN = g_Player.NowMotionDOWN;

		g_Player.JumpOld = g_Player.JumpNow;


		////---------------------------------------------------------------------------------------------------------------他で使う計算
		//キャラ全体の基準(親の親)
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);

		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);

		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);


		//------------------------------------------------------------------------------------------------------------注視点
		Camera* pCamera;
		pCamera = GetCamera();

		D3DXMATRIX EscapeMtx;
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&EscapeMtx);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);

		D3DXMatrixMultiply(&EscapeMtx, &EscapeMtx, &mtxTrans);

		for (int i = 0; i < 4; i++)
		{
			g_View[i].ViewRot.y = -pCamera[0].rot.y;

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_View[i].ViewPosMtx);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_View[i].ViewRot.y, g_View[i].ViewRot.x, g_View[i].ViewRot.z);

			D3DXMatrixMultiply(&g_View[i].ViewPosMtx, &g_View[i].ViewPosMtx, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_View[i].ViewPos.x, g_View[i].ViewPos.y, g_View[i].ViewPos.z);

			D3DXMatrixMultiply(&g_View[i].ViewPosMtx, &g_View[i].ViewPosMtx, &mtxTrans);

			if (i == 0)
			{
				//プレイヤーとかける
				D3DXMatrixMultiply(&g_View[i].ViewPosMtx, &g_View[i].ViewPosMtx, &EscapeMtx);

			}
			else if (i == 1)
			{
				//0番目とかける
				D3DXMatrixMultiply(&g_View[i].ViewPosMtx, &g_View[i].ViewPosMtx, &g_View[0].ViewPosMtx);
			}
			else if (i == 2)
			{
				//0番目とかける//アイテム出現位置
				D3DXMatrixMultiply(&g_View[i].ViewPosMtx, &g_View[i].ViewPosMtx, &g_View[0].ViewPosMtx);
			}
			else if (i == 3)
			{
				//0番目とかける//アイテム出現位置
				D3DXMatrixMultiply(&g_View[i].ViewPosMtx, &g_View[i].ViewPosMtx, &g_View[0].ViewPosMtx);
			}
		}
		//------------------------------------------------------------------------------------------------------------注視点




		//----------パーツ
		for (int nCnt = 0; nCnt < g_Model.nMaxPartsCnt; nCnt++)
		{//パーツ分回す
			//モデルの位置
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Model.ModelParts[nCnt].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.ModelParts[nCnt].Rot.y, g_Model.ModelParts[nCnt].Rot.x, g_Model.ModelParts[nCnt].Rot.z);

			D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Model.ModelParts[nCnt].Pos.x, g_Model.ModelParts[nCnt].Pos.y, g_Model.ModelParts[nCnt].Pos.z);

			D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &mtxTrans);

			//親子関係
			if (g_Model.ModelParts[nCnt].PEARENT == -1)
			{
				//プレイヤーとかける
				D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &g_Player.mtxWorld);
			}
			else
			{
				//自分の親のマトリックス欠けてる
				D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[g_Model.ModelParts[nCnt].PEARENT].mtxWorld);

			}
		}



		//行動エリア/-----------------------------------------------------------------------------------------------------------------------------------------
		ACTIONZONE* pActionZone;
		pActionZone = GetActionZone();

		for (int nCntZone = 0; nCntZone < MAXZONE; nCntZone++)
		{
			if (pActionZone[nCntZone].bUse == true)
			{

				SphereCollisionZone(g_Player.pos, 0, nCntZone);
				//	break;
			}
		}


		for (int nWall = 0; nWall < NUMSTAGE; nWall++)
		{
			if (pStage[nWall].bUse == true)
			{
				D3DXVECTOR3 StageMin = D3DXVECTOR3(pStage[nWall].posStage + pStage[nWall].MinPos);
				D3DXVECTOR3 StageMax = D3DXVECTOR3(pStage[nWall].posStage + pStage[nWall].MaxPos);

				//障害物検知
				AdjustPlayerPositionToCollision_VIEWPOS(D3DXVECTOR3(g_Player.pos.x, (g_Player.pos.y + g_View[1].ViewPos.y), g_Player.pos.z), 0, StageMin, StageMax);

			}
		}

		for (int i = 0; i < MAX_MODEL; i++)
		{
			if (pMapObject[i].bUse == true)
			{
				if (pMapObject[i].bCollision == true)
				{
					D3DXVECTOR3 ModelMin = D3DXVECTOR3(pMapObject[i].pos + pMapObject[i].Minpos);
					D3DXVECTOR3 ModelMax = D3DXVECTOR3(pMapObject[i].pos + pMapObject[i].Maxpos);


					//プレイヤー同士当たり判定
					//BoxCollisionPlayer(PlayerMin, PlayerMax, ModelMin, ModelMax, 1);
					//障害物検知
					AdjustPlayerPositionToCollision_VIEWPOS(D3DXVECTOR3(g_Player.pos.x, (g_Player.pos.y + g_View[1].ViewPos.y), g_Player.pos.z), 0, ModelMin, ModelMax);
				}
			}
		}













		//状態遷移
		//プレイヤー被弾振動管理
		if (g_Player.PlayerStateCnt > 0)
		{
			g_Player.PlayerStateCnt--;
		}

		if (g_Player.PlayerStateCnt <= 0)
		{
			g_Player.PlayerState = PLAYERSTATE_1P_NOMAL;

			////振動ストップ
			//VibrationLeft(0);
			//VibrationRight(0);
		}






		//MAPOBJECT *pObject;
		//pObject = GetMapObject();
		//pObject[0].pos = g_Player.pos;
	}
}
//=============================
//モデルの描画処理
//=============================
void DrawPlayer(int CameraLoopNum)
{

	if (g_Player.bUse == true)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXMATRIX mtxRot, mtxTrans, mtxParent;//計算用マトリックス

		D3DMATERIAL9 matDef;//現在のマテリアル保存用(一時退避)

		D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

		//キャラ全体の基準(親の親)
			//---------------------------------------------------------------------------------------------------プレイヤーの位置のみ
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);

		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);

		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);



		for (int nCnt = 0; nCnt < g_Model.nMaxPartsCnt; nCnt++)
		{
			//---------------------------------------------------------------------------------------------------モデルの位置

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Model.ModelParts[nCnt].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.ModelParts[nCnt].Rot.y, g_Model.ModelParts[nCnt].Rot.x, g_Model.ModelParts[nCnt].Rot.z);

			D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Model.ModelParts[nCnt].Pos.x, g_Model.ModelParts[nCnt].Pos.y, g_Model.ModelParts[nCnt].Pos.z);

			D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &mtxTrans);


			//bool tttest = false;


			//for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
			//{
			//	if (pEnemy[nCntEnemy].PriorityAttackTarget == true)
			//	{
			//		D3DXVECTOR3 enemyDirection = pEnemy[nCntEnemy].pos - g_Player.pos;

			//		float angle = atan2f(enemyDirection.z, enemyDirection.x);
			//		g_Model.ModelParts[1].Rot.x = 0.0f; // よじりを防ぐために必要な調整
			//		g_Model.ModelParts[1].Rot.y = angle;
			//		g_Model.ModelParts[1].Rot.z = 0.0f;


			//		tttest = true;
			//		//ここで腰をよじらせる
			//		//g_Model.ModelParts[1].Rot 
			//		//float test = atan2f(pEnemy[nCntEnemy].rot.z - g_Model.ModelParts[0].Rot.z, pEnemy[nCntEnemy].rot.x - g_Model.ModelParts[0].Rot.x);
			//		//g_Model.ModelParts[1].Rot.x = sinf(test);
			//		//g_Model.ModelParts[1].Rot.z = cosf(test);
			//	}
			//}
			//if (tttest == false)
			//{
			//	g_Model.ModelParts[1].Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//}





			//親子関係
			if (g_Model.ModelParts[nCnt].PEARENT == -1)
			{
				//プレイヤーとかける
				D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &g_Player.mtxWorld);
			}
			else
			{
				//自分の親のマトリックス欠けてる
				D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[g_Model.ModelParts[nCnt].PEARENT].mtxWorld);
			}

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Model.ModelParts[nCnt].mtxWorld);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatModel[nCnt]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)dwNumMatModel[nCnt]; nCntMat++)
			{

				//------------------------カラーチェンジ
				if (g_test == true)
				{
						// マテリアルの設定
						D3DMATERIAL9 matTemp = pMat[nCntMat].MatD3D;
						matTemp.Diffuse = D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.8f);
						//matTemp.Diffuse.a = 0.5f;  // 透過度を設定（0.0fで完全透明、1.0fで不透明）
						pDevice->SetMaterial(&matTemp);
				}
				else
				{
						//マテリアルの設定
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				}

				if (CameraLoopNum != 2)
				{//0カメ
					if (g_Player.bTransparent == true)
					{//透過
						// マテリアルの設定
						D3DMATERIAL9 matTemp = pMat[nCntMat].MatD3D;
						//matTemp.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
						matTemp.Diffuse.a = 0.2f;  // 透過度を設定（0.0fで完全透明、1.0fで不透明）
						pDevice->SetMaterial(&matTemp);
					}
				}

				//テクスチャの設定
				//pDevice->SetTexture(0, NULL);//今回は設定しない
				//テクスチャの設定
	
				pDevice->SetTexture(0, g_apTexture_1P[nCnt][nCntMat]);
				//モデル(パーツ)の描画
				g_pMeshModel[nCnt]->DrawSubset(nCntMat);

			}
		}
		//保存してたマテリアルを戻す
		pDevice->SetMaterial(&matDef);

		//テクスチャを戻す
		pDevice->SetTexture(0, NULL);
	}
	
}
//=============================
//プレイヤー情報取得処理
//=============================
Player* GetPlayer(void)
{
	return &g_Player;
}
//=============================
//プレイヤー注視点情報取得処理
//=============================
View* GetView(void)
{
	return &g_View[0];
}
//=============================
//プレイヤーメッシュ情報取得処理
//=============================
LPD3DXMESH* GetMesh_Player(void)
{
	return &g_pMeshModel[0];
}

//=============================
//キーボード入力反映処理(移動)
//=============================
void InPutKeyboardPlayer(void)
{
	bool MoveNow = false;//移動入力できてるか

//	bool NomalMove = false;//通常入力かどうか

	Camera* pCamera;
	pCamera = GetCamera();

	float nMoveSpeed = 0;

	//移動速度--移動速度変動時に書き換え可能
	nMoveSpeed = MOVESPEED;

	float Xdate = 0.0f;
	float Zdate = 0.0f;

	//キーボード
	if (GetkeyboardPress(DIK_A) == true )
	{//Aがおされた(左)
		Xdate =
			1;
		MoveNow = true;
	}
	else if (GetkeyboardPress(DIK_D) == true )
	{//Dがおされた(右)
		Xdate = -1;
		MoveNow = true;
	}

	if (GetkeyboardPress(DIK_W) == true )
	{//Wがおされた(上)
		Zdate = -1.0f;
		MoveNow = true;
	}
	else if (GetkeyboardPress(DIK_S) == true )
	{//Sがおされた(下)
		Zdate = 1.0f;
		MoveNow = true;
	}
	//移動する状態の時
	if (MoveNow == true)
	{
		float Angle = atan2f(Xdate, Zdate);//これが方角


		//------これはWW

		g_Player.fRotDest = (Angle - pCamera[0].rot.y - (1.0f * D3DX_PI));

		g_Player.move.x = sinf(Angle - pCamera[0].rot.y - (1.0f * D3DX_PI)) * nMoveSpeed;//三角関数利用して移動の長さを代入
		g_Player.move.z = cosf(Angle - pCamera[0].rot.y - (1.0f * D3DX_PI)) * nMoveSpeed;//三角関数利用して移動の長さを代入
	}


	//変換
	ConversionPlayerRot2(g_Player.fRotDest + D3DX_PI, 0);//D3DX_PIは角度補正
}
//=============================
//キーボード/コントローラー入力反映処理(移動)
//=============================
void InPutControllerPlayer(void)
{

	Camera* pCamera;
	pCamera = GetCamera();

	XINPUT_STATE joykeystate;




	//ショイパットの状態を取得
	DWORD dwResult = XInputGetState(0, &joykeystate);




	float nMoveSpeed = 0;

	//移動量を一時保存(移動量の変動などに)
	D3DXVECTOR3 EscapeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	bool MoveNow = false;//移動入力できてるか

	bool NomalMove = false;//通常入力かどうか

	bool MoveNowCom = false;//移動入力できてるか--Controller

	bool Sneak = false; //スニークしてるかどうか

	//分割率
	float  Split = 1.6f;




	//--移動速度変動時に書き換え可能
	nMoveSpeed = MOVESPEED;

	//joykeystate.Gamepad.sThumbLX <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE-6000++++++++++++++++左
	//joykeystate.Gamepad.sThumbLY >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE-6000++++++++++++++++上
	//joykeystate.Gamepad.sThumbLY <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE-6000++++++++++++++下
	//joykeystate.Gamepad.sThumbLX >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE-6000+++++++++++++++右


	//XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE+++++++++++++++++++++++++最大値


	//中間点までの距離
	float fEscape = (32000 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000) / 2.0f;//差分を半分に

	//中間点をたしてデッドゾーンと最大点の中間点を算出(通常入力、微入力の判別分岐点)
	float BranchPoint = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 + fEscape;


	float Xdate = 0.0f;
	float Zdate = 0.0f;

	////キーボード
	//if (GetkeyboardPress(DIK_A) == true )
	//{//Aがおされた(左)
	//	Xdate = 
	//		1;
	//	MoveNow = true;
	//}
	//else if (GetkeyboardPress(DIK_D) == true )
	//{//Dがおされた(右)
	//	Xdate = -1;
	//	MoveNow = true;
	//}

	//if (GetkeyboardPress(DIK_W) == true )
	//{//Wがおされた(上)
	//	 Zdate = -1.0f;
	//	 MoveNow = true;
	//}
	//else if (GetkeyboardPress(DIK_S) == true)
	//{//Sがおされた(下)
	//	 Zdate = 1.0f;
	//	 MoveNow = true;
	//}

	//Controller
	//--------------------------------------------------------------------------------------
	if (joykeystate.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		Sneak = true;
	}

	if ( joykeystate.Gamepad.sThumbLX <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Aがおされた(左)
	//	Xdate = 1;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLX >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Dがおされた(右)
	//	Xdate = -1;
		MoveNowCom = true;
	}
	else if ( joykeystate.Gamepad.sThumbLY >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Wがおされた(上)
		//Zdate = -1.0f;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLY <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Sがおされた(下)
		//Zdate = 1.0f;
		MoveNowCom = true;
	}


	if (MoveNowCom == false)
	{
		//移動する状態の時
		if (MoveNow == true)
		{
			g_Player.NowMotionDOWN = MOTIONTYPE_1P_MOVE;

			float Angle = atan2f(Xdate, Zdate);//これが方角


			//------これはWW

			g_Player.fRotDest = (Angle - pCamera[0].rot.y - (1.0f * D3DX_PI));

			EscapeMove.x = sinf(Angle - pCamera[0].rot.y - (1.0f * D3DX_PI)) * nMoveSpeed;//三角関数利用して移動の長さを代入
			EscapeMove.z = cosf(Angle - pCamera[0].rot.y - (1.0f * D3DX_PI)) * nMoveSpeed;//三角関数利用して移動の長さを代入
		}
	}
	else
	{//Controller
		if (g_Player.NowMotionDOWN == MOTIONTYPE_1P_STANDBY)
		{
			PlaySound(SOUND_LABEL_SE_WALK);
		}
		g_Player.NowMotionDOWN = MOTIONTYPE_1P_MOVE;

		float BoostMove=1.0f;
		if (Sneak == false)
		{
			BoostMove = 1.0f;
		}
		else if (Sneak == true)
		{//スニーク時減速
			//モーションも変える
			BoostMove = 0.5f;
		}

		float Angle2 = atan2f(-joykeystate.Gamepad.sThumbLX, -joykeystate.Gamepad.sThumbLY);//これが方角

		g_Player.fRotDest = (Angle2 - pCamera[0].rot.y - (1.0f * D3DX_PI));

		EscapeMove.x = sinf(Angle2 - pCamera[0].rot.y - (1.0f * D3DX_PI)) * nMoveSpeed* BoostMove;//三角関数利用して移動の長さを代入
		EscapeMove.z = cosf(Angle2 - pCamera[0].rot.y - (1.0f * D3DX_PI)) * nMoveSpeed* BoostMove;//三角関数利用して移動の長さを代入
		MoveNow = true;
	}



	//移動する状態の時
	if (MoveNow == true)
	{
		//通常入力まで倒していか
		if (BranchPoint <= joykeystate.Gamepad.sThumbLY || -BranchPoint >= joykeystate.Gamepad.sThumbLY)
		{
			NomalMove = true;//通常移動状態にする
		}
		if (BranchPoint <= joykeystate.Gamepad.sThumbLX || -BranchPoint >= joykeystate.Gamepad.sThumbLX)
		{
			NomalMove = true;//通常移動状態にする
		}

		if (NomalMove == true)
		{//通常移動時
			g_Player.move += EscapeMove * Split;
			NomalMove = false;
		}
		else
		{
			g_Player.move += EscapeMove * (Split / 1.9f);
		}
		//モデル角変換
		ConversionPlayerRot2(g_Player.fRotDest + D3DX_PI, 0);//D3DX_PIは角度補正	
	}


}
//=============================
//攻撃キー入力処理
//=============================
void InputKeyAttack(void)
{
//
//	Camera* pCamera;
//	pCamera = GetCamera();
//
	XINPUT_STATE joykeystate;

	//ショイパットの状態を取得
	DWORD dwResult = XInputGetState(0, &joykeystate);
//
//	float	nMoveSpeed = 0.0f;
//
//
//
//	//移動速度--移動速度変動時に書き換え可能
//	nMoveSpeed = MOVESPEED * 2;
//
//
//	//入力の有無を確認して分岐
//	if (GetkeyboardPress(DIK_SPACE) == true || joykeystate.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)//トリガー
//	{//スペースがおされた//L2キー
//	//	g_Player.NowMotionUP = MOTIONTYPE_1P_ATTACK;
//		g_Player.NowMotionDOWN = MOTIONTYPE_1P_ATTACK;
//
//	}
//#if _DEBUG
//	//ジャンプ
//	if (GetkeyboardPress(DIK_RETURN) || GetJoypadPress(JOYKEY_A,0) == true)
//	{//スペースがおされた(スペース)
//		if (g_Player.JumpOld == false)
//		{
//			//	PlaySound(SOUND_LABEL_SE_JUMP);
//		}
//		g_Player.JumpNow = true;
//
//		g_Player.move.y += 2.0f;
//
//		g_test = true;
//	}
//
//
//
//
//#endif
	//アクション
	if (GetJoypadTrigger(JOYKEY_X, 0) == true)
	{
		g_Player.bAction = true;
	}
//
//	if (GetJoypadTrigger(JOYKEY_Y, 0) == true)
//	{
//		// int を ModelType にキャストして代入
//		//g_MapObject_Escape[g_ModelCnt].nType = static_cast<ModelType>(Escape);
//		ITEMTYPE itemtype;
//		itemtype= static_cast<ITEMTYPE>(g_Cnt);
//
//		SetItem(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 150.0f, g_Player.pos.z), g_Player.rot, itemtype);
//
//		g_Cnt++;
//		if (g_Cnt>ITEMTYPE_MAX-1)
//		{
//			g_Cnt = 0;
//		}
//
//
//	}

}
//=============================
//キーボード/コントローラー入力検知処理
//=============================
int CheckInputMove2(void)
{
	//0:入力有り
	//-1:入力なし

	XINPUT_STATE joykeystate;
	//ショイパットの状態を取得
	DWORD dwResult = XInputGetState(0, &joykeystate);

	if (dwResult != ERROR_SUCCESS)
	{//Controllerなし
		if (GetkeyboardPress(DIK_A) == true)
		{//Aがおされた(左)
			return 0;
		}
		else if (GetkeyboardPress(DIK_D) == true)
		{//Dがおされた(右)
			return 0;
		}
		else if (GetkeyboardPress(DIK_W) == true)
		{//Wがおされた(上)
			return 0;
		}
		else if (GetkeyboardPress(DIK_S) == true)
		{//Sがおされた(下)
			return 0;
		}
		else
		{//入力なし
			return -1;
		}
	}
	else
	{//Controller有り

		//ここおそらくだめ

		if (GetkeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT , 0) == true || joykeystate.Gamepad.sThumbLX <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 * 0.5f))
		{//Aがおされた(左)
			return 0;
		}
		else if (GetkeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT , 0) == true || joykeystate.Gamepad.sThumbLX >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 * 0.5f))
		{//Dがおされた(右)
			return 0;
		}
		else if (GetkeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP , 0) == true || joykeystate.Gamepad.sThumbLY >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 * 0.5f))
		{//Wがおされた(上)
			return 0;
		}
		else if (GetkeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN , 0) == true || joykeystate.Gamepad.sThumbLY <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 * 0.5f))
		{//Sがおされた(下)
			return 0;
		}
		else
		{//入力なし
			return -1;
		}
	}
}

//=============================
//変換処理2D--------------------------めちゃ大事
//=============================
void ConversionPlayerRot2(float fRot, int nCnt)
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
	float rotDiff = fRot - g_Player.rot.y;

	// 差分が範囲外なら補正---------------------------------------------------------------近いうちちゃんと内容調べる
	if (fabsf(rotDiff) > D3DX_PI)
	{
		rotDiff = (rotDiff < 0) ? (rotDiff + 2 * D3DX_PI) : (rotDiff - 2 * D3DX_PI);
	}

	g_Player.rot.y += rotDiff * 0.1f;

	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= (2.0f * D3DX_PI);
	}
	else if (g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rot.y += (2.0f * D3DX_PI);
	}

}
//=============================
//変換処理3D--------------------------めちゃ大事
//=============================
D3DXVECTOR3 ConversionPlayerRot3(D3DXVECTOR3 fRot, int nCnt)
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
void LoadXfire_Player(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntPart = 0; nCntPart < g_Model.nMaxLoadPartsCnt; nCntPart++)
	{
		
		// ファイルの読み込み
		D3DXLoadMeshFromX(g_PlayerFileName[nCntPart][0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatModel[nCntPart],
			NULL,
			&dwNumMatModel[nCntPart],
			&g_pMeshModel[nCntPart]);

		// マテリアルデータへのポインタを取得
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pBuffMatModel[nCntPart]->GetBufferPointer();


		for (int i = 0; i < (int)dwNumMatModel[nCntPart]; i++)
		{
			if (pMat[i].pTextureFilename != nullptr)
			{
				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,pMat[i].pTextureFilename,&g_apTexture_1P[nCntPart][i]);
				
				
			}
		}
	}
	g_Player.bUse = true;
}

//===================================
//テキストからキャラの情報を読み込む処理----------------------------------------------------------------
//===================================
void LoadSet(void)
{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	FILE* pFile;//ファイルポインタを宣言


	char aString[MAX_WORD2];	//読み込む最大文字数

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


	pFile = fopen("data\\motion_PlayerModel.txt", "r");
 //	pFile = fopen("data\\motion_runningman.txt", "r");
//	pFile = fopen("data\\motionEnigma.txt", "r");



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
				fscanf(pFile, "%d", &g_Model.nMaxLoadPartsCnt);//モデル数格納

			}
			else if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
			{//各モデルのパーツのパスが来たら
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%s", &g_PlayerFileName[nEscapeCntModel][0]);//ファイルパス

				

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
						fscanf(pFile, "%d", &g_Model.nMaxPartsCnt);


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
								fscanf(pFile, "%d", &g_Model.ModelParts[nfirstEscapePartsCnt].INDEX);

							}
							else if (strcmp(&aString[0], "PARENT") == 0)
							{//親が来たら
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &g_Model.ModelParts[nfirstEscapePartsCnt].PEARENT);
							}
							else if (strcmp(&aString[0], "POS") == 0)
							{//POSが来たら
								fscanf(pFile, "%s", &aString[0]);

								fscanf(pFile, "%f %f %f", &g_Model.ModelParts[nfirstEscapePartsCnt].Pos.x, &g_Model.ModelParts[nfirstEscapePartsCnt].Pos.y, &g_Model.ModelParts[nfirstEscapePartsCnt].Pos.z);

								//保存
								g_Model.ModelParts[nfirstEscapePartsCnt].StartPos = g_Model.ModelParts[nfirstEscapePartsCnt].Pos;

							}
							else if (strcmp(&aString[0], "ROT") == 0)
							{//ROTが来たら
								fscanf(pFile, "%s", &aString[0]);

								fscanf(pFile, "%f %f %f", &g_Model.ModelParts[nfirstEscapePartsCnt].Rot.x, &g_Model.ModelParts[nfirstEscapePartsCnt].Rot.y, &g_Model.ModelParts[nfirstEscapePartsCnt].Rot.z);

								//保存
								g_Model.ModelParts[nfirstEscapePartsCnt].StartRot = g_Model.ModelParts[nfirstEscapePartsCnt].Rot;
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

						g_Model.Motion[nMotionCnt].Motiontype = nMotionCnt;
						nMotionCnt++;//モーションインクリメント

						if (g_Model.nMaxMotionCnt <= nMotionCnt)
						{
							g_Model.nMaxMotionCnt = nMotionCnt;//モーション数は最大のみ
						}

						KeyCnt = 0;//キー番号リセット

						break;
					}
					else if (strcmp(&aString[0], "LOOP") == 0)
					{//ループ数が来たら
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &g_Model.Motion[nMotionCnt].nLoop);
					}
					else if (strcmp(&aString[0], "NUM_KEY") == 0)//----------------最大キー数に応用
					{//キーの数が来たら
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &g_Model.Motion[nMotionCnt].nNumKey);
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
								fscanf(pFile, "%d", &g_Model.Motion[nMotionCnt].KeyData[KeyCnt].nSplitFrame);//-----------------------------------下記と同じ//わけないと、飛ばされたときに認識できない

							}
							else if (strcmp(&aString[0], "KEY") == 0)
							{//KEYが来たら

								while (1)
								{
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "FRAME") == 0)
									{//フレームの数が来たら
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%d", &g_Model.Motion[nMotionCnt].KeyData[KeyCnt].nSplitFrame);///------------------------上記と同じ

									}

									else if (strcmp(&aString[0], "END_KEY") == 0)
									{//エンドKEY

										nKeyPartsCnt++;//パーツインクリメント
										break;
									}
									else if (strcmp(&aString[0], "POS") == 0)
									{//POS数が来たら
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%f %f %f", &g_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.x, &g_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.y, &g_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.z);///------------------------Keyごとかつパーツごとで変動

									}
									else if (strcmp(&aString[0], "ROT") == 0)
									{//ROT数が来たら
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%f %f %f", &g_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.x, &g_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.y, &g_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.z);///------------------------Keyごとかつパーツごとで変動
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
void LowerBodyMotion(void)
{
	if (g_Player.NowMotionDOWN != g_Player.OldMotionDOWN)
	{//前回のモーションと違う時
	//-------------------------------リセット動作
		g_Player.NowKeyCntDOWN = 0;
		g_Player.NowFrameCntDOWN = 0;
		g_Player.EscapeMotion = g_Player.NowMotionDOWN;
		g_Player.BrendCnt = 0;
		for (int i = 0; i < MAX_PARTS; i++)
		{//リセット

			g_Model.ModelParts[i].calculationExecution = false;
			g_Model.ModelParts[i].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model.ModelParts[i].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Player.MotionLoopStop = false;
		}
		g_Player.MotionBrend = true;
	}




	if (g_Player.MotionBrend == true)
	{//モーションブレンド--無し


#if 0
		for (int nCntParts = 0; nCntParts < g_Model.nMaxPartsCnt; nCntParts++)
		{//パーツ分回る

				//ROT系
			if (g_Model.ModelParts[nCntParts].calculationExecution == false)
			{
				//CorrectionPos,CorrectionRotはあくまで、OFFSETをStart地点とした補正量なので、
				D3DXVECTOR3 TargetRot;
				TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				TargetRot = g_Model.ModelParts[nCntParts].StartRot + g_Model.Motion[g_Player.NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionRot;

				g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionPlayerRot3(TargetRot - g_Model.ModelParts[nCntParts].Rot, 0));

				g_Model.ModelParts[nCntParts].calculationExecution = true;
			}

			g_Model.ModelParts[nCntParts].Rot += g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove;

			//POS系
			//--------------------------------------------------------------------------------
			if (g_Model.ModelParts[nCntParts].PEARENT == -1)
			{//自分がすべての親の時
				D3DXVECTOR3 TargetPos;
				TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				//初期位置から見た地点を補正した、目標地点の算出
				TargetPos = g_Model.ModelParts[nCntParts].StartPos + g_Model.Motion[g_Player.NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionPos;

				//現在の位置から、上で算出した目標地点までの差分計算
				g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Model.ModelParts[nCntParts].Pos);

				//POSの更新
				g_Model.ModelParts[nCntParts].Pos += g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove;
				//------------------------------------------------------------------------------------
			}
		}

		g_Player.MotionBrend = false;

		g_Player.NowKeyCntDOWN++;//キーを進める

		for (int nCntParts = 0; nCntParts < g_Model.nMaxPartsCnt; nCntParts++)
		{//パーツ分回る
			g_Model.ModelParts[nCntParts].calculationExecution = false;
			g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		}


#else // 1

		if (g_Player.BrendCnt < BRENDFLAME)
		{
			for (int nCntParts = 0; nCntParts < g_Model.nMaxPartsCnt; nCntParts++)
			{//パーツ分回る

					//ROT系
				if (g_Model.ModelParts[nCntParts].calculationExecution == false)
				{
					//CorrectionPos,CorrectionRotはあくまで、OFFSETをStart地点とした補正量なので、
					D3DXVECTOR3 TargetRot;
					TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					TargetRot = g_Model.ModelParts[nCntParts].StartRot + g_Model.Motion[g_Player.NowMotionDOWN].KeyData[1].PartsData[nCntParts].CorrectionRot;

					g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionPlayerRot3(TargetRot - g_Model.ModelParts[nCntParts].Rot, 0) / BRENDFLAME);

					g_Model.ModelParts[nCntParts].calculationExecution = true;
				}

				g_Model.ModelParts[nCntParts].Rot += g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove;

				//POS系
				//--------------------------------------------------------------------------------
				if (g_Model.ModelParts[nCntParts].PEARENT == -1)
				{//自分がすべての親の時
					D3DXVECTOR3 TargetPos;
					TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					//初期位置から見た地点を補正した、目標地点の算出
					TargetPos = g_Model.ModelParts[nCntParts].StartPos + g_Model.Motion[g_Player.NowMotionDOWN].KeyData[1].PartsData[nCntParts].CorrectionPos;

					//現在の位置から、上で算出した目標地点までの差分計算
					g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Model.ModelParts[nCntParts].Pos) / BRENDFLAME;

					//POSの更新
					g_Model.ModelParts[nCntParts].Pos += g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove;
					//------------------------------------------------------------------------------------
				}
			}

		}
		g_Player.BrendCnt++;

		if (g_Player.BrendCnt >= BRENDFLAME)
		{
			g_Player.BrendCnt = 0;

			g_Player.MotionBrend = false;

			g_Player.NowKeyCntDOWN++;//キーを進める

			for (int nCntParts = 0; nCntParts < g_Model.nMaxPartsCnt; nCntParts++)
			{//パーツ分回る
				g_Model.ModelParts[nCntParts].calculationExecution = false;
				g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			}
		}
#endif
	}
	else
	{

		// 本動作------------------------------------------------------------------------------------------------------------------
		if (g_Player.MotionLoopStop == false)
		{
			if (g_Player.NowFrameCntDOWN < g_Model.Motion[g_Player.NowMotionDOWN].KeyData[g_Player.NowKeyCntDOWN /*- 1*/].nSplitFrame)
			{//分割フレームの分回る
				if (g_Player.NowKeyCntDOWN < g_Model.Motion[g_Player.NowMotionDOWN].nNumKey)
				{//キーの分回る

					for (int nCntParts = 0; nCntParts < g_Model.nMaxPartsCnt; nCntParts++)
					{//パーツ分回る
					//	if (nCntParts == 0 || (nCntParts >= 9 && nCntParts <= 14))
					//	{
							//ROT系
						if (g_Model.ModelParts[nCntParts].calculationExecution == false)
						{
							//CorrectionPos,CorrectionRotはあくまで、OFFSETをStart地点とした補正量なので、
							D3DXVECTOR3 TargetRot;
							TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

							if (g_Player.NowKeyCntDOWN != g_Model.Motion[g_Player.NowMotionDOWN].nNumKey - 1)
							{//最後キーじゃない
								TargetRot = g_Model.ModelParts[nCntParts].StartRot + g_Model.Motion[g_Player.NowMotionDOWN].KeyData[g_Player.NowKeyCntDOWN + 1].PartsData[nCntParts].CorrectionRot;
							}
							else if (g_Player.NowKeyCntDOWN == g_Model.Motion[g_Player.NowMotionDOWN].nNumKey - 1)
							{//最後キーのとき
								TargetRot = g_Model.ModelParts[nCntParts].StartRot + g_Model.Motion[g_Player.NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionRot;
							}
							g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionPlayerRot3(TargetRot - g_Model.ModelParts[nCntParts].Rot, 0)) / g_Model.Motion[g_Player.NowMotionDOWN].KeyData[g_Player.NowKeyCntDOWN].nSplitFrame;

							g_Model.ModelParts[nCntParts].calculationExecution = true;
						}

						g_Model.ModelParts[nCntParts].Rot += g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove;

						//POS系
						//--------------------------------------------------------------------------------
						if (g_Model.ModelParts[nCntParts].PEARENT == -1)
						{//自分がすべての親の時
							D3DXVECTOR3 TargetPos;
							TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
							if (g_Player.NowKeyCntDOWN != g_Model.Motion[g_Player.NowMotionDOWN].nNumKey - 1)
							{//最後キーじゃない
							//初期位置から見た地点を補正した、目標地点の算出
								TargetPos = g_Model.ModelParts[nCntParts].StartPos + g_Model.Motion[g_Player.NowMotionDOWN].KeyData[g_Player.NowKeyCntDOWN + 1].PartsData[nCntParts].CorrectionPos;
							}
							else if (g_Player.NowKeyCntDOWN == g_Model.Motion[g_Player.NowMotionDOWN].nNumKey - 1)
							{//最後キーのとき
							//初期位置から見た地点を補正した、目標地点の算出
								TargetPos = g_Model.ModelParts[nCntParts].StartPos + g_Model.Motion[g_Player.NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionPos;
							}
							//現在の位置から、上で算出した目標地点までの差分計算
							g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Model.ModelParts[nCntParts].Pos) / g_Model.Motion[g_Player.NowMotionDOWN].KeyData[g_Player.NowKeyCntDOWN].nSplitFrame;

							//POSの更新
							g_Model.ModelParts[nCntParts].Pos += g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove;
							//------------------------------------------------------------------------------------
						}
						//	}
					}
				}
				g_Player.NowFrameCntDOWN++;//フレーム進める
			}
			else
			{//フレーム数超えた
				g_Player.NowFrameCntDOWN = 0;//フレームリセット

				g_Player.NowKeyCntDOWN++;//キーを進める

				for (int i = 0; i < MAX_PARTS; i++)
				{//リセット
					g_Model.ModelParts[i].calculationExecution = false;
				}

				if (g_Player.NowKeyCntDOWN == g_Model.Motion[g_Player.NowMotionDOWN].nNumKey)
				{//キーが、最大キーを超えた時

					g_Player.NowFrameCntDOWN = 0;//フレームリセット
					g_Player.NowKeyCntDOWN = 0;//キーリセット

					if (g_Model.Motion[g_Player.NowMotionDOWN].nLoop == 0)
					{//ループしない
						if (g_Player.NowMotionDOWN == MOTIONTYPE_1P_JUMP)
						{
							g_Player.MotionLoopStop = true;
						}
						else
						{//飛翔以外
							//待機にする
							g_Player.NowMotionDOWN = MOTIONTYPE_1P_STANDBY;//待機状態に戻す
							//ブレンド挟む
							if (g_Player.MotionBrend == false)
							{
								g_Player.NowKeyCntDOWN = 0;
								g_Player.NowFrameCntDOWN = 0;
								g_Player.EscapeMotion = g_Player.NowMotionDOWN;
								g_Player.BrendCnt = 0;
								for (int i = 0; i < MAX_PARTS; i++)
								{//リセット

									g_Model.ModelParts[i].calculationExecution = false;
									g_Model.ModelParts[i].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
									g_Model.ModelParts[i].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
									g_Player.MotionLoopStop = false;

									g_Player.MotionBrend = true;

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

//
////===================================
////上半身モーション//胸
////===================================
//void UpperBodyMotion(void)
//{
//
//#if 0
//	//上下別モーション
//
//	if (g_Player.NowMotionUP != g_Player.OldMotionUP)
//	{//前回のモーションと違う時
//	//-------------------------------リセット動作
//		g_Player.NowKeyCntUP = 0;
//		g_Player.NowFrameCntUP = 0;
//		for (int i = 0; i < MAX_PARTS; i++)
//		{//リセット
//			g_Model.ModelParts[i].calculationExecution = false;
//			g_Model.ModelParts[i].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			g_Model.ModelParts[i].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			g_Player.MotionLoopStop = false;
//		}
//	}
//
//	// 本動作------------------------------------------------------------------------------------------------------------------
//		//1-8,15が上半身
//		//1は胸----------敵の方向に向けるためうごかさない
//		//0は腰
//
//		//345を除外(右手)
//
//	if (g_Player.NowMotionUP != MOTIONTYPE_1P_ATTACK)
//	{
//		g_Player.NowMotionUP = g_Player.NowMotionDOWN;
//
//		if (g_Player.NowMotionDOWN != MOTIONTYPE_1P_MOVE)
//		{
//			g_Player.NowMotionUP = MOTIONTYPE_1P_STANDBY;
//		}
//	}
//
//
//	if (g_Player.NowFrameCntUP < g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].nSplitFrame)
//	{//分割フレームの分回る
//		if (g_Player.NowKeyCntUP < g_Model.Motion[g_Player.NowMotionUP].nNumKey)
//		{//キーの分回る
//
//			for (int nCntParts = 0; nCntParts < g_Model.nMaxPartsCnt; nCntParts++)
//			{//パーツ分回る
//
//				if (nCntParts == 2 || nCntParts == 15 || nCntParts == 16 || (nCntParts >= 6 && nCntParts <= 8) || (nCntParts >= 3 && nCntParts <= 5))
//				{//下半身、腰、右手を除外----------------------------------------------------------------------------後に右手左手を分ける？？
//
//
//					//ROT系
//					if (g_Model.ModelParts[nCntParts].calculationExecution == false)
//					{
//						//CorrectionPos,CorrectionRotはあくまで、OFFSETをStart地点とした補正量なので、
//						D3DXVECTOR3 TargetRot;
//						TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//						TargetRot = g_Model.ModelParts[nCntParts].StartRot + g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].PartsData[nCntParts].CorrectionRot;
//
//						g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionPlayerRot3(TargetRot - g_Model.ModelParts[nCntParts].Rot, 0)) / g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].nSplitFrame;
//
//						g_Model.ModelParts[nCntParts].calculationExecution = true;
//					}
//
//					g_Model.ModelParts[nCntParts].Rot += g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove;
//
//					//POS系
//					//--------------------------------------------------------------------------------
//					if (g_Model.ModelParts[nCntParts].PEARENT == -1)
//					{//自分がすべての親の時
//						D3DXVECTOR3 TargetPos;
//						TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//						//初期位置から見た地点を補正した、目標地点の算出
//						TargetPos = g_Model.ModelParts[nCntParts].StartPos + g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].PartsData[nCntParts].CorrectionPos;
//
//						//現在の位置から、上で算出した目標地点までの差分計算
//						g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Model.ModelParts[nCntParts].Pos) / g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].nSplitFrame;
//
//						//POSの更新
//						g_Model.ModelParts[nCntParts].Pos += g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove;
//						//------------------------------------------------------------------------------------
//					}
//				}
//			}
//
//
//			//	//仮射撃
//			//if (g_Player.NowMotionUP == MOTIONTYPE_1P_ATTACK)
//			//{
//			//	for (int i = 0; i < 2; i++)
//			//	{
//			//		if (g_Player.NowKeyCntUP == 0 && g_Player.NowFrameCntUP == g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].nSplitFrame - 1)
//			//		{
//			//		//	SetBullet(D3DXVECTOR3(mtxWorldBullet[i]._41, mtxWorldBullet[i]._42, mtxWorldBullet[i]._43), BulletMoveVec[i], 0, 0, BULLETTYPE_Player);
//			//		//	SetEffect(D3DXVECTOR3(mtxWorldBullet[i]._41, mtxWorldBullet[i]._42, mtxWorldBullet[i]._43), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 10, 2, EFECTTYPE_Boost);
//			//		}
//			//	}
//			//}
//		}
//		g_Player.NowFrameCntUP++;//フレーム進める
//	}
//	else
//	{//フレーム数超えた
//		g_Player.NowFrameCntUP = 0;//フレームリセット
//
//		g_Player.NowKeyCntUP++;//キーを進める
//
//		for (int i = 0; i < MAX_PARTS; i++)
//		{//リセット
//			g_Model.ModelParts[i].calculationExecution = false;
//		}
//
//		if (g_Player.NowKeyCntUP == g_Model.Motion[g_Player.NowMotionUP].nNumKey)
//		{//キーが、最大キーを超えた時
//
//			g_Player.NowFrameCntUP = 0;//フレームリセット
//			g_Player.NowKeyCntUP = 0;//キーリセット
//
//			if (g_Model.Motion[g_Player.NowMotionUP].nLoop == 0)
//			{//ループしない
//				g_Player.NowMotionUP = MOTIONTYPE_1P_STANDBY;//待機状態に戻す
//			}
//		}
//	}
//}
////------------------------------------------------------------ここまで
//
//#else
//
//	//一旦統一モーション
//
//	g_Player.OldMotionUP = g_Player.OldMotionDOWN;
//	g_Player.NowMotionUP = g_Player.NowMotionDOWN;
//
//
//	if (g_Player.NowMotionUP != g_Player.OldMotionUP)
//	{//前回のモーションと違う時
//	//-------------------------------リセット動作
//		g_Player.NowKeyCntUP = 0;
//		g_Player.NowFrameCntUP = 0;
//		for (int i = 0; i < MAX_PARTS; i++)
//		{//リセット
//			g_Model.ModelParts[i].calculationExecution = false;
//			g_Model.ModelParts[i].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			g_Model.ModelParts[i].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			g_Player.MotionLoopStop = false;
//		}
//	}
//
//	// 本動作------------------------------------------------------------------------------------------------------------------
//		//1-8,15が上半身
//		//1は胸----------敵の方向に向けるためうごかさない
//		//0は腰
//
//		//345を除外(右手)
//
//	if (g_Player.NowMotionUP != MOTIONTYPE_1P_ATTACK)
//	{
//		g_Player.NowMotionUP = g_Player.NowMotionDOWN;
//
//		if (g_Player.NowMotionDOWN != MOTIONTYPE_1P_MOVE)
//		{
//			g_Player.NowMotionUP = MOTIONTYPE_1P_STANDBY;
//		}
//	}
//
//
//	if (g_Player.NowFrameCntUP < g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].nSplitFrame)
//	{//分割フレームの分回る
//		if (g_Player.NowKeyCntUP < g_Model.Motion[g_Player.NowMotionUP].nNumKey)
//		{//キーの分回る
//
//			for (int nCntParts = 0; nCntParts < g_Model.nMaxPartsCnt; nCntParts++)
//			{//パーツ分回る
//
//				if (nCntParts == 2 || nCntParts == 15 || nCntParts == 16 || (nCntParts >= 6 && nCntParts <= 8) || (nCntParts >= 3 && nCntParts <= 5))
//				{//下半身
//
//					//ROT系
//					if (g_Model.ModelParts[nCntParts].calculationExecution == false)
//					{
//						//CorrectionPos,CorrectionRotはあくまで、OFFSETをStart地点とした補正量なので、
//						D3DXVECTOR3 TargetRot;
//						TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//						TargetRot = g_Model.ModelParts[nCntParts].StartRot + g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].PartsData[nCntParts].CorrectionRot;
//
//						g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionPlayerRot3(TargetRot - g_Model.ModelParts[nCntParts].Rot, 0)) / g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].nSplitFrame;
//
//						g_Model.ModelParts[nCntParts].calculationExecution = true;
//					}
//
//					g_Model.ModelParts[nCntParts].Rot += g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove;
//
//					//POS系
//					//--------------------------------------------------------------------------------
//					if (g_Model.ModelParts[nCntParts].PEARENT == -1)
//					{//自分がすべての親の時
//						D3DXVECTOR3 TargetPos;
//						TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//						//初期位置から見た地点を補正した、目標地点の算出
//						TargetPos = g_Model.ModelParts[nCntParts].StartPos + g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].PartsData[nCntParts].CorrectionPos;
//
//						//現在の位置から、上で算出した目標地点までの差分計算
//						g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Model.ModelParts[nCntParts].Pos) / g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].nSplitFrame;
//
//						//POSの更新
//						g_Model.ModelParts[nCntParts].Pos += g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove;
//						//------------------------------------------------------------------------------------
//					}
//				}
//			}
//
//
//			//	//仮射撃
//			//if (g_Player.NowMotionUP == MOTIONTYPE_1P_ATTACK)
//			//{
//			//	for (int i = 0; i < 2; i++)
//			//	{
//			//		if (g_Player.NowKeyCntUP == 0 && g_Player.NowFrameCntUP == g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].nSplitFrame - 1)
//			//		{
//			//		//	SetBullet(D3DXVECTOR3(mtxWorldBullet[i]._41, mtxWorldBullet[i]._42, mtxWorldBullet[i]._43), BulletMoveVec[i], 0, 0, BULLETTYPE_Player);
//			//		//	SetEffect(D3DXVECTOR3(mtxWorldBullet[i]._41, mtxWorldBullet[i]._42, mtxWorldBullet[i]._43), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 10, 2, EFECTTYPE_Boost);
//			//		}
//			//	}
//			//}
//		}
//		g_Player.NowFrameCntUP++;//フレーム進める
//	}
//	else
//	{//フレーム数超えた
//		g_Player.NowFrameCntUP = 0;//フレームリセット
//
//		g_Player.NowKeyCntUP++;//キーを進める
//
//		for (int i = 0; i < MAX_PARTS; i++)
//		{//リセット
//			g_Model.ModelParts[i].calculationExecution = false;
//		}
//
//		if (g_Player.NowKeyCntUP == g_Model.Motion[g_Player.NowMotionUP].nNumKey)
//		{//キーが、最大キーを超えた時
//
//			g_Player.NowFrameCntUP = 0;//フレームリセット
//			g_Player.NowKeyCntUP = 0;//キーリセット
//
//			if (g_Model.Motion[g_Player.NowMotionUP].nLoop == 0)
//			{//ループしない
//				g_Player.NowMotionUP = MOTIONTYPE_1P_STANDBY;//待機状態に戻す
//			}
//		}
//	}
//
//
//}
////------------------------------------------------------------ここまで
//#endif // 0
//



//===================================
//モデル取得処理
//===================================
MODEL* GetModel(void)
{
	return &g_Model;
}

////===================================
////被弾処理
////===================================
//void HitPlayer(void)
//{
//	HP* pHP;
//	pHP = GetHP();
//
//
//	pHP[HPTYPE_PLAYER].HPstate = HPSTATE_DAMAGE;
//	pHP[HPTYPE_PLAYER].nCounterState = 3;
//
//}
