//=============================================================================
//
// ���ꂽ�n�� [BreakGround.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "BreakGround.h"
#include "Player.h"
#include "HPGaugePlayer.h"
#include "Scene.h"
#include "DebugProc.h"


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CBreakGround::CBreakGround(CScene* pScene) : CModel(pScene)
{
	m_id = GOT_BREAK_GROUND;

	m_pPlayer = nullptr;
	m_pHPGaugePlayer = nullptr;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CBreakGround::Init()
{
	HRESULT hr = CModel::Init();
	
	SetModel(MODEL_BREAK_GROUND);

	//����������������������������������������
	// �ϐ�������
	//����������������������������������������
	once = true;
	cnttemp = 0;
	terget = 30;

	m_pPlayer = (CPlayer*)m_pScene->Find(GOT_PLAYER);
	m_pHPGaugePlayer = (CHPGaugePlayer*)m_pScene->Find2DObj(GOT_HP_GAUGE_PLAYER);

	return hr;
}


/*������������������������������������������������������������������������������

	�I������

������������������������������������������������������������������������������*/
void CBreakGround::Fin()
{
	CModel::Fin();
}

/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CBreakGround::Update()
{
	if (once)
	{
		CGameObj* pNext;
		for (CGameObj* pObj = m_pScene->GetObj(); pObj; pObj = pNext)
		{
			pNext = pObj->GetNext();
			if (pObj->GetID() != GOT_PLAYER) { continue; }
			if (CollisionOBB(pObj, GetWorld(), GetCenter(), GetBBox())) 
			{ 
				m_pPlayer->LifeDmg(200); 
				m_pHPGaugePlayer->SetDamage(200);
			}
		}
		once = false;
	}

	cnttemp++;
	if (cnttemp > terget)
	{
		Fin();
		delete this;
	}


#if 0
	CDebugProc::Print("*** BreakGround ***\n");
#endif
}

/*������������������������������������������������������������������������������

	����

������������������������������������������������������������������������������*/
CBreakGround* CBreakGround::Creat(CScene* pScene, XMFLOAT4X4& mtxWorld)
{
	CBreakGround* pBreakGround = new CBreakGround(pScene);
	pBreakGround->Init();

	pBreakGround->SetWorld(mtxWorld);

	return pBreakGround;
}