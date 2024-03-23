//=========================================================
//
//�|�[�Y��ʂŎg���ϐ��A�錾�A�\����[moneyboxdigit.cpp]
// Author matsuda towa
//
//=========================================================
#include "moneyboxdigit.h"
#include "moneybox.h"
#include "password.h"
#include "input.h"
#include "model.h"
#include "keyinfo.h"
#include "Actionzone.h"
#include "speechbubble.h"
#include "sound.h"
#include "player.h"
#include "player2.h"
//=========================================================
//�O���[�o���ϐ�
//=========================================================
LPDIRECT3DTEXTURE9 g_pTextureMoneyboxDigit[NUM_DIGIT] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMoneyboxDigit = NULL;//���_�o�b�t�@�ւ̃|���S��
MONEYBOXDIGIT g_aMoneyboxDigit[NUM_DIGIT];	//�|�[�Y�\���̂̏��
int g_nSelectNumber;						//�I�����Ă鐔��
int g_nMark; //�I�����Ă�}�[�N
bool g_bClear; //�N���A�������̔���
bool g_Open = false;//������������
int g_CloseCnt = 140;//��ʕ���܂ł̗P�\

//=============================================
//�ǂ̃e�N�X�`���̎��
//=============================================
static const char* MONEYBOXDIGIT_TEX_NAME[NUM_DIGIT] =
{
	"data\\TEXTURE\\dial000.png",
	"data\\TEXTURE\\dial001.png",
	"data\\TEXTURE\\dial002.png",
	"data\\TEXTURE\\dial003.png",
};

//=========================================================
//������
//=========================================================
void InitMoneyboxDigit(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	g_Open = false;
	g_CloseCnt = 100;
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			MONEYBOXDIGIT_TEX_NAME[nCnt],
			&g_pTextureMoneyboxDigit[nCnt]
		);
	}

	g_nSelectNumber = 0; //�I�����Ă�ԍ��̏�����
	g_nMark = 0;//�I�����Ă�ԍ��̏�����
	g_bClear = false;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_DIGIT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMoneyboxDigit, NULL);

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMoneyboxDigit->Lock(0, 0, (void**)&pVtx, 0);

	int nCnt = 0;

	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		g_aMoneyboxDigit[nCnt].pos = D3DXVECTOR3(SCREEN_WIDE / 4.0f, (SCREEN_HEIGHT / 1.25f), 0.0f);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x - SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x + SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x - SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x + SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);

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

		//�e�L�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMoneyboxDigit->Unlock();
}

//=========================================================
//�I��
//=========================================================
void UninitMoneyboxDigit(void)
{
	int nCnt = 0;

	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureMoneyboxDigit[nCnt] != NULL)
		{
			g_pTextureMoneyboxDigit[nCnt]->Release();
			g_pTextureMoneyboxDigit[nCnt] = NULL;
		}
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffMoneyboxDigit != NULL)
		{
			g_pVtxBuffMoneyboxDigit->Release();
			g_pVtxBuffMoneyboxDigit = NULL;
		}
	}
}

//=========================================================
//�X�V
//=========================================================
void UpdateMoneyboxDigit(void)
{
	MONEYBOX* pMoneybox = GetMoneybox();

	if (pMoneybox->WhichPlayer == false)
	{
		ControlMoneybox1P();
	}
	else if (pMoneybox->WhichPlayer == true)
	{
		ControlMoneybox2P();
	}





}

//=========================================================
//1P�̑���
//=========================================================
void ControlMoneybox1P(void)
{
	XINPUT_STATE joykeystate;

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMoneyboxDigit->Lock(0, 0, (void**)&pVtx, 0);

//	int nCountPause = 0;

	DWORD dwResult = XInputGetState(0, &joykeystate);

	if (dwResult == ERROR_SUCCESS)
	{
		if (GetkeyboardTrigger(DIK_A) == true || GetJoypadTrigger(JOYKEY_LEFT, 0) == true || GetkeyboardTrigger(DIK_LEFT))
		{//A�������ꂽ(��)
			g_nSelectNumber--;
			if (g_nSelectNumber < 0)
			{
				g_nSelectNumber = NUM_DIGIT - 1;
			}

		}
		else if (GetkeyboardTrigger(DIK_D) == true || GetJoypadTrigger(JOYKEY_RIGHT, 0) == true || GetkeyboardTrigger(DIK_RIGHT))
		{//D�������ꂽ(��)

			g_nSelectNumber++;
			if (g_nSelectNumber >= NUM_DIGIT)
			{
				g_nSelectNumber = 0;
			}
		}
	}
	else
	{//�R���g���[���[���Ȃ������Ƃ�
		if (GetkeyboardTrigger(DIK_A) == true || GetkeyboardTrigger(DIK_LEFT))
		{//A�������ꂽ(��)
			g_nSelectNumber--;
			if (g_nSelectNumber < 0)
			{
				g_nSelectNumber = NUM_DIGIT - 1;
			}

		}
		else if (GetkeyboardTrigger(DIK_D) == true || GetkeyboardTrigger(DIK_RIGHT))
		{//D�������ꂽ(��)
			g_nSelectNumber++;
			if (g_nSelectNumber >= NUM_DIGIT)
			{
				g_nSelectNumber = 0;
			}
		}
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (g_nSelectNumber == 0)
		{
			if (nCnt == 0)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
			}
		}
		else if (g_nSelectNumber == 1)
		{
			if (nCnt == 1)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
			}

		}
		else if (g_nSelectNumber == 2)
		{
			if (nCnt == 2)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
			}
		}
		else if (g_nSelectNumber == 3)
		{
			if (nCnt == 3)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
			}
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMoneyboxDigit->Unlock();

	ChangePassword1P(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_nSelectNumber);
}

//=========================================================
//2P�̑���
//=========================================================
void ControlMoneybox2P(void)
{
	XINPUT_STATE joykeystate;

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMoneyboxDigit->Lock(0, 0, (void**)&pVtx, 0);

//	int nCountPause = 0;

	DWORD dwResult = XInputGetState(0, &joykeystate);

	if (dwResult == ERROR_SUCCESS)
	{
		if (GetkeyboardTrigger(DIK_A) == true || GetJoypadTrigger(JOYKEY_LEFT, 1) == true || GetkeyboardTrigger(DIK_LEFT))
		{//A�������ꂽ(��)
			g_nSelectNumber--;
			if (g_nSelectNumber < 0)
			{
				g_nSelectNumber = NUM_DIGIT - 1;
			}

		}
		else if (GetkeyboardTrigger(DIK_D) == true || GetJoypadTrigger(JOYKEY_RIGHT, 1) == true || GetkeyboardTrigger(DIK_RIGHT))
		{//D�������ꂽ(��)

			g_nSelectNumber++;
			if (g_nSelectNumber >= NUM_DIGIT)
			{
				g_nSelectNumber = 0;
			}
		}
	}
	else
	{//�R���g���[���[���Ȃ������Ƃ�
		if (GetkeyboardTrigger(DIK_A) == true || GetkeyboardTrigger(DIK_LEFT))
		{//A�������ꂽ(��)
			g_nSelectNumber--;
			if (g_nSelectNumber < 0)
			{
				g_nSelectNumber = NUM_DIGIT - 1;
			}

		}
		else if (GetkeyboardTrigger(DIK_D) == true || GetkeyboardTrigger(DIK_RIGHT))
		{//D�������ꂽ(��)
			g_nSelectNumber++;
			if (g_nSelectNumber >= NUM_DIGIT)
			{
				g_nSelectNumber = 0;
			}
		}
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (g_nSelectNumber == 0)
		{
			if (nCnt == 0)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
			}
		}
		else if (g_nSelectNumber == 1)
		{
			if (nCnt == 1)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
			}

		}
		else if (g_nSelectNumber == 2)
		{
			if (nCnt == 2)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
			}
		}
		else if (g_nSelectNumber == 3)
		{
			if (nCnt == 3)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
			}
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMoneyboxDigit->Unlock();

	ChangePassword2P(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_nSelectNumber);
}

//=========================================================
//�`��
//=========================================================
void DrawMoneyboxDigit(void)
{

	//���Ⴀ�Ȃ��ł���
	if (g_Open == true)
	{
		if (g_CloseCnt > 0)
		{
			g_CloseCnt--;
		}

		if (g_CloseCnt <= 0)
		{//�P�\�߂���
			Player* pPlayer;
			pPlayer = GetPlayer();

			Player_2P* pPlayer2;
			pPlayer2 = GetPlayer_2P();

			pPlayer->bMoneyBoxGimmick = false;
			pPlayer2->bMoneyBoxGimmick = false;
		}
	}


	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();//----------------���������ς�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMoneyboxDigit, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);//-------���������ς�

	int nCnt = 0;

	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMoneyboxDigit[nCnt]);//---------���������ς�

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��//----------���������ς�
			nCnt * 4,//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);//�`�悷��v���~�e�B�u��

		
		//�e�N�X�`����߂�
		pDevice->SetTexture(0, NULL);
	}
}

//=========================================================
//�ǂ��������삵�Ă�̂��̐ݒ�
//=========================================================
void SetMoneyboxDigit(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	MONEYBOX* pMoneybox = GetMoneybox();

	if (pMoneybox->WhichPlayer == false)
	{//1P�̎�
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_DIGIT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMoneyboxDigit, NULL);

		VERTEX_2D* pVtx;//���_���̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffMoneyboxDigit->Lock(0, 0, (void**)&pVtx, 0);

		int nCnt = 0;

		for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
		{
			g_aMoneyboxDigit[nCnt].pos = D3DXVECTOR3(SCREEN_WIDE / 4.0f + 53.0f, (SCREEN_HEIGHT / 1.25f), 0.0f);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x - SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x + SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x - SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x + SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);

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

			//�e�L�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffMoneyboxDigit->Unlock();
	}
	else if (pMoneybox->WhichPlayer == true)
	{//2P�̎�
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_DIGIT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMoneyboxDigit, NULL);

		VERTEX_2D* pVtx;//���_���̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffMoneyboxDigit->Lock(0, 0, (void**)&pVtx, 0);

		int nCnt = 0;

		for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
		{
			g_aMoneyboxDigit[nCnt].pos = D3DXVECTOR3(SCREEN_WIDE / 1.3f + 53.0f, (SCREEN_HEIGHT / 1.25f), 0.0f);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x - SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x + SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x - SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x + SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);

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

			//�e�L�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffMoneyboxDigit->Unlock();
	}

}

//=========================================================
//��������
//=========================================================
void CorrectMoneyboxDigit(void)
{

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMoneyboxDigit->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx += 4;
	}

	//�����ŃA�C�e���l������
	SetModel(D3DXVECTOR3(-700.0f, 70.0f, -450.0f),
	D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
	MODELTYPE_KEY2);

	SetKeyinfo(SPAWNPLACE_BASEMENT, -1);

	PlaySound(SOUND_LABEL_SE_OPEN);

	//�N���A������������Ă������ɂɐG����Ȃ��悤�ɂ���
	g_bClear = true;

	g_pVtxBuffMoneyboxDigit->Unlock();


	ACTIONZONE* pActionZone;
	pActionZone = GetActionZone();
	SPEECHBUBBLE* pSpeachBubble = GetSpeechBubble();

	for (int nCntZone = 0; nCntZone < MAXZONE; nCntZone++)
	{
		if (pActionZone[nCntZone].bUse == true)
		{
			if (pActionZone[nCntZone].ActionType == ACTION_TYPE_MONEYBOX)
			{
				pActionZone[nCntZone].bUse = false;
				pSpeachBubble[nCntZone].bUse = false;
				pSpeachBubble[nCntZone].bOK = false;			//	break;
				break;
			}
		}
	}
	g_Open = true;
}

//=========================================================
//���s����
//=========================================================
void MistakeMoneyboxDigit(void)
{
	//SE�ŕs������\��
	PlaySound(SOUND_LABEL_SE_NOTOPEN);
}

//=========================================================
//�N���A���擾
//=========================================================
bool GetClearMoneyBox(void)
{
	return g_bClear;
}

