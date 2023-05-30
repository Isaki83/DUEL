//=============================================================================
//
// 武器 [Weapon.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Model.h"


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 列挙型
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
enum EWeapon {
	WEAPON_NONE = 0,	// 武器無
	WEAPON_WOOD_SWORD,	// 木剣
	WEAPON_AXE,			// 斧
	WEAPON_LARGE_SWORD,	// 大剣

	MAX_WEAPON
};

class CPlayer;
class CHPGaugeEnemy;
class CGolem;
class CSwordMan;
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 武器 クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CWeapon : public CModel
{
private:
	CAssimpModel*	m_pModel;
	XMFLOAT4X4		m_mW;

	XMFLOAT3		m_fRotate;			// 回転
	static int		m_iPower;			// 攻撃力
	static float	m_fSpeed;			// 振る速さ
	XMFLOAT4		m_fRimColor;		// リムライトの色

	static EWeapon	m_Weapon;			// 今の武器
	static EWeapon	m_CenterIcon;		// 真ん中のアイコンが何の武器(武器選択画面)

	CPlayer*		m_pPlayer;			// 自機
	CGolem*			m_pGolem;			// ゴーレム
	CSwordMan*		m_pSwordMan;		// ソーダ―
	CHPGaugeEnemy*	m_pHPGaugeEnemy;	// HPゲージ(敵)

public:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CWeapon(CScene* pScene);
	HRESULT Init();
	void Fin();
	void Update();
	void Draw();
	void DrawAlpha();

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// ステータス
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	static void SetPower(int power) { m_iPower = power; }
	static int GetPower() { return m_iPower; }
	static void SetSpeed(float speed) { m_fSpeed = speed; }
	static float GetSpeed() { return m_fSpeed; }

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// その他
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	static void SetWeapon(EWeapon weapon) { m_Weapon = weapon; }
	static EWeapon GetWeapon() { return m_Weapon; }
	static void SetCenterIcon(EWeapon weapon) { m_CenterIcon = weapon; }
	static EWeapon GetCenterIcon() { return m_CenterIcon; }
	

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 当たり判定
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	void GolemCollision(int weapon);	// ゴーレム
};