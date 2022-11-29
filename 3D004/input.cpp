//==================================================================================================
//
//input.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "input.h"

//マクロ定義
#define NUM_KEY_MAX			(256)			//キーの最大数
#define NUM_GP				(4)				//ゲームパッドの数
#define NUM_MOUSE_MAX		(4)				//マウスボタンの数

//グローバル変数
LPDIRECTINPUT8 g_pInput[2] = {};				//DirectInputオブジェクトへのポインタ

LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		//入力デバイスへのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];					//キーボードのプレス情報
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];			//キーボードのトリガー情報
BYTE g_aKeyStateRelease[NUM_KEY_MAX];			//キーボードのリリース情報
BYTE g_aKeyStateRepeat[NUM_KEY_MAX];			//キーボードのリピート情報

LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;		//マウスへのポインタ
DIMOUSESTATE2 g_aMouseState;						//マウスの情報構造体
BYTE g_aMouseStatePress[NUM_MOUSE_MAX];			//マウスのボタン数

XINPUT_STATE g_aPadState[NUM_GP];				//ゲームパッドのプレス情報
XINPUT_STATE g_aPadStateTrigger[NUM_GP];		//ゲームパッドのトリガー情報
XINPUT_STATE g_aPadStateRelease[NUM_GP];		//ゲームパッドのリリース情報
XINPUT_STATE g_aPadStateRepeat[NUM_GP];			//ゲームパッドのリピート情報
XINPUT_VIBRATION g_aPadVibration[NUM_GP];		//ゲームパッド
PADVIB g_aPadVibState[NUM_GP];					//振動の状態

int g_nTimer;									//タイマー

//===================================================================
//デバイス初期化処理
//===================================================================
HRESULT InitDevice(HINSTANCE hInstance, HWND hWnd)
{
	//キーボード初期化
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//マウス初期化
	if (FAILED(InitMouse(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	InitGamePad();
}

//===================================================================
//デバイス更新処理
//===================================================================
void UpdateDevice(void)
{
	UpdateMouse();
	UpdateGamePad();
	UpdateKeyboard();
}

//===================================================================
//デバイス終了処理
//===================================================================
void UninitDevice(void)
{
	UninitMouse();
	UninitGamePad();
	UninitKeyboard();
}

//===================================================================
//キーボード初期化処理
//===================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput[0], NULL)))
	{
		return E_FAIL;
	}

	//入力デバイスの生成
	if (FAILED(g_pInput[0]->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard,NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットの生成
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	

	//キーボードのアクセス権獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}



//===================================================================
//キーボード終了処理
//===================================================================
void UninitKeyboard(void)
{
	if (g_pDevKeyboard != NULL)
	{//入力デバイス破棄
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	if (g_pInput[0] != NULL)
	{//DirectInputオブジェクトの破棄
		g_pInput[0]->Release();
		g_pInput[0] = NULL;
	}
}

//===================================================================
//キーボード更新処理
//===================================================================
void UpdateKeyboard(void)
{
	//変数宣言
	BYTE aKeyState[NUM_KEY_MAX];						//キーボード入力情報
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyState[nCntKey];
			g_aKeyStateRepeat[nCntKey] = (g_aKeyState[nCntKey] & aKeyState[nCntKey]);
			g_aKeyState[nCntKey] = aKeyState[nCntKey];			//キーのプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}

//===================================================================
//プレス情報取得
//===================================================================
bool GetKeyboardPress(int nKey)
{
	//三項演算子
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}

//===================================================================
//トリガー情報取得
//===================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//===================================================================
//リリース情報取得
//===================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//===================================================================
//リピート情報取得
//===================================================================
bool GetKeyboardRepeat(int nKey)
{
	return (g_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}

//↓からゲームパッド

//===================================================================
//ゲームパッド初期化処理
//===================================================================
HRESULT InitGamePad(void)
{
	//xinputを有効化する
	XInputEnable(true);

	//メモリのクリア
	for (int nCount = 0; nCount < NUM_GP; nCount++)
	{
		memset(&g_aPadState[nCount], 0, sizeof(XINPUT_STATE));
		memset(&g_aPadVibration[nCount], 0, sizeof(XINPUT_VIBRATION));
		memset(&g_aPadStateTrigger[nCount], 0, sizeof(XINPUT_STATE));
		memset(&g_aPadVibState[nCount], 0, sizeof(PADVIB));
	}

	return S_OK;
}

//===================================================================
//ゲームパッド終了処理
//===================================================================
void UninitGamePad(void)
{
	//xinputを無効化する
	XInputEnable(false);
}

//===================================================================
//ゲームパッド更新処理
//===================================================================
void UpdateGamePad(void)
{
	//変数宣言
	XINPUT_STATE aPadState[NUM_GP];
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_GP; nCntKey++)
	{
		if (g_nTimer > 0)
		{
			g_nTimer--;
		}
		else if (g_nTimer <= 0)
		{
			memset(&g_aPadVibState[nCntKey], 0, sizeof(PADVIB));
			g_aPadVibration[nCntKey].wLeftMotorSpeed = 0;
			g_aPadVibration[nCntKey].wRightMotorSpeed = 0;
			//振動状態を伝達
			XInputSetState(nCntKey, &g_aPadVibration[nCntKey]);
			g_nTimer = 0;
		}

		if (g_aPadVibration[nCntKey].wLeftMotorSpeed < 0 ||
			g_aPadVibration[nCntKey].wRightMotorSpeed < 0)
		{
			g_aPadVibration[nCntKey].wLeftMotorSpeed = 0;
			g_aPadVibration[nCntKey].wRightMotorSpeed = 0;
			//振動状態を伝達
			XInputSetState(nCntKey, &g_aPadVibration[nCntKey]);
		}
		//入力デバイスからデータを取得
		if (XInputGetState(nCntKey, &aPadState[nCntKey]) == ERROR_SUCCESS)
		{
			for (nCntKey = 0; nCntKey < NUM_GP; nCntKey++)
			{
				//トリガー
				g_aPadStateTrigger[nCntKey].Gamepad.wButtons =
					(g_aPadState[nCntKey].Gamepad.wButtons ^ aPadState[nCntKey].Gamepad.wButtons)
					& aPadState[nCntKey].Gamepad.wButtons;

				//リリース
				g_aPadStateRelease[nCntKey].Gamepad.wButtons = 
					(g_aPadState[nCntKey].Gamepad.wButtons ^ aPadState[nCntKey].Gamepad.wButtons)
					& g_aPadState[nCntKey].Gamepad.wButtons;

				//リピート
				g_aPadStateRepeat[nCntKey].Gamepad.wButtons =
					(g_aPadState[nCntKey].Gamepad.wButtons & aPadState[nCntKey].Gamepad.wButtons);

				//プレス
				g_aPadState[nCntKey] = aPadState[nCntKey];
			}
		}
	}
}

//===================================================================
//ジョイスティック情報取得
//===================================================================
float GetJoyStickLX(int nPlayer)
{
	//情報を返す
	return (float)g_aPadState[nPlayer].Gamepad.sThumbLX / USHRT_MAX * 2;
}

//===================================================================
//ジョイスティック情報取得
//===================================================================
float GetJoyStickLY(int nPlayer)
{
	//情報を返す
	return (float)g_aPadState[nPlayer].Gamepad.sThumbLY / USHRT_MAX * 2;
}

//===================================================================
//ジョイスティック情報取得
//===================================================================
float GetJoyStickRX(int nPlayer)
{
	//情報を返す
	return (float)g_aPadState[nPlayer].Gamepad.sThumbRX / USHRT_MAX * 2;
}

//===================================================================
//ジョイスティック情報取得
//===================================================================
float GetJoyStickRY(int nPlayer)
{
	//情報を返す
	return (float)g_aPadState[nPlayer].Gamepad.sThumbRY / USHRT_MAX * 2;
}

//===================================================================
//ジョイスティック移動量取得（L）
//===================================================================
D3DXVECTOR3 GetVecStickL(void)
{
	float fAngle = atan2f(GetJoyStickLX(0), GetJoyStickLY(0));
	float fLength = sqrtf(GetJoyStickLX(0) * GetJoyStickLX(0) + GetJoyStickLY(0) * GetJoyStickLY(0));

	D3DXVECTOR3 vec =
	{
		sinf(fAngle) * fLength,
		cosf(fAngle) * fLength,
		0.0f
	};

	return vec;
}

//===================================================================
//プレス情報取得
//===================================================================
bool GetGamePadPress(PADBUTTOS nKey,int nPlayer)
{
	//三項演算子
	return(g_aPadState[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//===================================================================
//トリガー情報取得
//===================================================================
bool GetGamePadTrigger(PADBUTTOS nKey, int nPlayer)
{
	//三項演算子
	return(g_aPadStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//===================================================================
//リリース情報取得
//===================================================================
bool GetGamePadRelease(PADBUTTOS nKey, int nPlayer)
{
	//三項演算子
	return(g_aPadStateRelease[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//===================================================================
//リピート情報取得
//===================================================================
bool GetGamePadRepeat(PADBUTTOS nKey, int nPlayer)
{
	//三項演算子
	return(g_aPadStateRepeat[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//===================================================================
//バイブ情報取得
//===================================================================
void Vibration(int nPlayer, PADVIB state, short sVib)
{
	switch(state)
	{
	case PADVIB_USE:
		g_aPadVibration[nPlayer].wLeftMotorSpeed = sVib;
		g_aPadVibration[nPlayer].wRightMotorSpeed = sVib;
		g_aPadVibState[nPlayer] = state;
		break;
	default:
		break;
	}

	//振動状態を伝達
	XInputSetState(nPlayer, &g_aPadVibration[nPlayer]);
}

//↓マウス

//===================================================================
//マウス初期化処理
//===================================================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput[1], NULL)))
	{
		return E_FAIL;
	}

	//入力デバイスの生成
	if (FAILED(g_pInput[1]->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{//マウス
		return E_FAIL;
	}

	//データフォーマットの生成
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{//マウス
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{//マウス
		return E_FAIL;
	}

	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = DIPROPAXISMODE_REL;						//相対位置モード（REL）、（ABS）絶対位置

	if (FAILED(g_pDevMouse->SetProperty(DIPROP_AXISMODE,&diprop.diph)))
	{
		return E_FAIL;
	}

	//マウスへのアクセス権獲得
	g_pDevMouse->Acquire();

	return S_OK;
}

//===================================================================
//マウス終了処理
//===================================================================
void UninitMouse(void)
{
	if (g_pDevMouse != NULL)
	{//入力デバイス破棄
		g_pDevMouse->Unacquire();
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	if (g_pInput[1] != NULL)
	{//DirectInputオブジェクトの破棄
		g_pInput[1]->Release();
		g_pInput[1] = NULL;
	}
}

//===================================================================
//マウス更新処理
//===================================================================
void UpdateMouse(void)
{
	//変数宣言
	DIMOUSESTATE2 aMouseState;

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &aMouseState)))
	{
		g_aMouseState = aMouseState;

		for(int nCntButton = 0;nCntButton < NUM_MOUSE_MAX; nCntButton++)
		{
			//プレス情報の取得
			g_aMouseState.rgbButtons[nCntButton] = aMouseState.rgbButtons[nCntButton];
		}
	}
	else
	{
		g_pDevMouse->Acquire();
	}
}

//===================================================================
//移動量取得
//===================================================================
LONG GetMouseMoveIX(void)
{
	return g_aMouseState.lX;
}

//===================================================================
//移動量取得
//===================================================================
LONG GetMouseMoveIY(void)
{
	return g_aMouseState.lY;
}

//===================================================================
//移動量取得
//===================================================================
LONG GetMouseMoveIZ(void)
{
	return g_aMouseState.lZ / LONG_MAX;
}

//===================================================================
//左クリック情報取得
//===================================================================
bool GetMousePress(int nButton)
{
	//三項演算子
	return (g_aMouseState.rgbButtons[nButton] & 0x80) ? true : false;
}

//===================================================================
//左クリック情報取得
//===================================================================
BYTE GetMouseDebug(int nButton)
{
	//三項演算子
	return g_aMouseState.rgbButtons[nButton];
}

//===================================================================
//タイマーセット
//===================================================================
void SetTimer(int nTimer)
{
	g_nTimer = nTimer;
}

