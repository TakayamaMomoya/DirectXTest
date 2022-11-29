//==================================================================================================
//
//meshfield.h
//Author:髙山桃也
//
//==================================================================================================

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//構造体宣言
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	int nNumIdx;							//インデックス数
	int nNumVtx;							//頂点数
}MeshField;

//プロトタイプ宣言
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);
#endif