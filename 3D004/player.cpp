//==================================================================================================
//
//player.cpp
//Author:���R����
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

//�}�N����`
#define MOVE_SPEED					(0.7f)									//�ړ����x
#define NUM_TEX						(8)										//�e�N�X�`����
#define ROLL_FACT					(0.06f)									//��]�����W��
#define ROLL_SPEED					(0.04f)									//��]���x
#define BULLET_SPEED				(10.0f)									//�e�̃X�s�[�h
#define MOVE_FACT					(0.9f)									//�ړ��ʌ����W��
#define MAX_PART					(24)									//�p�[�c�̍ő吔
#define MAX_STRING					(256)									//�ő�̕�����
#define MOTION_FILE					"data\\motion_AC.txt"					//���[�V�����t�@�C����
#define BOOST_SPEED					(20)									//�u�[�X�g�̑��x
#define DODGE_COST					(80.0f)									//����̃u�[�X�^�[�R�X�g

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTexturePlayer[MAX_PART][NUM_TEX] = {};			//�e�N�X�`���ւ̃|�C���^
int g_nIdxShadowPlayer;										//�e�̃C���f�b�N�X
Player g_player;											//�\���̂̏��
PlayerPart g_aPlayerPart[MAX_PART];							//�\���̂̏��
int g_nNumPlayerParts;										//�p�[�c��
char g_acFilenamePlayer[MAX_PART][MAX_STRING];				//�p�[�c�̃t�@�C����

//�v���g�^�C�v�錾
void ControlPlayer(void);
void UpdatePosPlayer(void);
void LimitMovePlayer(void);
void LoadMotion(FILE *pFile);

//==================================================================================================
//����������
//==================================================================================================
void InitPlayer(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//�ϐ�������
	g_player.pos = { 0.0f,0.0f,0.0f };
	g_player.move = { 0.0f,0.0f,0.0f };
	g_player.rot = { 0.0f,0.0f,0.0f };
	g_player.fBoost = INITIAL_MAX_BOOST;
	g_player.fBoostMax = INITIAL_MAX_BOOST;
	g_player.nLife = PLAYER_LIFE;
	g_nIdxShadowPlayer = 0;
	g_nNumPlayerParts = 0;

	//���擾
	PlayerPart *pPlayerPart = GetPlayerPart();

	//�t�@�C��������ƑI������ǂݍ���
	FILE *pFile = fopen(MOTION_FILE, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
	    //�t�@�C���ǂݍ��ݏ���
		LoadMotion(pFile);
	}
	else
	{
	}

	for (int nCntPart = 0;nCntPart < g_nNumPlayerParts;nCntPart++)
	{//�p�[�c�ǂݍ���
		//�ϐ�������
		pPlayerPart[nCntPart].dwNumMat = 0;

		//X�t�@�C���ǂݍ���
		D3DXLoadMeshFromX(&g_acFilenamePlayer[nCntPart][0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&pPlayerPart[nCntPart].pBuffMat,
			NULL,
			&pPlayerPart[nCntPart].dwNumMat,
			&pPlayerPart[nCntPart].pMesh);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)pPlayerPart[nCntPart].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)pPlayerPart[nCntPart].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`�������݂���
			    //�e�N�X�`���ǂݍ���
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

	//�e�C���f�b�N�X�擾
	g_nIdxShadowPlayer = SetShadow(40.0f);
}

//==================================================================================================
//�I������
//==================================================================================================
void UninitPlayer(void)
{
	//�ϐ��錾
	int nCntPlayer;

	//���擾
	PlayerPart *pPlayerPart = GetPlayerPart();

	for (nCntPlayer = 0;nCntPlayer < g_nNumPlayerParts;nCntPlayer++)
	{
		if (pPlayerPart->pMesh != NULL)
		{//���b�V���|�C���^�̔j��
			pPlayerPart->pMesh->Release();
			pPlayerPart->pMesh = NULL;
		}
	}
	
	for (nCntPlayer = 0; nCntPlayer < g_nNumPlayerParts; nCntPlayer++)
	{
		if (pPlayerPart->pBuffMat != NULL)
		{//���_�o�b�t�@�|�C���^�̔j��
			pPlayerPart->pBuffMat->Release();
			pPlayerPart->pBuffMat = NULL;
		}
	}

	for (int nCntTex = 0;nCntTex < NUM_TEX * MAX_PART;nCntTex++)
	{
		if (g_apTexturePlayer[nCntTex / NUM_TEX][nCntTex % NUM_TEX] != NULL)
		{//�e�N�X�`���|�C���^�̔j��
			g_apTexturePlayer[nCntTex / NUM_TEX][nCntTex % NUM_TEX]->Release();
			g_apTexturePlayer[nCntTex / NUM_TEX][nCntTex % NUM_TEX] = NULL;
		}
	}
}

//==================================================================================================
//�X�V����
//==================================================================================================
void UpdatePlayer(void)
{
	//���擾
	Camera *pCamera = GetCamera();

	//���쏈��
	ControlPlayer();

	//�ʒu�X�V����
	UpdatePosPlayer();

	//�ړ���������
	LimitMovePlayer();

	//��]���䏈��
	LimitRot(&g_player.rot);

	//�f�o�b�O�p,�̉�]
	g_aPlayerPart[1].rot.y += 0.3f;
	LimitRot(&g_aPlayerPart[1].rot);

	g_aPlayerPart[0].pos = g_player.pos;

	//�e�̈ʒu�ݒ�
	SetPositionShadow(g_nIdxShadowPlayer, g_player.pos);
}

//==================================================================================================
//�v���C���[���쏈��
//==================================================================================================
void ControlPlayer(void)
{
	//���擾
	Camera *pCamera = GetCamera();

	//�ړ�����======================================================
	if (GetKeyboardRepeat(DIK_UP) == true)
	{//�O�ړ�
		g_player.move.x += sinf(g_player.rot.y + D3DX_PI) * MOVE_SPEED;
		g_player.move.z += cosf(g_player.rot.y + D3DX_PI) * MOVE_SPEED;
	}
	if (GetKeyboardRepeat(DIK_DOWN) == true)
	{//��ړ�
		g_player.move.x += sinf(g_player.rot.y) * MOVE_SPEED;
		g_player.move.z += cosf(g_player.rot.y) * MOVE_SPEED;
	}
	if (GetKeyboardRepeat(DIK_LEFT) == true)
	{//���ړ�
		g_player.move.x += sinf(g_player.rot.y + D3DX_PI * 0.5f) * MOVE_SPEED;
		g_player.move.z += cosf(g_player.rot.y + D3DX_PI * 0.5f) * MOVE_SPEED;
	}
	if (GetKeyboardRepeat(DIK_RIGHT) == true)
	{//�E�ړ�
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

	//�U������======================================================
	if (GetKeyboardTrigger(DIK_SPACE) == true || GetGamePadTrigger(PADBUTTONS_RB,0) == true)
	{//�e����
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

	//�R���g���[���[=============================================
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
	{//�u�[�X�^�[�g�p
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
//�ʒu�X�V����
//==================================================================================================
void UpdatePosPlayer(void)
{
	//�ϐ��錾
	D3DXVECTOR3 move = g_player.move;

	//�ʒu�X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.z += g_player.move.z;

	//�ړ��ʌ���
	g_player.move.x = g_player.move.x * MOVE_FACT;
	g_player.move.z = g_player.move.z * MOVE_FACT;
}

//==================================================================================================
//�ړ���������
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
//�`�揈��
//==================================================================================================
void DrawPlayer(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans,mtxRot2;
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXVECTOR3 posPart,rotPart;

	//���擾
	PlayerPart *pPlayerPart = GetPlayerPart();
	
	for (int nCntPlayer = 0; nCntPlayer < g_nNumPlayerParts; nCntPlayer++)
	{
		//���[���h�}�g���b�N�X������
		D3DXMatrixIdentity(&pPlayerPart[nCntPlayer].mtxWorld);

		if (pPlayerPart[nCntPlayer].nIdxParent != -1)
		{//�e�̃}�g���b�N�X���p��
		}
		else
		{//�S�Ă̐e�p�[�c
			posPart = g_player.pos + pPlayerPart[nCntPlayer].pos;
			rotPart = g_player.rot + pPlayerPart[nCntPlayer].rot;
		}

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			pPlayerPart[nCntPlayer].rot.y, pPlayerPart[nCntPlayer].rot.x, pPlayerPart[nCntPlayer].rot.z);
		D3DXMatrixMultiply(&pPlayerPart[nCntPlayer].mtxWorld, &pPlayerPart[nCntPlayer].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			pPlayerPart[nCntPlayer].pos.x, pPlayerPart[nCntPlayer].pos.y, pPlayerPart[nCntPlayer].pos.z);
		D3DXMatrixMultiply(&pPlayerPart[nCntPlayer].mtxWorld, &pPlayerPart[nCntPlayer].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &pPlayerPart[nCntPlayer].mtxWorld);

		//���݂̃}�e���A���擾
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)pPlayerPart[nCntPlayer].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)pPlayerPart[nCntPlayer].dwNumMat; nCntMat++)
		{
			//�}�e���A���ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�F�ݒ�
			//pMat[nCntMat].MatD3D.Diffuse = {0.0f,0.0f,0.0f,1.0f};

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_apTexturePlayer[nCntPlayer][nCntMat]);

			//���f���i�p�[�c�j�`��
			pPlayerPart[nCntPlayer].pMesh->DrawSubset(nCntMat);
		}

		//�}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//==================================================================================================
//�v���C���[��ԕ`��(�f�o�b�O)
//==================================================================================================
void DrawPlayerState(LPD3DXFONT pFont)
{
	//�ϐ��錾
	RECT rect = { 20,390,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	float fSpeed = sqrtf(g_player.move.x * g_player.move.x + g_player.move.z * g_player.move.z);

	//������ɑ��
	sprintf(&aStr[0], "�v���C���[�̈ʒu[%.2f,%.2f,%.2f]\n�v���C���[�̌���[%.2f,%.2f,%.2f]\n�u�[�X�g�c��[%.2f]  �v���C���[�̑��x[%.2f]", 
		g_player.pos.x, g_player.pos.y, g_player.pos.z,g_player.rot.x, g_player.rot.y, g_player.rot.z,g_player.fBoost, fSpeed);

	//�e�L�X�g�`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//�v���C���[����`��(�f�o�b�O)
//==================================================================================================
void DrawControlPlayer(LPD3DXFONT pFont)
{
	//�ϐ��錾
	RECT rect = { 20,230,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	sprintf(&aStr[0], "�v���C���[�����ړ�[���L�[]\n�e����[SPACE]\n��][L,RSHIFT]");

	//�e�L�X�g�`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================================================================
//�p�[�c��ԕ`��(�f�o�b�O)
//==================================================================================================
void DrawPPartState(LPD3DXFONT pFont)
{
	char aStr[256];

	for (int nCntPart = 0;nCntPart < g_nNumPlayerParts;nCntPart++)
	{
		//�ϐ��錾
		RECT rect = { 1000,20 + 20 * nCntPart,SCREEN_WIDTH,SCREEN_HEIGHT };

		//������ɑ��
		sprintf(&aStr[0], "%d�ԃp�[�c�̈ʒu[%.2f,%.2f,%.2f]",
			nCntPart,g_aPlayerPart[nCntPart].mtxWorld._41, g_aPlayerPart[nCntPart].mtxWorld._42, g_aPlayerPart[nCntPart].mtxWorld._43);

		//�e�L�X�g�`��
		pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}

//==================================================================================================
//�t�@�C���ǂݍ���
//==================================================================================================
void LoadMotion(FILE *pFile)
{
	//���擾
	PlayerPart *pPlayerPart = GetPlayerPart();

	//�ϐ��錾
	char cTemp[MAX_STRING];

	while (1)
	{
		//�����ǂݍ���
		fscanf(pFile, "%s", &cTemp[0]);

		//�t�@�C�����ǂݍ���=========================================
		if (strcmp(cTemp, "NUM_MODEL") == 0)
		{//���f�����ǂݍ���

		    //"="�ǂݍ���
			fscanf(pFile, "%s", &cTemp[0]);

			//���f�����ǂݍ���
			fscanf(pFile, "%d", &g_nNumPlayerParts);

			for (int nCntFile = 0; nCntFile < g_nNumPlayerParts;)
			{//�t�@�C�����ǂݍ���

				fscanf(pFile, "%s", &cTemp[0]);

				if (strcmp(cTemp, "MODEL_FILENAME") == 0)
				{//�t�@�C�����ǂݍ���
					fscanf(pFile, "%s", &cTemp[0]);

					fscanf(pFile, "%s", &g_acFilenamePlayer[nCntFile][0]);

					nCntFile++;
				}
			}
		}
		//===========================================================

		//�L�����N�^�[�ݒ�===========================================
		if (strcmp(cTemp, "CHARACTERSET") == 0)
		{//�L�����N�^�[�X�^�[�g
			while (strcmp(cTemp, "END_CHARACTERSET") != 0)
			{//�I���܂ŃL�����N�^�[�ݒ�
				fscanf(pFile, "%s", &cTemp[0]);

				if (strcmp(cTemp, "PARTSSET") == 0)
				{//�p�[�c�X�^�[�g
					while (strcmp(cTemp, "END_PARTSSET") != 0)
					{//�I���܂Ńp�[�c�ݒ�
						fscanf(pFile, "%s", &cTemp[0]);

						if (strcmp(cTemp, "INDEX") == 0)
						{//�ԍ��ǂݍ���
							fscanf(pFile, "%s", &cTemp[0]);

							fscanf(pFile, "%d", &pPlayerPart->nIdx);
						}

						if (strcmp(cTemp, "PARENT") == 0)
						{//�e�ԍ��ǂݍ���
							fscanf(pFile, "%s", &cTemp[0]);

							fscanf(pFile, "%d", &pPlayerPart->nIdxParent);
						}

						if (strcmp(cTemp, "POS") == 0)
						{//�ʒu�ǂݍ���
							fscanf(pFile, "%s", &cTemp[0]);

							for (int nCntPos = 0; nCntPos < 3; nCntPos++)
							{
								fscanf(pFile, "%f", &pPlayerPart->pos[nCntPos]);
							}
						}

						if (strcmp(cTemp, "ROT") == 0)
						{//�����ǂݍ���
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
	}//while��
}

//==================================================================================================
//���擾
//==================================================================================================
Player *GetPlayer(void)
{
	return &g_player;
}

//==================================================================================================
//���擾
//==================================================================================================
PlayerPart *GetPlayerPart(void)
{
	return &g_aPlayerPart[0];
}