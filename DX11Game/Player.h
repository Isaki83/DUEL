/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	プレイヤー [Player.h]
	Author : ISAKI SUGIURA

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
#pragma once
#include "Model.h"
#include "Parts.h"
#include "PlayerAnim.h"

class CGround;
class CWeapon;
class CGolem;
class CSwordMan;
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// プレイヤー クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CPlayer : public CModel
{
private:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// アニメーション関連
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CPlayerAnimSet	m_animSet;				// アニメーション データ セット
	bool			m_bIsAttack;			// 攻撃中か
	bool			m_iAnimFin;				// アニメーションが最終フレームかどうか

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// ジャンプ関連
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	XMFLOAT3	m_fJumpStartPos;	// ジャンプ開始時の座標
	float		m_fJumpTime;		// ジャンプ開始してからの経過時間
	bool		m_bJumpFlag;		// ジャンプして良いか

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 当たり判定
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	int			m_iSide;			// AABBで当たっている面

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// その他
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	int			m_iLife;			// 体力
	bool		m_bMoveFlag;		// 移動しているか
	bool		m_bTargetEnemy;		// 敵の方向を向くか
	bool		m_bInvicibleFlag;	// 無敵フラグ
	bool		m_bAvoidFlag;		// 回避フラグ
	int			m_iAvoidDir;		// 回避方向
	int			m_iAvoidTimeCnt;	// 回避時間カウント
	float		m_fSpeedScale;		// スピード倍率
	bool		m_bSceneChengeFlag;	// シーンチェンジするか

	CGround*	m_pGround;			// 地面
	CWeapon*	m_pWeapon;			// 武器
	CGolem*		m_pGolem;			// ゴーレム
	CSwordMan*	m_pSwordMan;		// ソーダ―

public:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CPlayer(CScene* pScene);
	HRESULT Init();
	void Update();
	void Draw();
	void DrawAlpha();

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// アニメーション関連
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	int GetAnimNo() { return m_animSet.Get(); }
	int GetAnimCount() { return m_animSet.GetCount(); }

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 動き
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	void Move(XMFLOAT3 xyz, const char dir, float speed);	// 移動
	void WallJump();										// 壁に当たったらジャンプ

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// その他
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	bool GetAvoidFlag() { return m_bAvoidFlag; }
	void SetSceneChengeFlag(bool falg = true) { m_bSceneChengeFlag = falg; }
	bool GetSceneChengeFlag() { return m_bSceneChengeFlag; }

	void LifeDmg(int dmg) { m_iLife -= dmg; }
	int GetMaxLife();

private:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// モデル関連
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	void CalcMatrix();				// 角度からマトリックスを計算(全パーツ分)

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 当たり判定
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	void GroundCollision();			// 地面
};
