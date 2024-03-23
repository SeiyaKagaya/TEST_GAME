//=========================================================
//
//ポーズ画面で使う変数、宣言、構造体[moneybox.cpp]
// Author matsuda towa
//
//=========================================================
#include "moneybox.h"
#include "moneyboxdigit.h"
#include "password.h"
#include "text.h"

//=========================================================
//グローバル変数
//=========================================================
LPDIRECT3DTEXTURE9 g_pTextureMoneybox = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMoneybox = NULL;//頂点バッファへのポリゴン
MONEYBOX g_Moneybox;	//ポーズ構造体の情報
//=============================================
//壁のテクスチャの種類
//=============================================
static const char* MONEYBOX_TEX_NAME =
{
	"data\\TEXTURE\\safe000.png",
};

//=========================================================
//初期化
//=========================================================
void InitMoneybox(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

//デバイスの取得
	pDevice = GetDevice();

//	int nCntPause = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		MONEYBOX_TEX_NAME,
		&g_pTextureMoneybox
	);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMoneybox, NULL);

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMoneybox->Lock(0, 0, (void**)&pVtx, 0);

	g_Moneybox.pos = D3DXVECTOR3(SCREEN_WIDE / 4.0f, (SCREEN_HEIGHT/1.25f), 0.0f);
	g_Moneybox.WhichPlayer = false; //false:1P,true2P

	//頂点座標の設定

	pVtx[0].pos = D3DXVECTOR3(g_Moneybox.pos.x - SCREEN_WIDE/5.0f, g_Moneybox.pos.y - SCREEN_HEIGHT/5.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Moneybox.pos.x + SCREEN_WIDE/5.0f, g_Moneybox.pos.y - SCREEN_HEIGHT/5.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Moneybox.pos.x - SCREEN_WIDE/5.0f, g_Moneybox.pos.y + SCREEN_HEIGHT/5.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Moneybox.pos.x + SCREEN_WIDE/5.0f, g_Moneybox.pos.y + SCREEN_HEIGHT/5.0f, 0.0f);
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テキスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffMoneybox->Unlock();
}

//=========================================================
//終了
//=========================================================
void UninitMoneybox(void)
{
	//テクスチャの破棄
	if (g_pTextureMoneybox != NULL)
	{
		g_pTextureMoneybox->Release();
		g_pTextureMoneybox = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffMoneybox != NULL)
	{
		g_pVtxBuffMoneybox->Release();
		g_pVtxBuffMoneybox = NULL;
	}
}

//=========================================================
//更新
//=========================================================
void UpdateMoneybox(void)
{
}
//=========================================================
//描画
//=========================================================
void DrawMoneybox(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();//----------------書き換え済み

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMoneybox, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);//-------書き換え済み

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMoneybox);//---------書き換え済み

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類//----------書き換え済み
		0,//描画する最初の頂点インデックス
		2);//描画するプリミティブ数
	
	
	//テクスチャを戻す
	pDevice->SetTexture(0, NULL);

	if (g_Moneybox.WhichPlayer == false)
	{//1Pの時
		DrawTextSet(D3DXVECTOR3(g_Moneybox.pos.x-365.0f, g_Moneybox.pos.y + 100.0f,0.0f), 21, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), "Aボタン:解錠");
	}
	else if (g_Moneybox.WhichPlayer == true)
	{//2Pの時
		DrawTextSet(D3DXVECTOR3(g_Moneybox.pos.x-265.0f, g_Moneybox.pos.y + 100.0f, 0.0f), 21, FONT_GENSIN, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), "Aボタン:解錠");
	}
}

//=========================================================
//どっちが操作してるのかの設定
//=========================================================
void SetMonetbox(bool MoneyboxPlayer)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	g_Moneybox.WhichPlayer = MoneyboxPlayer;
	if (g_Moneybox.WhichPlayer == false)
	{//1Pの時
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMoneybox, NULL);

		VERTEX_2D* pVtx;//頂点情報のポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffMoneybox->Lock(0, 0, (void**)&pVtx, 0);

		g_Moneybox.pos = D3DXVECTOR3(SCREEN_WIDE / 4.0f + 53.0f, (SCREEN_HEIGHT / 1.25f), 0.0f);
		//頂点座標の設定

		pVtx[0].pos = D3DXVECTOR3(g_Moneybox.pos.x - SCREEN_WIDE / 5.0f, g_Moneybox.pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Moneybox.pos.x + SCREEN_WIDE / 5.0f, g_Moneybox.pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Moneybox.pos.x - SCREEN_WIDE / 5.0f, g_Moneybox.pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Moneybox.pos.x + SCREEN_WIDE / 5.0f, g_Moneybox.pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テキスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_pVtxBuffMoneybox->Unlock();
	}
	else if (g_Moneybox.WhichPlayer == true)
	{//1Pの時
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMoneybox, NULL);

		VERTEX_2D* pVtx;//頂点情報のポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffMoneybox->Lock(0, 0, (void**)&pVtx, 0);

		g_Moneybox.pos = D3DXVECTOR3(SCREEN_WIDE/1.3f + 53.0f, (SCREEN_HEIGHT / 1.25f), 0.0f);
		//頂点座標の設定

		pVtx[0].pos = D3DXVECTOR3(g_Moneybox.pos.x - SCREEN_WIDE / 5.0f , g_Moneybox.pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Moneybox.pos.x + SCREEN_WIDE / 5.0f , g_Moneybox.pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Moneybox.pos.x - SCREEN_WIDE / 5.0f , g_Moneybox.pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Moneybox.pos.x + SCREEN_WIDE / 5.0f , g_Moneybox.pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テキスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_pVtxBuffMoneybox->Unlock();
	}
	SetMoneyboxDigit();
	SetPassword();
}

//=========================================================
//金庫の情報取得
//=========================================================
MONEYBOX* GetMoneybox(void)
{
	return &g_Moneybox;
}
