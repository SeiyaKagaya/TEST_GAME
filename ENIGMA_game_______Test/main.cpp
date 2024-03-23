//============================================================================================
//
//�v���C���[�𑀍삵�G��|������[main.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "main.h"
#include "input.h"

#include "title.h"
#include "game.h"
#include "result.h"
#include "Tutorial.h"
#include "fade.h"
#include "sound.h"
#include "camera.h"
#include "player.h"
#include "gamefade.h"
#include "text.h"
#include "menu.h"
#include "Film.h"
#include "MenuFrame.h"

//�O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL;//direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;//direct#d�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;//�t�H���g�ւ̃|�C���^


//LPD3DXFONT g_pFont_Comment[MAXFONT] = {};//�t�H���g�ւ̃|�C���^




//MODE g_mode = MODE_TITLE;//���݂̃��[�h(������title��ʂ��g�p)

MODE g_mode = MODE_TITLE;//���݂̃��[�h(�����ɃQ�[����ʂ��g�p)-----------------------------�f�o�b�O�d�l
MODE g_OldMode = MODE_TITLE;//�ߋ��̃��[�h(�����ɃQ�[����ʂ��g�p)------
bool g_mesh = false;								//���C���[�t���[���؂�ւ��p
float g_fFogDensity;	//�t�H�O���x�w��p


int g_nCountFPS = 0;//FPS�J�E���^


// �O���[�o���ϐ�
LARGE_INTEGER g_startTime;
LARGE_INTEGER g_endTime;

//�f���^�^�C���֌W(�S������)
double g_frequency;


D3DVIEWPORT9 g_fullScreen_Viewport;//�S��ʃr���[�|�[�g


bool bClearFrag = false;//Clear�t���O

bool g_isFullscreen = false;			// �E�B���h�E��؂�ւ��邽�߂̃t���O
RECT g_windowRect;						// �E�B���h�E��؂�ւ��邽�߂̕ϐ�

//===================================
//���C���֐�
//===================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)//��������������

{
	DWORD dwCurrentTime;//���ݎ���
	DWORD dwExecLastTime;//�Ō�ɏ�����������

	DWORD dwFrameCount;//�t���[���J�E���g
	DWORD dwFPSLastTime;//�Ō��FPS���v����������


	HWND hWnd;	//�E�B���h�E�n���h���i���ʎq�j
	MSG msg;	//���b�Z�[�W���i�[����ϐ�

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();




	//�E�B���h�E�\��
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,							//�E�B���h�E�̃X�^�C��
		WindowProc,							//�E�B���h�E�̃v���[�W��
		0,									//0�ɂ���i�ʏ�͎g�p�����j
		0,									//0�ɂ���i�ʏ�͎g�p�����j
		hInstance,							//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),		//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),			//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			//�N���C���g�̈�̕\���F
		NULL,								//���j���[�o�[
		CLASS_NAME,							//�E�B���h�E�N���X�̒�`
		LoadIcon(NULL,IDI_APPLICATION)		//�t�@�C���̃A�C�R��
	};

	RECT rect = { 0,0,SCREEN_WIDE,SCREEN_HEIGHT };//��ʃT�C�Y�̍\����

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E���쐬
	hWnd = CreateWindowEx(0,	//�g���E�B���h�E�X�^�C��
		CLASS_NAME,				//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,			//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	//�E�B���h�E�X�^�C��
		0,//CW_USEDEFAULT,			//�E�B���h�E����X���W///-----------------------------����ꂽ����Ƃɖ߂�
		0,//CW_USEDEFAULT,			//�E�B���h�E����Y���W
		(rect.right - rect.left),//���@
		(rect.bottom - rect.top),//����
		//SCREEN_WIDE,			//�E�B���h�E���㕝
		//SCREEN_HEIGHT,			//�E�B���h�E���㍂��
		NULL,					//�e�E�B���h�E�̃n���h��
		NULL,					//���j���[�n���h���b�g���q�E�B���h�EID
		hInstance,				//�C���X�^���X�n���h��
		NULL);					//�E�B���h�E�쐬�f�[�^


	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//�����������s�����ꍇ
		return-1;//�ł��Ȃ������炱���ŏI���
	}

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;//������
	dwExecLastTime = timeGetTime();//���ݎ������擾�i�ۑ��j

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);//�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);        //�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���                          
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎悽�烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W
				TranslateMessage(&msg);//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W��ϊ�


				DispatchMessage(&msg); //�E�B���h�E�v���[�W���[�փ��b�Z�[�W����o
			}
		}
		else
		{//directX�̏���

			dwCurrentTime = timeGetTime();//���ݎ������擾
			

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;//FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;//�t���[���J�E���g���N���A
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))//�`�摬�x��ݒ�//--------------------------------------------------------
			{//60���̈�b�o��
				dwExecLastTime = dwCurrentTime;//�����J�n�̎���(���ݎ���)�ŕۑ�

				dwFrameCount++;//�t���[���J�E���g�����Z

				//�X�V����
				Update();
				//�`�揈��
				Draw();
			}
		}
	}

	//�I������----------------------------------------------------------------------
	timeEndPeriod(1);//����\��߂�
	Uninit();
	
	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}
//=======================================
//�E�B���h�E�v���V�[�W���[
//=======================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	int nID;//�Ԃ�l���i�[

	switch (uMsg)
	{
		
	case WM_CREATE:	//�E�B���h�E�����̃��b�Z�[�W
		break;
	///-----------------------------------------------------------�e�{�^������ł̔���
	case WM_COMMAND: //�R�}���h���s�̃��b�Z�[�W

		break;

	case WM_CLOSE: //����{�^�����������̃��b�Z�[�W

		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
		if (nID == IDYES)
		{
			//�E�B���h�E�j��
			DestroyWindow(hWnd);
		}
		else
		{//NO�̎�
			return 0;//0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN://�L�[�����̃��b�Z�[�W(ESC)
		switch (wParam)
		{
		case VK_ESCAPE://escape�{�^��
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				//�E�B���h�E��j������
				DestroyWindow(hWnd);
			}
			break;

		case VK_F11:
			ToggleFullscreen(hWnd);
			break;

		}
		break;

	case WM_LBUTTONDOWN://�}�E�X���N���b�N
		//�E�B���h�E�t�H�[�J�X�����킹��
		SetFocus(hWnd);
		break;

	case WM_DESTROY: //�E�B���h�E�j���̃��b�Z�[�W
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	}


	return DefWindowProc(hWnd, uMsg, wParam, lParam);//�K��̒l��Ԃ�
}
//=============================
//�f�o�C�X�̎擾
//=============================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//=============================
//����������
//=============================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindows)
{
	//----------------------------------------------------------------------------------------------------------------------------------�������狤��
	//��ʑS�̂̂Ƃ��̃r���[�|�[�g
	g_fullScreen_Viewport.X = 0;//�r���[�|�[�g�̊J�n�ʒu-X
	g_fullScreen_Viewport.Y = 0;//�r���[�|�[�g�̊J�n�ʒu-Y

	g_fullScreen_Viewport.Width = SCREEN_WIDE;//�r���[�|�[�g�̕�
	g_fullScreen_Viewport.Height = SCREEN_HEIGHT;//�r���[�|�[�g�̍���

	//�r���[�|�[�g�̐[�x�ݒ�
	g_fullScreen_Viewport.MinZ = 0.0f;
	g_fullScreen_Viewport.MaxZ = 1.0f;

	D3DDISPLAYMODE d3ddm;//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;//�v���[���e�[�V�����p�����[�^
	
	//direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�[���܂����`]
	ZeroMemory(&d3dpp, sizeof(d3dpp));//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDE;//�Q�[����ʃT�C�Y��
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//�Q�[����ʃT�C�Y�c
	d3dpp.BackBufferFormat = d3ddm.Format;//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//�_�u���o�b�t�@�̐؂�ւ��i�f���M���ɓ����j
	d3dpp.EnableAutoDepthStencil = TRUE;//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬

	//d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//�f�p�X�o�b�t�@�Ƃ���16�r�b�g���g��----------------------------------------------------------------------
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;//�f�p�X�o�b�t�@�Ƃ���24�r�b�g���g��----------------------------------------------------------------------



	d3dpp.Windowed = bWindows;//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//�C���^�[�o��

	//direct3D�f�o�C�X�̐����i�`�揈���ƒ��_�������n�[�h�E�F�A�ōs���j
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		//direct�RD�f�o�C�X�̐����i�`�揈���̓n�[�h�E�F�A�A���_������CPU�ōs���j
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
		{
			//direct�RD�f�o�C�X�̐����i�`�揈���ƒ��_������CPU�ōs���j
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�//-----------------------------------------------------------------
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//�J�����O�̐ݒ�

	//�A���t�@�u�����h�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);				//�t�H�O�ݒ�L��
	//g_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//�t�H�O�J���[
	//g_pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);		//�t�H�O���[�h

	//g_fFogDensity = 0.003f;				//�t�H�O���x�l
	//g_pD3DDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&g_fFogDensity));	//���x�w��


	//------------------------------------------------------------------------------------------

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);


	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);




	//�f�o�b�O�\���p�̃t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&g_pFont);


	//UIComment�\���p�̃t�H���g�̐���
	//MS�S�V�b�N
	//�f�o�C�X,��������,������,�t�H���g�X�^�C��,�~�b�v�}�b�v�̃��x��
	//,�Α̂ɂ��邩�ǂ���,
	//�����Z�b�g,
	//�o�͐��x,
	//�o�͕i��,
	//�t�H���g�s�b�`�ƃt�@�~��,
	//�t�H���g��,
	//�t�H���g�|�C���^
	
	
	/*D3DXCreateFont(g_pD3DDevice, 50, 0, FW_HEAVY, 1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_TT_ONLY_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		TEXT("�l�r ����"),
		&g_pFont_Comment);*/



	////---------------------------------------------------------------------------------------font�̃e�X�g
	//	//�t�H���g�̓ǂݍ���///
	//LPCSTR font_path = "data\\FONT\\DokiDokiFantasia.otf"; // �ǂ��ǂ��t�@���^�W�A�Ƃ����t�H���g���g�p�\��
	//if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) 
	//{
	//}
	//else 
	//{
	//	// �t�H���g�Ǎ��G���[����
	//	MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	//}
	////------------------------------------�ǂݍ��߂Ă�
	



	//	TEXT("data\\FONT\\HGRSMP.TTF"),



	//InitFont(g_pD3DDevice);



	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�R���g���[���[������
	InitJoypad();
//
//	//�T�E���h�̏���������
	InitSound(hWnd);

	//�e�L�X�g�̏�����
	InitText();


////----------------------------------------------------------------------------------------------------------------------------------�����܂ŋ���
//
	//���[�h�ݒ�
	Setmode(g_mode);

	//�t�F�[�h�̏���������
	InitFade(MODE(FADE_NONE));


	//����
	//InitPlayer();

	


	//�e��I�u�W�F�N�g�̏���������
	return S_OK;
}
//=============================
//�I������
//=============================
void Uninit(void)
{
	//�e��I�u�W�F�N�g�̏I������
	 
	//����
	//UninitPlayer();

	//�t�F�[�h�̏I������
	UninitFade();
	//�^�C�g����ʂ̏I������
	UninitTitle();
	//�Q�[����ʂ̏I������
	UninitGame();
	//���U���g��ʂ̏I������
	UninitResult();
	//�`���[�g���A����ʂ̏I������
	UninitTutorial();
	//���j���[��ʂ̏I������
	UninitMenuFrame();

	UninitSound();

	UninitText();

	////----------------------------------------------------------------------------------------------------------------------------------�������狤��

	//�L�[�{�[�h�̏I������
	UninitKeyboard();
	UninitJoypad();

	//direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	//�f�o�b�O�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
	


	//for (int i = 0; i < MAXFONT; i++)
	//{
	//	//UIComment�\���p�t�H���g�̔j��
	//	if (g_pFont_Comment[i] != NULL)
	//	{
	//		g_pFont_Comment[i]->Release();
	//		g_pFont_Comment[i] = NULL;
	//	}
	//}
	//UninitFont();

	//----------------------------------------------------------------------------------------------------------------------------------�����܂ŋ���

}
//=============================
//�X�V����
//=============================
void Update(void)
{
	//�e��I�u�W�F�N�g�̍X�V���� 

	//UpdatePlayer();
		
	// �f���^�^�C���̏�����
	InitializeDeltaTimer();

	// �f���^�^�C���̎擾
//	double deltaTime = GetDeltaTimer();
	//�ǂ��g�������





	//----------------------------------------------------------------------------------------------------------------------------------�������狤��
	//�t�F�[�h�̍X�V����
	UpdateFade();

	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	if (GetkeyboardTrigger(DIK_F4) == true)//-----------------���b�V���\���n
	{
		g_mesh = !g_mesh;
		if (g_mesh == false)
		{
			//���̏��
			g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
		else if (g_mesh == true)
		{
			//���C���[�t���[�����[�h�̏��
			g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
	}

	//�R���g���[���[
	UpdateJoypad();
	////----------------------------------------------------------------------------------------------------------------------------------�����܂ŋ���

	switch (g_mode)
	{
	case MODE_TITLE://�^�C�g�����
	
		UpdateTitle();
		break;

	case MODE_GAME://�Q�[�����
	
		UpdateGame();
		//UpdateAllScoreManagement();//�X�R�A�Ǘ���������
		UpdateFade();
		break;

	case MODE_RESULT://���U���g���
		UpdateResult();
		break;
	
	case MODE_TUTORIAL://�`���[�g���A�����
		UpdateTutorial();
		break;

	case MODE_MENU://���j���[���
		UpdateMenuFrame();
		break;

	}


}
//=============================
//�`�揈��
//=============================
void Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//����厖
	//��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);


	//Z�o�b�nZ�e�X�g�����Ȃ��ƌ��������ɂ����Ă��`��(�؂̊ђʂ�A���������ɂȂ������)
	

	//�`��i�K
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

		//DrawPlayer();

		


		//�e�I�u�W�F�N�g�̕`�揈��


		switch (g_mode)
		{
		case MODE_TITLE://�^�C�g�����
			
		//�r���[�|�[�g�����Ƃɖ߂�
			pDevice->SetViewport(&g_fullScreen_Viewport);//�r���[�|�[�g�̐ݒ�

			DrawTitle();
			break;

		case MODE_GAME://�Q�[�����

			DrawGame();
			
			//�e�X�g---------------------------------------------------------------------------------
			//DrawComentUI("�e�X�g�[�[�I", D3DXVECTOR3(100.0f, 500.0f, 0.0f), 200, FONT_DOKIDOKI);

			//�r���[�|�[�g�����Ƃɖ߂�
			//pDevice->SetViewport(&g_fullScreen_Viewport);//�r���[�|�[�g�̐ݒ�

			
			
			break;

		case MODE_RESULT://���U���g���
			//�r���[�|�[�g�����Ƃɖ߂�
			pDevice->SetViewport(&g_fullScreen_Viewport);//�r���[�|�[�g�̐ݒ�

			DrawResult();
			break;
		
		case MODE_TUTORIAL://�`���[�g���A�����
			//�r���[�|�[�g�����Ƃɖ߂�
			pDevice->SetViewport(&g_fullScreen_Viewport);//�r���[�|�[�g�̐ݒ�

			DrawTutorial();
			break;

		case MODE_MENU://���j���[���
		//�r���[�|�[�g�����Ƃɖ߂�
			pDevice->SetViewport(&g_fullScreen_Viewport);//�r���[�|�[�g�̐ݒ�

			DrawMenuFrame();
			break;
		}
			
	//	DrawFPS();
#if _DEBUG
			DrawDebugText();
#endif
		


	//	DrawTextSet(D3DXVECTOR3(900.0f, 0.0f, 0.0f), 30, FONT_DOKIDOKI, D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f),"�e�X�g�[FPS%d", g_nCountFPS);


		
		DrawFade();//�t�F�[�h

		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//=============================
//���[�h�̐ݒ菈��
//=============================
void Setmode(MODE g_ModeNext)
{
	//���݂̉��(���[�h)�̐ݒ菈��
	switch (g_mode)
	{
	case MODE_TITLE://�^�C�g�����
		UninitTitle();
		break;

	case MODE_GAME://�Q�[�����
		UninitGame();
		break;

	case MODE_RESULT://���U���g���
		UninitResult();
		break;

	case MODE_TUTORIAL://�`���[�g���A�����
		UninitTutorial();
		break;

	case MODE_MENU://���j���[���
		UninitMenuFrame();
		break;

	}
	g_OldMode = g_mode;
	g_mode = g_ModeNext;//���݂̉��(���[�h)��؂�ւ���

	//���݂̉��(���[�h)�̏���������

	switch (g_ModeNext)
	{
	case MODE_TITLE://�^�C�g�����
		InitTitle();
		break;

	case MODE_GAME://�Q�[�����

		//InitAllScoreManagement();//�X�R�A�Ǘ���������

		bClearFrag = false;

		// �f���^�^�C���̏�����
		InitializeDeltaTimer();

		InitGame();

		break;

	case MODE_RESULT://���U���g���
		InitResult();
		break;

	case MODE_TUTORIAL://�`���[�g���A�����
		InitTutorial();
		break;

	case MODE_MENU://���j���[���
		InitMenuFrame();
		break;
	}




}
//=============================
//���[�h�̎擾
//=============================
MODE GetMode(void)
{
	return g_mode;
}
//=============================
//���[�h�̎擾
//=============================
MODE GetOldMode(void)
{
	return g_OldMode;
}
//=============================
//�S��ʗp�r���[�|�[�g�擾
//=============================
D3DVIEWPORT9 GetViewPort(void)
{
	return g_fullScreen_Viewport;
}

//=============================
// �f���^�^�C����������
//=============================
void InitializeDeltaTimer(void) 
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	g_frequency = 1.0 / frequency.QuadPart;

	QueryPerformanceCounter(&g_startTime);
}
//=============================
// �f���^�^�C�����擾
//=============================
double GetDeltaTimer(void) 
{
	QueryPerformanceCounter(&g_endTime);
	double delta = (g_endTime.QuadPart - g_startTime.QuadPart) * g_frequency;

	g_startTime = g_endTime;

	return delta;
}
//=============================
// �E�B���h�E���t���X�N���[���ɕς��鏈��
//=============================
void ToggleFullscreen(HWND hWnd)
{
	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// �E�B���h�E���[�h�ɐ؂�ւ�
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// �t���X�N���[�����[�h�ɐ؂�ւ�
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}

////=============================
////FPS�\������
////=============================
//void DrawFPS(void)
//{
//	RECT rect = { 0,0,SCREEN_WIDE,SCREEN_HEIGHT};
//	char aStr[1024];
//	//������ɑ��
//	wsprintf(&aStr[0], "FPS:%d", g_nCountFPS);
//
//	//�e�L�X�g�̕`��
//	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 15, 15, 255));
//
//}
//=============================
//�f�o�b�O�R�����g�\������
//=============================
void DrawDebugText(void)
{
	RECT rect = { 0,0,SCREEN_WIDE,SCREEN_HEIGHT};
//	char aStr[1024];

	Camera* pCamera;
	pCamera = GetCamera();//�Ƃ肠����

	Player* pPlayer;
	pPlayer = GetPlayer();

	////�v���C���[����
	//int yRot = pPlayer[0].rot.y * 100;

	////�J��������
	//int CameraRot = pCamera[0].rot.y * 100;

	////�J�����ʒu
	//int fXdate = pCamera[0].posV.x;
	//int fYdate = pCamera[0].posV.y;
	//int fZdate = pCamera[0].posV.z;

	//�v���[���[�ʒu
	int Xpos = pPlayer->pos.x;
	int Ypos = pPlayer->pos.y;
	int Zpos = pPlayer->pos.z;

	//������ɑ��
	//wsprintf(&aStr[0], "F4-���b�V���\��\n\n�J�����p�x:%d\n�v���C���[���W\nX:%d/Y:%d/Z:%d\n�v���C���[�̊p�x:%d\n++�J�������W++\nX���W:%d\nY���W:%d\nZ���W:%d\n+---------+\n--�v���C���[����--\n���X�e�B�b�N--�ړ�\n�E�X�e�B�b�N--�J��������\nA�{�^��--����\n\nP:�f�o�b�O�p�|�[�Y\nO:Result��", CameraRot, Xpos, Ypos, Zpos, yRot, fXdate, fYdate, fZdate);

	////������ɑ��
	//wsprintf(&aStr[0],"�t���[��--%d\n�L�[ %d", pPlayer->NowFrameCntDOWN,pPlayer->NowKeyCntDOWN);

	////�e�L�X�g�̕`��
	//g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 55, 55, 255));



	//DrawTextSet(D3DXVECTOR3(750.0f, 0.0f, 0.0f), 0, FONT_AKABARASINDELERA, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), "�t���[��--%d", pPlayer->NowFrameCntDOWN);
	DrawTextSet(D3DXVECTOR3(950.0f, 670.0f, 0.0f), 0, FONT_AKABARASINDELERA, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), "�PP�̈ʒu--,%d,%d,%d", Xpos, Ypos, Zpos);

}

//=============================
//Clear�t���O���Ă鏈��
//=============================
void GameClearFragOn(void)
{
	bClearFrag = true;
}
//=============================
//Clear�t���O�擾����
//=============================
bool GetGameClearFrag(void)
{
	return bClearFrag;
}



















//-----------------------------------------------------------------------------�e�X�g
//
//ID3DXSprite* g_pSprite = NULL;
//LPDIRECT3DTEXTURE9 g_pFontTexture = NULL;
//
//
//
////=============================
////�t�H���g������
////=============================
//void InitFont(LPDIRECT3DDEVICE9 g_pD3DDevice)
//{
//	// �t�H���g�̃e�N�X�`���쐬
//	D3DXCreateTextureFromFile(g_pD3DDevice, "data\\FONT\\DokiDokiFantasia.otf", &g_pFontTexture);
//
//	// �t�H���g�쐬
//	D3DXCreateFont(g_pD3DDevice, 30, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET,
//		OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, "Arial", &g_pFont_Comment);
//
//	// �X�v���C�g�쐬
//	D3DXCreateSprite(g_pD3DDevice, &g_pSprite);
//}
////=============================
////�t�H���g�I������
////=============================
//void UninitFont()
//{
//	if (g_pFontTexture)
//		g_pFontTexture->Release();
//
//	if (g_pFont_Comment)
//		g_pFont_Comment->Release();
//
//	if (g_pSprite)
//		g_pSprite->Release();
//}
////=============================
////�R�����g�`��
////=============================
//void RenderFrame(LPDIRECT3DDEVICE9 g_pD3DDevice)
//{
//	// �t�H���g�`��̂��߂̐ݒ�
//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
//
//	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
//	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//
//	// �t�H���g�`��
//	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
//	g_pSprite->Draw(g_pFontTexture, NULL, NULL, NULL, 0xFFFFFFFF);
//	RenderText("�e�X�g!", 100, 100);
//	g_pSprite->End();
//}
////=============================
////�����_�[�e�L�X�g�Z�b�g
////=============================
//void RenderText(const char* text, int x, int y)
//{
//	RECT rc = { x, y, 0, 0 };
//
//	g_pFont_Comment->DrawText(g_pSprite, text, -1, &rc, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
//}