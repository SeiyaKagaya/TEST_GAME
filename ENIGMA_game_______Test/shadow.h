//=========================================================
//
//���f���Ŏg���ϐ��A�錾�A�\����[shadow.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SHADOW_H

#define _SHADOW_H_//��d�C���N���[�h�h�~

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
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	SHADOWSIZE ShadowSize;//�e�T�C�Y
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