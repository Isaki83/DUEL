/*

	X^[{^ [MonsterButton.cpp]
	Author : ISAKI SUGIURA

*/
#include "MonsterButton.h"
#include "Polygon.h"
#include "Scene.h"
#include "Input.h"


/*

	RXgN^

*/
CMonsterButton::CMonsterButton(CScene* pScene) : CButton(pScene)
{
	m_id = GOT_BUTTON_MONSTER;
}


/*

	ú»

*/
HRESULT CMonsterButton::Init()
{
	HRESULT hr = CButton::Init();
	if (FAILED(hr)) { return hr; }

	//
	// Ïú»
	//
	m_fPos = XMFLOAT2(400.0f, -285.0f);
	m_fSize = XMFLOAT2(350.0f, 70.0f);
	m_fColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	m_fNowSelectPos = XMFLOAT2(m_fPos.x, m_fPos.y - (m_fSize.y / 2.5f));
	m_fNowSelectMaxSize = 400.0f;

	SetCenter(m_fPos);
	SetBBox(XMFLOAT2(m_fNowSelectMaxSize / 2.0f, m_fSize.y / 2.0f));

	return hr;
}


/*

	`æ

*/
void CMonsterButton::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	//
	// ¶
	//
	CPolygon::SetTexture(m_pTexture[TEX_WORD_MONSTER]);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetSize(m_fSize.x, m_fSize.y);
	CPolygon::SetColor(m_fColor);
	CPolygon::SetPos(m_fPos.x, m_fPos.y);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::Draw(pDC);

	//
	// IðUI
	//
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
