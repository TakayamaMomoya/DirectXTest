//==================================================================================================
//
//main.cpp
//Author:���R����
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

//�}�N����`
#define WINDOW_NAME				"3D"				//�E�B���h�E�̖��O(�L���v�V����)

#define ID_TIMER
#define TIMER_INTERVAL

#define INITIAL_ALPHA			(100)				//�����̃A���t�@�e�X�g�������l

//�O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL;						//direct�RD�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//direct�RD�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_ppFont = NULL;						//�t�H���g�ւ̃|�C���^
MODE g_mode = MODE_TITLE;						//���[�h
int g_nCountFPS;								//FPS�J�E���^
bool g_bDebug = false;							//�f�o�b�O�\����ON/OFF
DWORD g_dwThresholdAlpha;						//�A���t�@�l�̂������l
bool g_bWire = false;							//���C���[�t���[���\�����ǂ���

//�v���g�^�C�v�錾
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
//���C���֐�
//==================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	//�ϐ��錾
	DWORD dwCurrentTime;				//���ݎ���
	DWORD dwExecLastTime;				//�Ō�ɏ�����������
	DWORD dwFrameCount;					//�t���[���J�E���g
	DWORD dwFPSLastTime;				//�Ō��FPS���v����������

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//�t�H���g�|�C���^�EFPS�J�E���^�̏�����
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

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���E�B���h�E�T�C�Y�ɍ��킹��
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
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

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//�������Ɏ��s�����ꍇ
		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{//WM�QQUIT���b�Z�[�W���󂯎�����烋�[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DeirectX�̏���

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS�v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				//FPS�𑪒肵�����Ԃ�ۑ�����
				dwFPSLastTime = dwCurrentTime;

				//�t���[���J�E���g�̃N���A
				dwFrameCount = 0;
			}


			//���ݎ����̎擾
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��
				//�����J�n�̎������v�Z
				dwExecLastTime = dwCurrentTime;

				//�X�V����
				Update();

				//�`�揈��
				Draw();

				//FPS�J�E���^�o��
				dwFrameCount++;
			}
		}
	}

	//�I������
	Uninit();

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//==================================================================================================
//�E�B���h�E�v���V�[�W��
//==================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
		//�E�B���h�E�j�����b�Z�[�W���󂯎�����ꍇ
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CLOSE:

		// �}�E�X�J�[�\���̕\��
		//ShowCursor(TRUE);
		
		//�m�F���b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{//�C�G�X�̏ꍇ
		 //�E�B���h�E�j��
			DestroyWindow(hWnd);
		}
		else
		{
			// �}�E�X�J�[�\���̕\��
			//ShowCursor(FALSE);
			return 0;
		}

	case WM_KEYDOWN:
		switch (wParam)
		{
			//[ESC]�L�[�������ꂽ
		case VK_ESCAPE:

			// �}�E�X�J�[�\���̕\��
			//ShowCursor(TRUE);

			//�m�F���b�Z�[�W
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{//�C�G�X�̏ꍇ
			 //�E�B���h�E�j��
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
//����������
//==================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�ϐ�������
	g_dwThresholdAlpha = INITIAL_ALPHA;

	D3DDISPLAYMODE d3ddm;								//�f�B�X�v���C���[�h�̐ݒ�
	D3DPRESENT_PARAMETERS d3dpp;						//�f�B�X�v���C���[�h�̐ݒ�

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{//Direct3D�I�u�W�F�N�g����
		return E_FAIL;
	}
	
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{//���݂̃f�B�X�v���C���[�h���擾
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�[�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//�p�����[�^�[�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//�Q�[����ʂ̕�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//����
	d3dpp.BackBufferFormat = d3ddm.Format;							//�`��
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//�f���M���ɓ���
	d3dpp.EnableAutoDepthStencil = TRUE;							//�f�u�X�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//�f�u�X�o�b�t�@��16bit�Ŏg��
	d3dpp.Windowed = bWindow;										//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//�C���^�[�o��

	//Direct3D�f�o�C�X�̐���
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

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v�X�e�[�g�̐ݒ�
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

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0,
		D3DTSS_ALPHAOP,
		D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0,
		D3DTSS_ALPHAARG1,
		D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0,
		D3DTSS_ALPHAARG2,
		D3DTA_CURRENT);

	//�f�o�b�O�\���̃t�H���g����
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH,"Terminal", &g_ppFont);

	//�f�o�C�X������
	InitDevice(hInstance, hWnd);

	//�|���S��������
	InitPolygon();

	//���b�V���t�B�[���h������
	InitMeshField();

	//���b�V���E�H�[��������
	InitMeshWall();

	//���b�V���V�����_�[������
	InitMeshCylinder();

	//���b�V���h�[��������
	InitMeshDome();

	//�J����������
	InitCamera();

	//���C�g������
	InitLight();

	//�e������
	InitShadow();

	//���f��������
	InitPlayer();

	//�Ǐ�����
	InitWall();

	//�r���{�[�h������
	InitBillBoard();

	//�e������
	InitBullet();

	//����������
	InitExplosion();

	//�G�t�F�N�g������
	InitEffect();

	//�p�[�e�B�N��������
	InitParticle();

	//�f�o�b�O�\���v���V�[�W��������
	InitDebugProc();

	//�̗͕\��������
	InitRemainLife();

	//�G������
	InitEnemy();

	//�����V�[�h�l�̐ݒ�
	srand((unsigned int)time(0));

	return S_OK;
}

//==================================================================================================
//�I������
//==================================================================================================
void Uninit(void)
{
	//�f�o�C�X�I������
	UninitDevice();

	//�|���S���I��
	UninitPolygon();

	//���b�V���t�B�[���h�I��
	UninitMeshField();

	//���b�V���E�H�[���I��
	UninitMeshWall();

	//���b�V���V�����_�[�I��
	UninitMeshCylinder();

	//���b�V���h�[���I��
	UninitMeshDome();

	//�J�����I��
	UninitCamera();

	//���C�g�I��
	UninitLight();

	//���f���I������
	UninitPlayer();

	//�e�I������
	UninitShadow();

	//�ǏI������
	UninitWall();

	//�r���{�[�h�I��
	UninitBillBoard();

	//�e�I������
	UninitBullet();

	//�G�t�F�N�g�I��
	UninitEffect();

	//�����I��
	UninitExplosion();

	//�p�[�e�B�N���I��
	UninitParticle();

	//�f�o�b�O�\���v���V�[�W���I��
	UninitDebugProc();

	//�̗͕\���I��
	UninitRemainLife();

	//�G�I��
	UninitEnemy();

	if (g_ppFont != NULL)
	{//�t�H���g�̔j��
		g_ppFont->Release();
		g_ppFont = NULL;
	}

	if (g_pD3DDevice != NULL)
	{//Direct3D�f�o�C�X�j��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{//Direct3D�I�u�W�F�N�g�̔j��
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	if (g_nCountFPS != NULL)
	{//FPS�J�E���^�̔j��
		g_nCountFPS = NULL;
	}
}

//==================================================================================================
//�X�V����
//==================================================================================================
void Update(void)
{
	//�f�o�b�O����
//#ifdef _DEBUG
	DebugControl();
//#endif

	//�f�o�C�X�X�V
	UpdateDevice();

	//�J�����X�V����
	UpdateCamera();

	//���f���X�V����
	UpdatePlayer();

	//���C�g�X�V����
	UpdateLight();

	//�r���{�[�h�X�V����
	UpdateBillBoard();

	//�e�X�V����
	UpdateBullet();

	//�����X�V����
	UpdateExplosion();

	//�G�t�F�N�g�X�V����
	UpdateEffect();

	//�p�[�e�B�N���X�V
	UpdateParticle();

	//�̗͕\���X�V
	UpdateRemainLife();

	//�G�X�V����
	UpdateEnemy();
}

//==================================================================================================
//�f�o�b�O����
//==================================================================================================
void DebugControl(void)
{
	//�A���t�@�e�X�g����======================================
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

	//���C���[�t���[��======================================
	if (GetKeyboardTrigger(DIK_F9))
	{
		g_bWire = g_bWire ? false : true;
	}
}

//==================================================================================================
//�`�揈��
//==================================================================================================
void Draw(void)
{
	//��ʃN���A
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	if (g_bWire)
	{//���C���[�t���[��
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`�揈��

		//�J�����ݒ�
		SetCamera();

		//�|���S���`��
		//DrawPolygon();

		//���b�V���t�B�[���h�`��
		DrawMeshField();

		//���b�V���E�H�[���`��
		DrawMeshWall();

		//�G�`�揈��
		DrawEnemy();

		//�����`�揈��
		DrawExplosion();

		//�e�`�揈��
		DrawBullet();

		//���b�V���V�����_�[�`��
		//DrawMeshCylinder();

		//���b�V���h�[���`��
		//DrawMeshDome();

		//�G�t�F�N�g�`��
		DrawEffect();

		//���f���`��
		DrawPlayer();

		//�e�`�揈��
		DrawShadow();

		//�r���{�[�h�`��
		//DrawBillBoard();

		//�̗͕\���`��
		//DrawRemainLife();

//#ifdef _DEBUG
		//�f�o�b�O�\��==========================
		DrawDebug();

		//�f�o�b�O�\���v���V�[�W���`��
		DrawDebugProc();
//#endif
		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�E�t�����g�o�b�t�@�����ւ���
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//==================================================================================================
//�f�o�b�O�\������
//==================================================================================================
void DrawDebug(void)
{
	//�ϐ��錾
	RECT rect = { 20,20,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	sprintf(&aStr[0], "FPS:%d\n[IJKL]�Ɩ���������\n[UM]�Ɩ��㉺\n[O]�I���Ɩ��؂�ւ�\n[9]�J�������[�h�؂�ւ�\n[F9]���C���[�t���[���؂�ւ�", g_nCountFPS);

	//�e�L�X�g�`��
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
//���C�g�f�o�b�O�\��
//==================================================================================================
void DebugLight(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	char aStr[256];
	D3DLIGHT9 light;

	for (int nCntLight = 0; nCntLight < MAX_LIGHT;nCntLight++)
	{
		//�ʒu�ݒ�
		RECT rect = { 20,300 + 20 * nCntLight,SCREEN_WIDTH,SCREEN_HEIGHT };

		//���C�g�̏��擾
		pDevice->GetLight(nCntLight,&light);

		//������ɑ��
		sprintf(&aStr[0], "���C�g%d�̕���[%.2f,%.2f,%.2f]", nCntLight + 1,light.Direction.x, light.Direction.y, light.Direction.z);

		//�e�L�X�g�`��
		g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}

//==================================================================================================
//�I�����C�g�\��
//==================================================================================================
void DebugCurrentLight(void)
{
	//�ϐ��錾
	RECT rect = { 20,370,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	sprintf(&aStr[0], "�I�𒆂̃��C�g[%d]",GetCurrentLight() + 1);

	//�e�L�X�g�`��
	g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//�}�E�X�f�o�b�O�\��
//==================================================================================================
void DebugMouse(void)
{	
	//�ϐ��錾
	char aStr[256];
	RECT rect = { 600,80,SCREEN_WIDTH,SCREEN_HEIGHT };

	//������ɑ��
	sprintf(&aStr[0], "�}�E�X�ړ���[%.2f,%.2f]", (float)GetMouseMoveIX(), (float)GetMouseMoveIY());

	//�e�L�X�g�`��
	g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//�N���b�N�擾����
//==================================================================================================
void DebugClick(void)
{
	//�ϐ��錾
	char aStr[256];
	RECT rect = { 800,80,SCREEN_WIDTH,SCREEN_HEIGHT };

	if (GetMousePress(MOUSEBUTTON_LMB) == true)
	{
		//������ɑ��
		sprintf(&aStr[0], "���N���b�N��");

		//�e�L�X�g�`��
		g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}

//==================================================================================================
//���[�h�ݒ菈��
//==================================================================================================
void SetMode(MODE mode)
{
}

//==================================================================================================
//�f�o�C�X�̎擾
//==================================================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//==================================================================================================
//��]���䏈��
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
//�O�ςɂ�铖���蔻��(�����������ǂ�������)
//==================================================================================================
bool CrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 PrVtx, D3DXVECTOR3 ScVtx)
{
	D3DXVECTOR3 vecLine = D3DXVECTOR3
	(//��UY���W�͕���
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
	{//�����̍��ɂ���ꍇ
		return true;
	}
	else
	{
		return false;
	}
}

//==================================================================================================
//�l�p�`�̊O�ϓ����蔻��
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
	{//�l�p�͈̔͂ɓ�������
		return true;
	}
	else
	{
		return false;
	}
}

//==================================================================================================
//�O�ϓ����蔻��(��)
//==================================================================================================
void WallCrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 *pos, D3DXVECTOR3 *move, D3DXVECTOR3 PrVtx, D3DXVECTOR3 ScVtx, float width)
{
	D3DXVECTOR3 vecLine = D3DXVECTOR3
	(//��UY���W�͕���
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
	{//�����̍��ɂ���ꍇ
		
		float fAngle = atan2f(vecToPos.x, vecToPos.z);
		float fLength = sqrtf(vecToPos.x * vecToPos.x + vecToPos.z * vecToPos.z);

		D3DXVECTOR3 posCross = 
		{//�����̌�_
			PrVtx.x + sinf(fAngle) * fLength,
			0.0f,
			PrVtx.z + cosf(fAngle) * fLength
		};

		*pos = D3DXVECTOR3
		(//�ʒu�̏C��
			posCross.x + sinf(fAngle - D3DX_PI * 0.5f) * width,
			0.0f,
			posCross.z + cosf(fAngle - D3DX_PI * 0.5f) * width
		);

		*move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}
}

//==================================================================================================
//�A���t�@�e�X�g�������l����
//==================================================================================================
void ControlAlphaThreshold(void)
{
	
}

//==================================================================================================
//�A���t�@�e�X�g�������l�擾
//==================================================================================================
DWORD GetAlphaThreshold(void)
{
	return g_dwThresholdAlpha;
}

//==================================================================================================
//�A���t�@�e�X�g�������l�\��
//==================================================================================================
void DrawAlphaThreshold(void)
{
	//�ϐ��錾
	char aStr[256];
	RECT rect = { 20,550,SCREEN_WIDTH,SCREEN_HEIGHT };

	//������ɑ��
	sprintf(&aStr[0], "�A���t�@�e�X�g�������l[%d]\n�A���t�@�e�X�g����[1,2]", g_dwThresholdAlpha);

	//�e�L�X�g�`��
	g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//�X�e�B�b�N�l�\��
//==================================================================================================
void DrawDebugPad(void)
{
	//�ϐ��錾
	char aStr[256];
	RECT rect = { 500,20,SCREEN_WIDTH,SCREEN_HEIGHT };

	//������ɑ��
	sprintf(&aStr[0], "���X�e�B�b�N[%.2f,%.2f]\n�E�X�e�B�b�N[%.2f,%.2f]", GetJoyStickLX(0), GetJoyStickLY(0), GetJoyStickRX(0), GetJoyStickRY(0));

	//�e�L�X�g�`��
	g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}