//==============================
//
// ���j���[�̃R���N�{�[�h[corkboard.cpp]
// Author:Kaito Hondo
//
//==============================

#include "main.h"
#include "corkboard.h"


// �}�N����`
#define NUM_CORKBOARD	(1)// �w�i�̐�

// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureCorkboard[NUM_CORKBOARD] = {};	// �e�N�X�`���i�R�����j�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCorkboard = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

// �w�i�̏���������
void InitCorkboard(void)
{

	LPDIRECT3DDEVICE9 pDevice;
	int nCntCorkboard;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, Corkboard_TEXTURE, &g_apTextureCorkboard[0]);


	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_CORKBOARD, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffCorkboard, NULL);

	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���l��
	g_pVtxBuffCorkboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCorkboard = 0; nCntCorkboard < NUM_CORKBOARD; nCntCorkboard++)
	{
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

		//�e�L�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;// ���_�f�[�^�̃|�C���^���S���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCorkboard->Unlock();
}

// �w�i�̏I������
void UninitCorkboard(void)
{
	int nCount;

	// �e�N�X�`���̔j��
	for (nCount = 0; nCount < NUM_CORKBOARD; nCount++)
	{

		if (g_apTextureCorkboard[nCount] != NULL)
		{
			g_apTextureCorkboard[nCount]->Release();
			g_apTextureCorkboard[nCount] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffCorkboard != NULL)
	{
		g_pVtxBuffCorkboard->Release();
		g_pVtxBuffCorkboard = NULL;
	}
}

// �w�i�̍X�V����
void UpdateCorkboard(void)
{

}

// �w�i�̕`�揈��
void DrawCorkboard(void)
{

	LPDIRECT3DDEVICE9 pDevice;
	int nCntCorkboard;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCorkboard, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntCorkboard = 0; nCntCorkboard < NUM_CORKBOARD; nCntCorkboard++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureCorkboard[nCntCorkboard]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntCorkboard * 4, 2);

	}
}