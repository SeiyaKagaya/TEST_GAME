//=========================================================
//
//�v���C���[�֌W�Ŏg���錾�Ȃ�[player2.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _PLAYER2_H_//���̃}�N������`����ĂȂ�������

#include "game.h"

//�}�N����`
#define _PLAYER2_H_//��d�C���N���[�h�h�~�̃}�N����`

#define BRENDFLAME2	(15.0f)//���[�V�����u�����h�̃t���[����

#define NUM_TEXTURE_2P (20)


#define VIEWPOS2 (D3DXVECTOR3 (18.0f,70.0f,0.0f))
#define ITEMDROPPOS2 (D3DXVECTOR3 (5.0f,70.0f,0.0f))//�A�C�e���h���b�v�����_
#define SPEECHPOS2 (D3DXVECTOR3 (35.0f,70.0f,0.0f))//�J���������_



#define MOVESPEED_2P		(0.7f)//�ړ����x(0.15)
//#define MOVESPEED_2MAG	(1.2f)//�󒆈ړ��{��

#define DAMPING_RATIO_2P	(0.20f)//������--�n��
#define DAMPING_RATIO2_2P	(0.05f)//������--��

#define ROT_MOVESPEED_2P		(0.04f)//���񑬓x
#define ROT_DAMPING_RATIO_2P	(0.4f)//���񑬓x�̌�����

#define MAX_WORD_2P	(1024*3)//�ǂݍ��ޕ����̍ő吔
#define MAX_PARTS_2P	(40)//�ő�PARTS��
#define MAX_WORD2_2P	(200)//�ő啶����
#define MAX_MOTION_2P	(20)//���[�V�����ő吔
#define MAXKEY_2P	(60)//�ő�L�[��

//�s���\���a
#define MAXMAREA_2P	(3000.0f)

//�v���C���[���C�t(��)
#define MAXLIFE_2P		(300)

//�v���C���[�T�C�Y(�����蔻��p)
#define PLAYERMIN_2P	(D3DXVECTOR3(-23.0f,0.0f,-23.0f))
#define PLAYERMAX_2P	(D3DXVECTOR3(23.0f,85.0f,23.0f))

#define GRAVITY_2P	(0.9f)//�d��

typedef enum
{
	MOTIONTYPE_2P_STANDBY = 0,
	MOTIONTYPE_2P_MOVE,
	MOTIONTYPE_2P_ATTACK,
	MOTIONTYPE_2P_JUMP,
	MOTIONTYPE_2P_RANDING,
	MOTIONTYPE_2P_BREND,
	MOTIONTYPE_2P_SNEAK,
	MOTIONTYPE_2P_DAMAGE,
	MOTIONTYPE_2P_MAX,
}MOTIONTYPE_2P;

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_2P_NOMAL = 0,
	PLAYERSTATE_2P_DAMEGE,
	PLAYERSTATE_2P_TELEPOR,
	PLAYERSTATE_2P_MAX,
}PLAYERSTATE_2P;


//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 oldPos;//�Â��ʒu

	D3DXVECTOR3 rot;	//����

	D3DXVECTOR3 move;   //�v���C���[�̈ړ�

	PLAYERSTATE_2P PlayerState;//�v���C���[���

	int PlayerStateCnt;

	int nLife;

	float rotmove;//�����ړ�

	float fRotDest;//�ړI�̌���

	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X

	int PARENT;//�e�q�֌W-�P�͉��ɂ������Ȃ�

	MOTIONTYPE_2P NowMotionUP;//���݂̃��[�V������ԏ�
	MOTIONTYPE_2P NowMotionDOWN;//���݂̃��[�V������ԉ�

	MOTIONTYPE_2P OldMotionUP;//�O��̃��[�V������ԏ�
	MOTIONTYPE_2P OldMotionDOWN;//���݂̃��[�V������ԉ�

	bool bUse;

	int NowKeyCntDOWN;//���݂̃L�[�ʒu
	int NowFrameCntDOWN;//���݂̃t���[���̈ʒu

	int NowKeyCntUP;//���݂̃L�[�ʒu
	int NowFrameCntUP;//���݂̃t���[���̈ʒu

	MOTIONTYPE_2P TargetMotion;//�ړI�n�̃��[�V����

	bool MotionLoopStop;//���[�V�����X�g�b�v�������Ă邩�ǂ���
	int JumpFrame;//�W�����v
	bool JumpNow;//�W�����v������

	bool JumpOld;//�W�����v��������

	int nldShadow;//�e�ԍ�

	bool bLandingNow;//���n
	bool bMoneyBoxGimmick; //���ɂ̃M�~�b�N�����Ă邩
	bool bTvGimmick; //�e���r�𑀍삵�Ă邩�ǂ���
	int nHaveRemocon; //�����R���������Ă��邩
	int nHaveDish; //�M�������Ă��邩
	int nHaveVegetable; //��؂������Ă��邩
	int nHaveSoup;	//�X�[�v�������Ă��邩

	bool bAction;//�s���{�^��

	bool bTransparent;//������


	bool MotionBrend;//���[�V�����u�����h���[�h
	int BrendCnt;//�u�����h�J�E���^�[
	MOTIONTYPE_2P EscapeMotion;

	bool CrossRoadNow;//�\���H�ɂ��邩
}Player_2P;



///-------------------------------------------------------------------------�ǔ������_
typedef struct
{
	D3DXVECTOR3 ViewPos;//�v���C���[�ǔ��������_
	D3DXVECTOR3 ViewRot;
	D3DXMATRIX ViewPosMtx;//�}�g���b�N�X
}View2;


//-------------------------------------------------------------------------�������烂�f���p�[�c/���[�V�����n

typedef struct
{
	//�����܂ŁAOFFSET���猩���␳�l
	D3DXVECTOR3 CorrectionPos;	//�ʒu�␳��
	D3DXVECTOR3 CorrectionRot;	//�����␳��
}PARTSDATA_2P;//PARTS���Ƃ̕␳�f�[�^

typedef struct
{
	int nSplitFrame;//�����t���[����

	PARTSDATA_2P PartsData[MAX_PARTS_2P];//���[�V�����̒��ł̃p�[�c�f�[�^����

}KEYDATA_2P;//�L�[�P��-----------Key���ŕϓ�

typedef struct
{
	int Motiontype;//MOTION�̎��//int�^�Ŏd�l
	int nLoop;//���[�v���邩[0:���[�v���Ȃ�1:���[�v����]
	int nNumKey;//���[�V�����̃L�[�̐�

	KEYDATA_2P KeyData[MAXKEY_2P];
}MOTION_2P;//���[�V�����̃f�[�^--���[�V�����̐�����

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
}MODELPARTS_2P;//���݂̃p�[�c�̃f�[�^

typedef struct
{
	int nMaxMotionCnt;//�ő僂�[�V������

	int nMaxPartsCnt;//�ő�p�[�c��
	int nMaxLoadPartsCnt;//�ǂݍ��ލő�p�[�c��

	MODELPARTS_2P ModelParts[MAX_PARTS_2P];//�^�p���錻�݂�Parts--X
	MOTION_2P Motion[MAX_MOTION_2P];//�ܑヂ�[�V�����Ȃ�

}MODEL_2P;//���f��(�Ƃ�������)

//�v���g�^�C�v�錾
void InitPlayer_2P(void);//�v���C���[�̏���������
void UninitPlayer_2P(void);//�v���C���[�̏I������
void UpdatePlayer_2P(void);//�v���C���[�̍X�V����
void DrawPlayer_2P(int CameraLoopNum);//�v���C���[�̕`�揈��

Player_2P* GetPlayer_2P(void);

MODEL_2P* GetModel_2P(void);//�ꎞ�G

View2* GetView_2P(void);//�����_�����


LPD3DXMESH* GetMesh_Player_2P(void);


void InPutKeyboardPlayer_2P(void);//�L�[�{�[�h���͔��f����(�ړ�)
void InPutControllerPlayer_2P(void);//�L�[�{�[�h/�R���g���[���[���͔��f����(�ړ�)
int  CheckInputMove2_2P(void);//�ړ��L�[�̓��͏�Ԃ̗L�����m�F
void InputKeyAttack_2P(void);//�U���L�[�n
void ConversionPlayerRot2_2P(float fRot, int nCnt);//�p�x�C���n

void LoadSet_2P(void);//txt�ɂ��L������OFFSET
void LowerBodyMotion_2P(void);//�����g���[�V����
void UpperBodyMotion_2P(void);//�㔼�g���[�V����

//Xfire��݂���
void LoadXfire_Player2(void);//OFF�Z�b�g�ł̏�񂩂烂�f���ǂݍ���


#endif // !_PLAYER2_H_
