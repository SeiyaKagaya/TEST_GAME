//=========================================================
//
//タイムリミット関係で使う変数、宣言、構造体[limittime.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _LIMITTIME_H_

#define _LIMITTIME_H_//二重インクルード防止

#include"main.h"


#define ENDFRAME (60*500)//制限時間フレ*秒

//相対座標の値
#define LIMITTIME_POSX	(20.0f)
#define LIMITTIME_POSY	(20.0f)
//数値同士の間
#define LIMITTIMEPOS_SPAN	(40.0f)
//タイムリミットの桁数
#define LIMITTIME_NUM	(3)
#define LIMITTIME_DIVISIONUMBER (10)//テクスチャの枚数

//タイムリミット構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;//移動量
	bool bUse;//使用しているかどうか
}LimitTime;

typedef struct
{
	int NowTime;//現在の残り時間を格納(game.cppでつかうため)
}NowTime;

//プロトタイプ宣言
void InitLimitTime(void);
void UninitLimitTime(void);
void UpdateLimitTime(void);
void DrawLimitTime(void);
void SetUpLimitTime(D3DXVECTOR3 pos, int nLimitTime);//名称変更予定
void SubLimitTime(void);
NowTime* GetNowTime(void);

#endif // _LIMITTIME_H_