//==================================================================================================
//
//meshcylinder.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "meshcylinder.h"
#include "input.h"
#include "light.h"

//マクロ定義
#define MESHCYLINDER_TEX_FILE		"data\\TEXTURE\\BG\\sky000.png"				//テクスチャファイル名
#define MOVE_SPEED					(1.0f)										//移動速度
#define MESH_LENGTH					(300.0f)									//メッシュの一辺の長さ
#define MESH_U						(16)										//横のブロック数
#define MESH_V						(1)											//縦のブロック数
#define MAX_CYLINDER				(8)											//筒の最大数
#define SPLIT_TEX_U					(3)											//横のテクスチャ分割数
#define SPLIT_TEX_V					(1)											//縦のテクスチャ分割数

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;									//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;								//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;								//インデックスバッファへのポインタ
MeshCylinder g_aMeshCylinder[MAX_CYLINDER];												//構造体の情報

//==================================================================================================
//初期化処理
//==================================================================================================
void InitMeshCylinder(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		MESHCYLINDER_TEX_FILE,
		&g_pTextureMeshCylinder);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (MESH_U + 1) * (MESH_V + 1) * MAX_CYLINDER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((MESH_U + 1) * (MESH_V + 1) + ((MESH_V + 1) - 2) * (MESH_U + 1) + (((MESH_V + 1) - 2) * 2)) * MAX_CYLINDER,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	//インデックスバッファへのポインタ
	WORD *pIdx;

	//インデックスバッファをロックし、頂点番号へのポインタを取得
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntWall = 0;nCntWall < MAX_CYLINDER;nCntWall++)
	{
		//最大頂点数計算
		g_aMeshCylinder[nCntWall].nNumVtx = (MESH_U + 1) * (MESH_V + 1);

		//変数初期化
		g_aMeshCylinder[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshCylinder[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshCylinder[nCntWall].bUse = false;

		//計算用変数
		float fRot;
		float fLength = 2000.0f;
		D3DXVECTOR3 VecRot;

		//頂点情報==================================================================================
		for (int nCountV = 0; nCountV < MESH_V + 1; nCountV++)
		{//頂点座標の設定
			for (int nCountU = 0; nCountU < MESH_U + 1; nCountU++)
			{
				//角度算出
				fRot = nCountU * (D3DX_PI / MESH_U) * 2;

				pVtx[nCountV * (MESH_U + 1) + nCountU].pos.x = (float)sin(fRot) * fLength;
				pVtx[nCountV * (MESH_U + 1) + nCountU].pos.y = (MESH_V - nCountV) * MESH_LENGTH;
				pVtx[nCountV * (MESH_U + 1) + nCountU].pos.z = cosf(fRot) * fLength;

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

		for (int nCnt = 0; nCnt < g_aMeshCylinder[nCntWall].nNumVtx; nCnt++)
		{
			//頂点カラーの設定
			pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		//インデックス==================================================================================
		g_aMeshCylinder[nCntWall].nNumIdx = (MESH_U + 1) * (MESH_V + 1) + ((MESH_V + 1) - 2) * (MESH_U + 1) + (((MESH_V + 1) - 2) * 2);

		for (int nCount = 0; nCount < g_aMeshCylinder[nCntWall].nNumIdx / 2; nCount++)
		{//インデックス決定
			if (
				nCount % ((MESH_U + 1) + (MESH_U + 2) * (nCount / (MESH_U + 2))) == 0
				&& nCount != 0
				)
			{
				pIdx[nCount * 2 + 1] = ((MESH_U + 1) * 2) + (MESH_U + 1) * (nCount / (MESH_U + 2));

				pIdx[nCount * 2] = MESH_U + (MESH_U + 1) * (nCount / (MESH_U + 2));
			}
			else
			{
				pIdx[nCount * 2 + 1] = nCount - (nCount / (MESH_U + 2));

				pIdx[nCount * 2] = (nCount - (nCount / (MESH_U + 2))) + (MESH_U + 1);
			}
		}

		//ポインタを進める
		pIdx += g_aMeshCylinder[nCntWall].nNumIdx;
		pVtx += g_aMeshCylinder[nCntWall].nNumVtx;
	}

	//頂点バッファをアンロック
	g_pVtxBuffMeshCylinder->Unlock();

	//インデックスバッファをアンロック
	g_pIdxBuffMeshCylinder->Unlock();

	SetMeshCylinder
	(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	);
}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitMeshCylinder(void)
{
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}

	if (g_pVtxBuffMeshCylinder != NULL)
	{//頂点バッファポインタの破棄
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	if (g_pIdxBuffMeshCylinder != NULL)
	{//インデックスバッファポインタの破棄
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdateMeshCylinder(void)
{
}

//==================================================================================================
//描画処理
//==================================================================================================
void DrawMeshCylinder(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntWall = 0; nCntWall < MAX_CYLINDER; nCntWall++)
	{
		if (g_aMeshCylinder[nCntWall].bUse)
		{
			//ワールドマトリックス初期化
			D3DXMatrixIdentity(&g_aMeshCylinder[nCntWall].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aMeshCylinder[nCntWall].rot.y, g_aMeshCylinder[nCntWall].rot.x, g_aMeshCylinder[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aMeshCylinder[nCntWall].mtxWorld, &g_aMeshCylinder[nCntWall].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_aMeshCylinder[nCntWall].pos.x, g_aMeshCylinder[nCntWall].pos.y, g_aMeshCylinder[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aMeshCylinder[nCntWall].mtxWorld, &g_aMeshCylinder[nCntWall].mtxWorld, &mtxTrans);

			//ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshCylinder[nCntWall].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffMeshCylinder);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャ設定
			pDevice->SetTexture(0, g_pTextureMeshCylinder);

			//ポリゴン描画
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				0,
				g_aMeshCylinder[nCntWall].nNumVtx,								//頂点数
				g_aMeshCylinder[nCntWall].nNumIdx * nCntWall,					//最初のインデックス
				g_aMeshCylinder[nCntWall].nNumIdx - 2							//ポリゴン数
			);
		}
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==================================================================================================
//筒設定処理
//==================================================================================================
void SetMeshCylinder(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntWall = 0; nCntWall < MAX_CYLINDER; nCntWall++)
	{
		if (g_aMeshCylinder[nCntWall].bUse == false)
		{
			g_aMeshCylinder[nCntWall].pos = pos;
			g_aMeshCylinder[nCntWall].rot = rot;

			g_aMeshCylinder[nCntWall].bUse = true;

			//for文抜ける
			break;
		}
	}
}