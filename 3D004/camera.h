//==================================================================================================
//
//camera.h
//Author:���R����
//
//==================================================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

//�}�N����`
#define MIN_DRAW		(10.0f)					//�`����J�n���鋗��
#define MAX_DRAW		(10000.0f)				//�`����I�����鋗��

//�񋓌^�錾
typedef enum
{
	CAMERA_MODE_CHASE = 0,						//�Ǐ]���[�h
	CAMERA_MODE_CONTROL,						//���샂�[�h
	CAMERA_MODE_AUTO,							//��荞�݃��[�h
	CAMERA_MODE_MAX
}CAMERA_MODE;

//�\���̐錾
typedef struct
{
	D3DXVECTOR3 posV;							//���_
	D3DXVECTOR3 posR;							//�����_
	D3DXVECTOR3 posVDest;						//�ړI�̎��_
	D3DXVECTOR3 posRDest;						//�ړI�̒����_
	D3DXVECTOR3 vecU;							//������x�N�g��
	D3DXVECTOR3 rot;							//����
	float fLength;								//���_���璍���_�܂ł̋���
	D3DXMATRIX mtxProjection;					//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;							//�r���[�}�g���b�N�X
	int nCounterWrap;							//�J��������荞�ނ܂ł̃J�E���^
	int nTimerWrap;								//�J��������荞�ނ܂ł̎���
}Camera;

//�v���g�^�C�v�錾
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera *GetCamera(void);
void DrawCameraState(LPD3DXFONT pFont);
void DrawCameraControl(LPD3DXFONT pFont);
void DrawCameraMode(LPD3DXFONT pFont);
#endif