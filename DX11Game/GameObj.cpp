//=============================================================================
//
// オブジェクト クラス実装 [GameObj.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "GameObj.h"
#include "Scene.h"
#include "DebugProc.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// グローバル変数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
namespace {
	const CMeshMaterial g_material = {
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.3f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.3f),
		XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
		XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
		1.0f
	};
	const XMFLOAT4 g_vRed(1.0f, 0.0f, 0.0f, 0.3f);
	const XMFLOAT4 g_vGreen(0.0f, 1.0f, 0.0f, 0.3f);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コンストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CGameObj::CGameObj(CScene* pScene) : m_pScene(pScene)
{
	m_id = GOT_GAMEOBJ;

	m_pBack = NULL;
	CGameObj* pTop = m_pScene->GetObj();
	m_pNext = pTop;
	if (pTop) { pTop->m_pBack = this; }
	m_pScene->SetObj(this);

	m_vPos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_vVel = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_vAccel = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_vAngle = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_vScale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	XMStoreFloat4x4(&m_mWorld, XMMatrixIdentity());

	m_vCenter = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_vBBox = XMFLOAT3(0.5f, 0.5f, 0.5f);
	m_fRadius = 0.5f;

	m_bVisible = true;

	m_bt = BT_NONE;
	m_pBBox = nullptr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	デストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CGameObj::~CGameObj(void)
{
	if (m_pNext) { m_pNext->m_pBack = m_pBack; }
	if (m_pBack) { m_pBack->m_pNext = m_pNext; }
	else { m_pScene->SetObj(m_pNext); }
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT CGameObj::Init()
{
	return S_OK;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	解放

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CGameObj::Fin()
{
	SAFE_DELETE(m_pBBox);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CGameObj::Update()
{
	m_vVel.x += m_vAccel.x;
	m_vVel.y += m_vAccel.y;
	m_vVel.z += m_vAccel.z;

	m_vPos.x += m_vVel.x;
	m_vPos.y += m_vVel.y;
	m_vPos.z += m_vVel.z;

	XMMATRIX mtxWorld, mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化
	mtxWorld = XMMatrixIdentity();

	// スケールを反映
	mtxScl = XMMatrixScaling(m_vScale.x, m_vScale.y, m_vScale.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

	// 回転を反映
	mtxRot = XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_vAngle.x),
		XMConvertToRadians(m_vAngle.y), XMConvertToRadians(m_vAngle.z));
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	// 移動を反映
	mtxTranslate = XMMatrixTranslation(m_vPos.x, m_vPos.y, m_vPos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	// ワールドマトリックス設定
	XMStoreFloat4x4(&m_mWorld, mtxWorld);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	描画

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CGameObj::Draw()
{
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	半透明描画

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CGameObj::DrawAlpha()
{
	if (m_bt)
	{
		// 平行移動マトリックス生成
		XMMATRIX mMove = XMMatrixTranslation(m_vCenter.x, m_vCenter.y, m_vCenter.z);
		// ワールドマトリックスにかけ合わせる
		XMMATRIX mWorld = XMLoadFloat4x4(&m_mWorld);
		mWorld = XMMatrixMultiply(mMove, mWorld);

		// 境界ボックス表示
		XMFLOAT4X4 mW;
		XMStoreFloat4x4(&mW, mWorld);
		if (m_pBBox && m_bt == BT_OBB) 
		{
			m_pBBox->SetWorld(&mW);
			m_pBBox->Draw();
		}
	}
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	全初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT CGameObj::InitAll(CGameObj* pTop)
{
	HRESULT hr = S_OK;
	for (CGameObj* pObj = pTop; pObj; pObj = pObj->m_pNext) 
	{
		hr = pObj->Init();
		if (FAILED(hr)) { return hr; }
	}
	return hr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	全更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CGameObj::UpdateAll(CGameObj*& pTop)
{
	for (CGameObj* pObj = pTop; pObj; pObj = pObj->m_pNext)
	{ if (pObj->m_pBBox) { pObj->m_pBBox->SetMaterial(&g_material); } }

	CGameObj* pNext;
	for (CGameObj* pObj = pTop; pObj; pObj = pNext) 
	{
		pNext = pObj->m_pNext;
		pObj->Update();
	}
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	全描画

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CGameObj::DrawAll(CGameObj* pTop)
{
	// 不透明部分描画
	for (CGameObj* pObj = pTop; pObj; pObj = pObj->m_pNext) 
	{
		if (pObj->m_bVisible) { pObj->Draw(); }
	}

	// 半透明部分描画
	SetBlendState(BS_ALPHABLEND);
	SetZWrite(false);
	for (CGameObj* pObj = pTop; pObj; pObj = pObj->m_pNext) 
	{
		if (pObj->m_bVisible) { pObj->DrawAlpha(); }
	}
	SetZWrite(true);
	SetBlendState(BS_NONE);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	全終了処理

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CGameObj::FinAll(CGameObj* pTop)
{
	CGameObj* pNext;
	for (CGameObj* pObj = pTop; pObj; pObj = pNext) 
	{
		pNext = pObj->m_pNext;
		pObj->Fin();
		delete pObj;
	}
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	球同士の当たり判定

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CGameObj::CollisionSphere(CGameObj* pOther)
{
	if (pOther == this) { return false; }
	if (!m_bVisible || !pOther->m_bVisible) { return false; }
	// 中心座標を求める
	XMFLOAT3 vA, vB;
	XMStoreFloat3(&vA, XMVector3TransformCoord(XMLoadFloat3(&m_vCenter), XMLoadFloat4x4(&m_mWorld)));
	XMStoreFloat3(&vB, XMVector3TransformCoord(XMLoadFloat3(&pOther->m_vCenter), XMLoadFloat4x4(&pOther->m_mWorld)));
	
	float dx = vA.x - vB.x;
	float dy = vA.y - vB.y;
	float dz = vA.z - vB.z;
	float dr = m_fRadius + pOther->m_fRadius;

	return dx * dx + dy * dy + dz * dz <= dr * dr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	AABB同士の当たり判定

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CGameObj::CollisionAABB(CGameObj* pOther)
{
	XMFLOAT3 Apos, Asize;
	XMFLOAT3 Bpos, Bsize;

	if (!m_bVisible) { return false; }

	if (pOther == this) { return false; }
	if (!pOther->m_bVisible) { return false; }

	//--- A
	// 中心座標を求める
	XMStoreFloat3(&Apos, XMVector3TransformCoord(XMLoadFloat3(&m_vCenter), XMLoadFloat4x4(&m_mWorld)));
	// サイズを求める
	Asize = m_vBBox;
	//--- B
	// 中心座標を求める
	XMStoreFloat3(&Bpos, XMVector3TransformCoord(XMLoadFloat3(&pOther->m_vCenter), XMLoadFloat4x4(&pOther->m_mWorld)));
	// サイズを求める
	Bsize = pOther->m_vBBox;
	

	return (Apos.x - Asize.x <= Bpos.x + Bsize.x) &&
		(Bpos.x - Bsize.x <= Apos.x + Asize.x) &&
		(Apos.y - Asize.y <= Bpos.y + Bsize.y) &&
		(Bpos.y - Bsize.y <= Apos.y + Asize.y) &&
		(Apos.z - Asize.z <= Bpos.z + Bsize.z) &&
		(Bpos.z - Bsize.z <= Apos.z + Asize.z);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	AABB同士の当たり判定
	(触れた面識別用)

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
int CGameObj::ColliAABBSideNo(CGameObj* pOther)
{
	XMFLOAT3 Apos, Asize;
	XMFLOAT3 Bpos, Bsize;

	if (!m_bVisible) { return false; }

	if (pOther == this) { return false; }
	if (!pOther->m_bVisible) { return false; }

	//--- A
	// 中心座標を求める
	XMStoreFloat3(&Apos, XMVector3TransformCoord(XMLoadFloat3(&m_vCenter), XMLoadFloat4x4(&m_mWorld)));
	// サイズを求める
	Asize = m_vBBox;
	//--- B
	// 中心座標を求める
	XMStoreFloat3(&Bpos, XMVector3TransformCoord(XMLoadFloat3(&pOther->m_vCenter), XMLoadFloat4x4(&pOther->m_mWorld)));
	// サイズを求める
	Bsize = pOther->m_vBBox;
	

	if (!CollisionAABB(pOther)) { return 0; }

	float up = fabsf((Apos.y + Asize.y) - (Bpos.y - Bsize.y));
	float down = fabsf((Apos.y - Asize.y) - (Bpos.y + Bsize.y));
	float left = fabsf((Apos.x - Asize.x) - (Bpos.x + Bsize.x));
	float right = fabsf((Apos.x + Asize.x) - (Bpos.x - Bsize.x));
	float front = fabsf((Apos.z - Asize.z) - (Bpos.z + Bsize.z));
	float back = fabsf((Apos.z + Asize.z) - (Bpos.z - Bsize.z));

	// Y軸
	if (up < down && up < left && up < right && up < front && up < back)
	{ return 1; }
	else if (down < up && down < left && down < right && down < front && down < back)
	{ return 2; }
	// X軸
	else if (left < up && left < down && left < right && left < front && left < back)
	{ return 3; }
	else if (right < up && right < down && right < left && right < front && right < back)
	{ return 4; }
	// Z軸
	else if (front < up && front < down && front < left && front < right && front < back)
	{ return 5; }
	else if (back < up && back < down && back < left && back < right && back < front)
	{ return 6; }

	return 0;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	OBB同士の衝突判定

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CGameObj::CollisionOBB(CGameObj* pOther, XMFLOAT4X4 matrix, XMFLOAT3 center, XMFLOAT3 bbox, bool parts, int partsNum)
{
	if (pOther == this) { return false; }
	if (!m_bVisible || !pOther->m_bVisible) { return false; }
	// 相手側を階層構造で判定とらない
	if (parts)
	{
		// ワールド マトリックス取得
		XMFLOAT4X4 mW1 = matrix;
		XMFLOAT4X4 mW2 = pOther->GetWorld();
		// 中心座標取得
		XMFLOAT3 vP1, vP2;
		XMStoreFloat3(&vP1, XMVector3TransformCoord(XMLoadFloat3(&center), XMLoadFloat4x4(&mW1)));
		XMStoreFloat3(&vP2, XMVector3TransformCoord(XMLoadFloat3(&pOther->GetCenter()), XMLoadFloat4x4(&mW2)));
		// 中心座標間のベクトルを求める
		XMVECTOR vD;
		vD = XMVectorSet(vP2.x - vP1.x, vP2.y - vP1.y, vP2.z - vP1.z, 0.0f);
		// モデル座標軸を求める
		XMVECTOR vN[6];
		vN[0] = XMVectorSet(mW1._11, mW1._12, mW1._13, 0.0f);
		vN[1] = XMVectorSet(mW1._21, mW1._22, mW1._23, 0.0f);
		vN[2] = XMVectorSet(mW1._31, mW1._32, mW1._33, 0.0f);
		vN[3] = XMVectorSet(mW2._11, mW2._12, mW2._13, 0.0f);
		vN[4] = XMVectorSet(mW2._21, mW2._22, mW2._23, 0.0f);
		vN[5] = XMVectorSet(mW2._31, mW2._32, mW2._33, 0.0f);
		// OBBの大きさ(半分)を掛けたベクトルを求める
		XMFLOAT3& vBB1 = bbox;
		XMFLOAT3& vBB2 = pOther->GetBBox();
		XMVECTOR vL[6];
		vL[0] = XMVectorSet(mW1._11 * vBB1.x, mW1._12 * vBB1.x, mW1._13 * vBB1.x, 0.0f);
		vL[1] = XMVectorSet(mW1._21 * vBB1.y, mW1._22 * vBB1.y, mW1._23 * vBB1.y, 0.0f);
		vL[2] = XMVectorSet(mW1._31 * vBB1.z, mW1._32 * vBB1.z, mW1._33 * vBB1.z, 0.0f);
		vL[3] = XMVectorSet(mW2._11 * vBB2.x, mW2._12 * vBB2.x, mW2._13 * vBB2.x, 0.0f);
		vL[4] = XMVectorSet(mW2._21 * vBB2.y, mW2._22 * vBB2.y, mW2._23 * vBB2.y, 0.0f);
		vL[5] = XMVectorSet(mW2._31 * vBB2.z, mW2._32 * vBB2.z, mW2._33 * vBB2.z, 0.0f);
		// 分離軸候補が面の法線ベクトル(モデル座標軸)
		float fL, f, fD;
		for (int i = 0; i < 6; ++i)
		{
			XMVECTOR& vS = vN[i];//分離軸候補
			// OBBの影(の半分)の合計
			fL = 0.0f;
			for (int j = 0; j < 6; ++j)
			{
				XMStoreFloat(&f, XMVector3Dot(vS, vL[j]));
				fL += fabsf(f);
			}
			// 中心座標間の距離と比較
			XMStoreFloat(&fD, XMVector3Dot(vS, vD));
			fD = fabsf(fD);
			if (fL < fD) return false;// 当たっていない
		}
		// 分離軸候補がそれぞれの辺に垂直なベクトル
		XMVECTOR vS;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 3; j < 6; ++j)
			{
				// 分離軸候補を求める
				vS = XMVector3Normalize(XMVector3Cross(vN[i], vN[j]));
				// OBBの影(の半分)の合計
				fL = 0.0f;
				for (int k = 0; k < 6; ++k)
				{
					XMStoreFloat(&f, XMVector3Dot(vS, vL[k]));
					fL += fabsf(f);
				}
				// 中心座標間の距離と比較
				XMStoreFloat(&fD, XMVector3Dot(vS, vD));
				fD = fabsf(fD);
				if (fL < fD) return false;// 当たっていない
			}
		}
		return true;// 当たっている
	}
	// 相手側を階層構造で判定とる
	else
	{
		if (!pOther->m_parts[partsNum].use) { return false; }

		// ワールド マトリックス取得
		XMFLOAT4X4 mW1 = matrix;
		XMFLOAT4X4 mW2 = pOther->GetParts(partsNum).matrix;
		// 中心座標取得
		XMFLOAT3 vP1, vP2;
		XMStoreFloat3(&vP1, XMVector3TransformCoord(XMLoadFloat3(&center), XMLoadFloat4x4(&mW1)));
		XMStoreFloat3(&vP2, XMVector3TransformCoord(XMLoadFloat3(&pOther->GetParts(partsNum).center), XMLoadFloat4x4(&mW2)));
		// 中心座標間のベクトルを求める
		XMVECTOR vD;
		vD = XMVectorSet(vP2.x - vP1.x, vP2.y - vP1.y, vP2.z - vP1.z, 0.0f);
		// モデル座標軸を求める
		XMVECTOR vN[6];
		vN[0] = XMVectorSet(mW1._11, mW1._12, mW1._13, 0.0f);
		vN[1] = XMVectorSet(mW1._21, mW1._22, mW1._23, 0.0f);
		vN[2] = XMVectorSet(mW1._31, mW1._32, mW1._33, 0.0f);
		vN[3] = XMVectorSet(mW2._11, mW2._12, mW2._13, 0.0f);
		vN[4] = XMVectorSet(mW2._21, mW2._22, mW2._23, 0.0f);
		vN[5] = XMVectorSet(mW2._31, mW2._32, mW2._33, 0.0f);
		// OBBの大きさ(半分)を掛けたベクトルを求める
		XMFLOAT3& vBB1 = bbox;
		XMFLOAT3& vBB2 = pOther->GetParts(partsNum).bbox;
		XMVECTOR vL[6];
		vL[0] = XMVectorSet(mW1._11 * vBB1.x, mW1._12 * vBB1.x, mW1._13 * vBB1.x, 0.0f);
		vL[1] = XMVectorSet(mW1._21 * vBB1.y, mW1._22 * vBB1.y, mW1._23 * vBB1.y, 0.0f);
		vL[2] = XMVectorSet(mW1._31 * vBB1.z, mW1._32 * vBB1.z, mW1._33 * vBB1.z, 0.0f);
		vL[3] = XMVectorSet(mW2._11 * vBB2.x, mW2._12 * vBB2.x, mW2._13 * vBB2.x, 0.0f);
		vL[4] = XMVectorSet(mW2._21 * vBB2.y, mW2._22 * vBB2.y, mW2._23 * vBB2.y, 0.0f);
		vL[5] = XMVectorSet(mW2._31 * vBB2.z, mW2._32 * vBB2.z, mW2._33 * vBB2.z, 0.0f);
		// 分離軸候補が面の法線ベクトル(モデル座標軸)
		float fL, f, fD;
		for (int i = 0; i < 6; ++i)
		{
			XMVECTOR& vS = vN[i];//分離軸候補
			// OBBの影(の半分)の合計
			fL = 0.0f;
			for (int j = 0; j < 6; ++j)
			{
				XMStoreFloat(&f, XMVector3Dot(vS, vL[j]));
				fL += fabsf(f);
			}
			// 中心座標間の距離と比較
			XMStoreFloat(&fD, XMVector3Dot(vS, vD));
			fD = fabsf(fD);
			if (fL < fD) return false;// 当たっていない
		}
		// 分離軸候補がそれぞれの辺に垂直なベクトル
		XMVECTOR vS;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 3; j < 6; ++j)
			{
				// 分離軸候補を求める
				vS = XMVector3Normalize(XMVector3Cross(vN[i], vN[j]));
				// OBBの影(の半分)の合計
				fL = 0.0f;
				for (int k = 0; k < 6; ++k)
				{
					XMStoreFloat(&f, XMVector3Dot(vS, vL[k]));
					fL += fabsf(f);
				}
				// 中心座標間の距離と比較
				XMStoreFloat(&fD, XMVector3Dot(vS, vD));
				fD = fabsf(fD);
				if (fL < fD) return false;// 当たっていない
			}
		}
		//CDebugProc::Print("[num  : (%d]\n", pOther->m_parts[partsNum].num);
		return true;// 当たっている
	}
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	境界ボックス設定

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CGameObj::SetBBox(XMFLOAT3 vBBox)
{
	if (m_pBBox) 
	{
		m_pBBox->Fin();
		SAFE_DELETE(m_pBBox);
	}

	m_vBBox = vBBox;

	m_pBBox = new CBox();
	HRESULT hr = m_pBBox->Init(vBBox);
	if (FAILED(hr)) 
	{
		m_pBBox->Fin();
		SAFE_DELETE(m_pBBox);
	}
	m_pBBox->SetMaterial(&g_material);
}
