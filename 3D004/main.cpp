//==================================================================================================
//
//main.cpp
//Author:髙山桃也
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

//マクロ定義
#define WINDOW_NAME				"3D"				//ウィンドウの名前(キャプション)

#define ID_TIMER
#define TIMER_INTERVAL

#define INITIAL_ALPHA			(100)				//初期のアルファテストしきい値

//グローバル変数
LPDIRECT3D9 g_pD3D = NULL;						//direct３Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//direct３Dデバイスへのポインタ
LPD3DXFONT g_ppFont = NULL;						//フォントへのポインタ
MODE g_mode = MODE_TITLE;						//モード
int g_nCountFPS;								//FPSカウンタ
bool g_bDebug = false;							//デバッグ表示のON/OFF
DWORD g_dwThresholdAlpha;						//アルファ値のしきい値
bool g_bWire = false;							//ワイヤーフレーム表示かどうか

//プロトタイプ宣言
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
//メイン関数
//==================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	//変数宣言
	DWORD dwCurrentTime;				//現在時刻
	DWORD dwExecLastTime;				//最後に処理した時刻
	DWORD dwFrameCount;					//フレームカウント
	DWORD dwFPSLastTime;				//最後にFPSを計測した時間

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//フォントポインタ・FPSカウンタの初期化
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

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域をウィンドウサイズに合わせる
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
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

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化に失敗した場合
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windowsの処理
			if (msg.message == WM_QUIT)
			{//WM＿QUITメッセージを受け取ったらループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DeirectXの処理

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPS計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				//FPSを測定した時間を保存する
				dwFPSLastTime = dwCurrentTime;

				//フレームカウントのクリア
				dwFrameCount = 0;
			}


			//現在時刻の取得
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒経過
				//処理開始の時刻を計算
				dwExecLastTime = dwCurrentTime;

				//更新処理
				Update();

				//描画処理
				Draw();

				//FPSカウンタ経過
				dwFrameCount++;
			}
		}
	}

	//終了処理
	Uninit();

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//==================================================================================================
//ウィンドウプロシージャ
//==================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
		//ウィンドウ破棄メッセージを受け取った場合
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CLOSE:

		// マウスカーソルの表示
		//ShowCursor(TRUE);
		
		//確認メッセージ
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{//イエスの場合
		 //ウィンドウ破棄
			DestroyWindow(hWnd);
		}
		else
		{
			// マウスカーソルの表示
			//ShowCursor(FALSE);
			return 0;
		}

	case WM_KEYDOWN:
		switch (wParam)
		{
			//[ESC]キーが押された
		case VK_ESCAPE:

			// マウスカーソルの表示
			//ShowCursor(TRUE);

			//確認メッセージ
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{//イエスの場合
			 //ウィンドウ破棄
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
//初期化処理
//==================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//変数初期化
	g_dwThresholdAlpha = INITIAL_ALPHA;

	D3DDISPLAYMODE d3ddm;								//ディスプレイモードの設定
	D3DPRESENT_PARAMETERS d3dpp;						//ディスプレイモードの設定

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{//Direct3Dオブジェクト生成
		return E_FAIL;
	}
	
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{//現在のディスプレイモードを取得
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメーターの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//パラメーターのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//ゲーム画面の幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//高さ
	d3dpp.BackBufferFormat = d3ddm.Format;							//形式
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//映像信号に同期
	d3dpp.EnableAutoDepthStencil = TRUE;							//デブスとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//デブスバッファを16bitで使う
	d3dpp.Windowed = bWindow;										//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//インターバル

	//Direct3Dデバイスの生成
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

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプステートの設定
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

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0,
		D3DTSS_ALPHAOP,
		D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0,
		D3DTSS_ALPHAARG1,
		D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0,
		D3DTSS_ALPHAARG2,
		D3DTA_CURRENT);

	//デバッグ表示のフォント生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH,"Terminal", &g_ppFont);

	//デバイス初期化
	InitDevice(hInstance, hWnd);

	//ポリゴン初期化
	InitPolygon();

	//メッシュフィールド初期化
	InitMeshField();

	//メッシュウォール初期化
	InitMeshWall();

	//メッシュシリンダー初期化
	InitMeshCylinder();

	//メッシュドーム初期化
	InitMeshDome();

	//カメラ初期化
	InitCamera();

	//ライト初期化
	InitLight();

	//影初期化
	InitShadow();

	//モデル初期化
	InitPlayer();

	//壁初期化
	InitWall();

	//ビルボード初期化
	InitBillBoard();

	//弾初期化
	InitBullet();

	//爆発初期化
	InitExplosion();

	//エフェクト初期化
	InitEffect();

	//パーティクル初期化
	InitParticle();

	//デバッグ表示プロシージャ初期化
	InitDebugProc();

	//体力表示初期化
	InitRemainLife();

	//敵初期化
	InitEnemy();

	//乱数シード値の設定
	srand((unsigned int)time(0));

	return S_OK;
}

//==================================================================================================
//終了処理
//==================================================================================================
void Uninit(void)
{
	//デバイス終了処理
	UninitDevice();

	//ポリゴン終了
	UninitPolygon();

	//メッシュフィールド終了
	UninitMeshField();

	//メッシュウォール終了
	UninitMeshWall();

	//メッシュシリンダー終了
	UninitMeshCylinder();

	//メッシュドーム終了
	UninitMeshDome();

	//カメラ終了
	UninitCamera();

	//ライト終了
	UninitLight();

	//モデル終了処理
	UninitPlayer();

	//影終了処理
	UninitShadow();

	//壁終了処理
	UninitWall();

	//ビルボード終了
	UninitBillBoard();

	//弾終了処理
	UninitBullet();

	//エフェクト終了
	UninitEffect();

	//爆発終了
	UninitExplosion();

	//パーティクル終了
	UninitParticle();

	//デバッグ表示プロシージャ終了
	UninitDebugProc();

	//体力表示終了
	UninitRemainLife();

	//敵終了
	UninitEnemy();

	if (g_ppFont != NULL)
	{//フォントの破棄
		g_ppFont->Release();
		g_ppFont = NULL;
	}

	if (g_pD3DDevice != NULL)
	{//Direct3Dデバイス破棄
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{//Direct3Dオブジェクトの破棄
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	if (g_nCountFPS != NULL)
	{//FPSカウンタの破棄
		g_nCountFPS = NULL;
	}
}

//==================================================================================================
//更新処理
//==================================================================================================
void Update(void)
{
	//デバッグ処理
//#ifdef _DEBUG
	DebugControl();
//#endif

	//デバイス更新
	UpdateDevice();

	//カメラ更新処理
	UpdateCamera();

	//モデル更新処理
	UpdatePlayer();

	//ライト更新処理
	UpdateLight();

	//ビルボード更新処理
	UpdateBillBoard();

	//弾更新処理
	UpdateBullet();

	//爆発更新処理
	UpdateExplosion();

	//エフェクト更新処理
	UpdateEffect();

	//パーティクル更新
	UpdateParticle();

	//体力表示更新
	UpdateRemainLife();

	//敵更新処理
	UpdateEnemy();
}

//==================================================================================================
//デバッグ操作
//==================================================================================================
void DebugControl(void)
{
	//アルファテスト操作======================================
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

	//ワイヤーフレーム======================================
	if (GetKeyboardTrigger(DIK_F9))
	{
		g_bWire = g_bWire ? false : true;
	}
}

//==================================================================================================
//描画処理
//==================================================================================================
void Draw(void)
{
	//画面クリア
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	if (g_bWire)
	{//ワイヤーフレーム
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画処理

		//カメラ設定
		SetCamera();

		//ポリゴン描画
		//DrawPolygon();

		//メッシュフィールド描画
		DrawMeshField();

		//メッシュウォール描画
		DrawMeshWall();

		//敵描画処理
		DrawEnemy();

		//爆発描画処理
		DrawExplosion();

		//弾描画処理
		DrawBullet();

		//メッシュシリンダー描画
		//DrawMeshCylinder();

		//メッシュドーム描画
		//DrawMeshDome();

		//エフェクト描画
		DrawEffect();

		//モデル描画
		DrawPlayer();

		//影描画処理
		DrawShadow();

		//ビルボード描画
		//DrawBillBoard();

		//体力表示描画
		//DrawRemainLife();

//#ifdef _DEBUG
		//デバッグ表示==========================
		DrawDebug();

		//デバッグ表示プロシージャ描画
		DrawDebugProc();
//#endif
		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バック・フロントバッファを入れ替える
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//==================================================================================================
//デバッグ表示処理
//==================================================================================================
void DrawDebug(void)
{
	//変数宣言
	RECT rect = { 20,20,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	sprintf(&aStr[0], "FPS:%d\n[IJKL]照明水平操作\n[UM]照明上下\n[O]選択照明切り替え\n[9]カメラモード切り替え\n[F9]ワイヤーフレーム切り替え", g_nCountFPS);

	//テキスト描画
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
//ライトデバッグ表示
//==================================================================================================
void DebugLight(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数宣言
	char aStr[256];
	D3DLIGHT9 light;

	for (int nCntLight = 0; nCntLight < MAX_LIGHT;nCntLight++)
	{
		//位置設定
		RECT rect = { 20,300 + 20 * nCntLight,SCREEN_WIDTH,SCREEN_HEIGHT };

		//ライトの情報取得
		pDevice->GetLight(nCntLight,&light);

		//文字列に代入
		sprintf(&aStr[0], "ライト%dの方向[%.2f,%.2f,%.2f]", nCntLight + 1,light.Direction.x, light.Direction.y, light.Direction.z);

		//テキスト描画
		g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}

//==================================================================================================
//選択ライト表示
//==================================================================================================
void DebugCurrentLight(void)
{
	//変数宣言
	RECT rect = { 20,370,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	sprintf(&aStr[0], "選択中のライト[%d]",GetCurrentLight() + 1);

	//テキスト描画
	g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//マウスデバッグ表示
//==================================================================================================
void DebugMouse(void)
{	
	//変数宣言
	char aStr[256];
	RECT rect = { 600,80,SCREEN_WIDTH,SCREEN_HEIGHT };

	//文字列に代入
	sprintf(&aStr[0], "マウス移動量[%.2f,%.2f]", (float)GetMouseMoveIX(), (float)GetMouseMoveIY());

	//テキスト描画
	g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//クリック取得処理
//==================================================================================================
void DebugClick(void)
{
	//変数宣言
	char aStr[256];
	RECT rect = { 800,80,SCREEN_WIDTH,SCREEN_HEIGHT };

	if (GetMousePress(MOUSEBUTTON_LMB) == true)
	{
		//文字列に代入
		sprintf(&aStr[0], "左クリック中");

		//テキスト描画
		g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}

//==================================================================================================
//モード設定処理
//==================================================================================================
void SetMode(MODE mode)
{
}

//==================================================================================================
//デバイスの取得
//==================================================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//==================================================================================================
//回転制御処理
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
//外積による当たり判定(当たったかどうかだけ)
//==================================================================================================
bool CrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 PrVtx, D3DXVECTOR3 ScVtx)
{
	D3DXVECTOR3 vecLine = D3DXVECTOR3
	(//一旦Y座標は平面
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
	{//線分の左にある場合
		return true;
	}
	else
	{
		return false;
	}
}

//==================================================================================================
//四角形の外積当たり判定
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
	{//四角の範囲に入ったら
		return true;
	}
	else
	{
		return false;
	}
}

//==================================================================================================
//外積当たり判定(壁)
//==================================================================================================
void WallCrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 *pos, D3DXVECTOR3 *move, D3DXVECTOR3 PrVtx, D3DXVECTOR3 ScVtx, float width)
{
	D3DXVECTOR3 vecLine = D3DXVECTOR3
	(//一旦Y座標は平面
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
	{//線分の左にある場合
		
		float fAngle = atan2f(vecToPos.x, vecToPos.z);
		float fLength = sqrtf(vecToPos.x * vecToPos.x + vecToPos.z * vecToPos.z);

		D3DXVECTOR3 posCross = 
		{//線分の交点
			PrVtx.x + sinf(fAngle) * fLength,
			0.0f,
			PrVtx.z + cosf(fAngle) * fLength
		};

		*pos = D3DXVECTOR3
		(//位置の修正
			posCross.x + sinf(fAngle - D3DX_PI * 0.5f) * width,
			0.0f,
			posCross.z + cosf(fAngle - D3DX_PI * 0.5f) * width
		);

		*move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}
}

//==================================================================================================
//アルファテストしきい値操作
//==================================================================================================
void ControlAlphaThreshold(void)
{
	
}

//==================================================================================================
//アルファテストしきい値取得
//==================================================================================================
DWORD GetAlphaThreshold(void)
{
	return g_dwThresholdAlpha;
}

//==================================================================================================
//アルファテストしきい値表示
//==================================================================================================
void DrawAlphaThreshold(void)
{
	//変数宣言
	char aStr[256];
	RECT rect = { 20,550,SCREEN_WIDTH,SCREEN_HEIGHT };

	//文字列に代入
	sprintf(&aStr[0], "アルファテストしきい値[%d]\nアルファテスト増減[1,2]", g_dwThresholdAlpha);

	//テキスト描画
	g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//スティック値表示
//==================================================================================================
void DrawDebugPad(void)
{
	//変数宣言
	char aStr[256];
	RECT rect = { 500,20,SCREEN_WIDTH,SCREEN_HEIGHT };

	//文字列に代入
	sprintf(&aStr[0], "左スティック[%.2f,%.2f]\n右スティック[%.2f,%.2f]", GetJoyStickLX(0), GetJoyStickLY(0), GetJoyStickRX(0), GetJoyStickRY(0));

	//テキスト描画
	g_ppFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}