//==============================
//
// メニュー[MenuFrame.h]
// Author:Kaito Hondo
//
//==============================

#ifndef _MENUFRAME_H_	// このマクロ定義がされてなかったら
#define _MENUFRAME_H_	// ２重インクルード防止のマクロ定義

#include "main.h"

//マクロ定義
#define MenuFrame_TEXTURE  "data\\TEXTURE\\Menuframe000.png"


// プロトタイプ宣言
void InitMenuFrame(void);
void UninitMenuFrame(void);
void UpdateMenuFrame(void);
void DrawMenuFrame(void);

#endif

