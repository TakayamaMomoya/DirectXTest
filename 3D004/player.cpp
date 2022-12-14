//==================================================================================================
//
//player.cpp
//Author:ûüRç
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

//}Nè`
#define MOVE_SPEED					(0.7f)									//Ú®¬x
#define NUM_TEX						(8)										//eNX`
#define ROLL_FACT					(0.06f)									//ñ]¸W
#define ROLL_SPEED					(0.04f)									//ñ]¬x
#define BULLET_SPEED				(10.0f)									//eÌXs[h
#define MOVE_FACT					(0.9f)									//Ú®Ê¸W
#define MAX_PART					(24)									//p[cÌÅå
#define MAX_STRING					(256)									//ÅåÌ¶
#define MOTION_FILE					"data\\motion_AC.txt"					//[Vt@C¼
#define BOOST_SPEED					(20)									//u[XgÌ¬x
#define DODGE_COST					(80.0f)									//ñðÌu[X^[RXg

//O[oÏé¾
LPDIRECT3DTEXTURE9 g_apTexturePlayer[MAX_PART][NUM_TEX] = {};			//eNX`ÖÌ|C^
int g_nIdxShadowPlayer;										//eÌCfbNX
Player g_player;											//\¢ÌÌîñ
PlayerPart g_aPlayerPart[MAX_PART];							//\¢ÌÌîñ
int g_nNumPlayerParts;										//p[c
char g_acFilenamePlayer[MAX_PART][MAX_STRING];				//p[cÌt@C¼

//vg^Cvé¾
void ControlPlayer(void);
void UpdatePosPlayer(void);
void LimitMovePlayer(void);
void LoadMotion(FILE *pFile);

//==================================================================================================
//ú»
//==================================================================================================
void InitPlayer(void)
{
	//foCX|C^Ýè
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;				//}eAf[^ÖÌ|C^

	//Ïú»
	g_player.pos = { 0.0f,0.0f,0.0f };
	g_player.move = { 0.0f,0.0f,0.0f };
	g_player.rot = { 0.0f,0.0f,0.0f };
	g_player.fBoost = INITIAL_MAX_BOOST;
	g_player.fBoostMax = INITIAL_MAX_BOOST;
	g_player.nLife = PLAYER_LIFE;
	g_nIdxShadowPlayer = 0;
	g_nNumPlayerParts = 0;

	//îñæ¾
	PlayerPart *pPlayerPart = GetPlayerPart();

	//t@C©çâèÆIððÇÝÞ
	FILE *pFile = fopen(MOTION_FILE, "r");

	if (pFile != NULL)
	{//t@CªJ¯½ê
	    //t@CÇÝÝ
		LoadMotion(pFile);
	}
	else
	{
	}

	for (int nCntPart = 0;nCntPart < g_nNumPlayerParts;nCntPart++)
	{//p[cÇÝÝ
		//Ïú»
		pPlayerPart[nCntPart].dwNumMat = 0;

		//Xt@CÇÝÝ
		D3DXLoadMeshFromX(&g_acFilenamePlayer[nCntPart][0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&pPlayerPart[nCntPart].pBuffMat,
			NULL,
			&pPlayerPart[nCntPart].dwNumMat,
			&pPlayerPart[nCntPart].pMesh);

		//}eAf[^ÖÌ|C^ðæ¾
		pMat = (D3DXMATERIAL*)pPlayerPart[nCntPart].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)pPlayerPart[nCntPart].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//eNX`ª¶Ý·é
			    //eNX`ÇÝÝ
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

	//eCfbNXæ¾
	g_nIdxShadowPlayer = SetShadow(40.0f);
}

//==================================================================================================
//I¹
//==================================================================================================
void UninitPlayer(void)
{
	//Ïé¾
	int nCntPlayer;

	//îñæ¾
	PlayerPart *pPlayerPart = GetPlayerPart();

	for (nCntPlayer = 0;nCntPlayer < g_nNumPlayerParts;nCntPlayer++)
	{
		if (pPlayerPart->pMesh != NULL)
		{//bV|C^Ìjü
			pPlayerPart->pMesh->Release();
			pPlayerPart->pMesh = NULL;
		}
	}
	
	for (nCntPlayer = 0; nCntPlayer < g_nNumPlayerParts; nCntPlayer++)
	{
		if (pPlayerPart->pBuffMat != NULL)
		{//¸_obt@|C^Ìjü
			pPlayerPart->pBuffMat->Release();
			pPlayerPart->pBuffMat = NULL;
		}
	}

	for (int nCntTex = 0;nCntTex < NUM_TEX * MAX_PART;nCntTex++)
	{
		if (g_apTexturePlayer[nCntTex / NUM_TEX][nCntTex % NUM_TEX] != NULL)
		{//eNX`|C^Ìjü
			g_apTexturePlayer[nCntTex / NUM_TEX][nCntTex % NUM_TEX]->Release();
			g_apTexturePlayer[nCntTex / NUM_TEX][nCntTex % NUM_TEX] = NULL;
		}
	}
}

//==================================================================================================
//XV
//==================================================================================================
void UpdatePlayer(void)
{
	//îñæ¾
	Camera *pCamera = GetCamera();

	//ì
	ControlPlayer();

	//ÊuXV
	UpdatePosPlayer();

	//Ú®§À
	LimitMovePlayer();

	//ñ]§ä
	LimitRot(&g_player.rot);

	//fobOp,Ìñ]
	g_aPlayerPart[1].rot.y += 0.3f;
	LimitRot(&g_aPlayerPart[1].rot);

	g_aPlayerPart[0].pos = g_player.pos;

	//eÌÊuÝè
	SetPositionShadow(g_nIdxShadowPlayer, g_player.pos);
}

//==================================================================================================
//vC[ì
//==================================================================================================
void ControlPlayer(void)
{
	//îñæ¾
	Camera *pCamera = GetCamera();

	//Ú®======================================================
	if (GetKeyboardRepeat(DIK_UP) == true)
	{//OÚ®
		g_player.move.x += sinf(g_player.rot.y + D3DX_PI) * MOVE_SPEED;
		g_player.move.z += cosf(g_player.rot.y + D3DX_PI) * MOVE_SPEED;
	}
	if (GetKeyboardRepeat(DIK_DOWN) == true)
	{//ãÚ®
		g_player.move.x += sinf(g_player.rot.y) * MOVE_SPEED;
		g_player.move.z += cosf(g_player.rot.y) * MOVE_SPEED;
	}
	if (GetKeyboardRepeat(DIK_LEFT) == true)
	{//¶Ú®
		g_player.move.x += sinf(g_player.rot.y + D3DX_PI * 0.5f) * MOVE_SPEED;
		g_player.move.z += cosf(g_player.rot.y + D3DX_PI * 0.5f) * MOVE_SPEED;
	}
	if (GetKeyboardRepeat(DIK_RIGHT) == true)
	{//EÚ®
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

	//U======================================================
	if (GetKeyboardTrigger(DIK_SPACE) == true || GetGamePadTrigger(PADBUTTONS_RB,0) == true)
	{//e­Ë
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

	//Rg[[=============================================
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
	{//u[X^[gp
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
//ÊuXV
//==================================================================================================
void UpdatePosPlayer(void)
{
	//Ïé¾
	D3DXVECTOR3 move = g_player.move;

	//ÊuXV
	g_player.pos.x += g_player.move.x;
	g_player.pos.z += g_player.move.z;

	//Ú®Ê¸
	g_player.move.x = g_player.move.x * MOVE_FACT;
	g_player.move.z = g_player.move.z * MOVE_FACT;
}

//==================================================================================================
//Ú®§À
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
//`æ
//==================================================================================================
void DrawPlayer(void)
{
	//foCX|C^Ýè
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//Ïé¾
	D3DXMATRIX mtxRot, mtxTrans,mtxRot2;
	D3DMATERIAL9 matDef;			//»ÝÌ}eAÛ¶p
	D3DXMATERIAL *pMat;				//}eAf[^ÖÌ|C^
	D3DXVECTOR3 posPart,rotPart;

	//îñæ¾
	PlayerPart *pPlayerPart = GetPlayerPart();
	
	for (int nCntPlayer = 0; nCntPlayer < g_nNumPlayerParts; nCntPlayer++)
	{
		//[h}gbNXú»
		D3DXMatrixIdentity(&pPlayerPart[nCntPlayer].mtxWorld);

		if (pPlayerPart[nCntPlayer].nIdxParent != -1)
		{//eÌ}gbNXðp®
		}
		else
		{//SÄÌep[c
			posPart = g_player.pos + pPlayerPart[nCntPlayer].pos;
			rotPart = g_player.rot + pPlayerPart[nCntPlayer].rot;
		}

		//ü«ð½f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			pPlayerPart[nCntPlayer].rot.y, pPlayerPart[nCntPlayer].rot.x, pPlayerPart[nCntPlayer].rot.z);
		D3DXMatrixMultiply(&pPlayerPart[nCntPlayer].mtxWorld, &pPlayerPart[nCntPlayer].mtxWorld, &mtxRot);

		//Êuð½f
		D3DXMatrixTranslation(&mtxTrans,
			pPlayerPart[nCntPlayer].pos.x, pPlayerPart[nCntPlayer].pos.y, pPlayerPart[nCntPlayer].pos.z);
		D3DXMatrixMultiply(&pPlayerPart[nCntPlayer].mtxWorld, &pPlayerPart[nCntPlayer].mtxWorld, &mtxTrans);

		//[h}gbNXÝè
		pDevice->SetTransform(D3DTS_WORLD, &pPlayerPart[nCntPlayer].mtxWorld);

		//»ÝÌ}eAæ¾
		pDevice->GetMaterial(&matDef);

		//}eAf[^ÖÌ|C^ðæ¾
		pMat = (D3DXMATERIAL*)pPlayerPart[nCntPlayer].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)pPlayerPart[nCntPlayer].dwNumMat; nCntMat++)
		{
			//}eAÝè
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//FÝè
			//pMat[nCntMat].MatD3D.Diffuse = {0.0f,0.0f,0.0f,1.0f};

			//eNX`Ýè
			pDevice->SetTexture(0, g_apTexturePlayer[nCntPlayer][nCntMat]);

			//fip[cj`æ
			pPlayerPart[nCntPlayer].pMesh->DrawSubset(nCntMat);
		}

		//}eAðß·
		pDevice->SetMaterial(&matDef);
	}
}

//==================================================================================================
//vC[óÔ`æ(fobO)
//==================================================================================================
void DrawPlayerState(LPD3DXFONT pFont)
{
	//Ïé¾
	RECT rect = { 20,390,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	float fSpeed = sqrtf(g_player.move.x * g_player.move.x + g_player.move.z * g_player.move.z);

	//¶ñÉãü
	sprintf(&aStr[0], "vC[ÌÊu[%.2f,%.2f,%.2f]\nvC[Ìü«[%.2f,%.2f,%.2f]\nu[XgcÊ[%.2f]  vC[Ì¬x[%.2f]", 
		g_player.pos.x, g_player.pos.y, g_player.pos.z,g_player.rot.x, g_player.rot.y, g_player.rot.z,g_player.fBoost, fSpeed);

	//eLXg`æ
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//vC[ì`æ(fobO)
//==================================================================================================
void DrawControlPlayer(LPD3DXFONT pFont)
{
	//Ïé¾
	RECT rect = { 20,230,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//¶ñÉãü
	sprintf(&aStr[0], "vC[½Ú®[îóL[]\ne­Ë[SPACE]\nñ][L,RSHIFT]");

	//eLXg`æ
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//p[cóÔ`æ(fobO)
//==================================================================================================
void DrawPPartState(LPD3DXFONT pFont)
{
	char aStr[256];

	for (int nCntPart = 0;nCntPart < g_nNumPlayerParts;nCntPart++)
	{
		//Ïé¾
		RECT rect = { 1000,20 + 20 * nCntPart,SCREEN_WIDTH,SCREEN_HEIGHT };

		//¶ñÉãü
		sprintf(&aStr[0], "%dÔp[cÌÊu[%.2f,%.2f,%.2f]",
			nCntPart,g_aPlayerPart[nCntPart].mtxWorld._41, g_aPlayerPart[nCntPart].mtxWorld._42, g_aPlayerPart[nCntPart].mtxWorld._43);

		//eLXg`æ
		pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}

//==================================================================================================
//t@CÇÝÝ
//==================================================================================================
void LoadMotion(FILE *pFile)
{
	//îñæ¾
	PlayerPart *pPlayerPart = GetPlayerPart();

	//Ïé¾
	char cTemp[MAX_STRING];

	while (1)
	{
		//¶ÇÝÝ
		fscanf(pFile, "%s", &cTemp[0]);

		//t@C¼ÇÝÝ=========================================
		if (strcmp(cTemp, "NUM_MODEL") == 0)
		{//fÇÝÝ

		    //"="ÇÝÝ
			fscanf(pFile, "%s", &cTemp[0]);

			//fÇÝÝ
			fscanf(pFile, "%d", &g_nNumPlayerParts);

			for (int nCntFile = 0; nCntFile < g_nNumPlayerParts;)
			{//t@C¼ÇÝÝ

				fscanf(pFile, "%s", &cTemp[0]);

				if (strcmp(cTemp, "MODEL_FILENAME") == 0)
				{//t@C¼ÇÝÝ
					fscanf(pFile, "%s", &cTemp[0]);

					fscanf(pFile, "%s", &g_acFilenamePlayer[nCntFile][0]);

					nCntFile++;
				}
			}
		}
		//===========================================================

		//LN^[Ýè===========================================
		if (strcmp(cTemp, "CHARACTERSET") == 0)
		{//LN^[X^[g
			while (strcmp(cTemp, "END_CHARACTERSET") != 0)
			{//IíèÜÅLN^[Ýè
				fscanf(pFile, "%s", &cTemp[0]);

				if (strcmp(cTemp, "PARTSSET") == 0)
				{//p[cX^[g
					while (strcmp(cTemp, "END_PARTSSET") != 0)
					{//IíèÜÅp[cÝè
						fscanf(pFile, "%s", &cTemp[0]);

						if (strcmp(cTemp, "INDEX") == 0)
						{//ÔÇÝÝ
							fscanf(pFile, "%s", &cTemp[0]);

							fscanf(pFile, "%d", &pPlayerPart->nIdx);
						}

						if (strcmp(cTemp, "PARENT") == 0)
						{//eÔÇÝÝ
							fscanf(pFile, "%s", &cTemp[0]);

							fscanf(pFile, "%d", &pPlayerPart->nIdxParent);
						}

						if (strcmp(cTemp, "POS") == 0)
						{//ÊuÇÝÝ
							fscanf(pFile, "%s", &cTemp[0]);

							for (int nCntPos = 0; nCntPos < 3; nCntPos++)
							{
								fscanf(pFile, "%f", &pPlayerPart->pos[nCntPos]);
							}
						}

						if (strcmp(cTemp, "ROT") == 0)
						{//ü«ÇÝÝ
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
	}//whileÂ¶
}

//==================================================================================================
//îñæ¾
//==================================================================================================
Player *GetPlayer(void)
{
	return &g_player;
}

//==================================================================================================
//îñæ¾
//==================================================================================================
PlayerPart *GetPlayerPart(void)
{
	return &g_aPlayerPart[0];
}