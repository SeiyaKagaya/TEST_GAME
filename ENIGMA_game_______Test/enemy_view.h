//=========================================================
//
//�G�̎���[enemy_view.h]
// Author Matsuda Towa
//
//=========================================================
#ifndef _ENEMYVIEW_H_//���̃}�N������`����ĂȂ�������

//�}�N����`
#define _ENEMYVIEWE_H_//��d�C���N���[�h�h�~�̃}�N����`

#include "game.h"

//+++++++++++++++++++++++++++++++++++++++++
//--�T�v--
//+player�����̒��ɓ�������ǂ�������
// 
//+++++++++++++++++++++++++++++++++++++++++

#define MAX_ENEMYVIEW	(300)//�G�̎���ő吔


//�]�ڃG���A�T�C�Y(�����蔻��p)
//#define GZONEMIN	(D3DXVECTOR3(-170.0f,0.0f,-170.0f))
//#define GZONEMAX	(D3DXVECTOR3(170.0f,120.0f,170.0f))

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

	bool bFollowEnemy; //�G�l�~�[�ɂ��Ă����ǂ���
	bool bDrawOk;
	bool bUse;
}ENEMYVIEW;


//�v���g�^�C�v�錾
void InitEnemy_View(void);//�G�̎���̏���������
void UninitEnemy_View(void);//�G�̎���̏I������
void UpdateEnemy_View(void);//�G�̎���̍X�V����
void DrawEnemy_View(void);//�G�̎���̕`�揈��

ENEMYVIEW* GetEnemy_View(void);

//-----------------------------�������W-----------���a---------�G�l�~�[�ɂ��Ă����ǂ���-------�F
void SetEnemy_View(D3DXVECTOR3 Pos, float Radius,bool bFollowEnemy, D3DXCOLOR ZoneColor);


#endif // !_EnemyView_H_
