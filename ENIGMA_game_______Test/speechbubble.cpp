//=========================================================
//
//吹き出しUIを表示する処理[speechbubble.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "game.h"
#include "speechbubble.h"


//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSpeechBubble = NULL; //頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureSpeechBubble[TEXNUM] = {};       //テクスチャへのポインタ



//D3DXVECTOR3 g_SpeechBubble[nSpeechBubble].posSpeechBubble;	//位置
//D3DXVECTOR3 g_SpeechBubble[nSpeechBubble].rotSpeechBubble;	//向き
//D3DXMATRIX g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble;//ワールドマトリックス


SPEECHBUBBLE g_SpeechBubble[NUMSPEECHBUBBLE];//制作中　構造体


int g_nldShadow3 = -1;


//=============================
//吹き出しUIの初期化処理
//=============================
void InitSpeechBubble(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UI000.png", &g_pTextureSpeechBubble[0]);//移動
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UI001.png", &g_pTextureSpeechBubble[1]);//操作
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UI002.png", &g_pTextureSpeechBubble[2]);//取得
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UI003.png", &g_pTextureSpeechBubble[3]);//長押し
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UI005.png", &g_pTextureSpeechBubble[4]);//脱出
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UI004.png", &g_pTextureSpeechBubble[5]);//切り替え
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * NUMSPEECHBUBBLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffSpeechBubble, NULL);

	VERTEX_3D* pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSpeechBubble->Lock(0, 0, (void**)&pVtx, 0);

	for (int nSpeechBubble = 0; nSpeechBubble < NUMSPEECHBUBBLE; nSpeechBubble++)
	{
	
		g_SpeechBubble[nSpeechBubble].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置
		g_SpeechBubble[nSpeechBubble].bUse = false;

		g_SpeechBubble[nSpeechBubble].nBubbleCnt = 0;
		g_SpeechBubble[nSpeechBubble].bOK = false;
		g_SpeechBubble[nSpeechBubble].bTrackingPlayer1=false;
		g_SpeechBubble[nSpeechBubble].bTrackingPlayer2=false;

		g_SpeechBubble[nSpeechBubble].BubbleSType = SPEECHBUBBLETYPE_MAX;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-0.0f, -0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, -0.0f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);

		//テクスチャ座標を設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下

		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffSpeechBubble->Unlock();


}
//=============================
//吹き出しUIの終了処理
//=============================
void UninitSpeechBubble(void)
{
	//StopSound(SOUND_LABEL_SE_SHOT);
	//StopSound(SOUND_LABEL_SE_EXPLOSIONBOMB);
	for (int i = 0; i < TEXNUM; i++)
	{
		//テクスチャの破棄
		if (g_pTextureSpeechBubble[i] != NULL)
		{
			g_pTextureSpeechBubble[i]->Release();
			g_pTextureSpeechBubble[i] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffSpeechBubble != NULL)
	{
		g_pVtxBuffSpeechBubble->Release();
		g_pVtxBuffSpeechBubble = NULL;
	}
}
//=============================
//吹き出しUIの更新処理
//=============================
void UpdateSpeechBubble(void)
{
	
	VERTEX_3D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSpeechBubble->Lock(0, 0, (void**)&pVtx, 0);

	for (int nSpeechBubble = 0; nSpeechBubble < NUMSPEECHBUBBLE; nSpeechBubble++)
	{
		if (g_SpeechBubble[nSpeechBubble].bUse == true)
		{

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-(g_SpeechBubble[nSpeechBubble].nBubbleCnt) * XMAG, g_SpeechBubble[nSpeechBubble].nBubbleCnt* XMAG2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_SpeechBubble[nSpeechBubble].nBubbleCnt * XMAG, g_SpeechBubble[nSpeechBubble].nBubbleCnt* XMAG2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-(g_SpeechBubble[nSpeechBubble].nBubbleCnt) * XMAG, -(g_SpeechBubble[nSpeechBubble].nBubbleCnt* XMAG2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_SpeechBubble[nSpeechBubble].nBubbleCnt * XMAG, -(g_SpeechBubble[nSpeechBubble].nBubbleCnt* XMAG2), 0.0f);

			//頂点座標の設定
			//pVtx[0].pos = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
			//pVtx[1].pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
			//pVtx[2].pos = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);
			//pVtx[3].pos = D3DXVECTOR3(10.0f, -10.0f, 0.0f);

		
			g_SpeechBubble[nSpeechBubble].bTrackingPlayer1 = false;

			g_SpeechBubble[nSpeechBubble].bTrackingPlayer2 = false;
		}

		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffSpeechBubble->Unlock();

}
//=============================
//吹き出しUIの描画処理
//=============================
void DrawSpeechBubble(int CameraLoopNum)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX  mtxTrans;//計算用マトリックス
	D3DXMATRIX mtxView;//ビューマトリックスの取得

	for (int nSpeechBubble = 0; nSpeechBubble < NUMSPEECHBUBBLE; nSpeechBubble++)
	{
		if (g_SpeechBubble[nSpeechBubble].bUse == true)
		{
			//ライトを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			////Zの比較変更
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			//Zバッファに書き込まない
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);



			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble);

			//向きを反映
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_SpeechBubble[nSpeechBubble].rotSpeechBubble.y, g_SpeechBubble[nSpeechBubble].rotSpeechBubble.x, g_SpeechBubble[nSpeechBubble].rotSpeechBubble.z);

			//D3DXMatrixMultiply(&g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble, &g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble, &mtxRot);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble, NULL, &mtxView);//逆行鉄を求める

			g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble._41 = 0.0f;
			g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble._42 = 0.0f;
			g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble._43 = 0.0f;


			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_SpeechBubble[nSpeechBubble].pos.x, g_SpeechBubble[nSpeechBubble].pos.y, g_SpeechBubble[nSpeechBubble].pos.z);

			D3DXMatrixMultiply(&g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble, &g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_SpeechBubble[nSpeechBubble].mtxWorldSpeechBubble);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffSpeechBubble, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			int Escape = static_cast<int>(g_SpeechBubble[nSpeechBubble].BubbleSType);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureSpeechBubble[Escape]);

			//テクスチャの設定
//			pDevice->SetTexture(0, NULL);
			
			//吹き出しUIの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				nSpeechBubble * 4,//描画する最初の頂点インデックス
				2);//描画するプリミティブ数

			//ライトを有効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			//Zの比較変更
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			//Zバッファに書き込まない
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

			
			//テクスチャを戻す
			pDevice->SetTexture(0, NULL);
			g_SpeechBubble[nSpeechBubble].bOK = false;
		}
	}
}
//=============================
//吹き出しUIの取得処理
//=============================

SPEECHBUBBLE* GetSpeechBubble(void)
{
	return &g_SpeechBubble[0];
}

//=============================
//吹き出しUIの設定処理
//=============================
void SetSpeechBubble(D3DXVECTOR3 Pos, int ActionIndex, int SetType, D3DXVECTOR3 CorrectionValue, SPEECHBUBBLETYPE UI_TYPE, int PlayerIndex)
{//壁の設定-------------------------------SetNum[登録番号--かぶらぬように]---[SetType-0が出現、１が縮小]

	if (g_SpeechBubble[ActionIndex].bOK == false)
	{
	//	if (UI_TYPE== SPEECHBUBBLETYPE_GAMECLEAR)
	//	{
	//		UI_TYPE = SPEECHBUBBLETYPE_TRANCE;
	//	}

		if (SetType == 0)
		{//拡大
			if (g_SpeechBubble[ActionIndex].bTrackingPlayer1 == false && PlayerIndex == 0)
			{
				g_SpeechBubble[ActionIndex].pos = D3DXVECTOR3(Pos.x, Pos.y, Pos.z);//位置
				g_SpeechBubble[ActionIndex].pos += CorrectionValue;
				g_SpeechBubble[ActionIndex].BubbleSType = UI_TYPE;
				g_SpeechBubble[ActionIndex].bTrackingPlayer1 = true;
			}
			else if (g_SpeechBubble[ActionIndex].bTrackingPlayer2 == false && PlayerIndex == 1)
			{
				g_SpeechBubble[ActionIndex].pos = D3DXVECTOR3(Pos.x, Pos.y, Pos.z);//位置
				g_SpeechBubble[ActionIndex].pos += CorrectionValue;
				g_SpeechBubble[ActionIndex].BubbleSType = UI_TYPE;
				g_SpeechBubble[ActionIndex].bTrackingPlayer2 = true;
			}



			g_SpeechBubble[ActionIndex].bUse = true;

			g_SpeechBubble[ActionIndex].nBubbleCnt += ZOOMSPEED;
			g_SpeechBubble[ActionIndex].bOK = true;

		}
		else if (SetType == 1)
		{//縮小
			g_SpeechBubble[ActionIndex].nBubbleCnt -= REDSPEED;
		}
	}





	if (g_SpeechBubble[ActionIndex].nBubbleCnt < 0)
	{
		g_SpeechBubble[ActionIndex].bOK = false;
		g_SpeechBubble[ActionIndex].nBubbleCnt = 0;
	}
	if (g_SpeechBubble[ActionIndex].nBubbleCnt > 30)
	{
		g_SpeechBubble[ActionIndex].nBubbleCnt = 30;
	}
}


