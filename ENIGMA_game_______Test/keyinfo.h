//=============================================
//
//���o��UI[keyinfo.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _KEYINFO_H_ //��`����ĂȂ�������
#define _KEYINFO_H_ //�Q��C���N���[�h�h�~

#include "main.h"

//=============================================
//�e�L�X�g�̎�ނ̒�`
//=============================================
typedef enum
{
	SPAWNPLACE_LIVING = 0, //���r���O�X�|�[��
	SPAWNPLACE_BASEMENT, //�n����
	SPAWNPLACE_BATHROOM, //�����
	NOT_HAVE_REMOCON, //�����R�������ĂȂ��Ƃ�
	NOT_HAVE_DISH, //�M�����ĂȂ��Ƃ�
	NOT_HAVE_VEGETABLE, //��؎����ĂȂ��Ƃ�
	NOT_HAVE_NEED_KITCHEN, //�L�b�`���ɕK�v�Ȃ��̎����ĂȂ��Ƃ�
	NOT_HAVE_SOUP,//�X�[�v�������ĂȂ��Ƃ�
	PUSH_CREEN,//�򉻑��u�������Ƃ�
	SPAWNPLACE_GATE,//�E�o��
	MISSMONEYBOX,//���Ɏ��s
	TAKE_A_BATH,//���C������
	SPAWN_DISH,//�M�N����
	SPAWNPLACE_MAX,
}KeySpawnPlace;

//=============================================
//��ʂɑ΂���g���b�v�̒�`
//=============================================
typedef struct
{
	D3DXVECTOR3 pos;
	float fAlpha; //�A���t�@�l
	int nScreenCnt; //�p���J�E���g
	int nPlayerIdx; //�\������v���C���[
	KeySpawnPlace nSpawnPlace; //�X�|�[���ꏊ
	bool bUse;
}Keyinfo;

void InitKeyinfo(void);
void UninitKeyinfo(void);
void UpdateKeyinfo(void);
void DrawKeyinfo(void);
void DrawTVinfo(void);
void DrawKitcheninfo(void);
void DrawDeskinfo(void);
void DrawKeyinfoText(void); //�e�L�X�g�\��
void DrawKeyinfoCreen(void);//�򉻑��u�e�L�X�g
void DrawKeyinfoGate(void);//�E�o��o��
void DrawKeyinfoMoneyBox(void);//���Ɏ��s
void DrawKeyinfoBath(void);//���C������
void DrawKeyinfoDish(void);//�M

void SetKeyinfo(KeySpawnPlace nSpawnPlace, int PlayerIdx); //�����ɃX�|�[���ꏊ


#endif