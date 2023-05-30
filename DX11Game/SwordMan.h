//=============================================================================
//
// ソーダ― [SwordMan.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Enemy.h"
#include "SwordManAnim.h"


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 列挙型
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// --- 状態 ---
// MOVE の状態
enum ESM_State_Move {
	SM_BIG_MOVE_BACK,	// 大移動(後ろ)
	SM_BIG_MOVE_SIDE,	// 大移動(左右)
	SM_RUN_MOVE,		// 走って近付く

	MAX_SM_STATE_MOVE
};
// ATTACK の状態
enum ESM_State_Attack {
	SM_ATTACK_NONE,	// 無

	SM_ATTACK_00,	// その場で2連撃
	SM_ATTACK_01,	// 遠くから急接近して2連撃
	SM_ATTACK_02,	// 走ってある程度近付いてから、突き状態で急接近して回し斬り
	SM_ATTACK_03,	// 地面に剣を指して広範囲に攻撃

	MAX_SM_STATE_ATTACK
};


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ソーダ― クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CSwordMan : public CEnemy
{
private:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// アニメーション関連
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CSwordManAnimSet	m_AnimSet;			// アニメーション データ セット

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 徘徊用
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	ESM_State_Move		SM_MoveState;
	ESM_State_Attack	SM_AttackState;

public:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CSwordMan(CScene* pScene);
	HRESULT Init();
	void Update();

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 徘徊用
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	void StateIdle();
	void StateMove(XMFLOAT3 vX, XMFLOAT3 vZ);
	void StateAttack01();
	void StateAttack02(XMFLOAT3 vZ);
	void StateAttack03();
	void StateDead();
};