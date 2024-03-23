//=========================================================
//
//���j���[��ʂ̏����֌W[menu.cpp]
// Author kaito hondo
//
//=========================================================
#include "main.h"
#include "Tutorial.h"
#include "input.h"
#include "game.h"
#include "icon.h"
#include "fade.h"
#include "Film.h"
#include "MenuFrame.h"
#include "menu.h"

#define NUM_ICONTEXTURE	(2)			//���j���[�̃e�N�X�`����
#define NUM_ICONUI		(3)			//���j���[�̕\���|���S���̐�
#define NUM_SELECTUI	(3)			//�I�����̐�
#define MAX_WIDE		(200)		//����
#define MAX_HEIGH		(40)		//�c��
#define MAXICONSIZE		(520.0f)	//�A�C�R���̒[����[�܂ł̍ő�T�C�Y
#define MINICONSIZE		(000.1f)	//�A�C�R���̒[����[�܂ł̍ŏ��T�C�Y
#define ROLLICONSPEED	(040.0f)		//�A�C�R�����I�����ꂽ�Ƃ��̃T�C�Y�ύX�̃X�s�[�h(f/1)

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureIcon[NUM_ICONTEXTURE] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffIcon = NULL;//���_�o�b�t�@�ւ̃|���S��
ICON g_aIcon[NUM_ICONUI];	//���j���[�\���̂̏��

int g_Icon = 0;//���j���[���
bool bMagColorIcon = false;
float fChangeColorIcon = 1.3f;

//=============================
//���j���[����������
//=============================
void InitIcon(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���j���[���̏�����
	g_Icon = START_ICON_GAME;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\IconFrame.png", &g_pTextureIcon[0]);//--------���������ς�//�Ƃ肠����
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\IconSpell.png", &g_pTextureIcon[1]);//--------���������ς�

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_ICONUI, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffIcon, NULL);

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffIcon->Lock(0, 0, (void**)&pVtx, 0);

	int nCountIcon = 0;

	for (nCountIcon = 0; nCountIcon < NUM_ICONUI; nCountIcon++)
	{
		g_aIcon[nCountIcon].pos = D3DXVECTOR3(SCREEN_WIDE / 2, SCREEN_HEIGHT / 2, 0.0f);
		g_aIcon[nCountIcon].texX = MINICONSIZE;
		g_aIcon[nCountIcon].bUse = false;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aIcon[nCountIcon].pos.x - MAX_WIDE, g_aIcon[nCountIcon].pos.y - MAX_HEIGH, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aIcon[nCountIcon].pos.x + MAX_WIDE, g_aIcon[nCountIcon].pos.y - MAX_HEIGH, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aIcon[nCountIcon].pos.x - MAX_WIDE, g_aIcon[nCountIcon].pos.y + MAX_HEIGH, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aIcon[nCountIcon].pos.x + MAX_WIDE, g_aIcon[nCountIcon].pos.y + MAX_HEIGH, 0.0f);

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

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffIcon->Unlock();
}
//=============================
//���j���[�I������
//=============================
void UninitIcon(void)
{
	int nCountIcon = 0;

	for (nCountIcon = 0; nCountIcon < NUM_ICONTEXTURE; nCountIcon++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureIcon[nCountIcon] != NULL)
		{
			g_pTextureIcon[nCountIcon]->Release();
			g_pTextureIcon[nCountIcon] = NULL;
		}
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffIcon != NULL)
		{
			g_pVtxBuffIcon->Release();
			g_pVtxBuffIcon = NULL;
		}
	}
}
//=============================
//���j���[�X�V����
//=============================
void UpdateIcon(void)
{
	XINPUT_STATE joykeystate;

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffIcon->Lock(0, 0, (void**)&pVtx, 0);

	int nCountIcon = 0;

	DWORD dwResult = XInputGetState(0, &joykeystate);

	//if (dwResult == ERROR_SUCCESS)
	//{
	//	//if (GetkeyboardTrigger(DIK_W) == true || GetJoypadTrigger(JOYKEY_UP, 0) == true || GetJoypadTrigger(JOYKEY_UP, 1) == true || joykeystate.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || GetkeyboardTrigger(DIK_UP))
	//	//{//W�������ꂽ(��)
	//	//	if (g_Icon > START_ICON_GAME)
	//	//	{//�Q�[���X�^�[�g�ɓ��B����܂ł̓}�C�i�X����
	//		//	g_Icon--;
	//	//	}
	//	//	else
	//	//	{//�Q�[���X�^�[�g��艺�ɍs�����Ƃ������ԉ�(�^�C�g��)�ɖ߂�
	//	//		g_Icon = START_ICON_TITLE;
	//	//	}

	//	//}
	//	//else if (GetkeyboardTrigger(DIK_S) == true || GetJoypadTrigger(JOYKEY_DOWN, 0) == true || GetJoypadTrigger(JOYKEY_DOWN, 1) == true || joykeystate.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || GetkeyboardTrigger(DIK_DOWN))
	//	//{//S�������ꂽ(��)
	//	//	if (g_Icon < START_ICON_TITLE)
	//	//	{//�^�C�g���ɓ��B����܂Ńv���X����
	//	//		g_Icon++;
	//	//	}
	//	//	else
	//	//	{//�^�C�g������ɍs�����Ƃ������ԏ�(�Q�[���X�^�[�g)�ɖ߂�
	//	//		g_Icon = START_ICON_GAME;
	//	//	}
	//	//}
	//	
	//}
	//else
	//{//�R���g���[���[���Ȃ������Ƃ�
	//	if (GetkeyboardTrigger(DIK_W) == true || GetkeyboardTrigger(DIK_UP))
	//	{//W�������ꂽ(��)
	//		if (g_Icon > START_ICON_GAME)
	//		{
	//			g_Icon--;
	//		}
	//		else
	//		{//�Q�[���X�^�[�g��艺�ɍs�����Ƃ������ԉ�(�^�C�g��)�ɖ߂�
	//			g_Icon = START_ICON_TITLE;
	//		}
	//	}
	//	else if (GetkeyboardTrigger(DIK_S) == true || GetkeyboardTrigger(DIK_DOWN))
	//	{//S�������ꂽ(��)
	//		if (g_Icon < START_ICON_TITLE)
	//		{
	//			g_Icon++;
	//		}
	//		else
	//		{//�^�C�g������ɍs�����Ƃ������ԏ�(�Q�[���X�^�[�g)�ɖ߂�
	//			g_Icon = START_ICON_GAME;
	//		}
	//	}
	//}

	g_Icon = GetMenu1()-1;

	for (nCountIcon = 0; nCountIcon < NUM_ICONUI; nCountIcon++)
	{
		if (nCountIcon == START_ICON_GAME)
		{
			g_aIcon[nCountIcon].pos = D3DXVECTOR3(SCREEN_WIDE * 0.05, SCREEN_HEIGHT / 3.0f, 0.0f);// �����ŕ����̈ʒu�ς���
		}
		else if (nCountIcon == START_ICON_TUTORIAL)
		{
			g_aIcon[nCountIcon].pos = D3DXVECTOR3(SCREEN_WIDE * 0.05, SCREEN_HEIGHT / 1.75f, 0.0f);

		}
		else if (nCountIcon == START_ICON_TITLE)
		{
			g_aIcon[nCountIcon].pos = D3DXVECTOR3(SCREEN_WIDE * 0.05, SCREEN_HEIGHT / 1.23f, 0.0f);
		}

		if (nCountIcon == g_Icon)
		{//�Ώۂ̂Ƃ�
			if (g_aIcon[nCountIcon].texX < MAXICONSIZE - ROLLICONSPEED + 1.0f)
			{
				g_aIcon[nCountIcon].texX += ROLLICONSPEED;
			}

			g_aIcon[nCountIcon].bUse = true;
		}
		else
		{
			g_aIcon[nCountIcon].texX = MINICONSIZE;
			g_aIcon[nCountIcon].bUse = false;
		}

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aIcon[nCountIcon].pos.x,							g_aIcon[nCountIcon].pos.y - (MAX_HEIGH * fChangeColorIcon), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aIcon[nCountIcon].pos.x + g_aIcon[nCountIcon].texX, g_aIcon[nCountIcon].pos.y - (MAX_HEIGH * fChangeColorIcon), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aIcon[nCountIcon].pos.x,							g_aIcon[nCountIcon].pos.y + (MAX_HEIGH * fChangeColorIcon), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aIcon[nCountIcon].pos.x + g_aIcon[nCountIcon].texX, g_aIcon[nCountIcon].pos.y + (MAX_HEIGH * fChangeColorIcon), 0.0f);


		//����L�[(ENTER)�������ꂽ���ǂ���
		if (GetkeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_A, 0) || GetJoypadTrigger(JOYKEY_A, 1) || GetkeyboardTrigger(DIK_RETURN))
		{
			if (g_Icon == START_ICON_GAME)
			{
				SetFade(MODE_GAME);
			}
			else if (g_Icon == START_ICON_TUTORIAL)
			{
				SetFade(MODE_TUTORIAL);
			}
			else if (g_Icon == START_ICON_TITLE)
			{
				SetFade(MODE_TITLE);
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffIcon->Unlock();
}
//=============================
//���j���[�`�揈��
//=============================
void DrawIcon(void)
{

	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();//----------------���������ς�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffIcon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);//-------���������ς�

	int nCountIcon = 0;

	for (nCountIcon = 0; nCountIcon < NUM_ICONUI; nCountIcon++)
	{
		if (g_aIcon[nCountIcon].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureIcon[0]);//---------���������ς�

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��//----------���������ς�
				nCountIcon * 4,//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);//�`�悷��v���~�e�B�u��
		}
	}

	//DrawIconFrame();

	//// �w�i�̕`�揈��
	//DrawFILM();
}

int GetIcon(void)
{
	return g_Icon;
}
