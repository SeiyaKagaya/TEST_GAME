//=========================================================
//
//パーティクル関係で使う変数、宣言、構造体[particle.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _PARTICLE_H_

#define _PARTICLE_H_//二重インクルード防止

#include"main.h"

//マクロ定義
#define MAX_PARTICLE	(2048)

//テクスチャの数
#define NUMTEX	(2)


//パーティクルの種類
enum PARTICLETYPE//列挙こうもかけるよのモデルケース
{
	PARTICLETYPE_ITEM = 0,

	PARTICLETYPE_MAX
};

//エフェクト構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXMATRIX mtxWorld;//ワールドマトリックス

	D3DXCOLOR col;		//色
	float fRadius;		//半径(大きさ)
	float DiffRadius;	//半径減衰率	
	float nLife;		//寿命(表示時間)
	float nType;		//タイプ識別
	int nloopCnt;		//ループ
	bool bUse;			//使用しているかどうか
}Particle;

//プロトタイプ宣言
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 Pos, float fRadius, int nLife, PARTICLETYPE Type, D3DXCOLOR Color);

Particle* GetParticle(void);

#endif // _PARTICLE_H_