//==================================================================================================
//
//wall.cpp
//Author:髙山桃也
//
//==================================================================================================

#ifndef _WALL_H_
#define _WALL_H_

//マクロ定義
#define MAX_WALL				(8)										//壁の最大数
#define WALL_WIDTH				(1000)									//幅	
#define WALL_HEIGHT				(200)									//高さ

//構造体宣言
typedef struct
{
	D3DXVECTOR3 pos;									//位置
	D3DXVECTOR3 rot;									//向き
	D3DXMATRIX mtxWorld;								//ワールドマトリックス
	float width;										//幅
	float height;										//高さ
	float ClsnWidth;									//判定の幅
	float ClsnDepth;									//判定の奥行き
	bool bUse;											//使用しているかどうか
}Wall;

//プロトタイプ宣言
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
Wall *GetWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXCOLOR col);
#endif