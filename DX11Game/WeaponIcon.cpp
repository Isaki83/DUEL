/*������������������������������������������������������������������������������

	����A�C�R�� [WeaponIcon.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#include "WeaponIcon.h"
#include "Polygon.h"
#include "Weapon.h"
#include "Fade.h"

/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CWeaponIcon::CWeaponIcon(CScene* pScene) : C2DObj(pScene)
{
	m_id = GOT_ICON;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CWeaponIcon::Init()
{
	HRESULT hr = C2DObj::Init();
	if (FAILED(hr)) { return hr; }

	//����������������������������������������
	// �ϐ�������
	//����������������������������������������
	m_fPos = XMFLOAT2(-600.0f, 320.0f);
	m_fSize = XMFLOAT2(70.0f, 70.0f);
	m_fColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	m_fTruePos = m_fPos;
	m_fSpeed = 0.0f;

	return hr;
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CWeaponIcon::Update()
{
	switch (CFade::GetScene())
	{
		// ����I�����
	case SCENE_WEAPON_SELECT:
		// �A�C�R�����،�(���W�̎��ɂ��Ă���A�C�R��)��������
		if (GetSubID() == GOTSUB_WSWORD)
		{
			if (m_fPos.x != m_fTruePos.x) { m_fPos.x += m_fSpeed; }
			else { m_fTruePos = m_fPos; }
		}

		// �I�𒆂Ȃ�Ԃ��t���[����������悤�ɂ���
		if (CWeapon::GetWeapon() == GetSubID()) { SetColorA(1.0f); }
		else { SetColorA(0.0f); }

		break;

	default:
		break;
	}
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CWeaponIcon::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	//����������������������������������������
	// �A�C�R��
	//����������������������������������������
	switch (CFade::GetScene())
	{
	// ����I�����
	case SCENE_WEAPON_SELECT:
		CPolygon::SetTexture(m_pTexture[m_iTex]);
		CPolygon::SetFrameSize(1.0f, 1.0f);
		CPolygon::SetSize(m_fSize.x, m_fSize.y);
		CPolygon::SetColor(XMFLOAT4(m_fColor.x, m_fColor.y, m_fColor.z, 1.0f));
		CPolygon::SetPos(m_fPos.x, m_fPos.y);
		CPolygon::SetUV(0.0f, 0.0f);
		CPolygon::Draw(pDC);

		CPolygon::SetTexture(m_pTexture[TEX_ICON_FRAME]);
		CPolygon::SetFrameSize(1.0f, 1.0f);
		CPolygon::SetSize(m_fSize.x, m_fSize.y);
		CPolygon::SetColor(XMFLOAT4(1.0f, 0.0f, 0.0f, m_fColor.w));
		CPolygon::SetPos(m_fPos.x, m_fPos.y);
		CPolygon::SetUV(0.0f, 0.0f);
		CPolygon::Draw(pDC);
		break;

	// �o�g�����
	case SCENE_BATTLE_GOLEM:
	case SCENE_BATTLE_SM:
		switch (CWeapon::GetWeapon())
		{
		case WEAPON_NONE:
			break;
		case WEAPON_WOOD_SWORD:
			CPolygon::SetTexture(m_pTexture[TEX_ICON_WSWORD]);
			break;
		case WEAPON_AXE:
			CPolygon::SetTexture(m_pTexture[TEX_ICON_AXE]);
			break;
		case WEAPON_LARGE_SWORD:
			CPolygon::SetTexture(m_pTexture[TEX_ICON_LSWORD]);
			break;
		}
		CPolygon::SetFrameSize(1.0f, 1.0f);
		CPolygon::SetSize(m_fSize.x, m_fSize.y);
		CPolygon::SetColor(m_fColor);
		CPolygon::SetPos(m_fPos.x, m_fPos.y);
		CPolygon::SetUV(0.0f, 0.0f);
		CPolygon::Draw(pDC);
		break;
	}

	SetBlendState(BS_NONE);
	SetZBuffer(true);
}