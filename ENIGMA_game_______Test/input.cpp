//=========================================================
//
//キー入力の処理関係[input.cpp]
// Author seiya kagaya
//
//=========================================================
#include "input.h"

//マクロ定義
#define NUM_KEY_MAX	(256)//キーの最大数

//グローバル変数

LPDIRECTINPUT8 g_pInput = NULL;//DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevkeyboard = NULL;//入力デバイス(キーボード)へのポインタ

BYTE g_aKeyState[NUM_KEY_MAX];//キーボードのプレス情報
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];//キーボードのトリガー情報
BYTE g_aKeyStateRelease[NUM_KEY_MAX];//キーボードのリリース情報
BYTE g_aKeyStateRepeat[NUM_KEY_MAX];//キーボードのリピート情報

XINPUT_STATE g_JoykeyState[XUSER_MAX_COUNT];								//ゲームパッドのプレス情報
XINPUT_STATE g_JoykeyStateTrigger[XUSER_MAX_COUNT];						//ゲームパッドのトリガー情報
XINPUT_STATE g_JoykeyStateRelease[XUSER_MAX_COUNT];						//ゲームパッドのリリース情報
XINPUT_STATE g_JoykeyStateRepeat[XUSER_MAX_COUNT];						//ゲームパッドのリピート情報

_XINPUT_KEYSTROKE g_KeyStroke;//コントローラーごとの識別



//=============================
//キーボードの初期化処理
//=============================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{

	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス（キーボード）の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevkeyboard, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(g_pDevkeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(g_pDevkeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	return S_OK;

}
//==================================================
//ゲームパッドの初期化
//==================================================
HRESULT InitJoypad()
{
	//メモリのクリア
	memset(&g_JoykeyState, 0, sizeof(XINPUT_STATE));

	//Xinputのステートの設定（有効活用）
	XInputEnable(true);

	return S_OK;
}
//=============================
//キーボードの終了処理
//=============================
void UninitKeyboard(void)
{
	//入力デバイス(キーボード)の破棄
	if (g_pDevkeyboard != NULL)
	{
		g_pDevkeyboard->Unacquire();//キーボードへのアクセス権を破棄
		g_pDevkeyboard->Release();
		g_pDevkeyboard = NULL;
	}
	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//==================================================
//ゲームパッドの終了
//==================================================
void UninitJoypad()
{
	//Xinputのステートの設定
	XInputEnable(false);
}

//=============================
//キーボードの更新処理
//=============================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//キーボードの入力情報
	
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevkeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//リリースが一番上じゃないと動作しない
			//ビット演算を駆使してリリース,リピートの情報を保存する(まだちゃんと理解してない)
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];
			g_aKeyStateRepeat[nCntKey] = (g_aKeyState[nCntKey] & aKeyState[nCntKey]);

			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];//キーボードのトリガー情報を保存する
			g_aKeyState[nCntKey] = aKeyState[nCntKey];//キーボードのプレス情報を保存する
		}
	}
	else
	{
		g_pDevkeyboard->Acquire();//キーボードへのアクセス権を獲得
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
//ゲームパッド更新
//==================================================
void UpdateJoypad()
{
	XINPUT_STATE joykeystate;

	for (DWORD PadNum = 0; PadNum < XUSER_MAX_COUNT; PadNum++)
	{

		//ジョイパットの状態を取得
		if (XInputGetState(PadNum, &joykeystate) == ERROR_SUCCESS)
		{
			//if (g_KeyStroke.UserIndex == 0)
		//	{



				//リリースが一番上じゃないと動作しない
					//ビット演算を駆使してリリース,リピートの情報を保存する(まだちゃんと理解してない)
			g_JoykeyStateRelease[PadNum].Gamepad.wButtons = (g_JoykeyState[PadNum].Gamepad.wButtons ^ joykeystate.Gamepad.wButtons) & ~joykeystate.Gamepad.wButtons;		//リリース処理	

			g_JoykeyStateRepeat[PadNum].Gamepad.wButtons = (g_JoykeyState[PadNum].Gamepad.wButtons & joykeystate.Gamepad.wButtons);											//リピート処理	

			g_JoykeyStateTrigger[PadNum].Gamepad.wButtons = (g_JoykeyState[PadNum].Gamepad.wButtons & joykeystate.Gamepad.wButtons) ^ joykeystate.Gamepad.wButtons;			//トリガー処理	


			// スティックのデッドゾーン
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
//キーボードのプレス情報を取得
//=============================
bool GetkeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) != 0;
}
//=============================
//キーボードのトリガー情報を取得
//=============================
bool GetkeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) != 0;
}
//=============================
//キーボードのリリース情報を取得
//=============================
bool GetkeyboardRelease(int nKey)
{
 	return(g_aKeyStateRelease[nKey] & 0x80) != 0;
}
//=============================
//キーボードのリピート情報を取得
//=============================
bool GetkeyboardRepeat(int nKey)
{
	return(g_aKeyStateRepeat[nKey] & 0x80) != 0;
}

//==================================================
//ゲームパッドの情報を取得(押込)
//==================================================
bool GetJoypadPress(JOYkey key, int PadNum)
{
	return (g_JoykeyState[PadNum].Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//==================================================
//ゲームパッドの情報を取得
//==================================================
bool GetJoypadTrigger(JOYkey key, int PadNum)
{
	return (g_JoykeyStateTrigger[PadNum].Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//=============================
//キーボードのリリース情報を取得
//=============================
bool GetJoypadRelease(JOYkey key, int PadNum)
{
	return (g_JoykeyStateRelease[PadNum].Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//=============================
//キーボードのリピート情報を取得
//=============================
bool GetJoypadRepeat(JOYkey key, int PadNum)
{
	return (g_JoykeyStateRepeat[PadNum].Gamepad.wButtons & (0x01 << key)) ? true : false;
}







//=============================
//コントローラー振動処理(左)
//=============================
void VibrationLeft(int MotorSpeed, int PadNum)
{
	XINPUT_STATE joykeystate;

	//ショイパットの状態を取得
	if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
	{

		//関数分け

		////動く
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = MotorSpeed; // use any value between 0-65535 here
		//vibration.wRightMotorSpeed = 16000; // use any value between 0-65535 here
		XInputSetState(PadNum, &vibration);
	}

}
//=============================
//コントローラー振動処理(右)
//=============================
void VibrationRight(int MotorSpeed, int PadNum)
{
	XINPUT_STATE joykeystate;

	//ショイパットの状態を取得
	if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
	{

		//関数分け

		////動く
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		//vibration.wLeftMotorSpeed = 32000; // use any value between 0-65535 here
		vibration.wRightMotorSpeed = MotorSpeed; // use any value between 0-65535 here
		XInputSetState(PadNum, &vibration);
	}
}



