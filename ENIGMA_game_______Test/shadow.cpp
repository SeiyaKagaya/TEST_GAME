//=========================================================
//
//polygon��\�����鏈��[shadow.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "shadow.h"
#include "player.h"
#include <stdio.h>

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL; //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;       //�e�N�X�`���ւ̃|�C���^

//D3DXVECTOR3 g_Shadow[nCnt].pos;	//�ʒu
//D3DXVECTOR3 g_Shadow[nCnt].rot;	//����
//D3DXMATRIX g_Shadow[nCnt].mtxWorld;//���[���h�}�g���b�N�X


Shadow g_Shadow[MAX_SHADOW];


//=============================
//�e�̏���������
//=============================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\shadow000.jpg", &g_pTextureShadow);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffShadow, NULL);
	
	VERTEX_3D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	
	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{

		g_Shadow[nCnt].pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//�ʒu
		g_Shadow[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����

		//g_Shadow[nCnt].mtxWorld= D3DXMATRIX(0.0f,0.0f,0.0f);//���[���h�}�g���b�N�X
		g_Shadow[nCnt].bUse = false;

		g_Shadow[nCnt].ShadowSize = SHADOWSIZE_PLAYER;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W��ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��


		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffShadow->Unlock();
}
//=============================
//�e�̏I������
//=============================
void UninitShadow(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}
//=============================
//�e�̍X�V����
//=============================
void UpdateShadow(void)
{
	float nPosSize=0.0f;

	VERTEX_3D* pVtx;//���_���ւ̃|�C���^

//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
    	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{

		if (g_Shadow[nCnt].ShadowSize == SHADOWSIZE_PLAYER)
		{
			nPosSize = SHADOW_SIZE_PLAYER;
		}
		else if (g_Shadow[nCnt].ShadowSize == SHADOWSIZE_ITEM)
		{
			nPosSize = SHADOW_SIZE_BULLET;
		}
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-nPosSize, 0.0f, nPosSize);
		pVtx[1].pos = D3DXVECTOR3(nPosSize, 0.0f, nPosSize);
		pVtx[2].pos = D3DXVECTOR3(-nPosSize, 0.0f, -nPosSize);
		pVtx[3].pos = D3DXVECTOR3(nPosSize, 0.0f, -nPosSize);


		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffShadow->Unlock();

}
//=============================
//�e�̕`�揈��
//=============================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_Shadow[nCnt].bUse == true)
		{
			//���C�g�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			////Z�̔�r�ύX
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			////Z�o�b�t�@�ɏ������܂Ȃ�
			//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Shadow[nCnt].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCnt].rot.y, g_Shadow[nCnt].rot.x, g_Shadow[nCnt].rot.z);

			D3DXMatrixMultiply(&g_Shadow[nCnt].mtxWorld, &g_Shadow[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCnt].pos.x, g_Shadow[nCnt].pos.y, g_Shadow[nCnt].pos.z);

			D3DXMatrixMultiply(&g_Shadow[nCnt].mtxWorld, &g_Shadow[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCnt].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�

			pDevice->SetTexture(0, g_pTextureShadow);

			//�e�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				nCnt * 4,//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);//�`�悷��v���~�e�B�u��

				//�A���t�@�u�����f�B���O�����Ƃɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

						//���C�g��L���ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			////Z�̔�r�ύX
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			////Z�o�b�t�@�ɏ������܂Ȃ�
			//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

			//�e�N�X�`����߂�
			pDevice->SetTexture(0, NULL);
		}
	}


}
//=============================
//�e�̐ݒ菈��
//=============================
int SetShadow(void)
{
	int nCntShadow = -1;

	VERTEX_3D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_Shadow[nCnt].bUse == false)
		{
			g_Shadow[nCnt].bUse = true;
			nCntShadow = nCnt;
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffShadow->Unlock();

	return nCntShadow;
}
//=============================
//�e�̈ʒu�ݒ菈��
//=============================
void SetPositionShadow(int nldShadow, D3DXVECTOR3 pos, SHADOWSIZE ShadowSize)
{
	//�w�肵���e�̈ʒu��ݒ�
	g_Shadow[nldShadow].pos = pos;
	g_Shadow[nldShadow].pos.y += 1.0f;
	g_Shadow[nldShadow].ShadowSize = ShadowSize;

}
//=============================
//�e�̌l�̏I������
//=============================
void EndProcessShadow(int nldShadow)
{
	g_Shadow[nldShadow].bUse = false;
}