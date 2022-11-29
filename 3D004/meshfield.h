//==================================================================================================
//
//meshfield.h
//Author:���R����
//
//==================================================================================================

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//�\���̐錾
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	int nNumIdx;							//�C���f�b�N�X��
	int nNumVtx;							//���_��
}MeshField;

//�v���g�^�C�v�錾
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);
#endif