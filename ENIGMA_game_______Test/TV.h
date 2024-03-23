//=============================================
//
//テレビのギミック[TV.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _TV_H_ //定義されてなかったら
#define _TV_H_ //２種インクルード防止

#include "main.h"
//=============================================
//マクロ定義
//=============================================
#define TVVISION_WIDE	(50.0f)
#define TVVISION_HEIGHT	(33.0f)
#define NUM_CHANNEL	(5)
#define TV_TEX_MOVE	(1.0f/(float)NUM_CHANNEL)

//=============================================
//テレビ画面の構想体の定義
//=============================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nSelectChannel; //選択されてるチャンネル
	int nWhichPlayer; //どっちのプレイヤーが捜査してるか
	float fWide;
	float fHeight;
	float fTexU;
	bool bUse;
	bool bOn; //テレビをつけるかどうか
}TV_VISION;

//=========================================================
//プロトタイプ宣言
//=========================================================
void InitTV(void);
void UninitTV(void);
void UpdateTV(void);
void DrawTV(void);
void TVController(int nWhichPlayer);
void SetTVVision(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWide, float fHeight);
void SelectChannel(int nSelectChannel);
TV_VISION* GetTVPos(void);

#endif // _POLYGON_H_ //定義されてなかったら