//=========================================================
//
//�^�C�g����ʂŎg���ϐ��A�錾�A�\����[title.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _TITLE_H

#define _TITLE_H_//��d�C���N���[�h�h�~

#include"main.h"

//�e�\���̂̒�`
struct Title
{
	D3DXVECTOR3 pos;//�ʒu
};

//�t�F�[�h�̏��
typedef enum
{
	TITLE_BG = 0,//�w�i���
	TITLE_NAME,	//�Q�[���̖��O���
	TITLE_PRESSENTER,	//�{�^�������������
	TITLE_PRESSLOOP,//�{�^���`�J�`�J���[�v
	TITLE_MAX

}TITLESTATE;

//�v���g�^�C�v�錾
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif // !_TITLE_H_