//=========================================================
//
//���j���[��ʂŎg���ϐ��A�錾�A�\����[menu.h]
// Author kaito hondo
//
//=========================================================
#ifndef _ICON_H

#define _ICON_H_//��d�C���N���[�h�h�~

#include"main.h"

//���j���[

typedef enum
{
	START_ICON_GAME = 0,	//�Q�[���ɍs��
	START_ICON_TUTORIAL,	//�`���[�g���A���ɍs��
	START_ICON_TITLE,		//�^�C�g����ʂɖ߂�
	START_ICON_MAX
}START_ICON;

typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	float texX;
	bool bUse;
}ICON;

//�t�F�[�h�̏��
typedef enum
{
	ICON_BG = 0,//�w�i���
	ICON_NAME,	//�Q�[���̖��O���
	ICON_PRESSENTER,	//�{�^�������������
	ICON_PRESSLOOP,//�{�^���`�J�`�J���[�v
	ICON_MAX
}ICONSTATE;

//�v���g�^�C�v�錾
void InitIcon(void);
void UninitIcon(void);
void UpdateIcon(void);
void DrawIcon(void);
int GetIcon(void);

#endif // !_PAUSE_H_
