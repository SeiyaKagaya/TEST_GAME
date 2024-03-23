//============================================================================================
//
//���C�g���Ǘ����鏈��[camera.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "light.h"

#define LIGHTNUM	(4)//���C�g�̐�

//�v���g�^�C�v�錾
D3DLIGHT9 g_Light[LIGHTNUM];//���C�g���

//=============================
//���C�g����������
//=============================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir;	//�ݒ�p�����x�N�g��

	for (int nCntLIght = 0; nCntLIght < LIGHTNUM; nCntLIght++)
	{
		//���C�g�����N���A����
		ZeroMemory(&g_Light[nCntLIght], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		g_Light[nCntLIght].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U����ݒ�
		g_Light[nCntLIght].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


		if (nCntLIght == 0)
		{
			//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
		}
		else if (nCntLIght == 1)
		{
			//���C�g�̕�����ݒ�
	//		vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
									//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
		}
		else if (nCntLIght == 2)
		{
			//���C�g�̕�����ݒ�
	//		vecDir = D3DXVECTOR3(-0.2f, -0.8f, -0.4f);


			//���C�g�̕�����ݒ�
		//	vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

						//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(-0.1f, 0.1f, -0.1f);
		}
		else if (nCntLIght == 3)
		{
			//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(0.1f, 0.1f, 0.1f);

		}

		D3DXVec3Normalize(&vecDir, &vecDir);//�x�N�g���𐳋K������

		g_Light[nCntLIght].Direction = vecDir;


		//���C�g�̐ݒ������
		pDevice->SetLight(nCntLIght, &g_Light[nCntLIght]);

		//���C�g��L��������
		pDevice->LightEnable(nCntLIght, TRUE);
	}

}
//=============================
//���C�g�I������
//=============================
void UninitLight(void)
{

}
//=============================
//���C�g�X�V����
//=============================
void UpdateLight(void)
{
	
}

