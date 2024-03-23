//=============================================
//
//マップエディター[hitcollision_mistake_prevention.h]
//Auther seiya.kagaya
//
//=============================================
#ifndef _COLLISION_PRE_H_//このマクロが定義されてなかったら


//マクロ定義
#define _COLLISION_PRE_H_//二重インクルード防止のマクロ定義

#include "game.h"


#define MAXCOLLISION_PRE	(30)//転移門最大数



//構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置

	D3DXVECTOR3 Min;//最小
	D3DXVECTOR3 Max;//最大

	D3DXVECTOR3 SizeMag;//おおきさ倍率
	D3DXCOLOR GateColor;//門の色--ペアを同じ色にする

	D3DXMATRIX mtxWorld;
	bool bUse;
}COLLISION_PRE;


//プロトタイプ宣言
void InitCollision_Pre(void);//転移門の初期化処理
void UninitCollision_Pre(void);//転移門の終了処理
void UpdateCollision_Pre(void);//転移門の更新処理
void DrawCollision_Pre(void);//転移門の描画処理

COLLISION_PRE* GetCollision_Pre(void);

//---------------------座標------------------------最小--------------------最大---色
void SetCollision_Pre(D3DXVECTOR3 Pos, D3DXVECTOR3 GateMin, D3DXVECTOR3 GateMax ,D3DXCOLOR GateColor);



#endif // !_COLLISION_PRE_H_
