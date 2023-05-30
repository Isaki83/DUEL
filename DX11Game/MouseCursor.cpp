/*������������������������������������������������������������������������������

	�}�E�X�J�[�\�� [MouseCursor.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#include "MouseCursor.h"
#include "Polygon.h"
#include "Manager.h"
#include "Input.h"


//����������������������������������������
// �}�N����`
//����������������������������������������
// �R���g���[���[�p
#define SPEED	(10)


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CMouseCursor::CMouseCursor(CScene* pScene) : C2DObj(pScene)
{
	m_id = GOT_MOUSECURSOR;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CMouseCursor::Init()
{
	HRESULT hr = C2DObj::Init();
	if (FAILED(hr)) { return hr; }

	//����������������������������������������
	// �ϐ�������
	//����������������������������������������
	m_fPos = XMFLOAT2(0.0f, 0.0f);
	m_fSize = XMFLOAT2(40.0f, 40.0f);
	m_fColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	SetCenter(m_fPos);
	SetBBox(XMFLOAT2(0.1f, 0.1f));

	return hr;
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CMouseCursor::Update()
{
	SetCenter(m_fPos);

	// �R���g���[���[�Ȃ�J�[�\��������
	if (0 < CInput::GetJoyCount()) { m_bVisible = false; }
	// �}�E�X
	else
	{
		m_bVisible = true;
		m_fPos.x = GetMouseClientPos().x - GetWindowSize().x / 2.0f;
		m_fPos.y = -(GetMouseClientPos().y - GetWindowSize().y / 2.0f);
	}
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CMouseCursor::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	//����������������������������������������
	// �J�[�\��
	//����������������������������������������
	CPolygon::SetTexture(m_pTexture[TEX_MOUSECURSOR]);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetSize(m_fSize.x, m_fSize.y);
	CPolygon::SetColor(m_fColor);
	CPolygon::SetPos(m_fPos.x, m_fPos.y);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::Draw(pDC);

	SetBlendState(BS_NONE);
	SetZBuffer(true);
}
