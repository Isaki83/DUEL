/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	プレイヤー(当たり判定) [PlayerCollision.cpp]
	Author : ISAKI SUGIURA

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
#include "Player.h"
#include "Ground.h"
#include "Scene.h"


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	地面との当たり判定

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CPlayer::GroundCollision()
{
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 当たっている地面の面
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CGameObj* pNext;
	for (CGameObj* pObj = m_pScene->GetObj(); pObj; pObj = pNext)
	{
		pNext = pObj->GetNext();
		if (pObj->GetID() != GOT_GROUND) { continue; }

		// 自分の中心座標を求める
		XMFLOAT3 posA;
		XMStoreFloat3(&posA, XMVector3TransformCoord(XMLoadFloat3(&GetCenter()), XMLoadFloat4x4(&GetWorld())));
		// 地面のサイズを求める
		XMFLOAT3 sizeA = GetBBox();

		// 地面の中心座標を求める
		XMFLOAT3 posB;
		XMStoreFloat3(&posB, XMVector3TransformCoord(XMLoadFloat3(&pObj->GetCenter()), XMLoadFloat4x4(&pObj->GetWorld())));
		// 地面のサイズを求める
		XMFLOAT3 sizeB = pObj->GetBBox();

		// どの面にあたっているか
		m_iSide = ColliAABBSideNo(pObj);

		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		// めり込まない
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		// どれだけめり込んでいるか
		XMFLOAT3 Overlap;
		Overlap.x = (sizeA.x + sizeB.x) - fabs(posA.x - posB.x);
		Overlap.y = (sizeA.y + sizeB.y) - fabs(posA.y - posB.y);
		Overlap.z = (sizeA.z + sizeB.z) - fabs(posA.z - posB.z);

		// Y軸
		if (m_iSide == 1) { m_vPos.y -= Overlap.y / 2.0f; }
		else if (m_iSide == 2) { m_vPos.y += Overlap.y; }
		// X軸
		if (m_iSide == 3) { m_vPos.x += Overlap.x / 2.0f; }
		else if (m_iSide == 4) { m_vPos.x -= Overlap.x / 2.0f; }
		// Z軸
		if (m_iSide == 5) { m_vPos.z += Overlap.z / 2.0f; }
		else if (m_iSide == 6) { m_vPos.z -= Overlap.z / 2.0f; }
	}
}
