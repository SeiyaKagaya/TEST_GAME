//=========================================================
//
//敵の視野[enemy_view.cpp]
// Author Matsuda Towa
//
//=========================================================
#include "enemy_view.h"
#include "enemy.h"
#include "main.h"

//=========================================================
//グローバル変数宣言
//=========================================================
LPD3DXMESH g_pMeshEnemy_View[MAX_ENEMYVIEW] = {};//メッシュ(頂点情報)へのポインタ

LPD3DXBUFFER g_pBuffMatEnemy_View[MAX_ENEMYVIEW] = {};//マテリアルへのポインタ
DWORD g_dwNumMatEnemy_View = 0;//マテリアルの数

ENEMYVIEW g_Enemy_View[MAX_ENEMYVIEW];
//=========================================================
//初期化
//=========================================================
void InitEnemy_View(void)
{
    // 変数の初期化
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
//終了
//=========================================================
void UninitEnemy_View(void)
{
    for (int nCntZone = 0; nCntZone < MAX_ENEMYVIEW; nCntZone++)
    {
        //メッシュの破棄
        if (g_pMeshEnemy_View[nCntZone] != NULL)
        {
            g_pMeshEnemy_View[nCntZone]->Release();
            g_pMeshEnemy_View[nCntZone] = NULL;
        }
        //マテリアルの破棄
        if (g_pBuffMatEnemy_View[nCntZone] != NULL)
        {
            g_pBuffMatEnemy_View[nCntZone]->Release();
            g_pBuffMatEnemy_View[nCntZone] = NULL;
        }
    }
}

//=========================================================
//更新
//=========================================================
void UpdateEnemy_View(void)
{
    for (int nCntZone = 0; nCntZone < MAX_ENEMYVIEW; nCntZone++)
    {
        if (g_Enemy_View[nCntZone].bUse == true)
        {
            ENEMYMODEL* pEnemy = GetEnemy();
            g_Enemy_View[nCntZone].pos += pEnemy->move;
            //D3DXMATRIX mtxRot, mtxTrans, mtxParent;//計算用マトリックス	

            //for (int nCntZone = 0; nCntZone < MAX_ENEMYVIEW; nCntZone++)
            //{

            //    if (g_Enemy_View[nCntZone].bDrawOk == true)
            //    {
            //        //ワールドマトリックスの初期化
            //        D3DXMatrixIdentity(&g_Enemy_View[nCntZone].mtxWorld);

            //        // モデルのサイズを変更
            //        D3DXMatrixScaling(&g_Enemy_View[nCntZone].mtxWorld, g_Enemy_View[nCntZone].SizeMag.x, g_Enemy_View[nCntZone].SizeMag.y, g_Enemy_View[nCntZone].SizeMag.z);


            //        if (g_Enemy_View[nCntZone].bFollowEnemy == true)
            //        {

            //            ////向きを反映
            //            //D3DXMatrixRotationYawPitchRoll(&mtxRot, pEnemy->rot.y, pEnemy->rot.x, pEnemy->rot.z);

            //            //D3DXMatrixMultiply(&g_Enemy_View[nCntZone].mtxWorld, &g_Enemy_View[nCntZone].mtxWorld, &mtxRot);

            //            //位置を反映
            //            D3DXMatrixTranslation(&mtxTrans, g_Enemy_View[nCntZone].pos.x, g_Enemy_View[nCntZone].pos.y, g_Enemy_View[nCntZone].pos.z);

            //            D3DXMatrixMultiply(&g_Enemy_View[nCntZone].mtxWorld, &g_Enemy_View[nCntZone].mtxWorld, &mtxTrans);

            //            //エネミーを親として動かす
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
//描画
//=========================================================
void DrawEnemy_View(void)
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

    D3DMATERIAL9 matDef;//現在のマテリアル保存用(一時退避)

    D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

    for (int nCntZone = 0; nCntZone < MAX_ENEMYVIEW; nCntZone++)
    {
        if (g_Enemy_View[nCntZone].bUse == true)
        {
            if (g_Enemy_View[nCntZone].bDrawOk == true)
            {
                //ワールドマトリックスの初期化
                D3DXMatrixIdentity(&g_Enemy_View[nCntZone].mtxWorld);

                // モデルのサイズを変更
                D3DXMatrixScaling(&g_Enemy_View[nCntZone].mtxWorld, g_Enemy_View[nCntZone].SizeMag.x, g_Enemy_View[nCntZone].SizeMag.y, g_Enemy_View[nCntZone].SizeMag.z);


                //if (g_Enemy_View[nCntZone].bFollowEnemy == true)
                //{
                //    ENEMYMODEL* pEnemy = GetEnemy();
                //    ////向きを反映
                //    //D3DXMatrixRotationYawPitchRoll(&mtxRot, pEnemy->rot.y, pEnemy->rot.x, pEnemy->rot.z);

                //    //D3DXMatrixMultiply(&g_Enemy_View[nCntZone].mtxWorld, &g_Enemy_View[nCntZone].mtxWorld, &mtxRot);

                //    //位置を反映
                //    D3DXMatrixTranslation(&mtxTrans, g_Enemy_View[nCntZone].pos.x, g_Enemy_View[nCntZone].pos.y, g_Enemy_View[nCntZone].pos.z);

                //    D3DXMatrixMultiply(&g_Enemy_View[nCntZone].mtxWorld, &g_Enemy_View[nCntZone].mtxWorld, &mtxTrans);

                //    //エネミーを親として動かす
                //    D3DXMatrixMultiply(&g_Enemy_View[nCntZone].mtxWorld, &g_Enemy_View[nCntZone].mtxWorld, &pEnemy->mtxWorld);
                //}
                //else
                //{


                //}
                
                //ワールドマトリックスの設定
                pDevice->SetTransform(D3DTS_WORLD, &g_Enemy_View[nCntZone].mtxWorld);

                //現在のマテリアルを取得
                pDevice->GetMaterial(&matDef);

                //マテリアルデータへのポインタを取得
                pMat = (D3DXMATERIAL*)g_pBuffMatEnemy_View[nCntZone]->GetBufferPointer();

                for (int nCntMat = 0; nCntMat < (int)g_dwNumMatEnemy_View; nCntMat++)
                {
                    //マテリアルの設定
                    pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                    //テクスチャの設定
                    pDevice->SetTexture(0, NULL);//今回は設定しない

                    //モデル(パーツ)の描画
                    g_pMeshEnemy_View[nCntMat]->DrawSubset(nCntMat);

                    //保存してたマテリアルを戻す
                    pDevice->SetMaterial(&matDef);

                    // マテリアルの設定
                    pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                    // ディフューズカラーを変更（例: 赤い色）
                    pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(g_Enemy_View[nCntZone].ZoneColor.r * g_Enemy_View[nCntZone].SizeMag.x, g_Enemy_View[nCntZone].ZoneColor.g * g_Enemy_View[nCntZone].SizeMag.x, g_Enemy_View[nCntZone].ZoneColor.b * g_Enemy_View[nCntZone].SizeMag.x, g_Enemy_View[nCntZone].ZoneColor.a);

                }
            }
        }
    }

}

//=========================================================
//視野の情報取得
//=========================================================
ENEMYVIEW* GetEnemy_View(void)
{
	return &g_Enemy_View[0];
}

//=========================================================
//視野セット
//=========================================================
void SetEnemy_View(D3DXVECTOR3 Pos, float Radius, bool bFollowEnemy, D3DXCOLOR ZoneColor)
{
    //デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = GetDevice();//----------------書き換え済み

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

            //サイズ変動
            g_Enemy_View[nCntZone].SizeMag.x = g_Enemy_View[nCntZone].ZoneMax.x / 10.0f;
            g_Enemy_View[nCntZone].SizeMag.y = g_Enemy_View[nCntZone].ZoneMax.y / 10.0f;
            g_Enemy_View[nCntZone].SizeMag.z = g_Enemy_View[nCntZone].ZoneMax.z / 10.0f;

            g_Enemy_View[nCntZone].bFollowEnemy = bFollowEnemy;
            g_Enemy_View[nCntZone].bUse = true;
            g_Enemy_View[nCntZone].bDrawOk = true;

            //ファイルの読み込み
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
