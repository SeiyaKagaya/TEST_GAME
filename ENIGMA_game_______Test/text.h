//=========================================================
//
//���U���g��ʂŎg���ϐ��A�錾�A�\����[text.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _TEXT_H

#define _TEXT_H_//��d�C���N���[�h�h�~

#include"main.h"
#include <d3d9.h>


//�t�H���g�̎��
//--------------------�t�H���g�̃��x���I��
typedef enum
{
	FONT_DOKIDOKI = 0,//�ǂ��ǂ��t�@���^�W�A
	FONT_AKABARASINDELERA,//���K�N�V���f����
	FONT_KEIFONT,//�����ӂ����
	FONT_SOUKOUMINCHO,//���b����
	FONT_KIRARAJI04,//����玚04
	FONT_ONRYOU,//����t�H���g
	FONT_GENSIN,//���񂵂�
	FONT_MAX,
}FONT;

#define MAXFONT (FONT_MAX)//---�t�H���g�̐�

//�v���g�^�C�v�錾
void InitText(void);
void UninitText(void);
//�e�L�X�g�����o������
void DrawTextSet(D3DXVECTOR3 DrawPos, int FontSize, FONT Font, D3DXCOLOR RGBA, const char* Text, ...);


//void DrawWorldText(D3DXVECTOR3 WorldPos, int FontSize, FONT Font, D3DXCOLOR RGBA, const char* Text, ...);


#endif // !_TEXT_H_