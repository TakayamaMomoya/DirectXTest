//==================================================================================================
//
//model.h
//Author:���R����
//
//==================================================================================================

#ifndef _MODEL_H_
#define _MODEL_H_

//�\���̐錾
typedef struct
{
	D3DXVECTOR3 pos;								//�ʒu
	D3DXVECTOR3 rot;								//����
	D3DXMATRIX g_mtxWorld;							//���[���h�}�g���b�N�X
}Model;

//�v���g�^�C�v�錾
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void DrawPlayerState(LPD3DXFONT pFont);
#endif