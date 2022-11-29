//==================================================================================================
//
//input.h
//Author:髙山桃也
//
//==================================================================================================

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#include "Xinput.h"

#pragma comment(lib,"xinput.lib")

//ゲームパッドボタン
typedef enum
{
	PADBUTTONS_UP = 0,				//ゲームパッドのボタン
	PADBUTTONS_DOWN,
	PADBUTTONS_LEFT,
	PADBUTTONS_RIGHT,
	PADBUTTONS_START,
	PADBUTTONS_BACK,
	PADBUTTONS_LSTICK,
	PADBUTTONS_RSTICK,
	PADBUTTONS_LB,
	PADBUTTONS_RB,
	PADBUTTONS_UNKNOWN,
	PADBUTTONS_UNKNOWN2,
	PADBUTTONS_A,
	PADBUTTONS_B,
	PADBUTTONS_X,
	PADBUTTONS_Y,
	PADBUTTONS_MAX
}PADBUTTOS;

//バイブレーションの状態
typedef enum
{
	PADVIB_NONE = 0,						//使用していない状態
	PADVIB_USE,								//使用している状態
	PADVIB_MAX
}PADVIB;

//マウスボタン
typedef enum
{
	MOUSEBUTTON_LMB = 0,					//左クリック
	MOUSEBUTTON_RMB,						//右クリック
	MOUSEBUTTON_WHEEL,						//ウィールクリック
	MOUSEBUTTON_SIDE01,						//サイドボタン１
	MOUSEBUTTON_SIDE02,						//サイドボタン２
	MOUSEBUTTON_MAX
}MOUSEBUTTON;

//======================
//プロトタイプ宣言
//======================

//キーボード
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);
bool GetKeyboardRepeat(int nKey);

//コントローラー
HRESULT InitGamePad(void);
void UninitGamePad(void);
void UpdateGamePad(void);
bool GetGamePadPress(PADBUTTOS nKey, int nPlayer);
bool GetGamePadTrigger(PADBUTTOS nKey, int nPlayer);
bool GetGamePadRelease(PADBUTTOS nKey, int nPlayer);
bool GetGamePadRepeat(PADBUTTOS nKey, int nPlayer);
float GetJoyStickLX(int nPlayer);
float GetJoyStickLY(int nPlayer);
float GetJoyStickRX(int nPlayer);
float GetJoyStickRY(int nPlayer);
D3DXVECTOR3 GetVecStickL(void);
D3DXVECTOR3 GetVecStickR(void);
void Vibration(int nPlayer, PADVIB state, short sVib);

//マウス
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
void UninitMouse(void);
void UpdateMouse(void);
LONG GetMouseMoveIX(void);
LONG GetMouseMoveIY(void);
LONG GetMouseMoveIZ(void);
bool GetMousePress(int nButton);
D3DXVECTOR3 GetMouseMove(void);
BYTE GetMouseDebug(int nButton);

//いろいろ
void SetTimer(int nTimer);

//統合
HRESULT InitDevice(HINSTANCE hInstance, HWND hWnd);
void UninitDevice(void);
void UpdateDevice(void);

#endif