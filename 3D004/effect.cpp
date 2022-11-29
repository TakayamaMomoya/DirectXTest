//==================================================================================================
//
//Effect.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "effect.h"
#include "player.h"

//マクロ定義
#define MAX_EFFECT				(4096)										//最大数
#define LIFE_SPEED				(10)										//寿命の減る速度
#define EFFECT_TEX_FILE			"data\\TEXTURE\\effect\\effect000.png"		//テクスチャファイル名
#define ANIM_TIME				(1)											//アニメーションを行う頻度
#define EFFECT_WIDTH			(10)										//横幅
#define EFFECT_HEIGHT			(40)										//高さ
#define MOVE_FACT				(0.96f)										//移動減衰係数

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//頂点バッファへのポインタ
Effect g_aEffect[MAX_EFFECT];						//エフェクトの情報

//プロトタイプ宣言
void UpdateEffectPos(Effect *pEffect);
void UpdateEffectPolygon(Effect *pEffect,int nCntEffect);

//==================================================================================================
//初期化処理
//==================================================================================================
void InitEffect(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice;

	//ポインタ宣言
	Effect *pEffect = GetEffect();

	//変数宣言
	int nCntEffect;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		EFFECT_TEX_FILE,
		&g_pTextureEffect);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++,pEffect++)
	{//全ての弾の初期化
	    //頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);

		//norの設定
		pVtx[0].nor = { 0.0f,0.0f,-1.0f };
		pVtx[1].nor = { 0.0f,0.0f,-1.0f };
		pVtx[2].nor = { 0.0f,0.0f,-1.0f };
		pVtx[3].nor = { 0.0f,0.0f,-1.0f };

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pEffect->fRadius = 0.0f;
		pEffect->fDecrease = 0.0f;
		pEffect->col = D3DXCOLOR{ 1.0f,1.0f,1.0f,1.0f };
		pEffect->pos = D3DXVECTOR3{ 0.0f,0.0f,0.0f };
		pEffect->move = D3DXVECTOR3{ 0.0f,0.0f,0.0f };
		pEffect->nLife = 0;
		pEffect->bUse = false;					//弾を使用していない状態にする

		//頂点データのポインタを4つ分進める
		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitEffect(void)
{
	if (g_pTextureEffect != NULL)
	{//テクスチャへのポインタ破棄
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	if (g_pVtxBuffEffect != NULL)
	{//頂点バッファへのポインタ破棄
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdateEffect(void)
{
	//変数宣言
	int nCntEffect;
	
	//ポインタ宣言
	Effect *pEffect = GetEffect();

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{//全ての弾の更新

		if (pEffect->bUse)
		{//使用されている状態なら

			//位置更新処理
			UpdateEffectPos(pEffect);

			//半径の更新
			pEffect->fRadius -= pEffect->fDecrease;

			//寿命カウントダウン
			pEffect->nLife -= LIFE_SPEED / 2;

			if (pEffect->nLife <= 0 || pEffect->fRadius <= 0)
			{//寿命が尽きたら
			 //使用していない状態にする
				pEffect->bUse = false;
			}

			//ポリゴン更新処理
			UpdateEffectPolygon(pEffect, nCntEffect);
		}
	}
}

//==================================================================================================
//位置更新処理
//==================================================================================================
void UpdateEffectPos(Effect *pEffect)
{
	//移動量減衰
	pEffect->move.x = pEffect->move.x * MOVE_FACT;
	pEffect->move.y = pEffect->move.y * MOVE_FACT;
	pEffect->move.z = pEffect->move.z * MOVE_FACT;

	//位置の更新
	pEffect->pos.x += pEffect->move.x;
	pEffect->pos.y += pEffect->move.y;
	pEffect->pos.z += pEffect->move.z;
}

//==================================================================================================
//ポリゴン更新処理
//==================================================================================================
void UpdateEffectPolygon(Effect *pEffect,int nCntEffect)
{
	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	//頂点データのポインタを4つ分進める
	pVtx += 4 * nCntEffect;

	//頂点座標の設定
	pVtx[0].pos = { -pEffect->fRadius,pEffect->fRadius, 0.0f };
	pVtx[1].pos = { pEffect->fRadius,pEffect->fRadius, 0.0f };
	pVtx[2].pos = { -pEffect->fRadius,-pEffect->fRadius, 0.0f };
	pVtx[3].pos = { pEffect->fRadius,-pEffect->fRadius, 0.0f };

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
	pVtx[1].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
	pVtx[2].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
	pVtx[3].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };

	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}

//==================================================================================================
//描画処理
//==================================================================================================
void DrawEffect(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans, mtxView;

	//ポインタ宣言
	Effect *pEffect = GetEffect();

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, GetAlphaThreshold());

	//Zテストの無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if (pEffect->bUse)
		{
			//ワールドマトリックス初期化
			D3DXMatrixIdentity(&pEffect->mtxWorld);

			//ビューマトリックス取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに向ける
			D3DXMatrixInverse(&pEffect->mtxWorld, NULL, &mtxView);
			pEffect->mtxWorld._41 = 0.0f;
			pEffect->mtxWorld._42 = 0.0f;
			pEffect->mtxWorld._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				pEffect->pos.x, pEffect->pos.y, pEffect->pos.z);
			D3DXMatrixMultiply(&pEffect->mtxWorld, &pEffect->mtxWorld, &mtxTrans);

			//ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &pEffect->mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャ設定
			pDevice->SetTexture(0, g_pTextureEffect);

			if (pEffect->bAdd == true)
			{
				//αブレンディングを加算合成に設定
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}

			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEffect, 2);

			if (pEffect->bAdd == true)
			{
				//αブレンディングを元に戻す
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			}
		}
	}

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
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col,float fRadius, int nLife,bool bAdd,float fDecrease)
{
	//変数宣言
	int nCntEffect;

	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//弾へのポインタ
	Effect *pEffect = GetEffect();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++,pEffect++)
	{//全ての弾をチェックする
		if (pEffect->bUse == false)
		{//使っていない状態なら

			//位置の設定
			pEffect->pos = pos;

			//位置の設定
			pEffect->move = move;

			//色の設定
			pEffect->col = col;

			//半径の設定
			pEffect->fRadius = fRadius;

			//減少量設定
			pEffect->fDecrease = fDecrease;

			//寿命の設定
			pEffect->nLife = nLife;

			//頂点座標の設定
			pVtx[0].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
			pVtx[1].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
			pVtx[2].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
			pVtx[3].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };

			//寿命の設定
			pEffect->nLife = nLife;

			//使用している設定
			pEffect->bUse = true;

			//使用している設定
			pEffect->bAdd = bAdd;

			//for文を抜ける
			break;
		}

		//頂点データのポインタを4つ分進める
		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}

//==================================================================================================
//ポインタ取得
//==================================================================================================
Effect *GetEffect(void)
{
	return &g_aEffect[0];
}