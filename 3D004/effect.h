//==================================================================================================
//
//Effect.h
//Author:???R????
//
//==================================================================================================

#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"main.h"

//?\????
typedef struct
{
	D3DXVECTOR3 pos;								//?ʒu
	D3DXVECTOR3 move;								//?ړ???
	D3DXMATRIX mtxWorld;							//???[???h?}?g???b?N?X
	D3DXCOLOR col;									//?F
	float fRadius;									//???a
	float fDecrease;								//??????
	int nLife;										//????
	bool bAdd;										//???Z???????邩?ǂ???
	bool bUse;										//?g?p???Ă??邩?ǂ???
}Effect;

//?v???g?^?C?v?錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col,float fRadius,int nLife,bool Add,float fDecrease);
Effect *GetEffect(void);
#endif
