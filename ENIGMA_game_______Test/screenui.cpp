//============================================================================================
//
//�^�C�g���\�����鏈��[screenui.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "screenui.h"
#include "text.h"


//#include "player.h"
#//include "input.h"
//#include "fade.h"
//#include "sound.h"




//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureScreenUI[NUM_UI] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScreenUI = NULL;//���_�o�b�t�@�ւ̃|���S��
ScreenUI g_ScreenUI[MAX_UI];//�^�C�g���̏��
//D3DXCOLOR g_colorfade[NUM_UI];
SCREENUISTATE g_ScreenUIState;//�t�F�[�h���̎���

ScreenState g_ScreenState[MAX_UI];

//=============================
//�X�N���[��UI�̏���������
//=============================
void InitScreenUI(void)
{
	for (int i = 0; i < MAX_UI; i++)
	{
		g_ScreenState[i].MoneyBox_bUse = false;
		g_ScreenState[i].TV_bUse = false;
	}

	int nCntScreenUI = 0;

	g_ScreenUIState = SCREENUI_MAX;

	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\yoko.png", &g_pTextureScreenUI[0]);	//�\���L�[
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Watch.png", &g_pTextureScreenUI[1]);	//���v
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\start.png", &g_pTextureScreenUI[2]);	//START

			//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4* MAX_UI, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffScreenUI, NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScreenUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScreenUI = 0; nCntScreenUI < MAX_UI; nCntScreenUI++)
	{
		g_ScreenUI[nCntScreenUI].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ScreenUI[nCntScreenUI].bUse = false;
		g_ScreenUI[nCntScreenUI].type = SCREENUI_MAX;

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
	g_pVtxBuffScreenUI->Unlock();

	SetScreenUI(D3DXVECTOR3(85.0f, 550.0f, 0.0f), SCREENUI_CROSS_0);
	SetScreenUI(D3DXVECTOR3(SCREEN_WIDE / 2.0f + 85.0f, 550.0f, 0.0f), SCREENUI_CROSS_1);

	SetScreenUI(D3DXVECTOR3(SCREEN_WIDE / 2.0f - 85.0f, SCREEN_HEIGHT - 697.0f, 0.0f), SCREENUI_WATCH);

	SetScreenUI(D3DXVECTOR3(20.0f, 700.0f, 0.0f), SCREENUI_START);
	SetScreenUI(D3DXVECTOR3(SCREEN_WIDE / 2.0f + 20.0f, 700.0f, 0.0f), SCREENUI_START);
}
//=============================
//�X�N���[��UI�̏I������
//=============================
void UninitScreenUI(void)
{
	//StopSound(SOUND_LABEL_BGM000);

	int nCntScreenUI = 0;

	for (nCntScreenUI = 0; nCntScreenUI < NUM_UI; nCntScreenUI++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureScreenUI[nCntScreenUI] != NULL)
		{
			g_pTextureScreenUI[nCntScreenUI]->Release();
			g_pTextureScreenUI[nCntScreenUI] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScreenUI != NULL)
	{
		g_pVtxBuffScreenUI->Release();
		g_pVtxBuffScreenUI = NULL;
	}
}
//=============================
//�X�N���[��UI�̍X�V����
//=============================
void UpdateScreenUI(void)
{
	int nCntScreenUI = 0;

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScreenUI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScreenUI = 0; nCntScreenUI < MAX_UI; nCntScreenUI++)
	{
		if (g_ScreenUI[nCntScreenUI].bUse == true)
		{
			if (g_ScreenUI[nCntScreenUI].type == SCREENUI_CROSS_0)
			{//�\�����[
			//	g_ScreenUI[nCntScreenUI].pos = D3DXVECTOR3(SCREEN_WIDE / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
			}
			else if (g_ScreenUI[nCntScreenUI].type == SCREENUI_CROSS_1)
			{//���v�̂Ƃ�
			//	g_ScreenUI[nCntScreenUI].pos = D3DXVECTOR3((SCREEN_WIDE / 2.0f) - 90.0f, SCREEN_HEIGHT - 700.0f, 0.0f);
			}
			else if (g_ScreenUI[nCntScreenUI].type == SCREENUI_WATCH)
			{//���v�̂Ƃ�

			}

			pVtx += 4;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScreenUI->Unlock();
}
//=============================
//�X�N���[��UI�̕`�揈��
//=============================
void DrawScreenUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();//----------------���������ς�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScreenUI, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);//-------���������ς�

	int nCntScreenUI = 0;
	int TexNum = 0;
	for (nCntScreenUI = 0; nCntScreenUI < MAX_UI; nCntScreenUI++)
	{
		if (g_ScreenUI[nCntScreenUI].bUse == true)
		{
			if (g_ScreenUI[nCntScreenUI].type == SCREENUI_CROSS_0 || g_ScreenUI[nCntScreenUI].type == SCREENUI_CROSS_1)
			{//
				TexNum = 0;
			}
			else if (g_ScreenUI[nCntScreenUI].type == SCREENUI_WATCH)
			{//���v�̂Ƃ�
				TexNum = 1;
			}
			else if (g_ScreenUI[nCntScreenUI].type == SCREENUI_START)
			{//���v�̂Ƃ�
				TexNum = 2;
			}
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureScreenUI[TexNum]);//---------���������ς�

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��//----------���������ς�
				nCntScreenUI * 4,//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);//�`�悷��v���~�e�B�u��
		}
		
	}

	//�e�N�X�`����߂�
	pDevice->SetTexture(0, NULL);




	if (g_ScreenState[0].MoneyBox_bUse==true)
	{
		//�����
		DrawTextSet(D3DXVECTOR3(4.0f, 525.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), "�_�C����\n   �I��");//��

		DrawTextSet(D3DXVECTOR3(4.0f, 503.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(0.7f, 0.7f, 1.0f, 1.0f), "�_�C������]");//��
	}
	else if(g_ScreenState[0].TV_bUse == true)
	{
		DrawTextSet(D3DXVECTOR3(4.0f, 503.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(0.7f, 0.7f, 1.0f, 1.0f), "�`�����l���؊�");//��
	}
	else
	{
		//�����
		DrawTextSet(D3DXVECTOR3(4.0f, 525.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), "�A�C�e��\n   �I��");//��

		DrawTextSet(D3DXVECTOR3(4.0f, 503.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(0.7f, 0.7f, 1.0f, 1.0f), "�A�C�e���g�p");//��
	}

	if (g_ScreenState[1].MoneyBox_bUse == true)
	{
		//�E���
		DrawTextSet(D3DXVECTOR3(4.0f + (SCREEN_WIDE / 2.0f), 525.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), "�_�C����\n   �I��");//��

		DrawTextSet(D3DXVECTOR3(4.0f + (SCREEN_WIDE / 2.0f), 503.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(0.7f, 0.7f, 1.0f, 1.0f), "�_�C������]");//��
	}
	else if (g_ScreenState[1].TV_bUse == true)
	{

		DrawTextSet(D3DXVECTOR3(4.0f + (SCREEN_WIDE / 2.0f), 503.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(0.7f, 0.7f, 1.0f, 1.0f), "�`�����l���؊�");//��

	}
	else
	{
		//�E���
		DrawTextSet(D3DXVECTOR3(4.0f + (SCREEN_WIDE / 2.0f), 525.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), "�A�C�e��\n   �I��");//��

		DrawTextSet(D3DXVECTOR3(4.0f + (SCREEN_WIDE / 2.0f), 503.0f, 0.0f), 19, FONT_GENSIN, D3DXCOLOR(0.7f, 0.7f, 1.0f, 1.0f), "�A�C�e���g�p");//��

	}



	for (int i = 0; i < MAX_UI; i++)
	{
		g_ScreenState[i].MoneyBox_bUse = false;
		g_ScreenState[i].TV_bUse = false;
	}

	DrawTextSet(D3DXVECTOR3(32.0f, 688.0f, 0.0f), 22, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), " :�|�[�Y");//��
	DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.0f + 32.0f, 688.0f, 0.0f), 22, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), " :�|�[�Y");//��
}
//=============================
//�X�N���[��UI�̐ݒ菈��
//=============================
void SetScreenUI(D3DXVECTOR3 pos, SCREENUISTATE UItype)
{
	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScreenUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScreenUI = 0; nCntScreenUI < MAX_UI; nCntScreenUI++)
	{
		if (g_ScreenUI[nCntScreenUI].bUse == false)
		{
			g_ScreenUI[nCntScreenUI].pos = pos;
			g_ScreenUI[nCntScreenUI].bUse = true;
			g_ScreenUI[nCntScreenUI].type = UItype;

			if (g_ScreenUI[nCntScreenUI].type == SCREENUI_CROSS_0)
			{//
				//���_���W�̍X�V-----------------------------------
				pVtx[0].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x - CROSSSIZE, g_ScreenUI[nCntScreenUI].pos.y - CROSSSIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x + CROSSSIZE, g_ScreenUI[nCntScreenUI].pos.y - CROSSSIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x - CROSSSIZE, g_ScreenUI[nCntScreenUI].pos.y + CROSSSIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x + CROSSSIZE, g_ScreenUI[nCntScreenUI].pos.y + CROSSSIZE, 0.0f);

			}
			else if (g_ScreenUI[nCntScreenUI].type == SCREENUI_CROSS_1)
			{//
				//���_���W�̍X�V-----------------------------------
				pVtx[0].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x - CROSSSIZE, g_ScreenUI[nCntScreenUI].pos.y - CROSSSIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x + CROSSSIZE, g_ScreenUI[nCntScreenUI].pos.y - CROSSSIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x - CROSSSIZE, g_ScreenUI[nCntScreenUI].pos.y + CROSSSIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x + CROSSSIZE, g_ScreenUI[nCntScreenUI].pos.y + CROSSSIZE, 0.0f);

			}
			else if (g_ScreenUI[nCntScreenUI].type == SCREENUI_WATCH)
			{//���v�̂Ƃ�
				//���_���W�̍X�V-----------------------------------
				pVtx[0].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x - WATCHSIZE, g_ScreenUI[nCntScreenUI].pos.y - WATCHSIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x + WATCHSIZE, g_ScreenUI[nCntScreenUI].pos.y - WATCHSIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x - WATCHSIZE, g_ScreenUI[nCntScreenUI].pos.y + WATCHSIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x + WATCHSIZE, g_ScreenUI[nCntScreenUI].pos.y + WATCHSIZE, 0.0f);				
			}
			else if (g_ScreenUI[nCntScreenUI].type == SCREENUI_START)
			{//�{�^��
				//���_���W�̍X�V-----------------------------------
				pVtx[0].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x - STARTSIZE, g_ScreenUI[nCntScreenUI].pos.y - STARTSIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x + STARTSIZE, g_ScreenUI[nCntScreenUI].pos.y - STARTSIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x - STARTSIZE, g_ScreenUI[nCntScreenUI].pos.y + STARTSIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_ScreenUI[nCntScreenUI].pos.x + STARTSIZE, g_ScreenUI[nCntScreenUI].pos.y + STARTSIZE, 0.0f);
			}


			//�e�N�X�`�����W��ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			break;
		}

		pVtx += 4;//�|�C���^���S�i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScreenUI->Unlock();
}
//=============================
//�X�N���[��UI�̎擾����
//=============================
ScreenState* GetScreenState(void)
{
	return &g_ScreenState[0];
}