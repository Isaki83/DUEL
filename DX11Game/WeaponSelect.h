//=============================================================================
//
// 武器選択画面 [WeaponSelect.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Fade.h"
#include "MouseCursor.h"
#include "ReturnButton.h"
#include "DecisionButton.h"
#include "ArrowButton.h"
#include "WeaponIcon.h"
#include "BG_Frame.h"
#include "Weapon.h"
#include "ParmBG.h"
#include "WeaponParmUI.h"
#include "NameUI.h"
#include "GameCamera.h"


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 武器選択画面 クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CWeaponSelect : public CScene
{
private:
	CGameCamera m_camera;

	CWeapon* m_pWeapon;

	CMouseCursor* m_pMouseCursor;
	CReturnButton* m_pReturnButton;
	CDecisionButton* m_pDecisionButton;
	CArrowButton* m_pArrowButton[2];
	CWeaponIcon* m_pWeaponIcon[MAX_WEAPON - 1]; // -1 は武器無しを除外するため
	CBG_Frame* m_pBG_Frame;
	CParmBG* m_pParmBG;
	CWeaponParmUI* m_pWeaponParmUI;
	CNameUI* m_pNameUI;

public:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CWeaponSelect();
	virtual ~CWeaponSelect();

	bool Init();
	void Fin();
	void Update();
	void Draw();

private:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// アイコン関連
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	void IconInit();
	void IconUpdate();
};