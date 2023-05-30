//=============================================================================
//
// 武器パラメーターUI [WeaponParmUI.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include <stdio.h>
#include <string.h>
#include "WeaponParmUI.h"
#include "Polygon.h"
#include "Weapon.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// マクロ定義
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#define FONT_WIDTH	(65.0f)
#define FONT_HEIGHT	(65.0f)

/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コンストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CWeaponParmUI::CWeaponParmUI(CScene* pScene) : C2DObj(pScene)
{
	m_id = GOT_PARM;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT CWeaponParmUI::Init()
{
	HRESULT hr = C2DObj::Init();
	if (FAILED(hr)) { return hr; }

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 変数初期化
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	m_fPos = XMFLOAT2(240.0f, 120.0f);
	m_fSize = XMFLOAT2(70.0f * 3.0f, 70.0f);
	m_fColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);


	m_szPower[0] = '\0';
	m_iPower = 0;
	m_szSpeed[0] = '\0';
	m_iSpeed = 0;

	return hr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CWeaponParmUI::Update()
{
	// 攻撃力
	m_iPower = CWeapon::GetPower();
	sprintf_s(m_szPower, sizeof(m_szPower), "%d", m_iPower);
	// 速さ
	m_iSpeed = CWeapon::GetSpeed() * 10.0f;
	sprintf_s(m_szSpeed, sizeof(m_szSpeed), "%d", m_iSpeed);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	描画

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CWeaponParmUI::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 攻撃力	文字
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CPolygon::SetTexture(m_pTexture[TEX_WORD_POWER]);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetSize(m_fSize.x, m_fSize.y);
	CPolygon::SetColor(m_fColor);
	CPolygon::SetPos(m_fPos.x, m_fPos.y);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::Draw(pDC);
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 攻撃力	値
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	XMFLOAT2 fPos = XMFLOAT2(m_fPos.x - FONT_WIDTH * strlen(m_szPower) / 2.0f + 240.0f, m_fPos.y);
	CPolygon::SetTexture(m_pTexture[TEX_WORD_FONT]);
	CPolygon::SetFrameSize(8.0f / 128.0f, 8.0f / 128.0f);
	CPolygon::SetSize(FONT_WIDTH, FONT_HEIGHT);
	CPolygon::SetColor(m_fColor);
	for (const char* pChr = m_szPower; *pChr; ++pChr)
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

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 速さ	文字
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CPolygon::SetTexture(m_pTexture[TEX_WORD_SPEED]);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetSize(m_fSize.x, m_fSize.y);
	CPolygon::SetColor(m_fColor);
	CPolygon::SetPos(m_fPos.x, m_fPos.y - 150.0f);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::Draw(pDC);
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 速さ	値
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	fPos = XMFLOAT2(m_fPos.x - FONT_WIDTH * strlen(m_szSpeed) / 2.0f + 240.0f, m_fPos.y - 150.0f);
	CPolygon::SetTexture(m_pTexture[TEX_WORD_FONT]);
	CPolygon::SetFrameSize(8.0f / 128.0f, 8.0f / 128.0f);
	CPolygon::SetSize(FONT_WIDTH, FONT_HEIGHT);
	CPolygon::SetColor(m_fColor);
	for (const char* pChr = m_szSpeed; *pChr; ++pChr)
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