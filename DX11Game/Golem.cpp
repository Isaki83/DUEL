//=============================================================================
//
// ゴーレム [Golem.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "Golem.h"
#include "BreakGround.h"
#include "Fade.h"
#include "Player.h"
#include "EnemyManger.h"
#include "HitStop.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 定数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#define SPEED				(10)
#define MAX_LIFE			(25000)
#define SEARCH_RANGE		(4000.0f)	// 索敵範囲
#define ATTACK_RANGE		(350.0f)	// 攻撃範囲


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーツ初期データ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
static TPartsData Golem_Data[MAX_GOLEM_PARTS] =
{ // 親パーツNo.				モデル番号				オフセット値						ダメージ倍率
	{-1,					MODEL_LOOT,				{ 0.0f,		0.0f,		0.0f},	0.0f},
	{PARTS_GOLEM_LOOT,		MODEL_GOLEM_HIP,		{ 0.0f,		200.5f,		0.0f},	0.6f},
	{PARTS_GOLEM_HIP,		MODEL_GOLEM_BODY,		{ 0.0f,		23.5f,		0.0f},	1.3f},
	{PARTS_GOLEM_BODY,		MODEL_GOLEM_HEAD,		{ 0.0f,		121.6f,		0.0f},	1.0f},
	{PARTS_GOLEM_BODY,		MODEL_GOLEM_ARM_UP,		{ -106.59f,	79.343f,	0.0f},	0.4f},
	{PARTS_GOLEM_ARM_UP_R,	MODEL_GOLEM_ARM_DOWN,	{ 0.0f,		-123.589f,	0.0f},	0.2f},
	{PARTS_GOLEM_BODY,		MODEL_GOLEM_ARM_UP,		{ 106.59f,	79.343f,	0.0f},	0.4f},
	{PARTS_GOLEM_ARM_UP_L,	MODEL_GOLEM_ARM_DOWN,	{ 0.0f,		-123.589f,	0.0f},	0.2f},
	{PARTS_GOLEM_HIP,		MODEL_GOLEM_LEG_UP,		{ -33.5f,	16.8f,		0.0f},	0.4f},
	{PARTS_GOLEM_LEG_UP_R,	MODEL_GOLEM_LEG_DOWN,	{ 0.0f,		-91.1f,		0.0f},	0.2f},
	{PARTS_GOLEM_HIP,		MODEL_GOLEM_LEG_UP,		{ 33.5f,	-16.8f,		0.0f},	0.4f},
	{PARTS_GOLEM_LEG_UP_L,	MODEL_GOLEM_LEG_DOWN,	{ 0.0f,		-91.1f,		0.0f},	0.2f},
};


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コンストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CGolem::CGolem(CScene* pScene) : CEnemy(pScene)
{
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT CGolem::Init()
{
	HRESULT hr = CEnemy::Init();
	if (FAILED(hr)) { return hr; }

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// パーツ関連
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	m_parts.clear();
	m_pMaxParts = MAX_GOLEM_PARTS;
	TParts parts[MAX_GOLEM_PARTS];
	for (int i = 0; i < m_pMaxParts; ++i)
	{
		if (i == 0) { parts[i].use = false; }
		else { parts[i].use = true; }
		parts[i].parent = Golem_Data[i].parent;
		parts[i].model = Golem_Data[i].model;
		parts[i].off = Golem_Data[i].off;
		parts[i].angle = XMFLOAT3(0.0f, 0.0f, 0.0f);
		parts[i].DmgRatio = Golem_Data[i].DmgRatio;
		parts[i].hitDefence = false;
		parts[i].hitAttack = false;
		parts[i].num = i;
		CAssimpModel* pModel = CModel::GetAssimp((EModel)parts[i].model);
		parts[i].center = pModel->GetCenter();
		parts[i].bbox = pModel->GetBBox();

		m_parts.push_back(parts[i]);
	}
	CalcMatrix();

	SetCenter(XMFLOAT3(0.0f, 240.0f, -20.0f));
	SetBBox(XMFLOAT3(95.0f, 206.0f, 95.0f));

	BaseState = STATE_ENEMY_IDLE;

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 体力
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	m_iMaxLife = MAX_LIFE;
	m_iLife = m_iMaxLife;

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// アニメーション
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	m_AnimSet.Init();

	return hr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CGolem::Update()
{
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// モデル全体のローカル座標軸取得
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// X軸
	XMFLOAT3 vX(m_mWorld._11, m_mWorld._12, m_mWorld._13);
	// Y軸
	XMFLOAT3 vY(m_mWorld._21, m_mWorld._22, m_mWorld._23);
	// Z軸
	XMFLOAT3 vZ(m_mWorld._31, m_mWorld._32, m_mWorld._33);

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// アニメーションをするために
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 時間から角度を線形補間で求める
	for (int i = 0; i < m_pMaxParts; ++i) { m_parts[i].angle = m_AnimSet.GetAngle(i); }
	// 時間とフレームを進める
	m_iAnimTime = m_AnimSet.AddTimer();


	// 角度が絶対値"360"までいったら値を"0"に戻す
	if (m_vAngle.y <= -360.0f || m_vAngle.y >= 360.0f) { m_vAngle.y = 0.0f; }

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// シーンごとの処理
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	switch (CFade::GetScene())
	{
#pragma region ホーム画面
	case SCENE_HOME:
		// 待機アニメーション再生
		m_AnimSet.Play(ANIM_GOLEM_IDLE);
		m_iAnimNum = ANIM_GOLEM_IDLE;
		break;
#pragma endregion
#pragma region 敵選択画面
	case SCENE_ENEMY_SELECT:
		// 待機アニメーション再生
		m_AnimSet.Play(ANIM_GOLEM_IDLE);
		m_iAnimNum = ANIM_GOLEM_IDLE;

		// 中心のアイコンが自分なら描画
		if (CEnemyManger::GetCenterIcon() == ENEMY_GOLEM) { m_bVisible = true; }
		else { m_bVisible = false; }

		break;
#pragma endregion
#pragma region バトル画面
	case SCENE_BATTLE_GOLEM:
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		// 地面に足がついていなかったら重力を与える
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		if (!(m_iSide == 2))
		{
			m_AnimSet.Play(ANIM_GOLEM_JUMP);
			m_iAnimNum = ANIM_GOLEM_JUMP;

			//ジャンプ中じゃないなら落下
			if (m_bJumpFlag) { m_vPos.y -= 15.0f; }
		}

		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		// 状態ごとの処理
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		switch (BaseState)
		{
#pragma region *-*-*- 待機 -*-*-*
		case STATE_ENEMY_IDLE:
			m_AnimSet.Play(ANIM_GOLEM_IDLE);
			m_iAnimNum = ANIM_GOLEM_IDLE;
			switch (m_iStatus)
			{
			case 0:
				// 待機時間を決める
				m_iDoTime = rand() % 300;
				m_iStatus = 1;
			case 1:
				// 時間を減らす
				m_iDoTime--;
				// 時間が無くなったら回転状態にする
				if (m_iDoTime <= 0)
				{
					m_iStatus = 0;
					BaseState = STATE_ENEMY_ROTATION;
				}
				break;
			default:
				break;
			}
			break;
#pragma endregion
#pragma region *-*-*- 移動 -*-*-*
		case STATE_ENEMY_MOVE:
			m_AnimSet.Play(ANIM_GOLEM_WALK);
			m_iAnimNum = ANIM_GOLEM_WALK;
			switch (m_iStatus)
			{
			case 0:
				// 移動時間を決める
				m_iDoTime = rand() % 300;
				m_iStatus = 1;
			case 1:
				// 時間を減らす
				m_iDoTime--;
				// 時間が0より小さくなるまで移動する
				if (m_iDoTime > 0)
				{	// 前進
					Move(vZ, '-', SPEED);
				}
				// 時間が無くなったら待機状態にする
				else
				{
					m_iStatus = 0;
					BaseState = STATE_ENEMY_IDLE;
				}
				// 一定より近付いたら攻撃的になる
				if (m_fDist <= SEARCH_RANGE)
				{
					m_iStatus = 0;
					BaseState = STATE_ENEMY_ATTACK;
				}
				break;
			default:
				break;
			}
			break;
#pragma endregion
#pragma region *-*-*- 回転 -*-*-*
		case STATE_ENEMY_ROTATION:
			m_AnimSet.Play(ANIM_GOLEM_WALK);
			m_iAnimNum = ANIM_GOLEM_WALK;
			switch (m_iStatus)
			{
			case 0:
				// 回転時間を決める
				m_iDoTime = rand() % 60;
				// 回転方向を決める
				m_iDirections = rand() % 2;
				m_iStatus = 1;
			case 1:
				// 時間を減らす
				m_iDoTime--;
				// 時間が0より小さくなるまで回転する
				if (m_iDoTime > 0)
				{
					if (m_iDirections == 0) { m_vAngle.y += 3; }
					else { m_vAngle.y -= 3; }
				}
				// 時間が無くなったら移動状態にする
				else
				{
					m_iStatus = 0;
					BaseState = STATE_ENEMY_MOVE;
				}
				break;
			default:
				break;
			}
			break;
#pragma endregion
#pragma region *-*-*- 攻撃的 -*-*-*
		case STATE_ENEMY_ATTACK:
			m_AnimSet.Play(ANIM_GOLEM_WALK);
			m_iAnimNum = ANIM_GOLEM_WALK;
			// プレイヤーの方向を向く
			m_vAngle.y = atan2(m_vPos.x - m_pPlayer->GetPos().x, m_vPos.z - m_pPlayer->GetPos().z) * (180.0f / 3.14f);
			if (m_vAngle.y <= -360.0f || m_vAngle.y >= 360.0f) { m_vAngle.y = 0.0f; }
			// 一定より離れていたら追尾移動
			if (m_fDist > ATTACK_RANGE && !m_bNowAttack)
			{	// 前進
				Move(vZ, '-', SPEED * 1.5f);
			}
			// 一定距離まで近付いたら攻撃
			else
			{
				switch (m_iStatus)
				{
				case 0:
					// 待機時間を決める
					m_iDoTime = rand() % 90 + 30;
					m_iStatus = 1;
				case 1:
					// 時間を減らす
					m_iDoTime--;
					// 時間が無くなったら攻撃する
					if (m_iDoTime <= 0)
					{
						m_fRimColor = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
						m_AnimSet.Play(ANIM_GOLEM_ATTACK);
						m_iAnimNum = ANIM_GOLEM_ATTACK;
						m_bNowAttack = true;
						if (m_iAnimTime.y == GOLEM_ATTACK)
						{
							CBreakGround::Creat(m_pScene, m_mWorld);
						}
						// 攻撃アニメーションが終わったら待機中に戻る
						if (m_iAnimTime.x)
						{
							m_fRimColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
							m_bNowAttack = false;
							m_iStatus = 0;
						}
					}
					// 待機時間中のアニメーション
					else
					{
						m_AnimSet.Play(ANIM_GOLEM_IDLE);
						m_iAnimNum = ANIM_GOLEM_IDLE;
					}
					break;
				default:
					break;
				}
			}
			// 一定より離れたら攻撃的を解除
			if (m_fDist > SEARCH_RANGE)
			{
				m_iStatus = 0;
				BaseState = STATE_ENEMY_ROTATION;
			}
			break;
#pragma endregion
#pragma region *-*-*- 死亡 - *-*-*
		case STATE_ENEMY_DEAD:
			m_AnimSet.Play(ANIM_GOLEM_DEATH, false);
			m_iAnimNum = ANIM_GOLEM_DEATH;
			// シーンチェンジ
			if (m_iAnimTime.x) { SetSceneChengeFlag(true); }
			break;
#pragma endregion
		default:
			break;
		}
#pragma endregion
	default:
		break;
	}

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 敵全種の共通処理
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CEnemy::Update();
}