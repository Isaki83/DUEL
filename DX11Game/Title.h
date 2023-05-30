//=============================================================================
//
// タイトル画面 [Title.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "TitleLogo.h"
#include "StartButton.h"
#include "ExitButton.h"
#include "MouseCursor.h"
#include "GameCamera.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 列挙型
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
enum EButtonTitle
{
	START_BUTTON = 0,
	EXIT_BUTTON,

	MAX_BUTTON_TITLE
};

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// タイトル画面 クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CTitle : public CScene
{
private:
	int m_iEnemy;	// 選択中の敵が何かを覚えておく
	int m_iButtonID;

	CGameCamera m_camera;

	CTitleLogo* m_pTitleLogo;
	CStartButton* m_pStartButton;
	CExitButton* m_pExitButton;
	CMouseCursor* m_pMouseCursor;

public:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CTitle();
	virtual ~CTitle();

	bool Init();
	void Fin();
	void Update();
	void Draw();
};
