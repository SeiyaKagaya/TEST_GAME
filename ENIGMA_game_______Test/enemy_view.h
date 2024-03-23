//=========================================================
//
//敵の視野[enemy_view.h]
// Author Matsuda Towa
//
//=========================================================
#ifndef _ENEMYVIEW_H_//このマクロが定義されてなかったら

//マクロ定義
#define _ENEMYVIEWE_H_//二重インクルード防止のマクロ定義

#include "game.h"

//+++++++++++++++++++++++++++++++++++++++++
//--概要--
//+playerがこの中に入ったら追いかける
// 
//+++++++++++++++++++++++++++++++++++++++++

#define MAX_ENEMYVIEW	(300)//敵の視野最大数


//転移エリアサイズ(当たり判定用)
//#define GZONEMIN	(D3DXVECTOR3(-170.0f,0.0f,-170.0f))
//#define GZONEMAX	(D3DXVECTOR3(170.0f,120.0f,170.0f))

//構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置

	D3DXVECTOR3 ZoneMin;//最小
	D3DXVECTOR3 ZoneMax;//最大

	int Radius;//半径


	D3DXVECTOR3 SizeMag;//おおきさ倍率
	D3DXCOLOR ZoneColor;//門の色--ペアを同じ色にする

	D3DXCOLOR EscapeZoneColor;//門の色--ペアを同じ色にする-避難用


	D3DXMATRIX mtxWorld;

	int nZoneIndex;//自分の番号

	bool bFollowEnemy; //エネミーについてくかどうか
	bool bDrawOk;
	bool bUse;
}ENEMYVIEW;


//プロトタイプ宣言
void InitEnemy_View(void);//敵の視野の初期化処理
void UninitEnemy_View(void);//敵の視野の終了処理
void UpdateEnemy_View(void);//敵の視野の更新処理
void DrawEnemy_View(void);//敵の視野の描画処理

ENEMYVIEW* GetEnemy_View(void);

//-----------------------------自分座標-----------半径---------エネミーについてくかどうか-------色
void SetEnemy_View(D3DXVECTOR3 Pos, float Radius,bool bFollowEnemy, D3DXCOLOR ZoneColor);


#endif // !_EnemyView_H_
