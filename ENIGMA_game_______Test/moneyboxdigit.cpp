//=========================================================
//
//ポーズ画面で使う変数、宣言、構造体[moneyboxdigit.cpp]
// Author matsuda towa
//
//=========================================================
#include "moneyboxdigit.h"
#include "moneybox.h"
#include "password.h"
#include "input.h"
#include "model.h"
#include "keyinfo.h"
#include "Actionzone.h"
#include "speechbubble.h"
#include "sound.h"
#include "player.h"
#include "player2.h"
//=========================================================
//グローバル変数
//=========================================================
LPDIRECT3DTEXTURE9 g_pTextureMoneyboxDigit[NUM_DIGIT] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMoneyboxDigit = NULL;//頂点バッファへのポリゴン
MONEYBOXDIGIT g_aMoneyboxDigit[NUM_DIGIT];	//ポーズ構造体の情報
int g_nSelectNumber;						//選択してる数字
int g_nMark; //選択してるマーク
bool g_bClear; //クリアしたかの判定
bool g_Open = false;//あいたか判別
int g_CloseCnt = 140;//画面閉じるまでの猶予

//=============================================
//壁のテクスチャの種類
//=============================================
static const char* MONEYBOXDIGIT_TEX_NAME[NUM_DIGIT] =
{
	"data\\TEXTURE\\dial000.png",
	"data\\TEXTURE\\dial001.png",
	"data\\TEXTURE\\dial002.png",
	"data\\TEXTURE\\dial003.png",
};

//=========================================================
//初期化
//=========================================================
void InitMoneyboxDigit(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	g_Open = false;
	g_CloseCnt = 100;
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			MONEYBOXDIGIT_TEX_NAME[nCnt],
			&g_pTextureMoneyboxDigit[nCnt]
		);
	}

	g_nSelectNumber = 0; //選択してる番号の初期化
	g_nMark = 0;//選択してる番号の初期化
	g_bClear = false;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_DIGIT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMoneyboxDigit, NULL);

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMoneyboxDigit->Lock(0, 0, (void**)&pVtx, 0);

	int nCnt = 0;

	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		g_aMoneyboxDigit[nCnt].pos = D3DXVECTOR3(SCREEN_WIDE / 4.0f, (SCREEN_HEIGHT / 1.25f), 0.0f);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x - SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x + SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x - SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x + SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テキスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffMoneyboxDigit->Unlock();
}

//=========================================================
//終了
//=========================================================
void UninitMoneyboxDigit(void)
{
	int nCnt = 0;

	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureMoneyboxDigit[nCnt] != NULL)
		{
			g_pTextureMoneyboxDigit[nCnt]->Release();
			g_pTextureMoneyboxDigit[nCnt] = NULL;
		}
		//頂点バッファの破棄
		if (g_pVtxBuffMoneyboxDigit != NULL)
		{
			g_pVtxBuffMoneyboxDigit->Release();
			g_pVtxBuffMoneyboxDigit = NULL;
		}
	}
}

//=========================================================
//更新
//=========================================================
void UpdateMoneyboxDigit(void)
{
	MONEYBOX* pMoneybox = GetMoneybox();

	if (pMoneybox->WhichPlayer == false)
	{
		ControlMoneybox1P();
	}
	else if (pMoneybox->WhichPlayer == true)
	{
		ControlMoneybox2P();
	}





}

//=========================================================
//1Pの操作
//=========================================================
void ControlMoneybox1P(void)
{
	XINPUT_STATE joykeystate;

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMoneyboxDigit->Lock(0, 0, (void**)&pVtx, 0);

//	int nCountPause = 0;

	DWORD dwResult = XInputGetState(0, &joykeystate);

	if (dwResult == ERROR_SUCCESS)
	{
		if (GetkeyboardTrigger(DIK_A) == true || GetJoypadTrigger(JOYKEY_LEFT, 0) == true || GetkeyboardTrigger(DIK_LEFT))
		{//Aがおされた(←)
			g_nSelectNumber--;
			if (g_nSelectNumber < 0)
			{
				g_nSelectNumber = NUM_DIGIT - 1;
			}

		}
		else if (GetkeyboardTrigger(DIK_D) == true || GetJoypadTrigger(JOYKEY_RIGHT, 0) == true || GetkeyboardTrigger(DIK_RIGHT))
		{//Dがおされた(→)

			g_nSelectNumber++;
			if (g_nSelectNumber >= NUM_DIGIT)
			{
				g_nSelectNumber = 0;
			}
		}
	}
	else
	{//コントローラーがなかったとき
		if (GetkeyboardTrigger(DIK_A) == true || GetkeyboardTrigger(DIK_LEFT))
		{//Aがおされた(←)
			g_nSelectNumber--;
			if (g_nSelectNumber < 0)
			{
				g_nSelectNumber = NUM_DIGIT - 1;
			}

		}
		else if (GetkeyboardTrigger(DIK_D) == true || GetkeyboardTrigger(DIK_RIGHT))
		{//Dがおされた(→)
			g_nSelectNumber++;
			if (g_nSelectNumber >= NUM_DIGIT)
			{
				g_nSelectNumber = 0;
			}
		}
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (g_nSelectNumber == 0)
		{
			if (nCnt == 0)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
			}
		}
		else if (g_nSelectNumber == 1)
		{
			if (nCnt == 1)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
			}

		}
		else if (g_nSelectNumber == 2)
		{
			if (nCnt == 2)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
			}
		}
		else if (g_nSelectNumber == 3)
		{
			if (nCnt == 3)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
			}
		}

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMoneyboxDigit->Unlock();

	ChangePassword1P(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_nSelectNumber);
}

//=========================================================
//2Pの操作
//=========================================================
void ControlMoneybox2P(void)
{
	XINPUT_STATE joykeystate;

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMoneyboxDigit->Lock(0, 0, (void**)&pVtx, 0);

//	int nCountPause = 0;

	DWORD dwResult = XInputGetState(0, &joykeystate);

	if (dwResult == ERROR_SUCCESS)
	{
		if (GetkeyboardTrigger(DIK_A) == true || GetJoypadTrigger(JOYKEY_LEFT, 1) == true || GetkeyboardTrigger(DIK_LEFT))
		{//Aがおされた(←)
			g_nSelectNumber--;
			if (g_nSelectNumber < 0)
			{
				g_nSelectNumber = NUM_DIGIT - 1;
			}

		}
		else if (GetkeyboardTrigger(DIK_D) == true || GetJoypadTrigger(JOYKEY_RIGHT, 1) == true || GetkeyboardTrigger(DIK_RIGHT))
		{//Dがおされた(→)

			g_nSelectNumber++;
			if (g_nSelectNumber >= NUM_DIGIT)
			{
				g_nSelectNumber = 0;
			}
		}
	}
	else
	{//コントローラーがなかったとき
		if (GetkeyboardTrigger(DIK_A) == true || GetkeyboardTrigger(DIK_LEFT))
		{//Aがおされた(←)
			g_nSelectNumber--;
			if (g_nSelectNumber < 0)
			{
				g_nSelectNumber = NUM_DIGIT - 1;
			}

		}
		else if (GetkeyboardTrigger(DIK_D) == true || GetkeyboardTrigger(DIK_RIGHT))
		{//Dがおされた(→)
			g_nSelectNumber++;
			if (g_nSelectNumber >= NUM_DIGIT)
			{
				g_nSelectNumber = 0;
			}
		}
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (g_nSelectNumber == 0)
		{
			if (nCnt == 0)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
			}
		}
		else if (g_nSelectNumber == 1)
		{
			if (nCnt == 1)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
			}

		}
		else if (g_nSelectNumber == 2)
		{
			if (nCnt == 2)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
			}
		}
		else if (g_nSelectNumber == 3)
		{
			if (nCnt == 3)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f);
			}
		}

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMoneyboxDigit->Unlock();

	ChangePassword2P(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_nSelectNumber);
}

//=========================================================
//描画
//=========================================================
void DrawMoneyboxDigit(void)
{

	//しゃあなしでここ
	if (g_Open == true)
	{
		if (g_CloseCnt > 0)
		{
			g_CloseCnt--;
		}

		if (g_CloseCnt <= 0)
		{//猶予過ぎた
			Player* pPlayer;
			pPlayer = GetPlayer();

			Player_2P* pPlayer2;
			pPlayer2 = GetPlayer_2P();

			pPlayer->bMoneyBoxGimmick = false;
			pPlayer2->bMoneyBoxGimmick = false;
		}
	}


	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();//----------------書き換え済み

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMoneyboxDigit, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);//-------書き換え済み

	int nCnt = 0;

	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureMoneyboxDigit[nCnt]);//---------書き換え済み

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類//----------書き換え済み
			nCnt * 4,//描画する最初の頂点インデックス
			2);//描画するプリミティブ数

		
		//テクスチャを戻す
		pDevice->SetTexture(0, NULL);
	}
}

//=========================================================
//どっちが操作してるのかの設定
//=========================================================
void SetMoneyboxDigit(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	MONEYBOX* pMoneybox = GetMoneybox();

	if (pMoneybox->WhichPlayer == false)
	{//1Pの時
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_DIGIT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMoneyboxDigit, NULL);

		VERTEX_2D* pVtx;//頂点情報のポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffMoneyboxDigit->Lock(0, 0, (void**)&pVtx, 0);

		int nCnt = 0;

		for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
		{
			g_aMoneyboxDigit[nCnt].pos = D3DXVECTOR3(SCREEN_WIDE / 4.0f + 53.0f, (SCREEN_HEIGHT / 1.25f), 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x - SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x + SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x - SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x + SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);

			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テキスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;
		}
		//頂点バッファをアンロックする
		g_pVtxBuffMoneyboxDigit->Unlock();
	}
	else if (pMoneybox->WhichPlayer == true)
	{//2Pの時
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_DIGIT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMoneyboxDigit, NULL);

		VERTEX_2D* pVtx;//頂点情報のポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffMoneyboxDigit->Lock(0, 0, (void**)&pVtx, 0);

		int nCnt = 0;

		for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
		{
			g_aMoneyboxDigit[nCnt].pos = D3DXVECTOR3(SCREEN_WIDE / 1.3f + 53.0f, (SCREEN_HEIGHT / 1.25f), 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x - SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x + SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y - SCREEN_HEIGHT / 5.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x - SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMoneyboxDigit[nCnt].pos.x + SCREEN_WIDE / 5.0f, g_aMoneyboxDigit[nCnt].pos.y + SCREEN_HEIGHT / 5.0f, 0.0f);

			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テキスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;
		}
		//頂点バッファをアンロックする
		g_pVtxBuffMoneyboxDigit->Unlock();
	}

}

//=========================================================
//成功処理
//=========================================================
void CorrectMoneyboxDigit(void)
{

	VERTEX_2D* pVtx;//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMoneyboxDigit->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx += 4;
	}

	//ここでアイテム獲得処理
	SetModel(D3DXVECTOR3(-700.0f, 70.0f, -450.0f),
	D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
	MODELTYPE_KEY2);

	SetKeyinfo(SPAWNPLACE_BASEMENT, -1);

	PlaySound(SOUND_LABEL_SE_OPEN);

	//クリアした判定をしてもう金庫に触れられないようにする
	g_bClear = true;

	g_pVtxBuffMoneyboxDigit->Unlock();


	ACTIONZONE* pActionZone;
	pActionZone = GetActionZone();
	SPEECHBUBBLE* pSpeachBubble = GetSpeechBubble();

	for (int nCntZone = 0; nCntZone < MAXZONE; nCntZone++)
	{
		if (pActionZone[nCntZone].bUse == true)
		{
			if (pActionZone[nCntZone].ActionType == ACTION_TYPE_MONEYBOX)
			{
				pActionZone[nCntZone].bUse = false;
				pSpeachBubble[nCntZone].bUse = false;
				pSpeachBubble[nCntZone].bOK = false;			//	break;
				break;
			}
		}
	}
	g_Open = true;
}

//=========================================================
//失敗処理
//=========================================================
void MistakeMoneyboxDigit(void)
{
	//SEで不正解を表す
	PlaySound(SOUND_LABEL_SE_NOTOPEN);
}

//=========================================================
//クリア情報取得
//=========================================================
bool GetClearMoneyBox(void)
{
	return g_bClear;
}

