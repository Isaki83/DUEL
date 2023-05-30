//=======================================================================================
//
// �C���v�b�g [Input.h]
// Author : ISAKI SUGIURA
//
//=======================================================================================
#pragma once
#include "main.h"

//����������������������������������������
// �}�N����`
//����������������������������������������
// �L�[�{�[�h
#define	NUM_KEY_MAX		(256)				// �L�[�ő吔

#define VK_0			'0'
#define VK_1			'1'
#define VK_2			'2'
#define VK_3			'3'
#define VK_4			'4'
#define VK_5			'5'
#define VK_6			'6'
#define VK_7			'7'
#define VK_8			'8'
#define VK_9			'9'
#define VK_A			'A'
#define VK_B			'B'
#define VK_C			'C'
#define VK_D			'D'
#define VK_E			'E'
#define VK_F			'F'
#define VK_G			'G'
#define VK_H			'H'
#define VK_I			'I'
#define VK_J			'J'
#define VK_K			'K'
#define VK_L			'L'
#define VK_M			'M'
#define VK_N			'N'
#define VK_O			'O'
#define VK_P			'P'
#define VK_Q			'Q'
#define VK_R			'R'
#define VK_S			'S'
#define VK_T			'T'
#define VK_U			'U'
#define VK_V			'V'
#define VK_W			'W'
#define VK_X			'X'
#define VK_Y			'Y'
#define VK_Z			'Z'

// �R���g���[���[
#define NUM_JOY_MAX		(32)				// �Q�[���p�b�h�ő吔
#define JOY_MIN_RANGE	(5000)
#define JOY_MAX_SLOPE	(32768.0f)

#define JOYBUTTON_RT	(0)
#define JOYBUTTON_LT	(1)

#define JOYBUTTON_A		(0)
#define JOYBUTTON_B		(1)
#define JOYBUTTON_X		(2)
#define JOYBUTTON_Y		(3)
#define JOYBUTTON_LB	(4)
#define JOYBUTTON_RB	(5)
#define JOYBUTTON_BACK	(6)
#define JOYBUTTON_START	(7)
#define JOYBUTTON_LS	(8)
#define JOYBUTTON_RS	(9)

#define MAX_JOYCROSS		(4)
#define NUM_JOYCROSS_ANGLE	(3)

#define JOYCROSS_UP		(0)
#define JOYCROSS_DOWN	(1)
#define JOYCROSS_LEFT	(2)
#define JOYCROSS_RIGHT	(3)

// �}�E�X
#define MOUSEBUTTON_L	(0)
#define MOUSEBUTTON_R	(1)
#define MOUSEBUTTON_M	(2)
#define MOUSEBUTTON_X1	(3)
#define MOUSEBUTTON_X2	(4)


//����������������������������������������
// ���͏��� �N���X
//����������������������������������������
class CInput
{
private:
	static WORD			m_wKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̉�����Ԃ�ێ����郏�[�N
	static WORD			m_wKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K��Ԃ�ێ����郏�[�N
	static WORD			m_wKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X��Ԃ�ێ����郏�[�N
	static WORD			m_wKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g��Ԃ�ێ����郏�[�N
	static int			m_nKeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^

	static DWORD		m_dwJoyCount;
	static JOYINFOEX	m_joyState[NUM_JOY_MAX];
	static DWORD		m_dwJoyButtonTrigger[NUM_JOY_MAX];
	static DWORD		m_dwJoyButtonRelease[NUM_JOY_MAX];
	static bool			m_dwJoyCrossState[MAX_JOYCROSS][2];
	static int			m_dwJoyCrossAngle[MAX_JOYCROSS][NUM_JOYCROSS_ANGLE];
	static POINT		m_ptClientMouse;					// �}�E�X�̃N���C�A���g���W
	static POINT		m_ptTopLeftWindow;					// �E�B���h�E�̍���̍��W
	static POINT		m_ptBottonRightWindow;				// �E�B���h�E�̉E���̍��W

public:
	static HRESULT Init();
	static void Fin();
	static void Update();

	//����������������������������������������
	// �L�[�{�[�h
	//����������������������������������������
	static bool GetKeyPress(int nKey);
	static bool GetKeyTrigger(int nKey);
	static bool GetKeyRelease(int nKey);
	static bool GetKeyRepeat(int nKey);

	//����������������������������������������
	// �R���g���[���[
	//����������������������������������������
	static DWORD GetJoyCount();
	static JOYINFOEX *GetJoyState(DWORD dwJoy);
	// �f�X�]�[��
	static bool GetJoyLeftState(DWORD dwJoy);
	static bool GetJoyRightState(DWORD dwJoy);
	// �X�e�B�b�N
	static XMFLOAT2 GetJoyLeftStick(DWORD dwJoy);
	static XMFLOAT2 GetJoyRightStick(DWORD dwJoy);
	static LONG GetJoyLeftX(DWORD dwJoy);
	static LONG GetJoyRightX(DWORD dwJoy);
	static LONG GetJoyLeftY(DWORD dwJoy);
	static LONG GetJoyRightY(DWORD dwJoy);
	static XMFLOAT2 GetJoyLeftSlope(DWORD dwJoy);
	static XMFLOAT2 GetJoyRightSlope(DWORD dwJoy);
	// �{�^��
	static bool GetJoyRTorLT(DWORD dwJoy, DWORD dwBtn);
	static bool GetJoyButton(DWORD dwJoy, DWORD dwBtn);
	static bool GetJoyTrigger(DWORD dwJoy, DWORD dwBtn);
	static bool GetJoyRelease(DWORD dwJoy, DWORD dwBtn);
	static bool GetJoyCrossState(DWORD dwJoy);
	static bool GetJoyCross(DWORD dwJoy, DWORD dwPad);
	static bool GetJoyCrossTrigger(DWORD dwJoy, DWORD dwPad);
	static bool GetJoyCrossRelease(DWORD dwJoy, DWORD dwPad);

	//����������������������������������������
	// �}�E�X
	//����������������������������������������
	static POINT *GetMouseClientPosition();
	static POINT *GetWindowTLPosition();
	static POINT *GetWindowBRPosition();
	static bool GetMouseButton(DWORD dwBtn);
	static bool GetMouseTrigger(DWORD dwBtn);
	static bool GetMouseRelease(DWORD dwBtn);

private:
	static HRESULT InitKeyboard();
	static void UninitKeyboard();
	static HRESULT UpdateKeyboard();

	static HRESULT InitJoystick();
	static void UninitJoystick();
	static HRESULT UpdateJoystick();

	static HRESULT InitMouse();
	static void UninitMouse();
	static HRESULT UpdateMouse();
};