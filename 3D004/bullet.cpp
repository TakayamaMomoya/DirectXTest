//==================================================================================================
//
//bullet.cpp
//Author:���R����
//
//==================================================================================================

#include "main.h"
#include "bullet.h"
#include "meshWall.h"
#include "input.h"
#include "shadow.h"
#include "explosion.h"
#include "input.h"
#include "effect.h"
#include <stdio.h>
#include "particle.h"
#include "enemy.h"

//�}�N����`
#define BULLET_TEX_FILE			"data\\TEXTURE\\EFFECT\\effect000.png"		//�e�N�X�`���t�@�C����
#define BULLET_WIDTH			(5)											//��
#define BULLET_HEIGHT			(5)											//����
#define MAX_BULLET				(256)										//�r���{�[�h�̍ő吔
#define NORMAL_LIFE				(60)										//�ʏ����

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;									//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;							//���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];												//�\���̂̏��
int g_nNumBullet;															//�e�̑���

//�v���g�^�C�v�錾
void CollisionWallBullet(Bullet *pBullet);
void CollisionEnemyBullet(Bullet *pBullet);

//==================================================================================================
//����������
//==================================================================================================
void InitBullet(void)
{
	//�ϐ�������
	g_nNumBullet = 0;

	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		BULLET_TEX_FILE,
		&g_pTextureBullet);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//���擾
	Bullet *pBullet = GetBullet();

	for (int nCntBullet = 0;nCntBullet < MAX_BULLET;nCntBullet++, pBullet++)
	{
		//�ϐ�������
		pBullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->bUse = false;
		pBullet->nIdxShadow = 0;
		pBullet->nLife = 0;

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
	g_pVtxBuffBullet->Unlock();

}

//==================================================================================================
//�I������
//==================================================================================================
void UninitBullet(void)
{
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	if (g_pVtxBuffBullet != NULL)
	{//���_�o�b�t�@�|�C���^�̔j��
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//==================================================================================================
//�X�V����
//==================================================================================================
void UpdateBullet(void)
{
	//���擾
	Bullet *pBullet = GetBullet();

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse)
		{
			pBullet->posOld = pBullet->pos;

			//�G�t�F�N�g�ݒ�
			SetEffect
			(
				pBullet->pos,
				D3DXVECTOR3(0.0f,0.0f,0.0f),
				D3DXCOLOR(0.5f,0.5f,1.0f,1.0f),
				10.0f,
				50,
				false,
				2.0f
			);

			//�e�ʒu�X�V����
			pBullet->pos += pBullet->move;

			//�ǂƂ̓����蔻��
			CollisionWallBullet(pBullet);

			//�G�Ƃ̓����蔻��
			CollisionEnemyBullet(pBullet);

			//�e�ʒu�ݒ�
			SetPositionShadow(pBullet->nIdxShadow, pBullet->pos);

			//��������
			pBullet->nLife--;

			if (pBullet->nLife <= 0)
			{//�g�p���Ă��Ȃ���Ԃɂ���
				DisableBullet(pBullet);

				
			}
		}
	}
}

//==================================================================================================
//�ǂƂ̓����蔻��
//==================================================================================================
void CollisionWallBullet(Bullet *pBullet)
{
	//���擾
	MeshWall *pMeshWall = GetMeshWall();

	//�v�Z�p�ϐ�
	D3DXVECTOR3 vecLine, vecToPos;

	for (int nCntWall = 0; nCntWall < MAX_MESHWALL;nCntWall++,pMeshWall++)
	{
		if (pMeshWall->bUse)
		{
			if (CrossProduct(pBullet->posOld, pBullet->pos, pBullet->move,
				D3DXVECTOR3
				(
					pMeshWall->pos.x + sinf(pMeshWall->rot.y + D3DX_PI * 0.5f) * pMeshWall->width * 0.5f,
					0.0f,
					pMeshWall->pos.z + cosf(pMeshWall->rot.y + D3DX_PI * 0.5f) * pMeshWall->width * 0.5f
				),
				D3DXVECTOR3
				(
					pMeshWall->pos.x + sinf(pMeshWall->rot.y - D3DX_PI * 0.5f) * pMeshWall->width * 0.5f,
					0.0f,
					pMeshWall->pos.z + cosf(pMeshWall->rot.y - D3DX_PI * 0.5f) * pMeshWall->width * 0.5f
				)) == true)
			{//���������ꍇ
				SetParticle(pBullet->pos,PARTICLE_TYPE_HIT,D3DXVECTOR3(0.0f,0.0f,0.0f),NULL);

				DisableBullet(pBullet);
			}
		}
	}
}

//==================================================================================================
//�G�Ƃ̓����蔻��
//==================================================================================================
void CollisionEnemyBullet(Bullet *pBullet)
{
	//���擾
	Enemy *pEnemy = GetEnemy();

	for (int nCntEnemy = 0;nCntEnemy < MAX_ENEMY;nCntEnemy++,pEnemy++)
	{
		if (pEnemy->bUse)
		{
			if (SqrCrossProduct(pBullet->posOld, pBullet->pos, pBullet->move, pEnemy->vtxMin, pEnemy->vtxMax) == true)
			{//�G�ɓ���������

				SetParticle(pBullet->pos, PARTICLE_TYPE_HIT, D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL);

				DisableBullet(pBullet);
			}
		}
	}
}

//==================================================================================================
//�`�揈��
//==================================================================================================
void DrawBullet(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans,mtxView;

	//���擾
	Bullet *pBullet = GetBullet();

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, GetAlphaThreshold());

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse)
		{
			//���[���h�}�g���b�N�X������
			D3DXMatrixIdentity(&pBullet->mtxWorld);

			//�r���[�}�g���b�N�X�擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����Ɍ�����
			D3DXMatrixInverse(&pBullet->mtxWorld, NULL, &mtxView);
			pBullet->mtxWorld._41 = 0.0f;
			pBullet->mtxWorld._42 = 0.0f;
			pBullet->mtxWorld._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				pBullet->pos.x, pBullet->pos.y, pBullet->pos.z);
			D3DXMatrixMultiply(&pBullet->mtxWorld, &pBullet->mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pBullet->mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBullet, 2);
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
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//���擾
	Bullet *pBullet = GetBullet();

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{
			//�ϐ��ݒ�
			pBullet->pos = pos;
			pBullet->move = move;
			pBullet->bUse = true;
			pBullet->nIdxShadow = SetShadow(BULLET_WIDTH);
			SetPositionShadow(pBullet->nIdxShadow,pos);
			pBullet->nLife = NORMAL_LIFE;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-BULLET_WIDTH, BULLET_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(BULLET_WIDTH, BULLET_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-BULLET_WIDTH, -BULLET_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(BULLET_WIDTH, -BULLET_HEIGHT, 0.0f);

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

			//�e�����㏸
			g_nNumBullet++;

			break;
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//==================================================================================================
//���擾����
//==================================================================================================
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}

//==================================================================================================
//�e����������
//==================================================================================================
void DisableBullet(Bullet *pBullet)
{
	SetExplosion(pBullet->pos);

	pBullet->bUse = false;
	g_nNumBullet--;

	//�e������
	EnableShadow(pBullet->nIdxShadow, false);
}

//==================================================================================================
//�e�f�o�b�O�\��
//==================================================================================================
void DrawBulletState(LPD3DXFONT pFont)
{
	//�ϐ��錾
	RECT rect = { 250,20,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	sprintf(&aStr[0], "�e�̑���[%d]",g_nNumBullet);

	//�e�L�X�g�`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}