//=============================================
//
//STGtest[gauge.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "gauge.h"
#include "text.h"

//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DTEXTURE9 g_pTextureGauge = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL; //���_�o�b�t�@�ւ̃|�C���^
Gauge g_aGauge[CNT_GAUGE]; //�Q�[�W�̏��

//=============================================
//�Q�[�W�̏���������
//=============================================
void InitGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge.png", &g_pTextureGauge);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * CNT_GAUGE, D3DUSAGE_WRITEONLY, 4, D3DPOOL_MANAGED, &g_pVtxBuffGauge, NULL);

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < CNT_GAUGE; nCnt++)
	{
		g_aGauge[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge[nCnt].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aGauge[nCnt].Length_X = 0.0f;
		g_aGauge[nCnt].Length_Y = 0.0f;
		g_aGauge[nCnt].MaxLength_X = 0.0f;
		g_aGauge[nCnt].type = GAUGETYPE_MAX;
		g_aGauge[nCnt].Cnt_X = 0;
		g_aGauge[nCnt].MaxCnt_X = 0;
		g_aGauge[nCnt].DrawOK = false;
		g_aGauge[nCnt].bUse = false;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x, g_aGauge[nCnt].pos.y - g_aGauge[nCnt].Length_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x - g_aGauge[nCnt].Length_X, g_aGauge[nCnt].pos.y - g_aGauge[nCnt].Length_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x, g_aGauge[nCnt].pos.y + g_aGauge[nCnt].Length_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x - g_aGauge[nCnt].Length_X, g_aGauge[nCnt].pos.y + g_aGauge[nCnt].Length_Y, 0.0f);

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

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffGauge->Unlock();
}

//=============================================
//�Q�[�W�̏I������
//=============================================
void UninitGauge(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureGauge != NULL)
	{
		g_pTextureGauge->Release();
		g_pTextureGauge = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGauge != NULL)
	{
		g_pVtxBuffGauge->Release();
		g_pVtxBuffGauge = NULL;
	}
}

//=============================================
//�Q�[�W�̍X�V����
//=============================================
void UpdateGauge(void)
{
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < CNT_GAUGE; nCnt++)
	{
		if (g_aGauge[nCnt].bUse == true)
		{
			if (g_aGauge[nCnt].type == GAUGETYPE_MAINBODY_1P || g_aGauge[nCnt].type == GAUGETYPE_MAINBODY_2P)
			{//�{��
				//�␳

				float	CorrectionValue = 0.0f;
				if (g_aGauge[nCnt].Cnt_X != 0)
				{
					CorrectionValue = g_aGauge[nCnt].MaxLength_X / (float)g_aGauge[nCnt].MaxCnt_X;//���܂�����߂�
				}

				//�␳��̒���
				g_aGauge[nCnt].Length_X = CorrectionValue * (float)g_aGauge[nCnt].Cnt_X;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x, g_aGauge[nCnt].pos.y - g_aGauge[nCnt].Length_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x + g_aGauge[nCnt].Length_X, g_aGauge[nCnt].pos.y - g_aGauge[nCnt].Length_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x, g_aGauge[nCnt].pos.y + g_aGauge[nCnt].Length_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x + g_aGauge[nCnt].Length_X, g_aGauge[nCnt].pos.y + g_aGauge[nCnt].Length_Y, 0.0f);
			}
			else
			{//�g
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x - FRANE_MAG_X, g_aGauge[nCnt].pos.y - g_aGauge[nCnt].Length_Y - FRANE_MAG_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x + FRANE_MAG_X + g_aGauge[nCnt].MaxLength_X, g_aGauge[nCnt].pos.y - g_aGauge[nCnt].Length_Y - FRANE_MAG_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x - FRANE_MAG_X, g_aGauge[nCnt].pos.y + g_aGauge[nCnt].Length_Y + FRANE_MAG_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aGauge[nCnt].pos.x + FRANE_MAG_X + g_aGauge[nCnt].MaxLength_X, g_aGauge[nCnt].pos.y + g_aGauge[nCnt].Length_Y + FRANE_MAG_Y, 0.0f);
			}
			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aGauge[nCnt].Col;
			pVtx[1].col = g_aGauge[nCnt].Col;
			pVtx[2].col = g_aGauge[nCnt].Col;
			pVtx[3].col = g_aGauge[nCnt].Col;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffGauge->Unlock();
}

//=============================================
//�Q�[�W�̕`�揈��
//=============================================
void DrawGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCnt = 0; nCnt < CNT_GAUGE; nCnt++)
	{
		if (g_aGauge[nCnt].bUse == true)
		{
			if (g_aGauge[nCnt].DrawOK == true)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureGauge);


				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					nCnt * 4,
					2);

				if (g_aGauge[nCnt].type == GAUGETYPE_FRAME_1P || g_aGauge[nCnt].type == GAUGETYPE_FRAME_2P)
				{
					DrawTextSet(D3DXVECTOR3(g_aGauge[nCnt].pos.x - 0.0f, g_aGauge[nCnt].pos.y - 37.0f, 0.0f), 22, FONT_GENSIN, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), "�������Q�[�W");
				}
			}

		}
		g_aGauge[nCnt].DrawOK = false;
	}
}

//=============================================
//�Q�[�W�̐ݒ�|�W�V��������
//=============================================
//-----------------------�ʒu------------�F-----------Y�̒���---------X�l�Ƃ��Ă̍ő�l---X�̍ő�̒���----------------�^�C�v
void SetGauge(D3DXVECTOR3 pos, D3DXCOLOR Col, float Length_Y, int MaxCnt_X, float MaxLength_X, GaugeType type)
{
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < CNT_GAUGE; nCnt++)
	{
		if (g_aGauge[nCnt].bUse == false)
		{
			g_aGauge[nCnt].pos = pos;
			g_aGauge[nCnt].Col = Col;
			g_aGauge[nCnt].Length_Y = Length_Y;
			g_aGauge[nCnt].type = type;
			g_aGauge[nCnt].MaxCnt_X = MaxCnt_X;
			g_aGauge[nCnt].MaxLength_X = MaxLength_X;
			g_aGauge[nCnt].bUse = true;
			g_aGauge[nCnt].DrawOK = false;
			break;
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffGauge->Unlock();
}

//==========================================
//�Q�[�W�̎擾
//==========================================
Gauge* GetGauge(void)
{
	return &g_aGauge[0];
}