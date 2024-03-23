//==============================
//
// フィルム動かす[Film.h]
// Author:Kaito Hondo
//
//==============================

#ifndef _FILM_H_	// このマクロ定義がされてなかったら
#define _FILM_H_	// ２重インクルード防止のマクロ定義

#include "main.h"

//マクロ定義
//#define FILM_TEXTURE  "data\\TEXTURE\\Film000.png"
//#define FILM_TEXTURE2 "data\\TEXTURE\\Film001.png"
//#define FILM_TEXTURE3 "data\\TEXTURE\\Film002.png"
#define FILM_TEXTURE4 "data\\TEXTURE\\Film0.png"
#define NUM_FILMTEXTURE	(1)	// 背景の数
#define NUM_FILM	(32)	// フィルムの最大数 

//パーツ構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	float texX;
	bool bUse;
}FILM;

// プロトタイプ宣言
void InitFILM(void);
void UninitFILM(void);
void UpdateFILM(void);
void DrawFILM(void);
void SetFILM(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float texX);

#endif

