//==================================================================================================
//
//explosion.cpp
//Author:ûüRç
//
//==================================================================================================

#include "main.h"
#include "explosion.h"
#include "input.h"
#include "shadow.h"
#include <stdio.h>

//}Nè`
#define EXPLOSION_TEX_FILE		"data\\TEXTURE\\EFFECT\\explosion000.png"			//eNX`t@C¼
#define EXPLOSION_WIDTH			(10)											//
#define EXPLOSION_HEIGHT		(10)											//³
#define MAX_EXPLOSION			(256)											//r{[hÌÅå
#define NORMAL_LIFE				(60)											//Êíõ½
#define ANIM_TIME				(10)												//Aj[VÌ¬x

//O[oÏé¾
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;									//eNX`ÖÌ|C^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;								//¸_obt@ÖÌ|C^
Explosion g_aExplosion[MAX_EXPLOSION];											//\¢ÌÌîñ
int g_nNumExplosion;															//eÌ

//vg^Cvé¾
void UpdateExplosionPolygon(int nCntExplosion, Explosion *pExplosion);

//==================================================================================================
//ú»
//==================================================================================================
void InitExplosion(void)
{
	//Ïé¾
	g_nNumExplosion = 0;

	//foCX|C^Ýè
	LPDIRECT3DDEVICE9 pDevice;

	//foCXÌæ¾
	pDevice = GetDevice();

	//eNX`ÇÝÝ
	D3DXCreateTextureFromFile(pDevice,
		EXPLOSION_TEX_FILE,
		&g_pTextureExplosion);

	//¸_obt@Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//¸_îñÌ|C^
	VERTEX_3D *pVtx;

	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	//îñæ¾
	Explosion *pExplosion = GetExplosion();

	for (int nCntExplosion = 0;nCntExplosion < MAX_EXPLOSION;nCntExplosion++, pExplosion++)
	{
		//Ïú»
		pExplosion->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pExplosion->bUse = false;
		pExplosion->nCounterAnim = 0;
		pExplosion->nTexU = 0;

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
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

		pVtx += 4;
	}

	//¸_obt@ðAbN
	g_pVtxBuffExplosion->Unlock();

}

//==================================================================================================
//I¹
//==================================================================================================
void UninitExplosion(void)
{
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	if (g_pVtxBuffExplosion != NULL)
	{//¸_obt@|C^Ìjü
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//==================================================================================================
//XV
//==================================================================================================
void UpdateExplosion(void)
{
	//îñæ¾
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
//|SXV
//==================================================================================================
void UpdateExplosionPolygon(int nCntExplosion, Explosion *pExplosion)
{
	//¸_îñÌ|C^
	VERTEX_3D *pVtx;

	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	//|C^ðißé
	pVtx += 4 * nCntExplosion;

	if (pExplosion->nTexU >= 8)
	{
		DisableExplosion(pExplosion);
	}

	pExplosion->nCounterAnim++;

	if (pExplosion->nCounterAnim % ANIM_TIME == 0)
	{//Aj[VJE^ªêèÌlÉBµ½ç
	 //p^[NODÌXV
		pExplosion->nTexU++;

		//eNX`ÀWÌXV
		pVtx[0].tex = { 0.125f * pExplosion->nTexU,0.0f };
		pVtx[1].tex = { 0.125f + 0.125f * pExplosion->nTexU,0.0f };
		pVtx[2].tex = { 0.125f * pExplosion->nTexU,1.0f };
		pVtx[3].tex = { 0.125f + 0.125f * pExplosion->nTexU,1.0f };
	}

	//¸_obt@ðAbN
	g_pVtxBuffExplosion->Unlock();
}

//==================================================================================================
//`æ
//==================================================================================================
void DrawExplosion(void)
{
	//foCX|C^Ýè
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans,mtxView;

	//îñæ¾
	Explosion *pExplosion = GetExplosion();

	//CeBOÌ³ø»
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//At@eXgÌLø»
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, GetAlphaThreshold());

	//ZeXgÌ³ø»
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse)
		{
			//[h}gbNXú»
			D3DXMatrixIdentity(&pExplosion->mtxWorld);

			//r[}gbNXæ¾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//|SðJÉü¯é
			D3DXMatrixInverse(&pExplosion->mtxWorld, NULL, &mtxView);
			pExplosion->mtxWorld._41 = 0.0f;
			pExplosion->mtxWorld._42 = 0.0f;
			pExplosion->mtxWorld._43 = 0.0f;

			//Êuð½f
			D3DXMatrixTranslation(&mtxTrans,
				pExplosion->pos.x, pExplosion->pos.y, pExplosion->pos.z);
			D3DXMatrixMultiply(&pExplosion->mtxWorld, &pExplosion->mtxWorld, &mtxTrans);

			//[h}gbNXÝè
			pDevice->SetTransform(D3DTS_WORLD, &pExplosion->mtxWorld);

			//¸_obt@ðf[^Xg[ÉÝè
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			//¸_tH[}bgÌÝè
			pDevice->SetFVF(FVF_VERTEX_3D);

			//eNX`Ýè
			pDevice->SetTexture(0, g_pTextureExplosion);

			//|S`æ
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntExplosion, 2);
		}
	}

	//CeBOÌLø»
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//ZeXgðLøÉ·é
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//At@eXgÌ³ø»
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==================================================================================================
//Ýè
//==================================================================================================
void SetExplosion(D3DXVECTOR3 pos)
{
	//¸_îñÌ|C^
	VERTEX_3D *pVtx;

	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	//îñæ¾
	Explosion *pExplosion = GetExplosion();

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse == false)
		{
			//ÏÝè
			pExplosion->pos = pos;
			pExplosion->bUse = true;
			pExplosion->nCounterAnim = 0;
			pExplosion->nTexU = 0;

			//¸_ÀWÌÝè
			pVtx[0].pos = D3DXVECTOR3(-EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-EXPLOSION_WIDTH, -EXPLOSION_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(EXPLOSION_WIDTH, -EXPLOSION_HEIGHT, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

			//eã¸
			g_nNumExplosion++;

			break;
		}

		pVtx += 4;
	}

	//¸_obt@ðAbN
	g_pVtxBuffExplosion->Unlock();
}

//==================================================================================================
//îñæ¾
//==================================================================================================
Explosion *GetExplosion(void)
{
	return &g_aExplosion[0];
}

//==================================================================================================
//e³ø»
//==================================================================================================
void DisableExplosion(Explosion *pExplosion)
{
	pExplosion->bUse = false;
	g_nNumExplosion--;
}

//==================================================================================================
//fobO\¦
//==================================================================================================
void DrawExplosionState(LPD3DXFONT pFont)
{
	//Ïé¾
	RECT rect = { 250,40,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//¶ñÉãü
	sprintf(&aStr[0], "­Ì[%d]",g_nNumExplosion);

	//eLXg`æ
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}