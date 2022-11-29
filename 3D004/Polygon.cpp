//==================================================================================================
//
//polygon.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "polygon.h"
#include "input.h"

//マクロ定義
#define POLYGON_TEX_FILE			"data\\TEXTURE\\BG\\metal001.jpg"			//のテクスチャファイル名
#define MOVE_SPEED					(1.0f)									//移動速度

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//頂点バッファへのポインタ
D3DXVECTOR3 g_posPolygon;							//位置
D3DXVECTOR3 g_rotPolygon;							//向き
D3DXMATRIX g_mtxWorldPolygon;						//ワールドマトリックス

//==================================================================================================
//初期化処理
//==================================================================================================
void InitPolygon(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		POLYGON_TEX_FILE,
		&g_pTexturePolygon);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-1000.0f, 0.0f, 1000.0f);
	pVtx[1].pos = D3DXVECTOR3(1000.0f, 0.0f, 1000.0f);
	pVtx[2].pos = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	pVtx[3].pos = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(200, 200, 200, 255);
	pVtx[1].col = D3DCOLOR_RGBA(200, 200, 200, 255);
	pVtx[2].col = D3DCOLOR_RGBA(200, 200, 200, 255);
	pVtx[3].col = D3DCOLOR_RGBA(200, 200, 200, 255);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(10.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 10.0f);
	pVtx[3].tex = D3DXVECTOR2(10.0f, 10.0f);

	//頂点バッファをアンロック
	g_pVtxBuffPolygon->Unlock();
}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitPolygon(void)
{
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}

	if (g_pVtxBuffPolygon != NULL)
	{//頂点バッファポインタの破棄
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdatePolygon(void)
{
}

//==================================================================================================
//描画処理
//==================================================================================================
void DrawPolygon(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;

	//デバイスの取得
	pDevice = GetDevice();

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll (&mtxRot,
		g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon,&mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorldPolygon);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTexturePolygon);

	//描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}