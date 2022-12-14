//==================================================================================================
//
//main.cpp
//Author:ϋόRη
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

//}Nθ`
#define WINDOW_NAME				"3D"				//EBhEΜΌO(LvV)

#define ID_TIMER
#define TIMER_INTERVAL

#define INITIAL_ALPHA			(100)				//ϊΜAt@eXg΅«’l

//O[oΟ
LPDIRECT3D9 g_pD3D = NULL;						//directRDIuWFNgΦΜ|C^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//directRDfoCXΦΜ|C^
LPD3DXFONT g_ppFont = NULL;						//tHgΦΜ|C^
MODE g_mode = MODE_TITLE;						//[h
int g_nCountFPS;								//FPSJE^
bool g_bDebug = false;							//fobO\¦ΜON/OFF
DWORD g_dwThresholdAlpha;						//At@lΜ΅«’l
bool g_bWire = false;							//C[t[\¦©Η€©

//vg^CvιΎ
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
//CΦ
//==================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	//ΟιΎ
	DWORD dwCurrentTime;				//»έ
	DWORD dwExecLastTime;				//ΕγΙ΅½
	DWORD dwFrameCount;					//t[JEg
	DWORD dwFPSLastTime;				//ΕγΙFPSπvͺ΅½Τ

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//tHg|C^EFPSJE^Μϊ»
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

	//EBhENXΜo^
	RegisterClassEx(&wcex);

	//NCAgΜζπEBhETCYΙνΉι
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//EBhEπΆ¬
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

	//ϊ»
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//ϊ»ΙΈs΅½κ
		return -1;
	}

	//ͺπ\πέθ
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	//EBhEΜ\¦
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//bZ[W[v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//WindowsΜ
			if (msg.message == WM_QUIT)
			{//WMQQUITbZ[Wπσ―ζΑ½η[vπ²―ι
				break;
			}
			else
			{
				//bZ[WΜέθ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DeirectXΜ

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5boί
				//FPSvͺ
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				//FPSπͺθ΅½ΤπΫΆ·ι
				dwFPSLastTime = dwCurrentTime;

				//t[JEgΜNA
				dwFrameCount = 0;
			}


			//»έΜζΎ
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60ͺΜ1boί
				//JnΜπvZ
				dwExecLastTime = dwCurrentTime;

				//XV
				Update();

				//`ζ
				Draw();

				//FPSJE^oί
				dwFrameCount++;
			}
		}
	}

	//IΉ
	Uninit();

	//EBhENXΜo^ππ
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
		//EBhEjόbZ[Wπσ―ζΑ½κ
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CLOSE:

		// }EXJ[\Μ\¦
		//ShowCursor(TRUE);
		
		//mFbZ[W
		nID = MessageBox(hWnd, "IΉ΅ά·©H", "IΉbZ[W", MB_YESNO);

		if (nID == IDYES)
		{//CGXΜκ
		 //EBhEjό
			DestroyWindow(hWnd);
		}
		else
		{
			// }EXJ[\Μ\¦
			//ShowCursor(FALSE);
			return 0;
		}

	case WM_KEYDOWN:
		switch (wParam)
		{
			//[ESC]L[ͺ³κ½
		case VK_ESCAPE:

			// }EXJ[\Μ\¦
			//ShowCursor(TRUE);

			//mFbZ[W
			nID = MessageBox(hWnd, "IΉ΅ά·©H", "IΉbZ[W", MB_YESNO);

			if (nID == IDYES)
			{//CGXΜκ
			 //EBhEjό
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
//ϊ»
//==================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//Οϊ»
	g_dwThresholdAlpha = INITIAL_ALPHA;

	D3DDISPLAYMODE d3ddm;								//fBXvC[hΜέθ
	D3DPRESENT_PARAMETERS d3dpp;						//fBXvC[hΜέθ

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{//Direct3DIuWFNgΆ¬
		return E_FAIL;
	}
	
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{//»έΜfBXvC[hπζΎ
		return E_FAIL;
	}

	//foCXΜv[e[Vp[^[Μέθ
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//p[^[Μ[NA

	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//Q[ζΚΜ
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//³
	d3dpp.BackBufferFormat = d3ddm.Format;							//`?
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//fMΙ―ϊ
	d3dpp.EnableAutoDepthStencil = TRUE;							//fuXΖXeVobt@πμ¬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//fuXobt@π16bitΕg€
	d3dpp.Windowed = bWindow;										//EBhE[h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//tbV[g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//C^[o

	//Direct3DfoCXΜΆ¬
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

	//_[Xe[gΜέθ
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//TvXe[gΜέθ
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

	//eNX`Xe[WXe[gΜέθ
	g_pD3DDevice->SetTextureStageState(0,
		D3DTSS_ALPHAOP,
		D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0,
		D3DTSS_ALPHAARG1,
		D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0,
		D3DTSS_ALPHAARG2,
		D3DTA_CURRENT);

	//fobO\¦ΜtHgΆ¬
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH,"Terminal", &g_ppFont);

	//foCXϊ»
	InitDevice(hInstance, hWnd);

	//|Sϊ»
	InitPolygon();

	//bVtB[hϊ»
	InitMeshField();

	//bVEH[ϊ»
	InitMeshWall();

	//bVV_[ϊ»
	InitMeshCylinder();

	//bVh[ϊ»
	InitMeshDome();

	//Jϊ»
	InitCamera();

	//Cgϊ»
	InitLight();

	//eϊ»
	InitShadow();

	//fϊ»
	InitPlayer();

	//Ηϊ»
	InitWall();

	//r{[hϊ»
	InitBillBoard();

	//eϊ»
	InitBullet();

	//­ϊ»
	InitExplosion();

	//GtFNgϊ»
	InitEffect();

	//p[eBNϊ»
	InitParticle();

	//fobO\¦vV[Wϊ»
	InitDebugProc();

	//ΜΝ\¦ϊ»
	InitRemainLife();

	//Gϊ»
	InitEnemy();

	//V[hlΜέθ
	srand((unsigned int)time(0));

	return S_OK;
}

//==================================================================================================
//IΉ
//==================================================================================================
void Uninit(void)
{
	//foCXIΉ
	UninitDevice();

	//|SIΉ
	UninitPolygon();

	//bVtB[hIΉ
	UninitMeshField();

	//bVEH[IΉ
	UninitMeshWall();

	//bVV_[IΉ
	UninitMeshCylinder();

	//bVh[IΉ
	UninitMeshDome();

	//JIΉ
	UninitCamera();

	//CgIΉ
	UninitLight();

	//fIΉ
	UninitPlayer();

	//eIΉ
	UninitShadow();

	//ΗIΉ
	UninitWall();

	//r{[hIΉ
	UninitBillBoard();

	//eIΉ
	UninitBullet();

	//GtFNgIΉ
	UninitEffect();

	//­IΉ
	UninitExplosion();

	//p[eBNIΉ
	UninitParticle();

	//fobO\¦vV[WIΉ
	UninitDebugProc();

	//ΜΝ\¦IΉ
	UninitRemainLife();

	//GIΉ
	UninitEnemy();

	if (g_ppFont != NULL)
	{//tHgΜjό
		g_ppFont->Release();
		g_ppFont = NULL;
	}

	if (g_pD3DDevice != NULL)
	{//Direct3DfoCXjό
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{//Direct3DIuWFNgΜjό
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	if (g_nCountFPS != NULL)
	{//FPSJE^Μjό
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

	//ΜΝ\¦XV
	UpdateRemainLife();

	//GXV
	UpdateEnemy();
}

//==================================================================================================
//fobOμ
//==================================================================================================
void DebugControl(void)
{
	//At@eXgμ======================================
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
//`ζ
//==================================================================================================
void Draw(void)
{
	//ζΚNA
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

	//`ζJn
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//`ζ

		//Jέθ
		SetCamera();

		//|S`ζ
		//DrawPolygon();

		//bVtB[h`ζ
		DrawMeshField();

		//bVEH[`ζ
		DrawMeshWall();

		//G`ζ
		DrawEnemy();

		//­`ζ
		DrawExplosion();

		//e`ζ
		DrawBullet();

		//bVV_[`ζ
		//DrawMeshCylinder();

		//bVh[`ζ
		//DrawMeshDome();

		//GtFNg`ζ
		DrawEffect();

		//f`ζ
		DrawPlayer();

		//e`ζ
		DrawShadow();

		//r{[h`ζ
		//DrawBillBoard();

		//ΜΝ\¦`ζ
		//DrawRemainLife();

//#ifdef _DEBUG
		//fobO\¦==========================
		DrawDebug();

		//fobO\¦vV[W`ζ
		DrawDebugProc();
//#endif
		//`ζIΉ
		g_pD3DDevice->EndScene();
	}

	//obNEtgobt@πόκΦ¦ι
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//==================================================================================================
//fobO\¦
//==================================================================================================
void DrawDebug(void)
{
	//ΟιΎ
	RECT rect = { 20,20,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//ΆρΙγό
	sprintf(&aStr[0], "FPS:%d\n[IJKL]ΖΎ½μ\n[UM]ΖΎγΊ\n[O]IπΖΎΨθΦ¦\n[9]J[hΨθΦ¦\n[F9]C[t[ΨθΦ¦", g_nCountFPS);

	//eLXg`ζ
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
	//foCX|C^έθ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ΟιΎ
	char aStr[256];
	D3DLIGHT9 light;

	for (int nCntLight = 0; nCntLight < MAX_LIGHT;nCntLight++)
	{
		//Κuέθ
		RECT rect = { 20,300 + 20 * nCntLight,SCREEN_WIDTH,SCREEN_HEIGHT };

		//CgΜξρζΎ
		pDevice->GetLight(nCntLight,&light);

		//ΆρΙγό
		sprintf(&aStr[0], "Cg%dΜϋό[%.2f,%.2f,%.2f]", nCntLight + 1,light.Direction.x, light.Direction.y, light.Direction.z);

		//eLXg`ζ
		g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}

//==================================================================================================
//IπCg\¦
//==================================================================================================
void DebugCurrentLight(void)
{
	//ΟιΎ
	RECT rect = { 20,370,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//ΆρΙγό
	sprintf(&aStr[0], "IπΜCg[%d]",GetCurrentLight() + 1);

	//eLXg`ζ
	g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//}EXfobO\¦
//==================================================================================================
void DebugMouse(void)
{	
	//ΟιΎ
	char aStr[256];
	RECT rect = { 600,80,SCREEN_WIDTH,SCREEN_HEIGHT };

	//ΆρΙγό
	sprintf(&aStr[0], "}EXΪ?Κ[%.2f,%.2f]", (float)GetMouseMoveIX(), (float)GetMouseMoveIY());

	//eLXg`ζ
	g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//NbNζΎ
//==================================================================================================
void DebugClick(void)
{
	//ΟιΎ
	char aStr[256];
	RECT rect = { 800,80,SCREEN_WIDTH,SCREEN_HEIGHT };

	if (GetMousePress(MOUSEBUTTON_LMB) == true)
	{
		//ΆρΙγό
		sprintf(&aStr[0], "ΆNbN");

		//eLXg`ζ
		g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}

//==================================================================================================
//[hέθ
//==================================================================================================
void SetMode(MODE mode)
{
}

//==================================================================================================
//foCXΜζΎ
//==================================================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//==================================================================================================
//ρ]§δ
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
//OΟΙζι½θ»θ(½Α½©Η€©Ύ―)
//==================================================================================================
bool CrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 PrVtx, D3DXVECTOR3 ScVtx)
{
	D3DXVECTOR3 vecLine = D3DXVECTOR3
	(//κUYΐWΝ½Κ
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
	{//όͺΜΆΙ ικ
		return true;
	}
	else
	{
		return false;
	}
}

//==================================================================================================
//lp`ΜOΟ½θ»θ
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
	{//lpΜΝΝΙόΑ½η
		return true;
	}
	else
	{
		return false;
	}
}

//==================================================================================================
//OΟ½θ»θ(Η)
//==================================================================================================
void WallCrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 *pos, D3DXVECTOR3 *move, D3DXVECTOR3 PrVtx, D3DXVECTOR3 ScVtx, float width)
{
	D3DXVECTOR3 vecLine = D3DXVECTOR3
	(//κUYΐWΝ½Κ
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
	{//όͺΜΆΙ ικ
		
		float fAngle = atan2f(vecToPos.x, vecToPos.z);
		float fLength = sqrtf(vecToPos.x * vecToPos.x + vecToPos.z * vecToPos.z);

		D3DXVECTOR3 posCross = 
		{//όͺΜπ_
			PrVtx.x + sinf(fAngle) * fLength,
			0.0f,
			PrVtx.z + cosf(fAngle) * fLength
		};

		*pos = D3DXVECTOR3
		(//ΚuΜC³
			posCross.x + sinf(fAngle - D3DX_PI * 0.5f) * width,
			0.0f,
			posCross.z + cosf(fAngle - D3DX_PI * 0.5f) * width
		);

		*move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}
}

//==================================================================================================
//At@eXg΅«’lμ
//==================================================================================================
void ControlAlphaThreshold(void)
{
	
}

//==================================================================================================
//At@eXg΅«’lζΎ
//==================================================================================================
DWORD GetAlphaThreshold(void)
{
	return g_dwThresholdAlpha;
}

//==================================================================================================
//At@eXg΅«’l\¦
//==================================================================================================
void DrawAlphaThreshold(void)
{
	//ΟιΎ
	char aStr[256];
	RECT rect = { 20,550,SCREEN_WIDTH,SCREEN_HEIGHT };

	//ΆρΙγό
	sprintf(&aStr[0], "At@eXg΅«’l[%d]\nAt@eXgΈ[1,2]", g_dwThresholdAlpha);

	//eLXg`ζ
	g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//XeBbNl\¦
//==================================================================================================
void DrawDebugPad(void)
{
	//ΟιΎ
	char aStr[256];
	RECT rect = { 500,20,SCREEN_WIDTH,SCREEN_HEIGHT };

	//ΆρΙγό
	sprintf(&aStr[0], "ΆXeBbN[%.2f,%.2f]\nEXeBbN[%.2f,%.2f]", GetJoyStickLX(0), GetJoyStickLY(0), GetJoyStickRX(0), GetJoyStickRY(0));

	//eLXg`ζ
	g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}