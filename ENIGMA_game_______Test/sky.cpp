//=========================================================
//
//�n�ʂ�\�����鏈��[sky.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "sky.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSky = NULL; //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureSky = NULL;       //�e�N�X�`���ւ̃|�C���^

//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^------------------------------------------------------NEW
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSky = NULL;

D3DXVECTOR3 g_posSky;	//�ʒu
D3DXVECTOR3 g_rotSky;	//����

D3DXMATRIX g_mtxWorldSky;//���[���h�}�g���b�N�X

//D3DXVECTOR3 pos;


#define POSSIZE		(2000.0f)//�{�̂̃T�C�Y///--------------------��ɓ������

#define SKY_CELL_NUM_X	(16)//���̃Z����(�Z����)
#define SKY_CELL_NUM_Y	(6)//���̃Z����(�Z����)


#define NUMVERTEX	((SKY_CELL_NUM_X + 1) * (SKY_CELL_NUM_Y + 1))//���_��

// �O�p�`�X�g���b�v�ł̕`���O��Ƃ��邽�߁A�C���f�b�N�X���ƃ|���S�����̌v�Z

#define NUMINDEX (2 * (SKY_CELL_NUM_X + 1) * SKY_CELL_NUM_Y + (SKY_CELL_NUM_Y - 1)) // �C���f�b�N�X��

// �k�ރ|���S���p���_���܂񂾃C���f�b�N�X��
#define NUMINDEX_WITH_DEGENERATE (NUMINDEX + 2 * (SKY_CELL_NUM_Y - 1))

// �|���S����(�v���~�e�B�u��)
#define NUMPOLYGON (SKY_CELL_NUM_X * SKY_CELL_NUM_Y * 2) // �|���S����

// �k�ރ|���S���̐����܂񂾃|���S����
#define NUMPOLYGON_WITH_DEGENERATE (NUMPOLYGON + SKY_CELL_NUM_Y - 1)


//���a
#define RADIUS	(2100.0f)//���X�{���オ��

//=============================
//�n�ʂ̏���������
//=============================
void InitSky(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sky000.jpg", &g_pTextureSky);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * NUMVERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffSky, NULL);


	//�C���f�b�N�X�o�b�t�@�̐���//------------------------------------------------------------------------------------------------------------NEW
	pDevice->CreateIndexBuffer(sizeof(WORD) * NUMINDEX_WITH_DEGENERATE,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSky,
		NULL);

	g_posSky = D3DXVECTOR3(0.0f, RADIUS*1.1f, -100.0f);	//�ʒu
	g_rotSky = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����


	VERTEX_3D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSky->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�֌W//----------------------------------------------------NEW
	WORD* pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffSky->Lock(0, 0, (void**)&pIdx, 0);

	int nIndexNUM = 0;

	for (int nCnt2 = 0; nCnt2 < (SKY_CELL_NUM_Y); nCnt2++)
	{//Z����

		for (int nCnt = 0; nCnt < SKY_CELL_NUM_X + 1; nCnt++)
		{//X����
			pIdx[nIndexNUM] = nCnt + ((nCnt2 + 1) * (SKY_CELL_NUM_X + 1));
			nIndexNUM++;
			pIdx[nIndexNUM] = nCnt + (nCnt2 * (SKY_CELL_NUM_X + 1));
			nIndexNUM++;
		}


		if (nCnt2 != (SKY_CELL_NUM_Y - 1))
		{//�ŏI�s����Ȃ��Ƃ�(����O����Ȃ�)
			//�k�ރ|���S��
			pIdx[nIndexNUM] = (nCnt2 * (SKY_CELL_NUM_X + 1)) + SKY_CELL_NUM_X;//�k�މE��
			nIndexNUM++;

			pIdx[nIndexNUM] = (nCnt2 * (SKY_CELL_NUM_X + 1)) + ((SKY_CELL_NUM_X + 1) * 2);//�k��
			nIndexNUM++;
		}

	}


	//int test = pIdx[0];//�m�F�p
	//int test2 = pIdx[1];
	//int test3 = pIdx[2];
	//int test4 = pIdx[3];
	//int test5 = pIdx[4];
	//int test6 = pIdx[5];
	//int test7 = pIdx[6];
	//int test8 = pIdx[7];
	//int test9 = pIdx[8];
	//int test10 = pIdx[9];
	//int test11 = pIdx[10];
	//int test12 = pIdx[11];
	//int test13 = pIdx[12];
	//int test14 = pIdx[13];

	//int test15 = pIdx[14];
	//int test16 = pIdx[15];
	//int test17 = pIdx[16];
	//int test18 = pIdx[17];

	//int test19 = pIdx[18];
	//int test20 = pIdx[19];

	//int test21 = pIdx[20];
	//int test22 = pIdx[21];

	//int test23 = pIdx[22];
	//int test24 = pIdx[23];

		//--���Œ��l//-------------------------------------
	//pIdx[0] = 3;
	//pIdx[1] = 0;
	//pIdx[2] = 4;
	//pIdx[3] = 1;
	//pIdx[4] = 5;
	//pIdx[5] = 2;
	//pIdx[6] = 2;//�ܕԂ����k�ރ|���S��
	//pIdx[7] = 6;//�����Ȃ��O�p�`�G���A
	//pIdx[8] = 6;//
	//pIdx[9] = 3;
	//pIdx[10] = 7;
	//pIdx[11] = 4;
	//pIdx[12] = 8;
	//pIdx[13] = 5;



	// ���_���W�̐ݒ�---------------------------------------------------------------------------OK
	for (int nCntY = 0; nCntY <= SKY_CELL_NUM_Y; nCntY++)//�c
	{
		for (int nCntX = 0; nCntX <= SKY_CELL_NUM_X; nCntX++)//��
		{
			int nIndex = nCntY * (SKY_CELL_NUM_X + 1) + nCntX; // ���_�̃C���f�b�N�X


			pVtx[nIndex].pos.x = g_posSky.x + (sinf((0.1252 * nCntX) * D3DX_PI) * (RADIUS * nCntY));

			pVtx[nIndex].pos.z = g_posSky.z + (cosf((0.1252f * nCntX) * D3DX_PI) * (RADIUS * nCntY));

			pVtx[nIndex].pos.y = g_posSky.y - (nCntY - SKY_CELL_NUM_Y / 2.0f) * POSSIZE;






			pVtx[nIndex].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[nIndex].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}











	// �e�N�X�`�����W�̐ݒ�//------------------------------------------------------------------------OK
	for (int nCntY = 0; nCntY <= SKY_CELL_NUM_Y; nCntY++)
	{
		for (int nCntX = 0; nCntX <= SKY_CELL_NUM_X; nCntX++)
		{
			int vtxIndex = nCntY * (SKY_CELL_NUM_X + 1) + nCntX; // ���_�̃C���f�b�N�X

		// �ȉ��̍s��ύX
			pVtx[vtxIndex].tex.x = static_cast<float>(nCntX) / SKY_CELL_NUM_X;
			pVtx[vtxIndex].tex.y = static_cast<float>(nCntY) / SKY_CELL_NUM_Y;
		}
	}



	//----------------------------------------------------------------------------------------------------------------------------



	//// ���_���W�̐ݒ�
	//for (int nCntY = 0; nCntY <= SKY_CELL_NUM_Y; nCntY++)
	//{
	//	for (int nCntX = 0; nCntX <= SKY_CELL_NUM_X; nCntX++)
	//	{
	//		int nIndex = nCntY * (SKY_CELL_NUM_X + 1) + nCntX; // ���_�̃C���f�b�N�X

	//		pVtx[nIndex].pos.x = g_posSky.x + (nCntX - SKY_CELL_NUM_X / 2.0f) * POSSIZE;//OK
	//		pVtx[nIndex].pos.y = g_posSky.y;
	//		pVtx[nIndex].pos.z = g_posSky.z - (nCntY - SKY_CELL_NUM_Y / 2.0f) * POSSIZE;


	//		pVtx[nIndex].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//		pVtx[nIndex].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	}
	//}

	////�e�N�X�`�����W��ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����--
	//pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��--

	//pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);//����--
	//pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	//pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);//�E��--

	//pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);//����--
	//pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);//����--
	//pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��--



	////--���Œ��l
	//pIdx[0] = 3;
	//pIdx[1] = 0;
	//pIdx[2] = 4;
	//pIdx[3] = 1;
	//pIdx[4] = 5;
	//pIdx[5] = 2;
	//pIdx[6] = 2;//�ܕԂ����k�ރ|���S��
	//pIdx[7] = 6;//�����Ȃ��O�p�`�G���A
	//pIdx[8] = 6;//
	//pIdx[9] = 3;
	//pIdx[10] = 7;
	//pIdx[11] = 4;
	//pIdx[12] = 8;
	//pIdx[13] = 5;




	g_pIdxBuffSky->Unlock();

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffSky->Unlock();
}
//=============================
//�n�ʂ̏I������
//=============================
void UninitSky(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSky != NULL)
	{
		g_pTextureSky->Release();
		g_pTextureSky = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̊J��//--------------------New
	if (g_pIdxBuffSky != NULL)
	{
		g_pIdxBuffSky->Release();
		g_pIdxBuffSky = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSky != NULL)
	{
		g_pVtxBuffSky->Release();
		g_pVtxBuffSky = NULL;
	}
}
//=============================
//�n�ʂ̍X�V����
//=============================
void UpdateSky(void)
{
	//�����Ȃ�
	g_rotSky.y += 0.0001f;

	if (g_rotSky.y > 3.14f)
	{
		g_rotSky.y = -3.14f;
	}
	else if (g_rotSky.y < -3.14f)
	{
		g_rotSky.y = 3.14f;
	}


}
//=============================
//�n�ʂ̕`�揈��
//=============================
void DrawSky(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldSky);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotSky.y, g_rotSky.x, g_rotSky.z);

	D3DXMatrixMultiply(&g_mtxWorldSky, &g_mtxWorldSky, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posSky.x, g_posSky.y, g_posSky.z);

	D3DXMatrixMultiply(&g_mtxWorldSky, &g_mtxWorldSky, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldSky);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSky, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�//--------------------------------------New
	pDevice->SetIndices(g_pIdxBuffSky);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureSky);



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