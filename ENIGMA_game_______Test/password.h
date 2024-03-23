//=========================================================
//
//�|�[�Y��ʂŎg���ϐ��A�錾�A�\����[password.h]
// Author matsuda towa
//
//=========================================================
#ifndef _PASSWORD_H

#define _PASSWORD_H//��d�C���N���[�h�h�~

#include"main.h"


//=========================================================
//�}�N����`
//=========================================================
#define NUM_DIGIT	(4) //����
#define NUM_PASSWORD	(5) //���̍ő�
#define TEX_ADD		(1.0f / (float)NUM_PASSWORD)
#define PASSWORD_FIRSTPOS_1P	(162.5f)
#define PASSWORD_FIRSTPOS_2P	(827.0f)
#define PASSWORD_ADDPOS	(105.0f)
#define PASSWORD_WIDE	(30.0f)
#define PASSWORD_HEIGHT	(30.0f)

//=========================================================
//�p�X���[�h�̎��
//=========================================================
typedef enum
{
	PASSWORDTYPE_EYE = 0,
	PASSWORDTYPE_HAND,
	PASSWORDTYPE_LEAF,
	PASSWORDTYPE_HEART,
	PASSWORDTYPE_GRAVE,
	PASSWORDTYPE_MAX,
}PasswordType;

//=========================================================
//�p�X���[�h�������\����
//=========================================================
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	PasswordType Type;						//�^�C�v
	int nType;								//�^�C�v�����炷����
}PASSWORD;

//=========================================================
//�v���g�^�C�v�錾
//=========================================================
void InitPassword(void);
void UninitPassword(void);
void UpdatePassword(void);
void DrawPassword(void);
void SetPassword(void);
void ChangePassword1P(D3DXCOLOR col, int nSelectDigit);
void ChangePassword2P(D3DXCOLOR col, int nSelectDigit);
#endif // !_PASSWORD_H