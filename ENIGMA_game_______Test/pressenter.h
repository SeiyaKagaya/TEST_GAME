//=========================================================
//
//enter画面で使う変数、宣言、構造体[pressenter.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _PRESSENTER_H

#define _PRESSENTER_H_//二重インクルード防止

#include"main.h"

//弾構造体の定義
struct PressEnter
{
	D3DXVECTOR3 pos;//位置
};

//プロトタイプ宣言
void InitPressEnter(void);
void UninitPressEnter(void);
void UpdatePressEnter(void);
void DrawPressEnter(void);

#endif // !_PRESSENTER_H_