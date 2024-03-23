//=========================================================
//
// //高度モーションモデル関係で使う宣言など[advanced_motion_model.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _ADVANCEDMODEL_H_//このマクロが定義されてなかったら

#include "game.h"

//マクロ定義
#define _ADVANCEDMODEL_H_//二重インクルード防止のマクロ定義

#define BRENDFLAME_AD	(15.0f)//モーションブレンドのフレーム数

#define MAX_WORD_AD	(1024*3)//読み込む文字の最大数
#define MAX_PARTS_AD	(60)//最大PARTS数
#define MAX_WORD2_AD	(3200)//最大文字数
#define MAX_MOTION_AD	(30)//モーション最大数
#define MAXKEY_AD	(240)//最大キー数



#define NUM_TEXTURE_AD	(60)


//MODELの名前
typedef enum
{
	MODEL_AD_TYPE_Test1 = 0,//
	MODEL_AD_TYPE_Test2,
	MODEL_AD_TYPE_MAX,
}MODELADTYPE;

//モーション種別
typedef enum
{
	MOTIONTYPE_AD_STANDBY = 0,
	MOTIONTYPE_AD_MOVE,
	MOTIONTYPE_AD_ATTACK,
	MOTIONTYPE_AD_JUMP,
	MOTIONTYPE_AD_RANDING,
	MOTIONTYPE_AD_BREND,
	MOTIONTYPE_AD_MAX,
}MOTIONTYPE_AD;

//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き

	D3DXMATRIX mtxWorld;//ワールドマトリックス

	int PARENT;//親子関係-１は何にも属さない

//	MOTIONTYPE NowMotionUP;//現在のモーション状態上
	MOTIONTYPE_AD NowMotionDOWN;//現在のモーション状態下

//	MOTIONTYPE OldMotionUP;//前回のモーション状態上
	MOTIONTYPE_AD OldMotionDOWN;//現在のモーション状態下

	bool bUse;

	int NowKeyCntDOWN;//現在のキー位置
	int NowFrameCntDOWN;//現在のフレームの位置

	int NowKeyCntUP;//現在のキー位置
	int NowFrameCntUP;//現在のフレームの位置

	MOTIONTYPE_AD TargetMotion;//目的地のモーション

	bool MotionLoopStop;//モーションストップが効いてるかどうか
	int JumpFrame;//ジャンプ
	bool JumpNow;//ジャンプしたか

	bool JumpOld;//ジャンプしたか古

	bool bLandingNow;//着地

	bool MotionBrend;//モーションブレンドモード

	int BrendCnt;//ブレンドカウンター
	MOTIONTYPE_AD EscapeMotion;

}ADMODEL;




//-------------------------------------------------------------------------ここからモデルパーツ/モーション系

typedef struct
{
	//あくまで、OFFSETから見た補正値
	D3DXVECTOR3 CorrectionPos;	//位置補正量
	D3DXVECTOR3 CorrectionRot;	//向き補正量
}PARTSDATA_AD;//PARTSごとの補正データ

typedef struct
{
	int nSplitFrame;//分割フレーム数


	PARTSDATA_AD PartsData[MAX_PARTS_AD];//モーションの中でのパーツデータたち
}KEYDATA_AD;//キー単位-----------Key数で変動

typedef struct
{
	int Motiontype;//MOTIONの種類//int型で仕様
	int nLoop;//ループするか[0:ループしない1:ループする]
	int nNumKey;//モーションのキーの数

	KEYDATA_AD KeyData[MAXKEY_AD];
}MOTION_AD;//モーションのデータ--モーションの数ある

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
}MODELPARTS_AD;//現在のパーツのデータ

typedef struct
{
	int nMaxMotionCnt;//最大モーション数

	int nMaxPartsCnt;//最大パーツ数
	int nMaxLoadPartsCnt;//読み込む最大パーツ数

	MODELPARTS_AD ModelParts[MAX_PARTS_AD];//運用する現在のParts--X
	MOTION_AD Motion[MAX_MOTION_AD];//五代モーションなど

}MODEL_AD;//モデル(という存在)

//プロトタイプ宣言
void InitAdvancedModel(void);//プレイヤーの初期化処理
void UninitAdvancedModel(void);//プレイヤーの終了処理


void UpdateAdvancedModel(void);//プレイヤーの更新処理
void DrawAdvancedModel(void);//プレイヤーの描画処理

ADMODEL* GetAdvancedModel(int Index);

MODEL_AD* GetAdModel(int Index);

LPD3DXMESH* GetMesh_AdvancedModel(int Index);

void ConversionAdvancedModelRot2(int Index, float fRot, int nCnt);//角度修正系

void LoadSet3(int Index);//txtによるキャラのOFFSET
void LoadXfire_AdModel(int Index);//OFFセットでの情報からモデル読み込み


void LowerBodyMotion3(int Index);//下半身モーション



//セット
void SetModel_AD(MODELADTYPE ModelName, D3DXVECTOR3 pos, D3DXVECTOR3 rot);


#endif // !_ADVANCEDMODEL_H_
