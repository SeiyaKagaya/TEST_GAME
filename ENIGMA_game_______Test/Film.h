//==============================
//
// �t�B����������[Film.h]
// Author:Kaito Hondo
//
//==============================

#ifndef _FILM_H_	// ���̃}�N����`������ĂȂ�������
#define _FILM_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//�}�N����`
//#define FILM_TEXTURE  "data\\TEXTURE\\Film000.png"
//#define FILM_TEXTURE2 "data\\TEXTURE\\Film001.png"
//#define FILM_TEXTURE3 "data\\TEXTURE\\Film002.png"
#define FILM_TEXTURE4 "data\\TEXTURE\\Film0.png"
#define NUM_FILMTEXTURE	(1)	// �w�i�̐�
#define NUM_FILM	(32)	// �t�B�����̍ő吔 

//�p�[�c�\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	float texX;
	bool bUse;
}FILM;

// �v���g�^�C�v�錾
void InitFILM(void);
void UninitFILM(void);
void UpdateFILM(void);
void DrawFILM(void);
void SetFILM(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float texX);

#endif

