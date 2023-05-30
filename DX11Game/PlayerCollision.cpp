/*������������������������������������������������������������������������������

	�v���C���[(�����蔻��) [PlayerCollision.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#include "Player.h"
#include "Ground.h"
#include "Scene.h"


/*������������������������������������������������������������������������������

	�n�ʂƂ̓����蔻��

������������������������������������������������������������������������������*/
void CPlayer::GroundCollision()
{
	//����������������������������������������
	// �������Ă���n�ʂ̖�
	//����������������������������������������
	CGameObj* pNext;
	for (CGameObj* pObj = m_pScene->GetObj(); pObj; pObj = pNext)
	{
		pNext = pObj->GetNext();
		if (pObj->GetID() != GOT_GROUND) { continue; }

		// �����̒��S���W�����߂�
		XMFLOAT3 posA;
		XMStoreFloat3(&posA, XMVector3TransformCoord(XMLoadFloat3(&GetCenter()), XMLoadFloat4x4(&GetWorld())));
		// �n�ʂ̃T�C�Y�����߂�
		XMFLOAT3 sizeA = GetBBox();

		// �n�ʂ̒��S���W�����߂�
		XMFLOAT3 posB;
		XMStoreFloat3(&posB, XMVector3TransformCoord(XMLoadFloat3(&pObj->GetCenter()), XMLoadFloat4x4(&pObj->GetWorld())));
		// �n�ʂ̃T�C�Y�����߂�
		XMFLOAT3 sizeB = pObj->GetBBox();

		// �ǂ̖ʂɂ������Ă��邩
		m_iSide = ColliAABBSideNo(pObj);

		//����������������������������������������
		// �߂荞�܂Ȃ�
		//����������������������������������������
		// �ǂꂾ���߂荞��ł��邩
		XMFLOAT3 Overlap;
		Overlap.x = (sizeA.x + sizeB.x) - fabs(posA.x - posB.x);
		Overlap.y = (sizeA.y + sizeB.y) - fabs(posA.y - posB.y);
		Overlap.z = (sizeA.z + sizeB.z) - fabs(posA.z - posB.z);

		// Y��
		if (m_iSide == 1) { m_vPos.y -= Overlap.y / 2.0f; }
		else if (m_iSide == 2) { m_vPos.y += Overlap.y; }
		// X��
		if (m_iSide == 3) { m_vPos.x += Overlap.x / 2.0f; }
		else if (m_iSide == 4) { m_vPos.x -= Overlap.x / 2.0f; }
		// Z��
		if (m_iSide == 5) { m_vPos.z += Overlap.z / 2.0f; }
		else if (m_iSide == 6) { m_vPos.z -= Overlap.z / 2.0f; }
	}
}
