//=========================================================
//
//�L�[���͊֌W�Ŏg���錾�Ȃ�[input.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _INPUT_H_

#define _INPUT_H_

#include "main.h"



//==================================================
//�L�[�̎��
//==================================================
typedef enum
{
	JOYKEY_UP = 0,			//�\���L�[��
	JOYKEY_DOWN,			//�\���L�[��
	JOYKEY_LEFT,			//�\���L�[��
	JOYKEY_RIGHT,			//�\���L�[�E
	JOYKEY_START,			//�X�^-�g
	JOYKEY_BACK,			//�o�b�N
	JOYKEY_LPUSH,			//L�g���K�[
	JOYKEY_RPUSH,			//R�g���K�[
	JOYKEY_L1,				//L1�{�^��
	JOYKEY_R1,				//R1�{�^��
	JOYKEY_L2,				//L2�{�^��
	JOYKEY_R2,				//R2�{�^��
	JOYKEY_A,				//A�{�^��
	JOYKEY_B,				//B�{�^��
	JOYKEY_X,				//X�{�^��
	JOYKEY_Y,				//Y�{�^��
	MAX_KEY
}JOYkey;





//�v���g�^�C�v�錾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);

void UninitKeyboard(void);
void UpdateKeyboard(void);

bool GetkeyboardPress(int nKey);
bool GetkeyboardTrigger(int nKey);
bool GetkeyboardRelease(int nKey);
bool GetkeyboardRepeat(int nKey);

HRESULT InitJoypad();
void UninitJoypad();
void UpdateJoypad();
bool GetJoypadPress(JOYkey key,int PadNum);
bool GetJoypadTrigger(JOYkey key, int PadNum);
bool GetJoypadRelease(JOYkey key, int PadNum);
bool GetJoypadRepeat(JOYkey key, int PadNum);


//�R���g���[���[�U������
void VibrationLeft(int MotorSpeed, int PadNum);
void VibrationRight(int MotorSpeed, int PadNum);


#endif
