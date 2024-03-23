//=========================================================
//
//�����o��UI��\�����鏈��[speechbubble.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "game.h"
#include "speechbubble.h"


//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSpeechBubble = NULL; //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureSpeechBubble[TEXNUM] = {};       //�e�N�X�`���ւ̃|�C���^



//D3DXVECTOR3 g_SpeechBubble[nSpeechBubble].posSpeechBubble;	//�ʒu
//D3DXVECTOR3 g_SpeechBubble[nSpeechBubble].rotSpeechBubble;	//����
//D3DXMATRIX g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble;//���[���h�}�g���b�N�X


SPEECHBUBBLE g_SpeechBubble[NUMSPEECHBUBBLE];//���쒆�@�\����


int g_nldShadow3 = -1;


//=============================
//�����o��UI�̏���������
//=============================
void InitSpeechBubble(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UI000.png", &g_pTextureSpeechBubble[0]);//�ړ�
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UI001.png", &g_pTextureSpeechBubble[1]);//����
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UI002.png", &g_pTextureSpeechBubble[2]);//�擾
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UI003.png", &g_pTextureSpeechBubble[3]);//������
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UI005.png", &g_pTextureSpeechBubble[4]);//�E�o
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UI004.png", &g_pTextureSpeechBubble[5]);//�؂�ւ�
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * NUMSPEECHBUBBLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffSpeechBubble, NULL);

	VERTEX_3D* pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSpeechBubble->Lock(0, 0, (void**)&pVtx, 0);

	for (int nSpeechBubble = 0; nSpeechBubble < NUMSPEECHBUBBLE; nSpeechBubble++)
	{
	
		g_SpeechBubble[nSpeechBubble].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_SpeechBubble[nSpeechBubble].bUse = false;

		g_SpeechBubble[nSpeechBubble].nBubbleCnt = 0;
		g_SpeechBubble[nSpeechBubble].bOK = false;
		g_SpeechBubble[nSpeechBubble].bTrackingPlayer1=false;
		g_SpeechBubble[nSpeechBubble].bTrackingPlayer2=false;

		g_SpeechBubble[nSpeechBubble].BubbleSType = SPEECHBUBBLETYPE_MAX;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-0.0f, -0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, -0.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);

		//�e�N�X�`�����W��ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��

		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffSpeechBubble->Unlock();


}
//=============================
//�����o��UI�̏I������
//=============================
void UninitSpeechBubble(void)
{
	//StopSound(SOUND_LABEL_SE_SHOT);
	//StopSound(SOUND_LABEL_SE_EXPLOSIONBOMB);
	for (int i = 0; i < TEXNUM; i++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureSpeechBubble[i] != NULL)
		{
			g_pTextureSpeechBubble[i]->Release();
			g_pTextureSpeechBubble[i] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSpeechBubble != NULL)
	{
		g_pVtxBuffSpeechBubble->Release();
		g_pVtxBuffSpeechBubble = NULL;
	}
}
//=============================
//�����o��UI�̍X�V����
//=============================
void UpdateSpeechBubble(void)
{
	
	VERTEX_3D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSpeechBubble->Lock(0, 0, (void**)&pVtx, 0);

	for (int nSpeechBubble = 0; nSpeechBubble < NUMSPEECHBUBBLE; nSpeechBubble++)
	{
		if (g_SpeechBubble[nSpeechBubble].bUse == true)
		{

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-(g_SpeechBubble[nSpeechBubble].nBubbleCnt) * XMAG, g_SpeechBubble[nSpeechBubble].nBubbleCnt* XMAG2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_SpeechBubble[nSpeechBubble].nBubbleCnt * XMAG, g_SpeechBubble[nSpeechBubble].nBubbleCnt* XMAG2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-(g_SpeechBubble[nSpeechBubble].nBubbleCnt) * XMAG, -(g_SpeechBubble[nSpeechBubble].nBubbleCnt* XMAG2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_SpeechBubble[nSpeechBubble].nBubbleCnt * XMAG, -(g_SpeechBubble[nSpeechBubble].nBubbleCnt* XMAG2), 0.0f);

			//���_���W�̐ݒ�
			//pVtx[0].pos = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
			//pVtx[1].pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
			//pVtx[2].pos = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);
			//pVtx[3].pos = D3DXVECTOR3(10.0f, -10.0f, 0.0f);

		
			g_SpeechBubble[nSpeechBubble].bTrackingPlayer1 = false;

			g_SpeechBubble[nSpeechBubble].bTrackingPlayer2 = false;
		}

		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffSpeechBubble->Unlock();

}
//=============================
//�����o��UI�̕`�揈��
//=============================
void DrawSpeechBubble(int CameraLoopNum)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX  mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;//�r���[�}�g���b�N�X�̎擾

	for (int nSpeechBubble = 0; nSpeechBubble < NUMSPEECHBUBBLE; nSpeechBubble++)
	{
		if (g_SpeechBubble[nSpeechBubble].bUse == true)
		{
			//���C�g�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			////Z�̔�r�ύX
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			//Z�o�b�t�@�ɏ������܂Ȃ�
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);



			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble);

			//�����𔽉f
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_SpeechBubble[nSpeechBubble].rotSpeechBubble.y, g_SpeechBubble[nSpeechBubble].rotSpeechBubble.x, g_SpeechBubble[nSpeechBubble].rotSpeechBubble.z);

			//D3DXMatrixMultiply(&g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble, &g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble, &mtxRot);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble, NULL, &mtxView);//�t�s�S�����߂�

			g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble._41 = 0.0f;
			g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble._42 = 0.0f;
			g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble._43 = 0.0f;


			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_SpeechBubble[nSpeechBubble].pos.x, g_SpeechBubble[nSpeechBubble].pos.y, g_SpeechBubble[nSpeechBubble].pos.z);

			D3DXMatrixMultiply(&g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble, &g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffSpeechBubble, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			int Escape = static_cast<int>(g_SpeechBubble[nSpeechBubble].BubbleSType);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSpeechBubble[Escape]);

			//�e�N�X�`���̐ݒ�
//			pDevice->SetTexture(0, NULL);
			
			//�����o��UI�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				nSpeechBubble * 4,//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);//�`�悷��v���~�e�B�u��

			//���C�g��L���ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			//Z�̔�r�ύX
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			//Z�o�b�t�@�ɏ������܂Ȃ�
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

			
			//�e�N�X�`����߂�
			pDevice->SetTexture(0, NULL);
			g_SpeechBubble[nSpeechBubble].bOK = false;
		}
	}
}
//=============================
//�����o��UI�̎擾����
//=============================

SPEECHBUBBLE* GetSpeechBubble(void)
{
	return &g_SpeechBubble[0];
}

//=============================
//�����o��UI�̐ݒ菈��
//=============================
void SetSpeechBubble(D3DXVECTOR3 Pos, int ActionIndex, int SetType, D3DXVECTOR3 CorrectionValue, SPEECHBUBBLETYPE UI_TYPE, int PlayerIndex)
{//�ǂ̐ݒ�-------------------------------SetNum[�o�^�ԍ�--���Ԃ�ʂ悤��]---[SetType-0���o���A�P���k��]

	if (g_SpeechBubble[ActionIndex].bOK == false)
	{
	//	if (UI_TYPE== SPEECHBUBBLETYPE_GAMECLEAR)
	//	{
	//		UI_TYPE = SPEECHBUBBLETYPE_TRANCE;
	//	}

		if (SetType == 0)
		{//�g��
			if (g_SpeechBubble[ActionIndex].bTrackingPlayer1 == false && PlayerIndex == 0)
			{
				g_SpeechBubble[ActionIndex].pos = D3DXVECTOR3(Pos.x, Pos.y, Pos.z);//�ʒu
				g_SpeechBubble[ActionIndex].pos += CorrectionValue;
				g_SpeechBubble[ActionIndex].BubbleSType = UI_TYPE;
				g_SpeechBubble[ActionIndex].bTrackingPlayer1 = true;
			}
			else if (g_SpeechBubble[ActionIndex].bTrackingPlayer2 == false && PlayerIndex == 1)
			{
				g_SpeechBubble[ActionIndex].pos = D3DXVECTOR3(Pos.x, Pos.y, Pos.z);//�ʒu
				g_SpeechBubble[ActionIndex].pos += CorrectionValue;
				g_SpeechBubble[ActionIndex].BubbleSType = UI_TYPE;
				g_SpeechBubble[ActionIndex].bTrackingPlayer2 = true;
			}



			g_SpeechBubble[ActionIndex].bUse = true;

			g_SpeechBubble[ActionIndex].nBubbleCnt += ZOOMSPEED;
			g_SpeechBubble[ActionIndex].bOK = true;

		}
		else if (SetType == 1)
		{//�k��
			g_SpeechBubble[ActionIndex].nBubbleCnt -= REDSPEED;
		}
	}





	if (g_SpeechBubble[ActionIndex].nBubbleCnt < 0)
	{
		g_SpeechBubble[ActionIndex].bOK = false;
		g_SpeechBubble[ActionIndex].nBubbleCnt = 0;
	}
	if (g_SpeechBubble[ActionIndex].nBubbleCnt > 30)
	{
		g_SpeechBubble[ActionIndex].nBubbleCnt = 30;
	}
}


