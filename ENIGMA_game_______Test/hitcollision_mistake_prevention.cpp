//=========================================================
//
//�����蔻�蔲���j�~�����鏈��[hitcollision_mistake_prevention.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "hitcollision_mistake_prevention.h"
//#include "player.h"
//#include "player2.h"
//#include "line.h"


//�O���[�o���ϐ��錾
LPD3DXMESH g_pMeshCollision_Pre[MAXCOLLISION_PRE] = {};//���b�V��(���_���)�ւ̃|�C���^

LPD3DXBUFFER g_pBuffMatCollision_Pre[MAXCOLLISION_PRE] = {};//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatCollision_Pre = 0;//�}�e���A���̐�

COLLISION_PRE g_Collision_Pre[MAXCOLLISION_PRE];




//=============================
// �����蔻�蔲���h�~����������
//=============================
void InitCollision_Pre(void)
{    // �ϐ��̏�����
    for (int nCntGate = 0; nCntGate < MAXCOLLISION_PRE; nCntGate++)
    {
        g_Collision_Pre[nCntGate].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_Collision_Pre[nCntGate].Min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_Collision_Pre[nCntGate].Max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

        g_Collision_Pre[nCntGate].bUse = false;
    }





    //---------------------���W------------------------�ŏ�--------------------�ő�---------�F-
    // �y�A�łQ���ƂɋL��--�F�͒P�F��(�����F�𑼂̂Ɏg�p������)
        

    //�\���H�̕�        
    SetCollision_Pre(D3DXVECTOR3(50.0f, 0.0f, -2745.0f), D3DXVECTOR3(-400.0f, 0.0f, -105.0f), D3DXVECTOR3(400.0f, 300.0f, 105.0f), D3DXCOLOR(5.0f, 0.0f, 0.0f, 0.5f));
    SetCollision_Pre(D3DXVECTOR3(50.0f, 0.0f, -3055.0f), D3DXVECTOR3(-400.0f, 0.0f, -105.0f), D3DXVECTOR3(400.0f, 300.0f, 105.0f), D3DXCOLOR(5.0f, 0.0f, 0.0f, 0.5f));

    SetCollision_Pre(D3DXVECTOR3(-1250.0f, 0.0f, -2745.0f), D3DXVECTOR3(-400.0f, 0.0f, -105.0f), D3DXVECTOR3(400.0f, 300.0f, 105.0f), D3DXCOLOR(5.0f, 0.0f, 0.0f, 0.5f));
    SetCollision_Pre(D3DXVECTOR3(-1250.0f, 0.0f, -3055.0f), D3DXVECTOR3(-400.0f, 0.0f, -105.0f), D3DXVECTOR3(400.0f, 300.0f, 105.0f), D3DXCOLOR(5.0f, 0.0f, 0.0f, 0.5f));

    SetCollision_Pre(D3DXVECTOR3(-445.0f, 0.0f, -2250.0f), D3DXVECTOR3(-105.0f, 0.0f, -400.0f), D3DXVECTOR3(105.0f, 300.0f, 400.0f), D3DXCOLOR(5.0f, 0.0f, 0.0f, 0.5f));
    SetCollision_Pre(D3DXVECTOR3(-755.0f, 0.0f, -2250.0f), D3DXVECTOR3(-105.0f, 0.0f, -400.0f), D3DXVECTOR3(105.0f, 300.0f, 400.0f), D3DXCOLOR(5.0f, 0.0f, 0.0f, 0.5f));

    SetCollision_Pre(D3DXVECTOR3(-445.0f, 0.0f, -3550.0f), D3DXVECTOR3(-105.0f, 0.0f, -400.0f), D3DXVECTOR3(105.0f, 300.0f, 400.0f), D3DXCOLOR(5.0f, 0.0f, 0.0f, 0.5f));
    SetCollision_Pre(D3DXVECTOR3(-755.0f, 0.0f, -3550.0f), D3DXVECTOR3(-105.0f, 0.0f, -400.0f), D3DXVECTOR3(105.0f, 300.0f, 400.0f), D3DXCOLOR(5.0f, 0.0f, 0.0f, 0.5f));



    //�\���H�̕�(�ʘH�[)        
    SetCollision_Pre(D3DXVECTOR3(-1640.0f, 0.0f, -2900.0f), D3DXVECTOR3(-100.0f, 0.0f, -100.0f), D3DXVECTOR3(100.0f, 600.0f, 100.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));
    SetCollision_Pre(D3DXVECTOR3(440.0f, 0.0f, -2900.0f), D3DXVECTOR3(-100.0f, 0.0f, -100.0f), D3DXVECTOR3(100.0f, 600.0f, 100.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));

    SetCollision_Pre(D3DXVECTOR3(-600.0f, 0.0f, -4000.0f), D3DXVECTOR3(-100.0f, 0.0f, -100.0f), D3DXVECTOR3(100.0f, 600.0f, 100.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));
    SetCollision_Pre(D3DXVECTOR3(-600.0f, 0.0f, -1800.0f), D3DXVECTOR3(-100.0f, 0.0f, -100.0f), D3DXVECTOR3(100.0f, 600.0f, 100.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));

    //�����
    SetCollision_Pre(D3DXVECTOR3(3237.0f, 0.0f, -260.0f), D3DXVECTOR3(-400.0f, 0.0f, 09.0f), D3DXVECTOR3(160.0f, 300.0f, 10.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));
    
    SetCollision_Pre(D3DXVECTOR3(3500.0f, 150.0f, -100.0f), D3DXVECTOR3(-2.0f, 0.0f, -050.0f), D3DXVECTOR3(2.0f, 200.0f, 050.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));
    
    SetCollision_Pre(D3DXVECTOR3(3600.0f, 0.0f, -400.0f), D3DXVECTOR3(-100.0f, 0.0f, -250.0f), D3DXVECTOR3(100.0f, 300.0f, 250.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));
    
    SetCollision_Pre(D3DXVECTOR3(3200.0f, 120.0f, -450.0f), D3DXVECTOR3(-2.0f, 0.0f, -200.0f), D3DXVECTOR3(2.0f, 200.0f, 200.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));
    
    SetCollision_Pre(D3DXVECTOR3(3200.0f, 0.0f, -600.0f), D3DXVECTOR3(-4.0f, 0.0f, -100.0f), D3DXVECTOR3(4.0f, 120.0f, 100.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));
   
    SetCollision_Pre(D3DXVECTOR3(3200.0f, 0.0f, -320.0f), D3DXVECTOR3(-4.0f, 0.0f, -80.0f), D3DXVECTOR3(4.0f, 120.0f, 50.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));
    
    SetCollision_Pre(D3DXVECTOR3(3400.0f, 0.0f, -1800.0f), D3DXVECTOR3(-300.0f, 0.0f, -100.0f), D3DXVECTOR3(300.0f, 300.0f, 100.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));

    //�g�C����
    SetCollision_Pre(D3DXVECTOR3(3525.0f, 0.0f, 20.0f), D3DXVECTOR3(-130.0f, 0.0f, -70.0f), D3DXVECTOR3(130.0f, 300.0f, 70.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));

}
//=============================
// �����蔻�蔲���h�~�I������
//=============================
void UninitCollision_Pre(void)
{
    for (int nCntGate = 0; nCntGate < MAXCOLLISION_PRE; nCntGate++)
    {
        //���b�V���̔j��
        if (g_pMeshCollision_Pre[nCntGate] != NULL)
        {
            g_pMeshCollision_Pre[nCntGate]->Release();
            g_pMeshCollision_Pre[nCntGate] = NULL;
        }
        //�}�e���A���̔j��
        if (g_pBuffMatCollision_Pre[nCntGate] != NULL)
        {
            g_pBuffMatCollision_Pre[nCntGate]->Release();
            g_pBuffMatCollision_Pre[nCntGate] = NULL;
        }
    }
}

//=============================
// �����蔻�蔲���h�~�X�V����
//=============================
void UpdateCollision_Pre(void)
{
    for (int nCntGate = 0; nCntGate < MAXCOLLISION_PRE; nCntGate++)
    {
        if (g_Collision_Pre[nCntGate].bUse == true)
        {
            D3DXVECTOR3 Collision_PreMin = g_Collision_Pre[nCntGate].pos + g_Collision_Pre[nCntGate].Min;
            D3DXVECTOR3 Collision_PreMax = g_Collision_Pre[nCntGate].pos + g_Collision_Pre[nCntGate].Max;

#if _DEBUG
            ////���C���̈ʒu
            //// �㉺�̕�
            //SetLine(D3DXVECTOR3(Collision_PreMin.x, Collision_PreMax.y, Collision_PreMin.z), D3DXVECTOR3(Collision_PreMax.x, Collision_PreMax.y, Collision_PreMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(Collision_PreMin.x, Collision_PreMin.y, Collision_PreMin.z), D3DXVECTOR3(Collision_PreMax.x, Collision_PreMin.y, Collision_PreMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //SetLine(D3DXVECTOR3(Collision_PreMin.x, Collision_PreMax.y, Collision_PreMax.z), D3DXVECTOR3(Collision_PreMax.x, Collision_PreMax.y, Collision_PreMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(Collision_PreMin.x, Collision_PreMin.y, Collision_PreMax.z), D3DXVECTOR3(Collision_PreMax.x, Collision_PreMin.y, Collision_PreMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //// ���ʂ̕�
            //SetLine(D3DXVECTOR3(Collision_PreMin.x, Collision_PreMin.y, Collision_PreMin.z), D3DXVECTOR3(Collision_PreMin.x, Collision_PreMax.y, Collision_PreMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(Collision_PreMax.x, Collision_PreMin.y, Collision_PreMin.z), D3DXVECTOR3(Collision_PreMax.x, Collision_PreMax.y, Collision_PreMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //SetLine(D3DXVECTOR3(Collision_PreMin.x, Collision_PreMin.y, Collision_PreMax.z), D3DXVECTOR3(Collision_PreMin.x, Collision_PreMax.y, Collision_PreMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(Collision_PreMax.x, Collision_PreMin.y, Collision_PreMax.z), D3DXVECTOR3(Collision_PreMax.x, Collision_PreMax.y, Collision_PreMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //// ���̑��̕�
            //SetLine(D3DXVECTOR3(Collision_PreMin.x, Collision_PreMin.y, Collision_PreMin.z), D3DXVECTOR3(Collision_PreMin.x, Collision_PreMin.y, Collision_PreMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(Collision_PreMax.x, Collision_PreMax.y, Collision_PreMin.z), D3DXVECTOR3(Collision_PreMax.x, Collision_PreMax.y, Collision_PreMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //SetLine(D3DXVECTOR3(Collision_PreMin.x, Collision_PreMax.y, Collision_PreMin.z), D3DXVECTOR3(Collision_PreMin.x, Collision_PreMax.y, Collision_PreMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(Collision_PreMax.x, Collision_PreMin.y, Collision_PreMin.z), D3DXVECTOR3(Collision_PreMax.x, Collision_PreMin.y, Collision_PreMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

#endif







        }
    }
}

//=============================
// �����蔻�蔲���h�~�`�揈��
//=============================
void DrawCollision_Pre(void)
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

    D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p(�ꎞ�ޔ�)

    D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

    for (int nCntGate = 0; nCntGate < MAXCOLLISION_PRE; nCntGate++)
    {
        if (g_Collision_Pre[nCntGate].bUse == true)
        {
            ////���C�g�𖳌��ɂ���
            //pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

            ////Z�̔�r�ύX
            //pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
            ////Z�o�b�t�@�ɏ������܂Ȃ�
            //pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);



            //���[���h�}�g���b�N�X�̏�����
            D3DXMatrixIdentity(&g_Collision_Pre[nCntGate].mtxWorld);

            // ���f���̃T�C�Y��ύX
            D3DXMatrixScaling(&g_Collision_Pre[nCntGate].mtxWorld, g_Collision_Pre[nCntGate].SizeMag.x, g_Collision_Pre[nCntGate].SizeMag.y, g_Collision_Pre[nCntGate].SizeMag.z);

            ////�����𔽉f
            //D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);

            //D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

            //�ʒu�𔽉f
            D3DXMatrixTranslation(&mtxTrans, g_Collision_Pre[nCntGate].pos.x, g_Collision_Pre[nCntGate].pos.y, g_Collision_Pre[nCntGate].pos.z);

            D3DXMatrixMultiply(&g_Collision_Pre[nCntGate].mtxWorld, &g_Collision_Pre[nCntGate].mtxWorld, &mtxTrans);

            //���[���h�}�g���b�N�X�̐ݒ�
            pDevice->SetTransform(D3DTS_WORLD, &g_Collision_Pre[nCntGate].mtxWorld);

            //���݂̃}�e���A�����擾
            pDevice->GetMaterial(&matDef);

            //�}�e���A���f�[�^�ւ̃|�C���^���擾
            pMat = (D3DXMATERIAL*)g_pBuffMatCollision_Pre[nCntGate]->GetBufferPointer();

            for (int nCntMat = 0; nCntMat < (int)g_dwNumMatCollision_Pre; nCntMat++)
            {
                //�}�e���A���̐ݒ�
            //    pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                //�e�N�X�`���̐ݒ�
                pDevice->SetTexture(0, NULL);//����͐ݒ肵�Ȃ�

                //���f��(�p�[�c)�̕`��
                g_pMeshCollision_Pre[nCntMat]->DrawSubset(nCntMat);

                //�ۑ����Ă��}�e���A����߂�
             //   pDevice->SetMaterial(&matDef);


                // �}�e���A���̐ݒ�
                pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                // �f�B�t���[�Y�J���[��ύX�i��: �Ԃ��F�j
                pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(g_Collision_Pre[nCntGate].GateColor.r * g_Collision_Pre[nCntGate].SizeMag.x, g_Collision_Pre[nCntGate].GateColor.g * g_Collision_Pre[nCntGate].SizeMag.x, g_Collision_Pre[nCntGate].GateColor.b * g_Collision_Pre[nCntGate].SizeMag.x, g_Collision_Pre[nCntGate].GateColor.a);

                ////���C�g��L���ɂ���
                //pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

                ////Z�̔�r�ύX
                //pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
                ////Z�o�b�t�@�ɏ������܂Ȃ�
                //pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
            }

            //�ۑ����Ă��}�e���A����߂�
            pDevice->SetMaterial(&matDef);

            //�e�N�X�`����߂�
            pDevice->SetTexture(0, NULL);
        }
    }




}
//=============================
// �����蔻�蔲���h�~�擾����
//=============================
COLLISION_PRE* GetCollision_Pre(void)
{
    return &g_Collision_Pre[0];
}
//=============================
// �����蔻�蔲���h�~�ݒ菈��
//=============================
//-----------------------------�������W-----------------�ŏ�----------------�ő�---------�����̔ԍ�----�]�ڐ�̔ԍ�--�����]�ڂ��ǂ���--�s���{�^���œ]�ڂ��ǂ���
void SetCollision_Pre(D3DXVECTOR3 Pos, D3DXVECTOR3 GateMin, D3DXVECTOR3 GateMax, D3DXCOLOR GateColor)
{
    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = GetDevice();//----------------���������ς�

    for (int nCntGate = 0; nCntGate < MAXCOLLISION_PRE; nCntGate++)
    {
        if (g_Collision_Pre[nCntGate].bUse == false)
        {
            g_Collision_Pre[nCntGate].pos = Pos;
            g_Collision_Pre[nCntGate].Min = GateMin;
            g_Collision_Pre[nCntGate].Max = GateMax;
            g_Collision_Pre[nCntGate].GateColor = GateColor;
         
            //�T�C�Y�ϓ�
            g_Collision_Pre[nCntGate].SizeMag.x = g_Collision_Pre[nCntGate].Max.x / 10.0f;
            g_Collision_Pre[nCntGate].SizeMag.y = g_Collision_Pre[nCntGate].Max.y / 20.0f;
            g_Collision_Pre[nCntGate].SizeMag.z = g_Collision_Pre[nCntGate].Max.z / 10.0f;

            g_Collision_Pre[nCntGate].bUse = true;

            //�t�@�C���̓ǂݍ���
            D3DXLoadMeshFromX("data\\MODEL\\DebugModel\\BOX.x",
                D3DXMESH_SYSTEMMEM,
                pDevice,
                NULL,
                &g_pBuffMatCollision_Pre[nCntGate],
                NULL,
                &g_dwNumMatCollision_Pre,
                &g_pMeshCollision_Pre[nCntGate]);

            break;
        }
    }
}

