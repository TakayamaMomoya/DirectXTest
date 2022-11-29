//==================================================================================================
//
//meshcylinder.cpp
//Author:���R����
//
//==================================================================================================

#include "main.h"
#include "meshcylinder.h"
#include "input.h"
#include "light.h"

//�}�N����`
#define MESHCYLINDER_TEX_FILE		"data\\TEXTURE\\BG\\sky000.png"				//�e�N�X�`���t�@�C����
#define MOVE_SPEED					(1.0f)										//�ړ����x
#define MESH_LENGTH					(300.0f)									//���b�V���̈�ӂ̒���
#define MESH_U						(16)										//���̃u���b�N��
#define MESH_V						(1)											//�c�̃u���b�N��
#define MAX_CYLINDER				(8)											//���̍ő吔
#define SPLIT_TEX_U					(3)											//���̃e�N�X�`��������
#define SPLIT_TEX_V					(1)											//�c�̃e�N�X�`��������

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;									//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;								//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;								//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MeshCylinder g_aMeshCylinder[MAX_CYLINDER];												//�\���̂̏��

//==================================================================================================
//����������
//==================================================================================================
void InitMeshCylinder(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		MESHCYLINDER_TEX_FILE,
		&g_pTextureMeshCylinder);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (MESH_U + 1) * (MESH_V + 1) * MAX_CYLINDER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((MESH_U + 1) * (MESH_V + 1) + ((MESH_V + 1) - 2) * (MESH_U + 1) + (((MESH_V + 1) - 2) * 2)) * MAX_CYLINDER,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	WORD *pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��ւ̃|�C���^���擾
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntWall = 0;nCntWall < MAX_CYLINDER;nCntWall++)
	{
		//�ő咸�_���v�Z
		g_aMeshCylinder[nCntWall].nNumVtx = (MESH_U + 1) * (MESH_V + 1);

		//�ϐ�������
		g_aMeshCylinder[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshCylinder[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshCylinder[nCntWall].bUse = false;

		//�v�Z�p�ϐ�
		float fRot;
		float fLength = 2000.0f;
		D3DXVECTOR3 VecRot;

		//���_���==================================================================================
		for (int nCountV = 0; nCountV < MESH_V + 1; nCountV++)
		{//���_���W�̐ݒ�
			for (int nCountU = 0; nCountU < MESH_U + 1; nCountU++)
			{
				//�p�x�Z�o
				fRot = nCountU * (D3DX_PI / MESH_U) * 2;

				pVtx[nCountV * (MESH_U + 1) + nCountU].pos.x = (float)sin(fRot) * fLength;
				pVtx[nCountV * (MESH_U + 1) + nCountU].pos.y = (MESH_V - nCountV) * MESH_LENGTH;
				pVtx[nCountV * (MESH_U + 1) + nCountU].pos.z = cosf(fRot) * fLength;

				//�e�N�X�`�����W
				pVtx[nCountV * (MESH_U + 1) + nCountU].tex = D3DXVECTOR2
				(
					((float)SPLIT_TEX_U / MESH_U) * nCountU,
					((float)SPLIT_TEX_V / MESH_V) * nCountV
				);

				VecRot = D3DXVECTOR3
				(
					pVtx[nCountV * (MESH_U + 1) + nCountU].pos.x,
					0.0f,
					pVtx[nCountV * (MESH_U + 1) + nCountU].pos.z
				);

				//�x�N�g�����K��
				D3DXVec3Normalize(&VecRot, &VecRot);

				//�@���x�N�g���̐ݒ�
				pVtx[nCountV * (MESH_U + 1) + nCountU].nor = VecRot;
			}
		}

		for (int nCnt = 0; nCnt < g_aMeshCylinder[nCntWall].nNumVtx; nCnt++)
		{
			//���_�J���[�̐ݒ�
			pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		//�C���f�b�N�X==================================================================================
		g_aMeshCylinder[nCntWall].nNumIdx = (MESH_U + 1) * (MESH_V + 1) + ((MESH_V + 1) - 2) * (MESH_U + 1) + (((MESH_V + 1) - 2) * 2);

		for (int nCount = 0; nCount < g_aMeshCylinder[nCntWall].nNumIdx / 2; nCount++)
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

		//�|�C���^��i�߂�
		pIdx += g_aMeshCylinder[nCntWall].nNumIdx;
		pVtx += g_aMeshCylinder[nCntWall].nNumVtx;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshCylinder->Unlock();

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffMeshCylinder->Unlock();

	SetMeshCylinder
	(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	);
}

//==================================================================================================
//�I������
//==================================================================================================
void UninitMeshCylinder(void)
{
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}

	if (g_pVtxBuffMeshCylinder != NULL)
	{//���_�o�b�t�@�|�C���^�̔j��
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	if (g_pIdxBuffMeshCylinder != NULL)
	{//�C���f�b�N�X�o�b�t�@�|�C���^�̔j��
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}

//==================================================================================================
//�X�V����
//==================================================================================================
void UpdateMeshCylinder(void)
{
}

//==================================================================================================
//�`�揈��
//==================================================================================================
void DrawMeshCylinder(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntWall = 0; nCntWall < MAX_CYLINDER; nCntWall++)
	{
		if (g_aMeshCylinder[nCntWall].bUse)
		{
			//���[���h�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aMeshCylinder[nCntWall].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aMeshCylinder[nCntWall].rot.y, g_aMeshCylinder[nCntWall].rot.x, g_aMeshCylinder[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aMeshCylinder[nCntWall].mtxWorld, &g_aMeshCylinder[nCntWall].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_aMeshCylinder[nCntWall].pos.x, g_aMeshCylinder[nCntWall].pos.y, g_aMeshCylinder[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aMeshCylinder[nCntWall].mtxWorld, &g_aMeshCylinder[nCntWall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshCylinder[nCntWall].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshCylinder);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureMeshCylinder);

			//�|���S���`��
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				0,
				g_aMeshCylinder[nCntWall].nNumVtx,								//���_��
				g_aMeshCylinder[nCntWall].nNumIdx * nCntWall,					//�ŏ��̃C���f�b�N�X
				g_aMeshCylinder[nCntWall].nNumIdx - 2							//�|���S����
			);
		}
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==================================================================================================
//���ݒ菈��
//==================================================================================================
void SetMeshCylinder(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntWall = 0; nCntWall < MAX_CYLINDER; nCntWall++)
	{
		if (g_aMeshCylinder[nCntWall].bUse == false)
		{
			g_aMeshCylinder[nCntWall].pos = pos;
			g_aMeshCylinder[nCntWall].rot = rot;

			g_aMeshCylinder[nCntWall].bUse = true;

			//for��������
			break;
		}
	}
}