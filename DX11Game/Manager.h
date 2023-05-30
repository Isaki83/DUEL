//=============================================================================
//
// マネージャー [Manager.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// プロトタイプ宣言
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// スクリーン座標でのウィンドウの左上と右下の座標を返す
XMFLOAT4 GetWindowTLBR();
// ウィンドウの縦、横幅を取得する
XMFLOAT2 GetWindowSize();
// マウスカーソル表示切替
void SetShowCursor(bool show);
// マウスをウィンドウの中心に固定する
void SetMouseMiddlePos();
// マウスのスクリーン座標を取得
XMFLOAT2 GetMouseScreenPos();
// マウスのクライアント座標を取得
XMFLOAT2 GetMouseClientPos();
// マウスの移動量を取得する
XMFLOAT2 GetMouseMovement();

