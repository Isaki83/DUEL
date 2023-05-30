//=============================================================================
//
// �I�����
// �p�����[�^�[�w�i [ParmBG.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "ParmBG.h"
#include "Polygon.h"


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CParmBG::CParmBG(CScene* pScene) : C2DObj(pScene)
{
	m_id = GOT_BG;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CParmBG::Init()
{
	HRESULT hr = C2DObj::Init();
	if (FAILED(hr)) { return hr; }

	//����������������������������������������
	// �ϐ�������
	//����������������������������������������
	m_fPos = XMFLOAT2(355.0f, 90.0f);
	m_fSize = XMFLOAT2(470.0f, 440.0f);
	m_fColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	return hr;
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CParmBG::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	//����������������������������������������
	// ����
	//����������������������������������������
	CPolygon::SetTexture(m_pTexture[TEX_BG_SELECT]);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetSize(m_fSize.x, m_fSize.y);
	CPolygon::SetColor(m_fColor);
	CPolygon::SetPos(m_fPos.x, m_fPos.y);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::Draw(pDC);

	SetBlendState(BS_NONE);
	SetZBuffer(true);
}
