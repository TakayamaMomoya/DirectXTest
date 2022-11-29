//==================================================================================================
//
//main.h
//Author:髙山桃也
//
//==================================================================================================

#ifndef _MAIN_H_
#define _MAIN_H_
#include <windows.h>
#include"d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)						//ビルド時の警告対処用マクロ
#include "dinput.h"
#include "xaudio2.h"

//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);

//ライブラリ
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")

//画面(モード)の設定
typedef enum
{
	MODE_TITLE = 0,						//タイトル画面
	MODE_TUTORIAL,						//チュートリアル画面
	MODE_MENU,							//メニュー画面
	MODE_GAME,							//ゲーム画面
	MODE_RESULT,						//結果画面
	MODE_RANKING,						//ランキング画面
	MODE_MAX
}MODE;

//マクロ定義
#define SCREEN_WIDTH			(1280)															//ウィンドウの幅
#define SCREEN_HEIGHT			(720)															//ウィンドウの高さ
#define FVF_VERTEX_2D			(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)					//頂点フォーマット設定
#define FVF_VERTEX_3D			(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//頂点フォーマット設定
#define CLASS_NAME				"WindowClass"													//ウィンドウクラスの名前
#define GRAVITY					(0.98f)															//重力加速度
#define NUM_STG					(3)																//ステージの数
	
//頂点情報２Dの構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;			//頂点座標
	float rhw;					//座標変換用係数（１．０ｆで固定）
	D3DCOLOR col;				//頂点カラー
	D3DXVECTOR2 tex;			//テクスチャ座標
}VERTEX_2D;

//頂点情報[３D]の構造体
typedef struct
{
	D3DXVECTOR3 pos;			//頂点座標
	D3DXVECTOR3 nor;			//法線ベクトル
	D3DCOLOR col;				//頂点カラー
	D3DXVECTOR2 tex;			//テクスチャ座標
}VERTEX_3D;

//プロトタイプ宣言
void SetMode(MODE mode);
void LimitRot(D3DXVECTOR3 *rot);
DWORD GetAlphaThreshold(void);
bool CrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 PrVtx, D3DXVECTOR3 ScVtx);
bool SqrCrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax);
void WallCrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 *pos, D3DXVECTOR3 *move, D3DXVECTOR3 PrVtx, D3DXVECTOR3 ScVtx,float width);
#endif