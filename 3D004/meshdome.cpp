//==================================================================================================
//
//meshdome.cpp
//Author:ûüRç
//
//==================================================================================================

#include "main.h"
#include "meshdome.h"
#include "input.h"
#include "light.h"

//}Nè`
#define MESHDOME_TEX_FILE		"data\\TEXTURE\\BG\\sky000.png"					//eNX`t@C¼
#define MOVE_SPEED					(1.0f)										//Ú®¬x
#define MESH_LENGTH					(300.0f)									//bVÌêÓÌ·³
#define MESH_U						(16)										//¡ÌubN
#define MESH_V						(3)											//cÌubN
#define MAX_DOME					(8)											//ÌÅå
#define SPLIT_TEX_U					(3)											//¡ÌeNX`ª
#define SPLIT_TEX_V					(1)											//cÌeNX`ª

//O[oÏé¾
LPDIRECT3DTEXTURE9 g_pTextureMeshDome = NULL;									//eNX`ÖÌ|C^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshDome = NULL;								//¸_obt@ÖÌ|C^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshDome = NULL;								//CfbNXobt@ÖÌ|C^
MeshDome g_aMeshDome[MAX_DOME];													//\¢ÌÌîñ

//==================================================================================================
//ú»
//==================================================================================================
void InitMeshDome(void)
{
	//foCX|C^Ýè
	LPDIRECT3DDEVICE9 pDevice;

	//foCXÌæ¾
	pDevice = GetDevice();

	//eNX`ÇÝÝ
	D3DXCreateTextureFromFile(pDevice,
		MESHDOME_TEX_FILE,
		&g_pTextureMeshDome);

	//¸_obt@Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (MESH_U + 1) * 2 * (MESH_V + 1) * MAX_DOME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshDome,
		NULL);

	//CfbNXobt@Ì¶¬
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((MESH_U + 1) * 2 * (MESH_V + 1) + ((MESH_V + 1) - 2) * (MESH_U + 1) + (((MESH_V + 1) - 2) * 2)) * MAX_DOME,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshDome,
		NULL);

	//¸_îñÌ|C^
	VERTEX_3D *pVtx;

	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffMeshDome->Lock(0, 0, (void**)&pVtx, 0);

	//CfbNXobt@ÖÌ|C^
	WORD *pIdx;

	//CfbNXobt@ðbNµA¸_ÔÖÌ|C^ðæ¾
	g_pIdxBuffMeshDome->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntWall = 0;nCntWall < MAX_DOME;nCntWall++)
	{
		//Ïú»
		g_aMeshDome[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshDome[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshDome[nCntWall].bUse = false;

		//vZpÏ
		int nCountU, nCountV;
		float fRotX, fRotY;
		float fLength = 2000.0f;
		D3DXVECTOR3 VecRot;

		//¸_îñ==================================================================================
		//Åå¸_vZ
		g_aMeshDome[nCntWall].nNumVtx = (MESH_U + 1) * (MESH_V + 1) + (MESH_U + 1);	//lp`ÌªÆAWÌ~`Ìª
		
		for (nCountV = 0; nCountV < MESH_V + 1; nCountV++)
		{//¸_ÀWÌÝè

			fRotX = D3DX_PI * 0.5f - nCountV * (D3DX_PI * 0.5f / MESH_V - 1);

			for (nCountU = 0; nCountU < MESH_U + 1; nCountU++)
			{
				//pxZo
				fRotY = -nCountU * (D3DX_PI / MESH_U) * 2;

				pVtx[nCountV * (MESH_U + 1) + nCountU].pos.x = sinf(fRotX) * sinf(fRotY) * fLength;
				pVtx[nCountV * (MESH_U + 1) + nCountU].pos.y = -cosf(fRotX) * fLength;
				pVtx[nCountV * (MESH_U + 1) + nCountU].pos.z = sinf(fRotX) * cosf(fRotY) * fLength;

				//eNX`ÀW
				pVtx[nCountV * (MESH_U + 1) + nCountU].tex = D3DXVECTOR2
				(
					((float)SPLIT_TEX_U / MESH_U) * nCountU,
					((float)SPLIT_TEX_V / MESH_V) * nCountV
				);

				VecRot = D3DXVECTOR3
				(
					pVtx[nCountV * (MESH_U + 1) + nCountU].pos.x,
					0.0f,
					pVtx[nCountV * (MESH_U + 1) + nCountU].pos.z
				);

				//xNg³K»
				D3DXVec3Normalize(&VecRot, &VecRot);

				//@üxNgÌÝè
				pVtx[nCountV * (MESH_U + 1) + nCountU].nor = VecRot;
			}
		}

		////WÌ¸_=====================================================================
		//pVtx[86].pos.x = 0.0f;
		//pVtx[86].pos.y = fLength;
		//pVtx[86].pos.z = 0.0f;

		//fRotX = D3DX_PI - D3DX_PI / MESH_U;

		//for (int nCntFan = 0; nCntFan < MESH_U; nCntFan++)
		//{
		//	//pxZo
		//	fRotY = -nCntFan * (D3DX_PI / MESH_U) * 2;

		//	pVtx[86 + nCntFan].pos.x = sinf(fRotX) * sinf(fRotY) * fLength;
		//	pVtx[86 + nCntFan].pos.y = -cosf(fRotX) * fLength;
		//	pVtx[86 + nCntFan].pos.z = sinf(fRotX) * cosf(fRotY) * fLength;
		//}

		for (int nCnt = 0; nCnt < g_aMeshDome[nCntWall].nNumVtx; nCnt++)
		{
			//¸_J[ÌÝè
			pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		//CfbNX==================================================================================
		g_aMeshDome[nCntWall].nNumIdx = (MESH_U + 1) * (MESH_V + 1) + ((MESH_V + 1) - 2) * (MESH_U + 1) + (((MESH_V + 1) - 2) * 2) + (MESH_U + 1);

		int nCntIdx;

		for (nCntIdx = 0; nCntIdx < (g_aMeshDome[nCntWall].nNumIdx - MESH_U - 1) / 2; nCntIdx++)
		{//CfbNXè
			if (
				nCntIdx % ((MESH_U + 1) + (MESH_U + 2) * (nCntIdx / (MESH_U + 2))) == 0
				&& nCntIdx != 0
				)
			{
				pIdx[nCntIdx * 2 + 1] = ((MESH_U + 1) * 2) + (MESH_U + 1) * (nCntIdx / (MESH_U + 2));

				pIdx[nCntIdx * 2] = MESH_U + (MESH_U + 1) * (nCntIdx / (MESH_U + 2));
			}
			else
			{
				pIdx[nCntIdx * 2 + 1] = nCntIdx - (nCntIdx / (MESH_U + 2));

				pIdx[nCntIdx * 2] = (nCntIdx - (nCntIdx / (MESH_U + 2))) + (MESH_U + 1);
			}
		}

		//|C^ðißé
		pIdx += g_aMeshDome[nCntWall].nNumIdx;
		pVtx += g_aMeshDome[nCntWall].nNumVtx;
	}

	//¸_obt@ðAbN
	g_pVtxBuffMeshDome->Unlock();

	//CfbNXobt@ðAbN
	g_pIdxBuffMeshDome->Unlock();

	SetMeshDome
	(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	);
}

//==================================================================================================
//I¹
//==================================================================================================
void UninitMeshDome(void)
{
	if (g_pTextureMeshDome != NULL)
	{
		g_pTextureMeshDome->Release();
		g_pTextureMeshDome = NULL;
	}

	if (g_pVtxBuffMeshDome != NULL)
	{//¸_obt@|C^Ìjü
		g_pVtxBuffMeshDome->Release();
		g_pVtxBuffMeshDome = NULL;
	}

	if (g_pIdxBuffMeshDome != NULL)
	{//CfbNXobt@|C^Ìjü
		g_pIdxBuffMeshDome->Release();
		g_pIdxBuffMeshDome = NULL;
	}
}

//==================================================================================================
//XV
//==================================================================================================
void UpdateMeshDome(void)
{
}

//==================================================================================================
//`æ
//==================================================================================================
void DrawMeshDome(void)
{
	//foCX|C^Ýè
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntWall = 0; nCntWall < MAX_DOME; nCntWall++)
	{
		if (g_aMeshDome[nCntWall].bUse)
		{
			//[h}gbNXú»
			D3DXMatrixIdentity(&g_aMeshDome[nCntWall].mtxWorld);

			//ü«ð½f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aMeshDome[nCntWall].rot.y, g_aMeshDome[nCntWall].rot.x, g_aMeshDome[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aMeshDome[nCntWall].mtxWorld, &g_aMeshDome[nCntWall].mtxWorld, &mtxRot);

			//Êuð½f
			D3DXMatrixTranslation(&mtxTrans,
				g_aMeshDome[nCntWall].pos.x, g_aMeshDome[nCntWall].pos.y, g_aMeshDome[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aMeshDome[nCntWall].mtxWorld, &g_aMeshDome[nCntWall].mtxWorld, &mtxTrans);

			//[h}gbNXÝè
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshDome[nCntWall].mtxWorld);

			//¸_obt@ðf[^Xg[ÉÝè
			pDevice->SetStreamSource(0, g_pVtxBuffMeshDome, 0, sizeof(VERTEX_3D));

			//CfbNXobt@ðf[^Xg[ÉÝè
			pDevice->SetIndices(g_pIdxBuffMeshDome);

			//¸_tH[}bgÌÝè
			pDevice->SetFVF(FVF_VERTEX_3D);

			//eNX`Ýè
			pDevice->SetTexture(0, g_pTextureMeshDome);

			//|S`æ
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				0,
				g_aMeshDome[nCntWall].nNumVtx - MESH_U + 1,					//¸_(Wð­)
				g_aMeshDome[nCntWall].nNumIdx * nCntWall,					//ÅÌCfbNX
				g_aMeshDome[nCntWall].nNumIdx - 2 - MESH_U					//|S(V)
			);

			//|S`æ
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLEFAN,
				0,
				0,
				MESH_U + 1,														//¸_(W)
				g_aMeshDome[nCntWall].nNumIdx - MESH_U - 1,						//ÅÌCfbNX(WÌÆ±ë©ç)
				MESH_U															//|S(V)
			);
		}
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==================================================================================================
//Ýè
//==================================================================================================
void SetMeshDome(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntWall = 0; nCntWall < MAX_DOME; nCntWall++)
	{
		if (g_aMeshDome[nCntWall].bUse == false)
		{
			g_aMeshDome[nCntWall].pos = pos;
			g_aMeshDome[nCntWall].rot = rot;

			g_aMeshDome[nCntWall].bUse = true;

			//for¶²¯é
			break;
		}
	}
}