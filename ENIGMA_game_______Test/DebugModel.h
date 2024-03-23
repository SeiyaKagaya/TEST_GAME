//=========================================================
//
//DEBUG���f���֌W�Ŏg���錾�Ȃ�[DebugModel.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _DEBUGMODEL_H_//���̃}�N������`����ĂȂ�������



//�}�N����`
#define _DEBUGMODEL_H_//��d�C���N���[�h�h�~�̃}�N����`

#include "game.h"
//+++++++++++++++++++++++++++++++++++++++++
//--�T�v--
//+�����蔻��ŁA���̒��ɓ������Ƃ��Ɏw�肳�ꂽ����ɔ��
// +player�ɓ]�ڒ��ォbool�Ŗ��������h���\��
//+++++++++++++++++++++++++++++++++++++++++

#define MAXDEBUGMODEL	(30)//�A�N�V�����G���A�ő吔


//�]�ڃG���A�T�C�Y(�����蔻��p)
//#define GZONEMIN	(D3DXVECTOR3(-170.0f,0.0f,-170.0f))
//#define GZONEMAX	(D3DXVECTOR3(170.0f,120.0f,170.0f))



////�]�ڐ�̓]�ڕ���
//typedef enum
//{
//	ACTION_TYPE_A = 0,
//	ACTION_TYPE_MAX,//--�i�s�����ɓ]��
//}ACTIONTYPE;
//




//�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu

	D3DXVECTOR3 ZoneMin;//�ŏ�
	D3DXVECTOR3 ZoneMax;//�ő�

	float Radius;//���a


	D3DXVECTOR3 SizeMag;//���������{��
	D3DXCOLOR ZoneColor;//��̐F--�y�A�𓯂��F�ɂ���

	D3DXCOLOR EscapeZoneColor;//��̐F--�y�A�𓯂��F�ɂ���-���p


	D3DXMATRIX mtxWorld;

	int nZoneIndex;//�����̔ԍ�
//	int nParentIndex;//�e�̔ԍ�

//	ACTIONTYPE ActionType;//����^�C�v

//	bool bPossibility;//����\���ǂ���--���ȂǁA�܂�������Ȃ�
	bool bUse;
}DEBUGMODEL;


//�v���g�^�C�v�錾
void InitDebugModel(void);//�A�N�V�����G���A�̏���������
void UninitDebugModel(void);//�A�N�V�����G���A�̏I������
void UpdateDebugModel(void);//�A�N�V�����G���A�̍X�V����
void DrawDebugModel(void);//�A�N�V�����G���A�̕`�揈��

//DEBUGMODEL* GetDebugModel(void);

//���`
//-----------------------------�������W-----------���a------------�F--Beacon���ǂ���
void SetDebugModelSphere(float Radius,D3DXCOLOR ZoneColor,bool Beacon);
//�l�p
//-----------------------------�������W-----------�ŏ��ő�------------�F
//void SetDebugModelBOX(D3DXVECTOR3 Min, D3DXVECTOR3 Max, D3DXCOLOR ZoneColor);


//�ݒu�p�R�����g
void DrawDebugDelComment(void);

//��胂�f�����폜���鏈��
void DeleteCoveredModel(void);


#endif // !_DEBUGMODEL_H_
