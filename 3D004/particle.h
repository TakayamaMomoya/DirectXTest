//==================================================================================================
//
//Particle.h
//Author:���R����
//
//==================================================================================================

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include"main.h"

//�p�[�e�B�N���̎��
typedef enum
{
	PARTICLE_TYPE_HIT = 0,								//�q�b�g
	PARTICLE_TYPE_BOOST,								//�u�[�X�^�[
	PARTICLE_TYPE_MAX
}PARTICLE_TYPE;

//�\����
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR3 *pPosOwner = NULL;						//������̏ꏊ�̃|�C���^
	D3DXVECTOR3 posWorld;								//���_����̑��Έʒu
	D3DXVECTOR3 move;									//�ړ���
	D3DXVECTOR3 rot;									//����
	D3DXCOLOR col;										//�F
	float fRadius;										//���a
	int nLife;											//����
	PARTICLE_TYPE type;									//���
	bool bUse;											//�g�p���Ă��邩�ǂ���
}PARTICLE;

//�v���g�^�C�v�錾
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, PARTICLE_TYPE type, D3DXVECTOR3 rot,D3DXVECTOR3 *pPos);
#endif