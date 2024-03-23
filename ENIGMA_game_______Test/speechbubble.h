//=========================================================
//
//吹き出しUI使う変数、宣言、構造体[speechbubble.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SPEECHBUBBLE_H_

#define _SPEECHBUBBLE_H_//二重インクルード防止

#include"main.h"

#include "game.h"

#define NUMSPEECHBUBBLE	(264)//弾の数

#define TEXNUM	(6)//テクスチャの数

#define ZOOMSPEED	(6)//拡大速度
#define REDSPEED	(4)//縮小速度

#define  XMAG (0.6f)
#define  XMAG2 (0.4f)

typedef enum
{
	SPEECHBUBBLETYPE_TRANCE = 0,
	SPEECHBUBBLETYPE_ACTION,
	SPEECHBUBBLETYPE_GET,
	SPEECHBUBBLETYPE_LONGACTION,
	SPEECHBUBBLETYPE_GAMECLEAR,
	SPEECHBUBBLETYPE_CHANNEL,
	SPEECHBUBBLETYPE_GAUGEFRAME,
	SPEECHBUBBLETYPE_GAUGE,
	SPEECHBUBBLETYPE_MAX,
}SPEECHBUBBLETYPE;


//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXMATRIX mtxWorldSpeechBubble;//ワールドマトリックス
	SPEECHBUBBLETYPE BubbleSType;//状態
	int nBubbleCnt;//
	bool bOK;//何処かのタイミングでOKになってればデクリメントさせない

	bool bTrackingPlayer1;
	bool bTrackingPlayer2;
	int TrackNum;

	bool bUse;
}SPEECHBUBBLE;




void InitSpeechBubble(void);
void UninitSpeechBubble(void);
void UpdateSpeechBubble(void);
void DrawSpeechBubble(int CameraLoopNum);

SPEECHBUBBLE* GetSpeechBubble(void);

//壁の設定-------------------------------アクション番号---[SetType-0が出現、１が縮小]---UI表示の補正値
void SetSpeechBubble(D3DXVECTOR3 Pos,int ActionIndex,int SetType, D3DXVECTOR3 CorrectionValue, SPEECHBUBBLETYPE UI_TYPE,int PlayerIndex);


// 予測交差点を計算する関数
//D3DXVECTOR3 PredictIntersection(SPEECHBUBBLE bullet, Enemy enemy);


#endif // _SPEECHBUBBLE_H_
