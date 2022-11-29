//==================================================================================================
//
//remainlife.cpp
//Author:���R����
//
//==================================================================================================

#include "main.h"
#include "remainlife.h"
#include "player.h"

//�}�N����`
#define NUM_TEX							(2)										//�e�N�X�`���̐�

#define REMAINLIFE_HEIGHT				(100.0f)								//����
#define REMAINLIFE_WIDTH				(500.0f)								//����

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureRemainLife[NUM_TEX] = {};							//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRemainLife = NULL;							//���_�o�b�t�@�ւ̃|�C���^
const char *c_apFilenameRemainLife[NUM_TEX] =
{
	"data\\TEXTURE\\REMAINLIFE\\remainlife001.png",
	"data\\TEXTURE\\REMAINLIFE\\remainlife002.png"
};																				//�e�N�X�`���t�@�C����
D3DXVECTOR3 g_remainlifePos;													//���W

//==================================================================================================
//����������
//==================================================================================================
void InitRemainLife(void)
{
	//�ϐ�������
	g_remainlifePos ={ 50.0f,50.0f,0.0f };

	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		c_apFilenameRemainLife[0],
		&g_pTextureRemainLife[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRemainLife,
		NULL);

	//���_���̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRemainLife->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_remainlifePos.x, g_remainlifePos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_remainlifePos.x + REMAINLIFE_WIDTH, g_remainlifePos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_remainlifePos.x, g_remainlifePos.y + REMAINLIFE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_remainlifePos.x + REMAINLIFE_WIDTH, g_remainlifePos.y + REMAINLIFE_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	D3DXCOLOR colNormal = { 1.0f,1.0f,1.0f,1.0f };

	//���_�J���[�̐ݒ�
	pVtx[0].col = colNormal;
	pVtx[1].col = colNormal;
	pVtx[2].col = colNormal;
	pVtx[3].col = colNormal;

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRemainLife->Unlock();
}

//==================================================================================================
//�I������
//==================================================================================================
void UninitRemainLife(void)
{
	for (int nCntRemainLife = 0;nCntRemainLife < NUM_TEX;nCntRemainLife++)
	{
		if (g_pTextureRemainLife[nCntRemainLife] != NULL)
		{//�e�N�X�`���ւ̃|�C���^�̔j��
			g_pTextureRemainLife[nCntRemainLife]->Release();
			g_pTextureRemainLife[nCntRemainLife] = NULL;
		}
	}

	if (g_pVtxBuffRemainLife != NULL)
	{//���_�o�b�t�@�ւ̃|�C���^�̔j��
		g_pVtxBuffRemainLife->Release();
		g_pVtxBuffRemainLife = NULL;
	}
}

//==================================================================================================
//�X�V����
//==================================================================================================
void UpdateRemainLife(void)
{
	//���擾
	Player *pPlayer = GetPlayer();

	//���_���̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
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

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRemainLife->Unlock();
}

//==================================================================================================
//�`�揈��
//==================================================================================================
void DrawRemainLife(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRemainLife, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureRemainLife[0]);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}