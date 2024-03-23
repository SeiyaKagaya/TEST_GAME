//=============================================
//
//�����C�̃M�~�b�N[steam.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "steam.h"
#include "bathgimmick.h"

//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSteam = NULL;
LPDIRECT3DTEXTURE9 g_pTextureSteam = NULL; //�e�N�X�`���|�C���^
D3DXMATRIX	g_mtxWorldSteam;
Steam g_aSteam[MAX_STEAM];

void InitSteam(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Steam.png",
		&g_pTextureSteam
	);

	for (int nCnt = 0; nCnt < MAX_STEAM; nCnt++)
	{
		g_aSteam[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�v���C���[�̏����ʒu
		g_aSteam[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //���[�u�l
		g_aSteam[nCnt].nLife = STEAM_LIFE; //���C�t
		g_aSteam[nCnt].bUse = false;
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_STEAM, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffSteam, NULL);

	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffSteam->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_STEAM; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aSteam[nCnt].pos.x - STEAM_WIDE, g_aSteam[nCnt].pos.y + STEAM_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aSteam[nCnt].pos.x + STEAM_WIDE, g_aSteam[nCnt].pos.y + STEAM_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aSteam[nCnt].pos.x - STEAM_WIDE, g_aSteam[nCnt].pos.y - STEAM_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aSteam[nCnt].pos.x + STEAM_WIDE, g_aSteam[nCnt].pos.y - STEAM_HEIGHT, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);

		//�e�N�X�`���̍��W�w��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	g_pVtxBuffSteam->Unlock();
}

void UninitSteam(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSteam != NULL)
	{
		g_pTextureSteam->Release();
		g_pTextureSteam = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSteam != NULL)
	{
		g_pVtxBuffSteam->Release();
		g_pVtxBuffSteam = NULL;
	}
}

void UpdateSteam(void)
{
	//�f�o�C�X�̎擾
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_STEAM; nCnt++)
	{
		if (g_aSteam[nCnt].bUse == true)
		{
			g_aSteam[nCnt].pos += g_aSteam[nCnt].move;

			g_aSteam[nCnt].nLife--;

			if (g_aSteam[nCnt].nLife <= 0)
			{
				g_aSteam[nCnt].bUse = false;
			}

		}
	}
}

void DrawSteam(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxTrans; //�v�Z�p�}�g���b�N�X

	D3DXMATRIX mtxView; //�r���[�}�g���b�N�X�擾�p

	for (int nCnt = 0; nCnt < MAX_STEAM; nCnt++)
	{
		if (g_aSteam[nCnt].bUse == true)
		{
			//z�̔�r���@�ύX
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			//z�o�b�t�@�ɏ������܂Ȃ�
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			//���e�X�g��L��
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			//�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldSteam);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S���̐��ʂ��J�����Ɍ�����
			D3DXMatrixInverse(&g_mtxWorldSteam, NULL, &mtxView);

			g_mtxWorldSteam._41 = 0.0f;
			g_mtxWorldSteam._42 = 0.0f;
			g_mtxWorldSteam._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aSteam[nCnt].pos.x, g_aSteam[nCnt].pos.y, g_aSteam[nCnt].pos.z);

			D3DXMatrixMultiply(&g_mtxWorldSteam, &g_mtxWorldSteam, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldSteam);

			//���u�����f�B���O�����Z�����ɐݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffSteam, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSteam);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);

			//���e�X�g�𖳌���
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

			//z�̔�r���@�ύX
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			//z�o�b�t�@�ɏ������܂Ȃ�
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

			//���u�����f�B���O�����ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			
			//�e�N�X�`����߂�
			pDevice->SetTexture(0, NULL);
		}
	}
}

void SetSteam(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col)
{
	//�f�o�C�X�̎擾
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffSteam->Lock(0, 0, (void**)&pVtx, 0);

	float fVertex;

	fVertex = (float)(rand() % 629 - 314) / 60.0f;

	for (int nCnt = 0; nCnt < MAX_STEAM; nCnt++)
	{
		if (g_aSteam[nCnt].bUse == false)
		{
			g_aSteam[nCnt].pos = pos;
			g_aSteam[nCnt].nLife = STEAM_LIFE; //���C�t
			g_aSteam[nCnt].move.x = sinf(fVertex) * (STEAM_SPEED / 3.0f);
			g_aSteam[nCnt].move.z = cosf(fVertex) * (STEAM_SPEED / 3.0f);
			g_aSteam[nCnt].move.y = STEAM_SPEED;

			int nVtx = nCnt * 4; //���_���W�̎w��
			//���_�J���[�̐ݒ�
			pVtx[nVtx].col = col;
			pVtx[nVtx + 1].col = col;
			pVtx[nVtx + 2].col = col;
			pVtx[nVtx + 3].col = col;

			//g_aSteam[nCnt].move.x = sinf(fVertex) * fMove;
			//g_aSteam[nCnt].move.y = cosf(fVertex) * fMove;
			g_aSteam[nCnt].bUse = true;

			break; //for�𔲂���
		}
	}
	g_pVtxBuffSteam->Unlock();

}

void OffSteam(void)
{
	for (int nCnt = 0; nCnt < MAX_STEAM; nCnt++)
	{
		if (g_aSteam[nCnt].bUse == true)
		{
			g_aSteam[nCnt].bUse = false;
		}
	}
}
