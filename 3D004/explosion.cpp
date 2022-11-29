//==================================================================================================
//
//explosion.cpp
//Author:���R����
//
//==================================================================================================

#include "main.h"
#include "explosion.h"
#include "input.h"
#include "shadow.h"
#include <stdio.h>

//�}�N����`
#define EXPLOSION_TEX_FILE		"data\\TEXTURE\\EFFECT\\explosion000.png"			//�e�N�X�`���t�@�C����
#define EXPLOSION_WIDTH			(10)											//��
#define EXPLOSION_HEIGHT		(10)											//����
#define MAX_EXPLOSION			(256)											//�r���{�[�h�̍ő吔
#define NORMAL_LIFE				(60)											//�ʏ����
#define ANIM_TIME				(10)												//�A�j���[�V�����̑��x

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;									//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;								//���_�o�b�t�@�ւ̃|�C���^
Explosion g_aExplosion[MAX_EXPLOSION];											//�\���̂̏��
int g_nNumExplosion;															//�e�̑���

//�v���g�^�C�v�錾
void UpdateExplosionPolygon(int nCntExplosion, Explosion *pExplosion);

//==================================================================================================
//����������
//==================================================================================================
void InitExplosion(void)
{
	//�ϐ��錾
	g_nNumExplosion = 0;

	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		EXPLOSION_TEX_FILE,
		&g_pTextureExplosion);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	//���擾
	Explosion *pExplosion = GetExplosion();

	for (int nCntExplosion = 0;nCntExplosion < MAX_EXPLOSION;nCntExplosion++, pExplosion++)
	{
		//�ϐ�������
		pExplosion->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pExplosion->bUse = false;
		pExplosion->nCounterAnim = 0;
		pExplosion->nTexU = 0;

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
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();

}

//==================================================================================================
//�I������
//==================================================================================================
void UninitExplosion(void)
{
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	if (g_pVtxBuffExplosion != NULL)
	{//���_�o�b�t�@�|�C���^�̔j��
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//==================================================================================================
//�X�V����
//==================================================================================================
void UpdateExplosion(void)
{
	//���擾
	Explosion *pExplosion = GetExplosion();

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse)
		{
			UpdateExplosionPolygon(nCntExplosion, pExplosion);
		}
	}
}

//==================================================================================================
//�|���S���X�V����
//==================================================================================================
void UpdateExplosionPolygon(int nCntExplosion, Explosion *pExplosion)
{
	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	//�|�C���^��i�߂�
	pVtx += 4 * nCntExplosion;

	if (pExplosion->nTexU >= 8)
	{
		DisableExplosion(pExplosion);
	}

	pExplosion->nCounterAnim++;

	if (pExplosion->nCounterAnim % ANIM_TIME == 0)
	{//�A�j���[�V�����J�E���^�����̒l�ɒB������
	 //�p�^�[��NO�D�̍X�V
		pExplosion->nTexU++;

		//�e�N�X�`�����W�̍X�V
		pVtx[0].tex = { 0.125f * pExplosion->nTexU,0.0f };
		pVtx[1].tex = { 0.125f + 0.125f * pExplosion->nTexU,0.0f };
		pVtx[2].tex = { 0.125f * pExplosion->nTexU,1.0f };
		pVtx[3].tex = { 0.125f + 0.125f * pExplosion->nTexU,1.0f };
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}

//==================================================================================================
//�`�揈��
//==================================================================================================
void DrawExplosion(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans,mtxView;

	//���擾
	Explosion *pExplosion = GetExplosion();

	//���C�e�B���O�̖�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, GetAlphaThreshold());

	//Z�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse)
		{
			//���[���h�}�g���b�N�X������
			D3DXMatrixIdentity(&pExplosion->mtxWorld);

			//�r���[�}�g���b�N�X�擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����Ɍ�����
			D3DXMatrixInverse(&pExplosion->mtxWorld, NULL, &mtxView);
			pExplosion->mtxWorld._41 = 0.0f;
			pExplosion->mtxWorld._42 = 0.0f;
			pExplosion->mtxWorld._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				pExplosion->pos.x, pExplosion->pos.y, pExplosion->pos.z);
			D3DXMatrixMultiply(&pExplosion->mtxWorld, &pExplosion->mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pExplosion->mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureExplosion);

			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntExplosion, 2);
		}
	}

	//���C�e�B���O�̗L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==================================================================================================
//�ݒ菈��
//==================================================================================================
void SetExplosion(D3DXVECTOR3 pos)
{
	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	//���擾
	Explosion *pExplosion = GetExplosion();

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse == false)
		{
			//�ϐ��ݒ�
			pExplosion->pos = pos;
			pExplosion->bUse = true;
			pExplosion->nCounterAnim = 0;
			pExplosion->nTexU = 0;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-EXPLOSION_WIDTH, -EXPLOSION_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(EXPLOSION_WIDTH, -EXPLOSION_HEIGHT, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

			//�e�����㏸
			g_nNumExplosion++;

			break;
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}

//==================================================================================================
//���擾����
//==================================================================================================
Explosion *GetExplosion(void)
{
	return &g_aExplosion[0];
}

//==================================================================================================
//�e����������
//==================================================================================================
void DisableExplosion(Explosion *pExplosion)
{
	pExplosion->bUse = false;
	g_nNumExplosion--;
}

//==================================================================================================
//�f�o�b�O�\��
//==================================================================================================
void DrawExplosionState(LPD3DXFONT pFont)
{
	//�ϐ��錾
	RECT rect = { 250,40,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	sprintf(&aStr[0], "�����̑���[%d]",g_nNumExplosion);

	//�e�L�X�g�`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}