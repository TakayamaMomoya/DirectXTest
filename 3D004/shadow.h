//==================================================================================================
//
//shadow.h
//Author:���R����
//
//==================================================================================================

#ifndef _SHADOW_H_
#define _SHADOW_H_

//�\���̐錾
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXVECTOR3 rot;							//����
	D3DXMATRIX mtxWorld;						//���[���h�}�g���b�N�X
	float fRadius;								//���a
	bool bUse;									//�g�p���Ă��邩�ǂ���
}Shadow;


//�v���g�^�C�v�錾
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(float fRadius);
void SetPositionShadow(int nIdxShadow,D3DXVECTOR3 pos);
Shadow *GetShadow(void);
void EnableShadow(int nIdxShadow, bool bUse);
#endif