//=============================================================================
//
// �o�g�����(�S�[����) [BattleGolem.h]
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


//����������������������������������������
// �o�g�����(�S�[����) �N���X
//����������������������������������������
class CBattleGolem : public CScene
{
protected:
	bool m_stopFlag;	// �ꎞ��~

	//����������������������������������������
	// �f�o�b�O �����蔻��\���p
	//����������������������������������������
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
	//����������������������������������������
	// ��{
	//����������������������������������������
	CBattleGolem();
	bool Init();
	void Fin();
	void Update();
	void Draw();


	CPlayer* GetPlayer() { return m_pPlayer; }

private:
	//����������������������������������������
	// �f�o�b�O �����蔻��\���p
	//����������������������������������������
	void UpdateBoundary();
};
