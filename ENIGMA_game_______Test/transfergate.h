//=========================================================
//
//�]�ڃG���A�֌W�Ŏg���錾�Ȃ�[transfergate.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _TRANSFERGATE_H_//���̃}�N������`����ĂȂ�������


//�}�N����`
#define _TRANSFERGATE_H_//��d�C���N���[�h�h�~�̃}�N����`

#include "game.h"


//+++++++++++++++++++++++++++++++++++++++++
//--�T�v--
//+�����蔻��ŁA���̒��ɓ������Ƃ��Ɏw�肳�ꂽ����ɔ��
// +player�ɓ]�ڒ��ォbool�Ŗ��������h���\��
//+++++++++++++++++++++++++++++++++++++++++

#define MAXGATE	(32)//�]�ږ�ő吔

//�]�ڐ�Í�
#define CLEAR_NUM	(MAXGATE - 5)
#define TRANSGATE_NUM	(MAXGATE - 4)
#define CROSSROAD_NUM	(MAXGATE - 3)
#define RONDOMTRANS_NUM	(MAXGATE - 2)
//#define RONDOMTRANS_NUM2	(MAXGATE - 1)

#define MAXROOM	(4)//�����̐�(�M�~�b�N����)


//�]�ڃG���A�T�C�Y(�����蔻��p)
//#define GATEMIN	(D3DXVECTOR3(-170.0f,0.0f,-170.0f))
//#define GATEMAX	(D3DXVECTOR3(170.0f,120.0f,170.0f))



//�]�ڐ�̓]�ڕ���
typedef enum
{
	TRANS_ANGLE_MIN_X = 1,
	TRANS_ANGLE_MAX_X,
	TRANS_ANGLE_MIN_Y,
	TRANS_ANGLE_MAX_Y,
	TRANS_ANGLE_MIN_Z,
	TRANS_ANGLE_MAX_Z,
	TRANS_ANGLE_RANDOM,
	TRANS_ANGLE_CLEAR,
	TRANS_ANGLE_MAX,//--�i�s�����ɓ]��
}TRANSANGLE;






//�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	
	D3DXVECTOR3 GateMin;//�ŏ�
	D3DXVECTOR3 GateMax;//�ő�

	D3DXVECTOR3 SizeMag;//���������{��
	D3DXCOLOR GateColor;//��̐F--�y�A�𓯂��F�ɂ���

	D3DXMATRIX mtxWorld;

	int nGateIndex;//�����̔ԍ�
	int nParentIndex;//�e�̔ԍ�

	TRANSANGLE ParentTransAngle;//�e�̓]�ڕ���

	bool bPossibility;//�]�ډ\���ǂ���--���ȂǁA�܂�������Ȃ�

	bool bCompulsionTrans;//�����]�ڂ��ǂ���


	int nTeleportCnt;//�]�ڃJ�E���g
	bool bActiomTrans;//�s���{�^���œ]��

	bool bUse;
}TRANSFERGATE;


//�v���g�^�C�v�錾
void InitTransferGate(void);//�]�ږ�̏���������
void UninitTransferGate(void);//�]�ږ�̏I������
void UpdateTransferGate(void);//�]�ږ�̍X�V����
void DrawTransferGate(void);//�]�ږ�̕`�揈��

TRANSFERGATE* GetTransferGate(void);

//---------------------���W------------------------�ŏ�--------------------�ő�---------�����̔ԍ�----�]�ڐ�̔ԍ�--�F--�����]�ڂ��ǂ���---------�s���{�^���œ]�ڂ��ǂ���
void SetTransferGate(D3DXVECTOR3 Pos, D3DXVECTOR3 GateMin, D3DXVECTOR3 GateMax, int nGateIndex, int nParentIndex, TRANSANGLE ParentTransAngle,D3DXCOLOR GateColor, bool bCompulsionTrans,bool bActionTrans);

//�]�ڈÓ]
void TeleportIN(int PlayerIndex, int GateIndex);
//�]�ږ��]
void TereportOUT();

#endif // !_TRANSFERGATE_H_
