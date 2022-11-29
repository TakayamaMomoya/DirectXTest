//==================================================================================================
//
//meshfield.cpp
//Author:���R����
//
//==================================================================================================

#include "main.h"
#include "meshfield.h"
#include "input.h"

//�}�N����`
#define MESHFIELD_TEX_FILE			"data\\TEXTURE\\BG\\metal001.jpg"			//�e�N�X�`���t�@�C����
#define MOVE_SPEED					(1.0f)										//�ړ����x
#define MESH_LENGTH					(500.0f)									//���b�V���̈�ӂ̒���
#define MESH_U						(2)											//���̃u���b�N��
#define MESH_V						(2)											//�c�̃u���b�N��
#define SPLIT_TEX					(4)											//�e�N�X�`��������

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;									//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;								//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;								//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MeshField g_MeshField;															//�\���̂̏��

//==================================================================================================
//����������
//==================================================================================================
void InitMeshField(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		MESHFIELD_TEX_FILE,
		&g_pTextureMeshField);

	g_MeshField.nNumVtx = (MESH_U + 1) * (MESH_V + 1);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_MeshField.nNumVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	int nCountV, nCountU;

	for (nCountV = 0;nCountV < MESH_V + 1; nCountV++)
	{//���_���W�̐ݒ�
		for (nCountU = 0; nCountU < MESH_U + 1; nCountU++)
		{
			//���_���W
			pVtx[nCountV * (MESH_U + 1) + nCountU].pos.x = (nCountU - ((MESH_U) * 0.5f)) * MESH_LENGTH; 
			pVtx[nCountV * (MESH_U + 1) + nCountU].pos.z = (((MESH_U) * 0.5f) - nCountV) * MESH_LENGTH;
			pVtx[nCountV * (MESH_U + 1) + nCountU].pos.y = 0.0f;
		
			//�e�N�X�`�����W
			pVtx[nCountV * (MESH_U + 1) + nCountU].tex = D3DXVECTOR2
			(
			    ((float)SPLIT_TEX / MESH_U) * nCountU,
				((float)SPLIT_TEX / MESH_V) * nCountV
			);



			//�@���x�N�g���̐ݒ�
			pVtx[nCountV * (MESH_U + 1) + nCountU].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}
	}

	for (int nCnt = 0;nCnt < g_MeshField.nNumVtx;nCnt++)
	{
		//���_�J���[�̐ݒ�
		pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshField->Unlock();

	g_MeshField.nNumIdx = (MESH_U + 1) * (MESH_V + 1) + ((MESH_V + 1) - 2) * (MESH_U + 1) + (((MESH_V + 1) - 2) * 2);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_MeshField.nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	WORD *pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��ւ̃|�C���^���擾
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCount = 0; nCount < g_MeshField.nNumIdx / 2; nCount++)
	{//�C���f�b�N�X����
		if (
			nCount % ((MESH_U + 1) + (MESH_U + 2) * (nCount / (MESH_U + 2))) == 0
			&& nCount != 0
			)
		{
			pIdx[nCount * 2 + 1] = ((MESH_U + 1) * 2) + (MESH_U + 1) * (nCount / (MESH_U + 2));

			pIdx[nCount * 2] = MESH_U + (MESH_U + 1) * (nCount / (MESH_U + 2));
		}
		else
		{
			pIdx[nCount * 2 + 1] = nCount - (nCount / (MESH_U + 2));

			pIdx[nCount * 2] = (nCount - (nCount / (MESH_U + 2))) + (MESH_U + 1);
		}
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffMeshField->Unlock();
}

//==================================================================================================
//�I������
//==================================================================================================
void UninitMeshField(void)
{
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	if (g_pVtxBuffMeshField != NULL)
	{//���_�o�b�t�@�|�C���^�̔j��
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	if (g_pIdxBuffMeshField != NULL)
	{//�C���f�b�N�X�o�b�t�@�|�C���^�̔j��
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//==================================================================================================
//�X�V����
//==================================================================================================
void UpdateMeshField(void)
{
}

//==================================================================================================
//�`�揈��
//==================================================================================================
void DrawMeshField(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&g_MeshField.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll (&mtxRot,
		g_MeshField.rot.y, g_MeshField.rot.x, g_MeshField.rot.z);
	D3DXMatrixMultiply(&g_MeshField.mtxWorld, &g_MeshField.mtxWorld,&mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		g_MeshField.pos.x, g_MeshField.pos.y, g_MeshField.pos.z);
	D3DXMatrixMultiply(&g_MeshField.mtxWorld, &g_MeshField.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD,&g_MeshField.mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	//�|���S���`��
	pDevice->DrawIndexedPrimitive (D3DPT_TRIANGLESTRIP, 0, 0, g_MeshField.nNumVtx, 0, g_MeshField.nNumIdx - 2);
}