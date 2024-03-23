//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンド一覧
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// タイトルBGM
	SOUND_LABEL_BGM001 = 1,		// クリアBGM
	SOUND_LABEL_BGM002 = 2,		// ゲームオーバーBGM
	SOUND_LABEL_BGM003 = 3,		// エニグマBGM
	SOUND_LABEL_BGM004 = 4,		// メニューBGM
	SOUND_LABEL_SE_WALK = 5,	// プレイヤー歩き音
	SOUND_LABEL_SE_DIAL = 6,	// ダイヤル
	SOUND_LABEL_SE_OPEN = 7,	// 金庫オープン
	SOUND_LABEL_SE_NOTOPEN = 8,	// 金庫オープン
	SOUND_LABEL_SE_WATER = 9,	// 流す
	SOUND_LABEL_SE_LEVER = 10,	// レバー
	SOUND_LABEL_SE_COOK = 11,	// クッキング
	SOUND_LABEL_SE_BUTTON = 12,	// ボタン
	SOUND_LABEL_SE_CURSOLMOVE = 13,	// カーソル
	SOUND_LABEL_SE_DECISION = 14,	// 決定
	SOUND_LABEL_SE_PAUSE = 15,	// ポーズ
	SOUND_LABEL_SE_EYETRAP = 16,	// アイトラップ
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
 

//自作--再生中かどうか--再生中=true/再生してない=false
//bool SaundPlayJudge(SOUND_LABEL label);

//int TestSoundmain(void);

#endif
