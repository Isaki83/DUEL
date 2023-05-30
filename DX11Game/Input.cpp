//=======================================================================================
//
// ���͏��� [Input.cpp]
// Author : ISAKI SUGIURA
//
//=======================================================================================
#include "Input.h"

//����������������������������������������
// �O���[�o���ϐ�
//����������������������������������������
namespace 
{
	const int	g_nMouseBtn[] = { VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON2 };
};

//����������������������������������������
// �ÓI�����o�ϐ�
//����������������������������������������
WORD		CInput::m_wKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̉�����Ԃ�ێ����郏�[�N
WORD		CInput::m_wKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K��Ԃ�ێ����郏�[�N
WORD		CInput::m_wKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X��Ԃ�ێ����郏�[�N
WORD		CInput::m_wKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g��Ԃ�ێ����郏�[�N
int			CInput::m_nKeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^

DWORD		CInput::m_dwJoyCount;
JOYINFOEX	CInput::m_joyState[NUM_JOY_MAX];
DWORD		CInput::m_dwJoyButtonTrigger[NUM_JOY_MAX];
DWORD		CInput::m_dwJoyButtonRelease[NUM_JOY_MAX];
bool		CInput::m_dwJoyCrossState[MAX_JOYCROSS][2] = { {false,false},{false,false},{false,false},{false,false} };	// trigger,Release����p(0�����A1���O)
int			CInput::m_dwJoyCrossAngle[MAX_JOYCROSS][NUM_JOYCROSS_ANGLE] = { {0,45,315},{135,180,225},{225,270,315},{45,90,135} };

POINT		CInput::m_ptClientMouse;
POINT		CInput::m_ptTopLeftWindow;
POINT		CInput::m_ptBottonRightWindow;


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CInput::Init()
{
	HRESULT hr = S_OK;

	// �L�[�{�[�h�̏�����
	hr = InitKeyboard();

	// �R���g���[���[�̏�����
	if (SUCCEEDED(hr)) { hr = InitJoystick(); }

	// �}�E�X�̏�����
	if (SUCCEEDED(hr)) { hr = InitMouse(); }

	return hr;
}


/*������������������������������������������������������������������������������

	�I��

������������������������������������������������������������������������������*/
void CInput::Fin()
{
	// �}�E�X�̏I������
	UninitMouse();

	// �R���g���[���[�̏I������
	UninitJoystick();

	// �L�[�{�[�h�̏I������
	UninitKeyboard();
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CInput::Update()
{
	// �L�[�{�[�h�̍X�V
	UpdateKeyboard();

	// �R���g���[���[�̍X�V
	UpdateJoystick();

	// �}�E�X�̍X�V
	UpdateMouse();
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	�L�[�{�[�h
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CInput::InitKeyboard()
{
	HRESULT hr = S_OK;

	return hr;
}


/*������������������������������������������������������������������������������

	�I��

������������������������������������������������������������������������������*/
void CInput::UninitKeyboard(void)
{
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
HRESULT CInput::UpdateKeyboard(void)
{
	HRESULT hr = S_OK;
	WORD wKeyState;

	// �L�[�{�[�h�̏�Ԃ��擾
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++) 
	{
		wKeyState = GetAsyncKeyState(nCntKey);

		m_wKeyStateTrigger[nCntKey] = (m_wKeyState[nCntKey] ^ wKeyState) & wKeyState;
		m_wKeyStateRelease[nCntKey] = (m_wKeyState[nCntKey] ^ wKeyState) & ~wKeyState;
		m_wKeyStateRepeat[nCntKey] = m_wKeyStateTrigger[nCntKey];

		if (wKeyState & 0x8000) 
		{
			m_nKeyStateRepeatCnt[nCntKey]++;
			if (m_nKeyStateRepeatCnt[nCntKey] >= 20) { m_wKeyStateRepeat[nCntKey] = wKeyState; }
		} 
		else 
		{
			m_nKeyStateRepeatCnt[nCntKey] = 0;
			m_wKeyStateRepeat[nCntKey] = 0;
		}

		m_wKeyState[nCntKey] = wKeyState;
	}

	return hr;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	�R���g���[���[
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CInput::InitJoystick()
{
	GetJoyCount();

	return S_OK;
}


/*������������������������������������������������������������������������������

	�I��

������������������������������������������������������������������������������*/
void CInput::UninitJoystick()
{
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
HRESULT CInput::UpdateJoystick()
{
	HRESULT hr = S_OK;

	for (DWORD i = 0; i < m_dwJoyCount; ++i) 
	{
		JOYINFOEX& ji = m_joyState[i];
		DWORD dwButtons = ji.dwButtons;
		ZeroMemory(&ji, sizeof(ji));
		ji.dwSize = sizeof(ji);
		ji.dwFlags = JOY_RETURNALL;
		if (joyGetPosEx(i, &ji) != JOYERR_NOERROR) 
		{
			hr = E_FAIL;
			break;
		}
		m_dwJoyButtonTrigger[i] = (m_joyState[i].dwButtons ^ dwButtons) & dwButtons;
		m_dwJoyButtonRelease[i] = (m_joyState[i].dwButtons ^ dwButtons) & ~dwButtons;

	}
	for (DWORD i = 0; i < MAX_JOYCROSS; ++i)
	{
		m_dwJoyCrossState[i][1] = m_dwJoyCrossState[i][0];
	}

	return hr;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	�}�E�X
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CInput::InitMouse()
{
	return S_OK;
}


/*������������������������������������������������������������������������������

	�I��

������������������������������������������������������������������������������*/
void CInput::UninitMouse()
{
}

//=============================================================================
// �}�E�X�̍X�V����
//=============================================================================
HRESULT CInput::UpdateMouse()
{
	extern HWND g_hWnd;	// main.cpp

	POINT ptClient;
	GetCursorPos(&ptClient);
	ScreenToClient(g_hWnd, &ptClient);
	m_ptClientMouse = ptClient;

	RECT re;
	GetWindowRect(g_hWnd, &re);
	m_ptTopLeftWindow.x = re.left;
	m_ptTopLeftWindow.y = re.top;
	m_ptBottonRightWindow.x = re.right;
	m_ptBottonRightWindow.y = re.bottom;
	return S_OK;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	�L�[�{�[�h
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*������������������������������������������������������������������������������

	�v���X��Ԃ��擾

������������������������������������������������������������������������������*/
bool CInput::GetKeyPress(int nKey)
{
	return (m_wKeyState[nKey] & 0x8000) ? true : false;
}


/*������������������������������������������������������������������������������

	�g���K��Ԃ��擾

������������������������������������������������������������������������������*/
bool CInput::GetKeyTrigger(int nKey)
{
	return (m_wKeyStateTrigger[nKey] & 0x8000) ? true : false;
}


/*������������������������������������������������������������������������������

	���s�[�g��Ԃ��擾

������������������������������������������������������������������������������*/
bool CInput::GetKeyRepeat(int nKey)
{
	return (m_wKeyStateRepeat[nKey] & 0x8000) ? true : false;
}


/*������������������������������������������������������������������������������

	�����|�X��Ԃ��擾

������������������������������������������������������������������������������*/
bool CInput::GetKeyRelease(int nKey)
{
	return (m_wKeyStateRelease[nKey] & 0x8000) ? true : false;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	�R���g���[���[
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*������������������������������������������������������������������������������

	�ڑ����擾

������������������������������������������������������������������������������*/
DWORD CInput::GetJoyCount()
{
	JOYINFO	ji;
	DWORD dwCount = joyGetNumDevs();
	if (dwCount > NUM_JOY_MAX) { dwCount = NUM_JOY_MAX; }
	for (m_dwJoyCount = 0; m_dwJoyCount < dwCount; ++m_dwJoyCount) 
	{ if (joyGetPos(m_dwJoyCount, &ji) != JOYERR_NOERROR) { break; } }
	return m_dwJoyCount;
}


/*������������������������������������������������������������������������������

	���擾

������������������������������������������������������������������������������*/
JOYINFOEX* CInput::GetJoyState(DWORD dwJoy)
{
	if (dwJoy >= NUM_JOY_MAX) { return nullptr; }
	return &m_joyState[dwJoy];
}


/*������������������������������������������������������������������������������

	�X�e�B�b�N�X���Ă�������擾
	�c�� : Vertical
	���� : Horizontal

������������������������������������������������������������������������������*/
bool CInput::GetJoyLeftState(DWORD dwJoy)
{
	LONG X, Y;
	X = GetJoyLeftX(dwJoy);
	Y = GetJoyLeftY(dwJoy);

	if (X * X + Y * Y >= JOY_MIN_RANGE * JOY_MIN_RANGE) { return true; }
	return false;
}
bool CInput::GetJoyRightState(DWORD dwJoy)
{
	LONG X, Y;
	X = GetJoyRightX(dwJoy);
	Y = GetJoyRightY(dwJoy);

	if (X * X + Y * Y >= JOY_MIN_RANGE * JOY_MIN_RANGE) { return true; }
	return false;
}
XMFLOAT2 CInput::GetJoyLeftStick(DWORD dwJoy)
{
	LONG X, Y;
	X = GetJoyLeftX(dwJoy);
	Y = GetJoyLeftY(dwJoy);
	
	float Vertical = fabsf(atan2f(X, -Y)) - 1.5f;
	float Horizontal = fabsf(atan2f(Y, -X)) - 1.5f;

	return XMFLOAT2(Horizontal, Vertical);
}
XMFLOAT2 CInput::GetJoyRightStick(DWORD dwJoy)
{
	LONG X, Y;
	X = GetJoyRightX(dwJoy);
	Y = GetJoyRightY(dwJoy);

	float Vertical = fabsf(atan2f(-X, -Y)) - 1.5f;
	float Horizontal = fabsf(atan2f(-Y, -X)) - 1.5f;

	return XMFLOAT2(Horizontal, Vertical);
}


/*������������������������������������������������������������������������������

	�X�e�B�b�N��X���擾

������������������������������������������������������������������������������*/
LONG CInput::GetJoyLeftX(DWORD dwJoy)
{
	if (dwJoy >= NUM_JOY_MAX) { return 0L; }
	return (LONG)m_joyState[dwJoy].dwXpos - 0x08000;
}
LONG CInput::GetJoyRightX(DWORD dwJoy)
{
	if (dwJoy >= NUM_JOY_MAX) return 0L;
	return (LONG)m_joyState[dwJoy].dwUpos - 0x08000;
}


/*������������������������������������������������������������������������������

	�X�e�B�b�N��Y���擾

������������������������������������������������������������������������������*/
LONG CInput::GetJoyLeftY(DWORD dwJoy)
{
	if (dwJoy >= NUM_JOY_MAX) { return 0L; }
	return (LONG)m_joyState[dwJoy].dwYpos - 0x08000;
}
LONG CInput::GetJoyRightY(DWORD dwJoy)
{
	if (dwJoy >= NUM_JOY_MAX) return 0L;
	return (LONG)m_joyState[dwJoy].dwRpos - 0x08000;
}


/*������������������������������������������������������������������������������

	�X�e�B�b�N�̌X���擾

������������������������������������������������������������������������������*/
XMFLOAT2 CInput::GetJoyLeftSlope(DWORD dwJoy)
{
	int X = (int)CInput::GetJoyLeftX(dwJoy);
	int Y = (int)CInput::GetJoyLeftY(dwJoy);

	return XMFLOAT2(fabsf((float)X / JOY_MAX_SLOPE), fabsf((float)Y / JOY_MAX_SLOPE));
}
XMFLOAT2 CInput::GetJoyRightSlope(DWORD dwJoy)
{
	int X = (int)CInput::GetJoyRightX(dwJoy);
	int Y = (int)CInput::GetJoyRightY(dwJoy);

	return XMFLOAT2(fabsf((float)X / JOY_MAX_SLOPE), fabsf((float)Y / JOY_MAX_SLOPE));
}


/*������������������������������������������������������������������������������

	LT / RT �{�^��

������������������������������������������������������������������������������*/
bool CInput::GetJoyRTorLT(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= NUM_JOY_MAX) { return 0L; }
	LONG Triger = (LONG)m_joyState[dwJoy].dwZpos - 0x08000;
	if (dwBtn == 0) { return (Triger > 0) ? true : false; }
	if (dwBtn == 1) { return (Triger <= 0) ? true : false; }
	return false;
}


/*������������������������������������������������������������������������������

	�{�^�����擾

������������������������������������������������������������������������������*/
bool CInput::GetJoyButton(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= NUM_JOY_MAX) { return false; }
	return (m_joyState[dwJoy].dwButtons & (1 << dwBtn)) ? true : false;
}


/*������������������������������������������������������������������������������

	�g���K���擾

������������������������������������������������������������������������������*/
bool CInput::GetJoyTrigger(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= NUM_JOY_MAX) { return false; }
	return (m_dwJoyButtonRelease[dwJoy] & (1 << dwBtn)) ? true : false;
}


/*������������������������������������������������������������������������������

	�����[�X���擾

������������������������������������������������������������������������������*/
bool CInput::GetJoyRelease(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= NUM_JOY_MAX) { return false; }
	return (m_dwJoyButtonTrigger[dwJoy] & (1 << dwBtn)) ? true : false;
}


/*������������������������������������������������������������������������������

	�\�� �{�^�����擾

������������������������������������������������������������������������������*/
bool CInput::GetJoyCrossState(DWORD dwJoy)
{
	if (dwJoy >= NUM_JOY_MAX) { return false; }
	if (m_joyState[dwJoy].dwPOV == 65535)
	{
		for (int i = 0; i < MAX_JOYCROSS; i++) { m_dwJoyCrossState[i][0] = false; }
		return false;
	}
	return true;
}


/*������������������������������������������������������������������������������

	�\�� �{�^�����擾	Press

������������������������������������������������������������������������������*/
bool CInput::GetJoyCross(DWORD dwJoy, DWORD dwPad)
{
	if (dwJoy >= NUM_JOY_MAX) { return false; }

	DWORD dwAngel = m_joyState[dwJoy].dwPOV / 100;
	for (int i = 0; i < MAX_JOYCROSS; i++)
	{ if (dwAngel == m_dwJoyCrossAngle[dwPad][i]) { return true; } }
	return false;
}


/*������������������������������������������������������������������������������

	�\�� �{�^�����擾	Trigger

������������������������������������������������������������������������������*/
bool CInput::GetJoyCrossTrigger(DWORD dwJoy, DWORD dwPad)
{
	if (dwJoy >= NUM_JOY_MAX) { return false; }
	if (!GetJoyCrossState(dwJoy)) { return false; }

	m_dwJoyCrossState[dwPad][0] = true;

	DWORD dwAngel = m_joyState[dwJoy].dwPOV / 100;
	for (int i = 0; i < MAX_JOYCROSS; i++)
	{
		if (dwAngel == m_dwJoyCrossAngle[dwPad][i])
		{
			if (!m_dwJoyCrossState[dwPad][1]) { return true; }
			else { return false; }
		}
	}
	m_dwJoyCrossState[dwPad][0] = false;
	return false;
}


/*������������������������������������������������������������������������������

	�R���g���[���[ �\�� �{�^�����擾	Release
	����

������������������������������������������������������������������������������*/
bool CInput::GetJoyCrossRelease(DWORD dwJoy, DWORD dwPad)
{
	/*if (dwJoy >= NUM_JOY_MAX) { return false; }
	if (!GetJoyCrossState(dwJoy) && !m_dwJoyCrossState[dwPad][1]) { return false; }

	m_dwJoyCrossState[dwPad][0] = true;

	DWORD dwAngel = m_joyState[dwJoy].dwPOV / 100;
	for (int i = 0; i < MAX_JOYCROSS; i++)
	{ if (dwAngel == m_dwJoyCrossAngle[dwPad][i]) { if (m_dwJoyCrossState[dwPad][0] && m_dwJoyCrossState[dwPad][1]) { return false; } } }
	m_dwJoyCrossState[dwPad][0] = false;
	if (!m_dwJoyCrossState[dwPad][0] && m_dwJoyCrossState[dwPad][1]) { return true; }*/
	return false;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	�R���g���[���[
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*������������������������������������������������������������������������������

	�N���C�A���g���W�擾

������������������������������������������������������������������������������*/
POINT* CInput::GetMouseClientPosition()
{
	return &m_ptClientMouse;
}


/*������������������������������������������������������������������������������

	�X�N���[���̈�ł̃E�B���h�E�̍��W�擾

������������������������������������������������������������������������������*/
// ����
POINT* CInput::GetWindowTLPosition()
{
	return &m_ptTopLeftWindow;
}
// �E��
POINT* CInput::GetWindowBRPosition()
{
	return &m_ptBottonRightWindow;
}


/*������������������������������������������������������������������������������

	�{�^�����擾

������������������������������������������������������������������������������*/
bool CInput::GetMouseButton(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_nMouseBtn)) { return false; }
	return GetKeyPress(g_nMouseBtn[dwBtn]);
}


/*������������������������������������������������������������������������������

	�g���K���擾

������������������������������������������������������������������������������*/
bool CInput::GetMouseTrigger(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_nMouseBtn)) { return false; }
	return GetKeyTrigger(g_nMouseBtn[dwBtn]);
}


/*������������������������������������������������������������������������������

	�����[�X���擾

������������������������������������������������������������������������������*/
bool CInput::GetMouseRelease(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_nMouseBtn)) { return false; }
	return GetKeyRelease(g_nMouseBtn[dwBtn]);
}
