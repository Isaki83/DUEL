//=============================================================================
//
// マネージャー [Manager.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "main.h"
#include "Manager.h"
#include "Input.h"


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// グローバル変数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
namespace
{
	int g_FrameCount;

	float g_WindowWidth;		// ウィンドウの横幅
	float g_WindowHeight;		// ウィンドウの縦幅

	int	g_iCursor;				// マウスカーソルを表示切替用
	POINT g_MouseScreenPos;		// マウスのスクリーン座標
	POINT g_MouseClientPos;		// マウスのクライアント座標
	XMFLOAT2 g_MouseMovement;	// マウスの移動量
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	スクリーン座標でのウィンドウの左上と右下の座標を返す
	Top,Left,Bottom,Right

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
XMFLOAT4 GetWindowTLBR()
{
	// スクリーン上でのウィンドウの座標取得
	// 左上
	POINT windowTL = *CInput::GetWindowTLPosition();
	// 右下
	POINT windowBR = *CInput::GetWindowBRPosition();

	return XMFLOAT4((float)windowTL.x, (float)windowTL.y, (float)windowBR.x, (float)windowBR.y);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	ウィンドウの縦幅、横幅を取得する

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
XMFLOAT2 GetWindowSize()
{
	// 横幅
	g_WindowWidth = GetWindowTLBR().z - GetWindowTLBR().x;
	// 縦幅
	g_WindowHeight = GetWindowTLBR().w - GetWindowTLBR().y;

	return XMFLOAT2(g_WindowWidth, g_WindowHeight);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	マウスカーソル表示切替

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
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

 
/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	マウスのスクリーン座標を取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
XMFLOAT2 GetMouseScreenPos()
{
	GetCursorPos(&g_MouseScreenPos);
	return XMFLOAT2((float)g_MouseScreenPos.x, (float)g_MouseScreenPos.y);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	マウスのクライアント座標を取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
XMFLOAT2 GetMouseClientPos()
{
//	g_MouseClientPos = *CInput::GetMouseClientPosition();
	g_MouseClientPos.x = GetMouseScreenPos().x - GetWindowTLBR().y;
	g_MouseClientPos.y = GetMouseScreenPos().y - GetWindowTLBR().x;
	return XMFLOAT2((float)g_MouseClientPos.x, (float)g_MouseClientPos.y);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	マウスをウィンドウの中心に固定する

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
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


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	マウスの移動量を取得する

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
XMFLOAT2 GetMouseMovement()
{
	g_MouseMovement.x = GetMouseClientPos().x - GetWindowSize().x / 2.0f;
	g_MouseMovement.y = GetMouseClientPos().y - GetWindowSize().y / 2.0f;
	return XMFLOAT2(g_MouseMovement.x, g_MouseMovement.y);
}