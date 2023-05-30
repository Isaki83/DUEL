//=============================================================================
//
// ���̉J [SwordRain.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "SwordRain.h"
#include "Player.h"
#include "HPGaugePlayer.h"
#include "Scene.h"
#include "DebugProc.h"

#define MAX_SPEED	(100)


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CSwordRain::CSwordRain(CScene* pScene) : CModel(pScene)
{
	m_id = GOT_SWORD_RAIN;

	m_pModel = nullptr;

	m_pPlayer = nullptr;
	m_pHPGaugePlayer = nullptr;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CSwordRain::Init()
{
	HRESULT hr = CModel::Init();

	//����������������������������������������
	// �ϐ�������
	//����������������������������������������
	m_pModel = CModel::GetAssimp(MODEL_BLACK_SWORD);
	SetCenter(m_pModel->GetCenter());
	SetBBox(XMFLOAT3(m_pModel->GetBBox().x * 3.0f, m_pModel->GetBBox().y, m_pModel->GetBBox().z * 3.0f));
	m_fRimColor = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	m_fAcssel = 1.5f;
	hit = true;
	cnttemp = 0;
	terget = 60;

	m_pPlayer = (CPlayer*)m_pScene->Find(GOT_PLAYER);
	m_pHPGaugePlayer = (CHPGaugePlayer*)m_pScene->Find2DObj(GOT_HP_GAUGE_PLAYER);

	return hr;
}


/*������������������������������������������������������������������������������

	�I������

������������������������������������������������������������������������������*/
void CSwordRain::Fin()
{
	CModel::Fin();
}

/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CSwordRain::Update()
{
	//����������������������������������������
	// ���f���S�̂̃��[�J�����W���擾
	//����������������������������������������
	// Y��
	XMFLOAT3 vY(m_mWorld._21, m_mWorld._22, m_mWorld._23);

	
	CGameObj* pNext;
	for (CGameObj* pObj = m_pScene->GetObj(); pObj; pObj = pNext)
	{
		pNext = pObj->GetNext();
		//����������������������������������������
		// �n�ʂƂ̓����蔻��
		//����������������������������������������
		if (pObj->GetID() == GOT_GROUND)
		{
			// �������Ă��Ȃ�
			if (!CollisionOBB(pObj, GetWorld(), GetCenter(), GetBBox()))
			{
				m_fAcssel = pow(m_fAcssel, 1.5);
				if (MAX_SPEED < m_fAcssel) { m_fAcssel = MAX_SPEED; }
				//����������������������������������������
				// ����������
				//����������������������������������������
				m_vPos.x -= vY.x * m_fAcssel;
				m_vPos.y -= vY.y * m_fAcssel;
				m_vPos.z -= vY.z * m_fAcssel;
			}
		}
		
		//����������������������������������������
		// �v���C���[�Ƃ̓����蔻��
		//����������������������������������������
		if (pObj->GetID() == GOT_PLAYER)
		{
			if (hit)
			{
				if (CollisionOBB(pObj, GetWorld(), GetCenter(), GetBBox()))
				{
					m_pPlayer->LifeDmg(200);
					m_pHPGaugePlayer->SetDamage(200);
					hit = false;
				}
			}
		}
	}

	//����������������������������������������
	// ���Ԃ������������
	//����������������������������������������
	cnttemp++;
	if (cnttemp > terget)
	{
		Fin();
		delete this;
	}

	//����������������������������������������
	// �S�̂̃��[���h �}�g���b�N�X�X�V
	//����������������������������������������
	CGameObj::Update();

#if 0
	CDebugProc::Print("*** SwordRain ***\n");
	CDebugProc::Print("[pos   : %f, %f, %f]\n", m_vPos.x, m_vPos.y, m_vPos.z);
	CDebugProc::Print("[angle : %f, %f, %f]\n", m_vAngle.x, m_vAngle.y, m_vAngle.z);
#endif
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CSwordRain::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	CLight* pLight = CLight::Get();
	pLight->SetDisable();	// ���C�e�B���O����
	pLight->SetRimColor(m_fRimColor);	// �������C�g�̐F�ݒ�

	if (m_pModel) { m_pModel->Draw(pDC, GetWorld(), eOpacityOnly, 1); }

	pLight->SetRimColorReset();	// �������C�g�̐F��߂�
	pLight->SetEnable();	// ���C�e�B���O�L��
}
void CSwordRain::DrawAlpha()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	CLight* pLight = CLight::Get();
	pLight->SetDisable();	// ���C�e�B���O����
	pLight->SetRimColor(m_fRimColor);	// �������C�g�̐F�ݒ�

	if (m_pModel) { m_pModel->Draw(pDC, GetWorld(), eTransparentOnly, 1); }

	pLight->SetRimColorReset();	// �������C�g�̐F��߂�
	pLight->SetEnable();	// ���C�e�B���O�L��
}


/*������������������������������������������������������������������������������

	����

������������������������������������������������������������������������������*/
CSwordRain* CSwordRain::Creat(CScene* pScene, XMFLOAT4X4& mtxWorld)
{
	CSwordRain* pSwordRain = new CSwordRain(pScene);
	pSwordRain->Init();
	// ���W(�G�̏������XZ+-800�Ń����_��)
	pSwordRain->SetPos(XMFLOAT3(
		mtxWorld._41 + (rand() % 1600 - 800),
		mtxWorld._42 + 1000.0f,
		mtxWorld._43 + (rand() % 1600 - 800)));
	// �p�x(YZ�����_��)
	pSwordRain->SetAngle(XMFLOAT3(
		0.0f, 
		(float)(rand() % 180),
		(float)(rand() % 60 - 30)));

	return pSwordRain;
}