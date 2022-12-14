//==================================================================================================
//
//main.cpp
//Author:ûüRç
//
//==================================================================================================

#include "main.h"
#include "input.h"
#include <stdio.h>
#include <time.h>
#include "Polygon.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"
#include "debugProc.h"
#include "meshfield.h"
#include "meshWall.h"
#include "meshcylinder.h"
#include "meshdome.h"
#include "remainlife.h"
#include "enemy.h"

//}Nè`
#define WINDOW_NAME				"3D"				//EBhEÌ¼O(LvV)

#define ID_TIMER
#define TIMER_INTERVAL

#define INITIAL_ALPHA			(100)				//úÌAt@eXgµ«¢l

//O[oÏ
LPDIRECT3D9 g_pD3D = NULL;						//directRDIuWFNgÖÌ|C^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//directRDfoCXÖÌ|C^
LPD3DXFONT g_ppFont = NULL;						//tHgÖÌ|C^
MODE g_mode = MODE_TITLE;						//[h
int g_nCountFPS;								//FPSJE^
bool g_bDebug = false;							//fobO\¦ÌON/OFF
DWORD g_dwThresholdAlpha;						//At@lÌµ«¢l
bool g_bWire = false;							//C[t[\¦©Ç¤©

//vg^Cvé¾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

void Uninit(void);
void Update(void);
void Draw(void);
void ControlAlphaThreshold(void);
void DebugControl(void);

void DrawDebug(void);
void DebugLight(void);
void DebugMouse(void);
void DebugClick(void);
void DebugCurrentLight(void);
void DrawAlphaThreshold(void);
void DrawDebugPad(void);

//==================================================================================================
//CÖ
//==================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	//Ïé¾
	DWORD dwCurrentTime;				//»Ý
	DWORD dwExecLastTime;				//ÅãÉµ½
	DWORD dwFrameCount;					//t[JEg
	DWORD dwFPSLastTime;				//ÅãÉFPSðvªµ½Ô

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//tHg|C^EFPSJE^Ìú»
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION),
	};

	HWND hWnd;
	MSG msg;

	//EBhENXÌo^
	RegisterClassEx(&wcex);

	//NCAgÌæðEBhETCYÉí¹é
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//EBhEð¶¬
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//ú»
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//ú»É¸sµ½ê
		return -1;
	}

	//ªð\ðÝè
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	//EBhEÌ\¦
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//bZ[W[v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//WindowsÌ
			if (msg.message == WM_QUIT)
			{//WMQQUITbZ[Wðó¯æÁ½ç[vð²¯é
				break;
			}
			else
			{
				//bZ[WÌÝè
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DeirectXÌ

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5boß
				//FPSvª
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				//FPSðªèµ½ÔðÛ¶·é
				dwFPSLastTime = dwCurrentTime;

				//t[JEgÌNA
				dwFrameCount = 0;
			}


			//»ÝÌæ¾
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60ªÌ1boß
				//JnÌðvZ
				dwExecLastTime = dwCurrentTime;

				//XV
				Update();

				//`æ
				Draw();

				//FPSJE^oß
				dwFrameCount++;
			}
		}
	}

	//I¹
	Uninit();

	//EBhENXÌo^ðð
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//==================================================================================================
//EBhEvV[W
//==================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
		//EBhEjübZ[Wðó¯æÁ½ê
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CLOSE:

		// }EXJ[\Ì\¦
		//ShowCursor(TRUE);
		
		//mFbZ[W
		nID = MessageBox(hWnd, "I¹µÜ·©H", "I¹bZ[W", MB_YESNO);

		if (nID == IDYES)
		{//CGXÌê
		 //EBhEjü
			DestroyWindow(hWnd);
		}
		else
		{
			// }EXJ[\Ì\¦
			//ShowCursor(FALSE);
			return 0;
		}

	case WM_KEYDOWN:
		switch (wParam)
		{
			//[ESC]L[ª³ê½
		case VK_ESCAPE:

			// }EXJ[\Ì\¦
			//ShowCursor(TRUE);

			//mFbZ[W
			nID = MessageBox(hWnd, "I¹µÜ·©H", "I¹bZ[W", MB_YESNO);

			if (nID == IDYES)
			{//CGXÌê
			 //EBhEjü
				DestroyWindow(hWnd);
			}
			else
			{
				break;
			}
		}

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//==================================================================================================
//ú»
//==================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//Ïú»
	g_dwThresholdAlpha = INITIAL_ALPHA;

	D3DDISPLAYMODE d3ddm;								//fBXvC[hÌÝè
	D3DPRESENT_PARAMETERS d3dpp;						//fBXvC[hÌÝè

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{//Direct3DIuWFNg¶¬
		return E_FAIL;
	}
	
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{//»ÝÌfBXvC[hðæ¾
		return E_FAIL;
	}

	//foCXÌv[e[Vp[^[ÌÝè
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//p[^[Ì[NA

	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//Q[æÊÌ
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//³
	d3dpp.BackBufferFormat = d3ddm.Format;							//`®
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//fMÉ¯ú
	d3dpp.EnableAutoDepthStencil = TRUE;							//fuXÆXeVobt@ðì¬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//fuXobt@ð16bitÅg¤
	d3dpp.Windowed = bWindow;										//EBhE[h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//tbV[g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//C^[o

	//Direct3DfoCXÌ¶¬
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}

		}
	}

	//_[Xe[gÌÝè
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//TvXe[gÌÝè
	g_pD3DDevice->SetSamplerState(0,
		D3DSAMP_MINFILTER,
		D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0,
		D3DSAMP_MAGFILTER,
		D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0,
		D3DSAMP_ADDRESSU,
		D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0,
		D3DSAMP_ADDRESSV,
		D3DTADDRESS_WRAP);

	//eNX`Xe[WXe[gÌÝè
	g_pD3DDevice->SetTextureStageState(0,
		D3DTSS_ALPHAOP,
		D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0,
		D3DTSS_ALPHAARG1,
		D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0,
		D3DTSS_ALPHAARG2,
		D3DTA_CURRENT);

	//fobO\¦ÌtHg¶¬
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH,"Terminal", &g_ppFont);

	//foCXú»
	InitDevice(hInstance, hWnd);

	//|Sú»
	InitPolygon();

	//bVtB[hú»
	InitMeshField();

	//bVEH[ú»
	InitMeshWall();

	//bVV_[ú»
	InitMeshCylinder();

	//bVh[ú»
	InitMeshDome();

	//Jú»
	InitCamera();

	//Cgú»
	InitLight();

	//eú»
	InitShadow();

	//fú»
	InitPlayer();

	//Çú»
	InitWall();

	//r{[hú»
	InitBillBoard();

	//eú»
	InitBullet();

	//­ú»
	InitExplosion();

	//GtFNgú»
	InitEffect();

	//p[eBNú»
	InitParticle();

	//fobO\¦vV[Wú»
	InitDebugProc();

	//ÌÍ\¦ú»
	InitRemainLife();

	//Gú»
	InitEnemy();

	//V[hlÌÝè
	srand((unsigned int)time(0));

	return S_OK;
}

//==================================================================================================
//I¹
//==================================================================================================
void Uninit(void)
{
	//foCXI¹
	UninitDevice();

	//|SI¹
	UninitPolygon();

	//bVtB[hI¹
	UninitMeshField();

	//bVEH[I¹
	UninitMeshWall();

	//bVV_[I¹
	UninitMeshCylinder();

	//bVh[I¹
	UninitMeshDome();

	//JI¹
	UninitCamera();

	//CgI¹
	UninitLight();

	//fI¹
	UninitPlayer();

	//eI¹
	UninitShadow();

	//ÇI¹
	UninitWall();

	//r{[hI¹
	UninitBillBoard();

	//eI¹
	UninitBullet();

	//GtFNgI¹
	UninitEffect();

	//­I¹
	UninitExplosion();

	//p[eBNI¹
	UninitParticle();

	//fobO\¦vV[WI¹
	UninitDebugProc();

	//ÌÍ\¦I¹
	UninitRemainLife();

	//GI¹
	UninitEnemy();

	if (g_ppFont != NULL)
	{//tHgÌjü
		g_ppFont->Release();
		g_ppFont = NULL;
	}

	if (g_pD3DDevice != NULL)
	{//Direct3DfoCXjü
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{//Direct3DIuWFNgÌjü
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	if (g_nCountFPS != NULL)
	{//FPSJE^Ìjü
		g_nCountFPS = NULL;
	}
}

//==================================================================================================
//XV
//==================================================================================================
void Update(void)
{
	//fobO
//#ifdef _DEBUG
	DebugControl();
//#endif

	//foCXXV
	UpdateDevice();

	//JXV
	UpdateCamera();

	//fXV
	UpdatePlayer();

	//CgXV
	UpdateLight();

	//r{[hXV
	UpdateBillBoard();

	//eXV
	UpdateBullet();

	//­XV
	UpdateExplosion();

	//GtFNgXV
	UpdateEffect();

	//p[eBNXV
	UpdateParticle();

	//ÌÍ\¦XV
	UpdateRemainLife();

	//GXV
	UpdateEnemy();
}

//==================================================================================================
//fobOì
//==================================================================================================
void DebugControl(void)
{
	//At@eXgì======================================
	if (GetKeyboardRepeat(DIK_1) == true)
	{
		if (g_dwThresholdAlpha > 0)
		{
			g_dwThresholdAlpha--;
		}
	}
	if (GetKeyboardRepeat(DIK_2) == true)
	{
		if (g_dwThresholdAlpha < 255)
		{
			g_dwThresholdAlpha++;
		}
	}

	//C[t[======================================
	if (GetKeyboardTrigger(DIK_F9))
	{
		g_bWire = g_bWire ? false : true;
	}
}

//==================================================================================================
//`æ
//==================================================================================================
void Draw(void)
{
	//æÊNA
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	if (g_bWire)
	{//C[t[
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	//`æJn
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//`æ

		//JÝè
		SetCamera();

		//|S`æ
		//DrawPolygon();

		//bVtB[h`æ
		DrawMeshField();

		//bVEH[`æ
		DrawMeshWall();

		//G`æ
		DrawEnemy();

		//­`æ
		DrawExplosion();

		//e`æ
		DrawBullet();

		//bVV_[`æ
		//DrawMeshCylinder();

		//bVh[`æ
		//DrawMeshDome();

		//GtFNg`æ
		DrawEffect();

		//f`æ
		DrawPlayer();

		//e`æ
		DrawShadow();

		//r{[h`æ
		//DrawBillBoard();

		//ÌÍ\¦`æ
		//DrawRemainLife();

//#ifdef _DEBUG
		//fobO\¦==========================
		DrawDebug();

		//fobO\¦vV[W`æ
		DrawDebugProc();
//#endif
		//`æI¹
		g_pD3DDevice->EndScene();
	}

	//obNEtgobt@ðüêÖ¦é
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//==================================================================================================
//fobO\¦
//==================================================================================================
void DrawDebug(void)
{
	//Ïé¾
	RECT rect = { 20,20,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//¶ñÉãü
	sprintf(&aStr[0], "FPS:%d\n[IJKL]Æ¾½ì\n[UM]Æ¾ãº\n[O]IðÆ¾ØèÖ¦\n[9]J[hØèÖ¦\n[F9]C[t[ØèÖ¦", g_nCountFPS);

	//eLXg`æ
	g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));

	DebugLight();

	DebugCurrentLight();

	DrawPlayerState(g_ppFont);

	DrawCameraState(g_ppFont);

	DrawCameraControl(g_ppFont);

	DrawCameraMode(g_ppFont);

	DrawBulletState(g_ppFont);

	DrawControlPlayer(g_ppFont);

	DrawAlphaThreshold();

	DrawExplosionState(g_ppFont);

	DrawPPartState(g_ppFont);

	DrawDebugPad();

	DebugMouse();
}

//==================================================================================================
//CgfobO\¦
//==================================================================================================
void DebugLight(void)
{
	//foCX|C^Ýè
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//Ïé¾
	char aStr[256];
	D3DLIGHT9 light;

	for (int nCntLight = 0; nCntLight < MAX_LIGHT;nCntLight++)
	{
		//ÊuÝè
		RECT rect = { 20,300 + 20 * nCntLight,SCREEN_WIDTH,SCREEN_HEIGHT };

		//CgÌîñæ¾
		pDevice->GetLight(nCntLight,&light);

		//¶ñÉãü
		sprintf(&aStr[0], "Cg%dÌûü[%.2f,%.2f,%.2f]", nCntLight + 1,light.Direction.x, light.Direction.y, light.Direction.z);

		//eLXg`æ
		g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}

//==================================================================================================
//IðCg\¦
//==================================================================================================
void DebugCurrentLight(void)
{
	//Ïé¾
	RECT rect = { 20,370,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//¶ñÉãü
	sprintf(&aStr[0], "IðÌCg[%d]",GetCurrentLight() + 1);

	//eLXg`æ
	g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//}EXfobO\¦
//==================================================================================================
void DebugMouse(void)
{	
	//Ïé¾
	char aStr[256];
	RECT rect = { 600,80,SCREEN_WIDTH,SCREEN_HEIGHT };

	//¶ñÉãü
	sprintf(&aStr[0], "}EXÚ®Ê[%.2f,%.2f]", (float)GetMouseMoveIX(), (float)GetMouseMoveIY());

	//eLXg`æ
	g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//NbNæ¾
//==================================================================================================
void DebugClick(void)
{
	//Ïé¾
	char aStr[256];
	RECT rect = { 800,80,SCREEN_WIDTH,SCREEN_HEIGHT };

	if (GetMousePress(MOUSEBUTTON_LMB) == true)
	{
		//¶ñÉãü
		sprintf(&aStr[0], "¶NbN");

		//eLXg`æ
		g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}

//==================================================================================================
//[hÝè
//==================================================================================================
void SetMode(MODE mode)
{
}

//==================================================================================================
//foCXÌæ¾
//==================================================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//==================================================================================================
//ñ]§ä
//==================================================================================================
void LimitRot(D3DXVECTOR3 *rot)
{
	//X====================
	if (rot->x > D3DX_PI)
	{
		rot->x = -D3DX_PI;
	}
	if (rot->x < -D3DX_PI)
	{
		rot->x = D3DX_PI;
	}

	//Y====================
	if (rot->y > D3DX_PI)
	{
		rot->y = -D3DX_PI;
	}
	if (rot->y < -D3DX_PI)
	{
		rot->y = D3DX_PI;
	}

	//Z====================
	if (rot->z > D3DX_PI)
	{
		rot->z = -D3DX_PI;
	}
	if (rot->z < -D3DX_PI)
	{
		rot->z = D3DX_PI;
	}
}

//==================================================================================================
//OÏÉæé½è»è(½Á½©Ç¤©¾¯)
//==================================================================================================
bool CrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 PrVtx, D3DXVECTOR3 ScVtx)
{
	D3DXVECTOR3 vecLine = D3DXVECTOR3
	(//êUYÀWÍ½Ê
		ScVtx.x - PrVtx.x,
		0.0f,
		ScVtx.z - PrVtx.z
	);

	D3DXVECTOR3 vecToPos = D3DXVECTOR3
	(
		pos.x - PrVtx.x,
		0.0f,
		pos.z - PrVtx.z
	);

	if ((vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) > 0)
	{//üªÌ¶É éê
		return true;
	}
	else
	{
		return false;
	}
}

//==================================================================================================
//lp`ÌOÏ½è»è
//==================================================================================================
bool SqrCrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax)
{
	if (CrossProduct(posOld, pos, move,
		D3DXVECTOR3(vtxMin.x,0.0f,vtxMax.z),
		D3DXVECTOR3(vtxMax.x,0.0f,vtxMax.z)) == true &&
		CrossProduct(posOld, pos, move,
		D3DXVECTOR3(vtxMax.x,0.0f,vtxMax.z),
		D3DXVECTOR3(vtxMax.x,0.0f,vtxMin.z)) == true &&
		CrossProduct(posOld, pos, move,
		D3DXVECTOR3(vtxMax.x,0.0f,vtxMin.z),
		D3DXVECTOR3(vtxMin.x,0.0f,vtxMin.z)) == true &&
		CrossProduct(posOld, pos, move,
		D3DXVECTOR3(vtxMin.x,0.0f,vtxMin.z),
		D3DXVECTOR3(vtxMin.x,0.0f,vtxMax.z)) == true)
	{//lpÌÍÍÉüÁ½ç
		return true;
	}
	else
	{
		return false;
	}
}

//==================================================================================================
//OÏ½è»è(Ç)
//==================================================================================================
void WallCrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 *pos, D3DXVECTOR3 *move, D3DXVECTOR3 PrVtx, D3DXVECTOR3 ScVtx, float width)
{
	D3DXVECTOR3 vecLine = D3DXVECTOR3
	(//êUYÀWÍ½Ê
		ScVtx.x - PrVtx.x,
		0.0f,
		ScVtx.z - PrVtx.z
	);

	D3DXVECTOR3 vecToPos = D3DXVECTOR3
	(
		pos->x - PrVtx.x,
		0.0f,
		pos->z - PrVtx.z
	);

	if ((vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) > 0)
	{//üªÌ¶É éê
		
		float fAngle = atan2f(vecToPos.x, vecToPos.z);
		float fLength = sqrtf(vecToPos.x * vecToPos.x + vecToPos.z * vecToPos.z);

		D3DXVECTOR3 posCross = 
		{//üªÌð_
			PrVtx.x + sinf(fAngle) * fLength,
			0.0f,
			PrVtx.z + cosf(fAngle) * fLength
		};

		*pos = D3DXVECTOR3
		(//ÊuÌC³
			posCross.x + sinf(fAngle - D3DX_PI * 0.5f) * width,
			0.0f,
			posCross.z + cosf(fAngle - D3DX_PI * 0.5f) * width
		);

		*move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}
}

//==================================================================================================
//At@eXgµ«¢lì
//==================================================================================================
void ControlAlphaThreshold(void)
{
	
}

//==================================================================================================
//At@eXgµ«¢læ¾
//==================================================================================================
DWORD GetAlphaThreshold(void)
{
	return g_dwThresholdAlpha;
}

//==================================================================================================
//At@eXgµ«¢l\¦
//==================================================================================================
void DrawAlphaThreshold(void)
{
	//Ïé¾
	char aStr[256];
	RECT rect = { 20,550,SCREEN_WIDTH,SCREEN_HEIGHT };

	//¶ñÉãü
	sprintf(&aStr[0], "At@eXgµ«¢l[%d]\nAt@eXg¸[1,2]", g_dwThresholdAlpha);

	//eLXg`æ
	g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//XeBbNl\¦
//==================================================================================================
void DrawDebugPad(void)
{
	//Ïé¾
	char aStr[256];
	RECT rect = { 500,20,SCREEN_WIDTH,SCREEN_HEIGHT };

	//¶ñÉãü
	sprintf(&aStr[0], "¶XeBbN[%.2f,%.2f]\nEXeBbN[%.2f,%.2f]", GetJoyStickLX(0), GetJoyStickLY(0), GetJoyStickRX(0), GetJoyStickRY(0));

	//eLXg`æ
	g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}