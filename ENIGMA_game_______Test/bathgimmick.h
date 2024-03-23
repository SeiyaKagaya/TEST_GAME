//=============================================
//
//�����C�̃M�~�b�N[bathgimmick.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BATHGIMMICK_H_ //��`����ĂȂ�������
#define _BATHGIMMICK_H_ //�Q��C���N���[�h�h�~

#include "main.h"
//=============================================
//�}�N����`
//=============================================
#define BATHWATER_WIDE	(30)
#define BATHWATER_DEPTH	(60)
#define SPAWN_STEAM		(20) //���C���o��J�E���g
#define USE_STEAM		(20) //���̃X�|�[���œ��C���o�鐔
#define RUNWATER_SPEED	(0.1f) //�����X�s�[�h

typedef enum
{
	GREEN_WATER = 0, //��
	BATH_WATER,
	WATER_MAX,
}WATER_TYPE;

//=============================================
//�����C�̂����̍\�z�̂̒�`
//=============================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	WATER_TYPE nType; //���̃^�C�v
	int nSteamSpawnCnt; //���C���X�|�[������܂ŃJ�E���g����
	int nRunPlayer; //�ǂ����̃v���C���[���쓮��������
	float fWide;
	float fDepth;
	bool bItemSpawn;
	bool bUse;
	bool bRun; //�����𗬂���
}BathWater;

//=========================================================
//�v���g�^�C�v�錾
//=========================================================
void InitBathGimmick(void);
void UninitBathGimmick(void);
void UpdateBathGimmick(void);
void DrawBathGimmick(void);
void SetBathWater(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWide, float fDepth, WATER_TYPE nType);
void RunWater(int nPlayer);
BathWater* GetBathGimmick(void);

#endif // _POLYGON_H_ //��`����ĂȂ�������