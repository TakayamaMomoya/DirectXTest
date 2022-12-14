//==================================================================================================
//
//meshwall.cpp
//Author:ûüRç
//
//==================================================================================================

#include "main.h"
#include "meshwall.h"
#include "input.h"

//}Nè`
#define MESHWALL_TEX_FILE			"data\\TEXTURE\\BG\\metal000.jpg"			//eNX`t@C¼
#define MOVE_SPEED					(1.0f)										//Ú®¬x
#define MESH_LENGTH					(500.0f)									//bVÌêÓÌ·³
#define MESH_U						(2)											//¡ÌubN
#define MESH_V						(1)											//cÌubN
#define MAX_SPLIT					(10)										//Ååª
#define SPLIT_TEX_U					(4)											//¡ÌeNX`ª
#define SPLIT_TEX_V					(1)											//cÌeNX`ª

//O[oÏé¾
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;									//eNX`ÖÌ|C^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;								//¸_obt@ÖÌ|C^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;								//CfbNXobt@ÖÌ|C^
MeshWall g_aMeshWall[MAX_MESHWALL];												//\¢ÌÌîñ
int g_nMaxIdxMeshWall;															//ÅåCfbNX
int g_nMaxVtxMeshWall;															//Åå¸_

//==================================================================================================
//ú»
//==================================================================================================
void InitMeshWall(void)
{
	//foCX|C^Ýè
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//eNX`ÇÝÝ
	D3DXCreateTextureFromFile(pDevice,
		MESHWALL_TEX_FILE,
		&g_pTextureMeshWall);

	//êÂ ½èÌÅå¸_
	g_nMaxVtxMeshWall = (MAX_SPLIT + 1) * (MAX_SPLIT + 1);

	//¸_obt@Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nMaxVtxMeshWall * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	//êÂ ½èÌÅåCfbNX
	g_nMaxIdxMeshWall = (MAX_SPLIT + 1) * (MAX_SPLIT + 1) + ((MAX_SPLIT + 1) - 2) * (MAX_SPLIT + 1) + (((MAX_SPLIT + 1) - 2) * 2);

	//CfbNXobt@Ì¶¬
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nMaxIdxMeshWall * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	//¸_îñÌ|C^
	VERTEX_3D *pVtx;

	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	//CfbNXobt@ÖÌ|C^
	WORD *pIdx;

	//CfbNXobt@ðbNµA¸_ÔÖÌ|C^ðæ¾
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntWall = 0;nCntWall < MAX_MESHWALL;nCntWall++)
	{
		//Ïú»
		g_aMeshWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntWall].bUse = false;
		g_aMeshWall[nCntWall].nNumIdx = 0;
		g_aMeshWall[nCntWall].nNumVtx = 0;
		g_aMeshWall[nCntWall].width = 0;
		g_aMeshWall[nCntWall].height = 0;

		for (int nCntVtx = 0; nCntVtx < g_nMaxVtxMeshWall; nCntVtx++)
		{//¸_îñÌÝè
			pVtx[nCntVtx].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			pVtx[nCntVtx].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[nCntVtx].tex = D3DXVECTOR2(0.0f, 0.0f);
		}

		for (int nCount = 0; nCount < g_nMaxIdxMeshWall; nCount++)
		{//CfbNXè
			pIdx[nCount] = 0;
		}

		//|C^ðißé
		pIdx += g_nMaxIdxMeshWall;
		pVtx += g_nMaxVtxMeshWall;
	}

	//¸_obt@ðAbN
	g_pVtxBuffMeshWall->Unlock();

	//CfbNXobt@ðAbN
	g_pIdxBuffMeshWall->Unlock();

	SetMeshWall
	(
		D3DXVECTOR3(0.0f,0.0f,-500.0f),
		D3DXVECTOR3(0.0f,D3DX_PI,0.0f),
		1000.0f,
		150.0f
	);

	SetMeshWall
	(
		D3DXVECTOR3(-500.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),
		1000.0f,
		150.0f
	);

	SetMeshWall
	(
		D3DXVECTOR3(0.0f, 0.0f, 500.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		1000.0f,
		150.0f
	);

	SetMeshWall
	(
		D3DXVECTOR3(500.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		1000.0f,
		150.0f
	);

	SetMeshWall
	(
		D3DXVECTOR3(50.0f, 0.0f, -500.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.8f, 0.0f),
		1000.0f,
		150.0f
	);
}

//==================================================================================================
//I¹
//==================================================================================================
void UninitMeshWall(void)
{
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}

	if (g_pVtxBuffMeshWall != NULL)
	{//¸_obt@|C^Ìjü
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	if (g_pIdxBuffMeshWall != NULL)
	{//CfbNXobt@|C^Ìjü
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//==================================================================================================
//XV
//==================================================================================================
void UpdateMeshWall(void)
{
}

//==================================================================================================
//`æ
//==================================================================================================
void DrawMeshWall(void)
{
	//foCX|C^Ýè
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		if (g_aMeshWall[nCntWall].bUse)
		{
			//[h}gbNXú»
			D3DXMatrixIdentity(&g_aMeshWall[nCntWall].mtxWorld);

			//ü«ð½f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aMeshWall[nCntWall].rot.y, g_aMeshWall[nCntWall].rot.x, g_aMeshWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntWall].mtxWorld, &g_aMeshWall[nCntWall].mtxWorld, &mtxRot);

			//Êuð½f
			D3DXMatrixTranslation(&mtxTrans,
				g_aMeshWall[nCntWall].pos.x, g_aMeshWall[nCntWall].pos.y, g_aMeshWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntWall].mtxWorld, &g_aMeshWall[nCntWall].mtxWorld, &mtxTrans);

			//[h}gbNXÝè
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshWall[nCntWall].mtxWorld);

			//¸_obt@ðf[^Xg[ÉÝè
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			//CfbNXobt@ðf[^Xg[ÉÝè
			pDevice->SetIndices(g_pIdxBuffMeshWall);

			//¸_tH[}bgÌÝè
			pDevice->SetFVF(FVF_VERTEX_3D);

			//eNX`Ýè
			pDevice->SetTexture(0, g_pTextureMeshWall);

			//|S`æ
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				0,
				g_aMeshWall[nCntWall].nNumVtx,								//¸_
				g_nMaxIdxMeshWall * nCntWall,								//ÅÌCfbNX
				g_aMeshWall[nCntWall].nNumIdx - 2							//|S
			);
		}
	}
}

//==================================================================================================
//ÇÝè
//==================================================================================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float width,float height)
{
	//¸_îñÌ|C^
	VERTEX_3D *pVtx;

	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	//CfbNXobt@ÖÌ|C^
	WORD *pIdx;

	//CfbNXobt@ðbNµA¸_ÔÖÌ|C^ðæ¾
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		if (g_aMeshWall[nCntWall].bUse == false)
		{
			//øó¯æè
			g_aMeshWall[nCntWall].pos = pos;
			g_aMeshWall[nCntWall].rot = rot;
			g_aMeshWall[nCntWall].bUse = true;
			g_aMeshWall[nCntWall].width = width;
			g_aMeshWall[nCntWall].height = height;

			//¸_vZ
			g_aMeshWall[nCntWall].nNumVtx = (MESH_U + 1) * (MESH_V + 1);

			for (int nCountV = 0; nCountV < MESH_V + 1; nCountV++)
			{//¸_ÀWÌÝè
				for (int nCountU = 0; nCountU < MESH_U + 1; nCountU++)
				{
					pVtx[nCountV * (MESH_U + 1) + nCountU].pos.x = (nCountU - ((MESH_U) * 0.5f)) * (width / MESH_U);
					pVtx[nCountV * (MESH_U + 1) + nCountU].pos.z = 0.0f;
					pVtx[nCountV * (MESH_U + 1) + nCountU].pos.y = (MESH_V - nCountV) * (height / MESH_V);

					//eNX`ÀW
					pVtx[nCountV * (MESH_U + 1) + nCountU].tex = D3DXVECTOR2
					(
						((float)SPLIT_TEX_U / MESH_U) * nCountU,
						((float)SPLIT_TEX_V / MESH_V) * nCountV
					);
				}
			}

			for (int nCnt = 0; nCnt < g_aMeshWall[nCntWall].nNumVtx; nCnt++)
			{
				//@üxNgÌÝè
				pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

				//¸_J[ÌÝè
				pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}

			g_aMeshWall[nCntWall].nNumIdx = (MESH_U + 1) * (MESH_V + 1) + ((MESH_V + 1) - 2) * (MESH_U + 1) + (((MESH_V + 1) - 2) * 2);

			for (int nCount = 0; nCount < g_aMeshWall[nCntWall].nNumIdx / 2; nCount++)
			{//CfbNXè
				if (
					nCount % ((MESH_U + 1) + (MESH_U + 2) * (nCount / (MESH_U + 2))) == 0
					&& nCount != 0
					)
				{//ÜèÔµ
					pIdx[nCount * 2 + 1] = ((MESH_U + 1) * 2) + (MESH_U + 1) * (nCount / (MESH_U + 2));

					pIdx[nCount * 2] = MESH_U + (MESH_U + 1) * (nCount / (MESH_U + 2));
				}
				else
				{//Êí
					pIdx[nCount * 2 + 1] = nCount - (nCount / (MESH_U + 2));

					pIdx[nCount * 2] = (nCount - (nCount / (MESH_U + 2))) + (MESH_U + 1);
				}
			}

			//for¶²¯é
			break;
		}

		//|C^ðißé
		pIdx += g_nMaxIdxMeshWall;
		pVtx += g_nMaxVtxMeshWall;
	}

	//¸_obt@ðAbN
	g_pVtxBuffMeshWall->Unlock();

	//CfbNXobt@ðAbN
	g_pIdxBuffMeshWall->Unlock();
}

//==================================================================================================
//|C^æ¾
//==================================================================================================
MeshWall *GetMeshWall(void)
{
	return &g_aMeshWall[0];
}