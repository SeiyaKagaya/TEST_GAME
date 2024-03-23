//============================================================================================
//
//フェードに関する宣言や構造体[fade.h]
// Author seiya kagaya
//
//============================================================================================
#ifndef _GAMEFADE_H_

#define _GAMEFADE_H_

#include "main.h"


#define MAXGAMEFADE	(2)

//フェードの状態
typedef enum
{
	GAMEFADE_NONE = 0,//何もしていない状態
	GAMEFADE_IN,	//フェードイン状態
	GAMEFADE_OUT,	//フェードアウト状態
	GAMEFADE_MAX

}GAMEFADE;

//プロトタイプ宣言
void InitGameFade(void);
void UninitGameFade(void);
void UpdateGameFade(void);
void DrawGameFade(void);

void SetGameFade(int PlayerNum,D3DXVECTOR3 ESCAPEMOVE,D3DXVECTOR3 EscapeRot,D3DXVECTOR3 EscapeRot_Player, bool GameClear,bool CrossRoadTrans);

GAMEFADE GetGameFade(void);

#endif