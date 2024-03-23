//=========================================================
//
//ポーズ画面で使う変数、宣言、構造体[moneybox.h]
// Author matsuda towa
//
//=========================================================
#ifndef _MONEYBOX_H

#define _MONEYBOX_H//二重インクルード防止

#include"main.h"

//=========================================================
//マクロ定義
//=========================================================
#define NUM_DIGIT	(4) //桁数
#define MAX_NUMBER	(10) //数の最大

//=========================================================
//金庫の構造体
//=========================================================
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	int nSelectDigit;						//選択してる桁
	bool WhichPlayer; //どっちのプレイヤーが操作しているか false:1P,true:2P
}MONEYBOX;

//=========================================================
//プロトタイプ宣言
//=========================================================
void InitMoneybox(void);
void UninitMoneybox(void);
void UpdateMoneybox(void);
void DrawMoneybox(void);
void SetMonetbox(bool MoneyboxPlayer);
MONEYBOX* GetMoneybox(void);

#endif // !_MONEYBOX_H
