//============================================================================================
//
//ラインを表示する処理の関係[line.h]
// Author seiya kagaya
//
//============================================================================================
#ifndef _LINE_H_
#define _LINE_H_
#include "main.h"

#include "game.h"


#define MAX_LINE	(6000)




//構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 startPos;
	D3DXVECTOR3 endPos;

	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	bool bUse;

	int Life;

}Line;



//プロトタイプ宣言
void InitLine(void);
void UninitLine(void);
void UpdateLine(void);
void DrawLine(void);


void SetLine(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR col);

//void HitLine(int nCntLine, int nDamege);

//Line* GetLine(void);//敵の取得





#endif // !_ENEMY_H_
