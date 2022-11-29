//==================================================================================================
//
//polygon.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "light.h"
#include "input.h"
#include <stdio.h>

//マクロ定義
#define ROLL_SPEED							(0.03f)						//回るスピード

//グローバル変数
D3DLIGHT9 g_aLight[MAX_LIGHT];				//構造体の情報
int g_nCurrentLight;

//==================================================================================================
//初期化処理
//==================================================================================================
void InitLight(void)
{
	//変数初期化
	g_nCurrentLight = 0;

	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice;
	D3DXVECTOR3 vecDir;

	//デバイスの取得
	pDevice = GetDevice();

	//ライトの種類設定
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光の設定
	g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向設定
	vecDir = D3DXVECTOR3(-1.4f, 0.24f, -2.21f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//ベクトル正規化
	g_aLight[0].Direction = vecDir;

	//ライト設定
	pDevice->SetLight(0, &g_aLight[0]);

	//ライト有効化
	pDevice->LightEnable(0, TRUE);

	//ライト２の設定============================================
	//ライトの種類設定
	g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光の設定
	g_aLight[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向設定
	vecDir = D3DXVECTOR3(1.42f, -0.8f, 0.08f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//ベクトル正規化
	g_aLight[1].Direction = vecDir;

	//ライト設定
	pDevice->SetLight(1, &g_aLight[1]);

	//ライト有効化
	pDevice->LightEnable(1, TRUE);

	//ライト３の設定============================================
	//ライトの種類設定
	g_aLight[2].Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光の設定
	g_aLight[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向設定
	vecDir = D3DXVECTOR3(-0.59f, -0.8f, 1.55f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//ベクトル正規化
	g_aLight[2].Direction = vecDir;

	//ライト設定
	pDevice->SetLight(2, &g_aLight[2]);

	//ライト有効化
	pDevice->LightEnable(2, TRUE);
}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitLight(void)
{
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdateLight(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	//ライト移動================================================
	if (GetKeyboardRepeat(DIK_J) == true)
	{//左移動
		g_aLight[g_nCurrentLight].Direction.x -= ROLL_SPEED;
	}
	if (GetKeyboardRepeat(DIK_L) == true)
	{//右移動
		g_aLight[g_nCurrentLight].Direction.x += ROLL_SPEED;
	}

	if (GetKeyboardRepeat(DIK_I) == true)
	{//奥移動
		g_aLight[g_nCurrentLight].Direction.z += ROLL_SPEED;
	}
	if (GetKeyboardRepeat(DIK_K) == true)
	{//手前移動
		g_aLight[g_nCurrentLight].Direction.z -= ROLL_SPEED;
	}

	if (GetKeyboardRepeat(DIK_U) == true)
	{//上移動
		g_aLight[g_nCurrentLight].Direction.y += ROLL_SPEED;
	}
	if (GetKeyboardRepeat(DIK_M) == true)
	{//下移動
		g_aLight[g_nCurrentLight].Direction.y -= ROLL_SPEED;
	}

	//ライト切り替え================================================
	if (GetKeyboardTrigger(DIK_O) == true)
	{//ライト切り替え
		g_nCurrentLight = (g_nCurrentLight + 1) % MAX_LIGHT;
	}

	for (int nCntLight = 0;nCntLight < MAX_LIGHT;nCntLight++)
	{
		//ベクトル正規化
		D3DXVec3Normalize
		(
			&(D3DXVECTOR3)g_aLight[nCntLight].Direction,
			&(D3DXVECTOR3)g_aLight[nCntLight].Direction
		);

		//ライト設定
		pDevice->SetLight(nCntLight, &g_aLight[nCntLight]);
	}
}

//==================================================================================================
//選択項目取得処理
//==================================================================================================
int GetCurrentLight(void)
{
	return g_nCurrentLight;
}