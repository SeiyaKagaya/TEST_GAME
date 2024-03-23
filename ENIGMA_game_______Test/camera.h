//=========================================================
//
//�J�����֌W�g���錾�Ȃ�[camera.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _CAMERA_H_//���̃}�N������`����ĂȂ�������

//�}�N����`
#define _CAMERA_H_//��d�C���N���[�h�h�~�̃}�N����`

#include"main.h"

#define TORIMA	(2.0f)//�ύX�\��A�e�X�g�ړ�
#define CAMERA_MOVE_DAMPING_RATIO	(0.5f)//�J�����ړ�����
#define CAMERA_ROT_DAMPING_RATIO	(0.5f)//�J������]����
#define CAMERA_ROT_SPEED			(0.015f)//�J�������񑬓x

#define MAXDRAW	(20000.0f)//�`��͈�

#define MAXCAMERA	(3)//�J�����̑䐔--1�����̂͌��Ɉ�S��ʂœ����Ă�

#define CAMERALENGTH (150.0f)//�ʏ펞�̑ΏۂƂ̋���--1
//#define CAMERALENGTH2 (75.0f)//�ʏ펞�̑ΏۂƂ̋���-2


//�J�����T�C�Y(�����蔻��p)
#define CAMERAMIN	(D3DXVECTOR3(-3.0f,-3.0f,-3.0f))
#define CAMERAMAX	(D3DXVECTOR3(3.0f,3.0f,3.0f))



//�J�����\����
typedef struct
{
	//D3DXVECTOR3 pos;//
	D3DXVECTOR3 OldPosV;//

	D3DXVECTOR3 posV;		//���_

	D3DXVECTOR3 posR;		//�����_
	D3DXVECTOR3 move;		//�ړ�
	D3DXVECTOR3 vecU;		//������x�N�g��
	D3DXMATRIX mtxProjection;//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;		//�r���[�}�g���b�N�X
	D3DXMATRIX mtxWorld;

	D3DXVECTOR3 rot;		//��](����)
	D3DXVECTOR3 rotMove;	//��]�ړ����x

	float CameraLength;//�ΏۂƃJ�����̋���

	D3DXVECTOR3 posVmove;
	float PosV_V;//�c�̂Ƃ���Z�x�N�g���I�ȑ���
	float PosV_X;//

	D3DVIEWPORT9 viewport;//�r���[�|�[�g


	bool bUse;

}Camera;



//�v���g�^�C�v�錾
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void DrawCamera(void);

void SetCamera(int nCnt);
Camera* GetCamera(void);

void InputCamera(void);//�J��������


D3DXVECTOR3 GetCameraPosV(void);//���_
D3DXVECTOR3 GetCameraPosR(void);//�����_


// �e��ʂ̃r���[�|�[�g�ݒ�
//bool SetUpViewport(int screen_id);



















#endif // !_CAMERA_H_