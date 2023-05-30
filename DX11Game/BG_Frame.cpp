/*������������������������������������������������������������������������������

	�w�i�g [BG_Frame.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#include "BG_Frame.h"
#include "Polygon.h"


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CBG_Frame::CBG_Frame(CScene* pScene) : C2DObj(pScene)
{
	m_id = GOT_BG;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CBG_Frame::Init()
{
	HRESULT hr = C2DObj::Init();
	if (FAILED(hr)) { return hr; }

	//����������������������������������������
	// �ϐ�������
	//����������������������������������������
	m_fPos = XMFLOAT2(0.0f, 0.0f);
	m_fSize = XMFLOAT2(1280.0f, 720.0f);
	m_fColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	return hr;
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CBG_Frame::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	//����������������������������������������
	// ����
	//����������������������������������������
	CPolygon::SetTexture(m_pTexture[TEX_BG_FRAME]);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetSize(m_fSize.x, m_fSize.y);
	CPolygon::SetColor(m_fColor);
	CPolygon::SetPos(m_fPos.x, m_fPos.y);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::Draw(pDC);

	SetBlendState(BS_NONE);
	SetZBuffer(true);
}
