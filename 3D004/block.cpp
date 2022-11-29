//==================================================================================================
//
//model.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include <stdio.h>

//マクロ定義
#define MOVE_SPEED					(1.0f)									//移動速度
#define NUM_TEX						(8)										//テクスチャ数
#define ROLL_FACT					(0.06f)									//回転減衰係数

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureModel[NUM_TEX] = {};		//テクスチャへのポインタ
LPD3DXMESH g_pMeshModel = NULL;							//メッシュへのポインタ
LPD3DXBUFFER g_pBuffMatModel = NULL;					//マテリアルへのバッファ
DWORD g_dwNumMatModel;									//マテリアルの数
int g_nIdxShadowModel;									//影のインデックス
Model g_model;											//構造体の情報

//==================================================================================================
//初期化処理
//==================================================================================================
void InitModel(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	//変数初期化
	g_model.pos = { 0.0f,0.0f,0.0f };
	g_model.rot = { 0.0f,0.0f,0.0f };
	g_dwNumMatModel = 0;
	g_nIdxShadowModel = 0;

	//Xファイル読み込み
	D3DXLoadMeshFromX("data\\MODEL\\robot000\\01_head.x",
					  D3DXMESH_SYSTEMMEM,
					  pDevice,
					  NULL,
					  &g_pBuffMatModel,
					  NULL,
					  &g_dwNumMatModel,
					  &g_pMeshModel);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャが存在する
		    //テクスチャ読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureModel[nCntMat]);
		}
	}

	//影インデックス取得
	g_nIdxShadowModel = SetShadow();
}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitModel(void)
{
	if (g_pMeshModel != NULL)
	{//メッシュポインタの破棄
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	if (g_pBuffMatModel != NULL)
	{//頂点バッファポインタの破棄
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}

	for (int nCntTex = 0;nCntTex < NUM_TEX;nCntTex++)
	{
		if (g_apTextureModel[nCntTex] != NULL)
		{//テクスチャポインタの破棄
			g_apTextureModel[nCntTex]->Release();
			g_apTextureModel[nCntTex] = NULL;
		}
	}
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdateModel(void)
{
	//情報取得
	Camera *pCamera = GetCamera();

	//操作処理======================================================
	if (GetKeyboardRepeat(DIK_UP) == true)
	{//前移動
		g_model.pos.x += sinf(pCamera->rot.y) * MOVE_SPEED;
		g_model.pos.z += cosf(pCamera->rot.y) * MOVE_SPEED;
	}
	else if (GetKeyboardRepeat(DIK_DOWN) == true)
	{//後移動
		g_model.pos.x += sinf(pCamera->rot.y + D3DX_PI) * MOVE_SPEED;
		g_model.pos.z += cosf(pCamera->rot.y + D3DX_PI) * MOVE_SPEED;
	}
	else if (GetKeyboardRepeat(DIK_LEFT) == true)
	{//左移動
		g_model.pos.x += sinf(pCamera->rot.y - D3DX_PI * 0.5f) * MOVE_SPEED;
		g_model.pos.z += cosf(pCamera->rot.y - D3DX_PI * 0.5f) * MOVE_SPEED;
	}
	else if (GetKeyboardRepeat(DIK_RIGHT) == true)
	{//右移動
		g_model.pos.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f) * MOVE_SPEED;
		g_model.pos.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f) * MOVE_SPEED;
	}

	if (GetKeyboardRepeat(DIK_LSHIFT) == true)
	{
		g_model.rot.y += 0.01f;
	}
	if (GetKeyboardRepeat(DIK_RSHIFT) == true)
	{
		g_model.rot.y -= 0.01f;
	}

	//カメラの奥に向く==================================================
	//差分角度を取得
	float fRotDiff = pCamera->rot.y - g_model.rot.y;

	//角度の修正
	if (fRotDiff < 0)
	{
		fRotDiff += 6.28f;
	}
	else if (fRotDiff > 0)
	{
		fRotDiff -= 6.28f;
	}

	//角度補正
	g_model.rot.y += fRotDiff * ROLL_FACT;

	//角度の修正
	if (fRotDiff < 0)
	{
		fRotDiff += 6.28f;
	}
	else if (fRotDiff > 0)
	{
		fRotDiff -= 6.28f;
	}

	//角度補正
	g_model.rot.y += fRotDiff * ROLL_FACT;

	//===================================================================

	if (g_model.rot.y > D3DX_PI)
	{
		g_model.rot.y = -D3DX_PI;
	}
	if (g_model.rot.y < -D3DX_PI)
	{
		g_model.rot.y = D3DX_PI;
	}

	//影の位置設定
	SetPositionShadow(g_nIdxShadowModel, g_model.pos);
}

//==================================================================================================
//描画処理
//==================================================================================================
void DrawModel(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&g_model.g_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll (&mtxRot,
		g_model.rot.y, g_model.rot.x, g_model.rot.z);
	D3DXMatrixMultiply(&g_model.g_mtxWorld, &g_model.g_mtxWorld,&mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		g_model.pos.x, g_model.pos.y, g_model.pos.z);
	D3DXMatrixMultiply(&g_model.g_mtxWorld, &g_model.g_mtxWorld, &mtxTrans);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD,&g_model.g_mtxWorld);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		//マテリアル設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャ設定
		pDevice->SetTexture(0, g_apTextureModel[nCntMat]);

		//モデル（パーツ）描画
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//==================================================================================================
//プレイヤー状態描画(デバッグ)
//==================================================================================================
void DrawPlayerState(LPD3DXFONT pFont)
{
	//変数宣言
	RECT rect = { 20,500,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	sprintf(&aStr[0], "プレイヤーの位置[%.2f,%.2f,%.2f]\nプレイヤーの向き[%.2f,%.2f,%.2f]", 
		g_model.pos.x, g_model.pos.y, g_model.pos.z,g_model.rot.x, g_model.rot.y, g_model.rot.z);

	//テキスト描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}