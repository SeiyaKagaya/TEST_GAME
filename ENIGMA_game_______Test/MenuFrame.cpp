//==============================
//
// ���j���[[MenuFrame.cpp]
// Author:Kaito Hondo
//
//==============================

#include "main.h"
#include "MenuFrame.h"
#include "menu.h"
#include "Film.h"
#include "corkboard.h"
#include "Icon.h"

// �}�N����`
#define NUM_MENUFRAME	(1)// �w�i�̐�

// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureMenuFrame[NUM_MENUFRAME] = {};	// �e�N�X�`���i1�����j�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMenuFrame = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

// �w�i�̏���������
void InitMenuFrame(void)
{
	// �w�i�̏���������
	InitFILM();

	InitIcon();

	InitMenu();

	InitCorkboard();


	LPDIRECT3DDEVICE9 pDevice;
	int nCntMenuFrame;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MenuFrame_TEXTURE, &g_apTextureMenuFrame[0]);


	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_MENUFRAME, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMenuFrame, NULL);

	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���l��
	g_pVtxBuffMenuFrame->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMenuFrame = 0; nCntMenuFrame < NUM_MENUFRAME; nCntMenuFrame++)
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
	g_pVtxBuffMenuFrame->Unlock();
}

// �w�i�̏I������
void UninitMenuFrame(void)
{
	// �w�i�̏I������
	UninitFILM();

	UninitIcon();

	UninitMenu();

	UninitCorkboard();


	int nCount;

	// �e�N�X�`���̔j��
	for (nCount = 0; nCount < NUM_MENUFRAME; nCount++)
	{

		if (g_apTextureMenuFrame[nCount] != NULL)
		{
			g_apTextureMenuFrame[nCount]->Release();
			g_apTextureMenuFrame[nCount] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffMenuFrame != NULL)
	{
		g_pVtxBuffMenuFrame->Release();
		g_pVtxBuffMenuFrame = NULL;
	}
}

// �w�i�̍X�V����
void UpdateMenuFrame(void)
{
	UpdateFILM();

	UpdateIcon();

	UpdateMenu();

	UpdateCorkboard();

}

// �w�i�̕`�揈��
void DrawMenuFrame(void)
{

	LPDIRECT3DDEVICE9 pDevice;
	int nCntMenuFrame;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMenuFrame, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntMenuFrame = 0; nCntMenuFrame < NUM_MENUFRAME; nCntMenuFrame++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureMenuFrame[nCntMenuFrame]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntMenuFrame * 4,
			2);

	}

	// �w�i�̕`�揈��
	DrawFILM();

	DrawIcon();

	DrawMenu();

	DrawCorkboard();

}