//==================================================================================================
//
//remainlife.cpp
//Author:髙山桃也
//
//==================================================================================================

#include "main.h"
#include "remainlife.h"
#include "player.h"

//マクロ定義
#define NUM_TEX							(2)										//テクスチャの数

#define REMAINLIFE_HEIGHT				(100.0f)								//高さ
#define REMAINLIFE_WIDTH				(500.0f)								//高さ

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureRemainLife[NUM_TEX] = {};							//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRemainLife = NULL;							//頂点バッファへのポインタ
const char *c_apFilenameRemainLife[NUM_TEX] =
{
	"data\\TEXTURE\\REMAINLIFE\\remainlife001.png",
	"data\\TEXTURE\\REMAINLIFE\\remainlife002.png"
};																				//テクスチャファイル名
D3DXVECTOR3 g_remainlifePos;													//座標

//==================================================================================================
//初期化処理
//==================================================================================================
void InitRemainLife(void)
{
	//変数初期化
	g_remainlifePos ={ 50.0f,50.0f,0.0f };

	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		c_apFilenameRemainLife[0],
		&g_pTextureRemainLife[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRemainLife,
		NULL);

	//頂点情報のポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRemainLife->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_remainlifePos.x, g_remainlifePos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_remainlifePos.x + REMAINLIFE_WIDTH, g_remainlifePos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_remainlifePos.x, g_remainlifePos.y + REMAINLIFE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_remainlifePos.x + REMAINLIFE_WIDTH, g_remainlifePos.y + REMAINLIFE_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	D3DXCOLOR colNormal = { 1.0f,1.0f,1.0f,1.0f };

	//頂点カラーの設定
	pVtx[0].col = colNormal;
	pVtx[1].col = colNormal;
	pVtx[2].col = colNormal;
	pVtx[3].col = colNormal;

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffRemainLife->Unlock();
}

//==================================================================================================
//終了処理
//==================================================================================================
void UninitRemainLife(void)
{
	for (int nCntRemainLife = 0;nCntRemainLife < NUM_TEX;nCntRemainLife++)
	{
		if (g_pTextureRemainLife[nCntRemainLife] != NULL)
		{//テクスチャへのポインタの破棄
			g_pTextureRemainLife[nCntRemainLife]->Release();
			g_pTextureRemainLife[nCntRemainLife] = NULL;
		}
	}

	if (g_pVtxBuffRemainLife != NULL)
	{//頂点バッファへのポインタの破棄
		g_pVtxBuffRemainLife->Release();
		g_pVtxBuffRemainLife = NULL;
	}
}

//==================================================================================================
//更新処理
//==================================================================================================
void UpdateRemainLife(void)
{
	//情報取得
	Player *pPlayer = GetPlayer();

	//頂点情報のポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRemainLife->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[1].pos = D3DXVECTOR3
	(
		(g_remainlifePos.x + REMAINLIFE_WIDTH) * pPlayer->fBoost / pPlayer->fBoostMax,
		g_remainlifePos.y, 
		0.0f
	);
	pVtx[3].pos = D3DXVECTOR3
	(
		(g_remainlifePos.x + REMAINLIFE_WIDTH) * pPlayer->fBoost / pPlayer->fBoostMax,
		g_remainlifePos.y + REMAINLIFE_HEIGHT, 
		0.0f
	);

	//頂点バッファをアンロック
	g_pVtxBuffRemainLife->Unlock();
}

//==================================================================================================
//描画処理
//==================================================================================================
void DrawRemainLife(void)
{
	//デバイスポインタ設定
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRemainLife, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureRemainLife[0]);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}