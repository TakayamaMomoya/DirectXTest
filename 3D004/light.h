//==================================================================================================
//
//light.h
//Author:髙山桃也
//
//==================================================================================================

#ifndef _LIGHT_H_
#define _LIGHT_H_

//マクロ定義
#define MAX_LIGHT				(3)			//ライトの最大数

//プロトタイプ宣言
void InitLight(void);
void UninitLight(void);
void UpdateLight(void);
int GetCurrentLight(void);
#endif