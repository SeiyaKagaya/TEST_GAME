//=========================================================
//
//パーティクルを表示する処理[particle.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
//#include "item.h"
//#include "sound.h"
//#include "input.h"
#include "particle.h"


//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL; //頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureParticle[PARTICLETYPE_MAX] = {};       //テクスチャへのポインタ



//D3DXVECTOR3 g_Particle[nParticle].posParticle;	//位置
//D3DXVECTOR3 g_Particle[nParticle].rotParticle;	//向き
//D3DXMATRIX g_Particle[nParticle].mtxWorld;//ワールドマトリックス


Particle g_Particle[MAX_PARTICLE];//制作中　構造体



//=============================
//パーティクルの初期化処理
//=============================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &g_pTextureParticle[0]);//御札


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffParticle, NULL);

	VERTEX_3D* pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nParticle = 0; nParticle < MAX_PARTICLE; nParticle++)
	{
		//g_Particle[nParticle].g_Particle[nParticle].posParticle
		//g_Particle[nParticle].rotParticle
		//g_Particle[nParticle].

		g_Particle[nParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置

		
		g_Particle[nParticle].nLife = 0;
		g_Particle[nParticle].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_Particle[nParticle].fRadius = 0.0f;
		g_Particle[nParticle].DiffRadius = 0;
		g_Particle[nParticle].nType = PARTICLETYPE_MAX;

		g_Particle[nParticle].bUse = false;
	

	
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-0, -0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, -0, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標を設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下

		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffParticle->Unlock();





}
//=============================
//パーティクルの終了処理
//=============================
void UninitParticle(void)
{
	//StopSound(SOUND_LABEL_SE_SHOT);
	//StopSound(SOUND_LABEL_SE_EXPLOSIONBOMB);
	//テクスチャの破棄
	for (int i = 0; i < PARTICLETYPE_MAX; i++)
	{
		if (g_pTextureParticle[i] != NULL)
		{
			g_pTextureParticle[i]->Release();
			g_pTextureParticle[i] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}
//=============================
//パーティクルの更新処理
//=============================
void UpdateParticle(void)
{

	VERTEX_3D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nParticle = 0; nParticle < MAX_PARTICLE; nParticle++)
	{
		if (g_Particle[nParticle].bUse == true)
		{
			//g_Particle[nParticle].oldPos = g_Particle[nParticle].pos;
			//位置を更新
			g_Particle[nParticle].pos += g_Particle[nParticle].move;



		
			//--------------------------------寿命
			g_Particle[nParticle].nLife--;

			g_Particle[nParticle].fRadius -= g_Particle[nParticle].DiffRadius;

			if (g_Particle[nParticle].nLife < 0)
			{
				g_Particle[nParticle].bUse = false;
			
			}
			//--------------------------------寿命

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_Particle[nParticle].fRadius, g_Particle[nParticle].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Particle[nParticle].fRadius, g_Particle[nParticle].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Particle[nParticle].fRadius, -g_Particle[nParticle].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Particle[nParticle].fRadius, -g_Particle[nParticle].fRadius, 0.0f);



			//頂点カラーの設定
			pVtx[0].col = g_Particle[nParticle].col;
			pVtx[1].col = g_Particle[nParticle].col;
			pVtx[2].col = g_Particle[nParticle].col;
			pVtx[3].col = g_Particle[nParticle].col;



		}
		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffParticle->Unlock();

}
//=============================
//パーティクルの描画処理
//=============================
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX  mtxTrans;//計算用マトリックス
	D3DXMATRIX mtxView;//ビューマトリックスの取得

	for (int nParticle = 0; nParticle < MAX_PARTICLE; nParticle++)
	{
		if (g_Particle[nParticle].bUse == true)
		{
			//ライトを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			////Zの比較変更
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			////Zバッファに書き込まない
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);




			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Particle[nParticle].mtxWorld);

			//向きを反映
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Particle[nParticle].rotParticle.y, g_Particle[nParticle].rotParticle.x, g_Particle[nParticle].rotParticle.z);

			//D3DXMatrixMultiply(&g_Particle[nParticle].mtxWorld, &g_Particle[nParticle].mtxWorld, &mtxRot);

					//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Particle[nParticle].pos.x, g_Particle[nParticle].pos.y, g_Particle[nParticle].pos.z);

			D3DXMatrixMultiply(&g_Particle[nParticle].mtxWorld, &g_Particle[nParticle].mtxWorld, &mtxTrans);



			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_Particle[nParticle].mtxWorld, NULL, &mtxView);//逆行鉄を求める

			g_Particle[nParticle].mtxWorld._41 = 0.0f;
			g_Particle[nParticle].mtxWorld._42 = 0.0f;
			g_Particle[nParticle].mtxWorld._43 = 0.0f;


			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Particle[nParticle].pos.x, g_Particle[nParticle].pos.y, g_Particle[nParticle].pos.z);

			D3DXMatrixMultiply(&g_Particle[nParticle].mtxWorld, &g_Particle[nParticle].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Particle[nParticle].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);


			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureParticle[0]);

			//アルファブレンディングを加算合成に設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


			//パーティクルの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				nParticle * 4,//描画する最初の頂点インデックス
				2);//描画するプリミティブ数


			//アルファブレンディングをもとに戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


			//ライトを有効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			////Zの比較変更
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			////Zバッファに書き込まない
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

			
			//テクスチャを戻す
			pDevice->SetTexture(0, NULL);
		}
	}
}
//=============================
//パーティクルの取得処理
//=============================

Particle* GetParticle(void)
{
	return &g_Particle[0];
}

//=============================
//パーティクルの設定処理
//=============================
void SetParticle(D3DXVECTOR3 Pos,float fRadius,int nLife, PARTICLETYPE Type, D3DXCOLOR Color)
{


	VERTEX_3D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nParticle = 0; nParticle < MAX_PARTICLE; nParticle++)
	{
		if (g_Particle[nParticle].bUse == false)
		{
				g_Particle[nParticle].pos = Pos;//位置

				g_Particle[nParticle].fRadius = fRadius;
				g_Particle[nParticle].DiffRadius = fRadius/ nLife;
				g_Particle[nParticle].col = Color;
				//pPlayer2->ParticleShotFrame = MAXSHOTFRAME;
				//VibrationLeft(35535);
				//VibrationRight(35535);

				//SE
				//PlaySound(SOUND_LABEL_SE_SHOT);

			g_Particle[nParticle].move =D3DXVECTOR3(0.0f,0.0f,0.0f);

			// 幅、高さ後ほど
			g_Particle[nParticle].nType = Type;
			g_Particle[nParticle].bUse = true;

			g_Particle[nParticle].nLife = nLife;
			break;
		}
		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffParticle->Unlock();
}
////=============================
//// 予測交差点を計算する関数
////=============================
//D3DXVECTOR3 PredictIntersection(Particle bullet, Enemy enemy)
//{
//	//計算ズレをあえて制作
//	//乱数を生成
//
//	int random = ((rand() % 20) - 10);//(25~-25)までの乱数
//
//	float random2 = random * 0.1f;//
//
//	//誤差を入れる
//	D3DXVECTOR3 randomPosError = D3DXVECTOR3(random2, random2 * -1.0f, random2);
//
//	// 自弾と敵(誤差も)の相対位置ベクトル
//	D3DXVECTOR3 relativePos = bullet.pos - (enemy.pos + randomPosError);
//
//	// 自弾と敵の相対速度ベクトル
//	D3DXVECTOR3 relativeVel = bullet.move - enemy.move;
//
//	// 自弾と敵の最短交差時間
//	float timeToIntersection = -D3DXVec3Dot(&relativePos, &relativeVel) / D3DXVec3LengthSq(&relativeVel);
//
//	// 敵の予測位置（交差点）を計算
//	D3DXVECTOR3 predictedIntersection = (enemy.pos + randomPosError) + enemy.move * timeToIntersection;
//
//	return predictedIntersection;
//}


