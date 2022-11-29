//==================================================================================================
//
//input.h
//Author:���R����
//
//==================================================================================================

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#include "Xinput.h"

#pragma comment(lib,"xinput.lib")

//�Q�[���p�b�h�{�^��
typedef enum
{
	PADBUTTONS_UP = 0,				//�Q�[���p�b�h�̃{�^��
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

//�o�C�u���[�V�����̏��
typedef enum
{
	PADVIB_NONE = 0,						//�g�p���Ă��Ȃ����
	PADVIB_USE,								//�g�p���Ă�����
	PADVIB_MAX
}PADVIB;

//�}�E�X�{�^��
typedef enum
{
	MOUSEBUTTON_LMB = 0,					//���N���b�N
	MOUSEBUTTON_RMB,						//�E�N���b�N
	MOUSEBUTTON_WHEEL,						//�E�B�[���N���b�N
	MOUSEBUTTON_SIDE01,						//�T�C�h�{�^���P
	MOUSEBUTTON_SIDE02,						//�T�C�h�{�^���Q
	MOUSEBUTTON_MAX
}MOUSEBUTTON;

//======================
//�v���g�^�C�v�錾
//======================

//�L�[�{�[�h
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);
bool GetKeyboardRepeat(int nKey);

//�R���g���[���[
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

//�}�E�X
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
void UninitMouse(void);
void UpdateMouse(void);
LONG GetMouseMoveIX(void);
LONG GetMouseMoveIY(void);
LONG GetMouseMoveIZ(void);
bool GetMousePress(int nButton);
D3DXVECTOR3 GetMouseMove(void);
BYTE GetMouseDebug(int nButton);

//���낢��
void SetTimer(int nTimer);

//����
HRESULT InitDevice(HINSTANCE hInstance, HWND hWnd);
void UninitDevice(void);
void UpdateDevice(void);

#endif