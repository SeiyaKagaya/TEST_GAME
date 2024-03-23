//=========================================================
//
//�^�C�����~�b�g�֌W�Ŏg���ϐ��A�錾�A�\����[limittime.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _LIMITTIME_H_

#define _LIMITTIME_H_//��d�C���N���[�h�h�~

#include"main.h"


#define ENDFRAME (60*500)//�������ԃt��*�b

//���΍��W�̒l
#define LIMITTIME_POSX	(20.0f)
#define LIMITTIME_POSY	(20.0f)
//���l���m�̊�
#define LIMITTIMEPOS_SPAN	(40.0f)
//�^�C�����~�b�g�̌���
#define LIMITTIME_NUM	(3)
#define LIMITTIME_DIVISIONUMBER (10)//�e�N�X�`���̖���

//�^�C�����~�b�g�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	bool bUse;//�g�p���Ă��邩�ǂ���
}LimitTime;

typedef struct
{
	int NowTime;//���݂̎c�莞�Ԃ��i�[(game.cpp�ł�������)
}NowTime;

//�v���g�^�C�v�錾
void InitLimitTime(void);
void UninitLimitTime(void);
void UpdateLimitTime(void);
void DrawLimitTime(void);
void SetUpLimitTime(D3DXVECTOR3 pos, int nLimitTime);//���̕ύX�\��
void SubLimitTime(void);
NowTime* GetNowTime(void);

#endif // _LIMITTIME_H_