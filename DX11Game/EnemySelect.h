//=============================================================================
//
// 敵選択画面 [EnemySelect.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "EnemyManger.h"
#include "MouseCursor.h"
#include "ReturnButton.h"
#include "DecisionButton.h"
#include "ArrowButton.h"
#include "EnemyIcon.h"
#include "BG_Frame.h"
#include "NameUI.h"
#include "GameCamera.h"


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 敵選択画面 クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CEnemySelect : public CScene
{
private:
	CGameCamera m_camera;

	CMouseCursor* m_pMouseCursor;
	CReturnButton* m_pReturnButton;
	CDecisionButton* m_pDecisionButton;
	CArrowButton* m_pArrowButton[2];
	CEnemyIcon* m_pEnemyIcon[MAX_ENEMY - 1]; // -1 は無しを除外するため
	CBG_Frame* m_pBG_Frame;
	CNameUI* m_pNameUI;

public:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CEnemySelect();
	virtual ~CEnemySelect();

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