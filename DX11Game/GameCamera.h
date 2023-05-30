//=============================================================================
//
// ゲーム カメラ [GameCamera.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Camera.h"
#include "GameObj.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ゲームカメラ クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CGameCamera : public CCamera
{
private:
	CGameObj* m_pPlayer;	// 自機
	float m_fRadius;		// 自機半径
	int m_nMode;			// カメラモード
	float m_fAngle;			// カメラアングル

	int m_iLookMe;			// 視点切り替え用

public:
	CGameCamera();

	void Init();
	void Update();

	// 自機設定
	void SetPlayer(CGameObj* pPlayer) { m_pPlayer = pPlayer; }
};
