=========================================================
//
//�e���ˏ����֌W�Ŏg���ϐ��A�錾�A�\����[bullet.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _BULLET_H_

#define _BULLET_H_//��d�C���N���[�h�h�~

#include"main.h"

#include "enemy.h"
#include "game.h"

#define NUMBULLET	(1048)//�e�̐�
#define TEXNUM	(4)//�e�N�X�`���̐�

#define BULLETSPEED	 (8)//���̑��x

#define BULLETSIZE	(4)

#define BULLETMOVESPEED_LOCK	(45.0f)
#define BULLETMOVESPEED	(4.0f)

#define BULLETDAMAGE	(15)


//�v���C���[�T�C�Y
#define BULLETMIN	(D3DXVECTOR3(-3.0f,-3.0f,-3.0f))
#define BULLETMAX	(D3DXVECTOR3(3.0f,3.0f,3.0f))


//�ǂ̌����Ă�����\����
typedef enum
{
	BULLETTYPE_Player = 0,
	BULLETTYPE_Enemy,
	BULLETTYPE_MAX,
}BULLETTYPE;


//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 oldPos;

	//D3DXVECTOR3 rot;	//����
	D3DXMATRIX mtxWorldBullet;//���[���h�}�g���b�N�X
	D3DXVECTOR3 move;		//�ړ�
	BULLETTYPE BulletType;//�ǂ̌���

	int nLife;//���C�t

	int nShadowNum;//�e�ԍ�

	EXISTENCETYPE ExstenceType;

	bool bUse;
}BULLET;




void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

BULLET* GetBullet(void);

void HitBullet_Enemy(int EnemyIndex);////�G��e����--�ʏ�e
void HitBullet_tPlayer(void);////���@��e����--�ʏ�e





//�ǂ̐ݒ�
void SetBullet(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, int Width, int height, BULLETTYPE testType);


// �\�������_���v�Z����֐�
D3DXVECTOR3 PredictIntersection(BULLET bullet, Enemy enemy);


#endif // _BULLET_H_
