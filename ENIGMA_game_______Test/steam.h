//=============================================
//
//お風呂のギミック[steam.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _STEAM_H_ //定義されてなかったら
#define _STEAM_H_ //２種インクルード防止

#include "main.h"

//=============================================
//マクロ定義
//=============================================
#define STEAM_LIFE		(120)
#define STEAM_WIDE		(20.0f)
#define STEAM_HEIGHT	(20.0f)
#define STEAM_SPEED		(2.0f)
#define MAX_STEAM	(1024)

//=============================================
//お風呂の湯気の構想体の定義
//=============================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	int nLife;
	bool bUse;
}Steam;

//=============================================
//プロトタイプ宣言
//=============================================
void InitSteam(void);
void UninitSteam(void);
void UpdateSteam(void);
void DrawSteam(void);
void SetSteam(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col);
void OffSteam(void);
#endif // _STEAM_H_ //定義されてなかったら