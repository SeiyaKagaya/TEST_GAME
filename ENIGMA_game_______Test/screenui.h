//=========================================================
//
//スクリーンUIで使う変数、宣言、構造体[screenui.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SCREENUI_H

#define _SCREENUI_H_//二重インクルード防止

#include"main.h"
#define MAX_UI	(12)

#define NUM_UI	(3)//UI画面の表示数

#define WATCHSIZE	(20.0f)
#define CROSSSIZE	(25.0f)
#define STARTSIZE	(17.0f)//使うかも...

//フェードの状態
typedef enum
{
	SCREENUI_CROSS_0 = 0,//十字キー
	SCREENUI_CROSS_1,//十字キー
	SCREENUI_WATCH,//時計
	SCREENUI_START,//スタート
	SCREENUI_MAX

}SCREENUISTATE;



//構造体の定義
struct ScreenState
{
	bool TV_bUse;
	bool MoneyBox_bUse;
};


//構造体の定義
struct ScreenUI
{
	SCREENUISTATE type;
	bool bUse;
	D3DXVECTOR3 pos;//位置
};





//プロトタイプ宣言
void InitScreenUI(void);
void UninitScreenUI(void);
void UpdateScreenUI(void);
void DrawScreenUI(void);


//スクリーンUIの設定処理
void SetScreenUI(D3DXVECTOR3 pos, SCREENUISTATE UItype);

ScreenState* GetScreenState(void);

#endif // !_SCREENUI_H_