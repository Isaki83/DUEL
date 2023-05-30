//=============================================================================
//
// 敵マネージャー [EnemyManger.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "EnemyManger.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 静的メンバ変数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
EEnemy CEnemyManger::m_Enemy = ENEMY_SWORDMAN;
EEnemy CEnemyManger::m_CenterIcon = m_Enemy;