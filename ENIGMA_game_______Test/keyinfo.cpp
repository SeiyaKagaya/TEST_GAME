//=============================================
//
//鍵出現UI[keyinfo.h]
//Auther Matsuda Towa
//
//=============================================
#include "keyinfo.h"
#include "game.h"
#include "text.h"

//=============================================
//マクロ定義
//=============================================
#define SCREEN_TIME	(140) //継続時間
#define KEYINFO_WIDE	(520) //継続時間
#define KEYINFO_HIGHT	(40) //継続時間

//=============================================
//グローバル変数宣言
//=============================================
LPDIRECT3DTEXTURE9 g_pTextureKeyinfo = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffKeyinfo = NULL;//頂点バッファへのポリゴン
Keyinfo g_Keyinfo;

//=============================================
//初期化
//=============================================
void InitKeyinfo(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

//デバイスの取得
	pDevice = GetDevice();

	//	int nCntPause = 0;

		//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\keyinfoframe.png",
		&g_pTextureKeyinfo
	);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffKeyinfo, NULL);

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffKeyinfo->Lock(0, 0, (void**)&pVtx, 0);

	g_Keyinfo.bUse = false;

	g_Keyinfo.fAlpha = 1.0f;
	g_Keyinfo.nScreenCnt = 0;
	g_Keyinfo.pos = D3DXVECTOR3(SCREEN_WIDE / 2.0f, SCREEN_HEIGHT / 1.95f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Keyinfo.pos.x - KEYINFO_WIDE, g_Keyinfo.pos.y - KEYINFO_HIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Keyinfo.pos.x + KEYINFO_WIDE, g_Keyinfo.pos.y - KEYINFO_HIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Keyinfo.pos.x - KEYINFO_WIDE, g_Keyinfo.pos.y + KEYINFO_HIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Keyinfo.pos.x + KEYINFO_WIDE, g_Keyinfo.pos.y + KEYINFO_HIGHT, 0.0f);
		
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);

	//テキスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffKeyinfo->Unlock();
}

//=============================================
//終了
//=============================================
void UninitKeyinfo(void)
{
	//テクスチャの破棄
	if (g_pTextureKeyinfo != NULL)
	{
		g_pTextureKeyinfo->Release();
		g_pTextureKeyinfo = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffKeyinfo != NULL)
	{
		g_pVtxBuffKeyinfo->Release();
		g_pVtxBuffKeyinfo = NULL;
	}
}

//=============================================
//更新
//=============================================
void UpdateKeyinfo(void)
{
	if (g_Keyinfo.bUse == true)
	{
		g_Keyinfo.nScreenCnt++;
		if (g_Keyinfo.nScreenCnt >= SCREEN_TIME)
		{
			VERTEX_2D* pVtx;//頂点情報のポインタ

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffKeyinfo->Lock(0, 0, (void**)&pVtx, 0);

			g_Keyinfo.fAlpha -= 0.1f;

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);


			if (g_Keyinfo.fAlpha <= 0.0f)
			{
				g_Keyinfo.fAlpha = 0.0f;
				g_Keyinfo.nScreenCnt = 0;
				g_Keyinfo.bUse = false;
			}
		}

	}
	
	g_pVtxBuffKeyinfo->Unlock();
}

//=============================================
//描画
//=============================================
void DrawKeyinfo(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

//デバイスの取得
	pDevice = GetDevice();//----------------書き換え済み


	if (g_Keyinfo.bUse == true)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffKeyinfo, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);//-------書き換え済み

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureKeyinfo);//---------書き換え済み

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類//----------書き換え済み
			0,//描画する最初の頂点インデックス
			2);//描画するプリミティブ数

		//テクスチャを戻す
		pDevice->SetTexture(0, NULL);

		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_REMOCON)
		{
			DrawTVinfo();
		}
		else if (g_Keyinfo.nSpawnPlace == NOT_HAVE_DISH 
			|| g_Keyinfo.nSpawnPlace == NOT_HAVE_VEGETABLE
			||g_Keyinfo.nSpawnPlace == NOT_HAVE_NEED_KITCHEN)
		{
			DrawKitcheninfo();
		}
		else if (g_Keyinfo.nSpawnPlace == NOT_HAVE_SOUP)
		{
			DrawDeskinfo();//机
		}
		else if (g_Keyinfo.nSpawnPlace == PUSH_CREEN)
		{
			DrawKeyinfoCreen();//浄化装置
		}
		else if (g_Keyinfo.nSpawnPlace == SPAWNPLACE_GATE)
		{
			DrawKeyinfoGate();
		}
		else if (g_Keyinfo.nSpawnPlace == MISSMONEYBOX)
		{
			DrawKeyinfoMoneyBox();
		}
		else if (g_Keyinfo.nSpawnPlace == TAKE_A_BATH)
		{
			DrawKeyinfoBath();
		}
		else if (g_Keyinfo.nSpawnPlace == SPAWN_DISH)
		{
			DrawKeyinfoDish();
		}
		else
		{
			DrawKeyinfoText();
		}
	}
	
}

//=============================================
//テキスト表示
//=============================================
void DrawTVinfo(void)
{
	if (g_Keyinfo.nPlayerIdx == 0)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "リモコンが無いため操作できない");
	}
	else if (g_Keyinfo.nPlayerIdx == 1)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f,  0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "リモコンが無いため操作できない");
	}
}

//=============================================
//テキスト表示
//=============================================
void DrawKitcheninfo(void)
{
	if (g_Keyinfo.nPlayerIdx == 0)
	{
		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_DISH)
		{
			DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "皿が無いため調理できない");
		}
		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_VEGETABLE)
		{
			DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "野菜が無いため調理できない");
		}
		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_NEED_KITCHEN)
		{
			DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "皿と野菜が無いため調理できない");
		}
	}
	else if (g_Keyinfo.nPlayerIdx == 1)
	{
		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_DISH)
		{
			DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "皿が無いため調理できない");
		}
		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_VEGETABLE)
		{
			DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "野菜が無いため調理できない");
		}
		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_NEED_KITCHEN)
		{
			DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "皿と野菜が無いため調理できない");
		}
	}
}
//=============================================
//テキスト表示
//=============================================
void DrawDeskinfo(void)
{
	if (g_Keyinfo.nPlayerIdx == 0)
	{
		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_SOUP)
		{
			DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "スープが無いため机に置けない");
		}
		
	}
	else if (g_Keyinfo.nPlayerIdx == 1)
	{
		if (g_Keyinfo.nSpawnPlace == NOT_HAVE_SOUP)
		{
			DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "スープが無いため机に置けない");
		}
	}
}

//=============================================
//テキスト表示
//=============================================
void DrawKeyinfoText(void)
{
	if (g_Keyinfo.nSpawnPlace == SPAWNPLACE_LIVING)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 3.25f, SCREEN_HEIGHT / 2.12f, 0.0f), 55, FONT_GENSIN, D3DXCOLOR(0.1f,1.0f, 0.0f, 1.0f), "リビングに鍵が出現した");
	}
	if (g_Keyinfo.nSpawnPlace == SPAWNPLACE_BASEMENT)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.6f, SCREEN_HEIGHT / 2.12f, 0.0f), 55, FONT_GENSIN, D3DXCOLOR(0.1f, 1.0f, 0.0f, 1.0f), "地下室に鍵が出現した");
	}
	if (g_Keyinfo.nSpawnPlace == SPAWNPLACE_BATHROOM)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.6f, SCREEN_HEIGHT / 2.12f, 0.0f), 55, FONT_GENSIN, D3DXCOLOR(0.1f, 1.0f, 0.0f, 1.0f), "お風呂場に鍵が出現した");
	}
}
//=============================================
//テキスト表示--浄化装置
//=============================================
void DrawKeyinfoCreen(void)//浄化装置テキスト
{
	if (g_Keyinfo.nPlayerIdx == 0)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "浴槽ろ過装置が起動した");
	}
	else if (g_Keyinfo.nPlayerIdx == 1)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "浴槽ろ過装置が起動した");
	}
	else
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.9f, SCREEN_HEIGHT / 2.12f, 0.0f), 55, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "浴槽ろ過装置が起動した");
	}
}
//=============================================
//テキスト表示--/出門出現
//=============================================
void DrawKeyinfoGate(void)
{
	if (g_Keyinfo.nPlayerIdx == 0)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), "リビングに何かが起きた");
	}
	else if (g_Keyinfo.nPlayerIdx == 1)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), "リビングに何かが起きた");
	}
	else
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.9f, SCREEN_HEIGHT / 2.12f, 0.0f), 55, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), "リビングに何かが起きた");
	}
}
//=============================================
//テキスト表示--/金庫失敗
//=============================================
void DrawKeyinfoMoneyBox(void)
{
	if (g_Keyinfo.nPlayerIdx == 0)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), "    パスワードが違うようだ");
	}
	else if (g_Keyinfo.nPlayerIdx == 1)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), "     パスワードが違うようだ");
	}
	else
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.9f, SCREEN_HEIGHT / 2.12f, 0.0f), 55, FONT_GENSIN, D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), "     パスワードが違うようだ");
	}
}
//=============================================
//テキスト表示--/風呂抜いた
//=============================================
void DrawKeyinfoBath(void)
{
	if (g_Keyinfo.nPlayerIdx == 0)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 11.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "   底からリモコンが出てきた");
	}
	else if (g_Keyinfo.nPlayerIdx == 1)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.7f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "    底からリモコンが出てきた");
	}
	else
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 2.9f, SCREEN_HEIGHT / 2.12f, 0.0f), 55, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "    底からリモコンが出てきた");
	}
}

//=============================================
//テキスト表示--/皿湧いた
//=============================================
void DrawKeyinfoDish(void)
{
	if (g_Keyinfo.nPlayerIdx == 0)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 7.5f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "   皿が出てきた");
	}
	else if (g_Keyinfo.nPlayerIdx == 1)
	{
		DrawTextSet(D3DXVECTOR3(SCREEN_WIDE / 1.52f, SCREEN_HEIGHT / 2.05f, 0.0f), 35, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "    皿が出てきた");
	}
}

//=============================================
//設定
//=============================================
void SetKeyinfo(KeySpawnPlace nSpawnPlace,int PlayerIdx)
{
	if (g_Keyinfo.bUse == false)
	{
		g_Keyinfo.nPlayerIdx = PlayerIdx;
		g_Keyinfo.fAlpha = 0.7f;
		g_Keyinfo.nScreenCnt = 0;
		g_Keyinfo.nSpawnPlace = nSpawnPlace;
		g_Keyinfo.bUse = true;
		VERTEX_2D* pVtx;//頂点情報のポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffKeyinfo->Lock(0, 0, (void**)&pVtx, 0);
		if (g_Keyinfo.nPlayerIdx == -1)
		{//全プレイヤーに
			g_Keyinfo.pos = D3DXVECTOR3(SCREEN_WIDE / 2.0f, SCREEN_HEIGHT / 1.95f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_Keyinfo.pos.x - KEYINFO_WIDE, g_Keyinfo.pos.y - KEYINFO_HIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Keyinfo.pos.x + KEYINFO_WIDE, g_Keyinfo.pos.y - KEYINFO_HIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Keyinfo.pos.x - KEYINFO_WIDE, g_Keyinfo.pos.y + KEYINFO_HIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Keyinfo.pos.x + KEYINFO_WIDE, g_Keyinfo.pos.y + KEYINFO_HIGHT, 0.0f);
		}
		else if (g_Keyinfo.nPlayerIdx == 0)
		{//全プレイヤーに
			g_Keyinfo.pos = D3DXVECTOR3(SCREEN_WIDE / 4.0f, SCREEN_HEIGHT / 1.95f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_Keyinfo.pos.x - KEYINFO_WIDE / 1.75f, g_Keyinfo.pos.y - KEYINFO_HIGHT / 1.75f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Keyinfo.pos.x + KEYINFO_WIDE / 1.75f, g_Keyinfo.pos.y - KEYINFO_HIGHT / 1.75f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Keyinfo.pos.x - KEYINFO_WIDE / 1.75f, g_Keyinfo.pos.y + KEYINFO_HIGHT / 1.75f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Keyinfo.pos.x + KEYINFO_WIDE / 1.75f, g_Keyinfo.pos.y + KEYINFO_HIGHT / 1.75f, 0.0f);
		}
		else if (g_Keyinfo.nPlayerIdx == 1)
		{//全プレイヤーに
			g_Keyinfo.pos = D3DXVECTOR3(SCREEN_WIDE / 1.33f, SCREEN_HEIGHT / 1.95f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_Keyinfo.pos.x - KEYINFO_WIDE / 1.75f, g_Keyinfo.pos.y - KEYINFO_HIGHT / 1.75f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Keyinfo.pos.x + KEYINFO_WIDE / 1.75f, g_Keyinfo.pos.y - KEYINFO_HIGHT / 1.75f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Keyinfo.pos.x - KEYINFO_WIDE / 1.75f, g_Keyinfo.pos.y + KEYINFO_HIGHT / 1.75f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Keyinfo.pos.x + KEYINFO_WIDE / 1.75f, g_Keyinfo.pos.y + KEYINFO_HIGHT / 1.75f, 0.0f);
		}
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Keyinfo.fAlpha);
		g_pVtxBuffKeyinfo->Unlock();

	}
}

