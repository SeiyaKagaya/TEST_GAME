//=============================================
//
//マップエディター[model.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _model_H_ //定義されてなかったら
#define _model_H_ //２種インクルード防止

#include "main.h"

#define MAX_MODEL	(256) //モデルの最大数
#define NUM_MODEL	(28) //モデルの種類
#define NUM_TEXTURE	(20) //テクスチャ数

typedef enum
{
	MODELTYPE_BATH = 0,
	MODELTYPE_CACTUS,
	MODELTYPE_CARDBOARD,
	MODELTYPE_CUPBOARD,
	MODELTYPE_DESK,
	MODELTYPE_DOOR,
	MODELTYPE_FLOWERPOT,
	MODELTYPE_GARAGE,
	MODELTYPE_KEY1,
	MODELTYPE_KEY2,
	MODELTYPE_KEY3,
	MODELTYPE_KITCHEN,
	MODELTYPE_METARSHELF,
	MODELTYPE_MICROWAVEOVEN,
	MODELTYPE_POT,
	MODELTYPE_REFRIGERATOR,
	MODELTYPE_SLIDEDOOR,
	MODELTYPE_SOFA,
	MODELTYPE_STAIRS,
	MODELTYPE_SWOLLENCACTUS,
	MODELTYPE_TOILET,
	MODELTYPE_TV,
	MODELTYPE_TVSTAND,
	MODELTYPE_WASHBASIN,
	MODELTYPE_CUBE,
	MODELTYPE_SAFE,
	MODELTYPE_ESCAPEDOOR,
	MODELTYPE_BUTTON,
	MODELTYPE_MAX,
}ModelType;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 Minpos;
	D3DXVECTOR3 Maxpos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	DWORD nNumMat;
	D3DXMATRIX mtxWorld;
	LPDIRECT3DTEXTURE9 pTexture;
	int nShadow;
	int nCntMat;
	ModelType nType;
	bool bUse;
	bool bCollision;//当たり判定あるか

}MAPOBJECT;

void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot,ModelType nType);
void GetKey(ModelType nType);
MAPOBJECT* GetMapObject(void);

//当たり判定除外処理
void ExclusionCollision(void);




#endif // _POLYGON_H_ //定義されてなかったら

