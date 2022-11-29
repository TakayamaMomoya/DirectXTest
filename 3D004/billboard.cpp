//==================================================================================================
//
//billborad.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "billboard.h"
#include "input.h"
#include "shadow.h"

//マクロ定義
#define BILLBOARD_TEX_FILE			"data\\TEXTURE\\BG\\tree000.png"		//テクスチャファイル名
#define BILLBOARD_WIDTH				(50)									//幅
#define BILLBOARD_HEIGHT			(50)									//高さ
#define MAX_BILLBOARD				(256)									//ビルボードの最大数

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBillBoard = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillBoard = NULL;	//頂点バッファへのポインタ
BillBoard g_aBillBoard[MAX_BILLBOARD];				//構造体の情報

//==================================================================================================
//初期化処理
//==================================================================================================
void InitBillBoard(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		BILLBOARD_TEX_FILE,
		&g_pTextureBillBoard);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillBoard,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBillBoard->Lock(0, 0, (void**)&pVtx, 0);

	//情報取得
	BillBoard *pBillBoard = GetBillBoard();

	for (int nCntBillBoard = 0;nCntBillBoard < MAX_BILLBOARD;nCntBillBoard++, pBillBoard++)
	{
		//変数初期化
		pBillBoard->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBillBoard->bUse = false;
		pBillBoard->nIdxShadow = 0;

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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffBillBoard->Unlock();

	SetBillBoard(D3DXVECTOR3(0.0f, 50.0f, -100.0f));
	SetBillBoard(D3DXVECTOR3(0.0f, 50.0f, -200.0f));
}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitBillBoard(void)
{
	if (g_pTextureBillBoard != NULL)
	{
		g_pTextureBillBoard->Release();
		g_pTextureBillBoard = NULL;
	}

	if (g_pVtxBuffBillBoard != NULL)
	{//頂点バッファポインタの破棄
		g_pVtxBuffBillBoard->Release();
		g_pVtxBuffBillBoard = NULL;
	}
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdateBillBoard(void)
{
}

//==================================================================================================
//描画処理
//==================================================================================================
void DrawBillBoard(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans,mtxView;

	//情報取得
	BillBoard *pBillBoard = GetBillBoard();

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, GetAlphaThreshold());

	for (int nCntBillBoard = 0; nCntBillBoard < MAX_BILLBOARD; nCntBillBoard++, pBillBoard++)
	{
		if (pBillBoard->bUse)
		{
			//ワールドマトリックス初期化
			D3DXMatrixIdentity(&pBillBoard->mtxWorld);

			//ビューマトリックス取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに向ける
			D3DXMatrixInverse(&pBillBoard->mtxWorld, NULL, &mtxView);
			pBillBoard->mtxWorld._41 = 0.0f;
			pBillBoard->mtxWorld._42 = 0.0f;
			pBillBoard->mtxWorld._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				pBillBoard->pos.x, pBillBoard->pos.y, pBillBoard->pos.z);
			D3DXMatrixMultiply(&pBillBoard->mtxWorld, &pBillBoard->mtxWorld, &mtxTrans);

			//ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &pBillBoard->mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBillBoard, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャ設定
			pDevice->SetTexture(0, g_pTextureBillBoard);

			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBillBoard, 2);
		}	
	}

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==================================================================================================
//設定処理
//==================================================================================================
void SetBillBoard(D3DXVECTOR3 pos)
{
	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBillBoard->Lock(0, 0, (void**)&pVtx, 0);

	//情報取得
	BillBoard *pBillBoard = GetBillBoard();

	for (int nCntBillBoard = 0; nCntBillBoard < MAX_BILLBOARD; nCntBillBoard++, pBillBoard++)
	{
		if (pBillBoard->bUse == false)
		{
			//変数設定
			pBillBoard->pos = pos;
			pBillBoard->bUse = true;
			pBillBoard->nIdxShadow = SetShadow(BILLBOARD_WIDTH);
			SetPositionShadow(pBillBoard->nIdxShadow,pos);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_WIDTH, BILLBOARD_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(BILLBOARD_WIDTH, BILLBOARD_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_WIDTH, -BILLBOARD_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(BILLBOARD_WIDTH, -BILLBOARD_HEIGHT, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffBillBoard->Unlock();
}

//==================================================================================================
//情報取得処理
//==================================================================================================
BillBoard *GetBillBoard(void)
{
	return &g_aBillBoard[0];
}