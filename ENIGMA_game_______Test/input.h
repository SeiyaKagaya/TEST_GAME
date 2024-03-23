//=========================================================
//
//キー入力関係で使う宣言など[input.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _INPUT_H_

#define _INPUT_H_

#include "main.h"



//==================================================
//キーの種類
//==================================================
typedef enum
{
	JOYKEY_UP = 0,			//十字キー上
	JOYKEY_DOWN,			//十字キー下
	JOYKEY_LEFT,			//十字キー左
	JOYKEY_RIGHT,			//十字キー右
	JOYKEY_START,			//スタ-ト
	JOYKEY_BACK,			//バック
	JOYKEY_LPUSH,			//Lトリガー
	JOYKEY_RPUSH,			//Rトリガー
	JOYKEY_L1,				//L1ボタン
	JOYKEY_R1,				//R1ボタン
	JOYKEY_L2,				//L2ボタン
	JOYKEY_R2,				//R2ボタン
	JOYKEY_A,				//Aボタン
	JOYKEY_B,				//Bボタン
	JOYKEY_X,				//Xボタン
	JOYKEY_Y,				//Yボタン
	MAX_KEY
}JOYkey;





//プロトタイプ宣言
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


//コントローラー振動処理
void VibrationLeft(int MotorSpeed, int PadNum);
void VibrationRight(int MotorSpeed, int PadNum);


#endif
