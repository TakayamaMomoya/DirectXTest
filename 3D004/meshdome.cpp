//==================================================================================================
//
//meshdome.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "meshdome.h"
#include "input.h"
#include "light.h"

//マクロ定義
#define MESHDOME_TEX_FILE		"data\\TEXTURE\\BG\\sky000.png"					//テクスチャファイル名
#define MOVE_SPEED					(1.0f)										//移動速度
#define MESH_LENGTH					(300.0f)									//メッシュの一辺の長さ
#define MESH_U						(16)										//横のブロック数
#define MESH_V						(3)											//縦のブロック数
#define MAX_DOME					(8)											//筒の最大数
#define SPLIT_TEX_U					(3)											//横のテクスチャ分割数
#define SPLIT_TEX_V					(1)											//縦のテクスチャ分割数

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureMeshDome = NULL;									//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshDome = NULL;								//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshDome = NULL;								//インデックスバッファへのポインタ
MeshDome g_aMeshDome[MAX_DOME];													//構造体の情報

//==================================================================================================
//初期化処理
//==================================================================================================
void InitMeshDome(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		MESHDOME_TEX_FILE,
		&g_pTextureMeshDome);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (MESH_U + 1) * 2 * (MESH_V + 1) * MAX_DOME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshDome,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((MESH_U + 1) * 2 * (MESH_V + 1) + ((MESH_V + 1) - 2) * (MESH_U + 1) + (((MESH_V + 1) - 2) * 2)) * MAX_DOME,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshDome,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshDome->Lock(0, 0, (void**)&pVtx, 0);

	//インデックスバッファへのポインタ
	WORD *pIdx;

	//インデックスバッファをロックし、頂点番号へのポインタを取得
	g_pIdxBuffMeshDome->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntWall = 0;nCntWall < MAX_DOME;nCntWall++)
	{
		//変数初期化
		g_aMeshDome[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshDome[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshDome[nCntWall].bUse = false;

		//計算用変数
		int nCountU, nCountV;
		float fRotX, fRotY;
		float fLength = 2000.0f;
		D3DXVECTOR3 VecRot;

		//頂点情報==================================================================================
		//最大頂点数計算
		g_aMeshDome[nCntWall].nNumVtx = (MESH_U + 1) * (MESH_V + 1) + (MESH_U + 1);	//四角形の分と、蓋の円形の分
		
		for (nCountV = 0; nCountV < MESH_V + 1; nCountV++)
		{//頂点座標の設定

			fRotX = D3DX_PI * 0.5f - nCountV * (D3DX_PI * 0.5f / MESH_V - 1);

			for (nCountU = 0; nCountU < MESH_U + 1; nCountU++)
			{
				//角度算出
				fRotY = -nCountU * (D3DX_PI / MESH_U) * 2;

				pVtx[nCountV * (MESH_U + 1) + nCountU].pos.x = sinf(fRotX) * sinf(fRotY) * fLength;
				pVtx[nCountV * (MESH_U + 1) + nCountU].pos.y = -cosf(fRotX) * fLength;
				pVtx[nCountV * (MESH_U + 1) + nCountU].pos.z = sinf(fRotX) * cosf(fRotY) * fLength;

				//テクスチャ座標
				pVtx[nCountV * (MESH_U + 1) + nCountU].tex = D3DXVECTOR2
				(
					((float)SPLIT_TEX_U / MESH_U) * nCountU,
					((float)SPLIT_TEX_V / MESH_V) * nCountV
				);

				VecRot = D3DXVECTOR3
				(
					pVtx[nCountV * (MESH_U + 1) + nCountU].pos.x,
					0.0f,
					pVtx[nCountV * (MESH_U + 1) + nCountU].pos.z
				);

				//ベクトル正規化
				D3DXVec3Normalize(&VecRot, &VecRot);

				//法線ベクトルの設定
				pVtx[nCountV * (MESH_U + 1) + nCountU].nor = VecRot;
			}
		}

		////蓋の頂点=====================================================================
		//pVtx[86].pos.x = 0.0f;
		//pVtx[86].pos.y = fLength;
		//pVtx[86].pos.z = 0.0f;

		//fRotX = D3DX_PI - D3DX_PI / MESH_U;

		//for (int nCntFan = 0; nCntFan < MESH_U; nCntFan++)
		//{
		//	//角度算出
		//	fRotY = -nCntFan * (D3DX_PI / MESH_U) * 2;

		//	pVtx[86 + nCntFan].pos.x = sinf(fRotX) * sinf(fRotY) * fLength;
		//	pVtx[86 + nCntFan].pos.y = -cosf(fRotX) * fLength;
		//	pVtx[86 + nCntFan].pos.z = sinf(fRotX) * cosf(fRotY) * fLength;
		//}

		for (int nCnt = 0; nCnt < g_aMeshDome[nCntWall].nNumVtx; nCnt++)
		{
			//頂点カラーの設定
			pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		//インデックス==================================================================================
		g_aMeshDome[nCntWall].nNumIdx = (MESH_U + 1) * (MESH_V + 1) + ((MESH_V + 1) - 2) * (MESH_U + 1) + (((MESH_V + 1) - 2) * 2) + (MESH_U + 1);

		int nCntIdx;

		for (nCntIdx = 0; nCntIdx < (g_aMeshDome[nCntWall].nNumIdx - MESH_U - 1) / 2; nCntIdx++)
		{//インデックス決定
			if (
				nCntIdx % ((MESH_U + 1) + (MESH_U + 2) * (nCntIdx / (MESH_U + 2))) == 0
				&& nCntIdx != 0
				)
			{
				pIdx[nCntIdx * 2 + 1] = ((MESH_U + 1) * 2) + (MESH_U + 1) * (nCntIdx / (MESH_U + 2));

				pIdx[nCntIdx * 2] = MESH_U + (MESH_U + 1) * (nCntIdx / (MESH_U + 2));
			}
			else
			{
				pIdx[nCntIdx * 2 + 1] = nCntIdx - (nCntIdx / (MESH_U + 2));

				pIdx[nCntIdx * 2] = (nCntIdx - (nCntIdx / (MESH_U + 2))) + (MESH_U + 1);
			}
		}

		//ポインタを進める
		pIdx += g_aMeshDome[nCntWall].nNumIdx;
		pVtx += g_aMeshDome[nCntWall].nNumVtx;
	}

	//頂点バッファをアンロック
	g_pVtxBuffMeshDome->Unlock();

	//インデックスバッファをアンロック
	g_pIdxBuffMeshDome->Unlock();

	SetMeshDome
	(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	);
}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitMeshDome(void)
{
	if (g_pTextureMeshDome != NULL)
	{
		g_pTextureMeshDome->Release();
		g_pTextureMeshDome = NULL;
	}

	if (g_pVtxBuffMeshDome != NULL)
	{//頂点バッファポインタの破棄
		g_pVtxBuffMeshDome->Release();
		g_pVtxBuffMeshDome = NULL;
	}

	if (g_pIdxBuffMeshDome != NULL)
	{//インデックスバッファポインタの破棄
		g_pIdxBuffMeshDome->Release();
		g_pIdxBuffMeshDome = NULL;
	}
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdateMeshDome(void)
{
}

//==================================================================================================
//描画処理
//==================================================================================================
void DrawMeshDome(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntWall = 0; nCntWall < MAX_DOME; nCntWall++)
	{
		if (g_aMeshDome[nCntWall].bUse)
		{
			//ワールドマトリックス初期化
			D3DXMatrixIdentity(&g_aMeshDome[nCntWall].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aMeshDome[nCntWall].rot.y, g_aMeshDome[nCntWall].rot.x, g_aMeshDome[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aMeshDome[nCntWall].mtxWorld, &g_aMeshDome[nCntWall].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_aMeshDome[nCntWall].pos.x, g_aMeshDome[nCntWall].pos.y, g_aMeshDome[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aMeshDome[nCntWall].mtxWorld, &g_aMeshDome[nCntWall].mtxWorld, &mtxTrans);

			//ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshDome[nCntWall].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshDome, 0, sizeof(VERTEX_3D));

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffMeshDome);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャ設定
			pDevice->SetTexture(0, g_pTextureMeshDome);

			//ポリゴン描画
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				0,
				g_aMeshDome[nCntWall].nNumVtx - MESH_U + 1,					//頂点数(蓋を除く)
				g_aMeshDome[nCntWall].nNumIdx * nCntWall,					//最初のインデックス
				g_aMeshDome[nCntWall].nNumIdx - 2 - MESH_U					//ポリゴン数(〃)
			);

			//ポリゴン描画
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLEFAN,
				0,
				0,
				MESH_U + 1,														//頂点数(蓋)
				g_aMeshDome[nCntWall].nNumIdx - MESH_U - 1,						//最初のインデックス(蓋のところから)
				MESH_U															//ポリゴン数(〃)
			);
		}
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==================================================================================================
//筒設定処理
//==================================================================================================
void SetMeshDome(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntWall = 0; nCntWall < MAX_DOME; nCntWall++)
	{
		if (g_aMeshDome[nCntWall].bUse == false)
		{
			g_aMeshDome[nCntWall].pos = pos;
			g_aMeshDome[nCntWall].rot = rot;

			g_aMeshDome[nCntWall].bUse = true;

			//for文抜ける
			break;
		}
	}
}