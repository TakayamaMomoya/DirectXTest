//==================================================================================================
//
//polygon.cpp
//Author:���R����
//
//==================================================================================================

#include "main.h"
#include "light.h"
#include "input.h"
#include <stdio.h>

//�}�N����`
#define ROLL_SPEED							(0.03f)						//���X�s�[�h

//�O���[�o���ϐ�
D3DLIGHT9 g_aLight[MAX_LIGHT];				//�\���̂̏��
int g_nCurrentLight;

//==================================================================================================
//����������
//==================================================================================================
void InitLight(void)
{
	//�ϐ�������
	g_nCurrentLight = 0;

	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	D3DXVECTOR3 vecDir;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���C�g�̎�ސݒ�
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U���̐ݒ�
	g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕����ݒ�
	vecDir = D3DXVECTOR3(-1.4f, 0.24f, -2.21f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//�x�N�g�����K��
	g_aLight[0].Direction = vecDir;

	//���C�g�ݒ�
	pDevice->SetLight(0, &g_aLight[0]);

	//���C�g�L����
	pDevice->LightEnable(0, TRUE);

	//���C�g�Q�̐ݒ�============================================
	//���C�g�̎�ސݒ�
	g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U���̐ݒ�
	g_aLight[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕����ݒ�
	vecDir = D3DXVECTOR3(1.42f, -0.8f, 0.08f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//�x�N�g�����K��
	g_aLight[1].Direction = vecDir;

	//���C�g�ݒ�
	pDevice->SetLight(1, &g_aLight[1]);

	//���C�g�L����
	pDevice->LightEnable(1, TRUE);

	//���C�g�R�̐ݒ�============================================
	//���C�g�̎�ސݒ�
	g_aLight[2].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U���̐ݒ�
	g_aLight[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕����ݒ�
	vecDir = D3DXVECTOR3(-0.59f, -0.8f, 1.55f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//�x�N�g�����K��
	g_aLight[2].Direction = vecDir;

	//���C�g�ݒ�
	pDevice->SetLight(2, &g_aLight[2]);

	//���C�g�L����
	pDevice->LightEnable(2, TRUE);
}

//==================================================================================================
//�I������
//==================================================================================================
void UninitLight(void)
{
}

//==================================================================================================
//�X�V����
//==================================================================================================
void UpdateLight(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	//���C�g�ړ�================================================
	if (GetKeyboardRepeat(DIK_J) == true)
	{//���ړ�
		g_aLight[g_nCurrentLight].Direction.x -= ROLL_SPEED;
	}
	if (GetKeyboardRepeat(DIK_L) == true)
	{//�E�ړ�
		g_aLight[g_nCurrentLight].Direction.x += ROLL_SPEED;
	}

	if (GetKeyboardRepeat(DIK_I) == true)
	{//���ړ�
		g_aLight[g_nCurrentLight].Direction.z += ROLL_SPEED;
	}
	if (GetKeyboardRepeat(DIK_K) == true)
	{//��O�ړ�
		g_aLight[g_nCurrentLight].Direction.z -= ROLL_SPEED;
	}

	if (GetKeyboardRepeat(DIK_U) == true)
	{//��ړ�
		g_aLight[g_nCurrentLight].Direction.y += ROLL_SPEED;
	}
	if (GetKeyboardRepeat(DIK_M) == true)
	{//���ړ�
		g_aLight[g_nCurrentLight].Direction.y -= ROLL_SPEED;
	}

	//���C�g�؂�ւ�================================================
	if (GetKeyboardTrigger(DIK_O) == true)
	{//���C�g�؂�ւ�
		g_nCurrentLight = (g_nCurrentLight + 1) % MAX_LIGHT;
	}

	for (int nCntLight = 0;nCntLight < MAX_LIGHT;nCntLight++)
	{
		//�x�N�g�����K��
		D3DXVec3Normalize
		(
			&(D3DXVECTOR3)g_aLight[nCntLight].Direction,
			&(D3DXVECTOR3)g_aLight[nCntLight].Direction
		);

		//���C�g�ݒ�
		pDevice->SetLight(nCntLight, &g_aLight[nCntLight]);
	}
}

//==================================================================================================
//�I�����ڎ擾����
//==================================================================================================
int GetCurrentLight(void)
{
	return g_nCurrentLight;
}