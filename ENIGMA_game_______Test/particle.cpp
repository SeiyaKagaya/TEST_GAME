//=========================================================
//
//�p�[�e�B�N����\�����鏈��[particle.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
//#include "item.h"
//#include "sound.h"
//#include "input.h"
#include "particle.h"


//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL; //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureParticle[PARTICLETYPE_MAX] = {};       //�e�N�X�`���ւ̃|�C���^



//D3DXVECTOR3 g_Particle[nParticle].posParticle;	//�ʒu
//D3DXVECTOR3 g_Particle[nParticle].rotParticle;	//����
//D3DXMATRIX g_Particle[nParticle].mtxWorld;//���[���h�}�g���b�N�X


Particle g_Particle[MAX_PARTICLE];//���쒆�@�\����



//=============================
//�p�[�e�B�N���̏���������
//=============================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &g_pTextureParticle[0]);//��D


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffParticle, NULL);

	VERTEX_3D* pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nParticle = 0; nParticle < MAX_PARTICLE; nParticle++)
	{
		//g_Particle[nParticle].g_Particle[nParticle].posParticle
		//g_Particle[nParticle].rotParticle
		//g_Particle[nParticle].

		g_Particle[nParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu

		
		g_Particle[nParticle].nLife = 0;
		g_Particle[nParticle].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_Particle[nParticle].fRadius = 0.0f;
		g_Particle[nParticle].DiffRadius = 0;
		g_Particle[nParticle].nType = PARTICLETYPE_MAX;

		g_Particle[nParticle].bUse = false;
	

	
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-0, -0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, -0, 0.0f);

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
	g_pVtxBuffParticle->Unlock();





}
//=============================
//�p�[�e�B�N���̏I������
//=============================
void UninitParticle(void)
{
	//StopSound(SOUND_LABEL_SE_SHOT);
	//StopSound(SOUND_LABEL_SE_EXPLOSIONBOMB);
	//�e�N�X�`���̔j��
	for (int i = 0; i < PARTICLETYPE_MAX; i++)
	{
		if (g_pTextureParticle[i] != NULL)
		{
			g_pTextureParticle[i]->Release();
			g_pTextureParticle[i] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}
//=============================
//�p�[�e�B�N���̍X�V����
//=============================
void UpdateParticle(void)
{

	VERTEX_3D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nParticle = 0; nParticle < MAX_PARTICLE; nParticle++)
	{
		if (g_Particle[nParticle].bUse == true)
		{
			//g_Particle[nParticle].oldPos = g_Particle[nParticle].pos;
			//�ʒu���X�V
			g_Particle[nParticle].pos += g_Particle[nParticle].move;



		
			//--------------------------------����
			g_Particle[nParticle].nLife--;

			g_Particle[nParticle].fRadius -= g_Particle[nParticle].DiffRadius;

			if (g_Particle[nParticle].nLife < 0)
			{
				g_Particle[nParticle].bUse = false;
			
			}
			//--------------------------------����

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_Particle[nParticle].fRadius, g_Particle[nParticle].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Particle[nParticle].fRadius, g_Particle[nParticle].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Particle[nParticle].fRadius, -g_Particle[nParticle].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Particle[nParticle].fRadius, -g_Particle[nParticle].fRadius, 0.0f);



			//���_�J���[�̐ݒ�
			pVtx[0].col = g_Particle[nParticle].col;
			pVtx[1].col = g_Particle[nParticle].col;
			pVtx[2].col = g_Particle[nParticle].col;
			pVtx[3].col = g_Particle[nParticle].col;



		}
		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffParticle->Unlock();

}
//=============================
//�p�[�e�B�N���̕`�揈��
//=============================
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX  mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;//�r���[�}�g���b�N�X�̎擾

	for (int nParticle = 0; nParticle < MAX_PARTICLE; nParticle++)
	{
		if (g_Particle[nParticle].bUse == true)
		{
			//���C�g�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			////Z�̔�r�ύX
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			////Z�o�b�t�@�ɏ������܂Ȃ�
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);




			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Particle[nParticle].mtxWorld);

			//�����𔽉f
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Particle[nParticle].rotParticle.y, g_Particle[nParticle].rotParticle.x, g_Particle[nParticle].rotParticle.z);

			//D3DXMatrixMultiply(&g_Particle[nParticle].mtxWorld, &g_Particle[nParticle].mtxWorld, &mtxRot);

					//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Particle[nParticle].pos.x, g_Particle[nParticle].pos.y, g_Particle[nParticle].pos.z);

			D3DXMatrixMultiply(&g_Particle[nParticle].mtxWorld, &g_Particle[nParticle].mtxWorld, &mtxTrans);



			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_Particle[nParticle].mtxWorld, NULL, &mtxView);//�t�s�S�����߂�

			g_Particle[nParticle].mtxWorld._41 = 0.0f;
			g_Particle[nParticle].mtxWorld._42 = 0.0f;
			g_Particle[nParticle].mtxWorld._43 = 0.0f;


			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Particle[nParticle].pos.x, g_Particle[nParticle].pos.y, g_Particle[nParticle].pos.z);

			D3DXMatrixMultiply(&g_Particle[nParticle].mtxWorld, &g_Particle[nParticle].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Particle[nParticle].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);


			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureParticle[0]);

			//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


			//�p�[�e�B�N���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				nParticle * 4,//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);//�`�悷��v���~�e�B�u��


			//�A���t�@�u�����f�B���O�����Ƃɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


			//���C�g��L���ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			////Z�̔�r�ύX
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			////Z�o�b�t�@�ɏ������܂Ȃ�
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

			
			//�e�N�X�`����߂�
			pDevice->SetTexture(0, NULL);
		}
	}
}
//=============================
//�p�[�e�B�N���̎擾����
//=============================

Particle* GetParticle(void)
{
	return &g_Particle[0];
}

//=============================
//�p�[�e�B�N���̐ݒ菈��
//=============================
void SetParticle(D3DXVECTOR3 Pos,float fRadius,int nLife, PARTICLETYPE Type, D3DXCOLOR Color)
{


	VERTEX_3D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nParticle = 0; nParticle < MAX_PARTICLE; nParticle++)
	{
		if (g_Particle[nParticle].bUse == false)
		{
				g_Particle[nParticle].pos = Pos;//�ʒu

				g_Particle[nParticle].fRadius = fRadius;
				g_Particle[nParticle].DiffRadius = fRadius/ nLife;
				g_Particle[nParticle].col = Color;
				//pPlayer2->ParticleShotFrame = MAXSHOTFRAME;
				//VibrationLeft(35535);
				//VibrationRight(35535);

				//SE
				//PlaySound(SOUND_LABEL_SE_SHOT);

			g_Particle[nParticle].move =D3DXVECTOR3(0.0f,0.0f,0.0f);

			// ���A������ق�
			g_Particle[nParticle].nType = Type;
			g_Particle[nParticle].bUse = true;

			g_Particle[nParticle].nLife = nLife;
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffParticle->Unlock();
}
////=============================
//// �\�������_���v�Z����֐�
////=============================
//D3DXVECTOR3 PredictIntersection(Particle bullet, Enemy enemy)
//{
//	//�v�Z�Y���������Đ���
//	//�����𐶐�
//
//	int random = ((rand() % 20) - 10);//(25~-25)�܂ł̗���
//
//	float random2 = random * 0.1f;//
//
//	//�덷������
//	D3DXVECTOR3 randomPosError = D3DXVECTOR3(random2, random2 * -1.0f, random2);
//
//	// ���e�ƓG(�덷��)�̑��Έʒu�x�N�g��
//	D3DXVECTOR3 relativePos = bullet.pos - (enemy.pos + randomPosError);
//
//	// ���e�ƓG�̑��Α��x�x�N�g��
//	D3DXVECTOR3 relativeVel = bullet.move - enemy.move;
//
//	// ���e�ƓG�̍ŒZ��������
//	float timeToIntersection = -D3DXVec3Dot(&relativePos, &relativeVel) / D3DXVec3LengthSq(&relativeVel);
//
//	// �G�̗\���ʒu�i�����_�j���v�Z
//	D3DXVECTOR3 predictedIntersection = (enemy.pos + randomPosError) + enemy.move * timeToIntersection;
//
//	return predictedIntersection;
//}


