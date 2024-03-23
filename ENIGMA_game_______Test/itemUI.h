//=========================================================
//
//弾発射処理関係で使う変数、宣言、構造体[item.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _ITEMUI_H_

#define _ITEMUI_H_//二重インクルード防止

#include"main.h"

#include "game.h"


#include "item.h"

#define ITEMTEXUINUM	(8)//テクスチャ最大数
#define MAXITEMUI	(32)//最大数

#define ITEMUISIZE	(32.0f)//サイズ
#define ITEMUISIZE2	(26.0f)//サイズ


#define MAXGETITEM	(3)//アイテム最大所持数

#define ITEMMOVESPEED_UI	(15.0f)

typedef enum
{
	ITEM_UI_TYPE_FRAME = 0,//枠
	ITEM_UI_TYPE_POINTER, //ポインター
	ITEM_UI_TYPE_MAINBODY,//本体
	ITEM_UI_TYPE_KEYUI,//鍵UI
	ITEM_UI_TYPE_MAX

}ITEM_UI_TYPE;



//の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	ITEM_UI_TYPE UItype;//UIのタイプ
	ITEMTYPE nItemType;//アイテムの種類
	
	int PosNum;//アイテム本体の時限定、座標位置番号を格納、その他は-1


	int PlayerNum;//プレイヤー番号1/2

	bool bUse;

}ITEM_UI;









void InitItem_UI(void);
void UninitItem_UI(void);
void UpdateItem_UI(bool Player1InputOK, bool Player2InputOK);
void DrawItem_UI(void);



void SetItem_UI(D3DXVECTOR3 pos, ITEM_UI_TYPE ItemUIType, ITEMTYPE ItemType,int PosNum,int PlayerNum);

void DrawHaveKey(int nHaveKey);



//アイテム減数処理
//void ItemRedProces_1P(void);

//アイテム取得できるか処理
void GetItem_FromUI(int ItemIndex,int PlayerNum);

//コントローラー入力反映処理(アイテムUI)
void InPutControllerITEM_UI(int PlayerNum);

//アイテム削除関数
void DeleteItem_UI(int PlayerNum, ITEMTYPE ItemType);

#endif // _ITEM_H_
