//============================================================================================
//
//ゲームを制御する処理[game.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "game.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "pause.h"
#include "eyetrap.h"
#include "camera.h"
#include "light.h"
#include "stage.h"
#include "keyinfo.h"

#include "player.h"
#include "player2.h"
#include "enemy.h"
#include "enemy_view.h"
#include "moneybox.h"
#include "moneyboxdigit.h"
#include "bathgimmick.h"
#include "steam.h"
#include "password.h"
#include "TV.h"

#include "shadow.h"
#include "meshfield.h"
//#include "sky.h"
#include "line.h"
#include "transfergate.h"
#include "gamefade.h"
#include "limittime.h"
#include "screenui.h"
#include "speechbubble.h"
#include "text.h"
#include "gauge.h"
#include "Billboard.h"

#include"DebugModel.h"

#include "item.h"
#include "particle.h"
#include"itemUI.h"
#include "simple_motion_model.h"
#include "advanced_motion_model.h"//--テクスチャだめ
#include "hitcollision_mistake_prevention.h"
#include "map.h"

//仮
#include "Model_Set_Save_Lode.h"

#include <stdio.h>//ヘッダーファイルをインクルード
#include <string.h>//文字列を扱う変数

	//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureGame = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGame = NULL;//頂点バッファへのポリゴン
ModelInfo g_aModelInfo[MAX_MODEL];
WallInfo g_aWallInfo[MAX_WALL];
FieldInfo g_aFieldInfo[MAX_FIELD];
int g_nUseModel; //モデルの使用数読み込み
int g_nUseWall; //壁の使用数読み込み
int g_nUseField; //床の使用数読み込み
int g_nHaveKey = 0; //鍵保有数

//制限時間代入
int g_EndFlame = ENDFRAME / 60;


//playerを更新してもいいか
bool g_PlayerUpdateOk = true;
bool g_Player2UpdateOk = true;

int g_nLoopCnt = 0;

int g_EndGameFrame = GAME_END_DELAY;//ゲーム終了まで3秒

bool g_bPause = false;
bool g_ClearFlag = false;
bool g_MoneyboxPlayer = false; //どっちのプレイヤーが操作してるか false:1P,true2P
bool g_bClearMoneybox = false;
bool g_bLever1 = false;
bool g_bLever2 = false;
bool g_bSoup = false;
bool g_bDesk = false;
bool g_bTutorialLeverRed = false;
bool g_bTutorialLeverBlue = false;

//ゲームループを一度でもしたか
bool GameLoopSave = false;

bool SetEscapeGate = false;//セットしたかどうか


//転移先初期値
int g_PlayerTransNum = 3;
int g_Player2TransNum = 3;

int nKitchen = 0;
int nDesk = 0;

bool g_MoneyOpen = false;//金庫あいたか

//=============================
//ゲーム画面の初期化処理
//=============================
void InitGame(void)
{
	g_MoneyOpen = false;
	g_PlayerUpdateOk = true;
	g_Player2UpdateOk = true;

	g_PlayerTransNum = 3;
	g_Player2TransNum = 3;

	g_EndGameFrame = GAME_END_DELAY;//クリアからゲーム終了までの余韻

	g_nLoopCnt = 0;//ゲームループリセット

	g_nHaveKey = 0; //鍵保有数リセット

	nKitchen = 0;

	g_bPause = false;//ポーズ解除

	g_MoneyboxPlayer = false; //ギミック起動解除

	g_bClearMoneybox = false; //ギミッククリアしてないにする

	g_bSoup = false; //スープがスポーンしたら

	g_bDesk = false; //デスクから鍵がスポーンしたか（仮）

	g_ClearFlag = false;//クリアしてないにする

	g_bLever1 = false; //レバーオフ
	g_bLever2 = false; //レバーオフ
	g_bTutorialLeverRed = false;
	g_bTutorialLeverBlue = false;
	SetEscapeGate = false;


	InitPause();

	InitLight();
	InitCamera();

	InitItem();
	InitItem_UI();
	InitBill();

	InitModel();
	LoadModel();
	InitStage();
	InitAdvancedModel();

	InitShadow();
	InitTV();
	InitMoneybox();
	InitMoneyboxDigit();
	InitPassword();
	InitBathGimmick();
	InitSteam();
	InitGauge();

	InitPlayer();
	InitPlayer_2P();
	InitEnemy_View();
	InitEnemy();

//	InitSky();

	InitSpeechBubble();
	InitTransferGate();
	InitCollision_Pre();
	InitActionZone();
	InitGameFade();
	InitScreenUI();
	InitKeyinfo();

	InitParticle();
	InitSimpleModel();
	InitEyeTrap();
	InitMap();
	InitMeshField();

	//Button

#if _DEBUG

	if (GameLoopSave == false)
	{
	}

	InitLine();

#endif

	InitModel_SSL();
	Model_DebugLoad();
	Model_DebugSet();


#if _DEBUG
	//新規モデル置き場
	NewSet_Debug_Model();
#endif



	//-------------------あたり判定再計算
	ExclusionCollision();

#if _DEBUG

	//デバッグモデル
	InitDebugModel();
#endif

	//----------------------------制限時間
	NowTime* pNowTime;
	pNowTime = GetNowTime();
	pNowTime->NowTime = g_EndFlame;
	InitLimitTime();
	//-----------------------------


	TRANSFERGATE* pTransferGate;
	pTransferGate = GetTransferGate();

	for (int i = 0; i < MAXGATE; i++)
	{
		if (pTransferGate[i].bUse == true)
		{
			if (i == 9)
			{
				continue;
			}
			SetActionZone(D3DXVECTOR3(pTransferGate[i].pos.x, pTransferGate[i].pos.y, pTransferGate[i].pos.z), 100, ACTION_TYPE_ESCAPE, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.4f));
		}
	}

	//風呂Button
	SetModel(D3DXVECTOR3(-395.0f, 50.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 1.57f), MODELTYPE_BUTTON);


	SetActionZone(D3DXVECTOR3(-395.0f, 50.0f, -40.0f), 100, ACTION_TYPE_PURIFICATION, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.4f));

	SetGauge(D3DXVECTOR3(230.0f, 470.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8.0f, 180, 200.0f, GAUGETYPE_FRAME_1P);
	SetGauge(D3DXVECTOR3(860.0f, 470.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8.0f, 180, 200.0f, GAUGETYPE_FRAME_2P);

	SetGauge(D3DXVECTOR3(230.0f, 470.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 6.0f, 180, 200.0f, GAUGETYPE_MAINBODY_1P);
	SetGauge(D3DXVECTOR3(860.0f, 470.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 6.0f, 180, 200.0f, GAUGETYPE_MAINBODY_2P);



	//確定緑風呂
	MAPOBJECT* pMapObject;
	pMapObject = GetMapObject();

	for (int i = 0; i < MAX_MODEL; i++)
	{
		if (pMapObject[i].bUse == true)
		{
			if (pMapObject[i].nType == MODELTYPE_BATH)
			{
				SetBathWater(D3DXVECTOR3(pMapObject[i].pos.x, pMapObject[i].pos.y + 40.0f, pMapObject[i].pos.z)
					, D3DXVECTOR3(pMapObject[i].rot.x, D3DX_PI * 0.5f, pMapObject[i].rot.z)
					, BATHWATER_WIDE
					, BATHWATER_DEPTH
					, GREEN_WATER);
			}
		}
	}

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (pMapObject[nCnt].bUse == true)
		{
			if (pMapObject[nCnt].nType == MODELTYPE_STAIRS)
			{
				pMapObject[nCnt].bCollision = false;
			}
			if (pMapObject[nCnt].nType == MODELTYPE_BUTTON)
			{
				pMapObject[nCnt].bCollision = false;
			}
		}
	}

	//乱数の種を設定
	srand((unsigned int)time(0));
}
//=============================
//ゲーム画面の終了処理
//=============================
void UninitGame(void)
{
	//振動ストップ
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		VibrationLeft(0, nCnt);
		VibrationRight(0, nCnt);
	}

	//	UninitPause();
	//
	//	UninitLight();
	//	UninitCamera();
	//	UninitModel();
	//	UninitStage();
	//	UninitPlayer();
	//	UninitPlayer_2P();
	//	UninitShadow();
	//	UninitMoneybox();
	//	UninitMoneyboxDigit();
	//	UninitPassword();
	//	UninitBathGimmick();
	//	UninitSteam();
	//
	//	UninitSky();
	//
	//	UninitTransferGate();
	//	UninitActionZone();
	//	UninitGameFade();
	//	UninitLimitTime();
	//	UninitScreenUI();
	//	UninitSpeechBubble();
	//	UninitParticle();
	//	UninitItem();
	//	UninitItem_UI();
	//
	//	UninitMeshField();
	//	UninitSimpleModel();
	//	UninitAdvancedModel();
	//	UninitCollision_Pre();
	//	UninitEyeTrap();
	//	UninitMap();
	//#if _DEBUG
	//
	//	UninitLine();
	//	UninitDebugModel();
	//#endif

	UninitLimitTime();

#if _DEBUG
	//デバッグモデル
	UninitDebugModel();//
#endif



#if _DEBUG
	UninitLine();//


#endif
	UninitMeshField();//
	UninitMap();//
	UninitEyeTrap();//
	UninitSimpleModel();//
	UninitParticle();//

	UninitScreenUI();//
	UninitGameFade();//
	UninitActionZone();//
	UninitCollision_Pre();//
	UninitTransferGate();//
	UninitSpeechBubble();//
//	UninitSky();//
	UninitPlayer_2P();//
	UninitPlayer();//
	UninitEnemy();
	UninitEnemy_View();
	UninitSteam();//
	UninitGauge();	//
	UninitBathGimmick();//
	UninitTV();
	UninitPassword();//
	UninitMoneyboxDigit();//
	UninitMoneybox();//
	UninitShadow();//
	UninitAdvancedModel();//
	UninitStage();//
	LoadModel();//
	UninitModel();//
	UninitItem_UI();//
	UninitKeyinfo();
	UninitItem();//
	UninitBill();
	UninitCamera();//
	UninitLight();//

	UninitPause();//--------------------















}
//=============================
//ゲーム画面の更新処理
//=============================
void UpdateGame(void)
{
	//制限時間の取得
	NowTime* pNowtime;

	//現在の残り時間を取得
	pNowtime = GetNowTime();

	g_bClearMoneybox = GetClearMoneyBox(); //金庫クリア確認

	Player* pPlayer;
	pPlayer = GetPlayer();

	Player_2P* pPlayer2;
	pPlayer2 = GetPlayer_2P();

	ScreenState* pScreenState = GetScreenState();


	bool bPlayer1inOK = false;
	bool bPlayer2inOK = false;

	bool bPlayer1inOK_map = false;
	bool bPlayer2inOK_map = false;

	if (g_nHaveKey >= 3)
	{
		if (SetEscapeGate == false)
		{
			SetModel(D3DXVECTOR3(2980.0f, 103.0f, -2525.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODELTYPE_ESCAPEDOOR);
			SetTransferGate(D3DXVECTOR3(2980.0f, 104.0f, -2470.0f), D3DXVECTOR3(-120.0f, 0.0f, -120.0f), D3DXVECTOR3(120.0f, 100.0f, 120.0f), TRANSGATE_NUM, CLEAR_NUM, TRANS_ANGLE_CLEAR, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f), true, true);

			SetActionZone(D3DXVECTOR3(2980.0f, 103.0f, -2470.0f), 120, ACTION_TYPE_GAMECLEAR, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.4f));
			SetKeyinfo(SPAWNPLACE_GATE, -1);
			SetEscapeGate = true;
		}
	}



	if (GetkeyboardTrigger(DIK_Q) == true)
	{//Qキー(ポーズ)が押された
		SetModel(pPlayer->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_KEY1);

		SetModel(pPlayer->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_KEY2);

		SetModel(pPlayer->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_KEY3);
	}

	if (GetkeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START, 0) == true || GetJoypadTrigger(JOYKEY_START, 1) == true)
	{//Pキー(ポーズ)が押された
		PlaySound(SOUND_LABEL_SE_PAUSE);
		g_bPause = g_bPause ? false : true;
	}
	if (GetJoypadTrigger(JOYKEY_B, 0) == true || GetJoypadTrigger(JOYKEY_B, 1) == true)
	{//Pキー(ポーズ)が押された
		g_bPause = false;
	}

	if (g_bPause == false)
	{//ポーズ中でなければ

		SubLimitTime();
		UpdateLimitTime();

		if (GetkeyboardPress(DIK_F5) == true)//トリガー
		{//F5が押された(デバッグ用)
			if (GameLoopSave == false)
			{
#if _DEBUG
				MAPOBJECT* pMapObject;
				pMapObject = GetMapObject();

				for (int i = 0; i < MAX_MODEL; i++)
				{
					if (pMapObject[i].bUse == true)
					{
						if (pMapObject[i].nType == MODELTYPE_ESCAPEDOOR)
						{
							pMapObject[i].bUse = false;//とりあえず
						}
					}
				}

				Model_DebugSave();//-----------------------------------------------------//SetModelを保存
				GameLoopSave = true;
#endif
			}

		}
		MODE pOldMode = GetOldMode();

		if (pOldMode == MODE_TUTORIAL)
		{
			if (g_nHaveKey == 3)
			{
				SetFade(MODE_MENU);
			}
		}
		if (GetkeyboardPress(DIK_F1) == true)//トリガー
		{//F1が押された(デバッグ用)

#if _DEBUG
	//		DeleteCoveredModel();
#endif
		}

		if (g_ClearFlag == true)
		{
			if (g_EndGameFrame > 0)
			{//Clear余韻用
				g_EndGameFrame--;
			}
			else
			{//余韻がたった
				GameClearFragOn();//Clearフラグ立てる
				//モード設定(フェードの後リザルト画面に移行)
				SetFade(MODE_RESULT);
			}
		}
		//--------------------------------------------------------------------------------クリア、敗北条件ここまで

//		g_nLoopCnt++;//出現タイミングで使用

		UpdateGameFade();

//		UpdateSky();

		UpdateLight();
		UpdateCamera();//カメラ
		UpdateModel();
		UpdateAdvancedModel();

		UpdateStage();
#if _DEBUG

#endif
		UpdateMeshField();
		UpdateItem();
		UpdateBill();

		if (pNowtime->NowTime < 0)
		{//時間切れ
			if (g_EndGameFrame > 0)
			{//Clear余韻用
				g_EndGameFrame--;
			}
			else
			{//余韻がたった
			 //モード設定(フェードの後リザルト画面に移行)
				SetFade(MODE_RESULT);
			}
		}
		else
		{
			if ((pPlayer->bTvGimmick == true || pPlayer2->bTvGimmick == true))
			{
				UpdateTV();
			}
			if (g_PlayerUpdateOk == true)
			{
				UpdatePlayer();
			}
			if (g_Player2UpdateOk == true)
			{
				UpdatePlayer_2P();
			}

			UpdateEnemy_View();
			UpdateEnemy();
		}

		//--------------------プレイヤー

		//-------現在アイテムの十字選択を無効化させるのに使用
		if (pPlayer->bMoneyBoxGimmick != true && pPlayer->bTvGimmick != true)
		{            //ギミックを操作していたらプレイヤーを止める(仮) ※ギミック中用のモーション出来たらそれに切り替え
			bPlayer1inOK = true;
			bPlayer1inOK_map = true;
		}
		if (pPlayer2->bMoneyBoxGimmick != true && pPlayer2->bTvGimmick != true)
		{//ギミックを操作していたらプレイヤーを止める(仮) ※ギミック中用のモーション出来たらそれに切り替え
			bPlayer2inOK = true;
			bPlayer2inOK_map = true;
		}

		//player停止時
		if (g_PlayerUpdateOk == false)
		{
			bPlayer1inOK = false;
		}
		if (g_Player2UpdateOk == false)
		{
			bPlayer2inOK = false;
		}


		//--------------------
		UpdateItem_UI(bPlayer1inOK, bPlayer2inOK);//入力受付可能かどうか
		UpdateKeyinfo();

		UpdateMap(bPlayer1inOK_map, bPlayer2inOK_map);//描画可能かどうか

		UpdateSimpleModel();


		if ((pPlayer->bMoneyBoxGimmick == true || pPlayer2->bMoneyBoxGimmick == true))
		{

			SetMonetbox(g_MoneyboxPlayer);//----------------------------------------------------------------------------------------------------------------------------------------------------------怪しい

			if (g_bClearMoneybox == false)
			{
				UpdateMoneybox();
				UpdateMoneyboxDigit();
				UpdatePassword();
			}
		}
		if (g_bLever1 == true && g_bLever2 == true)
		{
			LaverOn();
		}
		if (g_bTutorialLeverBlue == true && g_bTutorialLeverRed == true)
		{
			LaverOnTtl();
		}

		UpdateBathGimmick();
		UpdateSteam();
		UpdateGauge();
		UpdateTransferGate();
		UpdateActionZone();
		UpdateEyeTrap();

		UpdateShadow();
#if _DEBUG
		UpdateLine();
		UpdateDebugModel();
#endif
		UpdateScreenUI();
		UpdateSpeechBubble();
		UpdateModel();

		UpdateParticle();

		UpdateCollision_Pre();

		//テレビ
		if (pPlayer->bTvGimmick == true)
		{
			pScreenState[0].TV_bUse = true;

		}
		if (pPlayer2->bTvGimmick == true)
		{
			pScreenState[1].TV_bUse = true;
		}
		//金庫
		if (pPlayer->bMoneyBoxGimmick == true)
		{
			pScreenState[0].MoneyBox_bUse = true;
		}
		if(pPlayer2->bMoneyBoxGimmick == true)
		{
			pScreenState[1].MoneyBox_bUse = true;
		}


	}
	else
	{//ポーズ中
		UpdatePause();
	}
}
//=============================
//ゲーム画面の描画処理
//=============================
void DrawGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	Camera* pCamera;

	//先頭を受け取るため0番目を取得
	pCamera = GetCamera();

	Player* pPlayer;
	pPlayer = GetPlayer();

	Player_2P* pPlayer2;
	pPlayer2 = GetPlayer_2P();

	for (int nCnt = 0; nCnt < MAXCAMERA; nCnt++)
	{
		// バッファのクリア(バックバッファ、Zバッファ)
		pDevice->Clear(
			0,
			nullptr,
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(0, 0, 0),
			1.0f,
			0);


#if _DEBUG

#endif
		DrawMeshField();

//		DrawSky();


		DrawBathGimmick();
		DrawTV();
		DrawSteam();

		DrawModel();
		DrawSimpleModel();
		DrawStage();

		DrawAdvancedModel();



		DrawShadow();

		//特殊
		DrawPlayer(nCnt);
		DrawPlayer_2P(nCnt);
		DrawEnemy();

#if _DEBUG
		DrawTransferGate();

#endif



#if _DEBUG
		DrawCollision_Pre();
		DrawActionZone();
		DrawLine();
		DrawEnemy_View();
		DrawDebugModel();
#endif
		//αテストを有効
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);//基準値
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//比較方法(よりも大きい)--これでアルファ値が0より大きいときに描画（Zバッファにも書かれない ）

		DrawItem();
		DrawBill();

		DrawParticle();

		//αテストを無効
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		DrawSpeechBubble(nCnt);

		SetCamera(nCnt);

		DrawCamera();

		//ビューポートの設定
		pDevice->SetViewport(&pCamera[nCnt].viewport);
	}

	//全画面ビューポート
	D3DVIEWPORT9 FullViewport = GetViewPort();
	//ビューポートをもとに戻す
	pDevice->SetViewport(&FullViewport);//ビューポートの設定

	//------------------------------------------Debug用
	ACTIONZONE* pActionZone;
	pActionZone = GetActionZone();

	for (int nCntZone = 0; nCntZone < MAXZONE; nCntZone++)
	{
		if (pActionZone[nCntZone].bUse == true)
		{
			pActionZone[nCntZone].ZoneColor = pActionZone[nCntZone].EscapeZoneColor;
		}
	}

	DrawGameFade();
	DrawLimitTime();
	DrawScreenUI();


	DrawMap();

	DrawEyeTrap();
	DrawKeyinfo();
	DrawHaveKey(g_nHaveKey);


	DrawItem_UI();

	if ((pPlayer->bMoneyBoxGimmick == true || pPlayer2->bMoneyBoxGimmick == true))
	{
		DrawMoneybox();
		DrawMoneyboxDigit();
		DrawPassword();

	}
	DrawGauge();



	DrawTextSet(D3DXVECTOR3(10.0f, 10.0f, 0.0f), 30, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), "　★鍵を3つ集めて脱出しよう！");

	if (g_PlayerUpdateOk == false)
	{
		DrawTextSet(D3DXVECTOR3(250.0f, 200.0f, 0.0f), 30, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "2Pの脱出待ち");

	}
	if (g_Player2UpdateOk == false)
	{
		DrawTextSet(D3DXVECTOR3(890.0f, 200.0f, 0.0f), 30, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "　1Pの脱出待ち");

	}

#if _DEBUG

	//DrawTextSet(D3DXVECTOR3(550.0f, 490.0f, 0.0f), 20, FONT_AKABARASINDELERA, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), "F1で重なりモデルを削除(取扱注意)");
	//DrawTextSet(D3DXVECTOR3(550.0f, 660.0f, 0.0f), 20, FONT_AKABARASINDELERA, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), "F5キーでモデル配置をセーブ！一度のみ！");


	DrawTextSet(D3DXVECTOR3(30.0f, 10.0f, 0.0f), 40, FONT_AKABARASINDELERA, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), "転移先番号:1P    %d,2P   %d", g_PlayerTransNum, g_Player2TransNum);

	//DrawTextSet(D3DXVECTOR3(550.0f, 700.0f, 0.0f), 20, FONT_AKABARASINDELERA, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), "Xボタンでとりあえずアイテム出現");



	DrawDebugDelComment();

#endif

	if (g_bPause == true)
	{
		DrawPause();
	}
}
//===================================
//Clear専用処理
//===================================
void GameClear(void)
{
	g_ClearFlag = true;
}
//===================================
//ポーズ解除処理
//===================================
void ReleasePause(void)
{
	g_bPause = false;
}

//===================================
//モデル読み込み処理
//===================================
void LoadModel(void)
{
	//ファイルの読み込み
	FILE* pFile = fopen(MODEL_FILE, "rb");

	if (pFile != NULL)
	{
		//敵の使用してる数の読み込み
		fread(&g_nUseModel, sizeof(int), 1, pFile);

		//敵の使用数分、敵の読み込み
	//	fread(&g_aModelInfo[0], sizeof(ModelInfo), g_nUseModel, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}

	else
	{
		return;
	}

	for (int nCnt = 0; nCnt < g_nUseModel; nCnt++)
	{
		SetModel(g_aModelInfo[nCnt].pos, g_aModelInfo[nCnt].rot, g_aModelInfo[nCnt].nType);
	}
}

//===================================
//床読み込み処理処理
//===================================
void LoadField(void)
{
	//ファイルの読み込み
	FILE* pFile = fopen(FIELD_FILE, "rb");

	if (pFile != NULL)
	{
		//敵の使用してる数の読み込み
		fread(&g_nUseField, sizeof(int), 1, pFile);

		//敵の使用数分、敵の読み込み
	//	fread(&g_aFieldInfo[0], sizeof(FieldInfo), g_nUseField, pFile);

		//ファイルを閉じる
		fclose(pFile);

	}

	else
	{
		return;
	}

	//for (int nCnt = 0; nCnt < g_nUseField; nCnt++)
	//{
	//	//SetField(g_aFieldInfo[nCnt].pos, g_aFieldInfo[nCnt].rot, g_aFieldInfo[nCnt].fWide, g_aFieldInfo[nCnt].fDepth, g_aFieldInfo[nCnt].nType);
	//}
}

//===================================
//壁読み込み処理処理
//===================================
void LoadWall(void)
{
	//ファイルの読み込み
	FILE* pFile = fopen(WALL_FILE, "rb");

	if (pFile != NULL)
	{
		//敵の使用してる数の読み込み
		fread(&g_nUseWall, sizeof(int), 1, pFile);

		//敵の使用数分、敵の読み込み
	//	fread(&g_aWallInfo[0], sizeof(ModelInfo), g_nUseWall, pFile);

		//ファイルを閉じる
		fclose(pFile);

	}

	else
	{
		return;
	}

	//for (int nCnt = 0; nCnt < g_nUseWall; nCnt++)
	//{
	//	//SetWall(g_aWallInfo[nCnt].pos, g_aWallInfo[nCnt].rot, g_aWallInfo[nCnt].fWide, g_aWallInfo[nCnt].fHeight, g_aModelInfo[nCnt].nType);
	//}
}



//===================================
//レイを利用した円形での当たり判定
//===================================
bool CheckCollisionWithRay(D3DXVECTOR3 start, D3DXVECTOR3 direction, D3DXVECTOR3 move, float selfRadius, float targetRadius, D3DXVECTOR3 centerPos)
{
	// レイと球の衝突判定を行う関数
	// 引数:
	//   start: レイの始点
	//   direction: レイの方向ベクトル (正規化されていることを想定)
	//   move: 移動オブジェクトの移動ベクトル
	//   selfRadius: 自分の半径
	//   targetRadius: 相手の半径
	//   center: 球の中心座標
	// 戻り値:
	//   衝突があれば true, なければ false


		// レイの始点を自分の半径を相手の方向に向けた地点に設定
	D3DXVECTOR3 adjustedStart;
	D3DXVec3Normalize(&adjustedStart, &move);
	adjustedStart *= selfRadius;
	adjustedStart += start;

	// 移動オブジェクトが進むレイの始点から終点までのベクトルを計算
	D3DXVECTOR3 end = adjustedStart + direction * D3DXVec3Length(&move);

	// レイの始点から球の中心へのベクトルを計算
	D3DXVECTOR3 v = centerPos - adjustedStart;

	// レイの方向ベクトルと球に対する最も近い点を計算
	float t = D3DXVec3Dot(&v, &direction);
	D3DXVECTOR3 closestPoint;

	// レイが球の手前から始まる場合
	if (t < 0.0f)
	{
		closestPoint = adjustedStart;
	}
	// レイが球の奥から始まる場合
	else if (t > D3DXVec3Length(&move))
	{
		closestPoint = end;
	}
	// レイが球と交差する場合
	else
	{
		closestPoint = adjustedStart + direction * t;
	}

	// 最も近い点と球の中心との距離の二乗を計算
	D3DXVECTOR3 Escape = centerPos - closestPoint;

	float distanceSquared = D3DXVec3LengthSq(&Escape);


	float radiusSquared = (selfRadius + targetRadius) * (selfRadius + targetRadius);

	// 距離の二乗が半径の二乗以下ならば当たり
	return distanceSquared <= radiusSquared;
}



//===================================
//プレイヤー箱型当たり判定
//===================================
void BoxCollisionPlayer(D3DXVECTOR3 PlayerMin, D3DXVECTOR3 PlayerMax, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax, int PlayerIndex)
{//当たり判定

	//1Pのとき
	if (PlayerIndex == 1)
	{
		bool OverPenetration = true;//過貫通疑惑を判定--の予定

		Player* pPlayer;
		pPlayer = GetPlayer();

		//---------------------------------------X方向
		if (PlayerMin.z < HitMax.z &&
			PlayerMax.z > HitMin.z &&
			PlayerMax.x - pPlayer->pos.x + pPlayer->oldPos.x <= HitMin.x &&
			PlayerMax.x > HitMin.x &&
			PlayerMin.y < HitMax.y &&
			PlayerMax.y > HitMin.y)
		{
			pPlayer->move.x = 0.0f;
			pPlayer->pos.x = HitMin.x + (PlayerMin.x - pPlayer->pos.x) - 0.1f;

			OverPenetration = false;
		}

		if (PlayerMin.z < HitMax.z &&
			PlayerMax.z > HitMin.z &&
			PlayerMin.x - pPlayer->pos.x + pPlayer->oldPos.x >= HitMax.x &&
			PlayerMin.x < HitMax.x &&
			PlayerMin.y < HitMax.y &&
			PlayerMax.y > HitMin.y)
		{
			pPlayer->move.x = 0.0f;
			pPlayer->pos.x = HitMax.x + (PlayerMax.x - pPlayer->pos.x) + 0.1f;
			OverPenetration = false;
		}

		//---------------------------------------Z方向
		if (PlayerMin.x < HitMax.x &&
			PlayerMax.x > HitMin.x &&
			PlayerMin.z - pPlayer->pos.z + pPlayer->oldPos.z >= HitMax.z &&
			PlayerMin.z < HitMax.z &&
			PlayerMin.y < HitMax.y &&
			PlayerMax.y > HitMin.y)
		{
			pPlayer->move.z = 0.0f;
			pPlayer->pos.z = HitMax.z - (PlayerMin.z - pPlayer->pos.z) + 0.1f;
			OverPenetration = false;
		}

		if (PlayerMin.x < HitMax.x &&
			PlayerMax.x > HitMin.x &&
			PlayerMax.z - pPlayer->pos.z + pPlayer->oldPos.z <= HitMin.z &&
			PlayerMax.z > HitMin.z &&
			PlayerMin.y < HitMax.y &&
			PlayerMax.y > HitMin.y)
		{
			pPlayer->move.z = 0.0f;
			pPlayer->pos.z = HitMin.z - (PlayerMax.z - pPlayer->pos.z) - 0.1f;
			OverPenetration = false;
		}

		//------------------------------------Y方向
		if (PlayerMin.x < HitMax.x &&
			PlayerMax.x > HitMin.x &&
			PlayerMin.z < HitMax.z &&
			PlayerMax.z > HitMin.z &&
			PlayerMin.y - pPlayer->pos.y + pPlayer->oldPos.y >= HitMax.y &&
			PlayerMin.y < HitMax.y)
		{
			pPlayer->move.y = 0.0f;
			pPlayer->pos.y = HitMax.y + (PlayerMin.y - pPlayer->pos.y);

			if (pPlayer->NowMotionDOWN == MOTIONTYPE_1P_JUMP)
			{
				pPlayer->NowMotionDOWN = MOTIONTYPE_1P_RANDING;
			}
			else if (pPlayer->NowMotionDOWN == MOTIONTYPE_1P_MOVE)
			{
				pPlayer->NowMotionDOWN = MOTIONTYPE_1P_MOVE;
			}

			pPlayer->bLandingNow = true;
			OverPenetration = false;
		}


		if (OverPenetration == false)
		{

		}




	}
	else if (PlayerIndex == 2)
	{//2Pの時
		Player_2P* pPlayer2;
		pPlayer2 = GetPlayer_2P();

		bool OverPenetration = false;//過貫通疑惑を判定--の予定

		//---------------------------------------X方向
		if (PlayerMin.z < HitMax.z &&
			PlayerMax.z > HitMin.z &&
			PlayerMax.x - pPlayer2->pos.x + pPlayer2->oldPos.x <= HitMin.x &&
			PlayerMax.x > HitMin.x &&
			PlayerMin.y < HitMax.y &&
			PlayerMax.y > HitMin.y)
		{
			pPlayer2->move.x = 0.0f;
			pPlayer2->pos.x = HitMin.x + (PlayerMin.x - pPlayer2->pos.x) - 0.1f;
			OverPenetration = false;
		}

		if (PlayerMin.z < HitMax.z &&
			PlayerMax.z > HitMin.z &&
			PlayerMin.x - pPlayer2->pos.x + pPlayer2->oldPos.x >= HitMax.x &&
			PlayerMin.x < HitMax.x &&
			PlayerMin.y < HitMax.y &&
			PlayerMax.y > HitMin.y)
		{
			pPlayer2->move.x = 0.0f;
			pPlayer2->pos.x = HitMax.x + (PlayerMax.x - pPlayer2->pos.x) + 0.1f;
			OverPenetration = false;
		}

		//---------------------------------------Z方向
		if (PlayerMin.x < HitMax.x &&
			PlayerMax.x > HitMin.x &&
			PlayerMin.z - pPlayer2->pos.z + pPlayer2->oldPos.z >= HitMax.z &&
			PlayerMin.z < HitMax.z &&
			PlayerMin.y < HitMax.y &&
			PlayerMax.y > HitMin.y)
		{
			pPlayer2->move.z = 0.0f;
			pPlayer2->pos.z = HitMax.z - (PlayerMin.z - pPlayer2->pos.z) + 0.1f;
			OverPenetration = false;
		}

		if (PlayerMin.x < HitMax.x &&
			PlayerMax.x > HitMin.x &&
			PlayerMax.z - pPlayer2->pos.z + pPlayer2->oldPos.z <= HitMin.z &&
			PlayerMax.z > HitMin.z &&
			PlayerMin.y < HitMax.y &&
			PlayerMax.y > HitMin.y)
		{
			pPlayer2->move.z = 0.0f;
			pPlayer2->pos.z = HitMin.z - (PlayerMax.z - pPlayer2->pos.z) - 0.1f;
			OverPenetration = false;
		}

		//------------------------------------Y方向
		if (PlayerMin.x < HitMax.x &&
			PlayerMax.x > HitMin.x &&
			PlayerMin.z < HitMax.z &&
			PlayerMax.z > HitMin.z &&
			PlayerMin.y - pPlayer2->pos.y + pPlayer2->oldPos.y >= HitMax.y &&
			PlayerMin.y < HitMax.y)
		{
			pPlayer2->move.y = 0.0f;
			pPlayer2->pos.y = HitMax.y + (PlayerMin.y - pPlayer2->pos.y);

			if (pPlayer2->NowMotionDOWN == MOTIONTYPE_2P_JUMP)
			{
				pPlayer2->NowMotionDOWN = MOTIONTYPE_2P_RANDING;
			}
			else if (pPlayer2->NowMotionDOWN == MOTIONTYPE_2P_MOVE)
			{
				pPlayer2->NowMotionDOWN = MOTIONTYPE_2P_MOVE;
			}

			pPlayer2->bLandingNow = true;
			OverPenetration = false;
		}
	}


#if _DEBUG
	// 上下の辺
	SetLine(D3DXVECTOR3(HitMin.x, HitMax.y, HitMin.z), D3DXVECTOR3(HitMax.x, HitMax.y, HitMin.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMin.x, HitMin.y, HitMin.z), D3DXVECTOR3(HitMax.x, HitMin.y, HitMin.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	SetLine(D3DXVECTOR3(HitMin.x, HitMax.y, HitMax.z), D3DXVECTOR3(HitMax.x, HitMax.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMin.x, HitMin.y, HitMax.z), D3DXVECTOR3(HitMax.x, HitMin.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	// 側面の辺																											
	SetLine(D3DXVECTOR3(HitMin.x, HitMin.y, HitMin.z), D3DXVECTOR3(HitMin.x, HitMax.y, HitMin.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMax.x, HitMin.y, HitMin.z), D3DXVECTOR3(HitMax.x, HitMax.y, HitMin.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	SetLine(D3DXVECTOR3(HitMin.x, HitMin.y, HitMax.z), D3DXVECTOR3(HitMin.x, HitMax.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMax.x, HitMin.y, HitMax.z), D3DXVECTOR3(HitMax.x, HitMax.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));


	// その他の辺																									   
	SetLine(D3DXVECTOR3(HitMin.x, HitMin.y, HitMin.z), D3DXVECTOR3(HitMin.x, HitMin.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMax.x, HitMax.y, HitMin.z), D3DXVECTOR3(HitMax.x, HitMax.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	SetLine(D3DXVECTOR3(HitMin.x, HitMax.y, HitMin.z), D3DXVECTOR3(HitMin.x, HitMax.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMax.x, HitMin.y, HitMin.z), D3DXVECTOR3(HitMax.x, HitMin.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
#endif

}



//===================================
//プレイヤーとカメラの間の障害物判定
//===================================
void AdjustPlayerPositionToCollision_CAMERA(D3DXVECTOR3 playerPos, int CameraIndex, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax)
{
	Player* pPlayer;
	pPlayer = GetPlayer();
	Player_2P* pPlayer2;
	pPlayer2 = GetPlayer_2P();

	Camera* pCamera;
	pCamera = GetCamera();

	// カメラとプレイヤーの直線上での当たり判定
	D3DXVECTOR3 direction = pCamera[CameraIndex].posV - playerPos;//現在のプレイヤーとカメラの距離
	D3DXVECTOR3 normalizedDir;
	D3DXVec3Normalize(&normalizedDir, &direction);

	// 当たり判定の結果を保存する変数
	bool collision = false;
	float collisionDistance = 0.0f;//衝突した距離

	// プレイヤーからカメラに向かう方向にレイを飛ばして、障害物との当たり判定を行う
	// （ここでは単純に箱型当たり判定を使用していますが、実際のゲームにおいてはより高度なアルゴリズムを使用することが一般的です）
	while (collision == false)
	{
		D3DXVECTOR3 rayPos = playerPos + normalizedDir * collisionDistance;

		if (rayPos.x < HitMax.x && rayPos.x > HitMin.x &&
			rayPos.y < HitMax.y && rayPos.y > HitMin.y &&
			rayPos.z < HitMax.z && rayPos.z > HitMin.z)
		{
			// 衝突が検知された場合、collisionDistanceを調整して再度判定
			collision = true;
		}

		// レイの移動距離を増やして再度判定
		collisionDistance += 0.5f;

		// レイが一定距離(カメラとプレイヤーの距離)以上伸びた場合、無限ループを防ぐために抜ける
		if (CAMERALENGTH < collisionDistance)
		{
			break;
		}
	}

	// 衝突時にカメラの位置を調整
	if (collision == true)
	{
		pCamera[CameraIndex].posV -= (normalizedDir * 0.98f);
		pCamera[CameraIndex].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pCamera[CameraIndex].CameraLength = collisionDistance - 3.0f;

		if (collisionDistance < 46)
		{//距離が短い
			if (CameraIndex == 0)
			{//プレイヤー1
				pPlayer->bTransparent = true;
			}
			else if (CameraIndex == 1)
			{//プレイヤー2
				pPlayer2->bTransparent = true;
			}
		}

	}
}
//===================================
//プレイヤーと注視点の間の障害物判定
//===================================
void AdjustPlayerPositionToCollision_VIEWPOS(D3DXVECTOR3 playerPos, int PlayerIndex, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax)
{
	Player* pPlayer;
	pPlayer = GetPlayer();
	Player_2P* pPlayer2;
	pPlayer2 = GetPlayer_2P();

	View* pViewMtx = GetView();

	View2* pViewMtx2 = GetView_2P();

	HitMin -= D3DXVECTOR3(1.5f, 0.0f, 1.5f);
	HitMax += D3DXVECTOR3(1.5f, 0.0f, 1.5f);


	if (PlayerIndex == 0)
	{
		// 注視点とプレイヤーの直線上での当たり判定
		D3DXVECTOR3 direction = D3DXVECTOR3(pViewMtx[1].ViewPosMtx._41, pViewMtx[1].ViewPosMtx._42, pViewMtx[1].ViewPosMtx._43) - playerPos;//方角制定
		D3DXVECTOR3 normalizedDir;
		D3DXVec3Normalize(&normalizedDir, &direction);

		// 当たり判定の結果を保存する変数
		bool collision = false;
		float collisionDistance = 0.0f;//衝突した距離

		while (collision == false)
		{
			D3DXVECTOR3 rayPos = playerPos + normalizedDir * collisionDistance;

			if (rayPos.x < HitMax.x && rayPos.x > HitMin.x &&
				rayPos.y < HitMax.y && rayPos.y > HitMin.y &&
				rayPos.z < HitMax.z && rayPos.z > HitMin.z)
			{
				// 衝突が検知された場合、collisionDistanceを調整して再度判定
				collision = true;
			}

			// レイの移動距離を増やして再度判定
			collisionDistance += 0.5f;

			// レイが一定距離(カメラとプレイヤーの距離)以上伸びた場合、無限ループを防ぐために抜ける
			if (VIEWPOS.x < collisionDistance)
			{
				pViewMtx[1].ViewPos = VIEWPOS;
				break;
			}
		}
		// 衝突時にカメラの位置を調整
		if (collision == true)
		{
			pViewMtx[1].ViewPosMtx._41 -= (normalizedDir.x * collisionDistance * 0.8f);
			//pViewMtx[1].ViewPosMtx._42 -= (normalizedDir.y);
			pViewMtx[1].ViewPosMtx._43 -= (normalizedDir.z * collisionDistance * 0.8f);
		}
	}
	else if (PlayerIndex == 2)
	{
		// 注視点とプレイヤーの直線上での当たり判定
		D3DXVECTOR3 direction = D3DXVECTOR3(pViewMtx2[1].ViewPosMtx._41, pViewMtx2[1].ViewPosMtx._42, pViewMtx2[1].ViewPosMtx._43) - playerPos;//方角制定
		D3DXVECTOR3 normalizedDir;
		D3DXVec3Normalize(&normalizedDir, &direction);

		// 当たり判定の結果を保存する変数
		bool collision = false;
		float collisionDistance = 0.0f;//衝突した距離

		while (collision == false)
		{
			D3DXVECTOR3 rayPos = playerPos + normalizedDir * collisionDistance;

			if (rayPos.x < HitMax.x && rayPos.x > HitMin.x &&
				rayPos.y < HitMax.y && rayPos.y > HitMin.y &&
				rayPos.z < HitMax.z && rayPos.z > HitMin.z)
			{
				// 衝突が検知された場合、collisionDistanceを調整して再度判定
				collision = true;
			}

			// レイの移動距離を増やして再度判定
			collisionDistance += 0.5f;

			// レイが一定距離(カメラとプレイヤーの距離)以上伸びた場合、無限ループを防ぐために抜ける
			if (VIEWPOS.x < collisionDistance)
			{
				pViewMtx2[1].ViewPos = VIEWPOS;
				break;
			}
		}

		// 衝突時にカメラの位置を調整
		if (collision == true)
		{
			pViewMtx2[1].ViewPosMtx._41 -= (normalizedDir.x * collisionDistance * 0.6f);
			//pViewMtx[1].ViewPosMtx._42 -= (normalizedDir.y);
			pViewMtx2[1].ViewPosMtx._43 -= (normalizedDir.z * collisionDistance * 0.6f);
		}
	}
}

//===================================
//プレイヤーエネミー接触判定
//===================================
void BoxCollisionKill(D3DXVECTOR3 PlayerMin, D3DXVECTOR3 PlayerMax, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax, int PlayerIndex)
{//当たり判定

#if !_DEBUG
	//1Pのとき
	if (PlayerIndex == 1)
	{
		bool OverPenetration = true;//過貫通疑惑を判定

		Player* pPlayer;
		pPlayer = GetPlayer();

		//---------------------------------------X方向
		if (PlayerMin.z < HitMax.z &&
			PlayerMax.z > HitMin.z &&
			PlayerMax.x - pPlayer->pos.x + pPlayer->oldPos.x <= HitMin.x &&
			PlayerMax.x > HitMin.x &&
			PlayerMin.y < HitMax.y &&
			PlayerMax.y > HitMin.y)
		{
			pPlayer->move.x = 0.0f;
			pPlayer->pos.x = HitMin.x + (PlayerMin.x - pPlayer->pos.x) - 0.1f;

			OverPenetration = false;
			SetEyeTrap(0);
			//SetFade(MODE_RESULT);

		}

		if (PlayerMin.z < HitMax.z &&
			PlayerMax.z > HitMin.z &&
			PlayerMin.x - pPlayer->pos.x + pPlayer->oldPos.x >= HitMax.x &&
			PlayerMin.x < HitMax.x &&
			PlayerMin.y < HitMax.y &&
			PlayerMax.y > HitMin.y)
		{
			pPlayer->move.x = 0.0f;
			pPlayer->pos.x = HitMax.x + (PlayerMax.x - pPlayer->pos.x) + 0.1f;
			OverPenetration = false;
			SetEyeTrap(0);
			//SetFade(MODE_RESULT);

		}

		//---------------------------------------Z方向
		if (PlayerMin.x < HitMax.x &&
			PlayerMax.x > HitMin.x &&
			PlayerMin.z - pPlayer->pos.z + pPlayer->oldPos.z >= HitMax.z &&
			PlayerMin.z < HitMax.z &&
			PlayerMin.y < HitMax.y &&
			PlayerMax.y > HitMin.y)
		{
			pPlayer->move.z = 0.0f;
			pPlayer->pos.z = HitMax.z - (PlayerMin.z - pPlayer->pos.z) + 0.1f;
			OverPenetration = false;
			SetEyeTrap(0);
			//SetFade(MODE_RESULT);

		}

		if (PlayerMin.x < HitMax.x &&
			PlayerMax.x > HitMin.x &&
			PlayerMax.z - pPlayer->pos.z + pPlayer->oldPos.z <= HitMin.z &&
			PlayerMax.z > HitMin.z &&
			PlayerMin.y < HitMax.y &&
			PlayerMax.y > HitMin.y)
		{
			pPlayer->move.z = 0.0f;
			pPlayer->pos.z = HitMin.z - (PlayerMax.z - pPlayer->pos.z) - 0.1f;
			OverPenetration = false;
			SetEyeTrap(0);
			//SetFade(MODE_RESULT);

		}

		//------------------------------------Y方向
		if (PlayerMin.x < HitMax.x &&
			PlayerMax.x > HitMin.x &&
			PlayerMin.z < HitMax.z &&
			PlayerMax.z > HitMin.z &&
			PlayerMin.y - pPlayer->pos.y + pPlayer->oldPos.y >= HitMax.y &&
			PlayerMin.y < HitMax.y)
		{
			pPlayer->move.y = 0.0f;
			pPlayer->pos.y = HitMax.y + (PlayerMin.y - pPlayer->pos.y);

			if (pPlayer->NowMotionDOWN == MOTIONTYPE_1P_JUMP)
			{
				pPlayer->NowMotionDOWN = MOTIONTYPE_1P_RANDING;
			}
			else if (pPlayer->NowMotionDOWN == MOTIONTYPE_1P_MOVE)
			{
				pPlayer->NowMotionDOWN = MOTIONTYPE_1P_MOVE;
			}

			pPlayer->bLandingNow = true;
			OverPenetration = false;
		}


		if (OverPenetration == false)
		{

		}




	}
	else if (PlayerIndex == 2)
	{//2Pの時
		Player_2P* pPlayer2;
		pPlayer2 = GetPlayer_2P();

		bool OverPenetration = false;//過貫通疑惑を判定

		//---------------------------------------X方向
		if (PlayerMin.z < HitMax.z &&
			PlayerMax.z > HitMin.z &&
			PlayerMax.x - pPlayer2->pos.x + pPlayer2->oldPos.x <= HitMin.x &&
			PlayerMax.x > HitMin.x &&
			PlayerMin.y < HitMax.y &&
			PlayerMax.y > HitMin.y)
		{
			pPlayer2->move.x = 0.0f;
			pPlayer2->pos.x = HitMin.x + (PlayerMin.x - pPlayer2->pos.x) - 0.1f;
			OverPenetration = false;
			SetEyeTrap(1);
			//SetFade(MODE_RESULT);

		}

		if (PlayerMin.z < HitMax.z &&
			PlayerMax.z > HitMin.z &&
			PlayerMin.x - pPlayer2->pos.x + pPlayer2->oldPos.x >= HitMax.x &&
			PlayerMin.x < HitMax.x &&
			PlayerMin.y < HitMax.y &&
			PlayerMax.y > HitMin.y)
		{
			pPlayer2->move.x = 0.0f;
			pPlayer2->pos.x = HitMax.x + (PlayerMax.x - pPlayer2->pos.x) + 0.1f;
			OverPenetration = false;
			SetEyeTrap(1);
			//SetFade(MODE_RESULT);

		}

		//---------------------------------------Z方向
		if (PlayerMin.x < HitMax.x &&
			PlayerMax.x > HitMin.x &&
			PlayerMin.z - pPlayer2->pos.z + pPlayer2->oldPos.z >= HitMax.z &&
			PlayerMin.z < HitMax.z &&
			PlayerMin.y < HitMax.y &&
			PlayerMax.y > HitMin.y)
		{
			pPlayer2->move.z = 0.0f;
			pPlayer2->pos.z = HitMax.z - (PlayerMin.z - pPlayer2->pos.z) + 0.1f;
			OverPenetration = false;
			SetEyeTrap(1);
			//SetFade(MODE_RESULT);

		}

		if (PlayerMin.x < HitMax.x &&
			PlayerMax.x > HitMin.x &&
			PlayerMax.z - pPlayer2->pos.z + pPlayer2->oldPos.z <= HitMin.z &&
			PlayerMax.z > HitMin.z &&
			PlayerMin.y < HitMax.y &&
			PlayerMax.y > HitMin.y)
		{
			pPlayer2->move.z = 0.0f;
			pPlayer2->pos.z = HitMin.z - (PlayerMax.z - pPlayer2->pos.z) - 0.1f;
			OverPenetration = false;
			SetEyeTrap(1);
			//SetFade(MODE_RESULT);

		}

		//------------------------------------Y方向
		if (PlayerMin.x < HitMax.x &&
			PlayerMax.x > HitMin.x &&
			PlayerMin.z < HitMax.z &&
			PlayerMax.z > HitMin.z &&
			PlayerMin.y - pPlayer2->pos.y + pPlayer2->oldPos.y >= HitMax.y &&
			PlayerMin.y < HitMax.y)
		{
			pPlayer2->move.y = 0.0f;
			pPlayer2->pos.y = HitMax.y + (PlayerMin.y - pPlayer2->pos.y);

			if (pPlayer2->NowMotionDOWN == MOTIONTYPE_2P_JUMP)
			{
				pPlayer2->NowMotionDOWN = MOTIONTYPE_2P_RANDING;
			}
			else if (pPlayer2->NowMotionDOWN == MOTIONTYPE_2P_MOVE)
			{
				pPlayer2->NowMotionDOWN = MOTIONTYPE_2P_MOVE;
			}

			pPlayer2->bLandingNow = true;
			OverPenetration = false;
		}
	}

#endif

}

//===================================
//エネミー箱型当たり判定
//===================================
void BoxCollisionEnemy(D3DXVECTOR3 EnemyMin, D3DXVECTOR3 EnemyMax, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax)
{//当たり判定

	bool OverPenetration = true;//過貫通疑惑を判定

	ENEMYMODEL* pEnemy;
	pEnemy = GetEnemy();

	//---------------------------------------X方向
	if (EnemyMin.z < HitMax.z &&
		EnemyMax.z > HitMin.z &&
		EnemyMax.x - pEnemy->pos.x + pEnemy->oldPos.x <= HitMin.x &&
		EnemyMax.x > HitMin.x &&
		EnemyMin.y < HitMax.y &&
		EnemyMax.y > HitMin.y)
	{
		pEnemy->move.x = 0.0f;
		pEnemy->pos.x = HitMin.x + (EnemyMin.x - pEnemy->pos.x) - 0.1f;

		OverPenetration = false;

		if (pEnemy->ActionPattern == ACTIONPATTERN_ENEMY_WALK || pEnemy->ActionPattern == ACTIONPATTERN_ENEMY_SPAWN)
		{
			ActionEnemy(ACTIONPATTERN_ENEMY_WALK, -1);
		}
	}

	if (EnemyMin.z < HitMax.z &&
		EnemyMax.z > HitMin.z &&
		EnemyMin.x - pEnemy->pos.x + pEnemy->oldPos.x >= HitMax.x &&
		EnemyMin.x < HitMax.x &&
		EnemyMin.y < HitMax.y &&
		EnemyMax.y > HitMin.y)
	{
		pEnemy->move.x = 0.0f;
		pEnemy->pos.x = HitMax.x + (EnemyMax.x - pEnemy->pos.x) + 0.1f;
		OverPenetration = false;
		if (pEnemy->ActionPattern == ACTIONPATTERN_ENEMY_WALK || pEnemy->ActionPattern == ACTIONPATTERN_ENEMY_SPAWN)
		{
			ActionEnemy(ACTIONPATTERN_ENEMY_WALK, -1);
		}
	}

	//---------------------------------------Z方向
	if (EnemyMin.x < HitMax.x &&
		EnemyMax.x > HitMin.x &&
		EnemyMin.z - pEnemy->pos.z + pEnemy->oldPos.z >= HitMax.z &&
		EnemyMin.z < HitMax.z &&
		EnemyMin.y < HitMax.y &&
		EnemyMax.y > HitMin.y)
	{
		pEnemy->move.z = 0.0f;
		pEnemy->pos.z = HitMax.z - (EnemyMin.z - pEnemy->pos.z) + 0.1f;
		OverPenetration = false;
		if (pEnemy->ActionPattern == ACTIONPATTERN_ENEMY_WALK || pEnemy->ActionPattern == ACTIONPATTERN_ENEMY_SPAWN)
		{
			ActionEnemy(ACTIONPATTERN_ENEMY_WALK, -1);
		}
	}

	if (EnemyMin.x < HitMax.x &&
		EnemyMax.x > HitMin.x &&
		EnemyMax.z - pEnemy->pos.z + pEnemy->oldPos.z <= HitMin.z &&
		EnemyMax.z > HitMin.z &&
		EnemyMin.y < HitMax.y &&
		EnemyMax.y > HitMin.y)
	{
		pEnemy->move.z = 0.0f;
		pEnemy->pos.z = HitMin.z - (EnemyMax.z - pEnemy->pos.z) - 0.1f;
		OverPenetration = false;
		if (pEnemy->ActionPattern == ACTIONPATTERN_ENEMY_WALK || pEnemy->ActionPattern == ACTIONPATTERN_ENEMY_SPAWN)
		{
			ActionEnemy(ACTIONPATTERN_ENEMY_WALK, -1);
		}
	}

	//------------------------------------Y方向
	if (EnemyMin.x < HitMax.x &&
		EnemyMax.x > HitMin.x &&
		EnemyMin.z < HitMax.z &&
		EnemyMax.z > HitMin.z &&
		EnemyMin.y - pEnemy->pos.y + pEnemy->oldPos.y >= HitMax.y &&
		EnemyMin.y < HitMax.y)
	{
		pEnemy->move.y = 0.0f;
		pEnemy->pos.y = HitMax.y + (EnemyMin.y - pEnemy->pos.y);

		if (pEnemy->NowMotionDOWN == MOTIONTYPE_ENEMY_JUMP)
		{
			pEnemy->NowMotionDOWN = MOTIONTYPE_ENEMY_RANDING;
		}
		else if (pEnemy->NowMotionDOWN == MOTIONTYPE_ENEMY_MOVE)
		{
			pEnemy->NowMotionDOWN = MOTIONTYPE_ENEMY_MOVE;
		}

		pEnemy->bLandingNow = true;
		OverPenetration = false;
	}


	if (OverPenetration == false)
	{

	}

#if _DEBUG
	// 上下の辺
	SetLine(D3DXVECTOR3(HitMin.x, HitMax.y, HitMin.z), D3DXVECTOR3(HitMax.x, HitMax.y, HitMin.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMin.x, HitMin.y, HitMin.z), D3DXVECTOR3(HitMax.x, HitMin.y, HitMin.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	SetLine(D3DXVECTOR3(HitMin.x, HitMax.y, HitMax.z), D3DXVECTOR3(HitMax.x, HitMax.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMin.x, HitMin.y, HitMax.z), D3DXVECTOR3(HitMax.x, HitMin.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	// 側面の辺																											
	SetLine(D3DXVECTOR3(HitMin.x, HitMin.y, HitMin.z), D3DXVECTOR3(HitMin.x, HitMax.y, HitMin.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMax.x, HitMin.y, HitMin.z), D3DXVECTOR3(HitMax.x, HitMax.y, HitMin.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	SetLine(D3DXVECTOR3(HitMin.x, HitMin.y, HitMax.z), D3DXVECTOR3(HitMin.x, HitMax.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMax.x, HitMin.y, HitMax.z), D3DXVECTOR3(HitMax.x, HitMax.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));


	// その他の辺																									   
	SetLine(D3DXVECTOR3(HitMin.x, HitMin.y, HitMin.z), D3DXVECTOR3(HitMin.x, HitMin.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMax.x, HitMax.y, HitMin.z), D3DXVECTOR3(HitMax.x, HitMax.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	SetLine(D3DXVECTOR3(HitMin.x, HitMax.y, HitMin.z), D3DXVECTOR3(HitMin.x, HitMax.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMax.x, HitMin.y, HitMin.z), D3DXVECTOR3(HitMax.x, HitMin.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
#endif

}


//===================================
//転移門当たり判定
//===================================
void BoxCollisionGate(D3DXVECTOR3 PlayerMin, D3DXVECTOR3 PlayerMax, D3DXVECTOR3 GateMin, D3DXVECTOR3 GateMax, int PlayerIndex, int GateIndex, int ParentIndex)
{//当たり判定
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (GateIndex == 9)
	{
		return;
	}


	D3DXVECTOR3 EscapeRot_Player;
	EscapeRot_Player = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 EscapeRot_Camera;
	EscapeRot_Camera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Camera* pCamera;
	pCamera = GetCamera();

	TRANSFERGATE* pTransferGate;
	pTransferGate = GetTransferGate();

	//SPEECHBUBBLE* pSpeachBubble = GetSpeechBubble();


	//転移先
	D3DXVECTOR3 ParentGateMin = D3DXVECTOR3(0.0f, 1000.0f, 0.0f);//初期計算--後に不要になる??
	D3DXVECTOR3 ParentGateMax = D3DXVECTOR3(0.0f, 1200.0f, 0.0f);

	//移動量避難
	D3DXVECTOR3 ESCAPEMOVE = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float PlayerCenterCorre = 45.0f;
	int nEscapeIndex = 0;
	bool CrossRoadTrans = false;

	if (pTransferGate[GateIndex].nParentIndex == CROSSROAD_NUM)
	{//転移先番号が十字路


		nEscapeIndex = 9;//十字真ん中
//		int Angle= (rand() % 4);//0～3

		//決まった転移先番号を使用し転移(転移方向はifでマニュアル入力
		switch (nEscapeIndex)
		{
		case 0:
			pTransferGate[GateIndex].ParentTransAngle = TRANS_ANGLE_MIN_X;
			break;

		case 1:
			pTransferGate[GateIndex].ParentTransAngle = TRANS_ANGLE_MAX_X;
			break;

		case 2:
			pTransferGate[GateIndex].ParentTransAngle = TRANS_ANGLE_MIN_Z;
			break;

		case 3:
			pTransferGate[GateIndex].ParentTransAngle = TRANS_ANGLE_MAX_Z;
			break;
		}

		ParentIndex = nEscapeIndex;
	}
	else if (pTransferGate[GateIndex].nParentIndex == RONDOMTRANS_NUM)
	{//転移先番号がランダム転移のとき
		//nEscapeIndex = (((rand() % 4) + 5));//4～8----増えたら変動
		if (PlayerIndex == 0)
		{
			nEscapeIndex = g_PlayerTransNum;
		}
		if (PlayerIndex == 1)
		{
			nEscapeIndex = g_Player2TransNum;
		}

		//決まった転移先番号を使用し転移(転移方向はifでマニュアル入力
		switch (nEscapeIndex)
		{
		case 4:
			pTransferGate[GateIndex].ParentTransAngle = TRANS_ANGLE_MIN_Z;
			break;

		case 5:
			pTransferGate[GateIndex].ParentTransAngle = TRANS_ANGLE_MIN_Z;
			break;

		case 6:
			pTransferGate[GateIndex].ParentTransAngle = TRANS_ANGLE_MIN_Z;
			break;

		case 7:
			pTransferGate[GateIndex].ParentTransAngle = TRANS_ANGLE_MIN_X;
			break;
		case 8:
			pTransferGate[GateIndex].ParentTransAngle = TRANS_ANGLE_MAX_Z;
			break;

		}
		ParentIndex = nEscapeIndex;
	}
	else if (pTransferGate[GateIndex].nParentIndex == CLEAR_NUM)
	{//CLEARのとき
		pTransferGate[pTransferGate[GateIndex].nParentIndex].bUse = true;
		pTransferGate[pTransferGate[GateIndex].nParentIndex].bActiomTrans = true;
		pTransferGate[pTransferGate[GateIndex].nParentIndex].bCompulsionTrans = false;
	}

	ParentGateMin = D3DXVECTOR3(pTransferGate[ParentIndex].pos + pTransferGate[ParentIndex].GateMin);
	ParentGateMax = D3DXVECTOR3(pTransferGate[ParentIndex].pos + pTransferGate[ParentIndex].GateMax);

	if (pTransferGate[GateIndex].nParentIndex == CROSSROAD_NUM)
	{//転移先番号が十字路
		CrossRoadTrans = true;
	}
	else
	{
		CrossRoadTrans = false;
	}

	if (pTransferGate[ParentIndex].bUse == true)
	{

		if (pTransferGate[ParentIndex].bActiomTrans == false)
		{//アクショントランスじゃない時

		}
		else if (pTransferGate[ParentIndex].bActiomTrans == true)
		{//アクションで転移

			//1Pのとき
			if (PlayerIndex == 0)
			{
				//接触したか
				bool bHit = false;

				Player* pPlayer;
				pPlayer = GetPlayer();

				Player_2P* pPlayer2;
				pPlayer2 = GetPlayer_2P();


				if (GateMin.x <= pPlayer->pos.x && pPlayer->pos.x <= GateMax.x)
				{
					if (GateMin.y <= (pPlayer->pos.y + PlayerCenterCorre) && (pPlayer->pos.y + PlayerCenterCorre) <= GateMax.y)
					{
						if (GateMin.z <= pPlayer->pos.z && pPlayer->pos.z <= GateMax.z)
						{
							bHit = true;
						}
					}
				}

				if (bHit == true)
				{//接触判定時

					if (pPlayer->bAction == true)
					{
						pPlayer->PlayerState = PLAYERSTATE_1P_TELEPOR;

						if (pTransferGate[GateIndex].ParentTransAngle == TRANS_ANGLE_CLEAR)
						{//Clear転移
							SetGameFade(0, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EscapeRot_Camera, EscapeRot_Player, true, false);

							if (pTransferGate[ParentIndex].bCompulsionTrans == true)
							{//プレイヤー２も転移
								SetGameFade(1, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EscapeRot_Camera, EscapeRot_Player, true, false);
							}
						}
						else if (pTransferGate[GateIndex].ParentTransAngle == TRANS_ANGLE_MAX_X)
						{//+X

							ESCAPEMOVE.x = ParentGateMax.x + (PlayerMax.x - pPlayer->pos.x) + 11.1f;
							ESCAPEMOVE.y = pTransferGate[ParentIndex].pos.y;
							ESCAPEMOVE.z = pTransferGate[ParentIndex].pos.z;

							pPlayer->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
							EscapeRot_Player.y = -D3DX_PI * 0.5f;
							EscapeRot_Camera.y = -D3DX_PI * 0.5f;
						}
						else if (pTransferGate[GateIndex].ParentTransAngle == TRANS_ANGLE_MIN_X)
						{//-X

							ESCAPEMOVE.x = ParentGateMin.x + (PlayerMin.x - pPlayer->pos.x) - 11.1f;
							ESCAPEMOVE.y = pTransferGate[ParentIndex].pos.y;
							ESCAPEMOVE.z = pTransferGate[ParentIndex].pos.z;

							pPlayer->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
							EscapeRot_Player.y = D3DX_PI * 0.5f;
							EscapeRot_Camera.y = D3DX_PI * 0.5f;
						}
						else if (pTransferGate[GateIndex].ParentTransAngle == TRANS_ANGLE_MAX_Z)
						{//+Z

							ESCAPEMOVE.z = ParentGateMax.z - (PlayerMin.z - pPlayer->pos.z) + 11.1f;

							ESCAPEMOVE.x = pTransferGate[ParentIndex].pos.x;
							ESCAPEMOVE.y = pTransferGate[ParentIndex].pos.y;

							pPlayer->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

							EscapeRot_Player.y = D3DX_PI;
							EscapeRot_Camera.y = 0.0f;
						}
						else if (pTransferGate[GateIndex].ParentTransAngle == TRANS_ANGLE_MIN_Z)
						{//-Z

							ESCAPEMOVE.z = ParentGateMin.z - (PlayerMax.z - pPlayer->pos.z) - 11.1f;
							ESCAPEMOVE.x = pTransferGate[ParentIndex].pos.x;
							ESCAPEMOVE.y = pTransferGate[ParentIndex].pos.y;

							pPlayer->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

							EscapeRot_Player.y = 0.0f;
							EscapeRot_Camera.y = D3DX_PI;
						}
						//if (ParentIndex == 7)
						//{//水回りの扉から出たとき
						//	//風呂の水が通常か草かをランダム選出
						//	int nBathRand = RandSelect(WATER_MAX);
						//	MAPOBJECT* pMapObject = GetMapObject();
						//	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++, pMapObject++)
						//	{
						//		if (pMapObject->nType == MODELTYPE_BATH)
						//		{
						//			SetBathWater(D3DXVECTOR3(pMapObject->pos.x, pMapObject->pos.y + 40.0f, pMapObject->pos.z)
						//				, D3DXVECTOR3(pMapObject->rot.x, D3DX_PI * 0.5f, pMapObject->rot.z)
						//				, BATHWATER_WIDE
						//				, BATHWATER_DEPTH
						//				, (WATER_TYPE)nBathRand);
						//		}
						//	}

						//}4
						EyeTrap* pEyeTrap = GetEyeTrap();

						if (pEyeTrap[PlayerIndex].bUse == true)
						{
							pEyeTrap[PlayerIndex].bUse = false;
							pEyeTrap[PlayerIndex].nBlindCnt = 0;
						}

						if (nKitchen >= 0)
						{
							StopSound(SOUND_LABEL_SE_COOK);
						}
						
						SetGameFade(0, ESCAPEMOVE, EscapeRot_Camera, EscapeRot_Player, false, CrossRoadTrans);
						if (ParentIndex == 9)
						{//十字路のとき
							pPlayer->CrossRoadNow = true;
						}
						else
						{
							pPlayer->CrossRoadNow = false;
						}
						if (pTransferGate[ParentIndex].bCompulsionTrans == true)
						{//プレイヤー２も転移
							SetGameFade(1, ESCAPEMOVE, EscapeRot_Camera, EscapeRot_Player, false, CrossRoadTrans);
							if (ParentIndex == 9)
							{//十字路のとき
								pPlayer2->CrossRoadNow = true;
							}
							else
							{
								pPlayer2->CrossRoadNow = false;
							}
						}
					}
				}
			}
			else if (PlayerIndex == 1)
			{//2Pの時
				Player_2P* pPlayer2;
				pPlayer2 = GetPlayer_2P();

				Player* pPlayer;
				pPlayer = GetPlayer();
				//接触したか
				bool bHit = false;

				if (GateMin.x <= pPlayer2->pos.x && pPlayer2->pos.x <= GateMax.x)
				{
					if (GateMin.y <= (pPlayer2->pos.y + PlayerCenterCorre) && (pPlayer2->pos.y + PlayerCenterCorre) <= GateMax.y)
					{
						if (GateMin.z <= pPlayer2->pos.z && pPlayer2->pos.z <= GateMax.z)
						{
							bHit = true;
						}
					}
				}

				if (bHit == true)
				{//接触判定時

					if (pPlayer2->bAction == true)
					{
						pPlayer2->PlayerState = PLAYERSTATE_2P_TELEPOR;

						if (pTransferGate[GateIndex].ParentTransAngle == TRANS_ANGLE_CLEAR)
						{
							SetGameFade(1, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EscapeRot_Camera, EscapeRot_Player, true, false);

							if (pTransferGate[ParentIndex].bCompulsionTrans == true)
							{//プレイヤー２も転移
								SetGameFade(0, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EscapeRot_Camera, EscapeRot_Player, true, false);
							}
						}
						else if (pTransferGate[GateIndex].ParentTransAngle == TRANS_ANGLE_MAX_X)
						{//+X
							ESCAPEMOVE.x = ParentGateMax.x + (PlayerMax.x - pPlayer2->pos.x) + 11.1f;
							ESCAPEMOVE.y = pTransferGate[ParentIndex].pos.y;
							ESCAPEMOVE.z = pTransferGate[ParentIndex].pos.z;

							pPlayer2->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
							EscapeRot_Player.y = -D3DX_PI * 0.5f;
							EscapeRot_Camera.y = -D3DX_PI * 0.5f;
						}
						else if (pTransferGate[GateIndex].ParentTransAngle == TRANS_ANGLE_MIN_X)
						{//-X
							ESCAPEMOVE.x = ParentGateMin.x + (PlayerMin.x - pPlayer2->pos.x) - 11.1f;
							ESCAPEMOVE.y = pTransferGate[ParentIndex].pos.y;
							ESCAPEMOVE.z = pTransferGate[ParentIndex].pos.z;

							pPlayer2->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
							EscapeRot_Player.y = D3DX_PI * 0.5f;
							EscapeRot_Camera.y = D3DX_PI * 0.5f;
						}
						else if (pTransferGate[GateIndex].ParentTransAngle == TRANS_ANGLE_MAX_Z)
						{//+Z
							ESCAPEMOVE.z = ParentGateMax.z - (PlayerMin.z - pPlayer2->pos.z) + 11.1f;
							ESCAPEMOVE.x = pTransferGate[ParentIndex].pos.x;
							ESCAPEMOVE.y = pTransferGate[ParentIndex].pos.y;

							pPlayer2->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

							EscapeRot_Player.y = D3DX_PI;
							EscapeRot_Camera.y = 0.0f;
						}
						else if (pTransferGate[GateIndex].ParentTransAngle == TRANS_ANGLE_MIN_Z)
						{//-Z
							ESCAPEMOVE.z = ParentGateMin.z - (PlayerMax.z - pPlayer2->pos.z) - 11.1f;
							ESCAPEMOVE.x = pTransferGate[ParentIndex].pos.x;
							ESCAPEMOVE.y = pTransferGate[ParentIndex].pos.y;

							pPlayer2->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

							EscapeRot_Player.y = 0.0f;
							EscapeRot_Camera.y = D3DX_PI;
						}
						//if (ParentIndex == 7)
						//{//水回りの扉から出たとき
						//	//風呂の水が通常か草かをランダム選出
						//	int nBathRand = RandSelect(WATER_MAX);
						//	MAPOBJECT* pMapObject = GetMapObject();
						//	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++, pMapObject++)
						//	{
						//		if (pMapObject->nType == MODELTYPE_BATH)
						//		{
						//			SetBathWater(D3DXVECTOR3(pMapObject->pos.x, pMapObject->pos.y + 40.0f, pMapObject->pos.z)
						//				, D3DXVECTOR3(pMapObject->rot.x, D3DX_PI * 0.5f, pMapObject->rot.z)
						//				, BATHWATER_WIDE
						//				, BATHWATER_DEPTH
						//				, (WATER_TYPE)nBathRand);
						//		}
						//	}

						//}
						EyeTrap* pEyeTrap = GetEyeTrap();

						if (pEyeTrap[PlayerIndex].bUse == true)
						{
							pEyeTrap[PlayerIndex].bUse = false;
							pEyeTrap[PlayerIndex].nBlindCnt = 0;
						}

						if (nKitchen >= 0)
						{
							StopSound(SOUND_LABEL_SE_COOK);
						}
	
						SetGameFade(1, ESCAPEMOVE, EscapeRot_Camera, EscapeRot_Player, false, CrossRoadTrans);
						if (ParentIndex == 9)
						{//十字路のとき
							pPlayer2->CrossRoadNow = true;
						}
						else
						{
							pPlayer2->CrossRoadNow = false;
						}
						if (pTransferGate[ParentIndex].bCompulsionTrans == true)
						{//プレイヤー1も転移
							SetGameFade(0, ESCAPEMOVE, EscapeRot_Camera, EscapeRot_Player, false, CrossRoadTrans);
							if (ParentIndex == 9)
							{//十字路のとき
								pPlayer->CrossRoadNow = true;
							}
							else
							{
								pPlayer->CrossRoadNow = false;
							}
						}
					}
				}
			}
		}
	}
}

//===================================
//行動エリア円形当たり判定(アクションゾーン)
//===================================
void SphereCollisionZone(D3DXVECTOR3 PlayerPos, int PlayerIndex, int ZoneIndex)
{//当たり判定
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	Camera* pCamera;
	pCamera = GetCamera();

	Player* pPlayer;
	pPlayer = GetPlayer();

	Player_2P* pPlayer2;
	pPlayer2 = GetPlayer_2P();

	View* pViewMtx = GetView();

	View2* pViewMtx2 = GetView_2P();

	ACTIONZONE* pActionZone;
	pActionZone = GetActionZone();

	TV_VISION* pTVvision;
	pTVvision = GetTVPos();

	Gauge* pGauge = GetGauge();

	D3DXVECTOR3 PosMag = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//補正値
	SPEECHBUBBLETYPE BubbleType = SPEECHBUBBLETYPE_MAX;

	if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_BATH)
	{
		PosMag = D3DXVECTOR3(-40.0f, -20.0f, 0.0f);//補正値
		BubbleType = SPEECHBUBBLETYPE_ACTION;
	}
	else if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_MONEYBOX)
	{
		PosMag = D3DXVECTOR3(0.0f, 15.0f, 0.0f);//補正値
		BubbleType = SPEECHBUBBLETYPE_ACTION;
	}
	else if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_1 || pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_2)
	{
		PosMag = D3DXVECTOR3(0.0f, -20.0f, 40.0f);//補正値
		BubbleType = SPEECHBUBBLETYPE_LONGACTION;
	}
	else if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_KEY_1 || pActionZone[ZoneIndex].ActionType == ACTION_TYPE_KEY_2 || pActionZone[ZoneIndex].ActionType == ACTION_TYPE_KEY_3)
	{
		PosMag = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//補正値
		BubbleType = SPEECHBUBBLETYPE_GET;
	}
	else if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_KITCHEN)
	{
		BubbleType = SPEECHBUBBLETYPE_LONGACTION;
	}
	else if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_TV)
	{
		PosMag = D3DXVECTOR3(0.0f, -20.0f, -40.0f);//補正値
		if (pTVvision->bOn == true)
		{
			BubbleType = SPEECHBUBBLETYPE_CHANNEL;
		}
		else if (pTVvision->bOn == false)
		{
			BubbleType = SPEECHBUBBLETYPE_ACTION;
		}
	}
	else if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_ESCAPE)
	{
		PosMag = D3DXVECTOR3(0.0f, -20.0f, -40.0f);//補正値
		BubbleType = SPEECHBUBBLETYPE_TRANCE;
	}
	else if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_GAMECLEAR)
	{

		PosMag = D3DXVECTOR3(0.0f, 150.0f, 20.0f);//補正値
		BubbleType = SPEECHBUBBLETYPE_GAMECLEAR;
	}
	else if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_CUPBOARD)
	{

		PosMag = D3DXVECTOR3(-20.0f, -20.0f, 20.0f);//補正値
		BubbleType = SPEECHBUBBLETYPE_GET;
	}
	else if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_DESK)
	{
		BubbleType = SPEECHBUBBLETYPE_ACTION;
	}
	else if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_PURIFICATION)
	{
		BubbleType = SPEECHBUBBLETYPE_ACTION;
	}
	else if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_TUTORIAL1)
	{
		BubbleType = SPEECHBUBBLETYPE_LONGACTION;
	}
	else if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_TUTORIAL2)
	{
		BubbleType = SPEECHBUBBLETYPE_LONGACTION;
	}


	float PlayerCenterCorre = 45.0f;

	//接触したか
	bool bIn = false;

	//プレイヤーのposとエリアのposの差分を計算

	//差分ベクトル格納
	D3DXVECTOR3 diff;
	//1Pのとき
	if (PlayerIndex == 0)
	{
		PlayerPos.y += PlayerCenterCorre;//中心位置補正

		//差分ベクトルを計算
		diff = PlayerPos - pActionZone[ZoneIndex].pos;

	}
	else if (PlayerIndex == 1)
	{//2Pの時
		PlayerPos.y += PlayerCenterCorre;//中心位置補正

		//差分ベクトルを計算
		diff = PlayerPos - pActionZone[ZoneIndex].pos;
	}



	//各要素を二乗して入れる
	float squaredLength = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;

	//平方根を取る（直線差分）
	float distance = sqrt(squaredLength);

	if (distance < pActionZone[ZoneIndex].Radius)
	{//差分の距離が半径より短い==円の中にいる時
		bIn = true;//接触判定
	}

	if (bIn == true)
	{//接触判定時
		if (PlayerIndex == 0)
		{
			SetSpeechBubble(D3DXVECTOR3(pViewMtx[3].ViewPosMtx._41, pViewMtx[3].ViewPosMtx._42, pViewMtx[3].ViewPosMtx._43), ZoneIndex, 0, D3DXVECTOR3(0.0f, 00.0f, 0.0f), BubbleType, PlayerIndex);
			
		}
		else if (PlayerIndex == 1)
		{
			SetSpeechBubble(D3DXVECTOR3(pViewMtx2[3].ViewPosMtx._41, pViewMtx2[3].ViewPosMtx._42, pViewMtx2[3].ViewPosMtx._43), ZoneIndex, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f), BubbleType, PlayerIndex);
		}

	}
	else
	{
		if (PlayerIndex == 0)
		{
			SetSpeechBubble(D3DXVECTOR3(pViewMtx[3].ViewPosMtx._41, pViewMtx[3].ViewPosMtx._42, pViewMtx[3].ViewPosMtx._43), ZoneIndex, 1, D3DXVECTOR3(0.0f, 0.0f, 0.0f), BubbleType, PlayerIndex);
		}
		else if (PlayerIndex == 1)
		{
			SetSpeechBubble(D3DXVECTOR3(pViewMtx2[3].ViewPosMtx._41, pViewMtx2[3].ViewPosMtx._42, pViewMtx2[3].ViewPosMtx._43), ZoneIndex, 1, D3DXVECTOR3(0.0f, 00.0f, 0.0f), BubbleType, PlayerIndex);
		}
	}

	//1Pのとき
	if (PlayerIndex == 0)
	{
		//範囲内でアクションの種別ごとに動作

		if (bIn == true)
		{//接触判定時

			pActionZone[ZoneIndex].ZoneColor = D3DXCOLOR(1.0f, 5.0f, 2.0f, 0.2f);
			pActionZone[ZoneIndex].bDrawOk = false;
		}
		else
		{
			pActionZone[ZoneIndex].bDrawOk = true;
		}

		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_MONEYBOX && bIn == true)
		{//金庫のギミック（1P）

			if (GetJoypadTrigger(JOYKEY_X, 0) == true && pPlayer2->bMoneyBoxGimmick != true)
			{//金庫のギミック作動
				pPlayer->bMoneyBoxGimmick = pPlayer->bMoneyBoxGimmick ? false : true;
				if (pPlayer->bMoneyBoxGimmick == true)
				{
					g_MoneyboxPlayer = false;
				}
			}
		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_MONEYBOX && bIn == false)
		{//外に出たら解除
			pPlayer->bMoneyBoxGimmick = false;
		}


		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_TV && bIn == true)
		{//テレビのギミック
			if (pTVvision->bOn == true)
			{
				pPlayer->bTvGimmick = true;
			}

			if (GetJoypadTrigger(JOYKEY_X, 0) == true)
			{
				TVController(PlayerIndex);
			}
		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_TV && bIn == false)
		{//外に出たら解除
			pPlayer->bTvGimmick = false;
		}

		BathWater* pBathWater = GetBathGimmick();
		SPEECHBUBBLE* pSpeachBubble = GetSpeechBubble();
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_BATH && bIn == true)
		{//お風呂のギミック（1P）
			if (GetJoypadTrigger(JOYKEY_X, 0) == true)
			{//お風呂のギミック作動
				RunWater(0);
			}
		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_BATH
			&& pBathWater->bItemSpawn == true)
		{
			pActionZone[ZoneIndex].bUse = false;
			pSpeachBubble[ZoneIndex].bUse = false;
			pSpeachBubble[ZoneIndex].bOK = false;
		}

		bool pSpawnKey_Lever = GetSpawnKey_Lever();
		bool pSpawnKey_LeverTtl = GetSpawnKey_Leverttl();

		if ((pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_1
			|| pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_2)
			&& pSpawnKey_Lever == true)
		{//鍵がスポーンしたら削除
			pActionZone[ZoneIndex].bUse = false;
			pSpeachBubble[ZoneIndex].bUse = false;
			pSpeachBubble[ZoneIndex].bOK = false;

		}
		if ((pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_TUTORIAL1
			|| pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_TUTORIAL2)
			&& pSpawnKey_LeverTtl == true)
		{//チュートリアル鍵がスポーンしたら削除
			pActionZone[ZoneIndex].bUse = false;
			pSpeachBubble[ZoneIndex].bUse = false;
			pSpeachBubble[ZoneIndex].bOK = false;

		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_TUTORIAL1 && bIn == true)
		{//レバーのギミック（1P）
			if (GetJoypadPress(JOYKEY_X, 0) == true)
			{//レバーのギミック作動
				g_bTutorialLeverBlue = true;
			}
			if (GetJoypadRelease(JOYKEY_X, 0) == true)
			{
				g_bTutorialLeverBlue = false;
			}
		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_TUTORIAL2 && bIn == true)
		{//レバーのギミック（1P）
			if (GetJoypadPress(JOYKEY_X, 0) == true)
			{//レバーのギミック作動
				g_bTutorialLeverRed = true;
			}
			if (GetJoypadRelease(JOYKEY_X, 0) == true)
			{
				g_bTutorialLeverRed = false;
			}
		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_1 && bIn == true)
		{//レバーのギミック（1P）
			if (GetJoypadPress(JOYKEY_X, 0) == true)
			{//レバーのギミック作動
				g_bLever1 = true;
			}
			if (GetJoypadRelease(JOYKEY_X, 0) == true)
			{
				g_bLever1 = false;
			}
		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_2 && bIn == true)
		{//レバーのギミック（1P）
			if (GetJoypadPress(JOYKEY_X, 0) == true)
			{//レバーのギミック作動
				g_bLever2 = true;
			}
			if (GetJoypadRelease(JOYKEY_X, 0) == true)
			{
				g_bLever2 = false;
			}
		}
		if ((pActionZone[ZoneIndex].ActionType == ACTION_TYPE_KEY_1
			|| pActionZone[ZoneIndex].ActionType == ACTION_TYPE_KEY_2
			|| pActionZone[ZoneIndex].ActionType == ACTION_TYPE_KEY_3)
			&& bIn == true)
		{//鍵取得（1P）
			if (GetJoypadTrigger(JOYKEY_X, 0) == true)
			{//鍵のギミック作動
				g_nHaveKey++;
				pSpeachBubble[ZoneIndex].bUse = false;
				pSpeachBubble[ZoneIndex].bOK = false;
				pActionZone[ZoneIndex].bUse = false;
				switch (pActionZone[ZoneIndex].ActionType)
				{
				case ACTION_TYPE_KEY_1:
					GetKey(MODELTYPE_KEY1);
					break;

				case ACTION_TYPE_KEY_2:
					GetKey(MODELTYPE_KEY2);
					break;

				case ACTION_TYPE_KEY_3:
					GetKey(MODELTYPE_KEY3);
					break;
				}
			}
		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_KITCHEN && bIn == true)
		{
			for (int i = 0; i < CNT_GAUGE; i++)
			{

				if (pGauge[i].bUse == true)
				{
					if (pGauge[i].type == GAUGETYPE_MAINBODY_1P || pGauge[i].type == GAUGETYPE_FRAME_1P)
					{
						pGauge[i].DrawOK = true;
					}
				}
			}

			if (GetJoypadPress(JOYKEY_X, 0) == true)
			{
				if (pPlayer->nHaveDish >= 1 && pPlayer->nHaveVegetable >= 1)
				{
					if (nKitchen == 0)
					{
						PlaySound(SOUND_LABEL_SE_COOK);
					}
					nKitchen++;
					for (int i = 0; i < CNT_GAUGE; i++)
					{
						if (pGauge[i].bUse == true)
						{
							if (pGauge[i].type == GAUGETYPE_MAINBODY_1P)
							{
								pGauge[i].Cnt_X = nKitchen;

							}
						}
					}


					if (nKitchen > 180)
					{
						StopSound(SOUND_LABEL_SE_COOK);
						SetItem(D3DXVECTOR3(3400.0f, 200.0f, -1360.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_SOUP);

						DeleteItem_UI(PlayerIndex, ITEMTYPE_DISH);
						DeleteItem_UI(PlayerIndex, ITEMTYPE_VEGETABLE);
						g_bSoup = true;
						nKitchen = 0;//二回目も可能

						for (int i = 0; i < CNT_GAUGE; i++)
						{
							if (pGauge[i].bUse == true)
							{
								if (pGauge[i].type == GAUGETYPE_MAINBODY_1P)
								{
									pGauge[i].Cnt_X = nKitchen;

								}
							}
						}

					}
				}
				else if (pPlayer->nHaveDish >= 1 && pPlayer->nHaveVegetable <= 0 && g_bSoup == false)
				{
					SetKeyinfo(NOT_HAVE_VEGETABLE, PlayerIndex);
				}
				else if (pPlayer->nHaveVegetable >= 1 && pPlayer->nHaveDish <= 0 && g_bSoup == false)
				{
					SetKeyinfo(NOT_HAVE_DISH, PlayerIndex);
				}
				else if (pPlayer->nHaveDish <= 0 && pPlayer->nHaveVegetable <= 0 && g_bSoup == false)
				{
					SetKeyinfo(NOT_HAVE_NEED_KITCHEN, PlayerIndex);
				}
			}
		}

		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_EYETRAP && bIn == true)
		{//視界トラップ（1P）
			if (GetJoypadTrigger(JOYKEY_X, 0) == true)
			{//視界トラップ作動
				SetEyeTrap(0);
			}
		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_CUPBOARD && bIn == true)
		{//食器棚（1P）
			if (GetJoypadTrigger(JOYKEY_X, 0) == true)
			{//皿ドロ
				if (pPlayer->nHaveDish <= 0)
				{//皿を一個以上持っていたら
					SetKeyinfo(SPAWN_DISH, 0);
					SetItem(D3DXVECTOR3(3365.0f, 200.0f, -495.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_DISH);
					pPlayer->nHaveDish++;
				}
			}
		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_DESK && bIn == true)
		{//食卓(１P)
			if (GetJoypadPress(JOYKEY_X, 0) == true)
			{
				int nHaveSoup = pPlayer->nHaveSoup;
				if (nHaveSoup <= 0)
				{
					//スープ無いとき
					SetKeyinfo(NOT_HAVE_SOUP, PlayerIndex);
					return;
				}
				else
				{
					for (int nCnt = 0; nCnt < nHaveSoup; nCnt++)
					{
						DeleteItem_UI(PlayerIndex, ITEMTYPE_SOUP);
						//pPlayer->nHaveSoup--;
					}
					g_bDesk = true;
					pSpeachBubble[ZoneIndex].bUse = false;
					pSpeachBubble[ZoneIndex].bOK = false;
					pActionZone[ZoneIndex].bUse = false;
				}
			}
		}

		//仮
		if (g_bDesk == true)
		{
			MAPOBJECT* pModel = GetMapObject();
			for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++, pModel++)
			{
				if (pModel->nType == MODELTYPE_DESK)
				{
					SetModel(D3DXVECTOR3(pModel->pos.x - 30.0f, pModel->pos.y + 70.0f, pModel->pos.z), pModel->rot, MODELTYPE_KEY3);
					SetBill(D3DXVECTOR3(pModel->pos.x + 30.0f, pModel->pos.y + 55.0f, pModel->pos.z), BILLTYPE_SOUP);
					SetKeyinfo(SPAWNPLACE_LIVING, -1);
					g_bDesk = false;
				}
			}
		}



		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_PURIFICATION && bIn == true)
		{//浄化装置
			if (GetJoypadPress(JOYKEY_X, 0) == true)
			{//
				SetKeyinfo(PUSH_CREEN, -1);
				PlaySound(SOUND_LABEL_SE_BUTTON);
				//風呂を浄化
				pBathWater->bUse = false;

				//確定緑風呂
				MAPOBJECT* pMapObject;
				pMapObject = GetMapObject();

				for (int i = 0; i < MAX_MODEL; i++)
				{
					if (pMapObject[i].bUse == true)
					{
						if (pMapObject[i].nType == MODELTYPE_BATH)
						{
							SetBathWater(D3DXVECTOR3(pMapObject[i].pos.x, pMapObject[i].pos.y + 40.0f, pMapObject[i].pos.z)
								, D3DXVECTOR3(pMapObject[i].rot.x, D3DX_PI * 0.5f, pMapObject[i].rot.z)
								, BATHWATER_WIDE
								, BATHWATER_DEPTH
								, BATH_WATER);
						}
					}
				}

				pSpeachBubble[ZoneIndex].bUse = false;
				pSpeachBubble[ZoneIndex].bOK = false;
				pActionZone[ZoneIndex].bUse = false;
			}
		}
	}
	else if (PlayerIndex == 1)
	{//2Pの時
		if (bIn == true)
		{//接触判定時

			pActionZone[ZoneIndex].ZoneColor = D3DXCOLOR(1.0f, 5.0f, 2.0f, 0.2f);
			pActionZone[ZoneIndex].bDrawOk = false;
		}
		else
		{
			pActionZone[ZoneIndex].bDrawOk = true;
		}

		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_MONEYBOX && bIn == true)
		{//金庫のギミック（2P）
			if (GetJoypadTrigger(JOYKEY_X, 1) == true && pPlayer->bMoneyBoxGimmick != true)
			{//金庫のギミック作動
				pPlayer2->bMoneyBoxGimmick = pPlayer2->bMoneyBoxGimmick ? false : true;
				if (pPlayer2->bMoneyBoxGimmick == true)
				{
					g_MoneyboxPlayer = true;
				}
			}
		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_MONEYBOX && bIn == false)
		{//外に出たら解除
			pPlayer2->bMoneyBoxGimmick = false;
		}
		//動作ごとに分岐
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_MAX)
		{//

		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_TV && bIn == true)
		{//テレビのギミック
			pPlayer2->bTvGimmick = true;

			if (GetJoypadTrigger(JOYKEY_X, 1) == true)
			{
				TVController(PlayerIndex);
			}
		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_TV && bIn == false)
		{//外に出たら解除
			pPlayer2->bTvGimmick = false;
		}
		SPEECHBUBBLE* pSpeachBubble = GetSpeechBubble();
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_BATH && bIn == true)
		{//お風呂のギミック（1P）
			if (GetJoypadTrigger(JOYKEY_X, 1) == true)
			{//お風呂のギミック作動
				RunWater(1);
			}
		}
		BathWater* pBathWater = GetBathGimmick();
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_BATH
			&& pBathWater->bItemSpawn == true)
		{
			pActionZone[ZoneIndex].bUse = false;
			pSpeachBubble[ZoneIndex].bUse = false;
			pSpeachBubble[ZoneIndex].bOK = false;
		}
		bool pSpawnKey = GetSpawnKey_Lever();
		bool pSpawnKeyTtl = GetSpawnKey_Leverttl();

		if ((pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_1
			|| pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_2)
			&& pSpawnKey == true)
		{//鍵がスポーンしたら削除
			pActionZone[ZoneIndex].bUse = false;
			pSpeachBubble[ZoneIndex].bUse = false;
			pSpeachBubble[ZoneIndex].bOK = false;
		}
		if ((pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_TUTORIAL1
			|| pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_TUTORIAL2)
			&& pSpawnKeyTtl == true)
		{//チュートリアル鍵がスポーンしたら削除
			pActionZone[ZoneIndex].bUse = false;
			pSpeachBubble[ZoneIndex].bUse = false;
			pSpeachBubble[ZoneIndex].bOK = false;
		}

		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_TUTORIAL1 && bIn == true)
		{//レバーのギミック（1P）
			if (GetJoypadPress(JOYKEY_X, 1) == true)
			{//レバーのギミック作動
				g_bTutorialLeverBlue = true;
			}
			if (GetJoypadRelease(JOYKEY_X, 1) == true)
			{
				g_bTutorialLeverBlue = false;
			}
		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_TUTORIAL2 && bIn == true)
		{//レバーのギミック（1P）
			if (GetJoypadPress(JOYKEY_X, 1) == true)
			{//レバーのギミック作動
				g_bTutorialLeverRed = true;
			}
			if (GetJoypadRelease(JOYKEY_X, 1) == true)
			{
				g_bTutorialLeverRed = false;
			}
		}

		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_1 && bIn == true)
		{//レバーのギミック（1P）
			if (GetJoypadPress(JOYKEY_X, 1) == true)
			{//レバーのギミック作動
				g_bLever1 = true;
			}
			if (GetJoypadRelease(JOYKEY_X, 1) == true)
			{
				g_bLever1 = false;
			}
		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_LEVER_2 && bIn == true)
		{//レバーのギミック（1P）
			if (GetJoypadPress(JOYKEY_X, 1) == true)
			{//レバーのギミック作動
				g_bLever2 = true;
			}
			if (GetJoypadRelease(JOYKEY_X, 1) == true)
			{
				g_bLever2 = false;
			}

		}
		if ((pActionZone[ZoneIndex].ActionType == ACTION_TYPE_KEY_1
			|| pActionZone[ZoneIndex].ActionType == ACTION_TYPE_KEY_2
			|| pActionZone[ZoneIndex].ActionType == ACTION_TYPE_KEY_3)
			&& bIn == true)
		{//鍵取得（2P）
			if (GetJoypadTrigger(JOYKEY_X, 1) == true)
			{//鍵のギミック作動
				g_nHaveKey++;
				pSpeachBubble[ZoneIndex].bUse = false;
				pSpeachBubble[ZoneIndex].bOK = false;
				pActionZone[ZoneIndex].bUse = false;
				switch (pActionZone[ZoneIndex].ActionType)
				{
				case ACTION_TYPE_KEY_1:
					GetKey(MODELTYPE_KEY1);
					break;

				case ACTION_TYPE_KEY_2:
					GetKey(MODELTYPE_KEY2);
					break;

				case ACTION_TYPE_KEY_3:
					GetKey(MODELTYPE_KEY3);
					break;
				}
			}
		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_KITCHEN && bIn == true)
		{
			for (int i = 0; i < CNT_GAUGE; i++)
			{

				if (pGauge[i].bUse == true)
				{
					if (pGauge[i].type == GAUGETYPE_MAINBODY_2P || pGauge[i].type == GAUGETYPE_FRAME_2P)
					{
						pGauge[i].DrawOK = true;
					}
				}
			}
			if (GetJoypadPress(JOYKEY_X, 1) == true)
			{
				if (pPlayer2->nHaveDish >= 1 && pPlayer2->nHaveVegetable >= 1)
				{
					if (nKitchen == 0)
					{
						PlaySound(SOUND_LABEL_SE_COOK);
					}
					nKitchen++;

					for (int i = 0; i < CNT_GAUGE; i++)
					{

						if (pGauge[i].bUse == true)
						{
							if (pGauge[i].type == GAUGETYPE_MAINBODY_2P)
							{
								pGauge[i].Cnt_X = nKitchen;
							}
						}
					}

					if (nKitchen > 180)
					{
						StopSound(SOUND_LABEL_SE_COOK);
						SetItem(D3DXVECTOR3(3400.0f, 200.0f, -1360.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_SOUP);

						g_bSoup = true;
						DeleteItem_UI(PlayerIndex, ITEMTYPE_DISH);
						DeleteItem_UI(PlayerIndex, ITEMTYPE_VEGETABLE);
						nKitchen = 0;
						for (int i = 0; i < CNT_GAUGE; i++)
						{
							if (pGauge[i].bUse == true)
							{
								if (pGauge[i].type == GAUGETYPE_MAINBODY_2P)
								{
									pGauge[i].Cnt_X = nKitchen;
								}
							}
						}
					}
				}
				else if (pPlayer2->nHaveDish >= 1 && pPlayer2->nHaveVegetable <= 0 && g_bSoup == false)
				{
					SetKeyinfo(NOT_HAVE_VEGETABLE, PlayerIndex);
				}
				else if (pPlayer2->nHaveVegetable >= 1 && pPlayer2->nHaveDish <= 0 && g_bSoup == false)
				{
					SetKeyinfo(NOT_HAVE_DISH, PlayerIndex);
				}
				else if (pPlayer2->nHaveDish <= 0 && pPlayer2->nHaveVegetable <= 0 && g_bSoup == false)
				{
					SetKeyinfo(NOT_HAVE_NEED_KITCHEN, PlayerIndex);
				}
			}
		}

		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_EYETRAP && bIn == true)
		{//視界トラップ（2P）
			if (GetJoypadTrigger(JOYKEY_X, 1) == true)
			{//視界トラップ作動
				SetEyeTrap(1);
			}
		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_CUPBOARD && bIn == true)
		{//食器棚（2P）
			if (GetJoypadTrigger(JOYKEY_X, 1) == true)
			{//視界トラップ作動
				if (pPlayer2->nHaveDish <= 0)
				{//皿を一個以上持っていたら
					SetKeyinfo(SPAWN_DISH, 1);
					SetItem(D3DXVECTOR3(3365.0f, 200.0f, -495.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_DISH);
					pPlayer2->nHaveDish++;
				}
			}
		}
		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_DESK && bIn == true)
		{//食卓(2P)
			if (GetJoypadPress(JOYKEY_X, 1) == true)
			{
				int nHaveSoup = pPlayer2->nHaveSoup;

				if (nHaveSoup <= 0)
				{
					//スープ無いとき
					SetKeyinfo(NOT_HAVE_SOUP, PlayerIndex);
					return;
				}
				else
				{
					for (int nCnt = 0; nCnt < nHaveSoup; nCnt++)
					{
						DeleteItem_UI(PlayerIndex, ITEMTYPE_SOUP);
					}
					g_bDesk = true;
					pSpeachBubble[ZoneIndex].bUse = false;
					pSpeachBubble[ZoneIndex].bOK = false;
					pActionZone[ZoneIndex].bUse = false;
				}
			}
		}
		//仮
		if (g_bDesk == true)
		{
			MAPOBJECT* pModel = GetMapObject();
			for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++, pModel++)
			{
				if (pModel->nType == MODELTYPE_DESK)
				{
					SetModel(D3DXVECTOR3(pModel->pos.x - 30.0f, pModel->pos.y + 70.0f, pModel->pos.z), pModel->rot, MODELTYPE_KEY3);
					SetBill(D3DXVECTOR3(pModel->pos.x + 30.0f, pModel->pos.y + 55.0f, pModel->pos.z), BILLTYPE_SOUP);
					SetKeyinfo(SPAWNPLACE_LIVING, -1);
					g_bDesk = false;
				}
			}
			////スープ無いとき
			//SetKeyinfo(NOT_HAVE_SOUP, PlayerIndex);
		}

		if (pActionZone[ZoneIndex].ActionType == ACTION_TYPE_PURIFICATION && bIn == true)
		{//浄化装置
			if (GetJoypadPress(JOYKEY_X, 1) == true)
			{//
				PlaySound(SOUND_LABEL_SE_BUTTON);
				SetKeyinfo(PUSH_CREEN, -1);
				//風呂を浄化
				pBathWater->bUse = false;

				//確定緑風呂
				MAPOBJECT* pMapObject;
				pMapObject = GetMapObject();

				for (int i = 0; i < MAX_MODEL; i++)
				{
					if (pMapObject[i].bUse == true)
					{
						if (pMapObject[i].nType == MODELTYPE_BATH)
						{
							SetBathWater(D3DXVECTOR3(pMapObject[i].pos.x, pMapObject[i].pos.y + 40.0f, pMapObject[i].pos.z)
								, D3DXVECTOR3(pMapObject[i].rot.x, D3DX_PI * 0.5f, pMapObject[i].rot.z)
								, BATHWATER_WIDE
								, BATHWATER_DEPTH
								, BATH_WATER);
						}
					}
				}
				pSpeachBubble[ZoneIndex].bUse = false;
				pSpeachBubble[ZoneIndex].bOK = false;
				pActionZone[ZoneIndex].bUse = false;
			}
		}

	}
}
//===================================
//敵の視野に入った判定
//===================================
void SphereEnemyView(D3DXVECTOR3 PlayerPos, int PlayerIndex, int ZoneIndex)
{
	Camera* pCamera;
	pCamera = GetCamera();

	Player* pPlayer;
	pPlayer = GetPlayer();

	Player_2P* pPlayer2;
	pPlayer2 = GetPlayer_2P();


	ENEMYVIEW* pEnemyView;
	pEnemyView = GetEnemy_View();


	float PlayerCenterCorre = 45.0f;

	//接触したか
	bool bIn = false;

	//プレイヤーのposとエリアのposの差分を計算

	//差分ベクトル格納
	D3DXVECTOR3 diff;
	//1Pのとき
	if (PlayerIndex == 0)
	{
		PlayerPos.y += PlayerCenterCorre;//中心位置補正

		//差分ベクトルを計算
		diff = PlayerPos - pEnemyView[ZoneIndex].pos;

	}
	else if (PlayerIndex == 1)
	{//2Pの時
		PlayerPos.y += PlayerCenterCorre;//中心位置補正

		//差分ベクトルを計算
		diff = PlayerPos - pEnemyView[ZoneIndex].pos;
	}



	//各要素を二乗して入れる
	float squaredLength = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;

	//平方根を取る（直線差分）
	float distance = sqrt(squaredLength);

	if (distance < pEnemyView[ZoneIndex].Radius)
	{//差分の距離が半径より短い==円の中にいる時
		bIn = true;//接触判定
	}

	if (PlayerIndex == 0)
	{
		if (bIn == true)
		{

			pEnemyView[ZoneIndex].ZoneColor = D3DXCOLOR(1.0f, 5.0f, 2.0f, 0.2f);
			pEnemyView[ZoneIndex].bDrawOk = false;
			ActionEnemy(ACTIONPATTERN_ENEMY_CHASE, PlayerIndex);
		}
		else
		{
			pEnemyView[ZoneIndex].bDrawOk = true;
		}
	}
	else if (PlayerIndex == 1)
	{
		if (bIn == true)
		{

			pEnemyView[ZoneIndex].ZoneColor = D3DXCOLOR(1.0f, 5.0f, 2.0f, 0.2f);
			pEnemyView[ZoneIndex].bDrawOk = false;
			ActionEnemy(ACTIONPATTERN_ENEMY_CHASE, PlayerIndex);
		}
		else
		{
			pEnemyView[ZoneIndex].bDrawOk = true;
		}
	}
}

//===================================
//プレイヤー箱型当たり判定--アイテム
//===================================
void BoxCollisionItem(D3DXVECTOR3 PlayerMin, D3DXVECTOR3 PlayerMax, D3DXVECTOR3 HitPos, int PlayerIndex, int ItemIndex)
{//当たり判定
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ITEM* pItem;
	pItem = GetItem();

	bool bGet = false;


	float ADD = 50.0f;

	PlayerMin = D3DXVECTOR3(PlayerMin.x - ADD, PlayerMin.y - ADD, PlayerMin.z - ADD);
	PlayerMax = D3DXVECTOR3(PlayerMax.x + ADD, PlayerMax.y + ADD, PlayerMax.z + ADD);




	if (HitPos.x >= PlayerMin.x && HitPos.x <= PlayerMax.x)
	{
		if (HitPos.y >= PlayerMin.y && HitPos.y <= PlayerMax.y)
		{
			if (HitPos.z >= PlayerMin.z && HitPos.z <= PlayerMax.z)
			{
				bGet = true;
			}
		}
	}

	//1Pのとき
	if (PlayerIndex == 1)
	{
		//Player* pPlayer;
		//pPlayer = GetPlayer();
		if (bGet == true)
		{
			GetItem_FromUI(ItemIndex, 1);
		}
	}
	else if (PlayerIndex == 2)
	{//2Pの時
		Player_2P* pPlayer2;
		pPlayer2 = GetPlayer_2P();
		if (bGet == true)
		{
			GetItem_FromUI(ItemIndex, 2);
			//		pItemCnt_2P[pItem[ItemIndex].ItemType].ItemCnt++;
			//		pItem[ItemIndex].bUse = false;
		}
	}
}



//===================================
//アイテム用当たり判定
//===================================
void BoxCollisionFromItem(D3DXVECTOR3 ItemMin, D3DXVECTOR3 ItemMax, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax, int ItemIndex)
{//当たり判定

	ITEM* pItem;
	pItem = GetItem();


	bool OverPenetration = true;//過貫通疑惑を判定--の予定

	//---------------------------------------X方向
	if (ItemMin.z < HitMax.z &&
		ItemMax.z > HitMin.z &&
		ItemMax.x - pItem[ItemIndex].pos.x + pItem[ItemIndex].oldPos.x <= HitMin.x &&
		ItemMax.x > HitMin.x &&
		ItemMin.y < HitMax.y &&
		ItemMax.y > HitMin.y)
	{
		pItem[ItemIndex].move.x = 0.0f;
		pItem[ItemIndex].pos.x = HitMin.x + (ItemMin.x - pItem[ItemIndex].pos.x) - 0.1f;

		OverPenetration = false;
	}

	if (ItemMin.z < HitMax.z &&
		ItemMax.z > HitMin.z &&
		ItemMin.x - pItem[ItemIndex].pos.x + pItem[ItemIndex].oldPos.x >= HitMax.x &&
		ItemMin.x < HitMax.x &&
		ItemMin.y < HitMax.y &&
		ItemMax.y > HitMin.y)
	{
		pItem[ItemIndex].move.x = 0.0f;
		pItem[ItemIndex].pos.x = HitMax.x + (ItemMax.x - pItem[ItemIndex].pos.x) + 0.1f;
		OverPenetration = false;
	}

	//---------------------------------------Z方向
	if (ItemMin.x < HitMax.x &&
		ItemMax.x > HitMin.x &&
		ItemMin.z - pItem[ItemIndex].pos.z + pItem[ItemIndex].oldPos.z >= HitMax.z &&
		ItemMin.z < HitMax.z &&
		ItemMin.y < HitMax.y &&
		ItemMax.y > HitMin.y)
	{
		pItem[ItemIndex].move.z = 0.0f;
		pItem[ItemIndex].pos.z = HitMax.z - (ItemMin.z - pItem[ItemIndex].pos.z) + 0.1f;
		OverPenetration = false;
	}

	if (ItemMin.x < HitMax.x &&
		ItemMax.x > HitMin.x &&
		ItemMax.z - pItem[ItemIndex].pos.z + pItem[ItemIndex].oldPos.z <= HitMin.z &&
		ItemMax.z > HitMin.z &&
		ItemMin.y < HitMax.y &&
		ItemMax.y > HitMin.y)
	{
		pItem[ItemIndex].move.z = 0.0f;
		pItem[ItemIndex].pos.z = HitMin.z - (ItemMax.z - pItem[ItemIndex].pos.z) - 0.1f;
		OverPenetration = false;
	}

	//------------------------------------Y方向
	if (ItemMin.x < HitMax.x &&
		ItemMax.x > HitMin.x &&
		ItemMin.z < HitMax.z &&
		ItemMax.z > HitMin.z &&
		ItemMin.y - pItem[ItemIndex].pos.y + pItem[ItemIndex].oldPos.y >= HitMax.y &&
		ItemMin.y < HitMax.y)
	{
		pItem[ItemIndex].move.y = 0.0f;
		pItem[ItemIndex].pos.y = HitMax.y + (ItemMin.y - pItem[ItemIndex].pos.y);

		pItem[ItemIndex].bRetentionl = true;//滞留に
		pItem[ItemIndex].HitPosY = pItem[ItemIndex].pos.y + 0.1f;//接触位置更新

	}
	else
	{

		pItem[ItemIndex].HitPosY = 0.0f;//接触位置更新
	}






#if _DEBUG
	// 上下の辺
	SetLine(D3DXVECTOR3(HitMin.x, HitMax.y, HitMin.z), D3DXVECTOR3(HitMax.x, HitMax.y, HitMin.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMin.x, HitMin.y, HitMin.z), D3DXVECTOR3(HitMax.x, HitMin.y, HitMin.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	SetLine(D3DXVECTOR3(HitMin.x, HitMax.y, HitMax.z), D3DXVECTOR3(HitMax.x, HitMax.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMin.x, HitMin.y, HitMax.z), D3DXVECTOR3(HitMax.x, HitMin.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	// 側面の辺																											
	SetLine(D3DXVECTOR3(HitMin.x, HitMin.y, HitMin.z), D3DXVECTOR3(HitMin.x, HitMax.y, HitMin.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMax.x, HitMin.y, HitMin.z), D3DXVECTOR3(HitMax.x, HitMax.y, HitMin.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	SetLine(D3DXVECTOR3(HitMin.x, HitMin.y, HitMax.z), D3DXVECTOR3(HitMin.x, HitMax.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMax.x, HitMin.y, HitMax.z), D3DXVECTOR3(HitMax.x, HitMax.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));


	// その他の辺																									   
	SetLine(D3DXVECTOR3(HitMin.x, HitMin.y, HitMin.z), D3DXVECTOR3(HitMin.x, HitMin.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMax.x, HitMax.y, HitMin.z), D3DXVECTOR3(HitMax.x, HitMax.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	SetLine(D3DXVECTOR3(HitMin.x, HitMax.y, HitMin.z), D3DXVECTOR3(HitMin.x, HitMax.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	SetLine(D3DXVECTOR3(HitMax.x, HitMin.y, HitMin.z), D3DXVECTOR3(HitMax.x, HitMin.y, HitMax.z), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
#endif

}











//===================================
//転移番号参照--player1
//===================================
int GetTRansNumPlayer(void)
{
	return g_PlayerTransNum;//ポインターではない

}
//===================================
//転移番号参照--player2
//===================================
int GetTRansNumPlayer2(void)
{
	return g_Player2TransNum;//ポインターではない

}

//===================================
//転移番号上げ--player1
//===================================
void TRansNumPlayerUP(void)
{
	if (g_PlayerTransNum < 8)
	{
		g_PlayerTransNum++;
	}
	else
	{
		g_PlayerTransNum = 4;
	}
}
//===================================
//転移番号上げ--player2
//===================================
void TRansNumPlayer2UP(void)
{
	if (g_Player2TransNum < 8)
	{
		g_Player2TransNum++;
	}
	else
	{
		g_Player2TransNum = 4;
	}
}

//===================================
//転移番号下げ--player1
//===================================
void TRansNumPlayerDOWN(void)
{
	if (g_PlayerTransNum > 0)
	{
		g_PlayerTransNum--;
	}
	else
	{
		g_PlayerTransNum = 8;
	}
}
//===================================
//転移番号下げ--player1
//===================================
void TRansNumPlayer2DOWN(void)
{
	if (g_Player2TransNum > 0)
	{
		g_Player2TransNum--;
	}
	else
	{
		g_Player2TransNum = 8;
	}
}

//===================================
//更新停止--player1
//===================================
void PlayerUpdateStop(void)
{
	g_PlayerUpdateOk = false;
}
//===================================
//更新停止--player2
//===================================
void Player2UpdateStop(void)
{
	g_Player2UpdateOk = false;
}


//====================================
//ランダム選出
//====================================
int RandSelect(int nMax)
{
	int Random = ((float)rand() / RAND_MAX) * nMax;
	return Random;
}

//====================================
//長押し
//====================================
bool LongPress(int nButton, int nTime, int nPlayer)
{
	int nCntTime = nTime;
	if (GetJoypadPress((JOYkey)nButton, nPlayer) == true)
	{
		nCntTime--;
		if (nCntTime <= 0)
		{
			return true;
		}
	}
	return false;
}