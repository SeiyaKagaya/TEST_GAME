//=============================================
//
//�Q�[�W����[gauge.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "main.h"

//=============================================
//�}�N����`
//=============================================
#define CNT_GAUGE	(4)			//�Q�[�W�̍ő吔

#define FRANE_MAG_X	(3.0f)
#define FRANE_MAG_Y	(3.0f)

//=============================================
// �Q�[�W�̎��
//============================================= 
typedef enum
{
	GAUGETYPE_FRAME_1P = 0,
	GAUGETYPE_MAINBODY_1P,
	GAUGETYPE_FRAME_2P,
	GAUGETYPE_MAINBODY_2P,
	GAUGETYPE_MAX
}GaugeType;

//=============================================
//�\�z�̂̒�`
//=============================================
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXCOLOR Col;
	float Length_X;//�v���X������X�̒���
	float Length_Y;//�㉺������Y�̒���
	bool DrawOK;//�`��\��
	bool bUse; //�g�p����Ă��邩�̊m�F

	float MaxLength_X;//�����̍ő�
	int Cnt_X;//�ő�J�E���g
	int MaxCnt_X;//�ő�J�E���g
	GaugeType type;//����
}Gauge;

//�v���g�^�C�v�錾
void InitGauge(void);
void UninitGauge(void);
void UpdateGauge(void);
void DrawGauge(void);
//-----------------------�ʒu------------�F-----------Y�̒���---------X�l�Ƃ��Ă̍ő�l---X�̍ő�̒���----------------�^�C�v
void SetGauge(D3DXVECTOR3 pos, D3DXCOLOR Col, float Length_Y, int MaxCnt_X, float MaxLength_X, GaugeType type);
Gauge* GetGauge(void);
#endif // !_gauge_H_

