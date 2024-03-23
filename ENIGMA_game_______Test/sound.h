//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// �^�C�g��BGM
	SOUND_LABEL_BGM001 = 1,		// �N���ABGM
	SOUND_LABEL_BGM002 = 2,		// �Q�[���I�[�o�[BGM
	SOUND_LABEL_BGM003 = 3,		// �G�j�O�}BGM
	SOUND_LABEL_BGM004 = 4,		// ���j���[BGM
	SOUND_LABEL_SE_WALK = 5,	// �v���C���[������
	SOUND_LABEL_SE_DIAL = 6,	// �_�C����
	SOUND_LABEL_SE_OPEN = 7,	// ���ɃI�[�v��
	SOUND_LABEL_SE_NOTOPEN = 8,	// ���ɃI�[�v��
	SOUND_LABEL_SE_WATER = 9,	// ����
	SOUND_LABEL_SE_LEVER = 10,	// ���o�[
	SOUND_LABEL_SE_COOK = 11,	// �N�b�L���O
	SOUND_LABEL_SE_BUTTON = 12,	// �{�^��
	SOUND_LABEL_SE_CURSOLMOVE = 13,	// �J�[�\��
	SOUND_LABEL_SE_DECISION = 14,	// ����
	SOUND_LABEL_SE_PAUSE = 15,	// �|�[�Y
	SOUND_LABEL_SE_EYETRAP = 16,	// �A�C�g���b�v
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
 

//����--�Đ������ǂ���--�Đ���=true/�Đ����ĂȂ�=false
//bool SaundPlayJudge(SOUND_LABEL label);

//int TestSoundmain(void);

#endif
