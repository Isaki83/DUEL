//=============================================================================
//
// タイトル画面 [Title.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "Title.h"
#include "2Dobj.h"
#include "Sound.h"
#include "Input.h"
#include "Fade.h"
#include "Manager.h"
#include "Ground.h"
#include "SwordMan.h"
#include "DebugProc.h"


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コンストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CTitle::CTitle() : CScene()
{
	m_id = SCENE_TITLE;

	m_pMouseCursor = nullptr;
	m_pTitleLogo = nullptr;
	m_pStartButton = nullptr;
	m_pExitButton = nullptr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	デストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CTitle::~CTitle()
{
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CTitle::Init()
{
	m_camera.Init();
	CCamera::Set(&m_camera);

	// 生成
	new CGround(this);
	new CSwordMan(this);

	// 生成 / 描画の順番(上が手前)
	m_pMouseCursor = new CMouseCursor(this);
	m_pTitleLogo = new CTitleLogo(this);
	m_pStartButton = new CStartButton(this);
	m_pExitButton = new CExitButton(this);

	// 全オブジェクト初期化
	if (FAILED(CGameObj::InitAll(m_pObj))) { return false; }
	if (FAILED(C2DObj::InitAll(m_p2DObj))) { return false; }

	m_pStartButton->SetID(START_BUTTON);
	m_pExitButton->SetID(EXIT_BUTTON);
	m_iButtonID = 0;

	// BGM再生開始
	CSound::Play(BGM_2);

	return true;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	終了

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CTitle::Fin()
{
	// BGM再生停止
	CSound::Stop(BGM_2);

	// 全オブジェクト終了処理
	C2DObj::FinAll(m_p2DObj);
	CGameObj::FinAll(m_pObj);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CTitle::Update()
{
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// マウスカーソル非表示
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	SetShowCursor(false);

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 全オブジェクト更新
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CGameObj::UpdateAll(m_pObj);
	C2DObj::UpdateAll(m_p2DObj);

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// シーン移動
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#pragma region コントローラー
	if (0 < CInput::GetJoyCount())
	{
		// シーンチェンジ
		if (CInput::GetJoyTrigger(0, JOYBUTTON_A))
		{
			CSound::Play(SE_1);
			switch (m_iButtonID)
			{
			case START_BUTTON:
				CFade::Out(SCENE_HOME);
				break;
			case EXIT_BUTTON:
				exit(0);
				break;
			default:
				break;
			}
		}

		// 選択中のボタンを変える
		if (CInput::GetJoyCrossTrigger(0, JOYCROSS_UP))
		{
			CSound::Play(SE_2);
			m_iButtonID--;
			if (m_iButtonID < 0) { m_iButtonID = MAX_BUTTON_TITLE - 1; }
		}
		if (CInput::GetJoyCrossTrigger(0, JOYCROSS_DOWN))
		{
			CSound::Play(SE_2);
			m_iButtonID++;
			if (MAX_BUTTON_TITLE - 1 < m_iButtonID) { m_iButtonID = 0; }
		}

		// StartButton選択中
		if (m_iButtonID == m_pStartButton->GetID()) { m_pStartButton->NowSelectScaleUp(); }
		else { m_pStartButton->NowSelectScaleDown(); }
		// ExitButton選択中
		if (m_iButtonID == m_pExitButton->GetID()) { m_pExitButton->NowSelectScaleUp(); }
		else { m_pExitButton->NowSelectScaleDown(); }
	}
#pragma endregion
#pragma region マウス
	else
	{
		// ホーム画面に移動
		if (m_pMouseCursor->CollisionAABB(m_pMouseCursor, m_pStartButton))
		{
			m_pStartButton->NowSelectScaleUp();
			if (CInput::GetMouseRelease(MOUSEBUTTON_L))
			{
				CFade::Out(SCENE_HOME);
				CSound::Play(SE_1);
			}
		}
		else { m_pStartButton->NowSelectScaleDown(); }
		// ゲームを終了する
		if (m_pMouseCursor->CollisionAABB(m_pMouseCursor, m_pExitButton))
		{
			m_pExitButton->NowSelectScaleUp();
			if (CInput::GetMouseRelease(MOUSEBUTTON_L))
			{
				CSound::Play(SE_1);
				exit(0);
			}
		}
		else { m_pExitButton->NowSelectScaleDown(); }
	}
#pragma endregion
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	描画

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CTitle::Draw()
{
	// 描画
	CGameObj::DrawAll(m_pObj);
	C2DObj::DrawAll(m_p2DObj);
}
