//=========================================================
//
//�`���[�g���A����ʂŎg���ϐ��A�錾�A�\����[tutorial.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _TUTORIAL_H

#define _TUTORIAL_H_//��d�C���N���[�h�h�~

#include"main.h"

//�e�\���̂̒�`
struct Tutorial
{
	D3DXVECTOR3 pos;//�ʒu
};

//�v���g�^�C�v�錾
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

#endif // !_TUTORIAL_H_