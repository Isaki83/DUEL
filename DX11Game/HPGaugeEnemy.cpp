//=============================================================================
//
// HP�Q�[�W(�G) [HPGaugeEnemy.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "HPGaugeEnemy.h"
#include "Polygon.h"

/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CHPGaugeEnemy::CHPGaugeEnemy(CScene* pScene) : CHPGauge(pScene)
{
	m_id = GOT_HP_GAUGE_E;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CHPGaugeEnemy::Init()
{
	HRESULT hr = CHPGauge::Init();
	if (FAILED(hr)) { return hr; }

	//����������������������������������������
	// �ϐ�������
	//����������������������������������������
	m_fPos = XMFLOAT2(-300.0f, -250.0f);
	m_fSize = XMFLOAT2(1400.0f, 20.0f);
	m_fColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	// �ԐF�̃Q�[�W
	m_fDmgGaugePos = XMFLOAT2(m_fPos.x, m_fPos.y);
	m_fDmgGaugeSize = XMFLOAT2(m_fSize.x, m_fSize.y);
	// �ΐF�̃Q�[�W
	m_fGaugePos = XMFLOAT2(m_fPos.x, m_fPos.y);
	m_fGaugeSize = XMFLOAT2(m_fSize.x, m_fSize.y);

	m_fLife = 0.0f;
	m_fDamage = 0.0f;

	return hr;
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CHPGaugeEnemy::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	//����������������������������������������
	// �w�i
	//����������������������������������������
	CPolygon::SetTexture(m_pTexture[TEX_HP_GAUGE_BG]);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetSize(m_fSize.x, m_fSize.y);
	CPolygon::SetColor(m_fColor);
	CPolygon::SetPos(m_fPos.x, m_fPos.y);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::Draw(pDC);

	//����������������������������������������
	// �_���[�W
	//����������������������������������������
	CPolygon::SetTexture(m_pTexture[TEX_HP_GAUGE_DMG]);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetSize(m_fDmgGaugeSize.x, m_fDmgGaugeSize.y);
	CPolygon::SetColor(m_fColor);
	CPolygon::SetPos(m_fDmgGaugePos.x, m_fDmgGaugePos.y);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::Draw(pDC);

	//����������������������������������������
	// �Q�[�W
	//����������������������������������������
	CPolygon::SetTexture(m_pTexture[TEX_HP_GAUGE]);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetSize(m_fGaugeSize.x, m_fGaugeSize.y);
	CPolygon::SetColor(m_fColor);
	CPolygon::SetPos(m_fGaugePos.x, m_fGaugePos.y);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::Draw(pDC);

	SetBlendState(BS_NONE);
	SetZBuffer(true);
}
