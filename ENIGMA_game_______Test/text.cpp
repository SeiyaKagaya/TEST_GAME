//============================================================================================
//
//�e�L�X�g�\�����鏈��[Text.cpp]
// Author seiya kagaya
//
//============================================================================================
#include <stdarg.h>  // �ϒ������֘A�̃w�b�_
#include "text.h"
#include <stdio.h>
#include "camera.h"

LPD3DXFONT g_pFont_Comment[MAXFONT] = {};//�t�H���g�ւ̃|�C���^
LPD3DXFONT g_pFont_World[MAXFONT] = {};//�t�H���g�ւ̃|�C���^

//�t�H���g�\����
typedef struct
{
	const char* pFilePass;	// �t�@�C���p�X
	const char* pFontName;	// �t�H���g�l�[��
} FONTINFO;

// �t�H���g�̏��
//-------------------------------------------
//�@�@"�t�@�C���p�X","�t�H���g��"
//-------------------------------------------
FONTINFO g_FontInfo[FONT_MAX] =
{
	{"data\\FONT\\DokiDokiFantasia.otf", "�ǂ��ǂ��t�@���^�W�A"},	 
	{"data\\FONT\\akabara-cinderella.ttf", "���K�N�V���f����"},
	{"data\\FONT\\keifont.ttf", "�����ӂ����"},
	{"data\\FONT\\SoukouMincho.ttf", "���b����"},
	{"data\\FONT\\kiraraji04.ttf", "����玚04"},
	{"data\\FONT\\onryou.TTF", "����"},
	{"data\\FONT\\ZH-CN.TTF", "SDK_SC_Web Heavy"},

};



D3DXMATRIX g_mtxWorldText;

//=============================
//���U���g��ʂ̏���������
//=============================
void InitText(void)
{
	UninitText();

	//�t�H���g�̓ǂݍ��݃e�X�g//
	for (int i = 0; i < FONT_MAX; i++)
	{
		LPCSTR font_path = g_FontInfo[i].pFilePass; // �����Ŋe�t�H���g���g�p�\��
	
		if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0)
		{
		}
		else
		{
			// �t�H���g�Ǎ��G���[����
			MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
		}
	}
}
//=============================
//���U���g��ʂ̏I������
//=============================
void UninitText(void)
{
	for (int i = 0; i < MAXFONT; i++)
	{
		//UIComment�\���p�t�H���g�̔j��
		if (g_pFont_Comment[i] != NULL)
		{
			g_pFont_Comment[i]->Release();
			g_pFont_Comment[i] = NULL;
		}
		//UIComment�\���p�t�H���g�̔j��
		if (g_pFont_World[i] != NULL)
		{
			g_pFont_World[i]->Release();
			g_pFont_World[i] = NULL;
		}
	}
}

//=============================
//UI�R�����g�\������
//=============================
void DrawTextSet(D3DXVECTOR3 DrawPos, int FontSize, FONT Font, D3DXCOLOR RGBA, const char* Text, ...)
{//...�͉ϒ������iVariable Arguments�j
	
	 //�������厖
	if (g_pFont_Comment[Font] != nullptr)
	{
		g_pFont_Comment[Font]->Release();
		g_pFont_Comment[Font] = nullptr;
	}

	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	RECT rect = { DrawPos.x,DrawPos.y,SCREEN_WIDE,SCREEN_HEIGHT };
	char aStr[1024];

	D3DXCreateFont(pDevice, FontSize, 0, FW_HEAVY, 1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_TT_ONLY_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		TEXT(g_FontInfo[Font].pFontName),//--�ǂݍ��񂾃t�H���g�̖��O(�v���p�e�B�̃^�C�g���ŕ�����)
		&g_pFont_Comment[Font]);

	//D3DXCreateFont�̈����̈Ӗ�
	
	//D3DXCreateFont(pDevice,                /* �f�o�C�X */
	//	16,                            /* �����̍��� */
	//	0,                            /* ������ */
	//	FW_NORMAL,                    /* �t�H���g�̑��� */
	//	1,                            /* MIPMAP�̃��x�� */
	//	FALSE,                        /* �C�^���b�N���H */
	//	DEFAULT_CHARSET,            /* �����Z�b�g */
	//	OUT_DEFAULT_PRECIS,            /* �o�͐��x */
	//	DEFAULT_QUALITY,            /* �o�͕i�� */
	//	DEFAULT_PITCH | FF_SWISS,    /* �t�H���g�s�b�`�ƃt�@�~�� */
	//	L"�l�r �o�S�V�b�N",                    /* �t�H���g�� */
	//	&lpFont)         /* Direct3D�t�H���g�ւ̃|�C���^�ւ̃A�h���X */




	// �ϒ������̏���-------
	va_list args;				 //�ϒ������̈������X�g���w�肷��
	va_start(args, Text);		 //va_list ��������--��//�ϒ������̈�O�̈������w��
	vsprintf_s(aStr, Text, args);//�����w�蕶������g�p���ĉϒ��������當����𐶐����邽�߂̈��S�Ȋ֐�
	va_end(args);				 //va_start �}�N���ɂ���ĊJ�n���ꂽ�ϒ��������X�g���I�����邽�߂Ɏg�p

	// �e�L�X�g�̕`��
	g_pFont_Comment[Font]->DrawText(NULL, aStr, -1, &rect, DT_LEFT/* | DT_WORDBREAK*/, RGBA);



	//�g�p��I�I

	//	DrawTextSet(�@���W�@, �t�H���g�T�C�Y�@, �t�H���g���i��.�ō�������x���I�ȁj, �J���[, "�ł���������(�C�ӂ�%d.%f,%s)",(�C�ӂŕϐ�));
}



