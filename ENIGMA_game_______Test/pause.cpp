//=========================================================
//
//�|�[�Y�����̏����֌W[pause.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "input.h"
#include "game.h"
#include "pause.h"
#include "fade.h"
#include "text.h"
#include "sound.h"

#define NUM_PAUSEUI (4)//�|�[�Y�̕\���|���S���̐�
#define NUM_SELECTUI	(3)//�I�����̐�
#define MAX_WIDE				(256)//����
#define MAX_H				(30)//�c��

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePause[NUM_PAUSEUI] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;//���_�o�b�t�@�ւ̃|���S��
PAUSE g_aPause[NUM_PAUSEUI];	//�|�[�Y�\���̂̏��

int g_Pause=0;//�|�[�Y���

bool g_InputLock[2] = {};

//=============================
//�|�[�Y����������
//=============================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

//	int nCntPause = 0;

	//�|�[�Y���̏�����
	g_Pause = PAUSE_MENU_CONTINUE;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pauseframe.png", &g_pTexturePause[0]);//--------���������ς�//�Ƃ肠����
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Pause000.png", &g_pTexturePause[1]);//--------���������ς�
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Pause001.png", &g_pTexturePause[2]);//--------���������ς�
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Pause002.png", &g_pTexturePause[3]);//--------���������ς�

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PAUSEUI, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPause, NULL);

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	int nCountPause = 0;

	for (nCountPause = 0; nCountPause < NUM_PAUSEUI; nCountPause++)
	{
		g_aPause[nCountPause].pos = D3DXVECTOR3(SCREEN_WIDE / 2, SCREEN_HEIGHT / 2, 0.0f);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - MAX_WIDE, g_aPause[nCountPause].pos.y - MAX_H, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + MAX_WIDE, g_aPause[nCountPause].pos.y - MAX_H, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - MAX_WIDE, g_aPause[nCountPause].pos.y + MAX_H, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + MAX_WIDE, g_aPause[nCountPause].pos.y + MAX_H, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 55, 55, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 55, 55, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 55, 55, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 55, 55, 255);

		//�e�L�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
	
	g_InputLock[0] = false;//-����0���j���[�g��+����
	g_InputLock[1] = false;
}
//=============================
//�|�[�Y�I������
//=============================
void UninitPause(void)
{
	int nCountPause = 0;

	for (nCountPause = 0; nCountPause < NUM_PAUSEUI; nCountPause++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturePause[nCountPause] != NULL)
		{
			g_pTexturePause[nCountPause]->Release();
			g_pTexturePause[nCountPause] = NULL;
		}
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffPause != NULL)
		{
			g_pVtxBuffPause->Release();
			g_pVtxBuffPause = NULL;
		}
	}
}
//=============================
//�|�[�Y�X�V����
//=============================
void UpdatePause(void)
{
	XINPUT_STATE joykeystate;

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	int nCountPause = 0;

	DWORD dwResult = XInputGetState(0, &joykeystate);

	

	if (dwResult == ERROR_SUCCESS)
	{
		if (GetkeyboardTrigger(DIK_W) == true || GetJoypadTrigger(JOYKEY_UP,0) == true || GetJoypadTrigger(JOYKEY_UP, 1) == true || GetkeyboardTrigger(DIK_UP))
		{//W�������ꂽ(��)
			PlaySound(SOUND_LABEL_SE_CURSOLMOVE);

			if (g_Pause > PAUSE_MENU_CONTINUE)
			{
				g_Pause--;
			}
		}
		else if (GetkeyboardTrigger(DIK_S) == true || GetJoypadTrigger(JOYKEY_DOWN ,0) == true || GetJoypadTrigger(JOYKEY_DOWN, 1) == true || GetkeyboardTrigger(DIK_DOWN))
		{//S�������ꂽ(��)
			PlaySound(SOUND_LABEL_SE_CURSOLMOVE);

			if (g_Pause < PAUSE_MENU_QUIT)
			{
				g_Pause++;
			}
		}

		for (int i = 0; i < 2; i++)
		{
			dwResult = XInputGetState(i, &joykeystate);
	
			if (joykeystate.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{//W�������ꂽ(��)
				PlaySound(SOUND_LABEL_SE_CURSOLMOVE);

				if (g_InputLock[i] == false)
				{
					g_InputLock[i] = true;
					if (g_Pause > PAUSE_MENU_CONTINUE)
					{
						g_Pause--;
					}
				}

			}
			else if (joykeystate.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{//S�������ꂽ(��)
				PlaySound(SOUND_LABEL_SE_CURSOLMOVE);

				if (g_InputLock[i] == false)
				{
					g_InputLock[i] = true;
					if (g_Pause < PAUSE_MENU_QUIT)
					{
						g_Pause++;
					}
				}
			}
			else
			{
				g_InputLock[i] = false;
			}
			
		}


	}
	else
	{//�R���g���[���[���Ȃ������Ƃ�
		if (GetkeyboardTrigger(DIK_W) == true || GetkeyboardTrigger(DIK_UP))
		{//W�������ꂽ(��)
			if (g_Pause > PAUSE_MENU_CONTINUE)
			{
				g_Pause--;
			}
		}
		else if (GetkeyboardTrigger(DIK_S) == true || GetkeyboardTrigger(DIK_DOWN))
		{//S�������ꂽ(��)
			if (g_Pause < PAUSE_MENU_QUIT)
			{
				g_Pause++;
			}
		}
	}

	for (nCountPause = 0; nCountPause < NUM_PAUSEUI; nCountPause++)
	{

		//���_�J���[�̐ݒ�--�S��
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 240);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 240);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 240);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 240);

		if (nCountPause == 0)
		{
			g_aPause[nCountPause].pos = D3DXVECTOR3(SCREEN_WIDE / 2, SCREEN_HEIGHT / 2, 0.0f);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - (SCREEN_WIDE / 2), g_aPause[nCountPause].pos.y - (SCREEN_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + (SCREEN_WIDE / 2), g_aPause[nCountPause].pos.y - (SCREEN_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - (SCREEN_WIDE / 2), g_aPause[nCountPause].pos.y + (SCREEN_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + (SCREEN_WIDE / 2), g_aPause[nCountPause].pos.y + (SCREEN_HEIGHT / 2), 0.0f);
		}
		else if (nCountPause == PAUSE_MENU_CONTINUE)
		{
			g_aPause[nCountPause].pos = D3DXVECTOR3(SCREEN_WIDE / 2, SCREEN_HEIGHT / 3.5f, 0.0f);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - (MAX_WIDE * 1), g_aPause[nCountPause].pos.y - (MAX_H * 1), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + (MAX_WIDE * 1), g_aPause[nCountPause].pos.y - (MAX_H * 1), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - (MAX_WIDE * 1), g_aPause[nCountPause].pos.y + (MAX_H * 1), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + (MAX_WIDE * 1), g_aPause[nCountPause].pos.y + (MAX_H * 1), 0.0f);
		}
		else if (nCountPause == PAUSE_MENU_RETRY)
		{
			g_aPause[nCountPause].pos = D3DXVECTOR3(SCREEN_WIDE / 2, SCREEN_HEIGHT / 2.4f, 0.0f);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - (MAX_WIDE * 1), g_aPause[nCountPause].pos.y - (MAX_H * 1), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + (MAX_WIDE * 1), g_aPause[nCountPause].pos.y - (MAX_H * 1), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - (MAX_WIDE * 1), g_aPause[nCountPause].pos.y + (MAX_H * 1), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + (MAX_WIDE * 1), g_aPause[nCountPause].pos.y + (MAX_H * 1), 0.0f);
		}
		else if (nCountPause == PAUSE_MENU_QUIT)
		{
			g_aPause[nCountPause].pos = D3DXVECTOR3(SCREEN_WIDE / 2, SCREEN_HEIGHT / 1.8f, 0.0f);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - (MAX_WIDE * 1), g_aPause[nCountPause].pos.y - (MAX_H * 1), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + (MAX_WIDE * 1), g_aPause[nCountPause].pos.y - (MAX_H * 1), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - (MAX_WIDE * 1), g_aPause[nCountPause].pos.y + (MAX_H * 1), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + (MAX_WIDE * 1), g_aPause[nCountPause].pos.y + (MAX_H * 1), 0.0f);
		}

		if (nCountPause == g_Pause)
		{//�Ώۂ̂Ƃ�
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 55, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 55, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 55, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 55, 255, 255);
		}

		//����L�[(ENTER)�������ꂽ���ǂ���
		if (GetkeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_A,0) || GetJoypadTrigger(JOYKEY_A, 1) || GetkeyboardTrigger(DIK_RETURN))
		{
			PlaySound(SOUND_LABEL_SE_DECISION);

			if (g_Pause == PAUSE_MENU_CONTINUE)
			{
				ReleasePause();
			}
			else if (g_Pause == PAUSE_MENU_RETRY)
			{
				SetFade(MODE_GAME);
			}
			else if (g_Pause == PAUSE_MENU_QUIT)
			{
				SetFade(MODE_TITLE);
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}
//=============================
//�|�[�Y�`�揈��
//=============================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();//----------------���������ς�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);//-------���������ς�
	
	int nCountPause = 0;

	for (nCountPause = 0; nCountPause < NUM_PAUSEUI; nCountPause++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePause[nCountPause]);//---------���������ς�

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��//----------���������ς�
			nCountPause *4,//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);//�`�悷��v���~�e�B�u��

		
		
	}
	if (g_Pause == PAUSE_MENU_CONTINUE)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.8f, SCREEN_HEIGHT / 1.3f, 0.0f), 60, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "�Q�[���ɖ߂�");
	}
	else if (g_Pause == PAUSE_MENU_RETRY)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.8f, SCREEN_HEIGHT / 1.3f, 0.0f), 60, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "�ŏ�����v���C");
	}
	else if (g_Pause == PAUSE_MENU_QUIT)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.8f, SCREEN_HEIGHT / 1.3f, 0.0f), 60, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "�^�C�g���ɖ߂�");
	}
//�e�N�X�`����߂�
		pDevice->SetTexture(0, NULL);
}
