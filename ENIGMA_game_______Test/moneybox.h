//=========================================================
//
//�|�[�Y��ʂŎg���ϐ��A�錾�A�\����[moneybox.h]
// Author matsuda towa
//
//=========================================================
#ifndef _MONEYBOX_H

#define _MONEYBOX_H//��d�C���N���[�h�h�~

#include"main.h"

//=========================================================
//�}�N����`
//=========================================================
#define NUM_DIGIT	(4) //����
#define MAX_NUMBER	(10) //���̍ő�

//=========================================================
//���ɂ̍\����
//=========================================================
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	int nSelectDigit;						//�I�����Ă錅
	bool WhichPlayer; //�ǂ����̃v���C���[�����삵�Ă��邩 false:1P,true:2P
}MONEYBOX;

//=========================================================
//�v���g�^�C�v�錾
//=========================================================
void InitMoneybox(void);
void UninitMoneybox(void);
void UpdateMoneybox(void);
void DrawMoneybox(void);
void SetMonetbox(bool MoneyboxPlayer);
MONEYBOX* GetMoneybox(void);

#endif // !_MONEYBOX_H
