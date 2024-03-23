//==============================
//
// �t�B����������[Film.cpp]
// Author:Kaito Hondo
//
//==============================

#include "main.h"
#include "Film.h"

//�}�N����`
#define TATE_FILM	(100.0)
#define YOKO_FILM	(SCREEN_WIDE + 100.0)

// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureFILM[NUM_FILMTEXTURE] = {};	// �e�N�X�`���i1�����j�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFILM = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
FILM g_aFilm[NUM_FILM];
float g_aPosTexU[NUM_FILM];						// �e�N�X�`�����W�̊J�n�ʒu�iU�l�j
float g_aPosTexV[NUM_FILM];						// �e�N�X�`�����W�̊J�n�ʒu�iV�l�j
float g_fLengthFilm;	//�Ίp���̒���
float g_fAngleFilm;	//�Ίp���̊p�x


//==============================================================
// �w�i�̏���������
//==============================================================
void InitFILM(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntFILM;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, FILM_TEXTURE4, &g_apTextureFILM[0]);


	//�Ίp���̒������Z�o
	g_fLengthFilm = sqrtf(YOKO_FILM * YOKO_FILM + TATE_FILM * TATE_FILM) * 0.5f;

	//�Ίp���̊p�x���Z�o
	g_fAngleFilm = atan2f(YOKO_FILM, TATE_FILM);


	// �e�N�X�`�����W�̊J�n�ʒu�iV�l�j�̏�����
	for (nCntFILM = 0; nCntFILM < NUM_FILM; nCntFILM++)
	{
		g_aPosTexV[nCntFILM] = 0.0f;
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_FILM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffFILM, NULL);

	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���l��
	g_pVtxBuffFILM->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFILM = 0; nCntFILM < NUM_FILM; nCntFILM++)
	{
		g_aFilm[nCntFILM].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFilm[nCntFILM].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFilm[nCntFILM].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFilm[nCntFILM].texX = 0.0f;
		g_aFilm[nCntFILM].bUse = false;


		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDE, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDE, SCREEN_HEIGHT, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;// ���_�f�[�^�̃|�C���^���S���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFILM->Unlock();

	SetFILM(D3DXVECTOR3(SCREEN_WIDE * 0.8, SCREEN_HEIGHT * 0.2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, (D3DX_PI * -0.25)), -0.001f);
	SetFILM(D3DXVECTOR3(SCREEN_WIDE * 0.9, SCREEN_HEIGHT * 0.2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, (D3DX_PI * +0.40)), -0.001f);
	SetFILM(D3DXVECTOR3(SCREEN_WIDE * 0.1, SCREEN_HEIGHT * 0.9, 0.0f), D3DXVECTOR3(0.0f, 0.0f, (D3DX_PI * -0.25)), +0.001f);

}

//==============================================================
// �w�i�̏I������
//==============================================================
void UninitFILM(void)
{
	int nCount;

	// �e�N�X�`���̔j��
	for (nCount = 0; nCount < NUM_FILMTEXTURE; nCount++)
	{
		if (g_apTextureFILM[nCount] != NULL)
		{
			g_apTextureFILM[nCount]->Release();
			g_apTextureFILM[nCount] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffFILM != NULL)
	{
		g_pVtxBuffFILM->Release();
		g_pVtxBuffFILM = NULL;
	}
}

//==============================================================
// �w�i�̍X�V����
//==============================================================
void UpdateFILM(void)
{
	int nCntFILM;
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFILM->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFILM = 0; nCntFILM < NUM_FILM; nCntFILM++)
	{
		g_aPosTexU[nCntFILM] += g_aFilm[nCntFILM].texX;

		pVtx[0].pos.x = g_aFilm[nCntFILM].pos.x + sinf(g_aFilm[nCntFILM].rot.z - (D3DX_PI - g_fAngleFilm)) * g_fLengthFilm;
		pVtx[0].pos.y = g_aFilm[nCntFILM].pos.y + cosf(g_aFilm[nCntFILM].rot.z - (D3DX_PI - g_fAngleFilm)) * g_fLengthFilm;
		pVtx[1].pos.x = g_aFilm[nCntFILM].pos.x + sinf(g_aFilm[nCntFILM].rot.z + (D3DX_PI - g_fAngleFilm)) * g_fLengthFilm;
		pVtx[1].pos.y = g_aFilm[nCntFILM].pos.y + cosf(g_aFilm[nCntFILM].rot.z + (D3DX_PI - g_fAngleFilm)) * g_fLengthFilm;
		pVtx[2].pos.x = g_aFilm[nCntFILM].pos.x + sinf(g_aFilm[nCntFILM].rot.z - g_fAngleFilm) * g_fLengthFilm;
		pVtx[2].pos.y = g_aFilm[nCntFILM].pos.y + cosf(g_aFilm[nCntFILM].rot.z - g_fAngleFilm) * g_fLengthFilm;
		pVtx[3].pos.x = g_aFilm[nCntFILM].pos.x + sinf(g_aFilm[nCntFILM].rot.z + g_fAngleFilm) * g_fLengthFilm;
		pVtx[3].pos.y = g_aFilm[nCntFILM].pos.y + cosf(g_aFilm[nCntFILM].rot.z + g_fAngleFilm) * g_fLengthFilm;


		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntFILM], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntFILM] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntFILM], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntFILM] + 1.0f, 1.0f);

		g_aFilm[nCntFILM].pos += g_aFilm[nCntFILM].move;

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffFILM->Unlock();
}

//==============================================================
// �w�i�̕`�揈��
//==============================================================
void DrawFILM(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntFILM;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFILM, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntFILM = 0; nCntFILM < NUM_FILM; nCntFILM++)
	{
		if (g_aFilm[nCntFILM].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureFILM[0]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntFILM * 4,
				2);
		}
	}
}

//=======================================
//�t�B�����̐ݒ菈��
//=======================================
void SetFILM(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float texX)
{
	VERTEX_3D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFILM->Lock(0, 0, (void**)&pVtx, 0);

	for (int nFilm = 0; nFilm < NUM_FILM; nFilm++)
	{
		if (g_aFilm[nFilm].bUse == false)
		{
			g_aFilm[nFilm].pos = pos;	//�ʒu
			g_aFilm[nFilm].rot = rot;	//����
			g_aFilm[nFilm].texX = texX;
			g_aFilm[nFilm].bUse = true;
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffFILM->Unlock();
}
