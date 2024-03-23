//=========================================================
//
//�ȈՃ��[�V����MODEL�錾�Ȃ�[simple_motion_model.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SIMPELMOTION_//���̃}�N������`����ĂȂ�������

//�}�N����`
#define _SIMPELMOTION_//��d�C���N���[�h�h�~�̃}�N����`

#include "game.h"
//
//#define MAX_BOOSTER	(1)//�u�[�X�^�[�p�[�c��
//#define MAX_BOOSTERPARTS	(2)//�u�[�X�^�[�p�[�c��


//�t�H���g�̎��
//--------------------�t�H���g�̃��x���I��
typedef enum
{
	SIMPLEMOTIONMODEL_Test1 = 0,//
	SIMPLEMOTIONMODEL_Test2,
	SIMPLEMOTIONMODEL_LEVER_RED_ROOT,	//�ԃ��o�[�̍��{
	SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT,	//���o�[�̍��{
	SIMPLEMOTIONMODEL_LEVER_RED_LEVER,	//�ԃ��o�[�̃��o�[
	SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER,	//���o�[�̃��o�[

	SIMPLEMOTIONMODEL_LEVER_RED_ROOT2,	//�ԃ��o�[�̍��{
	SIMPLEMOTIONMODEL_LEVER_BLUE_ROOT2,	//���o�[�̍��{
	SIMPLEMOTIONMODEL_LEVER_RED_LEVER2,	//�ԃ��o�[�̃��o�[
	SIMPLEMOTIONMODEL_LEVER_BLUE_LEVER2,	//���o�[�̃��o�[

	SIMPLEMOTIONMODEL_MAX,
}SIMPLEMOTIONMODEL;


//���̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu

	D3DXVECTOR3 rot;	//����

	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X

	bool bUse;
}SIMPLEMODEL;

//�v���g�^�C�v�錾
void InitSimpleModel(void);
void UninitSimpleModel(void);
void UpdateSimpleModel(void);
void DrawSimpleModel(void);
void LaverOn(void);
void SpawnKey(void);
void LaverOnTtl(void);
void SpawnKeyTtl(void);

//�ȈՃ��[�V�������f���ݒ菈��
void SetSimpleModel(SIMPLEMOTIONMODEL SetUpName_Index, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
bool GetSpawnKey_Lever(void);
bool GetSpawnKey_Leverttl(void);

#endif // !_PLAYER_H_
