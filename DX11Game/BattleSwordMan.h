//=============================================================================
//
// �o�g�����(�\�[�_�\) [BattleSwordMan.h]
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


//����������������������������������������
// �o�g�����(�S�[����) �N���X
//����������������������������������������
class CBattleSwordMan : public CScene
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
	CSwordMan* m_pSwordMan;

	CHPGaugePlayer* m_pHPGaugePlayer;
	CHPGaugeEnemy* m_pHPGaugeEnemy;
	CWeaponIcon* m_pWeaponIcon;
	CEnemyIcon* m_pEnemyIcon;

public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CBattleSwordMan();
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
