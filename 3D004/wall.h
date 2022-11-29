//==================================================================================================
//
//wall.cpp
//Author:���R����
//
//==================================================================================================

#ifndef _WALL_H_
#define _WALL_H_

//�}�N����`
#define MAX_WALL				(8)										//�ǂ̍ő吔
#define WALL_WIDTH				(1000)									//��	
#define WALL_HEIGHT				(200)									//����

//�\���̐錾
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR3 rot;									//����
	D3DXMATRIX mtxWorld;								//���[���h�}�g���b�N�X
	float width;										//��
	float height;										//����
	float ClsnWidth;									//����̕�
	float ClsnDepth;									//����̉��s��
	bool bUse;											//�g�p���Ă��邩�ǂ���
}Wall;

//�v���g�^�C�v�錾
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
Wall *GetWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXCOLOR col);
#endif