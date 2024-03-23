//=============================================
//
//�}�b�v�G�f�B�^�[[model.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _model_H_ //��`����ĂȂ�������
#define _model_H_ //�Q��C���N���[�h�h�~

#include "main.h"

#define MAX_MODEL	(256) //���f���̍ő吔
#define NUM_MODEL	(28) //���f���̎��
#define NUM_TEXTURE	(20) //�e�N�X�`����

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
	bool bCollision;//�����蔻�肠�邩

}MAPOBJECT;

void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot,ModelType nType);
void GetKey(ModelType nType);
MAPOBJECT* GetMapObject(void);

//�����蔻�菜�O����
void ExclusionCollision(void);




#endif // _POLYGON_H_ //��`����ĂȂ�������

