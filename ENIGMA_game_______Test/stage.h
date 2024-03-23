//=========================================================
//
//�ǂŎg���ϐ��A�錾�A�\����[stage.h]
// Author seiya kagaya mori itsuki
//
//=========================================================
#ifndef _STAGE_H_

#define _STAGE_H__//��d�C���N���[�h�h�~

#include"main.h"

#define NUMSTAGE	(128)//�ǂ̐�
#define STAGETEXNUM	(8)//�e�N�X�`���̐�

#define STAGESIZE	(3000.0f)

//�e�N�X�`���̎��
typedef enum
{
	TEXTYPE_00 = 0,
	TEXTYPE_01,
	TEXTYPE_02,
	TEXTYPE_03,
	TEXTYPE_04,
	TEXTYPE_05,//�Ŕ�
	TEXTYPE_06,//��������
	TEXTYPE_07,//����
	TEXTYPE_08,//�M�ē�
	TEXTYPE_09,//�o�X�M�~�b��
	TEXTYPE_MAX
}TEXTYPE;

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 posStage;	//�ʒu
	D3DXVECTOR3 rotStage;	//����
	D3DXMATRIX mtxWorldStage;//���[���h�}�g���b�N�X
	TEXTYPE TexType;

	bool bCollision;//�����蔻�肪ON��
	D3DXVECTOR3	MaxPos;
	D3DXVECTOR3	MinPos;

	bool bUse;
}STAGE;

void InitStage(void);
void UninitStage(void);
void UpdateStage(void);
void DrawStage(void);
STAGE* GetStage(void);

//�ǂ̐ݒ�
void SetStage(D3DXVECTOR3 Pos, D3DXVECTOR3 rot, float bes, float ver, TEXTYPE TexType);

// ���[�J�����W�n�ł̕ǂ̒��_���W��ݒ肷��֐�
void SetWallVertices(VERTEX_3D* pVtx, float bes, float ver);

// �ǂ̈ʒu�Ɖ�]�ɏ���������̒��_���W���v�Z����֐�
void CalculateTransformedWallVertices(D3DXVECTOR3 Pos, D3DXVECTOR3 rot, float bes, float ver, VERTEX_3D* pVtxint,int Index);

void ExclusionCollision_Stage(void);


#endif