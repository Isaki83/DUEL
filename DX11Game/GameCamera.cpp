//=============================================================================
//
// �Q�[�� �J���� [GameCamera.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "GameCamera.h"
#include "Model.h"
#include "Input.h"
#include "Fade.h"
#include "DebugProc.h"

//����������������������������������������
// �O���[�o���ϐ�
//����������������������������������������
namespace 
{
	const float CAM_POS_P_X = 0.0f;		// ��_�J�����̎��_�ʒu(X���W)
	const float CAM_POS_P_Y = 100.0f;	// ��_�J�����̎��_�ʒu(Y���W)
	const float CAM_POS_P_Z = 600.0f;	// ��_�J�����̎��_�ʒu(Z���W)
	const float CAM_POS_R_X = 0.0f;		// ��_�J�����̒����_�ʒu(X���W)
	const float CAM_POS_R_Y = 0.0f;	// ��_�J�����̒����_�ʒu(Y���W)
	const float CAM_POS_R_Z = 0.0f;		// ��_�J�����̒����_�ʒu(Z���W)

	const float FP_POS_P_X = 0.0f;		// ��l�̃J�����̎��_�ʒu(X���W)
	const float FP_POS_P_Y = 232.3f;	// ��l�̃J�����̎��_�ʒu(Y���W)
	const float FP_POS_P_Z = -20.0f;	// ��l�̃J�����̎��_�ʒu(Z���W)
	const float FP_POS_R_X = 0.0f;		// ��l�̃J�����̒����_�ʒu(X���W)
	const float FP_POS_R_Y = 232.3f;	// ��l�̃J�����̒����_�ʒu(Y���W)
	const float FP_POS_R_Z = -45.00f;	// ��l�̃J�����̒����_�ʒu(Z���W)

	const float TP_POS_P_X = -150.0f;	// �O�l�̃J�����̎��_�ʒu(X���W)
	const float TP_POS_P_Y = 232.3f;	// �O�l�̃J�����̎��_�ʒu(Y���W)
	const float TP_POS_P_Z = 500.0f;	// �O�l�̃J�����̎��_�ʒu(Z���W)
	const float TP_POS_R_X = 0.0f;		// �O�l�̃J�����̒����_�ʒu(X���W)
	const float TP_POS_R_Y = 232.3f;		// �O�l�̃J�����̒����_�ʒu(Y���W)
	const float TP_POS_R_Z = -10000.0f;	// �O�l�̃J�����̒����_�ʒu(Z���W)
};


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CGameCamera::CGameCamera()
{
	m_pPlayer = nullptr;
	m_fRadius = 1.0f;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
void CGameCamera::Init()
{
	CCamera::Init();

	m_iLookMe = 0;

	SetSky(CModel::GetAssimp(MODEL_SKY));
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CGameCamera::Update()
{
	if (m_pPlayer) 
	{
		if (CInput::GetKeyTrigger(VK_F5))
		{
			m_iLookMe = (m_iLookMe + 1) % 2;
		}

		XMMATRIX mW;
		XMFLOAT3 vNewUp, vNewTarget, vNewPos;
		mW = XMLoadFloat4x4(&m_pPlayer->GetWorld());

		switch (m_iLookMe)
		{
		case 0:
			// �O�l�̃J����
			XMStoreFloat3(&vNewUp, XMVector3TransformNormal(XMVectorSet(0, 1, 0, 0), mW));
			XMStoreFloat3(&vNewTarget, XMVector3TransformCoord(XMVectorSet(TP_POS_R_X, TP_POS_R_Y, TP_POS_R_Z, 1.0f), mW));
			XMStoreFloat3(&vNewPos, XMVector3TransformCoord(XMVectorSet(TP_POS_P_X, TP_POS_P_Y, TP_POS_P_Z, 1.0f), mW));

			m_vUp.x = m_vUp.x * 0.9f + vNewUp.x * 0.1f;
			m_vUp.y = m_vUp.y * 0.9f + vNewUp.y * 0.1f;
			m_vUp.z = m_vUp.z * 0.9f + vNewUp.z * 0.1f;
			m_vTarget.x = m_vTarget.x * 0.9f + vNewTarget.x * 0.1f;
			m_vTarget.y = m_vTarget.y * 0.9f + vNewTarget.y * 0.1f;
			m_vTarget.z = m_vTarget.z * 0.9f + vNewTarget.z * 0.1f;
			m_vPos.x = m_vPos.x * 0.9f + vNewPos.x * 0.1f;
			m_vPos.y = m_vPos.y * 0.9f + vNewPos.y * 0.1f;
			m_vPos.z = m_vPos.z * 0.9f + vNewPos.z * 0.1f;
			break;
		case 1:
			// ��l�̃J����
			XMStoreFloat3(&vNewUp, XMVector3TransformNormal(XMVectorSet(0, 1, 0, 0), mW));
			XMStoreFloat3(&vNewTarget, XMVector3TransformCoord(XMVectorSet(FP_POS_R_X, FP_POS_R_Y, FP_POS_R_Z, 1.0f), mW));
			XMStoreFloat3(&vNewPos, XMVector3TransformCoord(XMVectorSet(FP_POS_P_X, FP_POS_P_Y, FP_POS_P_Z, 1.0f), mW));

			m_vUp = vNewUp;
			m_vTarget = vNewTarget;
			m_vPos = vNewPos;
			break;
		default:
			break;
		}
	} 
	else 
	{
		switch (CFade::GetScene())
		{
		case SCENE_TITLE:
			m_vPos = XMFLOAT3(CAM_POS_P_X + 100.0f, CAM_POS_P_Y + 550.0f, CAM_POS_P_Z - 100.0f);
			m_vTarget = XMFLOAT3(CAM_POS_R_X + 100.0f, CAM_POS_R_Y + 500.0f, CAM_POS_R_Z);
			m_vUp = XMFLOAT3(0.0f, 1.0f, 0.0f);
			break;
		default:
			m_vPos = XMFLOAT3(CAM_POS_P_X, CAM_POS_P_Y, CAM_POS_P_Z);
			m_vTarget = XMFLOAT3(CAM_POS_R_X, CAM_POS_R_Y, CAM_POS_R_Z);
			m_vUp = XMFLOAT3(0.0f, 1.0f, 0.0f);
			break;
		}
	}

	CCamera::Update();
	
#if 0
	CDebugProc::Print("*** ��� ***\n");
	CDebugProc::Print("[��     : (%f, %f, %f)]\n", m_vPos.x, m_vPos.y, m_vPos.z);
	CDebugProc::Print("[������ : (%f, %f, %f)]\n", m_vTarget.x, m_vTarget.y, m_vTarget.z);
	CDebugProc::Print("\n");
#endif
}