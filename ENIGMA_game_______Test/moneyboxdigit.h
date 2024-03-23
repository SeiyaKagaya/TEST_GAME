//=========================================================
//
//ポーズ画面で使う変数、宣言、構造体[moneyboxdigit.h]
// Author matsuda towa
//
//=========================================================
#ifndef _MONEYBOXDIGIT_H

#define _MONEYBOXDIGIT_H//二重インクルード防止

#include"main.h"

//=========================================================
//マクロ定義
//=========================================================
#define NUM_DIGIT	(4) //桁数
#define MAX_NUMBER	(10) //数の最大

//=========================================================
//金庫の桁ごとの構造体
//=========================================================
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	bool WhichPlayer; //どっちのプレイヤーが操作しているか false:1P,true:2P
}MONEYBOXDIGIT;

//=========================================================
//プロトタイプ宣言
//=========================================================
void InitMoneyboxDigit(void);
void UninitMoneyboxDigit(void);
void UpdateMoneyboxDigit(void);
void ControlMoneybox1P(void);
void ControlMoneybox2P(void);
void DrawMoneyboxDigit(void);
void SetMoneyboxDigit(void);
void CorrectMoneyboxDigit(void);
void MistakeMoneyboxDigit(void);
bool GetClearMoneyBox(void);

#endif // !_MONEYBOX_H
