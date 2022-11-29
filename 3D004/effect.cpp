//==================================================================================================
//
//Effect.cpp
//Author:���R����
//
//==================================================================================================

#include "main.h"
#include "effect.h"
#include "player.h"

//�}�N����`
#define MAX_EFFECT				(4096)										//�ő吔
#define LIFE_SPEED				(10)										//�����̌��鑬�x
#define EFFECT_TEX_FILE			"data\\TEXTURE\\effect\\effect000.png"		//�e�N�X�`���t�@�C����
#define ANIM_TIME				(1)											//�A�j���[�V�������s���p�x
#define EFFECT_WIDTH			(10)										//����
#define EFFECT_HEIGHT			(40)										//����
#define MOVE_FACT				(0.96f)										//�ړ������W��

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Effect g_aEffect[MAX_EFFECT];						//�G�t�F�N�g�̏��

//�v���g�^�C�v�錾
void UpdateEffectPos(Effect *pEffect);
void UpdateEffectPolygon(Effect *pEffect,int nCntEffect);

//==================================================================================================
//����������
//==================================================================================================
void InitEffect(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice;

	//�|�C���^�錾
	Effect *pEffect = GetEffect();

	//�ϐ��錾
	int nCntEffect;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		EFFECT_TEX_FILE,
		&g_pTextureEffect);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++,pEffect++)
	{//�S�Ă̒e�̏�����
	    //���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);

		//nor�̐ݒ�
		pVtx[0].nor = { 0.0f,0.0f,-1.0f };
		pVtx[1].nor = { 0.0f,0.0f,-1.0f };
		pVtx[2].nor = { 0.0f,0.0f,-1.0f };
		pVtx[3].nor = { 0.0f,0.0f,-1.0f };

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pEffect->fRadius = 0.0f;
		pEffect->fDecrease = 0.0f;
		pEffect->col = D3DXCOLOR{ 1.0f,1.0f,1.0f,1.0f };
		pEffect->pos = D3DXVECTOR3{ 0.0f,0.0f,0.0f };
		pEffect->move = D3DXVECTOR3{ 0.0f,0.0f,0.0f };
		pEffect->nLife = 0;
		pEffect->bUse = false;					//�e���g�p���Ă��Ȃ���Ԃɂ���

		//���_�f�[�^�̃|�C���^��4���i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//==================================================================================================
//�I������
//==================================================================================================
void UninitEffect(void)
{
	if (g_pTextureEffect != NULL)
	{//�e�N�X�`���ւ̃|�C���^�j��
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	if (g_pVtxBuffEffect != NULL)
	{//���_�o�b�t�@�ւ̃|�C���^�j��
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//==================================================================================================
//�X�V����
//==================================================================================================
void UpdateEffect(void)
{
	//�ϐ��錾
	int nCntEffect;
	
	//�|�C���^�錾
	Effect *pEffect = GetEffect();

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{//�S�Ă̒e�̍X�V

		if (pEffect->bUse)
		{//�g�p����Ă����ԂȂ�

			//�ʒu�X�V����
			UpdateEffectPos(pEffect);

			//���a�̍X�V
			pEffect->fRadius -= pEffect->fDecrease;

			//�����J�E���g�_�E��
			pEffect->nLife -= LIFE_SPEED / 2;

			if (pEffect->nLife <= 0 || pEffect->fRadius <= 0)
			{//�������s������
			 //�g�p���Ă��Ȃ���Ԃɂ���
				pEffect->bUse = false;
			}

			//�|���S���X�V����
			UpdateEffectPolygon(pEffect, nCntEffect);
		}
	}
}

//==================================================================================================
//�ʒu�X�V����
//==================================================================================================
void UpdateEffectPos(Effect *pEffect)
{
	//�ړ��ʌ���
	pEffect->move.x = pEffect->move.x * MOVE_FACT;
	pEffect->move.y = pEffect->move.y * MOVE_FACT;
	pEffect->move.z = pEffect->move.z * MOVE_FACT;

	//�ʒu�̍X�V
	pEffect->pos.x += pEffect->move.x;
	pEffect->pos.y += pEffect->move.y;
	pEffect->pos.z += pEffect->move.z;
}

//==================================================================================================
//�|���S���X�V����
//==================================================================================================
void UpdateEffectPolygon(Effect *pEffect,int nCntEffect)
{
	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	//���_�f�[�^�̃|�C���^��4���i�߂�
	pVtx += 4 * nCntEffect;

	//���_���W�̐ݒ�
	pVtx[0].pos = { -pEffect->fRadius,pEffect->fRadius, 0.0f };
	pVtx[1].pos = { pEffect->fRadius,pEffect->fRadius, 0.0f };
	pVtx[2].pos = { -pEffect->fRadius,-pEffect->fRadius, 0.0f };
	pVtx[3].pos = { pEffect->fRadius,-pEffect->fRadius, 0.0f };

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
	pVtx[1].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
	pVtx[2].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
	pVtx[3].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//==================================================================================================
//�`�揈��
//==================================================================================================
void DrawEffect(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans, mtxView;

	//�|�C���^�錾
	Effect *pEffect = GetEffect();

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, GetAlphaThreshold());

	//Z�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if (pEffect->bUse)
		{
			//���[���h�}�g���b�N�X������
			D3DXMatrixIdentity(&pEffect->mtxWorld);

			//�r���[�}�g���b�N�X�擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����Ɍ�����
			D3DXMatrixInverse(&pEffect->mtxWorld, NULL, &mtxView);
			pEffect->mtxWorld._41 = 0.0f;
			pEffect->mtxWorld._42 = 0.0f;
			pEffect->mtxWorld._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				pEffect->pos.x, pEffect->pos.y, pEffect->pos.z);
			D3DXMatrixMultiply(&pEffect->mtxWorld, &pEffect->mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pEffect->mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);

			if (pEffect->bAdd == true)
			{
				//���u�����f�B���O�����Z�����ɐݒ�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}

			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEffect, 2);

			if (pEffect->bAdd == true)
			{
				//���u�����f�B���O�����ɖ߂�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			}
		}
	}

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
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col,float fRadius, int nLife,bool bAdd,float fDecrease)
{
	//�ϐ��錾
	int nCntEffect;

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//�e�ւ̃|�C���^
	Effect *pEffect = GetEffect();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++,pEffect++)
	{//�S�Ă̒e���`�F�b�N����
		if (pEffect->bUse == false)
		{//�g���Ă��Ȃ���ԂȂ�

			//�ʒu�̐ݒ�
			pEffect->pos = pos;

			//�ʒu�̐ݒ�
			pEffect->move = move;

			//�F�̐ݒ�
			pEffect->col = col;

			//���a�̐ݒ�
			pEffect->fRadius = fRadius;

			//�����ʐݒ�
			pEffect->fDecrease = fDecrease;

			//�����̐ݒ�
			pEffect->nLife = nLife;

			//���_���W�̐ݒ�
			pVtx[0].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
			pVtx[1].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
			pVtx[2].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
			pVtx[3].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };

			//�����̐ݒ�
			pEffect->nLife = nLife;

			//�g�p���Ă���ݒ�
			pEffect->bUse = true;

			//�g�p���Ă���ݒ�
			pEffect->bAdd = bAdd;

			//for���𔲂���
			break;
		}

		//���_�f�[�^�̃|�C���^��4���i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//==================================================================================================
//�|�C���^�擾
//==================================================================================================
Effect *GetEffect(void)
{
	return &g_aEffect[0];
}