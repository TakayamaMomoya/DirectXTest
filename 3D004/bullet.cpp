//==================================================================================================
//
//bullet.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "bullet.h"
#include "meshWall.h"
#include "input.h"
#include "shadow.h"
#include "explosion.h"
#include "input.h"
#include "effect.h"
#include <stdio.h>
#include "particle.h"
#include "enemy.h"

//マクロ定義
#define BULLET_TEX_FILE			"data\\TEXTURE\\EFFECT\\effect000.png"		//テクスチャファイル名
#define BULLET_WIDTH			(5)											//幅
#define BULLET_HEIGHT			(5)											//高さ
#define MAX_BULLET				(256)										//ビルボードの最大数
#define NORMAL_LIFE				(60)										//通常寿命

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;									//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;							//頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];												//構造体の情報
int g_nNumBullet;															//弾の総数

//プロトタイプ宣言
void CollisionWallBullet(Bullet *pBullet);
void CollisionEnemyBullet(Bullet *pBullet);

//==================================================================================================
//初期化処理
//==================================================================================================
void InitBullet(void)
{
	//変数初期化
	g_nNumBullet = 0;

	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		BULLET_TEX_FILE,
		&g_pTextureBullet);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//情報取得
	Bullet *pBullet = GetBullet();

	for (int nCntBullet = 0;nCntBullet < MAX_BULLET;nCntBullet++, pBullet++)
	{
		//変数初期化
		pBullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->bUse = false;
		pBullet->nIdxShadow = 0;
		pBullet->nLife = 0;

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
	g_pVtxBuffBullet->Unlock();

}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitBullet(void)
{
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	if (g_pVtxBuffBullet != NULL)
	{//頂点バッファポインタの破棄
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdateBullet(void)
{
	//情報取得
	Bullet *pBullet = GetBullet();

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse)
		{
			pBullet->posOld = pBullet->pos;

			//エフェクト設定
			SetEffect
			(
				pBullet->pos,
				D3DXVECTOR3(0.0f,0.0f,0.0f),
				D3DXCOLOR(0.5f,0.5f,1.0f,1.0f),
				10.0f,
				50,
				false,
				2.0f
			);

			//弾位置更新処理
			pBullet->pos += pBullet->move;

			//壁との当たり判定
			CollisionWallBullet(pBullet);

			//敵との当たり判定
			CollisionEnemyBullet(pBullet);

			//影位置設定
			SetPositionShadow(pBullet->nIdxShadow, pBullet->pos);

			//寿命減少
			pBullet->nLife--;

			if (pBullet->nLife <= 0)
			{//使用していない状態にする
				DisableBullet(pBullet);

				
			}
		}
	}
}

//==================================================================================================
//壁との当たり判定
//==================================================================================================
void CollisionWallBullet(Bullet *pBullet)
{
	//情報取得
	MeshWall *pMeshWall = GetMeshWall();

	//計算用変数
	D3DXVECTOR3 vecLine, vecToPos;

	for (int nCntWall = 0; nCntWall < MAX_MESHWALL;nCntWall++,pMeshWall++)
	{
		if (pMeshWall->bUse)
		{
			if (CrossProduct(pBullet->posOld, pBullet->pos, pBullet->move,
				D3DXVECTOR3
				(
					pMeshWall->pos.x + sinf(pMeshWall->rot.y + D3DX_PI * 0.5f) * pMeshWall->width * 0.5f,
					0.0f,
					pMeshWall->pos.z + cosf(pMeshWall->rot.y + D3DX_PI * 0.5f) * pMeshWall->width * 0.5f
				),
				D3DXVECTOR3
				(
					pMeshWall->pos.x + sinf(pMeshWall->rot.y - D3DX_PI * 0.5f) * pMeshWall->width * 0.5f,
					0.0f,
					pMeshWall->pos.z + cosf(pMeshWall->rot.y - D3DX_PI * 0.5f) * pMeshWall->width * 0.5f
				)) == true)
			{//当たった場合
				SetParticle(pBullet->pos,PARTICLE_TYPE_HIT,D3DXVECTOR3(0.0f,0.0f,0.0f),NULL);

				DisableBullet(pBullet);
			}
		}
	}
}

//==================================================================================================
//敵との当たり判定
//==================================================================================================
void CollisionEnemyBullet(Bullet *pBullet)
{
	//情報取得
	Enemy *pEnemy = GetEnemy();

	for (int nCntEnemy = 0;nCntEnemy < MAX_ENEMY;nCntEnemy++,pEnemy++)
	{
		if (pEnemy->bUse)
		{
			if (SqrCrossProduct(pBullet->posOld, pBullet->pos, pBullet->move, pEnemy->vtxMin, pEnemy->vtxMax) == true)
			{//敵に当たったら

				SetParticle(pBullet->pos, PARTICLE_TYPE_HIT, D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL);

				DisableBullet(pBullet);
			}
		}
	}
}

//==================================================================================================
//描画処理
//==================================================================================================
void DrawBullet(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans,mtxView;

	//情報取得
	Bullet *pBullet = GetBullet();

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, GetAlphaThreshold());

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse)
		{
			//ワールドマトリックス初期化
			D3DXMatrixIdentity(&pBullet->mtxWorld);

			//ビューマトリックス取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに向ける
			D3DXMatrixInverse(&pBullet->mtxWorld, NULL, &mtxView);
			pBullet->mtxWorld._41 = 0.0f;
			pBullet->mtxWorld._42 = 0.0f;
			pBullet->mtxWorld._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				pBullet->pos.x, pBullet->pos.y, pBullet->pos.z);
			D3DXMatrixMultiply(&pBullet->mtxWorld, &pBullet->mtxWorld, &mtxTrans);

			//ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &pBullet->mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャ設定
			pDevice->SetTexture(0, g_pTextureBullet);

			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBullet, 2);
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
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	//頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//情報取得
	Bullet *pBullet = GetBullet();

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{
			//変数設定
			pBullet->pos = pos;
			pBullet->move = move;
			pBullet->bUse = true;
			pBullet->nIdxShadow = SetShadow(BULLET_WIDTH);
			SetPositionShadow(pBullet->nIdxShadow,pos);
			pBullet->nLife = NORMAL_LIFE;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-BULLET_WIDTH, BULLET_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(BULLET_WIDTH, BULLET_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-BULLET_WIDTH, -BULLET_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(BULLET_WIDTH, -BULLET_HEIGHT, 0.0f);

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

			//弾総数上昇
			g_nNumBullet++;

			break;
		}

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}

//==================================================================================================
//情報取得処理
//==================================================================================================
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}

//==================================================================================================
//弾無効化処理
//==================================================================================================
void DisableBullet(Bullet *pBullet)
{
	SetExplosion(pBullet->pos);

	pBullet->bUse = false;
	g_nNumBullet--;

	//影無効化
	EnableShadow(pBullet->nIdxShadow, false);
}

//==================================================================================================
//弾デバッグ表示
//==================================================================================================
void DrawBulletState(LPD3DXFONT pFont)
{
	//変数宣言
	RECT rect = { 250,20,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	sprintf(&aStr[0], "弾の総数[%d]",g_nNumBullet);

	//テキスト描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}