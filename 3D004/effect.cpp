//==================================================================================================
//
//Effect.cpp
//Author:ûüRç
//
//==================================================================================================

#include "main.h"
#include "effect.h"
#include "player.h"

//}Nè`
#define MAX_EFFECT				(4096)										//Åå
#define LIFE_SPEED				(10)										//õ½Ì¸é¬x
#define EFFECT_TEX_FILE			"data\\TEXTURE\\effect\\effect000.png"		//eNX`t@C¼
#define ANIM_TIME				(1)											//Aj[Vðs¤px
#define EFFECT_WIDTH			(10)										//¡
#define EFFECT_HEIGHT			(40)										//³
#define MOVE_FACT				(0.96f)										//Ú®¸W

//O[oÏé¾
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;			//eNX`ÖÌ|C^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//¸_obt@ÖÌ|C^
Effect g_aEffect[MAX_EFFECT];						//GtFNgÌîñ

//vg^Cvé¾
void UpdateEffectPos(Effect *pEffect);
void UpdateEffectPolygon(Effect *pEffect,int nCntEffect);

//==================================================================================================
//ú»
//==================================================================================================
void InitEffect(void)
{
	//foCX|C^Ýè
	LPDIRECT3DDEVICE9 pDevice;

	//|C^é¾
	Effect *pEffect = GetEffect();

	//Ïé¾
	int nCntEffect;

	//foCXÌæ¾
	pDevice = GetDevice();

	//eNX`ÇÝÝ
	D3DXCreateTextureFromFile(pDevice,
		EFFECT_TEX_FILE,
		&g_pTextureEffect);

	//¸_obt@Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//¸_îñÌ|C^
	VERTEX_3D *pVtx;

	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++,pEffect++)
	{//SÄÌeÌú»
	    //¸_ÀWÌÝè
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);

		//norÌÝè
		pVtx[0].nor = { 0.0f,0.0f,-1.0f };
		pVtx[1].nor = { 0.0f,0.0f,-1.0f };
		pVtx[2].nor = { 0.0f,0.0f,-1.0f };
		pVtx[3].nor = { 0.0f,0.0f,-1.0f };

		//eNX`ÀW
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
		pEffect->bUse = false;					//eðgpµÄ¢È¢óÔÉ·é

		//¸_f[^Ì|C^ð4Âªißé
		pVtx += 4;
	}

	//¸_obt@ðAbN
	g_pVtxBuffEffect->Unlock();
}

//==================================================================================================
//I¹
//==================================================================================================
void UninitEffect(void)
{
	if (g_pTextureEffect != NULL)
	{//eNX`ÖÌ|C^jü
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	if (g_pVtxBuffEffect != NULL)
	{//¸_obt@ÖÌ|C^jü
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//==================================================================================================
//XV
//==================================================================================================
void UpdateEffect(void)
{
	//Ïé¾
	int nCntEffect;
	
	//|C^é¾
	Effect *pEffect = GetEffect();

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{//SÄÌeÌXV

		if (pEffect->bUse)
		{//gp³êÄ¢éóÔÈç

			//ÊuXV
			UpdateEffectPos(pEffect);

			//¼aÌXV
			pEffect->fRadius -= pEffect->fDecrease;

			//õ½JEg_E
			pEffect->nLife -= LIFE_SPEED / 2;

			if (pEffect->nLife <= 0 || pEffect->fRadius <= 0)
			{//õ½ªs«½ç
			 //gpµÄ¢È¢óÔÉ·é
				pEffect->bUse = false;
			}

			//|SXV
			UpdateEffectPolygon(pEffect, nCntEffect);
		}
	}
}

//==================================================================================================
//ÊuXV
//==================================================================================================
void UpdateEffectPos(Effect *pEffect)
{
	//Ú®Ê¸
	pEffect->move.x = pEffect->move.x * MOVE_FACT;
	pEffect->move.y = pEffect->move.y * MOVE_FACT;
	pEffect->move.z = pEffect->move.z * MOVE_FACT;

	//ÊuÌXV
	pEffect->pos.x += pEffect->move.x;
	pEffect->pos.y += pEffect->move.y;
	pEffect->pos.z += pEffect->move.z;
}

//==================================================================================================
//|SXV
//==================================================================================================
void UpdateEffectPolygon(Effect *pEffect,int nCntEffect)
{
	//¸_îñÌ|C^
	VERTEX_3D *pVtx;

	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	//¸_f[^Ì|C^ð4Âªißé
	pVtx += 4 * nCntEffect;

	//¸_ÀWÌÝè
	pVtx[0].pos = { -pEffect->fRadius,pEffect->fRadius, 0.0f };
	pVtx[1].pos = { pEffect->fRadius,pEffect->fRadius, 0.0f };
	pVtx[2].pos = { -pEffect->fRadius,-pEffect->fRadius, 0.0f };
	pVtx[3].pos = { pEffect->fRadius,-pEffect->fRadius, 0.0f };

	//¸_J[ÌÝè
	pVtx[0].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
	pVtx[1].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
	pVtx[2].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
	pVtx[3].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };

	//¸_obt@ðAbN
	g_pVtxBuffEffect->Unlock();
}

//==================================================================================================
//`æ
//==================================================================================================
void DrawEffect(void)
{
	//foCX|C^Ýè
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans, mtxView;

	//|C^é¾
	Effect *pEffect = GetEffect();

	//At@eXgÌLø»
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, GetAlphaThreshold());

	//ZeXgÌ³ø»
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if (pEffect->bUse)
		{
			//[h}gbNXú»
			D3DXMatrixIdentity(&pEffect->mtxWorld);

			//r[}gbNXæ¾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//|SðJÉü¯é
			D3DXMatrixInverse(&pEffect->mtxWorld, NULL, &mtxView);
			pEffect->mtxWorld._41 = 0.0f;
			pEffect->mtxWorld._42 = 0.0f;
			pEffect->mtxWorld._43 = 0.0f;

			//Êuð½f
			D3DXMatrixTranslation(&mtxTrans,
				pEffect->pos.x, pEffect->pos.y, pEffect->pos.z);
			D3DXMatrixMultiply(&pEffect->mtxWorld, &pEffect->mtxWorld, &mtxTrans);

			//[h}gbNXÝè
			pDevice->SetTransform(D3DTS_WORLD, &pEffect->mtxWorld);

			//¸_obt@ðf[^Xg[ÉÝè
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//¸_tH[}bgÌÝè
			pDevice->SetFVF(FVF_VERTEX_3D);

			//eNX`Ýè
			pDevice->SetTexture(0, g_pTextureEffect);

			if (pEffect->bAdd == true)
			{
				//¿ufBOðÁZ¬ÉÝè
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}

			//|S`æ
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEffect, 2);

			if (pEffect->bAdd == true)
			{
				//¿ufBOð³Éß·
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			}
		}
	}

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
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col,float fRadius, int nLife,bool bAdd,float fDecrease)
{
	//Ïé¾
	int nCntEffect;

	//¸_îñÌ|C^
	VERTEX_3D *pVtx;

	//eÖÌ|C^
	Effect *pEffect = GetEffect();

	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++,pEffect++)
	{//SÄÌeð`FbN·é
		if (pEffect->bUse == false)
		{//gÁÄ¢È¢óÔÈç

			//ÊuÌÝè
			pEffect->pos = pos;

			//ÊuÌÝè
			pEffect->move = move;

			//FÌÝè
			pEffect->col = col;

			//¼aÌÝè
			pEffect->fRadius = fRadius;

			//¸­ÊÝè
			pEffect->fDecrease = fDecrease;

			//õ½ÌÝè
			pEffect->nLife = nLife;

			//¸_ÀWÌÝè
			pVtx[0].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
			pVtx[1].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
			pVtx[2].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };
			pVtx[3].col = D3DXCOLOR{ pEffect->col.r,pEffect->col.g,pEffect->col.b,pEffect->col.a };

			//õ½ÌÝè
			pEffect->nLife = nLife;

			//gpµÄ¢éÝè
			pEffect->bUse = true;

			//gpµÄ¢éÝè
			pEffect->bAdd = bAdd;

			//for¶ð²¯é
			break;
		}

		//¸_f[^Ì|C^ð4Âªißé
		pVtx += 4;
	}

	//¸_obt@ðAbN
	g_pVtxBuffEffect->Unlock();
}

//==================================================================================================
//|C^æ¾
//==================================================================================================
Effect *GetEffect(void)
{
	return &g_aEffect[0];
}