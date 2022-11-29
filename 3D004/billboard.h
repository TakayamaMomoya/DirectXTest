//==================================================================================================
//
//billboard.cpp
//Author:���R����
//
//==================================================================================================

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//�\���̐錾
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	int nIdxShadow;							//�e�̔ԍ�
	bool bUse;								//�g�p���Ă��邩�ǂ���
}BillBoard;


//�v���g�^�C�v�錾
void InitBillBoard(void);
void UninitBillBoard(void);
void UpdateBillBoard(void);
void DrawBillBoard(void);
BillBoard *GetBillBoard(void);
void SetBillBoard(D3DXVECTOR3 pos);
#endif