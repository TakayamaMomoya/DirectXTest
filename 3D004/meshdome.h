//==================================================================================================
//
//meshdome.h
//Author:髙山桃也
//
//==================================================================================================

#ifndef _MESHDOME_H_
#define _MESHDOME_H_

//構造体宣言
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	int nNumIdx;							//インデックス数
	int nNumVtx;							//頂点数
	bool bUse;								//使用しているかどうか
}MeshDome;

//プロトタイプ宣言
void InitMeshDome(void);
void UninitMeshDome(void);
void UpdateMeshDome(void);
void DrawMeshDome(void);
void SetMeshDome(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
#endif