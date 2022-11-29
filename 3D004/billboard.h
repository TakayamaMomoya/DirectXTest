//==================================================================================================
//
//billboard.cpp
//Author:髙山桃也
//
//==================================================================================================

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//構造体宣言
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	int nIdxShadow;							//影の番号
	bool bUse;								//使用しているかどうか
}BillBoard;


//プロトタイプ宣言
void InitBillBoard(void);
void UninitBillBoard(void);
void UpdateBillBoard(void);
void DrawBillBoard(void);
BillBoard *GetBillBoard(void);
void SetBillBoard(D3DXVECTOR3 pos);
#endif