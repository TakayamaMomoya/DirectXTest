//==================================================================================================
//
//model.cpp
//Author:���R����
//
//==================================================================================================

#include "main.h"
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include <stdio.h>

//�}�N����`
#define MOVE_SPEED					(1.0f)									//�ړ����x
#define NUM_TEX						(8)										//�e�N�X�`����
#define ROLL_FACT					(0.06f)									//��]�����W��

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureModel[NUM_TEX] = {};		//�e�N�X�`���ւ̃|�C���^
LPD3DXMESH g_pMeshModel = NULL;							//���b�V���ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;					//�}�e���A���ւ̃o�b�t�@
DWORD g_dwNumMatModel;									//�}�e���A���̐�
int g_nIdxShadowModel;									//�e�̃C���f�b�N�X
Model g_model;											//�\���̂̏��

//==================================================================================================
//����������
//==================================================================================================
void InitModel(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//�ϐ�������
	g_model.pos = { 0.0f,0.0f,0.0f };
	g_model.rot = { 0.0f,0.0f,0.0f };
	g_dwNumMatModel = 0;
	g_nIdxShadowModel = 0;

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\robot000\\01_head.x",
					  D3DXMESH_SYSTEMMEM,
					  pDevice,
					  NULL,
					  &g_pBuffMatModel,
					  NULL,
					  &g_dwNumMatModel,
					  &g_pMeshModel);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`�������݂���
		    //�e�N�X�`���ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureModel[nCntMat]);
		}
	}

	//�e�C���f�b�N�X�擾
	g_nIdxShadowModel = SetShadow();
}

//==================================================================================================
//�I������
//==================================================================================================
void UninitModel(void)
{
	if (g_pMeshModel != NULL)
	{//���b�V���|�C���^�̔j��
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	if (g_pBuffMatModel != NULL)
	{//���_�o�b�t�@�|�C���^�̔j��
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}

	for (int nCntTex = 0;nCntTex < NUM_TEX;nCntTex++)
	{
		if (g_apTextureModel[nCntTex] != NULL)
		{//�e�N�X�`���|�C���^�̔j��
			g_apTextureModel[nCntTex]->Release();
			g_apTextureModel[nCntTex] = NULL;
		}
	}
}

//==================================================================================================
//�X�V����
//==================================================================================================
void UpdateModel(void)
{
	//���擾
	Camera *pCamera = GetCamera();

	//���쏈��======================================================
	if (GetKeyboardRepeat(DIK_UP) == true)
	{//�O�ړ�
		g_model.pos.x += sinf(pCamera->rot.y) * MOVE_SPEED;
		g_model.pos.z += cosf(pCamera->rot.y) * MOVE_SPEED;
	}
	else if (GetKeyboardRepeat(DIK_DOWN) == true)
	{//��ړ�
		g_model.pos.x += sinf(pCamera->rot.y + D3DX_PI) * MOVE_SPEED;
		g_model.pos.z += cosf(pCamera->rot.y + D3DX_PI) * MOVE_SPEED;
	}
	else if (GetKeyboardRepeat(DIK_LEFT) == true)
	{//���ړ�
		g_model.pos.x += sinf(pCamera->rot.y - D3DX_PI * 0.5f) * MOVE_SPEED;
		g_model.pos.z += cosf(pCamera->rot.y - D3DX_PI * 0.5f) * MOVE_SPEED;
	}
	else if (GetKeyboardRepeat(DIK_RIGHT) == true)
	{//�E�ړ�
		g_model.pos.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f) * MOVE_SPEED;
		g_model.pos.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f) * MOVE_SPEED;
	}

	if (GetKeyboardRepeat(DIK_LSHIFT) == true)
	{
		g_model.rot.y += 0.01f;
	}
	if (GetKeyboardRepeat(DIK_RSHIFT) == true)
	{
		g_model.rot.y -= 0.01f;
	}

	//�J�����̉��Ɍ���==================================================
	//�����p�x���擾
	float fRotDiff = pCamera->rot.y - g_model.rot.y;

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
	g_model.rot.y += fRotDiff * ROLL_FACT;

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
	g_model.rot.y += fRotDiff * ROLL_FACT;

	//===================================================================

	if (g_model.rot.y > D3DX_PI)
	{
		g_model.rot.y = -D3DX_PI;
	}
	if (g_model.rot.y < -D3DX_PI)
	{
		g_model.rot.y = D3DX_PI;
	}

	//�e�̈ʒu�ݒ�
	SetPositionShadow(g_nIdxShadowModel, g_model.pos);
}

//==================================================================================================
//�`�揈��
//==================================================================================================
void DrawModel(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&g_model.g_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll (&mtxRot,
		g_model.rot.y, g_model.rot.x, g_model.rot.z);
	D3DXMatrixMultiply(&g_model.g_mtxWorld, &g_model.g_mtxWorld,&mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		g_model.pos.x, g_model.pos.y, g_model.pos.z);
	D3DXMatrixMultiply(&g_model.g_mtxWorld, &g_model.g_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD,&g_model.g_mtxWorld);

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		//�}�e���A���ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_apTextureModel[nCntMat]);

		//���f���i�p�[�c�j�`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//�}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//==================================================================================================
//�v���C���[��ԕ`��(�f�o�b�O)
//==================================================================================================
void DrawPlayerState(LPD3DXFONT pFont)
{
	//�ϐ��錾
	RECT rect = { 20,500,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	sprintf(&aStr[0], "�v���C���[�̈ʒu[%.2f,%.2f,%.2f]\n�v���C���[�̌���[%.2f,%.2f,%.2f]", 
		g_model.pos.x, g_model.pos.y, g_model.pos.z,g_model.rot.x, g_model.rot.y, g_model.rot.z);

	//�e�L�X�g�`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}