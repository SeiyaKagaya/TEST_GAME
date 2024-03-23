//============================================================================================
//
//ライトを管理する処理[camera.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "light.h"

#define LIGHTNUM	(4)//ライトの数

//プロトタイプ宣言
D3DLIGHT9 g_Light[LIGHTNUM];//ライト情報

//=============================
//ライト初期化処理
//=============================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir;	//設定用方向ベクトル

	for (int nCntLIght = 0; nCntLIght < LIGHTNUM; nCntLIght++)
	{
		//ライト情報をクリアする
		ZeroMemory(&g_Light[nCntLIght], sizeof(D3DLIGHT9));

		//ライトの種類を設定
		g_Light[nCntLIght].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの拡散光を設定
		g_Light[nCntLIght].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


		if (nCntLIght == 0)
		{
			//ライトの方向を設定
			vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
		}
		else if (nCntLIght == 1)
		{
			//ライトの方向を設定
	//		vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
									//ライトの方向を設定
			vecDir = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
		}
		else if (nCntLIght == 2)
		{
			//ライトの方向を設定
	//		vecDir = D3DXVECTOR3(-0.2f, -0.8f, -0.4f);


			//ライトの方向を設定
		//	vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

						//ライトの方向を設定
			vecDir = D3DXVECTOR3(-0.1f, 0.1f, -0.1f);
		}
		else if (nCntLIght == 3)
		{
			//ライトの方向を設定
			vecDir = D3DXVECTOR3(0.1f, 0.1f, 0.1f);

		}

		D3DXVec3Normalize(&vecDir, &vecDir);//ベクトルを正規化する

		g_Light[nCntLIght].Direction = vecDir;


		//ライトの設定をする
		pDevice->SetLight(nCntLIght, &g_Light[nCntLIght]);

		//ライトを有効化する
		pDevice->LightEnable(nCntLIght, TRUE);
	}

}
//=============================
//ライト終了処理
//=============================
void UninitLight(void)
{

}
//=============================
//ライト更新処理
//=============================
void UpdateLight(void)
{
	
}

