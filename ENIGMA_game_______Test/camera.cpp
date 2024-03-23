//============================================================================================
//
//カメラを管理する処理[camera.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "camera.h"
#include "input.h"
#include "player.h"
#include "player2.h"
#include "transfergate.h"
#include "stage.h"

//グローバル変数宣言
Camera g_camera[MAXCAMERA] = {};//カメラの情報


//Screen番号
//int g_CurrentScreenId;




//=============================
//カメラ初期化処理
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
		{//左上
			g_camera[nCnt].CameraLength = CAMERALENGTH;//対象との距離
		}
		else
		{
			g_camera[nCnt].CameraLength = CAMERALENGTH;//対象との距離
		}

		g_camera[nCnt].PosV_V = 0.0f;
		g_camera[nCnt].PosV_X = 0.0f;


		if (nCnt == 0)
		{//左上
			g_camera[nCnt].viewport.Width = (SCREEN_WIDE / 2.0f)-10.0f;//ビューポートの幅
			g_camera[nCnt].viewport.Height = (SCREEN_HEIGHT / 2.0f) + 20.0f;//ビューポートの高さ

	//		g_camera[nCnt].viewport.Height = SCREEN_HEIGHT / 2.0f;//ビューポートの高さ------------------------------------------------------------


			g_camera[nCnt].viewport.X = 0.0f;//ビューポートの開始位置-X
			g_camera[nCnt].viewport.Y = 50.0f;//ビューポートの開始位置-Y

					//ビューポートの深度設定
			g_camera[nCnt].viewport.MinZ = 0.0f;
			g_camera[nCnt].viewport.MaxZ = 1.0f;

		}
		else if(nCnt == 1)
		{//右上
			g_camera[nCnt].viewport.Width = (SCREEN_WIDE / 2.0f)-10.0f;//ビューポートの幅
			g_camera[nCnt].viewport.Height = (SCREEN_HEIGHT / 2.0f) + 20.0f;//ビューポートの高さ
		

	//		g_camera[nCnt].viewport.Height = SCREEN_HEIGHT / 2.0f;//ビューポートの高さ----------------------------------------------------------



			g_camera[nCnt].viewport.X = (SCREEN_WIDE/2.0f)+10.0f;//ビューポートの開始位置-X
			g_camera[nCnt].viewport.Y = 50.0f;//ビューポートの開始位置-Y

					//ビューポートの深度設定
			g_camera[nCnt].viewport.MinZ = 0.0f;
			g_camera[nCnt].viewport.MaxZ = 1.0f;
		}
		else if (nCnt == 2)
		{//画面後ろ--見えない範囲
			g_camera[nCnt].viewport.Width = 2.0f;//ビューポートの幅
			g_camera[nCnt].viewport.Height = 2.0f;//ビューポートの高さ

			g_camera[nCnt].viewport.X = 70.0f;//ビューポートの開始位置-X
			g_camera[nCnt].viewport.Y = 70.0f;//ビューポートの開始位置-Y

					//ビューポートの深度設定
			g_camera[nCnt].viewport.MinZ = 0.0f;
			g_camera[nCnt].viewport.MaxZ = 0.0f;
		}



	




		g_camera[nCnt].OldPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}
//=============================
//カメラ終了処理
//=============================
void UninitCamera(void)
{

}
//=============================
//カメラ更新処理
//=============================
void UpdateCamera(void)
{
	Player* pPlayer;
	pPlayer = GetPlayer();

	Player_2P* pPlayer2;
	pPlayer2 = GetPlayer_2P();

	//ここで初期化
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
		 {//画面外以外

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

			 //位置を更新
			 g_camera[nCnt].posV.x += g_camera[nCnt].move.x;
			 g_camera[nCnt].posV.y += g_camera[nCnt].move.y;
			 g_camera[nCnt].posV.z += g_camera[nCnt].move.z;


			 g_camera[nCnt].rot.x += g_camera[nCnt].rotMove.x;

			 if (g_camera[nCnt].rot.x > D3DX_PI * 0.1f)//旋回制限
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







			 //半径

			 //極座標---上から見て　　　X.Yのみで動く公式有り--X=cosf(rot.縦軸)*距離----平面　
			 //｜-＞うえからみた縦      sinf(rot縦軸)*距離									

			 //横から見て/////cosf(rot横軸)*距離---平面
			 //｜-＞横から見た縦--sinf(rot横軸)*距離

			 //を運用
			 //-------X=cos(シータ(角度))*距離、Y=sinf(シータ(角度))*距離
			 // 

			 //if (g_camera[nCnt].posV.y > 5.1f)//接触判定
			 //{//地面よりCAMERA上

			 //	g_camera[nCnt].CameraLength = CAMERALENGTH;
			 //}

																		 //こっから角度								//
			 g_camera[nCnt].posV.x = g_camera[nCnt].posR.x + g_camera[nCnt].CameraLength * cosf(g_camera[nCnt].rot.x) * sinf(g_camera[nCnt].rot.y);//1コサインシータを欠けた--コサインファイを欠けた

			 g_camera[nCnt].posV.y = g_camera[nCnt].posR.y - g_camera[nCnt].CameraLength * sinf(g_camera[nCnt].rot.x);						//2Yは普遍のためかくない

			 g_camera[nCnt].posV.z = g_camera[nCnt].posR.z - g_camera[nCnt].CameraLength * cosf(g_camera[nCnt].rot.x) * cosf(g_camera[nCnt].rot.y);//3//１と同じ感じ
			 //posRは			ここがPosV	ここは+に変更



			 g_camera[nCnt].CameraLength = CAMERALENGTH;//ここでカメラの本来の距離を再取得

			 if (g_camera[nCnt].posV.y > 5.2f)//接触判定
			 {//地面よりCAMERA上
			 }
			 else
			 {
				 g_camera[nCnt].posV.y = 5.15f;
			 }



//			 float EscapeLength = g_camera[nCnt].CameraLength;

			 //--------------------------------試験
			 //TRANSFERGATE* pTransferGate;
			 //pTransferGate = GetTransferGate();

			 //for (int i = 0; i < MAXGATE; i++)
			 //{
				// D3DXVECTOR3 GateMin = D3DXVECTOR3(pTransferGate[i].pos + pTransferGate[i].GateMin);
				// D3DXVECTOR3 GateMax = D3DXVECTOR3(pTransferGate[i].pos + pTransferGate[i].GateMax);

				// //障害物検知
				// AdjustPlayerPositionToCollision_CAMERA(pViewPos[nCnt], nCnt, GateMin, GateMax);
			 //}

			 //----------------------------------------------------------------------------モデル接触
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

						 //プレイヤー同士当たり判定
						// BoxCollisionPlayer(PlayerMin, PlayerMax, ModelMin, ModelMax, 1);
						 //障害物検知
						 AdjustPlayerPositionToCollision_CAMERA(pViewPos[nCnt], nCnt, ModelMin, ModelMax);

						 //ここでカメラの当たり判定
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

					 //障害物検知
					 AdjustPlayerPositionToCollision_CAMERA(pViewPos[nCnt], nCnt, StageMin, StageMax);

				 }
			 }

			// //-----------------------------------カメラ距離の変動差分を計算
			// int Dir = EscapeLength - g_camera[nCnt].CameraLength;

			// if (Dir <= 1)
			// {//誤差が無いと識別
			//	 if (Dir < 0)
			//	 {//マイナスを消す
			//		 Dir = 1;
			//	 }



			//	 //----------注視点を修正
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
			//{//誤差が生じた
			//	//float Escape = CAMERALENGTH;

			//	//変動倍率計算
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





			//移動量を更新(疑似慣性で減衰)
			g_camera[nCnt].move.x += (0.0f - g_camera[nCnt].move.x) * CAMERA_MOVE_DAMPING_RATIO;
			g_camera[nCnt].move.y += (0.0f - g_camera[nCnt].move.y) * CAMERA_MOVE_DAMPING_RATIO;
			g_camera[nCnt].move.z += (0.0f - g_camera[nCnt].move.z) * CAMERA_MOVE_DAMPING_RATIO;


			g_camera[nCnt].rotMove.x += (0.0f - g_camera[nCnt].rotMove.x) * CAMERA_ROT_DAMPING_RATIO;
			g_camera[nCnt].rotMove.y += (0.0f - g_camera[nCnt].rotMove.y) * CAMERA_ROT_DAMPING_RATIO;
			g_camera[nCnt].rotMove.z += (0.0f - g_camera[nCnt].rotMove.z) * CAMERA_ROT_DAMPING_RATIO;



			








			//古い位置を設定
			g_camera[nCnt].OldPosV = g_camera[nCnt].posV;
		}
		else
		{//見えない範囲
			g_camera[nCnt].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
		}
	}
}
void DrawCamera(void)
{
}



//=============================
//カメラ設定処理
//=============================
void SetCamera(int nCnt)
{


	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMatrixIdentity(&g_camera[nCnt].mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_camera[nCnt].mtxProjection,
		D3DXToRadian(45.0f),//視野角
		(float)SCREEN_WIDE / (float)SCREEN_HEIGHT,//画面のアスペクト比
		1.0f,//ｚ軸最小値
		MAXDRAW);//z軸最大値

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[nCnt].mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera[nCnt].mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera[nCnt].mtxView,
		&g_camera[nCnt].posV,
		&g_camera[nCnt].posR,
		&g_camera[nCnt].vecU);


	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[nCnt].mtxView);




}

//// 各画面のビューポート設定
//bool SetUpViewport(int screen_id)
//{
//	// スクリーン番号の更新
//	g_CurrentScreenId = screen_id;
//
//	// ビューポートパラメータ
//	D3DVIEWPORT9 view_port;
//
//	Size screen_size = GetSplitScreenSize();
//	Vec2 offset = GetScreenOriginPos(screen_id);
//	
//	// ビューポートの左上座標
//	view_port.X = offset.X;
//	view_port.Y = offset.Y;
//
//	// ビューポートの幅
//	view_port.Width = screen_size.Width;
//	// ビューポートの高さ
//	view_port.Height = screen_size.Height;
//	// ビューポート深度設定
//	view_port.MinZ = 0.0f;
//	view_port.MaxZ = 1.0f;
//
//	// ビューポート設定
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
//カメラ入手処理
//=============================
Camera* GetCamera(void)
{
	return &g_camera[0];
}
D3DXVECTOR3 GetCameraPosV(void)//視点
{
	return g_camera[0].posV;
}
D3DXVECTOR3 GetCameraPosR(void)//注視点
{
	return g_camera[0].posR;
}


//=============================
//カメラ操作処理
//=============================
void InputCamera(void)
{
	Player* pGrandPos;
	pGrandPos = GetPlayer();

	XINPUT_STATE joykeystate;

	//分割率
	float  Split = 0.6f;

	//ショイパットの状態を取得
	//DWORD dwResult = XInputGetState(0, &joykeystate);

	//IKで左右
	//RFで上下


	for (int nCnt = 0; nCnt < MAXCAMERA; nCnt++)
	{//とりあえず全部同時に動く

		//ショイパットの状態を取得
		DWORD dwResult = XInputGetState(nCnt, &joykeystate);

		//if (nCnt == 0)
		//{//カメラ0




			if (dwResult == ERROR_SUCCESS)
			{
				//右スティック----------------------------------------------------------------------------------------------------------------------------------------------------
				//上下も回転見たく距離を統一すべき


				//中間点までの距離
				float fEscape = (32000 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 2800) / 2.0f;//差分を半分に

				//中間点をたしてデッドゾーンと最大点の中間点を算出(通常入力、微入力の判別分岐点)
				float BranchPoint = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 2800 + fEscape;


				bool RotNow = false;

				bool NomalMove = false;

				D3DXVECTOR3 EscapeRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				if (GetkeyboardPress(DIK_LEFT) == true || joykeystate.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
				{//Aがおされた(左)

					RotNow = true;

					if (GetkeyboardPress(DIK_UP) == true || joykeystate.Gamepad.sThumbRY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
					{//Wがおされた(左上)
						EscapeRotMove.y += 1.57f * CAMERA_ROT_SPEED;
						EscapeRotMove.x += 1.57f * CAMERA_ROT_SPEED;
					}
					else if (GetkeyboardPress(DIK_DOWN) == true || joykeystate.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
					{//Sが押された(左下)
						EscapeRotMove.y += 1.57f * CAMERA_ROT_SPEED;
						EscapeRotMove.x -= 1.57f * CAMERA_ROT_SPEED;
					}
					else
					{//Aのみ(左)
						EscapeRotMove.y += 1.57f * CAMERA_ROT_SPEED;

					}
				}
				else if (GetkeyboardPress(DIK_RIGHT) == true || joykeystate.Gamepad.sThumbRX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
				{//Dがおされた(右)

					RotNow = true;

					if (GetkeyboardPress(DIK_UP) == true || joykeystate.Gamepad.sThumbRY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
					{//Wがおされた(右上)
						EscapeRotMove.y -= 1.57f * CAMERA_ROT_SPEED;
						EscapeRotMove.x += 1.57f * CAMERA_ROT_SPEED;
					}
					else if (GetkeyboardPress(DIK_DOWN) == true || joykeystate.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
					{//Sが押された(右下)
						EscapeRotMove.y -= 1.57f * CAMERA_ROT_SPEED;
						EscapeRotMove.x -= 1.57f * CAMERA_ROT_SPEED;
					}
					else
					{//Dのみ(右)
						EscapeRotMove.y -= 1.57f * CAMERA_ROT_SPEED;

					}
				}
				else if (GetkeyboardPress(DIK_UP) == true || joykeystate.Gamepad.sThumbRY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
				{//Wがおされた(上)

					RotNow = true;

					if (GetkeyboardPress(DIK_RIGHT) == true || joykeystate.Gamepad.sThumbRX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
					{//Dがおされた(右上)
						EscapeRotMove.x += 1.57f * CAMERA_ROT_SPEED;
						EscapeRotMove.y -= 1.57f * CAMERA_ROT_SPEED;

					}
					else if (GetkeyboardPress(DIK_LEFT) == true || joykeystate.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
					{//Aが押された(左上)
						EscapeRotMove.x += 1.57f * CAMERA_ROT_SPEED;
						EscapeRotMove.y += 1.57f * CAMERA_ROT_SPEED;
					}
					else
					{//Wのみ(上)

						EscapeRotMove.x += 1.57f * CAMERA_ROT_SPEED;
					}
				}
				else if (GetkeyboardPress(DIK_DOWN) == true || joykeystate.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
				{//Sがおされた(下)

					RotNow = true;

					if (GetkeyboardPress(DIK_RIGHT) == true || joykeystate.Gamepad.sThumbRX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
					{//Dがおされた(右下)
						EscapeRotMove.x -= 1.57f * CAMERA_ROT_SPEED;
						EscapeRotMove.y -= 1.57f * CAMERA_ROT_SPEED;
					}
					else if (GetkeyboardPress(DIK_LEFT) == true || joykeystate.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3500)
					{//Aが押された(左下)
						EscapeRotMove.x -= 1.57f * CAMERA_ROT_SPEED;
						EscapeRotMove.y += 1.57f * CAMERA_ROT_SPEED;

					}
					else
					{//Sのみ(下)
						EscapeRotMove.x -= 1.57f * CAMERA_ROT_SPEED;
					}
				}




				if (GetkeyboardPress(DIK_R) == true)
				{//Rがおされた(R)
					g_camera[nCnt].move.y += sinf(0.25f * D3DX_PI) * TORIMA;//三角関数利用して移動の長さを代入
				}
				else if (GetkeyboardPress(DIK_F) == true)
				{//Fがおされた(F)
					g_camera[nCnt].move.y += sinf(-0.25f * D3DX_PI) * TORIMA;//三角関数利用して移動の長さを代入
				}




				if (GetkeyboardPress(DIK_I) == true)
				{//Iがおされた(I)
					//g_camera[nCnt].move.y += sinf(0.25f * D3DX_PI) * TORIMA;//三角関数利用して移動の長さを代入
					EscapeRotMove.y += 1.57f * CAMERA_ROT_SPEED;
				}
				else if (GetkeyboardPress(DIK_K) == true)
				{//Kがおされた(K)
					//g_camera[nCnt].move.y += sinf(-0.25f * D3DX_PI) * TORIMA;//三角関数利用して移動の長さを代入
					EscapeRotMove.y -= 1.57f * CAMERA_ROT_SPEED;
				}



				//移動する状態の時
				if (RotNow == true)
				{
					//通常入力まで倒していか
					if (BranchPoint <= joykeystate.Gamepad.sThumbRY || -BranchPoint >= joykeystate.Gamepad.sThumbRY)
					{
						NomalMove = true;//通常移動状態にする
					}
					if (BranchPoint <= joykeystate.Gamepad.sThumbRX || -BranchPoint >= joykeystate.Gamepad.sThumbRX)
					{
						NomalMove = true;//通常移動状態にする
					}

					if (NomalMove == true)
					{//通常移動時
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
				{//Rがおされた(R)
					g_camera[nCnt].move.y += sinf(0.25f * D3DX_PI) * TORIMA;//三角関数利用して移動の長さを代入
				}
				else if (GetkeyboardPress(DIK_F) == true)
				{//Fがおされた(F)
					g_camera[nCnt].move.y += sinf(-0.25f * D3DX_PI) * TORIMA;//三角関数利用して移動の長さを代入
				}




				if (GetkeyboardPress(DIK_I) == true)
				{//Iがおされた(I)
					//g_camera[nCnt].move.y += sinf(0.25f * D3DX_PI) * TORIMA;//三角関数利用して移動の長さを代入
					g_camera[nCnt].rotMove.y += 1.57f * CAMERA_ROT_SPEED;
				}
				else if (GetkeyboardPress(DIK_K) == true)
				{//Kがおされた(K)
					//g_camera[nCnt].move.y += sinf(-0.25f * D3DX_PI) * TORIMA;//三角関数利用して移動の長さを代入
					g_camera[nCnt].rotMove.y -= 1.57f * CAMERA_ROT_SPEED;
				}








				if (GetkeyboardPress(DIK_T) == true)
				{//Tがおされた(T)
					g_camera[nCnt].CameraLength += 2;
				}
				else if (GetkeyboardPress(DIK_G) == true)
				{//Gがおされた(G)
					g_camera[nCnt].CameraLength -= 2;
				}


				

				/////----------------------------------------------------------------------------------------------------test
			}

		//}
	}
}