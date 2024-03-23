//============================================================================================
//
//���U���g�\�����鏈��[result.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "result.h"
#include "pressenter.h"
#include "game.h"
#include"text.h"

#include"sound.h"

//�}�N����`
#define NUM_TEX	(2)	//���U���g�Ŏg���e�N�X�`���̎��

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureResult[NUM_TEX] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;//���_�o�b�t�@�ւ̃|���S��

bool g_ClearFrag = false;

//=============================
//���U���g��ʂ̏���������
//=============================
void InitResult(void)
{	
	g_ClearFrag = false;

	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Result000.png", &g_apTextureResult[0]);//--------���������ς�
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Result001.png", &g_apTextureResult[1]);//--------���������ς�

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffResult, NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍X�V-----------------------------------
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDE, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDE, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;//�l�͌Œ�
	pVtx[1].rhw = 1.0f;//�l�͌Œ�
	pVtx[2].rhw = 1.0f;//�l�͌Œ�
	pVtx[3].rhw = 1.0f;//�l�͌Œ�

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W��ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��





	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();



	InitPressEnter();

	g_ClearFrag = GetGameClearFrag();//������Clear������//----------------------------------------����𗘗p����if����

	PlaySound(SOUND_LABEL_BGM001);
}
//=============================
//���U���g��ʂ̏I������
//=============================
void UninitResult(void)
{
	for (int nCnt = 0; nCnt < NUM_TEX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureResult[nCnt] != NULL)
		{
			g_apTextureResult[nCnt]->Release();
			g_apTextureResult[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}


	UninitPressEnter();
	
	StopSound();
}
//=============================
//���U���g��ʂ̍X�V����
//=============================
void UpdateResult(void)
{





	UpdatePressEnter();

	if (GetkeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A,0) == true || GetJoypadTrigger(JOYKEY_A, 1) == true)
	{//����L�[(Enter�L�[)�������ꂽ
	
		PlaySound(SOUND_LABEL_SE_DECISION);

		//PlaySound(SOUND_LABEL_SE_ENTER000);
		
		SetFade(MODE_TITLE);
	}
}
//=============================
//���U���g��ʂ̕`�揈��
//=============================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();//----------------���������ς�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);//-------���������ς�

	//for (int nCnt = 0; nCnt < NUM_TEX; nCnt++)
	{
		if (g_ClearFrag == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureResult[0]);//---------���������ς�

		}
		else
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureResult[1]);//---------���������ς�
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��//----------���������ς�
			0,//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);//�`�悷��v���~�e�B�u��
	}
	
	//�e�N�X�`����߂�
	pDevice->SetTexture(0, NULL);
	DrawPressEnter();
}