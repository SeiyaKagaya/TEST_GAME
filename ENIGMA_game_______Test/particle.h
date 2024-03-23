//=========================================================
//
//�p�[�e�B�N���֌W�Ŏg���ϐ��A�錾�A�\����[particle.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _PARTICLE_H_

#define _PARTICLE_H_//��d�C���N���[�h�h�~

#include"main.h"

//�}�N����`
#define MAX_PARTICLE	(2048)

//�e�N�X�`���̐�
#define NUMTEX	(2)


//�p�[�e�B�N���̎��
enum PARTICLETYPE//�񋓂������������̃��f���P�[�X
{
	PARTICLETYPE_ITEM = 0,

	PARTICLETYPE_MAX
};

//�G�t�F�N�g�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X

	D3DXCOLOR col;		//�F
	float fRadius;		//���a(�傫��)
	float DiffRadius;	//���a������	
	float nLife;		//����(�\������)
	float nType;		//�^�C�v����
	int nloopCnt;		//���[�v
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Particle;

//�v���g�^�C�v�錾
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 Pos, float fRadius, int nLife, PARTICLETYPE Type, D3DXCOLOR Color);

Particle* GetParticle(void);

#endif // _PARTICLE_H_