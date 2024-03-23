//=========================================================
//
//�ǂ�\�����鏈��[wall.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "stage.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStage = NULL; //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureStage[TEXTYPE_MAX] = {};       //�e�N�X�`���ւ̃|�C���^



//D3DXVECTOR3 g_Stage[nWall].posStage;	//�ʒu
//D3DXVECTOR3 g_Stage[nWall].rotStage;	//����
//D3DXMATRIX g_Stage[nWall].mtxWorldStage;//���[���h�}�g���b�N�X


STAGE g_Stage[NUMSTAGE];//���쒆�@�\����



//=============================
//�ǂ̏���������
//=============================
void InitStage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wallflower.jpg", &g_pTextureStage[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\concrete.jpg", &g_pTextureStage[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\blood.jpg", &g_pTextureStage[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wallgrain.jpg", &g_pTextureStage[3]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\safe000.png", &g_pTextureStage[4]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\JHOUKA.png", &g_pTextureStage[5]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cookinfo.png", &g_pTextureStage[6]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BlackCat.png", &g_pTextureStage[7]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\CupboardDish.png", &g_pTextureStage[8]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BathGimi.png", &g_pTextureStage[9]);

	//�����Ƀe�N�X�`����ǉ�������w�b�_�ɂ����₷����!!!!//

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * NUMSTAGE, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffStage, NULL);

		VERTEX_3D* pVtx;//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);

	for (int nWall = 0; nWall < NUMSTAGE; nWall++)
	{
		//g_Stage[nWall].g_Stage[nWall].posStage
		//g_Stage[nWall].rotStage
		g_Stage[nWall].bUse = false;

		g_Stage[nWall].posStage = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_Stage[nWall].rotStage = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_Stage[nWall].MaxPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ő�
		g_Stage[nWall].MinPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ŏ�
		g_Stage[nWall].bCollision = false;
		g_Stage[nWall].TexType = TEXTYPE_00;


		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-STAGESIZE, 100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(STAGESIZE, 100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-STAGESIZE, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(STAGESIZE, 0.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffStage->Unlock();

	//�n����-------------------------------------------------------------------------------------------------------------------------------------
	//�V��
	SetStage(D3DXVECTOR3(-0700.0f, 0400.0f, -0600.0f), D3DXVECTOR3(-1.57f, +0.00f, 0.00f), 0800.0f, 0800.0f, TEXTYPE_01);//�e�X�g�d�l

	//��
	SetStage(D3DXVECTOR3(-0900.0f, 0100.0f, +0110.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0600.0f, 0300.0f, TEXTYPE_01);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(-0400.0f, 0100.0f, -0030.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0200.0f, 0300.0f, TEXTYPE_01);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(-0150.0f, 0100.0f, -0230.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0250.0f, 0300.0f, TEXTYPE_01);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(+0030.0f, 0100.0f, -0800.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0700.0f, 0300.0f, TEXTYPE_01);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(-1200.0f, 0100.0f, -0600.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0750.0f, 0300.0f, TEXTYPE_01);//�e�X�g�d�l�����ĉE�X�C�b�`��
	SetStage(D3DXVECTOR3(-0140.0f, 0100.0f, -1230.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0180.0f, 0300.0f, TEXTYPE_01);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(-0320.0f, 0100.0f, -1330.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_01);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(-1050.0f, 0100.0f, -1230.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0170.0f, 0300.0f, TEXTYPE_01);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(-0880.0f, 0100.0f, -1330.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_01);//�e�X�g�d�l



	//�\���H----------------------------------------------------------------------------------------------------------------------------------------
	//�V��
	SetStage(D3DXVECTOR3(-0600.0f, 0300.0f, -2900.0f), D3DXVECTOR3(-1.57f, +0.00f, 0.00f), 1100.0f, 1000.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n��

	//��
	//�X�|�[���n�_�A��
	SetStage(D3DXVECTOR3(-0600.0f, 0000.0f, -1890.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n��
	SetStage(D3DXVECTOR3(-0600.0f, 0000.0f, -3910.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n�O
	SetStage(D3DXVECTOR3(+0450.0f, 0000.0f, -2900.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n��
	SetStage(D3DXVECTOR3(-1650.0f, 0000.0f, -2900.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n��

	//�ʘH���E��
	SetStage(D3DXVECTOR3(-0550.0f, 0000.0f, -2250.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n�㍶
	SetStage(D3DXVECTOR3(-0650.0f, 0000.0f, -2250.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n��E

	SetStage(D3DXVECTOR3(-0550.0f, 0000.0f, -3550.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n�O��
	SetStage(D3DXVECTOR3(-0650.0f, 0000.0f, -3550.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n�O�E

	SetStage(D3DXVECTOR3(-1250.0f, 0000.0f, -2950.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n�E�O
	SetStage(D3DXVECTOR3(-1250.0f, 0000.0f, -2850.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n�E��

	SetStage(D3DXVECTOR3(+0050.0f, 0000.0f, -2950.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n���O
	SetStage(D3DXVECTOR3(+0050.0f, 0000.0f, -2850.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n����

	//����������
	SetStage(D3DXVECTOR3(-0750.0f, 0000.0f, -2650.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n��E��
	SetStage(D3DXVECTOR3(-0450.0f, 0000.0f, -2650.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n�捶��

	SetStage(D3DXVECTOR3(-0750.0f, 0000.0f, -3150.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n�O�E��
	SetStage(D3DXVECTOR3(-0450.0f, 0000.0f, -3150.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n�O����

	SetStage(D3DXVECTOR3(-0850.0f, 0000.0f, -2750.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n�E��O
	SetStage(D3DXVECTOR3(-0350.0f, 0000.0f, -2750.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n����O

	SetStage(D3DXVECTOR3(-0850.0f, 0000.0f, -3050.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n�E��
	SetStage(D3DXVECTOR3(-0350.0f, 0000.0f, -3050.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//�e�X�g�d�l�X�|�[���n����



	//�����-------------------------------------------------------------------------------------------------------------------------------------
	//�V��
	SetStage(D3DXVECTOR3(+3250.0f, 0200.0f, -0250.0f), D3DXVECTOR3(-1.57f, +0.00f, 0.00f), 0400.0f, 0400.0f, TEXTYPE_03);//�e�X�g�d�l

	//��
	SetStage(D3DXVECTOR3(+3300.0f, 0000.0f, +0060.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_03);//�e�X�g�d�l�X�|�[���n��O��
	SetStage(D3DXVECTOR3(+3300.0f, 0000.0f, -0630.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_03);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(+2900.0f, 0000.0f, -0300.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_03);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(+3650.0f, 0000.0f, -0300.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_03);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(+3500.0f, 0000.0f, -0400.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0250.0f, 0300.0f, TEXTYPE_03);//�e�X�g�d�l
	
	SetStage(D3DXVECTOR3(+3600.0f, 0000.0f, -0150.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_03);//�e�X�g�d�l
	
	SetStage(D3DXVECTOR3(+3550.0f, 0000.0f, -0050.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0150.0f, 0300.0f, TEXTYPE_03);//�e�X�g�d�l
	
	SetStage(D3DXVECTOR3(+3150.0f, 0000.0f, -0250.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0250.0f, 0300.0f, TEXTYPE_03);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(+3150.0f, 0000.0f, -0250.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0250.0f, 0300.0f, TEXTYPE_03);//�e�X�g�d�l
	
	SetStage(D3DXVECTOR3(+3400.0f, 0000.0f, +0050.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_03);//�e�X�g�d�l
	
	SetStage(D3DXVECTOR3(+3500.0f, 0250.0f, -0050.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0100.0f, 0100.0f, TEXTYPE_03);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(+3500.0f, 0250.0f, -0050.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0100.0f, 0100.0f, TEXTYPE_03);//�e�X�g�d�l
	
	SetStage(D3DXVECTOR3(+3200.0f, 0220.0f, -0454.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0200.0f, 0100.0f, TEXTYPE_03);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(+3200.0f, 0220.0f, -0454.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0200.0f, 0100.0f, TEXTYPE_03);//�e�X�g�d�l
	
	//���ʐݒu�̂��߂��蔲��
	SetStage(D3DXVECTOR3(+3200.0f, 0020.0f, -0327.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0075.0f, 0100.0f, TEXTYPE_03);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(+3200.0f, 0020.0f, -0327.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0075.0f, 0100.0f, TEXTYPE_03);//�e�X�g�d�l
	
	//���ʐݒu�̂��߂��蔲��
	SetStage(D3DXVECTOR3(+3200.0f, 0020.0f, -0590.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0075.0f, 0100.0f, TEXTYPE_03);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(+3200.0f, 0020.0f, -0590.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0075.0f, 0100.0f, TEXTYPE_03);//�e�X�g�d�l
	


	//���r���O--------------------------------------------------------------------------------------------------------------------------------------------
	//�V��
	SetStage(D3DXVECTOR3(+3200.0f, 0300.0f, -1900.0f), D3DXVECTOR3(-1.57f, +0.00f, 0.00f), 0500.0f, 0700.0f, TEXTYPE_00);//�e�X�g�d�l

	//��
	SetStage(D3DXVECTOR3(+3150.0f, 0100.0f, -1700.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0050.0f, 0200.0f, TEXTYPE_00);//�e�X�g�d�l�����Ă����̕ǋ�ԉE��
	SetStage(D3DXVECTOR3(+3400.0f, 0100.0f, -1700.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0100.0f, 0200.0f, TEXTYPE_00);//�e�X�g�d�l�����Ă����̕ǋ�ԍ���
	SetStage(D3DXVECTOR3(+3500.0f, 0100.0f, -1500.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0200.0f, 0200.0f, TEXTYPE_00);//�e�X�g�d�l�����Ă����̍�����
	SetStage(D3DXVECTOR3(+3400.0f, 0100.0f, -1900.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0300.0f, 0200.0f, TEXTYPE_00);//�e�X�g�d�l�����Ă����̕ǔ��Α�
	SetStage(D3DXVECTOR3(+3100.0f, 0100.0f, -1800.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0100.0f, 0200.0f, TEXTYPE_00);//�e�X�g�d�l�����Ă����̕ǔ��Α��Ƃ̂Ȃ���
	SetStage(D3DXVECTOR3(+3100.0f, 0100.0f, -1340.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0100.0f, 0200.0f, TEXTYPE_00);//�e�X�g�d�l�����č��L�b�`���ւ̍�
	SetStage(D3DXVECTOR3(+3300.0f, 0100.0f, -1300.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0200.0f, 0200.0f, TEXTYPE_00);//�e�X�g�d�l�L�b�`�����荶��

	SetStage(D3DXVECTOR3(+2750.0f, 0100.0f, -1900.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0700.0f, 0200.0f, TEXTYPE_00);//�e�X�g�d�l�����č��L�b�`���ւ̍�

	SetStage(D3DXVECTOR3(+2900.0f, 0100.0f, -1440.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0200.0f, 0200.0f, TEXTYPE_00);//�e�X�g�d�l�L�b�`�����荶��
	
	SetStage(D3DXVECTOR3(+3200.0f, 0100.0f, -2550.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0500.0f, 0200.0f, TEXTYPE_00);//�e�X�g�d�l�L�b�`�����荶��

	SetStage(D3DXVECTOR3(+3700.0f, 0100.0f, -2200.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0350.0f, 0200.0f, TEXTYPE_00);//�e�X�g�d�l�����Ă����̕ǔ��Α��Ƃ̂Ȃ���

	SetStage(D3DXVECTOR3(+3250.0f, 0100.0f, -1800.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0100.0f, 0200.0f, TEXTYPE_01);//�e�X�g�d�l�K�i���s��
	SetStage(D3DXVECTOR3(+3300.0f, 0100.0f, -1750.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0050.0f, 0200.0f, TEXTYPE_00);//�e�X�g�d�l�K�i
	SetStage(D3DXVECTOR3(+3200.0f, 0100.0f, -1750.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0050.0f, 0200.0f, TEXTYPE_00);//�e�X�g�d�l�K�i

	//��
	SetStage(D3DXVECTOR3(+3200.0f, 0100.0f, -1900.0f), D3DXVECTOR3(1.57f, +0.00f, 0.00f), 0500.0f, 0700.0f, TEXTYPE_03);//�e�X�g�d�l

	//�`���[�g���A�����[��
	SetStage(D3DXVECTOR3(+3000.0f, 0000.0f, +2550.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_04);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(+3000.0f, 0000.0f, +1050.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_04);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(+3400.0f, 0000.0f, +1800.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0800.0f, 0300.0f, TEXTYPE_04);//�e�X�g�d�l
	SetStage(D3DXVECTOR3(+2600.0f, 0000.0f, +1800.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0800.0f, 0300.0f, TEXTYPE_04);//�e�X�g�d�l

	//��Button
	SetStage(D3DXVECTOR3(-400.5f, 100.0f, -40.0f), D3DXVECTOR3(0.00f, 1.57f, 0.0f),50.0f,50.0f, TEXTYPE_05);//�e�X�g�d�l
	//��������
	SetStage(D3DXVECTOR3(3300.0f, 200.0f, -1301.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 30.0f, TEXTYPE_06);
	//�M�ē�
	SetStage(D3DXVECTOR3(-140.0f, 100.0f, -235.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 60.0f, TEXTYPE_08);
	//�o�X�M�~�ē�
	SetStage(D3DXVECTOR3(3300.0f, 100.0f, -255.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f, 30.0f, TEXTYPE_09);


	//�������Ƃ̕�
	SetStage(D3DXVECTOR3(1500.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 5000.0f, 1000.0f, TEXTYPE_07);
	SetStage(D3DXVECTOR3(1500.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f), 5000.0f, 1000.0f, TEXTYPE_07);

	SetStage(D3DXVECTOR3(1319.0f, 0.0f, 741.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5000.0f, 1000.0f, TEXTYPE_07);
	SetStage(D3DXVECTOR3(1319.0f, 0.0f, 741.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 5000.0f, 1000.0f, TEXTYPE_07);

	SetStage(D3DXVECTOR3(3290.0f, 0.0f, -930.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2000.0f, 1000.0f, TEXTYPE_07);
	SetStage(D3DXVECTOR3(3290.0f, 0.0f, -930.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 2000.0f, 1000.0f, TEXTYPE_07);

	SetStage(D3DXVECTOR3(340.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2000.0f, 1000.0f, TEXTYPE_07);
	SetStage(D3DXVECTOR3(340.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 2000.0f, 1000.0f, TEXTYPE_07);



	//�����蔻�菜�O
	ExclusionCollision_Stage();
}
//=============================
//�ǂ̏I������
//=============================
void UninitStage(void)
{
	for (int nWall = 0; nWall < TEXTYPE_MAX; nWall++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureStage[nWall] != NULL)
		{
			g_pTextureStage[nWall]->Release();
			g_pTextureStage[nWall] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffStage != NULL)
	{
		g_pVtxBuffStage->Release();
		g_pVtxBuffStage = NULL;
	}
}
//=============================
//�ǂ̍X�V����
//=============================
void UpdateStage(void)
{
	//�����Ȃ�
}
//=============================
//�ǂ̕`�揈��
//=============================
void DrawStage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	for (int nWall = 0; nWall < NUMSTAGE; nWall++)
	{
		if (g_Stage[nWall].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Stage[nWall].mtxWorldStage);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Stage[nWall].rotStage.y, g_Stage[nWall].rotStage.x, g_Stage[nWall].rotStage.z);

			D3DXMatrixMultiply(&g_Stage[nWall].mtxWorldStage, &g_Stage[nWall].mtxWorldStage, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Stage[nWall].posStage.x, g_Stage[nWall].posStage.y, g_Stage[nWall].posStage.z);

			D3DXMatrixMultiply(&g_Stage[nWall].mtxWorldStage, &g_Stage[nWall].mtxWorldStage, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Stage[nWall].mtxWorldStage);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffStage, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureStage[g_Stage[nWall].TexType]);

			//�ǂ̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				nWall * 4,//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);//�`�悷��v���~�e�B�u��

			//�e�N�X�`����߂�
			pDevice->SetTexture(0, NULL);
		}
	}
}
//=============================
//�ǂ̐ݒ菈��
//=============================
void SetStage(D3DXVECTOR3 Pos,D3DXVECTOR3 rot, float bes, float ver, TEXTYPE TexType)
{
	VERTEX_3D* pVtx;//���_���ւ̃|�C���^

//	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);

	for (int nWall = 0; nWall < NUMSTAGE; nWall++)
	{
		if (g_Stage[nWall].bUse == false)
		{
			g_Stage[nWall].posStage = Pos;//�ʒu
			g_Stage[nWall].rotStage = rot;
			g_Stage[nWall].TexType = TexType;
			g_Stage[nWall].bUse = true;
			g_Stage[nWall].bCollision = true;

			//�ő�ŏ�
			CalculateTransformedWallVertices(g_Stage[nWall].posStage, rot, bes, ver, &pVtx[0], nWall);
			
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffStage->Unlock();
}
//=============================
//�ǂ̏��擾����
//=============================
STAGE* GetStage(void)
{
	return &g_Stage[0];
}
//=============================
// ���[�J�����W�n�ł̕ǂ̒��_���W��ݒ肷��֐�
//=============================
void SetWallVertices(VERTEX_3D* pVtx, float bes, float ver)
{

	// �ǂ̃��[�J�����W�n�ł̒��_���W��ݒ�
	pVtx[0].pos = D3DXVECTOR3(-bes, ver, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(bes, ver, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-bes, -ver, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(bes, -ver, 0.0f);
}

//=============================
// �ǂ̈ʒu�Ɖ�]�ɏ���������̒��_���W���v�Z����֐�
//=============================
void CalculateTransformedWallVertices(D3DXVECTOR3 Pos, D3DXVECTOR3 rot, float bes, float ver, VERTEX_3D* pVtx,int index)
{
	D3DXVECTOR3 MinPos = D3DXVECTOR3(999999.9f, 999999.9f, 999999.9f);
	D3DXVECTOR3 MaxPos = D3DXVECTOR3(-999999.9f, -999999.9f, -999999.9f);

	VERTEX_3D EscapepVtx[4];

	// �ǂ̃��[�J�����W�n�ł̒��_���W��ݒ�
	SetWallVertices(pVtx, bes, ver);

	// ���[�J�����W�n���烏�[���h���W�n�ւ̕ϊ��s����v�Z
	D3DXMATRIX mtxWorld;
	D3DXMatrixIdentity(&mtxWorld); // �P�ʍs��ŏ�����
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z); // ��]�s����v�Z
	D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z); // ���s�ړ��s����v�Z
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot); // ��]�s�������
//	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans); // ���s�ړ��s�������

	// �e���_�̍��W��ϊ��s��Ń��[���h���W�n�ɕϊ�
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&EscapepVtx[i].pos, &pVtx[i].pos, &mtxWorld);
		
		if (MaxPos.x <= EscapepVtx[i].pos.x)
		{
			MaxPos.x = EscapepVtx[i].pos.x;
		}
		if (MaxPos.y <= EscapepVtx[i].pos.y)
		{
			MaxPos.y = EscapepVtx[i].pos.y;
		}
		if (MaxPos.z <= EscapepVtx[i].pos.z)
		{
			MaxPos.z = EscapepVtx[i].pos.z;
		}


		if (MinPos.x >= EscapepVtx[i].pos.x)
		{
			MinPos.x = EscapepVtx[i].pos.x;
		}
		if (MinPos.y >= EscapepVtx[i].pos.y)
		{
			MinPos.y = EscapepVtx[i].pos.y;
		}
		if (MinPos.z >= EscapepVtx[i].pos.z)
		{
			MinPos.z = EscapepVtx[i].pos.z;
		}


	}
	//�����ōő�ŏ��v�Z
	g_Stage[index].MaxPos = MaxPos;
	g_Stage[index].MinPos = MinPos;

	g_Stage[index].MaxPos += D3DXVECTOR3(1.5f, 3.0f, 1.5f);
	g_Stage[index].MinPos -= D3DXVECTOR3(1.5f, 3.0f, 1.5f);
}


//=============================================
//�����蔻�菜�O����
//=============================================
void ExclusionCollision_Stage(void)
{
	//11-30
	for (int i = 11; i <= 30; i++)
	{
		g_Stage[i].bCollision = false;
	//	g_Stage[i].bUse = false;
	}
	g_Stage[31].bCollision = false;
	g_Stage[36].bCollision = false;
	g_Stage[37].bCollision = false;
	g_Stage[38].bCollision = false;
	g_Stage[39].bCollision = false;
	g_Stage[40].bCollision = false;
	for (int m = 41; m <= 49; m++)
	{
		g_Stage[m].bCollision = false;
	}
	g_Stage[51].bCollision = false;
	g_Stage[52].bCollision = false;
	g_Stage[54].bCollision = false;
	g_Stage[55].bCollision = false;
	g_Stage[62].bCollision = false;
	g_Stage[63].bCollision = false;
	g_Stage[64].bCollision = false;

	g_Stage[72].bCollision = false;
	g_Stage[73].bCollision = false;
	g_Stage[74].bCollision = false;
	g_Stage[75].bCollision = false;
	g_Stage[76].bCollision = false;
	g_Stage[77].bCollision = false;
	g_Stage[78].bCollision = false;
	g_Stage[79].bCollision = false;


}