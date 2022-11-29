//==================================================================================================
//
//player.h
//Author:���R����
//
//==================================================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//�}�N����`
#define PLAYER_LIFE					(10)									//�ʏ�̗�
#define INITIAL_MAX_BOOST			(200.0f)								//�����̃u�[�X�g�ő��

//�\���̐錾
typedef struct
{
	D3DXVECTOR3 pos;								//�ʒu
	D3DXVECTOR3 move;								//�ړ���
	D3DXVECTOR3 rot;								//����
	D3DXMATRIX mtxWorld;							//���[���h�}�g���b�N�X
	float fBoost;									//�u�[�X�g�c��
	float fBoostMax;								//�u�[�X�g�ő��
	int nLife;										//�̗�
}Player;

typedef struct
{
	D3DXVECTOR3 pos;								//�ʒu
	D3DXVECTOR3 rot;								//����
	D3DXMATRIX mtxWorld;							//���[���h�}�g���b�N�X
	LPD3DXMESH pMesh = NULL;						//���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat = NULL;					//�}�e���A���ւ̃o�b�t�@
	DWORD dwNumMat;									//�}�e���A���̐�
	int nIdx;										//�ԍ�
	int nIdxParent;									//�e�̔ԍ�
}PlayerPart;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void DrawPlayerState(LPD3DXFONT pFont);
void DrawControlPlayer(LPD3DXFONT pFont);
void DrawPPartState(LPD3DXFONT pFont);
Player *GetPlayer(void);
PlayerPart *GetPlayerPart(void);
#endif