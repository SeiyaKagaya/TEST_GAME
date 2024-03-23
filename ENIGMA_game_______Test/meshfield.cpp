//=========================================================
//
//�n�ʂ�\�����鏈��[meshfield.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "meshfield.h"
//#include "field.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL; //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;       //�e�N�X�`���ւ̃|�C���^

//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^------------------------------------------------------NEW
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;

D3DXVECTOR3 g_posMeshField;	//�ʒu
D3DXVECTOR3 g_rotMeshField;	//����

D3DXMATRIX g_mtxWorldMeshField;//���[���h�}�g���b�N�X

//D3DXVECTOR3 pos;


#define POSSIZE		(100.0f)//�{�̂̃T�C�Y///--------------------��ɓ������

#define MESH_CELL_NUM_X	(201)//���̃Z����(�Z����)
#define MESH_CELL_NUM_Z	(201)//���̃Z����(�Z����)


#define NUMVERTEX	((MESH_CELL_NUM_X + 1) * (MESH_CELL_NUM_Z + 1))//���_��

// �O�p�`�X�g���b�v�ł̕`���O��Ƃ��邽�߁A�C���f�b�N�X���ƃ|���S�����̌v�Z

#define NUMINDEX (2 * (MESH_CELL_NUM_X + 1) * MESH_CELL_NUM_Z + (MESH_CELL_NUM_Z - 1)) // �C���f�b�N�X��

// �k�ރ|���S���p���_���܂񂾃C���f�b�N�X��
#define NUMINDEX_WITH_DEGENERATE (NUMINDEX + 2 * (MESH_CELL_NUM_Z - 1))

// �|���S����(�v���~�e�B�u��)
#define NUMPOLYGON (MESH_CELL_NUM_X * MESH_CELL_NUM_Z * 2) // �|���S����

// �k�ރ|���S���̐����܂񂾃|���S����
#define NUMPOLYGON_WITH_DEGENERATE (NUMPOLYGON + MESH_CELL_NUM_Z - 1)


D3DXVECTOR3 EscapePvtxNor[NUMVERTEX] = {};//�@���ۑ���
//D3DXVECTOR3 EscapePvtxPos2[NUMVERTEX] = {};


int g_MaXpIdx = 0;//���鏇�Ԃ̍ő吔

//=============================
//�n�ʂ̏���������
//=============================
void InitMeshField(void)
{
	for (int i=0; i < NUMVERTEX; i++)
	{
		EscapePvtxNor[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}



	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\map001.jpg", &g_pTextureMeshField);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * NUMVERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMeshField, NULL);


	//�C���f�b�N�X�o�b�t�@�̐���//------------------------------------------------------------------------------------------------------------NEW
	pDevice->CreateIndexBuffer(sizeof(WORD) * NUMINDEX_WITH_DEGENERATE,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	g_posMeshField = D3DXVECTOR3(0.0f, -0.5f, 0.0f);	//�ʒu
	g_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����


	VERTEX_3D* pVtx;//���_���ւ̃|�C���^

	


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�֌W//----------------------------------------------------NEW
	WORD* pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIndex = 0; nCntIndex < NUMVERTEX; nCntIndex++)
	{
		pVtx[nCntIndex].pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	}

	int nIndexNUM = 0;

	for (int nCnt2 = 0; nCnt2 < (MESH_CELL_NUM_Z); nCnt2++)
	{//Z����

		for (int nCnt = 0 ; nCnt < MESH_CELL_NUM_X + 1; nCnt++)
		{//X����
			pIdx[nIndexNUM] = nCnt + ((nCnt2 + 1) * (MESH_CELL_NUM_X + 1));
			nIndexNUM++;
			pIdx[nIndexNUM] = nCnt + (nCnt2 * (MESH_CELL_NUM_X + 1));
			nIndexNUM++;
		}


		if (nCnt2 != (MESH_CELL_NUM_Z - 1))//�k�ރ|���S��
		{//�ŏI�s����Ȃ��Ƃ�(����O����Ȃ�)
			//�k�ރ|���S��
			pIdx[nIndexNUM] = (nCnt2* (MESH_CELL_NUM_X+1)) + MESH_CELL_NUM_X;//�k�މE��
			nIndexNUM++;

			pIdx[nIndexNUM] = (nCnt2 * (MESH_CELL_NUM_X + 1)) + ((MESH_CELL_NUM_X+1)*2);//�k��
			nIndexNUM++;
		}
		
	}

	g_MaXpIdx = nIndexNUM;


	// ���_���W�̐ݒ�---------------------------------------------------------------------------OK
	for (int nCntZ = 0; nCntZ <= MESH_CELL_NUM_Z; nCntZ++)//�cZ
	{
		for (int nCntX = 0; nCntX <= MESH_CELL_NUM_X; nCntX++)//��X
		{
			int nIndex = nCntZ * (MESH_CELL_NUM_X + 1) + nCntX; // ���_�̃C���f�b�N�X

			pVtx[nIndex].pos.x = g_posMeshField.x + (nCntX - MESH_CELL_NUM_X / 2.0f) * POSSIZE;

			if (nIndex % 4 == 0)
			{//���፷
				pVtx[nIndex].pos.y = g_posMeshField.y+ DIFF_IN_HEIGHT;

				//��X������
				pVtx[nIndex].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			}
			else
			{
				pVtx[nIndex].pos.y = g_posMeshField.y;
				//��X������
				pVtx[nIndex].nor = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
			}

			pVtx[nIndex].pos.z = g_posMeshField.z - (nCntZ - MESH_CELL_NUM_Z / 2.0f) * POSSIZE;



			//��X������
		//	pVtx[nIndex].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			pVtx[nIndex].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}





	//�@��
//	CalculateNormals();



//	���b�V���t�B�[���h�̖@���B�������܂��s�����Ƃ肠�������ڒl�����č��፷�����F�ł���悤�ɂ���

	


	// �e�N�X�`�����W�̐ݒ�//------------------------------------------------------------------------OK
	for (int nCntZ = 0; nCntZ <= MESH_CELL_NUM_Z; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= MESH_CELL_NUM_X; nCntX++)
		{
			int vtxIndex = nCntZ * (MESH_CELL_NUM_X + 1) + nCntX; // ���_�̃C���f�b�N�X

		// �ȉ��̍s��ύX
			pVtx[vtxIndex].tex.x = static_cast<float>(nCntX) / MESH_CELL_NUM_X;
			pVtx[vtxIndex].tex.y = static_cast<float>(nCntZ) / MESH_CELL_NUM_Z;
		}
	}

	//����Ȃ��|�����\��....
	int nIndexNUM4 = 0;
	for (int nCnt2 = 0; nCnt2 < (MESH_CELL_NUM_Z); nCnt2++)
	{//Z����

		if (nCnt2 != (MESH_CELL_NUM_Z - 1))//�k�ރ|���S��
		{//�ŏI�s����Ȃ��Ƃ�(����O����Ȃ�)

		 //�k�ރ|���S��
			//pIdx[nIndexNUM4] = (nCnt2 * (MESH_CELL_NUM_X + 1)) + MESH_CELL_NUM_X;//�k�މE��

			pVtx[nIndexNUM4].tex.x = 0.0f;
			pVtx[nIndexNUM4].tex.y = 0.0f;
			nIndexNUM4++;

			//pIdx[nIndexNUM4] = (nCnt2 * (MESH_CELL_NUM_X + 1)) + ((MESH_CELL_NUM_X + 1) * 2);//�k��
			pVtx[nIndexNUM4].tex.x = 0.0f;
			pVtx[nIndexNUM4].tex.y = 0.0f;
			nIndexNUM4++;
		}

	}




	g_pIdxBuffMeshField->Unlock();

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshField->Unlock();

}
//=============================
//�n�ʂ̏I������
//=============================
void UninitMeshField(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̊J��//--------------------New
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}
}
//=============================
//�n�ʂ̍X�V����
//=============================
void UpdateMeshField(void)
{
	//�����Ȃ�
}
//=============================
//�n�ʂ̕`�揈��
//=============================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�//--------------------------------------New
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);



	////�|���S���̕`��
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, NUMVERTEX, 0, NUMINDEX);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, NUMVERTEX, 0, NUMINDEX_WITH_DEGENERATE);

	//�n�ʂ̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
	//	0,//�`�悷��ŏ��̒��_�C���f�b�N�X
	//	2);//�`�悷��v���~�e�B�u��

	
	//�e�N�X�`����߂�
	pDevice->SetTexture(0, NULL);
}

//=============================
//�@���̌v�Z����
//=============================
void CalculateNormals(void)
{
	//���ꂪ��Ԗ��邭�Ȃ�@��
	//pVtx[nCntIndex2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���b�V���t�B�[���h�̖@���쐬�菇

	//�@
	//----���b�V�����\�����邷�ׂẴ|���S��(*�k�ރ|���S���͏���)�ɑ΂���
	//----1.�@�O�ρA���K�����s���ʖ@���x�N�g�����쐬
	//----2.�@1.�̖@���x�N�g�����|���S�����\������3�̒��_�����ɔz��ɕێ�----(�ێ���)EscapePvtxNor[nCnt];

	//�A
	//----���b�V�����\�����邷�ׂĂ̒��_�ɑ΂��Ĉȉ������s
	//----1.�@�@�ŕێ��������ׂĂ̖ʖ@���x�N�g�������Z
	//----2.�@1.�̃x�N�g���𐳋K��
 //----3.�@���_�f�[�^�̖@���x�N�g��(pVtx[nCnt].nor)�ɁA2.�̃x�N�g����ݒ�

	VERTEX_3D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�֌W//----------------------------------------------------NEW
	WORD* pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);


	//�e���_�@���v�Z
	
	//int EscapeCnt = 0;
	//���ʃx�N�g��
	////for (int nCntIndex = 0; nCntIndex < NUMVERTEX; nCntIndex ++)
	////{
	////	//�@���v�Z����

	////	D3DXVECTOR3 EscapeVtxPos1 = pVtx[pIdx[nCntIndex]].pos - pVtx[pIdx[nCntIndex + 1]].pos;
	////	D3DXVECTOR3 EscapeVtxPos2 = pVtx[pIdx[nCntIndex + 2]].pos - pVtx[pIdx[nCntIndex + 1]].pos;

	////	D3DXVECTOR3 EscapeNOR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	D3DXVec3Cross(&EscapeNOR, &EscapeVtxPos1, &EscapeVtxPos2);

	////	D3DXVECTOR3 NOR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	D3DXVec3Normalize(&NOR, &EscapeNOR);

	////	//�S���_
	////	EscapePvtxNor[nCntIndex] = NOR;//-------------------------------���_�̐����O�p������̂ŏ��Ԃǂ���ێ�--1//���_�@��--pIdx�̏��鏇��
	////	//EscapeCnt++;
	////}

	//////int EscapeCnt2 = 0;
	////for (int nCntIndex2 = 0; nCntIndex2 < NUMVERTEX; nCntIndex2++)
	////{
	////	D3DXVECTOR3 EscapeNOR = (EscapePvtxNor[pIdx[nCntIndex2]] + EscapePvtxNor[pIdx[nCntIndex2 + 1]] + EscapePvtxNor[pIdx[nCntIndex2 + 2]]);

	////	D3DXVECTOR3 NOR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);



	////	int nCntIndex3 = 0;
	////	for (pIdx[nCntIndex3] = 0; nCntIndex3 < g_MaXpIdx; nCntIndex3++)
	////	{
	////		if (pVtx[pIdx[nCntIndex2 + 1]].pos == pVtx[pIdx[nCntIndex3]].pos)
	////		{
	////			if (pIdx[nCntIndex2 + 1] != pIdx[nCntIndex3])
	////			{//�������g����Ȃ���
	////				if (pIdx[nCntIndex2 + 1] > pIdx[nCntIndex3])
	////				{//�������g����Ȃ���
	////					EscapeNOR += pVtx[pIdx[nCntIndex3]].pos;
	////				}
	////			}

	////		}


	////	}


	////	D3DXVec3Normalize(&NOR, &EscapeNOR);




	////	//�S���_
	////	EscapePvtxNor[nCntIndex2] = NOR;//-------------------------------���_�̐����O�p������̂ŏ��Ԃǂ���ێ�--2--�Čv�Z��e���_�@��
	////	//EscapeCnt2++;

	////	pVtx[nCntIndex2].nor = NOR;
	////}






	
	for (int nCntIndex = 0; nCntIndex < NUMVERTEX - 2; nCntIndex++)
	{

		if (nCntIndex % (MESH_CELL_NUM_Z - 1) == 1)//�k�ރ|���S��--�@���v�Z���Ȃ�
		{//�ŏI�s����Ȃ��Ƃ�(����O����Ȃ�)

		}
		else
		{//�@���v�Z����

			D3DXVECTOR3 EscapeVtxPos1 = pVtx[nCntIndex + 1].pos - pVtx[nCntIndex].pos;
			D3DXVECTOR3 EscapeVtxPos2 = pVtx[nCntIndex + 2].pos - pVtx[nCntIndex].pos;

			D3DXVECTOR3 EscapeNOR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


			D3DXVec3Cross(&EscapeNOR, &EscapeVtxPos1, &EscapeVtxPos2);

			D3DXVECTOR3 NOR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			D3DXVec3Normalize(&NOR, &EscapeNOR);

			EscapePvtxNor[nCntIndex] = NOR;//-------------------------------���_�̐����O�p������̂ŏ��Ԃǂ���ێ�--1//���ʖ@��

		}
	}
	 
	
	//�e���_�@���v�Z
	for (int nCntIndex = 0; nCntIndex < NUMVERTEX - 2; nCntIndex++)
	{
		D3DXVECTOR3 EscapeNOR = (EscapePvtxNor[nCntIndex] + EscapePvtxNor[nCntIndex + 1] + EscapePvtxNor[nCntIndex + 2]);
		D3DXVECTOR3 NOR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		D3DXVec3Normalize(&NOR, &EscapeNOR);

		int test;
		test = 2;

		EscapePvtxNor[nCntIndex] = NOR;//-------------------------------���_�̐����O�p������̂ŏ��Ԃǂ���ێ�--2--�Čv�Z��e���_�@��
	}

	for (int nCntIndex = 0; nCntIndex < NUMVERTEX - 2; nCntIndex++)
	{
		pVtx[nCntIndex].nor = EscapePvtxNor[nCntIndex];//-------------------------------���_�̐����O�p������̂ŏ��Ԃǂ���ێ�--2--�Čv�Z��e���_�@��

	}


	g_pIdxBuffMeshField->Unlock();

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshField->Unlock();
}