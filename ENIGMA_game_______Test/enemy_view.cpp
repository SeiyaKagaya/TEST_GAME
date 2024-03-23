//=========================================================
//
//�G�̎���[enemy_view.cpp]
// Author Matsuda Towa
//
//=========================================================
#include "enemy_view.h"
#include "enemy.h"
#include "main.h"

//=========================================================
//�O���[�o���ϐ��錾
//=========================================================
LPD3DXMESH g_pMeshEnemy_View[MAX_ENEMYVIEW] = {};//���b�V��(���_���)�ւ̃|�C���^

LPD3DXBUFFER g_pBuffMatEnemy_View[MAX_ENEMYVIEW] = {};//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatEnemy_View = 0;//�}�e���A���̐�

ENEMYVIEW g_Enemy_View[MAX_ENEMYVIEW];
//=========================================================
//������
//=========================================================
void InitEnemy_View(void)
{
    // �ϐ��̏�����
    for (int nCnt = 0; nCnt < MAX_ENEMYVIEW; nCnt++)
    {
        g_Enemy_View[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_Enemy_View[nCnt].ZoneMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_Enemy_View[nCnt].ZoneMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_Enemy_View[nCnt].nZoneIndex = -1;
        //   g_ActionZone[nCntZone].nParentIndex = -1;
        g_Enemy_View[nCnt].bFollowEnemy = false;
        g_Enemy_View[nCnt].bUse = false;
        g_Enemy_View[nCnt].bDrawOk = false;
    }
    SetEnemy_View(D3DXVECTOR3(0.0f, 500.0f, 0.0f), 200,false, D3DXCOLOR(0.0f, 0.0f, 0.5f, 0.0f));
    SetEnemy_View(D3DXVECTOR3(0.0f, 500.0f, 0.0f), 200,false, D3DXCOLOR(0.0f, 0.0f, 0.5f, 0.0f));

}

//=========================================================
//�I��
//=========================================================
void UninitEnemy_View(void)
{
    for (int nCntZone = 0; nCntZone < MAX_ENEMYVIEW; nCntZone++)
    {
        //���b�V���̔j��
        if (g_pMeshEnemy_View[nCntZone] != NULL)
        {
            g_pMeshEnemy_View[nCntZone]->Release();
            g_pMeshEnemy_View[nCntZone] = NULL;
        }
        //�}�e���A���̔j��
        if (g_pBuffMatEnemy_View[nCntZone] != NULL)
        {
            g_pBuffMatEnemy_View[nCntZone]->Release();
            g_pBuffMatEnemy_View[nCntZone] = NULL;
        }
    }
}

//=========================================================
//�X�V
//=========================================================
void UpdateEnemy_View(void)
{
    for (int nCntZone = 0; nCntZone < MAX_ENEMYVIEW; nCntZone++)
    {
        if (g_Enemy_View[nCntZone].bUse == true)
        {
            ENEMYMODEL* pEnemy = GetEnemy();
            g_Enemy_View[nCntZone].pos += pEnemy->move;
            //D3DXMATRIX mtxRot, mtxTrans, mtxParent;//�v�Z�p�}�g���b�N�X	

            //for (int nCntZone = 0; nCntZone < MAX_ENEMYVIEW; nCntZone++)
            //{

            //    if (g_Enemy_View[nCntZone].bDrawOk == true)
            //    {
            //        //���[���h�}�g���b�N�X�̏�����
            //        D3DXMatrixIdentity(&g_Enemy_View[nCntZone].mtxWorld);

            //        // ���f���̃T�C�Y��ύX
            //        D3DXMatrixScaling(&g_Enemy_View[nCntZone].mtxWorld, g_Enemy_View[nCntZone].SizeMag.x, g_Enemy_View[nCntZone].SizeMag.y, g_Enemy_View[nCntZone].SizeMag.z);


            //        if (g_Enemy_View[nCntZone].bFollowEnemy == true)
            //        {

            //            ////�����𔽉f
            //            //D3DXMatrixRotationYawPitchRoll(&mtxRot, pEnemy->rot.y, pEnemy->rot.x, pEnemy->rot.z);

            //            //D3DXMatrixMultiply(&g_Enemy_View[nCntZone].mtxWorld, &g_Enemy_View[nCntZone].mtxWorld, &mtxRot);

            //            //�ʒu�𔽉f
            //            D3DXMatrixTranslation(&mtxTrans, g_Enemy_View[nCntZone].pos.x, g_Enemy_View[nCntZone].pos.y, g_Enemy_View[nCntZone].pos.z);

            //            D3DXMatrixMultiply(&g_Enemy_View[nCntZone].mtxWorld, &g_Enemy_View[nCntZone].mtxWorld, &mtxTrans);

            //            //�G�l�~�[��e�Ƃ��ē�����
            //            D3DXMatrixMultiply(&g_Enemy_View[nCntZone].mtxWorld, &g_Enemy_View[nCntZone].mtxWorld, &pEnemy->mtxWorld);
            //        }
            //    }

            D3DXVECTOR3 ActionZoneMin = g_Enemy_View[nCntZone].pos + g_Enemy_View[nCntZone].ZoneMin;
            D3DXVECTOR3 ActionZoneMax = g_Enemy_View[nCntZone].pos + g_Enemy_View[nCntZone].ZoneMax;

            //}
        }
    }
}

//=========================================================
//�`��
//=========================================================
void DrawEnemy_View(void)
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

    D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p(�ꎞ�ޔ�)

    D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

    for (int nCntZone = 0; nCntZone < MAX_ENEMYVIEW; nCntZone++)
    {
        if (g_Enemy_View[nCntZone].bUse == true)
        {
            if (g_Enemy_View[nCntZone].bDrawOk == true)
            {
                //���[���h�}�g���b�N�X�̏�����
                D3DXMatrixIdentity(&g_Enemy_View[nCntZone].mtxWorld);

                // ���f���̃T�C�Y��ύX
                D3DXMatrixScaling(&g_Enemy_View[nCntZone].mtxWorld, g_Enemy_View[nCntZone].SizeMag.x, g_Enemy_View[nCntZone].SizeMag.y, g_Enemy_View[nCntZone].SizeMag.z);


                //if (g_Enemy_View[nCntZone].bFollowEnemy == true)
                //{
                //    ENEMYMODEL* pEnemy = GetEnemy();
                //    ////�����𔽉f
                //    //D3DXMatrixRotationYawPitchRoll(&mtxRot, pEnemy->rot.y, pEnemy->rot.x, pEnemy->rot.z);

                //    //D3DXMatrixMultiply(&g_Enemy_View[nCntZone].mtxWorld, &g_Enemy_View[nCntZone].mtxWorld, &mtxRot);

                //    //�ʒu�𔽉f
                //    D3DXMatrixTranslation(&mtxTrans, g_Enemy_View[nCntZone].pos.x, g_Enemy_View[nCntZone].pos.y, g_Enemy_View[nCntZone].pos.z);

                //    D3DXMatrixMultiply(&g_Enemy_View[nCntZone].mtxWorld, &g_Enemy_View[nCntZone].mtxWorld, &mtxTrans);

                //    //�G�l�~�[��e�Ƃ��ē�����
                //    D3DXMatrixMultiply(&g_Enemy_View[nCntZone].mtxWorld, &g_Enemy_View[nCntZone].mtxWorld, &pEnemy->mtxWorld);
                //}
                //else
                //{


                //}
                
                //���[���h�}�g���b�N�X�̐ݒ�
                pDevice->SetTransform(D3DTS_WORLD, &g_Enemy_View[nCntZone].mtxWorld);

                //���݂̃}�e���A�����擾
                pDevice->GetMaterial(&matDef);

                //�}�e���A���f�[�^�ւ̃|�C���^���擾
                pMat = (D3DXMATERIAL*)g_pBuffMatEnemy_View[nCntZone]->GetBufferPointer();

                for (int nCntMat = 0; nCntMat < (int)g_dwNumMatEnemy_View; nCntMat++)
                {
                    //�}�e���A���̐ݒ�
                    pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                    //�e�N�X�`���̐ݒ�
                    pDevice->SetTexture(0, NULL);//����͐ݒ肵�Ȃ�

                    //���f��(�p�[�c)�̕`��
                    g_pMeshEnemy_View[nCntMat]->DrawSubset(nCntMat);

                    //�ۑ����Ă��}�e���A����߂�
                    pDevice->SetMaterial(&matDef);

                    // �}�e���A���̐ݒ�
                    pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                    // �f�B�t���[�Y�J���[��ύX�i��: �Ԃ��F�j
                    pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(g_Enemy_View[nCntZone].ZoneColor.r * g_Enemy_View[nCntZone].SizeMag.x, g_Enemy_View[nCntZone].ZoneColor.g * g_Enemy_View[nCntZone].SizeMag.x, g_Enemy_View[nCntZone].ZoneColor.b * g_Enemy_View[nCntZone].SizeMag.x, g_Enemy_View[nCntZone].ZoneColor.a);

                }
            }
        }
    }

}

//=========================================================
//����̏��擾
//=========================================================
ENEMYVIEW* GetEnemy_View(void)
{
	return &g_Enemy_View[0];
}

//=========================================================
//����Z�b�g
//=========================================================
void SetEnemy_View(D3DXVECTOR3 Pos, float Radius, bool bFollowEnemy, D3DXCOLOR ZoneColor)
{
    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = GetDevice();//----------------���������ς�

    for (int nCntZone = 0; nCntZone < MAX_ENEMYVIEW; nCntZone++)
    {
        if (g_Enemy_View[nCntZone].bUse == false)
        {
            g_Enemy_View[nCntZone].pos = Pos;
            g_Enemy_View[nCntZone].Radius = Radius;

            g_Enemy_View[nCntZone].ZoneMin = D3DXVECTOR3(-Radius, -Radius, -Radius);
            g_Enemy_View[nCntZone].ZoneMax = D3DXVECTOR3(Radius, Radius, Radius);
            g_Enemy_View[nCntZone].ZoneColor = ZoneColor;
            g_Enemy_View[nCntZone].EscapeZoneColor = ZoneColor;

            //�T�C�Y�ϓ�
            g_Enemy_View[nCntZone].SizeMag.x = g_Enemy_View[nCntZone].ZoneMax.x / 10.0f;
            g_Enemy_View[nCntZone].SizeMag.y = g_Enemy_View[nCntZone].ZoneMax.y / 10.0f;
            g_Enemy_View[nCntZone].SizeMag.z = g_Enemy_View[nCntZone].ZoneMax.z / 10.0f;

            g_Enemy_View[nCntZone].bFollowEnemy = bFollowEnemy;
            g_Enemy_View[nCntZone].bUse = true;
            g_Enemy_View[nCntZone].bDrawOk = true;

            //�t�@�C���̓ǂݍ���
            D3DXLoadMeshFromX("data\\MODEL\\DebugModel\\SPHERE.x",
                D3DXMESH_SYSTEMMEM,
                pDevice,
                NULL,
                &g_pBuffMatEnemy_View[nCntZone],
                NULL,
                &g_dwNumMatEnemy_View,
                &g_pMeshEnemy_View[nCntZone]);



            break;
        }
    }
}
