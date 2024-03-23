//=========================================================
//
//ポーズ画面で使う変数、宣言、構造体[pause.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _PAUSE_H

#define _PAUSE_H_//二重インクルード防止

#include"main.h"

//ポーズメニュー

typedef enum
{
	PAUSE_MENU_CONTINUE = 1,	//ゲームに戻る
	PAUSE_MENU_RETRY,			//ゲームをやりなおす
	PAUSE_MENU_QUIT,			//タイトル画面に戻る
	PAUSE_MENU_MAX
}PAUSE_MENU;

typedef struct
{
	D3DXVECTOR3 pos;						//位置
}PAUSE;

//プロトタイプ宣言
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

#endif // !_PAUSE_H_