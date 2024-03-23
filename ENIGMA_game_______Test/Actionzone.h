//=========================================================
//
//行動エリア関係で使う宣言など[Actionzone.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _ACTIONZONE_H_//このマクロが定義されてなかったら



//マクロ定義
#define _ACTIONZONE_H_//二重インクルード防止のマクロ定義

#include "game.h"
//+++++++++++++++++++++++++++++++++++++++++
//--概要--
//+当たり判定で、この中に入ったときに指定されたもんに飛ぶ
// +playerに転移直後かboolで無限跳躍を防ぐ予定
//+++++++++++++++++++++++++++++++++++++++++

#define MAXZONE	(264)//アクションエリア最大数


//転移エリアサイズ(当たり判定用)
//#define GZONEMIN	(D3DXVECTOR3(-170.0f,0.0f,-170.0f))
//#define GZONEMAX	(D3DXVECTOR3(170.0f,120.0f,170.0f))



//転移先の転移方向
typedef enum
{
	ACTION_TYPE_A = 0,
	ACTION_TYPE_MONEYBOX,	//金庫ギミック
	ACTION_TYPE_BATH,		//お風呂ギミック
	ACTION_TYPE_LEVER_1,	//レバーギミック
	ACTION_TYPE_LEVER_2,	//レバーギミック
	ACTION_TYPE_KEY_1,		//鍵ギミック
	ACTION_TYPE_KEY_2,		//鍵ギミック
	ACTION_TYPE_KEY_3,		//鍵ギミック
	ACTION_TYPE_EYETRAP,	//視界トラップ
	ACTION_TYPE_ESCAPE,		//移動
	ACTION_TYPE_TV,			//TVギミック
	ACTION_TYPE_GAMECLEAR,	//クリア
	ACTION_TYPE_CUPBOARD,	//食器棚
	ACTION_TYPE_KITCHEN,	//キッチン
	ACTION_TYPE_DESK,		//食卓
	ACTION_TYPE_PURIFICATION,//浄化装置
	ACTION_TYPE_LEVER_TUTORIAL1,//チュートリアルレバー
	ACTION_TYPE_LEVER_TUTORIAL2,//チュートリアルレバー
	ACTION_TYPE_MAX,		//--進行方向に転移
}ACTIONTYPE;





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
//	int nParentIndex;//親の番号

	ACTIONTYPE ActionType;//動作タイプ

	bool bPossibility;//動作可能かどうか--鍵など、まだ手をつけない
	bool bDrawOk;
	bool bUse;
}ACTIONZONE;


//プロトタイプ宣言
void InitActionZone(void);//アクションエリアの初期化処理
void UninitActionZone(void);//アクションエリアの終了処理
void UpdateActionZone(void);//アクションエリアの更新処理
void DrawActionZone(void);//アクションエリアの描画処理

ACTIONZONE* GetActionZone(void);

//-----------------------------自分座標-----------半径---------行動タイプ-------色
void SetActionZone(D3DXVECTOR3 Pos, float Radius, ACTIONTYPE ActionType, D3DXCOLOR ZoneColor);


#endif // !_ACTIONZONE_H_
