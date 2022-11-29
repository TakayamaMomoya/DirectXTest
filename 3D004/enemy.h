//==================================================================================================
//
//enemy.h
//Author:髙山桃也
//
//==================================================================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//マクロ定義
#define MAX_ENEMY					(128)									//最大数

//列挙型
typedef enum
{
	ENEMYTYPE_HELI = 0,				//ヘリ
	ENEMYTYPE_TANK,					//戦車
	ENEMYTYPE_MAX
}ENEMYTYPE;

//構造体宣言
typedef struct
{
	D3DXVECTOR3 pos;								//位置
	D3DXVECTOR3 rot;								//向き
	D3DXVECTOR3 vtxMin;								//最小頂点
	D3DXVECTOR3 vtxMax;								//最大頂点
	D3DXMATRIX g_mtxWorld;							//ワールドマトリックス
	ENEMYTYPE type;									//種類
	bool bUse;										//使用しているかどうか
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
Enemy *GetEnemy(void);
void SetEnemy(D3DXVECTOR3 pos,ENEMYTYPE type);
#endif