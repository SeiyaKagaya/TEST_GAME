//=========================================================
//
//���x���[�V�������f���\�����鏈��[advanced_motion_model.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "advanced_motion_model.h"
#include "input.h"
#include <stdio.h>//�w�b�_�[�t�@�C�����C���N���[�h
#include <string.h>//������������ϐ�
#include "game.h"




ADMODEL g_AdvancedModel[MODEL_AD_TYPE_MAX];//�v���C���[�S��

///-------------------------------------------------------------------------���f��
LPD3DXMESH g_pMeshModel_AD[MODEL_AD_TYPE_MAX][MAX_PARTS_AD] = {};//���b�V��(���_���)�ւ̃|�C���^

LPD3DXBUFFER g_pBuffMatModel_AD[MODEL_AD_TYPE_MAX][MAX_PARTS_AD] = {};//�}�e���A���ւ̃|�C���^

DWORD dwNumMatModel_AD[MODEL_AD_TYPE_MAX][MAX_PARTS_AD] = {};//�}�e���A���̐�

//PDIRECT3DTEXTURE9 g_apTextureModel_AD[MODEL_AD_TYPE_MAX][MAX_PARTS_AD][NUM_TEXTURE_AD] = {}; //�e�N�X�`���|�C���^

MODEL_AD g_Model3[MODEL_AD_TYPE_MAX];//���f���S��
//--------------------------------------------------------------------------

//���f���\����--------------------------------
typedef struct
{
	const char* pFilePass;	// MODEL�t�@�C���p�X
	MODELADTYPE MyNume;//�����ԍ��iindex�j
} MODELADINFO;





//-------------------------------------------
//�@�@"���[�V�����t�@�C���p�X","����(index)"
//-------------------------------------------
MODELADINFO g_ModelMotionInfo[MODEL_AD_TYPE_MAX] =
{							//����-----------------�e
	{"data\\motionEnigma.txt",MODEL_AD_TYPE_Test1},//�e�X�g�̂��ߏ��������K�{
	{"data\\motionEnigma.txt",MODEL_AD_TYPE_Test2},
};
//**************************
//   2/20�@�@�e�N�X�`���͐��퓮�삵�Ȃ��I�I�I�I�I���������[�N��������I
//**************************



//�e���[�V�����̃��f����
int g_nEscapeCntModel[MODEL_AD_TYPE_MAX] = {};
char g_cModelFileName[MODEL_AD_TYPE_MAX][MAX_PARTS_AD][MAX_WORD2_AD] = {};//�p�X�i�[



//=============================
//���x���[�V�������f������������
//=============================
void InitAdvancedModel(void)
{
	for (int ModelNum = 0; ModelNum < MODEL_AD_TYPE_MAX; ModelNum++)
	{
		g_nEscapeCntModel[ModelNum] = 0;

		//�Ƃ肠�����p�[�c�̐�(���txt��)������

		//g_AdvancedModel.NowMotionUP = MOTIONTYPE_AD_MAX;
		g_AdvancedModel[ModelNum].NowMotionDOWN = MOTIONTYPE_AD_MAX;

		g_AdvancedModel[ModelNum].OldMotionDOWN = MOTIONTYPE_AD_MAX;

		g_AdvancedModel[ModelNum].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);	//�ʒu


		g_AdvancedModel[ModelNum].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����

		g_AdvancedModel[ModelNum].PARENT = -1;//�e�q�֌W

		g_AdvancedModel[ModelNum].JumpFrame = 0;

		g_AdvancedModel[ModelNum].bUse = false;;
		g_AdvancedModel[ModelNum].JumpNow = false;
		g_AdvancedModel[ModelNum].JumpOld = false;

		g_AdvancedModel[ModelNum].NowFrameCntDOWN = 0;
		g_AdvancedModel[ModelNum].NowKeyCntDOWN = 0;

		g_AdvancedModel[ModelNum].NowFrameCntUP = 0;
		g_AdvancedModel[ModelNum].NowKeyCntUP = 0;
		g_AdvancedModel[ModelNum].MotionLoopStop = false;
		g_AdvancedModel[ModelNum].MotionBrend = false;

		g_AdvancedModel[ModelNum].BrendCnt = 0;
		g_AdvancedModel[ModelNum].EscapeMotion = MOTIONTYPE_AD_BREND;

		//-------------------------------------------------���f���n
		g_Model3[ModelNum].nMaxMotionCnt = 0;
		g_Model3[ModelNum].nMaxPartsCnt = 0;
		g_Model3[ModelNum].nMaxLoadPartsCnt = 0;

		for (int nCntParts = 0; nCntParts < MAX_PARTS_AD; nCntParts++)//�e�p�[�c�{��
		{
			g_Model3[ModelNum].ModelParts[nCntParts].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model3[ModelNum].ModelParts[nCntParts].Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_Model3[ModelNum].ModelParts[nCntParts].StartPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model3[ModelNum].ModelParts[nCntParts].StartRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_Model3[ModelNum].ModelParts[nCntParts].PEARENT = 0;
			g_Model3[ModelNum].ModelParts[nCntParts].INDEX = 0;

			g_Model3[ModelNum].ModelParts[nCntParts].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model3[ModelNum].ModelParts[nCntParts].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_Model3[ModelNum].ModelParts[nCntParts].calculationExecution = false;
			//mtx�͂����Ă���
		}

		for (int nMotionCnt = 0; nMotionCnt < MAX_MONITORS; nMotionCnt++)//�e���[�V�����f�[�^
		{
			g_Model3[ModelNum].Motion[nMotionCnt].nNumKey = 0;
			g_Model3[ModelNum].Motion[nMotionCnt].nLoop = 0;
			g_Model3[ModelNum].Motion[nMotionCnt].Motiontype = MOTIONTYPE_AD_MAX;


			for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)//�e���[�V�������̊e�p�[�c�̊e�L�[���̃f�[�^
			{
				g_Model3[ModelNum].Motion[nMotionCnt].KeyData[nCntKey].nSplitFrame = 0;

				for (int nCntParts = 0; nCntParts < MAX_PARTS_AD; nCntParts++)//�e���[�V�������̊e�p�[�c�f�[�^
				{
					g_Model3[ModelNum].Motion[nMotionCnt].KeyData[nCntKey].PartsData[nCntParts].CorrectionPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					g_Model3[ModelNum].Motion[nMotionCnt].KeyData[nCntKey].PartsData[nCntParts].CorrectionRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}
		}

		////////�����ŃZ�b�g
		//SetModel_AD(MODEL_AD_TYPE_Test1, D3DXVECTOR3(-50.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
		//LoadXfire_AdModel(MODEL_AD_TYPE_Test1);
		//
		//SetModel_AD(MODEL_AD_TYPE_Test2, D3DXVECTOR3(-50.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
		//LoadXfire_AdModel(MODEL_AD_TYPE_Test2);
	}
}
//=============================
//���f���̏I������
//=============================
void UninitAdvancedModel(void)
{
	for (int ModelNum = 0; ModelNum < MODEL_AD_TYPE_MAX; ModelNum++)
	{


		for (int nCntModel = 0; nCntModel < MAX_PARTS_AD; nCntModel++)
		{
			// ���b�V���̔j��
			if (g_pMeshModel_AD[ModelNum][nCntModel] != NULL)
			{
				g_pMeshModel_AD[ModelNum][nCntModel]->Release();
				g_pMeshModel_AD[ModelNum][nCntModel] = NULL; // ������ NULL ��ݒ�
			}

			// �}�e���A���̔j��
			if (g_pBuffMatModel_AD[ModelNum][nCntModel] != NULL)
			{
				g_pBuffMatModel_AD[ModelNum][nCntModel]->Release();
				g_pBuffMatModel_AD[ModelNum][nCntModel] = NULL; // ������ NULL ��ݒ�
			}

			//for (int nCntTex = 0; nCntTex < NUM_TEXTURE_AD; nCntTex++)
			//{
			//	// �e�N�X�`���̔j��
			//	if (g_apTextureModel_AD[ModelNum][nCntModel][nCntTex] != NULL)
			//	{
			//		g_apTextureModel_AD[ModelNum][nCntModel][nCntTex]->Release();
			//		g_apTextureModel_AD[ModelNum][nCntModel][nCntTex] = NULL; // ������ NULL ��ݒ�
			//	}
			//}

		}
	}



}

//=============================
//���f���̍X�V����
//=============================
void UpdateAdvancedModel(void)
{
	for (int ModelNum = 0; ModelNum < MODEL_AD_TYPE_MAX; ModelNum++)
	{
		D3DXMATRIX mtxRot, mtxTrans, mtxParent;//�v�Z�p�}�g���b�N�X	


		//�Ƃ肠�����ҋ@
		g_AdvancedModel[ModelNum].NowMotionDOWN = MOTIONTYPE_AD_STANDBY;



		//�㉺�̃��[�V����
		LowerBodyMotion3(ModelNum);
		//	UpperBodyMotion();

		//�O��̃��[�V�����f�[�^���X�V
		//g_AdvancedModel[ModelNum].OldMotionUP = g_AdvancedModel[ModelNum].NowMotionUP;
		g_AdvancedModel[ModelNum].OldMotionDOWN = g_AdvancedModel[ModelNum].NowMotionDOWN;


		//----------�p�[�c
		for (int nCnt = 0; nCnt < g_Model3[ModelNum].nMaxPartsCnt; nCnt++)
		{//�p�[�c����
			//���f���̈ʒu
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model3[ModelNum].ModelParts[nCnt].Rot.y, g_Model3[ModelNum].ModelParts[nCnt].Rot.x, g_Model3[ModelNum].ModelParts[nCnt].Rot.z);

			D3DXMatrixMultiply(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Model3[ModelNum].ModelParts[nCnt].Pos.x, g_Model3[ModelNum].ModelParts[nCnt].Pos.y, g_Model3[ModelNum].ModelParts[nCnt].Pos.z);

			D3DXMatrixMultiply(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &mtxTrans);

			//�e�q�֌W
			if (g_Model3[ModelNum].ModelParts[nCnt].PEARENT == -1)
			{
				//�v���C���[�Ƃ�����
				D3DXMatrixMultiply(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_AdvancedModel[ModelNum].mtxWorld);
			}
			else
			{
				//�����̐e�̃}�g���b�N�X�����Ă�
				D3DXMatrixMultiply(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[g_Model3[ModelNum].ModelParts[nCnt].PEARENT].mtxWorld);

			}
		}
	}
}
//=============================
//���f���̕`�揈��
//=============================
void DrawAdvancedModel(void)
{
	for (int ModelNum = 0; ModelNum < MODEL_AD_TYPE_MAX; ModelNum++)
	{
		if (g_AdvancedModel[ModelNum].bUse == true)
		{
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			D3DXMATRIX mtxRot, mtxTrans, mtxParent;//�v�Z�p�}�g���b�N�X

			D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p(�ꎞ�ޔ�)

			D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

			//�L�����S�̂̊(�e�̐e)
				//---------------------------------------------------------------------------------------------------�v���C���[�̈ʒu�̂�
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_AdvancedModel[ModelNum].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_AdvancedModel[ModelNum].rot.y, g_AdvancedModel[ModelNum].rot.x, g_AdvancedModel[ModelNum].rot.z);

			D3DXMatrixMultiply(&g_AdvancedModel[ModelNum].mtxWorld, &g_AdvancedModel[ModelNum].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_AdvancedModel[ModelNum].pos.x, g_AdvancedModel[ModelNum].pos.y, g_AdvancedModel[ModelNum].pos.z);

			D3DXMatrixMultiply(&g_AdvancedModel[ModelNum].mtxWorld, &g_AdvancedModel[ModelNum].mtxWorld, &mtxTrans);



			for (int nCnt = 0; nCnt < g_Model3[ModelNum].nMaxPartsCnt; nCnt++)
			{
				//---------------------------------------------------------------------------------------------------���f���̈ʒu

				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld);

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model3[ModelNum].ModelParts[nCnt].Rot.y, g_Model3[ModelNum].ModelParts[nCnt].Rot.x, g_Model3[ModelNum].ModelParts[nCnt].Rot.z);

				D3DXMatrixMultiply(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_Model3[ModelNum].ModelParts[nCnt].Pos.x, g_Model3[ModelNum].ModelParts[nCnt].Pos.y, g_Model3[ModelNum].ModelParts[nCnt].Pos.z);

				D3DXMatrixMultiply(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &mtxTrans);


				//�e�q�֌W
				if (g_Model3[ModelNum].ModelParts[nCnt].PEARENT == -1)
				{
					//�v���C���[�Ƃ�����
					D3DXMatrixMultiply(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_AdvancedModel[ModelNum].mtxWorld);
				}
				else
				{
					//�����̐e�̃}�g���b�N�X�����Ă�
					D3DXMatrixMultiply(&g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld, &g_Model3[ModelNum].ModelParts[g_Model3[ModelNum].ModelParts[nCnt].PEARENT].mtxWorld);
				}

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_Model3[ModelNum].ModelParts[nCnt].mtxWorld);

				//���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatModel_AD[ModelNum][nCnt]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)dwNumMatModel_AD[ModelNum][nCnt]; nCntMat++)
				{
					//�}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, NULL);//����͐ݒ肵�Ȃ�
					//�e�N�X�`���̐ݒ�
				//	pDevice->SetTexture(0, g_apTextureModel_AD[ModelNum][nCnt][nCntMat]);

					//���f��(�p�[�c)�̕`��
					g_pMeshModel_AD[ModelNum][nCnt]->DrawSubset(nCntMat);

					//�ۑ����Ă��}�e���A����߂�
				//	pDevice->SetMaterial(&matDef);
				}
			}
			//�ۑ����Ă��}�e���A����߂�
			pDevice->SetMaterial(&matDef);

			//�e�N�X�`����߂�
			pDevice->SetTexture(0, NULL);
		}
	}
}
//=============================
//�v���C���[���擾����
//=============================
ADMODEL* GetAdvancedModel(int Index)
{
	return &g_AdvancedModel[Index];
}

//=============================
//�v���C���[���b�V�����擾����
//=============================
LPD3DXMESH* GetMesh_AdvancedModel(int Index)
{
	return &g_pMeshModel_AD[Index][0];
}

//=============================
//�ϊ�����2D--------------------------�߂���厖
//=============================
void ConversionAdvancedModelRot2(int Index, float fRot, int nCnt)
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
	float rotDiff = fRot - g_AdvancedModel[Index].rot.y;

	// �������͈͊O�Ȃ�␳---------------------------------------------------------------�߂����������Ɠ��e���ׂ�
	if (fabsf(rotDiff) > D3DX_PI)
	{
		rotDiff = (rotDiff < 0) ? (rotDiff + 2 * D3DX_PI) : (rotDiff - 2 * D3DX_PI);
	}

	g_AdvancedModel[Index].rot.y += rotDiff * 0.1f;

	if (g_AdvancedModel[Index].rot.y > D3DX_PI)
	{
		g_AdvancedModel[Index].rot.y -= (2.0f * D3DX_PI);
	}
	else if (g_AdvancedModel[Index].rot.y < -D3DX_PI)
	{
		g_AdvancedModel[Index].rot.y += (2.0f * D3DX_PI);
	}

}
//=============================
//�ϊ�����3D--------------------------�߂���厖
//=============================
D3DXVECTOR3 ConversionAdvancedModelRot3(D3DXVECTOR3 fRot, int nCnt)
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
//Xfire��݂���
//===================================
void LoadXfire_AdModel(int Index)//OFF�Z�b�g�ł̏�񂩂烂�f���ǂݍ���
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < g_Model3[Index].nMaxLoadPartsCnt; nCnt++)
	{
		//�t�@�C���̓ǂݍ���----------------------
		D3DXLoadMeshFromX(&g_cModelFileName[Index][nCnt][0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatModel_AD[Index][nCnt],
			NULL,
			&dwNumMatModel_AD[Index][nCnt],
			&g_pMeshModel_AD[Index][nCnt]);

		//D3DXMATERIAL* pMat;

		////�}�e���A���f�[�^�ւ̃|�C���^���擾
		//pMat = (D3DXMATERIAL*)g_pBuffMatModel_AD[Index][nCnt]->GetBufferPointer();

		//for (int nCntMat = 0; nCntMat < (int)dwNumMatModel_AD[Index][nCnt]; nCntMat++)
		//{
		//	if (pMat[nCntMat].pTextureFilename != NULL)
		//	{
		//		//�e�N�X�`���̓ǂݍ���
		//		D3DXCreateTextureFromFile(pDevice,
		//			pMat[nCntMat].pTextureFilename,
		//			&g_apTextureModel_AD[Index][nCnt][nCntMat]
		//		);
		//	}
		//}


	}
}
//===================================
//�e�L�X�g����L�����̏���ǂݍ��ޏ���----------------------------------------------------------------
//===================================
void LoadSet3(int Index)
{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	FILE* pFile;//�t�@�C���|�C���^��錾


	char aString[MAX_WORD2_AD];	//�ǂݍ��ލő啶����

	int nModelNum;//���f��
	nModelNum = 0;



	int nfirstEscapePartsCnt;//�͂��߂Ɏg���p�[�c�J�E���g
	nfirstEscapePartsCnt = 0;

	int nMotionCnt;//���[�V�����J�E���g
	nMotionCnt = 0;

	int KeyCnt;//�L�[�J�E���g
	KeyCnt = 0;


	int nKeyPartsCnt;//�e�L�[�̒��ł̃p�[�c�J�E���g
	nKeyPartsCnt = 0;

	//char cModelFileName[MAX_PARTS_AD][MAX_WORD2_AD] = {};//�Ƃ肠����20�Ńt�@�C�������Ǘ�

	pFile = fopen(g_ModelMotionInfo[Index].pFilePass, "r");

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
				fscanf(pFile, "%d", &g_Model3[Index].nMaxLoadPartsCnt);//���f�����i�[

			}
			else if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
			{//�e���f���̃p�[�c�̃p�X��������
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%s", &g_cModelFileName[Index][nModelNum][0]);//�t�@�C���p�X



				////�t�@�C���̓ǂݍ���----------------------
				//D3DXLoadMeshFromX(&g_cModelFileName[Index][nModelNum][0],
				//	D3DXMESH_SYSTEMMEM,
				//	pDevice,
				//	NULL,
				//	&g_pBuffMatModel_AD[Index][g_nEscapeCntModel[Index]],
				//	NULL,
				//	&dwNumMatModel_AD[Index][g_nEscapeCntModel[Index]],
				//	&g_pMeshModel_AD[Index][g_nEscapeCntModel[Index]]);

				//D3DXMATERIAL* pMat;

				////�}�e���A���f�[�^�ւ̃|�C���^���擾
				//pMat = (D3DXMATERIAL*)g_pBuffMatModel_AD[Index][g_nEscapeCntModel[Index]]->GetBufferPointer();

				//for (int nCntMat = 0; nCntMat < (int)dwNumMatModel_AD[Index][g_nEscapeCntModel[Index]]; nCntMat++)
				//{
				//	if (pMat[nCntMat].pTextureFilename != NULL)
				//	{
				//		//�e�N�X�`���̓ǂݍ���
				//		D3DXCreateTextureFromFile(pDevice,
				//			pMat[nCntMat].pTextureFilename,
				//			&g_apTextureModel_AD[Index][nCntMat]
				//		);
				//	}
				//}

				nModelNum++;
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
						fscanf(pFile, "%d", &g_Model3[Index].nMaxPartsCnt);


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
								fscanf(pFile, "%d", &g_Model3[Index].ModelParts[nfirstEscapePartsCnt].INDEX);

							}
							else if (strcmp(&aString[0], "PARENT") == 0)
							{//�e��������
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &g_Model3[Index].ModelParts[nfirstEscapePartsCnt].PEARENT);
							}
							else if (strcmp(&aString[0], "POS") == 0)
							{//POS��������
								fscanf(pFile, "%s", &aString[0]);

								fscanf(pFile, "%f %f %f", &g_Model3[Index].ModelParts[nfirstEscapePartsCnt].Pos.x, &g_Model3[Index].ModelParts[nfirstEscapePartsCnt].Pos.y, &g_Model3[Index].ModelParts[nfirstEscapePartsCnt].Pos.z);

								//�ۑ�
								g_Model3[Index].ModelParts[nfirstEscapePartsCnt].StartPos = g_Model3[Index].ModelParts[nfirstEscapePartsCnt].Pos;

							}
							else if (strcmp(&aString[0], "ROT") == 0)
							{//ROT��������
								fscanf(pFile, "%s", &aString[0]);

								fscanf(pFile, "%f %f %f", &g_Model3[Index].ModelParts[nfirstEscapePartsCnt].Rot.x, &g_Model3[Index].ModelParts[nfirstEscapePartsCnt].Rot.y, &g_Model3[Index].ModelParts[nfirstEscapePartsCnt].Rot.z);

								//�ۑ�
								g_Model3[Index].ModelParts[nfirstEscapePartsCnt].StartRot = g_Model3[Index].ModelParts[nfirstEscapePartsCnt].Rot;
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

						g_Model3[Index].Motion[nMotionCnt].Motiontype = nMotionCnt;
						nMotionCnt++;//���[�V�����C���N�������g

						if (g_Model3[Index].nMaxMotionCnt <= nMotionCnt)
						{
							g_Model3[Index].nMaxMotionCnt = nMotionCnt;//���[�V�������͍ő�̂�
						}

						KeyCnt = 0;//�L�[�ԍ����Z�b�g

						break;
					}
					else if (strcmp(&aString[0], "LOOP") == 0)
					{//���[�v����������
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &g_Model3[Index].Motion[nMotionCnt].nLoop);
					}
					else if (strcmp(&aString[0], "NUM_KEY") == 0)//----------------�ő�L�[���ɉ��p
					{//�L�[�̐���������
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &g_Model3[Index].Motion[nMotionCnt].nNumKey);
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
								fscanf(pFile, "%d", &g_Model3[Index].Motion[nMotionCnt].KeyData[KeyCnt].nSplitFrame);//-----------------------------------���L�Ɠ���//�킯�Ȃ��ƁA��΂��ꂽ�Ƃ��ɔF���ł��Ȃ�

							}
							else if (strcmp(&aString[0], "KEY") == 0)
							{//KEY��������

								while (1)
								{
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "FRAME") == 0)
									{//�t���[���̐���������
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%d", &g_Model3[Index].Motion[nMotionCnt].KeyData[KeyCnt].nSplitFrame);///------------------------��L�Ɠ���

									}

									else if (strcmp(&aString[0], "END_KEY") == 0)
									{//�G���hKEY

										nKeyPartsCnt++;//�p�[�c�C���N�������g
										break;
									}
									else if (strcmp(&aString[0], "POS") == 0)
									{//POS����������
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%f %f %f", &g_Model3[Index].Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.x, &g_Model3[Index].Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.y, &g_Model3[Index].Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.z);///------------------------Key���Ƃ��p�[�c���Ƃŕϓ�

									}
									else if (strcmp(&aString[0], "ROT") == 0)
									{//ROT����������
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%f %f %f", &g_Model3[Index].Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.x, &g_Model3[Index].Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.y, &g_Model3[Index].Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.z);///------------------------Key���Ƃ��p�[�c���Ƃŕϓ�
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
//-----------------------------------------------------------���[�V�������CPP������...����
//===================================
//�����g���[�V����//��
//===================================
void LowerBodyMotion3(int Index)
{
	if (g_AdvancedModel[Index].NowMotionDOWN != g_AdvancedModel[Index].OldMotionDOWN)
	{//�O��̃��[�V�����ƈႤ��
	//-------------------------------���Z�b�g����

		g_AdvancedModel[Index].NowKeyCntDOWN = 0;
		g_AdvancedModel[Index].NowFrameCntDOWN = 0;
		g_AdvancedModel[Index].EscapeMotion = g_AdvancedModel[Index].NowMotionDOWN;
		g_AdvancedModel[Index].BrendCnt = 0;
		for (int i = 0; i < MAX_PARTS_AD; i++)
		{//���Z�b�g

			g_Model3[Index].ModelParts[i].calculationExecution = false;
			g_Model3[Index].ModelParts[i].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model3[Index].ModelParts[i].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_AdvancedModel[Index].MotionLoopStop = false;



		}
		g_AdvancedModel[Index].MotionBrend = true;
	}




	if (g_AdvancedModel[Index].MotionBrend == true)
	{//���[�V�����u�����h--����


#if 0
		for (int nCntParts = 0; nCntParts < g_Model3[Index].nMaxPartsCnt; nCntParts++)
		{//�p�[�c�����

				//ROT�n
			if (g_Model3[Index].ModelParts[nCntParts].calculationExecution == false)
			{
				//CorrectionPos,CorrectionRot�͂����܂ŁAOFFSET��Start�n�_�Ƃ����␳�ʂȂ̂ŁA
				D3DXVECTOR3 TargetRot;
				TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				TargetRot = g_Model3[Index].ModelParts[nCntParts].StartRot + g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionRot;

				g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionAdvancedModelRot3(TargetRot - g_Model3[Index].ModelParts[nCntParts].Rot, 0));

				g_Model3[Index].ModelParts[nCntParts].calculationExecution = true;
			}

			g_Model3[Index].ModelParts[nCntParts].Rot += g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionRotMove;

			//POS�n
			//--------------------------------------------------------------------------------
			if (g_Model3[Index].ModelParts[nCntParts].PEARENT == -1)
			{//���������ׂĂ̐e�̎�
				D3DXVECTOR3 TargetPos;
				TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
				TargetPos = g_Model3[Index].ModelParts[nCntParts].StartPos + g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionPos;

				//���݂̈ʒu����A��ŎZ�o�����ڕW�n�_�܂ł̍����v�Z
				g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Model3[Index].ModelParts[nCntParts].Pos);

				//POS�̍X�V
				g_Model3[Index].ModelParts[nCntParts].Pos += g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionPosMove;
				//------------------------------------------------------------------------------------
			}
		}

		g_AdvancedModel[Index].MotionBrend = false;

		g_AdvancedModel[Index].NowKeyCntDOWN++;//�L�[��i�߂�

		for (int nCntParts = 0; nCntParts < g_Model3[Index].nMaxPartsCnt; nCntParts++)
		{//�p�[�c�����
			g_Model3[Index].ModelParts[nCntParts].calculationExecution = false;
			g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		}


#else // 1

		if (g_AdvancedModel[Index].BrendCnt < BRENDFLAME_AD)
		{
			for (int nCntParts = 0; nCntParts < g_Model3[Index].nMaxPartsCnt; nCntParts++)
			{//�p�[�c�����

					//ROT�n
				if (g_Model3[Index].ModelParts[nCntParts].calculationExecution == false)
				{
					//CorrectionPos,CorrectionRot�͂����܂ŁAOFFSET��Start�n�_�Ƃ����␳�ʂȂ̂ŁA
					D3DXVECTOR3 TargetRot;
					TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					TargetRot = g_Model3[Index].ModelParts[nCntParts].StartRot + g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionRot;

					g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionAdvancedModelRot3(TargetRot - g_Model3[Index].ModelParts[nCntParts].Rot, 0) / BRENDFLAME_AD);

					g_Model3[Index].ModelParts[nCntParts].calculationExecution = true;
				}

				g_Model3[Index].ModelParts[nCntParts].Rot += g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionRotMove;

				//POS�n
				//--------------------------------------------------------------------------------
				if (g_Model3[Index].ModelParts[nCntParts].PEARENT == -1)
				{//���������ׂĂ̐e�̎�
					D3DXVECTOR3 TargetPos;
					TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
					TargetPos = g_Model3[Index].ModelParts[nCntParts].StartPos + g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionPos;

					//���݂̈ʒu����A��ŎZ�o�����ڕW�n�_�܂ł̍����v�Z
					g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Model3[Index].ModelParts[nCntParts].Pos) / BRENDFLAME_AD;

					//POS�̍X�V
					g_Model3[Index].ModelParts[nCntParts].Pos += g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionPosMove;
					//------------------------------------------------------------------------------------
				}
			}

		}
		g_AdvancedModel[Index].BrendCnt++;

		if (g_AdvancedModel[Index].BrendCnt >= BRENDFLAME_AD)
		{
			g_AdvancedModel[Index].BrendCnt = 0;

			g_AdvancedModel[Index].MotionBrend = false;

			g_AdvancedModel[Index].NowKeyCntDOWN++;//�L�[��i�߂�

			for (int nCntParts = 0; nCntParts < g_Model3[Index].nMaxPartsCnt; nCntParts++)
			{//�p�[�c�����
				g_Model3[Index].ModelParts[nCntParts].calculationExecution = false;
				g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			}
		}
#endif



	}
	else
	{


		// �{����------------------------------------------------------------------------------------------------------------------
		if (g_AdvancedModel[Index].MotionLoopStop == false)
		{
			if (g_AdvancedModel[Index].NowFrameCntDOWN < g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[g_AdvancedModel[Index].NowKeyCntDOWN /*- 1*/].nSplitFrame)
			{//�����t���[���̕����
				if (g_AdvancedModel[Index].NowKeyCntDOWN < g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].nNumKey)
				{//�L�[�̕����

					for (int nCntParts = 0; nCntParts < g_Model3[Index].nMaxPartsCnt; nCntParts++)
					{//�p�[�c�����
					//	if (nCntParts == 0 || (nCntParts >= 9 && nCntParts <= 14))
					//	{
							//ROT�n
						if (g_Model3[Index].ModelParts[nCntParts].calculationExecution == false)
						{
							//CorrectionPos,CorrectionRot�͂����܂ŁAOFFSET��Start�n�_�Ƃ����␳�ʂȂ̂ŁA
							D3DXVECTOR3 TargetRot;
							TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

							if (g_AdvancedModel[Index].NowKeyCntDOWN != g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].nNumKey - 1)
							{//�Ō�L�[����Ȃ�
								TargetRot = g_Model3[Index].ModelParts[nCntParts].StartRot + g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[g_AdvancedModel[Index].NowKeyCntDOWN + 1].PartsData[nCntParts].CorrectionRot;
							}
							else if (g_AdvancedModel[Index].NowKeyCntDOWN == g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].nNumKey - 1)
							{//�Ō�L�[�̂Ƃ�
								TargetRot = g_Model3[Index].ModelParts[nCntParts].StartRot + g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionRot;
							}
							g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionAdvancedModelRot3(TargetRot - g_Model3[Index].ModelParts[nCntParts].Rot, 0)) / g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[g_AdvancedModel[Index].NowKeyCntDOWN].nSplitFrame;

							g_Model3[Index].ModelParts[nCntParts].calculationExecution = true;
						}

						g_Model3[Index].ModelParts[nCntParts].Rot += g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionRotMove;

						//POS�n
						//--------------------------------------------------------------------------------
						if (g_Model3[Index].ModelParts[nCntParts].PEARENT == -1)
						{//���������ׂĂ̐e�̎�
							D3DXVECTOR3 TargetPos;
							TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
							if (g_AdvancedModel[Index].NowKeyCntDOWN != g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].nNumKey - 1)
							{//�Ō�L�[����Ȃ�
							//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
								TargetPos = g_Model3[Index].ModelParts[nCntParts].StartPos + g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[g_AdvancedModel[Index].NowKeyCntDOWN + 1].PartsData[nCntParts].CorrectionPos;
							}
							else if (g_AdvancedModel[Index].NowKeyCntDOWN == g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].nNumKey - 1)
							{//�Ō�L�[�̂Ƃ�
							//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
								TargetPos = g_Model3[Index].ModelParts[nCntParts].StartPos + g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionPos;
							}
							//���݂̈ʒu����A��ŎZ�o�����ڕW�n�_�܂ł̍����v�Z
							g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Model3[Index].ModelParts[nCntParts].Pos) / g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].KeyData[g_AdvancedModel[Index].NowKeyCntDOWN].nSplitFrame;

							//POS�̍X�V
							g_Model3[Index].ModelParts[nCntParts].Pos += g_Model3[Index].ModelParts[nCntParts].CorrectCorrectionPosMove;
							//------------------------------------------------------------------------------------
						}
						//	}
					}
				}
				g_AdvancedModel[Index].NowFrameCntDOWN++;//�t���[���i�߂�
			}
			else
			{//�t���[����������
				g_AdvancedModel[Index].NowFrameCntDOWN = 0;//�t���[�����Z�b�g

				g_AdvancedModel[Index].NowKeyCntDOWN++;//�L�[��i�߂�

				for (int i = 0; i < MAX_PARTS_AD; i++)
				{//���Z�b�g
					g_Model3[Index].ModelParts[i].calculationExecution = false;
				}

				if (g_AdvancedModel[Index].NowKeyCntDOWN == g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].nNumKey)
				{//�L�[���A�ő�L�[�𒴂�����

					g_AdvancedModel[Index].NowFrameCntDOWN = 0;//�t���[�����Z�b�g
					g_AdvancedModel[Index].NowKeyCntDOWN = 0;//�L�[���Z�b�g

					if (g_Model3[Index].Motion[g_AdvancedModel[Index].NowMotionDOWN].nLoop == 0)
					{//���[�v���Ȃ�
						if (g_AdvancedModel[Index].NowMotionDOWN == MOTIONTYPE_AD_JUMP)
						{
							g_AdvancedModel[Index].MotionLoopStop = true;
						}
						else
						{//���ĈȊO
							//�ҋ@�ɂ���
							g_AdvancedModel[Index].NowMotionDOWN = MOTIONTYPE_AD_STANDBY;//�ҋ@��Ԃɖ߂�
							//�u�����h����
							if (g_AdvancedModel[Index].MotionBrend == false)
							{
								g_AdvancedModel[Index].NowKeyCntDOWN = 0;
								g_AdvancedModel[Index].NowFrameCntDOWN = 0;
								g_AdvancedModel[Index].EscapeMotion = g_AdvancedModel[Index].NowMotionDOWN;
								g_AdvancedModel[Index].BrendCnt = 0;
								for (int i = 0; i < MAX_PARTS_AD; i++)
								{//���Z�b�g

									g_Model3[Index].ModelParts[i].calculationExecution = false;
									g_Model3[Index].ModelParts[i].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
									g_Model3[Index].ModelParts[i].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
									g_AdvancedModel[Index].MotionLoopStop = false;

									g_AdvancedModel[Index].MotionBrend = true;

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
//���f���擾����
//===================================
MODEL_AD* GetAdModel(int Index)
{
	return &g_Model3[Index];
}


//===================================
//�Z�b�g
//===================================
void SetModel_AD(MODELADTYPE ModelName, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{

	g_AdvancedModel[ModelName].pos = pos;	//�ʒu
	g_AdvancedModel[ModelName].rot = rot;	//����
	g_AdvancedModel[ModelName].bUse = true;

	LoadSet3(ModelName);//---------------------------------------------------------���������[�h

}
