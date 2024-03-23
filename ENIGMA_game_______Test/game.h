//=========================================================
//
//ゲーム画面で使う変数、宣言、構造体[game.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _GAME_H_
#define _GAME_H_//二重インクルード防止

#include"main.h"
#include "model.h"
#include "Actionzone.h"

//#define MAX_WORD	(8192)
//#define MAX_WORD3	(512)

//#define MAX_MODEL	(256) //モデルの最大数
//#define NUM_MODEL	(26) //モデルの種類
#define MAX_FIELD	(256) //床の最大数
#define MAX_WALL	(256) //壁の最大数
#define GAME_END_DELAY	(60)//余韻
#define MODEL_FILE	"data\\Model.bin" //モデルファイル
#define FIELD_FILE	"data\\Field.bin" //床ファイル
#define WALL_FILE	"data\\Wall.bin" //壁ファイル



//=============================================
//モデル読み込みの構想体の定義
//=============================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	D3DXMATRIX mtxWorld;
	D3DCOLORVALUE Diffuse[MAX_MODEL];
	ModelType nType;
	bool bUse;
	bool bUseGame;
}ModelInfo;

//=============================================
//壁読み込みの構想体の定義
//=============================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nType;
	float fWide;
	float fHeight;
	bool bUse;
	bool bUseGame;
}WallInfo;

//=============================================
//床読み込みの構想体の定義
//=============================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nType;
	float fWide;
	float fDepth;
	bool bUse;
	bool bUseGame;
}FieldInfo;

//=============================================
//ゲームの状態
//=============================================
typedef enum
{
	GAMESTATE_PLAY = 0,
	GAMESTATE_TUTORIAL,
	GAMESTATE_END,
	GANESTATE_MAX
}GAMESTATE;



//プロトタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void  GameClear(void);
void ReleasePause(void);
void LoadModel(void);
void LoadField(void);
void LoadWall(void);

//レイを利用した円形同士の当たり判定
bool CheckCollisionWithRay(D3DXVECTOR3 start, D3DXVECTOR3 direction, D3DXVECTOR3 move, float selfRadius, float targetRadius, D3DXVECTOR3 centerPos);



//箱型当たり判定
void BoxCollisionPlayer(D3DXVECTOR3 PlayerMin, D3DXVECTOR3 PlayerMax, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax,int PlayerIndex);
void BoxCollisionKill(D3DXVECTOR3 PlayerMin, D3DXVECTOR3 PlayerMax, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax, int PlayerIndex);
void BoxCollisionEnemy(D3DXVECTOR3 EnemyMin, D3DXVECTOR3 EnemyMax, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax);

//プレイヤーとカメラの間の障害物判定
void AdjustPlayerPositionToCollision_CAMERA(D3DXVECTOR3 playerPos, int CameraIndex, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax);

//プレイヤーと注視点の間の障害物判定
void AdjustPlayerPositionToCollision_VIEWPOS(D3DXVECTOR3 playerPos, int PlayerIndex, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax);

//転移門当たり判定
void BoxCollisionGate(D3DXVECTOR3 PlayerMin, D3DXVECTOR3 PlayerMax, D3DXVECTOR3 GateMin, D3DXVECTOR3 GateMax, int PlayerIndex, int GateIndex, int ParentIndex);

//行動エリア当たり判定
void SphereCollisionZone(D3DXVECTOR3 PlayerPos, int PlayerIndex, int ZoneIndex);

//敵の視野判定
void SphereEnemyView(D3DXVECTOR3 PlayerPos, int PlayerIndex, int ZoneIndex);

//プレイヤー箱型当たり判定--アイテム
void BoxCollisionItem(D3DXVECTOR3 PlayerMin, D3DXVECTOR3 PlayerMax, D3DXVECTOR3 HitPos, int PlayerIndex, int ItemIndex);


//アイテム用当たり判定
void BoxCollisionFromItem(D3DXVECTOR3 ItemMin, D3DXVECTOR3 ItemMax, D3DXVECTOR3 HitMin, D3DXVECTOR3 HitMax, int ItemIndex);



//転移先上げ
void TRansNumPlayerUP(void);
void TRansNumPlayer2UP(void);

//転移先下げ
void TRansNumPlayerDOWN(void);
void TRansNumPlayer2DOWN(void);

//転移番号参照--player1
int GetTRansNumPlayer(void);

//転移番号参照--player2
int GetTRansNumPlayer2(void);


//ランダム選出
int RandSelect(int nMax);

//長押ししたか
bool LongPress(int nButton, int nTime,int nPlayer);

//更新停止
void PlayerUpdateStop(void);
void Player2UpdateStop(void);

#endif 