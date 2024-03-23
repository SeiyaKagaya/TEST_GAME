//============================================================================================
//
//�^�C�g���\�����鏈��[title.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "title.h"


#include "player.h"
#include "input.h"
#include "fade.h"

#include "text.h"

#include "sound.h"


#define NUM_TITLE	(3)//title��ʂ̕\����

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTitle[NUM_TITLE] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//���_�o�b�t�@�ւ̃|���S��
Title g_Title[NUM_TITLE];//�^�C�g���̏��
D3DXCOLOR g_colorfade[NUM_TITLE];
TITLESTATE g_TitleState;//�t�F�[�h���̎���

bool g_nSkipCnt = false;//Enter�Ŏn�߂�邩�ǂ���
bool g_nButtonCnt = false;//�{�^�������`�J�`�J�̂��

//=============================
//�^�C�g����ʂ̏���������
//=============================
void InitTitle(void)
{
	int nCntTitle = 0;


	g_nSkipCnt = false;
	g_nButtonCnt = false;

	g_TitleState = TITLE_BG;

	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\titleBG.png", &g_pTextureTitle[0]);	//�^�C�g���w�i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\titlespell.png", &g_pTextureTitle[1]);	//�Q�[���̖��O
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pressA.png", &g_pTextureTitle[2]);//�{�^������

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 12, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		g_colorfade[nCntTitle] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		//g_colorfade[nCntTitle].a = 0.0f;

		g_Title[nCntTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;//�l�͌Œ�
		pVtx[1].rhw = 1.0f;//�l�͌Œ�
		pVtx[2].rhw = 1.0f;//�l�͌Œ�
		pVtx[3].rhw = 1.0f;//�l�͌Œ�]

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���_���W�̍X�V-----------------------------------
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�e�N�X�`�����W��ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	PlaySound(SOUND_LABEL_BGM000);
}
//=============================
//�^�C�g����ʂ̏I������
//=============================
void UninitTitle(void)
{
	StopSound(SOUND_LABEL_BGM000);

	int nCntTitle = 0;

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}
//=============================
//�^�C�g����ʂ̍X�V����
//=============================
void UpdateTitle(void)
{
	int nCntTitle = 0;

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		if (nCntTitle == TITLE_BG)
		{//�^�C�g���w�i�̂Ƃ�
			g_Title[nCntTitle].pos = D3DXVECTOR3(SCREEN_WIDE / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);

			//���_���W�̍X�V-----------------------------------
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDE, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDE, SCREEN_HEIGHT, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			if (g_TitleState == TITLE_BG)
			{//�w�i
				if (g_colorfade[nCntTitle].a < 1.0f)
				{
					g_colorfade[nCntTitle].a += 0.03f;	//�|���S����s�����ɂ��Ă���
				}
				if (g_colorfade[nCntTitle].a >= 1.0f)
				{
					g_colorfade[nCntTitle].a = 1.0f;
					g_TitleState = TITLE_NAME;//���O�t�F�[�h�̃^�C�~���O
				}
			}

		}
		else if (nCntTitle == TITLE_NAME)
		{//�^�C�g�����̂Ƃ�
			g_Title[nCntTitle].pos = D3DXVECTOR3(SCREEN_WIDE * 0.7f, SCREEN_HEIGHT * 0.5f, 0.0f);

			//���_���W�̍X�V-----------------------------------
			pVtx[0].pos = D3DXVECTOR3(g_Title[nCntTitle].pos.x - 200.0f, g_Title[nCntTitle].pos.y - 200.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Title[nCntTitle].pos.x + 200.0f, g_Title[nCntTitle].pos.y - 200.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Title[nCntTitle].pos.x - 200.0f, g_Title[nCntTitle].pos.y + 200.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Title[nCntTitle].pos.x + 200.0f, g_Title[nCntTitle].pos.y + 200.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			if (g_TitleState == TITLE_NAME)
			{//�^�C�g������
				if (g_colorfade[nCntTitle].a < 1.0f)
				{
					g_colorfade[nCntTitle].a += 0.005f;	//�|���S����s�����ɂ��Ă���
				}
				if (g_colorfade[nCntTitle].a >= 1.0f)
				{
					g_colorfade[nCntTitle].a = 1.0f;
					g_TitleState = TITLE_PRESSENTER;
				}
			}
		}
		else if (nCntTitle == TITLE_PRESSENTER)
		{//�{�^�������̂Ƃ�
			g_Title[nCntTitle].pos = D3DXVECTOR3(SCREEN_WIDE * 0.75f, SCREEN_HEIGHT * 0.9f, 0.0f);


			//���_���W�̍X�V-----------------------------------
			pVtx[0].pos = D3DXVECTOR3(g_Title[nCntTitle].pos.x - 320.0f, g_Title[nCntTitle].pos.y - 40.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Title[nCntTitle].pos.x + 320.0f, g_Title[nCntTitle].pos.y - 40.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Title[nCntTitle].pos.x - 320.0f, g_Title[nCntTitle].pos.y + 40.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Title[nCntTitle].pos.x + 320.0f, g_Title[nCntTitle].pos.y + 40.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			if (g_TitleState == TITLE_PRESSENTER)
			{//�{�^������
				if (g_colorfade[nCntTitle].a < 1.0f)
				{
					g_colorfade[nCntTitle].a += 0.02f;	//�|���S����s�����ɂ��Ă���
				}
				if (g_colorfade[nCntTitle].a >= 1.0f)
				{
					g_colorfade[nCntTitle].a = 1.0f;
					g_TitleState = TITLE_PRESSLOOP;
				}
			}
		}

		if (g_TitleState == TITLE_PRESSLOOP)
		{//�{�^���������[�v
			g_nSkipCnt = true;//��ʕϑJ�\��

			g_colorfade[0].a = 1.0f;
			g_colorfade[1].a = 1.0f;

			if (nCntTitle == TITLE_PRESSENTER)
			{//�{�^�������̂Ƃ�
				if (g_nButtonCnt == false)
				{
					g_colorfade[nCntTitle].a -= 0.01f;	//�|���S���𓧖��ɂ��Ă���

					if (g_colorfade[nCntTitle].a <= 0.5f)
					{
						g_colorfade[nCntTitle].a = 0.5f;
						g_nButtonCnt = true;
					}
				}
				else if (g_nButtonCnt == true)
				{
					g_colorfade[nCntTitle].a += 0.01f;	//�|���S����s�����ɂ��Ă���

					if (g_colorfade[nCntTitle].a >= 1.0f)
					{
						g_colorfade[nCntTitle].a = 1.0f;
						g_nButtonCnt = false;
					}
				}
			}

		}

		//�e�N�X�`�����W��ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��


		if (nCntTitle == TITLE_PRESSENTER)
		{//�{�^�������̂Ƃ�
		//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorfade[nCntTitle].a);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorfade[nCntTitle].a);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorfade[nCntTitle].a);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorfade[nCntTitle].a);
		}
		else
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorfade[nCntTitle].a);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorfade[nCntTitle].a);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorfade[nCntTitle].a);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorfade[nCntTitle].a);
		}

		pVtx += 4;
	}

	if (GetkeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A, 0) == true || GetJoypadTrigger(JOYKEY_A, 1) == true)
	{//����L�[(Enter�L�[)�������ꂽ
		PlaySound(SOUND_LABEL_SE_DECISION);

		if (g_nSkipCnt == false)
		{//�܂���ʓ����Ă钆
			g_TitleState = TITLE_PRESSLOOP;
		}
		else if (g_nSkipCnt == true)
		{
			//	PlaySound(SOUND_LABEL_SE_ENTER001);
			SetFade(MODE_MENU);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}
//=============================
//�^�C�g����ʂ̕`�揈��
//=============================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();//----------------���������ς�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);//-------���������ς�

	int nCntTitle = 0;

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCntTitle]);//---------���������ς�

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��//----------���������ς�
			nCntTitle * 4,//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);//�`�悷��v���~�e�B�u��

		
		//�e�N�X�`����߂�
		pDevice->SetTexture(0, NULL);
	}
}
