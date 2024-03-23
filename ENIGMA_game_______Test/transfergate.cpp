//=========================================================
//
//�G���A�ɂ���ē]�ڂ����鏈��[transfergate.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "transfergate.h"
//#include "player.h"
//#include "player2.h"
#include "line.h"


//�O���[�o���ϐ��錾
LPD3DXMESH g_pMeshGate[MAXGATE] = {};//���b�V��(���_���)�ւ̃|�C���^

LPD3DXBUFFER g_pBuffMatGate[MAXGATE] = {};//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatGate = 0;//�}�e���A���̐�

TRANSFERGATE g_TransferGate[MAXGATE];




//=============================
// �]�ږ叉��������
//=============================
void InitTransferGate(void)
{    // �ϐ��̏�����
    for (int nCntGate = 0; nCntGate < MAXGATE; nCntGate++)
    {
        g_TransferGate[nCntGate].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_TransferGate[nCntGate].GateMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_TransferGate[nCntGate].GateMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_TransferGate[nCntGate].nGateIndex = -1;
        g_TransferGate[nCntGate].nParentIndex = -1;
        g_TransferGate[nCntGate].ParentTransAngle = TRANS_ANGLE_MAX;
        g_TransferGate[nCntGate].bCompulsionTrans = false;
        g_TransferGate[nCntGate].bPossibility = false;
        g_TransferGate[nCntGate].bUse = false;
        g_TransferGate[nCntGate].bActiomTrans = false;
    }





//---------------------���W------------------------�ŏ�--------------------�ő�---------�����̔ԍ�----�]�ڐ�̔ԍ�---�����̕���----�F--�����]�ڂ��ǂ���---------�s���{�^���œ]�ڂ��ǂ���
// �y�A�łQ���ƂɋL��--�F�͒P�F��(�����F�𑼂̂Ɏg�p������)
    //
    //---****���l--�s���{�^���]�ڂ́A�]�ʕ���(TRANS_ANGLE�`)���uTRANS_ANGLE_MAX�v�ɂł��Ȃ��B�������w�肷��ׂ�
    //

    //-----��{�̓{�^���ňړ����݂�Ȃňړ��ɂȂ邩��



   //0�`�R���\���H--�]�ڐ�������_��
    //�\���H�E
    SetTransferGate(D3DXVECTOR3(-1520.0f, 0.0f, -2900.0f), D3DXVECTOR3(-50.0f, 0.0f, -60.0f), D3DXVECTOR3(50.0f, 100.0f, 60.0f), 0, RONDOMTRANS_NUM, TRANS_ANGLE_RANDOM, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.7f), false, true);
    //�\���H��
    SetTransferGate(D3DXVECTOR3(330.0f, 0.0f, -2900.0f), D3DXVECTOR3(-50.0f, 0.0f, -60.0f), D3DXVECTOR3(50.0f, 100.0f, 60.0f), 1, RONDOMTRANS_NUM, TRANS_ANGLE_RANDOM, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.7f), false, true);

    //�\���H��
    SetTransferGate(D3DXVECTOR3(-600.0f, 0.0f, -1920.0f), D3DXVECTOR3(-50.0f, 0.0f, -50.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), 2, RONDOMTRANS_NUM, TRANS_ANGLE_RANDOM, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f), false, true);
    //�\���H��
    SetTransferGate(D3DXVECTOR3(-600.0f, 0.0f, -3880.0f), D3DXVECTOR3(-50.0f, 0.0f, -50.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), 3, RONDOMTRANS_NUM, TRANS_ANGLE_RANDOM, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f), false, true);


   //4�`8���\���H��--

    //�q�ɉ�
    SetTransferGate(D3DXVECTOR3(-600.0f, 0.0f, 90.0f), D3DXVECTOR3(-60.0f, 0.0f, -55.0f), D3DXVECTOR3(60.0f, 100.0f, 55.0f), 4, CROSSROAD_NUM, TRANS_ANGLE_MIN_Z, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f), false, true);

    //����
    SetTransferGate(D3DXVECTOR3(3000.0f, 0.0f, 40.0f), D3DXVECTOR3(-50.0f, 0.0f, -50.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), 5, CROSSROAD_NUM, TRANS_ANGLE_MIN_Z, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.7f), false, true);
  
    //���r���O��
    SetTransferGate(D3DXVECTOR3(3000, 104.0f, -1460.0f), D3DXVECTOR3(-50.0f, 0.0f, -60.0f), D3DXVECTOR3(50.0f, 100.0f, 60.0f), 6, CROSSROAD_NUM, TRANS_ANGLE_MIN_Z, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.7f), false, true);
 
    //--�q�ɍ�
    SetTransferGate(D3DXVECTOR3(-10.0f, 0.0f, -930.0f), D3DXVECTOR3(-50.0f, 0.0f, -60.0f), D3DXVECTOR3(50.0f, 100.0f, 60.0f), 7, CROSSROAD_NUM, TRANS_ANGLE_MIN_X, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.7f), false, true);


    //���r���O�K�i
    SetTransferGate(D3DXVECTOR3(3250.0f, 104.0f, -1700.0f), D3DXVECTOR3(-50.0f, 0.0f, -50.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), 8, CROSSROAD_NUM, TRANS_ANGLE_MAX_Z, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.7f), false, true);
    



    //�\���H�ǐ^��
    SetTransferGate(D3DXVECTOR3(-600.0f, 0.0f, -2900.0f), D3DXVECTOR3(-50.0f, 0.0f, -50.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), 9, RONDOMTRANS_NUM, TRANS_ANGLE_RANDOM, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f), false, true);


}
//=============================
// �]�ږ�I������
//=============================
void UninitTransferGate(void)
{
    for (int nCntGate = 0; nCntGate < MAXGATE; nCntGate++)
    {
        //���b�V���̔j��
        if (g_pMeshGate[nCntGate] != NULL)
        {
            g_pMeshGate[nCntGate]->Release();
            g_pMeshGate[nCntGate] = NULL;
        }
        //�}�e���A���̔j��
        if (g_pBuffMatGate[nCntGate] != NULL)
        {
            g_pBuffMatGate[nCntGate]->Release();
            g_pBuffMatGate[nCntGate] = NULL;
        }
    }
}

//=============================
// �]�ږ�X�V����
//=============================
void UpdateTransferGate(void)
{
    for (int nCntGate = 0; nCntGate < MAXGATE; nCntGate++)
    {
        if (g_TransferGate[nCntGate].bUse == true)
        {
            D3DXVECTOR3 TransferGateMin = g_TransferGate[nCntGate].pos + g_TransferGate[nCntGate].GateMin;
            D3DXVECTOR3 TransferGateMax = g_TransferGate[nCntGate].pos + g_TransferGate[nCntGate].GateMax;
   
#if _DEBUG
            ////���C���̈ʒu
            //// �㉺�̕�
            //SetLine(D3DXVECTOR3(TransferGateMin.x, TransferGateMax.y, TransferGateMin.z), D3DXVECTOR3(TransferGateMax.x, TransferGateMax.y, TransferGateMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(TransferGateMin.x, TransferGateMin.y, TransferGateMin.z), D3DXVECTOR3(TransferGateMax.x, TransferGateMin.y, TransferGateMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //SetLine(D3DXVECTOR3(TransferGateMin.x, TransferGateMax.y, TransferGateMax.z), D3DXVECTOR3(TransferGateMax.x, TransferGateMax.y, TransferGateMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(TransferGateMin.x, TransferGateMin.y, TransferGateMax.z), D3DXVECTOR3(TransferGateMax.x, TransferGateMin.y, TransferGateMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //// ���ʂ̕�
            //SetLine(D3DXVECTOR3(TransferGateMin.x, TransferGateMin.y, TransferGateMin.z), D3DXVECTOR3(TransferGateMin.x, TransferGateMax.y, TransferGateMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(TransferGateMax.x, TransferGateMin.y, TransferGateMin.z), D3DXVECTOR3(TransferGateMax.x, TransferGateMax.y, TransferGateMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //SetLine(D3DXVECTOR3(TransferGateMin.x, TransferGateMin.y, TransferGateMax.z), D3DXVECTOR3(TransferGateMin.x, TransferGateMax.y, TransferGateMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(TransferGateMax.x, TransferGateMin.y, TransferGateMax.z), D3DXVECTOR3(TransferGateMax.x, TransferGateMax.y, TransferGateMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //// ���̑��̕�
            //SetLine(D3DXVECTOR3(TransferGateMin.x, TransferGateMin.y, TransferGateMin.z), D3DXVECTOR3(TransferGateMin.x, TransferGateMin.y, TransferGateMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(TransferGateMax.x, TransferGateMax.y, TransferGateMin.z), D3DXVECTOR3(TransferGateMax.x, TransferGateMax.y, TransferGateMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //SetLine(D3DXVECTOR3(TransferGateMin.x, TransferGateMax.y, TransferGateMin.z), D3DXVECTOR3(TransferGateMin.x, TransferGateMax.y, TransferGateMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(TransferGateMax.x, TransferGateMin.y, TransferGateMin.z), D3DXVECTOR3(TransferGateMax.x, TransferGateMin.y, TransferGateMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
        
#endif






        
        }
    }
}

//=============================
// �]�ږ�`�揈��
//=============================
void DrawTransferGate(void)
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

    D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p(�ꎞ�ޔ�)

    D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

    for (int nCntGate = 0; nCntGate < MAXGATE; nCntGate++)
    {
        if (g_TransferGate[nCntGate].bUse == true)
        {
            if (nCntGate== CLEAR_NUM)
            {
                break;
            }
            if (nCntGate == TRANSGATE_NUM)
            {
                break;
            }

            ////���C�g�𖳌��ɂ���
            //pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

            ////Z�̔�r�ύX
            //pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
            ////Z�o�b�t�@�ɏ������܂Ȃ�
            //pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);



            //���[���h�}�g���b�N�X�̏�����
            D3DXMatrixIdentity(&g_TransferGate[nCntGate].mtxWorld);

            // ���f���̃T�C�Y��ύX
            D3DXMatrixScaling(&g_TransferGate[nCntGate].mtxWorld, g_TransferGate[nCntGate].SizeMag.x, g_TransferGate[nCntGate].SizeMag.y, g_TransferGate[nCntGate].SizeMag.z);

            ////�����𔽉f
            //D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);

            //D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

            //�ʒu�𔽉f
            D3DXMatrixTranslation(&mtxTrans, g_TransferGate[nCntGate].pos.x, g_TransferGate[nCntGate].pos.y, g_TransferGate[nCntGate].pos.z);

            D3DXMatrixMultiply(&g_TransferGate[nCntGate].mtxWorld, &g_TransferGate[nCntGate].mtxWorld, &mtxTrans);

            //���[���h�}�g���b�N�X�̐ݒ�
            pDevice->SetTransform(D3DTS_WORLD, &g_TransferGate[nCntGate].mtxWorld);

            //���݂̃}�e���A�����擾
            pDevice->GetMaterial(&matDef);

            //�}�e���A���f�[�^�ւ̃|�C���^���擾
            pMat = (D3DXMATERIAL*)g_pBuffMatGate[nCntGate]->GetBufferPointer();

            for (int nCntMat = 0; nCntMat < (int)g_dwNumMatGate; nCntMat++)
            {
                //�}�e���A���̐ݒ�
                pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                //�e�N�X�`���̐ݒ�
                pDevice->SetTexture(0, NULL);//����͐ݒ肵�Ȃ�

                //���f��(�p�[�c)�̕`��
                g_pMeshGate[nCntMat]->DrawSubset(nCntMat);

                //�ۑ����Ă��}�e���A����߂�
            //    pDevice->SetMaterial(&matDef);


                // �}�e���A���̐ݒ�
                pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                // �f�B�t���[�Y�J���[��ύX�i��: �Ԃ��F�j
                pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(g_TransferGate[nCntGate].GateColor.r * g_TransferGate[nCntGate].SizeMag.x, g_TransferGate[nCntGate].GateColor.g * g_TransferGate[nCntGate].SizeMag.x, g_TransferGate[nCntGate].GateColor.b * g_TransferGate[nCntGate].SizeMag.x, g_TransferGate[nCntGate].GateColor.a);
          
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
// �]�ږ�擾����
//=============================
TRANSFERGATE* GetTransferGate(void)
{
    return &g_TransferGate[0];
}
//=============================
// �]�ږ�ݒ菈��
//=============================
//-----------------------------�������W-----------------�ŏ�----------------�ő�---------�����̔ԍ�----�]�ڐ�̔ԍ�--�����]�ڂ��ǂ���--�s���{�^���œ]�ڂ��ǂ���
void SetTransferGate(D3DXVECTOR3 Pos, D3DXVECTOR3 GateMin, D3DXVECTOR3 GateMax, int nGateIndex, int nParentIndex, TRANSANGLE ParentTransAngle, D3DXCOLOR GateColor, bool bCompulsionTrans, bool bActionTrans)
{    
    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = GetDevice();//----------------���������ς�

 //   for (int nCntGate = 0; nCntGate < MAXGATE; nCntGate++)
  //  {
        if (g_TransferGate[nGateIndex].bUse == false)
        {
      
            g_TransferGate[nGateIndex].pos = Pos;
            g_TransferGate[nGateIndex].GateMin = GateMin;
            g_TransferGate[nGateIndex].GateMax = GateMax;
            g_TransferGate[nGateIndex].GateColor = GateColor;
            g_TransferGate[nGateIndex].bActiomTrans = bActionTrans;

            //�T�C�Y�ϓ�
             g_TransferGate[nGateIndex].SizeMag.x = g_TransferGate[nGateIndex].GateMax.x / 10.0f;
             g_TransferGate[nGateIndex].SizeMag.y = g_TransferGate[nGateIndex].GateMax.y / 20.0f;
             g_TransferGate[nGateIndex].SizeMag.z = g_TransferGate[nGateIndex].GateMax.z / 10.0f;



            g_TransferGate[nGateIndex].nGateIndex = nGateIndex;//�����̔ԍ�
            g_TransferGate[nGateIndex].nParentIndex = nParentIndex;//�]�ڐ�̔ԍ�
            g_TransferGate[nGateIndex].ParentTransAngle = ParentTransAngle;//�]�ڐ�]�ڕ���
            g_TransferGate[nGateIndex].bCompulsionTrans = bCompulsionTrans;//�����]�ڂ�

            g_TransferGate[nGateIndex].bPossibility = true;//---------------------------------�Ƃ肠����
            g_TransferGate[nGateIndex].bUse = true;


            //�t�@�C���̓ǂݍ���
            D3DXLoadMeshFromX("data\\MODEL\\DebugModel\\BOX.x",
                D3DXMESH_SYSTEMMEM,
                pDevice,
                NULL,
                &g_pBuffMatGate[nGateIndex],
                NULL,
                &g_dwNumMatGate,
                &g_pMeshGate[nGateIndex]);


         //   break;
        }
 //   }
}

