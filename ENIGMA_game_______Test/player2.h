//=========================================================
//
//プレイヤー関係で使う宣言など[player2.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _PLAYER2_H_//このマクロが定義されてなかったら

#include "game.h"

//マクロ定義
#define _PLAYER2_H_//二重インクルード防止のマクロ定義

#define BRENDFLAME2	(15.0f)//モーションブレンドのフレーム数

#define NUM_TEXTURE_2P (20)


#define VIEWPOS2 (D3DXVECTOR3 (18.0f,70.0f,0.0f))
#define ITEMDROPPOS2 (D3DXVECTOR3 (5.0f,70.0f,0.0f))//アイテムドロップ注視点
#define SPEECHPOS2 (D3DXVECTOR3 (35.0f,70.0f,0.0f))//カメラ注視点



#define MOVESPEED_2P		(0.7f)//移動速度(0.15)
//#define MOVESPEED_2MAG	(1.2f)//空中移動倍率

#define DAMPING_RATIO_2P	(0.20f)//減衰比--地上
#define DAMPING_RATIO2_2P	(0.05f)//減衰比--空中

#define ROT_MOVESPEED_2P		(0.04f)//旋回速度
#define ROT_DAMPING_RATIO_2P	(0.4f)//旋回速度の減衰比

#define MAX_WORD_2P	(1024*3)//読み込む文字の最大数
#define MAX_PARTS_2P	(40)//最大PARTS数
#define MAX_WORD2_2P	(200)//最大文字数
#define MAX_MOTION_2P	(20)//モーション最大数
#define MAXKEY_2P	(60)//最大キー数

//行動可能半径
#define MAXMAREA_2P	(3000.0f)

//プレイヤーライフ(仮)
#define MAXLIFE_2P		(300)

//プレイヤーサイズ(当たり判定用)
#define PLAYERMIN_2P	(D3DXVECTOR3(-23.0f,0.0f,-23.0f))
#define PLAYERMAX_2P	(D3DXVECTOR3(23.0f,85.0f,23.0f))

#define GRAVITY_2P	(0.9f)//重力

typedef enum
{
	MOTIONTYPE_2P_STANDBY = 0,
	MOTIONTYPE_2P_MOVE,
	MOTIONTYPE_2P_ATTACK,
	MOTIONTYPE_2P_JUMP,
	MOTIONTYPE_2P_RANDING,
	MOTIONTYPE_2P_BREND,
	MOTIONTYPE_2P_SNEAK,
	MOTIONTYPE_2P_DAMAGE,
	MOTIONTYPE_2P_MAX,
}MOTIONTYPE_2P;

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_2P_NOMAL = 0,
	PLAYERSTATE_2P_DAMEGE,
	PLAYERSTATE_2P_TELEPOR,
	PLAYERSTATE_2P_MAX,
}PLAYERSTATE_2P;


//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 oldPos;//古い位置

	D3DXVECTOR3 rot;	//向き

	D3DXVECTOR3 move;   //プレイヤーの移動

	PLAYERSTATE_2P PlayerState;//プレイヤー状態

	int PlayerStateCnt;

	int nLife;

	float rotmove;//向き移動

	float fRotDest;//目的の向き

	D3DXMATRIX mtxWorld;//ワールドマトリックス

	int PARENT;//親子関係-１は何にも属さない

	MOTIONTYPE_2P NowMotionUP;//現在のモーション状態上
	MOTIONTYPE_2P NowMotionDOWN;//現在のモーション状態下

	MOTIONTYPE_2P OldMotionUP;//前回のモーション状態上
	MOTIONTYPE_2P OldMotionDOWN;//現在のモーション状態下

	bool bUse;

	int NowKeyCntDOWN;//現在のキー位置
	int NowFrameCntDOWN;//現在のフレームの位置

	int NowKeyCntUP;//現在のキー位置
	int NowFrameCntUP;//現在のフレームの位置

	MOTIONTYPE_2P TargetMotion;//目的地のモーション

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
	int nHaveSoup;	//スープをもっているか

	bool bAction;//行動ボタン

	bool bTransparent;//透明か


	bool MotionBrend;//モーションブレンドモード
	int BrendCnt;//ブレンドカウンター
	MOTIONTYPE_2P EscapeMotion;

	bool CrossRoadNow;//十字路にいるか
}Player_2P;



///-------------------------------------------------------------------------追尾注視点
typedef struct
{
	D3DXVECTOR3 ViewPos;//プレイヤー追尾時注視点
	D3DXVECTOR3 ViewRot;
	D3DXMATRIX ViewPosMtx;//マトリックス
}View2;


//-------------------------------------------------------------------------ここからモデルパーツ/モーション系

typedef struct
{
	//あくまで、OFFSETから見た補正値
	D3DXVECTOR3 CorrectionPos;	//位置補正量
	D3DXVECTOR3 CorrectionRot;	//向き補正量
}PARTSDATA_2P;//PARTSごとの補正データ

typedef struct
{
	int nSplitFrame;//分割フレーム数

	PARTSDATA_2P PartsData[MAX_PARTS_2P];//モーションの中でのパーツデータたち

}KEYDATA_2P;//キー単位-----------Key数で変動

typedef struct
{
	int Motiontype;//MOTIONの種類//int型で仕様
	int nLoop;//ループするか[0:ループしない1:ループする]
	int nNumKey;//モーションのキーの数

	KEYDATA_2P KeyData[MAXKEY_2P];
}MOTION_2P;//モーションのデータ--モーションの数ある

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
}MODELPARTS_2P;//現在のパーツのデータ

typedef struct
{
	int nMaxMotionCnt;//最大モーション数

	int nMaxPartsCnt;//最大パーツ数
	int nMaxLoadPartsCnt;//読み込む最大パーツ数

	MODELPARTS_2P ModelParts[MAX_PARTS_2P];//運用する現在のParts--X
	MOTION_2P Motion[MAX_MOTION_2P];//五代モーションなど

}MODEL_2P;//モデル(という存在)

//プロトタイプ宣言
void InitPlayer_2P(void);//プレイヤーの初期化処理
void UninitPlayer_2P(void);//プレイヤーの終了処理
void UpdatePlayer_2P(void);//プレイヤーの更新処理
void DrawPlayer_2P(int CameraLoopNum);//プレイヤーの描画処理

Player_2P* GetPlayer_2P(void);

MODEL_2P* GetModel_2P(void);//一時敵

View2* GetView_2P(void);//注視点を入手


LPD3DXMESH* GetMesh_Player_2P(void);


void InPutKeyboardPlayer_2P(void);//キーボード入力反映処理(移動)
void InPutControllerPlayer_2P(void);//キーボード/コントローラー入力反映処理(移動)
int  CheckInputMove2_2P(void);//移動キーの入力状態の有無を確認
void InputKeyAttack_2P(void);//攻撃キー系
void ConversionPlayerRot2_2P(float fRot, int nCnt);//角度修正系

void LoadSet_2P(void);//txtによるキャラのOFFSET
void LowerBodyMotion_2P(void);//下半身モーション
void UpperBodyMotion_2P(void);//上半身モーション

//Xfireよみこみ
void LoadXfire_Player2(void);//OFFセットでの情報からモデル読み込み


#endif // !_PLAYER2_H_
