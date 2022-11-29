//==================================================================================================
//
//camera.h
//Author:髙山桃也
//
//==================================================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

//マクロ定義
#define MIN_DRAW		(10.0f)					//描画を開始する距離
#define MAX_DRAW		(10000.0f)				//描画を終了する距離

//列挙型宣言
typedef enum
{
	CAMERA_MODE_CHASE = 0,						//追従モード
	CAMERA_MODE_CONTROL,						//操作モード
	CAMERA_MODE_AUTO,							//回り込みモード
	CAMERA_MODE_MAX
}CAMERA_MODE;

//構造体宣言
typedef struct
{
	D3DXVECTOR3 posV;							//視点
	D3DXVECTOR3 posR;							//注視点
	D3DXVECTOR3 posVDest;						//目的の視点
	D3DXVECTOR3 posRDest;						//目的の注視点
	D3DXVECTOR3 vecU;							//上方向ベクトル
	D3DXVECTOR3 rot;							//向き
	float fLength;								//視点から注視点までの距離
	D3DXMATRIX mtxProjection;					//プロジェクションマトリックス
	D3DXMATRIX mtxView;							//ビューマトリックス
	int nCounterWrap;							//カメラが回り込むまでのカウンタ
	int nTimerWrap;								//カメラが回り込むまでの時間
}Camera;

//プロトタイプ宣言
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera *GetCamera(void);
void DrawCameraState(LPD3DXFONT pFont);
void DrawCameraControl(LPD3DXFONT pFont);
void DrawCameraMode(LPD3DXFONT pFont);
#endif