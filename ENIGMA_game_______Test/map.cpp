//============================================================================================
//
//�}�b�vUI�\�����鏈��[result.cpp]
// Author seiya kagaya
//
//============================================================================================
//#include "item.h"
#include "map.h"
#include "game.h"
#include "particle.h"
#include "input.h"
#include "player.h"
#include "camera.h"
#include "player2.h"
#include "text.h"
#include "menu.h"


//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureMap[MAPTEXUINUM] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMap = NULL;//���_�o�b�t�@�ւ̃|���S��

MAP g_Map[MAXMAP];

//�`��\��(�A�b�v�f�[�g�ŕϓ��E�`��Ŏg�p)
bool g_DrawOK2[2] = {};//�O�Ԗڂ������ture

D3DXVECTOR2 g_UVpos[2];//�s���̂݁@

const char* g_Comment[5] = {};//Comment���i�[

//=============================
//�}�b�vUI�̏���������
//=============================
void InitMap(void)
{
	g_DrawOK2[0] = false;
	g_DrawOK2[1] = false;

	g_UVpos[0] = D3DXVECTOR2(0.5f, 0.5f);//UV��̈ʒu
	g_UVpos[1] = D3DXVECTOR2(0.5f, 0.5f);//UV��̈ʒu

	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	int nCntMap;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PlayerPin.png", &g_pTextureMap[0]);//�v���C���[�s��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Map0.png", &g_pTextureMap[1]);//�n�}//�\���H
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Map1.png", &g_pTextureMap[2]);//�n�}//�q��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Map2.png", &g_pTextureMap[3]);//�n�}//���r���O
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Map3.png", &g_pTextureMap[4]);//�n�}//����
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Map4.png", &g_pTextureMap[5]);//�n�}//����[�Ƃ肠��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\MapFrame2.png", &g_pTextureMap[6]);//�g

	//�}�b�v��
	g_Comment[0] = "      ��";
	g_Comment[1] = "     �q��";
	g_Comment[2] = "  ���r���O";
	g_Comment[3] = "     ����";
	g_Comment[4] = "�@  �}�b�v";


	//�}�b�vUI�̏��̏�����(�����鏉���n�_)
	for (nCntMap = 0; nCntMap < MAXMAP; nCntMap++)
	{
		g_Map[nCntMap].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Map[nCntMap].UItype = MAP_UI_TYPE_MAX;
		g_Map[nCntMap].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Map[nCntMap].ScreenNum = -1;
		g_Map[nCntMap].PosNum = -1;
		//�Ίp���̒������Z�o
		g_Map[nCntMap].fLength = sqrtf(MAPPINSIZE2 * MAPPINSIZE2 + MAPPINSIZE2 * MAPPINSIZE2) / 2.0f;//��*��+����*����

		//�Ίp���̊p�x���Z�o
		g_Map[nCntMap].fAngle = atan2f(MAPPINSIZE2, MAPPINSIZE2);//�����A��

		g_Map[nCntMap].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAXMAP, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMap, NULL);

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMap->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntMap = 0; nCntMap < MAXMAP; nCntMap++)
	{
		//���_���W�̍X�V-----------------------------------
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;//�l�͌Œ�
		pVtx[1].rhw = 1.0f;//�l�͌Œ�
		pVtx[2].rhw = 1.0f;//�l�͌Œ�
		pVtx[3].rhw = 1.0f;//�l�͌Œ�

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

		pVtx += 4;//���_�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMap->Unlock();

	//�n�}
	SetMap(D3DXVECTOR3(SCREEN_WIDE * 0.4f, SCREEN_HEIGHT * 0.78f, 0.0f), MAP_UI_TYPE_MAP1, 0);
	//�n�}
	SetMap(D3DXVECTOR3(SCREEN_WIDE * 0.9f, SCREEN_HEIGHT * 0.78f, 0.0f), MAP_UI_TYPE_MAP1, 1);

	//��
	SetMap(D3DXVECTOR3(SCREEN_WIDE * 0.4f, SCREEN_HEIGHT * 0.78f, 0.0f), MAP_UI_TYPE_PLAYERPIN_1P_0, 0);

	//�E
	SetMap(D3DXVECTOR3(SCREEN_WIDE * 0.9f, SCREEN_HEIGHT * 0.78f, 0.0f), MAP_UI_TYPE_PLAYERPIN_2P_1, 1);

	//��
	SetMap(D3DXVECTOR3(SCREEN_WIDE * 0.4f, SCREEN_HEIGHT * 0.78f, 0.0f), MAP_UI_TYPE_MAPFRAME, 0);

	SetMap(D3DXVECTOR3(SCREEN_WIDE * 0.9f, SCREEN_HEIGHT * 0.78f, 0.0f), MAP_UI_TYPE_MAPFRAME, 1);


}
//=============================
//�}�b�vUI�̏I������
//=============================
void UninitMap(void)
{
	for (int i = 0; i < MAPTEXUINUM; i++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureMap[i] != NULL)
		{
			g_pTextureMap[i]->Release();
			g_pTextureMap[i] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMap != NULL)
	{
		g_pVtxBuffMap->Release();
		g_pVtxBuffMap = NULL;
	}
}
//=============================
//�}�b�vUI�̍X�V����
//=============================
void UpdateMap(bool Draw1OK, bool Draw2OK)
{
	Player* pPlayer;
	pPlayer = GetPlayer();

	Player_2P* pPlayer2;
	pPlayer2 = GetPlayer_2P();

	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMap->Lock(0, 0, (void**)&pVtx, 0);

	g_DrawOK2[0] = Draw1OK;
	g_DrawOK2[1] = Draw2OK;



	for (int nCntMap = 0; nCntMap < MAXMAP; nCntMap++)
	{
		if (g_Map[nCntMap].bUse == true)
		{//�}�b�vUI���g�p����Ă���

	D3DXVECTOR2 EscapeUV;

			switch (g_Map[nCntMap].UItype)
			{
			case MAP_UI_TYPE_PLAYERPIN_1P_0:

				EscapeUV.x = -pPlayer->pos.x * MOVESIZE;
				EscapeUV.y = pPlayer->pos.z * MOVESIZE;

				g_UVpos[0] = EscapeUV;//UV��̈ʒu//------------------------------------�����X�|�[�������炷�K�v����
				
				g_Map[nCntMap].rot.z = -pPlayer->rot.y;

					//���_���W�̍X�V-----------------------------------
				pVtx[0].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
				pVtx[0].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
				pVtx[0].pos.z = 0.0f;

				pVtx[1].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
				pVtx[1].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
				pVtx[1].pos.z = 0.0f;

				pVtx[2].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
				pVtx[2].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
				pVtx[2].pos.z = 0.0f;

				pVtx[3].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
				pVtx[3].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
				pVtx[3].pos.z = 0.0f;

				//�e�N�X�`�����W��ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��

				break;

			case MAP_UI_TYPE_PLAYERPIN_2P_1:

				EscapeUV.x =-pPlayer2->pos.x * MOVESIZE;
				EscapeUV.y = pPlayer2->pos.z * MOVESIZE;

				g_UVpos [1]= EscapeUV;//UV��̈ʒu//------------------------------------�����X�|�[�������炷�K�v����

				g_Map[nCntMap].rot.z = -pPlayer2->rot.y;

					//���_���W�̍X�V-----------------------------------
				pVtx[0].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
				pVtx[0].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
				pVtx[0].pos.z = 0.0f;

				pVtx[1].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
				pVtx[1].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
				pVtx[1].pos.z = 0.0f;

				pVtx[2].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
				pVtx[2].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
				pVtx[2].pos.z = 0.0f;

				pVtx[3].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
				pVtx[3].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
				pVtx[3].pos.z = 0.0f;

				//�e�N�X�`�����W��ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��

				break;


	
			case MAP_UI_TYPE_PLAYERPIN_2P_0://����
				
				g_Map[nCntMap].rot.z = -pPlayer2->rot.y;


					//���_���W�̍X�V-----------------------------------
				pVtx[0].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
				pVtx[0].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
				pVtx[0].pos.z = 0.0f;

				pVtx[1].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
				pVtx[1].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
				pVtx[1].pos.z = 0.0f;

				pVtx[2].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
				pVtx[2].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
				pVtx[2].pos.z = 0.0f;

				pVtx[3].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
				pVtx[3].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
				pVtx[3].pos.z = 0.0f;

				//�e�N�X�`�����W��ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��

				break;

			case MAP_UI_TYPE_PLAYERPIN_1P_1://����

				g_Map[nCntMap].rot.z = -pPlayer->rot.y;

					//���_���W�̍X�V-----------------------------------
				pVtx[0].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
				pVtx[0].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
				pVtx[0].pos.z = 0.0f;

				pVtx[1].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
				pVtx[1].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
				pVtx[1].pos.z = 0.0f;

				pVtx[2].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
				pVtx[2].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
				pVtx[2].pos.z = 0.0f;

				pVtx[3].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
				pVtx[3].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
				pVtx[3].pos.z = 0.0f;

				//�e�N�X�`�����W��ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��
				
				break;

			case MAP_UI_TYPE_MAP1:
				
				g_UVpos[0] += MAP0_START_POS_0;
				g_UVpos[1] += MAP1_START_POS_0;

				//�e�N�X�`�����W��ݒ�
				pVtx[0].tex = D3DXVECTOR2(g_UVpos[g_Map[nCntMap].ScreenNum].x - UVSize,g_UVpos[g_Map[nCntMap].ScreenNum].y - UVSize);//����
				pVtx[1].tex = D3DXVECTOR2(g_UVpos[g_Map[nCntMap].ScreenNum].x + UVSize,g_UVpos[g_Map[nCntMap].ScreenNum].y - UVSize);//�E��
				pVtx[2].tex = D3DXVECTOR2(g_UVpos[g_Map[nCntMap].ScreenNum].x - UVSize,g_UVpos[g_Map[nCntMap].ScreenNum].y + UVSize);//����
				pVtx[3].tex = D3DXVECTOR2(g_UVpos[g_Map[nCntMap].ScreenNum].x + UVSize,g_UVpos[g_Map[nCntMap].ScreenNum].y + UVSize);//�E��
				
				break;
			}
		}
		pVtx += 4;//���_�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMap->Unlock();
}
//=============================
//�}�b�vUI�̕`�揈��
//=============================
void DrawMap(void)
{
	Player* pPlayer;
	pPlayer = GetPlayer();

	Player_2P* pPlayer2;
	pPlayer2 = GetPlayer_2P();
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	int SelectTexMap1 = GetTRansNumPlayer();
	int SelectTexMap2 = GetTRansNumPlayer2();

	int nCntMap = 0;//�}�b�v�ԍ�
	int MenutoGame=0;//�`���[�g���A������

	//map�̔ԍ��ޔ�p
	int Escape1 = 0;
	int Escape2 = 0;

	//Comment�ԍ�
	int ComentIndex = 0;
	int ComentIndex2 = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMap, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);//-------���������ς�
	for (nCntMap = 0; nCntMap < MAXMAP; nCntMap++)
	{
		if (g_Map[nCntMap].bUse == true)
		{//�}�b�vUI���g�p����Ă���
			//�e�N�X�`���C���f�b�N�X
			int SelectTex = 0;
			int SelectTex2 = 0;


			switch (g_Map[nCntMap].UItype)
			{
			case MAP_UI_TYPE_PLAYERPIN_1P_0:
				SelectTex = 0;
				break;

			case MAP_UI_TYPE_PLAYERPIN_2P_0:
				SelectTex = 0;
				break;


			case MAP_UI_TYPE_PLAYERPIN_1P_1:
				SelectTex = 0;
				break;

			case MAP_UI_TYPE_PLAYERPIN_2P_1:
				SelectTex = 0;
				break;

			case MAP_UI_TYPE_MAP1:

				if (nCntMap==0)
				{//���n�}
					switch (SelectTexMap1)
					{//�]�ڐ挟�m(����)
					case 3://�����l
						SelectTex = 3;//���r���O
						break;
					case 4://�q�ɉ�
						SelectTex = 2;//�q��
						break;
					case 5://����
						SelectTex = 4;//����
						break;
					case 6://���r���O��
						SelectTex = 3;//���r���O
						break;
					case 7://�q�ɍ�
						SelectTex = 2;//�q��
						break;
					case 8://���r���O�K�i
						SelectTex = 3;//���r���O
						break;
					}

					if (pPlayer->CrossRoadNow==true)
					{//�\���H�̂Ƃ�
						SelectTex = 1;
					}


					//���j���[����ǂ̃��[�h��I�񂾂��擾
					MenutoGame = GetMenu1();

					if (MenutoGame != START_MENU_GAME)
					{//���j���[�Łu�`���[�g���A���v��I�񂾏ꍇ
						SelectTex = 5;//�`���[�g���A���X�e�[�W
					}


					Escape1 = SelectTex;//�ۑ�
				}
				else if (nCntMap == 1)
				{//�E�n�}
					switch (SelectTexMap2)
					{//�]�ڐ挟�m(����)
					case 3://�����l
						SelectTex2 = 3;//���r���O
						break;
					case 4://�q�ɉ�
						SelectTex2 = 2;//�q��
						break;
					case 5://����
						SelectTex2 = 4;//����
						break;
					case 6://���r���O��
						SelectTex2 = 3;//���r���O
						break;
					case 7://�q�ɍ�
						SelectTex2 = 2;//�q��
						break;
					case 8://���r���O�K�i
						SelectTex2 = 3;//���r���O
						break;
					}

					if (pPlayer2->CrossRoadNow == true)
					{//�\���H�̂Ƃ�
						SelectTex2 = 1;
					}

					//���j���[����ǂ̃��[�h��I�񂾂��擾
					MenutoGame = GetMenu1();

					if (MenutoGame != START_MENU_GAME)
					{//���j���[�Łu�`���[�g���A���v��I�񂾏ꍇ
						SelectTex2 = 5;//�`���[�g���A���X�e�[�W
					}

					Escape2 = SelectTex2;//�ʒu�悤�ɕۑ�

					SelectTex = SelectTex2;//�`��p����
				}
				
				break;

			case MAP_UI_TYPE_MAPFRAME:

				SelectTex =6;
				break;
	
			}

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMap[SelectTex]);//---------���������ς�


			if (g_DrawOK2[g_Map[nCntMap].ScreenNum] == true)
			{
				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
					nCntMap * 4,//�`�悷��ŏ��̒��_�C���f�b�N�X
					2);//�`�悷��v���~�e�B�u��

				
				//�e�N�X�`����߂�
				pDevice->SetTexture(0, NULL);
			}
		}
	}

	//switch (Escape1)//���n�}�̃e�N�X�`��Index
	//{
	//case 1://�\���H
	//	break;
	//case 2://�q��
	//	break;
	//case 3://���r���O
	//	break;
	//case 4://����
	//	break;
	//case 5://�`���[�g���A��
	//	break;
	//}

	//switch (Escape2)//�E�n�}�̃e�N�X�`��Index
	//{
	//case 1://�\���H
	//	break;
	//case 2://�q��
	//	break;
	//case 3://���r���O
	//	break;
	//case 4://����
	//	break;
	//case 5://�`���[�g���A��
	//	break;
	//}
	
	//�C���f�b�N�X��ϊ�
	ComentIndex = (Escape1 - 1);
	ComentIndex2 = (Escape2 - 1);
	
	//g_Comment[ComentIndex];

	DrawTextSet(D3DXVECTOR3(SCREEN_WIDE * 0.35, 457.0f, 0.0f), 30, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "%s",g_Comment[ComentIndex]);


	DrawTextSet(D3DXVECTOR3(SCREEN_WIDE * 0.85, 457.0f, 0.0f), 30, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "%s", g_Comment[ComentIndex2]);
}
//=============================
//�}�b�vUI�̐ݒ菈��
//=============================
void SetMap(D3DXVECTOR3 pos, MAP_UI_TYPE MAPType,int ScreenNum)
{//���̂Ƃ���ł��Ăԉ\��������̂ł��̂܂܂̂ق����֗�

	VERTEX_2D* pVtx;//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMap->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMap = 0; nCntMap < MAXMAP; nCntMap++)
	{
		if (g_Map[nCntMap].bUse == false)
		{//�}�b�vUI���g�p����Ă��Ȃ�

			g_Map[nCntMap].bUse = true;//�g�p���Ă�ɂ���

			g_Map[nCntMap].pos = pos;
			g_Map[nCntMap].UItype = MAPType;

			g_Map[nCntMap].ScreenNum = ScreenNum;


				switch (MAPType)
				{
				case MAP_UI_TYPE_PLAYERPIN_1P_0:
					//���_���W�̍X�V-----------------------------------
					pVtx[0].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
					pVtx[0].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
					pVtx[0].pos.z = 0.0f;

					pVtx[1].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
					pVtx[1].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
					pVtx[1].pos.z = 0.0f;

					pVtx[2].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
					pVtx[2].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
					pVtx[2].pos.z = 0.0f;

					pVtx[3].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
					pVtx[3].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
					pVtx[3].pos.z = 0.0f;

					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

					//�e�N�X�`�����W��ݒ�
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��

					break;

				case MAP_UI_TYPE_PLAYERPIN_2P_0:
					
					//���_���W�̍X�V-----------------------------------
					pVtx[0].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
					pVtx[0].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
					pVtx[0].pos.z = 0.0f;

					pVtx[1].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
					pVtx[1].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
					pVtx[1].pos.z = 0.0f;

					pVtx[2].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
					pVtx[2].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
					pVtx[2].pos.z = 0.0f;

					pVtx[3].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
					pVtx[3].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
					pVtx[3].pos.z = 0.0f;

					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(0, 0, 255, 150);
					pVtx[1].col = D3DCOLOR_RGBA(0, 0, 255, 150);
					pVtx[2].col = D3DCOLOR_RGBA(0, 0, 255, 150);
					pVtx[3].col = D3DCOLOR_RGBA(0, 0, 255, 150);

					//�e�N�X�`�����W��ݒ�
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��

					break;


				case MAP_UI_TYPE_PLAYERPIN_1P_1:

					//���_���W�̍X�V-----------------------------------
					pVtx[0].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle +  g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
					pVtx[0].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle +  g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
					pVtx[0].pos.z = 0.0f;

					pVtx[1].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle -  g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
					pVtx[1].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle -  g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
					pVtx[1].pos.z = 0.0f;

					pVtx[2].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle -  g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
					pVtx[2].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle -  g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
					pVtx[2].pos.z = 0.0f;

					pVtx[3].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle +  g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
					pVtx[3].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle +  g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
					pVtx[3].pos.z = 0.0f;

					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 150);
					pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 150);
					pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 150);
					pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 150);

					//�e�N�X�`�����W��ݒ�
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��

					break;

				case MAP_UI_TYPE_PLAYERPIN_2P_1:

					//���_���W�̍X�V-----------------------------------
					pVtx[0].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
					pVtx[0].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
					pVtx[0].pos.z = 0.0f;

					pVtx[1].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
					pVtx[1].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
					pVtx[1].pos.z = 0.0f;

					pVtx[2].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
					pVtx[2].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//����
					pVtx[2].pos.z = 0.0f;

					pVtx[3].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
					pVtx[3].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//�E��
					pVtx[3].pos.z = 0.0f;

					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(0, 0, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(0, 0, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(0, 0, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(0, 0, 255, 255);

					//�e�N�X�`�����W��ݒ�
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��

					break;

				case MAP_UI_TYPE_MAP1:
					//���_���W�̍X�V-----------------------------------
					pVtx[0].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x - ((SCREEN_WIDE* ADDMAP_2)* ADDMAP), g_Map[nCntMap].pos.y - ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x + ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), g_Map[nCntMap].pos.y - ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x - ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), g_Map[nCntMap].pos.y + ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x + ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), g_Map[nCntMap].pos.y + ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), 0.0f);

					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);


						//�e�N�X�`�����W��ݒ�
					pVtx[0].tex = D3DXVECTOR2(g_UVpos[0].x - UVSize, g_UVpos[0].y - UVSize);//����
					pVtx[1].tex = D3DXVECTOR2(g_UVpos[0].x + UVSize, g_UVpos[0].y - UVSize);//�E��
					pVtx[2].tex = D3DXVECTOR2(g_UVpos[0].x - UVSize, g_UVpos[0].y + UVSize);//����
					pVtx[3].tex = D3DXVECTOR2(g_UVpos[0].x + UVSize, g_UVpos[0].y + UVSize);//�E��

					break;


				case MAP_UI_TYPE_MAPFRAME:
					//���_���W�̍X�V-----------------------------------
					pVtx[0].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x - ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), g_Map[nCntMap].pos.y - ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x + ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), g_Map[nCntMap].pos.y - ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x - ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), g_Map[nCntMap].pos.y + ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x + ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), g_Map[nCntMap].pos.y + ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), 0.0f);

					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

					//�e�N�X�`�����W��ݒ�
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��


					

					break;

				//case MAP_UI_TYPE_MAP2:

				//	//���_���W�̍X�V-----------------------------------
				//	pVtx[0].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x - ((SCREEN_WIDE * 0.5f) * ADDMAP), g_Map[nCntMap].pos.y - ((SCREEN_WIDE * 0.5f) * ADDMAP), 0.0f);
				//	pVtx[1].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x + ((SCREEN_WIDE * 0.5f) * ADDMAP), g_Map[nCntMap].pos.y - ((SCREEN_WIDE * 0.5f) * ADDMAP), 0.0f);
				//	pVtx[2].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x - ((SCREEN_WIDE * 0.5f) * ADDMAP), g_Map[nCntMap].pos.y + ((SCREEN_WIDE * 0.5f) * ADDMAP), 0.0f);
				//	pVtx[3].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x + ((SCREEN_WIDE * 0.5f) * ADDMAP), g_Map[nCntMap].pos.y + ((SCREEN_WIDE * 0.5f) * ADDMAP), 0.0f);

				//	//���_�J���[�̐ݒ�
				//	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
				//	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
				//	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
				//	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);

				//	//�e�N�X�`�����W��ݒ�
				//	pVtx[0].tex = D3DXVECTOR2(g_UVpos[g_Map[nCntMap].ScreenNum].x - UVSize, g_UVpos[g_Map[nCntMap].ScreenNum].y - UVSize);//����
				//	pVtx[1].tex = D3DXVECTOR2(g_UVpos[g_Map[nCntMap].ScreenNum].x + UVSize, g_UVpos[g_Map[nCntMap].ScreenNum].y - UVSize);//�E��
				//	pVtx[2].tex = D3DXVECTOR2(g_UVpos[g_Map[nCntMap].ScreenNum].x - UVSize, g_UVpos[g_Map[nCntMap].ScreenNum].y + UVSize);//����
				//	pVtx[3].tex = D3DXVECTOR2(g_UVpos[g_Map[nCntMap].ScreenNum].x + UVSize, g_UVpos[g_Map[nCntMap].ScreenNum].y + UVSize);//�E��
				//	
				//	break;
				}

				


		
			break;
		}
		pVtx += 4;//�|�C���^���S�i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMap->Unlock();
}

