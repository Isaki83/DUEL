/*������������������������������������������������������������������������������

	���{�^�� [ArrowButton.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#include "ArrowButton.h"
#include "Polygon.h"
#include "Scene.h"
#include "Input.h"


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CArrowButton::CArrowButton(CScene* pScene) : CButton(pScene)
{
	m_id = GOT_BUTTON_ARROW;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CArrowButton::Init()
{
	HRESULT hr = CButton::Init();
	if (FAILED(hr)) { return hr; }

	//����������������������������������������
	// �ϐ�������
	//����������������������������������������
	m_fPos = XMFLOAT2(0.0f, 0.0f);
	m_fSize = XMFLOAT2(70.0f, 70.0f);
	m_fColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	m_fDirection = 0.0f;
	
	SetCenter(m_fPos);
	SetBBox(XMFLOAT2(40.0f, 40.0f));

	return hr;
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CArrowButton::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	//����������������������������������������
	// �w�i
	//����������������������������������������
	CPolygon::SetTexture(m_pTexture[TEX_BUTTON_BG_01]);
	CPolygon::SetFrameSize(0.5f, 1.0f);
	CPolygon::SetSize(m_fSize.x, m_fSize.y);
	CPolygon::SetColor(m_fColor);
	CPolygon::SetPos(m_fPos.x, m_fPos.y);
	CPolygon::SetUV(m_fDirection, 0.0f);
	CPolygon::Draw(pDC);

	SetBlendState(BS_NONE);
	SetZBuffer(true);
}


/*������������������������������������������������������������������������������

	���̌���

	����
	0 ... right
	1 ... left

������������������������������������������������������������������������������*/
void CArrowButton::SetDirection(int dir)
{
	switch (dir)
	{
	case 0:
		m_fDirection = 0.5f;
		break;

	case 1:
		m_fDirection = 0.0f;
		break;
	}
}