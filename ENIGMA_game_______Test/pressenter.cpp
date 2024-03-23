//============================================================================================
//
//enter�\�����鏈��[pressenter.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "main.h"
#include "pressenter.h"
#include "input.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePressEnter = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPressEnter = NULL;//���_�o�b�t�@�ւ̃|���S��
PressEnter g_PressEnter;
D3DXCOLOR g_colorfade2;

bool g_nButtonCnt2=false;

//=============================
//�^�C�g����ʂ̏���������
//=============================
void InitPressEnter(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pressA.png", &g_pTexturePressEnter);//--------���������ς�

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPressEnter, NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

	g_PressEnter.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_colorfade2 = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	g_nButtonCnt2 = false;

	//���_���W�̍X�V-----------------------------------
	pVtx[0].pos = D3DXVECTOR3(g_PressEnter.pos.x - 380.0f, g_PressEnter.pos.y - 29.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_PressEnter.pos.x + 380.0f, g_PressEnter.pos.y - 29.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_PressEnter.pos.x - 380.0f, g_PressEnter.pos.y + 29.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_PressEnter.pos.x + 380.0f, g_PressEnter.pos.y + 29.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;//�l�͌Œ�
	pVtx[1].rhw = 1.0f;//�l�͌Œ�
	pVtx[2].rhw = 1.0f;//�l�͌Œ�
	pVtx[3].rhw = 1.0f;//�l�͌Œ�

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPressEnter->Unlock();
}
//=============================
//�^�C�g����ʂ̏I������
//=============================
void UninitPressEnter(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePressEnter != NULL)
	{
		g_pTexturePressEnter->Release();
		g_pTexturePressEnter = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPressEnter != NULL)
	{
		g_pVtxBuffPressEnter->Release();
		g_pVtxBuffPressEnter = NULL;
	}
}
//=============================
//�^�C�g����ʂ̍X�V����
//=============================
void UpdatePressEnter(void)
{
	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

	g_PressEnter.pos = D3DXVECTOR3(SCREEN_WIDE - 270.0f, SCREEN_HEIGHT - 30.0f, 0.0f);

	//���_���W�̍X�V-----------------------------------
	pVtx[0].pos = D3DXVECTOR3(g_PressEnter.pos.x - 250.0f, g_PressEnter.pos.y - 20.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_PressEnter.pos.x + 250.0f, g_PressEnter.pos.y - 20.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_PressEnter.pos.x - 250.0f, g_PressEnter.pos.y + 20.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_PressEnter.pos.x + 250.0f, g_PressEnter.pos.y + 20.0f, 0.0f);

	if (g_nButtonCnt2 == false)
	{
		g_colorfade2.a -= 0.022f;	//�|���S����s�����ɂ��Ă���

		if (g_colorfade2.a <= 0.0f)
		{
			g_colorfade2.a = 0.0f;
			g_nButtonCnt2 = true;
		}
	}
	else if (g_nButtonCnt2 == true)
	{
		g_colorfade2.a += 0.022f;	//�|���S����s�����ɂ��Ă���

		if (g_colorfade2.a >= 1.0f)
		{
			g_colorfade2.a = 1.0f;
			g_nButtonCnt2 = false;
		}
	}

	//�e�N�X�`�����W��ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_colorfade2.a);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_colorfade2.a);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_colorfade2.a);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, g_colorfade2.a);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPressEnter->Unlock();
}
//=============================
//�^�C�g����ʂ̕`�揈��
//=============================
void DrawPressEnter(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();//----------------���������ς�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPressEnter, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);//-------���������ς�

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePressEnter);//---------���������ς�

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��//----------���������ς�
		0,//�`�悷��ŏ��̒��_�C���f�b�N�X
		2);//�`�悷��v���~�e�B�u��

	
	//�e�N�X�`����߂�
	pDevice->SetTexture(0, NULL);

}