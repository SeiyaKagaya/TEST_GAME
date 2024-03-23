//=============================================
//
//�e���r�̃M�~�b�N[TV.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _TV_H_ //��`����ĂȂ�������
#define _TV_H_ //�Q��C���N���[�h�h�~

#include "main.h"
//=============================================
//�}�N����`
//=============================================
#define TVVISION_WIDE	(50.0f)
#define TVVISION_HEIGHT	(33.0f)
#define NUM_CHANNEL	(5)
#define TV_TEX_MOVE	(1.0f/(float)NUM_CHANNEL)

//=============================================
//�e���r��ʂ̍\�z�̂̒�`
//=============================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nSelectChannel; //�I������Ă�`�����l��
	int nWhichPlayer; //�ǂ����̃v���C���[���{�����Ă邩
	float fWide;
	float fHeight;
	float fTexU;
	bool bUse;
	bool bOn; //�e���r�����邩�ǂ���
}TV_VISION;

//=========================================================
//�v���g�^�C�v�錾
//=========================================================
void InitTV(void);
void UninitTV(void);
void UpdateTV(void);
void DrawTV(void);
void TVController(int nWhichPlayer);
void SetTVVision(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWide, float fHeight);
void SelectChannel(int nSelectChannel);
TV_VISION* GetTVPos(void);

#endif // _POLYGON_H_ //��`����ĂȂ�������