/*������������������������������������������������������������������������������

	HP�o�[ [HPGauge.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#include "HPGauge.h"
#include "Polygon.h"


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CHPGauge::CHPGauge(CScene* pScene) : C2DObj(pScene)
{
	m_id = GOT_HP_GAUGE_E;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CHPGauge::Init()
{
	HRESULT hr = C2DObj::Init();
	if (FAILED(hr)) { return hr; }

	//����������������������������������������
	// �ϐ�������
	//����������������������������������������
	m_fPos = XMFLOAT2(0.0f, 0.0f);
	m_fSize = XMFLOAT2(0.0f, 0.0f);
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

	�X�V

������������������������������������������������������������������������������*/
void CHPGauge::Update()
{
	// �ԃQ�[�W��������茸�炷
	if (m_fGaugeSize.x < m_fDmgGaugeSize.x) { m_fDmgGaugeSize.x -= (m_fDmgGaugeSize.x - m_fGaugeSize.x) * 0.025f; }
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CHPGauge::Draw()
{
	
}


/*������������������������������������������������������������������������������

	�Q�[�W�����炷

������������������������������������������������������������������������������*/
void CHPGauge::SetDamage(float dmg)
{
	m_fDamage = dmg;
	// �΃Q�[�W�����炷
	m_fGaugeSize.x -= m_fDamage * m_fLife;
}