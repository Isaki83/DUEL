/*������������������������������������������������������������������������������

	�_���[�W [Damage.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#include <stdio.h>
#include <string.h>
#include "Damage.h"
#include "Polygon.h"
#include "Camera.h"

//����������������������������������������
// �}�N����`
//����������������������������������������
#define FONT_WIDTH	(30.0f)
#define FONT_HEIGHT	(30.0f)

/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CDamage::CDamage(CScene* pScene) : C2DObj(pScene)
{
	m_id = GOT_DAMAGE;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CDamage::Init()
{
	HRESULT hr = C2DObj::Init();
	if (FAILED(hr)) { return hr; }

	//����������������������������������������
	// �ϐ�������
	//����������������������������������������
	m_szStat[0] = '\0';
	m_iDamage = 0;

	return hr;
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CDamage::Update()
{
#pragma region �r���{�[�h
	CCamera* pCamera = CCamera::Get();
	XMFLOAT4X4& mV = pCamera->GetViewMatrix();
	XMFLOAT4X4& mP = pCamera->GetProjMatrix();
	// �r���{�[�h�p���[���h�ϊ�
	XMFLOAT4X4 mW(mV._11, mV._21, mV._31, 0.0f,
		mV._12, mV._22, mV._32, 0.0f,
		mV._13, mV._23, mV._33, 0.0f,
		m_fWorldPos.x, m_fWorldPos.y, m_fWorldPos.z, 1.0f);
	// �r���[�|�[�g�ϊ�
	XMFLOAT4X4 mVP(SCREEN_WIDTH / 2.0f, 0.0f, 0.0f, 0.0f,
		0.0f, SCREEN_HEIGHT / 2.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	// �}�g���b�N�X������
	XMMATRIX matrix = XMLoadFloat4x4(&mW) * XMLoadFloat4x4(&mV) * XMLoadFloat4x4(&mP) * XMLoadFloat4x4(&mVP);
	// ���S���W�A�������W�A�E����W��2D���W�ɕϊ�
	static const XMFLOAT3 v = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT4 vPos;
	XMStoreFloat4(&vPos, XMVector3Transform(XMLoadFloat3(&v), matrix));
	// �������_��񓯎����_�ɕϊ�
	vPos.x /= vPos.w;
	vPos.y /= vPos.w;
	vPos.z /= vPos.w;
	// �Ə����S
	m_fPos.x = vPos.x;
	m_fPos.y = vPos.y;
#pragma endregion

	sprintf_s(m_szStat, sizeof(m_szStat), "%d", m_iDamage);

	m_fColor.w -= 0.05f;
	if (m_fColor.w <= 0.0f)
	{
		Fin();
		delete this;
	}
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CDamage::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	//����������������������������������������
	// �_���[�W
	//����������������������������������������
	XMFLOAT2 fPos(m_fPos.x - FONT_WIDTH * strlen(m_szStat) / 2.0f, m_fPos.y);
	CPolygon::SetTexture(m_pTexture[TEX_WORD_FONT]);
	CPolygon::SetFrameSize(8.0f / 128.0f, 8.0f / 128.0f);
	CPolygon::SetSize(FONT_WIDTH, FONT_HEIGHT);
	CPolygon::SetColor(XMFLOAT4(1.0f, 0.0f, 0.0f, m_fColor.w));
	for (const char* pChr = m_szStat; *pChr; ++pChr)
	{
		if (*pChr == '\n')
		{
			fPos.x = m_fPos.x + FONT_WIDTH * 0.5f;
			fPos.y += FONT_HEIGHT;
			continue;
		}
		int nChr = (BYTE)*pChr;
		CPolygon::SetPos(fPos.x, fPos.y);
		CPolygon::SetUV((nChr & 15) / 16.0f, (nChr >> 4) / 16.0f);
		CPolygon::Draw(pDC);
		fPos.x += FONT_WIDTH;
	}

	SetBlendState(BS_NONE);
	SetZBuffer(true);
}

CDamage* CDamage::Create(CScene* pScene, XMFLOAT4X4& mtxWorld, int dmg)
{

	CDamage* pDamage = new CDamage(pScene);
	pDamage->m_iDamage = dmg;

	pDamage->m_fWorldPos.x = mtxWorld._41;
	pDamage->m_fWorldPos.y = mtxWorld._42;
	pDamage->m_fWorldPos.z = mtxWorld._43;

	return pDamage;
}