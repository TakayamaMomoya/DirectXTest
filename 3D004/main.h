//==================================================================================================
//
//main.h
//Author:ûüRç
//
//==================================================================================================

#ifndef _MAIN_H_
#define _MAIN_H_
#include <windows.h>
#include"d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)						//rhÌxÎp}N
#include "dinput.h"
#include "xaudio2.h"

//vg^Cvé¾
LPDIRECT3DDEVICE9 GetDevice(void);

//Cu
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")

//æÊ([h)ÌÝè
typedef enum
{
	MODE_TITLE = 0,						//^CgæÊ
	MODE_TUTORIAL,						//`[gAæÊ
	MODE_MENU,							//j[æÊ
	MODE_GAME,							//Q[æÊ
	MODE_RESULT,						//ÊæÊ
	MODE_RANKING,						//LOæÊ
	MODE_MAX
}MODE;

//}Nè`
#define SCREEN_WIDTH			(1280)															//EBhEÌ
#define SCREEN_HEIGHT			(720)															//EBhEÌ³
#define FVF_VERTEX_2D			(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)					//¸_tH[}bgÝè
#define FVF_VERTEX_3D			(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//¸_tH[}bgÝè
#define CLASS_NAME				"WindowClass"													//EBhENXÌ¼O
#define GRAVITY					(0.98f)															//dÍÁ¬x
#define NUM_STG					(3)																//Xe[WÌ
	
//¸_îñQDÌ\¢Ìðè`
typedef struct
{
	D3DXVECTOR3 pos;			//¸_ÀW
	float rhw;					//ÀWÏ·pWiPDOÅÅèj
	D3DCOLOR col;				//¸_J[
	D3DXVECTOR2 tex;			//eNX`ÀW
}VERTEX_2D;

//¸_îñ[RD]Ì\¢Ì
typedef struct
{
	D3DXVECTOR3 pos;			//¸_ÀW
	D3DXVECTOR3 nor;			//@üxNg
	D3DCOLOR col;				//¸_J[
	D3DXVECTOR2 tex;			//eNX`ÀW
}VERTEX_3D;

//vg^Cvé¾
void SetMode(MODE mode);
void LimitRot(D3DXVECTOR3 *rot);
DWORD GetAlphaThreshold(void);
bool CrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 PrVtx, D3DXVECTOR3 ScVtx);
bool SqrCrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax);
void WallCrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 *pos, D3DXVECTOR3 *move, D3DXVECTOR3 PrVtx, D3DXVECTOR3 ScVtx,float width);
#endif