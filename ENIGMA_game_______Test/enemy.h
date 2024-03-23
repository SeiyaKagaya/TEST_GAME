//=========================================================
//
// �G�̏���[enemy.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _ENEMY_H_//���̃}�N������`����ĂȂ�������

#include "game.h"

//=============================================
//�}�N����`
//=============================================
#define _ENEMY_H_//��d�C���N���[�h�h�~�̃}�N����`

#define BRENDFLAME_ENEMY	(15.0f)//���[�V�����u�����h�̃t���[����

#define MAX_WORD_ENEMY	(8192)//�ǂݍ��ޕ����̍ő吔
#define MAX_PARTS_ENEMY	(60)//�ő�PARTS��
#define MAX_WORD2_ENEMY	(300)//�ő啶����
#define MAX_MOTION_ENEMY	(30)//���[�V�����ő吔
#define MAXKEY_ENEMY	(240)//�ő�L�[��
//�G�l�~�[�T�C�Y(�����蔻��p)
#define ENEMYMIN	(D3DXVECTOR3(-50.0f,0.0f,-50.0f))
#define ENEMYMAX	(D3DXVECTOR3(50.0f,185.0f,50.0f))
#define MAX_ENEMY_SPEED	(8)
#define ENEMY_FILE_NAME	"data\\motionEnigma.txt" //�G�l�~�[�̃t�@�C���l�[��



#define NUM_TEXTURE_ENEMY	(20)

//�G�̍s���p�^�[��
typedef enum
{
	ACTIONPATTERN_ENEMY_STANDBY = 0,
	ACTIONPATTERN_ENEMY_SPAWN,
	ACTIONPATTERN_ENEMY_WALK,
	ACTIONPATTERN_ENEMY_CHASE,
	ACTIONPATTERN_ENEMY_ATTACK,
	ACTIONPATTERN_ENEMY_MAX,
}ACTIONPATTERN_ENEMY;

//���[�V�������
typedef enum
{
	MOTIONTYPE_ENEMY_STANDBY = 0,
	MOTIONTYPE_ENEMY_MOVE,
	MOTIONTYPE_ENEMY_ATTACK,
	MOTIONTYPE_ENEMY_JUMP,
	MOTIONTYPE_ENEMY_RANDING,
	MOTIONTYPE_ENEMY_BREND,
	MOTIONTYPE_ENEMY_MAX,
}MOTIONTYPE_ENEMY;


//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 oldPos;//�Â��ʒu
	D3DXVECTOR3 MinPos;//�ŏ��ʒu
	D3DXVECTOR3 MaxPos;//�ő�ʒu
	D3DXVECTOR3 rot;	//����
	D3DXVECTOR3 move;   //�G�l�~�[�̈ړ�
	float rotmove;//�����ړ�

	float fRotDest;//�ړI�̌���

	ACTIONPATTERN_ENEMY ActionPattern; //�s���p�^�[��

	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X

	int PARENT;//�e�q�֌W-�P�͉��ɂ������Ȃ�

	int nPlayerIdx; //�Ǐ]����v���C���[

//	MOTIONTYPE NowMotionUP;//���݂̃��[�V������ԏ�
	MOTIONTYPE_ENEMY NowMotionDOWN;//���݂̃��[�V������ԉ�

//	MOTIONTYPE OldMotionUP;//�O��̃��[�V������ԏ�
	MOTIONTYPE_ENEMY OldMotionDOWN;//���݂̃��[�V������ԉ�

	bool bUse;

	int NowKeyCntDOWN;//���݂̃L�[�ʒu
	int NowFrameCntDOWN;//���݂̃t���[���̈ʒu

	int NowKeyCntUP;//���݂̃L�[�ʒu
	int NowFrameCntUP;//���݂̃t���[���̈ʒu

	MOTIONTYPE_ENEMY TargetMotion;//�ړI�n�̃��[�V����

	bool MotionLoopStop;//���[�V�����X�g�b�v�������Ă邩�ǂ���
	int JumpFrame;//�W�����v
	bool JumpNow;//�W�����v������

	bool JumpOld;//�W�����v��������

	bool bLandingNow;//���n

	bool MotionBrend;//���[�V�����u�����h���[�h

	int BrendCnt;//�u�����h�J�E���^�[
	MOTIONTYPE_ENEMY EscapeMotion;

}ENEMYMODEL;




//-------------------------------------------------------------------------�������烂�f���p�[�c/���[�V�����n

typedef struct
{
	//�����܂ŁAOFFSET���猩���␳�l
	D3DXVECTOR3 CorrectionPos;	//�ʒu�␳��
	D3DXVECTOR3 CorrectionRot;	//�����␳��
}PARTSDATA_ENEMY;//PARTS���Ƃ̕␳�f�[�^

typedef struct
{
	int nSplitFrame;//�����t���[����


	PARTSDATA_ENEMY PartsData[MAX_PARTS_ENEMY];//���[�V�����̒��ł̃p�[�c�f�[�^����
}KEYDATA_ENEMY;//�L�[�P��-----------Key���ŕϓ�

typedef struct
{
	int Motiontype;//MOTION�̎��//int�^�Ŏd�l
	int nLoop;//���[�v���邩[0:���[�v���Ȃ�1:���[�v����]
	int nNumKey;//���[�V�����̃L�[�̐�

	KEYDATA_ENEMY KeyData[MAXKEY_ENEMY];
}MOTION_ENEMY;//���[�V�����̃f�[�^--���[�V�����̐�����

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
}MODELPARTS_ENEMY;//���݂̃p�[�c�̃f�[�^

typedef struct
{
	int nMaxMotionCnt;//�ő僂�[�V������

	int nMaxPartsCnt;//�ő�p�[�c��
	int nMaxLoadPartsCnt;//�ǂݍ��ލő�p�[�c��

	MODELPARTS_ENEMY ModelParts[MAX_PARTS_ENEMY];//�^�p���錻�݂�Parts--X
	MOTION_ENEMY Motion[MAX_MOTION_ENEMY];//�ܑヂ�[�V�����Ȃ�

}MODEL_ENEMY;//���f��(�Ƃ�������)

//�v���g�^�C�v�錾
void InitEnemy(void);//�v���C���[�̏���������
void UninitEnemy(void);//�v���C���[�̏I������
void UpdateEnemy(void);//�v���C���[�̍X�V����
void ActionEnemy(ACTIONPATTERN_ENEMY ActionPattern, int PlayerIdx); //�A�N�V�����p�^�[���ɂ���ď����ύX
void DrawEnemy(void);//�v���C���[�̕`�揈��

ENEMYMODEL* GetEnemy(void);

MODEL_ENEMY* GetEnemyModel(void);

LPD3DXMESH* GetMesh_Enemy(void);


//void InPutKeyboardAdvancedModel(void);//�L�[�{�[�h���͔��f����(�ړ�)
//oid InPutControllerAdvancedModel(void);//�L�[�{�[�h/�R���g���[���[���͔��f����(�ړ�)
//int  CheckInputMove2(void);//�ړ��L�[�̓��͏�Ԃ̗L�����m�F
//void InputKeyAttack(void);//�U���L�[�n
void ConversionEnemyRot2(float fRot, int nCnt);//�p�x�C���n

D3DXVECTOR3 ConversionEnemyRot3(D3DXVECTOR3 fRot, int nCnt);

void LoadSetEnemy3(void);//txt�ɂ��L������OFFSET
void LowerBodyEnemy3(void);//�����g���[�V����
//void UpperBodyMotion(void);//�㔼�g���[�V����

//�Z�b�g
void SetModel_Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot);


#endif // !_ADVANCEDMODEL_H_
