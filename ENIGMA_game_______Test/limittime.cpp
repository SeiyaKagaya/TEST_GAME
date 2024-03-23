//============================================================================================
//
//�^�C�����~�b�g��\�����鏈��[limittime.cpp]
// Author seiya kagaya
//
//============================================================================================
#include"limittime.h"
#include "game.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureLimitTime = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLimitTime = NULL;//���_�o�b�t�@�ւ̃|���S��
LimitTime g_aLimitTime[LIMITTIME_NUM];//�^�C�����~�b�g�̏��
NowTime g_Nowtime;//���݂̎c�莞�Ԃ��i�[
D3DXVECTOR3 g_posLimitTime;//�^�C�����~�b�g�̈ʒu

//�^�C�����~�b�g�̒l��錾
int g_nLimitTimeScore = 0;//�^�C�����~�b�g�̒l�i�O���[�o���Ō��݂̃^�C�����~�b�g���Z�l���i�[�j

//�^�C�����~�b�g�̒l��錾
int g_nLimitTime=0;
//Looop�J�E���g
int g_nLimitCnt = 0;


//=============================
//�^�C�����~�b�g�̏���������
//=============================
void InitLimitTime(void)
{
	//�^�C�����~�b�g�̒l����
	 g_nLimitTimeScore = g_Nowtime.NowTime;//�^�C�����~�b�g�̒l�i�O���[�o���Ō��݂̃^�C�����~�b�g���Z�l���i�[�j

	 g_nLimitTime = g_Nowtime.NowTime;

	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	int nCntLimitTime;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number000.png", &g_pTextureLimitTime);//--------���������ς�

	g_posLimitTime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu������

	//�^�C�����~�b�g�̏��̏�����(�����鏉���n�_)
	for (nCntLimitTime = 0; nCntLimitTime < LIMITTIME_NUM; nCntLimitTime++)
	{
		g_aLimitTime[nCntLimitTime].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLimitTime[nCntLimitTime].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLimitTime[nCntLimitTime].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * LIMITTIME_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffLimitTime, NULL);

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLimitTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLimitTime = 0; nCntLimitTime < LIMITTIME_NUM; nCntLimitTime++)
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
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 225, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W��ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / LIMITTIME_DIVISIONUMBER);//����
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f / LIMITTIME_DIVISIONUMBER);//�E��

		pVtx += 4;//���_�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLimitTime->Unlock();

	//�\���ꏊ�̐ݒ�
	for (int SetCnt = 0; SetCnt <= LIMITTIME_NUM; SetCnt++)
	{
		SetUpLimitTime(D3DXVECTOR3(SCREEN_WIDE - 600.0f - (LIMITTIMEPOS_SPAN * SetCnt), SCREEN_HEIGHT - 700.0f, 0), 0);//�P��//------------8��
	}

}
//=============================
//�^�C�����~�b�g�̏I������
//=============================
void UninitLimitTime(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureLimitTime != NULL)
	{
		g_pTextureLimitTime->Release();
		g_pTextureLimitTime = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLimitTime != NULL)
	{
		g_pVtxBuffLimitTime->Release();
		g_pVtxBuffLimitTime = NULL;
	}
}
//=============================
//�^�C�����~�b�g�̍X�V����
//=============================
void UpdateLimitTime(void)
{
	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLimitTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLimitTime = 0; nCntLimitTime < LIMITTIME_NUM; nCntLimitTime++)
	{
		if (g_nLimitTimeScore < ((ENDFRAME / 60) / 3))
		{//�c��3���̂P

			pVtx[0].col = D3DCOLOR_RGBA(255, 55, 55, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 55, 55, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 25, 25, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 25, 25, 255);
		}
		else if (g_nLimitTimeScore < ((ENDFRAME/60) / 2))
		{//�����؂���
			pVtx[0].col = D3DCOLOR_RGBA(255, 241, 55, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 241, 55, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 241, 25, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 241, 25, 255);
		}
		else
		{//�ʏ펞

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		pVtx += 4;//���_�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLimitTime->Unlock();
}
//=============================
//�^�C�����~�b�g�̕`�揈��
//=============================
void DrawLimitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	int nCntLimitTime=0;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLimitTime, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);//-------���������ς�

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureLimitTime);//---------���������ς�

	for (nCntLimitTime = 0; nCntLimitTime < LIMITTIME_NUM; nCntLimitTime++)
	{
		if (g_aLimitTime[nCntLimitTime].bUse == true)
		{//�^�C�����~�b�g���g�p����Ă���
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				nCntLimitTime * 4,//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);//�`�悷��v���~�e�B�u��

			
			
		}
	}
//�e�N�X�`����߂�
			pDevice->SetTexture(0, NULL);
}
//=============================
//�^�C�����~�b�g�̐ݒ菈��
//=============================
void SetUpLimitTime(D3DXVECTOR3 pos, int nLimitTime)
{//���̂Ƃ���ł��Ăԉ\��������̂ł��̂܂܂̂ق����֗�

	VERTEX_2D* pVtx;//���_���̃|�C���^

	int nCntLimitTime = 0;//�Ƃ�܌Œ�i�������Ɠ��`�j

	int aPosTexU[LIMITTIME_NUM];//�e�s�̐��l���i�[

	int nESCdata=0;//�ꎞ���p�̕ϐ�

	g_nLimitCnt++;//�C���N�������g

	if (g_nLimitCnt % 60 == 0)
	{

		g_nLimitTimeScore--;//�\�����鐔�l�����炷
	}

	nLimitTime = g_nLimitTimeScore;//�ꎞ���

	for (nCntLimitTime = 0; nCntLimitTime < LIMITTIME_NUM; nCntLimitTime++)//�����΂炵�Ċe�s�̐��l����//-------------------�����l�Z�o��add�̐��l���Z�����������Ă�
	{
		nESCdata = g_nLimitTimeScore % 10;//��]�Z�ł̂��܂�(��ԉ��̒l���擾)
		g_nLimitTimeScore /= 10;//�{�̂�10�Ŋ�������(��ԉ��̒l����)
		aPosTexU[nCntLimitTime] = nESCdata;//��ԉ��̒l����
	}

	g_nLimitTimeScore = nLimitTime;//�o������Ă��܂����̂ł��Ƃɖ߂�

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLimitTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLimitTime = 0; nCntLimitTime < LIMITTIME_NUM; nCntLimitTime++)
	{
		if (g_aLimitTime[nCntLimitTime].bUse == false)
		{//�^�C�����~�b�g���g�p����Ă��Ȃ�

			g_aLimitTime[nCntLimitTime].bUse = true;//�g�p���Ă�ɂ���

			g_aLimitTime[nCntLimitTime].pos = pos;

			//���_���W�̍X�V-----------------------------------
			pVtx[0].pos = D3DXVECTOR3(g_aLimitTime[nCntLimitTime].pos.x - LIMITTIME_POSX, g_aLimitTime[nCntLimitTime].pos.y - LIMITTIME_POSY, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLimitTime[nCntLimitTime].pos.x + LIMITTIME_POSX, g_aLimitTime[nCntLimitTime].pos.y - LIMITTIME_POSY, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLimitTime[nCntLimitTime].pos.x - LIMITTIME_POSX, g_aLimitTime[nCntLimitTime].pos.y + LIMITTIME_POSY, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLimitTime[nCntLimitTime].pos.x + LIMITTIME_POSX, g_aLimitTime[nCntLimitTime].pos.y + LIMITTIME_POSY, 0.0f);

			for (int nCntCheck = 0; nCntCheck < LIMITTIME_NUM; nCntCheck++)
			{
				//�e�N�X�`�����W��ݒ�//�����ɋꗶ�B�v���K
				pVtx[0].tex = D3DXVECTOR2((1.0f / LIMITTIME_DIVISIONUMBER) * aPosTexU[nCntCheck], 0.0f);//����
				pVtx[1].tex = D3DXVECTOR2((1.0f / LIMITTIME_DIVISIONUMBER) * aPosTexU[nCntCheck] + (1.0f / LIMITTIME_DIVISIONUMBER), 0.0f);//�E��
				pVtx[2].tex = D3DXVECTOR2((1.0f / LIMITTIME_DIVISIONUMBER) * aPosTexU[nCntCheck], 1.0f);//����
				pVtx[3].tex = D3DXVECTOR2((1.0f / LIMITTIME_DIVISIONUMBER) * aPosTexU[nCntCheck] + (1.0f / LIMITTIME_DIVISIONUMBER), 1.0f);//�E��
			}
			break;
		}
		pVtx += 4;//�|�C���^���S�i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLimitTime->Unlock();
}
//=============================
//�^�C�����~�b�g���Z����
//=============================
void SubLimitTime(void)
{
	VERTEX_2D* pVtx;//���_���̃|�C���^

	int paPosTexU[LIMITTIME_NUM] = {};//�e�s�̐��l���i�[
	int nESCdata=0;//�ꎞ���p�̕ϐ�
	int nLimitTime=0;//���v�^�C�����~�b�g�ꎞ���

	g_nLimitCnt++;//�C���N�������g

	if (g_nLimitCnt % 60 == 0)
	{
		g_nLimitTimeScore--;//�\�����鐔�l�����炷
	}

	nLimitTime = g_nLimitTimeScore;//�ꎞ���

	for (int nCntLimitTime = 0; nCntLimitTime < LIMITTIME_NUM; nCntLimitTime++)//�����΂炵�Ċe�s�̐��l����
	{
		nESCdata = g_nLimitTimeScore % 10;//��]�Z�ł̂��܂�(��ԉ��̒l���擾)
		g_nLimitTimeScore /= 10;//�{�̂�10�Ŋ�������(��ԉ��̒l����)
		paPosTexU[nCntLimitTime] = nESCdata;//��ԉ��̒l����
	}

	g_nLimitTimeScore = nLimitTime;//�o������Ă��܂����̂ł��Ƃɖ߂�

	g_Nowtime.NowTime = g_nLimitTimeScore;//�������ɂ��R�s�[���Ƃ�

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLimitTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCheck = 0; nCntCheck < LIMITTIME_NUM; nCntCheck++)
	{
		//�e�N�X�`�����W��ݒ�//�����ɋꗶ�B�v���K
		pVtx[0].tex = D3DXVECTOR2((1.0f / LIMITTIME_DIVISIONUMBER) * paPosTexU[nCntCheck], 0.0f);//����
		pVtx[1].tex = D3DXVECTOR2((1.0f / LIMITTIME_DIVISIONUMBER) * paPosTexU[nCntCheck] + (1.0f / LIMITTIME_DIVISIONUMBER), 0.0f);//�E��
		pVtx[2].tex = D3DXVECTOR2((1.0f / LIMITTIME_DIVISIONUMBER) * paPosTexU[nCntCheck], 1.0f);//����
		pVtx[3].tex = D3DXVECTOR2((1.0f / LIMITTIME_DIVISIONUMBER) * paPosTexU[nCntCheck] + (1.0f / LIMITTIME_DIVISIONUMBER), 1.0f);//�E��

		pVtx += 4;//�|�C���^���S�i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLimitTime->Unlock();
}
//=============================
//���݂̎��Ԏ擾����
//=============================
NowTime* GetNowTime(void)
{
	return &g_Nowtime;
}
