//============================================================================================
//
//テキスト表示する処理[Text.cpp]
// Author seiya kagaya
//
//============================================================================================
#include <stdarg.h>  // 可変長引数関連のヘッダ
#include "text.h"
#include <stdio.h>
#include "camera.h"

LPD3DXFONT g_pFont_Comment[MAXFONT] = {};//フォントへのポインタ
LPD3DXFONT g_pFont_World[MAXFONT] = {};//フォントへのポインタ

//フォント構造体
typedef struct
{
	const char* pFilePass;	// ファイルパス
	const char* pFontName;	// フォントネーム
} FONTINFO;

// フォントの情報
//-------------------------------------------
//　　"ファイルパス","フォント名"
//-------------------------------------------
FONTINFO g_FontInfo[FONT_MAX] =
{
	{"data\\FONT\\DokiDokiFantasia.otf", "どきどきファンタジア"},	 
	{"data\\FONT\\akabara-cinderella.ttf", "赤薔薇シンデレラ"},
	{"data\\FONT\\keifont.ttf", "けいふぉんと"},
	{"data\\FONT\\SoukouMincho.ttf", "装甲明朝"},
	{"data\\FONT\\kiraraji04.ttf", "きらら字04"},
	{"data\\FONT\\onryou.TTF", "怨霊"},
	{"data\\FONT\\ZH-CN.TTF", "SDK_SC_Web Heavy"},

};



D3DXMATRIX g_mtxWorldText;

//=============================
//リザルト画面の初期化処理
//=============================
void InitText(void)
{
	UninitText();

	//フォントの読み込みテスト//
	for (int i = 0; i < FONT_MAX; i++)
	{
		LPCSTR font_path = g_FontInfo[i].pFilePass; // ここで各フォントを使用可能に
	
		if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0)
		{
		}
		else
		{
			// フォント読込エラー処理
			MessageBox(NULL, "フォント読込失敗", "", MB_OK);
		}
	}
}
//=============================
//リザルト画面の終了処理
//=============================
void UninitText(void)
{
	for (int i = 0; i < MAXFONT; i++)
	{
		//UIComment表示用フォントの破棄
		if (g_pFont_Comment[i] != NULL)
		{
			g_pFont_Comment[i]->Release();
			g_pFont_Comment[i] = NULL;
		}
		//UIComment表示用フォントの破棄
		if (g_pFont_World[i] != NULL)
		{
			g_pFont_World[i]->Release();
			g_pFont_World[i] = NULL;
		}
	}
}

//=============================
//UIコメント表示処理
//=============================
void DrawTextSet(D3DXVECTOR3 DrawPos, int FontSize, FONT Font, D3DXCOLOR RGBA, const char* Text, ...)
{//...は可変長引数（Variable Arguments）
	
	 //初期化大事
	if (g_pFont_Comment[Font] != nullptr)
	{
		g_pFont_Comment[Font]->Release();
		g_pFont_Comment[Font] = nullptr;
	}

	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	RECT rect = { DrawPos.x,DrawPos.y,SCREEN_WIDE,SCREEN_HEIGHT };
	char aStr[1024];

	D3DXCreateFont(pDevice, FontSize, 0, FW_HEAVY, 1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_TT_ONLY_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		TEXT(g_FontInfo[Font].pFontName),//--読み込んだフォントの名前(プロパティのタイトルで分かる)
		&g_pFont_Comment[Font]);

	//D3DXCreateFontの引数の意味
	
	//D3DXCreateFont(pDevice,                /* デバイス */
	//	16,                            /* 文字の高さ */
	//	0,                            /* 文字幅 */
	//	FW_NORMAL,                    /* フォントの太さ */
	//	1,                            /* MIPMAPのレベル */
	//	FALSE,                        /* イタリックか？ */
	//	DEFAULT_CHARSET,            /* 文字セット */
	//	OUT_DEFAULT_PRECIS,            /* 出力精度 */
	//	DEFAULT_QUALITY,            /* 出力品質 */
	//	DEFAULT_PITCH | FF_SWISS,    /* フォントピッチとファミリ */
	//	L"ＭＳ Ｐゴシック",                    /* フォント名 */
	//	&lpFont)         /* Direct3Dフォントへのポインタへのアドレス */




	// 可変長引数の処理-------
	va_list args;				 //可変長引数の引数リストを指定する
	va_start(args, Text);		 //va_list を初期化--＞//可変長引数の一つ前の引数を指定
	vsprintf_s(aStr, Text, args);//書式指定文字列を使用して可変長引数から文字列を生成するための安全な関数
	va_end(args);				 //va_start マクロによって開始された可変長引数リストを終了するために使用

	// テキストの描画
	g_pFont_Comment[Font]->DrawText(NULL, aStr, -1, &rect, DT_LEFT/* | DT_WORDBREAK*/, RGBA);



	//使用例！！

	//	DrawTextSet(　座標　, フォントサイズ　, フォント名（ｈ.で作ったラベル的な）, カラー, "打ちたい文字(任意で%d.%f,%s)",(任意で変数));
}



