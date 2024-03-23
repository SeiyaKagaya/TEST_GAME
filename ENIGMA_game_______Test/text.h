//=========================================================
//
//リザルト画面で使う変数、宣言、構造体[text.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _TEXT_H

#define _TEXT_H_//二重インクルード防止

#include"main.h"
#include <d3d9.h>


//フォントの種類
//--------------------フォントのラベル的な
typedef enum
{
	FONT_DOKIDOKI = 0,//どきどきファンタジア
	FONT_AKABARASINDELERA,//赤薔薇シンデレラ
	FONT_KEIFONT,//けいふぉんと
	FONT_SOUKOUMINCHO,//装甲明朝
	FONT_KIRARAJI04,//きらら字04
	FONT_ONRYOU,//怨霊フォント
	FONT_GENSIN,//げんしん
	FONT_MAX,
}FONT;

#define MAXFONT (FONT_MAX)//---フォントの数

//プロトタイプ宣言
void InitText(void);
void UninitText(void);
//テキスト書き出し処理
void DrawTextSet(D3DXVECTOR3 DrawPos, int FontSize, FONT Font, D3DXCOLOR RGBA, const char* Text, ...);


//void DrawWorldText(D3DXVECTOR3 WorldPos, int FontSize, FONT Font, D3DXCOLOR RGBA, const char* Text, ...);


#endif // !_TEXT_H_