//==================================================================================================
//
//billborad.cpp
//Author:���R����
//
//==================================================================================================

#include "main.h"
#include "billboard.h"
#include "input.h"
#include "shadow.h"

//�}�N����`
#define BILLBOARD_TEX_FILE			"data\\TEXTURE\\BG\\tree000.png"		//�e�N�X�`���t�@�C����
#define BILLBOARD_WIDTH				(50)									//��
#define BILLBOARD_HEIGHT			(50)									//����
#define MAX_BILLBOARD				(256)									//�r���{�[�h�̍ő吔

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBillBoard = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillBoard = NULL;	//���_�o�b�t�@�ւ̃|�C���^
BillBoard g_aBillBoard[MAX_BILLBOARD];				//�\���̂̏��

//==================================================================================================
//����������
//==================================================================================================
void InitBillBoard(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		BILLBOARD_TEX_FILE,
		&g_pTextureBillBoard);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillBoard,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBillBoard->Lock(0, 0, (void**)&pVtx, 0);

	//���擾
	BillBoard *pBillBoard = GetBillBoard();

	for (int nCntBillBoard = 0;nCntBillBoard < MAX_BILLBOARD;nCntBillBoard++, pBillBoard++)
	{
		//�ϐ�������
		pBillBoard->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBillBoard->bUse = false;
		pBillBoard->nIdxShadow = 0;

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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBillBoard->Unlock();

	SetBillBoard(D3DXVECTOR3(0.0f, 50.0f, -100.0f));
	SetBillBoard(D3DXVECTOR3(0.0f, 50.0f, -200.0f));
}

//==================================================================================================
//�I������
//==================================================================================================
void UninitBillBoard(void)
{
	if (g_pTextureBillBoard != NULL)
	{
		g_pTextureBillBoard->Release();
		g_pTextureBillBoard = NULL;
	}

	if (g_pVtxBuffBillBoard != NULL)
	{//���_�o�b�t�@�|�C���^�̔j��
		g_pVtxBuffBillBoard->Release();
		g_pVtxBuffBillBoard = NULL;
	}
}

//==================================================================================================
//�X�V����
//==================================================================================================
void UpdateBillBoard(void)
{
}

//==================================================================================================
//�`�揈��
//==================================================================================================
void DrawBillBoard(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans,mtxView;

	//���擾
	BillBoard *pBillBoard = GetBillBoard();

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, GetAlphaThreshold());

	for (int nCntBillBoard = 0; nCntBillBoard < MAX_BILLBOARD; nCntBillBoard++, pBillBoard++)
	{
		if (pBillBoard->bUse)
		{
			//���[���h�}�g���b�N�X������
			D3DXMatrixIdentity(&pBillBoard->mtxWorld);

			//�r���[�}�g���b�N�X�擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����Ɍ�����
			D3DXMatrixInverse(&pBillBoard->mtxWorld, NULL, &mtxView);
			pBillBoard->mtxWorld._41 = 0.0f;
			pBillBoard->mtxWorld._42 = 0.0f;
			pBillBoard->mtxWorld._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				pBillBoard->pos.x, pBillBoard->pos.y, pBillBoard->pos.z);
			D3DXMatrixMultiply(&pBillBoard->mtxWorld, &pBillBoard->mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pBillBoard->mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillBoard, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureBillBoard);

			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBillBoard, 2);
		}	
	}

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==================================================================================================
//�ݒ菈��
//==================================================================================================
void SetBillBoard(D3DXVECTOR3 pos)
{
	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBillBoard->Lock(0, 0, (void**)&pVtx, 0);

	//���擾
	BillBoard *pBillBoard = GetBillBoard();

	for (int nCntBillBoard = 0; nCntBillBoard < MAX_BILLBOARD; nCntBillBoard++, pBillBoard++)
	{
		if (pBillBoard->bUse == false)
		{
			//�ϐ��ݒ�
			pBillBoard->pos = pos;
			pBillBoard->bUse = true;
			pBillBoard->nIdxShadow = SetShadow(BILLBOARD_WIDTH);
			SetPositionShadow(pBillBoard->nIdxShadow,pos);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_WIDTH, BILLBOARD_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(BILLBOARD_WIDTH, BILLBOARD_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_WIDTH, -BILLBOARD_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(BILLBOARD_WIDTH, -BILLBOARD_HEIGHT, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBillBoard->Unlock();
}

//==================================================================================================
//���擾����
//==================================================================================================
BillBoard *GetBillBoard(void)
{
	return &g_aBillBoard[0];
}