//==============================
//
// メニューのコルクボード[corkboard.h]
// Author:Kaito Hondo
//
//==============================

#ifndef _CORKBOARD_H_	// このマクロ定義がされてなかったら
#define _CORKBOARD_H_	// ２重インクルード防止のマクロ定義

#include "main.h"

//マクロ定義
#define Corkboard_TEXTURE  "data\\TEXTURE\\Menuframe002.png"


// プロトタイプ宣言
void InitCorkboard(void);
void UninitCorkboard(void);
void UpdateCorkboard(void);
void DrawCorkboard(void);

#endif


