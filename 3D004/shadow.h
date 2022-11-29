//==================================================================================================
//
//shadow.h
//Author:髙山桃也
//
//==================================================================================================

#ifndef _SHADOW_H_
#define _SHADOW_H_

//構造体宣言
typedef struct
{
	D3DXVECTOR3 pos;							//位置
	D3DXVECTOR3 rot;							//向き
	D3DXMATRIX mtxWorld;						//ワールドマトリックス
	float fRadius;								//半径
	bool bUse;									//使用しているかどうか
}Shadow;


//プロトタイプ宣言
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(float fRadius);
void SetPositionShadow(int nIdxShadow,D3DXVECTOR3 pos);
Shadow *GetShadow(void);
void EnableShadow(int nIdxShadow, bool bUse);
#endif