//=========================================================
//
//�A�C�e����\�����鏈��[billboard.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "Billboard.h"
//#include "sound.h"
#include "input.h"
#include "game.h"

//�}�N����`
#define MAXSIZE	(15.0f)	//�r���{�[�h�T�C�Y

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBill = NULL; //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureBill[BILLTYPE_MAX] = {};       //�e�N�X�`���ւ̃|�C���^
BILL g_aBill[NUMBILL];

//=============================
//�A�C�e���̏���������
//=============================
void InitBill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_dish.png", &g_apTextureBill[0]);		//�M
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_remocon.png", &g_apTextureBill[1]);	//�����R��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_vegetable.png", &g_apTextureBill[2]);//���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_soup.png", &g_apTextureBill[3]);		//�X�[�v

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * NUMBILL, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBill, NULL);

	VERTEX_3D* pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBill->Lock(0, 0, (void**)&pVtx, 0);

	for (int nBill = 0; nBill < NUMBILL; nBill++)
	{
		g_aBill[nBill].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_aBill[nBill].nType = BILLTYPE_DISH;
		g_aBill[nBill].bUse = false;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-MAXSIZE, MAXSIZE * 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(MAXSIZE, MAXSIZE * 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-MAXSIZE, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(MAXSIZE, 0, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBuffBill->Unlock();

}
//=============================
//�A�C�e���̏I������
//=============================
void UninitBill(void)
{
	//StopSound(SOUND_LABEL_SE_SHOT);
	//StopSound(SOUND_LABEL_SE_EXPLOSIONBOMB);
	//�e�N�X�`���̔j��
	for (int i = 0; i < BILLTYPE_MAX; i++)
	{
		if (g_apTextureBill[i] != NULL)
		{
			g_apTextureBill[i]->Release();
			g_apTextureBill[i] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBill != NULL)
	{
		g_pVtxBuffBill->Release();
		g_pVtxBuffBill = NULL;
	}
}
//=============================
//�A�C�e���̍X�V����
//=============================
void UpdateBill(void)
{
	//VERTEX_3D* pVtx;//���_���ւ̃|�C���^

	////���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//g_pVtxBuffBill->Lock(0, 0, (void**)&pVtx, 0);

	//for (int nBill = 0; nBill < NUMBILL; nBill++)
	//{

	//	pVtx += 4;
	//}
	////���_�o�b�t�@�̃A�����b�N
	//g_pVtxBuffBill->Unlock();

}
//=============================
//�A�C�e���̕`�揈��
//=============================
void DrawBill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX  mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;//�r���[�}�g���b�N�X�̎擾

	for (int nBill = 0; nBill < NUMBILL; nBill++)
	{
		if (g_aBill[nBill].bUse == true)
		{
			//���C�g�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			////Z�̔�r�ύX
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			////Z�o�b�t�@�ɏ������܂Ȃ�
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBill[nBill].mtxWorldBill);

			//�����𔽉f
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBill[nBill].rotItem.y, g_aBill[nBill].rotItem.x, g_aBill[nBill].rotItem.z);

			//D3DXMatrixMultiply(&g_aBill[nBill].mtxWorldBill, &g_aBill[nBill].mtxWorldBill, &mtxRot);

					//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBill[nBill].pos.x, g_aBill[nBill].pos.y, g_aBill[nBill].pos.z);

			D3DXMatrixMultiply(&g_aBill[nBill].mtxWorldBill, &g_aBill[nBill].mtxWorldBill, &mtxTrans);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_aBill[nBill].mtxWorldBill, NULL, &mtxView);//�t�s�S�����߂�

			g_aBill[nBill].mtxWorldBill._41 = 0.0f;
			g_aBill[nBill].mtxWorldBill._42 = 0.0f;
			g_aBill[nBill].mtxWorldBill._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBill[nBill].pos.x, g_aBill[nBill].pos.y, g_aBill[nBill].pos.z);

			D3DXMatrixMultiply(&g_aBill[nBill].mtxWorldBill, &g_aBill[nBill].mtxWorldBill, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBill[nBill].mtxWorldBill);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBill, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);


			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureBill[g_aBill[nBill].nType]);

			////�A���t�@�u�����f�B���O�����Z�����ɐݒ�
			//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


			//�A�C�e���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				nBill * 4,//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);//�`�悷��v���~�e�B�u��


			////�A���t�@�u�����f�B���O�����Ƃɖ߂�
			//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


			//���C�g��L���ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			////Z�̔�r�ύX
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			////Z�o�b�t�@�ɏ������܂Ȃ�
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);


			//�e�N�X�`����߂�
			pDevice->SetTexture(0, NULL);
		}
	}
}

//=============================
//�A�C�e���̐ݒ菈��
//=============================
void SetBill(D3DXVECTOR3 Pos, int nType)
{
	VERTEX_3D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBill->Lock(0, 0, (void**)&pVtx, 0);

	for (int nBill = 0; nBill < NUMBILL; nBill++)
	{
		if (g_aBill[nBill].bUse == false)
		{
			g_aBill[nBill].pos = Pos;//�ʒu
			g_aBill[nBill].nType = nType;
			g_aBill[nBill].bUse = true;
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBill->Unlock();
}