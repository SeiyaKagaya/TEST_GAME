//=========================================================
//
//メニュー画面で使う変数、宣言、構造体[menu.h]
// Author kaito hondo
//
//=========================================================
#ifndef _ICON_H

#define _ICON_H_//二重インクルード防止

#include"main.h"

//メニュー

typedef enum
{
	START_ICON_GAME = 0,	//ゲームに行く
	START_ICON_TUTORIAL,	//チュートリアルに行く
	START_ICON_TITLE,		//タイトル画面に戻る
	START_ICON_MAX
}START_ICON;

typedef struct
{
	D3DXVECTOR3 pos;						//位置
	float texX;
	bool bUse;
}ICON;

//フェードの状態
typedef enum
{
	ICON_BG = 0,//背景状態
	ICON_NAME,	//ゲームの名前状態
	ICON_PRESSENTER,	//ボタンおせ文字状態
	ICON_PRESSLOOP,//ボタンチカチカループ
	ICON_MAX
}ICONSTATE;

//プロトタイプ宣言
void InitIcon(void);
void UninitIcon(void);
void UpdateIcon(void);
void DrawIcon(void);
int GetIcon(void);

#endif // !_PAUSE_H_
