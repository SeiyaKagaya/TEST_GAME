//==================================================
//
//�t�F�[�h�Ɋւ��鏈��[fade.cpp]
// Author seiya kagaya
//
//==================================================
#include "main.h"
#include "fade.h"
//#include "sound.h"

//�O���[�o���ϐ��錾
FADE g_fade;
D3DXCOLOR g_colorfade;
MODE g_ModeNext;
//LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;       //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL; //���_�o�b�t�@�ւ̃|�C���^

int g_fadeCnt = 0;//�Q�[����ʂւ̈ڍs���������ɐF���c�����΍�

//=============================
//�t�F�[�h�̏���������
//=============================
void InitFade(MODE mode_next)
{
	LPDIRECT3DDEVICE9 pDevice;  //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	//�ϐ��̏�����
	g_colorfade.a = 1.0f;

	g_fade = FADE_IN;
	
	g_fadeCnt = 0;

	VERTEX_2D* pVtx;  //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDE, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDE, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffFade->Unlock();
}
//=============================
//�t�F�[�h�̏I������
//=============================
void UninitFade(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}
//=============================
//�t�F�[�h�̍X�V����
//=============================
void UpdateFade(void)
{
	VERTEX_2D* pVtx;  //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//�t�F�[�h�C�����

			g_colorfade.a -= 0.05f;	//�|���S���𓧖��ɂ��Ă���

			if (g_colorfade.a <= 0.0f)
			{
				g_colorfade.a = 0.0f;

				g_fade = FADE_NONE;	//�������Ă��Ȃ����
			}
		}
		else if (g_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			g_colorfade.a += 0.1f;	//�|���S����s�����ɂ��Ă���

			if (g_colorfade.a >= 1.2f)
			{
				g_colorfade.a = 1.2f;

				g_fadeCnt++;//���[�h�ڍs�J�E���^�[

				g_fade = FADE_IN;	//�t�F�[�h�C�����
			}

			if (g_fadeCnt == 1)
			{//�F�������c���������
				//���[�h�ݒ�(���̉�ʂɈڍs)
				Setmode(g_ModeNext);
				g_fadeCnt = 0;
			}
		}

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDE, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDE, SCREEN_HEIGHT, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorfade.a);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorfade.a);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorfade.a);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorfade.a);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffFade->Unlock();
}
//=============================
//�t�F�[�h�̕`�揈��
//=============================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

//	if (g_fade != FADE_NONE)
//	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
//	}
}
//=============================
//�t�F�[�h�̐ݒ菈��
//=============================
void SetFade(MODE mode_next)
{
	if (g_fade == FADE_NONE)
	{
		g_colorfade.a = 0.0f;
		g_fadeCnt = 0;
		g_colorfade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);			//�����|���S��(����)�ɂ��Ă���
		g_fade = FADE_OUT;											//�t�F�[�h�A�E�g��Ԃ�
		g_ModeNext = mode_next;										//���̉��(���[�h)��ݒ�

	}
}
//=============================
//�t�F�[�h�̎擾����
//=============================
FADE GetFade(void)
{
	return g_fade;
}
