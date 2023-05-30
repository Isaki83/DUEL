//=============================================================================
//
// ソーダ― [SwordMan.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "SwordMan.h"
#include "SwordRain.h"
#include "Particle.h"
#include "HPGaugePlayer.h"
#include "Fade.h"
#include "Player.h"
#include "EnemyManger.h"
#include "Sound.h"
#include "Random.h"


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 定数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#define SPEED				(10)		// 移動スピード
#define DOWN_SPEED			(0.6f)		// 減速倍率 (索敵範囲内にいるとき)
#define MAX_LIFE			(25000)		// 体力
#define SEARCH_RANGE		(1000.0f)	// 索敵範囲
#define ATTACK_RANGE		(350.0f)	// 攻撃範囲
#define GRAVITY				(0.98f)		// 重力
#define VELOCITY			(25.0f)		// 初速度


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーツ初期データ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
static TPartsData SwordMan_Data[MAX_SM_PARTS] =
{ // 親パーツNo.				モデル番号			オフセット値						ダメージ倍率
	{-1,					MODEL_LOOT,			{ 0.0f,		0.0f,		0.0f},	0.0f},
	{PARTS_SM_LOOT,			MODEL_SM_HIP,		{ 0.0f,		156.6f,		0.0f},	0.8f},
	{PARTS_SM_HIP,			MODEL_SM_BODY,		{ 0.0f,		17.3f,		0.0f},	1.0f},
	{PARTS_SM_BODY,			MODEL_SM_HEAD,		{ 0.0f,		123.3f,		0.0f},	1.5f},
	{PARTS_SM_BODY,			MODEL_SM_ARM,		{ -51.0f,	122.1f,		0.0f},	0.6f},
	{PARTS_SM_ARM_UP_R,		MODEL_SM_ARM,		{ 0.0f,		-101.0f,	0.0f},	0.4f},
	{PARTS_SM_ARM_DOWN_R,	MODEL_SM_HAND,		{ 0.0f,		-102.8f,	0.0f},	0.2f},
	{PARTS_SM_BODY,			MODEL_SM_ARM,		{ 51.0f,	122.1f,		0.0f},	0.6f},
	{PARTS_SM_ARM_UP_L,		MODEL_SM_ARM,		{ 0.0f,		-101.0f,	0.0f},	0.4f},
	{PARTS_SM_ARM_DOWN_L,	MODEL_SM_HAND,		{ 0.0f,		-102.8f,	0.0f},	0.2f},
	{PARTS_SM_HIP,			MODEL_SM_LEG,		{ -25.8f,	-10.2f,		0.0f},	0.6f},
	{PARTS_SM_LEG_UP_R,		MODEL_SM_LEG,		{ 0.0f,		-74.8f,		0.0f},	0.4f},
	{PARTS_SM_HIP,			MODEL_SM_LEG,		{ 25.8f,	-10.2f,		0.0f},	0.6f},
	{PARTS_SM_LEG_UP_L,		MODEL_SM_LEG,		{ 0.0f,		-74.8f,		0.0f},	0.4f},
	{PARTS_SM_HAND_R,		MODEL_BLACK_SWORD,	{ 0.0f,		-7.5f,		0.0f},	0.0f},
};

/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コンストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CSwordMan::CSwordMan(CScene* pScene) : CEnemy(pScene)
{
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT CSwordMan::Init()
{
	HRESULT hr = CEnemy::Init();
	if (FAILED(hr)) { return hr; }

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// パーツ関連
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	m_parts.clear();
	m_pMaxParts = MAX_SM_PARTS;
	TParts parts[MAX_SM_PARTS];
	for (int i = 0; i < m_pMaxParts; ++i)
	{
		if ((i == 0) || (i == PARTS_BLACK_SWORD)) { parts[i].use = false; }
		else { parts[i].use = true; }
		parts[i].parent = SwordMan_Data[i].parent;
		parts[i].model = SwordMan_Data[i].model;
		parts[i].off = SwordMan_Data[i].off;
		parts[i].angle = XMFLOAT3(0.0f, 0.0f, 0.0f);
		parts[i].DmgRatio = SwordMan_Data[i].DmgRatio;
		parts[i].hitDefence = false;
		parts[i].hitAttack = false;
		parts[i].num = i;
		CAssimpModel* pModel = CModel::GetAssimp((EModel)parts[i].model);
		parts[i].center = pModel->GetCenter();
		if (i == PARTS_BLACK_SWORD)
		{
			parts[i].bbox = XMFLOAT3(pModel->GetBBox().x * 1.5f, pModel->GetBBox().y * 1.5f, pModel->GetBBox().z * 1.5f);
		}
		else
		{
			parts[i].bbox = pModel->GetBBox();
		}
		m_parts.push_back(parts[i]);
	}
	CalcMatrix();

	SetCenter(XMFLOAT3(0.0f, 178.0f, 0.0f));
	SetBBox(XMFLOAT3(134.5f / 2.0f, 357.2f / 2.0f, 69.6f / 2.0f));

	BaseState = STATE_ENEMY_IDLE;
	SM_MoveState = SM_BIG_MOVE_BACK;
	SM_AttackState = SM_ATTACK_NONE;

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
void CSwordMan::Update()
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

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// パーティクルを出す位置の調整
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	XMFLOAT4X4 fW;
	fW = m_parts[PARTS_BLACK_SWORD].matrix;
	fW._41 -= fW._21 * m_parts[PARTS_BLACK_SWORD].bbox.y;
	fW._42 = m_vPos.y;
	fW._43 -= fW._23 * m_parts[PARTS_BLACK_SWORD].bbox.y;


	// 角度が絶対値"360"までいったら値を"0"に戻す
	if (m_vAngle.y <= -360.0f || m_vAngle.y >= 360.0f) { m_vAngle.y = 0.0f; }

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// シーンごとの処理
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	switch (CFade::GetScene())
	{
#pragma region タイトル画面
	case SCENE_TITLE:
		GroundCollision();
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		// 地面に足がついていなかったら重力を与える
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		if (!(m_iSide == 2))
		{	//ジャンプ中じゃないなら落下
			if (m_bJumpFlag) { m_vPos.y -= 15.0f; }
		}

		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		// 処理
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		switch (BaseState)
		{
		case STATE_ENEMY_IDLE:
			// 待機アニメーション再生
			m_AnimSet.Play(ANIM_SM_IDLE);
			m_iAnimNum = ANIM_SM_IDLE;
			// 位置、向き設定
			SetPos(XMFLOAT3(0.0f, 600.0f, 0.0f));
			SetAngle(XMFLOAT3(0.0f, 220.0f, 0.0f));
			BaseState = STATE_ENEMY_ATTACK;
			m_iStatus = 0;
		case STATE_ENEMY_ATTACK:
			m_iTime++;
			if (180 < m_iTime)
			{
				switch (m_iStatus)
				{
				case 0:
					// 攻撃１アニメーション再生
					m_AnimSet.Play(ANIM_SM_ATTACK_00_01);
					m_iAnimNum = ANIM_SM_ATTACK_00_01;
					m_iStatus = 1;
					break;
				case 1:
					// case 0: で再生したアニメーションが終わったら
					if (m_iAnimTime.x)
					{
						// パーティクル生成
						for (int j = 0; j < MAX_PARTICLE; j++)
						{
							CParticle::Creat(m_pScene, fW, 90, XMINT3(10, 30, 10), XMFLOAT3(0.0f, -1.0f, 0.0f));
						}
						// 攻撃２アニメーション再生
						m_AnimSet.Play(ANIM_SM_ATTACK_00_02);
						m_iAnimNum = ANIM_SM_ATTACK_00_02;
						m_iStatus = 2;
					}
					break;
				case 2:
					// case 1: で再生したアニメーションが終わったら
					if (m_iAnimTime.x)
					{
						// 待機アニメーション再生
						m_AnimSet.Play(ANIM_SM_IDLE);
						m_iAnimNum = ANIM_SM_IDLE;
						m_iTime = 0;
						m_iStatus = 0;
					}
					break;
				}
			}
			break;
		}
		break;
#pragma endregion
#pragma region ホーム画面
	case SCENE_HOME:
		// 待機アニメーション再生
		m_AnimSet.Play(ANIM_SM_IDLE);
		m_iAnimNum = ANIM_SM_IDLE;
		break;
#pragma endregion
#pragma region 敵選択画面
	case SCENE_ENEMY_SELECT:
		// 待機アニメーション再生
		m_AnimSet.Play(ANIM_SM_IDLE);
		m_iAnimNum = ANIM_SM_IDLE;

		// 中心のアイコンが自分なら描画
		if (CEnemyManger::GetCenterIcon() == ENEMY_SWORDMAN) { m_bVisible = true; }
		else { m_bVisible = false; }
		break;
#pragma endregion
#pragma region ゲーム画面
	case SCENE_BATTLE_SM:
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		// 地面に足がついていなかったら重力を与える
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		if (!(m_iSide == 2))
		{	//ジャンプ中じゃないなら落下
			if (m_bJumpFlag) { m_vPos.y -= 15.0f; }
		}

		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		// 攻撃の状態によって色を変える
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		switch (SM_AttackState)
		{
		case SM_ATTACK_NONE:	// 白色
			m_fRimColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		case SM_ATTACK_01:		// 赤色
			m_fRimColor = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
			break;
		case SM_ATTACK_02:		// 黄色
			m_fRimColor = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);
			break;
		case SM_ATTACK_03:		// 青色
			m_fRimColor = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
			break;
		}

		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		// 状態ごとの処理
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		switch (BaseState)
		{
#pragma region *-*-*- 待機 -*-*-*
		case STATE_ENEMY_IDLE:
			StateIdle();
			break;
#pragma endregion
#pragma region *-*-*- 移動 -*-*-*
		case STATE_ENEMY_MOVE:
			StateMove(vX, vZ);
			break;
#pragma endregion
#pragma region *-*-*- 攻撃的 -*-*-*
		case STATE_ENEMY_ATTACK:
			StateAttack01();
			StateAttack02(vZ);
			StateAttack03();
			break;
#pragma endregion
#pragma region *-*-*- 死亡 -*-*-*
		case STATE_ENEMY_DEAD:
			StateDead();
			break;
#pragma endregion
		default:
			break;
		}

		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		// 攻撃中の当たり判定
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		if (m_pPlayer && !m_pPlayer->GetAvoidFlag())
		{
			CGameObj* pNext;
			for (CGameObj* pObj = m_pScene->GetObj(); pObj; pObj = pNext)
			{
				pNext = pObj->GetNext();
				if (pObj->GetID() != GOT_PLAYER) { continue; }

				if (CollisionOBB(pObj, GetParts(PARTS_BLACK_SWORD).matrix, GetParts(PARTS_BLACK_SWORD).center, GetParts(PARTS_BLACK_SWORD).bbox))
				{
					if ((m_iAnimNum == ANIM_SM_ATTACK_01_03) || (m_iAnimNum == ANIM_SM_ATTACK_01_04) ||
						(m_iAnimNum == ANIM_SM_ATTACK_02_02) || (m_iAnimNum == ANIM_SM_ATTACK_02_03))
					{
						// 一回のアニメーションで一回しか判定をとらない
						if (!GetParts(PARTS_BLACK_SWORD).hitAttack)
						{
							m_pPlayer->LifeDmg(200);
							m_pHPGaugePlayer->SetDamage(200);
							SetPartsHitAttack(PARTS_BLACK_SWORD, true);
						}
					}
				}
			}
		}

		break;
#pragma endregion
	default:
		break;
	}

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 敵全種の共通処理
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CEnemy::Update();

#if 0
	CDebugProc::Print("*** ｿｰﾄﾞﾏﾝ ***\n");
	CDebugProc::Print("[m_vPos   : %f, %f, %f]\n", m_vPos.x, m_vPos.y, m_vPos.z);
	//	CDebugProc::Print("[AttackTime      : %d - %d]\n", 
	//		(m_iAnimNum == ANIM_SM_ATTACK_1) ? SM_ATTACK1_S : (m_iAnimNum == ANIM_SM_ATTACK_2) ? SM_ATTACK2_S : 0 ,
	//		(m_iAnimNum == ANIM_SM_ATTACK_1) ? SM_ATTACK1_E : (m_iAnimNum == ANIM_SM_ATTACK_2) ? SM_ATTACK2_E : 0);
#endif
}



/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	待機 状態

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
#pragma region 待機
void CSwordMan::StateIdle()
{
	CRandom random;
	std::vector<ActionWeight> actionWeights{
		{0, 0.6f},		// 走って近付く
		{1, 0.4f},		// 大移動(左右)
	};

	switch (m_iStatus)
	{
	case 0:
		// アニメーション再生
		m_AnimSet.Play(ANIM_SM_IDLE);
		m_iAnimNum = ANIM_SM_IDLE;
		// 待機時間を決める
		m_iDoTime = rand() % 20 + 20; // 20 ~ 39
		m_iStatus = 1;
		break;
	case 1:
		m_iDoTime--;
		// 待機時間が無くなったら
		if (m_iDoTime < 0)
		{
			// 攻撃３をやろうとしていたら
			if (SM_AttackState == SM_ATTACK_03)
			{
				BaseState = STATE_ENEMY_ATTACK;
				m_iStatus = 0;
			}
			// そうじゃないならランダム遷移
			else
			{
				switch (random.WeightRandom(actionWeights))
				{
				case 0:
					// 距離が離れていたら
					if (SEARCH_RANGE < m_fDist)
					{
						// 攻撃２の状態に設定
						SM_AttackState = SM_ATTACK_02;
						// 走って近付く
						SM_MoveState = SM_RUN_MOVE;
						BaseState = STATE_ENEMY_MOVE;
						m_iStatus = 0;
					}
				case 1:
					// 移動の状態を大移動(左右)に変える
					SM_MoveState = SM_BIG_MOVE_SIDE;
					BaseState = STATE_ENEMY_MOVE;
					m_iStatus = 0;
					break;
				}
			}
		}
		break;
	}
}
#pragma endregion


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	移動 状態

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
#pragma region 移動
void CSwordMan::StateMove(XMFLOAT3 vX, XMFLOAT3 vZ)
{
	CRandom random;
	std::vector<ActionWeight> actionWeights;

	switch (SM_MoveState)
	{
#pragma region 大移動(後ろ)
	case SM_BIG_MOVE_BACK:
		switch (m_iStatus)
		{
		case 0:
			// アニメーション再生
			m_AnimSet.Play(ANIM_SM_JUMP);
			m_iAnimNum = ANIM_SM_JUMP;
			// 移動時間を決める
			m_iDoTime = rand() % 40 + 20; // 20 ~ 40
			// スピード倍率設定
			m_fSpeedScale = (float)(rand() % 20 + 30) / 10.0f;	// 3.0f ~ 5.0f
			// 次だす攻撃を決める
			if (SM_AttackState == SM_ATTACK_NONE)
			{
				actionWeights = {
					{0, 0.3f},
					{1, 0.1f}
				};
				switch (random.WeightRandom(actionWeights))
				{
				case 0:
					SM_AttackState = SM_ATTACK_01;
					break;
				default:
					break;
				}
			}
			m_iStatus = 1;
			break;
		case 1:
			m_iDoTime--;
			// 後ろ
			Move(vZ, '+', SPEED * m_fSpeedScale);
			// 移動時間が無くなったら
			if (m_iDoTime < 0)
			{
				// 攻撃２をやろうとしていたら
				if (SM_AttackState == SM_ATTACK_01)
				{
					// プレイヤーと近すぎたら"横に飛ぶ"
					if (m_fDist < ATTACK_RANGE * 2)
					{
						SM_MoveState = SM_BIG_MOVE_SIDE;
						m_iStatus = 0;
					}
					// 距離が離れていたら
					else
					{
						BaseState = STATE_ENEMY_ATTACK;
						m_iStatus = 0;
					}
				}
				// そうじゃないならランダム遷移
				else
				{
					actionWeights = {
						{0, 0.3f},
						{1, 0.1f}
					};
					switch (random.WeightRandom(actionWeights))
					{
					case 0:
						// 距離が離れていたら
						if (SEARCH_RANGE < m_fDist)
						{
							// 攻撃２の状態に設定
							SM_AttackState = SM_ATTACK_02;
							// 走って近付く
							SM_MoveState = SM_RUN_MOVE;
							m_iStatus = 0;
						}
						else
						{
							// 移動の状態を大移動(左右)に変える
							SM_MoveState = SM_BIG_MOVE_SIDE;
							m_iStatus = 0;
						}
						break;
					case 1:
						// 移動の状態を大移動(左右)に変える
						SM_MoveState = SM_BIG_MOVE_SIDE;
						m_iStatus = 0;
						break;
					}
				}
			}
			break;
		}
		break;
#pragma endregion
#pragma region 大移動(左右)
	case SM_BIG_MOVE_SIDE:
		switch (m_iStatus)
		{
		case 0:
			// アニメーション再生
			m_AnimSet.Play(ANIM_SM_JUMP);
			m_iAnimNum = ANIM_SM_JUMP;
			// 移動時間を決める
			m_iDoTime = rand() % 40 + 20; // 20 ~ 40
			// 移動方向を決める(2方向)
			m_iDirections = rand() % 2;
			// スピード倍率設定
			m_fSpeedScale = (float)(rand() % 20 + 30) / 10.0f;	// 3.0f ~ 5.0f
			m_iStatus = 1;
			break;
		case 1:
			m_iDoTime--;
			if (m_pPlayer)
			{
				// プレイヤーの方向を向く
				m_vAngle.y = atan2(m_vPos.x - m_pPlayer->GetPos().x, m_vPos.z - m_pPlayer->GetPos().z) * (180.0f / 3.14f);
			}
			// 移動方向
			switch (m_iDirections)
			{
			case 0:	// 右
				Move(vX, '-', SPEED * m_fSpeedScale);
				break;
			case 1:	// 左
				Move(vX, '+', SPEED * m_fSpeedScale);
				break;
			}
			// 移動時間が無くなったら
			if (m_iDoTime < 0)
			{
				// 攻撃１をやろうとしていたら"後ろに飛ぶ"
				if (SM_AttackState == SM_ATTACK_01)
				{
					SM_MoveState = SM_BIG_MOVE_BACK;
					m_iStatus = 0;
				}
				// そうじゃないならランダム遷移
				else
				{
					actionWeights = {
						{0, 0.3f},	// 距離次第で走って近付くか大移動(後ろ)
						{1, 0.2f},	// 大移動(後ろ)
						{2, 0.1f}	// 大移動(左右)
					};
					switch (random.WeightRandom(actionWeights))
					{
					case 0:
						// 距離が離れていたら
						if (SEARCH_RANGE < m_fDist)
						{
							// 攻撃２の状態に設定
							SM_AttackState = SM_ATTACK_02;
							// 走って近付く
							SM_MoveState = SM_RUN_MOVE;
							m_iStatus = 0;
						}
						else
						{
							SM_MoveState = SM_BIG_MOVE_BACK;
							m_iStatus = 0;
						}
						break;
					case 1:
						SM_MoveState = SM_BIG_MOVE_BACK;
						m_iStatus = 0;
						break;
					case 2:
						m_iStatus = 0;
						break;
					}
				}
			}
		}
		break;
#pragma endregion
#pragma region 走って近付く
	case SM_RUN_MOVE:
		switch (m_iStatus)
		{
		case 0:
			// アニメーション再生
			m_AnimSet.Play(ANIM_SM_RUN);
			m_iAnimNum = ANIM_SM_RUN;
			// スピード倍率設定
			m_fSpeedScale = 4.0f;
			m_iStatus = 1;
			break;
		case 1:
			// プレイヤーの方向を向く
			m_vAngle.y = atan2(m_vPos.x - m_pPlayer->GetPos().x, m_vPos.z - m_pPlayer->GetPos().z) * (180.0f / 3.14f);
			// 前進
			Move(vZ, '-', SPEED * m_fSpeedScale);
			// 近付いたら攻撃
			if (m_fDist < SEARCH_RANGE)
			{
				BaseState = STATE_ENEMY_ATTACK;
				m_iStatus = 0;
			}
			break;
		}
		break;
#pragma endregion
	}
}
#pragma endregion


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	攻撃１ 状態
	*** 遠くから急接近して2連撃 ***

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
#pragma region 攻撃１
void CSwordMan::StateAttack01()
{
	if (SM_AttackState != SM_ATTACK_01) { return; }
	switch (m_iStatus)
	{
	case 0:
		// アニメーション再生
		m_AnimSet.Play(ANIM_SM_ATTACK_01_01);
		m_iAnimNum = ANIM_SM_ATTACK_01_01;
		// 今の座標を保存
		m_fPrevPos = m_vPos;
		m_fPrevPlayerPos = m_pPlayer->GetPos();
		// スピード倍率設定
		m_fSpeedScale = 6.0f;
		// プレイヤーの方向を向く
		m_vAngle.y = atan2(m_vPos.x - m_pPlayer->GetPos().x, m_vPos.z - m_pPlayer->GetPos().z) * (180.0f / 3.14f);
		m_iStatus = 1;
		break;
	case 1:
		// 直前に再生したアニメーションが終わったら
		if (m_iAnimTime.x)
		{
			// アニメーション再生
			m_AnimSet.Play(ANIM_SM_ATTACK_01_02);
			m_iAnimNum = ANIM_SM_ATTACK_01_02;
			m_iStatus = 2;
		}
		break;
	case 2:
		// 目標地点まで移動
		lblPosXZ(XMFLOAT2(m_fPrevPos.x, m_fPrevPos.z), XMFLOAT2(m_fPrevPlayerPos.x, m_fPrevPlayerPos.z), SPEED * m_fSpeedScale);
		// 距離計算
		XMVECTOR vT = XMVectorSet(m_vPos.x - m_fPrevPlayerPos.x, 0.0f, m_vPos.z - m_fPrevPlayerPos.z, 0.0f);
		XMStoreFloat(&m_fPrevDist, XMVector3Length(vT));
		// 攻撃範囲まで近づいたら
		if (m_fPrevDist < ATTACK_RANGE) { m_iStatus = 3; }
		break;
	case 3:
		CSound::Play(SM_A0101);
		// アニメーション再生
		m_AnimSet.Play(ANIM_SM_ATTACK_01_03);
		m_iAnimNum = ANIM_SM_ATTACK_01_03;
		m_iStatus = 4;
		break;
	case 4:
		// 直前に再生したアニメーションが終わったら
		if (m_iAnimTime.x)
		{
			// 判定を戻す
			SetPartsHitAttack(PARTS_BLACK_SWORD, false);
			// アニメーション再生
			m_AnimSet.Play(ANIM_SM_ATTACK_01_04);
			m_iAnimNum = ANIM_SM_ATTACK_01_04;
			m_iStatus = 5;
		}
		break;
	case 5:
		// 直前に再生したアニメーションが終わったら
		if (m_iAnimTime.x)
		{
			// 判定を戻す
			SetPartsHitAttack(PARTS_BLACK_SWORD, false);
			// アニメーション再生
			m_AnimSet.Play(ANIM_SM_ATTACK_01_05);
			m_iAnimNum = ANIM_SM_ATTACK_01_05;
			m_iStatus = 6;
		}
		break;
	case 6:
		// 直前に再生したアニメーションが終わったら
		if (m_iAnimTime.x)
		{
			// 基本の状態を待機に変える
			BaseState = STATE_ENEMY_IDLE;
			m_iStatus = 0;
			SM_AttackState = SM_ATTACK_NONE;
		}
		break;
	}
}
#pragma endregion


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	攻撃２ 状態
	*** 走ってある程度近付いてから、突き状態で急接近して回し斬り ***

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
#pragma region 攻撃２
void CSwordMan::StateAttack02(XMFLOAT3 vZ)
{
	if (SM_AttackState != SM_ATTACK_02) { return; }

	CRandom random;
	std::vector<ActionWeight> actionWeights;

	switch (m_iStatus)
	{
	case 0:
		CSound::Play(SM_A0201);
		// アニメーション再生
		m_AnimSet.Play(ANIM_SM_ATTACK_02_01);
		m_iAnimNum = ANIM_SM_ATTACK_02_01;
		// スピード倍率設定
		m_fSpeedScale = 6.0f;
		// プレイヤーの方向を向く
		m_vAngle.y = atan2(m_vPos.x - m_pPlayer->GetPos().x, m_vPos.z - m_pPlayer->GetPos().z) * (180.0f / 3.14f);
		m_iStatus = 1;
		break;
	case 1:
		// 直前に再生したアニメーションが終わったら
		if (m_iAnimTime.x)
		{
			CSound::Play(SM_A0202);
			// アニメーション再生
			m_AnimSet.Play(ANIM_SM_ATTACK_02_02);
			m_iAnimNum = ANIM_SM_ATTACK_02_02;
			m_iStatus = 2;
		}
		break;
	case 2:
		// プレイヤーの方向を向く
		m_vAngle.y = atan2(m_vPos.x - m_pPlayer->GetPos().x, m_vPos.z - m_pPlayer->GetPos().z) * (180.0f / 3.14f);
		// 前進
		Move(vZ, '-', SPEED * m_fSpeedScale);
		if (m_fDist < ATTACK_RANGE)
		{
			// 判定を戻す
			SetPartsHitAttack(PARTS_BLACK_SWORD, false);
			m_iStatus = 3;
		}
		break;
	case 3:
		CSound::Play(SM_A0203);
		// アニメーション再生
		m_AnimSet.Play(ANIM_SM_ATTACK_02_03);
		m_iAnimNum = ANIM_SM_ATTACK_02_03;
		m_iStatus = 4;
		break;
	case 4:
		// 直前に再生したアニメーションが終わったら
		if (m_iAnimTime.x)
		{
			// 判定を戻す
			SetPartsHitAttack(PARTS_BLACK_SWORD, false);
			// アニメーション再生
			m_AnimSet.Play(ANIM_SM_ATTACK_02_04);
			m_iAnimNum = ANIM_SM_ATTACK_02_04;
			m_iStatus = 5;
		}
		break;
	case 5:
		// 直前に再生したアニメーションが終わったら
		if (m_iAnimTime.x)
		{
			// 基本の状態を待機に変える
			BaseState = STATE_ENEMY_IDLE;
			m_iStatus = 0;
			SM_AttackState = SM_ATTACK_NONE;
			// 次ぎだす攻撃を決める
			if (SM_AttackState == SM_ATTACK_NONE)
			{
				actionWeights = {
					{0, 0.2f},	// 攻撃３
					{1, 0.1f}	// それ以外
				};
				switch (random.WeightRandom(actionWeights))
				{
				case 0:
					SM_AttackState = SM_ATTACK_03;
					break;
				default:
					break;
				}
			}
		}
		break;
	}
}
#pragma endregion


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	攻撃３ 状態
	*** 地面に剣を指して広範囲に攻撃 ***

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
#pragma region 攻撃３
void CSwordMan::StateAttack03()
{
	if (SM_AttackState != SM_ATTACK_03) { return; }
	switch (m_iStatus)
	{
	case 0:
		CSound::Play(SM_A0301);
		// アニメーション再生
		m_AnimSet.Play(ANIM_SM_ATTACK_03_01);
		m_iAnimNum = ANIM_SM_ATTACK_03_01;
		m_iStatus = 1;
		break;
	case 1:
		// 直前に再生したアニメーションが終わったら
		if (m_iAnimTime.x)
		{
			for (int i = 0; i < 30; i++) { CSwordRain::Creat(m_pScene, m_mWorld); }
			CSound::Play(SM_A0302);
			// アニメーション再生
			m_AnimSet.Play(ANIM_SM_ATTACK_03_02);
			m_iAnimNum = ANIM_SM_ATTACK_03_02;
			m_iStatus = 2;
		}
		break;
	case 2:
		// 直前に再生したアニメーションが終わったら
		if (m_iAnimTime.x)
		{
			// 基本の状態を待機に変える
			BaseState = STATE_ENEMY_IDLE;
			m_iStatus = 0;
			SM_AttackState = SM_ATTACK_NONE;
		}
		break;
	}
}
#pragma endregion


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	死亡 状態

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
#pragma region 死亡
void CSwordMan::StateDead()
{
	// シーンチェンジ
	SetSceneChengeFlag(true);
}
#pragma endregion
