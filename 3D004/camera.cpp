//==================================================================================================
//
//camera.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "camera.h"
#include "player.h"
#include "input.h"
#include <stdio.h>

//マクロ定義
#define MOVE_SPEED					(1.0f)						//移動スピード
#define ROLL_SPEED					(0.05f)						//回転スピード
#define MOUSE_FACT					(0.03f)						//マウスの値減衰係数
#define INITIAL_TIMER				(60)						//初期の回り込むまでの時間
#define WRAP_SPEED					(0.1f)						//回り込む条件の移動量
#define ROLL_FACT					(0.02f)						//回転減衰係数

//グローバル変数宣言
Camera g_camera;												//構造体の情報
CAMERA_MODE g_cameraMode;										//カメラのモード

//プロトタイプ宣言
void ControlCamera(void);
void FollowPlayer(void);
void AutoCamera(void);
void SetPosV(void);
void SetPosR(void);

//==================================================================================================
//初期化処理
//==================================================================================================
void InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(0.0f, 40.0f, -200.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fLength = 0.0f;
	g_camera.nCounterWrap = 0;
	g_camera.nTimerWrap = INITIAL_TIMER;

	float fLength = sqrtf
	(
		(g_camera.posV.x - g_camera.posR.x) * (g_camera.posV.x - g_camera.posR.x) + (g_camera.posV.z - g_camera.posR.z) * (g_camera.posV.z - g_camera.posR.z)
	);
	//X視点
	g_camera.fLength = sqrtf
	(
		fLength * fLength + (g_camera.posV.y - g_camera.posR.y) * (g_camera.posV.y - g_camera.posR.y)
	);

	g_camera.rot.x = atan2f(fLength, g_camera.posV.y - g_camera.posR.y);

	SetPosV();
}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitCamera(void)
{
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdateCamera(void)
{
	switch (g_cameraMode)
	{//モードによる分岐
	case CAMERA_MODE_CONTROL:

		//操作処理
		ControlCamera();

		break;
	case CAMERA_MODE_CHASE:

		//追従処理
		FollowPlayer();

		break;
	case CAMERA_MODE_AUTO:

		//回り込み処理
		AutoCamera();

		break;
	}

	//回転制限
	if (g_camera.rot.x > 3.0f)
	{
		g_camera.rot.x = 3.0f;
	}
	if (g_camera.rot.x < 0.1f)
	{
		g_camera.rot.x = 0.1f;
	}

	if (GetKeyboardTrigger(DIK_9) == true)
	{//モード切り替え
		g_cameraMode = (CAMERA_MODE)((g_cameraMode + 1) % CAMERA_MODE_MAX);
	}

	//回転制御処理
	LimitRot(&g_camera.rot);
}

//==================================================================================================
//操作処理
//==================================================================================================
void ControlCamera(void)
{
	//視点移動===============================================
	if (GetKeyboardRepeat(DIK_A) == true)
	{//左移動
		g_camera.posV.x -= sinf(g_camera.rot.y + D3DX_PI * -0.5f) * MOVE_SPEED;
		g_camera.posV.z -= cosf(g_camera.rot.y + D3DX_PI * -0.5f) * MOVE_SPEED;
		SetPosR();
	}
	if (GetKeyboardRepeat(DIK_D) == true)
	{//右移動
		g_camera.posV.x -= sinf(g_camera.rot.y - D3DX_PI * -0.5f) * MOVE_SPEED;
		g_camera.posV.z -= cosf(g_camera.rot.y - D3DX_PI * -0.5f) * MOVE_SPEED;
		SetPosR();
	}
	if (GetKeyboardRepeat(DIK_W) == true)
	{//前移動
		g_camera.posV.x -= sinf(g_camera.rot.y) * MOVE_SPEED;
		g_camera.posV.z -= cosf(g_camera.rot.y) * MOVE_SPEED;
		SetPosR();
	}
	if (GetKeyboardRepeat(DIK_S) == true)
	{//後移動
		g_camera.posV.x -= sinf(g_camera.rot.y + D3DX_PI) * MOVE_SPEED;
		g_camera.posV.z -= cosf(g_camera.rot.y + D3DX_PI) * MOVE_SPEED;
		SetPosR();
	}

	//視点回転===============================================
	if (GetKeyboardRepeat(DIK_Q) == true)
	{//左を向く
		g_camera.rot.y -= ROLL_SPEED;
		//注視点を相対位置に設定
		SetPosR();
	}
	if (GetKeyboardRepeat(DIK_E) == true)
	{//右を向く
		g_camera.rot.y += ROLL_SPEED;
		//注視点を相対位置に設定
		SetPosR();
	}

	if (GetKeyboardRepeat(DIK_Z) == true)
	{//左公転
		g_camera.rot.y += ROLL_SPEED;
		//注視点を相対位置に設定
		SetPosV();
	}
	if (GetKeyboardRepeat(DIK_C) == true)
	{//右公転
		g_camera.rot.y -= ROLL_SPEED;
		//注視点を相対位置に設定
		SetPosV();
	}

	//縦回転====================================================================
	if (GetKeyboardRepeat(DIK_T) == true)
	{//上を向く
		g_camera.rot.x += ROLL_SPEED;
		//注視点を相対位置に設定
		SetPosR();

		if (g_camera.rot.x < 0.1f)
		{
			g_camera.rot.x = 0.1f;
		}
	}
	if (GetKeyboardRepeat(DIK_B) == true)
	{//下を向く
		g_camera.rot.x -= ROLL_SPEED;
		//注視点を相対位置に設定
		SetPosR();

		if (g_camera.rot.x > 3.0f)
		{
			g_camera.rot.x = 3.0f;
		}
	}

	if (GetKeyboardRepeat(DIK_N) == true)
	{//下
		g_camera.rot.x += ROLL_SPEED;

		//注視点を相対位置に設定
		SetPosV();

		if (g_camera.rot.x < 0.1f)
		{
			g_camera.rot.x = 0.1f;
		}
	}
	if (GetKeyboardRepeat(DIK_Y) == true)
	{//上
		g_camera.rot.x -= ROLL_SPEED;
		//注視点を相対位置に設定
		SetPosV();

		if (g_camera.rot.x > 3.0f)
		{
			g_camera.rot.x = 3.0f;
		}
	}

	//マウス操作======================================================
	if (GetMousePress(MOUSEBUTTON_LMB) == true)
	{//左クリック中、注視点旋回
		D3DXVECTOR3 rot;

		//マウスの移動量代入
		rot = { (float)GetMouseMoveIX() * ROLL_SPEED, (float)GetMouseMoveIY() * ROLL_SPEED, 0.0f };

		//視点の旋回
		g_camera.rot.y += rot.x;
		g_camera.rot.x -= rot.y;

		//注視点を相対位置に設定
		SetPosV();
	}
	if (GetMousePress(MOUSEBUTTON_RMB) == true)
	{//右クリック中、視点旋回
		D3DXVECTOR3 rot;

		//マウスの移動量代入
		rot = { (float)GetMouseMoveIX() * ROLL_SPEED, (float)GetMouseMoveIY() * ROLL_SPEED, 0.0f };

		//視点の旋回
		g_camera.rot.y += rot.x;
		g_camera.rot.x -= rot.y;

		//注視点を相対位置に設定
		SetPosR();
	}

	if (GetMouseMoveIZ() != 0)
	{
		g_camera.fLength -= GetMouseMoveIZ() * 0.1f;

		if (g_camera.fLength < 30.0f)
		{
			g_camera.fLength = 30.0f;
		}

		SetPosV();
	}
}

//==================================================================================================
//追従処理
//==================================================================================================
void FollowPlayer(void)
{
	//情報取得
	Player *pPlayer = GetPlayer();

	//目標の注視点設定
	g_camera.posRDest =
	{
		pPlayer->pos.x,
		pPlayer->pos.y + 100,
		pPlayer->pos.z
	};

	//目標の視点設定
	g_camera.posVDest =
	{
		g_camera.posRDest.x + sinf(g_camera.rot.x) * sinf(pPlayer->rot.y) * g_camera.fLength,
		g_camera.posRDest.y + cosf(g_camera.rot.x) * g_camera.fLength,
		g_camera.posRDest.z + sinf(g_camera.rot.x) * cosf(pPlayer->rot.y) * g_camera.fLength
	};

	//注視点補正
	g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.1f;
	g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.1f;
	g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.1f;

	//現在の視点補正
	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.1f;
	g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.1f;
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.1f;
}

//==================================================================================================
//回り込み処理
//==================================================================================================
void AutoCamera(void)
{
	//情報取得
	Player *pPlayer = GetPlayer();

	float fSpeed = sqrtf
	(//スピード算出
		pPlayer->move.x * pPlayer->move.x + 
		pPlayer->move.z * pPlayer->move.z
	);

	if (fSpeed < WRAP_SPEED)
	{//ある程度止まったら回り込み準備
		g_camera.nCounterWrap++;

		if (g_camera.nCounterWrap >= g_camera.nTimerWrap)
		{//一定時間経過で回り込む

			g_camera.nCounterWrap = g_camera.nTimerWrap;

		 //カメラの奥に向く==================================================
			//差分角度を取得
			float fRotDiff = pPlayer->rot.y + D3DX_PI - g_camera.rot.y;

			//角度の修正
			if (fRotDiff < 0)
			{
				fRotDiff += 6.28f;
			}
			else if (fRotDiff > 0)
			{
				fRotDiff -= 6.28f;
			}

			//角度補正
			g_camera.rot.y += fRotDiff * ROLL_FACT;

			//角度の修正
			if (fRotDiff < 0)
			{
				fRotDiff += 6.28f;
			}
			else if (fRotDiff > 0)
			{
				fRotDiff -= 6.28f;
			}

			//角度補正
			g_camera.rot.y += fRotDiff * ROLL_FACT;

			//===================================================================

			SetPosV();
		}
	}
	else
	{
		//目標の注視点設定
		g_camera.posRDest = pPlayer->pos;

		//目標の視点設定
		g_camera.posVDest =
		{
			g_camera.posRDest.x + sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fLength,
			g_camera.posRDest.y + cosf(g_camera.rot.x) * g_camera.fLength,
			g_camera.posRDest.z + sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fLength
		};

		g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.1f;
		g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.1f;
		g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.1f;

		//現在の視点補正
		g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.1f;
		g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.1f;
		g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.1f;
	}
}

//==================================================================================================
//視点設定
//==================================================================================================
void SetPosV(void)
{
	g_camera.posV =
	{
		g_camera.posR.x + sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fLength,
		g_camera.posR.y + cosf(g_camera.rot.x) * g_camera.fLength,
		g_camera.posR.z + sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fLength
	};
}

//==================================================================================================
//注視点設定
//==================================================================================================
void SetPosR(void)
{
	g_camera.posR =
	{
		g_camera.posV.x - sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fLength,
		g_camera.posV.y - cosf(g_camera.rot.x) * g_camera.fLength,
		g_camera.posV.z - sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fLength
	};
}

//==================================================================================================
//設定処理
//==================================================================================================
void SetCamera(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//プロジェクションマトリックス==================================================
	//プロジェクションマトリックス初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックス作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		MIN_DRAW,
		MAX_DRAW);

	//マトリックス設定
	pDevice->SetTransform(D3DTS_PROJECTION,&g_camera.mtxProjection);

	//ビューマトリックス============================================================
	//ビューマトリックス初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックス作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//ビューマトリックス設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//==================================================================================================
//情報取得処理
//==================================================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}

//==================================================================================================
//情報描画処理(デバッグ)
//==================================================================================================
void DrawCameraState(LPD3DXFONT pFont)
{
	//変数宣言
	RECT rect = { 20,450,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	sprintf(&aStr[0], "視点の位置[%.2f,%.2f,%.2f]\n注視点の位置[%.2f,%.2f,%.2f]\n視点の向き[%.2f,%.2f,%.2f]\n視点から注視点の距離[%.2f]\nカメラモード[%d]",
		g_camera.posV.x, g_camera.posV.y, g_camera.posV.z, g_camera.posR.x, g_camera.posR.y, g_camera.posR.z, g_camera.rot.x, g_camera.rot.y, g_camera.rot.z,g_camera.fLength,(int)g_cameraMode);

	//テキスト描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//操作方法描画(デバッグ)
//==================================================================================================
void DrawCameraControl(LPD3DXFONT pFont)
{
	//変数宣言
	RECT rect = { 20,150,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	sprintf(&aStr[0], "カメラ水平移動[WASD]\n視点操作[ZC][YN]\n注視点操作[QE][YN]");

	//テキスト描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//モード描画(デバッグ)
//==================================================================================================
void DrawCameraMode(LPD3DXFONT pFont)
{
	//変数宣言
	RECT rect = { 500,70,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	switch (g_cameraMode)
	{
	case CAMERA_MODE_CHASE:

		//文字列に代入
		sprintf(&aStr[0], "カメラモード[追従]");

		//テキスト描画
		pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(255, 255, 255, 255));

		break;

	case CAMERA_MODE_CONTROL:

		//文字列に代入
		sprintf(&aStr[0], "カメラモード[操作]");

		//テキスト描画
		pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(255, 255, 255, 255));

		break;

	case CAMERA_MODE_AUTO:

		//文字列に代入
		sprintf(&aStr[0], "カメラモード[回り込み]");

		//テキスト描画
		pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(255, 255, 255, 255));

		break;
	}

	
}