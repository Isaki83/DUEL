//=============================================================================
//
// �G�I����� [EnemySelect.h]
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


//����������������������������������������
// �G�I����� �N���X
//����������������������������������������
class CEnemySelect : public CScene
{
private:
	CGameCamera m_camera;

	CMouseCursor* m_pMouseCursor;
	CReturnButton* m_pReturnButton;
	CDecisionButton* m_pDecisionButton;
	CArrowButton* m_pArrowButton[2];
	CEnemyIcon* m_pEnemyIcon[MAX_ENEMY - 1]; // -1 �͖��������O���邽��
	CBG_Frame* m_pBG_Frame;
	CNameUI* m_pNameUI;

public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CEnemySelect();
	virtual ~CEnemySelect();

	bool Init();
	void Fin();
	void Update();
	void Draw();

private:
	//����������������������������������������
	// �A�C�R���֘A
	//����������������������������������������
	void IconInit();
	void IconUpdate();
};