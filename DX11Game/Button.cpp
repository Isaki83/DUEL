/*������������������������������������������������������������������������������

	�{�^�� [Button.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#include "Button.h"


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CButton::CButton(CScene* pScene) : C2DObj(pScene)
{
	m_id = GOT_2DOBJ;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CButton::Init()
{
	HRESULT hr = C2DObj::Init();
	if (FAILED(hr)) { return hr; }

	//����������������������������������������
	// �ϐ�������
	//����������������������������������������
	m_fPos = XMFLOAT2(0.0f, 0.0f);
	m_fSize = XMFLOAT2(0.0f, 0.0f);
	m_fColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	m_iID = 0;
	m_bIsNowSelect = false;
	m_fNowSelectPos = XMFLOAT2(0.0f, 0.0f);
	m_fNowSelectSize = XMFLOAT2(0.0f, 7.5f);
	m_fNowSelectMaxSize = 0.0f;

	SetCenter(m_fPos);
	SetBBox(XMFLOAT2(m_fSize.x / 2.0f, m_fSize.y / 2.0f));

	return hr;
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CButton::Update()
{
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CButton::Draw()
{
}

/*������������������������������������������������������������������������������

	�I�𒆂�����UI�̃T�C�Y����
	�������T�C�Y���ς��܂�

������������������������������������������������������������������������������*/
void CButton::NowSelectScaleUp()
{
	// ���ɐL�т�������X���[
	if ((m_bIsNowSelect) && (m_fNowSelectSize.x == m_fNowSelectMaxSize)) { return; }

	m_fNowSelectSize.x += m_fNowSelectMaxSize / 10.0f;
	if (m_fNowSelectMaxSize < m_fNowSelectSize.x)
	{
		m_fNowSelectSize.x = m_fNowSelectMaxSize;
		m_bIsNowSelect = true;
	}
}
void CButton::NowSelectScaleDown()
{
	// �k�݂�������X���[
	if ((!m_bIsNowSelect) && (m_fNowSelectSize.x == 0.0f)) { return; }

	m_fNowSelectSize.x -= m_fNowSelectMaxSize / 10.0f;
	if (m_fNowSelectSize.x < 0)
	{
		m_fNowSelectSize.x = 0.0f;
		m_bIsNowSelect = false;
	}
}