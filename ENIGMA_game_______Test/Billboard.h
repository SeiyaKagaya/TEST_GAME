//=========================================================
//
//�e���ˏ����֌W�Ŏg���ϐ��A�錾�A�\����[item.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _BILLBOARD_H_

#define _BILLBOARD_H_//��d�C���N���[�h�h�~

#include"main.h"

#define NUMBILL	(64)//�r���{�[�h�̍ő吔

//�r���{�[�h�̎��
typedef enum
{
	BILLTYPE_DISH = 0,
	BILLTYPE_REMOCON,
	BILLTYPE_VEGETABLE,
	BILLTYPE_SOUP,
	BILLTYPE_MAX
}BillType;

//�r���{�[�h�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXMATRIX mtxWorldBill;//���[���h�}�g���b�N�X
	int nType;
	bool bUse;
}BILL;

void InitBill(void);
void UninitBill(void);
void UpdateBill(void);
void DrawBill(void);

//�ݒ�
void SetBill(D3DXVECTOR3 Pos, int nType);

#endif // _BILLBOARD_H_
