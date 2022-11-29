//==================================================================================================
//
//meshwall.h
//Author:髙山桃也
//
//==================================================================================================

#ifndef _MESHWALL_H_
#define _MESHWALL_H_

//マクロ定義
#define MAX_MESHWALL				(16)										//壁の最大数

//構造体宣言
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	float width;							//幅
	float height;							//高さ
	int nNumIdx;							//インデックス数
	int nNumVtx;							//頂点数
	bool bUse;								//使用しているかどうか
}MeshWall;

//プロトタイプ宣言
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float width, float height);
MeshWall *GetMeshWall(void);
#endif