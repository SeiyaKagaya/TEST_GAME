//=========================================================
//
// 敵の処理[enemy.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _ENEMY_H_//このマクロが定義されてなかったら

#include "game.h"

//=============================================
//マクロ定義
//=============================================
#define _ENEMY_H_//二重インクルード防止のマクロ定義

#define BRENDFLAME_ENEMY	(15.0f)//モーションブレンドのフレーム数

#define MAX_WORD_ENEMY	(8192)//読み込む文字の最大数
#define MAX_PARTS_ENEMY	(60)//最大PARTS数
#define MAX_WORD2_ENEMY	(300)//最大文字数
#define MAX_MOTION_ENEMY	(30)//モーション最大数
#define MAXKEY_ENEMY	(240)//最大キー数
//エネミーサイズ(当たり判定用)
#define ENEMYMIN	(D3DXVECTOR3(-50.0f,0.0f,-50.0f))
#define ENEMYMAX	(D3DXVECTOR3(50.0f,185.0f,50.0f))
#define MAX_ENEMY_SPEED	(8)
#define ENEMY_FILE_NAME	"data\\motionEnigma.txt" //エネミーのファイルネーム



#define NUM_TEXTURE_ENEMY	(20)

//敵の行動パターン
typedef enum
{
	ACTIONPATTERN_ENEMY_STANDBY = 0,
	ACTIONPATTERN_ENEMY_SPAWN,
	ACTIONPATTERN_ENEMY_WALK,
	ACTIONPATTERN_ENEMY_CHASE,
	ACTIONPATTERN_ENEMY_ATTACK,
	ACTIONPATTERN_ENEMY_MAX,
}ACTIONPATTERN_ENEMY;

//モーション種別
typedef enum
{
	MOTIONTYPE_ENEMY_STANDBY = 0,
	MOTIONTYPE_ENEMY_MOVE,
	MOTIONTYPE_ENEMY_ATTACK,
	MOTIONTYPE_ENEMY_JUMP,
	MOTIONTYPE_ENEMY_RANDING,
	MOTIONTYPE_ENEMY_BREND,
	MOTIONTYPE_ENEMY_MAX,
}MOTIONTYPE_ENEMY;


//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 oldPos;//古い位置
	D3DXVECTOR3 MinPos;//最小位置
	D3DXVECTOR3 MaxPos;//最大位置
	D3DXVECTOR3 rot;	//向き
	D3DXVECTOR3 move;   //エネミーの移動
	float rotmove;//向き移動

	float fRotDest;//目的の向き

	ACTIONPATTERN_ENEMY ActionPattern; //行動パターン

	D3DXMATRIX mtxWorld;//ワールドマトリックス

	int PARENT;//親子関係-１は何にも属さない

	int nPlayerIdx; //追従するプレイヤー

//	MOTIONTYPE NowMotionUP;//現在のモーション状態上
	MOTIONTYPE_ENEMY NowMotionDOWN;//現在のモーション状態下

//	MOTIONTYPE OldMotionUP;//前回のモーション状態上
	MOTIONTYPE_ENEMY OldMotionDOWN;//現在のモーション状態下

	bool bUse;

	int NowKeyCntDOWN;//現在のキー位置
	int NowFrameCntDOWN;//現在のフレームの位置

	int NowKeyCntUP;//現在のキー位置
	int NowFrameCntUP;//現在のフレームの位置

	MOTIONTYPE_ENEMY TargetMotion;//目的地のモーション

	bool MotionLoopStop;//モーションストップが効いてるかどうか
	int JumpFrame;//ジャンプ
	bool JumpNow;//ジャンプしたか

	bool JumpOld;//ジャンプしたか古

	bool bLandingNow;//着地

	bool MotionBrend;//モーションブレンドモード

	int BrendCnt;//ブレンドカウンター
	MOTIONTYPE_ENEMY EscapeMotion;

}ENEMYMODEL;




//-------------------------------------------------------------------------ここからモデルパーツ/モーション系

typedef struct
{
	//あくまで、OFFSETから見た補正値
	D3DXVECTOR3 CorrectionPos;	//位置補正量
	D3DXVECTOR3 CorrectionRot;	//向き補正量
}PARTSDATA_ENEMY;//PARTSごとの補正データ

typedef struct
{
	int nSplitFrame;//分割フレーム数


	PARTSDATA_ENEMY PartsData[MAX_PARTS_ENEMY];//モーションの中でのパーツデータたち
}KEYDATA_ENEMY;//キー単位-----------Key数で変動

typedef struct
{
	int Motiontype;//MOTIONの種類//int型で仕様
	int nLoop;//ループするか[0:ループしない1:ループする]
	int nNumKey;//モーションのキーの数

	KEYDATA_ENEMY KeyData[MAXKEY_ENEMY];
}MOTION_ENEMY;//モーションのデータ--モーションの数ある

typedef struct
{
	//モーションの位置計算に運用、最後にMODELのDrawPosSに入れる
	D3DXVECTOR3 Pos;	//位置

	D3DXVECTOR3 Rot;	//向き

	int INDEX;//自分の番号
	int PEARENT;		//自分の親

	D3DXMATRIX mtxWorld;//ワールドマトリックス

	//はじめのTポーズ
	D3DXVECTOR3 StartPos;
	D3DXVECTOR3 StartRot;


	D3DXVECTOR3 CorrectCorrectionPosMove;//モーションでの移動量pos
	D3DXVECTOR3 CorrectCorrectionRotMove;//モーションでの移動量move
	bool calculationExecution;
}MODELPARTS_ENEMY;//現在のパーツのデータ

typedef struct
{
	int nMaxMotionCnt;//最大モーション数

	int nMaxPartsCnt;//最大パーツ数
	int nMaxLoadPartsCnt;//読み込む最大パーツ数

	MODELPARTS_ENEMY ModelParts[MAX_PARTS_ENEMY];//運用する現在のParts--X
	MOTION_ENEMY Motion[MAX_MOTION_ENEMY];//五代モーションなど

}MODEL_ENEMY;//モデル(という存在)

//プロトタイプ宣言
void InitEnemy(void);//プレイヤーの初期化処理
void UninitEnemy(void);//プレイヤーの終了処理
void UpdateEnemy(void);//プレイヤーの更新処理
void ActionEnemy(ACTIONPATTERN_ENEMY ActionPattern, int PlayerIdx); //アクションパターンによって処理変更
void DrawEnemy(void);//プレイヤーの描画処理

ENEMYMODEL* GetEnemy(void);

MODEL_ENEMY* GetEnemyModel(void);

LPD3DXMESH* GetMesh_Enemy(void);


//void InPutKeyboardAdvancedModel(void);//キーボード入力反映処理(移動)
//oid InPutControllerAdvancedModel(void);//キーボード/コントローラー入力反映処理(移動)
//int  CheckInputMove2(void);//移動キーの入力状態の有無を確認
//void InputKeyAttack(void);//攻撃キー系
void ConversionEnemyRot2(float fRot, int nCnt);//角度修正系

D3DXVECTOR3 ConversionEnemyRot3(D3DXVECTOR3 fRot, int nCnt);

void LoadSetEnemy3(void);//txtによるキャラのOFFSET
void LowerBodyEnemy3(void);//下半身モーション
//void UpperBodyMotion(void);//上半身モーション

//セット
void SetModel_Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot);


#endif // !_ADVANCEDMODEL_H_
