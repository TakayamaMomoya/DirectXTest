//==================================================================================================
//
//meshwall.h
//Author:���R����
//
//==================================================================================================

#ifndef _MESHWALL_H_
#define _MESHWALL_H_

//�}�N����`
#define MAX_MESHWALL				(16)										//�ǂ̍ő吔

//�\���̐錾
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	float width;							//��
	float height;							//����
	int nNumIdx;							//�C���f�b�N�X��
	int nNumVtx;							//���_��
	bool bUse;								//�g�p���Ă��邩�ǂ���
}MeshWall;

//�v���g�^�C�v�錾
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float width, float height);
MeshWall *GetMeshWall(void);
#endif