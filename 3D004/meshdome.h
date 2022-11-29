//==================================================================================================
//
//meshdome.h
//Author:���R����
//
//==================================================================================================

#ifndef _MESHDOME_H_
#define _MESHDOME_H_

//�\���̐錾
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	int nNumIdx;							//�C���f�b�N�X��
	int nNumVtx;							//���_��
	bool bUse;								//�g�p���Ă��邩�ǂ���
}MeshDome;

//�v���g�^�C�v�錾
void InitMeshDome(void);
void UninitMeshDome(void);
void UpdateMeshDome(void);
void DrawMeshDome(void);
void SetMeshDome(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
#endif