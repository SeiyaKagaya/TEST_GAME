//=========================================================
//
//タイトル画面で使う変数、宣言、構造体[title.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _TITLE_H

#define _TITLE_H_//二重インクルード防止

#include"main.h"

//弾構造体の定義
struct Title
{
	D3DXVECTOR3 pos;//位置
};

//フェードの状態
typedef enum
{
	TITLE_BG = 0,//背景状態
	TITLE_NAME,	//ゲームの名前状態
	TITLE_PRESSENTER,	//ボタンおせ文字状態
	TITLE_PRESSLOOP,//ボタンチカチカループ
	TITLE_MAX

}TITLESTATE;

//プロトタイプ宣言
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif // !_TITLE_H_