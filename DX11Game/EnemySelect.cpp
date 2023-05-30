//=============================================================================
//
// 敵選択画面 [EnemySelect.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "EnemySelect.h"
#include "2Dobj.h"
#include "Sound.h"
#include "Input.h"
#include "Fade.h"
#include "Manager.h"
#include "Golem.h"
#include "SwordMan.h"


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コンストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CEnemySelect::CEnemySelect() : CScene()
{
	m_id = SCENE_ENEMY_SELECT;

	m_pMouseCursor = nullptr;
	m_pReturnButton = nullptr;
	m_pDecisionButton = nullptr;
	for (int i = 0; i < _countof(m_pArrowButton); i++) { m_pArrowButton[i] = nullptr; }
	for (int i = 0; i < _countof(m_pEnemyIcon); i++) { m_pEnemyIcon[i] = nullptr; }
	m_pBG_Frame = nullptr;
	m_pNameUI = nullptr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	デストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CEnemySelect::~CEnemySelect()
{
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CEnemySelect::Init()
{
	m_camera.Init();
	CCamera::Set(&m_camera);

	new CGolem(this);
	new CSwordMan(this);

	m_pMouseCursor = new CMouseCursor(this);
	m_pReturnButton = new CReturnButton(this);
	m_pDecisionButton = new CDecisionButton(this);
	m_pNameUI = new CNameUI(this);
	for (int i = 0; i < 2; i++) { m_pArrowButton[i] = new CArrowButton(this); }
	for (int i = 0; i < MAX_ENEMY - 1; i++) { m_pEnemyIcon[i] = new CEnemyIcon(this); }
	m_pBG_Frame = new CBG_Frame(this);

	// 全オブジェクト初期化
	if (FAILED(CGameObj::InitAll(m_pObj))) { return false; }
	if (FAILED(C2DObj::InitAll(m_p2DObj))) { return false; }
	IconInit();

	// BGM再生開始
	CSound::Play(BGM_2);

	return true;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	終了

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CEnemySelect::Fin()
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
void CEnemySelect::Update()
{
	// マウスカーソル非表示
	SetShowCursor(false);

	// 全オブジェクト更新
	IconUpdate();
	CGameObj::UpdateAll(m_pObj);
	C2DObj::UpdateAll(m_p2DObj);

	
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// ホーム画面に移動
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#pragma region コントローラー
	if (0 < CInput::GetJoyCount())
	{
		if (CInput::GetJoyButton(0, JOYBUTTON_B))
		{	
			// 色を変える
			m_pReturnButton->SetColor(XMFLOAT4(1.0f, 0.8f, 0.8f, 1.0f));

			// 大きさを小さくする
			m_pReturnButton->SetSize(XMFLOAT2(120.0f, 60.0f));
		}
		if (CInput::GetJoyRelease(0, JOYBUTTON_B))
		{
			CSound::Play(SE_1);

			// 色を戻す
			m_pReturnButton->SetColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

			// シーンチェンジ
			CFade::Out(SCENE_HOME);
		}
	}
#pragma endregion
#pragma region マウス
	else
	{
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		// マウスと戻るボタンの当たり判定
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		if (m_pMouseCursor->CollisionAABB(m_pMouseCursor, m_pReturnButton))
		{
			// 色を変える
			m_pReturnButton->SetColor(XMFLOAT4(1.0f, 0.8f, 0.8f, 1.0f));
			if (CInput::GetMouseButton(MOUSEBUTTON_L))
			{	// 大きさを小さくする
				m_pReturnButton->SetSize(XMFLOAT2(120.0f, 60.0f));
			}
			if (CInput::GetMouseRelease(MOUSEBUTTON_L))
			{
				CSound::Play(SE_1);

				// シーンチェンジ
				CFade::Out(SCENE_HOME);
			}
		}
		else
		{	// 色を戻す
			m_pReturnButton->SetColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
#pragma endregion
	if (CInput::GetMouseRelease(MOUSEBUTTON_L) || CInput::GetJoyRelease(0, JOYBUTTON_B))
	{	// 大きさを戻す
		m_pReturnButton->SetSize(XMFLOAT2(128.0f, 64.0f));
	}
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	描画

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CEnemySelect::Draw()
{
	// 全キャラ描画
	CGameObj::DrawAll(m_pObj);

	// 2DObj描画
	C2DObj::DrawAll(m_p2DObj);
}
