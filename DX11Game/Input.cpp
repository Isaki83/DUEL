//=======================================================================================
//
// 入力処理 [Input.cpp]
// Author : ISAKI SUGIURA
//
//=======================================================================================
#include "Input.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// グローバル変数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
namespace 
{
	const int	g_nMouseBtn[] = { VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON2 };
};

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 静的メンバ変数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
WORD		CInput::m_wKeyState[NUM_KEY_MAX];			// キーボードの押下状態を保持するワーク
WORD		CInput::m_wKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガ状態を保持するワーク
WORD		CInput::m_wKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース状態を保持するワーク
WORD		CInput::m_wKeyStateRepeat[NUM_KEY_MAX];		// キーボードのリピート状態を保持するワーク
int			CInput::m_nKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ

DWORD		CInput::m_dwJoyCount;
JOYINFOEX	CInput::m_joyState[NUM_JOY_MAX];
DWORD		CInput::m_dwJoyButtonTrigger[NUM_JOY_MAX];
DWORD		CInput::m_dwJoyButtonRelease[NUM_JOY_MAX];
bool		CInput::m_dwJoyCrossState[MAX_JOYCROSS][2] = { {false,false},{false,false},{false,false},{false,false} };	// trigger,Release判定用(0が今、1が前)
int			CInput::m_dwJoyCrossAngle[MAX_JOYCROSS][NUM_JOYCROSS_ANGLE] = { {0,45,315},{135,180,225},{225,270,315},{45,90,135} };

POINT		CInput::m_ptClientMouse;
POINT		CInput::m_ptTopLeftWindow;
POINT		CInput::m_ptBottonRightWindow;


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT CInput::Init()
{
	HRESULT hr = S_OK;

	// キーボードの初期化
	hr = InitKeyboard();

	// コントローラーの初期化
	if (SUCCEEDED(hr)) { hr = InitJoystick(); }

	// マウスの初期化
	if (SUCCEEDED(hr)) { hr = InitMouse(); }

	return hr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	終了

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CInput::Fin()
{
	// マウスの終了処理
	UninitMouse();

	// コントローラーの終了処理
	UninitJoystick();

	// キーボードの終了処理
	UninitKeyboard();
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CInput::Update()
{
	// キーボードの更新
	UpdateKeyboard();

	// コントローラーの更新
	UpdateJoystick();

	// マウスの更新
	UpdateMouse();
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	キーボード
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT CInput::InitKeyboard()
{
	HRESULT hr = S_OK;

	return hr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	終了

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CInput::UninitKeyboard(void)
{
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT CInput::UpdateKeyboard(void)
{
	HRESULT hr = S_OK;
	WORD wKeyState;

	// キーボードの状態を取得
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
	コントローラー
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT CInput::InitJoystick()
{
	GetJoyCount();

	return S_OK;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	終了

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CInput::UninitJoystick()
{
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
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
	マウス
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT CInput::InitMouse()
{
	return S_OK;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	終了

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CInput::UninitMouse()
{
}

//=============================================================================
// マウスの更新処理
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
	キーボード
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	プレス状態を取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CInput::GetKeyPress(int nKey)
{
	return (m_wKeyState[nKey] & 0x8000) ? true : false;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	トリガ状態を取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CInput::GetKeyTrigger(int nKey)
{
	return (m_wKeyStateTrigger[nKey] & 0x8000) ? true : false;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	リピート状態を取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CInput::GetKeyRepeat(int nKey)
{
	return (m_wKeyStateRepeat[nKey] & 0x8000) ? true : false;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	リリ－ス状態を取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CInput::GetKeyRelease(int nKey)
{
	return (m_wKeyStateRelease[nKey] & 0x8000) ? true : false;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	コントローラー
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	接続数取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
DWORD CInput::GetJoyCount()
{
	JOYINFO	ji;
	DWORD dwCount = joyGetNumDevs();
	if (dwCount > NUM_JOY_MAX) { dwCount = NUM_JOY_MAX; }
	for (m_dwJoyCount = 0; m_dwJoyCount < dwCount; ++m_dwJoyCount) 
	{ if (joyGetPos(m_dwJoyCount, &ji) != JOYERR_NOERROR) { break; } }
	return m_dwJoyCount;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	情報取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
JOYINFOEX* CInput::GetJoyState(DWORD dwJoy)
{
	if (dwJoy >= NUM_JOY_MAX) { return nullptr; }
	return &m_joyState[dwJoy];
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	スティック傾けている方向取得
	縦軸 : Vertical
	横軸 : Horizontal

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
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


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	スティックのX軸取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
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


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	スティックのY軸取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
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


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	スティックの傾き取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
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


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	LT / RT ボタン

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CInput::GetJoyRTorLT(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= NUM_JOY_MAX) { return 0L; }
	LONG Triger = (LONG)m_joyState[dwJoy].dwZpos - 0x08000;
	if (dwBtn == 0) { return (Triger > 0) ? true : false; }
	if (dwBtn == 1) { return (Triger <= 0) ? true : false; }
	return false;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	ボタン情報取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CInput::GetJoyButton(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= NUM_JOY_MAX) { return false; }
	return (m_joyState[dwJoy].dwButtons & (1 << dwBtn)) ? true : false;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	トリガ情報取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CInput::GetJoyTrigger(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= NUM_JOY_MAX) { return false; }
	return (m_dwJoyButtonRelease[dwJoy] & (1 << dwBtn)) ? true : false;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	リリース情報取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CInput::GetJoyRelease(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= NUM_JOY_MAX) { return false; }
	return (m_dwJoyButtonTrigger[dwJoy] & (1 << dwBtn)) ? true : false;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	十字 ボタン情報取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
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


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	十字 ボタン情報取得	Press

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CInput::GetJoyCross(DWORD dwJoy, DWORD dwPad)
{
	if (dwJoy >= NUM_JOY_MAX) { return false; }

	DWORD dwAngel = m_joyState[dwJoy].dwPOV / 100;
	for (int i = 0; i < MAX_JOYCROSS; i++)
	{ if (dwAngel == m_dwJoyCrossAngle[dwPad][i]) { return true; } }
	return false;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	十字 ボタン情報取得	Trigger

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
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


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コントローラー 十字 ボタン情報取得	Release
	未完

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
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
	コントローラー
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	クライアント座標取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
POINT* CInput::GetMouseClientPosition()
{
	return &m_ptClientMouse;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	スクリーン領域でのウィンドウの座標取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
// 左上
POINT* CInput::GetWindowTLPosition()
{
	return &m_ptTopLeftWindow;
}
// 右下
POINT* CInput::GetWindowBRPosition()
{
	return &m_ptBottonRightWindow;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	ボタン情報取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CInput::GetMouseButton(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_nMouseBtn)) { return false; }
	return GetKeyPress(g_nMouseBtn[dwBtn]);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	トリガ情報取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CInput::GetMouseTrigger(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_nMouseBtn)) { return false; }
	return GetKeyTrigger(g_nMouseBtn[dwBtn]);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	リリース情報取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CInput::GetMouseRelease(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_nMouseBtn)) { return false; }
	return GetKeyRelease(g_nMouseBtn[dwBtn]);
}
