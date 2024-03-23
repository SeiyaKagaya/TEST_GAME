//=========================================================
//
//���C����\�����鏈��[line.cpp]
// Author seiya kagaya
//
//=========================================================
#include "line.h"

// �O���[�o���ϐ�
Line g_aLine[MAX_LINE];
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLine = NULL;
D3DXMATRIX g_mtxWorldLine;  // ���[���h�}�g���b�N�X
bool g_bLineDisplay;                    // ���C����\�����邩



//=============================
// ���C���̏���������
//=============================
void InitLine(void)
{


    LPDIRECT3DDEVICE9 pDevice = GetDevice();    // �f�o�C�X���擾

    // �ϐ��̏�����
    for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
    {
        g_aLine[nCntLine].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_aLine[nCntLine].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_aLine[nCntLine].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
        g_aLine[nCntLine].Life = 0;
        g_aLine[nCntLine].bUse = false;
    }

    // ���_�o�b�t�@�̐���
    pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * MAX_LINE, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffLine, NULL);

    VERTEX_3D* pVtx;

    // ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
    g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

    for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
    {
        // ���_���W�̐ݒ�
        pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

        // �@���x�N�g���̐ݒ�
        pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
        pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

        // ���_�J���[
        pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
        pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

        // �e�N�X�`�����W�̐ݒ�
        pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
        pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);

        pVtx += 2;
    }

    // ���_�o�b�t�@���A�����b�N����
    g_pVtxBuffLine->Unlock();
}

//=============================
// ���C���̏I������
//=============================
void UninitLine(void)
{
    // ���_�o�b�t�@�̔j��
    if (g_pVtxBuffLine != NULL)
    {
        g_pVtxBuffLine->Release();
        g_pVtxBuffLine = NULL;
    }
}

//=============================
// ���C���̍X�V����
//=============================
void UpdateLine(void)
{
    for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
    {
        if (g_aLine[nCntLine].bUse == true)
        {
            g_aLine[nCntLine].Life--;

            if (g_aLine[nCntLine].Life<=0)
            {
                g_aLine[nCntLine].bUse = false;

            }
        }
    }
}

//=============================
// ���C���̕`�揈��
//=============================
void DrawLine(void)
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();        // �f�o�C�X���擾
    D3DXMATRIX mtxRot, mtxTrans;                            // �v�Z�p�}�g���b�N�X

    if (!g_bLineDisplay)
    {
    //    return;
    }

    for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
    {
        if (g_aLine[nCntLine].bUse == true)
        {
            // ���[���h�}�g���b�N�X�̏�����
            D3DXMatrixIdentity(&g_mtxWorldLine);

            // �����𔽉f
            D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aLine[nCntLine].rot.y, g_aLine[nCntLine].rot.x, g_aLine[nCntLine].rot.z);

            D3DXMatrixMultiply(&g_mtxWorldLine, &g_mtxWorldLine, &mtxRot);

            // �ʒu�𔽉f
            D3DXMatrixTranslation(&mtxTrans, g_aLine[nCntLine].pos.x, g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z);

            D3DXMatrixMultiply(&g_mtxWorldLine, &g_mtxWorldLine, &mtxTrans);

            // ���[���h�}�g���b�N�X�̐ݒ�
            pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldLine);

            // ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
            pDevice->SetStreamSource(0, g_pVtxBuffLine, 0, sizeof(VERTEX_3D));

            // ���_�t�H�[�}�b�g�̐ݒ�
            pDevice->SetFVF(FVF_VERTEX_3D);

            // �e�N�X�`���̐ݒ�
            pDevice->SetTexture(0, NULL);

            // �|���S���̕`��
            pDevice->DrawPrimitive(D3DPT_LINELIST, //�v���~�e�B�u�̎��
                nCntLine * 2, //�`�悷��ŏ��̒��_�C���f�b�N�X
                1);             //�`�悷��v���~�e�B�u��

            //[nCntLine].bUse = false;

                 
            //�e�N�X�`����߂�
            pDevice->SetTexture(0, NULL);
        }
    }
}


//=============================
// ���C���̐ݒ菈��
//=============================
void SetLine(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR col)
{
    VERTEX_3D* pVtx;

    // ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
    g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

    for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
    {
        if (g_aLine[nCntLine].bUse == false)
        {
            g_aLine[nCntLine].pos = D3DXVECTOR3((start.x + end.x) * 0.5f, (start.y + end.y) * 0.5f, (start.z + end.z) * 0.5f);
            g_aLine[nCntLine].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
            g_aLine[nCntLine].startPos = start;
            g_aLine[nCntLine].endPos = end;
            g_aLine[nCntLine].col = col;
            g_aLine[nCntLine].Life = 2;

            // ���_���W�̐ݒ�
            pVtx[0].pos = D3DXVECTOR3(-fabsf(end.x - start.x) * 0.5f, -fabsf(end.y - start.y) * 0.5f, -fabsf(end.z - start.z) * 0.5f);
            pVtx[1].pos = D3DXVECTOR3(fabsf(end.x - start.x) * 0.5f, fabsf(end.y - start.y) * 0.5f, fabsf(end.z - start.z) * 0.5f);

            pVtx[0].col = col;
            pVtx[1].col = col;

            g_aLine[nCntLine].bUse = true;

            break;
        }

        pVtx += 2;
    }

    // ���_�o�b�t�@���A�����b�N����
    g_pVtxBuffLine->Unlock();
}
//
////=============================
//// ���C���̕\���ݒ�擾����
////=============================
//bool* GetLineDisplay(void)
//{
//    return &g_bLineDisplay;
//}