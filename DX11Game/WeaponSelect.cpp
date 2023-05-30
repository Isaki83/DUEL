//=============================================================================
//
// 武器選択画面 [WeaponSelect.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "WeaponSelect.h"
#include "2Dobj.h"
#include "Sound.h"
#include "Input.h"
#include "Manager.h"


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コンストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CWeaponSelect::CWeaponSelect() : CScene()
{
	m_id = SCENE_WEAPON_SELECT;

	m_pWeapon = nullptr;

	m_pMouseCursor = nullptr;
	m_pReturnButton = nullptr;
	m_pDecisionButton = nullptr;
	for (int i = 0; i < _countof(m_pArrowButton); i++) { m_pArrowButton[i] = nullptr; }
	for (int i = 0; i < _countof(m_pWeaponIcon); i++) { m_pWeaponIcon[i] = nullptr; }
	m_pBG_Frame = nullptr;
	m_pParmBG = nullptr;
	m_pWeaponParmUI = nullptr;
	m_pNameUI = nullptr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	デストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CWeaponSelect::~CWeaponSelect()
{
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CWeaponSelect::Init()
{
	m_camera.Init();
	CCamera::Set(&m_camera);

	// 武器生成
	m_pWeapon = new CWeapon(this);

	m_pMouseCursor = new CMouseCursor(this);
	m_pReturnButton = new CReturnButton(this);
	m_pNameUI = new CNameUI(this);
	m_pWeaponParmUI = new CWeaponParmUI(this);
	m_pParmBG = new CParmBG(this);
	m_pDecisionButton = new CDecisionButton(this);
	for (int i = 0; i < 2; i++) { m_pArrowButton[i] = new CArrowButton(this); }
	for (int i = 0; i < MAX_WEAPON - 1; i++) { m_pWeaponIcon[i] = new CWeaponIcon(this); }
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
void CWeaponSelect::Fin()
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
void CWeaponSelect::Update()
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
void CWeaponSelect::Draw()
{
	// 全キャラ描画
	CGameObj::DrawAll(m_pObj);

	// 2DObj描画
	C2DObj::DrawAll(m_p2DObj);
}
