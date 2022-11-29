//==================================================================================================
//
//explosion.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "explosion.h"
#include "input.h"
#include "shadow.h"
#include <stdio.h>

//マクロ定義
#define EXPLOSION_TEX_FILE		"data\\TEXTURE\\EFFECT\\explosion000.png"			//テクスチャファイル名
#define EXPLOSION_WIDTH			(10)											//幅
#define EXPLOSION_HEIGHT		(10)											//高さ
#define MAX_EXPLOSION			(256)											//ビルボードの最大数
#define NORMAL_LIFE				(60)											//通常寿命
#define ANIM_TIME				(10)												//アニメーションの速度

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;									//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;								//頂点バッファへのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];											//構造体の情報
int g_nNumExplosion;															//弾の総数

//プロトタイプ宣言
void UpdateExplosionPolygon(int nCntExplosion, Explosion *pExplosion);

//==================================================================================================
//初期化処理
//==================================================================================================
void InitExplosion(void)
{
	//変数宣言
	g_nNumExplosion = 0;

	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		EXPLOSION_TEX_FILE,
		&g_pTextureExplosion);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	//情報取得
	Explosion *pExplosion = GetExplosion();

	for (int nCntExplosion = 0;nCntExplosion < MAX_EXPLOSION;nCntExplosion++, pExplosion++)
	{
		//変数初期化
		pExplosion->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pExplosion->bUse = false;
		pExplosion->nCounterAnim = 0;
		pExplosion->nTexU = 0;

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
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffExplosion->Unlock();

}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitExplosion(void)
{
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	if (g_pVtxBuffExplosion != NULL)
	{//頂点バッファポインタの破棄
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdateExplosion(void)
{
	//情報取得
	Explosion *pExplosion = GetExplosion();

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse)
		{
			UpdateExplosionPolygon(nCntExplosion, pExplosion);
		}
	}
}

//==================================================================================================
//ポリゴン更新処理
//==================================================================================================
void UpdateExplosionPolygon(int nCntExplosion, Explosion *pExplosion)
{
	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	//ポインタを進める
	pVtx += 4 * nCntExplosion;

	if (pExplosion->nTexU >= 8)
	{
		DisableExplosion(pExplosion);
	}

	pExplosion->nCounterAnim++;

	if (pExplosion->nCounterAnim % ANIM_TIME == 0)
	{//アニメーションカウンタが一定の値に達したら
	 //パターンNO．の更新
		pExplosion->nTexU++;

		//テクスチャ座標の更新
		pVtx[0].tex = { 0.125f * pExplosion->nTexU,0.0f };
		pVtx[1].tex = { 0.125f + 0.125f * pExplosion->nTexU,0.0f };
		pVtx[2].tex = { 0.125f * pExplosion->nTexU,1.0f };
		pVtx[3].tex = { 0.125f + 0.125f * pExplosion->nTexU,1.0f };
	}

	//頂点バッファをアンロック
	g_pVtxBuffExplosion->Unlock();
}

//==================================================================================================
//描画処理
//==================================================================================================
void DrawExplosion(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans,mtxView;

	//情報取得
	Explosion *pExplosion = GetExplosion();

	//ライティングの無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, GetAlphaThreshold());

	//Zテストの無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse)
		{
			//ワールドマトリックス初期化
			D3DXMatrixIdentity(&pExplosion->mtxWorld);

			//ビューマトリックス取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに向ける
			D3DXMatrixInverse(&pExplosion->mtxWorld, NULL, &mtxView);
			pExplosion->mtxWorld._41 = 0.0f;
			pExplosion->mtxWorld._42 = 0.0f;
			pExplosion->mtxWorld._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				pExplosion->pos.x, pExplosion->pos.y, pExplosion->pos.z);
			D3DXMatrixMultiply(&pExplosion->mtxWorld, &pExplosion->mtxWorld, &mtxTrans);

			//ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &pExplosion->mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャ設定
			pDevice->SetTexture(0, g_pTextureExplosion);

			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntExplosion, 2);
		}
	}

	//ライティングの有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==================================================================================================
//設定処理
//==================================================================================================
void SetExplosion(D3DXVECTOR3 pos)
{
	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	//情報取得
	Explosion *pExplosion = GetExplosion();

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse == false)
		{
			//変数設定
			pExplosion->pos = pos;
			pExplosion->bUse = true;
			pExplosion->nCounterAnim = 0;
			pExplosion->nTexU = 0;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-EXPLOSION_WIDTH, -EXPLOSION_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(EXPLOSION_WIDTH, -EXPLOSION_HEIGHT, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

			//弾総数上昇
			g_nNumExplosion++;

			break;
		}

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffExplosion->Unlock();
}

//==================================================================================================
//情報取得処理
//==================================================================================================
Explosion *GetExplosion(void)
{
	return &g_aExplosion[0];
}

//==================================================================================================
//弾無効化処理
//==================================================================================================
void DisableExplosion(Explosion *pExplosion)
{
	pExplosion->bUse = false;
	g_nNumExplosion--;
}

//==================================================================================================
//デバッグ表示
//==================================================================================================
void DrawExplosionState(LPD3DXFONT pFont)
{
	//変数宣言
	RECT rect = { 250,40,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	sprintf(&aStr[0], "爆発の総数[%d]",g_nNumExplosion);

	//テキスト描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}