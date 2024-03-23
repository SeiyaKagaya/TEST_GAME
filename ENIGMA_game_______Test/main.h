//=========================================================
//
//メインの描画処理関係で使う変数、宣言、構造体[main.h]
// Author seiya kagaya
//
//=========================================================
#ifndef	_MAIN_H_	//このマクロ定義がされてなかったら

#define _MAIN_H_	//２重インクルード防止のマクロ定義

#include <Windows.h>
#include <time.h>    //タイム関数に使用



#include "d3dx9.h"	//描写処理に使う
#define DIRECTINPUT_VERSION (0x0800)//ビルド時の警告対処マクロ
#include "dinput.h"	//入力処理に必要
#include "xaudio2.h"//サウンド処理に使用
#include "xinput.h"

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")	//描画処理に必要
#pragma comment(lib,"d3dx9.lib")//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")//コンポーネット（部品）使用に必要
#pragma comment(lib,"winmm.lib")//システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")//入力処理に必要
#pragma comment(lib,"xinput.lib")//ジョイパッド処理に必要

//マクロ定義
#define CLASS_NAME	"windowclass"			//	ウィンドウクラスの名前
#define WINDOW_NAME	" ENIGMA"	//ウィンドウの名前（キャプションに表示）

#define SCREEN_WIDE	(1280)//ウィンドウの幅
#define SCREEN_HEIGHT	(720)//ウィンドウの高さ
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)//頂点情報を設定
#define MOVE_X	(0)//x座標の移動
#define MOVE_Y	(0)//y座標の移動

#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)//3D用頂点座標(頂点座標{3D},法線、頂点フォーマット２つ)





////フォントの種類
//typedef enum
//{
//	FONT_DOKIDOKI = 0,//どきどきファンタジア
//	FONT_MAX,
//}FONT;
//
//#define MAXFONT (FONT_MAX)//---フォントの数


//頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//座標変化用係数（1.0fで固定）
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
}VERTEX_2D;

//頂点情報[3D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;			//法線ベクトル
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
}VERTEX_3D;


//画面(モード)の種類
typedef enum
{
	MODE_TITLE = 0,//タイトル画面
	MODE_GAME,//ゲーム画面
	MODE_RESULT,//リザルト画面
	MODE_TUTORIAL,//チュートリアル画面
	MODE_MENU,//メニュー画面
	MODE_MAX,
}MODE;







//プロトタイプ宣言
LRESULT CALLBACK WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);//初期化処理

void Uninit(void);//終了処理
void Update(void);//更新処理
void Draw(void);//描画処理

void DrawFPS(void);//FPSの表示
//void DrawPlayerState(void);//プレイヤーの状態
void DrawDebugText(void);//その他説明


void Setmode(MODE mode);//モードの設定
MODE GetMode(void);//モードの取得
MODE GetOldMode(void);


LPDIRECT3DDEVICE9 GetDevice(void);//デバイスの取得


D3DVIEWPORT9 GetViewPort(void);//全画面ようビューポート取得






//-----------------------未完成--仮

// デルタタイムを初期化
void InitializeDeltaTimer(void);
// デルタタイムを取得
double GetDeltaTimer(void);




void GameClearFragOn(void);//Clearフラグたてる　
bool GetGameClearFrag(void);//Clear状態を取得




//UIコメント表示処理
//void DrawComentUI(const char* Text, D3DXVECTOR3 DrawPos, int FontSize, FONT Font);





//
////フォント初期化
//void InitFont(LPDIRECT3DDEVICE9 g_pD3DDevice);
////フォント終了処理
//void UninitFont(void);
////コメント描画
//void RenderFrame(LPDIRECT3DDEVICE9 g_pD3DDevice);
////レンダーテキストセット
//void RenderText(const char* text, int x, int y);
//







#endif // _MAIN_H_ 








