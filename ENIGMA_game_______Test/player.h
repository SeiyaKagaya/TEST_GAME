//=========================================================
//
//プレイヤー関係で使う宣言など[player.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _PLAYER_H_//このマクロが定義されてなかったら

#include "game.h"

//マクロ定義
#define _PLAYER_H_//二重インクルード防止のマクロ定義

#define BRENDFLAME	(15.0f)//モーションブレンドのフレーム数


#define VIEWPOS (D3DXVECTOR3 (18.0f,70.0f,0.0f))//カメラ注視点
#define ITEMDROPPOS (D3DXVECTOR3 (5.0f,70.0f,0.0f))//アイテムスポーン
#define SPEECHPOS (D3DXVECTOR3 (35.0f,70.0f,0.0f))//カメラ注視点



#define NUM_TEXTURE_1P (20)

#define MOVESPEED		(0.7f)//移動速度(0.15)


//#define MOVESPEEDMAG	(1.2f)//空中移動倍率

#define DAMPING_RATIO	(0.20f)//減衰比--地上
#define DAMPING_RATIO2	(0.05f)//減衰比--空中

#define ROT_MOVESPEED		(0.04f)//旋回速度
#define ROT_DAMPING_RATIO	(0.4f)//旋回速度の減衰比

#define MAX_WORD	(1024*3)//読み込む文字の最大数
#define MAX_PARTS	(40)//最大PARTS数
#define MAX_WORD2	(300)//最大文字数
#define MAX_MOTION	(12)//モーション最大数
#define MAXKEY	(60)//最大キー数

//行動可能半径
#define MAXMAREA	(3000.0f)

//プレイヤーライフ(仮)
#define MAXLIFE		(300)

//プレイヤーサイズ(当たり判定用)
#define PLAYERMIN	(D3DXVECTOR3(-23.0f,0.0f,-23.0f))
#define PLAYERMAX	(D3DXVECTOR3(23.0f,85.0f,23.0f))

#define GRAVITY	(0.9f)//重力

typedef enum
{
	MOTIONTYPE_1P_STANDBY = 0,
	MOTIONTYPE_1P_MOVE,
	MOTIONTYPE_1P_ATTACK,
	MOTIONTYPE_1P_JUMP,
	MOTIONTYPE_1P_RANDING,
	MOTIONTYPE_1P_BREND,
	MOTIONTYPE_1P_SNEAK,
	MOTIONTYPE_1P_DAMAGE,
	MOTIONTYPE_1P_MAX,
}MOTIONTYPE;

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_1P_NOMAL = 0,
	PLAYERSTATE_1P_DAMEGE,
	PLAYERSTATE_1P_TELEPOR,
	PLAYERSTATE_1P_MAX,
}PLAYERSTATE;


//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 oldPos;//古い位置

	D3DXVECTOR3 rot;	//向き

	D3DXVECTOR3 move;   //プレイヤーの移動

	PLAYERSTATE PlayerState;//プレイヤー状態

	int PlayerStateCnt;

	int nLife;

	float rotmove;//向き移動

	float fRotDest;//目的の向き

	D3DXMATRIX mtxWorld;//ワールドマトリックス

	int PARENT;//親子関係-１は何にも属さない

//	MOTIONTYPE NowMotionUP;//現在のモーション状態上
	MOTIONTYPE NowMotionDOWN;//現在のモーション状態下

//	MOTIONTYPE OldMotionUP;//前回のモーション状態上
	MOTIONTYPE OldMotionDOWN;//現在のモーション状態下

	bool bUse;

	int NowKeyCntDOWN;//現在のキー位置
	int NowFrameCntDOWN;//現在のフレームの位置

	int NowKeyCntUP;//現在のキー位置
	int NowFrameCntUP;//現在のフレームの位置

	MOTIONTYPE TargetMotion;//目的地のモーション

	bool MotionLoopStop;//モーションストップが効いてるかどうか
	int JumpFrame;//ジャンプ
	bool JumpNow;//ジャンプしたか

	bool JumpOld;//ジャンプしたか古

	int nldShadow;//影番号

	bool bLandingNow;//着地
	bool bMoneyBoxGimmick; //金庫のギミックをしてるか
	bool bTvGimmick; //テレビを操作してるかどうか
	int nHaveRemocon; //リモコンを持っているか
	int nHaveDish; //皿を持っているか
	int nHaveVegetable; //野菜を持っているか
	int nHaveSoup;		//スープを持っているか

	bool bTransparent;//透明か
	
	bool bAction;//行動ボタン押した


	bool MotionBrend;//モーションブレンドモード
	int BrendCnt;//ブレンドカウンター
	MOTIONTYPE EscapeMotion;


	bool CrossRoadNow;//十字路にいるか

}Player;

///-------------------------------------------------------------------------追尾注視点
typedef struct
{
	D3DXVECTOR3 ViewPos;//プレイヤー追尾時注視点
	D3DXVECTOR3 ViewRot;
	D3DXMATRIX ViewPosMtx;//マトリックス
}View;
//--------------------------------------------------------------------------




//-------------------------------------------------------------------------ここからモデルパーツ/モーション系

typedef struct
{
	//あくまで、OFFSETから見た補正値
	D3DXVECTOR3 CorrectionPos;	//位置補正量
	D3DXVECTOR3 CorrectionRot;	//向き補正量
}PARTSDATA;//PARTSごとの補正データ

typedef struct
{
	int nSplitFrame;//分割フレーム数

	PARTSDATA PartsData[MAX_PARTS];//モーションの中でのパーツデータたち

}KEYDATA;//キー単位-----------Key数で変動

typedef struct
{
	int Motiontype;//MOTIONの種類//int型で仕様
	int nLoop;//ループするか[0:ループしない1:ループする]
	int nNumKey;//モーションのキーの数

	KEYDATA KeyData[MAXKEY];
}MOTION;//モーションのデータ--モーションの数ある

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
}MODELPARTS;//現在のパーツのデータ

typedef struct
{
	int nMaxMotionCnt;//最大モーション数

	int nMaxPartsCnt;//最大パーツ数
	int nMaxLoadPartsCnt;//読み込む最大パーツ数

	MODELPARTS ModelParts[MAX_PARTS];//運用する現在のParts--X
	MOTION Motion[MAX_MOTION];//五代モーションなど

}MODEL;//モデル(という存在)

//プロトタイプ宣言
void InitPlayer(void);//プレイヤーの初期化処理
void UninitPlayer(void);//プレイヤーの終了処理
void UpdatePlayer(void);//プレイヤーの更新処理
void DrawPlayer(int CameraLoopNum);//プレイヤーの描画処理

Player* GetPlayer(void);

MODEL* GetModel(void);//一時敵

View* GetView(void);//注視点を入手

LPD3DXMESH* GetMesh_Player(void);


void InPutKeyboardPlayer(void);//キーボード入力反映処理(移動)
void InPutControllerPlayer(void);//キーボード/コントローラー入力反映処理(移動)
int  CheckInputMove2(void);//移動キーの入力状態の有無を確認
void InputKeyAttack(void);//攻撃キー系
void ConversionPlayerRot2(float fRot, int nCnt);//角度修正系

void LoadSet(void);//txtによるキャラのOFFSET
void LowerBodyMotion(void);//下半身モーション
void UpperBodyMotion(void);//上半身モーション


//Xfireよみこみ
void LoadXfire_Player(void);//OFFセットでの情報からモデル読み込み

#endif // !_PLAYER_H_
