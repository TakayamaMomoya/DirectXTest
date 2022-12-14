//==================================================================================================
//
//input.cpp
//Author:ûüRç
//
//==================================================================================================

#include "input.h"

//}Nè`
#define NUM_KEY_MAX			(256)			//L[ÌÅå
#define NUM_GP				(4)				//Q[pbhÌ
#define NUM_MOUSE_MAX		(4)				//}EX{^Ì

//O[oÏ
LPDIRECTINPUT8 g_pInput[2] = {};				//DirectInputIuWFNgÖÌ|C^

LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		//üÍfoCXÖÌ|C^
BYTE g_aKeyState[NUM_KEY_MAX];					//L[{[hÌvXîñ
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];			//L[{[hÌgK[îñ
BYTE g_aKeyStateRelease[NUM_KEY_MAX];			//L[{[hÌ[Xîñ
BYTE g_aKeyStateRepeat[NUM_KEY_MAX];			//L[{[hÌs[gîñ

LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;		//}EXÖÌ|C^
DIMOUSESTATE2 g_aMouseState;						//}EXÌîñ\¢Ì
BYTE g_aMouseStatePress[NUM_MOUSE_MAX];			//}EXÌ{^

XINPUT_STATE g_aPadState[NUM_GP];				//Q[pbhÌvXîñ
XINPUT_STATE g_aPadStateTrigger[NUM_GP];		//Q[pbhÌgK[îñ
XINPUT_STATE g_aPadStateRelease[NUM_GP];		//Q[pbhÌ[Xîñ
XINPUT_STATE g_aPadStateRepeat[NUM_GP];			//Q[pbhÌs[gîñ
XINPUT_VIBRATION g_aPadVibration[NUM_GP];		//Q[pbh
PADVIB g_aPadVibState[NUM_GP];					//U®ÌóÔ

int g_nTimer;									//^C}[

//===================================================================
//foCXú»
//===================================================================
HRESULT InitDevice(HINSTANCE hInstance, HWND hWnd)
{
	//L[{[hú»
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//}EXú»
	if (FAILED(InitMouse(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	InitGamePad();
}

//===================================================================
//foCXXV
//===================================================================
void UpdateDevice(void)
{
	UpdateMouse();
	UpdateGamePad();
	UpdateKeyboard();
}

//===================================================================
//foCXI¹
//===================================================================
void UninitDevice(void)
{
	UninitMouse();
	UninitGamePad();
	UninitKeyboard();
}

//===================================================================
//L[{[hú»
//===================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputIuWFNgÌ¶¬
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput[0], NULL)))
	{
		return E_FAIL;
	}

	//üÍfoCXÌ¶¬
	if (FAILED(g_pInput[0]->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard,NULL)))
	{
		return E_FAIL;
	}

	//f[^tH[}bgÌ¶¬
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//¦²[hðÝè
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	

	//L[{[hÌANZX l¾
	g_pDevKeyboard->Acquire();

	return S_OK;
}



//===================================================================
//L[{[hI¹
//===================================================================
void UninitKeyboard(void)
{
	if (g_pDevKeyboard != NULL)
	{//üÍfoCXjü
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	if (g_pInput[0] != NULL)
	{//DirectInputIuWFNgÌjü
		g_pInput[0]->Release();
		g_pInput[0] = NULL;
	}
}

//===================================================================
//L[{[hXV
//===================================================================
void UpdateKeyboard(void)
{
	//Ïé¾
	BYTE aKeyState[NUM_KEY_MAX];						//L[{[hüÍîñ
	int nCntKey;

	//üÍfoCX©çf[^ðæ¾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyState[nCntKey];
			g_aKeyStateRepeat[nCntKey] = (g_aKeyState[nCntKey] & aKeyState[nCntKey]);
			g_aKeyState[nCntKey] = aKeyState[nCntKey];			//L[ÌvXîñðÛ¶
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}

//===================================================================
//vXîñæ¾
//===================================================================
bool GetKeyboardPress(int nKey)
{
	//OZq
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}

//===================================================================
//gK[îñæ¾
//===================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//===================================================================
//[Xîñæ¾
//===================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//===================================================================
//s[gîñæ¾
//===================================================================
bool GetKeyboardRepeat(int nKey)
{
	return (g_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}

//«©çQ[pbh

//===================================================================
//Q[pbhú»
//===================================================================
HRESULT InitGamePad(void)
{
	//xinputðLø»·é
	XInputEnable(true);

	//ÌNA
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
//Q[pbhI¹
//===================================================================
void UninitGamePad(void)
{
	//xinputð³ø»·é
	XInputEnable(false);
}

//===================================================================
//Q[pbhXV
//===================================================================
void UpdateGamePad(void)
{
	//Ïé¾
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
			//U®óÔð`B
			XInputSetState(nCntKey, &g_aPadVibration[nCntKey]);
			g_nTimer = 0;
		}

		if (g_aPadVibration[nCntKey].wLeftMotorSpeed < 0 ||
			g_aPadVibration[nCntKey].wRightMotorSpeed < 0)
		{
			g_aPadVibration[nCntKey].wLeftMotorSpeed = 0;
			g_aPadVibration[nCntKey].wRightMotorSpeed = 0;
			//U®óÔð`B
			XInputSetState(nCntKey, &g_aPadVibration[nCntKey]);
		}
		//üÍfoCX©çf[^ðæ¾
		if (XInputGetState(nCntKey, &aPadState[nCntKey]) == ERROR_SUCCESS)
		{
			for (nCntKey = 0; nCntKey < NUM_GP; nCntKey++)
			{
				//gK[
				g_aPadStateTrigger[nCntKey].Gamepad.wButtons =
					(g_aPadState[nCntKey].Gamepad.wButtons ^ aPadState[nCntKey].Gamepad.wButtons)
					& aPadState[nCntKey].Gamepad.wButtons;

				//[X
				g_aPadStateRelease[nCntKey].Gamepad.wButtons = 
					(g_aPadState[nCntKey].Gamepad.wButtons ^ aPadState[nCntKey].Gamepad.wButtons)
					& g_aPadState[nCntKey].Gamepad.wButtons;

				//s[g
				g_aPadStateRepeat[nCntKey].Gamepad.wButtons =
					(g_aPadState[nCntKey].Gamepad.wButtons & aPadState[nCntKey].Gamepad.wButtons);

				//vX
				g_aPadState[nCntKey] = aPadState[nCntKey];
			}
		}
	}
}

//===================================================================
//WCXeBbNîñæ¾
//===================================================================
float GetJoyStickLX(int nPlayer)
{
	//îñðÔ·
	return (float)g_aPadState[nPlayer].Gamepad.sThumbLX / USHRT_MAX * 2;
}

//===================================================================
//WCXeBbNîñæ¾
//===================================================================
float GetJoyStickLY(int nPlayer)
{
	//îñðÔ·
	return (float)g_aPadState[nPlayer].Gamepad.sThumbLY / USHRT_MAX * 2;
}

//===================================================================
//WCXeBbNîñæ¾
//===================================================================
float GetJoyStickRX(int nPlayer)
{
	//îñðÔ·
	return (float)g_aPadState[nPlayer].Gamepad.sThumbRX / USHRT_MAX * 2;
}

//===================================================================
//WCXeBbNîñæ¾
//===================================================================
float GetJoyStickRY(int nPlayer)
{
	//îñðÔ·
	return (float)g_aPadState[nPlayer].Gamepad.sThumbRY / USHRT_MAX * 2;
}

//===================================================================
//WCXeBbNÚ®Êæ¾iLj
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
//vXîñæ¾
//===================================================================
bool GetGamePadPress(PADBUTTOS nKey,int nPlayer)
{
	//OZq
	return(g_aPadState[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//===================================================================
//gK[îñæ¾
//===================================================================
bool GetGamePadTrigger(PADBUTTOS nKey, int nPlayer)
{
	//OZq
	return(g_aPadStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//===================================================================
//[Xîñæ¾
//===================================================================
bool GetGamePadRelease(PADBUTTOS nKey, int nPlayer)
{
	//OZq
	return(g_aPadStateRelease[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//===================================================================
//s[gîñæ¾
//===================================================================
bool GetGamePadRepeat(PADBUTTOS nKey, int nPlayer)
{
	//OZq
	return(g_aPadStateRepeat[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//===================================================================
//oCuîñæ¾
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

	//U®óÔð`B
	XInputSetState(nPlayer, &g_aPadVibration[nPlayer]);
}

//«}EX

//===================================================================
//}EXú»
//===================================================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputIuWFNgÌ¶¬
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput[1], NULL)))
	{
		return E_FAIL;
	}

	//üÍfoCXÌ¶¬
	if (FAILED(g_pInput[1]->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{//}EX
		return E_FAIL;
	}

	//f[^tH[}bgÌ¶¬
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{//}EX
		return E_FAIL;
	}

	//¦²[hðÝè
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{//}EX
		return E_FAIL;
	}

	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = DIPROPAXISMODE_REL;						//ÎÊu[hiRELjAiABSjâÎÊu

	if (FAILED(g_pDevMouse->SetProperty(DIPROP_AXISMODE,&diprop.diph)))
	{
		return E_FAIL;
	}

	//}EXÖÌANZX l¾
	g_pDevMouse->Acquire();

	return S_OK;
}

//===================================================================
//}EXI¹
//===================================================================
void UninitMouse(void)
{
	if (g_pDevMouse != NULL)
	{//üÍfoCXjü
		g_pDevMouse->Unacquire();
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	if (g_pInput[1] != NULL)
	{//DirectInputIuWFNgÌjü
		g_pInput[1]->Release();
		g_pInput[1] = NULL;
	}
}

//===================================================================
//}EXXV
//===================================================================
void UpdateMouse(void)
{
	//Ïé¾
	DIMOUSESTATE2 aMouseState;

	//üÍfoCX©çf[^ðæ¾
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &aMouseState)))
	{
		g_aMouseState = aMouseState;

		for(int nCntButton = 0;nCntButton < NUM_MOUSE_MAX; nCntButton++)
		{
			//vXîñÌæ¾
			g_aMouseState.rgbButtons[nCntButton] = aMouseState.rgbButtons[nCntButton];
		}
	}
	else
	{
		g_pDevMouse->Acquire();
	}
}

//===================================================================
//Ú®Êæ¾
//===================================================================
LONG GetMouseMoveIX(void)
{
	return g_aMouseState.lX;
}

//===================================================================
//Ú®Êæ¾
//===================================================================
LONG GetMouseMoveIY(void)
{
	return g_aMouseState.lY;
}

//===================================================================
//Ú®Êæ¾
//===================================================================
LONG GetMouseMoveIZ(void)
{
	return g_aMouseState.lZ / LONG_MAX;
}

//===================================================================
//¶NbNîñæ¾
//===================================================================
bool GetMousePress(int nButton)
{
	//OZq
	return (g_aMouseState.rgbButtons[nButton] & 0x80) ? true : false;
}

//===================================================================
//¶NbNîñæ¾
//===================================================================
BYTE GetMouseDebug(int nButton)
{
	//OZq
	return g_aMouseState.rgbButtons[nButton];
}

//===================================================================
//^C}[Zbg
//===================================================================
void SetTimer(int nTimer)
{
	g_nTimer = nTimer;
}

