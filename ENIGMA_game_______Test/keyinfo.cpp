//=============================================
//
//���o��UI[keyinfo.h]
//Auther Matsuda Towa
//
//=============================================
#include "keyinfo.h"
#include "game.h"
#include "text.h"

//=============================================
//�}�N����`
//=============================================
#define SCREEN_TIME	(140) //�p������
#define KEYINFO_WIDE	(520) //�p������
#define KEYINFO_HIGHT	(40) //�p������

//=============================================
//�O���[�o���ϐ��錾
//=============================================
LPDIRECT3DTEXTURE9 g_pTextureKeyinfo = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffKeyinfo = NULL;//���_�o�b�t�@�ւ̃|���S��
Keyinfo g_Keyinfo;

//=============================================
//������
//=============================================
void InitKeyinfo(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//	int nCntPause = 0;

		//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\keyinfoframe.png",
		&g_pTextureKeyinfo
	);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffKeyinfo, NULL);

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffKeyinfo->Lock(0, 0, (void**)&pVtx, 0);

	g_Keyinfo.bUse = false;

	g_Keyinfo.fAlpha = 1.0f;
	g_Keyinfo.nScreenCnt = 0;
	g_Keyinfo.pos = D3DXVECTOR3(SCREEN_WIDE / 2.0f, SCREEN_HEIGHT / 1.95f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Keyinfo.pos.x - KEYINFO_WIDE, g_Keyinfo.pos.y - KEYINFO_HIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Keyinfo.pos.x + KEYINFO_WIDE, g_Keyinfo.pos.y - KEYINFO_HIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Keyinfo.pos.x - KEYINFO_WIDE, g_Keyinfo.pos.y + KEYINFO_HIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Keyinfo.pos.x + KEYINFO_WIDE, g_Keyinfo.pos.y + KEYINFO_HIGHT, 0.0f);
		
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);

	//�e�L�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffKeyinfo->Unlock();
}

//=============================================
//�I��
//=============================================
void UninitKeyinfo(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureKeyinfo != NULL)
	{
		g_pTextureKeyinfo->Release();
		g_pTextureKeyinfo = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffKeyinfo != NULL)
	{
		g_pVtxBuffKeyinfo->Release();
		g_pVtxBuffKeyinfo = NULL;
	}
}

//=============================================
//�X�V
//=============================================
void UpdateKeyinfo(void)
{
	if (g_Keyinfo.bUse == true)
	{
		g_Keyinfo.nScreenCnt++;
		if (g_Keyinfo.nScreenCnt >= SCREEN_TIME)
		{
			VERTEX_2D* pVtx;//���_���̃|�C���^

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffKeyinfo->Lock(0, 0, (void**)&pVtx, 0);

			g_Keyinfo.fAlpha -= 0.1f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);


			if (g_Keyinfo.fAlpha <= 0.0f)
			{
				g_Keyinfo.fAlpha = 0.0f;
				g_Keyinfo.nScreenCnt = 0;
				g_Keyinfo.bUse = false;
			}
		}

	}
	
	g_pVtxBuffKeyinfo->Unlock();
}

//=============================================
//�`��
//=============================================
void DrawKeyinfo(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

//�f�o�C�X�̎擾
	pDevice = GetDevice();//----------------���������ς�


	if (g_Keyinfo.bUse == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffKeyinfo, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);//-------���������ς�

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureKeyinfo);//---------���������ς�

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��//----------���������ς�
			0,//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);//�`�悷��v���~�e�B�u��

		//�e�N�X�`����߂�
		pDevice->SetTexture(0, NULL);

		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_REMOCON)
		{
			DrawTVinfo();
		}
		else if (g_Keyinfo.nSpawnPlace == NOT_HAVE_DISH 
			|| g_Keyinfo.nSpawnPlace == NOT_HAVE_VEGETABLE
			||g_Keyinfo.nSpawnPlace == NOT_HAVE_NEED_KITCHEN)
		{
			DrawKitcheninfo();
		}
		else if (g_Keyinfo.nSpawnPlace == NOT_HAVE_SOUP)
		{
			DrawDeskinfo();//��
		}
		else if (g_Keyinfo.nSpawnPlace == PUSH_CREEN)
		{
			DrawKeyinfoCreen();//�򉻑��u
		}
		else if (g_Keyinfo.nSpawnPlace == SPAWNPLACE_GATE)
		{
			DrawKeyinfoGate();
		}
		else if (g_Keyinfo.nSpawnPlace == MISSMONEYBOX)
		{
			DrawKeyinfoMoneyBox();
		}
		else if (g_Keyinfo.nSpawnPlace == TAKE_A_BATH)
		{
			DrawKeyinfoBath();
		}
		else if (g_Keyinfo.nSpawnPlace == SPAWN_DISH)
		{
			DrawKeyinfoDish();
		}
		else
		{
			DrawKeyinfoText();
		}
	}
	
}

//=============================================
//�e�L�X�g�\��
//=============================================
void DrawTVinfo(void)
{
	if (g_Keyinfo.nPlayerIdx == 0)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "�����R�����������ߑ���ł��Ȃ�");
	}
	else if (g_Keyinfo.nPlayerIdx == 1)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f,  0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "�����R�����������ߑ���ł��Ȃ�");
	}
}

//=============================================
//�e�L�X�g�\��
//=============================================
void DrawKitcheninfo(void)
{
	if (g_Keyinfo.nPlayerIdx == 0)
	{
		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_DISH)
		{
			DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "�M���������ߒ����ł��Ȃ�");
		}
		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_VEGETABLE)
		{
			DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "��؂��������ߒ����ł��Ȃ�");
		}
		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_NEED_KITCHEN)
		{
			DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "�M�Ɩ�؂��������ߒ����ł��Ȃ�");
		}
	}
	else if (g_Keyinfo.nPlayerIdx == 1)
	{
		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_DISH)
		{
			DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "�M���������ߒ����ł��Ȃ�");
		}
		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_VEGETABLE)
		{
			DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "��؂��������ߒ����ł��Ȃ�");
		}
		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_NEED_KITCHEN)
		{
			DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "�M�Ɩ�؂��������ߒ����ł��Ȃ�");
		}
	}
}
//=============================================
//�e�L�X�g�\��
//=============================================
void DrawDeskinfo(void)
{
	if (g_Keyinfo.nPlayerIdx == 0)
	{
		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_SOUP)
		{
			DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "�X�[�v���������ߊ��ɒu���Ȃ�");
		}
		
	}
	else if (g_Keyinfo.nPlayerIdx == 1)
	{
		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_SOUP)
		{
			DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "�X�[�v���������ߊ��ɒu���Ȃ�");
		}
	}
}

//=============================================
//�e�L�X�g�\��
//=============================================
void DrawKeyinfoText(void)
{
	if (g_Keyinfo.nSpawnPlace == SPAWNPLACE_LIVING)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 3.25f, SCREEN_HEIGHT / 2.12f, 0.0f), 55, FONT_GENSIN, D3DXCOLOR(0.1f,1.0f, 0.0f, 1.0f), "���r���O�Ɍ����o������");
	}
	if (g_Keyinfo.nSpawnPlace == SPAWNPLACE_BASEMENT)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.6f, SCREEN_HEIGHT / 2.12f, 0.0f), 55, FONT_GENSIN, D3DXCOLOR(0.1f, 1.0f, 0.0f, 1.0f), "�n�����Ɍ����o������");
	}
	if (g_Keyinfo.nSpawnPlace == SPAWNPLACE_BATHROOM)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.6f, SCREEN_HEIGHT / 2.12f, 0.0f), 55, FONT_GENSIN, D3DXCOLOR(0.1f, 1.0f, 0.0f, 1.0f), "�����C��Ɍ����o������");
	}
}
//=============================================
//�e�L�X�g�\��--�򉻑��u
//=============================================
void DrawKeyinfoCreen(void)//�򉻑��u�e�L�X�g
{
	if (g_Keyinfo.nPlayerIdx == 0)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "������ߑ��u���N������");
	}
	else if (g_Keyinfo.nPlayerIdx == 1)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "������ߑ��u���N������");
	}
	else
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.9f, SCREEN_HEIGHT / 2.12f, 0.0f), 55, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "������ߑ��u���N������");
	}
}
//=============================================
//�e�L�X�g�\��--/�o��o��
//=============================================
void DrawKeyinfoGate(void)
{
	if (g_Keyinfo.nPlayerIdx == 0)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), "���r���O�ɉ������N����");
	}
	else if (g_Keyinfo.nPlayerIdx == 1)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), "���r���O�ɉ������N����");
	}
	else
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.9f, SCREEN_HEIGHT / 2.12f, 0.0f), 55, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), "���r���O�ɉ������N����");
	}
}
//=============================================
//�e�L�X�g�\��--/���Ɏ��s
//=============================================
void DrawKeyinfoMoneyBox(void)
{
	if (g_Keyinfo.nPlayerIdx == 0)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), "    �p�X���[�h���Ⴄ�悤��");
	}
	else if (g_Keyinfo.nPlayerIdx == 1)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), "     �p�X���[�h���Ⴄ�悤��");
	}
	else
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.9f, SCREEN_HEIGHT / 2.12f, 0.0f), 55, FONT_GENSIN, D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), "     �p�X���[�h���Ⴄ�悤��");
	}
}
//=============================================
//�e�L�X�g�\��--/���C������
//=============================================
void DrawKeyinfoBath(void)
{
	if (g_Keyinfo.nPlayerIdx == 0)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "   �ꂩ�烊���R�����o�Ă���");
	}
	else if (g_Keyinfo.nPlayerIdx == 1)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "    �ꂩ�烊���R�����o�Ă���");
	}
	else
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.9f, SCREEN_HEIGHT / 2.12f, 0.0f), 55, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "    �ꂩ�烊���R�����o�Ă���");
	}
}

//=============================================
//�e�L�X�g�\��--/�M�N����
//=============================================
void DrawKeyinfoDish(void)
{
	if (g_Keyinfo.nPlayerIdx == 0)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 7.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "   �M���o�Ă���");
	}
	else if (g_Keyinfo.nPlayerIdx == 1)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.52f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "    �M���o�Ă���");
	}
}

//=============================================
//�ݒ�
//=============================================
void SetKeyinfo(KeySpawnPlace nSpawnPlace,int PlayerIdx)
{
	if (g_Keyinfo.bUse == false)
	{
		g_Keyinfo.nPlayerIdx = PlayerIdx;
		g_Keyinfo.fAlpha = 0.7f;
		g_Keyinfo.nScreenCnt = 0;
		g_Keyinfo.nSpawnPlace = nSpawnPlace;
		g_Keyinfo.bUse = true;
		VERTEX_2D* pVtx;//���_���̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffKeyinfo->Lock(0, 0, (void**)&pVtx, 0);
		if (g_Keyinfo.nPlayerIdx == -1)
		{//�S�v���C���[��
			g_Keyinfo.pos = D3DXVECTOR3(SCREEN_WIDE / 2.0f, SCREEN_HEIGHT / 1.95f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_Keyinfo.pos.x - KEYINFO_WIDE, g_Keyinfo.pos.y - KEYINFO_HIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Keyinfo.pos.x + KEYINFO_WIDE, g_Keyinfo.pos.y - KEYINFO_HIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Keyinfo.pos.x - KEYINFO_WIDE, g_Keyinfo.pos.y + KEYINFO_HIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Keyinfo.pos.x + KEYINFO_WIDE, g_Keyinfo.pos.y + KEYINFO_HIGHT, 0.0f);
		}
		else if (g_Keyinfo.nPlayerIdx == 0)
		{//�S�v���C���[��
			g_Keyinfo.pos = D3DXVECTOR3(SCREEN_WIDE / 4.0f, SCREEN_HEIGHT / 1.95f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_Keyinfo.pos.x - KEYINFO_WIDE / 1.75f, g_Keyinfo.pos.y - KEYINFO_HIGHT / 1.75f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Keyinfo.pos.x + KEYINFO_WIDE / 1.75f, g_Keyinfo.pos.y - KEYINFO_HIGHT / 1.75f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Keyinfo.pos.x - KEYINFO_WIDE / 1.75f, g_Keyinfo.pos.y + KEYINFO_HIGHT / 1.75f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Keyinfo.pos.x + KEYINFO_WIDE / 1.75f, g_Keyinfo.pos.y + KEYINFO_HIGHT / 1.75f, 0.0f);
		}
		else if (g_Keyinfo.nPlayerIdx == 1)
		{//�S�v���C���[��
			g_Keyinfo.pos = D3DXVECTOR3(SCREEN_WIDE / 1.33f, SCREEN_HEIGHT / 1.95f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_Keyinfo.pos.x - KEYINFO_WIDE / 1.75f, g_Keyinfo.pos.y - KEYINFO_HIGHT / 1.75f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Keyinfo.pos.x + KEYINFO_WIDE / 1.75f, g_Keyinfo.pos.y - KEYINFO_HIGHT / 1.75f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Keyinfo.pos.x - KEYINFO_WIDE / 1.75f, g_Keyinfo.pos.y + KEYINFO_HIGHT / 1.75f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Keyinfo.pos.x + KEYINFO_WIDE / 1.75f, g_Keyinfo.pos.y + KEYINFO_HIGHT / 1.75f, 0.0f);
		}
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
		g_pVtxBuffKeyinfo->Unlock();

	}
}

