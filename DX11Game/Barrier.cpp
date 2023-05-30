/*������������������������������������������������������������������������������

	�o���A [Barrier.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#include "Barrier.h"
#include "Polygon.h"


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CBarrier::CBarrier(CScene* pScene) : C2DObj(pScene)
{
	m_id = GOT_BARRIER;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CBarrier::Init()
{
	HRESULT hr = C2DObj::Init();
	if (FAILED(hr)) { return hr; }

	//����������������������������������������
	// �ϐ�������
	//����������������������������������������
	m_fPos = XMFLOAT2(0.0f, 0.0f);
	m_fSize = XMFLOAT2(1280.0f, 720.0f);
	m_fColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	m_iTime = 0;

	return hr;
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CBarrier::Update()
{
	// ������܂ł̎���
	m_iTime--;
	if (m_iTime < 0)
	{
		Fin();
		delete this;
	}
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CBarrier::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	//����������������������������������������
	// �J�[�\��
	//����������������������������������������
	CPolygon::SetTexture(m_pTexture[TEX_BARRIER]);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetSize(m_fSize.x, m_fSize.y);
	CPolygon::SetColor(m_fColor);
	CPolygon::SetPos(m_fPos.x, m_fPos.y);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::Draw(pDC);

	SetBlendState(BS_NONE);
	SetZBuffer(true);
}


CBarrier* CBarrier::Create(CScene* pScene, int time)
{
	CBarrier* pBarrier = new CBarrier(pScene);

	pBarrier->Init();
	pBarrier->m_iTime = time;

	return pBarrier;
}