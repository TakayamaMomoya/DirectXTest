//==================================================================================================
//
//wall.cpp
//Author:���R����
//
//==================================================================================================

#include "main.h"
#include "wall.h"
#include "input.h"

//�}�N����`
#define WALL_TEX_FILE			"data\\TEXTURE\\BG\\metal000.jpg"		//�e�N�X�`���t�@�C����
#define MOVE_SPEED				(1.0f)									//�ړ����x

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Wall g_aWall[MAX_WALL];							//�\���̂̏��

//==================================================================================================
//����������
//==================================================================================================
void InitWall(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		WALL_TEX_FILE,
		&g_pTextureWall);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	//���擾
	Wall *pWall = GetWall();

	for (int nCntWall = 0; nCntWall < MAX_WALL;nCntWall++, pWall++)
	{
		//�ϐ�������
		pWall->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pWall->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pWall->height = 0.0f;
		pWall->width = 0.0f;
		pWall->bUse = false;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

		//�|�C���^��i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffWall->Unlock();

	SetWall
	(
		D3DXVECTOR3(0.0f,0.0f,0.0f + WALL_WIDTH * 0.5f),
		D3DXVECTOR3(0.0f,0.0f,0.0f),
		D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)
	);
	SetWall
	(
		D3DXVECTOR3(WALL_WIDTH * 0.5f, 0.0f, -WALL_WIDTH * 0.5f + WALL_WIDTH * 0.5f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	);
	SetWall
	(
		D3DXVECTOR3(-WALL_WIDTH * 0.5f, 0.0f, -WALL_WIDTH * 0.5f + WALL_WIDTH * 0.5f),
		D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	);
	SetWall
	(
		D3DXVECTOR3(0.0f, 0.0f, -WALL_WIDTH + WALL_WIDTH * 0.5f),
		D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	);

	//������========================================================================
	SetWall
	(
		D3DXVECTOR3(0.0f, 0.0f, -WALL_WIDTH + 0.1f + WALL_WIDTH * 0.5f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f)
	);
	SetWall
	(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f + WALL_WIDTH * 0.5f - 0.1f),
		D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f)
	);
	SetWall
	(
		D3DXVECTOR3(WALL_WIDTH * 0.5f + 0.1f , 0.0f, -WALL_WIDTH * 0.5f + WALL_WIDTH * 0.5f),
		D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f)
	);
	SetWall
	(
		D3DXVECTOR3(-WALL_WIDTH * 0.5f - 0.1f , 0.0f, -WALL_WIDTH * 0.5f + WALL_WIDTH * 0.5f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f)
	);
}

//==================================================================================================
//�I������
//==================================================================================================
void UninitWall(void)
{
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	if (g_pVtxBuffWall != NULL)
	{//���_�o�b�t�@�|�C���^�̔j��
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//==================================================================================================
//�X�V����
//==================================================================================================
void UpdateWall(void)
{
}

//==================================================================================================
//�`�揈��
//==================================================================================================
void DrawWall(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���擾����
	Wall *pWall = GetWall();

	for (int nCntWall = 0;nCntWall < MAX_WALL;nCntWall++,pWall++)
	{
		if (pWall->bUse == true)
		{//�g�p���Ă���ꍇ
		 //���[���h�}�g���b�N�X������
			D3DXMatrixIdentity(&pWall->mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				pWall->rot.y, pWall->rot.x, pWall->rot.z);
			D3DXMatrixMultiply(&pWall->mtxWorld, &pWall->mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				pWall->pos.x, pWall->pos.y, pWall->pos.z);
			D3DXMatrixMultiply(&pWall->mtxWorld, &pWall->mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pWall->mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntWall, 2);
		}
	}
}

//==================================================================================================
//���擾����
//==================================================================================================
Wall *GetWall(void)
{
	return &g_aWall[0];
}

//==================================================================================================
//�ݒ菈��
//==================================================================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXCOLOR col)
{
	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	//���擾����
	Wall *pWall = GetWall();

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pWall++)
	{
		if (pWall->bUse == false)
		{//�g�p���Ă��Ȃ����
			//�ϐ�������
			pWall->pos = pos;
			pWall->rot = rot;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-WALL_WIDTH * 0.5f, WALL_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(WALL_WIDTH * 0.5f, WALL_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-WALL_WIDTH * 0.5f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(WALL_WIDTH * 0.5f, 0.0f, 0.0f);

			//�@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(10.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 10.0f);
			pVtx[3].tex = D3DXVECTOR2(10.0f, 10.0f);

			//�g�p��Ԃɂ���
			pWall->bUse = true;

			//for���𔲂���
			break;
		}

		//�|�C���^��i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffWall->Unlock();
}