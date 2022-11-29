//==================================================================================================
//
//Particle.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "particle.h"
#include "effect.h"
#include "player.h"

//マクロ定義
#define MAX_PARTICLE			(128)					//パーティクルの数
#define LIFE_SPEED				(10)					//寿命の減るスピード
#define HIT_RADIUS				(7.0f)					//ヒットエフェクトサイズ
#define HIT_LIFE				(40)					//ヒットエフェクト寿命
#define BOOST_RADIUS			(14.0f)					//ブーストエフェクトサイズ
#define BOOST_LIFE				(40)					//ブーストエフェクト寿命

//グローバル変数宣言
PARTICLE g_aParticle[MAX_PARTICLE];						//エフェクトの情報

//==================================================================================================
//初期化処理
//==================================================================================================
void InitParticle(void)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{//構造体の初期化
		g_aParticle[nCntParticle].pos = { 0.0f,0.0f,0.0f };
		g_aParticle[nCntParticle].posWorld = { 0.0f,0.0f,0.0f };
		g_aParticle[nCntParticle].move = { 0.0f,0.0f,0.0f };
		g_aParticle[nCntParticle].col = { 0.0f,0.0f,0.0f ,0.0f};
		g_aParticle[nCntParticle].fRadius = 0.0f;
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].type = PARTICLE_TYPE_HIT;
		g_aParticle[nCntParticle].bUse = false;
	}
}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitParticle(void)
{
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdateParticle(void)
{
	//変数宣言
	int nCntParticle;
	float fRot,fRot2;
	float fMove;
	
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{//全ての更新

		if (g_aParticle[nCntParticle].bUse == true)
		{//使用されている状態なら

			if (g_aParticle[nCntParticle].pPosOwner != NULL)
			{
				g_aParticle[nCntParticle].pos = *g_aParticle[nCntParticle].pPosOwner;
			}

			for (int nCntApper = 0; nCntApper < 10; nCntApper++)
			{
				switch (g_aParticle[nCntParticle].type)
				{//タイプによる分岐
				case PARTICLE_TYPE_HIT:
					//ヒットパーティクル==============================================
					//移動方向の設定
					fRot = rand() % 629 - 314 / 100.0f;
					fRot2 = rand() % 629 - 314 / 100.0f;

					//移動量の設定
					fMove = (float)(rand() % 10) / 10 + 1;

					g_aParticle[nCntParticle].move.x = sinf(fRot) * sinf(fRot2) * fMove;
					g_aParticle[nCntParticle].move.y = cosf(fRot) * fMove;
					g_aParticle[nCntParticle].move.z = sinf(fRot) * cosf(fRot2) * fMove;

					//色の設定
					g_aParticle[nCntParticle].col = D3DXCOLOR{ 1.0f,0.7f,0.0f,1.0f };

					//半径の設定
					g_aParticle[nCntParticle].fRadius = HIT_RADIUS;

					//エフェクト設定
					SetEffect(g_aParticle[nCntParticle].pos, g_aParticle[nCntParticle].move,
						g_aParticle[nCntParticle].col, g_aParticle[nCntParticle].fRadius, 1000,true,0.2f);
					break;
				case PARTICLE_TYPE_BOOST:
					//ヒットパーティクル==============================================
					//移動方向の設定
					fRot = g_aParticle[nCntParticle].rot.x + (rand() % 25 / 2) / 200.0f;
					fRot2 = g_aParticle[nCntParticle].rot.y + (rand() % 25 / 2) / 200.0f;

					//移動量の設定
					fMove = (float)(rand() % 20) / 10 + 10;

					g_aParticle[nCntParticle].move.x = sinf(fRot) * sinf(fRot2) * fMove;
					g_aParticle[nCntParticle].move.y = cosf(fRot) * fMove;
					g_aParticle[nCntParticle].move.z = sinf(fRot) * cosf(fRot2) * fMove;

					//色の設定
					g_aParticle[nCntParticle].col = D3DXCOLOR{ 0.3f,0.3f,0.5f,1.0f };

					//半径の設定
					g_aParticle[nCntParticle].fRadius = BOOST_RADIUS;

					//エフェクト設定
					SetEffect(g_aParticle[nCntParticle].pos, g_aParticle[nCntParticle].move,
						g_aParticle[nCntParticle].col, g_aParticle[nCntParticle].fRadius, 1000, true, 1.0f);
					break;
				}
			}

			if (g_aParticle[nCntParticle].nLife <= 0)
			{//寿命が尽きたら
			 //使用していない状態にする
				g_aParticle[nCntParticle].bUse = false;

				if (g_aParticle[nCntParticle].pPosOwner != NULL)
				{
					g_aParticle[nCntParticle].pPosOwner = NULL;
				}
			}
			//寿命カウントダウン
			g_aParticle[nCntParticle].nLife -= LIFE_SPEED;
		}
	}
}

//==================================================================================================
//描画処理
//==================================================================================================
void DrawParticle(void)
{
}

//==================================================================================================
//設定処理
//==================================================================================================
void SetParticle(D3DXVECTOR3 pos, PARTICLE_TYPE type, D3DXVECTOR3 rot, D3DXVECTOR3 *pPos)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{//使用していない状態なら
			//位置設定
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].type = type;
			g_aParticle[nCntParticle].bUse = true;

			if (pPos != NULL)
			{
				g_aParticle[nCntParticle].pPosOwner = pPos;
			}

			switch (g_aParticle[nCntParticle].type)
			{//タイプによる分岐
			case PARTICLE_TYPE_HIT:
				g_aParticle[nCntParticle].nLife = 20;
				break;
			case PARTICLE_TYPE_BOOST:
				g_aParticle[nCntParticle].nLife = 20;
				g_aParticle[nCntParticle].rot = rot;
				break;
			}

			break;
		}	
	}
}