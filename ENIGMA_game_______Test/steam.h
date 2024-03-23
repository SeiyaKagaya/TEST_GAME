//=============================================
//
//�����C�̃M�~�b�N[steam.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _STEAM_H_ //��`����ĂȂ�������
#define _STEAM_H_ //�Q��C���N���[�h�h�~

#include "main.h"

//=============================================
//�}�N����`
//=============================================
#define STEAM_LIFE		(120)
#define STEAM_WIDE		(20.0f)
#define STEAM_HEIGHT	(20.0f)
#define STEAM_SPEED		(2.0f)
#define MAX_STEAM	(1024)

//=============================================
//�����C�̓��C�̍\�z�̂̒�`
//=============================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	int nLife;
	bool bUse;
}Steam;

//=============================================
//�v���g�^�C�v�錾
//=============================================
void InitSteam(void);
void UninitSteam(void);
void UpdateSteam(void);
void DrawSteam(void);
void SetSteam(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col);
void OffSteam(void);
#endif // _STEAM_H_ //��`����ĂȂ�������