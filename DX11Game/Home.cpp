//=============================================================================
//
// ホーム画面 [Home.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "Home.h"
#include "2Dobj.h"
#include "Sound.h"
#include "Input.h"
#include "Fade.h"
#include "Manager.h"
#include "EnemyManger.h"
#include "Golem.h"
#include "SwordMan.h"


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コンストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CHome::CHome() : CScene()
{
	m_id = SCENE_HOME;

	m_pWeapon = nullptr;

	m_pMouseCursor = nullptr;
	m_pBG_Frame = nullptr;
	m_pReturnButton = nullptr;
	m_pWeaponButton = nullptr;
	m_pMonsterButton = nullptr;
	m_pDuelStartButton = nullptr;
}

/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	デストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CHome::~CHome()
{
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CHome::Init()
{
	m_camera.Init();
	CCamera::Set(&m_camera);

	// 生成
	m_pWeapon = new CWeapon(this);
	switch (CEnemyManger::GetEnemy())
	{
	case ENEMY_GOLEM:
		new CGolem(this);
		break;
	case ENEMY_SWORDMAN:
		new CSwordMan(this);
		break;
	default:
		break;
	}

	m_pMouseCursor = new CMouseCursor(this);
	m_pReturnButton = new CReturnButton(this);
	m_pWeaponButton = new CWeaponButton(this);
	m_pMonsterButton = new CMonsterButton(this);
	m_pDuelStartButton = new CDuelStartButton(this);
	m_pBG_Frame = new CBG_Frame(this);

	// 全オブジェクト初期化
	if (FAILED(CGameObj::InitAll(m_pObj))) { return false; }
	if (FAILED(C2DObj::InitAll(m_p2DObj))) { return false; }

	m_pMonsterButton->SetID(MONSTER_BUTTON);
	m_pDuelStartButton->SetID(DUEL_START_BUTTON);
	m_pWeaponButton->SetID(WEAPON_BUTTON);
	m_iButtonID = DUEL_START_BUTTON;

	// BGM再生開始
	CSound::Play(BGM_2);

	return true;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	終了

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CHome::Fin()
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
void CHome::Update()
{
	// マウスカーソル非表示
	SetShowCursor(false);

	// 全オブジェクト更新
	CGameObj::UpdateAll(m_pObj);
	C2DObj::UpdateAll(m_p2DObj);

	
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// シーン移動
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#pragma region コントローラー
	if (0 < CInput::GetJoyCount())
	{
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		// タイトル画面に移動
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		if (CInput::GetJoyTrigger(0, JOYBUTTON_B))
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

			// 大きさを戻す
			m_pReturnButton->SetSize(XMFLOAT2(128.0f, 64.0f));

			// シーンチェンジ
			CFade::Out(SCENE_TITLE);
		}

		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		// IDによって移動するシーンが変わる
		// 武器選択画面 / 戦闘開始 / 敵選択画面
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		// シーン移動
		if (CInput::GetJoyTrigger(0, JOYBUTTON_A))
		{
			CSound::Play(SE_1);
			switch (m_iButtonID)
			{
			case MONSTER_BUTTON:
				CFade::Out(SCENE_ENEMY_SELECT);
				break;
			case DUEL_START_BUTTON:
				switch (CEnemyManger::GetEnemy())
				{
				case ENEMY_GOLEM:
					CFade::Out(SCENE_BATTLE_GOLEM);
					break;
				case ENEMY_SWORDMAN:
					CFade::Out(SCENE_BATTLE_SM);
					break;
				default:
					break;
				}
				break;
			case WEAPON_BUTTON:
				CFade::Out(SCENE_WEAPON_SELECT);
				break;
			default:
				break;
			}
		}

		// 選択中のボタンを変える
		if (CInput::GetJoyCrossTrigger(0, JOYCROSS_RIGHT))
		{
			CSound::Play(SE_2);
			m_iButtonID--;
			if (m_iButtonID < 0) { m_iButtonID = MAX_BUTTON_HOME - 1; }
		}
		if (CInput::GetJoyCrossTrigger(0, JOYCROSS_LEFT))
		{
			CSound::Play(SE_2);
			m_iButtonID++;
			if (MAX_BUTTON_HOME - 1 < m_iButtonID) { m_iButtonID = 0; }
		}

		// MonsterButton選択中
		if (m_iButtonID == m_pMonsterButton->GetID()) { m_pMonsterButton->NowSelectScaleUp(); }
		else { m_pMonsterButton->NowSelectScaleDown(); }
		// DuelStartButton選択中
		if (m_iButtonID == m_pDuelStartButton->GetID()) { m_pDuelStartButton->NowSelectScaleUp(); }
		else { m_pDuelStartButton->NowSelectScaleDown(); }
		// WeaponButton選択中
		if (m_iButtonID == m_pWeaponButton->GetID()) { m_pWeaponButton->NowSelectScaleUp(); }
		else { m_pWeaponButton->NowSelectScaleDown(); }
	}
#pragma endregion
#pragma region マウス
	else
	{
		// タイトル画面に移動
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
				CFade::Out(SCENE_TITLE);
			}
		}
		else
		{	// 色を戻す
			m_pReturnButton->SetColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (CInput::GetMouseRelease(MOUSEBUTTON_L))
		{	// 大きさを戻す
			m_pReturnButton->SetSize(XMFLOAT2(128.0f, 64.0f));
		}

		// ゲームシーンに移動
		if (m_pMouseCursor->CollisionAABB(m_pMouseCursor, m_pDuelStartButton))
		{
			m_pDuelStartButton->NowSelectScaleUp();
			if (CInput::GetMouseTrigger(MOUSEBUTTON_L))
			{
				switch (CEnemyManger::GetEnemy())
				{
				case ENEMY_GOLEM:
					CFade::Out(SCENE_BATTLE_GOLEM);
					break;
				case ENEMY_SWORDMAN:
					CFade::Out(SCENE_BATTLE_SM);
					break;
				default:
					break;
				}
				CSound::Play(SE_1);
			}
		}
		else { m_pDuelStartButton->NowSelectScaleDown(); }
		// 武器選択シーンに移動
		if (m_pMouseCursor->CollisionAABB(m_pMouseCursor, m_pWeaponButton))
		{
			m_pWeaponButton->NowSelectScaleUp();
			if (CInput::GetMouseTrigger(MOUSEBUTTON_L))
			{
				CFade::Out(SCENE_WEAPON_SELECT);
				CSound::Play(SE_1);
			}
		}
		else { m_pWeaponButton->NowSelectScaleDown(); }
		// モンスター選択シーンに移動
		if (m_pMouseCursor->CollisionAABB(m_pMouseCursor, m_pMonsterButton))
		{
			m_pMonsterButton->NowSelectScaleUp();
			if (CInput::GetMouseTrigger(MOUSEBUTTON_L))
			{
				CFade::Out(SCENE_ENEMY_SELECT);
				CSound::Play(SE_1);
			}
		}
		else { m_pMonsterButton->NowSelectScaleDown(); }
	}
#pragma endregion
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	描画

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CHome::Draw()
{
	// 全キャラ描画
	CGameObj::DrawAll(m_pObj);

	// 2DObj描画
	C2DObj::DrawAll(m_p2DObj);
}
