//============================================================================================
//
//�Ƃ肠�����e�L�X�g��model�Z�b�g��Ԃ̃Z�[�u�ƃ��[�h����[Model_Set_Save_Lode.cpp]
// Author seiya kagaya
//
//============================================================================================

#include "main.h"
#include "game.h"
#include <cstdio>
#include "player.h"
#include"model.h"


typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	ModelType  nType;
	bool bUse;

}MAPOBJECT_ESCAPE;

//�ޔ�p
MAPOBJECT_ESCAPE g_MapObject_Escape[MAX_MODEL];


int g_ModelCnt = 0;//�J�E���^�[

//=============================
//������
//=============================
void InitModel_SSL(void)
{
	g_ModelCnt = 0;

	for (int  i = 0; i < MAX_MODEL; i++)
	{
		g_MapObject_Escape[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MapObject_Escape[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MapObject_Escape[i].nType = MODELTYPE_MAX;
		g_MapObject_Escape[i].bUse = false;
	}




}
//=============================
//�V�K�Z�b�g�u����
//=============================
void NewSet_Debug_Model(void)
{
	//+�����ɐV�K�Œu�����f���̊֐���u���B�Z�[�u��̓��Z�b�g���ׂ�

	
}

//=============================
//�e�L�X�g����z�u���̏���ǂݍ��ޏ���
//=============================
void Model_DebugLoad(void)
{
	MAPOBJECT* pMapObject;
	pMapObject = GetMapObject();
	

	FILE* pFile;//�t�@�C���|�C���^��錾


	char aString[MAX_WORD];	//�ǂݍ��ލő啶����

//	int nEscapeCntModel = 0;

	pFile = fopen("data\\ARRANGEMENTS_MODEL\\ModelSet.txt", "r");

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
			//else if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
			//{//�e���f���̃p�[�c�̃p�X��������
			//	fscanf(pFile, "%s", &aString[0]);
			//	fscanf(pFile, "%s", &g_ModelSet[0].cModelFileName[nEscapeCntModel]);//�t�@�C���p�X

			//	nEscapeCntModel++;//���f���i�[��C���N��
			//}

			else if (strcmp(&aString[0], "MODELSET") == 0)
			{//���f���Z�b�g��������
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "END_MODELSET") == 0)
					{
						g_MapObject_Escape[g_ModelCnt].bUse = true;//-----------������true��
						g_ModelCnt++;
						break;
					}
					else if (strcmp(&aString[0], "MODELTYPE") == 0)
					{//�^�C�v��������
						fscanf(pFile, "%s", &aString[0]);

						 int Escape = 0;
						fscanf(pFile, "%d", &Escape);
						
						// int �� ModelType �ɃL���X�g���đ��
						g_MapObject_Escape[g_ModelCnt].nType = static_cast<ModelType>(Escape);

					}
					else if (strcmp(&aString[0], "POS") == 0)
					{//POS��������
						fscanf(pFile, "%s", &aString[0]);

						fscanf(pFile, "%f %f %f", &g_MapObject_Escape[g_ModelCnt].pos.x, &g_MapObject_Escape[g_ModelCnt].pos.y, &g_MapObject_Escape[g_ModelCnt].pos.z);


					}
					else if (strcmp(&aString[0], "ROT") == 0)
					{//ROT��������
						fscanf(pFile, "%s", &aString[0]);

						fscanf(pFile, "%f %f %f", &g_MapObject_Escape[g_ModelCnt].rot.x, &g_MapObject_Escape[g_ModelCnt].rot.y, &g_MapObject_Escape[g_ModelCnt].rot.z);

					}
				}
			}
		}
	}
}



//=============================
//�͂��߂ɃZ�b�g
//=============================
void Model_DebugSet(void)
{
	MAPOBJECT* pMapObject;
	pMapObject = GetMapObject();

	for (int i = 0; i < g_ModelCnt; i++)
	{
		if (pMapObject[i].bUse == false)
		{
			SetModel(g_MapObject_Escape[i].pos, g_MapObject_Escape[i].rot, g_MapObject_Escape[i].nType);
		}
	}
}

//=============================
//���f���Z�b�g��Ԃ��Z�[�u
//=============================
void Model_DebugSave(void)
{
	FILE* pFile;//�t�@�C���|�C���^��錾

	MAPOBJECT* pMapObject;
	pMapObject = GetMapObject();

   //�t�@�C�����J��
	pFile = fopen("data\\ARRANGEMENTS_MODEL\\ModelSet.txt", "w");

	if (pFile != NULL)
	{

		for (int i = 0; i < MAX_MODEL; i++)
		{
			if (pMapObject[i].bUse == true)
			{
				int Escape = static_cast<int>(pMapObject[i].nType);

				fprintf(pFile, "MODELSET\nPOS = %.2f %.2f %.2f\nROT = %.2f %.2f %.2f\nMODELTYPE = %d\nEND_MODELSET\n\n"
					, pMapObject[i].pos.x, pMapObject[i].pos.y, pMapObject[i].pos.z
					, pMapObject[i].rot.x, pMapObject[i].rot.y, pMapObject[i].rot.z
					, Escape);
			}
		}




		fprintf(pFile, "\nEND_SCRIPT");

		//�t�@�C������
		fclose(pFile);
	}
	else
	{
	}

}
