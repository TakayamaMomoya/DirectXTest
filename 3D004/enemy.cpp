//==================================================================================================
//
//enemy.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "enemy.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include <stdio.h>

//マクロ定義
#define MOVE_SPEED					(1.0f)									//移動速度
#define NUM_TEX						(8)										//テクスチャ数
#define ROLL_FACT					(0.06f)									//回転減衰係数

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureEnemy[ENEMYTYPE_MAX][NUM_TEX] = {};			//テクスチャへのポインタ
LPD3DXMESH g_pMeshEnemy[ENEMYTYPE_MAX] = {};								//メッシュへのポインタ
LPD3DXBUFFER g_pBuffMatEnemy[ENEMYTYPE_MAX] = {};							//マテリアルへのバッファ
DWORD g_dwNumMatEnemy[ENEMYTYPE_MAX];										//マテリアルの数
Enemy g_aEnemy[MAX_ENEMY];													//構造体の情報

//==================================================================================================
//初期化処理
//==================================================================================================
void InitEnemy(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	//情報取得
	Enemy *pEnemy = GetEnemy();
	
	//変数初期化
	for (int nCount = 0; nCount < ENEMYTYPE_MAX;nCount++)
	{
		g_dwNumMatEnemy[nCount] = 0;
	}

	//Xファイル読み込み
	D3DXLoadMeshFromX("data\\MODEL\\viecle\\ApacheHelicopter.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatEnemy[ENEMYTYPE_HELI],
		NULL,
		&g_dwNumMatEnemy[ENEMYTYPE_HELI],
		&g_pMeshEnemy[ENEMYTYPE_HELI]);

	pMat = (D3DXMATERIAL*)g_pBuffMatEnemy[ENEMYTYPE_HELI]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatEnemy[ENEMYTYPE_HELI]; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャが存在する
			//テクスチャ読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureEnemy[ENEMYTYPE_HELI][nCntMat]);
		}
	}

	//Xファイル読み込み
	D3DXLoadMeshFromX("data\\MODEL\\viecle\\tank000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatEnemy[ENEMYTYPE_TANK],
		NULL,
		&g_dwNumMatEnemy[ENEMYTYPE_TANK],
		&g_pMeshEnemy[ENEMYTYPE_TANK]);

	pMat = (D3DXMATERIAL*)g_pBuffMatEnemy[ENEMYTYPE_TANK]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatEnemy[ENEMYTYPE_TANK]; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャが存在する
		 //テクスチャ読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureEnemy[ENEMYTYPE_TANK][nCntMat]);
		}
	}

	for (int nCntEnemy = 0;nCntEnemy < MAX_ENEMY;nCntEnemy++, pEnemy++)
	{
		//変数初期化
		pEnemy->pos = { 0.0f,0.0f,0.0f };
		pEnemy->rot = { 0.0f,0.0f,0.0f };
		pEnemy->vtxMin = { 0.0f,0.0f,0.0f };
		pEnemy->vtxMax = { 0.0f,0.0f,0.0f };
		pEnemy->type = ENEMYTYPE_HELI;
		pEnemy->bUse = false;

		////頂点数の取得
		//nNumVtx = g_pMeshEnemy->GetNumVertices();

		////フォーマットサイズ入手
		//dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshEnemy->GetFVF());

		////頂点バッファのロック
		//g_pMeshEnemy->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		//for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		//{
		//	D3DXVECTOR3  vtx = *(D3DXVECTOR3*)pVtxBuff;

		//	if (vtx.x > pEnemy->vtxMax.x)
		//	{//Xの最大値
		//		pEnemy->vtxMax.x = vtx.x;
		//	}
		//	else if (vtx.x < pEnemy->vtxMin.x)
		//	{//Xの最小値
		//		pEnemy->vtxMin.x = vtx.x;
		//	}

		//	if (vtx.z > pEnemy->vtxMax.z)
		//	{//Zの最大値
		//		pEnemy->vtxMax.z = vtx.z;
		//	}
		//	else if (vtx.z < pEnemy->vtxMin.z)
		//	{//Zの最小値
		//		pEnemy->vtxMin.z = vtx.z;
		//	}

		//	pVtxBuff += dwSizeFVF;
		//}

		////マテリアルデータへのポインタを取得
		
	}

	SetEnemy(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), ENEMYTYPE_HELI);
	
	SetEnemy(D3DXVECTOR3(300.0f,0.0f,0.0f),ENEMYTYPE_TANK);
}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitEnemy(void)
{
	for (int nCntMesh = 0;nCntMesh < ENEMYTYPE_MAX;nCntMesh++)
	{
		if (g_pMeshEnemy[nCntMesh] != NULL)
		{//メッシュポインタの破棄
			g_pMeshEnemy[nCntMesh]->Release();
			g_pMeshEnemy[nCntMesh] = NULL;
		}
	}

	for (int nCntMat = 0; nCntMat < ENEMYTYPE_MAX; nCntMat++)
	{
		if (g_pBuffMatEnemy[nCntMat] != NULL)
		{//頂点バッファポインタの破棄
			g_pBuffMatEnemy[nCntMat]->Release();
			g_pBuffMatEnemy[nCntMat] = NULL;
		}
	}

	for (int nCntType = 0;nCntType < ENEMYTYPE_MAX;nCntType++)
	{
		for (int nCntTex = 0; nCntTex < NUM_TEX; nCntTex++)
		{
			if (g_apTextureEnemy[nCntType][nCntTex] != NULL)
			{//テクスチャポインタの破棄
				g_apTextureEnemy[nCntType][nCntTex]->Release();
				g_apTextureEnemy[nCntType][nCntTex] = NULL;
			}
		}
	}
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdateEnemy(void)
{

}

//==================================================================================================
//描画処理
//==================================================================================================
void DrawEnemy(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	//情報取得
	Enemy *pEnemy = GetEnemy();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse)
		{
			//ワールドマトリックス初期化
			D3DXMatrixIdentity(&pEnemy->g_mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				pEnemy->rot.y, pEnemy->rot.x, pEnemy->rot.z);
			D3DXMatrixMultiply(&pEnemy->g_mtxWorld, &pEnemy->g_mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				pEnemy->pos.x, pEnemy->pos.y, pEnemy->pos.z);
			D3DXMatrixMultiply(&pEnemy->g_mtxWorld, &pEnemy->g_mtxWorld, &mtxTrans);

			//ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &pEnemy->g_mtxWorld);

			//現在のマテリアル取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatEnemy[pEnemy->type]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatEnemy[pEnemy->type]; nCntMat++)
			{
				//マテリアル設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャ設定
				pDevice->SetTexture(0, g_apTextureEnemy[pEnemy->type][nCntMat]);

				//モデル（パーツ）描画
				g_pMeshEnemy[pEnemy->type]->DrawSubset(nCntMat);
			}

			//マテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//==================================================================================================
//設定処理
//==================================================================================================
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	//情報取得
	Enemy *pEnemy = GetEnemy();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == false)
		{
			//計算用変数
			int nNumVtx;			//頂点数
			DWORD dwSizeFVF;		//頂点フォーマットのサイズ
			BYTE *pVtxBuff;			//頂点バッファへのポインタ

			//情報設定
			pEnemy->bUse = true;
			pEnemy->pos = pos;
			pEnemy->type = type;

			//頂点数の取得
			nNumVtx = g_pMeshEnemy[pEnemy->type]->GetNumVertices();

			//フォーマットサイズ入手
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshEnemy[pEnemy->type]->GetFVF());

			//頂点バッファのロック
			g_pMeshEnemy[pEnemy->type]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3  vtx = *(D3DXVECTOR3*)pVtxBuff;

				if (vtx.x > pEnemy->vtxMax.x)
				{//Xの最大値
					pEnemy->vtxMax.x = vtx.x;
				}
				else if (vtx.x < pEnemy->vtxMin.x)
				{//Xの最小値
					pEnemy->vtxMin.x = vtx.x;
				}

				if (vtx.z > pEnemy->vtxMax.z)
				{//Zの最大値
					pEnemy->vtxMax.z = vtx.z;
				}
				else if (vtx.z < pEnemy->vtxMin.z)
				{//Zの最小値
					pEnemy->vtxMin.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;
			}

			pEnemy->vtxMax = pEnemy->pos + pEnemy->vtxMax;
			pEnemy->vtxMin = pEnemy->pos + pEnemy->vtxMin;

			//頂点バッファのアンロック
			g_pMeshEnemy[pEnemy->type]->UnlockVertexBuffer();

			//for文抜ける
			break;
		}
	}
}

//==================================================================================================
//ポインタ取得処理
//==================================================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}