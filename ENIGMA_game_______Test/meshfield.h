//=========================================================
//
//地面で使う変数、宣言、構造体[meshfield.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MESHFIELD_H

#define _MESHFIELD_H_//二重インクルード防止

#define DIFF_IN_HEIGHT	(1)

#include"main.h"

void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);


//法線の計算処理
void CalculateNormals(void);

#endif