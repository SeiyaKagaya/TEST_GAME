//=========================================================
//
//弾発射処理関係で使う変数、宣言、構造体[item.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _BILLBOARD_H_

#define _BILLBOARD_H_//二重インクルード防止

#include"main.h"

#define NUMBILL	(64)//ビルボードの最大数

//ビルボードの種類
typedef enum
{
	BILLTYPE_DISH = 0,
	BILLTYPE_REMOCON,
	BILLTYPE_VEGETABLE,
	BILLTYPE_SOUP,
	BILLTYPE_MAX
}BillType;

//ビルボードの構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXMATRIX mtxWorldBill;//ワールドマトリックス
	int nType;
	bool bUse;
}BILL;

void InitBill(void);
void UninitBill(void);
void UpdateBill(void);
void DrawBill(void);

//設定
void SetBill(D3DXVECTOR3 Pos, int nType);

#endif // _BILLBOARD_H_
