=========================================================
//
//弾発射処理関係で使う変数、宣言、構造体[bullet.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _BULLET_H_

#define _BULLET_H_//二重インクルード防止

#include"main.h"

#include "enemy.h"
#include "game.h"

#define NUMBULLET	(1048)//弾の数
#define TEXNUM	(4)//テクスチャの数

#define BULLETSPEED	 (8)//球の速度

#define BULLETSIZE	(4)

#define BULLETMOVESPEED_LOCK	(45.0f)
#define BULLETMOVESPEED	(4.0f)

#define BULLETDAMAGE	(15)


//プレイヤーサイズ
#define BULLETMIN	(D3DXVECTOR3(-3.0f,-3.0f,-3.0f))
#define BULLETMAX	(D3DXVECTOR3(3.0f,3.0f,3.0f))


//壁の向いてる方向構造体
typedef enum
{
	BULLETTYPE_Player = 0,
	BULLETTYPE_Enemy,
	BULLETTYPE_MAX,
}BULLETTYPE;


//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 oldPos;

	//D3DXVECTOR3 rot;	//向き
	D3DXMATRIX mtxWorldBullet;//ワールドマトリックス
	D3DXVECTOR3 move;		//移動
	BULLETTYPE BulletType;//壁の向き

	int nLife;//ライフ

	int nShadowNum;//影番号

	EXISTENCETYPE ExstenceType;

	bool bUse;
}BULLET;




void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

BULLET* GetBullet(void);

void HitBullet_Enemy(int EnemyIndex);////敵被弾処理--通常弾
void HitBullet_tPlayer(void);////自機被弾処理--通常弾





//壁の設定
void SetBullet(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, int Width, int height, BULLETTYPE testType);


// 予測交差点を計算する関数
D3DXVECTOR3 PredictIntersection(BULLET bullet, Enemy enemy);


#endif // _BULLET_H_
