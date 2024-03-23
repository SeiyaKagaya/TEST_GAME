//=========================================================
//
//�|�[�Y��ʂŎg���ϐ��A�錾�A�\����[pause.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _PAUSE_H

#define _PAUSE_H_//��d�C���N���[�h�h�~

#include"main.h"

//�|�[�Y���j���[

typedef enum
{
	PAUSE_MENU_CONTINUE = 1,	//�Q�[���ɖ߂�
	PAUSE_MENU_RETRY,			//�Q�[�������Ȃ���
	PAUSE_MENU_QUIT,			//�^�C�g����ʂɖ߂�
	PAUSE_MENU_MAX
}PAUSE_MENU;

typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
}PAUSE;

//�v���g�^�C�v�錾
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

#endif // !_PAUSE_H_