//==================================================================================================
//
//Particle.cpp
//Author:���R����
//
//==================================================================================================

#include "main.h"
#include "particle.h"
#include "effect.h"
#include "player.h"

//�}�N����`
#define MAX_PARTICLE			(128)					//�p�[�e�B�N���̐�
#define LIFE_SPEED				(10)					//�����̌���X�s�[�h
#define HIT_RADIUS				(7.0f)					//�q�b�g�G�t�F�N�g�T�C�Y
#define HIT_LIFE				(40)					//�q�b�g�G�t�F�N�g����
#define BOOST_RADIUS			(14.0f)					//�u�[�X�g�G�t�F�N�g�T�C�Y
#define BOOST_LIFE				(40)					//�u�[�X�g�G�t�F�N�g����

//�O���[�o���ϐ��錾
PARTICLE g_aParticle[MAX_PARTICLE];						//�G�t�F�N�g�̏��

//==================================================================================================
//����������
//==================================================================================================
void InitParticle(void)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{//�\���̂̏�����
		g_aParticle[nCntParticle].pos = { 0.0f,0.0f,0.0f };
		g_aParticle[nCntParticle].posWorld = { 0.0f,0.0f,0.0f };
		g_aParticle[nCntParticle].move = { 0.0f,0.0f,0.0f };
		g_aParticle[nCntParticle].col = { 0.0f,0.0f,0.0f ,0.0f};
		g_aParticle[nCntParticle].fRadius = 0.0f;
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].type = PARTICLE_TYPE_HIT;
		g_aParticle[nCntParticle].bUse = false;
	}
}

//==================================================================================================
//�I������
//==================================================================================================
void UninitParticle(void)
{
}

//==================================================================================================
//�X�V����
//==================================================================================================
void UpdateParticle(void)
{
	//�ϐ��錾
	int nCntParticle;
	float fRot,fRot2;
	float fMove;
	
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{//�S�Ă̍X�V

		if (g_aParticle[nCntParticle].bUse == true)
		{//�g�p����Ă����ԂȂ�

			if (g_aParticle[nCntParticle].pPosOwner != NULL)
			{
				g_aParticle[nCntParticle].pos = *g_aParticle[nCntParticle].pPosOwner;
			}

			for (int nCntApper = 0; nCntApper < 10; nCntApper++)
			{
				switch (g_aParticle[nCntParticle].type)
				{//�^�C�v�ɂ�镪��
				case PARTICLE_TYPE_HIT:
					//�q�b�g�p�[�e�B�N��==============================================
					//�ړ������̐ݒ�
					fRot = rand() % 629 - 314 / 100.0f;
					fRot2 = rand() % 629 - 314 / 100.0f;

					//�ړ��ʂ̐ݒ�
					fMove = (float)(rand() % 10) / 10 + 1;

					g_aParticle[nCntParticle].move.x = sinf(fRot) * sinf(fRot2) * fMove;
					g_aParticle[nCntParticle].move.y = cosf(fRot) * fMove;
					g_aParticle[nCntParticle].move.z = sinf(fRot) * cosf(fRot2) * fMove;

					//�F�̐ݒ�
					g_aParticle[nCntParticle].col = D3DXCOLOR{ 1.0f,0.7f,0.0f,1.0f };

					//���a�̐ݒ�
					g_aParticle[nCntParticle].fRadius = HIT_RADIUS;

					//�G�t�F�N�g�ݒ�
					SetEffect(g_aParticle[nCntParticle].pos, g_aParticle[nCntParticle].move,
						g_aParticle[nCntParticle].col, g_aParticle[nCntParticle].fRadius, 1000,true,0.2f);
					break;
				case PARTICLE_TYPE_BOOST:
					//�q�b�g�p�[�e�B�N��==============================================
					//�ړ������̐ݒ�
					fRot = g_aParticle[nCntParticle].rot.x + (rand() % 25 / 2) / 200.0f;
					fRot2 = g_aParticle[nCntParticle].rot.y + (rand() % 25 / 2) / 200.0f;

					//�ړ��ʂ̐ݒ�
					fMove = (float)(rand() % 20) / 10 + 10;

					g_aParticle[nCntParticle].move.x = sinf(fRot) * sinf(fRot2) * fMove;
					g_aParticle[nCntParticle].move.y = cosf(fRot) * fMove;
					g_aParticle[nCntParticle].move.z = sinf(fRot) * cosf(fRot2) * fMove;

					//�F�̐ݒ�
					g_aParticle[nCntParticle].col = D3DXCOLOR{ 0.3f,0.3f,0.5f,1.0f };

					//���a�̐ݒ�
					g_aParticle[nCntParticle].fRadius = BOOST_RADIUS;

					//�G�t�F�N�g�ݒ�
					SetEffect(g_aParticle[nCntParticle].pos, g_aParticle[nCntParticle].move,
						g_aParticle[nCntParticle].col, g_aParticle[nCntParticle].fRadius, 1000, true, 1.0f);
					break;
				}
			}

			if (g_aParticle[nCntParticle].nLife <= 0)
			{//�������s������
			 //�g�p���Ă��Ȃ���Ԃɂ���
				g_aParticle[nCntParticle].bUse = false;

				if (g_aParticle[nCntParticle].pPosOwner != NULL)
				{
					g_aParticle[nCntParticle].pPosOwner = NULL;
				}
			}
			//�����J�E���g�_�E��
			g_aParticle[nCntParticle].nLife -= LIFE_SPEED;
		}
	}
}

//==================================================================================================
//�`�揈��
//==================================================================================================
void DrawParticle(void)
{
}

//==================================================================================================
//�ݒ菈��
//==================================================================================================
void SetParticle(D3DXVECTOR3 pos, PARTICLE_TYPE type, D3DXVECTOR3 rot, D3DXVECTOR3 *pPos)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{//�g�p���Ă��Ȃ���ԂȂ�
			//�ʒu�ݒ�
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].type = type;
			g_aParticle[nCntParticle].bUse = true;

			if (pPos != NULL)
			{
				g_aParticle[nCntParticle].pPosOwner = pPos;
			}

			switch (g_aParticle[nCntParticle].type)
			{//�^�C�v�ɂ�镪��
			case PARTICLE_TYPE_HIT:
				g_aParticle[nCntParticle].nLife = 20;
				break;
			case PARTICLE_TYPE_BOOST:
				g_aParticle[nCntParticle].nLife = 20;
				g_aParticle[nCntParticle].rot = rot;
				break;
			}

			break;
		}	
	}
}