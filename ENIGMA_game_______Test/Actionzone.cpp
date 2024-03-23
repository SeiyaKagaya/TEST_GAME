//=========================================================
//
//�G���A�ɂ���čs�������鏈��[Actionzone.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "Actionzone.h"
//#include "player.h"
//#include "player2.h"
#include "line.h"
//using namespace __unnamed_enum_0153_1;


//�O���[�o���ϐ��錾
LPD3DXMESH g_pMeshZone[MAXZONE] = {};//���b�V��(���_���)�ւ̃|�C���^

LPD3DXBUFFER g_pBuffMatZone[MAXZONE] = {};//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatZone = 0;//�}�e���A���̐�

ACTIONZONE g_ActionZone[MAXZONE];

//=============================
// �A�N�V�����G���A����������
//=============================
void InitActionZone(void)
{    // �ϐ��̏�����
    for (int nCntZone = 0; nCntZone < MAXZONE; nCntZone++)
    {
        g_ActionZone[nCntZone].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_ActionZone[nCntZone].ZoneMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_ActionZone[nCntZone].ZoneMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_ActionZone[nCntZone].nZoneIndex = -1;
     //   g_ActionZone[nCntZone].nParentIndex = -1;
        g_ActionZone[nCntZone].ActionType = ACTION_TYPE_MAX;
        g_ActionZone[nCntZone].bPossibility = false;
        g_ActionZone[nCntZone].bUse = false;
        g_ActionZone[nCntZone].bDrawOk = false;
    }



    //-----------------------------�������W-----------���a---------�s���^�C�v-------�F
// �y�A�łQ���ƂɋL��--�F�͒P�F��(�����F�𑼂̂Ɏg�p������)

    ////����łP�y�A
    //SetActionZone(D3DXVECTOR3(1000.0f, 0.0f, -500.0f), 200, ACTION_TYPE_MAX, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.7f));
    //SetActionZone(D3DXVECTOR3(1000.0f, 0.0f, 500.0f), 200, ACTION_TYPE_MAX, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.7f));


    //SetActionZone(D3DXVECTOR3(500.0f, 300.0f, -300.0f), 300, ACTION_TYPE_MAX, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.7f));
    //SetActionZone(D3DXVECTOR3(500.0f, 300.0f, 300.0f), 300, ACTION_TYPE_MAX, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.7f));




    //    //����łP�y�A
    //SetActionZone(D3DXVECTOR3(2000.0f, 0.0f, -700.0f), D3DXVECTOR3(-50.0f, 0.0f, -50.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), 0, 1, ACTION_TYPE_MAX);
    //SetActionZone(D3DXVECTOR3(2000.0f, 0.0f, 700.0f), D3DXVECTOR3(-50.0f, 0.0f, -50.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), 1, 0, ACTION_TYPE_MAX);


    //SetActionZone(D3DXVECTOR3(200.0f, 100.0f, -300.0f), D3DXVECTOR3(-50.0f, 0.0f, -50.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), 2, 3, ACTION_TYPE_MAX_Z);
    //SetActionZone(D3DXVECTOR3(200.0f, 50.0f, 300.0f), D3DXVECTOR3(-50.0f, 0.0f, -50.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), 3, 2, TRANS_ANGLE_MIN_Z);


}

//=============================
// �A�N�V�����G���A�I������
//=============================
void UninitActionZone(void)
{
    for (int nCntZone = 0; nCntZone < MAXZONE; nCntZone++)
    {
        //���b�V���̔j��
        if (g_pMeshZone[nCntZone] != NULL)
        {
            g_pMeshZone[nCntZone]->Release();
            g_pMeshZone[nCntZone] = NULL;
        }
        //�}�e���A���̔j��
        if (g_pBuffMatZone[nCntZone] != NULL)
        {
            g_pBuffMatZone[nCntZone]->Release();
            g_pBuffMatZone[nCntZone] = NULL;
        }
    }
}

//=============================
// �A�N�V�����G���A�X�V����
//=============================
void UpdateActionZone(void)
{
    for (int nCntZone = 0; nCntZone < MAXZONE; nCntZone++)
    {
        if (g_ActionZone[nCntZone].bUse == true)
        {
            D3DXVECTOR3 ActionZoneMin = g_ActionZone[nCntZone].pos + g_ActionZone[nCntZone].ZoneMin;
            D3DXVECTOR3 ActionZoneMax = g_ActionZone[nCntZone].pos + g_ActionZone[nCntZone].ZoneMax;

#if _DEBUG
            ////���C���̈ʒu
            //// �㉺�̕�
            //SetLine(D3DXVECTOR3(ActionZoneMin.x, ActionZoneMax.y, ActionZoneMin.z), D3DXVECTOR3(ActionZoneMax.x, ActionZoneMax.y, ActionZoneMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(ActionZoneMin.x, ActionZoneMin.y, ActionZoneMin.z), D3DXVECTOR3(ActionZoneMax.x, ActionZoneMin.y, ActionZoneMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //SetLine(D3DXVECTOR3(ActionZoneMin.x, ActionZoneMax.y, ActionZoneMax.z), D3DXVECTOR3(ActionZoneMax.x, ActionZoneMax.y, ActionZoneMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(ActionZoneMin.x, ActionZoneMin.y, ActionZoneMax.z), D3DXVECTOR3(ActionZoneMax.x, ActionZoneMin.y, ActionZoneMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //// ���ʂ̕�
            //SetLine(D3DXVECTOR3(ActionZoneMin.x, ActionZoneMin.y, ActionZoneMin.z), D3DXVECTOR3(ActionZoneMin.x, ActionZoneMax.y, ActionZoneMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(ActionZoneMax.x, ActionZoneMin.y, ActionZoneMin.z), D3DXVECTOR3(ActionZoneMax.x, ActionZoneMax.y, ActionZoneMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //SetLine(D3DXVECTOR3(ActionZoneMin.x, ActionZoneMin.y, ActionZoneMax.z), D3DXVECTOR3(ActionZoneMin.x, ActionZoneMax.y, ActionZoneMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(ActionZoneMax.x, ActionZoneMin.y, ActionZoneMax.z), D3DXVECTOR3(ActionZoneMax.x, ActionZoneMax.y, ActionZoneMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //// ���̑��̕�
            //SetLine(D3DXVECTOR3(ActionZoneMin.x, ActionZoneMin.y, ActionZoneMin.z), D3DXVECTOR3(ActionZoneMin.x, ActionZoneMin.y, ActionZoneMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(ActionZoneMax.x, ActionZoneMax.y, ActionZoneMin.z), D3DXVECTOR3(ActionZoneMax.x, ActionZoneMax.y, ActionZoneMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //SetLine(D3DXVECTOR3(ActionZoneMin.x, ActionZoneMax.y, ActionZoneMin.z), D3DXVECTOR3(ActionZoneMin.x, ActionZoneMax.y, ActionZoneMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(ActionZoneMax.x, ActionZoneMin.y, ActionZoneMin.z), D3DXVECTOR3(ActionZoneMax.x, ActionZoneMin.y, ActionZoneMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

#endif







        }
    }
}

//=============================
// �A�N�V�����G���A�`�揈��
//=============================
void DrawActionZone(void)
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

    D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p(�ꎞ�ޔ�)

    D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

    for (int nCntZone = 0; nCntZone < MAXZONE; nCntZone++)
    {
        if (g_ActionZone[nCntZone].bUse == true)
        {
            if (g_ActionZone[nCntZone].bDrawOk == true)
            {
                //���[���h�}�g���b�N�X�̏�����
                D3DXMatrixIdentity(&g_ActionZone[nCntZone].mtxWorld);

                 //���f���̃T�C�Y��ύX
                D3DXMatrixScaling(&g_ActionZone[nCntZone].mtxWorld, g_ActionZone[nCntZone].SizeMag.x, g_ActionZone[nCntZone].SizeMag.y, g_ActionZone[nCntZone].SizeMag.z);

                ////�����𔽉f
                //D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);

                //D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

                //�ʒu�𔽉f
                D3DXMatrixTranslation(&mtxTrans, g_ActionZone[nCntZone].pos.x, g_ActionZone[nCntZone].pos.y, g_ActionZone[nCntZone].pos.z);

                D3DXMatrixMultiply(&g_ActionZone[nCntZone].mtxWorld, &g_ActionZone[nCntZone].mtxWorld, &mtxTrans);

                //���[���h�}�g���b�N�X�̐ݒ�
                pDevice->SetTransform(D3DTS_WORLD, &g_ActionZone[nCntZone].mtxWorld);

                //���݂̃}�e���A�����擾
                pDevice->GetMaterial(&matDef);

                //�}�e���A���f�[�^�ւ̃|�C���^���擾
                pMat = (D3DXMATERIAL*)g_pBuffMatZone[nCntZone]->GetBufferPointer();

                for (int nCntMat = 0; nCntMat < (int)g_dwNumMatZone; nCntMat++)
                {
                    //�}�e���A���̐ݒ�
                 //   pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                    //�e�N�X�`���̐ݒ�
                    pDevice->SetTexture(0, NULL);//����͐ݒ肵�Ȃ�

                  

                    //�ۑ����Ă��}�e���A����߂�
                  //  pDevice->SetMaterial(&matDef);


                    // �}�e���A���̐ݒ�
                    pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                    // �f�B�t���[�Y�J���[��ύX�i��: �Ԃ��F�j
                    pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(g_ActionZone[nCntZone].ZoneColor.r * g_ActionZone[nCntZone].SizeMag.x, g_ActionZone[nCntZone].ZoneColor.g * g_ActionZone[nCntZone].SizeMag.x, g_ActionZone[nCntZone].ZoneColor.b * g_ActionZone[nCntZone].SizeMag.x, g_ActionZone[nCntZone].ZoneColor.a);

                    //���f��(�p�[�c)�̕`��
                    g_pMeshZone[nCntMat]->DrawSubset(nCntMat);
                
                }
                //�ۑ����Ă��}�e���A����߂�
                pDevice->SetMaterial(&matDef);

                //�e�N�X�`����߂�
                pDevice->SetTexture(0, NULL);

            }
        }
    }

}
//=============================
// �A�N�V�����G���A�擾����
//=============================
ACTIONZONE* GetActionZone(void)
{
    return &g_ActionZone[0];
}
//=============================
// �A�N�V�����G���A�ݒ菈��
//=============================
//-----------------------------�������W-----------���a---------�s���^�C�v-------�F
void SetActionZone(D3DXVECTOR3 Pos, float Radius, ACTIONTYPE ActionType, D3DXCOLOR ZoneColor)
{
    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = GetDevice();//----------------���������ς�

    for (int nCntZone = 0; nCntZone < MAXZONE; nCntZone++)
    {
        if (ActionType == ACTION_TYPE_GAMECLEAR)
        {//���ꂾ��������
            nCntZone = MAXZONE-2;
        }

        if (g_ActionZone[nCntZone].bUse == false)
        {
            g_ActionZone[nCntZone].pos = Pos;
            g_ActionZone[nCntZone].Radius = Radius;

            g_ActionZone[nCntZone].ZoneMin = D3DXVECTOR3(-Radius, -Radius, -Radius);
            g_ActionZone[nCntZone].ZoneMax = D3DXVECTOR3(Radius, Radius, Radius);
            g_ActionZone[nCntZone].ZoneColor = ZoneColor;
            g_ActionZone[nCntZone].EscapeZoneColor = ZoneColor;

            //�T�C�Y�ϓ�
            g_ActionZone[nCntZone].SizeMag.x = g_ActionZone[nCntZone].ZoneMax.x / 10.0f;
            g_ActionZone[nCntZone].SizeMag.y = g_ActionZone[nCntZone].ZoneMax.y / 10.0f;
            g_ActionZone[nCntZone].SizeMag.z = g_ActionZone[nCntZone].ZoneMax.z / 10.0f;


            g_ActionZone[nCntZone].ActionType = ActionType;//�]�ڐ�]�ڕ���
            g_ActionZone[nCntZone].bPossibility = true;
            g_ActionZone[nCntZone].bUse = true;
            g_ActionZone[nCntZone].bDrawOk = true;

            //�t�@�C���̓ǂݍ���
            D3DXLoadMeshFromX("data\\MODEL\\DebugModel\\SPHERE.x",
                D3DXMESH_SYSTEMMEM,
                pDevice,
                NULL,
                &g_pBuffMatZone[nCntZone],
                NULL,
                &g_dwNumMatZone,
                &g_pMeshZone[nCntZone]);


            break;
        }
    }
}
