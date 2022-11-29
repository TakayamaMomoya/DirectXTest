//==================================================================================================
//
//meshwall.h
//Author:���R����
//
//==================================================================================================

#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

//�\���̐錾
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	int nNumIdx;							//�C���f�b�N�X��
	int nNumVtx;							//���_��
	bool bUse;								//�g�p���Ă��邩�ǂ���
}MeshCylinder;

//�v���g�^�C�v�錾
void InitMeshCylinder(void);
void UninitMeshCylinder(void);
void UpdateMeshCylinder(void);
void DrawMeshCylinder(void);
void SetMeshCylinder(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
#endif