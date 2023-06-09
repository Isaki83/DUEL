//=============================================================================
//
// ν [Weapon.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "Weapon.h"
#include "Player.h"
#include "2Dobj.h"
#include "Fade.h"
#include "DebugProc.h"


//
// θ
//
// UΝ
#define P_WOOD_SWORD	(200)
#define P_AXE			(400)
#define P_LARGE_SWORD	(600)
// Uι¬³
#define S_WOOD_SWORD	(2.0f)
#define S_AXE			(1.5f)
#define S_LARGE_SWORD	(1.0f)


//
// ΓIoΟ
//
EWeapon CWeapon::m_Weapon = WEAPON_LARGE_SWORD;
EWeapon CWeapon::m_CenterIcon = m_Weapon;
int CWeapon::m_iPower = 0;
float CWeapon::m_fSpeed = 0.0f;


/*

	RXgN^

*/
CWeapon::CWeapon(CScene* pScene) : CModel(pScene)
{
	m_id = GOT_WEAPON;

	m_pModel = nullptr;

	m_pPlayer = nullptr;
	m_pGolem = nullptr;
	m_pSwordMan = nullptr;

	m_pHPGaugeEnemy = nullptr;

	XMMATRIX mIdentity = XMMatrixIdentity();
	XMStoreFloat4x4(&m_mW, mIdentity);
}


/*

	ϊ»

*/
HRESULT CWeapon::Init()
{
	HRESULT hr = CModel::Init();

	//
	// ν²ΖΜϊ»
	//
	switch (GetWeapon())
	{
	case WEAPON_NONE:
		SetWeapon(WEAPON_NONE);
		SetPower(0);
		SetSpeed(0.0f);
		m_pModel = nullptr;
		break;
	case WEAPON_WOOD_SWORD:
		SetWeapon(WEAPON_WOOD_SWORD);
		SetPower(P_WOOD_SWORD);
		SetSpeed(S_WOOD_SWORD);
		m_pModel = CModel::GetAssimp(MODEL_WOOD_SWORD);
		break;
	case WEAPON_AXE:
		SetWeapon(WEAPON_AXE);
		SetPower(P_AXE);
		SetSpeed(S_AXE);
		m_pModel = CModel::GetAssimp(MODEL_AXE);
		break;
	case WEAPON_LARGE_SWORD:
		SetWeapon(WEAPON_LARGE_SWORD);
		SetPower(P_LARGE_SWORD);
		SetSpeed(S_LARGE_SWORD);
		m_pModel = CModel::GetAssimp(MODEL_LARGE_SWORD);
		break;
	}

	SetCenter(m_pModel->GetCenter());
	SetBBox(
		XMFLOAT3(m_pModel->GetBBox().x * 1.5f, 
			m_pModel->GetBBox().y * 1.5f, 
			m_pModel->GetBBox().z * 1.5f));

	m_fRotate = XMFLOAT3(0.0f, 90.0f, 0.0f);
	m_fRimColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	m_pPlayer = (CPlayer*)m_pScene->Find(GOT_PLAYER);
	m_pGolem = (CGolem*)m_pScene->Find(GOT_ENEMY);
	m_pSwordMan = (CSwordMan*)m_pScene->Find(GOT_ENEMY);

	m_pHPGaugeEnemy = (CHPGaugeEnemy*)m_pScene->Find2DObj(GOT_HP_GAUGE_E);

	return hr;
}


/*

	IΉ

*/
void CWeapon::Fin()
{
	CModel::Fin();
}


/*

	XV

*/
void CWeapon::Update()
{
	// [hΟ·sρXV
	SetWorld(m_mW);

	// gj[ F
	m_fRimColor = XMFLOAT4(1.0f, 0.30769231f, 0.90384615f, 1.0f);

	XMMATRIX mW = DirectX::XMMatrixIdentity();
	switch (CFade::GetScene())
	{
	case SCENE_HOME:
		// ρ]
		m_fRotate.y++;

		// gk
		mW = XMMatrixMultiply(mW, XMMatrixScaling(2.0f, 2.0f, 2.0f));
		// ρ]
		mW = XMMatrixMultiply(mW, XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(m_fRotate.x), XMConvertToRadians(m_fRotate.y), XMConvertToRadians(m_fRotate.z)));
		// ΐW
		mW = XMMatrixMultiply(mW, XMMatrixTranslation(300.0f, -150.0f, 0.0f));
		// ΟX½f
		XMStoreFloat4x4(&m_mW, mW);
		break;
	case SCENE_WEAPON_SELECT:
		switch (GetCenterIcon())
		{
		case WEAPON_NONE:
			m_pModel = nullptr;
			break;
		case WEAPON_WOOD_SWORD:
			m_pModel = CModel::GetAssimp(MODEL_WOOD_SWORD);
			SetPower(P_WOOD_SWORD);
			SetSpeed(S_WOOD_SWORD);
			break;
		case WEAPON_AXE:
			m_pModel = CModel::GetAssimp(MODEL_AXE);
			SetPower(P_AXE);
			SetSpeed(S_AXE);
			break;
		case WEAPON_LARGE_SWORD:
			m_pModel = CModel::GetAssimp(MODEL_LARGE_SWORD);
			SetPower(P_LARGE_SWORD);
			SetSpeed(S_LARGE_SWORD);
			break;
		}

		// ρ]
		m_fRotate.y++;

		// gk
		mW = XMMatrixMultiply(mW, XMMatrixScaling(2.0f, 2.0f, 2.0f));
		// ρ]
		mW = XMMatrixMultiply(mW, XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(m_fRotate.x), XMConvertToRadians(m_fRotate.y), XMConvertToRadians(m_fRotate.z)));
		// ΐW
		mW = XMMatrixMultiply(mW, XMMatrixTranslation(200.0f, -150.0f, 0.0f));
		// ΟX½f
		XMStoreFloat4x4(&m_mW, mW);
		break;

	case SCENE_BATTLE_GOLEM:
	case SCENE_BATTLE_SM:
		// ©@ΜθΜΚuΙZbg
		if (m_pPlayer)
		{
			switch (GetWeapon())
			{
			case WEAPON_WOOD_SWORD:
				mW = XMMatrixRotationX(XMConvertToRadians(-90.0f));
				mW = XMMatrixMultiply(mW, XMMatrixTranslation(0.0f, -12.3f, 0.0f));
				mW = XMMatrixMultiply(mW, XMLoadFloat4x4(&m_pPlayer->GetParts(PARTS_MC_HAND_R).matrix));
				XMStoreFloat4x4(&m_mW, mW);
				break;
			case WEAPON_AXE:
				mW = XMMatrixRotationX(XMConvertToRadians(-90.0f));
				mW = XMMatrixMultiply(mW, XMMatrixTranslation(0.0f, -12.3f, 0.f));
				mW = XMMatrixMultiply(mW, XMLoadFloat4x4(&m_pPlayer->GetParts(PARTS_MC_HAND_R).matrix));
				XMStoreFloat4x4(&m_mW, mW);
				break;
			case WEAPON_LARGE_SWORD:
				mW = XMMatrixRotationX(XMConvertToRadians(-90.0f));
				mW = XMMatrixMultiply(mW, XMMatrixTranslation(0.0f, -12.3f, 0.f));
				mW = XMMatrixMultiply(mW, XMLoadFloat4x4(&m_pPlayer->GetParts(PARTS_MC_HAND_R).matrix));
				XMStoreFloat4x4(&m_mW, mW);
				break;
			}
		}
		break;
		
	default:
		break;
	}


#if 0
	CDebugProc::Print("*** Μή· ***\n");
	CDebugProc::Print("[Μή· : (%d)]\n", GetWeapon());
	CDebugProc::Print("[²Α  : (%f, %f, %f)]\n", m_mWorld._41, m_mWorld._42, m_mWorld._43);
	CDebugProc::Print("[cen : (%f, %f, %f)]\n", m_vCenter.x, m_vCenter.y, m_vCenter.z);
	CDebugProc::Print("[box : (%f, %f, %f)]\n", m_vBBox.x, m_vBBox.y, m_vBBox.z);
#endif
}


/*

	`ζ

*/
void CWeapon::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	CLight* pLight = CLight::Get();
	pLight->SetDisable();	// CeBO³ψ
	pLight->SetRimColor(m_fRimColor);	// CgΜFέθ

	if (m_pModel) { m_pModel->Draw(pDC, m_mW, eOpacityOnly, 1); }

	pLight->SetRimColorReset();	// CgΜFπί·
	pLight->SetEnable();	// CeBOLψ
}
void CWeapon::DrawAlpha()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	CLight* pLight = CLight::Get();
	pLight->SetDisable();	// CeBO³ψ
	pLight->SetRimColor(m_fRimColor);	// CgΜFέθ

	if (m_pModel) { m_pModel->Draw(pDC, m_mW, eTransparentOnly, 1); }

	CGameObj::DrawAlpha();

	pLight->SetRimColorReset();	// CgΜFπί·
	pLight->SetEnable();	// CeBOLψ
}