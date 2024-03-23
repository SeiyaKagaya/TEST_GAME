//=============================================
//
//�}�b�v�G�f�B�^�[[Model.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "model.h"
#include "input.h"
#include "camera.h"
#include "TV.h"
//#include "field.h"
#include "shadow.h"
#include "bathgimmick.h"
#include "Actionzone.h"
#include "particle.h"

//=============================================
//�}�N����`
//=============================================
#define DAMPING_COEFFICIENT	(0.2f) //��R��
#define MAX_MODEL	(256) //���f���̍ő吔 
#define MODEL_SHADOW_RADIUS	(40.0f)
#define BATH_ACTIONZONE_RADIUS	(120.0f)	//�����C�̃M�~�b�N����
#define KEYPARTICLERADIUS		(100.0f)	//���ɕt������p�[�e�B�N���̔��a

//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DTEXTURE9 g_apTextureModel[NUM_MODEL][NUM_TEXTURE] = {}; //�e�N�X�`���|�C���^
MAPOBJECT g_aModel[MAX_MODEL];

//=============================================
//���f���̎��
//=============================================
static const char* MODEL_NAME[NUM_MODEL] =
{
	"data\\MODEL\\bath.x",
	"data\\MODEL\\cactus.x",
	"data\\MODEL\\cardboard.x",
	"data\\MODEL\\Cupboard.x",
	"data\\MODEL\\desk.x",
	"data\\MODEL\\door.x",
	"data\\MODEL\\flower pot.x",
	"data\\MODEL\\garage.x",
	"data\\MODEL\\key1.x",
	"data\\MODEL\\key2.x",
	"data\\MODEL\\key3.x",
	"data\\MODEL\\kitchen.x",
	"data\\MODEL\\metalshelf.x",
	"data\\MODEL\\microwaveoven.x",
	"data\\MODEL\\pot.x",
	"data\\MODEL\\refrigerator.x",
	"data\\MODEL\\slidedoor.x",
	"data\\MODEL\\sofa.x",
	"data\\MODEL\\stairs.x",
	"data\\MODEL\\swollencactus.x",
	"data\\MODEL\\toilet.x",
	"data\\MODEL\\TV.x",
	"data\\MODEL\\TVstand.x",
	"data\\MODEL\\Washbasin.x",
	"data\\MODEL\\cube.x",
	"data\\MODEL\\safe.x",
	"data\\MODEL\\escapedoor.x",
	"data\\MODEL\\Button.x",

};

//=============================================
//�|���S���̏���������
//=============================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntType = 0; nCntType < NUM_MODEL; nCntType++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(MODEL_NAME[nCntType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aModel[nCntType].pBuffMat,
			NULL,
			&g_aModel[nCntType].nNumMat,
			&g_aModel[nCntType].pMesh);

		D3DXMATERIAL* pMat; //�}�e���A���|�C���^
		pMat = (D3DXMATERIAL*)g_aModel[nCntType].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntType].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_apTextureModel[nCntType][nCntMat]
				);
			}
		}
	}

//	int nNumVtx; //���_��
//	DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
//	BYTE* pVtxBuff; //���_�o�b�t�@�̃|�C���^

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{

		g_aModel[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //���f���̏����ʒu
		g_aModel[nCnt].Minpos = D3DXVECTOR3(100000.0f, 1000000.0f, 1000000.0f); //���f���̍ŏ��ʒu
		g_aModel[nCnt].Maxpos = D3DXVECTOR3(-10000.0f, -1000000.0f, -100000.0f); //���f���̍ő�ʒu
		g_aModel[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̕���
		g_aModel[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̈ړ����x
		g_aModel[nCnt].nShadow = -1;
		g_aModel[nCnt].nType = MODELTYPE_BATH;
		g_aModel[nCnt].bUse = false;
		g_aModel[nCnt].bCollision = false;



		//------------------------------------------------------------------------------------------����_��
	////	���_���̎擾
	//	nNumVtx = g_aModel[g_aModel[nCnt].nType].pMesh->GetNumVertices();
	////	���_�t�H�[�}�b�g�̃T�C�Y���擾
	//	sizeFVF = D3DXGetFVFVertexSize(g_aModel[g_aModel[nCnt].nType].pMesh->GetFVF());

	//	//���_�o�b�t�@�̃��b�N
	//	g_aModel[g_aModel[nCnt].nType].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	//	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	//	{
	//		//���_���W�̑��
	//		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

	//		if (vtx.x > g_aModel[nCnt].Maxpos.x)
	//		{
	//			g_aModel[nCnt].Maxpos.x = vtx.x;
	//		}
	//		if (vtx.x < g_aModel[nCnt].Minpos.x)
	//		{
	//			g_aModel[nCnt].Minpos.x = vtx.x;
	//		}

	//		if (vtx.y > g_aModel[nCnt].Maxpos.y)
	//		{
	//			g_aModel[nCnt].Maxpos.y = vtx.y;
	//		}
	//		if (vtx.y < g_aModel[nCnt].Minpos.y)
	//		{
	//			g_aModel[nCnt].Minpos.y = vtx.y;
	//		}

	//		if (vtx.z > g_aModel[nCnt].Maxpos.z)
	//		{
	//			g_aModel[nCnt].Maxpos.z = vtx.z;
	//		}
	//		if (vtx.z < g_aModel[nCnt].Minpos.z)
	//		{
	//			g_aModel[nCnt].Minpos.z = vtx.z;
	//		}

	//		// ���̒��_�ɐi��
	//		pVtxBuff += sizeFVF;

	//	}

	//	g_aModel[g_aModel[nCnt].nType].pMesh->UnlockVertexBuffer();



	}
}

//=============================================
//�|���S���̏I������
//=============================================
void UninitModel(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		//		if (g_aModel[nCnt].bUse == true)
		//		{
					//���b�V���̔j��
		if (g_aModel[nCnt].pMesh != NULL)
		{
			g_aModel[nCnt].pMesh->Release();
			g_aModel[nCnt].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_aModel[nCnt].pBuffMat != NULL)
		{
			g_aModel[nCnt].pBuffMat->Release();
			g_aModel[nCnt].pBuffMat = NULL;
		}

		for (int nCntTex = 0; nCntTex < (int)g_aModel[nCnt].nNumMat; nCntTex++)
		{
			// �e�N�X�`���̔j��
			if (g_apTextureModel[nCnt][nCntTex] != NULL)
			{
				g_apTextureModel[nCnt][nCntTex]->Release();
				g_apTextureModel[nCnt][nCntTex] = NULL; // ������ NULL ��ݒ�
			}
		}
		//		}
	}
}

//=============================================
//�|���S���̍X�V����
//=============================================
void UpdateModel(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == true)
		{
			if (g_aModel[nCnt].nType == MODELTYPE_KEY1)
			{
				SetParticle(g_aModel[nCnt].pos, KEYPARTICLERADIUS, 12, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.04f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_KEY2)
			{
				SetParticle(g_aModel[nCnt].pos, KEYPARTICLERADIUS, 12, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.04f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_KEY3)
			{
				SetParticle(g_aModel[nCnt].pos, KEYPARTICLERADIUS, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.04f));
			}

		}
	}
	
}

//=============================================
//�|���S���̕`�揈��
//=============================================
void DrawModel(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DMATERIAL9 matDef; //���݂̃}�e���A���̕ۑ�
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	//���݂��擾
	pDevice->GetMaterial(&matDef);

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == true)
		{
			//�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aModel[nCnt].mtxWorld);

			//���e�X�g��L��
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCnt].rot.y, g_aModel[nCnt].rot.x, g_aModel[nCnt].rot.z);

			D3DXMatrixMultiply(&g_aModel[nCnt].mtxWorld, &g_aModel[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCnt].pos.x, g_aModel[nCnt].pos.y, g_aModel[nCnt].pos.z);

			D3DXMatrixMultiply(&g_aModel[nCnt].mtxWorld, &g_aModel[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCnt].mtxWorld);

			D3DXMATERIAL* pMat; //�}�e���A��

			pMat = (D3DXMATERIAL*)g_aModel[g_aModel[nCnt].nType].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aModel[g_aModel[nCnt].nType].nNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureModel[g_aModel[nCnt].nType][nCntMat]);

				//�p�[�c�̐ݒ�
				g_aModel[g_aModel[nCnt].nType].pMesh->DrawSubset(nCntMat);
			}
			//���e�X�g�𖳌���
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

			//�ۑ����Ă��}�e���A����߂�
			pDevice->SetMaterial(&matDef);

			//�e�N�X�`����߂�
			pDevice->SetTexture(0, NULL);
		}
	}
}

//=============================================
//�|���S���̐ݒ�
//=============================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ModelType nType)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == false)
		{
			g_aModel[nCnt].pos = pos;
			g_aModel[nCnt].rot = rot;
			g_aModel[nCnt].nType = nType;


			if (g_aModel[nCnt].nType == MODELTYPE_BATH)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS, ACTION_TYPE_BATH, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_DESK)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS, ACTION_TYPE_DESK, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.7f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_KEY1)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS + 20.0f, ACTION_TYPE_KEY_1, D3DXCOLOR(0.5f, 0.5f, 0.0f, 0.7f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_KEY2)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS + 20.0f, ACTION_TYPE_KEY_2, D3DXCOLOR(0.5f, 1.0f, 1.0f, 0.7f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_KEY3)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS + 20.0f, ACTION_TYPE_KEY_3, D3DXCOLOR(1.0f, 0.5f, 1.0f, 0.7f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_KITCHEN)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS, ACTION_TYPE_KITCHEN, D3DXCOLOR(0.5f, 0.6f, 1.0f, 0.7f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_TV)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS, ACTION_TYPE_TV, D3DXCOLOR(0.0f, 0.5f, 0.0f, 0.7f));
				SetTVVision(D3DXVECTOR3(g_aModel[nCnt].pos.x - 17.0f, g_aModel[nCnt].pos.y + 28.0f, g_aModel[nCnt].pos.z)
					, g_aModel[nCnt].rot
					, TVVISION_WIDE
					, TVVISION_HEIGHT);
			}
            if (g_aModel[nCnt].nType == MODELTYPE_SAFE)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS, ACTION_TYPE_MONEYBOX, D3DXCOLOR(0.0f, 0.5f, 0.0f, 0.7f));
			}
			if (g_aModel[nCnt].nType == MODELTYPE_CUPBOARD)
			{
				SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS, ACTION_TYPE_CUPBOARD, D3DXCOLOR(0.0f, 0.5f, 0.0f, 0.7f));
			}

			/*if (g_aModel[nCnt].nType == MODELTYPE_BUTTON)
			{
				g_aModel[nCnt].bCollision = false;
			}*/
			//SetActionZone(g_aModel[nCnt].pos, BATH_ACTIONZONE_RADIUS, ACTION_TYPE_MAX, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f));



			g_aModel[nCnt].Minpos = D3DXVECTOR3(100000.0f, 1000000.0f, 100000.0f); //���f���̍ŏ��ʒu
			g_aModel[nCnt].Maxpos = D3DXVECTOR3(-10000.0f, -1000000.0f, -100000.0f); //���f���̍ő�ʒu

			int nNumVtx; //���_��
			DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
			BYTE* pVtxBuff; //���_�o�b�t�@�̃|�C���^

			//���_���̎擾
			nNumVtx = g_aModel[g_aModel[nCnt].nType].pMesh->GetNumVertices();
			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_aModel[g_aModel[nCnt].nType].pMesh->GetFVF());

			//���_�o�b�t�@�̃��b�N
			g_aModel[g_aModel[nCnt].nType].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				//���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				// ���W�ϊ��s����쐬
				D3DXMATRIXA16 matRotation;
				D3DXMatrixRotationYawPitchRoll(&matRotation, rot.y, rot.x, rot.z);

				// ���_���W����]
				D3DXVec3TransformCoord(&vtx, &vtx, &matRotation);

				if (vtx.x > g_aModel[nCnt].Maxpos.x)
				{
					g_aModel[nCnt].Maxpos.x = vtx.x;
				}
				if (vtx.x < g_aModel[nCnt].Minpos.x)
				{
					g_aModel[nCnt].Minpos.x = vtx.x;
				}

				if (vtx.y > g_aModel[nCnt].Maxpos.y)
				{
					g_aModel[nCnt].Maxpos.y = vtx.y;
				}
				if (vtx.y < g_aModel[nCnt].Minpos.y)
				{
					g_aModel[nCnt].Minpos.y = vtx.y;
				}

				if (vtx.z > g_aModel[nCnt].Maxpos.z)
				{
					g_aModel[nCnt].Maxpos.z = vtx.z;
				}
				if (vtx.z < g_aModel[nCnt].Minpos.z)
				{
					g_aModel[nCnt].Minpos.z = vtx.z;
				}

				// ���̒��_�ɐi��
				pVtxBuff += sizeFVF;
			}

			g_aModel[g_aModel[nCnt].nType].pMesh->UnlockVertexBuffer();

			g_aModel[nCnt].bUse = true;

			if (g_aModel[nCnt].nType == MODELTYPE_KEY1
				|| g_aModel[nCnt].nType == MODELTYPE_KEY2
				|| g_aModel[nCnt].nType == MODELTYPE_KEY3)
			{//���̂ݓ����蔻��폜
				g_aModel[nCnt].bCollision = false;
			}
			else
			{
				g_aModel[nCnt].bCollision = true;
			}
			break;
		}
	}
}
//=============================================
//���擾
//=============================================
void GetKey(ModelType nType)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == true && g_aModel[nCnt].nType == nType)
		{
			g_aModel[nCnt].bUse = false;
		}
	}
}
//=============================================
//�|���S���̏��擾
//=============================================
MAPOBJECT* GetMapObject(void)
{
	return &g_aModel[0];
}

//=============================================
//�����蔻�菜�O����
//=============================================
void ExclusionCollision(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == true)
		{
			if (g_aModel[nCnt].nType== MODELTYPE_STAIRS)
			{
				g_aModel[nCnt].bCollision = false;
			}
			if (g_aModel[nCnt].nType == MODELTYPE_BUTTON)
			{
				g_aModel[nCnt].bCollision = false;
			}
		}
	}



	//�����ŋL�ڂ��ꂽ���͓̂����蔻������O�����
	for (int nCnt = 2; nCnt < 23; nCnt++)
	{
		g_aModel[nCnt].bCollision = false;
	}
	for (int nCnt = 35; nCnt < 54; nCnt++)
	{
		g_aModel[nCnt].bCollision = false;
	}

	////�ǂꂩ�𓖂��蔻��h�������Ăł�������ɂ���------------------------------
	////12--�_���{�[���P
	g_aModel[11].Minpos = D3DXVECTOR3(-211.0f, 0.0f, -31.0f);
	g_aModel[11].Maxpos = D3DXVECTOR3(211.0f, 153.0f, 31.0f);
	g_aModel[11].bCollision = true;
	////38--�_���{�[��2
	g_aModel[37].Minpos = D3DXVECTOR3(-31.0f, 0.0f, -90.0f);
	g_aModel[37].Maxpos = D3DXVECTOR3(31.0f, 153.0f, 90.0f);

	g_aModel[37].bCollision = true;
	//47--�_���{�[��3
	g_aModel[46].Minpos = D3DXVECTOR3(-31.0f, 0.0f, -90.0f);
	g_aModel[46].Maxpos = D3DXVECTOR3(31.0f, 153.0f, 90.0f);
	g_aModel[46].bCollision = true;
	//36--�V���b�^�[
	g_aModel[35].Minpos = D3DXVECTOR3(-280.0f, 0.0f, -45.0f);
	g_aModel[35].Maxpos = D3DXVECTOR3(280.0f, 410.0f, -35.0f);
	g_aModel[35].bCollision = true;
}