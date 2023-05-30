/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	2DObj [2DObj.cpp]
	Author : ISAKI SUGIURA

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
#include "2DObj.h"
#include "Texture.h"
#include "Scene.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// グローバル変数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
namespace
{
	LPCTSTR PATH_TEXTURE[MAX_TEXTURE] = {
		// マウスカーソル
		_T("data/texture/MouseCursor.png"),
		// 背景枠
		_T("data/texture/BG_Frame01.png"),
		_T("data/texture/SelectBG.png"),
		// ボタン
		_T("data/texture/nowSelect.png"),
		_T("data/texture/ButtonBG01.png"),
		_T("data/texture/Return.png"),
		// 文字
		_T("data/texture/Word/font.png"),
		_T("data/texture/Word/Duel.png"),
		_T("data/texture/Word/Start.png"),
		_T("data/texture/Word/Weapon.png"),
		_T("data/texture/Word/Monster.png"),
		_T("data/texture/Word/DuelStart.png"),
		_T("data/texture/Word/Decision.png"),
		_T("data/texture/Word/Exit.png"),
		_T("data/texture/Word/WoodSword.png"),
		_T("data/texture/Word/Axe.png"),
		_T("data/texture/Word/LargeSword.png"),
		_T("data/texture/Word/Golem.png"),
		_T("data/texture/Word/Sworder.png"),
		_T("data/texture/Word/Power.png"),
		_T("data/texture/Word/Speed.png"),
		// HPゲージ
		_T("data/texture/HPGaugeBG.png"),
		_T("data/texture/HPGaugeDmg.png"),
		_T("data/texture/HPGauge.png"),
		// アイコン
		_T("data/texture/Icon/Frame.png"),
		_T("data/texture/Icon/WSword_Icon.png"),
		_T("data/texture/Icon/Axe_Icon.png"),
		_T("data/texture/Icon/LSword_Icon.png"),
		_T("data/texture/Icon/Golem_Icon.png"),
		_T("data/texture/Icon/SwordMan_Icon.png"),
		_T("data/texture/Barrier.png"),
	};
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 静的メンバ変数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
ID3D11ShaderResourceView* C2DObj::m_pTexture[MAX_TEXTURE];


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コンストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
C2DObj::C2DObj(CScene* pScene) : m_pScene(pScene)
{
	m_id = GOT_2DOBJ;
	m_subid = GOT_2DOBJSUB;

	m_pBack = NULL;
	C2DObj* pTop = m_pScene->Get2DObj();
	m_pNext = pTop;
	if (pTop) { pTop->m_pBack = this; }
	m_pScene->Set2DObj(this);

	m_fPos = XMFLOAT2(0.0f, 0.0f);
	m_fSize = XMFLOAT2(0.0f, 0.0f);
	m_fColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	m_fCenter = XMFLOAT2(0.0f, 0.0f);
	m_fBBox = XMFLOAT2(0.5f, 0.5f);

	m_bVisible = true;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	デストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
C2DObj::~C2DObj(void)
{
	if (m_pNext) { m_pNext->m_pBack = m_pBack; }
	if (m_pBack) { m_pBack->m_pNext = m_pNext; }
	else { m_pScene->Set2DObj(m_pNext); }
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT C2DObj::Init()
{
	return S_OK;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	解放

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void C2DObj::Fin()
{
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void C2DObj::Update()
{
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	描画

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void C2DObj::Draw()
{
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	全初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT C2DObj::InitAll(C2DObj* pTop)
{
	HRESULT hr = S_OK;
	for (C2DObj* pObj = pTop; pObj; pObj = pObj->m_pNext)
	{
		hr = pObj->Init();
		if (FAILED(hr)) { return hr; }
	}
	return hr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	全更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void C2DObj::UpdateAll(C2DObj*& pTop)
{
	C2DObj* pNext;
	for (C2DObj* pObj = pTop; pObj; pObj = pNext)
	{
		pNext = pObj->m_pNext;
		pObj->Update();
	}
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	全描画

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void C2DObj::DrawAll(C2DObj* pTop)
{
	C2DObj* pNext;
	for (C2DObj* pObj = pTop; pObj; pObj = pNext)
	{
		pNext = pObj->m_pNext;
		if (pObj->m_bVisible) { pObj->Draw(); }
	}
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	全終了処理

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void C2DObj::FinAll(C2DObj* pTop)
{
	C2DObj* pNext;
	for (C2DObj* pObj = pTop; pObj; pObj = pNext)
	{
		pNext = pObj->m_pNext;
		pObj->Fin();
		delete pObj;
	}
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	当たり判定

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
// AABB同士
bool C2DObj::CollisionAABB(C2DObj* ObjA, C2DObj* ObjB)
{
	if (ObjA == ObjB) { return false; }
	if (!ObjA->m_bVisible) { return false; }
	if (!ObjB->m_bVisible) { return false; }

	return (ObjA->m_fCenter.x - ObjA->m_fBBox.x <= ObjB->m_fCenter.x + ObjB->m_fBBox.x) &&
			(ObjB->m_fCenter.x - ObjB->m_fBBox.x <= ObjA->m_fCenter.x + ObjA->m_fBBox.x) &&
			(ObjA->m_fCenter.y - ObjA->m_fBBox.y <= ObjB->m_fCenter.y + ObjB->m_fBBox.y) &&
			(ObjB->m_fCenter.y - ObjB->m_fBBox.y <= ObjA->m_fCenter.y + ObjA->m_fBBox.y);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	テクスチャ読込

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT C2DObj::LoadAll()
{
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr = S_OK;

	ReleaseAll();

	// テクスチャの読み込み
	for (int i = 0; i < MAX_TEXTURE; ++i)
	{
		hr = CreateTextureFromFile(pDevice, PATH_TEXTURE[i], &m_pTexture[i]);
		if (FAILED(hr)) { break; }
	}

	return hr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	テクスチャ開放

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void C2DObj::ReleaseAll()
{
	for (int i = 0; i < MAX_TEXTURE; ++i) { SAFE_RELEASE(m_pTexture[i]); }
}