//=========================================================
//
//�|�[�Y��ʂŎg���ϐ��A�錾�A�\����[moneybox.cpp]
// Author matsuda towa
//
//=========================================================
#include "moneybox.h"
#include "moneyboxdigit.h"
#include "password.h"
#include "text.h"

//=========================================================
//�O���[�o���ϐ�
//=========================================================
LPDIRECT3DTEXTURE9 g_pTextureMoneybox = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMoneybox = NULL;//���_�o�b�t�@�ւ̃|���S��
MONEYBOX g_Moneybox;	//�|�[�Y�\���̂̏��
//=============================================
//�ǂ̃e�N�X�`���̎��
//=============================================
static const char* MONEYBOX_TEX_NAME =
{
	"data\\TEXTURE\\safe000.png",
};

//=========================================================
//������
//=========================================================
void InitMoneybox(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

//�f�o�C�X�̎擾
	pDevice = GetDevice();

//	int nCntPause = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		MONEYBOX_TEX_NAME,
		&g_pTextureMoneybox
	);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMoneybox, NULL);

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMoneybox->Lock(0, 0, (void**)&pVtx, 0);

	g_Moneybox.pos = D3DXVECTOR3(SCREEN_WIDE / 4.0f, (SCREEN_HEIGHT/1.25f), 0.0f);
	g_Moneybox.WhichPlayer = false; //false:1P,true2P

	//���_���W�̐ݒ�

	pVtx[0].pos = D3DXVECTOR3(g_Moneybox.pos.x - SCREEN_WIDE/5.0f, g_Moneybox.pos.y - SCREEN_HEIGHT/5.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Moneybox.pos.x + SCREEN_WIDE/5.0f, g_Moneybox.pos.y - SCREEN_HEIGHT/5.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Moneybox.pos.x - SCREEN_WIDE/5.0f, g_Moneybox.pos.y + SCREEN_HEIGHT/5.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Moneybox.pos.x + SCREEN_WIDE/5.0f, g_Moneybox.pos.y + SCREEN_HEIGHT/5.0f, 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�L�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffMoneybox->Unlock();
}

//=========================================================
//�I��
//=========================================================
void UninitMoneybox(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMoneybox != NULL)
	{
		g_pTextureMoneybox->Release();
		g_pTextureMoneybox = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMoneybox != NULL)
	{
		g_pVtxBuffMoneybox->Release();
		g_pVtxBuffMoneybox = NULL;
	}
}

//=========================================================
//�X�V
//=========================================================
void UpdateMoneybox(void)
{
}
//=========================================================
//�`��
//=========================================================
void DrawMoneybox(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();//----------------���������ς�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMoneybox, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);//-------���������ς�

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMoneybox);//---------���������ς�

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��//----------���������ς�
		0,//�`�悷��ŏ��̒��_�C���f�b�N�X
		2);//�`�悷��v���~�e�B�u��
	
	
	//�e�N�X�`����߂�
	pDevice->SetTexture(0, NULL);

	if (g_Moneybox.WhichPlayer == false)
	{//1P�̎�
		DrawTextSet(D3DXVECTOR3(g_Moneybox.pos.x-365.0f, g_Moneybox.pos.y + 100.0f,0.0f), 21, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), "A�{�^��:����");
	}
	else if (g_Moneybox.WhichPlayer == true)
	{//2P�̎�
		DrawTextSet(D3DXVECTOR3(g_Moneybox.pos.x-265.0f, g_Moneybox.pos.y + 100.0f, 0.0f), 21, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), "A�{�^��:����");
	}
}

//=========================================================
//�ǂ��������삵�Ă�̂��̐ݒ�
//=========================================================
void SetMonetbox(bool MoneyboxPlayer)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	g_Moneybox.WhichPlayer = MoneyboxPlayer;
	if (g_Moneybox.WhichPlayer == false)
	{//1P�̎�
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMoneybox, NULL);

		VERTEX_2D* pVtx;//���_���̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffMoneybox->Lock(0, 0, (void**)&pVtx, 0);

		g_Moneybox.pos = D3DXVECTOR3(SCREEN_WIDE / 4.0f + 53.0f, (SCREEN_HEIGHT / 1.25f), 0.0f);
		//���_���W�̐ݒ�

		pVtx[0].pos = D3DXVECTOR3(g_Moneybox.pos.x - SCREEN_WIDE / 5.0f, g_Moneybox.pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Moneybox.pos.x + SCREEN_WIDE / 5.0f, g_Moneybox.pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Moneybox.pos.x - SCREEN_WIDE / 5.0f, g_Moneybox.pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Moneybox.pos.x + SCREEN_WIDE / 5.0f, g_Moneybox.pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�L�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_pVtxBuffMoneybox->Unlock();
	}
	else if (g_Moneybox.WhichPlayer == true)
	{//1P�̎�
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMoneybox, NULL);

		VERTEX_2D* pVtx;//���_���̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffMoneybox->Lock(0, 0, (void**)&pVtx, 0);

		g_Moneybox.pos = D3DXVECTOR3(SCREEN_WIDE/1.3f + 53.0f, (SCREEN_HEIGHT / 1.25f), 0.0f);
		//���_���W�̐ݒ�

		pVtx[0].pos = D3DXVECTOR3(g_Moneybox.pos.x - SCREEN_WIDE / 5.0f , g_Moneybox.pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Moneybox.pos.x + SCREEN_WIDE / 5.0f , g_Moneybox.pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Moneybox.pos.x - SCREEN_WIDE / 5.0f , g_Moneybox.pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Moneybox.pos.x + SCREEN_WIDE / 5.0f , g_Moneybox.pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�L�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_pVtxBuffMoneybox->Unlock();
	}
	SetMoneyboxDigit();
	SetPassword();
}

//=========================================================
//���ɂ̏��擾
//=========================================================
MONEYBOX* GetMoneybox(void)
{
	return &g_Moneybox;
}
