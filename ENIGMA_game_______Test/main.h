//=========================================================
//
//���C���̕`�揈���֌W�Ŏg���ϐ��A�錾�A�\����[main.h]
// Author seiya kagaya
//
//=========================================================
#ifndef	_MAIN_H_	//���̃}�N����`������ĂȂ�������

#define _MAIN_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

#include <Windows.h>
#include <time.h>    //�^�C���֐��Ɏg�p



#include "d3dx9.h"	//�`�ʏ����Ɏg��
#define DIRECTINPUT_VERSION (0x0800)//�r���h���̌x���Ώ��}�N��
#include "dinput.h"	//���͏����ɕK�v
#include "xaudio2.h"//�T�E���h�����Ɏg�p
#include "xinput.h"

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")	//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")//�R���|�[�l�b�g�i���i�j�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")//�W���C�p�b�h�����ɕK�v

//�}�N����`
#define CLASS_NAME	"windowclass"			//	�E�B���h�E�N���X�̖��O
#define WINDOW_NAME	" ENIGMA"	//�E�B���h�E�̖��O�i�L���v�V�����ɕ\���j

#define SCREEN_WIDE	(1280)//�E�B���h�E�̕�
#define SCREEN_HEIGHT	(720)//�E�B���h�E�̍���
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)//���_����ݒ�
#define MOVE_X	(0)//x���W�̈ړ�
#define MOVE_Y	(0)//y���W�̈ړ�

#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)//3D�p���_���W(���_���W{3D},�@���A���_�t�H�[�}�b�g�Q��)





////�t�H���g�̎��
//typedef enum
//{
//	FONT_DOKIDOKI = 0,//�ǂ��ǂ��t�@���^�W�A
//	FONT_MAX,
//}FONT;
//
//#define MAXFONT (FONT_MAX)//---�t�H���g�̐�


//���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//���W�ω��p�W���i1.0f�ŌŒ�j
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_2D;

//���_���[3D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;			//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_3D;


//���(���[�h)�̎��
typedef enum
{
	MODE_TITLE = 0,//�^�C�g�����
	MODE_GAME,//�Q�[�����
	MODE_RESULT,//���U���g���
	MODE_TUTORIAL,//�`���[�g���A�����
	MODE_MENU,//���j���[���
	MODE_MAX,
}MODE;







//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);//����������

void Uninit(void);//�I������
void Update(void);//�X�V����
void Draw(void);//�`�揈��

void DrawFPS(void);//FPS�̕\��
//void DrawPlayerState(void);//�v���C���[�̏��
void DrawDebugText(void);//���̑�����


void Setmode(MODE mode);//���[�h�̐ݒ�
MODE GetMode(void);//���[�h�̎擾
MODE GetOldMode(void);


LPDIRECT3DDEVICE9 GetDevice(void);//�f�o�C�X�̎擾


D3DVIEWPORT9 GetViewPort(void);//�S��ʂ悤�r���[�|�[�g�擾






//-----------------------������--��

// �f���^�^�C����������
void InitializeDeltaTimer(void);
// �f���^�^�C�����擾
double GetDeltaTimer(void);




void GameClearFragOn(void);//Clear�t���O���Ă�@
bool GetGameClearFrag(void);//Clear��Ԃ��擾




//UI�R�����g�\������
//void DrawComentUI(const char* Text, D3DXVECTOR3 DrawPos, int FontSize, FONT Font);





//
////�t�H���g������
//void InitFont(LPDIRECT3DDEVICE9 g_pD3DDevice);
////�t�H���g�I������
//void UninitFont(void);
////�R�����g�`��
//void RenderFrame(LPDIRECT3DDEVICE9 g_pD3DDevice);
////�����_�[�e�L�X�g�Z�b�g
//void RenderText(const char* text, int x, int y);
//







#endif // _MAIN_H_ 








