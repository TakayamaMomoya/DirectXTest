//==================================================================================================
//
//main.h
//Author:���R����
//
//==================================================================================================

#ifndef _MAIN_H_
#define _MAIN_H_
#include <windows.h>
#include"d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)						//�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"
#include "xaudio2.h"

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);

//���C�u����
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")

//���(���[�h)�̐ݒ�
typedef enum
{
	MODE_TITLE = 0,						//�^�C�g�����
	MODE_TUTORIAL,						//�`���[�g���A�����
	MODE_MENU,							//���j���[���
	MODE_GAME,							//�Q�[�����
	MODE_RESULT,						//���ʉ��
	MODE_RANKING,						//�����L���O���
	MODE_MAX
}MODE;

//�}�N����`
#define SCREEN_WIDTH			(1280)															//�E�B���h�E�̕�
#define SCREEN_HEIGHT			(720)															//�E�B���h�E�̍���
#define FVF_VERTEX_2D			(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)					//���_�t�H�[�}�b�g�ݒ�
#define FVF_VERTEX_3D			(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//���_�t�H�[�}�b�g�ݒ�
#define CLASS_NAME				"WindowClass"													//�E�B���h�E�N���X�̖��O
#define GRAVITY					(0.98f)															//�d�͉����x
#define NUM_STG					(3)																//�X�e�[�W�̐�
	
//���_���QD�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;			//���_���W
	float rhw;					//���W�ϊ��p�W���i�P�D�O���ŌŒ�j
	D3DCOLOR col;				//���_�J���[
	D3DXVECTOR2 tex;			//�e�N�X�`�����W
}VERTEX_2D;

//���_���[�RD]�̍\����
typedef struct
{
	D3DXVECTOR3 pos;			//���_���W
	D3DXVECTOR3 nor;			//�@���x�N�g��
	D3DCOLOR col;				//���_�J���[
	D3DXVECTOR2 tex;			//�e�N�X�`�����W
}VERTEX_3D;

//�v���g�^�C�v�錾
void SetMode(MODE mode);
void LimitRot(D3DXVECTOR3 *rot);
DWORD GetAlphaThreshold(void);
bool CrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 PrVtx, D3DXVECTOR3 ScVtx);
bool SqrCrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax);
void WallCrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 *pos, D3DXVECTOR3 *move, D3DXVECTOR3 PrVtx, D3DXVECTOR3 ScVtx,float width);
#endif