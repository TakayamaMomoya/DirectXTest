//==================================================================================================
//
//explosion.cpp
//Author:���R����
//
//==================================================================================================

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//�\���̐錾
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	int nTexU;								//�e�N�X�`�����W
	int nCounterAnim;						//�A�j���[�V�����J�E���^�[
	bool bUse;								//�g�p���Ă��邩�ǂ���
}Explosion;

//�v���g�^�C�v�錾
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
Explosion *GetExplosion(void);
void SetExplosion(D3DXVECTOR3 pos);
void DisableExplosion(Explosion *pExplosion);
void DrawExplosionState(LPD3DXFONT pFont);
#endif