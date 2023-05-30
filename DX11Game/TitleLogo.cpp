/*������������������������������������������������������������������������������

	�^�C�g�����S [TitleLogo.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#include "TitleLogo.h"
#include "Polygon.h"


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CTitleLogo::CTitleLogo(CScene* pScene) : C2DObj(pScene)
{
	m_id = GOT_TITLE_LOGO;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CTitleLogo::Init()
{
	HRESULT hr = C2DObj::Init();
	if (FAILED(hr)) { return hr; }

	//����������������������������������������
	// �ϐ�������
	//����������������������������������������
	m_fPos = XMFLOAT2(0.0f, 100.0f);
	m_fSize = XMFLOAT2(600.0f, 150.0f);
	m_fColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.7f);

	return hr;
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CTitleLogo::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	//����������������������������������������
	// ����
	//����������������������������������������
	CPolygon::SetTexture(m_pTexture[TEX_WORD_DUEL]);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetSize(m_fSize.x, m_fSize.y);
	CPolygon::SetColor(m_fColor);
	CPolygon::SetPos(m_fPos.x, m_fPos.y);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::Draw(pDC);

	SetBlendState(BS_NONE);
	SetZBuffer(true);
}
