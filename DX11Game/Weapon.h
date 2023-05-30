//=============================================================================
//
// ���� [Weapon.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Model.h"


//����������������������������������������
// �񋓌^
//����������������������������������������
enum EWeapon {
	WEAPON_NONE = 0,	// ���햳
	WEAPON_WOOD_SWORD,	// �،�
	WEAPON_AXE,			// ��
	WEAPON_LARGE_SWORD,	// �匕

	MAX_WEAPON
};

class CPlayer;
class CHPGaugeEnemy;
class CGolem;
class CSwordMan;
//����������������������������������������
// ���� �N���X
//����������������������������������������
class CWeapon : public CModel
{
private:
	CAssimpModel*	m_pModel;
	XMFLOAT4X4		m_mW;

	XMFLOAT3		m_fRotate;			// ��]
	static int		m_iPower;			// �U����
	static float	m_fSpeed;			// �U�鑬��
	XMFLOAT4		m_fRimColor;		// �������C�g�̐F

	static EWeapon	m_Weapon;			// ���̕���
	static EWeapon	m_CenterIcon;		// �^�񒆂̃A�C�R�������̕���(����I�����)

	CPlayer*		m_pPlayer;			// ���@
	CGolem*			m_pGolem;			// �S�[����
	CSwordMan*		m_pSwordMan;		// �\�[�_�\
	CHPGaugeEnemy*	m_pHPGaugeEnemy;	// HP�Q�[�W(�G)

public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CWeapon(CScene* pScene);
	HRESULT Init();
	void Fin();
	void Update();
	void Draw();
	void DrawAlpha();

	//����������������������������������������
	// �X�e�[�^�X
	//����������������������������������������
	static void SetPower(int power) { m_iPower = power; }
	static int GetPower() { return m_iPower; }
	static void SetSpeed(float speed) { m_fSpeed = speed; }
	static float GetSpeed() { return m_fSpeed; }

	//����������������������������������������
	// ���̑�
	//����������������������������������������
	static void SetWeapon(EWeapon weapon) { m_Weapon = weapon; }
	static EWeapon GetWeapon() { return m_Weapon; }
	static void SetCenterIcon(EWeapon weapon) { m_CenterIcon = weapon; }
	static EWeapon GetCenterIcon() { return m_CenterIcon; }
	

	//����������������������������������������
	// �����蔻��
	//����������������������������������������
	void GolemCollision(int weapon);	// �S�[����
};