//==================================================================================================
//
//camera.cpp
//Author:���R����
//
//==================================================================================================

#include "main.h"
#include "camera.h"
#include "player.h"
#include "input.h"
#include <stdio.h>

//�}�N����`
#define MOVE_SPEED					(1.0f)						//�ړ��X�s�[�h
#define ROLL_SPEED					(0.05f)						//��]�X�s�[�h
#define MOUSE_FACT					(0.03f)						//�}�E�X�̒l�����W��
#define INITIAL_TIMER				(60)						//�����̉�荞�ނ܂ł̎���
#define WRAP_SPEED					(0.1f)						//��荞�ޏ����̈ړ���
#define ROLL_FACT					(0.02f)						//��]�����W��

//�O���[�o���ϐ��錾
Camera g_camera;												//�\���̂̏��
CAMERA_MODE g_cameraMode;										//�J�����̃��[�h

//�v���g�^�C�v�錾
void ControlCamera(void);
void FollowPlayer(void);
void AutoCamera(void);
void SetPosV(void);
void SetPosR(void);

//==================================================================================================
//����������
//==================================================================================================
void InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(0.0f, 40.0f, -200.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fLength = 0.0f;
	g_camera.nCounterWrap = 0;
	g_camera.nTimerWrap = INITIAL_TIMER;

	float fLength = sqrtf
	(
		(g_camera.posV.x - g_camera.posR.x) * (g_camera.posV.x - g_camera.posR.x) + (g_camera.posV.z - g_camera.posR.z) * (g_camera.posV.z - g_camera.posR.z)
	);
	//X���_
	g_camera.fLength = sqrtf
	(
		fLength * fLength + (g_camera.posV.y - g_camera.posR.y) * (g_camera.posV.y - g_camera.posR.y)
	);

	g_camera.rot.x = atan2f(fLength, g_camera.posV.y - g_camera.posR.y);

	SetPosV();
}

//==================================================================================================
//�I������
//==================================================================================================
void UninitCamera(void)
{
}

//==================================================================================================
//�X�V����
//==================================================================================================
void UpdateCamera(void)
{
	switch (g_cameraMode)
	{//���[�h�ɂ�镪��
	case CAMERA_MODE_CONTROL:

		//���쏈��
		ControlCamera();

		break;
	case CAMERA_MODE_CHASE:

		//�Ǐ]����
		FollowPlayer();

		break;
	case CAMERA_MODE_AUTO:

		//��荞�ݏ���
		AutoCamera();

		break;
	}

	//��]����
	if (g_camera.rot.x > 3.0f)
	{
		g_camera.rot.x = 3.0f;
	}
	if (g_camera.rot.x < 0.1f)
	{
		g_camera.rot.x = 0.1f;
	}

	if (GetKeyboardTrigger(DIK_9) == true)
	{//���[�h�؂�ւ�
		g_cameraMode = (CAMERA_MODE)((g_cameraMode + 1) % CAMERA_MODE_MAX);
	}

	//��]���䏈��
	LimitRot(&g_camera.rot);
}

//==================================================================================================
//���쏈��
//==================================================================================================
void ControlCamera(void)
{
	//���_�ړ�===============================================
	if (GetKeyboardRepeat(DIK_A) == true)
	{//���ړ�
		g_camera.posV.x -= sinf(g_camera.rot.y + D3DX_PI * -0.5f) * MOVE_SPEED;
		g_camera.posV.z -= cosf(g_camera.rot.y + D3DX_PI * -0.5f) * MOVE_SPEED;
		SetPosR();
	}
	if (GetKeyboardRepeat(DIK_D) == true)
	{//�E�ړ�
		g_camera.posV.x -= sinf(g_camera.rot.y - D3DX_PI * -0.5f) * MOVE_SPEED;
		g_camera.posV.z -= cosf(g_camera.rot.y - D3DX_PI * -0.5f) * MOVE_SPEED;
		SetPosR();
	}
	if (GetKeyboardRepeat(DIK_W) == true)
	{//�O�ړ�
		g_camera.posV.x -= sinf(g_camera.rot.y) * MOVE_SPEED;
		g_camera.posV.z -= cosf(g_camera.rot.y) * MOVE_SPEED;
		SetPosR();
	}
	if (GetKeyboardRepeat(DIK_S) == true)
	{//��ړ�
		g_camera.posV.x -= sinf(g_camera.rot.y + D3DX_PI) * MOVE_SPEED;
		g_camera.posV.z -= cosf(g_camera.rot.y + D3DX_PI) * MOVE_SPEED;
		SetPosR();
	}

	//���_��]===============================================
	if (GetKeyboardRepeat(DIK_Q) == true)
	{//��������
		g_camera.rot.y -= ROLL_SPEED;
		//�����_�𑊑Έʒu�ɐݒ�
		SetPosR();
	}
	if (GetKeyboardRepeat(DIK_E) == true)
	{//�E������
		g_camera.rot.y += ROLL_SPEED;
		//�����_�𑊑Έʒu�ɐݒ�
		SetPosR();
	}

	if (GetKeyboardRepeat(DIK_Z) == true)
	{//�����]
		g_camera.rot.y += ROLL_SPEED;
		//�����_�𑊑Έʒu�ɐݒ�
		SetPosV();
	}
	if (GetKeyboardRepeat(DIK_C) == true)
	{//�E���]
		g_camera.rot.y -= ROLL_SPEED;
		//�����_�𑊑Έʒu�ɐݒ�
		SetPosV();
	}

	//�c��]====================================================================
	if (GetKeyboardRepeat(DIK_T) == true)
	{//�������
		g_camera.rot.x += ROLL_SPEED;
		//�����_�𑊑Έʒu�ɐݒ�
		SetPosR();

		if (g_camera.rot.x < 0.1f)
		{
			g_camera.rot.x = 0.1f;
		}
	}
	if (GetKeyboardRepeat(DIK_B) == true)
	{//��������
		g_camera.rot.x -= ROLL_SPEED;
		//�����_�𑊑Έʒu�ɐݒ�
		SetPosR();

		if (g_camera.rot.x > 3.0f)
		{
			g_camera.rot.x = 3.0f;
		}
	}

	if (GetKeyboardRepeat(DIK_N) == true)
	{//��
		g_camera.rot.x += ROLL_SPEED;

		//�����_�𑊑Έʒu�ɐݒ�
		SetPosV();

		if (g_camera.rot.x < 0.1f)
		{
			g_camera.rot.x = 0.1f;
		}
	}
	if (GetKeyboardRepeat(DIK_Y) == true)
	{//��
		g_camera.rot.x -= ROLL_SPEED;
		//�����_�𑊑Έʒu�ɐݒ�
		SetPosV();

		if (g_camera.rot.x > 3.0f)
		{
			g_camera.rot.x = 3.0f;
		}
	}

	//�}�E�X����======================================================
	if (GetMousePress(MOUSEBUTTON_LMB) == true)
	{//���N���b�N���A�����_����
		D3DXVECTOR3 rot;

		//�}�E�X�̈ړ��ʑ��
		rot = { (float)GetMouseMoveIX() * ROLL_SPEED, (float)GetMouseMoveIY() * ROLL_SPEED, 0.0f };

		//���_�̐���
		g_camera.rot.y += rot.x;
		g_camera.rot.x -= rot.y;

		//�����_�𑊑Έʒu�ɐݒ�
		SetPosV();
	}
	if (GetMousePress(MOUSEBUTTON_RMB) == true)
	{//�E�N���b�N���A���_����
		D3DXVECTOR3 rot;

		//�}�E�X�̈ړ��ʑ��
		rot = { (float)GetMouseMoveIX() * ROLL_SPEED, (float)GetMouseMoveIY() * ROLL_SPEED, 0.0f };

		//���_�̐���
		g_camera.rot.y += rot.x;
		g_camera.rot.x -= rot.y;

		//�����_�𑊑Έʒu�ɐݒ�
		SetPosR();
	}

	if (GetMouseMoveIZ() != 0)
	{
		g_camera.fLength -= GetMouseMoveIZ() * 0.1f;

		if (g_camera.fLength < 30.0f)
		{
			g_camera.fLength = 30.0f;
		}

		SetPosV();
	}
}

//==================================================================================================
//�Ǐ]����
//==================================================================================================
void FollowPlayer(void)
{
	//���擾
	Player *pPlayer = GetPlayer();

	//�ڕW�̒����_�ݒ�
	g_camera.posRDest =
	{
		pPlayer->pos.x,
		pPlayer->pos.y + 100,
		pPlayer->pos.z
	};

	//�ڕW�̎��_�ݒ�
	g_camera.posVDest =
	{
		g_camera.posRDest.x + sinf(g_camera.rot.x) * sinf(pPlayer->rot.y) * g_camera.fLength,
		g_camera.posRDest.y + cosf(g_camera.rot.x) * g_camera.fLength,
		g_camera.posRDest.z + sinf(g_camera.rot.x) * cosf(pPlayer->rot.y) * g_camera.fLength
	};

	//�����_�␳
	g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.1f;
	g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.1f;
	g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.1f;

	//���݂̎��_�␳
	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.1f;
	g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.1f;
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.1f;
}

//==================================================================================================
//��荞�ݏ���
//==================================================================================================
void AutoCamera(void)
{
	//���擾
	Player *pPlayer = GetPlayer();

	float fSpeed = sqrtf
	(//�X�s�[�h�Z�o
		pPlayer->move.x * pPlayer->move.x + 
		pPlayer->move.z * pPlayer->move.z
	);

	if (fSpeed < WRAP_SPEED)
	{//������x�~�܂������荞�ݏ���
		g_camera.nCounterWrap++;

		if (g_camera.nCounterWrap >= g_camera.nTimerWrap)
		{//��莞�Ԍo�߂ŉ�荞��

			g_camera.nCounterWrap = g_camera.nTimerWrap;

		 //�J�����̉��Ɍ���==================================================
			//�����p�x���擾
			float fRotDiff = pPlayer->rot.y + D3DX_PI - g_camera.rot.y;

			//�p�x�̏C��
			if (fRotDiff < 0)
			{
				fRotDiff += 6.28f;
			}
			else if (fRotDiff > 0)
			{
				fRotDiff -= 6.28f;
			}

			//�p�x�␳
			g_camera.rot.y += fRotDiff * ROLL_FACT;

			//�p�x�̏C��
			if (fRotDiff < 0)
			{
				fRotDiff += 6.28f;
			}
			else if (fRotDiff > 0)
			{
				fRotDiff -= 6.28f;
			}

			//�p�x�␳
			g_camera.rot.y += fRotDiff * ROLL_FACT;

			//===================================================================

			SetPosV();
		}
	}
	else
	{
		//�ڕW�̒����_�ݒ�
		g_camera.posRDest = pPlayer->pos;

		//�ڕW�̎��_�ݒ�
		g_camera.posVDest =
		{
			g_camera.posRDest.x + sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fLength,
			g_camera.posRDest.y + cosf(g_camera.rot.x) * g_camera.fLength,
			g_camera.posRDest.z + sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fLength
		};

		g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.1f;
		g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.1f;
		g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.1f;

		//���݂̎��_�␳
		g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.1f;
		g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.1f;
		g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.1f;
	}
}

//==================================================================================================
//���_�ݒ�
//==================================================================================================
void SetPosV(void)
{
	g_camera.posV =
	{
		g_camera.posR.x + sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fLength,
		g_camera.posR.y + cosf(g_camera.rot.x) * g_camera.fLength,
		g_camera.posR.z + sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fLength
	};
}

//==================================================================================================
//�����_�ݒ�
//==================================================================================================
void SetPosR(void)
{
	g_camera.posR =
	{
		g_camera.posV.x - sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fLength,
		g_camera.posV.y - cosf(g_camera.rot.x) * g_camera.fLength,
		g_camera.posV.z - sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fLength
	};
}

//==================================================================================================
//�ݒ菈��
//==================================================================================================
void SetCamera(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X==================================================
	//�v���W�F�N�V�����}�g���b�N�X������
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		MIN_DRAW,
		MAX_DRAW);

	//�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,&g_camera.mtxProjection);

	//�r���[�}�g���b�N�X============================================================
	//�r���[�}�g���b�N�X������
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//�r���[�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//==================================================================================================
//���擾����
//==================================================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}

//==================================================================================================
//���`�揈��(�f�o�b�O)
//==================================================================================================
void DrawCameraState(LPD3DXFONT pFont)
{
	//�ϐ��錾
	RECT rect = { 20,450,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	sprintf(&aStr[0], "���_�̈ʒu[%.2f,%.2f,%.2f]\n�����_�̈ʒu[%.2f,%.2f,%.2f]\n���_�̌���[%.2f,%.2f,%.2f]\n���_���璍���_�̋���[%.2f]\n�J�������[�h[%d]",
		g_camera.posV.x, g_camera.posV.y, g_camera.posV.z, g_camera.posR.x, g_camera.posR.y, g_camera.posR.z, g_camera.rot.x, g_camera.rot.y, g_camera.rot.z,g_camera.fLength,(int)g_cameraMode);

	//�e�L�X�g�`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//������@�`��(�f�o�b�O)
//==================================================================================================
void DrawCameraControl(LPD3DXFONT pFont)
{
	//�ϐ��錾
	RECT rect = { 20,150,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	sprintf(&aStr[0], "�J���������ړ�[WASD]\n���_����[ZC][YN]\n�����_����[QE][YN]");

	//�e�L�X�g�`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//���[�h�`��(�f�o�b�O)
//==================================================================================================
void DrawCameraMode(LPD3DXFONT pFont)
{
	//�ϐ��錾
	RECT rect = { 500,70,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	switch (g_cameraMode)
	{
	case CAMERA_MODE_CHASE:

		//������ɑ��
		sprintf(&aStr[0], "�J�������[�h[�Ǐ]]");

		//�e�L�X�g�`��
		pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(255, 255, 255, 255));

		break;

	case CAMERA_MODE_CONTROL:

		//������ɑ��
		sprintf(&aStr[0], "�J�������[�h[����]");

		//�e�L�X�g�`��
		pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(255, 255, 255, 255));

		break;

	case CAMERA_MODE_AUTO:

		//������ɑ��
		sprintf(&aStr[0], "�J�������[�h[��荞��]");

		//�e�L�X�g�`��
		pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(255, 255, 255, 255));

		break;
	}

	
}