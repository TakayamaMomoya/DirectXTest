//==================================================================================================
//
//field.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "field.h"
#include "input.h"

//マクロ定義
#define FIELD_TEX_FILE			"data\\TEXTURE\\sand000.jpg"			//のテクスチャファイル名
#define MOVE_SPEED					(1.0f)									//移動速度

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureField = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;	//頂点バッファへのポインタ
D3DXVECTOR3 g_posField;							//位置
D3DXVECTOR3 g_rotField;							//向き
D3DXMATRIX g_mtxWorldField;						//ワールドマトリックス

//==================================================================================================
//初期化処理
//==================================================================================================
void InitField(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		FIELD_TEX_FILE,
		&g_pTextureField);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(10.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 10.0f);
	pVtx[3].tex = D3DXVECTOR2(10.0f, 10.0f);

	//頂点バッファをアンロック
	g_pVtxBuffField->Unlock();
}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitField(void)
{
	if (g_pTextureField != NULL)
	{
		g_pTextureField->Release();
		g_pTextureField = NULL;
	}

	if (g_pVtxBuffField != NULL)
	{//頂点バッファポインタの破棄
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdateField(void)
{
}

//==================================================================================================
//描画処理
//==================================================================================================
void DrawField(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;

	//デバイスの取得
	pDevice = GetDevice();

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&g_mtxWorldField);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll (&mtxRot,
		g_rotField.y, g_rotField.x, g_rotField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField,&mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		g_posField.x, g_posField.y, g_posField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTrans);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorldField);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureField);

	//描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}