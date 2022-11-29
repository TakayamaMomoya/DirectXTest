//==================================================================================================
//
//field.cpp
//Author:���R����
//
//==================================================================================================

#include "main.h"
#include "field.h"
#include "input.h"

//�}�N����`
#define FIELD_TEX_FILE			"data\\TEXTURE\\sand000.jpg"			//�̃e�N�X�`���t�@�C����
#define MOVE_SPEED					(1.0f)									//�ړ����x

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureField = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posField;							//�ʒu
D3DXVECTOR3 g_rotField;							//����
D3DXMATRIX g_mtxWorldField;						//���[���h�}�g���b�N�X

//==================================================================================================
//����������
//==================================================================================================
void InitField(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		FIELD_TEX_FILE,
		&g_pTextureField);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-1000.0f, 0.0f, 1000.0f);
	pVtx[1].pos = D3DXVECTOR3(1000.0f, 0.0f, 1000.0f);
	pVtx[2].pos = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	pVtx[3].pos = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(10.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 10.0f);
	pVtx[3].tex = D3DXVECTOR2(10.0f, 10.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffField->Unlock();
}

//==================================================================================================
//�I������
//==================================================================================================
void UninitField(void)
{
	if (g_pTextureField != NULL)
	{
		g_pTextureField->Release();
		g_pTextureField = NULL;
	}

	if (g_pVtxBuffField != NULL)
	{//���_�o�b�t�@�|�C���^�̔j��
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//==================================================================================================
//�X�V����
//==================================================================================================
void UpdateField(void)
{
}

//==================================================================================================
//�`�揈��
//==================================================================================================
void DrawField(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&g_mtxWorldField);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll (&mtxRot,
		g_rotField.y, g_rotField.x, g_rotField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField,&mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		g_posField.x, g_posField.y, g_posField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTrans);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorldField);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureField);

	//�`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}