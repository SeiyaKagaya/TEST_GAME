//=========================================================
//
//���f����\�����鏈��[player.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "player.h"
#include "player2.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "line.h"
#include "transfergate.h"
#include "Actionzone.h"
#include "enemy_view.h"
#include "enemy.h"
#include "bathgimmick.h"
#include "menu.h"
#include "sound.h"

//#include "sound.h"

#include <stdio.h>//�w�b�_�[�t�@�C�����C���N���[�h
#include <string.h>//������������ϐ�
#include "game.h"
#include "item.h"
#include "stage.h"
#include "hitcollision_mistake_prevention.h"



Player g_Player;//�v���C���[�S��

///-------------------------------------------------------------------------���f��
LPD3DXMESH g_pMeshModel[MAX_PARTS] = {};//���b�V��(���_���)�ւ̃|�C���^

LPD3DXBUFFER g_pBuffMatModel[MAX_PARTS] = {};//�}�e���A���ւ̃|�C���^

DWORD dwNumMatModel[MAX_PARTS] = {};//�}�e���A���̐�

MODEL g_Model;//���f���S��
//--------------------------------------------------------------------------

LPDIRECT3DTEXTURE9 g_apTexture_1P[MAX_PARTS][NUM_TEXTURE_1P] = {}; //�e�N�X�`���|�C���^

//�e���[�V�����̃��f����
char g_PlayerFileName[MAX_PARTS][MAX_WORD2][MAX_WORD] = {};//�p�X�i�[


//�ǔ������_
View g_View[4];


int g_Cnt = 0;//�e�X�g�B


bool g_test = false;

//=============================
//���f���̏���������
//=============================
void InitPlayer(void)
{
	g_Cnt = 0;

	for (int i=0; i < 4; i++)
	{
		//�����_
		if (i==0)
		{
			g_View[i].ViewPos = D3DXVECTOR3(0.0f,0.0f,0.0f);

		}
		else if(i == 1)
		{
			g_View[i].ViewPos = VIEWPOS;
		}
		else if (i == 2)
		{
			g_View[i].ViewPos = ITEMDROPPOS;
		}
		else if (i == 3)
		{
			g_View[i].ViewPos = SPEECHPOS;
		}

		g_View[i].ViewRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	g_Player.nldShadow = -4;//�e

	//�Ƃ肠�����p�[�c�̐�(���txt��)������

//	g_Player.NowMotionUP = MOTIONTYPE_1P_MAX;
	g_Player.NowMotionDOWN = MOTIONTYPE_1P_MAX;

//	g_Player.OldMotionUP = MOTIONTYPE_1P_MAX;
	g_Player.OldMotionDOWN = MOTIONTYPE_1P_MAX;

	g_Player.fRotDest = D3DX_PI;

	g_Player.nLife = MAXLIFE;


	//���j���[����ǂ̃��[�h��I�񂾂��擾
	int MenutoGame = GetMenu1();

	if (MenutoGame == START_MENU_GAME)
	{//���j���[�Łu�Q�[���X�^�[�g�v��I�񂾏ꍇ
		g_Player.pos = D3DXVECTOR3(3300.0f, 104.5f, -2000.0f);	//�ʒu
	}
	else
	{//����ȊO(�`���[�g���A����I�񂾏ꍇ)
		g_Player.pos = D3DXVECTOR3(3000.0f, 10.0f, 2500.0f);	//�ʒu
	}



	g_Player.oldPos = g_Player.pos;	//�ʒu

	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����

	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//

	g_Player.PlayerState = PLAYERSTATE_1P_NOMAL;
	g_Player.PlayerStateCnt = 0;

	g_Player.rotmove = 0.0f;
	g_Player.PARENT = -1;//�e�q�֌W

	g_Player.JumpFrame = 0;

	g_Player.bUse = false;
	g_Player.JumpNow = false;
	g_Player.JumpOld = false;

	g_Player.bMoneyBoxGimmick = false;
	g_Player.bTvGimmick = false;
	g_Player.nHaveRemocon = 0;
	g_Player.nHaveDish = 0;
	g_Player.nHaveVegetable = 0;
	g_Player.nHaveSoup= 0;

	g_Player.NowFrameCntDOWN = 0;
	g_Player.NowKeyCntDOWN = 0;

	g_Player.NowFrameCntUP = 0;
	g_Player.NowKeyCntUP = 0;
	g_Player.MotionLoopStop = false;
	g_Player.MotionBrend = false;
	g_Player.bAction = false;
	g_Player.BrendCnt = 0;
	g_Player.EscapeMotion = MOTIONTYPE_1P_BREND;
	g_Player.bTransparent = false;
	g_Player.CrossRoadNow = false;
	//-------------------------------------------------���f���n
	g_Model.nMaxMotionCnt = 0;
	g_Model.nMaxPartsCnt = 0;
	g_Model.nMaxLoadPartsCnt = 0;

	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)//�e�p�[�c�{��
	{
		g_Model.ModelParts[nCntParts].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model.ModelParts[nCntParts].Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Model.ModelParts[nCntParts].StartPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model.ModelParts[nCntParts].StartRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Model.ModelParts[nCntParts].PEARENT = 0;
		g_Model.ModelParts[nCntParts].INDEX = 0;

		g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Model.ModelParts[nCntParts].calculationExecution = false;

		//mtx�͂����Ă���
	}

	for (int nMotionCnt = 0; nMotionCnt < MAX_MONITORS; nMotionCnt++)//�e���[�V�����f�[�^
	{
		g_Model.Motion[nMotionCnt].nNumKey = 0;
		g_Model.Motion[nMotionCnt].nLoop = 0;
		g_Model.Motion[nMotionCnt].Motiontype = MOTIONTYPE_1P_MAX;


		for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)//�e���[�V�������̊e�p�[�c�̊e�L�[���̃f�[�^
		{
			g_Model.Motion[nMotionCnt].KeyData[nCntKey].nSplitFrame = 0;

			for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)//�e���[�V�������̊e�p�[�c�f�[�^
			{
				g_Model.Motion[nMotionCnt].KeyData[nCntKey].PartsData[nCntParts].CorrectionPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Model.Motion[nMotionCnt].KeyData[nCntKey].PartsData[nCntParts].CorrectionRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}

	//�e��ݒ�
	g_Player.nldShadow = SetShadow();

	LoadSet();//---------------------------------------------------------���������[�h
	LoadXfire_Player();
	

	int test;
	test = 0;
}
//=============================
//���f���̏I������
//=============================
void UninitPlayer(void)
{

	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{
		for (int nCntTex = 0; nCntTex < NUM_TEXTURE_1P; nCntTex++)
		{
			// �e�N�X�`���̔j��
			if (g_apTexture_1P[nCntModel][nCntTex] != NULL)
			{
				g_apTexture_1P[nCntModel][nCntTex]->Release();
				g_apTexture_1P[nCntModel][nCntTex] = NULL; // ������ NULL ��ݒ�
	
			}
		}

		// ���b�V���̔j��
		if (g_pMeshModel[nCntModel] != NULL)
		{
			g_pMeshModel[nCntModel]->Release();
			g_pMeshModel[nCntModel] = NULL;
		}
		// �}�e���A���̔j��
		if (g_pBuffMatModel[nCntModel] != NULL)
		{
			g_pBuffMatModel[nCntModel]->Release();
			g_pBuffMatModel[nCntModel] = NULL;
		}
	}
}
//=============================
//���f���̍X�V����
//=============================
void UpdatePlayer(void)
{


	//g_Player.bUse = true;

	if (g_Player.bUse == true)
	{
		//�v���C���[�Q�̃T�C�Y
		Player_2P* pPlayer2;
		pPlayer2 = GetPlayer_2P();
		D3DXMATRIX mtxRot, mtxTrans, mtxParent;//�v�Z�p�}�g���b�N�X

		XINPUT_STATE joykeystate;

		//�V���C�p�b�g�̏�Ԃ��擾
		DWORD dwResult = XInputGetState(0, &joykeystate);

		g_Player.JumpNow = false;
		g_Player.bLandingNow = false;
		g_Player.bAction = false;
		g_test = false;

		//---------------------------------------------------------------------------------------------------------�����ō��𑊎�Ɍ�����
	//	bool calculated = false;//���X������

		//���̊p�x
	//	float minYAngle = -0.5f; // �����̊p�x�̌��E
	//	float maxYAngle = 0.5f;  // �㑤�̊p�x�̌��E

		//-----------------------------------------------------------------------------------���͂�������
		if (CheckInputMove2() == -1)
		{//�ړ����͂Ȃ�
			if (pPlayer2->NowMotionDOWN != MOTIONTYPE_2P_MOVE)
			{
				StopSound(SOUND_LABEL_SE_WALK);
			}
			if (g_Player.NowMotionDOWN != MOTIONTYPE_1P_STANDBY && g_Player.NowMotionDOWN != MOTIONTYPE_1P_JUMP && g_Player.NowMotionDOWN != MOTIONTYPE_1P_RANDING && g_Player.NowMotionDOWN != MOTIONTYPE_1P_ATTACK)//------------------------
			{//���[�V�����ϓ�
				g_Player.NowMotionDOWN = MOTIONTYPE_1P_STANDBY;
			}

			//		if (g_Player.NowMotionUP != MOTIONTYPE_1P_ATTACK)
			//		{//���[�V�����ϓ�
			//			g_Player.NowMotionUP = MOTIONTYPE_1P_STANDBY;
			//		}
		}

		if (CheckInputMove2() == 0)
		{//�ړ����͂���
			if (dwResult == ERROR_SUCCESS)
			{//�L�[�{�[�h/�R���g���[���[���͔��f(�ړ�)
				InPutControllerPlayer();
			}
			else
			{//�L�[�{�[�h���͔��f(�ړ�)
				InPutKeyboardPlayer();
			}

		}
		//�U���n����
		InputKeyAttack();

		//�Â�pos����
		g_Player.oldPos = g_Player.pos;

		//�ʒu���X�V
		g_Player.pos += g_Player.move;


		//--------------------------------------------------------------------------------------------------------------------------------------------------//�����蔻�肱������
		//�v���C���[�̃T�C�Y
		D3DXVECTOR3 PlayerMin = D3DXVECTOR3(g_Player.pos + PLAYERMIN);
		D3DXVECTOR3 PlayerMax = D3DXVECTOR3(g_Player.pos + PLAYERMAX);

		D3DXVECTOR3 PlayerMin_2P = D3DXVECTOR3(pPlayer2->pos + PLAYERMIN_2P);
		D3DXVECTOR3 PlayerMax_2P = D3DXVECTOR3(pPlayer2->pos + PLAYERMAX_2P);

		//�v���C���[���m�����蔻��
		BoxCollisionPlayer(PlayerMin, PlayerMax, PlayerMin_2P, PlayerMax_2P, 1);

		//�G�l�~�[
		ENEMYMODEL* pEnemy;
		pEnemy = GetEnemy();
		BoxCollisionKill(PlayerMin, PlayerMax, pEnemy->MinPos, pEnemy->MaxPos, 1);


		//�A�C�e��------------------------------------------------------------------------------------------------------------------------------------------------
		ITEM* pItem;
		pItem = GetItem();

		for (int ItemCnt = 0; ItemCnt < NUMITEM; ItemCnt++)
		{
			if (pItem[ItemCnt].bUse == true)
			{
				if (pItem[ItemCnt].bGetNO == false)
				{
					BoxCollisionItem(PlayerMin, PlayerMax, pItem[ItemCnt].pos, 1, ItemCnt);
				}
			}
		}

		//�]�ږ�/-----------------------------------------------------------------------------------------------------------------------------------------
		TRANSFERGATE* pTransferGate;
		pTransferGate = GetTransferGate();

		for (int nCntGate = 0; nCntGate < MAXGATE; nCntGate++)
		{
			if (pTransferGate[nCntGate].bUse == true)
			{
				D3DXVECTOR3 GateMin = D3DXVECTOR3(pTransferGate[nCntGate].pos + pTransferGate[nCntGate].GateMin);
				D3DXVECTOR3 GateMax = D3DXVECTOR3(pTransferGate[nCntGate].pos + pTransferGate[nCntGate].GateMax);

				BoxCollisionGate(PlayerMin, PlayerMax, GateMin, GateMax, 0, pTransferGate[nCntGate].nGateIndex, pTransferGate[nCntGate].nParentIndex);

				//	break;
			}
		}


		//----------------------------------------------------------------------------���f���ڐG
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
					BoxCollisionPlayer(PlayerMin, PlayerMax, ModelMin, ModelMax, 1);
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
					BoxCollisionPlayer(PlayerMin, PlayerMax, StageMin, StageMax, 1);
				}
			}
		}


		

		//�G�̎���/-----------------------------------------------------------------------------------------------------------------------------------------
		ENEMYVIEW* pEnemyView;
		pEnemyView = GetEnemy_View();

		for (int nCntZone = 0; nCntZone < MAX_ENEMYVIEW; nCntZone++)
		{
			if (pEnemyView[nCntZone].bUse == true && pEnemyView[nCntZone].bFollowEnemy == true)
			{

				SphereEnemyView(g_Player.pos, 0, nCntZone);
				//	break;
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
				BoxCollisionPlayer(PlayerMin, PlayerMax, ColisionPreMin, ColisionPreMax, 1);

			}
		}








		////--------------------------------------------------------------------------------------------------------------------------------------------------//�����蔻�肱���܂�

		if (g_Player.pos.y <= 0.0f)
		{//�n��-0�ȉ��ɂ��Ȃ�
			g_Player.bLandingNow = true;
		}

		if (g_Player.bLandingNow == false)
		{//��
			//�ړ��ʂ��X�V(�^�������Ō���)
			g_Player.move.x += (0.0f - g_Player.move.x) * DAMPING_RATIO2;
			g_Player.move.y += (0.0f - g_Player.move.y) * DAMPING_RATIO2;
			g_Player.move.z += (0.0f - g_Player.move.z) * DAMPING_RATIO2;
		}
		else
		{//�n��
			//�ړ��ʂ��X�V(�^�������Ō���)
			g_Player.move.x += (0.0f - g_Player.move.x) * DAMPING_RATIO;
			g_Player.move.y += (0.0f - g_Player.move.y) * DAMPING_RATIO;
			g_Player.move.z += (0.0f - g_Player.move.z) * DAMPING_RATIO;
		}


		//�d��
		if (g_Player.pos.y > 0.0f)
		{//��(�n��ł͂Ȃ�)�̎�

			//�d��
			g_Player.move.y -= GRAVITY;

			if (g_Player.bLandingNow == false)
			{//�W�����v�Ŗ���
				g_Player.NowMotionDOWN = MOTIONTYPE_1P_JUMP;
			}
		}
		else
		{//�n��
			g_Player.pos.y = 0.0f;

			if (g_Player.NowMotionDOWN == MOTIONTYPE_1P_JUMP)
			{//���ł�Ƃ��ɒ��n
				g_Player.NowMotionDOWN = MOTIONTYPE_1P_RANDING;
			}
		}

		//////�N���s�G���A(���E�G���A)----------------------
		////if (g_Player.pos.x > MAXMAREA)
		////{
		////	g_Player.pos.x = (MAXMAREA - 1.0f);
		////}
		////else if (g_Player.pos.x < -MAXMAREA)
		////{
		////	g_Player.pos.x = -(MAXMAREA - 1.0f);
		////}

		////if (g_Player.pos.z > MAXMAREA)
		////{
		////	g_Player.pos.z = (MAXMAREA - 1.0f);
		////}
		////else if (g_Player.pos.z < -MAXMAREA)
		////{
		////	g_Player.pos.z = -(MAXMAREA - 1.0f);
		////}

		//�e
		SetPositionShadow(g_Player.nldShadow, g_Player.pos, SHADOWSIZE_PLAYER);

		//�㉺�̃��[�V����
		LowerBodyMotion();
		
			//�O��̃��[�V�����f�[�^���X�V
			//g_Player.OldMotionUP = g_Player.NowMotionUP;
		g_Player.OldMotionDOWN = g_Player.NowMotionDOWN;

		g_Player.JumpOld = g_Player.JumpNow;


		////---------------------------------------------------------------------------------------------------------------���Ŏg���v�Z
		//�L�����S�̂̊(�e�̐e)
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);

		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);

		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);


		//------------------------------------------------------------------------------------------------------------�����_
		Camera* pCamera;
		pCamera = GetCamera();

		D3DXMATRIX EscapeMtx;
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&EscapeMtx);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);

		D3DXMatrixMultiply(&EscapeMtx, &EscapeMtx, &mtxTrans);

		for (int i = 0; i < 4; i++)
		{
			g_View[i].ViewRot.y = -pCamera[0].rot.y;

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_View[i].ViewPosMtx);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_View[i].ViewRot.y, g_View[i].ViewRot.x, g_View[i].ViewRot.z);

			D3DXMatrixMultiply(&g_View[i].ViewPosMtx, &g_View[i].ViewPosMtx, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_View[i].ViewPos.x, g_View[i].ViewPos.y, g_View[i].ViewPos.z);

			D3DXMatrixMultiply(&g_View[i].ViewPosMtx, &g_View[i].ViewPosMtx, &mtxTrans);

			if (i == 0)
			{
				//�v���C���[�Ƃ�����
				D3DXMatrixMultiply(&g_View[i].ViewPosMtx, &g_View[i].ViewPosMtx, &EscapeMtx);

			}
			else if (i == 1)
			{
				//0�ԖڂƂ�����
				D3DXMatrixMultiply(&g_View[i].ViewPosMtx, &g_View[i].ViewPosMtx, &g_View[0].ViewPosMtx);
			}
			else if (i == 2)
			{
				//0�ԖڂƂ�����//�A�C�e���o���ʒu
				D3DXMatrixMultiply(&g_View[i].ViewPosMtx, &g_View[i].ViewPosMtx, &g_View[0].ViewPosMtx);
			}
			else if (i == 3)
			{
				//0�ԖڂƂ�����//�A�C�e���o���ʒu
				D3DXMatrixMultiply(&g_View[i].ViewPosMtx, &g_View[i].ViewPosMtx, &g_View[0].ViewPosMtx);
			}
		}
		//------------------------------------------------------------------------------------------------------------�����_




		//----------�p�[�c
		for (int nCnt = 0; nCnt < g_Model.nMaxPartsCnt; nCnt++)
		{//�p�[�c����
			//���f���̈ʒu
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Model.ModelParts[nCnt].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.ModelParts[nCnt].Rot.y, g_Model.ModelParts[nCnt].Rot.x, g_Model.ModelParts[nCnt].Rot.z);

			D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Model.ModelParts[nCnt].Pos.x, g_Model.ModelParts[nCnt].Pos.y, g_Model.ModelParts[nCnt].Pos.z);

			D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &mtxTrans);

			//�e�q�֌W
			if (g_Model.ModelParts[nCnt].PEARENT == -1)
			{
				//�v���C���[�Ƃ�����
				D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &g_Player.mtxWorld);
			}
			else
			{
				//�����̐e�̃}�g���b�N�X�����Ă�
				D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[g_Model.ModelParts[nCnt].PEARENT].mtxWorld);

			}
		}



		//�s���G���A/-----------------------------------------------------------------------------------------------------------------------------------------
		ACTIONZONE* pActionZone;
		pActionZone = GetActionZone();

		for (int nCntZone = 0; nCntZone < MAXZONE; nCntZone++)
		{
			if (pActionZone[nCntZone].bUse == true)
			{

				SphereCollisionZone(g_Player.pos, 0, nCntZone);
				//	break;
			}
		}


		for (int nWall = 0; nWall < NUMSTAGE; nWall++)
		{
			if (pStage[nWall].bUse == true)
			{
				D3DXVECTOR3 StageMin = D3DXVECTOR3(pStage[nWall].posStage + pStage[nWall].MinPos);
				D3DXVECTOR3 StageMax = D3DXVECTOR3(pStage[nWall].posStage + pStage[nWall].MaxPos);

				//��Q�����m
				AdjustPlayerPositionToCollision_VIEWPOS(D3DXVECTOR3(g_Player.pos.x, (g_Player.pos.y + g_View[1].ViewPos.y), g_Player.pos.z), 0, StageMin, StageMax);

			}
		}

		for (int i = 0; i < MAX_MODEL; i++)
		{
			if (pMapObject[i].bUse == true)
			{
				if (pMapObject[i].bCollision == true)
				{
					D3DXVECTOR3 ModelMin = D3DXVECTOR3(pMapObject[i].pos + pMapObject[i].Minpos);
					D3DXVECTOR3 ModelMax = D3DXVECTOR3(pMapObject[i].pos + pMapObject[i].Maxpos);


					//�v���C���[���m�����蔻��
					//BoxCollisionPlayer(PlayerMin, PlayerMax, ModelMin, ModelMax, 1);
					//��Q�����m
					AdjustPlayerPositionToCollision_VIEWPOS(D3DXVECTOR3(g_Player.pos.x, (g_Player.pos.y + g_View[1].ViewPos.y), g_Player.pos.z), 0, ModelMin, ModelMax);
				}
			}
		}













		//��ԑJ��
		//�v���C���[��e�U���Ǘ�
		if (g_Player.PlayerStateCnt > 0)
		{
			g_Player.PlayerStateCnt--;
		}

		if (g_Player.PlayerStateCnt <= 0)
		{
			g_Player.PlayerState = PLAYERSTATE_1P_NOMAL;

			////�U���X�g�b�v
			//VibrationLeft(0);
			//VibrationRight(0);
		}






		//MAPOBJECT *pObject;
		//pObject = GetMapObject();
		//pObject[0].pos = g_Player.pos;
	}
}
//=============================
//���f���̕`�揈��
//=============================
void DrawPlayer(int CameraLoopNum)
{

	if (g_Player.bUse == true)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXMATRIX mtxRot, mtxTrans, mtxParent;//�v�Z�p�}�g���b�N�X

		D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p(�ꎞ�ޔ�)

		D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

		//�L�����S�̂̊(�e�̐e)
			//---------------------------------------------------------------------------------------------------�v���C���[�̈ʒu�̂�
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);

		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);

		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);



		for (int nCnt = 0; nCnt < g_Model.nMaxPartsCnt; nCnt++)
		{
			//---------------------------------------------------------------------------------------------------���f���̈ʒu

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Model.ModelParts[nCnt].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.ModelParts[nCnt].Rot.y, g_Model.ModelParts[nCnt].Rot.x, g_Model.ModelParts[nCnt].Rot.z);

			D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Model.ModelParts[nCnt].Pos.x, g_Model.ModelParts[nCnt].Pos.y, g_Model.ModelParts[nCnt].Pos.z);

			D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &mtxTrans);


			//bool tttest = false;


			//for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
			//{
			//	if (pEnemy[nCntEnemy].PriorityAttackTarget == true)
			//	{
			//		D3DXVECTOR3 enemyDirection = pEnemy[nCntEnemy].pos - g_Player.pos;

			//		float angle = atan2f(enemyDirection.z, enemyDirection.x);
			//		g_Model.ModelParts[1].Rot.x = 0.0f; // �悶���h�����߂ɕK�v�Ȓ���
			//		g_Model.ModelParts[1].Rot.y = angle;
			//		g_Model.ModelParts[1].Rot.z = 0.0f;


			//		tttest = true;
			//		//�����ō����悶�点��
			//		//g_Model.ModelParts[1].Rot 
			//		//float test = atan2f(pEnemy[nCntEnemy].rot.z - g_Model.ModelParts[0].Rot.z, pEnemy[nCntEnemy].rot.x - g_Model.ModelParts[0].Rot.x);
			//		//g_Model.ModelParts[1].Rot.x = sinf(test);
			//		//g_Model.ModelParts[1].Rot.z = cosf(test);
			//	}
			//}
			//if (tttest == false)
			//{
			//	g_Model.ModelParts[1].Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//}





			//�e�q�֌W
			if (g_Model.ModelParts[nCnt].PEARENT == -1)
			{
				//�v���C���[�Ƃ�����
				D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &g_Player.mtxWorld);
			}
			else
			{
				//�����̐e�̃}�g���b�N�X�����Ă�
				D3DXMatrixMultiply(&g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[nCnt].mtxWorld, &g_Model.ModelParts[g_Model.ModelParts[nCnt].PEARENT].mtxWorld);
			}

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Model.ModelParts[nCnt].mtxWorld);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatModel[nCnt]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)dwNumMatModel[nCnt]; nCntMat++)
			{

				//------------------------�J���[�`�F���W
				if (g_test == true)
				{
						// �}�e���A���̐ݒ�
						D3DMATERIAL9 matTemp = pMat[nCntMat].MatD3D;
						matTemp.Diffuse = D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.8f);
						//matTemp.Diffuse.a = 0.5f;  // ���ߓx��ݒ�i0.0f�Ŋ��S�����A1.0f�ŕs�����j
						pDevice->SetMaterial(&matTemp);
				}
				else
				{
						//�}�e���A���̐ݒ�
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				}

				if (CameraLoopNum != 2)
				{//0�J��
					if (g_Player.bTransparent == true)
					{//����
						// �}�e���A���̐ݒ�
						D3DMATERIAL9 matTemp = pMat[nCntMat].MatD3D;
						//matTemp.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
						matTemp.Diffuse.a = 0.2f;  // ���ߓx��ݒ�i0.0f�Ŋ��S�����A1.0f�ŕs�����j
						pDevice->SetMaterial(&matTemp);
					}
				}

				//�e�N�X�`���̐ݒ�
				//pDevice->SetTexture(0, NULL);//����͐ݒ肵�Ȃ�
				//�e�N�X�`���̐ݒ�
	
				pDevice->SetTexture(0, g_apTexture_1P[nCnt][nCntMat]);
				//���f��(�p�[�c)�̕`��
				g_pMeshModel[nCnt]->DrawSubset(nCntMat);

			}
		}
		//�ۑ����Ă��}�e���A����߂�
		pDevice->SetMaterial(&matDef);

		//�e�N�X�`����߂�
		pDevice->SetTexture(0, NULL);
	}
	
}
//=============================
//�v���C���[���擾����
//=============================
Player* GetPlayer(void)
{
	return &g_Player;
}
//=============================
//�v���C���[�����_���擾����
//=============================
View* GetView(void)
{
	return &g_View[0];
}
//=============================
//�v���C���[���b�V�����擾����
//=============================
LPD3DXMESH* GetMesh_Player(void)
{
	return &g_pMeshModel[0];
}

//=============================
//�L�[�{�[�h���͔��f����(�ړ�)
//=============================
void InPutKeyboardPlayer(void)
{
	bool MoveNow = false;//�ړ����͂ł��Ă邩

//	bool NomalMove = false;//�ʏ���͂��ǂ���

	Camera* pCamera;
	pCamera = GetCamera();

	float nMoveSpeed = 0;

	//�ړ����x--�ړ����x�ϓ����ɏ��������\
	nMoveSpeed = MOVESPEED;

	float Xdate = 0.0f;
	float Zdate = 0.0f;

	//�L�[�{�[�h
	if (GetkeyboardPress(DIK_A) == true )
	{//A�������ꂽ(��)
		Xdate =
			1;
		MoveNow = true;
	}
	else if (GetkeyboardPress(DIK_D) == true )
	{//D�������ꂽ(�E)
		Xdate = -1;
		MoveNow = true;
	}

	if (GetkeyboardPress(DIK_W) == true )
	{//W�������ꂽ(��)
		Zdate = -1.0f;
		MoveNow = true;
	}
	else if (GetkeyboardPress(DIK_S) == true )
	{//S�������ꂽ(��)
		Zdate = 1.0f;
		MoveNow = true;
	}
	//�ړ������Ԃ̎�
	if (MoveNow == true)
	{
		float Angle = atan2f(Xdate, Zdate);//���ꂪ���p


		//------�����WW

		g_Player.fRotDest = (Angle - pCamera[0].rot.y - (1.0f * D3DX_PI));

		g_Player.move.x = sinf(Angle - pCamera[0].rot.y - (1.0f * D3DX_PI)) * nMoveSpeed;//�O�p�֐����p���Ĉړ��̒�������
		g_Player.move.z = cosf(Angle - pCamera[0].rot.y - (1.0f * D3DX_PI)) * nMoveSpeed;//�O�p�֐����p���Ĉړ��̒�������
	}


	//�ϊ�
	ConversionPlayerRot2(g_Player.fRotDest + D3DX_PI, 0);//D3DX_PI�͊p�x�␳
}
//=============================
//�L�[�{�[�h/�R���g���[���[���͔��f����(�ړ�)
//=============================
void InPutControllerPlayer(void)
{

	Camera* pCamera;
	pCamera = GetCamera();

	XINPUT_STATE joykeystate;




	//�V���C�p�b�g�̏�Ԃ��擾
	DWORD dwResult = XInputGetState(0, &joykeystate);




	float nMoveSpeed = 0;

	//�ړ��ʂ��ꎞ�ۑ�(�ړ��ʂ̕ϓ��Ȃǂ�)
	D3DXVECTOR3 EscapeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	bool MoveNow = false;//�ړ����͂ł��Ă邩

	bool NomalMove = false;//�ʏ���͂��ǂ���

	bool MoveNowCom = false;//�ړ����͂ł��Ă邩--Controller

	bool Sneak = false; //�X�j�[�N���Ă邩�ǂ���

	//������
	float  Split = 1.6f;




	//--�ړ����x�ϓ����ɏ��������\
	nMoveSpeed = MOVESPEED;

	//joykeystate.Gamepad.sThumbLX <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE-6000++++++++++++++++��
	//joykeystate.Gamepad.sThumbLY >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE-6000++++++++++++++++��
	//joykeystate.Gamepad.sThumbLY <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE-6000++++++++++++++��
	//joykeystate.Gamepad.sThumbLX >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE-6000+++++++++++++++�E


	//XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE+++++++++++++++++++++++++�ő�l


	//���ԓ_�܂ł̋���
	float fEscape = (32000 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000) / 2.0f;//�����𔼕���

	//���ԓ_�������ăf�b�h�]�[���ƍő�_�̒��ԓ_���Z�o(�ʏ���́A�����͂̔��ʕ���_)
	float BranchPoint = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 + fEscape;


	float Xdate = 0.0f;
	float Zdate = 0.0f;

	////�L�[�{�[�h
	//if (GetkeyboardPress(DIK_A) == true )
	//{//A�������ꂽ(��)
	//	Xdate = 
	//		1;
	//	MoveNow = true;
	//}
	//else if (GetkeyboardPress(DIK_D) == true )
	//{//D�������ꂽ(�E)
	//	Xdate = -1;
	//	MoveNow = true;
	//}

	//if (GetkeyboardPress(DIK_W) == true )
	//{//W�������ꂽ(��)
	//	 Zdate = -1.0f;
	//	 MoveNow = true;
	//}
	//else if (GetkeyboardPress(DIK_S) == true)
	//{//S�������ꂽ(��)
	//	 Zdate = 1.0f;
	//	 MoveNow = true;
	//}

	//Controller
	//--------------------------------------------------------------------------------------
	if (joykeystate.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		Sneak = true;
	}

	if ( joykeystate.Gamepad.sThumbLX <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//A�������ꂽ(��)
	//	Xdate = 1;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLX >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//D�������ꂽ(�E)
	//	Xdate = -1;
		MoveNowCom = true;
	}
	else if ( joykeystate.Gamepad.sThumbLY >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//W�������ꂽ(��)
		//Zdate = -1.0f;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLY <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//S�������ꂽ(��)
		//Zdate = 1.0f;
		MoveNowCom = true;
	}


	if (MoveNowCom == false)
	{
		//�ړ������Ԃ̎�
		if (MoveNow == true)
		{
			g_Player.NowMotionDOWN = MOTIONTYPE_1P_MOVE;

			float Angle = atan2f(Xdate, Zdate);//���ꂪ���p


			//------�����WW

			g_Player.fRotDest = (Angle - pCamera[0].rot.y - (1.0f * D3DX_PI));

			EscapeMove.x = sinf(Angle - pCamera[0].rot.y - (1.0f * D3DX_PI)) * nMoveSpeed;//�O�p�֐����p���Ĉړ��̒�������
			EscapeMove.z = cosf(Angle - pCamera[0].rot.y - (1.0f * D3DX_PI)) * nMoveSpeed;//�O�p�֐����p���Ĉړ��̒�������
		}
	}
	else
	{//Controller
		if (g_Player.NowMotionDOWN == MOTIONTYPE_1P_STANDBY)
		{
			PlaySound(SOUND_LABEL_SE_WALK);
		}
		g_Player.NowMotionDOWN = MOTIONTYPE_1P_MOVE;

		float BoostMove=1.0f;
		if (Sneak == false)
		{
			BoostMove = 1.0f;
		}
		else if (Sneak == true)
		{//�X�j�[�N������
			//���[�V�������ς���
			BoostMove = 0.5f;
		}

		float Angle2 = atan2f(-joykeystate.Gamepad.sThumbLX, -joykeystate.Gamepad.sThumbLY);//���ꂪ���p

		g_Player.fRotDest = (Angle2 - pCamera[0].rot.y - (1.0f * D3DX_PI));

		EscapeMove.x = sinf(Angle2 - pCamera[0].rot.y - (1.0f * D3DX_PI)) * nMoveSpeed* BoostMove;//�O�p�֐����p���Ĉړ��̒�������
		EscapeMove.z = cosf(Angle2 - pCamera[0].rot.y - (1.0f * D3DX_PI)) * nMoveSpeed* BoostMove;//�O�p�֐����p���Ĉړ��̒�������
		MoveNow = true;
	}



	//�ړ������Ԃ̎�
	if (MoveNow == true)
	{
		//�ʏ���͂܂œ|���Ă���
		if (BranchPoint <= joykeystate.Gamepad.sThumbLY || -BranchPoint >= joykeystate.Gamepad.sThumbLY)
		{
			NomalMove = true;//�ʏ�ړ���Ԃɂ���
		}
		if (BranchPoint <= joykeystate.Gamepad.sThumbLX || -BranchPoint >= joykeystate.Gamepad.sThumbLX)
		{
			NomalMove = true;//�ʏ�ړ���Ԃɂ���
		}

		if (NomalMove == true)
		{//�ʏ�ړ���
			g_Player.move += EscapeMove * Split;
			NomalMove = false;
		}
		else
		{
			g_Player.move += EscapeMove * (Split / 1.9f);
		}
		//���f���p�ϊ�
		ConversionPlayerRot2(g_Player.fRotDest + D3DX_PI, 0);//D3DX_PI�͊p�x�␳	
	}


}
//=============================
//�U���L�[���͏���
//=============================
void InputKeyAttack(void)
{
//
//	Camera* pCamera;
//	pCamera = GetCamera();
//
	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
	DWORD dwResult = XInputGetState(0, &joykeystate);
//
//	float	nMoveSpeed = 0.0f;
//
//
//
//	//�ړ����x--�ړ����x�ϓ����ɏ��������\
//	nMoveSpeed = MOVESPEED * 2;
//
//
//	//���̗͂L�����m�F���ĕ���
//	if (GetkeyboardPress(DIK_SPACE) == true || joykeystate.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)//�g���K�[
//	{//�X�y�[�X�������ꂽ//L2�L�[
//	//	g_Player.NowMotionUP = MOTIONTYPE_1P_ATTACK;
//		g_Player.NowMotionDOWN = MOTIONTYPE_1P_ATTACK;
//
//	}
//#if _DEBUG
//	//�W�����v
//	if (GetkeyboardPress(DIK_RETURN) || GetJoypadPress(JOYKEY_A,0) == true)
//	{//�X�y�[�X�������ꂽ(�X�y�[�X)
//		if (g_Player.JumpOld == false)
//		{
//			//	PlaySound(SOUND_LABEL_SE_JUMP);
//		}
//		g_Player.JumpNow = true;
//
//		g_Player.move.y += 2.0f;
//
//		g_test = true;
//	}
//
//
//
//
//#endif
	//�A�N�V����
	if (GetJoypadTrigger(JOYKEY_X, 0) == true)
	{
		g_Player.bAction = true;
	}
//
//	if (GetJoypadTrigger(JOYKEY_Y, 0) == true)
//	{
//		// int �� ModelType �ɃL���X�g���đ��
//		//g_MapObject_Escape[g_ModelCnt].nType = static_cast<ModelType>(Escape);
//		ITEMTYPE itemtype;
//		itemtype= static_cast<ITEMTYPE>(g_Cnt);
//
//		SetItem(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 150.0f, g_Player.pos.z), g_Player.rot, itemtype);
//
//		g_Cnt++;
//		if (g_Cnt>ITEMTYPE_MAX-1)
//		{
//			g_Cnt = 0;
//		}
//
//
//	}

}
//=============================
//�L�[�{�[�h/�R���g���[���[���͌��m����
//=============================
int CheckInputMove2(void)
{
	//0:���͗L��
	//-1:���͂Ȃ�

	XINPUT_STATE joykeystate;
	//�V���C�p�b�g�̏�Ԃ��擾
	DWORD dwResult = XInputGetState(0, &joykeystate);

	if (dwResult != ERROR_SUCCESS)
	{//Controller�Ȃ�
		if (GetkeyboardPress(DIK_A) == true)
		{//A�������ꂽ(��)
			return 0;
		}
		else if (GetkeyboardPress(DIK_D) == true)
		{//D�������ꂽ(�E)
			return 0;
		}
		else if (GetkeyboardPress(DIK_W) == true)
		{//W�������ꂽ(��)
			return 0;
		}
		else if (GetkeyboardPress(DIK_S) == true)
		{//S�������ꂽ(��)
			return 0;
		}
		else
		{//���͂Ȃ�
			return -1;
		}
	}
	else
	{//Controller�L��

		//���������炭����

		if (GetkeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT , 0) == true || joykeystate.Gamepad.sThumbLX <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 * 0.5f))
		{//A�������ꂽ(��)
			return 0;
		}
		else if (GetkeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT , 0) == true || joykeystate.Gamepad.sThumbLX >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 * 0.5f))
		{//D�������ꂽ(�E)
			return 0;
		}
		else if (GetkeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP , 0) == true || joykeystate.Gamepad.sThumbLY >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 * 0.5f))
		{//W�������ꂽ(��)
			return 0;
		}
		else if (GetkeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN , 0) == true || joykeystate.Gamepad.sThumbLY <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 * 0.5f))
		{//S�������ꂽ(��)
			return 0;
		}
		else
		{//���͂Ȃ�
			return -1;
		}
	}
}

//=============================
//�ϊ�����2D--------------------------�߂���厖
//=============================
void ConversionPlayerRot2(float fRot, int nCnt)
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
	float rotDiff = fRot - g_Player.rot.y;

	// �������͈͊O�Ȃ�␳---------------------------------------------------------------�߂����������Ɠ��e���ׂ�
	if (fabsf(rotDiff) > D3DX_PI)
	{
		rotDiff = (rotDiff < 0) ? (rotDiff + 2 * D3DX_PI) : (rotDiff - 2 * D3DX_PI);
	}

	g_Player.rot.y += rotDiff * 0.1f;

	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= (2.0f * D3DX_PI);
	}
	else if (g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rot.y += (2.0f * D3DX_PI);
	}

}
//=============================
//�ϊ�����3D--------------------------�߂���厖
//=============================
D3DXVECTOR3 ConversionPlayerRot3(D3DXVECTOR3 fRot, int nCnt)
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
void LoadXfire_Player(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntPart = 0; nCntPart < g_Model.nMaxLoadPartsCnt; nCntPart++)
	{
		
		// �t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(g_PlayerFileName[nCntPart][0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatModel[nCntPart],
			NULL,
			&dwNumMatModel[nCntPart],
			&g_pMeshModel[nCntPart]);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pBuffMatModel[nCntPart]->GetBufferPointer();


		for (int i = 0; i < (int)dwNumMatModel[nCntPart]; i++)
		{
			if (pMat[i].pTextureFilename != nullptr)
			{
				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,pMat[i].pTextureFilename,&g_apTexture_1P[nCntPart][i]);
				
				
			}
		}
	}
	g_Player.bUse = true;
}

//===================================
//�e�L�X�g����L�����̏���ǂݍ��ޏ���----------------------------------------------------------------
//===================================
void LoadSet(void)
{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	FILE* pFile;//�t�@�C���|�C���^��錾


	char aString[MAX_WORD2];	//�ǂݍ��ލő啶����

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


	pFile = fopen("data\\motion_PlayerModel.txt", "r");
 //	pFile = fopen("data\\motion_runningman.txt", "r");
//	pFile = fopen("data\\motionEnigma.txt", "r");



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
				fscanf(pFile, "%d", &g_Model.nMaxLoadPartsCnt);//���f�����i�[

			}
			else if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
			{//�e���f���̃p�[�c�̃p�X��������
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%s", &g_PlayerFileName[nEscapeCntModel][0]);//�t�@�C���p�X

				

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
						fscanf(pFile, "%d", &g_Model.nMaxPartsCnt);


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
								fscanf(pFile, "%d", &g_Model.ModelParts[nfirstEscapePartsCnt].INDEX);

							}
							else if (strcmp(&aString[0], "PARENT") == 0)
							{//�e��������
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &g_Model.ModelParts[nfirstEscapePartsCnt].PEARENT);
							}
							else if (strcmp(&aString[0], "POS") == 0)
							{//POS��������
								fscanf(pFile, "%s", &aString[0]);

								fscanf(pFile, "%f %f %f", &g_Model.ModelParts[nfirstEscapePartsCnt].Pos.x, &g_Model.ModelParts[nfirstEscapePartsCnt].Pos.y, &g_Model.ModelParts[nfirstEscapePartsCnt].Pos.z);

								//�ۑ�
								g_Model.ModelParts[nfirstEscapePartsCnt].StartPos = g_Model.ModelParts[nfirstEscapePartsCnt].Pos;

							}
							else if (strcmp(&aString[0], "ROT") == 0)
							{//ROT��������
								fscanf(pFile, "%s", &aString[0]);

								fscanf(pFile, "%f %f %f", &g_Model.ModelParts[nfirstEscapePartsCnt].Rot.x, &g_Model.ModelParts[nfirstEscapePartsCnt].Rot.y, &g_Model.ModelParts[nfirstEscapePartsCnt].Rot.z);

								//�ۑ�
								g_Model.ModelParts[nfirstEscapePartsCnt].StartRot = g_Model.ModelParts[nfirstEscapePartsCnt].Rot;
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

						g_Model.Motion[nMotionCnt].Motiontype = nMotionCnt;
						nMotionCnt++;//���[�V�����C���N�������g

						if (g_Model.nMaxMotionCnt <= nMotionCnt)
						{
							g_Model.nMaxMotionCnt = nMotionCnt;//���[�V�������͍ő�̂�
						}

						KeyCnt = 0;//�L�[�ԍ����Z�b�g

						break;
					}
					else if (strcmp(&aString[0], "LOOP") == 0)
					{//���[�v����������
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &g_Model.Motion[nMotionCnt].nLoop);
					}
					else if (strcmp(&aString[0], "NUM_KEY") == 0)//----------------�ő�L�[���ɉ��p
					{//�L�[�̐���������
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &g_Model.Motion[nMotionCnt].nNumKey);
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
								fscanf(pFile, "%d", &g_Model.Motion[nMotionCnt].KeyData[KeyCnt].nSplitFrame);//-----------------------------------���L�Ɠ���//�킯�Ȃ��ƁA��΂��ꂽ�Ƃ��ɔF���ł��Ȃ�

							}
							else if (strcmp(&aString[0], "KEY") == 0)
							{//KEY��������

								while (1)
								{
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "FRAME") == 0)
									{//�t���[���̐���������
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%d", &g_Model.Motion[nMotionCnt].KeyData[KeyCnt].nSplitFrame);///------------------------��L�Ɠ���

									}

									else if (strcmp(&aString[0], "END_KEY") == 0)
									{//�G���hKEY

										nKeyPartsCnt++;//�p�[�c�C���N�������g
										break;
									}
									else if (strcmp(&aString[0], "POS") == 0)
									{//POS����������
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%f %f %f", &g_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.x, &g_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.y, &g_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.z);///------------------------Key���Ƃ��p�[�c���Ƃŕϓ�

									}
									else if (strcmp(&aString[0], "ROT") == 0)
									{//ROT����������
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%f %f %f", &g_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.x, &g_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.y, &g_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.z);///------------------------Key���Ƃ��p�[�c���Ƃŕϓ�
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
void LowerBodyMotion(void)
{
	if (g_Player.NowMotionDOWN != g_Player.OldMotionDOWN)
	{//�O��̃��[�V�����ƈႤ��
	//-------------------------------���Z�b�g����
		g_Player.NowKeyCntDOWN = 0;
		g_Player.NowFrameCntDOWN = 0;
		g_Player.EscapeMotion = g_Player.NowMotionDOWN;
		g_Player.BrendCnt = 0;
		for (int i = 0; i < MAX_PARTS; i++)
		{//���Z�b�g

			g_Model.ModelParts[i].calculationExecution = false;
			g_Model.ModelParts[i].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model.ModelParts[i].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Player.MotionLoopStop = false;
		}
		g_Player.MotionBrend = true;
	}




	if (g_Player.MotionBrend == true)
	{//���[�V�����u�����h--����


#if 0
		for (int nCntParts = 0; nCntParts < g_Model.nMaxPartsCnt; nCntParts++)
		{//�p�[�c�����

				//ROT�n
			if (g_Model.ModelParts[nCntParts].calculationExecution == false)
			{
				//CorrectionPos,CorrectionRot�͂����܂ŁAOFFSET��Start�n�_�Ƃ����␳�ʂȂ̂ŁA
				D3DXVECTOR3 TargetRot;
				TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				TargetRot = g_Model.ModelParts[nCntParts].StartRot + g_Model.Motion[g_Player.NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionRot;

				g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionPlayerRot3(TargetRot - g_Model.ModelParts[nCntParts].Rot, 0));

				g_Model.ModelParts[nCntParts].calculationExecution = true;
			}

			g_Model.ModelParts[nCntParts].Rot += g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove;

			//POS�n
			//--------------------------------------------------------------------------------
			if (g_Model.ModelParts[nCntParts].PEARENT == -1)
			{//���������ׂĂ̐e�̎�
				D3DXVECTOR3 TargetPos;
				TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
				TargetPos = g_Model.ModelParts[nCntParts].StartPos + g_Model.Motion[g_Player.NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionPos;

				//���݂̈ʒu����A��ŎZ�o�����ڕW�n�_�܂ł̍����v�Z
				g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Model.ModelParts[nCntParts].Pos);

				//POS�̍X�V
				g_Model.ModelParts[nCntParts].Pos += g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove;
				//------------------------------------------------------------------------------------
			}
		}

		g_Player.MotionBrend = false;

		g_Player.NowKeyCntDOWN++;//�L�[��i�߂�

		for (int nCntParts = 0; nCntParts < g_Model.nMaxPartsCnt; nCntParts++)
		{//�p�[�c�����
			g_Model.ModelParts[nCntParts].calculationExecution = false;
			g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		}


#else // 1

		if (g_Player.BrendCnt < BRENDFLAME)
		{
			for (int nCntParts = 0; nCntParts < g_Model.nMaxPartsCnt; nCntParts++)
			{//�p�[�c�����

					//ROT�n
				if (g_Model.ModelParts[nCntParts].calculationExecution == false)
				{
					//CorrectionPos,CorrectionRot�͂����܂ŁAOFFSET��Start�n�_�Ƃ����␳�ʂȂ̂ŁA
					D3DXVECTOR3 TargetRot;
					TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					TargetRot = g_Model.ModelParts[nCntParts].StartRot + g_Model.Motion[g_Player.NowMotionDOWN].KeyData[1].PartsData[nCntParts].CorrectionRot;

					g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionPlayerRot3(TargetRot - g_Model.ModelParts[nCntParts].Rot, 0) / BRENDFLAME);

					g_Model.ModelParts[nCntParts].calculationExecution = true;
				}

				g_Model.ModelParts[nCntParts].Rot += g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove;

				//POS�n
				//--------------------------------------------------------------------------------
				if (g_Model.ModelParts[nCntParts].PEARENT == -1)
				{//���������ׂĂ̐e�̎�
					D3DXVECTOR3 TargetPos;
					TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
					TargetPos = g_Model.ModelParts[nCntParts].StartPos + g_Model.Motion[g_Player.NowMotionDOWN].KeyData[1].PartsData[nCntParts].CorrectionPos;

					//���݂̈ʒu����A��ŎZ�o�����ڕW�n�_�܂ł̍����v�Z
					g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Model.ModelParts[nCntParts].Pos) / BRENDFLAME;

					//POS�̍X�V
					g_Model.ModelParts[nCntParts].Pos += g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove;
					//------------------------------------------------------------------------------------
				}
			}

		}
		g_Player.BrendCnt++;

		if (g_Player.BrendCnt >= BRENDFLAME)
		{
			g_Player.BrendCnt = 0;

			g_Player.MotionBrend = false;

			g_Player.NowKeyCntDOWN++;//�L�[��i�߂�

			for (int nCntParts = 0; nCntParts < g_Model.nMaxPartsCnt; nCntParts++)
			{//�p�[�c�����
				g_Model.ModelParts[nCntParts].calculationExecution = false;
				g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			}
		}
#endif
	}
	else
	{

		// �{����------------------------------------------------------------------------------------------------------------------
		if (g_Player.MotionLoopStop == false)
		{
			if (g_Player.NowFrameCntDOWN < g_Model.Motion[g_Player.NowMotionDOWN].KeyData[g_Player.NowKeyCntDOWN /*- 1*/].nSplitFrame)
			{//�����t���[���̕����
				if (g_Player.NowKeyCntDOWN < g_Model.Motion[g_Player.NowMotionDOWN].nNumKey)
				{//�L�[�̕����

					for (int nCntParts = 0; nCntParts < g_Model.nMaxPartsCnt; nCntParts++)
					{//�p�[�c�����
					//	if (nCntParts == 0 || (nCntParts >= 9 && nCntParts <= 14))
					//	{
							//ROT�n
						if (g_Model.ModelParts[nCntParts].calculationExecution == false)
						{
							//CorrectionPos,CorrectionRot�͂����܂ŁAOFFSET��Start�n�_�Ƃ����␳�ʂȂ̂ŁA
							D3DXVECTOR3 TargetRot;
							TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

							if (g_Player.NowKeyCntDOWN != g_Model.Motion[g_Player.NowMotionDOWN].nNumKey - 1)
							{//�Ō�L�[����Ȃ�
								TargetRot = g_Model.ModelParts[nCntParts].StartRot + g_Model.Motion[g_Player.NowMotionDOWN].KeyData[g_Player.NowKeyCntDOWN + 1].PartsData[nCntParts].CorrectionRot;
							}
							else if (g_Player.NowKeyCntDOWN == g_Model.Motion[g_Player.NowMotionDOWN].nNumKey - 1)
							{//�Ō�L�[�̂Ƃ�
								TargetRot = g_Model.ModelParts[nCntParts].StartRot + g_Model.Motion[g_Player.NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionRot;
							}
							g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionPlayerRot3(TargetRot - g_Model.ModelParts[nCntParts].Rot, 0)) / g_Model.Motion[g_Player.NowMotionDOWN].KeyData[g_Player.NowKeyCntDOWN].nSplitFrame;

							g_Model.ModelParts[nCntParts].calculationExecution = true;
						}

						g_Model.ModelParts[nCntParts].Rot += g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove;

						//POS�n
						//--------------------------------------------------------------------------------
						if (g_Model.ModelParts[nCntParts].PEARENT == -1)
						{//���������ׂĂ̐e�̎�
							D3DXVECTOR3 TargetPos;
							TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
							if (g_Player.NowKeyCntDOWN != g_Model.Motion[g_Player.NowMotionDOWN].nNumKey - 1)
							{//�Ō�L�[����Ȃ�
							//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
								TargetPos = g_Model.ModelParts[nCntParts].StartPos + g_Model.Motion[g_Player.NowMotionDOWN].KeyData[g_Player.NowKeyCntDOWN + 1].PartsData[nCntParts].CorrectionPos;
							}
							else if (g_Player.NowKeyCntDOWN == g_Model.Motion[g_Player.NowMotionDOWN].nNumKey - 1)
							{//�Ō�L�[�̂Ƃ�
							//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
								TargetPos = g_Model.ModelParts[nCntParts].StartPos + g_Model.Motion[g_Player.NowMotionDOWN].KeyData[0].PartsData[nCntParts].CorrectionPos;
							}
							//���݂̈ʒu����A��ŎZ�o�����ڕW�n�_�܂ł̍����v�Z
							g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Model.ModelParts[nCntParts].Pos) / g_Model.Motion[g_Player.NowMotionDOWN].KeyData[g_Player.NowKeyCntDOWN].nSplitFrame;

							//POS�̍X�V
							g_Model.ModelParts[nCntParts].Pos += g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove;
							//------------------------------------------------------------------------------------
						}
						//	}
					}
				}
				g_Player.NowFrameCntDOWN++;//�t���[���i�߂�
			}
			else
			{//�t���[����������
				g_Player.NowFrameCntDOWN = 0;//�t���[�����Z�b�g

				g_Player.NowKeyCntDOWN++;//�L�[��i�߂�

				for (int i = 0; i < MAX_PARTS; i++)
				{//���Z�b�g
					g_Model.ModelParts[i].calculationExecution = false;
				}

				if (g_Player.NowKeyCntDOWN == g_Model.Motion[g_Player.NowMotionDOWN].nNumKey)
				{//�L�[���A�ő�L�[�𒴂�����

					g_Player.NowFrameCntDOWN = 0;//�t���[�����Z�b�g
					g_Player.NowKeyCntDOWN = 0;//�L�[���Z�b�g

					if (g_Model.Motion[g_Player.NowMotionDOWN].nLoop == 0)
					{//���[�v���Ȃ�
						if (g_Player.NowMotionDOWN == MOTIONTYPE_1P_JUMP)
						{
							g_Player.MotionLoopStop = true;
						}
						else
						{//���ĈȊO
							//�ҋ@�ɂ���
							g_Player.NowMotionDOWN = MOTIONTYPE_1P_STANDBY;//�ҋ@��Ԃɖ߂�
							//�u�����h����
							if (g_Player.MotionBrend == false)
							{
								g_Player.NowKeyCntDOWN = 0;
								g_Player.NowFrameCntDOWN = 0;
								g_Player.EscapeMotion = g_Player.NowMotionDOWN;
								g_Player.BrendCnt = 0;
								for (int i = 0; i < MAX_PARTS; i++)
								{//���Z�b�g

									g_Model.ModelParts[i].calculationExecution = false;
									g_Model.ModelParts[i].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
									g_Model.ModelParts[i].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
									g_Player.MotionLoopStop = false;

									g_Player.MotionBrend = true;

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

//
////===================================
////�㔼�g���[�V����//��
////===================================
//void UpperBodyMotion(void)
//{
//
//#if 0
//	//�㉺�ʃ��[�V����
//
//	if (g_Player.NowMotionUP != g_Player.OldMotionUP)
//	{//�O��̃��[�V�����ƈႤ��
//	//-------------------------------���Z�b�g����
//		g_Player.NowKeyCntUP = 0;
//		g_Player.NowFrameCntUP = 0;
//		for (int i = 0; i < MAX_PARTS; i++)
//		{//���Z�b�g
//			g_Model.ModelParts[i].calculationExecution = false;
//			g_Model.ModelParts[i].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			g_Model.ModelParts[i].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			g_Player.MotionLoopStop = false;
//		}
//	}
//
//	// �{����------------------------------------------------------------------------------------------------------------------
//		//1-8,15���㔼�g
//		//1�͋�----------�G�̕����Ɍ����邽�߂��������Ȃ�
//		//0�͍�
//
//		//345�����O(�E��)
//
//	if (g_Player.NowMotionUP != MOTIONTYPE_1P_ATTACK)
//	{
//		g_Player.NowMotionUP = g_Player.NowMotionDOWN;
//
//		if (g_Player.NowMotionDOWN != MOTIONTYPE_1P_MOVE)
//		{
//			g_Player.NowMotionUP = MOTIONTYPE_1P_STANDBY;
//		}
//	}
//
//
//	if (g_Player.NowFrameCntUP < g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].nSplitFrame)
//	{//�����t���[���̕����
//		if (g_Player.NowKeyCntUP < g_Model.Motion[g_Player.NowMotionUP].nNumKey)
//		{//�L�[�̕����
//
//			for (int nCntParts = 0; nCntParts < g_Model.nMaxPartsCnt; nCntParts++)
//			{//�p�[�c�����
//
//				if (nCntParts == 2 || nCntParts == 15 || nCntParts == 16 || (nCntParts >= 6 && nCntParts <= 8) || (nCntParts >= 3 && nCntParts <= 5))
//				{//�����g�A���A�E������O----------------------------------------------------------------------------��ɉE�荶��𕪂���H�H
//
//
//					//ROT�n
//					if (g_Model.ModelParts[nCntParts].calculationExecution == false)
//					{
//						//CorrectionPos,CorrectionRot�͂����܂ŁAOFFSET��Start�n�_�Ƃ����␳�ʂȂ̂ŁA
//						D3DXVECTOR3 TargetRot;
//						TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//						TargetRot = g_Model.ModelParts[nCntParts].StartRot + g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].PartsData[nCntParts].CorrectionRot;
//
//						g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionPlayerRot3(TargetRot - g_Model.ModelParts[nCntParts].Rot, 0)) / g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].nSplitFrame;
//
//						g_Model.ModelParts[nCntParts].calculationExecution = true;
//					}
//
//					g_Model.ModelParts[nCntParts].Rot += g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove;
//
//					//POS�n
//					//--------------------------------------------------------------------------------
//					if (g_Model.ModelParts[nCntParts].PEARENT == -1)
//					{//���������ׂĂ̐e�̎�
//						D3DXVECTOR3 TargetPos;
//						TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//						//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
//						TargetPos = g_Model.ModelParts[nCntParts].StartPos + g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].PartsData[nCntParts].CorrectionPos;
//
//						//���݂̈ʒu����A��ŎZ�o�����ڕW�n�_�܂ł̍����v�Z
//						g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Model.ModelParts[nCntParts].Pos) / g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].nSplitFrame;
//
//						//POS�̍X�V
//						g_Model.ModelParts[nCntParts].Pos += g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove;
//						//------------------------------------------------------------------------------------
//					}
//				}
//			}
//
//
//			//	//���ˌ�
//			//if (g_Player.NowMotionUP == MOTIONTYPE_1P_ATTACK)
//			//{
//			//	for (int i = 0; i < 2; i++)
//			//	{
//			//		if (g_Player.NowKeyCntUP == 0 && g_Player.NowFrameCntUP == g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].nSplitFrame - 1)
//			//		{
//			//		//	SetBullet(D3DXVECTOR3(mtxWorldBullet[i]._41, mtxWorldBullet[i]._42, mtxWorldBullet[i]._43), BulletMoveVec[i], 0, 0, BULLETTYPE_Player);
//			//		//	SetEffect(D3DXVECTOR3(mtxWorldBullet[i]._41, mtxWorldBullet[i]._42, mtxWorldBullet[i]._43), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 10, 2, EFECTTYPE_Boost);
//			//		}
//			//	}
//			//}
//		}
//		g_Player.NowFrameCntUP++;//�t���[���i�߂�
//	}
//	else
//	{//�t���[����������
//		g_Player.NowFrameCntUP = 0;//�t���[�����Z�b�g
//
//		g_Player.NowKeyCntUP++;//�L�[��i�߂�
//
//		for (int i = 0; i < MAX_PARTS; i++)
//		{//���Z�b�g
//			g_Model.ModelParts[i].calculationExecution = false;
//		}
//
//		if (g_Player.NowKeyCntUP == g_Model.Motion[g_Player.NowMotionUP].nNumKey)
//		{//�L�[���A�ő�L�[�𒴂�����
//
//			g_Player.NowFrameCntUP = 0;//�t���[�����Z�b�g
//			g_Player.NowKeyCntUP = 0;//�L�[���Z�b�g
//
//			if (g_Model.Motion[g_Player.NowMotionUP].nLoop == 0)
//			{//���[�v���Ȃ�
//				g_Player.NowMotionUP = MOTIONTYPE_1P_STANDBY;//�ҋ@��Ԃɖ߂�
//			}
//		}
//	}
//}
////------------------------------------------------------------�����܂�
//
//#else
//
//	//��U���ꃂ�[�V����
//
//	g_Player.OldMotionUP = g_Player.OldMotionDOWN;
//	g_Player.NowMotionUP = g_Player.NowMotionDOWN;
//
//
//	if (g_Player.NowMotionUP != g_Player.OldMotionUP)
//	{//�O��̃��[�V�����ƈႤ��
//	//-------------------------------���Z�b�g����
//		g_Player.NowKeyCntUP = 0;
//		g_Player.NowFrameCntUP = 0;
//		for (int i = 0; i < MAX_PARTS; i++)
//		{//���Z�b�g
//			g_Model.ModelParts[i].calculationExecution = false;
//			g_Model.ModelParts[i].CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			g_Model.ModelParts[i].CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			g_Player.MotionLoopStop = false;
//		}
//	}
//
//	// �{����------------------------------------------------------------------------------------------------------------------
//		//1-8,15���㔼�g
//		//1�͋�----------�G�̕����Ɍ����邽�߂��������Ȃ�
//		//0�͍�
//
//		//345�����O(�E��)
//
//	if (g_Player.NowMotionUP != MOTIONTYPE_1P_ATTACK)
//	{
//		g_Player.NowMotionUP = g_Player.NowMotionDOWN;
//
//		if (g_Player.NowMotionDOWN != MOTIONTYPE_1P_MOVE)
//		{
//			g_Player.NowMotionUP = MOTIONTYPE_1P_STANDBY;
//		}
//	}
//
//
//	if (g_Player.NowFrameCntUP < g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].nSplitFrame)
//	{//�����t���[���̕����
//		if (g_Player.NowKeyCntUP < g_Model.Motion[g_Player.NowMotionUP].nNumKey)
//		{//�L�[�̕����
//
//			for (int nCntParts = 0; nCntParts < g_Model.nMaxPartsCnt; nCntParts++)
//			{//�p�[�c�����
//
//				if (nCntParts == 2 || nCntParts == 15 || nCntParts == 16 || (nCntParts >= 6 && nCntParts <= 8) || (nCntParts >= 3 && nCntParts <= 5))
//				{//�����g
//
//					//ROT�n
//					if (g_Model.ModelParts[nCntParts].calculationExecution == false)
//					{
//						//CorrectionPos,CorrectionRot�͂����܂ŁAOFFSET��Start�n�_�Ƃ����␳�ʂȂ̂ŁA
//						D3DXVECTOR3 TargetRot;
//						TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//						TargetRot = g_Model.ModelParts[nCntParts].StartRot + g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].PartsData[nCntParts].CorrectionRot;
//
//						g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove = (ConversionPlayerRot3(TargetRot - g_Model.ModelParts[nCntParts].Rot, 0)) / g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].nSplitFrame;
//
//						g_Model.ModelParts[nCntParts].calculationExecution = true;
//					}
//
//					g_Model.ModelParts[nCntParts].Rot += g_Model.ModelParts[nCntParts].CorrectCorrectionRotMove;
//
//					//POS�n
//					//--------------------------------------------------------------------------------
//					if (g_Model.ModelParts[nCntParts].PEARENT == -1)
//					{//���������ׂĂ̐e�̎�
//						D3DXVECTOR3 TargetPos;
//						TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//						//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
//						TargetPos = g_Model.ModelParts[nCntParts].StartPos + g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].PartsData[nCntParts].CorrectionPos;
//
//						//���݂̈ʒu����A��ŎZ�o�����ڕW�n�_�܂ł̍����v�Z
//						g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove = (TargetPos - g_Model.ModelParts[nCntParts].Pos) / g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].nSplitFrame;
//
//						//POS�̍X�V
//						g_Model.ModelParts[nCntParts].Pos += g_Model.ModelParts[nCntParts].CorrectCorrectionPosMove;
//						//------------------------------------------------------------------------------------
//					}
//				}
//			}
//
//
//			//	//���ˌ�
//			//if (g_Player.NowMotionUP == MOTIONTYPE_1P_ATTACK)
//			//{
//			//	for (int i = 0; i < 2; i++)
//			//	{
//			//		if (g_Player.NowKeyCntUP == 0 && g_Player.NowFrameCntUP == g_Model.Motion[g_Player.NowMotionUP].KeyData[g_Player.NowKeyCntUP].nSplitFrame - 1)
//			//		{
//			//		//	SetBullet(D3DXVECTOR3(mtxWorldBullet[i]._41, mtxWorldBullet[i]._42, mtxWorldBullet[i]._43), BulletMoveVec[i], 0, 0, BULLETTYPE_Player);
//			//		//	SetEffect(D3DXVECTOR3(mtxWorldBullet[i]._41, mtxWorldBullet[i]._42, mtxWorldBullet[i]._43), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 10, 2, EFECTTYPE_Boost);
//			//		}
//			//	}
//			//}
//		}
//		g_Player.NowFrameCntUP++;//�t���[���i�߂�
//	}
//	else
//	{//�t���[����������
//		g_Player.NowFrameCntUP = 0;//�t���[�����Z�b�g
//
//		g_Player.NowKeyCntUP++;//�L�[��i�߂�
//
//		for (int i = 0; i < MAX_PARTS; i++)
//		{//���Z�b�g
//			g_Model.ModelParts[i].calculationExecution = false;
//		}
//
//		if (g_Player.NowKeyCntUP == g_Model.Motion[g_Player.NowMotionUP].nNumKey)
//		{//�L�[���A�ő�L�[�𒴂�����
//
//			g_Player.NowFrameCntUP = 0;//�t���[�����Z�b�g
//			g_Player.NowKeyCntUP = 0;//�L�[���Z�b�g
//
//			if (g_Model.Motion[g_Player.NowMotionUP].nLoop == 0)
//			{//���[�v���Ȃ�
//				g_Player.NowMotionUP = MOTIONTYPE_1P_STANDBY;//�ҋ@��Ԃɖ߂�
//			}
//		}
//	}
//
//
//}
////------------------------------------------------------------�����܂�
//#endif // 0
//



//===================================
//���f���擾����
//===================================
MODEL* GetModel(void)
{
	return &g_Model;
}

////===================================
////��e����
////===================================
//void HitPlayer(void)
//{
//	HP* pHP;
//	pHP = GetHP();
//
//
//	pHP[HPTYPE_PLAYER].HPstate = HPSTATE_DAMAGE;
//	pHP[HPTYPE_PLAYER].nCounterState = 3;
//
//}
