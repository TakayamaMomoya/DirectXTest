//==================================================================================================
//
//input.cpp
//Author:���R����
//
//==================================================================================================

#include "input.h"

//�}�N����`
#define NUM_KEY_MAX			(256)			//�L�[�̍ő吔
#define NUM_GP				(4)				//�Q�[���p�b�h�̐�
#define NUM_MOUSE_MAX		(4)				//�}�E�X�{�^���̐�

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pInput[2] = {};				//DirectInput�I�u�W�F�N�g�ւ̃|�C���^

LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		//���̓f�o�C�X�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];					//�L�[�{�[�h�̃v���X���
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];			//�L�[�{�[�h�̃g���K�[���
BYTE g_aKeyStateRelease[NUM_KEY_MAX];			//�L�[�{�[�h�̃����[�X���
BYTE g_aKeyStateRepeat[NUM_KEY_MAX];			//�L�[�{�[�h�̃��s�[�g���

LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;		//�}�E�X�ւ̃|�C���^
DIMOUSESTATE2 g_aMouseState;						//�}�E�X�̏��\����
BYTE g_aMouseStatePress[NUM_MOUSE_MAX];			//�}�E�X�̃{�^����

XINPUT_STATE g_aPadState[NUM_GP];				//�Q�[���p�b�h�̃v���X���
XINPUT_STATE g_aPadStateTrigger[NUM_GP];		//�Q�[���p�b�h�̃g���K�[���
XINPUT_STATE g_aPadStateRelease[NUM_GP];		//�Q�[���p�b�h�̃����[�X���
XINPUT_STATE g_aPadStateRepeat[NUM_GP];			//�Q�[���p�b�h�̃��s�[�g���
XINPUT_VIBRATION g_aPadVibration[NUM_GP];		//�Q�[���p�b�h
PADVIB g_aPadVibState[NUM_GP];					//�U���̏��

int g_nTimer;									//�^�C�}�[

//===================================================================
//�f�o�C�X����������
//===================================================================
HRESULT InitDevice(HINSTANCE hInstance, HWND hWnd)
{
	//�L�[�{�[�h������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�}�E�X������
	if (FAILED(InitMouse(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	InitGamePad();
}

//===================================================================
//�f�o�C�X�X�V����
//===================================================================
void UpdateDevice(void)
{
	UpdateMouse();
	UpdateGamePad();
	UpdateKeyboard();
}

//===================================================================
//�f�o�C�X�I������
//===================================================================
void UninitDevice(void)
{
	UninitMouse();
	UninitGamePad();
	UninitKeyboard();
}

//===================================================================
//�L�[�{�[�h����������
//===================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput[0], NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X�̐���
	if (FAILED(g_pInput[0]->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard,NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�̐���
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	

	//�L�[�{�[�h�̃A�N�Z�X���l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}



//===================================================================
//�L�[�{�[�h�I������
//===================================================================
void UninitKeyboard(void)
{
	if (g_pDevKeyboard != NULL)
	{//���̓f�o�C�X�j��
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	if (g_pInput[0] != NULL)
	{//DirectInput�I�u�W�F�N�g�̔j��
		g_pInput[0]->Release();
		g_pInput[0] = NULL;
	}
}

//===================================================================
//�L�[�{�[�h�X�V����
//===================================================================
void UpdateKeyboard(void)
{
	//�ϐ��錾
	BYTE aKeyState[NUM_KEY_MAX];						//�L�[�{�[�h���͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyState[nCntKey];
			g_aKeyStateRepeat[nCntKey] = (g_aKeyState[nCntKey] & aKeyState[nCntKey]);
			g_aKeyState[nCntKey] = aKeyState[nCntKey];			//�L�[�̃v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}

//===================================================================
//�v���X���擾
//===================================================================
bool GetKeyboardPress(int nKey)
{
	//�O�����Z�q
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}

//===================================================================
//�g���K�[���擾
//===================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//===================================================================
//�����[�X���擾
//===================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//===================================================================
//���s�[�g���擾
//===================================================================
bool GetKeyboardRepeat(int nKey)
{
	return (g_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}

//������Q�[���p�b�h

//===================================================================
//�Q�[���p�b�h����������
//===================================================================
HRESULT InitGamePad(void)
{
	//xinput��L��������
	XInputEnable(true);

	//�������̃N���A
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
//�Q�[���p�b�h�I������
//===================================================================
void UninitGamePad(void)
{
	//xinput�𖳌�������
	XInputEnable(false);
}

//===================================================================
//�Q�[���p�b�h�X�V����
//===================================================================
void UpdateGamePad(void)
{
	//�ϐ��錾
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
			//�U����Ԃ�`�B
			XInputSetState(nCntKey, &g_aPadVibration[nCntKey]);
			g_nTimer = 0;
		}

		if (g_aPadVibration[nCntKey].wLeftMotorSpeed < 0 ||
			g_aPadVibration[nCntKey].wRightMotorSpeed < 0)
		{
			g_aPadVibration[nCntKey].wLeftMotorSpeed = 0;
			g_aPadVibration[nCntKey].wRightMotorSpeed = 0;
			//�U����Ԃ�`�B
			XInputSetState(nCntKey, &g_aPadVibration[nCntKey]);
		}
		//���̓f�o�C�X����f�[�^���擾
		if (XInputGetState(nCntKey, &aPadState[nCntKey]) == ERROR_SUCCESS)
		{
			for (nCntKey = 0; nCntKey < NUM_GP; nCntKey++)
			{
				//�g���K�[
				g_aPadStateTrigger[nCntKey].Gamepad.wButtons =
					(g_aPadState[nCntKey].Gamepad.wButtons ^ aPadState[nCntKey].Gamepad.wButtons)
					& aPadState[nCntKey].Gamepad.wButtons;

				//�����[�X
				g_aPadStateRelease[nCntKey].Gamepad.wButtons = 
					(g_aPadState[nCntKey].Gamepad.wButtons ^ aPadState[nCntKey].Gamepad.wButtons)
					& g_aPadState[nCntKey].Gamepad.wButtons;

				//���s�[�g
				g_aPadStateRepeat[nCntKey].Gamepad.wButtons =
					(g_aPadState[nCntKey].Gamepad.wButtons & aPadState[nCntKey].Gamepad.wButtons);

				//�v���X
				g_aPadState[nCntKey] = aPadState[nCntKey];
			}
		}
	}
}

//===================================================================
//�W���C�X�e�B�b�N���擾
//===================================================================
float GetJoyStickLX(int nPlayer)
{
	//����Ԃ�
	return (float)g_aPadState[nPlayer].Gamepad.sThumbLX / USHRT_MAX * 2;
}

//===================================================================
//�W���C�X�e�B�b�N���擾
//===================================================================
float GetJoyStickLY(int nPlayer)
{
	//����Ԃ�
	return (float)g_aPadState[nPlayer].Gamepad.sThumbLY / USHRT_MAX * 2;
}

//===================================================================
//�W���C�X�e�B�b�N���擾
//===================================================================
float GetJoyStickRX(int nPlayer)
{
	//����Ԃ�
	return (float)g_aPadState[nPlayer].Gamepad.sThumbRX / USHRT_MAX * 2;
}

//===================================================================
//�W���C�X�e�B�b�N���擾
//===================================================================
float GetJoyStickRY(int nPlayer)
{
	//����Ԃ�
	return (float)g_aPadState[nPlayer].Gamepad.sThumbRY / USHRT_MAX * 2;
}

//===================================================================
//�W���C�X�e�B�b�N�ړ��ʎ擾�iL�j
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
//�v���X���擾
//===================================================================
bool GetGamePadPress(PADBUTTOS nKey,int nPlayer)
{
	//�O�����Z�q
	return(g_aPadState[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//===================================================================
//�g���K�[���擾
//===================================================================
bool GetGamePadTrigger(PADBUTTOS nKey, int nPlayer)
{
	//�O�����Z�q
	return(g_aPadStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//===================================================================
//�����[�X���擾
//===================================================================
bool GetGamePadRelease(PADBUTTOS nKey, int nPlayer)
{
	//�O�����Z�q
	return(g_aPadStateRelease[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//===================================================================
//���s�[�g���擾
//===================================================================
bool GetGamePadRepeat(PADBUTTOS nKey, int nPlayer)
{
	//�O�����Z�q
	return(g_aPadStateRepeat[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//===================================================================
//�o�C�u���擾
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

	//�U����Ԃ�`�B
	XInputSetState(nPlayer, &g_aPadVibration[nPlayer]);
}

//���}�E�X

//===================================================================
//�}�E�X����������
//===================================================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput[1], NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X�̐���
	if (FAILED(g_pInput[1]->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{//�}�E�X
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�̐���
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{//�}�E�X
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{//�}�E�X
		return E_FAIL;
	}

	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = DIPROPAXISMODE_REL;						//���Έʒu���[�h�iREL�j�A�iABS�j��Έʒu

	if (FAILED(g_pDevMouse->SetProperty(DIPROP_AXISMODE,&diprop.diph)))
	{
		return E_FAIL;
	}

	//�}�E�X�ւ̃A�N�Z�X���l��
	g_pDevMouse->Acquire();

	return S_OK;
}

//===================================================================
//�}�E�X�I������
//===================================================================
void UninitMouse(void)
{
	if (g_pDevMouse != NULL)
	{//���̓f�o�C�X�j��
		g_pDevMouse->Unacquire();
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	if (g_pInput[1] != NULL)
	{//DirectInput�I�u�W�F�N�g�̔j��
		g_pInput[1]->Release();
		g_pInput[1] = NULL;
	}
}

//===================================================================
//�}�E�X�X�V����
//===================================================================
void UpdateMouse(void)
{
	//�ϐ��錾
	DIMOUSESTATE2 aMouseState;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &aMouseState)))
	{
		g_aMouseState = aMouseState;

		for(int nCntButton = 0;nCntButton < NUM_MOUSE_MAX; nCntButton++)
		{
			//�v���X���̎擾
			g_aMouseState.rgbButtons[nCntButton] = aMouseState.rgbButtons[nCntButton];
		}
	}
	else
	{
		g_pDevMouse->Acquire();
	}
}

//===================================================================
//�ړ��ʎ擾
//===================================================================
LONG GetMouseMoveIX(void)
{
	return g_aMouseState.lX;
}

//===================================================================
//�ړ��ʎ擾
//===================================================================
LONG GetMouseMoveIY(void)
{
	return g_aMouseState.lY;
}

//===================================================================
//�ړ��ʎ擾
//===================================================================
LONG GetMouseMoveIZ(void)
{
	return g_aMouseState.lZ / LONG_MAX;
}

//===================================================================
//���N���b�N���擾
//===================================================================
bool GetMousePress(int nButton)
{
	//�O�����Z�q
	return (g_aMouseState.rgbButtons[nButton] & 0x80) ? true : false;
}

//===================================================================
//���N���b�N���擾
//===================================================================
BYTE GetMouseDebug(int nButton)
{
	//�O�����Z�q
	return g_aMouseState.rgbButtons[nButton];
}

//===================================================================
//�^�C�}�[�Z�b�g
//===================================================================
void SetTimer(int nTimer)
{
	g_nTimer = nTimer;
}

