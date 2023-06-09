//=============================================================================
//
// í [Weapon.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Model.h"


//
// ñ^
//
enum EWeapon {
	WEAPON_NONE = 0,	// í³
	WEAPON_WOOD_SWORD,	// Ø
	WEAPON_AXE,			// 
	WEAPON_LARGE_SWORD,	// å

	MAX_WEAPON
};

class CPlayer;
class CHPGaugeEnemy;
class CGolem;
class CSwordMan;
//
// í NX
//
class CWeapon : public CModel
{
private:
	CAssimpModel*	m_pModel;
	XMFLOAT4X4		m_mW;

	XMFLOAT3		m_fRotate;			// ñ]
	static int		m_iPower;			// UÍ
	static float	m_fSpeed;			// Ué¬³
	XMFLOAT4		m_fRimColor;		// CgÌF

	static EWeapon	m_Weapon;			// ¡Ìí
	static EWeapon	m_CenterIcon;		// ^ñÌACRª½Ìí(íIðæÊ)

	CPlayer*		m_pPlayer;			// ©@
	CGolem*			m_pGolem;			// S[
	CSwordMan*		m_pSwordMan;		// \[_\
	CHPGaugeEnemy*	m_pHPGaugeEnemy;	// HPQ[W(G)

public:
	//
	// î{
	//
	CWeapon(CScene* pScene);
	HRESULT Init();
	void Fin();
	void Update();
	void Draw();
	void DrawAlpha();

	//
	// Xe[^X
	//
	static void SetPower(int power) { m_iPower = power; }
	static int GetPower() { return m_iPower; }
	static void SetSpeed(float speed) { m_fSpeed = speed; }
	static float GetSpeed() { return m_fSpeed; }

	//
	// »Ì¼
	//
	static void SetWeapon(EWeapon weapon) { m_Weapon = weapon; }
	static EWeapon GetWeapon() { return m_Weapon; }
	static void SetCenterIcon(EWeapon weapon) { m_CenterIcon = weapon; }
	static EWeapon GetCenterIcon() { return m_CenterIcon; }
	

	//
	// ½è»è
	//
	void GolemCollision(int weapon);	// S[
};