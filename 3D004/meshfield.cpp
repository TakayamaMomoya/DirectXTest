//==================================================================================================
//
//meshfield.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "meshfield.h"
#include "input.h"

//マクロ定義
#define MESHFIELD_TEX_FILE			"data\\TEXTURE\\BG\\metal001.jpg"			//テクスチャファイル名
#define MOVE_SPEED					(1.0f)										//移動速度
#define MESH_LENGTH					(500.0f)									//メッシュの一辺の長さ
#define MESH_U						(2)											//横のブロック数
#define MESH_V						(2)											//縦のブロック数
#define SPLIT_TEX					(4)											//テクスチャ分割数

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;									//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;								//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;								//インデックスバッファへのポインタ
MeshField g_MeshField;															//構造体の情報

//==================================================================================================
//初期化処理
//==================================================================================================
void InitMeshField(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		MESHFIELD_TEX_FILE,
		&g_pTextureMeshField);

	g_MeshField.nNumVtx = (MESH_U + 1) * (MESH_V + 1);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_MeshField.nNumVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	int nCountV, nCountU;

	for (nCountV = 0;nCountV < MESH_V + 1; nCountV++)
	{//頂点座標の設定
		for (nCountU = 0; nCountU < MESH_U + 1; nCountU++)
		{
			//頂点座標
			pVtx[nCountV * (MESH_U + 1) + nCountU].pos.x = (nCountU - ((MESH_U) * 0.5f)) * MESH_LENGTH; 
			pVtx[nCountV * (MESH_U + 1) + nCountU].pos.z = (((MESH_U) * 0.5f) - nCountV) * MESH_LENGTH;
			pVtx[nCountV * (MESH_U + 1) + nCountU].pos.y = 0.0f;
		
			//テクスチャ座標
			pVtx[nCountV * (MESH_U + 1) + nCountU].tex = D3DXVECTOR2
			(
			    ((float)SPLIT_TEX / MESH_U) * nCountU,
				((float)SPLIT_TEX / MESH_V) * nCountV
			);



			//法線ベクトルの設定
			pVtx[nCountV * (MESH_U + 1) + nCountU].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}
	}

	for (int nCnt = 0;nCnt < g_MeshField.nNumVtx;nCnt++)
	{
		//頂点カラーの設定
		pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//頂点バッファをアンロック
	g_pVtxBuffMeshField->Unlock();

	g_MeshField.nNumIdx = (MESH_U + 1) * (MESH_V + 1) + ((MESH_V + 1) - 2) * (MESH_U + 1) + (((MESH_V + 1) - 2) * 2);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_MeshField.nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	//インデックスバッファへのポインタ
	WORD *pIdx;

	//インデックスバッファをロックし、頂点番号へのポインタを取得
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCount = 0; nCount < g_MeshField.nNumIdx / 2; nCount++)
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

	//インデックスバッファをアンロック
	g_pIdxBuffMeshField->Unlock();
}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitMeshField(void)
{
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	if (g_pVtxBuffMeshField != NULL)
	{//頂点バッファポインタの破棄
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	if (g_pIdxBuffMeshField != NULL)
	{//インデックスバッファポインタの破棄
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdateMeshField(void)
{
}

//==================================================================================================
//描画処理
//==================================================================================================
void DrawMeshField(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&g_MeshField.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll (&mtxRot,
		g_MeshField.rot.y, g_MeshField.rot.x, g_MeshField.rot.z);
	D3DXMatrixMultiply(&g_MeshField.mtxWorld, &g_MeshField.mtxWorld,&mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		g_MeshField.pos.x, g_MeshField.pos.y, g_MeshField.pos.z);
	D3DXMatrixMultiply(&g_MeshField.mtxWorld, &g_MeshField.mtxWorld, &mtxTrans);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD,&g_MeshField.mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureMeshField);

	//ポリゴン描画
	pDevice->DrawIndexedPrimitive (D3DPT_TRIANGLESTRIP, 0, 0, g_MeshField.nNumVtx, 0, g_MeshField.nNumIdx - 2);
}