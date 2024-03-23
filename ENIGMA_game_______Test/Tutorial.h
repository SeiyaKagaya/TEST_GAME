//=========================================================
//
//チュートリアル画面で使う変数、宣言、構造体[tutorial.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _TUTORIAL_H

#define _TUTORIAL_H_//二重インクルード防止

#include"main.h"

//弾構造体の定義
struct Tutorial
{
	D3DXVECTOR3 pos;//位置
};

//プロトタイプ宣言
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

#endif // !_TUTORIAL_H_