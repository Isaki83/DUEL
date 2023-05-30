//=============================================================================
//
// �}�l�[�W���[ [Manager.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "main.h"
#include "Manager.h"
#include "Input.h"


//����������������������������������������
// �O���[�o���ϐ�
//����������������������������������������
namespace
{
	int g_FrameCount;

	float g_WindowWidth;		// �E�B���h�E�̉���
	float g_WindowHeight;		// �E�B���h�E�̏c��

	int	g_iCursor;				// �}�E�X�J�[�\����\���ؑ֗p
	POINT g_MouseScreenPos;		// �}�E�X�̃X�N���[�����W
	POINT g_MouseClientPos;		// �}�E�X�̃N���C�A���g���W
	XMFLOAT2 g_MouseMovement;	// �}�E�X�̈ړ���
}


/*������������������������������������������������������������������������������

	�X�N���[�����W�ł̃E�B���h�E�̍���ƉE���̍��W��Ԃ�
	Top,Left,Bottom,Right

������������������������������������������������������������������������������*/
XMFLOAT4 GetWindowTLBR()
{
	// �X�N���[����ł̃E�B���h�E�̍��W�擾
	// ����
	POINT windowTL = *CInput::GetWindowTLPosition();
	// �E��
	POINT windowBR = *CInput::GetWindowBRPosition();

	return XMFLOAT4((float)windowTL.x, (float)windowTL.y, (float)windowBR.x, (float)windowBR.y);
}


/*������������������������������������������������������������������������������

	�E�B���h�E�̏c���A�������擾����

������������������������������������������������������������������������������*/
XMFLOAT2 GetWindowSize()
{
	// ����
	g_WindowWidth = GetWindowTLBR().z - GetWindowTLBR().x;
	// �c��
	g_WindowHeight = GetWindowTLBR().w - GetWindowTLBR().y;

	return XMFLOAT2(g_WindowWidth, g_WindowHeight);
}


/*������������������������������������������������������������������������������

	�}�E�X�J�[�\���\���ؑ�

������������������������������������������������������������������������������*/
void SetShowCursor(bool show)
{
	switch (show)
	{
	case true:
		do
		{
			g_iCursor = ShowCursor(true);
		} while (g_iCursor <= 0);
		break;

	case false:
		do
		{
			g_iCursor = ShowCursor(false);
		} while (g_iCursor >= 0);
		break;

	default:
		break;
	}
}

 
/*������������������������������������������������������������������������������

	�}�E�X�̃X�N���[�����W���擾

������������������������������������������������������������������������������*/
XMFLOAT2 GetMouseScreenPos()
{
	GetCursorPos(&g_MouseScreenPos);
	return XMFLOAT2((float)g_MouseScreenPos.x, (float)g_MouseScreenPos.y);
}


/*������������������������������������������������������������������������������

	�}�E�X�̃N���C�A���g���W���擾

������������������������������������������������������������������������������*/
XMFLOAT2 GetMouseClientPos()
{
//	g_MouseClientPos = *CInput::GetMouseClientPosition();
	g_MouseClientPos.x = GetMouseScreenPos().x - GetWindowTLBR().y;
	g_MouseClientPos.y = GetMouseScreenPos().y - GetWindowTLBR().x;
	return XMFLOAT2((float)g_MouseClientPos.x, (float)g_MouseClientPos.y);
}


/*������������������������������������������������������������������������������

	�}�E�X���E�B���h�E�̒��S�ɌŒ肷��

������������������������������������������������������������������������������*/
void SetMouseMiddlePos()
{
	g_FrameCount++;
	if (g_FrameCount > 2)
	{
		SetCursorPos(GetWindowTLBR().y + GetWindowSize().x / 2.0f,
			GetWindowTLBR().x + GetWindowSize().y / 2.0f);
		g_FrameCount = 0;
	}
}


/*������������������������������������������������������������������������������

	�}�E�X�̈ړ��ʂ��擾����

������������������������������������������������������������������������������*/
XMFLOAT2 GetMouseMovement()
{
	g_MouseMovement.x = GetMouseClientPos().x - GetWindowSize().x / 2.0f;
	g_MouseMovement.y = GetMouseClientPos().y - GetWindowSize().y / 2.0f;
	return XMFLOAT2(g_MouseMovement.x, g_MouseMovement.y);
}