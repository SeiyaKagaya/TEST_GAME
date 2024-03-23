//=========================================================
//
//�L�[���͂̏����֌W[input.cpp]
// Author seiya kagaya
//
//=========================================================
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX	(256)//�L�[�̍ő吔

//�O���[�o���ϐ�

LPDIRECTINPUT8 g_pInput = NULL;//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevkeyboard = NULL;//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^

BYTE g_aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̃v���X���
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];//�L�[�{�[�h�̃g���K�[���
BYTE g_aKeyStateRelease[NUM_KEY_MAX];//�L�[�{�[�h�̃����[�X���
BYTE g_aKeyStateRepeat[NUM_KEY_MAX];//�L�[�{�[�h�̃��s�[�g���

XINPUT_STATE g_JoykeyState[XUSER_MAX_COUNT];								//�Q�[���p�b�h�̃v���X���
XINPUT_STATE g_JoykeyStateTrigger[XUSER_MAX_COUNT];						//�Q�[���p�b�h�̃g���K�[���
XINPUT_STATE g_JoykeyStateRelease[XUSER_MAX_COUNT];						//�Q�[���p�b�h�̃����[�X���
XINPUT_STATE g_JoykeyStateRepeat[XUSER_MAX_COUNT];						//�Q�[���p�b�h�̃��s�[�g���

_XINPUT_KEYSTROKE g_KeyStroke;//�R���g���[���[���Ƃ̎���



//=============================
//�L�[�{�[�h�̏���������
//=============================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{

	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevkeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevkeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevkeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	return S_OK;

}
//==================================================
//�Q�[���p�b�h�̏�����
//==================================================
HRESULT InitJoypad()
{
	//�������̃N���A
	memset(&g_JoykeyState, 0, sizeof(XINPUT_STATE));

	//Xinput�̃X�e�[�g�̐ݒ�i�L�����p�j
	XInputEnable(true);

	return S_OK;
}
//=============================
//�L�[�{�[�h�̏I������
//=============================
void UninitKeyboard(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (g_pDevkeyboard != NULL)
	{
		g_pDevkeyboard->Unacquire();//�L�[�{�[�h�ւ̃A�N�Z�X����j��
		g_pDevkeyboard->Release();
		g_pDevkeyboard = NULL;
	}
	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//==================================================
//�Q�[���p�b�h�̏I��
//==================================================
void UninitJoypad()
{
	//Xinput�̃X�e�[�g�̐ݒ�
	XInputEnable(false);
}

//=============================
//�L�[�{�[�h�̍X�V����
//=============================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̓��͏��
	
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevkeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//�����[�X����ԏザ��Ȃ��Ɠ��삵�Ȃ�
			//�r�b�g���Z����g���ă����[�X,���s�[�g�̏���ۑ�����(�܂������Ɨ������ĂȂ�)
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];
			g_aKeyStateRepeat[nCntKey] = (g_aKeyState[nCntKey] & aKeyState[nCntKey]);

			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];//�L�[�{�[�h�̃g���K�[����ۑ�����
			g_aKeyState[nCntKey] = aKeyState[nCntKey];//�L�[�{�[�h�̃v���X����ۑ�����
		}
	}
	else
	{
		g_pDevkeyboard->Acquire();//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}

}

//DWORD dwResult;
//for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
//{
//	XINPUT_STATE state;
//	ZeroMemory(&state, sizeof(XINPUT_STATE));
//
//	// Simply get the state of the controller from XInput.
//	dwResult = XInputGetState(i, &state);
//
//	if (dwResult == ERROR_SUCCESS)
//	{
//		// Controller is connected
//	}
//	else
//	{
//		// Controller is not connected
//	}
//}





//==================================================
//�Q�[���p�b�h�X�V
//==================================================
void UpdateJoypad()
{
	XINPUT_STATE joykeystate;

	for (DWORD PadNum = 0; PadNum < XUSER_MAX_COUNT; PadNum++)
	{

		//�W���C�p�b�g�̏�Ԃ��擾
		if (XInputGetState(PadNum, &joykeystate) == ERROR_SUCCESS)
		{
			//if (g_KeyStroke.UserIndex == 0)
		//	{



				//�����[�X����ԏザ��Ȃ��Ɠ��삵�Ȃ�
					//�r�b�g���Z����g���ă����[�X,���s�[�g�̏���ۑ�����(�܂������Ɨ������ĂȂ�)
			g_JoykeyStateRelease[PadNum].Gamepad.wButtons = (g_JoykeyState[PadNum].Gamepad.wButtons ^ joykeystate.Gamepad.wButtons) & ~joykeystate.Gamepad.wButtons;		//�����[�X����	

			g_JoykeyStateRepeat[PadNum].Gamepad.wButtons = (g_JoykeyState[PadNum].Gamepad.wButtons & joykeystate.Gamepad.wButtons);											//���s�[�g����	

			g_JoykeyStateTrigger[PadNum].Gamepad.wButtons = (g_JoykeyState[PadNum].Gamepad.wButtons & joykeystate.Gamepad.wButtons) ^ joykeystate.Gamepad.wButtons;			//�g���K�[����	


			// �X�e�B�b�N�̃f�b�h�]�[��
			if ((g_JoykeyState[PadNum].Gamepad.sThumbLX <  (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000) &&
				g_JoykeyState[PadNum].Gamepad.sThumbLX > -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000)) &&
				(g_JoykeyState[PadNum].Gamepad.sThumbLY <  (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000) &&
					g_JoykeyState[PadNum].Gamepad.sThumbLY > -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000)))
			{
				g_JoykeyState[PadNum].Gamepad.sThumbLX = 0;
				g_JoykeyState[PadNum].Gamepad.sThumbLY = 0;
			}

			g_JoykeyState[PadNum] = joykeystate;

			//	}
		}
	}
}
//=============================
//�L�[�{�[�h�̃v���X�����擾
//=============================
bool GetkeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) != 0;
}
//=============================
//�L�[�{�[�h�̃g���K�[�����擾
//=============================
bool GetkeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) != 0;
}
//=============================
//�L�[�{�[�h�̃����[�X�����擾
//=============================
bool GetkeyboardRelease(int nKey)
{
 	return(g_aKeyStateRelease[nKey] & 0x80) != 0;
}
//=============================
//�L�[�{�[�h�̃��s�[�g�����擾
//=============================
bool GetkeyboardRepeat(int nKey)
{
	return(g_aKeyStateRepeat[nKey] & 0x80) != 0;
}

//==================================================
//�Q�[���p�b�h�̏����擾(����)
//==================================================
bool GetJoypadPress(JOYkey key, int PadNum)
{
	return (g_JoykeyState[PadNum].Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//==================================================
//�Q�[���p�b�h�̏����擾
//==================================================
bool GetJoypadTrigger(JOYkey key, int PadNum)
{
	return (g_JoykeyStateTrigger[PadNum].Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//=============================
//�L�[�{�[�h�̃����[�X�����擾
//=============================
bool GetJoypadRelease(JOYkey key, int PadNum)
{
	return (g_JoykeyStateRelease[PadNum].Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//=============================
//�L�[�{�[�h�̃��s�[�g�����擾
//=============================
bool GetJoypadRepeat(JOYkey key, int PadNum)
{
	return (g_JoykeyStateRepeat[PadNum].Gamepad.wButtons & (0x01 << key)) ? true : false;
}







//=============================
//�R���g���[���[�U������(��)
//=============================
void VibrationLeft(int MotorSpeed, int PadNum)
{
	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
	if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
	{

		//�֐�����

		////����
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = MotorSpeed; // use any value between 0-65535 here
		//vibration.wRightMotorSpeed = 16000; // use any value between 0-65535 here
		XInputSetState(PadNum, &vibration);
	}

}
//=============================
//�R���g���[���[�U������(�E)
//=============================
void VibrationRight(int MotorSpeed, int PadNum)
{
	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
	if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
	{

		//�֐�����

		////����
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		//vibration.wLeftMotorSpeed = 32000; // use any value between 0-65535 here
		vibration.wRightMotorSpeed = MotorSpeed; // use any value between 0-65535 here
		XInputSetState(PadNum, &vibration);
	}
}



