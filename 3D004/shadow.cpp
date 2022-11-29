//==================================================================================================
//
//shadow.cpp
//Author:���R����
//
//==================================================================================================

#include "main.h"
#include "shadow.h"
#include "input.h"

//�}�N����`
#define SHADOW_TEX_FILE			"data\\TEXTURE\\EFFECT\\shadow000.jpg"		//�e�N�X�`���t�@�C����
#define SHADOW_WIDTH			(50)										//��
#define SHADOW_HEIGHT			(50)										//����
#define MAX_SHADOW				(256)										//�e�̍ő吔

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Shadow g_aShadow[MAX_SHADOW];						//�\���̂̏��

//==================================================================================================
//����������
//==================================================================================================
void InitShadow(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		SHADOW_TEX_FILE,
		&g_pTextureShadow);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	//���擾
	Shadow *pShadow = GetShadow();

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++,pShadow++)
	{
		//�ϐ��̏�����
		pShadow->pos = { 0.0f,0.1f,0.0f };
		pShadow->rot = { 0.0f,0.0f,0.0f };
		pShadow->fRadius = 0.0f;
		pShadow->bUse = false;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�|�C���^��i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffShadow->Unlock();
}

//==================================================================================================
//�I������
//==================================================================================================
void UninitShadow(void)
{
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	if (g_pVtxBuffShadow != NULL)
	{//���_�o�b�t�@�|�C���^�̔j��
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//==================================================================================================
//�X�V����
//==================================================================================================
void UpdateShadow(void)
{
}

//==================================================================================================
//�`�揈��
//==================================================================================================
void DrawShadow(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	//���Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���擾
	Shadow *pShadow = GetShadow();

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++,pShadow++)
	{
		if (pShadow->bUse == true)
		{//�g�p���Ă���Ȃ�
		 //���[���h�}�g���b�N�X������
			D3DXMatrixIdentity(&pShadow->mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				pShadow->rot.y, pShadow->rot.x, pShadow->rot.z);
			D3DXMatrixMultiply(&pShadow->mtxWorld, &pShadow->mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				pShadow->pos.x, pShadow->pos.y, pShadow->pos.z);
			D3DXMatrixMultiply(&pShadow->mtxWorld, &pShadow->mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pShadow->mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);

			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntShadow, 2);

		}
	}

	//���Z�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//==================================================================================================
//�ݒ菈��
//==================================================================================================
int SetShadow(float fRadius)
{
	//�ϐ��錾
	int nCntShadow = -1;

	//���擾
	Shadow *pShadow = GetShadow();

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_SHADOW; nCount++, nCntShadow++, pShadow++)
	{
		if (pShadow->bUse == false)
		{//�g�p���Ă��Ȃ���ԂȂ�

			//���a���
			pShadow->fRadius = fRadius;

		    //���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-pShadow->fRadius, 0.0f, pShadow->fRadius);
			pVtx[1].pos = D3DXVECTOR3(pShadow->fRadius, 0.0f, pShadow->fRadius);
			pVtx[2].pos = D3DXVECTOR3(-pShadow->fRadius, 0.0f, -pShadow->fRadius);
			pVtx[3].pos = D3DXVECTOR3(pShadow->fRadius, 0.0f, -pShadow->fRadius);

			//�@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
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
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			nCntShadow = nCount;

			//�g�p��Ԃɂ���
			pShadow->bUse = true;

			//for���𔲂���
			break;
		}

		//�|�C���^��i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffShadow->Unlock();

	return nCntShadow;
}

//==================================================================================================
//�ʒu�ݒ菈��
//==================================================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_aShadow[nIdxShadow].pos = {pos.x,g_aShadow[nIdxShadow].pos.y,pos.z};
}

//==================================================================================================
//���擾����
//==================================================================================================
Shadow *GetShadow(void)
{
	return &g_aShadow[0];
}

//==================================================================================================
//�e�L�������Ǘ�
//==================================================================================================
void EnableShadow(int nIdxShadow, bool bUse)
{
	g_aShadow[nIdxShadow].bUse = bUse;
}