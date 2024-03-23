//============================================================================================
//
//とりあえずテキストでmodelセット状態のセーブとロード処理[Model_Set_Save_Lode.cpp]
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

//退避用
MAPOBJECT_ESCAPE g_MapObject_Escape[MAX_MODEL];


int g_ModelCnt = 0;//カウンター

//=============================
//初期化
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
//新規セット置き場
//=============================
void NewSet_Debug_Model(void)
{
	//+ここに新規で置くモデルの関数を置く。セーブ後はリセットすべし

	
}

//=============================
//テキストから配置物の情報を読み込む処理
//=============================
void Model_DebugLoad(void)
{
	MAPOBJECT* pMapObject;
	pMapObject = GetMapObject();
	

	FILE* pFile;//ファイルポインタを宣言


	char aString[MAX_WORD];	//読み込む最大文字数

//	int nEscapeCntModel = 0;

	pFile = fopen("data\\ARRANGEMENTS_MODEL\\ModelSet.txt", "r");

	if (pFile != NULL)
	{//ファイルが開いたら
		while (1)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "END_SCRIPT") == 0)
			{//最後にきたら
				fclose(pFile);
				break;
			}
			//else if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
			//{//各モデルのパーツのパスが来たら
			//	fscanf(pFile, "%s", &aString[0]);
			//	fscanf(pFile, "%s", &g_ModelSet[0].cModelFileName[nEscapeCntModel]);//ファイルパス

			//	nEscapeCntModel++;//モデル格納後インクリ
			//}

			else if (strcmp(&aString[0], "MODELSET") == 0)
			{//モデルセットがきたら
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "END_MODELSET") == 0)
					{
						g_MapObject_Escape[g_ModelCnt].bUse = true;//-----------ここでtrueに
						g_ModelCnt++;
						break;
					}
					else if (strcmp(&aString[0], "MODELTYPE") == 0)
					{//タイプが来たら
						fscanf(pFile, "%s", &aString[0]);

						 int Escape = 0;
						fscanf(pFile, "%d", &Escape);
						
						// int を ModelType にキャストして代入
						g_MapObject_Escape[g_ModelCnt].nType = static_cast<ModelType>(Escape);

					}
					else if (strcmp(&aString[0], "POS") == 0)
					{//POSが来たら
						fscanf(pFile, "%s", &aString[0]);

						fscanf(pFile, "%f %f %f", &g_MapObject_Escape[g_ModelCnt].pos.x, &g_MapObject_Escape[g_ModelCnt].pos.y, &g_MapObject_Escape[g_ModelCnt].pos.z);


					}
					else if (strcmp(&aString[0], "ROT") == 0)
					{//ROTが来たら
						fscanf(pFile, "%s", &aString[0]);

						fscanf(pFile, "%f %f %f", &g_MapObject_Escape[g_ModelCnt].rot.x, &g_MapObject_Escape[g_ModelCnt].rot.y, &g_MapObject_Escape[g_ModelCnt].rot.z);

					}
				}
			}
		}
	}
}



//=============================
//はじめにセット
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
//モデルセット状態をセーブ
//=============================
void Model_DebugSave(void)
{
	FILE* pFile;//ファイルポインタを宣言

	MAPOBJECT* pMapObject;
	pMapObject = GetMapObject();

   //ファイルを開く
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

		//ファイル閉じる
		fclose(pFile);
	}
	else
	{
	}

}
