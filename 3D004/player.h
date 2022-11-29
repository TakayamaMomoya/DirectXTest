//==================================================================================================
//
//player.h
//Author:髙山桃也
//
//==================================================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//マクロ定義
#define PLAYER_LIFE					(10)									//通常体力
#define INITIAL_MAX_BOOST			(200.0f)								//初期のブースト最大量

//構造体宣言
typedef struct
{
	D3DXVECTOR3 pos;								//位置
	D3DXVECTOR3 move;								//移動量
	D3DXVECTOR3 rot;								//向き
	D3DXMATRIX mtxWorld;							//ワールドマトリックス
	float fBoost;									//ブースト残量
	float fBoostMax;								//ブースト最大量
	int nLife;										//体力
}Player;

typedef struct
{
	D3DXVECTOR3 pos;								//位置
	D3DXVECTOR3 rot;								//向き
	D3DXMATRIX mtxWorld;							//ワールドマトリックス
	LPD3DXMESH pMesh = NULL;						//メッシュへのポインタ
	LPD3DXBUFFER pBuffMat = NULL;					//マテリアルへのバッファ
	DWORD dwNumMat;									//マテリアルの数
	int nIdx;										//番号
	int nIdxParent;									//親の番号
}PlayerPart;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void DrawPlayerState(LPD3DXFONT pFont);
void DrawControlPlayer(LPD3DXFONT pFont);
void DrawPPartState(LPD3DXFONT pFont);
Player *GetPlayer(void);
PlayerPart *GetPlayerPart(void);
#endif