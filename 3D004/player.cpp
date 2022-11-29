//==================================================================================================
//
//player.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "player.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "wall.h"
#include "particle.h"
#include <stdio.h>
#include <string.h>
#include "meshWall.h"

//マクロ定義
#define MOVE_SPEED					(0.7f)									//移動速度
#define NUM_TEX						(8)										//テクスチャ数
#define ROLL_FACT					(0.06f)									//回転減衰係数
#define ROLL_SPEED					(0.04f)									//回転速度
#define BULLET_SPEED				(10.0f)									//弾のスピード
#define MOVE_FACT					(0.9f)									//移動量減衰係数
#define MAX_PART					(24)									//パーツの最大数
#define MAX_STRING					(256)									//最大の文字数
#define MOTION_FILE					"data\\motion_AC.txt"					//モーションファイル名
#define BOOST_SPEED					(20)									//ブーストの速度
#define DODGE_COST					(80.0f)									//回避のブースターコスト

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTexturePlayer[MAX_PART][NUM_TEX] = {};			//テクスチャへのポインタ
int g_nIdxShadowPlayer;										//影のインデックス
Player g_player;											//構造体の情報
PlayerPart g_aPlayerPart[MAX_PART];							//構造体の情報
int g_nNumPlayerParts;										//パーツ数
char g_acFilenamePlayer[MAX_PART][MAX_STRING];				//パーツのファイル名

//プロトタイプ宣言
void ControlPlayer(void);
void UpdatePosPlayer(void);
void LimitMovePlayer(void);
void LoadMotion(FILE *pFile);

//==================================================================================================
//初期化処理
//==================================================================================================
void InitPlayer(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	//変数初期化
	g_player.pos = { 0.0f,0.0f,0.0f };
	g_player.move = { 0.0f,0.0f,0.0f };
	g_player.rot = { 0.0f,0.0f,0.0f };
	g_player.fBoost = INITIAL_MAX_BOOST;
	g_player.fBoostMax = INITIAL_MAX_BOOST;
	g_player.nLife = PLAYER_LIFE;
	g_nIdxShadowPlayer = 0;
	g_nNumPlayerParts = 0;

	//情報取得
	PlayerPart *pPlayerPart = GetPlayerPart();

	//ファイルから問題と選択肢を読み込む
	FILE *pFile = fopen(MOTION_FILE, "r");

	if (pFile != NULL)
	{//ファイルが開けた場合
	    //ファイル読み込み処理
		LoadMotion(pFile);
	}
	else
	{
	}

	for (int nCntPart = 0;nCntPart < g_nNumPlayerParts;nCntPart++)
	{//パーツ読み込み
		//変数初期化
		pPlayerPart[nCntPart].dwNumMat = 0;

		//Xファイル読み込み
		D3DXLoadMeshFromX(&g_acFilenamePlayer[nCntPart][0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&pPlayerPart[nCntPart].pBuffMat,
			NULL,
			&pPlayerPart[nCntPart].dwNumMat,
			&pPlayerPart[nCntPart].pMesh);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)pPlayerPart[nCntPart].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)pPlayerPart[nCntPart].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャが存在する
			    //テクスチャ読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_apTexturePlayer[nCntPart][nCntMat]);
			}
		}

		if (pPlayerPart[nCntPart].nIdxParent != -1)
		{
			pPlayerPart[nCntPart].pos = pPlayerPart[pPlayerPart[nCntPart].nIdxParent].pos + pPlayerPart[nCntPart].pos;
		}
		else
		{
			
		}
	}

	//影インデックス取得
	g_nIdxShadowPlayer = SetShadow(40.0f);
}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitPlayer(void)
{
	//変数宣言
	int nCntPlayer;

	//情報取得
	PlayerPart *pPlayerPart = GetPlayerPart();

	for (nCntPlayer = 0;nCntPlayer < g_nNumPlayerParts;nCntPlayer++)
	{
		if (pPlayerPart->pMesh != NULL)
		{//メッシュポインタの破棄
			pPlayerPart->pMesh->Release();
			pPlayerPart->pMesh = NULL;
		}
	}
	
	for (nCntPlayer = 0; nCntPlayer < g_nNumPlayerParts; nCntPlayer++)
	{
		if (pPlayerPart->pBuffMat != NULL)
		{//頂点バッファポインタの破棄
			pPlayerPart->pBuffMat->Release();
			pPlayerPart->pBuffMat = NULL;
		}
	}

	for (int nCntTex = 0;nCntTex < NUM_TEX * MAX_PART;nCntTex++)
	{
		if (g_apTexturePlayer[nCntTex / NUM_TEX][nCntTex % NUM_TEX] != NULL)
		{//テクスチャポインタの破棄
			g_apTexturePlayer[nCntTex / NUM_TEX][nCntTex % NUM_TEX]->Release();
			g_apTexturePlayer[nCntTex / NUM_TEX][nCntTex % NUM_TEX] = NULL;
		}
	}
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdatePlayer(void)
{
	//情報取得
	Camera *pCamera = GetCamera();

	//操作処理
	ControlPlayer();

	//位置更新処理
	UpdatePosPlayer();

	//移動制限処理
	LimitMovePlayer();

	//回転制御処理
	LimitRot(&g_player.rot);

	//デバッグ用,体回転
	g_aPlayerPart[1].rot.y += 0.3f;
	LimitRot(&g_aPlayerPart[1].rot);

	g_aPlayerPart[0].pos = g_player.pos;

	//影の位置設定
	SetPositionShadow(g_nIdxShadowPlayer, g_player.pos);
}

//==================================================================================================
//プレイヤー操作処理
//==================================================================================================
void ControlPlayer(void)
{
	//情報取得
	Camera *pCamera = GetCamera();

	//移動処理======================================================
	if (GetKeyboardRepeat(DIK_UP) == true)
	{//前移動
		g_player.move.x += sinf(g_player.rot.y + D3DX_PI) * MOVE_SPEED;
		g_player.move.z += cosf(g_player.rot.y + D3DX_PI) * MOVE_SPEED;
	}
	if (GetKeyboardRepeat(DIK_DOWN) == true)
	{//後移動
		g_player.move.x += sinf(g_player.rot.y) * MOVE_SPEED;
		g_player.move.z += cosf(g_player.rot.y) * MOVE_SPEED;
	}
	if (GetKeyboardRepeat(DIK_LEFT) == true)
	{//左移動
		g_player.move.x += sinf(g_player.rot.y + D3DX_PI * 0.5f) * MOVE_SPEED;
		g_player.move.z += cosf(g_player.rot.y + D3DX_PI * 0.5f) * MOVE_SPEED;
	}
	if (GetKeyboardRepeat(DIK_RIGHT) == true)
	{//右移動
		g_player.move.x += sinf(g_player.rot.y - D3DX_PI * 0.5f) * MOVE_SPEED;
		g_player.move.z += cosf(g_player.rot.y - D3DX_PI * 0.5f) * MOVE_SPEED;
	}

	if (GetKeyboardRepeat(DIK_LSHIFT) == true)
	{
		g_player.rot.y -= ROLL_SPEED;
	}
	if (GetKeyboardRepeat(DIK_RSHIFT) == true)
	{
		g_player.rot.y += ROLL_SPEED;
	}

	if (GetKeyboardTrigger(DIK_J) == true)
	{
		g_player.nLife--;
	}

	//攻撃処理======================================================
	if (GetKeyboardTrigger(DIK_SPACE) == true || GetGamePadTrigger(PADBUTTONS_RB,0) == true)
	{//弾発射
		SetBullet
		(
			D3DXVECTOR3
			(
				g_player.pos.x,
				g_player.pos.y + 10,
				g_player.pos.z
			),
			D3DXVECTOR3
			(
				-BULLET_SPEED * sinf(g_player.rot.y) * cosf(g_player.rot.x),
				-BULLET_SPEED * sinf(g_player.rot.y) * sinf(g_player.rot.x),
				-BULLET_SPEED * cosf(g_player.rot.y)
			)
		);
	}

	//コントローラー=============================================
	float fStickAngle = atan2f(GetVecStickL().x, GetVecStickL().y);
	float fStickLength = sqrtf(GetVecStickL().x * GetVecStickL().x + GetVecStickL().y * GetVecStickL().y);

	if (fStickLength != 0)
	{
		g_player.move.x -= sinf(g_player.rot.y + fStickAngle) * MOVE_SPEED;
		g_player.move.z -= cosf(g_player.rot.y + fStickAngle) * MOVE_SPEED;
	}

	if (g_player.fBoost >= g_player.fBoostMax)
	{
		g_player.fBoost = g_player.fBoostMax;
	}
	else
	{
		g_player.fBoost ++;
	}

	if (g_player.fBoost > DODGE_COST)
	{//ブースター使用
		if (GetGamePadTrigger(PADBUTTONS_A, 0) == true)
		{
			g_player.fBoost -= DODGE_COST;

			g_player.move.x -= sinf(g_player.rot.y + fStickAngle) * MOVE_SPEED * BOOST_SPEED;
			g_player.move.z -= cosf(g_player.rot.y + fStickAngle) * MOVE_SPEED * BOOST_SPEED;
		
			SetParticle
			(
				D3DXVECTOR3
				(
					g_player.pos.x - sinf(g_player.rot.x) * sinf(g_player.rot.y) * 10.0f,
					g_player.pos.y - cosf(g_player.rot.x) * 10.0f,
					g_player.pos.z - sinf(g_player.rot.x) * cosf(g_player.rot.y) * 10.0f
				),
				PARTICLE_TYPE_BOOST,
				D3DXVECTOR3(2.0f, g_player.rot.y, 0.0f),
				&g_player.pos
			);
		}
	}

	g_player.rot.y += GetJoyStickRX(0) * ROLL_SPEED;
}

//==================================================================================================
//位置更新処理
//==================================================================================================
void UpdatePosPlayer(void)
{
	//変数宣言
	D3DXVECTOR3 move = g_player.move;

	//位置更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.z += g_player.move.z;

	//移動量減衰
	g_player.move.x = g_player.move.x * MOVE_FACT;
	g_player.move.z = g_player.move.z * MOVE_FACT;
}

//==================================================================================================
//移動制限処理
//==================================================================================================
void LimitMovePlayer(void)
{
	MeshWall *pMeshWall = GetMeshWall();

	for (int nCntWall = 0;nCntWall < MAX_WALL; nCntWall++,pMeshWall++)
	{
		if (pMeshWall->bUse)
		{
			WallCrossProduct
			(
				g_player.pos,
				&g_player.pos,
				&g_player.move,
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
				),
				1.0f
			);
		}
	}
}

//==================================================================================================
//描画処理
//==================================================================================================
void DrawPlayer(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	D3DXMATRIX mtxRot, mtxTrans,mtxRot2;
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ
	D3DXVECTOR3 posPart,rotPart;

	//情報取得
	PlayerPart *pPlayerPart = GetPlayerPart();
	
	for (int nCntPlayer = 0; nCntPlayer < g_nNumPlayerParts; nCntPlayer++)
	{
		//ワールドマトリックス初期化
		D3DXMatrixIdentity(&pPlayerPart[nCntPlayer].mtxWorld);

		if (pPlayerPart[nCntPlayer].nIdxParent != -1)
		{//親のマトリックスを継ぐ
		}
		else
		{//全ての親パーツ
			posPart = g_player.pos + pPlayerPart[nCntPlayer].pos;
			rotPart = g_player.rot + pPlayerPart[nCntPlayer].rot;
		}

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			pPlayerPart[nCntPlayer].rot.y, pPlayerPart[nCntPlayer].rot.x, pPlayerPart[nCntPlayer].rot.z);
		D3DXMatrixMultiply(&pPlayerPart[nCntPlayer].mtxWorld, &pPlayerPart[nCntPlayer].mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans,
			pPlayerPart[nCntPlayer].pos.x, pPlayerPart[nCntPlayer].pos.y, pPlayerPart[nCntPlayer].pos.z);
		D3DXMatrixMultiply(&pPlayerPart[nCntPlayer].mtxWorld, &pPlayerPart[nCntPlayer].mtxWorld, &mtxTrans);

		//ワールドマトリックス設定
		pDevice->SetTransform(D3DTS_WORLD, &pPlayerPart[nCntPlayer].mtxWorld);

		//現在のマテリアル取得
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)pPlayerPart[nCntPlayer].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)pPlayerPart[nCntPlayer].dwNumMat; nCntMat++)
		{
			//マテリアル設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//色設定
			//pMat[nCntMat].MatD3D.Diffuse = {0.0f,0.0f,0.0f,1.0f};

			//テクスチャ設定
			pDevice->SetTexture(0, g_apTexturePlayer[nCntPlayer][nCntMat]);

			//モデル（パーツ）描画
			pPlayerPart[nCntPlayer].pMesh->DrawSubset(nCntMat);
		}

		//マテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//==================================================================================================
//プレイヤー状態描画(デバッグ)
//==================================================================================================
void DrawPlayerState(LPD3DXFONT pFont)
{
	//変数宣言
	RECT rect = { 20,390,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	float fSpeed = sqrtf(g_player.move.x * g_player.move.x + g_player.move.z * g_player.move.z);

	//文字列に代入
	sprintf(&aStr[0], "プレイヤーの位置[%.2f,%.2f,%.2f]\nプレイヤーの向き[%.2f,%.2f,%.2f]\nブースト残量[%.2f]  プレイヤーの速度[%.2f]", 
		g_player.pos.x, g_player.pos.y, g_player.pos.z,g_player.rot.x, g_player.rot.y, g_player.rot.z,g_player.fBoost, fSpeed);

	//テキスト描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//プレイヤー操作描画(デバッグ)
//==================================================================================================
void DrawControlPlayer(LPD3DXFONT pFont)
{
	//変数宣言
	RECT rect = { 20,230,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	sprintf(&aStr[0], "プレイヤー水平移動[矢印キー]\n弾発射[SPACE]\n回転[L,RSHIFT]");

	//テキスト描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//パーツ状態描画(デバッグ)
//==================================================================================================
void DrawPPartState(LPD3DXFONT pFont)
{
	char aStr[256];

	for (int nCntPart = 0;nCntPart < g_nNumPlayerParts;nCntPart++)
	{
		//変数宣言
		RECT rect = { 1000,20 + 20 * nCntPart,SCREEN_WIDTH,SCREEN_HEIGHT };

		//文字列に代入
		sprintf(&aStr[0], "%d番パーツの位置[%.2f,%.2f,%.2f]",
			nCntPart,g_aPlayerPart[nCntPart].mtxWorld._41, g_aPlayerPart[nCntPart].mtxWorld._42, g_aPlayerPart[nCntPart].mtxWorld._43);

		//テキスト描画
		pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}

//==================================================================================================
//ファイル読み込み
//==================================================================================================
void LoadMotion(FILE *pFile)
{
	//情報取得
	PlayerPart *pPlayerPart = GetPlayerPart();

	//変数宣言
	char cTemp[MAX_STRING];

	while (1)
	{
		//文字読み込み
		fscanf(pFile, "%s", &cTemp[0]);

		//ファイル名読み込み=========================================
		if (strcmp(cTemp, "NUM_MODEL") == 0)
		{//モデル数読み込み

		    //"="読み込み
			fscanf(pFile, "%s", &cTemp[0]);

			//モデル数読み込み
			fscanf(pFile, "%d", &g_nNumPlayerParts);

			for (int nCntFile = 0; nCntFile < g_nNumPlayerParts;)
			{//ファイル名読み込み

				fscanf(pFile, "%s", &cTemp[0]);

				if (strcmp(cTemp, "MODEL_FILENAME") == 0)
				{//ファイル名読み込み
					fscanf(pFile, "%s", &cTemp[0]);

					fscanf(pFile, "%s", &g_acFilenamePlayer[nCntFile][0]);

					nCntFile++;
				}
			}
		}
		//===========================================================

		//キャラクター設定===========================================
		if (strcmp(cTemp, "CHARACTERSET") == 0)
		{//キャラクタースタート
			while (strcmp(cTemp, "END_CHARACTERSET") != 0)
			{//終わりまでキャラクター設定
				fscanf(pFile, "%s", &cTemp[0]);

				if (strcmp(cTemp, "PARTSSET") == 0)
				{//パーツスタート
					while (strcmp(cTemp, "END_PARTSSET") != 0)
					{//終わりまでパーツ設定
						fscanf(pFile, "%s", &cTemp[0]);

						if (strcmp(cTemp, "INDEX") == 0)
						{//番号読み込み
							fscanf(pFile, "%s", &cTemp[0]);

							fscanf(pFile, "%d", &pPlayerPart->nIdx);
						}

						if (strcmp(cTemp, "PARENT") == 0)
						{//親番号読み込み
							fscanf(pFile, "%s", &cTemp[0]);

							fscanf(pFile, "%d", &pPlayerPart->nIdxParent);
						}

						if (strcmp(cTemp, "POS") == 0)
						{//位置読み込み
							fscanf(pFile, "%s", &cTemp[0]);

							for (int nCntPos = 0; nCntPos < 3; nCntPos++)
							{
								fscanf(pFile, "%f", &pPlayerPart->pos[nCntPos]);
							}
						}

						if (strcmp(cTemp, "ROT") == 0)
						{//向き読み込み
							fscanf(pFile, "%s", &cTemp[0]);

							for (int nCntRot = 0; nCntRot < 3; nCntRot++)
							{
								fscanf(pFile, "%f", &pPlayerPart->rot[nCntRot]);
							}
						}

					}//END_PART

					pPlayerPart++;
				}
			}//END_CHAR
		}
		//===========================================================

		if (strcmp(cTemp, "END_SCRIPT") == 0)
		{
			break;
		}
	}//while閉じ
}

//==================================================================================================
//情報取得
//==================================================================================================
Player *GetPlayer(void)
{
	return &g_player;
}

//==================================================================================================
//情報取得
//==================================================================================================
PlayerPart *GetPlayerPart(void)
{
	return &g_aPlayerPart[0];
}