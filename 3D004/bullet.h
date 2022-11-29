//==================================================================================================
//
//bullet.cpp
//Author:���R����
//
//==================================================================================================

#ifndef _BULLET_H_
#define _BULLET_H_

//�\���̐錾
typedef struct
{
	D3DXVECTOR3 pos;						//���݈ʒu
	D3DXVECTOR3 posOld;						//�O��̈ʒu
	D3DXVECTOR3 move;						//�ړ���
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	int nIdxShadow;							//�e�̔ԍ�
	int nLife;								//����
	bool bUse;								//�g�p���Ă��邩�ǂ���
}Bullet;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
Bullet *GetBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);
void DisableBullet(Bullet *pBullet);
void DrawBulletState(LPD3DXFONT pFont);
#endif