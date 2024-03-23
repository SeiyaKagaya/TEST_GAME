//=========================================================
//
//�e���ˏ����֌W�Ŏg���ϐ��A�錾�A�\����[item.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _ITEM_H_

#define _ITEM_H_//��d�C���N���[�h�h�~

#include"main.h"
#include "game.h"

#define NUMITEM	(64)//�A�C�e���̍ő吔
//#define TEXNUM	(4)//�e�N�X�`���̐�
#define ITEMSPEED	 (8)//�A�C�e���̍ŏ��̑��x
#define ITEMSIZE	(14.0f)
#define ITEMMOVESPEED_LOCK	(2.0f)
#define ITEMMOVESPEED	(4.0f)
#define ITEMDAMAGE	(15)


//�A�C�e���T�C�Y
#define ITEMMIN	(D3DXVECTOR3(-14.0f,0.0f,-14.0f))
#define ITEMMAX	(D3DXVECTOR3(14.0f,28.0f,14.0f))


//�̌����Ă�����\����
typedef enum
{
	ITEMTYPE_DISH = 0,	//�M
	ITEMTYPE_REMOCON,	//�����R��
	ITEMTYPE_VEGETABLE,	//���
	ITEMTYPE_SOUP,		//�X�[�v
	ITEMTYPE_MAX,
}ITEMTYPE;












//�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 oldPos;	//�Â��ʒu
	float HitPosY;//�ڐG����Y���W

//	D3DXVECTOR3 pos2;	//���V�p�ʒu
	bool bfloatRot;//���V����
	int  nfloatCnt;//���V�J�E���g


	//D3DXVECTOR3 oldPos;

	//D3DXVECTOR3 rot;	//����
	D3DXMATRIX mtxWorldItem;//���[���h�}�g���b�N�X
	D3DXVECTOR3 move;		//�ړ�
	ITEMTYPE ItemType;

	//int nLife;//���C�t
	int nShadowNum;//�e�ԍ�

	bool bRetentionl;//�ؗ����Ă邩

	int nStayGetCnt;//�擾�\�܂ł̑ҋ@
	bool bGetNO;//�擾�ł��邩

	bool bUse;
}ITEM;

//�̍\����
typedef struct
{
	int ItemCnt;



}ITEMCNT;




void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

ITEM* GetItem(void);

//ITEMCNT* GetItemCnt_1P(void);
//ITEMCNT* GetItemCnt_2P(void);

//�ݒ�
void SetItem(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, ITEMTYPE Type);

//�ݒ�2
void SetItem2(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, ITEMTYPE Type,int NoGetCnt);

#endif // _ITEM_H_
