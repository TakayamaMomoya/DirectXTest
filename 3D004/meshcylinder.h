//==================================================================================================
//
//meshwall.h
//Author:髙山桃也
//
//==================================================================================================

#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

//構造体宣言
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	int nNumIdx;							//インデックス数
	int nNumVtx;							//頂点数
	bool bUse;								//使用しているかどうか
}MeshCylinder;

//プロトタイプ宣言
void InitMeshCylinder(void);
void UninitMeshCylinder(void);
void UpdateMeshCylinder(void);
void DrawMeshCylinder(void);
void SetMeshCylinder(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
#endif