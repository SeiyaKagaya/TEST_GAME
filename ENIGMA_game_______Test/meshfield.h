//=========================================================
//
//�n�ʂŎg���ϐ��A�錾�A�\����[meshfield.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MESHFIELD_H

#define _MESHFIELD_H_//��d�C���N���[�h�h�~

#define DIFF_IN_HEIGHT	(1)

#include"main.h"

void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);


//�@���̌v�Z����
void CalculateNormals(void);

#endif