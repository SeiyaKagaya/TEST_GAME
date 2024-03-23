//=============================================
//
//�}�b�v�G�f�B�^�[[hitcollision_mistake_prevention.h]
//Auther seiya.kagaya
//
//=============================================
#ifndef _COLLISION_PRE_H_//���̃}�N������`����ĂȂ�������


//�}�N����`
#define _COLLISION_PRE_H_//��d�C���N���[�h�h�~�̃}�N����`

#include "game.h"


#define MAXCOLLISION_PRE	(30)//�]�ږ�ő吔



//�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu

	D3DXVECTOR3 Min;//�ŏ�
	D3DXVECTOR3 Max;//�ő�

	D3DXVECTOR3 SizeMag;//���������{��
	D3DXCOLOR GateColor;//��̐F--�y�A�𓯂��F�ɂ���

	D3DXMATRIX mtxWorld;
	bool bUse;
}COLLISION_PRE;


//�v���g�^�C�v�錾
void InitCollision_Pre(void);//�]�ږ�̏���������
void UninitCollision_Pre(void);//�]�ږ�̏I������
void UpdateCollision_Pre(void);//�]�ږ�̍X�V����
void DrawCollision_Pre(void);//�]�ږ�̕`�揈��

COLLISION_PRE* GetCollision_Pre(void);

//---------------------���W------------------------�ŏ�--------------------�ő�---�F
void SetCollision_Pre(D3DXVECTOR3 Pos, D3DXVECTOR3 GateMin, D3DXVECTOR3 GateMax ,D3DXCOLOR GateColor);



#endif // !_COLLISION_PRE_H_
