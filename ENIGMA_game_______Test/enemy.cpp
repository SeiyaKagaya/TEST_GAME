//=========================================================
//
// �G�̏���[enemy.cpp]
// Author seiya kagaya
//
//=========================================================
#include "enemy.h"
#include "stage.h"
#include "player.h"
#include "player2.h"
#include "particle.h"
#include "result.h"
#include "hitcollision_mistake_prevention.h"
#include "model.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "eyetrap.h"
#include "enemy_view.h"
#include <stdio.h>//�w�b�_�[�t�@�C�����C���N���[�h
#include <string.h>//������������ϐ�
#include "game.h"


//=========================================================
//�O���[�o���ϐ�
//=========================================================
ENEMYMODEL g_Enemy;//�v���C���[�S��

///-------------------------------------------------------------------------���f��
LPD3DXMESH g_pMeshModel_Enemy[MAX_PARTS_ENEMY] = {};//���b�V��(���_���)�ւ̃|�C���^

LPD3DXBUFFER g_pBuffMatModel_Enemy[MAX_PARTS_ENEMY] = {};//�}�e���A���ւ̃|�C���^

DWORD dwNumMatModel_Enemy[MAX_PARTS_ENEMY] = {};//�}�e���A���̐�

LPDIRECT3DTEXTURE9 g_apTextureModel_Enemy[NUM_TEXTURE_ENEMY] = {}; //�e�N�X�`���|�C���^

MODEL_ENEMY g_Enemy3;//���f���S��
//--------------------------------------------------------------------------

//=============================
//�G�l�~�[����������
//=============================
void InitEnemy(void)
{
	//g_ENEMYvancedModel.NowMotionUP = MOTIONTYPE_ENEMY_MAX;
	g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_MAX;

	g_Enemy.OldMotionDOWN = MOTIONTYPE_ENEMY_MAX;

	g_Enemy.pos = D3DXVECTOR3(-50.0f, 0.0f, -500.0f);	//�ʒu
	g_Enemy.MinPos = D3DXVECTOR3(g_Enemy.pos + ENEMYMIN);	//�ʒu
	g_Enemy.MaxPos = D3DXVECTOR3(g_Enemy.pos + ENEMYMAX);	//�ʒu

	g_Enemy.oldPos = g_Enemy.pos;	//�ߋ��̈ʒu

	g_Enemy.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����

	g_Enemy.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���s�X�s�[�h

	g_Enemy.ActionPattern = ACTIONPATTERN_ENEMY_WALK;

	ActionEnemy(g_Enemy.ActionPattern, -1);

	g_Enemy.rotmove = 0.0f;

	g_Enemy.PARENT = -1;//�e�q�֌W

	g_Enemy.nPlayerIdx = -1;

	g_Enemy.JumpFrame = 0;

	g_Enemy.bUse = false;;
	g_Enemy.JumpNow = false;
	g_Enemy.JumpOld = false;

	g_Enemy.NowFrameCntDOWN = 0;
	g_Enemy.NowKeyCntDOWN = 0;

	g_Enemy.NowFrameCntUP = 0;
	g_Enemy.NowKeyCntUP = 0;
	g_Enemy.MotionLoopStop = false;
	g_Enemy.MotionBrend = false;

	g_Enemy.BrendCnt = 0;
	g_Enemy.EscapeMotion = MOTIONTYPE_ENEMY_BREND;

	//-------------------------------------------------���f���n
	g_Enemy3.nMaxMotionCnt = 0;
	g_Enemy3.nMaxPartsCnt = 0;
	g_Enemy3.nMaxLoadPartsCnt = 0;

	for (int nCntParts = 0; nCntParts < MAX_PARTS_ENEMY; nCntParts++)//�e�p�[�c�{��
	{
		g_Enemy3.ModelParts[nCntParts].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy3.ModelParts[nCntParts].Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Enemy3.ModelParts[nCntParts].StartPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy3.ModelParts[nCntParts].StartRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Enemy3.ModelParts[nCntParts].PEARENT = 0;
		g_Enemy3.ModelParts[nCntParts].INDEX = 0;

		g_Enemy3.ModelParts[nCntParts].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy3.ModelParts[nCntParts].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Enemy3.ModelParts[nCntParts].calculationExecution = false;
	}
	for (int nMotionCnt = 0; nMotionCnt < MAX_MONITORS; nMotionCnt++)//�e���[�V�����f�[�^
	{
		g_Enemy3.Motion[nMotionCnt].nNumKey = 0;
		g_Enemy3.Motion[nMotionCnt].nLoop = 0;
		g_Enemy3.Motion[nMotionCnt].Motiontype = MOTIONTYPE_ENEMY_MAX;


		for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)//�e���[�V�������̊e�p�[�c�̊e�L�[���̃f�[�^
		{
			g_Enemy3.Motion[nMotionCnt].KeyData[nCntKey].nSplitFrame = 0;

			for (int nCntParts = 0; nCntParts < MAX_PARTS_ENEMY; nCntParts++)//�e���[�V�������̊e�p�[�c�f�[�^
			{
				g_Enemy3.Motion[nMotionCnt].KeyData[nCntKey].PartsData[nCntParts].CorrectionPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Enemy3.Motion[nMotionCnt].KeyData[nCntKey].PartsData[nCntParts].CorrectionRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}

	//�����ŃZ�b�g
	SetModel_Enemy(D3DXVECTOR3(-50.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
}

//=============================
//�G�l�~�[�I������
//=============================
void UninitEnemy(void)
{
	for (int nCntModel = 0; nCntModel < MAX_PARTS_ENEMY; nCntModel++)
	{
		//���b�V���̔j��
		if (g_pMeshModel_Enemy[nCntModel] != NULL)
		{
			g_pMeshModel_Enemy[nCntModel]->Release();
			g_pMeshModel_Enemy[nCntModel] = NULL;
		}
		//�}�e���A���̔j��
		if (g_pBuffMatModel_Enemy[nCntModel] != NULL)
		{
			g_pBuffMatModel_Enemy[nCntModel]->Release();
			g_pBuffMatModel_Enemy[nCntModel] = NULL;
		}
	}
	for (int nNumTex = 0; nNumTex < NUM_TEXTURE_ENEMY; nNumTex++)
	{
		if (g_apTextureModel_Enemy[nNumTex] != NULL)
		{
			g_apTextureModel_Enemy[nNumTex]->Release();
			g_apTextureModel_Enemy[nNumTex] = NULL;
		}
	}
}

//=============================
//�G�l�~�[�X�V����
//=============================
void UpdateEnemy(void)
{
	if (g_Enemy.bUse == true)
	{
		D3DXMATRIX mtxRot, mtxTrans, mtxParent;//�v�Z�p�}�g���b�N�X	


		//	//�Ƃ肠�����ҋ@
		//g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_STANDBY;

		//int Random = ((float)rand() / RAND_MAX) * 2;
		//if (Random == 0)
		//{
		//	g_Enemy.move = D3DXVECTOR3(-5.0f, 0.0f, 0.0f);
		//}
		//else if (Random == 1)
		//{
		//	g_Enemy.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//}


		//�Â�pos����
		g_Enemy.oldPos = g_Enemy.pos;

		if (g_Enemy.ActionPattern == ACTIONPATTERN_ENEMY_CHASE)
		{
			if (g_Enemy.nPlayerIdx == 0)
			{
				Player* pPlayer = GetPlayer();
				float PlayerLength_x = pPlayer->pos.x - g_Enemy.pos.x; //�v���C���[�Ƃ̋����v�Z
				float PlayerLength_z = pPlayer->pos.z - g_Enemy.pos.z; //�v���C���[�Ƃ̋����v�Z
				float fLength = sqrtf(PlayerLength_x * PlayerLength_x + PlayerLength_z * PlayerLength_z);
				if (fLength > 800.0f)
				{
					//�U���X�g�b�v
					for (int nCnt = 0; nCnt < 2; nCnt++)
					{
						VibrationLeft(0, nCnt);
						VibrationRight(0, nCnt);
					}
					ActionEnemy(ACTIONPATTERN_ENEMY_WALK, -1);
				}
				if (fLength < 30.0f)
				{
					SetEyeTrap(g_Enemy.nPlayerIdx);
					//SetFade(MODE_RESULT);
				}
				float fAngle = atan2f(PlayerLength_x, PlayerLength_z);
				g_Enemy.rot.y = (fAngle - (1.0f * D3DX_PI));
				g_Enemy.move.x += sinf(fAngle) * 0.08f;
				g_Enemy.move.z += cosf(fAngle) * 0.08f;
			}
			if (g_Enemy.nPlayerIdx == 1)
			{
				Player_2P* pPlayer_2P = GetPlayer_2P();
				//�v���C���[�Ǐ]����
				float PlayerLength_x = pPlayer_2P->pos.x - g_Enemy.pos.x; //�v���C���[�Ƃ̋����v�Z
				float PlayerLength_z = pPlayer_2P->pos.z - g_Enemy.pos.z; //�v���C���[�Ƃ̋����v�Z
				float fLength = sqrtf(PlayerLength_x * PlayerLength_x + PlayerLength_z * PlayerLength_z);
				if (fLength > 800.0f)
				{
					VibrationLeft(0, g_Enemy.nPlayerIdx);
					VibrationRight(0, g_Enemy.nPlayerIdx);
					ActionEnemy(ACTIONPATTERN_ENEMY_WALK, -1);
				}
				if (fLength < 30.0f)
				{
					SetEyeTrap(g_Enemy.nPlayerIdx);
					//SetFade(MODE_GAMEOVER);
				}
				float fAngle = atan2f(PlayerLength_x, PlayerLength_z);
				g_Enemy.rot.y = (fAngle - (1.0f * D3DX_PI));
				g_Enemy.move.x += sinf(fAngle) * 0.08f;
				g_Enemy.move.z += cosf(fAngle) * 0.08f;
			}

		}
		//�ʒu���X�V
		g_Enemy.pos += g_Enemy.move;

		//if (g_Enemy.move != D3DXVECTOR3(0.0f,0.0f,0.0f))
		//{
		//	g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_MOVE;
		//}
		//else if (g_Enemy.move == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		//{
		//	g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_MOVE;
		//}
		//�㉺�̃��[�V����
		LowerBodyEnemy3();
		//	UpperBodyMotion();

		//�O��̃��[�V�����f�[�^���X�V
		//g_Enemy.OldMotionUP = g_Enemy.NowMotionUP;
		g_Enemy.OldMotionDOWN = g_Enemy.NowMotionDOWN;


		//----------�p�[�c
		for (int nCnt = 0; nCnt < g_Enemy3.nMaxPartsCnt; nCnt++)
		{//�p�[�c����
			//���f���̈ʒu
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Enemy3.ModelParts[nCnt].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy3.ModelParts[nCnt].Rot.y, g_Enemy3.ModelParts[nCnt].Rot.x, g_Enemy3.ModelParts[nCnt].Rot.z);

			D3DXMatrixMultiply(&g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Enemy3.ModelParts[nCnt].Pos.x, g_Enemy3.ModelParts[nCnt].Pos.y, g_Enemy3.ModelParts[nCnt].Pos.z);

			D3DXMatrixMultiply(&g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[nCnt].mtxWorld, &mtxTrans);

			//�e�q�֌W
			if (g_Enemy3.ModelParts[nCnt].PEARENT == -1)
			{
				//�v���C���[�Ƃ�����
				D3DXMatrixMultiply(&g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy.mtxWorld);
			}
			else
			{
				//�����̐e�̃}�g���b�N�X�����Ă�
				D3DXMatrixMultiply(&g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[g_Enemy3.ModelParts[nCnt].PEARENT].mtxWorld);

			}
		}

		//--------------------------------------------------------------------------------------------------------------------------------------------------//�����蔻�肱������
		//�v���C���[�̃T�C�Y
		g_Enemy.MinPos = D3DXVECTOR3(g_Enemy.pos + ENEMYMIN);
		g_Enemy.MaxPos = D3DXVECTOR3(g_Enemy.pos + ENEMYMAX);

		MAPOBJECT* pMapObject;
		pMapObject = GetMapObject();

		for (int i = 0; i < MAX_MODEL; i++)
		{
			if (pMapObject[i].bUse == true)
			{
				if (pMapObject[i].bCollision == true)
				{
					D3DXVECTOR3 ModelMin = D3DXVECTOR3(pMapObject[i].pos + pMapObject[i].Minpos);
					D3DXVECTOR3 ModelMax = D3DXVECTOR3(pMapObject[i].pos + pMapObject[i].Maxpos);

					//����
					BoxCollisionEnemy(g_Enemy.MinPos, g_Enemy.MaxPos, ModelMin, ModelMax);
				}
			}
		}

		//----------------------------------------------------------------------------�ǁA���ڐG
		STAGE* pStage;
		pStage = GetStage();
		for (int nWall = 0; nWall < NUMSTAGE; nWall++)
		{
			if (pStage[nWall].bUse == true)
			{
				if (pStage[nWall].bCollision == true)
				{
					D3DXVECTOR3 StageMin = D3DXVECTOR3(pStage[nWall].posStage + pStage[nWall].MinPos);
					D3DXVECTOR3 StageMax = D3DXVECTOR3(pStage[nWall].posStage + pStage[nWall].MaxPos);

					//�v���C���[���m�����蔻��
					BoxCollisionEnemy(g_Enemy.MinPos, g_Enemy.MaxPos, StageMin, StageMax);
				}
			}
		}

		//�����蔻�蔲���h�~/-----------------------------------------------------------------------------------------------------------------------------------------
		COLLISION_PRE* pColisionPre;
		pColisionPre = GetCollision_Pre();

		for (int i = 0; i < MAXCOLLISION_PRE; i++)
		{
			if (pColisionPre[i].bUse == true)
			{

				D3DXVECTOR3 ColisionPreMin = D3DXVECTOR3(pColisionPre[i].pos + pColisionPre[i].Min);
				D3DXVECTOR3 ColisionPreMax = D3DXVECTOR3(pColisionPre[i].pos + pColisionPre[i].Max);

				//�v���C���[���m�����蔻��
				BoxCollisionEnemy(g_Enemy.MinPos, g_Enemy.MaxPos, ColisionPreMin, ColisionPreMax);

			}
		}
	}
}

//===================================
//�G�l�~�[�s������
//===================================
void ActionEnemy(ACTIONPATTERN_ENEMY ActionPattern, int PlayerIdx)
{
	g_Enemy.ActionPattern = ActionPattern;
	g_Enemy.nPlayerIdx = PlayerIdx;

	if (ActionPattern == ACTIONPATTERN_ENEMY_STANDBY)
	{//�Î~���
		g_Enemy.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_STANDBY;
	}
	else if (ActionPattern == ACTIONPATTERN_ENEMY_WALK)
	{
		int nTurn = ((float)rand() / RAND_MAX) * 4;
		int nMoveX = MAX_ENEMY_SPEED;
		int nMoveZ = MAX_ENEMY_SPEED;
		if (nTurn == 0)
		{
			nMoveX *= -1;
		}
		if (nTurn == 1)
		{
			nMoveZ *= -1;
		}
		if (nTurn == 2)
		{
			nMoveX *= -1;
			nMoveZ *= -1;
		}

		float Angle = atan2f((float)nMoveX, (float)nMoveZ);//���p
		g_Enemy.rot.y = (Angle - (1.0f * D3DX_PI));

		g_Enemy.move = D3DXVECTOR3((float)nMoveX, 0.0f, (float)nMoveZ);
		g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_MOVE;

	}
	else if (ActionPattern == ACTIONPATTERN_ENEMY_SPAWN)
	{
		g_Enemy.pos += g_Enemy.move;
		g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_MOVE;
	}
	else if (ActionPattern == ACTIONPATTERN_ENEMY_CHASE)
	{
		if (PlayerIdx == 0)
		{
			Player* pPlayer = GetPlayer();
			float PlayerLength_x = pPlayer->pos.x - g_Enemy.pos.x; //�v���C���[�Ƃ̋����v�Z
			float PlayerLength_z = pPlayer->pos.z - g_Enemy.pos.z; //�v���C���[�Ƃ̋����v�Z
		//	float fLength = sqrtf(PlayerLength_x * PlayerLength_x + PlayerLength_z * PlayerLength_z);
			float fAngle = atan2f(PlayerLength_x, PlayerLength_z);
			g_Enemy.rot.y = (fAngle - (1.0f * D3DX_PI));
			g_Enemy.move.x += sinf(fAngle) * 0.09f;
			g_Enemy.move.z += cosf(fAngle) * 0.09f;
			VibrationLeft(0, 1);
			VibrationRight(0, 1);
			VibrationLeft(25535, 0);
			VibrationRight(25535, 0);
		}
		if (PlayerIdx == 1)
		{
			Player_2P* pPlayer_2P = GetPlayer_2P();
			//�v���C���[�Ǐ]����
			float PlayerLength_x = pPlayer_2P->pos.x - g_Enemy.pos.x; //�v���C���[�Ƃ̋����v�Z
			float PlayerLength_z = pPlayer_2P->pos.z - g_Enemy.pos.z; //�v���C���[�Ƃ̋����v�Z
		//	float fLength = sqrtf(PlayerLength_x * PlayerLength_x + PlayerLength_z * PlayerLength_z);
			float fAngle = atan2f(PlayerLength_x, PlayerLength_z);
			g_Enemy.rot.y = (fAngle - (1.0f * D3DX_PI));
			g_Enemy.move.x += sinf(fAngle) * 0.05f;
			g_Enemy.move.z += cosf(fAngle) * 0.05f;
			VibrationLeft(0, 0);
			VibrationRight(0, 0);
			VibrationLeft(25535, 1);
			VibrationRight(25535, 1);
		}


		g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_MOVE;
	}
	LowerBodyEnemy3();

}

//=============================
//�G�l�~�[�`�揈��
//=============================
void DrawEnemy(void)
{
	if (g_Enemy.bUse == true)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXMATRIX mtxRot, mtxTrans, mtxParent;//�v�Z�p�}�g���b�N�X

		D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p(�ꎞ�ޔ�)

		D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

		//�L�����S�̂̊(�e�̐e)
			//---------------------------------------------------------------------------------------------------�v���C���[�̈ʒu�̂�
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Enemy.mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy.rot.y, g_Enemy.rot.x, g_Enemy.rot.z);

		D3DXMatrixMultiply(&g_Enemy.mtxWorld, &g_Enemy.mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Enemy.pos.x, g_Enemy.pos.y, g_Enemy.pos.z);

		D3DXMatrixMultiply(&g_Enemy.mtxWorld, &g_Enemy.mtxWorld, &mtxTrans);



		for (int nCnt = 0; nCnt < g_Enemy3.nMaxPartsCnt; nCnt++)
		{
			//---------------------------------------------------------------------------------------------------���f���̈ʒu

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Enemy3.ModelParts[nCnt].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy3.ModelParts[nCnt].Rot.y, g_Enemy3.ModelParts[nCnt].Rot.x, g_Enemy3.ModelParts[nCnt].Rot.z);

			D3DXMatrixMultiply(&g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Enemy3.ModelParts[nCnt].Pos.x, g_Enemy3.ModelParts[nCnt].Pos.y, g_Enemy3.ModelParts[nCnt].Pos.z);

			D3DXMatrixMultiply(&g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[nCnt].mtxWorld, &mtxTrans);


			//�e�q�֌W
			if (g_Enemy3.ModelParts[nCnt].PEARENT == -1)
			{
				//�v���C���[�Ƃ�����
				D3DXMatrixMultiply(&g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy.mtxWorld);
			}
			else
			{
				//�����̐e�̃}�g���b�N�X�����Ă�
				D3DXMatrixMultiply(&g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[nCnt].mtxWorld, &g_Enemy3.ModelParts[g_Enemy3.ModelParts[nCnt].PEARENT].mtxWorld);
			}

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy3.ModelParts[nCnt].mtxWorld);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatModel_Enemy[nCnt]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)dwNumMatModel_Enemy[nCnt]; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);//����͐ݒ肵�Ȃ�
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureModel_Enemy[nCntMat]);

				//���f��(�p�[�c)�̕`��
				g_pMeshModel_Enemy[nCnt]->DrawSubset(nCntMat);

				//�ۑ����Ă��}�e���A����߂�
				pDevice->SetMaterial(&matDef);
			}
		}

	}
}

//=============================
//�G�l�~�[���擾����
//=============================
ENEMYMODEL* GetEnemy(void)
{
	return &g_Enemy;
}

//===================================
//���f���擾����
//===================================
MODEL_ENEMY* GetEnemyModel(void)
{
	return &g_Enemy3;
}

//=============================
//�G�l�~�[���b�V�����擾����
//=============================
LPD3DXMESH* GetMesh_Enemy(void)
{
	return &g_pMeshModel_Enemy[0];
}

//=============================
//�ϊ�����2D--------------------------�߂���厖
//=============================
void ConversionEnemyRot2(float fRot, int nCnt)
{
	//�P�c��f
	//fmodf�Ƃ�+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//fmod�֐��͎�ɕ��������_���̌덷���l�����A��]���v�Z���邽�߂Ɏg�p����܂��B
	//�ʏ�A�����ł̏�]���Z�q% �Ɠ����悤�ȓ��������܂����A
	//�����̏�]���Z�q�͐������m�̉��Z�ɓ������Ă���A���������_���ɂ͑Ή����Ă��܂���B
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//fabsf�Ƃ�+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//���������_���̐�Βl���v�Z���邽�߂Ɏg�p����܂��B
	//�����ł́AEscapeRotDiff2 �̐�Βl�� D3DX_PI �𒴂��Ă��邩�ǂ����𔻒肵�Ă��܂�
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// �p�x��͈͓��Ɏ��߂�
	fRot = fmodf(fRot + D3DX_PI, 2 * D3DX_PI) - D3DX_PI;

	// �p�x�̍���
	float rotDiff = fRot - g_Enemy.rot.y;

	// �������͈͊O�Ȃ�␳---------------------------------------------------------------�߂����������Ɠ��e���ׂ�
	if (fabsf(rotDiff) > D3DX_PI)
	{
		rotDiff = (rotDiff < 0) ? (rotDiff + 2 * D3DX_PI) : (rotDiff - 2 * D3DX_PI);
	}

	g_Enemy.rot.y += rotDiff * 0.1f;

	if (g_Enemy.rot.y > D3DX_PI)
	{
		g_Enemy.rot.y -= (2.0f * D3DX_PI);
	}
	else if (g_Enemy.rot.y < -D3DX_PI)
	{
		g_Enemy.rot.y += (2.0f * D3DX_PI);
	}
}

//=============================
//�ϊ�����3D--------------------------�߂���厖
//=============================
D3DXVECTOR3 ConversionEnemyRot3(D3DXVECTOR3 fRot, int nCnt)
{

	//�P�c��f
	//fmodf�Ƃ�+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//fmod�֐��͎�ɕ��������_���̌덷���l�����A��]���v�Z���邽�߂Ɏg�p����܂��B
	//�ʏ�A�����ł̏�]���Z�q% �Ɠ����悤�ȓ��������܂����A
	//�����̏�]���Z�q�͐������m�̉��Z�ɓ������Ă���A���������_���ɂ͑Ή����Ă��܂���B
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//fabsf�Ƃ�+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//���������_���̐�Βl���v�Z���邽�߂Ɏg�p����܂��B
	//�����ł́AEscapeRotDiff2 �̐�Βl�� D3DX_PI �𒴂��Ă��邩�ǂ����𔻒肵�Ă��܂�
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// �p�x��͈͓��Ɏ��߂�
	fRot.x = fmodf(fRot.x + D3DX_PI, 2 * D3DX_PI) - D3DX_PI;
	fRot.y = fmodf(fRot.y + D3DX_PI, 2 * D3DX_PI) - D3DX_PI;
	fRot.z = fmodf(fRot.z + D3DX_PI, 2 * D3DX_PI) - D3DX_PI;

	float rotDiff = fRot.x;
	float rotDiff2 = fRot.y;
	float rotDiff3 = fRot.z;

	//�֐��̊O�łŊp�x�␳

	return D3DXVECTOR3(rotDiff, rotDiff2, rotDiff3);

}

//===================================
//�e�L�X�g����L�����̏���ǂݍ��ޏ���----------------------------------------------------------------
//===================================
void LoadSetEnemy3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	FILE* pFile;//�t�@�C���|�C���^��錾


	char aString[MAX_WORD2_ENEMY];	//�ǂݍ��ލő啶����

	int nModelNum;//���f��
	nModelNum = 0;

	int nEscapeCntModel;//���f����
	nEscapeCntModel = 0;

	int nfirstEscapePartsCnt;//�͂��߂Ɏg���p�[�c�J�E���g
	nfirstEscapePartsCnt = 0;

	int nMotionCnt;//���[�V�����J�E���g
	nMotionCnt = 0;

	int KeyCnt;//�L�[�J�E���g
	KeyCnt = 0;


	int nKeyPartsCnt;//�e�L�[�̒��ł̃p�[�c�J�E���g
	nKeyPartsCnt = 0;

	char cModelFileName[MAX_PARTS_ENEMY][MAX_WORD2_ENEMY] = {};//�Ƃ肠����20�Ńt�@�C�������Ǘ�

	pFile = fopen(ENEMY_FILE_NAME, "r");

	if (pFile != NULL)
	{//�t�@�C�����J������
		while (1)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "END_SCRIPT") == 0)
			{//�Ō�ɂ�����
				fclose(pFile);
				break;
			}
			else if (strcmp(&aString[0], "NUM_MODEL") == 0)
			{//���f������������
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%d", &g_Enemy3.nMaxLoadPartsCnt);//���f�����i�[

			}
			else if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
			{//�e���f���̃p�[�c�̃p�X��������
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%s", &cModelFileName[0]);//�t�@�C���p�X

				//�t�@�C���̓ǂݍ���----------------------
				D3DXLoadMeshFromX(cModelFileName[0],
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_pBuffMatModel_Enemy[nEscapeCntModel],
					NULL,
					&dwNumMatModel_Enemy[nEscapeCntModel],
					&g_pMeshModel_Enemy[nEscapeCntModel]);

				D3DXMATERIAL* pMat;

				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatModel_Enemy[nEscapeCntModel]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)dwNumMatModel_Enemy[nEscapeCntModel]; nCntMat++)
				{
					if (pMat[nCntMat].pTextureFilename != NULL)
					{
						//�e�N�X�`���̓ǂݍ���
						D3DXCreateTextureFromFile(pDevice,
							pMat[nCntMat].pTextureFilename,
							&g_apTextureModel_Enemy[nCntMat]
						);
					}
				}

				//----------------------------------------

				nEscapeCntModel++;//���f���i�[��C���N��

			}
			else if (strcmp(&aString[0], "CHARACTERSET") == 0)
			{//�L�����Z�b�g��������
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "END_CHARACTERSET") == 0)
					{
						//nCnt++;
						break;
					}
					else if (strcmp(&aString[0], "NUM_PARTS") == 0)
					{//Parts����������
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &g_Enemy3.nMaxPartsCnt);


					}
					else if (strcmp(&aString[0], "PARTSSET") == 0)
					{//Parts�ݒ肪������
						while (1)
						{
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "END_PARTSSET") == 0)
							{//Parts���G���h��������

								nfirstEscapePartsCnt++;
								break;
							}
							else if (strcmp(&aString[0], "INDEX") == 0)
							{//�C���f�b�N�X��������
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &g_Enemy3.ModelParts[nfirstEscapePartsCnt].INDEX);

							}
							else if (strcmp(&aString[0], "PARENT") == 0)
							{//�e��������
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &g_Enemy3.ModelParts[nfirstEscapePartsCnt].PEARENT);
							}
							else if (strcmp(&aString[0], "POS") == 0)
							{//POS��������
								fscanf(pFile, "%s", &aString[0]);

								fscanf(pFile, "%f %f %f", &g_Enemy3.ModelParts[nfirstEscapePartsCnt].Pos.x, &g_Enemy3.ModelParts[nfirstEscapePartsCnt].Pos.y, &g_Enemy3.ModelParts[nfirstEscapePartsCnt].Pos.z);

								//�ۑ�
								g_Enemy3.ModelParts[nfirstEscapePartsCnt].StartPos = g_Enemy3.ModelParts[nfirstEscapePartsCnt].Pos;

							}
							else if (strcmp(&aString[0], "ROT") == 0)
							{//ROT��������
								fscanf(pFile, "%s", &aString[0]);

								fscanf(pFile, "%f %f %f", &g_Enemy3.ModelParts[nfirstEscapePartsCnt].Rot.x, &g_Enemy3.ModelParts[nfirstEscapePartsCnt].Rot.y, &g_Enemy3.ModelParts[nfirstEscapePartsCnt].Rot.z);

								//�ۑ�
								g_Enemy3.ModelParts[nfirstEscapePartsCnt].StartRot = g_Enemy3.ModelParts[nfirstEscapePartsCnt].Rot;
							}
						}

					}
				}
			}
			else if (strcmp(&aString[0], "MOTIONSET") == 0)
			{//MOTION�Z�b�g��������
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "END_MOTIONSET") == 0)
					{//�G���hMOTION�Z�b�g

						g_Enemy3.Motion[nMotionCnt].Motiontype = nMotionCnt;
						nMotionCnt++;//���[�V�����C���N�������g

						if (g_Enemy3.nMaxMotionCnt <= nMotionCnt)
						{
							g_Enemy3.nMaxMotionCnt = nMotionCnt;//���[�V�������͍ő�̂�
						}

						KeyCnt = 0;//�L�[�ԍ����Z�b�g

						break;
					}
					else if (strcmp(&aString[0], "LOOP") == 0)
					{//���[�v����������
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &g_Enemy3.Motion[nMotionCnt].nLoop);
					}
					else if (strcmp(&aString[0], "NUM_KEY") == 0)//----------------�ő�L�[���ɉ��p
					{//�L�[�̐���������
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &g_Enemy3.Motion[nMotionCnt].nNumKey);
					}
					else if (strcmp(&aString[0], "KEYSET") == 0)
					{//KEY�Z�b�g��������
						while (1)
						{
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "END_KEYSET") == 0)
							{//�G���hKEY�Z�b�g

								KeyCnt++;//�L�[�C���N�������g
								nKeyPartsCnt = 0;//�p�[�c�ԍ������Z�b�g
								break;

							}
							else if (strcmp(&aString[0], "FRAME") == 0)
							{//�t���[���̐���������
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &g_Enemy3.Motion[nMotionCnt].KeyData[KeyCnt].nSplitFrame);//-----------------------------------���L�Ɠ���//�킯�Ȃ��ƁA��΂��ꂽ�Ƃ��ɔF���ł��Ȃ�

							}
							else if (strcmp(&aString[0], "KEY") == 0)
							{//KEY��������

								while (1)
								{
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "FRAME") == 0)
									{//�t���[���̐���������
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%d", &g_Enemy3.Motion[nMotionCnt].KeyData[KeyCnt].nSplitFrame);///------------------------��L�Ɠ���

									}

									else if (strcmp(&aString[0], "END_KEY") == 0)
									{//�G���hKEY

										nKeyPartsCnt++;//�p�[�c�C���N�������g
										break;
									}
									else if (strcmp(&aString[0], "POS") == 0)
									{//POS����������
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%f %f %f", &g_Enemy3.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.x, &g_Enemy3.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.y, &g_Enemy3.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.z);///------------------------Key���Ƃ��p�[�c���Ƃŕϓ�

									}
									else if (strcmp(&aString[0], "ROT") == 0)
									{//ROT����������
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%f %f %f", &g_Enemy3.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.x, &g_Enemy3.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.y, &g_Enemy3.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.z);///------------------------Key���Ƃ��p�[�c���Ƃŕϓ�
									}
								}
							}
						}
					}
				}
			}
		}
	}


}

//===================================
//�����g���[�V����//��
//===================================
void LowerBodyEnemy3(void)
{
	if (g_Enemy.NowMotionDOWN != g_Enemy.OldMotionDOWN)
	{//�O��̃��[�V�����ƈႤ��
	//-------------------------------���Z�b�g����g
		if (g_Enemy.MotionBrend == false)
		{
			g_Enemy.NowKeyCntDOWN = 0;
			g_Enemy.NowFrameCntDOWN = 0;
			g_Enemy.EscapeMotion = g_Enemy.NowMotionDOWN;
			g_Enemy.BrendCnt = 0;
			for (int i = 0; i < MAX_PARTS_ENEMY; i++)
			{//���Z�b�g

				g_Enemy3.ModelParts[i].calculationExecution = false;
				g_Enemy3.ModelParts[i].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Enemy3.ModelParts[i].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Enemy.MotionLoopStop = false;

				g_Enemy.MotionBrend = true;

			}
		}
	}
	if (g_Enemy.MotionBrend == true)
	{//���[�V�����u�����h--����
		if (g_Enemy.BrendCnt < BRENDFLAME_ENEMY)
		{
			for (int nCntParts = 0; nCntParts < g_Enemy3.nMaxPartsCnt; nCntParts++)
			{//�p�[�c�����

					//ROT�n
				if (g_Enemy3.ModelParts[nCntParts].calculationExecution == false)
				{
					//CorrectionPos,CorrectionRot�͂����܂ŁAOFFSET��Start�n�_�Ƃ����␳�ʂȂ̂ŁA
					D3DXVECTOR3 TargetRot;
					TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					TargetRot = g_Enemy3.ModelParts[nCntParts].StartRot + g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionRot;

					g_Enemy3.ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionEnemyRot3(TargetRot - g_Enemy3.ModelParts[nCntParts].Rot, 0) / BRENDFLAME_ENEMY);

					g_Enemy3.ModelParts[nCntParts].calculationExecution = true;
				}

				g_Enemy3.ModelParts[nCntParts].Rot += g_Enemy3.ModelParts[nCntParts].CorrectCorrectionRotMove;

				//POS�n
				//--------------------------------------------------------------------------------
				if (g_Enemy3.ModelParts[nCntParts].PEARENT == -1)
				{//���������ׂĂ̐e�̎�
					D3DXVECTOR3 TargetPos;
					TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
					TargetPos = g_Enemy3.ModelParts[nCntParts].StartPos + g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionPos;

					//���݂̈ʒu����A��ŎZ�o�����ڕW�n�_�܂ł̍����v�Z
					g_Enemy3.ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Enemy3.ModelParts[nCntParts].Pos) / BRENDFLAME_ENEMY;

					//POS�̍X�V
					g_Enemy3.ModelParts[nCntParts].Pos += g_Enemy3.ModelParts[nCntParts].CorrectCorrectionPosMove;
					//------------------------------------------------------------------------------------
				}
			}

		}
		g_Enemy.BrendCnt++;

		if (g_Enemy.BrendCnt >= BRENDFLAME_ENEMY)
		{
			g_Enemy.BrendCnt = 0;

			g_Enemy.MotionBrend = false;

			g_Enemy.NowKeyCntDOWN++;//�L�[��i�߂�

			for (int nCntParts = 0; nCntParts < g_Enemy3.nMaxPartsCnt; nCntParts++)
			{//�p�[�c�����
				g_Enemy3.ModelParts[nCntParts].calculationExecution = false;
				g_Enemy3.ModelParts[nCntParts].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Enemy3.ModelParts[nCntParts].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			}
		}
	}
	else
	{

		// �{����------------------------------------------------------------------------------------------------------------------
		if (g_Enemy.MotionLoopStop == false)
		{
			if (g_Enemy.NowKeyCntDOWN == 0)
			{//0�Ԗڂ̃L�[�����f�[�^�Y���ŔF���ł��Ȃ�
				if (g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy.NowKeyCntDOWN - 1].nSplitFrame == 0)
				{//�����t���[������0�����Y���ȊO���肦�Ȃ�
					g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy.NowKeyCntDOWN - 1].nSplitFrame = g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy3.Motion[g_Enemy.NowMotionDOWN].nNumKey - 1].nSplitFrame;
					//	g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy.NowKeyCntDOWN - 1].nSplitFrame = 5;
				}

			}

			if (g_Enemy.NowFrameCntDOWN < g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy.NowKeyCntDOWN - 1].nSplitFrame)
			{//�����t���[���̕����
				if (g_Enemy.NowKeyCntDOWN < g_Enemy3.Motion[g_Enemy.NowMotionDOWN].nNumKey)
				{//�L�[�̕����
					if (g_Enemy.NowKeyCntDOWN == 12)
					{
						if (g_Enemy.NowMotionDOWN == MOTIONTYPE_ENEMY_ATTACK)
						{
							int test;

							test = 1111;
						}
					}

					for (int nCntParts = 0; nCntParts < g_Enemy3.nMaxPartsCnt; nCntParts++)
					{//�p�[�c�����
					//	if (nCntParts == 0 || (nCntParts >= 9 && nCntParts <= 14))
					//	{
							//ROT�n
						if (g_Enemy3.ModelParts[nCntParts].calculationExecution == false)
						{
							//CorrectionPos,CorrectionRot�͂����܂ŁAOFFSET��Start�n�_�Ƃ����␳�ʂȂ̂ŁA
							D3DXVECTOR3 TargetRot;
							TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

							TargetRot = g_Enemy3.ModelParts[nCntParts].StartRot + g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy.NowKeyCntDOWN].PartsData[nCntParts].CorrectionRot;

							g_Enemy3.ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionEnemyRot3(TargetRot - g_Enemy3.ModelParts[nCntParts].Rot, 0)) / g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy.NowKeyCntDOWN - 1].nSplitFrame;

							g_Enemy3.ModelParts[nCntParts].calculationExecution = true;
						}

						g_Enemy3.ModelParts[nCntParts].Rot += g_Enemy3.ModelParts[nCntParts].CorrectCorrectionRotMove;

						//POS�n
						//--------------------------------------------------------------------------------
						if (g_Enemy3.ModelParts[nCntParts].PEARENT == -1)
						{//���������ׂĂ̐e�̎�
							D3DXVECTOR3 TargetPos;
							TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

							//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
							TargetPos = g_Enemy3.ModelParts[nCntParts].StartPos + g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy.NowKeyCntDOWN].PartsData[nCntParts].CorrectionPos;

							//���݂̈ʒu����A��ŎZ�o�����ڕW�n�_�܂ł̍����v�Z
							g_Enemy3.ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Enemy3.ModelParts[nCntParts].Pos) / g_Enemy3.Motion[g_Enemy.NowMotionDOWN].KeyData[g_Enemy.NowKeyCntDOWN - 1].nSplitFrame;

							//POS�̍X�V
							g_Enemy3.ModelParts[nCntParts].Pos += g_Enemy3.ModelParts[nCntParts].CorrectCorrectionPosMove;
							//------------------------------------------------------------------------------------
						}
						//	}
					}
				}
				g_Enemy.NowFrameCntDOWN++;//�t���[���i�߂�
			}
			else
			{//�t���[����������
				g_Enemy.NowFrameCntDOWN = 0;//�t���[�����Z�b�g

				g_Enemy.NowKeyCntDOWN++;//�L�[��i�߂�

				for (int i = 0; i < MAX_PARTS_ENEMY; i++)
				{//���Z�b�g
					g_Enemy3.ModelParts[i].calculationExecution = false;
				}

				if (g_Enemy.NowKeyCntDOWN == g_Enemy3.Motion[g_Enemy.NowMotionDOWN].nNumKey)
				{//�L�[���A�ő�L�[�𒴂�����

					g_Enemy.NowFrameCntDOWN = 0;//�t���[�����Z�b�g
					g_Enemy.NowKeyCntDOWN = 0;//�L�[���Z�b�g

					if (g_Enemy3.Motion[g_Enemy.NowMotionDOWN].nLoop == 0)
					{//���[�v���Ȃ�
						if (g_Enemy.NowMotionDOWN == MOTIONTYPE_ENEMY_JUMP)
						{
							g_Enemy.MotionLoopStop = true;
						}
						else
						{//���ĈȊO
							//�ҋ@�ɂ���
							g_Enemy.NowMotionDOWN = MOTIONTYPE_ENEMY_STANDBY;//�ҋ@��Ԃɖ߂�
							//�u�����h����
							if (g_Enemy.MotionBrend == false)
							{
								g_Enemy.NowKeyCntDOWN = 0;
								g_Enemy.NowFrameCntDOWN = 0;
								g_Enemy.EscapeMotion = g_Enemy.NowMotionDOWN;
								g_Enemy.BrendCnt = 0;
								for (int i = 0; i < MAX_PARTS_ENEMY; i++)
								{//���Z�b�g

									g_Enemy3.ModelParts[i].calculationExecution = false;
									g_Enemy3.ModelParts[i].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
									g_Enemy3.ModelParts[i].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
									g_Enemy.MotionLoopStop = false;

									g_Enemy.MotionBrend = true;

								}
							}
						}
					}
					else
					{//���[�v

					}

				}
			}
		}
	}

}

//===================================
//�G�l�~�[�ݒ菈��
//===================================
void SetModel_Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	if (g_Enemy.bUse == false)
	{
		g_Enemy.pos = pos;	//�ʒu
		g_Enemy.rot = rot;	//����
		g_Enemy.bUse = true;
		g_Enemy.move = D3DXVECTOR3(0.0f, 0.0f, MAX_ENEMY_SPEED);
		g_Enemy.MotionBrend = true;
		g_Enemy.OldMotionDOWN = MOTIONTYPE_ENEMY_MAX;
		g_Enemy.ActionPattern = ACTIONPATTERN_ENEMY_SPAWN;
		g_Enemy.TargetMotion = MOTIONTYPE_ENEMY_MOVE;
		g_Enemy.NowKeyCntDOWN = 0;
		ActionEnemy(g_Enemy.ActionPattern, -1);
		SetEnemy_View(D3DXVECTOR3(g_Enemy.pos)
			, 250.0f
			, true
			, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.4f));
		LoadSetEnemy3();//---------------------------------------------------------���������[�h
		LowerBodyEnemy3();
	}
}
