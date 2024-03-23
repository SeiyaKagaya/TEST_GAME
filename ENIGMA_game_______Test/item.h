//=========================================================
//
//弾発射処理関係で使う変数、宣言、構造体[item.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _ITEM_H_

#define _ITEM_H_//二重インクルード防止

#include"main.h"
#include "game.h"

#define NUMITEM	(64)//アイテムの最大数
//#define TEXNUM	(4)//テクスチャの数
#define ITEMSPEED	 (8)//アイテムの最初の速度
#define ITEMSIZE	(14.0f)
#define ITEMMOVESPEED_LOCK	(2.0f)
#define ITEMMOVESPEED	(4.0f)
#define ITEMDAMAGE	(15)


//アイテムサイズ
#define ITEMMIN	(D3DXVECTOR3(-14.0f,0.0f,-14.0f))
#define ITEMMAX	(D3DXVECTOR3(14.0f,28.0f,14.0f))


//の向いてる方向構造体
typedef enum
{
	ITEMTYPE_DISH = 0,	//皿
	ITEMTYPE_REMOCON,	//リモコン
	ITEMTYPE_VEGETABLE,	//野菜
	ITEMTYPE_SOUP,		//スープ
	ITEMTYPE_MAX,
}ITEMTYPE;












//の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 oldPos;	//古い位置
	float HitPosY;//接触したY座標

//	D3DXVECTOR3 pos2;	//浮遊用位置
	bool bfloatRot;//浮遊方向
	int  nfloatCnt;//浮遊カウント


	//D3DXVECTOR3 oldPos;

	//D3DXVECTOR3 rot;	//向き
	D3DXMATRIX mtxWorldItem;//ワールドマトリックス
	D3DXVECTOR3 move;		//移動
	ITEMTYPE ItemType;

	//int nLife;//ライフ
	int nShadowNum;//影番号

	bool bRetentionl;//滞留してるか

	int nStayGetCnt;//取得可能までの待機
	bool bGetNO;//取得できるか

	bool bUse;
}ITEM;

//の構造体
typedef struct
{
	int ItemCnt;



}ITEMCNT;




void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

ITEM* GetItem(void);

//ITEMCNT* GetItemCnt_1P(void);
//ITEMCNT* GetItemCnt_2P(void);

//設定
void SetItem(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, ITEMTYPE Type);

//設定2
void SetItem2(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, ITEMTYPE Type,int NoGetCnt);

#endif // _ITEM_H_
