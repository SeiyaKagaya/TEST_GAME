//=========================================================
//
//�s���G���A�֌W�Ŏg���錾�Ȃ�[Actionzone.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _ACTIONZONE_H_//���̃}�N������`����ĂȂ�������



//�}�N����`
#define _ACTIONZONE_H_//��d�C���N���[�h�h�~�̃}�N����`

#include "game.h"
//+++++++++++++++++++++++++++++++++++++++++
//--�T�v--
//+�����蔻��ŁA���̒��ɓ������Ƃ��Ɏw�肳�ꂽ����ɔ��
// +player�ɓ]�ڒ��ォbool�Ŗ��������h���\��
//+++++++++++++++++++++++++++++++++++++++++

#define MAXZONE	(264)//�A�N�V�����G���A�ő吔


//�]�ڃG���A�T�C�Y(�����蔻��p)
//#define GZONEMIN	(D3DXVECTOR3(-170.0f,0.0f,-170.0f))
//#define GZONEMAX	(D3DXVECTOR3(170.0f,120.0f,170.0f))



//�]�ڐ�̓]�ڕ���
typedef enum
{
	ACTION_TYPE_A = 0,
	ACTION_TYPE_MONEYBOX,	//���ɃM�~�b�N
	ACTION_TYPE_BATH,		//�����C�M�~�b�N
	ACTION_TYPE_LEVER_1,	//���o�[�M�~�b�N
	ACTION_TYPE_LEVER_2,	//���o�[�M�~�b�N
	ACTION_TYPE_KEY_1,		//���M�~�b�N
	ACTION_TYPE_KEY_2,		//���M�~�b�N
	ACTION_TYPE_KEY_3,		//���M�~�b�N
	ACTION_TYPE_EYETRAP,	//���E�g���b�v
	ACTION_TYPE_ESCAPE,		//�ړ�
	ACTION_TYPE_TV,			//TV�M�~�b�N
	ACTION_TYPE_GAMECLEAR,	//�N���A
	ACTION_TYPE_CUPBOARD,	//�H��I
	ACTION_TYPE_KITCHEN,	//�L�b�`��
	ACTION_TYPE_DESK,		//�H��
	ACTION_TYPE_PURIFICATION,//�򉻑��u
	ACTION_TYPE_LEVER_TUTORIAL1,//�`���[�g���A�����o�[
	ACTION_TYPE_LEVER_TUTORIAL2,//�`���[�g���A�����o�[
	ACTION_TYPE_MAX,		//--�i�s�����ɓ]��
}ACTIONTYPE;





//�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu

	D3DXVECTOR3 ZoneMin;//�ŏ�
	D3DXVECTOR3 ZoneMax;//�ő�

	int Radius;//���a


	D3DXVECTOR3 SizeMag;//���������{��
	D3DXCOLOR ZoneColor;//��̐F--�y�A�𓯂��F�ɂ���

	D3DXCOLOR EscapeZoneColor;//��̐F--�y�A�𓯂��F�ɂ���-���p


	D3DXMATRIX mtxWorld;

	int nZoneIndex;//�����̔ԍ�
//	int nParentIndex;//�e�̔ԍ�

	ACTIONTYPE ActionType;//����^�C�v

	bool bPossibility;//����\���ǂ���--���ȂǁA�܂�������Ȃ�
	bool bDrawOk;
	bool bUse;
}ACTIONZONE;


//�v���g�^�C�v�錾
void InitActionZone(void);//�A�N�V�����G���A�̏���������
void UninitActionZone(void);//�A�N�V�����G���A�̏I������
void UpdateActionZone(void);//�A�N�V�����G���A�̍X�V����
void DrawActionZone(void);//�A�N�V�����G���A�̕`�揈��

ACTIONZONE* GetActionZone(void);

//-----------------------------�������W-----------���a---------�s���^�C�v-------�F
void SetActionZone(D3DXVECTOR3 Pos, float Radius, ACTIONTYPE ActionType, D3DXCOLOR ZoneColor);


#endif // !_ACTIONZONE_H_
