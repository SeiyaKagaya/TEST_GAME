//=========================================================
//
//�|�[�Y��ʂŎg���ϐ��A�錾�A�\����[moneyboxdigit.h]
// Author matsuda towa
//
//=========================================================
#ifndef _MONEYBOXDIGIT_H

#define _MONEYBOXDIGIT_H//��d�C���N���[�h�h�~

#include"main.h"

//=========================================================
//�}�N����`
//=========================================================
#define NUM_DIGIT	(4) //����
#define MAX_NUMBER	(10) //���̍ő�

//=========================================================
//���ɂ̌����Ƃ̍\����
//=========================================================
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	bool WhichPlayer; //�ǂ����̃v���C���[�����삵�Ă��邩 false:1P,true:2P
}MONEYBOXDIGIT;

//=========================================================
//�v���g�^�C�v�錾
//=========================================================
void InitMoneyboxDigit(void);
void UninitMoneyboxDigit(void);
void UpdateMoneyboxDigit(void);
void ControlMoneybox1P(void);
void ControlMoneybox2P(void);
void DrawMoneyboxDigit(void);
void SetMoneyboxDigit(void);
void CorrectMoneyboxDigit(void);
void MistakeMoneyboxDigit(void);
bool GetClearMoneyBox(void);

#endif // !_MONEYBOX_H
