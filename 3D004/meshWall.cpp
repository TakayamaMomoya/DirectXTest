//==================================================================================================
//
//meshwall.cpp
//Author:���R����
//
//==================================================================================================

#include "main.h"
#include "meshwall.h"
#include "input.h"

//�}�N����`
#define MESHWALL_TEX_FILE			"data\\TEXTURE\\BG\\metal000.jpg"			//�e�N�X�`���t�@�C����
#define MOVE_SPEED					(1.0f)										//�ړ����x
#define MESH_LENGTH					(500.0f)									//���b�V���̈�ӂ̒���
#define MESH_U						(2)											//���̃u���b�N��
#define MESH_V						(1)											//�c�̃u���b�N��
#define MAX_SPLIT					(10)										//�ő啪����
#define SPLIT_TEX_U					(4)											//���̃e�N�X�`��������
#define SPLIT_TEX_V					(1)											//�c�̃e�N�X�`��������

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;									//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;								//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;								//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MeshWall g_aMeshWall[MAX_MESHWALL];												//�\���̂̏��
int g_nMaxIdxMeshWall;															//�ő�C���f�b�N�X��
int g_nMaxVtxMeshWall;															//�ő咸�_��

//==================================================================================================
//����������
//==================================================================================================
void InitMeshWall(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		MESHWALL_TEX_FILE,
		&g_pTextureMeshWall);

	//�������̍ő咸�_��
	g_nMaxVtxMeshWall = (MAX_SPLIT + 1) * (MAX_SPLIT + 1);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nMaxVtxMeshWall * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	//�������̍ő�C���f�b�N�X��
	g_nMaxIdxMeshWall = (MAX_SPLIT + 1) * (MAX_SPLIT + 1) + ((MAX_SPLIT + 1) - 2) * (MAX_SPLIT + 1) + (((MAX_SPLIT + 1) - 2) * 2);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nMaxIdxMeshWall * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	WORD *pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��ւ̃|�C���^���擾
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntWall = 0;nCntWall < MAX_MESHWALL;nCntWall++)
	{
		//�ϐ�������
		g_aMeshWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntWall].bUse = false;
		g_aMeshWall[nCntWall].nNumIdx = 0;
		g_aMeshWall[nCntWall].nNumVtx = 0;
		g_aMeshWall[nCntWall].width = 0;
		g_aMeshWall[nCntWall].height = 0;

		for (int nCntVtx = 0; nCntVtx < g_nMaxVtxMeshWall; nCntVtx++)
		{//���_���̐ݒ�
			pVtx[nCntVtx].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			pVtx[nCntVtx].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[nCntVtx].tex = D3DXVECTOR2(0.0f, 0.0f);
		}

		for (int nCount = 0; nCount < g_nMaxIdxMeshWall; nCount++)
		{//�C���f�b�N�X����
			pIdx[nCount] = 0;
		}

		//�|�C���^��i�߂�
		pIdx += g_nMaxIdxMeshWall;
		pVtx += g_nMaxVtxMeshWall;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshWall->Unlock();

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffMeshWall->Unlock();

	SetMeshWall
	(
		D3DXVECTOR3(0.0f,0.0f,-500.0f),
		D3DXVECTOR3(0.0f,D3DX_PI,0.0f),
		1000.0f,
		150.0f
	);

	SetMeshWall
	(
		D3DXVECTOR3(-500.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),
		1000.0f,
		150.0f
	);

	SetMeshWall
	(
		D3DXVECTOR3(0.0f, 0.0f, 500.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		1000.0f,
		150.0f
	);

	SetMeshWall
	(
		D3DXVECTOR3(500.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		1000.0f,
		150.0f
	);

	SetMeshWall
	(
		D3DXVECTOR3(50.0f, 0.0f, -500.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.8f, 0.0f),
		1000.0f,
		150.0f
	);
}

//==================================================================================================
//�I������
//==================================================================================================
void UninitMeshWall(void)
{
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}

	if (g_pVtxBuffMeshWall != NULL)
	{//���_�o�b�t�@�|�C���^�̔j��
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	if (g_pIdxBuffMeshWall != NULL)
	{//�C���f�b�N�X�o�b�t�@�|�C���^�̔j��
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//==================================================================================================
//�X�V����
//==================================================================================================
void UpdateMeshWall(void)
{
}

//==================================================================================================
//�`�揈��
//==================================================================================================
void DrawMeshWall(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		if (g_aMeshWall[nCntWall].bUse)
		{
			//���[���h�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aMeshWall[nCntWall].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aMeshWall[nCntWall].rot.y, g_aMeshWall[nCntWall].rot.x, g_aMeshWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntWall].mtxWorld, &g_aMeshWall[nCntWall].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_aMeshWall[nCntWall].pos.x, g_aMeshWall[nCntWall].pos.y, g_aMeshWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntWall].mtxWorld, &g_aMeshWall[nCntWall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshWall[nCntWall].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshWall);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureMeshWall);

			//�|���S���`��
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				0,
				g_aMeshWall[nCntWall].nNumVtx,								//���_��
				g_nMaxIdxMeshWall * nCntWall,								//�ŏ��̃C���f�b�N�X
				g_aMeshWall[nCntWall].nNumIdx - 2							//�|���S����
			);
		}
	}
}

//==================================================================================================
//�ǐݒ菈��
//==================================================================================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float width,float height)
{
	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	WORD *pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��ւ̃|�C���^���擾
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		if (g_aMeshWall[nCntWall].bUse == false)
		{
			//�����󂯎��
			g_aMeshWall[nCntWall].pos = pos;
			g_aMeshWall[nCntWall].rot = rot;
			g_aMeshWall[nCntWall].bUse = true;
			g_aMeshWall[nCntWall].width = width;
			g_aMeshWall[nCntWall].height = height;

			//���_���v�Z
			g_aMeshWall[nCntWall].nNumVtx = (MESH_U + 1) * (MESH_V + 1);

			for (int nCountV = 0; nCountV < MESH_V + 1; nCountV++)
			{//���_���W�̐ݒ�
				for (int nCountU = 0; nCountU < MESH_U + 1; nCountU++)
				{
					pVtx[nCountV * (MESH_U + 1) + nCountU].pos.x = (nCountU - ((MESH_U) * 0.5f)) * (width / MESH_U);
					pVtx[nCountV * (MESH_U + 1) + nCountU].pos.z = 0.0f;
					pVtx[nCountV * (MESH_U + 1) + nCountU].pos.y = (MESH_V - nCountV) * (height / MESH_V);

					//�e�N�X�`�����W
					pVtx[nCountV * (MESH_U + 1) + nCountU].tex = D3DXVECTOR2
					(
						((float)SPLIT_TEX_U / MESH_U) * nCountU,
						((float)SPLIT_TEX_V / MESH_V) * nCountV
					);
				}
			}

			for (int nCnt = 0; nCnt < g_aMeshWall[nCntWall].nNumVtx; nCnt++)
			{
				//�@���x�N�g���̐ݒ�
				pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

				//���_�J���[�̐ݒ�
				pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}

			g_aMeshWall[nCntWall].nNumIdx = (MESH_U + 1) * (MESH_V + 1) + ((MESH_V + 1) - 2) * (MESH_U + 1) + (((MESH_V + 1) - 2) * 2);

			for (int nCount = 0; nCount < g_aMeshWall[nCntWall].nNumIdx / 2; nCount++)
			{//�C���f�b�N�X����
				if (
					nCount % ((MESH_U + 1) + (MESH_U + 2) * (nCount / (MESH_U + 2))) == 0
					&& nCount != 0
					)
				{//�܂�Ԃ�
					pIdx[nCount * 2 + 1] = ((MESH_U + 1) * 2) + (MESH_U + 1) * (nCount / (MESH_U + 2));

					pIdx[nCount * 2] = MESH_U + (MESH_U + 1) * (nCount / (MESH_U + 2));
				}
				else
				{//�ʏ�
					pIdx[nCount * 2 + 1] = nCount - (nCount / (MESH_U + 2));

					pIdx[nCount * 2] = (nCount - (nCount / (MESH_U + 2))) + (MESH_U + 1);
				}
			}

			//for��������
			break;
		}

		//�|�C���^��i�߂�
		pIdx += g_nMaxIdxMeshWall;
		pVtx += g_nMaxVtxMeshWall;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshWall->Unlock();

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffMeshWall->Unlock();
}

//==================================================================================================
//�|�C���^�擾����
//==================================================================================================
MeshWall *GetMeshWall(void)
{
	return &g_aMeshWall[0];
}