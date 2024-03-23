//=========================================================
//
//転移エリア関係で使う宣言など[transfergate.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _TRANSFERGATE_H_//このマクロが定義されてなかったら


//マクロ定義
#define _TRANSFERGATE_H_//二重インクルード防止のマクロ定義

#include "game.h"


//+++++++++++++++++++++++++++++++++++++++++
//--概要--
//+当たり判定で、この中に入ったときに指定されたもんに飛ぶ
// +playerに転移直後かboolで無限跳躍を防ぐ予定
//+++++++++++++++++++++++++++++++++++++++++

#define MAXGATE	(32)//転移門最大数

//転移先暗号
#define CLEAR_NUM	(MAXGATE - 5)
#define TRANSGATE_NUM	(MAXGATE - 4)
#define CROSSROAD_NUM	(MAXGATE - 3)
#define RONDOMTRANS_NUM	(MAXGATE - 2)
//#define RONDOMTRANS_NUM2	(MAXGATE - 1)

#define MAXROOM	(4)//部屋の数(ギミックあり)


//転移エリアサイズ(当たり判定用)
//#define GATEMIN	(D3DXVECTOR3(-170.0f,0.0f,-170.0f))
//#define GATEMAX	(D3DXVECTOR3(170.0f,120.0f,170.0f))



//転移先の転移方向
typedef enum
{
	TRANS_ANGLE_MIN_X = 1,
	TRANS_ANGLE_MAX_X,
	TRANS_ANGLE_MIN_Y,
	TRANS_ANGLE_MAX_Y,
	TRANS_ANGLE_MIN_Z,
	TRANS_ANGLE_MAX_Z,
	TRANS_ANGLE_RANDOM,
	TRANS_ANGLE_CLEAR,
	TRANS_ANGLE_MAX,//--進行方向に転移
}TRANSANGLE;






//構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	
	D3DXVECTOR3 GateMin;//最小
	D3DXVECTOR3 GateMax;//最大

	D3DXVECTOR3 SizeMag;//おおきさ倍率
	D3DXCOLOR GateColor;//門の色--ペアを同じ色にする

	D3DXMATRIX mtxWorld;

	int nGateIndex;//自分の番号
	int nParentIndex;//親の番号

	TRANSANGLE ParentTransAngle;//親の転移方向

	bool bPossibility;//転移可能かどうか--鍵など、まだ手をつけない

	bool bCompulsionTrans;//強制転移かどうか


	int nTeleportCnt;//転移カウント
	bool bActiomTrans;//行動ボタンで転移

	bool bUse;
}TRANSFERGATE;


//プロトタイプ宣言
void InitTransferGate(void);//転移門の初期化処理
void UninitTransferGate(void);//転移門の終了処理
void UpdateTransferGate(void);//転移門の更新処理
void DrawTransferGate(void);//転移門の描画処理

TRANSFERGATE* GetTransferGate(void);

//---------------------座標------------------------最小--------------------最大---------自分の番号----転移先の番号--色--強制転移かどうか---------行動ボタンで転移かどうか
void SetTransferGate(D3DXVECTOR3 Pos, D3DXVECTOR3 GateMin, D3DXVECTOR3 GateMax, int nGateIndex, int nParentIndex, TRANSANGLE ParentTransAngle,D3DXCOLOR GateColor, bool bCompulsionTrans,bool bActionTrans);

//転移暗転
void TeleportIN(int PlayerIndex, int GateIndex);
//転移明転
void TereportOUT();

#endif // !_TRANSFERGATE_H_
