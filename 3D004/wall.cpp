//==================================================================================================
//
//wall.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "wall.h"
#include "input.h"

//マクロ定義
#define WALL_TEX_FILE			"data\\TEXTURE\\BG\\metal000.jpg"		//テクスチャファイル名
#define MOVE_SPEED				(1.0f)									//移動速度

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//頂点バッファへのポインタ
Wall g_aWall[MAX_WALL];							//構造体の情報

//==================================================================================================
//初期化処理
//==================================================================================================
void InitWall(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		WALL_TEX_FILE,
		&g_pTextureWall);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	//情報取得
	Wall *pWall = GetWall();

	for (int nCntWall = 0; nCntWall < MAX_WALL;nCntWall++, pWall++)
	{
		//変数初期化
		pWall->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pWall->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pWall->height = 0.0f;
		pWall->width = 0.0f;
		pWall->bUse = false;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(10.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 10.0f);
		pVtx[3].tex = D3DXVECTOR2(10.0f, 10.0f);

		//ポインタを進める
		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffWall->Unlock();

	SetWall
	(
		D3DXVECTOR3(0.0f,0.0f,0.0f + WALL_WIDTH * 0.5f),
		D3DXVECTOR3(0.0f,0.0f,0.0f),
		D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)
	);
	SetWall
	(
		D3DXVECTOR3(WALL_WIDTH * 0.5f, 0.0f, -WALL_WIDTH * 0.5f + WALL_WIDTH * 0.5f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	);
	SetWall
	(
		D3DXVECTOR3(-WALL_WIDTH * 0.5f, 0.0f, -WALL_WIDTH * 0.5f + WALL_WIDTH * 0.5f),
		D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	);
	SetWall
	(
		D3DXVECTOR3(0.0f, 0.0f, -WALL_WIDTH + WALL_WIDTH * 0.5f),
		D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	);

	//透明壁========================================================================
	SetWall
	(
		D3DXVECTOR3(0.0f, 0.0f, -WALL_WIDTH + 0.1f + WALL_WIDTH * 0.5f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f)
	);
	SetWall
	(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f + WALL_WIDTH * 0.5f - 0.1f),
		D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f)
	);
	SetWall
	(
		D3DXVECTOR3(WALL_WIDTH * 0.5f + 0.1f , 0.0f, -WALL_WIDTH * 0.5f + WALL_WIDTH * 0.5f),
		D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f)
	);
	SetWall
	(
		D3DXVECTOR3(-WALL_WIDTH * 0.5f - 0.1f , 0.0f, -WALL_WIDTH * 0.5f + WALL_WIDTH * 0.5f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f)
	);
}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitWall(void)
{
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	if (g_pVtxBuffWall != NULL)
	{//頂点バッファポインタの破棄
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdateWall(void)
{
}

//==================================================================================================
//描画処理
//==================================================================================================
void DrawWall(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;

	//デバイスの取得
	pDevice = GetDevice();

	//情報取得処理
	Wall *pWall = GetWall();

	for (int nCntWall = 0;nCntWall < MAX_WALL;nCntWall++,pWall++)
	{
		if (pWall->bUse == true)
		{//使用している場合
		 //ワールドマトリックス初期化
			D3DXMatrixIdentity(&pWall->mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				pWall->rot.y, pWall->rot.x, pWall->rot.z);
			D3DXMatrixMultiply(&pWall->mtxWorld, &pWall->mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				pWall->pos.x, pWall->pos.y, pWall->pos.z);
			D3DXMatrixMultiply(&pWall->mtxWorld, &pWall->mtxWorld, &mtxTrans);

			//ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &pWall->mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャ設定
			pDevice->SetTexture(0, g_pTextureWall);

			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntWall, 2);
		}
	}
}

//==================================================================================================
//情報取得処理
//==================================================================================================
Wall *GetWall(void)
{
	return &g_aWall[0];
}

//==================================================================================================
//設定処理
//==================================================================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXCOLOR col)
{
	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	//情報取得処理
	Wall *pWall = GetWall();

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pWall++)
	{
		if (pWall->bUse == false)
		{//使用していない状態
			//変数初期化
			pWall->pos = pos;
			pWall->rot = rot;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-WALL_WIDTH * 0.5f, WALL_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(WALL_WIDTH * 0.5f, WALL_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-WALL_WIDTH * 0.5f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(WALL_WIDTH * 0.5f, 0.0f, 0.0f);

			//法線ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			//頂点カラーの設定
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(10.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 10.0f);
			pVtx[3].tex = D3DXVECTOR2(10.0f, 10.0f);

			//使用状態にする
			pWall->bUse = true;

			//for文を抜ける
			break;
		}

		//ポインタを進める
		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffWall->Unlock();
}