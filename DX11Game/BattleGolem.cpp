//=============================================================================
//
// バトル画面(ゴーレム) [BattleGolem.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "BattleGolem.h"
#include "Input.h"
#include "GameObj.h"
#include "Sound.h"
#include "Ground.h"
#include "Manager.h"
#include "Fade.h"
#include "EnemyManger.h"
#include "HitStop.h"
#include "DebugProc.h"


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コンストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CBattleGolem::CBattleGolem() : CScene()
{
	m_id = SCENE_BATTLE_GOLEM;

	m_nBoundary = 0;
	m_bBoundary = false;

	m_pPlayer = nullptr;
	m_pGolem = nullptr;

	m_pHPGaugePlayer = nullptr;
	m_pHPGaugeEnemy = nullptr;
	m_pWeaponIcon = nullptr;
	m_pEnemyIcon = nullptr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CBattleGolem::Init()
{
	m_stopFlag = false;

	m_camera.Init();
	CCamera::Set(&m_camera);

	CLight* pLight = CLight::Get();
	if (pLight) { pLight->Init(); }

	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	// 地面生成
	new CGround(this);
	// 武器生成
	m_pWeapon = new CWeapon(this);
	// プレイヤー生成
	m_pPlayer = new CPlayer(this);
	// 敵生成
	m_pGolem = new CGolem(this);

	// HPゲージ(プレイヤー)生成
	m_pHPGaugePlayer = new CHPGaugePlayer(this);
	// HPゲージ(敵)生成
	m_pHPGaugeEnemy = new CHPGaugeEnemy(this);
	// アイコン生成
	m_pWeaponIcon = new CWeaponIcon(this);
	m_pEnemyIcon = new CEnemyIcon(this);

	// 全オブジェクト初期化
	if (FAILED(CGameObj::InitAll(m_pObj))) { return false; }
	if (FAILED(C2DObj::InitAll(m_p2DObj))) { return false; }
	// 初期化
	m_pPlayer->SetPos(XMFLOAT3(0.0f, 500.0f, 3000.0f));
	m_pGolem->SetPos(XMFLOAT3(0.0f, 600.0f, 0.0f));
	m_pHPGaugePlayer->SetLife(m_pPlayer->GetMaxLife());
	m_pHPGaugeEnemy->SetLife(m_pGolem->GetMaxLife());

	m_camera.SetPlayer(m_pPlayer);

	// BGM再生開始
	CSound::Play(BGM_1);
	

	return true;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	終了

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CBattleGolem::Fin()
{
	// BGM再生停止
	CSound::Stop(BGM_1);

	// 全オブジェクト終了処理
	C2DObj::FinAll(m_p2DObj);
	CGameObj::FinAll(m_pObj);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CBattleGolem::Update()
{
	// マウスカーソル非表示
	SetShowCursor(false);

	if (CInput::GetKeyTrigger(VK_F3)) 
	{
		m_nBoundary = (m_nBoundary + 1) % 2;
		UpdateBoundary();
	}
	if (m_bBoundary)
	{
		static LPCSTR boundary[] = { "ﾋﾋｮｳｼﾞ", "ﾋｮｳｼﾞ" };
		CDebugProc::Print("\x84\xCE[F3] : ｷｮｳｶｲ %s\x84\xCF\n", boundary[m_nBoundary]);
	}

	if (CInput::GetKeyRelease(VK_Q) || CInput::GetJoyRelease(0, JOYBUTTON_START))
	{
		m_stopFlag = !m_stopFlag;
	}

	if (!m_stopFlag)
	{
		// マウスをウィンドウの中心に固定する
		SetMouseMiddlePos();

		if (CHitStop::HitStop())
		{
			// 全キャラ更新
			CGameObj::UpdateAll(m_pObj);
			C2DObj::UpdateAll(m_p2DObj);
		}
	}

	// 敵とプレイヤーどちらかが死んだら
	if (m_pGolem->GetSceneChengeFlag() || m_pPlayer->GetSceneChengeFlag())
	{
		CFade::Out(SCENE_HOME);
		m_pGolem->SetSceneChengeFlag(false);
		m_pPlayer->SetSceneChengeFlag(false);
	}
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	描画

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CBattleGolem::Draw()
{
	// 全キャラ描画
	CGameObj::DrawAll(m_pObj);

	// 2DObj描画
	C2DObj::DrawAll(m_p2DObj);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	境界表示更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CBattleGolem::UpdateBoundary()
{
	switch (m_nBoundary) 
	{
	case 0:	// 境界表示無し
		m_pWeapon->SetBoundaryType(BT_NONE);
		m_pGolem->SetBoundaryType(BT_NONE);
		m_pPlayer->SetBoundaryType(BT_NONE);
		m_bBoundary = false;
		break;
	case 1:	// 境界ボックス(BT_OBB)
		m_pWeapon->SetBoundaryType(BT_OBB);
		m_pGolem->SetBoundaryType(BT_OBB);
		m_pPlayer->SetBoundaryType(BT_OBB);
		m_bBoundary = true;
		break;
	}
}