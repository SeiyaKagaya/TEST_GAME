//=========================================================
//
//DEBUGモデル関係で使う宣言など[DebugModel.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _DEBUGMODEL_H_//このマクロが定義されてなかったら



//マクロ定義
#define _DEBUGMODEL_H_//二重インクルード防止のマクロ定義

#include "game.h"
//+++++++++++++++++++++++++++++++++++++++++
//--概要--
//+当たり判定で、この中に入ったときに指定されたもんに飛ぶ
// +playerに転移直後かboolで無限跳躍を防ぐ予定
//+++++++++++++++++++++++++++++++++++++++++

#define MAXDEBUGMODEL	(30)//アクションエリア最大数


//転移エリアサイズ(当たり判定用)
//#define GZONEMIN	(D3DXVECTOR3(-170.0f,0.0f,-170.0f))
//#define GZONEMAX	(D3DXVECTOR3(170.0f,120.0f,170.0f))



////転移先の転移方向
//typedef enum
//{
//	ACTION_TYPE_A = 0,
//	ACTION_TYPE_MAX,//--進行方向に転移
//}ACTIONTYPE;
//




//構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置

	D3DXVECTOR3 ZoneMin;//最小
	D3DXVECTOR3 ZoneMax;//最大

	float Radius;//半径


	D3DXVECTOR3 SizeMag;//おおきさ倍率
	D3DXCOLOR ZoneColor;//門の色--ペアを同じ色にする

	D3DXCOLOR EscapeZoneColor;//門の色--ペアを同じ色にする-避難用


	D3DXMATRIX mtxWorld;

	int nZoneIndex;//自分の番号
//	int nParentIndex;//親の番号

//	ACTIONTYPE ActionType;//動作タイプ

//	bool bPossibility;//動作可能かどうか--鍵など、まだ手をつけない
	bool bUse;
}DEBUGMODEL;


//プロトタイプ宣言
void InitDebugModel(void);//アクションエリアの初期化処理
void UninitDebugModel(void);//アクションエリアの終了処理
void UpdateDebugModel(void);//アクションエリアの更新処理
void DrawDebugModel(void);//アクションエリアの描画処理

//DEBUGMODEL* GetDebugModel(void);

//球形
//-----------------------------自分座標-----------半径------------色--Beaconかどうか
void SetDebugModelSphere(float Radius,D3DXCOLOR ZoneColor,bool Beacon);
//四角
//-----------------------------自分座標-----------最小最大------------色
//void SetDebugModelBOX(D3DXVECTOR3 Min, D3DXVECTOR3 Max, D3DXCOLOR ZoneColor);


//設置用コメント
void DrawDebugDelComment(void);

//被りモデルを削除する処理
void DeleteCoveredModel(void);


#endif // !_DEBUGMODEL_H_
