//=============================================
//
//鍵出現UI[keyinfo.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _KEYINFO_H_ //定義されてなかったら
#define _KEYINFO_H_ //２種インクルード防止

#include "main.h"

//=============================================
//テキストの種類の定義
//=============================================
typedef enum
{
	SPAWNPLACE_LIVING = 0, //リビングスポーン
	SPAWNPLACE_BASEMENT, //地下室
	SPAWNPLACE_BATHROOM, //水回り
	NOT_HAVE_REMOCON, //リモコン持ってないとき
	NOT_HAVE_DISH, //皿持ってないとき
	NOT_HAVE_VEGETABLE, //野菜持ってないとき
	NOT_HAVE_NEED_KITCHEN, //キッチンに必要なもの持ってないとき
	NOT_HAVE_SOUP,//スープを持ってないとき
	PUSH_CREEN,//浄化装置押したとき
	SPAWNPLACE_GATE,//脱出門
	MISSMONEYBOX,//金庫失敗
	TAKE_A_BATH,//風呂抜いた
	SPAWN_DISH,//皿湧いた
	SPAWNPLACE_MAX,
}KeySpawnPlace;

//=============================================
//画面に対するトラップの定義
//=============================================
typedef struct
{
	D3DXVECTOR3 pos;
	float fAlpha; //アルファ値
	int nScreenCnt; //継続カウント
	int nPlayerIdx; //表示するプレイヤー
	KeySpawnPlace nSpawnPlace; //スポーン場所
	bool bUse;
}Keyinfo;

void InitKeyinfo(void);
void UninitKeyinfo(void);
void UpdateKeyinfo(void);
void DrawKeyinfo(void);
void DrawTVinfo(void);
void DrawKitcheninfo(void);
void DrawDeskinfo(void);
void DrawKeyinfoText(void); //テキスト表示
void DrawKeyinfoCreen(void);//浄化装置テキスト
void DrawKeyinfoGate(void);//脱出門出現
void DrawKeyinfoMoneyBox(void);//金庫失敗
void DrawKeyinfoBath(void);//風呂抜いた
void DrawKeyinfoDish(void);//皿

void SetKeyinfo(KeySpawnPlace nSpawnPlace, int PlayerIdx); //引数にスポーン場所


#endif