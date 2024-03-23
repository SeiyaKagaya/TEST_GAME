//=========================================================
//
//�ȈՃ��[�V�������f���\�����鏈��[simple_motion_model.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "simple_motion_model.h"
#include "enemy.h"
#include "keyinfo.h"
#include "sound.h"

//-------------------------------------------
//�}�N����`
//-------------------------------------------
#define LEVER_ACTIONZONE_RADIUS	(120.0f) //�����C�̃M�~�b�N����
#define NUM_ROOM	(3) //������
#define LIVING_SPAWN_POS	(D3DXVECTOR3(3675.0f,120.0f,-1923.0f))
#define BASEMENT_SPAWN_POS	(D3DXVECTOR3(-904.0f,20.0f,-1205.0f))
#define BATHROOM_SPAWN_POS	(D3DXVECTOR3(3235.0f,20.0f,-600.0f))

//�O���[�o���ϐ��錾
bool g_bKeyspawn = false; 
bool g_bKeyspawnTtl = false;

//���f���\����
typedef struct
{
	const char* pFilePass;	// MODEL�t�@�C���p�X
	SIMPLEMOTIONMODEL MyNum;//�����ԍ��iindex�j
	SIMPLEMOTIONMODEL ParentNum;//�e�ԍ�(index).�����������Ɣԍ���
	SIMPLEMODEL SinpleModel;//pos�Ȃ�
} SIMPLEMODELINFO;



//-------------------------------------------
//�@�@"�t�@�C���p�X","����(index)"."�e(index)"
//-------------------------------------------
SIMPLEMODELINFO g_ModelInfo[SIMPLEMOTIONMODEL_MAX] =
{							//����-----------------�e
	{"data\\MODEL\\key1.x",SIMPLEMOTIONMODEL_Test1,SIMPLEMOTIONMODEL_Test1},//�e�X�g�̂��ߏ��������K�{
	{"data\\MODEL\\key2.x",SIMPLEMOTIONMODEL_Test2,SIMPLEMOTIONMODEL_Test1},
	{"data\\MODEL\\leverroot.x",SIMPLEMOTIONMODEL_LEVER_RED_ROOT,SIMPLEMOTIONMODEL_LEVER_RED_ROOT},
	{"data\\MODEL\\leverroot.x",SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT,SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT},
	{"data\\MODEL\\leverred.x",SIMPLEMOTIONMODEL_LEVER_RED_LEVER,SIMPLEMOTIONMODEL_LEVER_RED_ROOT},
	{"data\\MODEL\\leverblue.x",SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER,SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT},

	{"data\\MODEL\\leverroot.x",SIMPLEMOTIONMODEL_LEVER_RED_ROOT2,SIMPLEMOTIONMODEL_LEVER_RED_ROOT2},
	{"data\\MODEL\\leverroot.x",SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT2,SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT2},
	{"data\\MODEL\\leverred.x",SIMPLEMOTIONMODEL_LEVER_RED_LEVER2,SIMPLEMOTIONMODEL_LEVER_RED_ROOT2},
	{"data\\MODEL\\leverblue.x",SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER2,SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT2},

};

///-------------------------------------------------------------------------���f��
LPD3DXMESH g_pMeshSimpleModel[SIMPLEMOTIONMODEL_MAX] = {};//���b�V��(���_���)�ւ̃|�C���^

LPD3DXBUFFER g_pBuffMatSimpleModel[SIMPLEMOTIONMODEL_MAX] = {};//�}�e���A���ւ̃|�C���^

DWORD dwNumMatSimpleModel[SIMPLEMOTIONMODEL_MAX] = {};//�}�e���A���̐�


//=============================
//�ȈՃ��[�V�������f������������
//=============================
void InitSimpleModel(void)
{
	for (int SimpleModel = 0; SimpleModel < SIMPLEMOTIONMODEL_MAX; SimpleModel++)//�e�p�[�c�{��
	{
		g_ModelInfo[SimpleModel].SinpleModel.bUse = false;
		g_ModelInfo[SimpleModel].SinpleModel.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ModelInfo[SimpleModel].SinpleModel.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}


	g_bKeyspawn = false;
	g_bKeyspawnTtl = false;


	//�������珉���l�Z�b�g
	//SetSimpleModel(SIMPLEMOTIONMODEL_Test1, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//SetSimpleModel(SIMPLEMOTIONMODEL_Test2, D3DXVECTOR3(30.0f, 40.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	//�ԃ��o�[
	SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_RED_ROOT, D3DXVECTOR3(-1180.0f, 100.0f, -1000.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));		//�{��
	SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_RED_LEVER, D3DXVECTOR3(0.0f, 0.0f, 8.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//���o�[
	
	//�`���[�g���A�����o�[��
	SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_RED_ROOT2, D3DXVECTOR3(2700.0f, 100.0f, 2530.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//�{��
	SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_RED_LEVER2, D3DXVECTOR3(0.0f, 0.0f, 8.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//���o�[

	//�`���[�g���A�����o�[��
	SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT2, D3DXVECTOR3(3300.0f, 100.0f, 1070.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));	//�{��
	SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER2, D3DXVECTOR3(0.0f, 0.0f, 8.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//���o�[
	//�`���[�g���A�����o�[�̃A�N�V�����]�[���ݒu
	SetActionZone(D3DXVECTOR3(3300.0f, 100.0f, 1000.0f), LEVER_ACTIONZONE_RADIUS, ACTION_TYPE_LEVER_TUTORIAL2, D3DXCOLOR(1.0f, 0.0f, 0.3f, 0.8f));


	//���o�[1�̃A�N�V�����]�[���ݒu
	SetActionZone(D3DXVECTOR3(-1180.0f, 100.0f, -1000.0f), LEVER_ACTIONZONE_RADIUS, ACTION_TYPE_LEVER_1, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f));
	
	//�`���[�g���A�����o�[�Ԃ̃A�N�V�����]�[���ݒu
	SetActionZone(D3DXVECTOR3(2700.0f, 100.0f, 2530.0f), LEVER_ACTIONZONE_RADIUS, ACTION_TYPE_LEVER_TUTORIAL1, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f));
	
	int fSetRandom = ((float)rand() / RAND_MAX) * (NUM_ROOM - 1); //�n�������������ɕ����Ń����_��

	if (fSetRandom == 0)
	{
		//���o�[
		SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT, D3DXVECTOR3(3553.0f, 100.0f, -130.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));	//�{��
		SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER, D3DXVECTOR3(0.0f, 0.0f, 8.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//���o�[
		//���o�[2�̃A�N�V�����]�[���ݒu
		SetActionZone(D3DXVECTOR3(3553.0f, 100.0f, -126.0f), LEVER_ACTIONZONE_RADIUS, ACTION_TYPE_LEVER_2, D3DXCOLOR(1.0f, 0.0f, 0.3f, 0.8f));
	}
	if (fSetRandom == 1)
	{
		//���o�[
		SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT, D3DXVECTOR3(2928.0f, 200.0f, -2530.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));	//�{��
		SetSimpleModel(SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER, D3DXVECTOR3(0.0f, 0.0f, 8.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//���o�[
		//���o�[2�̃A�N�V�����]�[���ݒu
		SetActionZone(D3DXVECTOR3(2928.0f, 200.0f, -2524.0f), LEVER_ACTIONZONE_RADIUS, ACTION_TYPE_LEVER_2, D3DXCOLOR(1.0f, 0.0f, 0.3f, 0.8f));
	}

}
//=============================
//�ȈՃ��[�V�������f���I������
//=============================
void UninitSimpleModel(void)
{
	for (int SimpleModel = 0; SimpleModel < SIMPLEMOTIONMODEL_MAX; SimpleModel++)
	{
		//���b�V���̔j��
		if (g_pMeshSimpleModel[SimpleModel] != NULL)
		{
			g_pMeshSimpleModel[SimpleModel]->Release();
			g_pMeshSimpleModel[SimpleModel] = NULL;
		}
		//�}�e���A���̔j��
		if (g_pBuffMatSimpleModel[SimpleModel] != NULL)
		{
			g_pBuffMatSimpleModel[SimpleModel]->Release();
			g_pBuffMatSimpleModel[SimpleModel] = NULL;
		}
	}
}
//=============================
//�ȈՃ��[�V�������f���X�V����
//=============================
void UpdateSimpleModel(void)
{
	//*********�����ł��̂ɍ��킹�ď�����ǉ�


	//for (int SimpleModel = 0; SimpleModel < SIMPLEMOTIONMODEL_MAX; SimpleModel++)
	//{

	//}
}
//=============================
//�ȈՃ��[�V�������f���`�揈��
//=============================
void DrawSimpleModel(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxParent;//�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p(�ꎞ�ޔ�)

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^
	
	
	for (int SimpleModel = 0; SimpleModel < SIMPLEMOTIONMODEL_MAX; SimpleModel++)
	{
		if (g_ModelInfo[SimpleModel].SinpleModel.bUse == true)
		{


			//���f���̈ʒu
		//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_ModelInfo[SimpleModel].SinpleModel.mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ModelInfo[SimpleModel].SinpleModel.rot.y, g_ModelInfo[SimpleModel].SinpleModel.rot.x, g_ModelInfo[SimpleModel].SinpleModel.rot.z);

			D3DXMatrixMultiply(&g_ModelInfo[SimpleModel].SinpleModel.mtxWorld, &g_ModelInfo[SimpleModel].SinpleModel.mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_ModelInfo[SimpleModel].SinpleModel.pos.x, g_ModelInfo[SimpleModel].SinpleModel.pos.y, g_ModelInfo[SimpleModel].SinpleModel.pos.z);

			D3DXMatrixMultiply(&g_ModelInfo[SimpleModel].SinpleModel.mtxWorld, &g_ModelInfo[SimpleModel].SinpleModel.mtxWorld, &mtxTrans);

			//�e�q�֌W
			if (g_ModelInfo[SimpleModel].ParentNum == g_ModelInfo[SimpleModel].MyNum)
			{//�������e
				//�v���C���[�Ƃ�����
			//	D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &g_Player.mtxWorld);
			}
			else
			{
				//�����̐e�̃}�g���b�N�X�����Ă�
				D3DXMatrixMultiply(&g_ModelInfo[SimpleModel].SinpleModel.mtxWorld, &g_ModelInfo[SimpleModel].SinpleModel.mtxWorld, &g_ModelInfo[g_ModelInfo[SimpleModel].ParentNum].SinpleModel.mtxWorld);

			}

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_ModelInfo[SimpleModel].SinpleModel.mtxWorld);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatSimpleModel[SimpleModel]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)dwNumMatSimpleModel[SimpleModel]; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);//����͐ݒ肵�Ȃ�

				//���f��(�p�[�c)�̕`��
				g_pMeshSimpleModel[SimpleModel]->DrawSubset(nCntMat);

				//�ۑ����Ă��}�e���A����߂�
		//		pDevice->SetMaterial(&matDef);
			}

			//�ۑ����Ă��}�e���A����߂�
			pDevice->SetMaterial(&matDef);

			//�e�N�X�`����߂�
			pDevice->SetTexture(0, NULL);
		}
	}
}

//=============================
//���o�[ON����
//=============================
void LaverOn(void)
{
	if (g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_RED_LEVER].SinpleModel.rot.x > -1.75f)
	{
		g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_RED_LEVER].SinpleModel.rot.x -= 0.1f;
	}

	if (g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER].SinpleModel.rot.x > -1.75f)
	{
		g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER].SinpleModel.rot.x -= 0.1f;
	}
	if (g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER].SinpleModel.rot.x <= -1.75f
		&& g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_RED_LEVER].SinpleModel.rot.x <= -1.75f
		&& g_bKeyspawn == false)
	{
		g_bKeyspawn = true;
		PlaySound(SOUND_LABEL_SE_LEVER);
		SpawnKey();
	}
}

//=============================
//�`���[�g���A�����o�[ON����
//=============================
void LaverOnTtl(void)
{
	if (g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_RED_LEVER2].SinpleModel.rot.x > -1.75f)
	{
		g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_RED_LEVER2].SinpleModel.rot.x -= 0.1f;
	}

	if (g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER2].SinpleModel.rot.x > -1.75f)
	{
		g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER2].SinpleModel.rot.x -= 0.1f;
	}
	if (g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER2].SinpleModel.rot.x <= -1.75f
		&& g_ModelInfo[SIMPLEMOTIONMODEL_LEVER_RED_LEVER2].SinpleModel.rot.x <= -1.75f
		&& g_bKeyspawnTtl == false)
	{
		g_bKeyspawnTtl = true;
		PlaySound(SOUND_LABEL_SE_LEVER);
		SpawnKeyTtl();
	}
}


//=============================
//�L�[�X�|�[������
//=============================
void SpawnKey(void)
{
	int fRandomSpawn = ((float)rand() / RAND_MAX) * NUM_ROOM;
	if (fRandomSpawn == 0)
	{
		SetModel(LIVING_SPAWN_POS,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_KEY1);

		SetKeyinfo(SPAWNPLACE_LIVING,-1);
	}
	if (fRandomSpawn == 1)
	{
		SetModel(BASEMENT_SPAWN_POS,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_KEY1);

		SetKeyinfo(SPAWNPLACE_BASEMENT,-1);
	}
	if (fRandomSpawn == 2)
	{
		SetModel(BATHROOM_SPAWN_POS,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_KEY1);

		SetKeyinfo(SPAWNPLACE_BATHROOM,-1);
	}
	//SetModel(D3DXVECTOR3(-904.0f,
	//	20.0f,
	//	-1205.0f),
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_KEY1);



	SetModel_Enemy(D3DXVECTOR3(-655.0f,
		0.0f,
		-1141.0f),
		D3DXVECTOR3(0.0f, 3.14f, 0.0f));
}

//=============================
//�`���[�g���A���L�[�X�|�[������
//=============================
void SpawnKeyTtl(void)
{

	//2800,50,2200--3200,50,1900--2800,50,1600
		SetModel(D3DXVECTOR3(2800.0f,50.0f,2200.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_KEY1);
		SetModel(D3DXVECTOR3(3200.0f,50.0f,1900.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_KEY2);
		SetModel(D3DXVECTOR3(2800.0f,50.0f,1600.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_KEY3);

		//SetKeyinfo(SPAWNPLACE_LIVING, -1);
}


//=============================
//�ȈՃ��[�V�������f���ݒ菈��
//=============================
void SetSimpleModel(SIMPLEMOTIONMODEL SetUpName_Index,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//***�e���g�͎����̈ʒu�B�q�̓I�t�Z�b�g�l���L��
	
	if (g_ModelInfo[SetUpName_Index].SinpleModel.bUse == false)
	{
		g_ModelInfo[SetUpName_Index].SinpleModel.bUse = true;
		g_ModelInfo[SetUpName_Index].SinpleModel.pos = pos;
		g_ModelInfo[SetUpName_Index].SinpleModel.rot = rot;


		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(g_ModelInfo[SetUpName_Index].pFilePass,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatSimpleModel[SetUpName_Index],
			NULL,
			&dwNumMatSimpleModel[SetUpName_Index],
			&g_pMeshSimpleModel[SetUpName_Index]);
	}
	else
	{
		//�G���[
	}
}

//=============================
//���X�|�[���������擾
//=============================
bool GetSpawnKey_Lever(void)
{
	return g_bKeyspawn;
}

//=============================
//�`���[�g���A���Ō��X�|�[���������擾
//=============================
bool GetSpawnKey_Leverttl(void)
{
	return g_bKeyspawnTtl;
}