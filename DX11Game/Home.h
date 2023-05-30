//=============================================================================
//
// ホーム画面 [Home.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Fade.h"
#include "Weapon.h"
#include "MouseCursor.h"
#include "BG_Frame.h"
#include "ReturnButton.h"
#include "WeaponButton.h"
#include "MonsterButton.h"
#include "DuelStartButton.h"
#include "GameCamera.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 列挙型
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
enum EButtonHome
{
	MONSTER_BUTTON = 0,
	DUEL_START_BUTTON,
	WEAPON_BUTTON,


	MAX_BUTTON_HOME
};

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ホーム画面 クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CHome : public CScene
{
private:
	int m_iButtonID;

	CGameCamera m_camera;

	CWeapon* m_pWeapon;

	CMouseCursor* m_pMouseCursor;
	CBG_Frame* m_pBG_Frame;
	CReturnButton* m_pReturnButton;
	CWeaponButton* m_pWeaponButton;
	CMonsterButton* m_pMonsterButton;
	CDuelStartButton* m_pDuelStartButton;

public:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CHome();
	virtual ~CHome();

	bool Init();
	void Fin();
	void Update();
	void Draw();
};