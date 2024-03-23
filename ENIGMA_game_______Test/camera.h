//=========================================================
//
//カメラ関係使う宣言など[camera.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _CAMERA_H_//このマクロが定義されてなかったら

//マクロ定義
#define _CAMERA_H_//二重インクルード防止のマクロ定義

#include"main.h"

#define TORIMA	(2.0f)//変更予定、テスト移動
#define CAMERA_MOVE_DAMPING_RATIO	(0.5f)//カメラ移動慣性
#define CAMERA_ROT_DAMPING_RATIO	(0.5f)//カメラ回転慣性
#define CAMERA_ROT_SPEED			(0.015f)//カメラ旋回速度

#define MAXDRAW	(20000.0f)//描画範囲

#define MAXCAMERA	(3)//カメラの台数--1多いのは後ろに一つ全画面で動いてる

#define CAMERALENGTH (150.0f)//通常時の対象との距離--1
//#define CAMERALENGTH2 (75.0f)//通常時の対象との距離-2


//カメラサイズ(当たり判定用)
#define CAMERAMIN	(D3DXVECTOR3(-3.0f,-3.0f,-3.0f))
#define CAMERAMAX	(D3DXVECTOR3(3.0f,3.0f,3.0f))



//カメラ構造体
typedef struct
{
	//D3DXVECTOR3 pos;//
	D3DXVECTOR3 OldPosV;//

	D3DXVECTOR3 posV;		//視点

	D3DXVECTOR3 posR;		//注視点
	D3DXVECTOR3 move;		//移動
	D3DXVECTOR3 vecU;		//上方向ベクトル
	D3DXMATRIX mtxProjection;//プロジェクションマトリックス
	D3DXMATRIX mtxView;		//ビューマトリックス
	D3DXMATRIX mtxWorld;

	D3DXVECTOR3 rot;		//回転(向き)
	D3DXVECTOR3 rotMove;	//回転移動速度

	float CameraLength;//対象とカメラの距離

	D3DXVECTOR3 posVmove;
	float PosV_V;//縦のときのZベクトル的な存在
	float PosV_X;//

	D3DVIEWPORT9 viewport;//ビューポート


	bool bUse;

}Camera;



//プロトタイプ宣言
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void DrawCamera(void);

void SetCamera(int nCnt);
Camera* GetCamera(void);

void InputCamera(void);//カメラ操作


D3DXVECTOR3 GetCameraPosV(void);//視点
D3DXVECTOR3 GetCameraPosR(void);//注視点


// 各画面のビューポート設定
//bool SetUpViewport(int screen_id);



















#endif // !_CAMERA_H_