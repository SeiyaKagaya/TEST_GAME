//=========================================================
//
//簡易モーションMODEL宣言など[simple_motion_model.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SIMPELMOTION_//このマクロが定義されてなかったら

//マクロ定義
#define _SIMPELMOTION_//二重インクルード防止のマクロ定義

#include "game.h"
//
//#define MAX_BOOSTER	(1)//ブースターパーツ数
//#define MAX_BOOSTERPARTS	(2)//ブースターパーツ数


//フォントの種類
//--------------------フォントのラベル的な
typedef enum
{
	SIMPLEMOTIONMODEL_Test1 = 0,//
	SIMPLEMOTIONMODEL_Test2,
	SIMPLEMOTIONMODEL_LEVER_RED_ROOT,	//赤レバーの根本
	SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT,	//青レバーの根本
	SIMPLEMOTIONMODEL_LEVER_RED_LEVER,	//赤レバーのレバー
	SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER,	//青レバーのレバー

	SIMPLEMOTIONMODEL_LEVER_RED_ROOT2,	//赤レバーの根本
	SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT2,	//青レバーの根本
	SIMPLEMOTIONMODEL_LEVER_RED_LEVER2,	//赤レバーのレバー
	SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER2,	//青レバーのレバー

	SIMPLEMOTIONMODEL_MAX,
}SIMPLEMOTIONMODEL;


//情報の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置

	D3DXVECTOR3 rot;	//向き

	D3DXMATRIX mtxWorld;//ワールドマトリックス

	bool bUse;
}SIMPLEMODEL;

//プロトタイプ宣言
void InitSimpleModel(void);
void UninitSimpleModel(void);
void UpdateSimpleModel(void);
void DrawSimpleModel(void);
void LaverOn(void);
void SpawnKey(void);
void LaverOnTtl(void);
void SpawnKeyTtl(void);

//簡易モーションモデル設定処理
void SetSimpleModel(SIMPLEMOTIONMODEL SetUpName_Index, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
bool GetSpawnKey_Lever(void);
bool GetSpawnKey_Leverttl(void);

#endif // !_PLAYER_H_
