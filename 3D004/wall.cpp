//==================================================================================================
//
//wall.cpp
//Author:ûüRç
//
//==================================================================================================

#include "main.h"
#include "wall.h"
#include "input.h"

//}Nè`
#define WALL_TEX_FILE			"data\\TEXTURE\\BG\\metal000.jpg"		//eNX`t@C¼
#define MOVE_SPEED				(1.0f)									//Ú®¬x

//O[oÏé¾
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;		//eNX`ÖÌ|C^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//¸_obt@ÖÌ|C^
Wall g_aWall[MAX_WALL];							//\¢ÌÌîñ

//==================================================================================================
//ú»
//==================================================================================================
void InitWall(void)
{
	//foCX|C^Ýè
	LPDIRECT3DDEVICE9 pDevice;

	//foCXÌæ¾
	pDevice = GetDevice();

	//eNX`ÇÝÝ
	D3DXCreateTextureFromFile(pDevice,
		WALL_TEX_FILE,
		&g_pTextureWall);

	//¸_obt@Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	//¸_îñÌ|C^
	VERTEX_3D *pVtx;

	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	//îñæ¾
	Wall *pWall = GetWall();

	for (int nCntWall = 0; nCntWall < MAX_WALL;nCntWall++, pWall++)
	{
		//Ïú»
		pWall->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pWall->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pWall->height = 0.0f;
		pWall->width = 0.0f;
		pWall->bUse = false;

		//¸_ÀWÌÝè
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//@üxNgÌÝè
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//¸_J[ÌÝè
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//eNX`ÀW
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(10.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 10.0f);
		pVtx[3].tex = D3DXVECTOR2(10.0f, 10.0f);

		//|C^ðißé
		pVtx += 4;
	}

	//¸_obt@ðAbN
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

	//§¾Ç========================================================================
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
//I¹
//==================================================================================================
void UninitWall(void)
{
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	if (g_pVtxBuffWall != NULL)
	{//¸_obt@|C^Ìjü
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//==================================================================================================
//XV
//==================================================================================================
void UpdateWall(void)
{
}

//==================================================================================================
//`æ
//==================================================================================================
void DrawWall(void)
{
	//foCX|C^Ýè
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;

	//foCXÌæ¾
	pDevice = GetDevice();

	//îñæ¾
	Wall *pWall = GetWall();

	for (int nCntWall = 0;nCntWall < MAX_WALL;nCntWall++,pWall++)
	{
		if (pWall->bUse == true)
		{//gpµÄ¢éê
		 //[h}gbNXú»
			D3DXMatrixIdentity(&pWall->mtxWorld);

			//ü«ð½f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				pWall->rot.y, pWall->rot.x, pWall->rot.z);
			D3DXMatrixMultiply(&pWall->mtxWorld, &pWall->mtxWorld, &mtxRot);

			//Êuð½f
			D3DXMatrixTranslation(&mtxTrans,
				pWall->pos.x, pWall->pos.y, pWall->pos.z);
			D3DXMatrixMultiply(&pWall->mtxWorld, &pWall->mtxWorld, &mtxTrans);

			//[h}gbNXÝè
			pDevice->SetTransform(D3DTS_WORLD, &pWall->mtxWorld);

			//¸_obt@ðf[^Xg[ÉÝè
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//¸_tH[}bgÌÝè
			pDevice->SetFVF(FVF_VERTEX_3D);

			//eNX`Ýè
			pDevice->SetTexture(0, g_pTextureWall);

			//|S`æ
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntWall, 2);
		}
	}
}

//==================================================================================================
//îñæ¾
//==================================================================================================
Wall *GetWall(void)
{
	return &g_aWall[0];
}

//==================================================================================================
//Ýè
//==================================================================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXCOLOR col)
{
	//¸_îñÌ|C^
	VERTEX_3D *pVtx;

	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	//îñæ¾
	Wall *pWall = GetWall();

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pWall++)
	{
		if (pWall->bUse == false)
		{//gpµÄ¢È¢óÔ
			//Ïú»
			pWall->pos = pos;
			pWall->rot = rot;

			//¸_ÀWÌÝè
			pVtx[0].pos = D3DXVECTOR3(-WALL_WIDTH * 0.5f, WALL_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(WALL_WIDTH * 0.5f, WALL_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-WALL_WIDTH * 0.5f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(WALL_WIDTH * 0.5f, 0.0f, 0.0f);

			//@üxNgÌÝè
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			//¸_J[ÌÝè
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			//eNX`ÀW
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(10.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 10.0f);
			pVtx[3].tex = D3DXVECTOR2(10.0f, 10.0f);

			//gpóÔÉ·é
			pWall->bUse = true;

			//for¶ð²¯é
			break;
		}

		//|C^ðißé
		pVtx += 4;
	}

	//¸_obt@ðAbN
	g_pVtxBuffWall->Unlock();
}