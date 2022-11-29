//==================================================================================================
//
//Particle.h
//Author:髙山桃也
//
//==================================================================================================

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include"main.h"

//パーティクルの種類
typedef enum
{
	PARTICLE_TYPE_HIT = 0,								//ヒット
	PARTICLE_TYPE_BOOST,								//ブースター
	PARTICLE_TYPE_MAX
}PARTICLE_TYPE;

//構造体
typedef struct
{
	D3DXVECTOR3 pos;									//位置
	D3DXVECTOR3 *pPosOwner = NULL;						//持ち主の場所のポインタ
	D3DXVECTOR3 posWorld;								//原点からの相対位置
	D3DXVECTOR3 move;									//移動量
	D3DXVECTOR3 rot;									//向き
	D3DXCOLOR col;										//色
	float fRadius;										//半径
	int nLife;											//寿命
	PARTICLE_TYPE type;									//種類
	bool bUse;											//使用しているかどうか
}PARTICLE;

//プロトタイプ宣言
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, PARTICLE_TYPE type, D3DXVECTOR3 rot,D3DXVECTOR3 *pPos);
#endif