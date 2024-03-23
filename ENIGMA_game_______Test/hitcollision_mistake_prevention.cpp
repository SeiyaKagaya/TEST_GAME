//=========================================================
//
//当たり判定抜け阻止させる処理[hitcollision_mistake_prevention.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "hitcollision_mistake_prevention.h"
//#include "player.h"
//#include "player2.h"
//#include "line.h"


//グローバル変数宣言
LPD3DXMESH g_pMeshCollision_Pre[MAXCOLLISION_PRE] = {};//メッシュ(頂点情報)へのポインタ

LPD3DXBUFFER g_pBuffMatCollision_Pre[MAXCOLLISION_PRE] = {};//マテリアルへのポインタ
DWORD g_dwNumMatCollision_Pre = 0;//マテリアルの数

COLLISION_PRE g_Collision_Pre[MAXCOLLISION_PRE];




//=============================
// 当たり判定抜け防止初期化処理
//=============================
void InitCollision_Pre(void)
{    // 変数の初期化
    for (int nCntGate = 0; nCntGate < MAXCOLLISION_PRE; nCntGate++)
    {
        g_Collision_Pre[nCntGate].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_Collision_Pre[nCntGate].Min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        g_Collision_Pre[nCntGate].Max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

        g_Collision_Pre[nCntGate].bUse = false;
    }





    //---------------------座標------------------------最小--------------------最大---------色-
    // ペアで２つごとに記入--色は単色で(合成色を他のに使用したい)
        

    //十字路の壁        
    SetCollision_Pre(D3DXVECTOR3(50.0f, 0.0f, -2745.0f), D3DXVECTOR3(-400.0f, 0.0f, -105.0f), D3DXVECTOR3(400.0f, 300.0f, 105.0f), D3DXCOLOR(5.0f, 0.0f, 0.0f, 0.5f));
    SetCollision_Pre(D3DXVECTOR3(50.0f, 0.0f, -3055.0f), D3DXVECTOR3(-400.0f, 0.0f, -105.0f), D3DXVECTOR3(400.0f, 300.0f, 105.0f), D3DXCOLOR(5.0f, 0.0f, 0.0f, 0.5f));

    SetCollision_Pre(D3DXVECTOR3(-1250.0f, 0.0f, -2745.0f), D3DXVECTOR3(-400.0f, 0.0f, -105.0f), D3DXVECTOR3(400.0f, 300.0f, 105.0f), D3DXCOLOR(5.0f, 0.0f, 0.0f, 0.5f));
    SetCollision_Pre(D3DXVECTOR3(-1250.0f, 0.0f, -3055.0f), D3DXVECTOR3(-400.0f, 0.0f, -105.0f), D3DXVECTOR3(400.0f, 300.0f, 105.0f), D3DXCOLOR(5.0f, 0.0f, 0.0f, 0.5f));

    SetCollision_Pre(D3DXVECTOR3(-445.0f, 0.0f, -2250.0f), D3DXVECTOR3(-105.0f, 0.0f, -400.0f), D3DXVECTOR3(105.0f, 300.0f, 400.0f), D3DXCOLOR(5.0f, 0.0f, 0.0f, 0.5f));
    SetCollision_Pre(D3DXVECTOR3(-755.0f, 0.0f, -2250.0f), D3DXVECTOR3(-105.0f, 0.0f, -400.0f), D3DXVECTOR3(105.0f, 300.0f, 400.0f), D3DXCOLOR(5.0f, 0.0f, 0.0f, 0.5f));

    SetCollision_Pre(D3DXVECTOR3(-445.0f, 0.0f, -3550.0f), D3DXVECTOR3(-105.0f, 0.0f, -400.0f), D3DXVECTOR3(105.0f, 300.0f, 400.0f), D3DXCOLOR(5.0f, 0.0f, 0.0f, 0.5f));
    SetCollision_Pre(D3DXVECTOR3(-755.0f, 0.0f, -3550.0f), D3DXVECTOR3(-105.0f, 0.0f, -400.0f), D3DXVECTOR3(105.0f, 300.0f, 400.0f), D3DXCOLOR(5.0f, 0.0f, 0.0f, 0.5f));



    //十字路の壁(通路端)        
    SetCollision_Pre(D3DXVECTOR3(-1640.0f, 0.0f, -2900.0f), D3DXVECTOR3(-100.0f, 0.0f, -100.0f), D3DXVECTOR3(100.0f, 600.0f, 100.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));
    SetCollision_Pre(D3DXVECTOR3(440.0f, 0.0f, -2900.0f), D3DXVECTOR3(-100.0f, 0.0f, -100.0f), D3DXVECTOR3(100.0f, 600.0f, 100.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));

    SetCollision_Pre(D3DXVECTOR3(-600.0f, 0.0f, -4000.0f), D3DXVECTOR3(-100.0f, 0.0f, -100.0f), D3DXVECTOR3(100.0f, 600.0f, 100.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));
    SetCollision_Pre(D3DXVECTOR3(-600.0f, 0.0f, -1800.0f), D3DXVECTOR3(-100.0f, 0.0f, -100.0f), D3DXVECTOR3(100.0f, 600.0f, 100.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));

    //水回り
    SetCollision_Pre(D3DXVECTOR3(3237.0f, 0.0f, -260.0f), D3DXVECTOR3(-400.0f, 0.0f, 09.0f), D3DXVECTOR3(160.0f, 300.0f, 10.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));
    
    SetCollision_Pre(D3DXVECTOR3(3500.0f, 150.0f, -100.0f), D3DXVECTOR3(-2.0f, 0.0f, -050.0f), D3DXVECTOR3(2.0f, 200.0f, 050.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));
    
    SetCollision_Pre(D3DXVECTOR3(3600.0f, 0.0f, -400.0f), D3DXVECTOR3(-100.0f, 0.0f, -250.0f), D3DXVECTOR3(100.0f, 300.0f, 250.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));
    
    SetCollision_Pre(D3DXVECTOR3(3200.0f, 120.0f, -450.0f), D3DXVECTOR3(-2.0f, 0.0f, -200.0f), D3DXVECTOR3(2.0f, 200.0f, 200.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));
    
    SetCollision_Pre(D3DXVECTOR3(3200.0f, 0.0f, -600.0f), D3DXVECTOR3(-4.0f, 0.0f, -100.0f), D3DXVECTOR3(4.0f, 120.0f, 100.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));
   
    SetCollision_Pre(D3DXVECTOR3(3200.0f, 0.0f, -320.0f), D3DXVECTOR3(-4.0f, 0.0f, -80.0f), D3DXVECTOR3(4.0f, 120.0f, 50.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));
    
    SetCollision_Pre(D3DXVECTOR3(3400.0f, 0.0f, -1800.0f), D3DXVECTOR3(-300.0f, 0.0f, -100.0f), D3DXVECTOR3(300.0f, 300.0f, 100.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));

    //トイレ横
    SetCollision_Pre(D3DXVECTOR3(3525.0f, 0.0f, 20.0f), D3DXVECTOR3(-130.0f, 0.0f, -70.0f), D3DXVECTOR3(130.0f, 300.0f, 70.0f), D3DXCOLOR(5.0f, 0.0f, 5.0f, 0.5f));

}
//=============================
// 当たり判定抜け防止終了処理
//=============================
void UninitCollision_Pre(void)
{
    for (int nCntGate = 0; nCntGate < MAXCOLLISION_PRE; nCntGate++)
    {
        //メッシュの破棄
        if (g_pMeshCollision_Pre[nCntGate] != NULL)
        {
            g_pMeshCollision_Pre[nCntGate]->Release();
            g_pMeshCollision_Pre[nCntGate] = NULL;
        }
        //マテリアルの破棄
        if (g_pBuffMatCollision_Pre[nCntGate] != NULL)
        {
            g_pBuffMatCollision_Pre[nCntGate]->Release();
            g_pBuffMatCollision_Pre[nCntGate] = NULL;
        }
    }
}

//=============================
// 当たり判定抜け防止更新処理
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
            ////ラインの位置
            //// 上下の辺
            //SetLine(D3DXVECTOR3(Collision_PreMin.x, Collision_PreMax.y, Collision_PreMin.z), D3DXVECTOR3(Collision_PreMax.x, Collision_PreMax.y, Collision_PreMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(Collision_PreMin.x, Collision_PreMin.y, Collision_PreMin.z), D3DXVECTOR3(Collision_PreMax.x, Collision_PreMin.y, Collision_PreMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //SetLine(D3DXVECTOR3(Collision_PreMin.x, Collision_PreMax.y, Collision_PreMax.z), D3DXVECTOR3(Collision_PreMax.x, Collision_PreMax.y, Collision_PreMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(Collision_PreMin.x, Collision_PreMin.y, Collision_PreMax.z), D3DXVECTOR3(Collision_PreMax.x, Collision_PreMin.y, Collision_PreMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //// 側面の辺
            //SetLine(D3DXVECTOR3(Collision_PreMin.x, Collision_PreMin.y, Collision_PreMin.z), D3DXVECTOR3(Collision_PreMin.x, Collision_PreMax.y, Collision_PreMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(Collision_PreMax.x, Collision_PreMin.y, Collision_PreMin.z), D3DXVECTOR3(Collision_PreMax.x, Collision_PreMax.y, Collision_PreMin.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //SetLine(D3DXVECTOR3(Collision_PreMin.x, Collision_PreMin.y, Collision_PreMax.z), D3DXVECTOR3(Collision_PreMin.x, Collision_PreMax.y, Collision_PreMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(Collision_PreMax.x, Collision_PreMin.y, Collision_PreMax.z), D3DXVECTOR3(Collision_PreMax.x, Collision_PreMax.y, Collision_PreMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //// その他の辺
            //SetLine(D3DXVECTOR3(Collision_PreMin.x, Collision_PreMin.y, Collision_PreMin.z), D3DXVECTOR3(Collision_PreMin.x, Collision_PreMin.y, Collision_PreMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(Collision_PreMax.x, Collision_PreMax.y, Collision_PreMin.z), D3DXVECTOR3(Collision_PreMax.x, Collision_PreMax.y, Collision_PreMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

            //SetLine(D3DXVECTOR3(Collision_PreMin.x, Collision_PreMax.y, Collision_PreMin.z), D3DXVECTOR3(Collision_PreMin.x, Collision_PreMax.y, Collision_PreMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
            //SetLine(D3DXVECTOR3(Collision_PreMax.x, Collision_PreMin.y, Collision_PreMin.z), D3DXVECTOR3(Collision_PreMax.x, Collision_PreMin.y, Collision_PreMax.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

#endif







        }
    }
}

//=============================
// 当たり判定抜け防止描画処理
//=============================
void DrawCollision_Pre(void)
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

    D3DMATERIAL9 matDef;//現在のマテリアル保存用(一時退避)

    D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

    for (int nCntGate = 0; nCntGate < MAXCOLLISION_PRE; nCntGate++)
    {
        if (g_Collision_Pre[nCntGate].bUse == true)
        {
            ////ライトを無効にする
            //pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

            ////Zの比較変更
            //pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
            ////Zバッファに書き込まない
            //pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);



            //ワールドマトリックスの初期化
            D3DXMatrixIdentity(&g_Collision_Pre[nCntGate].mtxWorld);

            // モデルのサイズを変更
            D3DXMatrixScaling(&g_Collision_Pre[nCntGate].mtxWorld, g_Collision_Pre[nCntGate].SizeMag.x, g_Collision_Pre[nCntGate].SizeMag.y, g_Collision_Pre[nCntGate].SizeMag.z);

            ////向きを反映
            //D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);

            //D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

            //位置を反映
            D3DXMatrixTranslation(&mtxTrans, g_Collision_Pre[nCntGate].pos.x, g_Collision_Pre[nCntGate].pos.y, g_Collision_Pre[nCntGate].pos.z);

            D3DXMatrixMultiply(&g_Collision_Pre[nCntGate].mtxWorld, &g_Collision_Pre[nCntGate].mtxWorld, &mtxTrans);

            //ワールドマトリックスの設定
            pDevice->SetTransform(D3DTS_WORLD, &g_Collision_Pre[nCntGate].mtxWorld);

            //現在のマテリアルを取得
            pDevice->GetMaterial(&matDef);

            //マテリアルデータへのポインタを取得
            pMat = (D3DXMATERIAL*)g_pBuffMatCollision_Pre[nCntGate]->GetBufferPointer();

            for (int nCntMat = 0; nCntMat < (int)g_dwNumMatCollision_Pre; nCntMat++)
            {
                //マテリアルの設定
            //    pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                //テクスチャの設定
                pDevice->SetTexture(0, NULL);//今回は設定しない

                //モデル(パーツ)の描画
                g_pMeshCollision_Pre[nCntMat]->DrawSubset(nCntMat);

                //保存してたマテリアルを戻す
             //   pDevice->SetMaterial(&matDef);


                // マテリアルの設定
                pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                // ディフューズカラーを変更（例: 赤い色）
                pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(g_Collision_Pre[nCntGate].GateColor.r * g_Collision_Pre[nCntGate].SizeMag.x, g_Collision_Pre[nCntGate].GateColor.g * g_Collision_Pre[nCntGate].SizeMag.x, g_Collision_Pre[nCntGate].GateColor.b * g_Collision_Pre[nCntGate].SizeMag.x, g_Collision_Pre[nCntGate].GateColor.a);

                ////ライトを有効にする
                //pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

                ////Zの比較変更
                //pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
                ////Zバッファに書き込まない
                //pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
            }

            //保存してたマテリアルを戻す
            pDevice->SetMaterial(&matDef);

            //テクスチャを戻す
            pDevice->SetTexture(0, NULL);
        }
    }




}
//=============================
// 当たり判定抜け防止取得処理
//=============================
COLLISION_PRE* GetCollision_Pre(void)
{
    return &g_Collision_Pre[0];
}
//=============================
// 当たり判定抜け防止設定処理
//=============================
//-----------------------------自分座標-----------------最小----------------最大---------自分の番号----転移先の番号--矯正転移かどうか--行動ボタンで転移かどうか
void SetCollision_Pre(D3DXVECTOR3 Pos, D3DXVECTOR3 GateMin, D3DXVECTOR3 GateMax, D3DXCOLOR GateColor)
{
    //デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = GetDevice();//----------------書き換え済み

    for (int nCntGate = 0; nCntGate < MAXCOLLISION_PRE; nCntGate++)
    {
        if (g_Collision_Pre[nCntGate].bUse == false)
        {
            g_Collision_Pre[nCntGate].pos = Pos;
            g_Collision_Pre[nCntGate].Min = GateMin;
            g_Collision_Pre[nCntGate].Max = GateMax;
            g_Collision_Pre[nCntGate].GateColor = GateColor;
         
            //サイズ変動
            g_Collision_Pre[nCntGate].SizeMag.x = g_Collision_Pre[nCntGate].Max.x / 10.0f;
            g_Collision_Pre[nCntGate].SizeMag.y = g_Collision_Pre[nCntGate].Max.y / 20.0f;
            g_Collision_Pre[nCntGate].SizeMag.z = g_Collision_Pre[nCntGate].Max.z / 10.0f;

            g_Collision_Pre[nCntGate].bUse = true;

            //ファイルの読み込み
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

