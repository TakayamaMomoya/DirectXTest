//==================================================================================================
//
//meshwall.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "meshwall.h"
#include "input.h"

//マクロ定義
#define MESHWALL_TEX_FILE			"data\\TEXTURE\\BG\\metal000.jpg"			//テクスチャファイル名
#define MOVE_SPEED					(1.0f)										//移動速度
#define MESH_LENGTH					(500.0f)									//メッシュの一辺の長さ
#define MESH_U						(2)											//横のブロック数
#define MESH_V						(1)											//縦のブロック数
#define MAX_SPLIT					(10)										//最大分割数
#define SPLIT_TEX_U					(4)											//横のテクスチャ分割数
#define SPLIT_TEX_V					(1)											//縦のテクスチャ分割数

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;									//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;								//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;								//インデックスバッファへのポインタ
MeshWall g_aMeshWall[MAX_MESHWALL];												//構造体の情報
int g_nMaxIdxMeshWall;															//最大インデックス数
int g_nMaxVtxMeshWall;															//最大頂点数

//==================================================================================================
//初期化処理
//==================================================================================================
void InitMeshWall(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		MESHWALL_TEX_FILE,
		&g_pTextureMeshWall);

	//一つあたりの最大頂点数
	g_nMaxVtxMeshWall = (MAX_SPLIT + 1) * (MAX_SPLIT + 1);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nMaxVtxMeshWall * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	//一つあたりの最大インデックス数
	g_nMaxIdxMeshWall = (MAX_SPLIT + 1) * (MAX_SPLIT + 1) + ((MAX_SPLIT + 1) - 2) * (MAX_SPLIT + 1) + (((MAX_SPLIT + 1) - 2) * 2);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nMaxIdxMeshWall * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	//インデックスバッファへのポインタ
	WORD *pIdx;

	//インデックスバッファをロックし、頂点番号へのポインタを取得
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntWall = 0;nCntWall < MAX_MESHWALL;nCntWall++)
	{
		//変数初期化
		g_aMeshWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntWall].bUse = false;
		g_aMeshWall[nCntWall].nNumIdx = 0;
		g_aMeshWall[nCntWall].nNumVtx = 0;
		g_aMeshWall[nCntWall].width = 0;
		g_aMeshWall[nCntWall].height = 0;

		for (int nCntVtx = 0; nCntVtx < g_nMaxVtxMeshWall; nCntVtx++)
		{//頂点情報の設定
			pVtx[nCntVtx].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			pVtx[nCntVtx].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[nCntVtx].tex = D3DXVECTOR2(0.0f, 0.0f);
		}

		for (int nCount = 0; nCount < g_nMaxIdxMeshWall; nCount++)
		{//インデックス決定
			pIdx[nCount] = 0;
		}

		//ポインタを進める
		pIdx += g_nMaxIdxMeshWall;
		pVtx += g_nMaxVtxMeshWall;
	}

	//頂点バッファをアンロック
	g_pVtxBuffMeshWall->Unlock();

	//インデックスバッファをアンロック
	g_pIdxBuffMeshWall->Unlock();

	SetMeshWall
	(
		D3DXVECTOR3(0.0f,0.0f,-500.0f),
		D3DXVECTOR3(0.0f,D3DX_PI,0.0f),
		1000.0f,
		150.0f
	);

	SetMeshWall
	(
		D3DXVECTOR3(-500.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),
		1000.0f,
		150.0f
	);

	SetMeshWall
	(
		D3DXVECTOR3(0.0f, 0.0f, 500.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		1000.0f,
		150.0f
	);

	SetMeshWall
	(
		D3DXVECTOR3(500.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		1000.0f,
		150.0f
	);

	SetMeshWall
	(
		D3DXVECTOR3(50.0f, 0.0f, -500.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.8f, 0.0f),
		1000.0f,
		150.0f
	);
}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitMeshWall(void)
{
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}

	if (g_pVtxBuffMeshWall != NULL)
	{//頂点バッファポインタの破棄
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	if (g_pIdxBuffMeshWall != NULL)
	{//インデックスバッファポインタの破棄
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdateMeshWall(void)
{
}

//==================================================================================================
//描画処理
//==================================================================================================
void DrawMeshWall(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		if (g_aMeshWall[nCntWall].bUse)
		{
			//ワールドマトリックス初期化
			D3DXMatrixIdentity(&g_aMeshWall[nCntWall].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aMeshWall[nCntWall].rot.y, g_aMeshWall[nCntWall].rot.x, g_aMeshWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntWall].mtxWorld, &g_aMeshWall[nCntWall].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_aMeshWall[nCntWall].pos.x, g_aMeshWall[nCntWall].pos.y, g_aMeshWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntWall].mtxWorld, &g_aMeshWall[nCntWall].mtxWorld, &mtxTrans);

			//ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshWall[nCntWall].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffMeshWall);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャ設定
			pDevice->SetTexture(0, g_pTextureMeshWall);

			//ポリゴン描画
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				0,
				g_aMeshWall[nCntWall].nNumVtx,								//頂点数
				g_nMaxIdxMeshWall * nCntWall,								//最初のインデックス
				g_aMeshWall[nCntWall].nNumIdx - 2							//ポリゴン数
			);
		}
	}
}

//==================================================================================================
//壁設定処理
//==================================================================================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float width,float height)
{
	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	//インデックスバッファへのポインタ
	WORD *pIdx;

	//インデックスバッファをロックし、頂点番号へのポインタを取得
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		if (g_aMeshWall[nCntWall].bUse == false)
		{
			//引数受け取り
			g_aMeshWall[nCntWall].pos = pos;
			g_aMeshWall[nCntWall].rot = rot;
			g_aMeshWall[nCntWall].bUse = true;
			g_aMeshWall[nCntWall].width = width;
			g_aMeshWall[nCntWall].height = height;

			//頂点数計算
			g_aMeshWall[nCntWall].nNumVtx = (MESH_U + 1) * (MESH_V + 1);

			for (int nCountV = 0; nCountV < MESH_V + 1; nCountV++)
			{//頂点座標の設定
				for (int nCountU = 0; nCountU < MESH_U + 1; nCountU++)
				{
					pVtx[nCountV * (MESH_U + 1) + nCountU].pos.x = (nCountU - ((MESH_U) * 0.5f)) * (width / MESH_U);
					pVtx[nCountV * (MESH_U + 1) + nCountU].pos.z = 0.0f;
					pVtx[nCountV * (MESH_U + 1) + nCountU].pos.y = (MESH_V - nCountV) * (height / MESH_V);

					//テクスチャ座標
					pVtx[nCountV * (MESH_U + 1) + nCountU].tex = D3DXVECTOR2
					(
						((float)SPLIT_TEX_U / MESH_U) * nCountU,
						((float)SPLIT_TEX_V / MESH_V) * nCountV
					);
				}
			}

			for (int nCnt = 0; nCnt < g_aMeshWall[nCntWall].nNumVtx; nCnt++)
			{
				//法線ベクトルの設定
				pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

				//頂点カラーの設定
				pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}

			g_aMeshWall[nCntWall].nNumIdx = (MESH_U + 1) * (MESH_V + 1) + ((MESH_V + 1) - 2) * (MESH_U + 1) + (((MESH_V + 1) - 2) * 2);

			for (int nCount = 0; nCount < g_aMeshWall[nCntWall].nNumIdx / 2; nCount++)
			{//インデックス決定
				if (
					nCount % ((MESH_U + 1) + (MESH_U + 2) * (nCount / (MESH_U + 2))) == 0
					&& nCount != 0
					)
				{//折り返し
					pIdx[nCount * 2 + 1] = ((MESH_U + 1) * 2) + (MESH_U + 1) * (nCount / (MESH_U + 2));

					pIdx[nCount * 2] = MESH_U + (MESH_U + 1) * (nCount / (MESH_U + 2));
				}
				else
				{//通常
					pIdx[nCount * 2 + 1] = nCount - (nCount / (MESH_U + 2));

					pIdx[nCount * 2] = (nCount - (nCount / (MESH_U + 2))) + (MESH_U + 1);
				}
			}

			//for文抜ける
			break;
		}

		//ポインタを進める
		pIdx += g_nMaxIdxMeshWall;
		pVtx += g_nMaxVtxMeshWall;
	}

	//頂点バッファをアンロック
	g_pVtxBuffMeshWall->Unlock();

	//インデックスバッファをアンロック
	g_pIdxBuffMeshWall->Unlock();
}

//==================================================================================================
//ポインタ取得処理
//==================================================================================================
MeshWall *GetMeshWall(void)
{
	return &g_aMeshWall[0];
}