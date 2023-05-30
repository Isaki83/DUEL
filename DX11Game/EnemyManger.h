//=============================================================================
//
// 敵マネージャー [EnemyManger.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 列挙型
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
enum EEnemy {
	ENEMY_NONE = 0,		// 敵無
	ENEMY_GOLEM,		// ゴーレム
	ENEMY_SWORDMAN,		// ソードマン

	MAX_ENEMY
};

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 敵マネージャー クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CEnemyManger
{
private:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// その他
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	static	EEnemy	m_Enemy;			// 今の敵
	static	EEnemy	m_CenterIcon;		// 真ん中のアイコンが何の敵(敵選択画面)

public:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// その他
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	static void SetEnemy(EEnemy enemy) { m_Enemy = enemy; }
	static EEnemy GetEnemy() { return m_Enemy; }
	static void SetCenterIcon(EEnemy enemy) { m_CenterIcon = enemy; }
	static EEnemy GetCenterIcon() { return m_CenterIcon; }
};