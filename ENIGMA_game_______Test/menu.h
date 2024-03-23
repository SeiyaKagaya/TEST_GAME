//=========================================================
//
//メニュー画面で使う変数、宣言、構造体[menu.h]
// Author kaito hondo
//
//=========================================================
#ifndef _MENU_H

#define _MENU_H_//二重インクルード防止

#include"main.h"

//メニュー

typedef enum
{
	START_MENU_BG = 0,
	START_MENU_GAME,	//ゲームに行く
	START_MENU_TUTORIAL,	//チュートリアルに行く
	START_MENU_TITLE,		//タイトル画面に戻る
	START_MENU_MAX
}START_MENU;

typedef struct
{
	D3DXVECTOR3 pos;						//位置
}MENU;

//フェードの状態
typedef enum
{
	MENU_BG = 0,//背景状態
	MENU_NAME,	//ゲームの名前状態
	MENU_PRESSENTER,	//ボタンおせ文字状態
	MENU_PRESSLOOP,//ボタンチカチカループ
	MENU_MAX
}MENUSTATE;

//プロトタイプ宣言
void InitMenu(void);
void UninitMenu(void);
void UpdateMenu(void);
void DrawMenu(void);
int GetMenu1(void);

#endif // !_PAUSE_H_
