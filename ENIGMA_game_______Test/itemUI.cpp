//============================================================================================
//
//�A�C�e��UI�\�����鏈��[result.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "item.h"
#include "itemUI.h"
#include "game.h"
#include "particle.h"
#include "input.h"
#include "player.h"
#include "camera.h"
#include "player2.h"
#include "text.h"


//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureItem_UI[ITEMTEXUINUM] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem_UI = NULL;//���_�o�b�t�@�ւ̃|���S��

ITEM_UI g_ItemUI[MAXITEMUI];

int g_ItemNum = 0;//�A�C�e��������
int g_PointNum[2] = {};//�|�C���^�[�̈ʒu�ԍ�

int g_ItemNum2 = 0;//�A�C�e��������


//�`��\��(�A�b�v�f�[�g�ŕϓ��E�`��Ŏg�p)
bool g_DrawOK[3] = {};//�O�Ԗڂ������ture

//=============================
//�A�C�e��UI�̏���������
//=============================
void InitItem_UI(void)
{
	g_ItemNum = 0;
	g_PointNum[0] = 0;
	g_PointNum[1] = 0;



	g_ItemNum2 = 0;
	
	g_DrawOK[0] = false;
	g_DrawOK[1] = false;
	g_DrawOK[2] = true;

	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	int nCntItem_UI;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\frame.png", &g_pTextureItem_UI[0]);//�g
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\frameselect.png", &g_pTextureItem_UI[1]);//�|�C���^�[

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_dish.png", &g_pTextureItem_UI[2]);		//�M
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_remocon.png", &g_pTextureItem_UI[3]);	//�����R��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_vegetable.png", &g_pTextureItem_UI[4]);//���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item_soup.png", &g_pTextureItem_UI[5]);//�X�[�v
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\key000.png", &g_pTextureItem_UI[6]);//

	
	//�A�C�e��UI�̏��̏�����(�����鏉���n�_)
	for (nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	{
		g_ItemUI[nCntItem_UI].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ItemUI[nCntItem_UI].nItemType = ITEMTYPE_MAX;
		g_ItemUI[nCntItem_UI].UItype = ITEM_UI_TYPE_MAX;
		g_ItemUI[nCntItem_UI].PlayerNum = -1;
		g_ItemUI[nCntItem_UI].PosNum = -1;
		g_ItemUI[nCntItem_UI].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAXITEMUI, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffItem_UI, NULL);

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem_UI->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	{
		//���_���W�̍X�V-----------------------------------
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		pVtx += 4;//���_�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem_UI->Unlock();

	SetItem_UI(D3DXVECTOR3(ITEMUISIZE + 10.0f, 460.0f, 0), ITEM_UI_TYPE_POINTER, ITEMTYPE_MAX, -1, 1);//�|�C���^�[�����ʒu

	SetItem_UI(D3DXVECTOR3(ITEMUISIZE + 650.0f, 460.0f, 0), ITEM_UI_TYPE_POINTER, ITEMTYPE_MAX, -1, 2);//�|�C���^�[�����ʒu

		//�\���ꏊ�̐ݒ�
	for (int SetCnt = 0; SetCnt < MAXGETITEM; SetCnt++)
	{
		SetItem_UI(D3DXVECTOR3(ITEMUISIZE + 10.0f + (ITEMUISIZE * 2.1f * SetCnt), 460.0f, 0), ITEM_UI_TYPE_FRAME, ITEMTYPE_MAX, -1, 1);//�g
	}
	//�\���ꏊ�̐ݒ�
	for (int SetCnt2 = 0; SetCnt2 < MAXGETITEM; SetCnt2++)
	{
		SetItem_UI(D3DXVECTOR3(ITEMUISIZE + 640.0f + (ITEMUISIZE * 2.1f * SetCnt2) + 10.0f, 460.0f, 0), ITEM_UI_TYPE_FRAME, ITEMTYPE_MAX, -1, 2);//�g
	}


	SetItem_UI(D3DXVECTOR3(SCREEN_WIDE-100.0f, 35.0f, 0), ITEM_UI_TYPE_KEYUI, ITEMTYPE_MAX, -1, -1);//��--�v���C���[�Ȃ�

}
//=============================
//�A�C�e��UI�̏I������
//=============================
void UninitItem_UI(void)
{
	for (int i = 0; i < ITEMTEXUINUM; i++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureItem_UI[i] != NULL)
		{
			g_pTextureItem_UI[i]->Release();
			g_pTextureItem_UI[i] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItem_UI != NULL)
	{
		g_pVtxBuffItem_UI->Release();
		g_pVtxBuffItem_UI = NULL;
	}
}
//=============================
//�A�C�e��UI�̍X�V����
//=============================
void UpdateItem_UI(bool Player1InputOK, bool Player2InputOK)
{
	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem_UI->Lock(0, 0, (void**)&pVtx, 0);

	g_DrawOK[0] = Player1InputOK;
	g_DrawOK[1] = Player2InputOK;


	if (Player1InputOK==true)
	{
	InPutControllerITEM_UI(0);//����

	}

	if (Player2InputOK == true)
	{
		InPutControllerITEM_UI(1);//����
	}


	//�A�C�e������P
	//----------------------------------------------------------------------------------------------------------------------------------------------
	bool bSetOK = false;
	int EscapeIndex[3] = {};
	bool EscapebUse[3] = {};

	for (int nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	{
		if (g_ItemUI[nCntItem_UI].bUse == true)
		{
			if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_MAINBODY)
			{//UI�{��
				if (g_ItemUI[nCntItem_UI].PlayerNum == 1)
				{//�v���C���[1
					if (g_ItemUI[nCntItem_UI].PosNum == 0)
					{
						EscapeIndex[0] = nCntItem_UI;
						EscapebUse[0] = true;

						bSetOK = true;
					}
					else if (g_ItemUI[nCntItem_UI].PosNum == 1)
					{
						EscapeIndex[1] = nCntItem_UI;
						EscapebUse[1] = true;

						bSetOK = true;
					}
					else if (g_ItemUI[nCntItem_UI].PosNum == 2)
					{
						EscapeIndex[2] = nCntItem_UI;
						EscapebUse[2] = true;

						bSetOK = true;
					}
				}
			}
		}
	}

	if (EscapebUse[2] == true)
	{
		if (EscapebUse[1] == false)
		{
			g_ItemUI[EscapeIndex[2]].PosNum = 1;
			//�㏑��
			EscapebUse[1] = true;
			EscapeIndex[1] = EscapeIndex[2];

		}
	}
	if (EscapebUse[1] == true)
	{
		if (EscapebUse[0] == false)
		{
			g_ItemUI[EscapeIndex[1]].PosNum = 0;
			//�㏑��...�ꉞ
			EscapebUse[0] = true;
			EscapeIndex[0] = EscapeIndex[1];
		}
	}
	//if (EscapebUse[0] == true)
	//{
	if (bSetOK == true)
	{
		for (int i = 0; i < 3; i++)
		{
			//if (g_ItemUI[i].UItype == ITEM_UI_TYPE_MAINBODY)
			//{
			g_ItemUI[EscapeIndex[i]].pos = D3DXVECTOR3(ITEMUISIZE + 10.0f + (ITEMUISIZE * 2.1f * g_ItemUI[EscapeIndex[i]].PosNum), 460.0f, 0);
			//}
		}
	}
	//}
	//----------------------------------------------------------------------------------------------------------------------------------------------

	//�A�C�e������Q
	//----------------------------------------------------------------------------------------------------------------------------------------------
	bool bSetOK2 = false;
	int EscapeIndex2[3] = {};
	bool EscapebUse2[3] = {};

	for (int nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	{
		if (g_ItemUI[nCntItem_UI].bUse == true)
		{
			if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_MAINBODY)
			{//UI�{��
				if (g_ItemUI[nCntItem_UI].PlayerNum == 2)
				{//�v���C���[1
					if (g_ItemUI[nCntItem_UI].PosNum == 0)
					{
						EscapeIndex2[0] = nCntItem_UI;
						EscapebUse2[0] = true;

						bSetOK2 = true;
					}
					else if (g_ItemUI[nCntItem_UI].PosNum == 1)
					{
						EscapeIndex2[1] = nCntItem_UI;
						EscapebUse2[1] = true;

						bSetOK2 = true;
					}
					else if (g_ItemUI[nCntItem_UI].PosNum == 2)
					{
						EscapeIndex2[2] = nCntItem_UI;
						EscapebUse2[2] = true;

						bSetOK2 = true;
					}
				}
			}
		}
	}

	if (EscapebUse2[2] == true)
	{
		if (EscapebUse2[1] == false)
		{
			g_ItemUI[EscapeIndex2[2]].PosNum = 1;
			//�㏑��
			EscapebUse2[1] = true;
			EscapeIndex2[1] = EscapeIndex2[2];

		}
	}
	if (EscapebUse2[1] == true)
	{
		if (EscapebUse2[0] == false)
		{
			g_ItemUI[EscapeIndex2[1]].PosNum = 0;
			//�㏑��...�ꉞ
			EscapebUse2[0] = true;
			EscapeIndex2[0] = EscapeIndex2[1];
		}
	}
//	if (EscapebUse2[0] == true)
//	{
	if (bSetOK2 == true)
	{
		for (int i = 0; i < 3; i++)
		{
			//if (g_ItemUI[i].UItype == ITEM_UI_TYPE_MAINBODY)
			//{
			g_ItemUI[EscapeIndex2[i]].pos = D3DXVECTOR3(ITEMUISIZE + 640.0f + 10.0f + (ITEMUISIZE * 2.1f * g_ItemUI[EscapeIndex2[i]].PosNum), 460.0f, 0);
			//}
		}
	}
	//}
	//----------------------------------------------------------------------------------------------------------------------------------------------

	for (int nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	{
		if (g_ItemUI[nCntItem_UI].bUse == true)
		{//�A�C�e��UI���g�p����Ă���

			if (g_ItemUI[nCntItem_UI].PlayerNum == 1)
			{//�v���C���[1
				if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_POINTER)
				{//�|�C���^�[�̂Ƃ�
					g_ItemUI[nCntItem_UI].pos = D3DXVECTOR3(ITEMUISIZE + 10.0f + (ITEMUISIZE * 2.1f * g_PointNum[0]), 460.0f, 0);

				}
			}
			else if (g_ItemUI[nCntItem_UI].PlayerNum == 2)
			{//�v���C���[2
				if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_POINTER)
				{//�|�C���^�[�̂Ƃ�
					g_ItemUI[nCntItem_UI].pos = D3DXVECTOR3(ITEMUISIZE + 650.0f + (ITEMUISIZE * 2.1f * g_PointNum[1]), 460.0f, 0);

				}
			}
		}

		if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_POINTER)
		{//�|�C���^�[�̂Ƃ�
						//���_���W�̍X�V-----------------------------------
			pVtx[0].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE * 1.1f, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE * 1.1f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE * 1.1f, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE * 1.1f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE * 1.1f, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE * 1.1f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE * 1.1f, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE * 1.1f, 0.0f);

		}
		else if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_MAINBODY)
		{//�|�C���^�[�̂Ƃ�
						//���_���W�̍X�V-----------------------------------
			pVtx[0].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE * 0.7f, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE * 0.7f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE * 0.7f, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE * 0.7f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE * 0.7f, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE * 0.7f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE * 0.7f, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE * 0.7f, 0.0f);

		}
		else if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_KEYUI)
		{
			//���_���W�̍X�V-----------------------------------
			pVtx[0].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE2 - 10.0f, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE2 - 10.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE2 - 10.0f, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE2 - 10.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE2 - 10.0f, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE2 - 10.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE2 - 10.0f, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE2 - 10.0f, 0.0f);
		}
		else
		{
		//���_���W�̍X�V-----------------------------------
			pVtx[0].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE, 0.0f);
		}

		pVtx += 4;//���_�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem_UI->Unlock();
}
//=============================
//�A�C�e��UI�̕`�揈��
//=============================
void DrawItem_UI(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	int nCntItem_UI = 0;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItem_UI, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);//-------���������ς�
	for (nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	{
		if (g_ItemUI[nCntItem_UI].bUse == true)
		{//�A�C�e��UI���g�p����Ă���
			if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_FRAME || g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_POINTER)
			{//�g���|�C���^�[�̎�



			//�񋓂�int��
				int EscapeNum = static_cast<int>(g_ItemUI[nCntItem_UI].UItype);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureItem_UI[EscapeNum]);//---------���������ς�
			}
			else if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_MAINBODY)
			{//�A�C�e������

					//�񋓂�int��
				int EscapeNum2 = static_cast<int>(g_ItemUI[nCntItem_UI].nItemType);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureItem_UI[EscapeNum2 + 2]);//---------���������ς�
			}
			else if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_KEYUI)
			{//�A�C�e������

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureItem_UI[6]);//---------���������ς�
			}




			if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_KEYUI)
			{//�A�C�e������
				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
					nCntItem_UI * 4,//�`�悷��ŏ��̒��_�C���f�b�N�X
					2);//�`�悷��v���~�e�B�u��
			}
			else
			{
				if (g_DrawOK[g_ItemUI[nCntItem_UI].PlayerNum - 1] == true)
				{
					//�|���S���̕`��
					pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
						nCntItem_UI * 4,//�`�悷��ŏ��̒��_�C���f�b�N�X
						2);//�`�悷��v���~�e�B�u��
				}
			}
		
			//�e�N�X�`����߂�
			pDevice->SetTexture(0, NULL);
		}
	}


	//DrawTextSet(D3DXVECTOR3(110.0f, 460.0f, 0.0f), 25, FONT_AKABARASINDELERA, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), "1������%d�|�C���^�ʒu%d",g_ItemNum,g_PointNum[0]);

	//DrawTextSet(D3DXVECTOR3(110.0f, 560.0f, 0.0f), 25, FONT_AKABARASINDELERA, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), "2������%d�|�C���^�ʒu%d", g_ItemNum2, g_PointNum[1]);
}
//=============================
//�A�C�e��UI�̐ݒ菈��
//=============================
void SetItem_UI(D3DXVECTOR3 pos, ITEM_UI_TYPE ItemUIType, ITEMTYPE ItemType, int PosNum, int PlayerNum)
{//���̂Ƃ���ł��Ăԉ\��������̂ł��̂܂܂̂ق����֗�

	VERTEX_2D* pVtx;//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem_UI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	{
		if (g_ItemUI[nCntItem_UI].bUse == false)
		{//�A�C�e��UI���g�p����Ă��Ȃ�

			g_ItemUI[nCntItem_UI].bUse = true;//�g�p���Ă�ɂ���

			g_ItemUI[nCntItem_UI].pos = pos;
			g_ItemUI[nCntItem_UI].UItype = ItemUIType;
			g_ItemUI[nCntItem_UI].nItemType = ItemType;
			g_ItemUI[nCntItem_UI].PosNum = PosNum;
			g_ItemUI[nCntItem_UI].PlayerNum = PlayerNum;

			if (ItemUIType == ITEM_UI_TYPE_KEYUI)
			{
				//���_���W�̍X�V-----------------------------------
				pVtx[0].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE2, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE2, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE2, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE2, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE2, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE2, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE2, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE2, 0.0f);
			}
			else
			{
				//���_���W�̍X�V-----------------------------------
				pVtx[0].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE, g_ItemUI[nCntItem_UI].pos.y - ITEMUISIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x - ITEMUISIZE, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_ItemUI[nCntItem_UI].pos.x + ITEMUISIZE, g_ItemUI[nCntItem_UI].pos.y + ITEMUISIZE, 0.0f);
			}
			
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 225, 200);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);

			break;
		}
		pVtx += 4;//�|�C���^���S�i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem_UI->Unlock();
}

//=============================
//���擾���`��
//=============================
void DrawHaveKey(int nHaveKey)
{
	DrawTextSet(D3DXVECTOR3(SCREEN_WIDE - 85.0f, -5.0f, 0), 65, FONT_AKABARASINDELERA, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "%d", nHaveKey);
}

//=============================
//�A�C�e���擾�ł��邩����
//=============================
void GetItem_FromUI(int ItemIndex,int PlayerNum)
{
	ITEM* pItem;
	pItem = GetItem();
	if (PlayerNum == 1)
	{
		Player* pPlayer = GetPlayer();
		if (g_ItemNum < MAXGETITEM)
		{//�ő吔�ɒB���Ă��Ȃ�

			SetItem_UI(D3DXVECTOR3(ITEMUISIZE + 10.0f + (ITEMUISIZE * 2.1f * g_ItemNum), 460.0f, 0), ITEM_UI_TYPE_MAINBODY, pItem[ItemIndex].ItemType, g_ItemNum, 1);//�A�C�e��

			pItem[ItemIndex].bUse = false;

			g_ItemNum++;

			if (pItem[ItemIndex].ItemType == ITEMTYPE_DISH)//��D
			{
				SetParticle(pItem[ItemIndex].pos, 30.0f, 42, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.35f));
				pPlayer->nHaveDish++;
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_REMOCON)//�񕜃A�C�e��
			{
				SetParticle(pItem[ItemIndex].pos, 30.0f, 42, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.35f));
				pPlayer->nHaveRemocon++;
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_VEGETABLE)//�G�n(������??)
			{
				SetParticle(pItem[ItemIndex].pos, 30.0f, 42, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f));
				pPlayer->nHaveVegetable++;

			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_SOUP)//�X�[�v(������??)
			{
				SetParticle(pItem[ItemIndex].pos, 30.0f, 42, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f));
				pPlayer->nHaveSoup++;

			}
		}
		else
		{
			//�擾�ł��Ȃ����o
			if (pItem[ItemIndex].ItemType == ITEMTYPE_DISH)//��D
			{
				SetParticle(pItem[ItemIndex].pos, 40.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.55f));
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_REMOCON)//�񕜃A�C�e��
			{
				SetParticle(pItem[ItemIndex].pos, 40.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.55f));
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_VEGETABLE)//�G�n(������??)
			{
				SetParticle(pItem[ItemIndex].pos, 40.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.55f));
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_SOUP)//�X�[�v(������??)
			{
				SetParticle(pItem[ItemIndex].pos, 40.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.55f));

			}
		}
	}
	else if (PlayerNum == 2)
	{
		Player_2P* pPlayer2 = GetPlayer_2P();

		if (g_ItemNum2 < MAXGETITEM)
		{//�ő吔�ɒB���Ă��Ȃ�

			SetItem_UI(D3DXVECTOR3(ITEMUISIZE + 640.0f + (ITEMUISIZE * 2.1f * g_ItemNum2)+10.0f, 460.0f, 0), ITEM_UI_TYPE_MAINBODY, pItem[ItemIndex].ItemType, g_ItemNum2, 2);//�A�C�e��

			pItem[ItemIndex].bUse = false;

			g_ItemNum2++;

			if (pItem[ItemIndex].ItemType == ITEMTYPE_DISH)//��D
			{
				SetParticle(pItem[ItemIndex].pos, 30.0f, 42, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.35f));
				pPlayer2->nHaveDish++;
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_REMOCON)//�񕜃A�C�e��
			{
				SetParticle(pItem[ItemIndex].pos, 30.0f, 42, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.35f));
				pPlayer2->nHaveRemocon++;
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_VEGETABLE)//�G�n(������??)
			{
				SetParticle(pItem[ItemIndex].pos, 30.0f, 42, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f));
				pPlayer2->nHaveVegetable++;
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_SOUP)//�X�[�v(������??)
			{
				SetParticle(pItem[ItemIndex].pos, 30.0f, 42, PARTICLETYPE_ITEM, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f));
				pPlayer2->nHaveSoup++;

			}

		}
		else
		{
			//�擾�ł��Ȃ����o
			if (pItem[ItemIndex].ItemType == ITEMTYPE_DISH)//��D
			{
				SetParticle(pItem[ItemIndex].pos, 40.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.55f));
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_REMOCON)//�񕜃A�C�e��
			{
				SetParticle(pItem[ItemIndex].pos, 40.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.55f));
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_VEGETABLE)//�G�n(������??)
			{
				SetParticle(pItem[ItemIndex].pos, 40.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.55f));
			}
			else if (pItem[ItemIndex].ItemType == ITEMTYPE_SOUP)//�G�n(������??)
			{
				SetParticle(pItem[ItemIndex].pos, 40.0f, 12, PARTICLETYPE_ITEM, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.55f));
			}
		}
	}
}






//=============================
//�R���g���[���[���͔��f����(�A�C�e��UI)
//=============================
void InPutControllerITEM_UI(int PlayerNum)
{
//	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
//	DWORD dwResult = XInputGetState(PlayerNum, &joykeystate);

	//�J�[�\������
	if (GetJoypadTrigger(JOYKEY_LEFT, PlayerNum) == true)
	{//A�������ꂽ(��)

		if (PlayerNum == 0)
		{
			if (g_PointNum[0] > 0)
			{//�ʏ�
				g_PointNum[0]--;
			}
			else
			{//��ɖ߂�
				g_PointNum[0] = MAXGETITEM - 1;
			}
		}
		else if (PlayerNum == 1)
		{
			if (g_PointNum[1] > 0)
			{//�ʏ�
				g_PointNum[1]--;
			}
			else
			{//��ɖ߂�
				g_PointNum[1] = MAXGETITEM - 1;
			}
		}

	}
	else if (GetJoypadTrigger(JOYKEY_RIGHT, PlayerNum) == true)
	{//D�������ꂽ(�E)
		if (PlayerNum == 0)
		{
			if (g_PointNum[0] < MAXGETITEM - 1)
			{//�ʏ�
				g_PointNum[0]++;
			}
			else
			{//���ɖ߂�
				g_PointNum[0] = 0;
			}
		}
		else if (PlayerNum == 1)
		{
			if (g_PointNum[1] < MAXGETITEM - 1)
			{//�ʏ�
				g_PointNum[1]++;
			}
			else
			{//���ɖ߂�
				g_PointNum[1] = 0;
			}
		}
	}

	//�A�C�e���h���b�v
	if(GetJoypadTrigger(JOYKEY_UP, PlayerNum) == true|| GetJoypadTrigger(JOYKEY_DOWN, PlayerNum) == true)
	{//W�������ꂽ(��.��)
		Camera* pCamera;
		pCamera = GetCamera();

		Player* pPlayer;
		pPlayer = GetPlayer();

		for (int nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
		{
			if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_MAINBODY)
			{//UI�{��
				if (g_ItemUI[nCntItem_UI].PlayerNum == PlayerNum+1)
				{

					if (g_ItemUI[nCntItem_UI].PosNum == g_PointNum[PlayerNum])
					{//�ʒu��v
						View* pViewMtx = GetView();
						View2* pViewMtx2 = GetView_2P();

						D3DXVECTOR3 EscMove;
						D3DXVECTOR3 EscPos2;

						if (PlayerNum == 0)
						{
							EscPos2 = D3DXVECTOR3(pViewMtx[2].ViewPosMtx._41, pViewMtx[2].ViewPosMtx._42, pViewMtx[2].ViewPosMtx._43);
						}
						else if (PlayerNum == 1)
						{
							EscPos2 = D3DXVECTOR3(pViewMtx2[2].ViewPosMtx._41, pViewMtx2[2].ViewPosMtx._42, pViewMtx2[2].ViewPosMtx._43);

						}

						float Xdate = 0.0f;
						float Zdate = 0.0f;

						Zdate = -1.0f;


						float Angle = atan2f(Xdate, Zdate);//���ꂪ���p


						//------�����WW

						EscMove.x = sinf(Angle - pCamera[PlayerNum].rot.y - (1.0f * D3DX_PI)) * ITEMMOVESPEED_UI;//�O�p�֐����p���Ĉړ��̒�������
						EscMove.z = cosf(Angle - pCamera[PlayerNum].rot.y - (1.0f * D3DX_PI)) * ITEMMOVESPEED_UI;//�O�p�֐����p���Ĉړ��̒�������
						EscMove.y = 2.0f;

						SetItem2(EscPos2, EscMove, g_ItemUI[nCntItem_UI].nItemType, 15);


						g_ItemUI[nCntItem_UI].PosNum = -1;//�ꉞ���Z�b�g
						g_ItemUI[nCntItem_UI].bUse = false;

						if (PlayerNum == 0)
						{
					//		Player* pPlayer = GetPlayer();
							if (g_ItemUI[nCntItem_UI].nItemType == ITEMTYPE_DISH)
							{
								pPlayer->nHaveDish--;
							}
							if (g_ItemUI[nCntItem_UI].nItemType == ITEMTYPE_REMOCON)
							{
								pPlayer->nHaveRemocon--;
							}
							if (g_ItemUI[nCntItem_UI].nItemType == ITEMTYPE_VEGETABLE)
							{
								pPlayer->nHaveVegetable--;
							}
							if (g_ItemUI[nCntItem_UI].nItemType == ITEMTYPE_SOUP)
							{
								pPlayer->nHaveSoup--;
							}
							g_ItemNum--;
						}
						else if (PlayerNum == 1)
						{
							Player_2P* pPlayer2 = GetPlayer_2P();
							if (g_ItemUI[nCntItem_UI].nItemType == ITEMTYPE_DISH)
							{
								pPlayer2->nHaveDish--;
							}
							if (g_ItemUI[nCntItem_UI].nItemType == ITEMTYPE_REMOCON)
							{
								pPlayer2->nHaveRemocon--;
							}
							if (g_ItemUI[nCntItem_UI].nItemType == ITEMTYPE_VEGETABLE)
							{
								pPlayer2->nHaveVegetable--;
							}
							if (g_ItemUI[nCntItem_UI].nItemType == ITEMTYPE_SOUP)
							{
								pPlayer2->nHaveSoup--;
							}
							g_ItemNum2--;
						}

						break;
					}
				}
			}
		}


	}
	
	////�A�C�e���g�p
	//if (GetJoypadTrigger(JOYKEY_DOWN, PlayerNum) == true)
	//{//S�������ꂽ(��)
	//	
	//	for (int nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	//	{
	//		if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_MAINBODY)
	//		{//UI�{��
	//			if (g_ItemUI[nCntItem_UI].PlayerNum == PlayerNum+1)
	//			{
	//				if (PlayerNum == 0)
	//				{

	//					if (g_ItemUI[nCntItem_UI].PosNum == g_PointNum[PlayerNum])
	//					{//�ʒu��v
	//						g_ItemUI[nCntItem_UI].PosNum = -1;//�ꉞ���Z�b�g
	//						g_ItemUI[nCntItem_UI].bUse = false;

	//						g_ItemNum--;

	//						break;
	//					}
	//				}
	//				else if (PlayerNum == 1)
	//				{

	//					if (g_ItemUI[nCntItem_UI].PosNum == g_PointNum[PlayerNum])
	//					{//�ʒu��v
	//						g_ItemUI[nCntItem_UI].PosNum = -1;//�ꉞ���Z�b�g
	//						g_ItemUI[nCntItem_UI].bUse = false;

	//						g_ItemNum2--;

	//						break;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}



	
}

//================================================
//�A�C�e���폜�֐�
//================================================
void DeleteItem_UI(int PlayerNum, ITEMTYPE ItemType)
{
	for (int nCntItem_UI = 0; nCntItem_UI < MAXITEMUI; nCntItem_UI++)
	{
		if (g_ItemUI[nCntItem_UI].bUse == true)
		{
			if (g_ItemUI[nCntItem_UI].UItype == ITEM_UI_TYPE_MAINBODY)
			{//UI�{��
				if (g_ItemUI[nCntItem_UI].PlayerNum == PlayerNum + 1)
				{
					if (g_ItemUI[nCntItem_UI].PlayerNum == 1)
					{
						Player* pPlayer = GetPlayer();
						if (g_ItemUI[nCntItem_UI].nItemType == ItemType)
						{
							//g_ItemUI[nCntItem_UI].PosNum = -1;//�ꉞ���Z�b�g
							g_ItemUI[nCntItem_UI].bUse = false;
							g_ItemUI[nCntItem_UI].PosNum = -1;

							if (ItemType == ITEMTYPE_DISH)
							{
								pPlayer->nHaveDish--;
							}
							if (ItemType == ITEMTYPE_VEGETABLE)
							{
								pPlayer->nHaveVegetable--;
							}
							if (ItemType == ITEMTYPE_SOUP)
							{
								pPlayer->nHaveSoup--;
							}
							if (ItemType == ITEMTYPE_REMOCON)
							{
								pPlayer->nHaveRemocon--;
							}
							g_ItemNum--;
							break;
						}
					}
					else if (g_ItemUI[nCntItem_UI].PlayerNum == 2)
					{
						Player_2P* pPlayer2 = GetPlayer_2P();
						if (g_ItemUI[nCntItem_UI].nItemType == ItemType)
						{
							//g_ItemUI[nCntItem_UI].PosNum = -1;//�ꉞ���Z�b�g
							g_ItemUI[nCntItem_UI].bUse = false;
							g_ItemUI[nCntItem_UI].PosNum = -1;

							if (ItemType == ITEMTYPE_DISH)
							{
								pPlayer2->nHaveDish--;
							}
							if (ItemType == ITEMTYPE_VEGETABLE)
							{
								pPlayer2->nHaveVegetable--;
							}
							if (ItemType == ITEMTYPE_SOUP)
							{
								pPlayer2->nHaveSoup--;
							}
							if (ItemType == ITEMTYPE_REMOCON)
							{
								pPlayer2->nHaveRemocon--;
							}
							g_ItemNum2--;
							break;
						}
					}
				}
			}
		}
	}
}
