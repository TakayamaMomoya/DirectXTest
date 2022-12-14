//==================================================================================================
//
//enemy.cpp
//Author:ûüRç
//
//==================================================================================================

#include "main.h"
#include "enemy.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include <stdio.h>

//}Nè`
#define MOVE_SPEED					(1.0f)									//Ú®¬x
#define NUM_TEX						(8)										//eNX`
#define ROLL_FACT					(0.06f)									//ñ]¸W

//O[oÏé¾
LPDIRECT3DTEXTURE9 g_apTextureEnemy[ENEMYTYPE_MAX][NUM_TEX] = {};			//eNX`ÖÌ|C^
LPD3DXMESH g_pMeshEnemy[ENEMYTYPE_MAX] = {};								//bVÖÌ|C^
LPD3DXBUFFER g_pBuffMatEnemy[ENEMYTYPE_MAX] = {};							//}eAÖÌobt@
DWORD g_dwNumMatEnemy[ENEMYTYPE_MAX];										//}eAÌ
Enemy g_aEnemy[MAX_ENEMY];													//\¢ÌÌîñ

//==================================================================================================
//ú»
//==================================================================================================
void InitEnemy(void)
{
	//foCX|C^Ýè
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;				//}eAf[^ÖÌ|C^

	//îñæ¾
	Enemy *pEnemy = GetEnemy();
	
	//Ïú»
	for (int nCount = 0; nCount < ENEMYTYPE_MAX;nCount++)
	{
		g_dwNumMatEnemy[nCount] = 0;
	}

	//Xt@CÇÝÝ
	D3DXLoadMeshFromX("data\\MODEL\\viecle\\ApacheHelicopter.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatEnemy[ENEMYTYPE_HELI],
		NULL,
		&g_dwNumMatEnemy[ENEMYTYPE_HELI],
		&g_pMeshEnemy[ENEMYTYPE_HELI]);

	pMat = (D3DXMATERIAL*)g_pBuffMatEnemy[ENEMYTYPE_HELI]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatEnemy[ENEMYTYPE_HELI]; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//eNX`ª¶Ý·é
			//eNX`ÇÝÝ
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureEnemy[ENEMYTYPE_HELI][nCntMat]);
		}
	}

	//Xt@CÇÝÝ
	D3DXLoadMeshFromX("data\\MODEL\\viecle\\tank000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatEnemy[ENEMYTYPE_TANK],
		NULL,
		&g_dwNumMatEnemy[ENEMYTYPE_TANK],
		&g_pMeshEnemy[ENEMYTYPE_TANK]);

	pMat = (D3DXMATERIAL*)g_pBuffMatEnemy[ENEMYTYPE_TANK]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatEnemy[ENEMYTYPE_TANK]; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//eNX`ª¶Ý·é
		 //eNX`ÇÝÝ
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureEnemy[ENEMYTYPE_TANK][nCntMat]);
		}
	}

	for (int nCntEnemy = 0;nCntEnemy < MAX_ENEMY;nCntEnemy++, pEnemy++)
	{
		//Ïú»
		pEnemy->pos = { 0.0f,0.0f,0.0f };
		pEnemy->rot = { 0.0f,0.0f,0.0f };
		pEnemy->vtxMin = { 0.0f,0.0f,0.0f };
		pEnemy->vtxMax = { 0.0f,0.0f,0.0f };
		pEnemy->type = ENEMYTYPE_HELI;
		pEnemy->bUse = false;

		////¸_Ìæ¾
		//nNumVtx = g_pMeshEnemy->GetNumVertices();

		////tH[}bgTCYüè
		//dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshEnemy->GetFVF());

		////¸_obt@ÌbN
		//g_pMeshEnemy->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		//for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		//{
		//	D3DXVECTOR3  vtx = *(D3DXVECTOR3*)pVtxBuff;

		//	if (vtx.x > pEnemy->vtxMax.x)
		//	{//XÌÅål
		//		pEnemy->vtxMax.x = vtx.x;
		//	}
		//	else if (vtx.x < pEnemy->vtxMin.x)
		//	{//XÌÅ¬l
		//		pEnemy->vtxMin.x = vtx.x;
		//	}

		//	if (vtx.z > pEnemy->vtxMax.z)
		//	{//ZÌÅål
		//		pEnemy->vtxMax.z = vtx.z;
		//	}
		//	else if (vtx.z < pEnemy->vtxMin.z)
		//	{//ZÌÅ¬l
		//		pEnemy->vtxMin.z = vtx.z;
		//	}

		//	pVtxBuff += dwSizeFVF;
		//}

		////}eAf[^ÖÌ|C^ðæ¾
		
	}

	SetEnemy(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), ENEMYTYPE_HELI);
	
	SetEnemy(D3DXVECTOR3(300.0f,0.0f,0.0f),ENEMYTYPE_TANK);
}

//==================================================================================================
//I¹
//==================================================================================================
void UninitEnemy(void)
{
	for (int nCntMesh = 0;nCntMesh < ENEMYTYPE_MAX;nCntMesh++)
	{
		if (g_pMeshEnemy[nCntMesh] != NULL)
		{//bV|C^Ìjü
			g_pMeshEnemy[nCntMesh]->Release();
			g_pMeshEnemy[nCntMesh] = NULL;
		}
	}

	for (int nCntMat = 0; nCntMat < ENEMYTYPE_MAX; nCntMat++)
	{
		if (g_pBuffMatEnemy[nCntMat] != NULL)
		{//¸_obt@|C^Ìjü
			g_pBuffMatEnemy[nCntMat]->Release();
			g_pBuffMatEnemy[nCntMat] = NULL;
		}
	}

	for (int nCntType = 0;nCntType < ENEMYTYPE_MAX;nCntType++)
	{
		for (int nCntTex = 0; nCntTex < NUM_TEX; nCntTex++)
		{
			if (g_apTextureEnemy[nCntType][nCntTex] != NULL)
			{//eNX`|C^Ìjü
				g_apTextureEnemy[nCntType][nCntTex]->Release();
				g_apTextureEnemy[nCntType][nCntTex] = NULL;
			}
		}
	}
}

//==================================================================================================
//XV
//==================================================================================================
void UpdateEnemy(void)
{

}

//==================================================================================================
//`æ
//==================================================================================================
void DrawEnemy(void)
{
	//foCX|C^Ýè
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//Ïé¾
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;			//»ÝÌ}eAÛ¶p
	D3DXMATERIAL *pMat;				//}eAf[^ÖÌ|C^

	//îñæ¾
	Enemy *pEnemy = GetEnemy();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse)
		{
			//[h}gbNXú»
			D3DXMatrixIdentity(&pEnemy->g_mtxWorld);

			//ü«ð½f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				pEnemy->rot.y, pEnemy->rot.x, pEnemy->rot.z);
			D3DXMatrixMultiply(&pEnemy->g_mtxWorld, &pEnemy->g_mtxWorld, &mtxRot);

			//Êuð½f
			D3DXMatrixTranslation(&mtxTrans,
				pEnemy->pos.x, pEnemy->pos.y, pEnemy->pos.z);
			D3DXMatrixMultiply(&pEnemy->g_mtxWorld, &pEnemy->g_mtxWorld, &mtxTrans);

			//[h}gbNXÝè
			pDevice->SetTransform(D3DTS_WORLD, &pEnemy->g_mtxWorld);

			//»ÝÌ}eAæ¾
			pDevice->GetMaterial(&matDef);

			//}eAf[^ÖÌ|C^ðæ¾
			pMat = (D3DXMATERIAL*)g_pBuffMatEnemy[pEnemy->type]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatEnemy[pEnemy->type]; nCntMat++)
			{
				//}eAÝè
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//eNX`Ýè
				pDevice->SetTexture(0, g_apTextureEnemy[pEnemy->type][nCntMat]);

				//fip[cj`æ
				g_pMeshEnemy[pEnemy->type]->DrawSubset(nCntMat);
			}

			//}eAðß·
			pDevice->SetMaterial(&matDef);
		}
	}
}

//==================================================================================================
//Ýè
//==================================================================================================
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	//îñæ¾
	Enemy *pEnemy = GetEnemy();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == false)
		{
			//vZpÏ
			int nNumVtx;			//¸_
			DWORD dwSizeFVF;		//¸_tH[}bgÌTCY
			BYTE *pVtxBuff;			//¸_obt@ÖÌ|C^

			//îñÝè
			pEnemy->bUse = true;
			pEnemy->pos = pos;
			pEnemy->type = type;

			//¸_Ìæ¾
			nNumVtx = g_pMeshEnemy[pEnemy->type]->GetNumVertices();

			//tH[}bgTCYüè
			dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshEnemy[pEnemy->type]->GetFVF());

			//¸_obt@ÌbN
			g_pMeshEnemy[pEnemy->type]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3  vtx = *(D3DXVECTOR3*)pVtxBuff;

				if (vtx.x > pEnemy->vtxMax.x)
				{//XÌÅål
					pEnemy->vtxMax.x = vtx.x;
				}
				else if (vtx.x < pEnemy->vtxMin.x)
				{//XÌÅ¬l
					pEnemy->vtxMin.x = vtx.x;
				}

				if (vtx.z > pEnemy->vtxMax.z)
				{//ZÌÅål
					pEnemy->vtxMax.z = vtx.z;
				}
				else if (vtx.z < pEnemy->vtxMin.z)
				{//ZÌÅ¬l
					pEnemy->vtxMin.z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;
			}

			pEnemy->vtxMax = pEnemy->pos + pEnemy->vtxMax;
			pEnemy->vtxMin = pEnemy->pos + pEnemy->vtxMin;

			//¸_obt@ÌAbN
			g_pMeshEnemy[pEnemy->type]->UnlockVertexBuffer();

			//for¶²¯é
			break;
		}
	}
}

//==================================================================================================
//|C^æ¾
//==================================================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}