//==================================================================================================
//
//enemy.h
//Author:���R����
//
//==================================================================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//�}�N����`
#define MAX_ENEMY					(128)									//�ő吔

//�񋓌^
typedef enum
{
	ENEMYTYPE_HELI = 0,				//�w��
	ENEMYTYPE_TANK,					//���
	ENEMYTYPE_MAX
}ENEMYTYPE;

//�\���̐錾
typedef struct
{
	D3DXVECTOR3 pos;								//�ʒu
	D3DXVECTOR3 rot;								//����
	D3DXVECTOR3 vtxMin;								//�ŏ����_
	D3DXVECTOR3 vtxMax;								//�ő咸�_
	D3DXMATRIX g_mtxWorld;							//���[���h�}�g���b�N�X
	ENEMYTYPE type;									//���
	bool bUse;										//�g�p���Ă��邩�ǂ���
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
Enemy *GetEnemy(void);
void SetEnemy(D3DXVECTOR3 pos,ENEMYTYPE type);
#endif