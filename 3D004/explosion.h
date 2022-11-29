//==================================================================================================
//
//explosion.cpp
//Author:髙山桃也
//
//==================================================================================================

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//構造体宣言
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	int nTexU;								//テクスチャ座標
	int nCounterAnim;						//アニメーションカウンター
	bool bUse;								//使用しているかどうか
}Explosion;

//プロトタイプ宣言
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
Explosion *GetExplosion(void);
void SetExplosion(D3DXVECTOR3 pos);
void DisableExplosion(Explosion *pExplosion);
void DrawExplosionState(LPD3DXFONT pFont);
#endif