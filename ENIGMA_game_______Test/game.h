//=========================================================
//
//�Q�[����ʂŎg���ϐ��A�錾�A�\����[game.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _GAME_H_
#define _GAME_H_//��d�C���N���[�h�h�~

#include"main.h"
#include "model.h"
#include "Actionzone.h"

//#define MAX_WORD	(8192)
//#define MAX_WORD3	(512)

//#define MAX_MODEL	(256) //���f���̍ő吔
//#define NUM_MODEL	(26) //���f���̎��
#define MAX_FIELD	(256) //���̍ő吔
#define MAX_WALL	(256) //�ǂ̍ő吔
#define GAME_END_DELAY	(60)//�]�C
#define MODEL_FILE	"data\\Model.bin" //���f���t�@�C��
#define FIELD_FILE	"data\\Field.bin" //���t�@�C��
#define WALL_FILE	"data\\Wall.bin" //�ǃt�@�C��



//=============================================
//���f���ǂݍ��݂̍\�z�̂̒�`
//=============================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	D3DXMATRIX mtxWorld;
	D3DCOLORVALUE Diffuse[MAX_MODEL];
	ModelType nType;
	bool bUse;
	bool bUseGame;
}ModelInfo;

//=============================================
//�Ǔǂݍ��݂̍\�z�̂̒�`
//=============================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nType;
	float fWide;
	float fHeight;
	bool bUse;
	bool bUseGame;
}WallInfo;

//=============================================
//���ǂݍ��݂̍\�z�̂̒�`
//=============================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nType;
	float fWide;
	float fDepth;
	bool bUse;
	bool bUseGame;
}FieldInfo;

//=============================================
//�Q�[���̏��
//=============================================
typedef enum
{
	GAMESTATE_PLAY = 0,
	GAMESTATE_TUTORIAL,
	GAMESTATE_END,
	GANESTATE_MAX
}GAMESTATE;



//�v���g�^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void  GameClear(void);
void ReleasePause(void);
void LoadModel(void);
void LoadField(void);
void LoadWall(void);

//���C�𗘗p�����~�`���m�̓����蔻��
bool CheckCollisionWithRay(D3DXVECTOR3 start, D3DXVECTOR3 direction, D3DXVECTOR3 move, float selfRadius, float targetRadius, D3DXVECTOR3 centerPos);



//���^�����蔻��
void BoxCollisionPlayer(D3DXVECTOR3 PlayerMin, D3DXVECTOR3 PlayerMax, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax,int PlayerIndex);
void BoxCollisionKill(D3DXVECTOR3 PlayerMin, D3DXVECTOR3 PlayerMax, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax, int PlayerIndex);
void BoxCollisionEnemy(D3DXVECTOR3 EnemyMin, D3DXVECTOR3 EnemyMax, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax);

//�v���C���[�ƃJ�����̊Ԃ̏�Q������
void AdjustPlayerPositionToCollision_CAMERA(D3DXVECTOR3 playerPos, int CameraIndex, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax);

//�v���C���[�ƒ����_�̊Ԃ̏�Q������
void AdjustPlayerPositionToCollision_VIEWPOS(D3DXVECTOR3 playerPos, int PlayerIndex, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax);

//�]�ږ哖���蔻��
void BoxCollisionGate(D3DXVECTOR3 PlayerMin, D3DXVECTOR3 PlayerMax, D3DXVECTOR3 GateMin, D3DXVECTOR3 GateMax, int PlayerIndex, int GateIndex, int ParentIndex);

//�s���G���A�����蔻��
void SphereCollisionZone(D3DXVECTOR3 PlayerPos, int PlayerIndex, int ZoneIndex);

//�G�̎��씻��
void SphereEnemyView(D3DXVECTOR3 PlayerPos, int PlayerIndex, int ZoneIndex);

//�v���C���[���^�����蔻��--�A�C�e��
void BoxCollisionItem(D3DXVECTOR3 PlayerMin, D3DXVECTOR3 PlayerMax, D3DXVECTOR3 HitPos, int PlayerIndex, int ItemIndex);


//�A�C�e���p�����蔻��
void BoxCollisionFromItem(D3DXVECTOR3 ItemMin, D3DXVECTOR3 ItemMax, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax, int ItemIndex);



//�]�ڐ�グ
void TRansNumPlayerUP(void);
void TRansNumPlayer2UP(void);

//�]�ڐ扺��
void TRansNumPlayerDOWN(void);
void TRansNumPlayer2DOWN(void);

//�]�ڔԍ��Q��--player1
int GetTRansNumPlayer(void);

//�]�ڔԍ��Q��--player2
int GetTRansNumPlayer2(void);


//�����_���I�o
int RandSelect(int nMax);

//������������
bool LongPress(int nButton, int nTime,int nPlayer);

//�X�V��~
void PlayerUpdateStop(void);
void Player2UpdateStop(void);

#endif 