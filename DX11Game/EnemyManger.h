//=============================================================================
//
// �G�}�l�[�W���[ [EnemyManger.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once

//����������������������������������������
// �񋓌^
//����������������������������������������
enum EEnemy {
	ENEMY_NONE = 0,		// �G��
	ENEMY_GOLEM,		// �S�[����
	ENEMY_SWORDMAN,		// �\�[�h�}��

	MAX_ENEMY
};

//����������������������������������������
// �G�}�l�[�W���[ �N���X
//����������������������������������������
class CEnemyManger
{
private:
	//����������������������������������������
	// ���̑�
	//����������������������������������������
	static	EEnemy	m_Enemy;			// ���̓G
	static	EEnemy	m_CenterIcon;		// �^�񒆂̃A�C�R�������̓G(�G�I�����)

public:
	//����������������������������������������
	// ���̑�
	//����������������������������������������
	static void SetEnemy(EEnemy enemy) { m_Enemy = enemy; }
	static EEnemy GetEnemy() { return m_Enemy; }
	static void SetCenterIcon(EEnemy enemy) { m_CenterIcon = enemy; }
	static EEnemy GetCenterIcon() { return m_CenterIcon; }
};