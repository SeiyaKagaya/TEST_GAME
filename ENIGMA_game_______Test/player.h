//=========================================================
//
//�v���C���[�֌W�Ŏg���錾�Ȃ�[player.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _PLAYER_H_//���̃}�N������`����ĂȂ�������

#include "game.h"

//�}�N����`
#define _PLAYER_H_//��d�C���N���[�h�h�~�̃}�N����`

#define BRENDFLAME	(15.0f)//���[�V�����u�����h�̃t���[����


#define VIEWPOS (D3DXVECTOR3 (18.0f,70.0f,0.0f))//�J���������_
#define ITEMDROPPOS (D3DXVECTOR3 (5.0f,70.0f,0.0f))//�A�C�e���X�|�[��
#define SPEECHPOS (D3DXVECTOR3 (35.0f,70.0f,0.0f))//�J���������_



#define NUM_TEXTURE_1P (20)

#define MOVESPEED		(0.7f)//�ړ����x(0.15)


//#define MOVESPEEDMAG	(1.2f)//�󒆈ړ��{��

#define DAMPING_RATIO	(0.20f)//������--�n��
#define DAMPING_RATIO2	(0.05f)//������--��

#define ROT_MOVESPEED		(0.04f)//���񑬓x
#define ROT_DAMPING_RATIO	(0.4f)//���񑬓x�̌�����

#define MAX_WORD	(1024*3)//�ǂݍ��ޕ����̍ő吔
#define MAX_PARTS	(40)//�ő�PARTS��
#define MAX_WORD2	(300)//�ő啶����
#define MAX_MOTION	(12)//���[�V�����ő吔
#define MAXKEY	(60)//�ő�L�[��

//�s���\���a
#define MAXMAREA	(3000.0f)

//�v���C���[���C�t(��)
#define MAXLIFE		(300)

//�v���C���[�T�C�Y(�����蔻��p)
#define PLAYERMIN	(D3DXVECTOR3(-23.0f,0.0f,-23.0f))
#define PLAYERMAX	(D3DXVECTOR3(23.0f,85.0f,23.0f))

#define GRAVITY	(0.9f)//�d��

typedef enum
{
	MOTIONTYPE_1P_STANDBY = 0,
	MOTIONTYPE_1P_MOVE,
	MOTIONTYPE_1P_ATTACK,
	MOTIONTYPE_1P_JUMP,
	MOTIONTYPE_1P_RANDING,
	MOTIONTYPE_1P_BREND,
	MOTIONTYPE_1P_SNEAK,
	MOTIONTYPE_1P_DAMAGE,
	MOTIONTYPE_1P_MAX,
}MOTIONTYPE;

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_1P_NOMAL = 0,
	PLAYERSTATE_1P_DAMEGE,
	PLAYERSTATE_1P_TELEPOR,
	PLAYERSTATE_1P_MAX,
}PLAYERSTATE;


//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 oldPos;//�Â��ʒu

	D3DXVECTOR3 rot;	//����

	D3DXVECTOR3 move;   //�v���C���[�̈ړ�

	PLAYERSTATE PlayerState;//�v���C���[���

	int PlayerStateCnt;

	int nLife;

	float rotmove;//�����ړ�

	float fRotDest;//�ړI�̌���

	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X

	int PARENT;//�e�q�֌W-�P�͉��ɂ������Ȃ�

//	MOTIONTYPE NowMotionUP;//���݂̃��[�V������ԏ�
	MOTIONTYPE NowMotionDOWN;//���݂̃��[�V������ԉ�

//	MOTIONTYPE OldMotionUP;//�O��̃��[�V������ԏ�
	MOTIONTYPE OldMotionDOWN;//���݂̃��[�V������ԉ�

	bool bUse;

	int NowKeyCntDOWN;//���݂̃L�[�ʒu
	int NowFrameCntDOWN;//���݂̃t���[���̈ʒu

	int NowKeyCntUP;//���݂̃L�[�ʒu
	int NowFrameCntUP;//���݂̃t���[���̈ʒu

	MOTIONTYPE TargetMotion;//�ړI�n�̃��[�V����

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
	int nHaveSoup;		//�X�[�v�������Ă��邩

	bool bTransparent;//������
	
	bool bAction;//�s���{�^��������


	bool MotionBrend;//���[�V�����u�����h���[�h
	int BrendCnt;//�u�����h�J�E���^�[
	MOTIONTYPE EscapeMotion;


	bool CrossRoadNow;//�\���H�ɂ��邩

}Player;

///-------------------------------------------------------------------------�ǔ������_
typedef struct
{
	D3DXVECTOR3 ViewPos;//�v���C���[�ǔ��������_
	D3DXVECTOR3 ViewRot;
	D3DXMATRIX ViewPosMtx;//�}�g���b�N�X
}View;
//--------------------------------------------------------------------------




//-------------------------------------------------------------------------�������烂�f���p�[�c/���[�V�����n

typedef struct
{
	//�����܂ŁAOFFSET���猩���␳�l
	D3DXVECTOR3 CorrectionPos;	//�ʒu�␳��
	D3DXVECTOR3 CorrectionRot;	//�����␳��
}PARTSDATA;//PARTS���Ƃ̕␳�f�[�^

typedef struct
{
	int nSplitFrame;//�����t���[����

	PARTSDATA PartsData[MAX_PARTS];//���[�V�����̒��ł̃p�[�c�f�[�^����

}KEYDATA;//�L�[�P��-----------Key���ŕϓ�

typedef struct
{
	int Motiontype;//MOTION�̎��//int�^�Ŏd�l
	int nLoop;//���[�v���邩[0:���[�v���Ȃ�1:���[�v����]
	int nNumKey;//���[�V�����̃L�[�̐�

	KEYDATA KeyData[MAXKEY];
}MOTION;//���[�V�����̃f�[�^--���[�V�����̐�����

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
}MODELPARTS;//���݂̃p�[�c�̃f�[�^

typedef struct
{
	int nMaxMotionCnt;//�ő僂�[�V������

	int nMaxPartsCnt;//�ő�p�[�c��
	int nMaxLoadPartsCnt;//�ǂݍ��ލő�p�[�c��

	MODELPARTS ModelParts[MAX_PARTS];//�^�p���錻�݂�Parts--X
	MOTION Motion[MAX_MOTION];//�ܑヂ�[�V�����Ȃ�

}MODEL;//���f��(�Ƃ�������)

//�v���g�^�C�v�錾
void InitPlayer(void);//�v���C���[�̏���������
void UninitPlayer(void);//�v���C���[�̏I������
void UpdatePlayer(void);//�v���C���[�̍X�V����
void DrawPlayer(int CameraLoopNum);//�v���C���[�̕`�揈��

Player* GetPlayer(void);

MODEL* GetModel(void);//�ꎞ�G

View* GetView(void);//�����_�����

LPD3DXMESH* GetMesh_Player(void);


void InPutKeyboardPlayer(void);//�L�[�{�[�h���͔��f����(�ړ�)
void InPutControllerPlayer(void);//�L�[�{�[�h/�R���g���[���[���͔��f����(�ړ�)
int  CheckInputMove2(void);//�ړ��L�[�̓��͏�Ԃ̗L�����m�F
void InputKeyAttack(void);//�U���L�[�n
void ConversionPlayerRot2(float fRot, int nCnt);//�p�x�C���n

void LoadSet(void);//txt�ɂ��L������OFFSET
void LowerBodyMotion(void);//�����g���[�V����
void UpperBodyMotion(void);//�㔼�g���[�V����


//Xfire��݂���
void LoadXfire_Player(void);//OFF�Z�b�g�ł̏�񂩂烂�f���ǂݍ���

#endif // !_PLAYER_H_
