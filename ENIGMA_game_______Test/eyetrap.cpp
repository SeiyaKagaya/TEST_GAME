//=============================================
//
//�����C�̃M�~�b�N[eyetrap.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "eyetrap.h"
#include "sound.h"

//=============================================
//�ǂ̃e�N�X�`���̎��
//=============================================
static const char* EyeTrap_TEX_NAME =
{
	"data\\TEXTURE\\trap000.png",
};

//=========================================================
//�O���[�o���ϐ�
//=========================================================
LPDIRECT3DTEXTURE9 g_pTextureEyeEyeTrap = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEyeEyeTrap = NULL;//���_�o�b�t�@�ւ̃|���S��
EyeTrap g_EyeTrap[NUM_TRAP];	//�|�[�Y�\���̂̏��

//=============================================
//�g���b�v�̏�����
//=============================================
void InitEyeTrap(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//	int nCntPause = 0;

		//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		EyeTrap_TEX_NAME,
		&g_pTextureEyeEyeTrap
	);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TRAP, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffEyeEyeTrap, NULL);

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEyeEyeTrap->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntTrap = 0; nCntTrap < NUM_TRAP; nCntTrap++)
	{
		g_EyeTrap[nCntTrap].bUse = false;
		if (nCntTrap == 0)
		{
			g_EyeTrap[nCntTrap].fAlpha = INIT_A_VALUE;
			g_EyeTrap[nCntTrap].nBlindCnt = 0;
			g_EyeTrap[nCntTrap].pos = D3DXVECTOR3(SCREEN_WIDE / 4.0f, SCREEN_HEIGHT / 3.0f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_EyeTrap[nCntTrap].pos.x - SCREEN_WIDE / 4.0f, g_EyeTrap[nCntTrap].pos.y - SCREEN_HEIGHT / 3.5f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_EyeTrap[nCntTrap].pos.x + SCREEN_WIDE / 4.0f, g_EyeTrap[nCntTrap].pos.y - SCREEN_HEIGHT / 3.5f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_EyeTrap[nCntTrap].pos.x - SCREEN_WIDE / 4.0f, g_EyeTrap[nCntTrap].pos.y + SCREEN_HEIGHT / 3.5f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_EyeTrap[nCntTrap].pos.x + SCREEN_WIDE / 4.0f, g_EyeTrap[nCntTrap].pos.y + SCREEN_HEIGHT / 3.5f, 0.0f);
		}
		else if (nCntTrap == 1)
		{
			g_EyeTrap[nCntTrap].fAlpha = INIT_A_VALUE;
			g_EyeTrap[nCntTrap].nBlindCnt = 0;
			g_EyeTrap[nCntTrap].pos = D3DXVECTOR3(SCREEN_WIDE / 1.35f, SCREEN_HEIGHT / 3.0f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_EyeTrap[nCntTrap].pos.x - SCREEN_WIDE / 4.0f, g_EyeTrap[nCntTrap].pos.y - SCREEN_HEIGHT / 3.5f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_EyeTrap[nCntTrap].pos.x + SCREEN_WIDE / 4.0f, g_EyeTrap[nCntTrap].pos.y - SCREEN_HEIGHT / 3.5f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_EyeTrap[nCntTrap].pos.x - SCREEN_WIDE / 4.0f, g_EyeTrap[nCntTrap].pos.y + SCREEN_HEIGHT / 3.5f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_EyeTrap[nCntTrap].pos.x + SCREEN_WIDE / 4.0f, g_EyeTrap[nCntTrap].pos.y + SCREEN_HEIGHT / 3.5f, 0.0f);
		}
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nCntTrap].fAlpha);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nCntTrap].fAlpha);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nCntTrap].fAlpha);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nCntTrap].fAlpha);

		//�e�L�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	g_pVtxBuffEyeEyeTrap->Unlock();
}

//=============================================
//�g���b�v�̏I��
//=============================================
void UninitEyeTrap(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEyeEyeTrap != NULL)
	{
		g_pTextureEyeEyeTrap->Release();
		g_pTextureEyeEyeTrap = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEyeEyeTrap != NULL)
	{
		g_pVtxBuffEyeEyeTrap->Release();
		g_pVtxBuffEyeEyeTrap = NULL;
	}

}

//=============================================
//�g���b�v�̍X�V
//=============================================
void UpdateEyeTrap(void)
{
	for (int nCnt = 0; nCnt < NUM_TRAP; nCnt++)
	{
		if (g_EyeTrap[nCnt].bUse == true)
		{
			g_EyeTrap[nCnt].nBlindCnt++;
			if (g_EyeTrap[nCnt].nBlindCnt >= BLIND_TIME)
			{
				VERTEX_2D* pVtx;//���_���̃|�C���^

				//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				g_pVtxBuffEyeEyeTrap->Lock(0, 0, (void**)&pVtx, 0);

				g_EyeTrap[nCnt].fAlpha -= 0.1f;
				int nVtx = nCnt * 4;
				//���_�J���[�̐ݒ�
				pVtx[nVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nCnt].fAlpha);
				pVtx[nVtx + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nCnt].fAlpha);
				pVtx[nVtx + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nCnt].fAlpha);
				pVtx[nVtx + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nCnt].fAlpha);

				if (g_EyeTrap[nCnt].fAlpha <= 0.0f)
				{
					g_EyeTrap[nCnt].fAlpha = 0.0f;
					g_EyeTrap[nCnt].nBlindCnt = 0;
					g_EyeTrap[nCnt].bUse = false;
				}
			}

		}
	}
	g_pVtxBuffEyeEyeTrap->Unlock();

}

//=============================================
//�g���b�v�̕`��
//=============================================
void DrawEyeTrap(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

//�f�o�C�X�̎擾
	pDevice = GetDevice();//----------------���������ς�

	for (int nCntTrap = 0; nCntTrap < NUM_TRAP; nCntTrap++)
	{
		if (g_EyeTrap[nCntTrap].bUse == true)
		{
			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEyeEyeTrap, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);//-------���������ς�

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEyeEyeTrap);//---------���������ς�

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��//----------���������ς�
				4*nCntTrap,//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);//�`�悷��v���~�e�B�u��
			
			//�e�N�X�`����߂�
			pDevice->SetTexture(0, NULL);
		}
	}
}

//=============================================
//�g���b�v�̐ݒ�
//=============================================
void SetEyeTrap(int nPlayer)
{
	if (g_EyeTrap[nPlayer].bUse == false)
	{
		PlaySound(SOUND_LABEL_SE_EYETRAP);
		g_EyeTrap[nPlayer].nBlindCnt = 0;
		g_EyeTrap[nPlayer].bUse = true;
		g_EyeTrap[nPlayer].fAlpha = INIT_A_VALUE;
		int nVtx = nPlayer * 4;
		VERTEX_2D* pVtx;//���_���̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffEyeEyeTrap->Lock(0, 0, (void**)&pVtx, 0);
		//���_�J���[�̐ݒ�
		pVtx[nVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nPlayer].fAlpha);
		pVtx[nVtx + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nPlayer].fAlpha);
		pVtx[nVtx + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nPlayer].fAlpha);
		pVtx[nVtx + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_EyeTrap[nPlayer].fAlpha);
		g_pVtxBuffEyeEyeTrap->Unlock();

	}
}

//=============================================
//�g���b�v�̎擾
//=============================================
EyeTrap* GetEyeTrap(void)
{
	return &g_EyeTrap[0];
}
