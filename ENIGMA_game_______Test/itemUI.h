//=========================================================
//
//�e���ˏ����֌W�Ŏg���ϐ��A�錾�A�\����[item.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _ITEMUI_H_

#define _ITEMUI_H_//��d�C���N���[�h�h�~

#include"main.h"

#include "game.h"


#include "item.h"

#define ITEMTEXUINUM	(8)//�e�N�X�`���ő吔
#define MAXITEMUI	(32)//�ő吔

#define ITEMUISIZE	(32.0f)//�T�C�Y
#define ITEMUISIZE2	(26.0f)//�T�C�Y


#define MAXGETITEM	(3)//�A�C�e���ő及����

#define ITEMMOVESPEED_UI	(15.0f)

typedef enum
{
	ITEM_UI_TYPE_FRAME = 0,//�g
	ITEM_UI_TYPE_POINTER, //�|�C���^�[
	ITEM_UI_TYPE_MAINBODY,//�{��
	ITEM_UI_TYPE_KEYUI,//��UI
	ITEM_UI_TYPE_MAX

}ITEM_UI_TYPE;



//�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	ITEM_UI_TYPE UItype;//UI�̃^�C�v
	ITEMTYPE nItemType;//�A�C�e���̎��
	
	int PosNum;//�A�C�e���{�̂̎�����A���W�ʒu�ԍ����i�[�A���̑���-1


	int PlayerNum;//�v���C���[�ԍ�1/2

	bool bUse;

}ITEM_UI;









void InitItem_UI(void);
void UninitItem_UI(void);
void UpdateItem_UI(bool Player1InputOK, bool Player2InputOK);
void DrawItem_UI(void);



void SetItem_UI(D3DXVECTOR3 pos, ITEM_UI_TYPE ItemUIType, ITEMTYPE ItemType,int PosNum,int PlayerNum);

void DrawHaveKey(int nHaveKey);



//�A�C�e����������
//void ItemRedProces_1P(void);

//�A�C�e���擾�ł��邩����
void GetItem_FromUI(int ItemIndex,int PlayerNum);

//�R���g���[���[���͔��f����(�A�C�e��UI)
void InPutControllerITEM_UI(int PlayerNum);

//�A�C�e���폜�֐�
void DeleteItem_UI(int PlayerNum, ITEMTYPE ItemType);

#endif // _ITEM_H_
