//=============================================================================
//
// 敵 [Enemy.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Model.h"
#include "Parts.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 列挙型
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// --- 状態 ---
// 基本の状態
enum EEnemy_State {
	STATE_ENEMY_NONE,		// 状態 無

	STATE_ENEMY_IDLE,		// 待機
	STATE_ENEMY_MOVE,		// 移動
	STATE_ENEMY_ROTATION,	// 回転
	STATE_ENEMY_ATTACK,		// 攻撃
	STATE_ENEMY_DEAD,		// 死ぬ

	MAX_ENEMY_STATE
};

class CGround;
class CPlayer;
class CHPGaugePlayer;
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 敵 継承元クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CEnemy : public CModel
{
protected:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// アニメーション関連
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	XMINT2				m_iAnimTime;			// アニメーション
												// .x : 最終フレームかどうか 1 or 0
												// .y : 何フレーム目か
	int					m_iAnimNum;				// 今のアニメーション
	bool				m_bNowAttack;			// 攻撃中かどうか

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 徘徊用
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	EEnemy_State		BaseState;
	int					m_iStatus = 0;		// 状態の状態
	int					m_iDoTime;			// 行動時間
	int					m_iDirections;		// 方向
	int					m_iWhatAttack;		// 何の攻撃をするか
	float				m_fSpeedScale;		// スピード倍率

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// ジャンプ関連
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	XMFLOAT3			m_fJumpStartPos;	// ジャンプ開始時の座標
	float				m_fJumpTime;		// ジャンプ開始してからの経過時間
	bool				m_bJumpFlag;		// ジャンプして良いか

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 当たり判定
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	int					m_iSide;			// AABBで当たっている面

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// その他
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	float				m_fGravity;			// 重力
	float				m_fVelocity;		// 加速度
	XMFLOAT3			m_fPrevPos;			// 前の座標
	XMFLOAT3			m_fPrevPlayerPos;	// 前のプレイヤーの座標
	int					m_iMaxLife;			// 最大体力
	int					m_iLife;			// 体力
	int					m_iTmp[5];			// 汎用
	bool				m_bOnce;			// 一回しかやりたくないとき
	float				m_fDist;			// プレイヤーと自分の距離
	float				m_fPrevDist;		// 前の座標で計算した距離
	bool				m_bSceneChengeFlag;	// シーンチェンジするか
	int					m_pMaxParts;		// パーツ最大数
	int					m_iTime;			// 時間
	XMFLOAT4			m_fRimColor;		// リムライトの色

	CGround*			m_pGround;			// 地面
	CPlayer*			m_pPlayer;			// 自機
	CHPGaugePlayer*		m_pHPGaugePlayer;	// HPゲージ

public:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CEnemy(CScene* pScene);
	virtual HRESULT Init();
	virtual void Update();
	void Draw();
	void DrawAlpha();

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 動き
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	void Move(XMFLOAT3 xyz, const char dir, float speed);
	bool lblPos(XMFLOAT3 posA, XMFLOAT3 posB, float speed);
	bool lblPosXZ(XMFLOAT2 posA, XMFLOAT2 posB, float speed);
	void WallJump();

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// その他
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	void LifeDmg(int dmg) { m_iLife -= dmg; }		// 体力を減らす
	int GetMaxLife() { return m_iMaxLife; }			// 最大体力を渡す

	void SetSceneChengeFlag(bool falg = true) { m_bSceneChengeFlag = falg; }
	bool GetSceneChengeFlag() { return m_bSceneChengeFlag; }

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// モデル関連
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	void CalcMatrix();				// 角度からマトリックスを計算(全パーツ分)

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 当たり判定
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	void GroundCollision();			// 地面
};