//==================================================
//
//ゲーム内フェードに関する処理[GameFade.cpp]
// Author seiya kagaya
//
//==================================================
#include "main.h"
#include "gamefade.h"
#include "player.h"
#include "player2.h"
#include "camera.h"
#include "shadow.h"
//#include "sound.h"

//グローバル変数宣言
GAMEFADE g_GameFade[MAXGAMEFADE];
D3DXCOLOR g_colorGameFade[MAXGAMEFADE];
//MODE g_ModeNext;
LPDIRECT3DTEXTURE9 g_pTextureGameFade = NULL;       //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameFade = NULL; //頂点バッファへのポインタ

//int g_GameFadeCnt[MAXGAMEFADE] = {};//ゲーム画面への移行時かすかに色が残る問題を対策

D3DXVECTOR3 g_EscapeMove[MAXGAMEFADE];
D3DXVECTOR3 g_EscapeRot_Camera[MAXGAMEFADE];
D3DXVECTOR3 g_EscapeRot_Player[MAXGAMEFADE];

bool g_CrossRoadTrans[MAXGAMEFADE] = {};

bool g_PlayerBlack = false;
bool g_Player2Black = false;

bool g_GameClear = false;
int g_GoalNum = 0;//ゴール人数

bool g_PlayerGoal = false;
bool g_Player2Goal = false;
//=============================
//ゲーム内フェードの初期化処理
//=============================
void InitGameFade(void)
{
	g_PlayerGoal = false;
	g_Player2Goal = false;

	g_GoalNum = 0;

	LPDIRECT3DDEVICE9 pDevice;  //デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*MAXGAMEFADE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameFade,
		NULL);



	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ki.jpg", &g_pTextureGameFade);	//タイトル背景

	VERTEX_2D* pVtx;  //頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGameFade->Lock(0, 0, (void**)&pVtx, 0);

	g_GameClear = false;

	for (int FadeCnt = 0; FadeCnt < MAXGAMEFADE; FadeCnt++)
	{
		g_EscapeMove[FadeCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EscapeRot_Camera[FadeCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EscapeRot_Player[FadeCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_CrossRoadTrans[FadeCnt] = false;
		//変数の初期化
		g_colorGameFade[FadeCnt].a = 0.0f;

		g_GameFade[FadeCnt] = GAMEFADE_NONE;

		//g_GameFadeCnt[FadeCnt] = 0;

		if (FadeCnt == 0)
		{//カメラ1のいち
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDE/2.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDE/2.0f, SCREEN_HEIGHT, 0.0f);
		}
		else if(FadeCnt==1)
		{//カメラ2のいち
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDE/2.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDE, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDE/2.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDE, SCREEN_HEIGHT, 0.0f);
		}




		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		//テクスチャ座標を設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下


		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffGameFade->Unlock();
}
//=============================
//ゲーム内フェードの終了処理
//=============================
void UninitGameFade(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuffGameFade != NULL)
	{
		g_pVtxBuffGameFade->Release();
		g_pVtxBuffGameFade = NULL;
	}
	//テクスチャの破棄
	if (g_pTextureGameFade != NULL)
	{
		g_pTextureGameFade->Release();
		g_pTextureGameFade = NULL;
	}
}
//=============================
//ゲーム内フェードの更新処理
//=============================
void UpdateGameFade(void)
{
	VERTEX_2D* pVtx;  //頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGameFade->Lock(0, 0, (void**)&pVtx, 0);

	Player* pPlayer;
	pPlayer = GetPlayer();

	Player_2P* pPlayer2;
	pPlayer2 = GetPlayer_2P();

	Camera* pCamera;
	pCamera = GetCamera();

	for (int FadeCnt = 0; FadeCnt < MAXGAMEFADE; FadeCnt++)
	{
		if (g_GameFade[FadeCnt] != GAMEFADE_NONE)
		{
			if (g_GameFade[FadeCnt] == GAMEFADE_IN)
			{//ゲーム内フェードイン状態

				g_colorGameFade[FadeCnt].a -= 0.03f;	//ポリゴンを透明にしていく

				if (g_colorGameFade[FadeCnt].a <= 0.0f)
				{
					g_colorGameFade[FadeCnt].a = 0.0f;


					g_GameFade[FadeCnt] = GAMEFADE_NONE;	//何もしていない状態
				}
			}
			else if (g_GameFade[FadeCnt] == GAMEFADE_OUT)
			{//ゲーム内フェードアウト状態
				g_colorGameFade[FadeCnt].a += 0.07f;	//ポリゴンを不透明にしていく

				if (g_PlayerGoal == false || g_Player2Goal == false)
				{
					if (g_colorGameFade[FadeCnt].a >= 1.0f)
					{
						g_colorGameFade[FadeCnt].a = 1.0f;

						//	g_GameFadeCnt[FadeCnt]++;//モード移行カウンター

						if (FadeCnt == 0)
						{
							pPlayer->pos = g_EscapeMove[FadeCnt];
							pCamera[0].rot.x = 0.0f;
							pCamera[0].rot.z = 0.0f;

							pCamera[0].rot.y = g_EscapeRot_Camera[FadeCnt].y;


							pPlayer->rot = g_EscapeRot_Player[FadeCnt];
							if (g_CrossRoadTrans[0] == true)
							{
								TRansNumPlayerUP();
							}
							pPlayer->PlayerState = PLAYERSTATE_1P_NOMAL;

							if (g_PlayerGoal == false)
							{
								g_GameFade[FadeCnt] = GAMEFADE_IN;	//ゲーム内フェードイン状態
							}
							else
							{
								if (g_colorGameFade[FadeCnt].a >= 1.0f)
								{
									if (g_PlayerGoal == true)
									{
										pPlayer->pos = g_EscapeMove[FadeCnt];
										PlayerUpdateStop();
										g_colorGameFade[FadeCnt].a = 1.0f;
										EndProcessShadow(pPlayer->nldShadow);
									}
									if (g_PlayerGoal == true && g_Player2Goal == true)
									{//二人以上転移完了したら

										GameClear();//Clearに
									}
								}
							}
						}
						else if (FadeCnt == 1)
						{
							pPlayer2->pos = g_EscapeMove[FadeCnt];
							pCamera[1].rot.x = 0.0f;
							pCamera[1].rot.z = 0.0f;
							pCamera[1].rot.y = g_EscapeRot_Camera[FadeCnt].y;

							pPlayer2->rot = g_EscapeRot_Player[FadeCnt];
			
							if (g_CrossRoadTrans[1] == true)
							{
								TRansNumPlayer2UP();
							}
							pPlayer2->PlayerState = PLAYERSTATE_2P_NOMAL;

							if (g_Player2Goal == false)
							{
								g_GameFade[FadeCnt] = GAMEFADE_IN;	//ゲーム内フェードイン状態
							}
							else
							{
								if (g_colorGameFade[FadeCnt].a >= 1.0f)
								{
									
									if (g_Player2Goal == true)
									{
										pPlayer2->pos = g_EscapeMove[FadeCnt];
										Player2UpdateStop();
										g_colorGameFade[FadeCnt].a = 1.0f;
										EndProcessShadow(pPlayer2->nldShadow);
									}

									if (g_PlayerGoal == true && g_Player2Goal == true)
									{//二人以上転移完了したら

										GameClear();//Clearに
									}
								}
							}
						}

						
					}
				}
				else
				{
					if (g_PlayerGoal == true)
					{//二人以上転移完了したら
						pPlayer->pos = g_EscapeMove[FadeCnt];
						EndProcessShadow(pPlayer->nldShadow);
						PlayerUpdateStop();
						
					}
					if (g_Player2Goal == true)
					{
						pPlayer2->pos = g_EscapeMove[FadeCnt];
						EndProcessShadow(pPlayer2->nldShadow);
						Player2UpdateStop();
					}

					if (g_PlayerGoal == true && g_Player2Goal == true)
					{
						GameClear();//Clearに
					}
				}
			}

			if (FadeCnt == 0)
			{//カメラ1のいち
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDE / 2.0f, 0.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDE / 2.0f, SCREEN_HEIGHT, 0.0f);

			}
			else if (FadeCnt == 1)
			{//カメラ2のいち
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDE / 2.0f, 0.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDE, 0.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDE / 2.0f, SCREEN_HEIGHT, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDE, SCREEN_HEIGHT, 0.0f);
			}


			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorGameFade[FadeCnt].a);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorGameFade[FadeCnt].a);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorGameFade[FadeCnt].a);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorGameFade[FadeCnt].a);


			pVtx += 4;
		}
	}
	//頂点バッファのアンロック
	g_pVtxBuffGameFade->Unlock();

	
}
//=============================
//ゲーム内フェードの描画処理
//=============================
void DrawGameFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGameFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int FadeCnt = 0; FadeCnt < MAXGAMEFADE; FadeCnt++)
	{
//		if (g_GameFade[FadeCnt] != GAMEFADE_NONE)
//		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureGameFade);//---------書き換え済み

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, FadeCnt * 4, 2);
//		}
			
		
	}
	//テクスチャを戻す
			pDevice->SetTexture(0, NULL);
}
//=============================
//ゲーム内フェードの設定処理
//=============================
void SetGameFade(int PlayerNum, D3DXVECTOR3 ESCAPEMOVE, D3DXVECTOR3 EscapeRot_Camera, D3DXVECTOR3 EscapeRot_Player, bool GameClear,bool CrossRoadTrans)
{
	if (g_GameFade[PlayerNum] == GAMEFADE_NONE)
	{
		//	g_colorGameFade[PlayerNum].a = 0.0f;
		//	g_GameFadeCnt[PlayerNum] = 0;
		g_colorGameFade[PlayerNum] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);			//黒いポリゴン(透明)にしておく
		g_GameFade[PlayerNum] = GAMEFADE_OUT;											//ゲーム内フェードアウト状態に
		g_EscapeMove[PlayerNum] = ESCAPEMOVE;//移動量
		g_EscapeRot_Camera[PlayerNum] = EscapeRot_Camera;
		g_EscapeRot_Player[PlayerNum] = EscapeRot_Player;
		g_CrossRoadTrans[PlayerNum] = CrossRoadTrans;
		//	g_ModeNext = mode_next;										//次の画面(モード)を設定

	}


	if (GameClear == true)
	{
		if (g_PlayerGoal==true&& PlayerNum==0)
		{
			return;
		}
		if (g_Player2Goal == true && PlayerNum == 1)
		{
			return;
		}

		if (PlayerNum == 0)
		{//1P
			g_PlayerGoal = true;

		//	g_GoalNum++;
		}
		else if (PlayerNum == 1)
		{//1P
			g_Player2Goal = true;

		//	g_GoalNum++;
		}


	}

	if (g_PlayerGoal==true && g_Player2Goal==true)
	{//二人以上ゴールしたら
		g_GameClear = true;
	}
}
//=============================
//ゲーム内フェードの取得処理
//=============================
GAMEFADE GetGameFade(void)
{
	return g_GameFade[0];
}
