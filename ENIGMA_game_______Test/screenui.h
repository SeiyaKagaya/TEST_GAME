//=========================================================
//
//�X�N���[��UI�Ŏg���ϐ��A�錾�A�\����[screenui.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SCREENUI_H

#define _SCREENUI_H_//��d�C���N���[�h�h�~

#include"main.h"
#define MAX_UI	(12)

#define NUM_UI	(3)//UI��ʂ̕\����

#define WATCHSIZE	(20.0f)
#define CROSSSIZE	(25.0f)
#define STARTSIZE	(17.0f)//�g������...

//�t�F�[�h�̏��
typedef enum
{
	SCREENUI_CROSS_0 = 0,//�\���L�[
	SCREENUI_CROSS_1,//�\���L�[
	SCREENUI_WATCH,//���v
	SCREENUI_START,//�X�^�[�g
	SCREENUI_MAX

}SCREENUISTATE;



//�\���̂̒�`
struct ScreenState
{
	bool TV_bUse;
	bool MoneyBox_bUse;
};


//�\���̂̒�`
struct ScreenUI
{
	SCREENUISTATE type;
	bool bUse;
	D3DXVECTOR3 pos;//�ʒu
};





//�v���g�^�C�v�錾
void InitScreenUI(void);
void UninitScreenUI(void);
void UpdateScreenUI(void);
void DrawScreenUI(void);


//�X�N���[��UI�̐ݒ菈��
void SetScreenUI(D3DXVECTOR3 pos, SCREENUISTATE UItype);

ScreenState* GetScreenState(void);

#endif // !_SCREENUI_H_