//==================================================================================================
//
//model.h
//Author:髙山桃也
//
//==================================================================================================

#ifndef _MODEL_H_
#define _MODEL_H_

//構造体宣言
typedef struct
{
	D3DXVECTOR3 pos;								//位置
	D3DXVECTOR3 rot;								//向き
	D3DXMATRIX g_mtxWorld;							//ワールドマトリックス
}Model;

//プロトタイプ宣言
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void DrawPlayerState(LPD3DXFONT pFont);
#endif