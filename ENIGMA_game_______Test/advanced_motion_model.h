//=========================================================
//
// //���x���[�V�������f���֌W�Ŏg���錾�Ȃ�[advanced_motion_model.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _ADVANCEDMODEL_H_//���̃}�N������`����ĂȂ�������

#include "game.h"

//�}�N����`
#define _ADVANCEDMODEL_H_//��d�C���N���[�h�h�~�̃}�N����`

#define BRENDFLAME_AD	(15.0f)//���[�V�����u�����h�̃t���[����

#define MAX_WORD_AD	(1024*3)//�ǂݍ��ޕ����̍ő吔
#define MAX_PARTS_AD	(60)//�ő�PARTS��
#define MAX_WORD2_AD	(3200)//�ő啶����
#define MAX_MOTION_AD	(30)//���[�V�����ő吔
#define MAXKEY_AD	(240)//�ő�L�[��



#define NUM_TEXTURE_AD	(60)


//MODEL�̖��O
typedef enum
{
	MODEL_AD_TYPE_Test1 = 0,//
	MODEL_AD_TYPE_Test2,
	MODEL_AD_TYPE_MAX,
}MODELADTYPE;

//���[�V�������
typedef enum
{
	MOTIONTYPE_AD_STANDBY = 0,
	MOTIONTYPE_AD_MOVE,
	MOTIONTYPE_AD_ATTACK,
	MOTIONTYPE_AD_JUMP,
	MOTIONTYPE_AD_RANDING,
	MOTIONTYPE_AD_BREND,
	MOTIONTYPE_AD_MAX,
}MOTIONTYPE_AD;

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����

	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X

	int PARENT;//�e�q�֌W-�P�͉��ɂ������Ȃ�

//	MOTIONTYPE NowMotionUP;//���݂̃��[�V������ԏ�
	MOTIONTYPE_AD NowMotionDOWN;//���݂̃��[�V������ԉ�

//	MOTIONTYPE OldMotionUP;//�O��̃��[�V������ԏ�
	MOTIONTYPE_AD OldMotionDOWN;//���݂̃��[�V������ԉ�

	bool bUse;

	int NowKeyCntDOWN;//���݂̃L�[�ʒu
	int NowFrameCntDOWN;//���݂̃t���[���̈ʒu

	int NowKeyCntUP;//���݂̃L�[�ʒu
	int NowFrameCntUP;//���݂̃t���[���̈ʒu

	MOTIONTYPE_AD TargetMotion;//�ړI�n�̃��[�V����

	bool MotionLoopStop;//���[�V�����X�g�b�v�������Ă邩�ǂ���
	int JumpFrame;//�W�����v
	bool JumpNow;//�W�����v������

	bool JumpOld;//�W�����v��������

	bool bLandingNow;//���n

	bool MotionBrend;//���[�V�����u�����h���[�h

	int BrendCnt;//�u�����h�J�E���^�[
	MOTIONTYPE_AD EscapeMotion;

}ADMODEL;




//-------------------------------------------------------------------------�������烂�f���p�[�c/���[�V�����n

typedef struct
{
	//�����܂ŁAOFFSET���猩���␳�l
	D3DXVECTOR3 CorrectionPos;	//�ʒu�␳��
	D3DXVECTOR3 CorrectionRot;	//�����␳��
}PARTSDATA_AD;//PARTS���Ƃ̕␳�f�[�^

typedef struct
{
	int nSplitFrame;//�����t���[����


	PARTSDATA_AD PartsData[MAX_PARTS_AD];//���[�V�����̒��ł̃p�[�c�f�[�^����
}KEYDATA_AD;//�L�[�P��-----------Key���ŕϓ�

typedef struct
{
	int Motiontype;//MOTION�̎��//int�^�Ŏd�l
	int nLoop;//���[�v���邩[0:���[�v���Ȃ�1:���[�v����]
	int nNumKey;//���[�V�����̃L�[�̐�

	KEYDATA_AD KeyData[MAXKEY_AD];
}MOTION_AD;//���[�V�����̃f�[�^--���[�V�����̐�����

typedef struct
{
	//���[�V�����̈ʒu�v�Z�ɉ^�p�A�Ō��MODEL��DrawPosS�ɓ����
	D3DXVECTOR3 Pos;	//�ʒu
	D3DXVECTOR3 Rot;	//����
	int INDEX;//�����̔ԍ�
	int PEARENT;		//�����̐e

	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X

	//�͂��߂�T�|�[�Y
	D3DXVECTOR3 StartPos;
	D3DXVECTOR3 StartRot;


	D3DXVECTOR3 CorrectCorrectionPosMove;//���[�V�����ł̈ړ���pos
	D3DXVECTOR3 CorrectCorrectionRotMove;//���[�V�����ł̈ړ���move
	bool calculationExecution;
}MODELPARTS_AD;//���݂̃p�[�c�̃f�[�^

typedef struct
{
	int nMaxMotionCnt;//�ő僂�[�V������

	int nMaxPartsCnt;//�ő�p�[�c��
	int nMaxLoadPartsCnt;//�ǂݍ��ލő�p�[�c��

	MODELPARTS_AD ModelParts[MAX_PARTS_AD];//�^�p���錻�݂�Parts--X
	MOTION_AD Motion[MAX_MOTION_AD];//�ܑヂ�[�V�����Ȃ�

}MODEL_AD;//���f��(�Ƃ�������)

//�v���g�^�C�v�錾
void InitAdvancedModel(void);//�v���C���[�̏���������
void UninitAdvancedModel(void);//�v���C���[�̏I������


void UpdateAdvancedModel(void);//�v���C���[�̍X�V����
void DrawAdvancedModel(void);//�v���C���[�̕`�揈��

ADMODEL* GetAdvancedModel(int Index);

MODEL_AD* GetAdModel(int Index);

LPD3DXMESH* GetMesh_AdvancedModel(int Index);

void ConversionAdvancedModelRot2(int Index, float fRot, int nCnt);//�p�x�C���n

void LoadSet3(int Index);//txt�ɂ��L������OFFSET
void LoadXfire_AdModel(int Index);//OFF�Z�b�g�ł̏�񂩂烂�f���ǂݍ���


void LowerBodyMotion3(int Index);//�����g���[�V����



//�Z�b�g
void SetModel_AD(MODELADTYPE ModelName, D3DXVECTOR3 pos, D3DXVECTOR3 rot);


#endif // !_ADVANCEDMODEL_H_
