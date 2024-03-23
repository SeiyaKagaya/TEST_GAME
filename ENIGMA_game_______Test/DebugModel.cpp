//=========================================================
//
//DEBUG���f������[DebugModel.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "DebugModel.h"
#include "player.h"
#include "player2.h"
#include "camera.h"
#include "input.h"
#include "text.h"
#include "model.h"
#include "stage.h"
//#include "line.h"
//using namespace __unnamed_enum_0153_1;


//�O���[�o���ϐ��錾
LPD3DXMESH g_pMeshDebugModel[MAXDEBUGMODEL] = {};//���b�V��(���_���)�ւ̃|�C���^

LPD3DXBUFFER g_pBuffMatDebugModel[MAXDEBUGMODEL] = {};//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatDebugModel = 0;//�}�e���A���̐�

DEBUGMODEL g_DebugModel[MAXDEBUGMODEL];


//�����Ă郂�f����
int g_NUM_Model = -1;
int g_NUM_Stage = -1;


//�폜���f���̍��W
D3DXVECTOR3 g_DelModelPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//�Z���N�g�ԍ�
int g_SelectNum = 0;
int g_SelectNumStage = 0;

//=============================
// �f�o�b�O���f������������
//=============================
void InitDebugModel(void)
{    
    g_NUM_Model = -1;
    g_SelectNum = 0;
    g_NUM_Stage = -1;
    g_SelectNumStage = 0;

    //�폜���f���̍��W
    g_DelModelPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    
    // �ϐ��̏�����
    for (int nCntModel = 0; nCntModel < MAXDEBUGMODEL; nCntModel++)
    {
        g_DebugModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_DebugModel[nCntModel].ZoneMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_DebugModel[nCntModel].ZoneMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_DebugModel[nCntModel].nZoneIndex = -1;
        //   g_DebugModel[nCntModel].nParentIndex = -1;
      //  g_DebugModel[nCntModel].ActionType = ACTION_TYPE_MAX;
       // g_DebugModel[nCntModel].bPossibility = false;
        g_DebugModel[nCntModel].bUse = false;
    }



    //-----------------------------���a---------�s���^�C�v-------�F
// �y�A�łQ���ƂɋL��--�F�͒P�F��(�����F�𑼂̂Ɏg�p������)

    //����łP�y�A
    SetDebugModelSphere( 2, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f),false);//�����_1
    SetDebugModelSphere( 2, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f),false);//�����_2


    SetDebugModelSphere( 4,  D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f),false);//�J����1
    SetDebugModelSphere( 4, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f),false);//�J����2

   

    //�l�p
    //--------------------------�ŏ��ő�------------�F
  // SetDebugModelBOX(D3DXVECTOR3(-10.0f, 0.0f, -10.0f), D3DXVECTOR3(10.0f, 1000.0f, 10.0f), D3DXCOLOR(5.0f, 0.0f, 0.0f, 5.0f));
    SetDebugModelSphere(40, D3DXCOLOR(0.0f, 5.0f, 5.0f, 0.5f), true);
     SetDebugModelSphere(50, D3DXCOLOR(0.0f, 5.0f, 5.0f, 0.2f),false);//���{



     SetDebugModelSphere(80, D3DXCOLOR(1.0f, 1.0f, 5.0f, 0.5f), true);
     SetDebugModelSphere(100, D3DXCOLOR(1.0f, 1.0f, 5.0f, 0.2f), false);//���{


    //����łP�y�A
    //SetDebugModel(D3DXVECTOR3(2000.0f, 0.0f, -700.0f), D3DXVECTOR3(-50.0f, 0.0f, -50.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), 0, 1, ACTION_TYPE_MAX);
    //SetDebugModel(D3DXVECTOR3(2000.0f, 0.0f, 700.0f), D3DXVECTOR3(-50.0f, 0.0f, -50.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), 1, 0, ACTION_TYPE_MAX);


   // SetDebugModel(D3DXVECTOR3(200.0f, 100.0f, -300.0f), D3DXVECTOR3(-50.0f, 0.0f, -50.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), 2, 3, ACTION_TYPE_MAX_Z);
   // SetDebugModel(D3DXVECTOR3(200.0f, 50.0f, 300.0f), D3DXVECTOR3(-50.0f, 0.0f, -50.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), 3, 2, TRANS_ANGLE_MIN_Z);

    MAPOBJECT* pMapObject;
    pMapObject = GetMapObject();

    for (int i = 0; i < MAX_MODEL; i++)
    {
        if (pMapObject[i].bUse == true)
        {
            g_NUM_Model++;
        }
    }

    STAGE* pStage;
    pStage = GetStage();

    for (int nWall = 0; nWall < NUMSTAGE; nWall++)
    {
        if (pStage[nWall].bUse == true)
        {
            g_NUM_Stage++;
        }
    }
}

//=============================
// �f�o�b�O���f���I������
//=============================
void UninitDebugModel(void)
{
    for (int nCntModel = 0; nCntModel < MAXDEBUGMODEL; nCntModel++)
    {
        //���b�V���̔j��
        if (g_pMeshDebugModel[nCntModel] != NULL)
        {
            g_pMeshDebugModel[nCntModel]->Release();
            g_pMeshDebugModel[nCntModel] = NULL;
        }
        //�}�e���A���̔j��
        if (g_pBuffMatDebugModel[nCntModel] != NULL)
        {
            g_pBuffMatDebugModel[nCntModel]->Release();
            g_pBuffMatDebugModel[nCntModel] = NULL;
        }
    }
}

//=============================
// �f�o�b�O���f���X�V����
//=============================
void UpdateDebugModel(void)
{
    Camera* pCamera;
    pCamera = GetCamera();

    View* pViewMtx = GetView();

    View2* pViewMtx2 = GetView_2P();

    MAPOBJECT* pMapObject;
    pMapObject = GetMapObject();

    STAGE* pStage;
    pStage = GetStage();

    if (GetkeyboardTrigger(DIK_2) == true)
    {//2�������ꂽ
        g_SelectNum++;
        if (g_SelectNum > g_NUM_Model)
        {
            g_SelectNum = 0;
        }
    }
    else if (GetkeyboardTrigger(DIK_1) == true)
    {//1�������ꂽ
        g_SelectNum--;
        if (g_SelectNum < 0)
        {
            g_SelectNum = g_NUM_Model;
        }
    }
    else if (GetkeyboardTrigger(DIK_DELETE) == true)
    {//Delete�������ꂽ
        pMapObject[g_SelectNum].bUse = false;
        g_NUM_Model--;
    }


    if (GetkeyboardTrigger(DIK_4) == true)
    {//2�������ꂽ
        g_SelectNumStage++;
        if (g_SelectNumStage > g_NUM_Stage)
        {
            g_SelectNumStage = 0;
        }
    }
    else if (GetkeyboardTrigger(DIK_3) == true)
    {//1�������ꂽ
        g_SelectNumStage--;
        if (g_SelectNumStage < 0)
        {
            g_SelectNumStage = g_NUM_Stage;
        }
    }








    for (int nCntModel = 0; nCntModel < MAXDEBUGMODEL; nCntModel++)
    {
        if (g_DebugModel[nCntModel].bUse == true)
        {
            if (nCntModel == 0)
            {//�����_1
                g_DebugModel[nCntModel].pos = D3DXVECTOR3(pViewMtx[1].ViewPosMtx._41, pViewMtx[1].ViewPosMtx._42, pViewMtx[1].ViewPosMtx._43);
            }
            else if(nCntModel == 1)
            {//�����_2
                g_DebugModel[nCntModel].pos = D3DXVECTOR3(pViewMtx2[1].ViewPosMtx._41, pViewMtx2[1].ViewPosMtx._42, pViewMtx2[1].ViewPosMtx._43);
            }
            else if (nCntModel == 2)
            {//�J����1
                g_DebugModel[nCntModel].pos = pCamera[0].posV;
            }
            else if (nCntModel == 3)
            {//�J����2
                g_DebugModel[nCntModel].pos = pCamera[1].posV;
            }

            else if (nCntModel == 4)
            {//�폜�s��

                if (pMapObject[g_SelectNum].bUse == true)
                {
                    g_DebugModel[nCntModel].pos = pMapObject[g_SelectNum].pos;
                }
            }

            else if (nCntModel == 5)
            {//�폜�s��

                if (pMapObject[g_SelectNum].bUse == true)
                {
                    g_DebugModel[nCntModel].pos = pMapObject[g_SelectNum].pos;
                }
            }


            else if (nCntModel == 5)
            {//�폜�s��

                if (pStage[g_SelectNumStage].bUse == true)
                {
                    g_DebugModel[nCntModel].pos = pStage[g_SelectNumStage].posStage;
                    if (pStage[g_SelectNumStage].bCollision==false)
                    {
                        g_DebugModel[nCntModel].ZoneColor = D3DXCOLOR(5.0f, 1.0f, 5.0f, 0.5f);
                    }
                    else
                    {
                        g_DebugModel[nCntModel].ZoneColor = D3DXCOLOR(1.0f, 1.0f, 5.0f, 0.5f);
                    }
                }
            }

            else if (nCntModel == 6)
            {//�폜�s��

                if (pStage[g_SelectNumStage].bUse == true)
                {
                    g_DebugModel[nCntModel].pos = pStage[g_SelectNumStage].posStage;
                }

                if (pStage[g_SelectNumStage].bCollision == false)
                {
                    g_DebugModel[nCntModel].ZoneColor = D3DXCOLOR(5.0f, 1.0f, 5.0f, 0.5f);
                }
                else
                {
                    g_DebugModel[nCntModel].ZoneColor = D3DXCOLOR(1.0f, 1.0f, 5.0f, 0.5f);
                }
            }

          







        //    D3DXVECTOR3 DebugModelMin = g_DebugModel[nCntModel].pos + g_DebugModel[nCntModel].ZoneMin;
        //    D3DXVECTOR3 DebugModelMax = g_DebugModel[nCntModel].pos + g_DebugModel[nCntModel].ZoneMax;

        //    //���C���̈ʒu
        //    // �㉺�̕�
        //    SetLine(D3DXVECTOR3(DebugModelMin.x, DebugModelMax.y, DebugModelMin.z), D3DXVECTOR3(DebugModelMax.x, DebugModelMax.y, DebugModelMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
        //    SetLine(D3DXVECTOR3(DebugModelMin.x, DebugModelMin.y, DebugModelMin.z), D3DXVECTOR3(DebugModelMax.x, DebugModelMin.y, DebugModelMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

        //    SetLine(D3DXVECTOR3(DebugModelMin.x, DebugModelMax.y, DebugModelMax.z), D3DXVECTOR3(DebugModelMax.x, DebugModelMax.y, DebugModelMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
        //    SetLine(D3DXVECTOR3(DebugModelMin.x, DebugModelMin.y, DebugModelMax.z), D3DXVECTOR3(DebugModelMax.x, DebugModelMin.y, DebugModelMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

        //    // ���ʂ̕�
        //    SetLine(D3DXVECTOR3(DebugModelMin.x, DebugModelMin.y, DebugModelMin.z), D3DXVECTOR3(DebugModelMin.x, DebugModelMax.y, DebugModelMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
        //    SetLine(D3DXVECTOR3(DebugModelMax.x, DebugModelMin.y, DebugModelMin.z), D3DXVECTOR3(DebugModelMax.x, DebugModelMax.y, DebugModelMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

        //    SetLine(D3DXVECTOR3(DebugModelMin.x, DebugModelMin.y, DebugModelMax.z), D3DXVECTOR3(DebugModelMin.x, DebugModelMax.y, DebugModelMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
        //    SetLine(D3DXVECTOR3(DebugModelMax.x, DebugModelMin.y, DebugModelMax.z), D3DXVECTOR3(DebugModelMax.x, DebugModelMax.y, DebugModelMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

        //    // ���̑��̕�
        //    SetLine(D3DXVECTOR3(DebugModelMin.x, DebugModelMin.y, DebugModelMin.z), D3DXVECTOR3(DebugModelMin.x, DebugModelMin.y, DebugModelMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
        //    SetLine(D3DXVECTOR3(DebugModelMax.x, DebugModelMax.y, DebugModelMin.z), D3DXVECTOR3(DebugModelMax.x, DebugModelMax.y, DebugModelMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

        //    SetLine(D3DXVECTOR3(DebugModelMin.x, DebugModelMax.y, DebugModelMin.z), D3DXVECTOR3(DebugModelMin.x, DebugModelMax.y, DebugModelMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
        //    SetLine(D3DXVECTOR3(DebugModelMax.x, DebugModelMin.y, DebugModelMin.z), D3DXVECTOR3(DebugModelMax.x, DebugModelMin.y, DebugModelMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));









        }
    }
}

//=============================
// �f�o�b�O���f���`�揈��
//=============================
void DrawDebugModel(void)
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

    D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p(�ꎞ�ޔ�)

    D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

    for (int nCntModel = 0; nCntModel < MAXDEBUGMODEL; nCntModel++)
    {
        if (g_DebugModel[nCntModel].bUse == true)
        {


            //���[���h�}�g���b�N�X�̏�����
            D3DXMatrixIdentity(&g_DebugModel[nCntModel].mtxWorld);

            // ���f���̃T�C�Y��ύX
            D3DXMatrixScaling(&g_DebugModel[nCntModel].mtxWorld, g_DebugModel[nCntModel].SizeMag.x, g_DebugModel[nCntModel].SizeMag.y, g_DebugModel[nCntModel].SizeMag.z);

            ////�����𔽉f
            //D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);

            //D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

            //�ʒu�𔽉f
            D3DXMatrixTranslation(&mtxTrans, g_DebugModel[nCntModel].pos.x, g_DebugModel[nCntModel].pos.y, g_DebugModel[nCntModel].pos.z);

            D3DXMatrixMultiply(&g_DebugModel[nCntModel].mtxWorld, &g_DebugModel[nCntModel].mtxWorld, &mtxTrans);

            //���[���h�}�g���b�N�X�̐ݒ�
            pDevice->SetTransform(D3DTS_WORLD, &g_DebugModel[nCntModel].mtxWorld);

            //���݂̃}�e���A�����擾
            pDevice->GetMaterial(&matDef);

            //�}�e���A���f�[�^�ւ̃|�C���^���擾
            pMat = (D3DXMATERIAL*)g_pBuffMatDebugModel[nCntModel]->GetBufferPointer();

            for (int nCntMat = 0; nCntMat < (int)g_dwNumMatDebugModel; nCntMat++)
            {
                //�}�e���A���̐ݒ�
             //   pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                //�e�N�X�`���̐ݒ�
                pDevice->SetTexture(0, NULL);//����͐ݒ肵�Ȃ�

                //���f��(�p�[�c)�̕`��
                g_pMeshDebugModel[nCntMat]->DrawSubset(nCntMat);

                //�ۑ����Ă��}�e���A����߂�
            //    pDevice->SetMaterial(&matDef);


                // �}�e���A���̐ݒ�
                pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                // �f�B�t���[�Y�J���[��ύX�i��: �Ԃ��F�j
                pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(g_DebugModel[nCntModel].ZoneColor.r * g_DebugModel[nCntModel].SizeMag.x, g_DebugModel[nCntModel].ZoneColor.g * g_DebugModel[nCntModel].SizeMag.x, g_DebugModel[nCntModel].ZoneColor.b * g_DebugModel[nCntModel].SizeMag.x, g_DebugModel[nCntModel].ZoneColor.a);




            }

           

            //�e�N�X�`����߂�
            pDevice->SetTexture(0, NULL);
        }
    }



 //�ۑ����Ă��}�e���A����߂�
            pDevice->SetMaterial(&matDef);
}


//=============================
//�ݒu�p�R�����g
//=============================
void DrawDebugDelComment(void)
{
#if _DEBUG
    DrawTextSet(D3DXVECTOR3(550.0f, 570.0f, 0.0f), 20, FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "1,2�Ń��f���؂�ւ��A\nDelete�Ń��f���폜" );
    DrawTextSet(D3DXVECTOR3(550.0f, 600.0f, 0.0f), 20, FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "���f��%d/%d", g_SelectNum, g_NUM_Model);

    DrawTextSet(D3DXVECTOR3(550.0f, 430.0f, 0.0f), 20, FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 0.5f, 1.0f, 1.0f), "1,2�ŕǏ��؂�ւ�");
    DrawTextSet(D3DXVECTOR3(550.0f, 460.0f, 0.0f), 20, FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 0.5f, 1.0f, 1.0f), "�Ǐ�%d/%d", g_SelectNumStage, g_NUM_Stage);
#endif
}


//=============================
// �f�o�b�O���f���ݒ菈��
//=============================
//----------------------------���a---------�s���^�C�v-------�F
void SetDebugModelSphere(float Radius,D3DXCOLOR ZoneColor,bool Beacon)
{
    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = GetDevice();//----------------���������ς�

    for (int nCntModel = 0; nCntModel < MAXDEBUGMODEL; nCntModel++)
    {
        if (g_DebugModel[nCntModel].bUse == false)
        {
           // g_DebugModel[nCntModel].pos = Pos;
            g_DebugModel[nCntModel].Radius = Radius;

            g_DebugModel[nCntModel].ZoneMin = D3DXVECTOR3(-Radius, -Radius, -Radius);
            g_DebugModel[nCntModel].ZoneMax = D3DXVECTOR3(Radius, Radius, Radius);
            g_DebugModel[nCntModel].ZoneColor = ZoneColor;
            g_DebugModel[nCntModel].EscapeZoneColor = ZoneColor;

            if (Beacon == false)
            {
                //�T�C�Y�ϓ�
                g_DebugModel[nCntModel].SizeMag.x = g_DebugModel[nCntModel].ZoneMax.x / 10.0f;
                g_DebugModel[nCntModel].SizeMag.y = g_DebugModel[nCntModel].ZoneMax.y / 10.0f;
                g_DebugModel[nCntModel].SizeMag.z = g_DebugModel[nCntModel].ZoneMax.z / 10.0f;
            }
            else
            {
                //�T�C�Y�ϓ�
                g_DebugModel[nCntModel].SizeMag.x = g_DebugModel[nCntModel].ZoneMax.x / 20.0f;
                g_DebugModel[nCntModel].SizeMag.y = g_DebugModel[nCntModel].ZoneMax.y*20.0f;
                g_DebugModel[nCntModel].SizeMag.z = g_DebugModel[nCntModel].ZoneMax.z / 20.0f;
            }



        //    g_DebugModel[nCntModel].ActionType = ActionType;//�]�ڐ�]�ڕ���
        //   g_DebugModel[nCntModel].bPossibility = true;
            g_DebugModel[nCntModel].bUse = true;


            //�t�@�C���̓ǂݍ���
            D3DXLoadMeshFromX("data\\MODEL\\DebugModel\\SPHERE.x",
                D3DXMESH_SYSTEMMEM,
                pDevice,
                NULL,
                &g_pBuffMatDebugModel[nCntModel],
                NULL,
                &g_dwNumMatDebugModel,
                &g_pMeshDebugModel[nCntModel]);


            break;
        }
    }
}

//=============================
//��胂�f�����폜���鏈��
//=============================
void DeleteCoveredModel(void)
{
    MAPOBJECT* pMapObject;
    pMapObject = GetMapObject();

    for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
    {
        if (pMapObject[nCntModel].bUse == true)
        {
            for (int nCnt2 = 0; nCnt2 < MAX_MODEL; nCnt2++)
            {
                if (nCnt2 != nCntModel)
                {//�������g����Ȃ��Ƃ�
                    
                    if (pMapObject[nCnt2].bUse == true)
                    {
                        if (pMapObject[nCntModel].nType == pMapObject[nCnt2].nType && pMapObject[nCntModel].pos == pMapObject[nCnt2].pos && pMapObject[nCntModel].Maxpos == pMapObject[nCnt2].Maxpos)
                        {//3�������Ƃ�(�^�C�v��pos��MaxPos)
                            pMapObject[nCnt2].bUse = false;
                            g_NUM_Model--;
                        }
                    }
                }
            }
        }
    }
}

////=============================
////�l�p
////=============================
//////-----------------------------------�ŏ��ő�------------�F
//void SetDebugModelBOX(D3DXVECTOR3 Min, D3DXVECTOR3 Max, D3DXCOLOR ZoneColor)
//{
//    //�f�o�C�X�̎擾
//    LPDIRECT3DDEVICE9 pDevice = GetDevice();//----------------���������ς�
//
//    for (int nCntModel = 0; nCntModel < MAXDEBUGMODEL; nCntModel++)
//    {
//        if (g_DebugModel[nCntModel].bUse == false)
//        {
//            // g_DebugModel[nCntModel].pos = Pos;
//         //   g_DebugModel[nCntModel].Radius = Radius;
//
//            g_DebugModel[nCntModel].ZoneMin = Min;
//            g_DebugModel[nCntModel].ZoneMax = Max;
//            g_DebugModel[nCntModel].ZoneColor = ZoneColor;
//            g_DebugModel[nCntModel].EscapeZoneColor = ZoneColor;
//
//            //�T�C�Y�ϓ�
//            g_DebugModel[nCntModel].SizeMag.x = g_DebugModel[nCntModel].ZoneMax.x;
//            g_DebugModel[nCntModel].SizeMag.y = g_DebugModel[nCntModel].ZoneMax.y;
//            g_DebugModel[nCntModel].SizeMag.z = g_DebugModel[nCntModel].ZoneMax.z;
//
//
//            //    g_DebugModel[nCntModel].ActionType = ActionType;//�]�ڐ�]�ڕ���
//            //   g_DebugModel[nCntModel].bPossibility = true;
//            g_DebugModel[nCntModel].bUse = true;
//
//
//            //�t�@�C���̓ǂݍ���
//            D3DXLoadMeshFromX("data\\MODEL\\DebugModel\\BOX.x",
//                D3DXMESH_SYSTEMMEM,
//                pDevice,
//                NULL,
//                &g_pBuffMatDebugModel[nCntModel],
//                NULL,
//                &g_dwNumMatDebugModel,
//                &g_pMeshDebugModel[nCntModel]);
//
//
//            break;
//        }
//    }
//}
