//=========================================================
//
//モデルで使う変数、宣言、構造体[shadow.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SHADOW_H

#define _SHADOW_H_//二重インクルード防止

#define MAX_SHADOW	(1024)

#define SHADOW_SIZE_PLAYER	(25)
#define SHADOW_SIZE_BULLET	(1)


#include"main.h"

typedef enum
{
	SHADOWSIZE_PLAYER=0,
	SHADOWSIZE_ITEM,
	SHADOWSIZE_MAX,
}SHADOWSIZE;

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	SHADOWSIZE ShadowSize;//影サイズ
	bool bUse;
}Shadow;


void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(void);
void SetPositionShadow(int nldShadow, D3DXVECTOR3 pos, SHADOWSIZE ShadowSize);

void EndProcessShadow(int nldShadow);
#endif