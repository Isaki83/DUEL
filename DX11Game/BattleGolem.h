//=============================================================================
//
// バトル画面(ゴーレム) [BattleGolem.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "Player.h"
#include "Weapon.h"
#include "HPGaugePlayer.h"
#include "HPGaugeEnemy.h"
#include "WeaponIcon.h"
#include "EnemyIcon.h"
#include "GameCamera.h"
#include "Golem.h"


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// バトル画面(ゴーレム) クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CBattleGolem : public CScene
{
protected:
	bool m_stopFlag;	// 一時停止

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// デバッグ 当たり判定表示用
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	int m_nBoundary;
	bool m_bBoundary;


	CGameCamera m_camera;

	CPlayer* m_pPlayer;
	CWeapon* m_pWeapon;
	CGolem* m_pGolem;

	CHPGaugePlayer* m_pHPGaugePlayer;
	CHPGaugeEnemy* m_pHPGaugeEnemy;
	CWeaponIcon* m_pWeaponIcon;
	CEnemyIcon* m_pEnemyIcon;

public:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CBattleGolem();
	bool Init();
	void Fin();
	void Update();
	void Draw();


	CPlayer* GetPlayer() { return m_pPlayer; }

private:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// デバッグ 当たり判定表示用
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	void UpdateBoundary();
};
