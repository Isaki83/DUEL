//=============================================================================
//
// バトル画面(ソーダ―) [BattleSwordMan.h]
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
#include "SwordMan.h"


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// バトル画面(ゴーレム) クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CBattleSwordMan : public CScene
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
	CSwordMan* m_pSwordMan;

	CHPGaugePlayer* m_pHPGaugePlayer;
	CHPGaugeEnemy* m_pHPGaugeEnemy;
	CWeaponIcon* m_pWeaponIcon;
	CEnemyIcon* m_pEnemyIcon;

public:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CBattleSwordMan();
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
