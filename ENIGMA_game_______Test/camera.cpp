//============================================================================================
//
//�J�������Ǘ����鏈��[camera.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "camera.h"
#include "input.h"
#include "player.h"
#include "player2.h"
#include "transfergate.h"
#include "stage.h"

//�O���[�o���ϐ��錾
Camera g_camera[MAXCAMERA] = {};//�J�����̏��


//Screen�ԍ�
//int g_CurrentScreenId;




//=============================
//�J��������������
//=============================
void InitCamera(void)
{	
	Player* pPlayer;
	pPlayer = GetPlayer();
	
	for (int nCnt = 0; nCnt < MAXCAMERA; nCnt++)
	{

		g_camera[nCnt].posV = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		g_camera[nCnt].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


		g_camera[nCnt].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera[nCnt].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		g_camera[nCnt].rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera[nCnt].posVmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);



		g_camera[nCnt].posR = pPlayer->pos;

		if (nCnt == 0)
		{//����
			g_camera[nCnt].CameraLength = CAMERALENGTH;//�ΏۂƂ̋���
		}
		else
		{
			g_camera[nCnt].CameraLength = CAMERALENGTH;//�ΏۂƂ̋���
		}

		g_camera[nCnt].PosV_V = 0.0f;
		g_camera[nCnt].PosV_X = 0.0f;


		if (nCnt == 0)
		{//����
			g_camera[nCnt].viewport.Width = (SCREEN_WIDE / 2.0f)-10.0f;//�r���[�|�[�g�̕�
			g_camera[nCnt].viewport.Height = (SCREEN_HEIGHT / 2.0f) + 20.0f;//�r���[�|�[�g�̍���

	//		g_camera[nCnt].viewport.Height = SCREEN_HEIGHT / 2.0f;//�r���[�|�[�g�̍���------------------------------------------------------------


			g_camera[nCnt].viewport.X = 0.0f;//�r���[�|�[�g�̊J�n�ʒu-X
			g_camera[nCnt].viewport.Y = 50.0f;//�r���[�|�[�g�̊J�n�ʒu-Y

					//�r���[�|�[�g�̐[�x�ݒ�
			g_camera[nCnt].viewport.MinZ = 0.0f;
			g_camera[nCnt].viewport.MaxZ = 1.0f;

		}
		else if(nCnt == 1)
		{//�E��
			g_camera[nCnt].viewport.Width = (SCREEN_WIDE / 2.0f)-10.0f;//�r���[�|�[�g�̕�
			g_camera[nCnt].viewport.Height = (SCREEN_HEIGHT / 2.0f) + 20.0f;//�r���[�|�[�g�̍���
		

	//		g_camera[nCnt].viewport.Height = SCREEN_HEIGHT / 2.0f;//�r���[�|�[�g�̍���----------------------------------------------------------



			g_camera[nCnt].viewport.X = (SCREEN_WIDE/2.0f)+10.0f;//�r���[�|�[�g�̊J�n�ʒu-X
			g_camera[nCnt].viewport.Y = 50.0f;//�r���[�|�[�g�̊J�n�ʒu-Y

					//�r���[�|�[�g�̐[�x�ݒ�
			g_camera[nCnt].viewport.MinZ = 0.0f;
			g_camera[nCnt].viewport.MaxZ = 1.0f;
		}
		else if (nCnt == 2)
		{//��ʌ��--�����Ȃ��͈�
			g_camera[nCnt].viewport.Width = 2.0f;//�r���[�|�[�g�̕�
			g_camera[nCnt].viewport.Height = 2.0f;//�r���[�|�[�g�̍���

			g_camera[nCnt].viewport.X = 70.0f;//�r���[�|�[�g�̊J�n�ʒu-X
			g_camera[nCnt].viewport.Y = 70.0f;//�r���[�|�[�g�̊J�n�ʒu-Y

					//�r���[�|�[�g�̐[�x�ݒ�
			g_camera[nCnt].viewport.MinZ = 0.0f;
			g_camera[nCnt].viewport.MaxZ = 0.0f;
		}



	




		g_camera[nCnt].OldPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}
//=============================
//�J�����I������
//=============================
void UninitCamera(void)
{

}
//=============================
//�J�����X�V����
//=============================
void UpdateCamera(void)
{
	Player* pPlayer;
	pPlayer = GetPlayer();

	Player_2P* pPlayer2;
	pPlayer2 = GetPlayer_2P();

	//�����ŏ�����
	pPlayer->bTransparent = false;
	pPlayer2->bTransparent = false;

	D3DXVECTOR3 pViewPos[MAXCAMERA];

	View* pViewMtx = GetView();

	View2* pViewMtx2 = GetView_2P();

	InputCamera();

	for (int nCnt = 0; nCnt < MAXCAMERA; nCnt++)
	{
		 pViewPos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


		 if (nCnt != 2)
		 {//��ʊO�ȊO

			 if (nCnt == 0)
			 {


				 pViewPos[nCnt] = D3DXVECTOR3(pViewMtx[1].ViewPosMtx._41, pViewMtx[1].ViewPosMtx._42, pViewMtx[1].ViewPosMtx._43);

				 g_camera[nCnt].posR = pViewPos[nCnt];

			 }
			 else if (nCnt == 1)
			 {


				 pViewPos[nCnt] = D3DXVECTOR3(pViewMtx2[1].ViewPosMtx._41, pViewMtx2[1].ViewPosMtx._42, pViewMtx2[1].ViewPosMtx._43);

				 g_camera[nCnt].posR = pViewPos[nCnt];

			 }

			 //�ʒu���X�V
			 g_camera[nCnt].posV.x += g_camera[nCnt].move.x;
			 g_camera[nCnt].posV.y += g_camera[nCnt].move.y;
			 g_camera[nCnt].posV.z += g_camera[nCnt].move.z;


			 g_camera[nCnt].rot.x += g_camera[nCnt].rotMove.x;

			 if (g_camera[nCnt].rot.x > D3DX_PI * 0.1f)//���񐧌�
			 {
				 g_camera[nCnt].rot.x = D3DX_PI * 0.0999f;
			 }
			 if (g_camera[nCnt].rot.x < -D3DX_PI * 0.1f)
			 {
				 g_camera[nCnt].rot.x = -D3DX_PI * 0.0999f;
			 }

			 g_camera[nCnt].rot.y += g_camera[nCnt].rotMove.y;
			 g_camera[nCnt].rot.z += g_camera[nCnt].rotMove.z;


			 if (g_camera[nCnt].rot.y < -3.14f)
			 {
				 g_camera[nCnt].rot.y = 3.14f;
			 }
			 else if (g_camera[nCnt].rot.y > 3.14f)
			 {
				 g_camera[nCnt].rot.y = -3.14f;
			 }







			 //���a

			 //�ɍ��W---�ォ�猩�ā@�@�@X.Y�݂̂œ��������L��--X=cosf(rot.�c��)*����----���ʁ@
			 //�b-����������݂��c      sinf(rot�c��)*����									

			 //�����猩��/////cosf(rot����)*����---����
			 //�b-�������猩���c--sinf(rot����)*����

			 //���^�p
			 //-------X=cos(�V�[�^(�p�x))*�����AY=sinf(�V�[�^(�p�x))*����
			 // 

			 //if (g_camera[nCnt].posV.y > 5.1f)//�ڐG����
			 //{//�n�ʂ��CAMERA��

			 //	g_camera[nCnt].CameraLength = CAMERALENGTH;
			 //}

																		 //��������p�x								//
			 g_camera[nCnt].posV.x = g_camera[nCnt].posR.x + g_camera[nCnt].CameraLength * cosf(g_camera[nCnt].rot.x) * sinf(g_camera[nCnt].rot.y);//1�R�T�C���V�[�^��������--�R�T�C���t�@�C��������

			 g_camera[nCnt].posV.y = g_camera[nCnt].posR.y - g_camera[nCnt].CameraLength * sinf(g_camera[nCnt].rot.x);						//2Y�͕��Ղ̂��߂����Ȃ�

			 g_camera[nCnt].posV.z = g_camera[nCnt].posR.z - g_camera[nCnt].CameraLength * cosf(g_camera[nCnt].rot.x) * cosf(g_camera[nCnt].rot.y);//3//�P�Ɠ�������
			 //posR��			������PosV	������+�ɕύX



			 g_camera[nCnt].CameraLength = CAMERALENGTH;//�����ŃJ�����̖{���̋������Ď擾

			 if (g_camera[nCnt].posV.y > 5.2f)//�ڐG����
			 {//�n�ʂ��CAMERA��
			 }
			 else
			 {
				 g_camera[nCnt].posV.y = 5.15f;
			 }



//			 float EscapeLength = g_camera[nCnt].CameraLength;

			 //--------------------------------����
			 //TRANSFERGATE* pTransferGate;
			 //pTransferGate = GetTransferGate();

			 //for (int i = 0; i < MAXGATE; i++)
			 //{
				// D3DXVECTOR3 GateMin = D3DXVECTOR3(pTransferGate[i].pos + pTransferGate[i].GateMin);
				// D3DXVECTOR3 GateMax = D3DXVECTOR3(pTransferGate[i].pos + pTransferGate[i].GateMax);

				// //��Q�����m
				// AdjustPlayerPositionToCollision_CAMERA(pViewPos[nCnt], nCnt, GateMin, GateMax);
			 //}

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

						 //�v���C���[���m�����蔻��
						// BoxCollisionPlayer(PlayerMin, PlayerMax, ModelMin, ModelMax, 1);
						 //��Q�����m
						 AdjustPlayerPositionToCollision_CAMERA(pViewPos[nCnt], nCnt, ModelMin, ModelMax);

						 //�����ŃJ�����̓����蔻��
					 }
				 }
			 }

			 STAGE* pStage;
			 pStage = GetStage();

			 for (int nWall = 0; nWall < NUMSTAGE; nWall++)
			 {
				 if (pStage[nWall].bUse == true)
				 {
					 D3DXVECTOR3 StageMin = D3DXVECTOR3(pStage[nWall].posStage + pStage[nWall].MinPos);
					 D3DXVECTOR3 StageMax = D3DXVECTOR3(pStage[nWall].posStage + pStage[nWall].MaxPos);

					 //��Q�����m
					 AdjustPlayerPositionToCollision_CAMERA(pViewPos[nCnt], nCnt, StageMin, StageMax);

				 }
			 }

			// //-----------------------------------�J���������̕ϓ��������v�Z
			// int Dir = EscapeLength - g_camera[nCnt].CameraLength;

			// if (Dir <= 1)
			// {//�덷�������Ǝ���
			//	 if (Dir < 0)
			//	 {//�}�C�i�X������
			//		 Dir = 1;
			//	 }



			//	 //----------�����_���C��
			//	 if (nCnt == 0)
			//	 {
			//	//	 pViewMtx[1].ViewPos.x = VIEWPOS.x;
			//	 }
			//	 else if (nCnt == 1)
			//	 {
			////		 pViewMtx2[1].ViewPos.x = VIEWPOS2.x;
			//	 }

			// }
			//else
			//{//�덷��������
			//	//float Escape = CAMERALENGTH;

			//	//�ϓ��{���v�Z
			//	int DirMag = Dir / CAMERALENGTH;
			//	DirMag += fmod(Dir, CAMERALENGTH);

			//	if (nCnt == 0)
			//	{
			//		pViewMtx[1].ViewPos.x = VIEWPOS.x * DirMag;
			//	}
			//	else if (nCnt == 1)
			//	{
			//		pViewMtx2[1].ViewPos.x = VIEWPOS2.x * DirMag;
			//	}

			//}





			//�ړ��ʂ��X�V(�^�������Ō���)
			g_camera[nCnt].move.x += (0.0f - g_camera[nCnt].move.x) * CAMERA_MOVE_DAMPING_RATIO;
			g_camera[nCnt].move.y += (0.0f - g_camera[nCnt].move.y) * CAMERA_MOVE_DAMPING_RATIO;
			g_camera[nCnt].move.z += (0.0f - g_camera[nCnt].move.z) * CAMERA_MOVE_DAMPING_RATIO;


			g_camera[nCnt].rotMove.x += (0.0f - g_camera[nCnt].rotMove.x) * CAMERA_ROT_DAMPING_RATIO;
			g_camera[nCnt].rotMove.y += (0.0f - g_camera[nCnt].rotMove.y) * CAMERA_ROT_DAMPING_RATIO;
			g_camera[nCnt].rotMove.z += (0.0f - g_camera[nCnt].rotMove.z) * CAMERA_ROT_DAMPING_RATIO;



			








			//�Â��ʒu��ݒ�
			g_camera[nCnt].OldPosV = g_camera[nCnt].posV;
		}
		else
		{//�����Ȃ��͈�
			g_camera[nCnt].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
		}
	}
}
void DrawCamera(void)
{
}



//=============================
//�J�����ݒ菈��
//=============================
void SetCamera(int nCnt)
{


	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMatrixIdentity(&g_camera[nCnt].mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera[nCnt].mtxProjection,
		D3DXToRadian(45.0f),//����p
		(float)SCREEN_WIDE / (float)SCREEN_HEIGHT,//��ʂ̃A�X�y�N�g��
		1.0f,//�����ŏ��l
		MAXDRAW);//z���ő�l

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[nCnt].mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[nCnt].mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera[nCnt].mtxView,
		&g_camera[nCnt].posV,
		&g_camera[nCnt].posR,
		&g_camera[nCnt].vecU);


	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[nCnt].mtxView);




}

//// �e��ʂ̃r���[�|�[�g�ݒ�
//bool SetUpViewport(int screen_id)
//{
//	// �X�N���[���ԍ��̍X�V
//	g_CurrentScreenId = screen_id;
//
//	// �r���[�|�[�g�p�����[�^
//	D3DVIEWPORT9 view_port;
//
//	Size screen_size = GetSplitScreenSize();
//	Vec2 offset = GetScreenOriginPos(screen_id);
//	
//	// �r���[�|�[�g�̍�����W
//	view_port.X = offset.X;
//	view_port.Y = offset.Y;
//
//	// �r���[�|�[�g�̕�
//	view_port.Width = screen_size.Width;
//	// �r���[�|�[�g�̍���
//	view_port.Height = screen_size.Height;
//	// �r���[�|�[�g�[�x�ݒ�
//	view_port.MinZ = 0.0f;
//	view_port.MaxZ = 1.0f;
//
//	// �r���[�|�[�g�ݒ�
//	if (FAILED(g_D3DDevice->SetViewport(&view_port)))
//	{
//		return false;
//	}
//
//	return true;
//}
//
//





//=============================
//�J�������菈��
//=============================
Camera* GetCamera(void)
{
	return &g_camera[0];
}
D3DXVECTOR3 GetCameraPosV(void)//���_
{
	return g_camera[0].posV;
}
D3DXVECTOR3 GetCameraPosR(void)//�����_
{
	return g_camera[0].posR;
}


//=============================
//�J�������쏈��
//=============================
void InputCamera(void)
{
	Player* pGrandPos;
	pGrandPos = GetPlayer();

	XINPUT_STATE joykeystate;

	//������
	float  Split = 0.6f;

	//�V���C�p�b�g�̏�Ԃ��擾
	//DWORD dwResult = XInputGetState(0, &joykeystate);

	//IK�ō��E
	//RF�ŏ㉺


	for (int nCnt = 0; nCnt < MAXCAMERA; nCnt++)
	{//�Ƃ肠�����S�������ɓ���

		//�V���C�p�b�g�̏�Ԃ��擾
		DWORD dwResult = XInputGetState(nCnt, &joykeystate);

		//if (nCnt == 0)
		//{//�J����0




			if (dwResult == ERROR_SUCCESS)
			{
				//�E�X�e�B�b�N----------------------------------------------------------------------------------------------------------------------------------------------------
				//�㉺����]�����������𓝈ꂷ�ׂ�


				//���ԓ_�܂ł̋���
				float fEscape = (32000 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 2800) / 2.0f;//�����𔼕���

				//���ԓ_�������ăf�b�h�]�[���ƍő�_�̒��ԓ_���Z�o(�ʏ���́A�����͂̔��ʕ���_)
				float BranchPoint = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 2800 + fEscape;


				bool RotNow = false;

				bool NomalMove = false;

				D3DXVECTOR3 EscapeRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				if (GetkeyboardPress(DIK_LEFT) == true || joykeystate.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
				{//A�������ꂽ(��)

					RotNow = true;

					if (GetkeyboardPress(DIK_UP) == true || joykeystate.Gamepad.sThumbRY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
					{//W�������ꂽ(����)
						EscapeRotMove.y += 1.57f * CAMERA_ROT_SPEED;
						EscapeRotMove.x += 1.57f * CAMERA_ROT_SPEED;
					}
					else if (GetkeyboardPress(DIK_DOWN) == true || joykeystate.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
					{//S�������ꂽ(����)
						EscapeRotMove.y += 1.57f * CAMERA_ROT_SPEED;
						EscapeRotMove.x -= 1.57f * CAMERA_ROT_SPEED;
					}
					else
					{//A�̂�(��)
						EscapeRotMove.y += 1.57f * CAMERA_ROT_SPEED;

					}
				}
				else if (GetkeyboardPress(DIK_RIGHT) == true || joykeystate.Gamepad.sThumbRX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
				{//D�������ꂽ(�E)

					RotNow = true;

					if (GetkeyboardPress(DIK_UP) == true || joykeystate.Gamepad.sThumbRY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
					{//W�������ꂽ(�E��)
						EscapeRotMove.y -= 1.57f * CAMERA_ROT_SPEED;
						EscapeRotMove.x += 1.57f * CAMERA_ROT_SPEED;
					}
					else if (GetkeyboardPress(DIK_DOWN) == true || joykeystate.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
					{//S�������ꂽ(�E��)
						EscapeRotMove.y -= 1.57f * CAMERA_ROT_SPEED;
						EscapeRotMove.x -= 1.57f * CAMERA_ROT_SPEED;
					}
					else
					{//D�̂�(�E)
						EscapeRotMove.y -= 1.57f * CAMERA_ROT_SPEED;

					}
				}
				else if (GetkeyboardPress(DIK_UP) == true || joykeystate.Gamepad.sThumbRY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
				{//W�������ꂽ(��)

					RotNow = true;

					if (GetkeyboardPress(DIK_RIGHT) == true || joykeystate.Gamepad.sThumbRX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
					{//D�������ꂽ(�E��)
						EscapeRotMove.x += 1.57f * CAMERA_ROT_SPEED;
						EscapeRotMove.y -= 1.57f * CAMERA_ROT_SPEED;

					}
					else if (GetkeyboardPress(DIK_LEFT) == true || joykeystate.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
					{//A�������ꂽ(����)
						EscapeRotMove.x += 1.57f * CAMERA_ROT_SPEED;
						EscapeRotMove.y += 1.57f * CAMERA_ROT_SPEED;
					}
					else
					{//W�̂�(��)

						EscapeRotMove.x += 1.57f * CAMERA_ROT_SPEED;
					}
				}
				else if (GetkeyboardPress(DIK_DOWN) == true || joykeystate.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
				{//S�������ꂽ(��)

					RotNow = true;

					if (GetkeyboardPress(DIK_RIGHT) == true || joykeystate.Gamepad.sThumbRX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
					{//D�������ꂽ(�E��)
						EscapeRotMove.x -= 1.57f * CAMERA_ROT_SPEED;
						EscapeRotMove.y -= 1.57f * CAMERA_ROT_SPEED;
					}
					else if (GetkeyboardPress(DIK_LEFT) == true || joykeystate.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
					{//A�������ꂽ(����)
						EscapeRotMove.x -= 1.57f * CAMERA_ROT_SPEED;
						EscapeRotMove.y += 1.57f * CAMERA_ROT_SPEED;

					}
					else
					{//S�̂�(��)
						EscapeRotMove.x -= 1.57f * CAMERA_ROT_SPEED;
					}
				}




				if (GetkeyboardPress(DIK_R) == true)
				{//R�������ꂽ(R)
					g_camera[nCnt].move.y += sinf(0.25f * D3DX_PI) * TORIMA;//�O�p�֐����p���Ĉړ��̒�������
				}
				else if (GetkeyboardPress(DIK_F) == true)
				{//F�������ꂽ(F)
					g_camera[nCnt].move.y += sinf(-0.25f * D3DX_PI) * TORIMA;//�O�p�֐����p���Ĉړ��̒�������
				}




				if (GetkeyboardPress(DIK_I) == true)
				{//I�������ꂽ(I)
					//g_camera[nCnt].move.y += sinf(0.25f * D3DX_PI) * TORIMA;//�O�p�֐����p���Ĉړ��̒�������
					EscapeRotMove.y += 1.57f * CAMERA_ROT_SPEED;
				}
				else if (GetkeyboardPress(DIK_K) == true)
				{//K�������ꂽ(K)
					//g_camera[nCnt].move.y += sinf(-0.25f * D3DX_PI) * TORIMA;//�O�p�֐����p���Ĉړ��̒�������
					EscapeRotMove.y -= 1.57f * CAMERA_ROT_SPEED;
				}



				//�ړ������Ԃ̎�
				if (RotNow == true)
				{
					//�ʏ���͂܂œ|���Ă���
					if (BranchPoint <= joykeystate.Gamepad.sThumbRY || -BranchPoint >= joykeystate.Gamepad.sThumbRY)
					{
						NomalMove = true;//�ʏ�ړ���Ԃɂ���
					}
					if (BranchPoint <= joykeystate.Gamepad.sThumbRX || -BranchPoint >= joykeystate.Gamepad.sThumbRX)
					{
						NomalMove = true;//�ʏ�ړ���Ԃɂ���
					}

					if (NomalMove == true)
					{//�ʏ�ړ���
						g_camera[nCnt].rotMove += EscapeRotMove;
						NomalMove = false;
					}
					else
					{
						g_camera[nCnt].rotMove += EscapeRotMove * Split;
					}
				}

			}
			else
			{
				if (GetkeyboardPress(DIK_R) == true)
				{//R�������ꂽ(R)
					g_camera[nCnt].move.y += sinf(0.25f * D3DX_PI) * TORIMA;//�O�p�֐����p���Ĉړ��̒�������
				}
				else if (GetkeyboardPress(DIK_F) == true)
				{//F�������ꂽ(F)
					g_camera[nCnt].move.y += sinf(-0.25f * D3DX_PI) * TORIMA;//�O�p�֐����p���Ĉړ��̒�������
				}




				if (GetkeyboardPress(DIK_I) == true)
				{//I�������ꂽ(I)
					//g_camera[nCnt].move.y += sinf(0.25f * D3DX_PI) * TORIMA;//�O�p�֐����p���Ĉړ��̒�������
					g_camera[nCnt].rotMove.y += 1.57f * CAMERA_ROT_SPEED;
				}
				else if (GetkeyboardPress(DIK_K) == true)
				{//K�������ꂽ(K)
					//g_camera[nCnt].move.y += sinf(-0.25f * D3DX_PI) * TORIMA;//�O�p�֐����p���Ĉړ��̒�������
					g_camera[nCnt].rotMove.y -= 1.57f * CAMERA_ROT_SPEED;
				}








				if (GetkeyboardPress(DIK_T) == true)
				{//T�������ꂽ(T)
					g_camera[nCnt].CameraLength += 2;
				}
				else if (GetkeyboardPress(DIK_G) == true)
				{//G�������ꂽ(G)
					g_camera[nCnt].CameraLength -= 2;
				}


				

				/////----------------------------------------------------------------------------------------------------test
			}

		//}
	}
}