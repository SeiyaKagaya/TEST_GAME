//=========================================================
//
//enter��ʂŎg���ϐ��A�錾�A�\����[pressenter.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _PRESSENTER_H

#define _PRESSENTER_H_//��d�C���N���[�h�h�~

#include"main.h"

//�e�\���̂̒�`
struct PressEnter
{
	D3DXVECTOR3 pos;//�ʒu
};

//�v���g�^�C�v�錾
void InitPressEnter(void);
void UninitPressEnter(void);
void UpdatePressEnter(void);
void DrawPressEnter(void);

#endif // !_PRESSENTER_H_