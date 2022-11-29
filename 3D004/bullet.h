//==================================================================================================
//
//bullet.cpp
//Author:髙山桃也
//
//==================================================================================================

#ifndef _BULLET_H_
#define _BULLET_H_

//構造体宣言
typedef struct
{
	D3DXVECTOR3 pos;						//現在位置
	D3DXVECTOR3 posOld;						//前回の位置
	D3DXVECTOR3 move;						//移動量
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	int nIdxShadow;							//影の番号
	int nLife;								//寿命
	bool bUse;								//使用しているかどうか
}Bullet;

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
Bullet *GetBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);
void DisableBullet(Bullet *pBullet);
void DrawBulletState(LPD3DXFONT pFont);
#endif