//=========================================================
//
//エリアによって行動させる処理[Actionzone.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "Actionzone.h"
//#include "player.h"
//#include "player2.h"
#include "line.h"
//using namespace __unnamed_enum_0153_1;


//グローバル変数宣言
LPD3DXMESH g_pMeshZone[MAXZONE] = {};//メッシュ(頂点情報)へのポインタ

LPD3DXBUFFER g_pBuffMatZone[MAXZONE] = {};//マテリアルへのポインタ
DWORD g_dwNumMatZone = 0;//マテリアルの数

ACTIONZONE g_ActionZone[MAXZONE];

//=============================
// アクションエリア初期化処理
//=============================
void InitActionZone(void)
{    // 変数の初期化
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



    //-----------------------------自分座標-----------半径---------行動タイプ-------色
// ペアで２つごとに記入--色は単色で(合成色を他のに使用したい)

    ////これで１ペア
    //SetActionZone(D3DXVECTOR3(1000.0f, 0.0f, -500.0f), 200, ACTION_TYPE_MAX, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.7f));
    //SetActionZone(D3DXVECTOR3(1000.0f, 0.0f, 500.0f), 200, ACTION_TYPE_MAX, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.7f));


    //SetActionZone(D3DXVECTOR3(500.0f, 300.0f, -300.0f), 300, ACTION_TYPE_MAX, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.7f));
    //SetActionZone(D3DXVECTOR3(500.0f, 300.0f, 300.0f), 300, ACTION_TYPE_MAX, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.7f));




    //    //これで１ペア
    //SetActionZone(D3DXVECTOR3(2000.0f, 0.0f, -700.0f), D3DXVECTOR3(-50.0f, 0.0f, -50.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), 0, 1, ACTION_TYPE_MAX);
    //SetActionZone(D3DXVECTOR3(2000.0f, 0.0f, 700.0f), D3DXVECTOR3(-50.0f, 0.0f, -50.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), 1, 0, ACTION_TYPE_MAX);


    //SetActionZone(D3DXVECTOR3(200.0f, 100.0f, -300.0f), D3DXVECTOR3(-50.0f, 0.0f, -50.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), 2, 3, ACTION_TYPE_MAX_Z);
    //SetActionZone(D3DXVECTOR3(200.0f, 50.0f, 300.0f), D3DXVECTOR3(-50.0f, 0.0f, -50.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), 3, 2, TRANS_ANGLE_MIN_Z);


}

//=============================
// アクションエリア終了処理
//=============================
void UninitActionZone(void)
{
    for (int nCntZone = 0; nCntZone < MAXZONE; nCntZone++)
    {
        //メッシュの破棄
        if (g_pMeshZone[nCntZone] != NULL)
        {
            g_pMeshZone[nCntZone]->Release();
            g_pMeshZone[nCntZone] = NULL;
        }
        //マテリアルの破棄
        if (g_pBuffMatZone[nCntZone] != NULL)
        {
            g_pBuffMatZone[nCntZone]->Release();
            g_pBuffMatZone[nCntZone] = NULL;
        }
    }
}

//=============================
// アクションエリア更新処理
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
            ////ラインの位置
            //// 上下の辺
            //SetLine(D3DXVECTOR3(ActionZoneMin.x, ActionZoneMax.y, ActionZoneMin.z), D3DXVECTOR3(ActionZoneMax.x, ActionZoneMax.y, ActionZoneMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(ActionZoneMin.x, ActionZoneMin.y, ActionZoneMin.z), D3DXVECTOR3(ActionZoneMax.x, ActionZoneMin.y, ActionZoneMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //SetLine(D3DXVECTOR3(ActionZoneMin.x, ActionZoneMax.y, ActionZoneMax.z), D3DXVECTOR3(ActionZoneMax.x, ActionZoneMax.y, ActionZoneMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(ActionZoneMin.x, ActionZoneMin.y, ActionZoneMax.z), D3DXVECTOR3(ActionZoneMax.x, ActionZoneMin.y, ActionZoneMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //// 側面の辺
            //SetLine(D3DXVECTOR3(ActionZoneMin.x, ActionZoneMin.y, ActionZoneMin.z), D3DXVECTOR3(ActionZoneMin.x, ActionZoneMax.y, ActionZoneMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(ActionZoneMax.x, ActionZoneMin.y, ActionZoneMin.z), D3DXVECTOR3(ActionZoneMax.x, ActionZoneMax.y, ActionZoneMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //SetLine(D3DXVECTOR3(ActionZoneMin.x, ActionZoneMin.y, ActionZoneMax.z), D3DXVECTOR3(ActionZoneMin.x, ActionZoneMax.y, ActionZoneMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(ActionZoneMax.x, ActionZoneMin.y, ActionZoneMax.z), D3DXVECTOR3(ActionZoneMax.x, ActionZoneMax.y, ActionZoneMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //// その他の辺
            //SetLine(D3DXVECTOR3(ActionZoneMin.x, ActionZoneMin.y, ActionZoneMin.z), D3DXVECTOR3(ActionZoneMin.x, ActionZoneMin.y, ActionZoneMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(ActionZoneMax.x, ActionZoneMax.y, ActionZoneMin.z), D3DXVECTOR3(ActionZoneMax.x, ActionZoneMax.y, ActionZoneMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //SetLine(D3DXVECTOR3(ActionZoneMin.x, ActionZoneMax.y, ActionZoneMin.z), D3DXVECTOR3(ActionZoneMin.x, ActionZoneMax.y, ActionZoneMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(ActionZoneMax.x, ActionZoneMin.y, ActionZoneMin.z), D3DXVECTOR3(ActionZoneMax.x, ActionZoneMin.y, ActionZoneMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

#endif







        }
    }
}

//=============================
// アクションエリア描画処理
//=============================
void DrawActionZone(void)
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

    D3DMATERIAL9 matDef;//現在のマテリアル保存用(一時退避)

    D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

    for (int nCntZone = 0; nCntZone < MAXZONE; nCntZone++)
    {
        if (g_ActionZone[nCntZone].bUse == true)
        {
            if (g_ActionZone[nCntZone].bDrawOk == true)
            {
                //ワールドマトリックスの初期化
                D3DXMatrixIdentity(&g_ActionZone[nCntZone].mtxWorld);

                 //モデルのサイズを変更
                D3DXMatrixScaling(&g_ActionZone[nCntZone].mtxWorld, g_ActionZone[nCntZone].SizeMag.x, g_ActionZone[nCntZone].SizeMag.y, g_ActionZone[nCntZone].SizeMag.z);

                ////向きを反映
                //D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);

                //D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

                //位置を反映
                D3DXMatrixTranslation(&mtxTrans, g_ActionZone[nCntZone].pos.x, g_ActionZone[nCntZone].pos.y, g_ActionZone[nCntZone].pos.z);

                D3DXMatrixMultiply(&g_ActionZone[nCntZone].mtxWorld, &g_ActionZone[nCntZone].mtxWorld, &mtxTrans);

                //ワールドマトリックスの設定
                pDevice->SetTransform(D3DTS_WORLD, &g_ActionZone[nCntZone].mtxWorld);

                //現在のマテリアルを取得
                pDevice->GetMaterial(&matDef);

                //マテリアルデータへのポインタを取得
                pMat = (D3DXMATERIAL*)g_pBuffMatZone[nCntZone]->GetBufferPointer();

                for (int nCntMat = 0; nCntMat < (int)g_dwNumMatZone; nCntMat++)
                {
                    //マテリアルの設定
                 //   pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                    //テクスチャの設定
                    pDevice->SetTexture(0, NULL);//今回は設定しない

                  

                    //保存してたマテリアルを戻す
                  //  pDevice->SetMaterial(&matDef);


                    // マテリアルの設定
                    pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                    // ディフューズカラーを変更（例: 赤い色）
                    pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(g_ActionZone[nCntZone].ZoneColor.r * g_ActionZone[nCntZone].SizeMag.x, g_ActionZone[nCntZone].ZoneColor.g * g_ActionZone[nCntZone].SizeMag.x, g_ActionZone[nCntZone].ZoneColor.b * g_ActionZone[nCntZone].SizeMag.x, g_ActionZone[nCntZone].ZoneColor.a);

                    //モデル(パーツ)の描画
                    g_pMeshZone[nCntMat]->DrawSubset(nCntMat);
                
                }
                //保存してたマテリアルを戻す
                pDevice->SetMaterial(&matDef);

                //テクスチャを戻す
                pDevice->SetTexture(0, NULL);

            }
        }
    }

}
//=============================
// アクションエリア取得処理
//=============================
ACTIONZONE* GetActionZone(void)
{
    return &g_ActionZone[0];
}
//=============================
// アクションエリア設定処理
//=============================
//-----------------------------自分座標-----------半径---------行動タイプ-------色
void SetActionZone(D3DXVECTOR3 Pos, float Radius, ACTIONTYPE ActionType, D3DXCOLOR ZoneColor)
{
    //デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = GetDevice();//----------------書き換え済み

    for (int nCntZone = 0; nCntZone < MAXZONE; nCntZone++)
    {
        if (ActionType == ACTION_TYPE_GAMECLEAR)
        {//これだけ分ける
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

            //サイズ変動
            g_ActionZone[nCntZone].SizeMag.x = g_ActionZone[nCntZone].ZoneMax.x / 10.0f;
            g_ActionZone[nCntZone].SizeMag.y = g_ActionZone[nCntZone].ZoneMax.y / 10.0f;
            g_ActionZone[nCntZone].SizeMag.z = g_ActionZone[nCntZone].ZoneMax.z / 10.0f;


            g_ActionZone[nCntZone].ActionType = ActionType;//転移先転移方向
            g_ActionZone[nCntZone].bPossibility = true;
            g_ActionZone[nCntZone].bUse = true;
            g_ActionZone[nCntZone].bDrawOk = true;

            //ファイルの読み込み
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
