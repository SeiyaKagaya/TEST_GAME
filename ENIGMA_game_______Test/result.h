//=========================================================
//
//リザルト画面で使う変数、宣言、構造体[result.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _RESULT_H

#define _RESULT_H_//二重インクルード防止

#include"main.h"

//実はここでも良いらしい(C++では少し違うので注意)
#include "input.h"
#include "fade.h"
#include "sound.h"

//プロトタイプ宣言
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

#endif // !_RESULT_H_