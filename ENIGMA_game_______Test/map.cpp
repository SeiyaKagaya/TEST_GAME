//============================================================================================
//
//マップUI表示する処理[result.cpp]
// Author seiya kagaya
//
//============================================================================================
//#include "item.h"
#include "map.h"
#include "game.h"
#include "particle.h"
#include "input.h"
#include "player.h"
#include "camera.h"
#include "player2.h"
#include "text.h"
#include "menu.h"


//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureMap[MAPTEXUINUM] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMap = NULL;//頂点バッファへのポリゴン

MAP g_Map[MAXMAP];

//描画可能か(アップデートで変動・描画で使用)
bool g_DrawOK2[2] = {};//三番目だけ常にture

D3DXVECTOR2 g_UVpos[2];//ピンのみ　

const char* g_Comment[5] = {};//Commentを格納

//=============================
//マップUIの初期化処理
//=============================
void InitMap(void)
{
	g_DrawOK2[0] = false;
	g_DrawOK2[1] = false;

	g_UVpos[0] = D3DXVECTOR2(0.5f, 0.5f);//UV上の位置
	g_UVpos[1] = D3DXVECTOR2(0.5f, 0.5f);//UV上の位置

	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	int nCntMap;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PlayerPin.png", &g_pTextureMap[0]);//プレイヤーピン
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Map0.png", &g_pTextureMap[1]);//地図//十字路
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Map1.png", &g_pTextureMap[2]);//地図//倉庫
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Map2.png", &g_pTextureMap[3]);//地図//リビング
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Map3.png", &g_pTextureMap[4]);//地図//浴室
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Map4.png", &g_pTextureMap[5]);//地図//ちゅーとりある
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\MapFrame2.png", &g_pTextureMap[6]);//枠

	//マップ名
	g_Comment[0] = "      匣";
	g_Comment[1] = "     倉庫";
	g_Comment[2] = "  リビング";
	g_Comment[3] = "     浴室";
	g_Comment[4] = "　  マップ";


	//マップUIの情報の初期化(いわゆる初期地点)
	for (nCntMap = 0; nCntMap < MAXMAP; nCntMap++)
	{
		g_Map[nCntMap].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Map[nCntMap].UItype = MAP_UI_TYPE_MAX;
		g_Map[nCntMap].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Map[nCntMap].ScreenNum = -1;
		g_Map[nCntMap].PosNum = -1;
		//対角線の長さを算出
		g_Map[nCntMap].fLength = sqrtf(MAPPINSIZE2 * MAPPINSIZE2 + MAPPINSIZE2 * MAPPINSIZE2) / 2.0f;//幅*幅+高さ*高さ

		//対角線の角度を算出
		g_Map[nCntMap].fAngle = atan2f(MAPPINSIZE2, MAPPINSIZE2);//高さ、幅

		g_Map[nCntMap].bUse = false;//使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAXMAP, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMap, NULL);

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMap->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntMap = 0; nCntMap < MAXMAP; nCntMap++)
	{
		//頂点座標の更新-----------------------------------
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;//値は固定
		pVtx[1].rhw = 1.0f;//値は固定
		pVtx[2].rhw = 1.0f;//値は固定
		pVtx[3].rhw = 1.0f;//値は固定

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

		pVtx += 4;//頂点のポインタを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffMap->Unlock();

	//地図
	SetMap(D3DXVECTOR3(SCREEN_WIDE * 0.4f, SCREEN_HEIGHT * 0.78f, 0.0f), MAP_UI_TYPE_MAP1, 0);
	//地図
	SetMap(D3DXVECTOR3(SCREEN_WIDE * 0.9f, SCREEN_HEIGHT * 0.78f, 0.0f), MAP_UI_TYPE_MAP1, 1);

	//左
	SetMap(D3DXVECTOR3(SCREEN_WIDE * 0.4f, SCREEN_HEIGHT * 0.78f, 0.0f), MAP_UI_TYPE_PLAYERPIN_1P_0, 0);

	//右
	SetMap(D3DXVECTOR3(SCREEN_WIDE * 0.9f, SCREEN_HEIGHT * 0.78f, 0.0f), MAP_UI_TYPE_PLAYERPIN_2P_1, 1);

	//縁
	SetMap(D3DXVECTOR3(SCREEN_WIDE * 0.4f, SCREEN_HEIGHT * 0.78f, 0.0f), MAP_UI_TYPE_MAPFRAME, 0);

	SetMap(D3DXVECTOR3(SCREEN_WIDE * 0.9f, SCREEN_HEIGHT * 0.78f, 0.0f), MAP_UI_TYPE_MAPFRAME, 1);


}
//=============================
//マップUIの終了処理
//=============================
void UninitMap(void)
{
	for (int i = 0; i < MAPTEXUINUM; i++)
	{
		//テクスチャの破棄
		if (g_pTextureMap[i] != NULL)
		{
			g_pTextureMap[i]->Release();
			g_pTextureMap[i] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffMap != NULL)
	{
		g_pVtxBuffMap->Release();
		g_pVtxBuffMap = NULL;
	}
}
//=============================
//マップUIの更新処理
//=============================
void UpdateMap(bool Draw1OK, bool Draw2OK)
{
	Player* pPlayer;
	pPlayer = GetPlayer();

	Player_2P* pPlayer2;
	pPlayer2 = GetPlayer_2P();

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMap->Lock(0, 0, (void**)&pVtx, 0);

	g_DrawOK2[0] = Draw1OK;
	g_DrawOK2[1] = Draw2OK;



	for (int nCntMap = 0; nCntMap < MAXMAP; nCntMap++)
	{
		if (g_Map[nCntMap].bUse == true)
		{//マップUIが使用されている

	D3DXVECTOR2 EscapeUV;

			switch (g_Map[nCntMap].UItype)
			{
			case MAP_UI_TYPE_PLAYERPIN_1P_0:

				EscapeUV.x = -pPlayer->pos.x * MOVESIZE;
				EscapeUV.y = pPlayer->pos.z * MOVESIZE;

				g_UVpos[0] = EscapeUV;//UV上の位置//------------------------------------初期スポーン分ずらす必要あり
				
				g_Map[nCntMap].rot.z = -pPlayer->rot.y;

					//頂点座標の更新-----------------------------------
				pVtx[0].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左上
				pVtx[0].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左上
				pVtx[0].pos.z = 0.0f;

				pVtx[1].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右上
				pVtx[1].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右上
				pVtx[1].pos.z = 0.0f;

				pVtx[2].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左下
				pVtx[2].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左下
				pVtx[2].pos.z = 0.0f;

				pVtx[3].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右下
				pVtx[3].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右下
				pVtx[3].pos.z = 0.0f;

				//テクスチャ座標を設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下

				break;

			case MAP_UI_TYPE_PLAYERPIN_2P_1:

				EscapeUV.x =-pPlayer2->pos.x * MOVESIZE;
				EscapeUV.y = pPlayer2->pos.z * MOVESIZE;

				g_UVpos [1]= EscapeUV;//UV上の位置//------------------------------------初期スポーン分ずらす必要あり

				g_Map[nCntMap].rot.z = -pPlayer2->rot.y;

					//頂点座標の更新-----------------------------------
				pVtx[0].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左上
				pVtx[0].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左上
				pVtx[0].pos.z = 0.0f;

				pVtx[1].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右上
				pVtx[1].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右上
				pVtx[1].pos.z = 0.0f;

				pVtx[2].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左下
				pVtx[2].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左下
				pVtx[2].pos.z = 0.0f;

				pVtx[3].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右下
				pVtx[3].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右下
				pVtx[3].pos.z = 0.0f;

				//テクスチャ座標を設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下

				break;


	
			case MAP_UI_TYPE_PLAYERPIN_2P_0://相手
				
				g_Map[nCntMap].rot.z = -pPlayer2->rot.y;


					//頂点座標の更新-----------------------------------
				pVtx[0].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左上
				pVtx[0].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左上
				pVtx[0].pos.z = 0.0f;

				pVtx[1].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右上
				pVtx[1].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右上
				pVtx[1].pos.z = 0.0f;

				pVtx[2].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左下
				pVtx[2].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左下
				pVtx[2].pos.z = 0.0f;

				pVtx[3].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右下
				pVtx[3].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右下
				pVtx[3].pos.z = 0.0f;

				//テクスチャ座標を設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下

				break;

			case MAP_UI_TYPE_PLAYERPIN_1P_1://相手

				g_Map[nCntMap].rot.z = -pPlayer->rot.y;

					//頂点座標の更新-----------------------------------
				pVtx[0].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左上
				pVtx[0].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左上
				pVtx[0].pos.z = 0.0f;

				pVtx[1].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右上
				pVtx[1].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右上
				pVtx[1].pos.z = 0.0f;

				pVtx[2].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左下
				pVtx[2].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左下
				pVtx[2].pos.z = 0.0f;

				pVtx[3].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右下
				pVtx[3].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右下
				pVtx[3].pos.z = 0.0f;

				//テクスチャ座標を設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下
				
				break;

			case MAP_UI_TYPE_MAP1:
				
				g_UVpos[0] += MAP0_START_POS_0;
				g_UVpos[1] += MAP1_START_POS_0;

				//テクスチャ座標を設定
				pVtx[0].tex = D3DXVECTOR2(g_UVpos[g_Map[nCntMap].ScreenNum].x - UVSize,g_UVpos[g_Map[nCntMap].ScreenNum].y - UVSize);//左上
				pVtx[1].tex = D3DXVECTOR2(g_UVpos[g_Map[nCntMap].ScreenNum].x + UVSize,g_UVpos[g_Map[nCntMap].ScreenNum].y - UVSize);//右上
				pVtx[2].tex = D3DXVECTOR2(g_UVpos[g_Map[nCntMap].ScreenNum].x - UVSize,g_UVpos[g_Map[nCntMap].ScreenNum].y + UVSize);//左下
				pVtx[3].tex = D3DXVECTOR2(g_UVpos[g_Map[nCntMap].ScreenNum].x + UVSize,g_UVpos[g_Map[nCntMap].ScreenNum].y + UVSize);//右下
				
				break;
			}
		}
		pVtx += 4;//頂点のポインタを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffMap->Unlock();
}
//=============================
//マップUIの描画処理
//=============================
void DrawMap(void)
{
	Player* pPlayer;
	pPlayer = GetPlayer();

	Player_2P* pPlayer2;
	pPlayer2 = GetPlayer_2P();
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	int SelectTexMap1 = GetTRansNumPlayer();
	int SelectTexMap2 = GetTRansNumPlayer2();

	int nCntMap = 0;//マップ番号
	int MenutoGame=0;//チュートリアル識別

	//mapの番号退避用
	int Escape1 = 0;
	int Escape2 = 0;

	//Comment番号
	int ComentIndex = 0;
	int ComentIndex2 = 0;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMap, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);//-------書き換え済み
	for (nCntMap = 0; nCntMap < MAXMAP; nCntMap++)
	{
		if (g_Map[nCntMap].bUse == true)
		{//マップUIが使用されている
			//テクスチャインデックス
			int SelectTex = 0;
			int SelectTex2 = 0;


			switch (g_Map[nCntMap].UItype)
			{
			case MAP_UI_TYPE_PLAYERPIN_1P_0:
				SelectTex = 0;
				break;

			case MAP_UI_TYPE_PLAYERPIN_2P_0:
				SelectTex = 0;
				break;


			case MAP_UI_TYPE_PLAYERPIN_1P_1:
				SelectTex = 0;
				break;

			case MAP_UI_TYPE_PLAYERPIN_2P_1:
				SelectTex = 0;
				break;

			case MAP_UI_TYPE_MAP1:

				if (nCntMap==0)
				{//左地図
					switch (SelectTexMap1)
					{//転移先検知(部屋)
					case 3://初期値
						SelectTex = 3;//リビング
						break;
					case 4://倉庫下
						SelectTex = 2;//倉庫
						break;
					case 5://浴室
						SelectTex = 4;//浴室
						break;
					case 6://リビング下
						SelectTex = 3;//リビング
						break;
					case 7://倉庫左
						SelectTex = 2;//倉庫
						break;
					case 8://リビング階段
						SelectTex = 3;//リビング
						break;
					}

					if (pPlayer->CrossRoadNow==true)
					{//十字路のとき
						SelectTex = 1;
					}


					//メニューからどのモードを選んだか取得
					MenutoGame = GetMenu1();

					if (MenutoGame != START_MENU_GAME)
					{//メニューで「チュートリアル」を選んだ場合
						SelectTex = 5;//チュートリアルステージ
					}


					Escape1 = SelectTex;//保存
				}
				else if (nCntMap == 1)
				{//右地図
					switch (SelectTexMap2)
					{//転移先検知(部屋)
					case 3://初期値
						SelectTex2 = 3;//リビング
						break;
					case 4://倉庫下
						SelectTex2 = 2;//倉庫
						break;
					case 5://浴室
						SelectTex2 = 4;//浴室
						break;
					case 6://リビング下
						SelectTex2 = 3;//リビング
						break;
					case 7://倉庫左
						SelectTex2 = 2;//倉庫
						break;
					case 8://リビング階段
						SelectTex2 = 3;//リビング
						break;
					}

					if (pPlayer2->CrossRoadNow == true)
					{//十字路のとき
						SelectTex2 = 1;
					}

					//メニューからどのモードを選んだか取得
					MenutoGame = GetMenu1();

					if (MenutoGame != START_MENU_GAME)
					{//メニューで「チュートリアル」を選んだ場合
						SelectTex2 = 5;//チュートリアルステージ
					}

					Escape2 = SelectTex2;//位置ように保存

					SelectTex = SelectTex2;//描画用統合
				}
				
				break;

			case MAP_UI_TYPE_MAPFRAME:

				SelectTex =6;
				break;
	
			}

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureMap[SelectTex]);//---------書き換え済み


			if (g_DrawOK2[g_Map[nCntMap].ScreenNum] == true)
			{
				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
					nCntMap * 4,//描画する最初の頂点インデックス
					2);//描画するプリミティブ数

				
				//テクスチャを戻す
				pDevice->SetTexture(0, NULL);
			}
		}
	}

	//switch (Escape1)//左地図のテクスチャIndex
	//{
	//case 1://十字路
	//	break;
	//case 2://倉庫
	//	break;
	//case 3://リビング
	//	break;
	//case 4://浴室
	//	break;
	//case 5://チュートリアル
	//	break;
	//}

	//switch (Escape2)//右地図のテクスチャIndex
	//{
	//case 1://十字路
	//	break;
	//case 2://倉庫
	//	break;
	//case 3://リビング
	//	break;
	//case 4://浴室
	//	break;
	//case 5://チュートリアル
	//	break;
	//}
	
	//インデックスを変換
	ComentIndex = (Escape1 - 1);
	ComentIndex2 = (Escape2 - 1);
	
	//g_Comment[ComentIndex];

	DrawTextSet(D3DXVECTOR3(SCREEN_WIDE * 0.35, 457.0f, 0.0f), 30, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "%s",g_Comment[ComentIndex]);


	DrawTextSet(D3DXVECTOR3(SCREEN_WIDE * 0.85, 457.0f, 0.0f), 30, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "%s", g_Comment[ComentIndex2]);
}
//=============================
//マップUIの設定処理
//=============================
void SetMap(D3DXVECTOR3 pos, MAP_UI_TYPE MAPType,int ScreenNum)
{//他のところでも呼ぶ可能性があるのでこのままのほうが便利

	VERTEX_2D* pVtx;//頂点情報のポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMap->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMap = 0; nCntMap < MAXMAP; nCntMap++)
	{
		if (g_Map[nCntMap].bUse == false)
		{//マップUIが使用されていない

			g_Map[nCntMap].bUse = true;//使用してるにする

			g_Map[nCntMap].pos = pos;
			g_Map[nCntMap].UItype = MAPType;

			g_Map[nCntMap].ScreenNum = ScreenNum;


				switch (MAPType)
				{
				case MAP_UI_TYPE_PLAYERPIN_1P_0:
					//頂点座標の更新-----------------------------------
					pVtx[0].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左上
					pVtx[0].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左上
					pVtx[0].pos.z = 0.0f;

					pVtx[1].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右上
					pVtx[1].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右上
					pVtx[1].pos.z = 0.0f;

					pVtx[2].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左下
					pVtx[2].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左下
					pVtx[2].pos.z = 0.0f;

					pVtx[3].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右下
					pVtx[3].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右下
					pVtx[3].pos.z = 0.0f;

					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

					//テクスチャ座標を設定
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下

					break;

				case MAP_UI_TYPE_PLAYERPIN_2P_0:
					
					//頂点座標の更新-----------------------------------
					pVtx[0].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左上
					pVtx[0].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左上
					pVtx[0].pos.z = 0.0f;

					pVtx[1].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右上
					pVtx[1].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右上
					pVtx[1].pos.z = 0.0f;

					pVtx[2].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左下
					pVtx[2].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左下
					pVtx[2].pos.z = 0.0f;

					pVtx[3].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右下
					pVtx[3].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右下
					pVtx[3].pos.z = 0.0f;

					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(0, 0, 255, 150);
					pVtx[1].col = D3DCOLOR_RGBA(0, 0, 255, 150);
					pVtx[2].col = D3DCOLOR_RGBA(0, 0, 255, 150);
					pVtx[3].col = D3DCOLOR_RGBA(0, 0, 255, 150);

					//テクスチャ座標を設定
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下

					break;


				case MAP_UI_TYPE_PLAYERPIN_1P_1:

					//頂点座標の更新-----------------------------------
					pVtx[0].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle +  g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左上
					pVtx[0].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle +  g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左上
					pVtx[0].pos.z = 0.0f;

					pVtx[1].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle -  g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右上
					pVtx[1].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle -  g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右上
					pVtx[1].pos.z = 0.0f;

					pVtx[2].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle -  g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左下
					pVtx[2].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle -  g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左下
					pVtx[2].pos.z = 0.0f;

					pVtx[3].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle +  g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右下
					pVtx[3].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle +  g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右下
					pVtx[3].pos.z = 0.0f;

					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 150);
					pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 150);
					pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 150);
					pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 150);

					//テクスチャ座標を設定
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下

					break;

				case MAP_UI_TYPE_PLAYERPIN_2P_1:

					//頂点座標の更新-----------------------------------
					pVtx[0].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左上
					pVtx[0].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左上
					pVtx[0].pos.z = 0.0f;

					pVtx[1].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右上
					pVtx[1].pos.y = g_Map[nCntMap].pos.y - cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右上
					pVtx[1].pos.z = 0.0f;

					pVtx[2].pos.x = g_Map[nCntMap].pos.x - sinf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左下
					pVtx[2].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle - g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//左下
					pVtx[2].pos.z = 0.0f;

					pVtx[3].pos.x = g_Map[nCntMap].pos.x + sinf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右下
					pVtx[3].pos.y = g_Map[nCntMap].pos.y + cosf(g_Map[nCntMap].fAngle + g_Map[nCntMap].rot.z) * g_Map[nCntMap].fLength;//右下
					pVtx[3].pos.z = 0.0f;

					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(0, 0, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(0, 0, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(0, 0, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(0, 0, 255, 255);

					//テクスチャ座標を設定
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下

					break;

				case MAP_UI_TYPE_MAP1:
					//頂点座標の更新-----------------------------------
					pVtx[0].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x - ((SCREEN_WIDE* ADDMAP_2)* ADDMAP), g_Map[nCntMap].pos.y - ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x + ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), g_Map[nCntMap].pos.y - ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x - ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), g_Map[nCntMap].pos.y + ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x + ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), g_Map[nCntMap].pos.y + ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), 0.0f);

					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);


						//テクスチャ座標を設定
					pVtx[0].tex = D3DXVECTOR2(g_UVpos[0].x - UVSize, g_UVpos[0].y - UVSize);//左上
					pVtx[1].tex = D3DXVECTOR2(g_UVpos[0].x + UVSize, g_UVpos[0].y - UVSize);//右上
					pVtx[2].tex = D3DXVECTOR2(g_UVpos[0].x - UVSize, g_UVpos[0].y + UVSize);//左下
					pVtx[3].tex = D3DXVECTOR2(g_UVpos[0].x + UVSize, g_UVpos[0].y + UVSize);//右下

					break;


				case MAP_UI_TYPE_MAPFRAME:
					//頂点座標の更新-----------------------------------
					pVtx[0].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x - ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), g_Map[nCntMap].pos.y - ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x + ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), g_Map[nCntMap].pos.y - ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x - ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), g_Map[nCntMap].pos.y + ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x + ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), g_Map[nCntMap].pos.y + ((SCREEN_WIDE * ADDMAP_2) * ADDMAP), 0.0f);

					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

					//テクスチャ座標を設定
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下


					

					break;

				//case MAP_UI_TYPE_MAP2:

				//	//頂点座標の更新-----------------------------------
				//	pVtx[0].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x - ((SCREEN_WIDE * 0.5f) * ADDMAP), g_Map[nCntMap].pos.y - ((SCREEN_WIDE * 0.5f) * ADDMAP), 0.0f);
				//	pVtx[1].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x + ((SCREEN_WIDE * 0.5f) * ADDMAP), g_Map[nCntMap].pos.y - ((SCREEN_WIDE * 0.5f) * ADDMAP), 0.0f);
				//	pVtx[2].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x - ((SCREEN_WIDE * 0.5f) * ADDMAP), g_Map[nCntMap].pos.y + ((SCREEN_WIDE * 0.5f) * ADDMAP), 0.0f);
				//	pVtx[3].pos = D3DXVECTOR3(g_Map[nCntMap].pos.x + ((SCREEN_WIDE * 0.5f) * ADDMAP), g_Map[nCntMap].pos.y + ((SCREEN_WIDE * 0.5f) * ADDMAP), 0.0f);

				//	//頂点カラーの設定
				//	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
				//	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
				//	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
				//	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);

				//	//テクスチャ座標を設定
				//	pVtx[0].tex = D3DXVECTOR2(g_UVpos[g_Map[nCntMap].ScreenNum].x - UVSize, g_UVpos[g_Map[nCntMap].ScreenNum].y - UVSize);//左上
				//	pVtx[1].tex = D3DXVECTOR2(g_UVpos[g_Map[nCntMap].ScreenNum].x + UVSize, g_UVpos[g_Map[nCntMap].ScreenNum].y - UVSize);//右上
				//	pVtx[2].tex = D3DXVECTOR2(g_UVpos[g_Map[nCntMap].ScreenNum].x - UVSize, g_UVpos[g_Map[nCntMap].ScreenNum].y + UVSize);//左下
				//	pVtx[3].tex = D3DXVECTOR2(g_UVpos[g_Map[nCntMap].ScreenNum].x + UVSize, g_UVpos[g_Map[nCntMap].ScreenNum].y + UVSize);//右下
				//	
				//	break;
				}

				


		
			break;
		}
		pVtx += 4;//ポインタを４つ進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffMap->Unlock();
}

