//=========================================================
//
//ポーズ画面で使う変数、宣言、構造体[password.h]
// Author matsuda towa
//
//=========================================================
#ifndef _PASSWORD_H

#define _PASSWORD_H//二重インクルード防止

#include"main.h"


//=========================================================
//マクロ定義
//=========================================================
#define NUM_DIGIT	(4) //桁数
#define NUM_PASSWORD	(5) //数の最大
#define TEX_ADD		(1.0f / (float)NUM_PASSWORD)
#define PASSWORD_FIRSTPOS_1P	(162.5f)
#define PASSWORD_FIRSTPOS_2P	(827.0f)
#define PASSWORD_ADDPOS	(105.0f)
#define PASSWORD_WIDE	(30.0f)
#define PASSWORD_HEIGHT	(30.0f)

//=========================================================
//パスワードの種類
//=========================================================
typedef enum
{
	PASSWORDTYPE_EYE = 0,
	PASSWORDTYPE_HAND,
	PASSWORDTYPE_LEAF,
	PASSWORDTYPE_HEART,
	PASSWORDTYPE_GRAVE,
	PASSWORDTYPE_MAX,
}PasswordType;

//=========================================================
//パスワード情報をもつ構造体
//=========================================================
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	PasswordType Type;						//タイプ
	int nType;								//タイプをずらすため
}PASSWORD;

//=========================================================
//プロトタイプ宣言
//=========================================================
void InitPassword(void);
void UninitPassword(void);
void UpdatePassword(void);
void DrawPassword(void);
void SetPassword(void);
void ChangePassword1P(D3DXCOLOR col, int nSelectDigit);
void ChangePassword2P(D3DXCOLOR col, int nSelectDigit);
#endif // !_PASSWORD_H