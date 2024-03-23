//=========================================================
//
//ラインを表示する処理[line.cpp]
// Author seiya kagaya
//
//=========================================================
#include "line.h"

// グローバル変数
Line g_aLine[MAX_LINE];
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLine = NULL;
D3DXMATRIX g_mtxWorldLine;  // ワールドマトリックス
bool g_bLineDisplay;                    // ラインを表示するか



//=============================
// ラインの初期化処理
//=============================
void InitLine(void)
{


    LPDIRECT3DDEVICE9 pDevice = GetDevice();    // デバイスを取得

    // 変数の初期化
    for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
    {
        g_aLine[nCntLine].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_aLine[nCntLine].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_aLine[nCntLine].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
        g_aLine[nCntLine].Life = 0;
        g_aLine[nCntLine].bUse = false;
    }

    // 頂点バッファの生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * MAX_LINE, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffLine, NULL);

    VERTEX_3D* pVtx;

    // 頂点バッファをロックし、頂点情報へのポインタを取得
    g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

    for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
    {
        // 頂点座標の設定
        pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

        // 法線ベクトルの設定
        pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
        pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

        // 頂点カラー
        pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
        pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

        // テクスチャ座標の設定
        pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
        pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);

        pVtx += 2;
    }

    // 頂点バッファをアンロックする
    g_pVtxBuffLine->Unlock();
}

//=============================
// ラインの終了処理
//=============================
void UninitLine(void)
{
    // 頂点バッファの破棄
    if (g_pVtxBuffLine != NULL)
    {
        g_pVtxBuffLine->Release();
        g_pVtxBuffLine = NULL;
    }
}

//=============================
// ラインの更新処理
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
// ラインの描画処理
//=============================
void DrawLine(void)
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();        // デバイスを取得
    D3DXMATRIX mtxRot, mtxTrans;                            // 計算用マトリックス

    if (!g_bLineDisplay)
    {
    //    return;
    }

    for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
    {
        if (g_aLine[nCntLine].bUse == true)
        {
            // ワールドマトリックスの初期化
            D3DXMatrixIdentity(&g_mtxWorldLine);

            // 向きを反映
            D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aLine[nCntLine].rot.y, g_aLine[nCntLine].rot.x, g_aLine[nCntLine].rot.z);

            D3DXMatrixMultiply(&g_mtxWorldLine, &g_mtxWorldLine, &mtxRot);

            // 位置を反映
            D3DXMatrixTranslation(&mtxTrans, g_aLine[nCntLine].pos.x, g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z);

            D3DXMatrixMultiply(&g_mtxWorldLine, &g_mtxWorldLine, &mtxTrans);

            // ワールドマトリックスの設定
            pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldLine);

            // 頂点バッファをデータストリームに設定
            pDevice->SetStreamSource(0, g_pVtxBuffLine, 0, sizeof(VERTEX_3D));

            // 頂点フォーマットの設定
            pDevice->SetFVF(FVF_VERTEX_3D);

            // テクスチャの設定
            pDevice->SetTexture(0, NULL);

            // ポリゴンの描画
            pDevice->DrawPrimitive(D3DPT_LINELIST, //プリミティブの種類
                nCntLine * 2, //描画する最初の頂点インデックス
                1);             //描画するプリミティブ数

            //[nCntLine].bUse = false;

                 
            //テクスチャを戻す
            pDevice->SetTexture(0, NULL);
        }
    }
}


//=============================
// ラインの設定処理
//=============================
void SetLine(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR col)
{
    VERTEX_3D* pVtx;

    // 頂点バッファをロックし、頂点情報へのポインタを取得
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

            // 頂点座標の設定
            pVtx[0].pos = D3DXVECTOR3(-fabsf(end.x - start.x) * 0.5f, -fabsf(end.y - start.y) * 0.5f, -fabsf(end.z - start.z) * 0.5f);
            pVtx[1].pos = D3DXVECTOR3(fabsf(end.x - start.x) * 0.5f, fabsf(end.y - start.y) * 0.5f, fabsf(end.z - start.z) * 0.5f);

            pVtx[0].col = col;
            pVtx[1].col = col;

            g_aLine[nCntLine].bUse = true;

            break;
        }

        pVtx += 2;
    }

    // 頂点バッファをアンロックする
    g_pVtxBuffLine->Unlock();
}
//
////=============================
//// ラインの表示設定取得処理
////=============================
//bool* GetLineDisplay(void)
//{
//    return &g_bLineDisplay;
//}