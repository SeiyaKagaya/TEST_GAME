//=============================================
//
//ゲージ処理[gauge.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "main.h"

//=============================================
//マクロ定義
//=============================================
#define CNT_GAUGE	(4)			//ゲージの最大数

#define FRANE_MAG_X	(3.0f)
#define FRANE_MAG_Y	(3.0f)

//=============================================
// ゲージの種類
//============================================= 
typedef enum
{
	GAUGETYPE_FRAME_1P = 0,
	GAUGETYPE_MAINBODY_1P,
	GAUGETYPE_FRAME_2P,
	GAUGETYPE_MAINBODY_2P,
	GAUGETYPE_MAX
}GaugeType;

//=============================================
//構想体の定義
//=============================================
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXCOLOR Col;
	float Length_X;//プラス方向のXの長さ
	float Length_Y;//上下方向のYの長さ
	bool DrawOK;//描画可能か
	bool bUse; //使用されているかの確認

	float MaxLength_X;//長さの最大
	int Cnt_X;//最大カウント
	int MaxCnt_X;//最大カウント
	GaugeType type;//属性
}Gauge;

//プロトタイプ宣言
void InitGauge(void);
void UninitGauge(void);
void UpdateGauge(void);
void DrawGauge(void);
//-----------------------位置------------色-----------Yの長さ---------X値としての最大値---Xの最大の長さ----------------タイプ
void SetGauge(D3DXVECTOR3 pos, D3DXCOLOR Col, float Length_Y, int MaxCnt_X, float MaxLength_X, GaugeType type);
Gauge* GetGauge(void);
#endif // !_gauge_H_

