//============================================================================================
//
//�t�F�[�h�Ɋւ���錾��\����[fade.h]
// Author seiya kagaya
//
//============================================================================================
#ifndef _GAMEFADE_H_

#define _GAMEFADE_H_

#include "main.h"


#define MAXGAMEFADE	(2)

//�t�F�[�h�̏��
typedef enum
{
	GAMEFADE_NONE = 0,//�������Ă��Ȃ����
	GAMEFADE_IN,	//�t�F�[�h�C�����
	GAMEFADE_OUT,	//�t�F�[�h�A�E�g���
	GAMEFADE_MAX

}GAMEFADE;

//�v���g�^�C�v�錾
void InitGameFade(void);
void UninitGameFade(void);
void UpdateGameFade(void);
void DrawGameFade(void);

void SetGameFade(int PlayerNum,D3DXVECTOR3 ESCAPEMOVE,D3DXVECTOR3 EscapeRot,D3DXVECTOR3 EscapeRot_Player, bool GameClear,bool CrossRoadTrans);

GAMEFADE GetGameFade(void);

#endif