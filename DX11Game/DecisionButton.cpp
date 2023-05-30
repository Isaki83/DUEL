/*������������������������������������������������������������������������������

	����{�^�� [DecisionButton.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#include "DecisionButton.h"
#include "Polygon.h"
#include "Scene.h"
#include "Input.h"


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CDecisionButton::CDecisionButton(CScene* pScene) : CButton(pScene)
{
	m_id = GOT_BUTTON_DECISION;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CDecisionButton::Init()
{
	HRESULT hr = CButton::Init();
	if (FAILED(hr)) { return hr; }

	//����������������������������������������
	// �ϐ�������
	//����������������������������������������
	m_fPos = XMFLOAT2(0.0f, -175.0f);
	m_fSize = XMFLOAT2(140.0f, 70.0f);
	m_fColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	m_fBGPos = 100.0f;
	m_iTime = 0;
	m_fAdd = 0.25f;

	m_fNowSelectPos = XMFLOAT2(m_fPos.x, m_fPos.y - (m_fSize.y / 2.5f));
	m_fNowSelectMaxSize = m_fSize.x;

	SetCenter(m_fPos);
	SetBBox(XMFLOAT2(m_fSize.x / 2.0f, m_fSize.y / 2.0f));

	return hr;
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CDecisionButton::Update()
{
	// �����̍��E�́u<>�v���ӂ�ӂ킷��
	m_iTime++;
	m_fBGPos += m_fAdd;
	if (30 < m_iTime)
	{
		m_fAdd *= -1.0f;
		m_iTime = 0;
	}
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CDecisionButton::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	//����������������������������������������
	// �w�i
	//����������������������������������������
	CPolygon::SetTexture(m_pTexture[TEX_BUTTON_BG_01]);
	CPolygon::SetFrameSize(0.5f, 1.0f);
	CPolygon::SetSize(m_fSize.x * 0.5f, m_fSize.y);
	CPolygon::SetColor(m_fColor);
	// ��
	CPolygon::SetPos(m_fPos.x - m_fBGPos, m_fPos.y);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::Draw(pDC);
	// �E
	CPolygon::SetPos(m_fPos.x + m_fBGPos, m_fPos.y);
	CPolygon::SetUV(0.5f, 0.0f);
	CPolygon::Draw(pDC);

	//����������������������������������������
	// ����
	//����������������������������������������
	CPolygon::SetTexture(m_pTexture[TEX_WORD_DECISION]);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetSize(m_fSize.x, m_fSize.y);
	CPolygon::SetColor(m_fColor);
	CPolygon::SetPos(m_fPos.x, m_fPos.y);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::Draw(pDC);

	//����������������������������������������
	// �I��UI
	//����������������������������������������
	CPolygon::SetTexture(m_pTexture[TEX_BUTTON_NOW_SELE]);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetSize(m_fNowSelectSize.x, m_fNowSelectSize.y);
	CPolygon::SetColor(m_fColor);
	CPolygon::SetPos(m_fNowSelectPos.x, m_fNowSelectPos.y);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::Draw(pDC);

	SetBlendState(BS_NONE);
	SetZBuffer(true);
}