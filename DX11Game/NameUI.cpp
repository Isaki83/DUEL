//=============================================================================
//
// 武器と敵の名前 [NameUI.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "NameUI.h"
#include "Polygon.h"
#include "Weapon.h"
#include "EnemyManger.h"
#include "Fade.h"


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コンストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CNameUI::CNameUI(CScene* pScene) : C2DObj(pScene)
{
	m_id = GOT_BG;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT CNameUI::Init()
{
	HRESULT hr = C2DObj::Init();
	if (FAILED(hr)) { return hr; }

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 変数初期化
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	m_fPos = XMFLOAT2(355.0f, 250.0f);
	m_fSize = XMFLOAT2(140.0f, 70.0f);
	m_fColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	m_iTex = 0;
	m_fBGPos = 150.0f;

	return hr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void  CNameUI::Update()
{
	switch (CFade::GetScene())
	{
#pragma region ホーム画面
	case SCENE_WEAPON_SELECT:
		switch (CWeapon::GetCenterIcon())
		{
		case WEAPON_NONE:
			m_iTex = 0;
			break;
		case WEAPON_WOOD_SWORD:
			m_fSize.x = 140.0f;
			m_iTex = TEX_WORD_WSWORD;
			break;
		case WEAPON_AXE:
			m_fSize.x = 70.0f;
			m_iTex = TEX_WORD_AXE;
			break;
		case WEAPON_LARGE_SWORD:
			m_fSize.x = 140.0f;
			m_iTex = TEX_WORD_LSWORD;
			break;
		}
		break;
#pragma endregion
#pragma region 敵選択画面
	case SCENE_ENEMY_SELECT:
		switch (CEnemyManger::GetCenterIcon())
		{
		case ENEMY_NONE:
			m_iTex = 0;
			break;
		case ENEMY_GOLEM:
			m_fSize.x = 210.0f;
			m_iTex = TEX_WORD_GOLEM;
			break;
		case ENEMY_SWORDMAN:
			m_fSize.x = 210.0f;
			m_iTex = TEX_WORD_SWORDER;
			break;
		}
		break;
#pragma endregion
	default:
		break;
	}
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	描画

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CNameUI::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 背景
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CPolygon::SetTexture(m_pTexture[TEX_BUTTON_BG_01]);
	CPolygon::SetFrameSize(0.5f, 1.0f);
	CPolygon::SetSize(70.0f, m_fSize.y);
	CPolygon::SetColor(m_fColor);
	// 左
	CPolygon::SetPos(m_fPos.x - m_fBGPos, m_fPos.y);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::Draw(pDC);
	// 右
	CPolygon::SetPos(m_fPos.x + m_fBGPos, m_fPos.y);
	CPolygon::SetUV(0.5f, 0.0f);
	CPolygon::Draw(pDC);

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 文字
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CPolygon::SetTexture(m_pTexture[m_iTex]);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetSize(m_fSize.x, m_fSize.y);
	CPolygon::SetColor(m_fColor);
	CPolygon::SetPos(m_fPos.x, m_fPos.y);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::Draw(pDC);

	SetBlendState(BS_NONE);
	SetZBuffer(true);
}
