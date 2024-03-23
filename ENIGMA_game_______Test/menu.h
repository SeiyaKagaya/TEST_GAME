//=========================================================
//
//���j���[��ʂŎg���ϐ��A�錾�A�\����[menu.h]
// Author kaito hondo
//
//=========================================================
#ifndef _MENU_H

#define _MENU_H_//��d�C���N���[�h�h�~

#include"main.h"

//���j���[

typedef enum
{
	START_MENU_BG = 0,
	START_MENU_GAME,	//�Q�[���ɍs��
	START_MENU_TUTORIAL,	//�`���[�g���A���ɍs��
	START_MENU_TITLE,		//�^�C�g����ʂɖ߂�
	START_MENU_MAX
}START_MENU;

typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
}MENU;

//�t�F�[�h�̏��
typedef enum
{
	MENU_BG = 0,//�w�i���
	MENU_NAME,	//�Q�[���̖��O���
	MENU_PRESSENTER,	//�{�^�������������
	MENU_PRESSLOOP,//�{�^���`�J�`�J���[�v
	MENU_MAX
}MENUSTATE;

//�v���g�^�C�v�錾
void InitMenu(void);
void UninitMenu(void);
void UpdateMenu(void);
void DrawMenu(void);
int GetMenu1(void);

#endif // !_PAUSE_H_
