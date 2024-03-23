//=========================================================
//
//壁を表示する処理[wall.cpp]
// Author seiya kagaya
//
//=========================================================
#include "main.h"
#include "stage.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStage = NULL; //頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureStage[TEXTYPE_MAX] = {};       //テクスチャへのポインタ



//D3DXVECTOR3 g_Stage[nWall].posStage;	//位置
//D3DXVECTOR3 g_Stage[nWall].rotStage;	//向き
//D3DXMATRIX g_Stage[nWall].mtxWorldStage;//ワールドマトリックス


STAGE g_Stage[NUMSTAGE];//制作中　構造体



//=============================
//壁の初期化処理
//=============================
void InitStage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wallflower.jpg", &g_pTextureStage[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\concrete.jpg", &g_pTextureStage[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\blood.jpg", &g_pTextureStage[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wallgrain.jpg", &g_pTextureStage[3]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\safe000.png", &g_pTextureStage[4]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\JHOUKA.png", &g_pTextureStage[5]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cookinfo.png", &g_pTextureStage[6]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BlackCat.png", &g_pTextureStage[7]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\CupboardDish.png", &g_pTextureStage[8]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BathGimi.png", &g_pTextureStage[9]);

	//ここにテクスチャを追加したらヘッダにも増やすこと!!!!//

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * NUMSTAGE, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffStage, NULL);

		VERTEX_3D* pVtx;//頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);

	for (int nWall = 0; nWall < NUMSTAGE; nWall++)
	{
		//g_Stage[nWall].g_Stage[nWall].posStage
		//g_Stage[nWall].rotStage
		g_Stage[nWall].bUse = false;

		g_Stage[nWall].posStage = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置
		g_Stage[nWall].rotStage = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向き
		g_Stage[nWall].MaxPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//最大
		g_Stage[nWall].MinPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//最小
		g_Stage[nWall].bCollision = false;
		g_Stage[nWall].TexType = TEXTYPE_00;


		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-STAGESIZE, 100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(STAGESIZE, 100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-STAGESIZE, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(STAGESIZE, 0.0f, 0.0f);

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
	g_pVtxBuffStage->Unlock();

	//地下室-------------------------------------------------------------------------------------------------------------------------------------
	//天井
	SetStage(D3DXVECTOR3(-0700.0f, 0400.0f, -0600.0f), D3DXVECTOR3(-1.57f, +0.00f, 0.00f), 0800.0f, 0800.0f, TEXTYPE_01);//テスト仕様

	//壁
	SetStage(D3DXVECTOR3(-0900.0f, 0100.0f, +0110.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0600.0f, 0300.0f, TEXTYPE_01);//テスト仕様
	SetStage(D3DXVECTOR3(-0400.0f, 0100.0f, -0030.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0200.0f, 0300.0f, TEXTYPE_01);//テスト仕様
	SetStage(D3DXVECTOR3(-0150.0f, 0100.0f, -0230.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0250.0f, 0300.0f, TEXTYPE_01);//テスト仕様
	SetStage(D3DXVECTOR3(+0030.0f, 0100.0f, -0800.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0700.0f, 0300.0f, TEXTYPE_01);//テスト仕様
	SetStage(D3DXVECTOR3(-1200.0f, 0100.0f, -0600.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0750.0f, 0300.0f, TEXTYPE_01);//テスト仕様入って右スイッチ壁
	SetStage(D3DXVECTOR3(-0140.0f, 0100.0f, -1230.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0180.0f, 0300.0f, TEXTYPE_01);//テスト仕様
	SetStage(D3DXVECTOR3(-0320.0f, 0100.0f, -1330.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_01);//テスト仕様
	SetStage(D3DXVECTOR3(-1050.0f, 0100.0f, -1230.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0170.0f, 0300.0f, TEXTYPE_01);//テスト仕様
	SetStage(D3DXVECTOR3(-0880.0f, 0100.0f, -1330.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_01);//テスト仕様



	//十字路----------------------------------------------------------------------------------------------------------------------------------------
	//天井
	SetStage(D3DXVECTOR3(-0600.0f, 0300.0f, -2900.0f), D3DXVECTOR3(-1.57f, +0.00f, 0.00f), 1100.0f, 1000.0f, TEXTYPE_02);//テスト仕様スポーン地後

	//壁
	//スポーン地点、先
	SetStage(D3DXVECTOR3(-0600.0f, 0000.0f, -1890.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地後
	SetStage(D3DXVECTOR3(-0600.0f, 0000.0f, -3910.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地前
	SetStage(D3DXVECTOR3(+0450.0f, 0000.0f, -2900.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地左
	SetStage(D3DXVECTOR3(-1650.0f, 0000.0f, -2900.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地左

	//通路左右壁
	SetStage(D3DXVECTOR3(-0550.0f, 0000.0f, -2250.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地後左
	SetStage(D3DXVECTOR3(-0650.0f, 0000.0f, -2250.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地後右

	SetStage(D3DXVECTOR3(-0550.0f, 0000.0f, -3550.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地前左
	SetStage(D3DXVECTOR3(-0650.0f, 0000.0f, -3550.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地前右

	SetStage(D3DXVECTOR3(-1250.0f, 0000.0f, -2950.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地右前
	SetStage(D3DXVECTOR3(-1250.0f, 0000.0f, -2850.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地右後

	SetStage(D3DXVECTOR3(+0050.0f, 0000.0f, -2950.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地左前
	SetStage(D3DXVECTOR3(+0050.0f, 0000.0f, -2850.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地左後

	//中央部屋壁
	SetStage(D3DXVECTOR3(-0750.0f, 0000.0f, -2650.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地先右後
	SetStage(D3DXVECTOR3(-0450.0f, 0000.0f, -2650.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地先左後

	SetStage(D3DXVECTOR3(-0750.0f, 0000.0f, -3150.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地前右奥
	SetStage(D3DXVECTOR3(-0450.0f, 0000.0f, -3150.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地前左奥

	SetStage(D3DXVECTOR3(-0850.0f, 0000.0f, -2750.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地右手前
	SetStage(D3DXVECTOR3(-0350.0f, 0000.0f, -2750.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地左手前

	SetStage(D3DXVECTOR3(-0850.0f, 0000.0f, -3050.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地右奥
	SetStage(D3DXVECTOR3(-0350.0f, 0000.0f, -3050.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_02);//テスト仕様スポーン地左奥



	//水回り-------------------------------------------------------------------------------------------------------------------------------------
	//天井
	SetStage(D3DXVECTOR3(+3250.0f, 0200.0f, -0250.0f), D3DXVECTOR3(-1.57f, +0.00f, 0.00f), 0400.0f, 0400.0f, TEXTYPE_03);//テスト仕様

	//壁
	SetStage(D3DXVECTOR3(+3300.0f, 0000.0f, +0060.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_03);//テスト仕様スポーン地手前壁
	SetStage(D3DXVECTOR3(+3300.0f, 0000.0f, -0630.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_03);//テスト仕様
	SetStage(D3DXVECTOR3(+2900.0f, 0000.0f, -0300.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_03);//テスト仕様
	SetStage(D3DXVECTOR3(+3650.0f, 0000.0f, -0300.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_03);//テスト仕様
	SetStage(D3DXVECTOR3(+3500.0f, 0000.0f, -0400.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0250.0f, 0300.0f, TEXTYPE_03);//テスト仕様
	
	SetStage(D3DXVECTOR3(+3600.0f, 0000.0f, -0150.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_03);//テスト仕様
	
	SetStage(D3DXVECTOR3(+3550.0f, 0000.0f, -0050.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0150.0f, 0300.0f, TEXTYPE_03);//テスト仕様
	
	SetStage(D3DXVECTOR3(+3150.0f, 0000.0f, -0250.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0250.0f, 0300.0f, TEXTYPE_03);//テスト仕様
	SetStage(D3DXVECTOR3(+3150.0f, 0000.0f, -0250.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0250.0f, 0300.0f, TEXTYPE_03);//テスト仕様
	
	SetStage(D3DXVECTOR3(+3400.0f, 0000.0f, +0050.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0100.0f, 0300.0f, TEXTYPE_03);//テスト仕様
	
	SetStage(D3DXVECTOR3(+3500.0f, 0250.0f, -0050.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0100.0f, 0100.0f, TEXTYPE_03);//テスト仕様
	SetStage(D3DXVECTOR3(+3500.0f, 0250.0f, -0050.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0100.0f, 0100.0f, TEXTYPE_03);//テスト仕様
	
	SetStage(D3DXVECTOR3(+3200.0f, 0220.0f, -0454.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0200.0f, 0100.0f, TEXTYPE_03);//テスト仕様
	SetStage(D3DXVECTOR3(+3200.0f, 0220.0f, -0454.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0200.0f, 0100.0f, TEXTYPE_03);//テスト仕様
	
	//両面設置のためすり抜け
	SetStage(D3DXVECTOR3(+3200.0f, 0020.0f, -0327.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0075.0f, 0100.0f, TEXTYPE_03);//テスト仕様
	SetStage(D3DXVECTOR3(+3200.0f, 0020.0f, -0327.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0075.0f, 0100.0f, TEXTYPE_03);//テスト仕様
	
	//両面設置のためすり抜け
	SetStage(D3DXVECTOR3(+3200.0f, 0020.0f, -0590.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0075.0f, 0100.0f, TEXTYPE_03);//テスト仕様
	SetStage(D3DXVECTOR3(+3200.0f, 0020.0f, -0590.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0075.0f, 0100.0f, TEXTYPE_03);//テスト仕様
	


	//リビング--------------------------------------------------------------------------------------------------------------------------------------------
	//天井
	SetStage(D3DXVECTOR3(+3200.0f, 0300.0f, -1900.0f), D3DXVECTOR3(-1.57f, +0.00f, 0.00f), 0500.0f, 0700.0f, TEXTYPE_00);//テスト仕様

	//壁
	SetStage(D3DXVECTOR3(+3150.0f, 0100.0f, -1700.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0050.0f, 0200.0f, TEXTYPE_00);//テスト仕様入ってすぐの壁空間右側
	SetStage(D3DXVECTOR3(+3400.0f, 0100.0f, -1700.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0100.0f, 0200.0f, TEXTYPE_00);//テスト仕様入ってすぐの壁空間左側
	SetStage(D3DXVECTOR3(+3500.0f, 0100.0f, -1500.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0200.0f, 0200.0f, TEXTYPE_00);//テスト仕様入ってすぐの左側壁
	SetStage(D3DXVECTOR3(+3400.0f, 0100.0f, -1900.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0300.0f, 0200.0f, TEXTYPE_00);//テスト仕様入ってすぐの壁反対側
	SetStage(D3DXVECTOR3(+3100.0f, 0100.0f, -1800.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0100.0f, 0200.0f, TEXTYPE_00);//テスト仕様入ってすぐの壁反対側とのつなぎ横
	SetStage(D3DXVECTOR3(+3100.0f, 0100.0f, -1340.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0100.0f, 0200.0f, TEXTYPE_00);//テスト仕様入って左キッチンへの左
	SetStage(D3DXVECTOR3(+3300.0f, 0100.0f, -1300.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0200.0f, 0200.0f, TEXTYPE_00);//テスト仕様キッチン入り左壁

	SetStage(D3DXVECTOR3(+2750.0f, 0100.0f, -1900.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0700.0f, 0200.0f, TEXTYPE_00);//テスト仕様入って左キッチンへの左

	SetStage(D3DXVECTOR3(+2900.0f, 0100.0f, -1440.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0200.0f, 0200.0f, TEXTYPE_00);//テスト仕様キッチン入り左壁
	
	SetStage(D3DXVECTOR3(+3200.0f, 0100.0f, -2550.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0500.0f, 0200.0f, TEXTYPE_00);//テスト仕様キッチン入り左壁

	SetStage(D3DXVECTOR3(+3700.0f, 0100.0f, -2200.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0350.0f, 0200.0f, TEXTYPE_00);//テスト仕様入ってすぐの壁反対側とのつなぎ横

	SetStage(D3DXVECTOR3(+3250.0f, 0100.0f, -1800.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0100.0f, 0200.0f, TEXTYPE_01);//テスト仕様階段奥行き
	SetStage(D3DXVECTOR3(+3300.0f, 0100.0f, -1750.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0050.0f, 0200.0f, TEXTYPE_00);//テスト仕様階段
	SetStage(D3DXVECTOR3(+3200.0f, 0100.0f, -1750.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0050.0f, 0200.0f, TEXTYPE_00);//テスト仕様階段

	//床
	SetStage(D3DXVECTOR3(+3200.0f, 0100.0f, -1900.0f), D3DXVECTOR3(1.57f, +0.00f, 0.00f), 0500.0f, 0700.0f, TEXTYPE_03);//テスト仕様

	//チュートリアルルーム
	SetStage(D3DXVECTOR3(+3000.0f, 0000.0f, +2550.0f), D3DXVECTOR3(0.00f, +0.00f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_04);//テスト仕様
	SetStage(D3DXVECTOR3(+3000.0f, 0000.0f, +1050.0f), D3DXVECTOR3(0.00f, +3.14f, 0.00f), 0400.0f, 0300.0f, TEXTYPE_04);//テスト仕様
	SetStage(D3DXVECTOR3(+3400.0f, 0000.0f, +1800.0f), D3DXVECTOR3(0.00f, +1.57f, 0.00f), 0800.0f, 0300.0f, TEXTYPE_04);//テスト仕様
	SetStage(D3DXVECTOR3(+2600.0f, 0000.0f, +1800.0f), D3DXVECTOR3(0.00f, -1.57f, 0.00f), 0800.0f, 0300.0f, TEXTYPE_04);//テスト仕様

	//浄化Button
	SetStage(D3DXVECTOR3(-400.5f, 100.0f, -40.0f), D3DXVECTOR3(0.00f, 1.57f, 0.0f),50.0f,50.0f, TEXTYPE_05);//テスト仕様
	//料理教室
	SetStage(D3DXVECTOR3(3300.0f, 200.0f, -1301.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 30.0f, TEXTYPE_06);
	//皿案内
	SetStage(D3DXVECTOR3(-140.0f, 100.0f, -235.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 60.0f, TEXTYPE_08);
	//バスギミ案内
	SetStage(D3DXVECTOR3(3300.0f, 100.0f, -255.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f, 30.0f, TEXTYPE_09);


	//部屋ごとの壁
	SetStage(D3DXVECTOR3(1500.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 5000.0f, 1000.0f, TEXTYPE_07);
	SetStage(D3DXVECTOR3(1500.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f), 5000.0f, 1000.0f, TEXTYPE_07);

	SetStage(D3DXVECTOR3(1319.0f, 0.0f, 741.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5000.0f, 1000.0f, TEXTYPE_07);
	SetStage(D3DXVECTOR3(1319.0f, 0.0f, 741.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 5000.0f, 1000.0f, TEXTYPE_07);

	SetStage(D3DXVECTOR3(3290.0f, 0.0f, -930.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2000.0f, 1000.0f, TEXTYPE_07);
	SetStage(D3DXVECTOR3(3290.0f, 0.0f, -930.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 2000.0f, 1000.0f, TEXTYPE_07);

	SetStage(D3DXVECTOR3(340.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2000.0f, 1000.0f, TEXTYPE_07);
	SetStage(D3DXVECTOR3(340.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 2000.0f, 1000.0f, TEXTYPE_07);



	//当たり判定除外
	ExclusionCollision_Stage();
}
//=============================
//壁の終了処理
//=============================
void UninitStage(void)
{
	for (int nWall = 0; nWall < TEXTYPE_MAX; nWall++)
	{
		//テクスチャの破棄
		if (g_pTextureStage[nWall] != NULL)
		{
			g_pTextureStage[nWall]->Release();
			g_pTextureStage[nWall] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffStage != NULL)
	{
		g_pVtxBuffStage->Release();
		g_pVtxBuffStage = NULL;
	}
}
//=============================
//壁の更新処理
//=============================
void UpdateStage(void)
{
	//何もなし
}
//=============================
//壁の描画処理
//=============================
void DrawStage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	for (int nWall = 0; nWall < NUMSTAGE; nWall++)
	{
		if (g_Stage[nWall].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Stage[nWall].mtxWorldStage);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Stage[nWall].rotStage.y, g_Stage[nWall].rotStage.x, g_Stage[nWall].rotStage.z);

			D3DXMatrixMultiply(&g_Stage[nWall].mtxWorldStage, &g_Stage[nWall].mtxWorldStage, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Stage[nWall].posStage.x, g_Stage[nWall].posStage.y, g_Stage[nWall].posStage.z);

			D3DXMatrixMultiply(&g_Stage[nWall].mtxWorldStage, &g_Stage[nWall].mtxWorldStage, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Stage[nWall].mtxWorldStage);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffStage, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureStage[g_Stage[nWall].TexType]);

			//壁の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				nWall * 4,//描画する最初の頂点インデックス
				2);//描画するプリミティブ数

			//テクスチャを戻す
			pDevice->SetTexture(0, NULL);
		}
	}
}
//=============================
//壁の設定処理
//=============================
void SetStage(D3DXVECTOR3 Pos,D3DXVECTOR3 rot, float bes, float ver, TEXTYPE TexType)
{
	VERTEX_3D* pVtx;//頂点情報へのポインタ

//	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);

	for (int nWall = 0; nWall < NUMSTAGE; nWall++)
	{
		if (g_Stage[nWall].bUse == false)
		{
			g_Stage[nWall].posStage = Pos;//位置
			g_Stage[nWall].rotStage = rot;
			g_Stage[nWall].TexType = TexType;
			g_Stage[nWall].bUse = true;
			g_Stage[nWall].bCollision = true;

			//最大最小
			CalculateTransformedWallVertices(g_Stage[nWall].posStage, rot, bes, ver, &pVtx[0], nWall);
			
			break;
		}
		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffStage->Unlock();
}
//=============================
//壁の情報取得処理
//=============================
STAGE* GetStage(void)
{
	return &g_Stage[0];
}
//=============================
// ローカル座標系での壁の頂点座標を設定する関数
//=============================
void SetWallVertices(VERTEX_3D* pVtx, float bes, float ver)
{

	// 壁のローカル座標系での頂点座標を設定
	pVtx[0].pos = D3DXVECTOR3(-bes, ver, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(bes, ver, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-bes, -ver, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(bes, -ver, 0.0f);
}

//=============================
// 壁の位置と回転に準拠した後の頂点座標を計算する関数
//=============================
void CalculateTransformedWallVertices(D3DXVECTOR3 Pos, D3DXVECTOR3 rot, float bes, float ver, VERTEX_3D* pVtx,int index)
{
	D3DXVECTOR3 MinPos = D3DXVECTOR3(999999.9f, 999999.9f, 999999.9f);
	D3DXVECTOR3 MaxPos = D3DXVECTOR3(-999999.9f, -999999.9f, -999999.9f);

	VERTEX_3D EscapepVtx[4];

	// 壁のローカル座標系での頂点座標を設定
	SetWallVertices(pVtx, bes, ver);

	// ローカル座標系からワールド座標系への変換行列を計算
	D3DXMATRIX mtxWorld;
	D3DXMatrixIdentity(&mtxWorld); // 単位行列で初期化
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z); // 回転行列を計算
	D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z); // 平行移動行列を計算
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot); // 回転行列を合成
//	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans); // 平行移動行列を合成

	// 各頂点の座標を変換行列でワールド座標系に変換
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&EscapepVtx[i].pos, &pVtx[i].pos, &mtxWorld);
		
		if (MaxPos.x <= EscapepVtx[i].pos.x)
		{
			MaxPos.x = EscapepVtx[i].pos.x;
		}
		if (MaxPos.y <= EscapepVtx[i].pos.y)
		{
			MaxPos.y = EscapepVtx[i].pos.y;
		}
		if (MaxPos.z <= EscapepVtx[i].pos.z)
		{
			MaxPos.z = EscapepVtx[i].pos.z;
		}


		if (MinPos.x >= EscapepVtx[i].pos.x)
		{
			MinPos.x = EscapepVtx[i].pos.x;
		}
		if (MinPos.y >= EscapepVtx[i].pos.y)
		{
			MinPos.y = EscapepVtx[i].pos.y;
		}
		if (MinPos.z >= EscapepVtx[i].pos.z)
		{
			MinPos.z = EscapepVtx[i].pos.z;
		}


	}
	//ここで最大最小計算
	g_Stage[index].MaxPos = MaxPos;
	g_Stage[index].MinPos = MinPos;

	g_Stage[index].MaxPos += D3DXVECTOR3(1.5f, 3.0f, 1.5f);
	g_Stage[index].MinPos -= D3DXVECTOR3(1.5f, 3.0f, 1.5f);
}


//=============================================
//当たり判定除外処理
//=============================================
void ExclusionCollision_Stage(void)
{
	//11-30
	for (int i = 11; i <= 30; i++)
	{
		g_Stage[i].bCollision = false;
	//	g_Stage[i].bUse = false;
	}
	g_Stage[31].bCollision = false;
	g_Stage[36].bCollision = false;
	g_Stage[37].bCollision = false;
	g_Stage[38].bCollision = false;
	g_Stage[39].bCollision = false;
	g_Stage[40].bCollision = false;
	for (int m = 41; m <= 49; m++)
	{
		g_Stage[m].bCollision = false;
	}
	g_Stage[51].bCollision = false;
	g_Stage[52].bCollision = false;
	g_Stage[54].bCollision = false;
	g_Stage[55].bCollision = false;
	g_Stage[62].bCollision = false;
	g_Stage[63].bCollision = false;
	g_Stage[64].bCollision = false;

	g_Stage[72].bCollision = false;
	g_Stage[73].bCollision = false;
	g_Stage[74].bCollision = false;
	g_Stage[75].bCollision = false;
	g_Stage[76].bCollision = false;
	g_Stage[77].bCollision = false;
	g_Stage[78].bCollision = false;
	g_Stage[79].bCollision = false;


}