//=============================================================================
//
// �G [Enemy.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "Enemy.h"
#include "Fade.h"
#include "Player.h"
#include "2Dobj.h"

//����������������������������������������
// �萔
//����������������������������������������
#define GRAVITY				(0.98f)		// �d��
#define VELOCITY			(25.0f)		// �����x



/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CEnemy::CEnemy(CScene* pScene) : CModel(pScene)
{
	m_id = GOT_ENEMY;

	m_pGround = nullptr;
	m_pPlayer = nullptr;
}

/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CEnemy::Init()
{
	HRESULT hr = CModel::Init();
	if (FAILED(hr)) { return hr; }

	//����������������������������������������
	// �A�j���[�V�����֘A
	//����������������������������������������
	m_iAnimTime = XMINT2(0, 0);
	m_iAnimNum = 0;
	m_bNowAttack = false;

	//����������������������������������������
	// �p�j�p
	//����������������������������������������
	BaseState = STATE_ENEMY_NONE;
	m_iStatus = 0;
	m_iDoTime = rand() % 60;
	m_iDirections = 0;
	m_iWhatAttack = 0;
	m_fSpeedScale = 1.0f;

	//����������������������������������������
	// �W�����v�֘A
	//����������������������������������������
	m_fJumpStartPos = m_vPos;
	m_fJumpTime = 0.0f;
	m_bJumpFlag = true;

	//����������������������������������������
	// �����蔻��
	//����������������������������������������
	m_iSide = 0;

	//����������������������������������������
	// ���̑�
	//����������������������������������������
	m_fGravity = GRAVITY;
	m_fVelocity = VELOCITY;
	m_fPrevPos = m_vPos;
	m_fPrevPlayerPos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 5; i++) { m_iTmp[i] = 0; }
	m_bOnce = true;
	m_fDist = 0.0f;
	m_fPrevDist = 0.0f;
	m_bSceneChengeFlag = false;
	m_iTime = 0;
	m_vAngle = XMFLOAT3(0.0f, 180.0f, 0.0f);
	m_fRimColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	m_pGround = (CGround*)m_pScene->Find(GOT_GROUND);
	m_pPlayer = (CPlayer*)m_pScene->Find(GOT_PLAYER);
	m_pHPGaugePlayer = (CHPGaugePlayer*)m_pScene->Find2DObj(GOT_HP_GAUGE_PLAYER);

	return hr;
}

/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CEnemy::Update()
{
	//����������������������������������������
	// ���f���S�̂̃��[�J�����W���擾
	//����������������������������������������
	// X��
	XMFLOAT3 vX(m_mWorld._11, m_mWorld._12, m_mWorld._13);
	// Y��
	XMFLOAT3 vY(m_mWorld._21, m_mWorld._22, m_mWorld._23);
	// Z��
	XMFLOAT3 vZ(m_mWorld._31, m_mWorld._32, m_mWorld._33);

	//����������������������������������������
	// �V�[�����Ƃ̏���
	//����������������������������������������
	switch (CFade::GetScene())
	{
#pragma region �z�[�����
	case SCENE_HOME:
		m_vAngle.y += 0.5f;
		SetPos(XMFLOAT3(-200.0f, -160.0f, 150.0f));
		break;
#pragma endregion
#pragma region �G�I�����
	case SCENE_ENEMY_SELECT:
		m_vAngle.y += 0.5f;
		SetPos(XMFLOAT3(0.0f, -150.0f, 150.0f));
		break;
#pragma endregion
#pragma region �o�g�����
	case SCENE_BATTLE_GOLEM:
	case SCENE_BATTLE_SM:
		//����������������������������������������
		// �ǂɓ���������W�����v
		//����������������������������������������
		WallJump();

		//����������������������������������������
		// �̗͂� 0 �ɂȂ�����
		//����������������������������������������
		if (m_iLife <= 0) { BaseState = STATE_ENEMY_DEAD; }

		//����������������������������������������
		// �v���C���[�Ǝ����Ƃ̋���
		//����������������������������������������
		if (m_pPlayer)
		{
			XMVECTOR vT = XMVectorSet(m_vPos.x - m_pPlayer->GetPos().x,
				0.0f, m_vPos.z - m_pPlayer->GetPos().z, 0.0f);
			XMStoreFloat(&m_fDist, XMVector3Length(vT));
		}

		//����������������������������������������
		// ���ȏ�O�ɂ����Ȃ��悤�ɂ���
		//����������������������������������������
		if (m_vPos.x < -4900.0f) { m_vPos.x = -4900.0f; }
		else if (4900.0f < m_vPos.x) { m_vPos.x = 4900.0f; }
		if (m_vPos.z < -4900.0f) { m_vPos.z = -4900.0f; }
		else if (4900.0f < m_vPos.z) { m_vPos.z = 4900.0f; }

		//����������������������������������������
		// �n�ʂƂ̓����蔻��
		//����������������������������������������
		GroundCollision();
		break;
#pragma endregion
	default:
		break;
	}

	//����������������������������������������
	// �S�̂̃��[���h �}�g���b�N�X�X�V
	//����������������������������������������
	CGameObj::Update();

	//����������������������������������������
	// �e�p�[�c�̊p�x����}�g���b�N�X���쐬
	//����������������������������������������
	CalcMatrix();
}

/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CEnemy::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	CLight* pLight = CLight::Get();
	pLight->SetDisable();	// ���C�e�B���O����
	pLight->SetRimColor(m_fRimColor);	// �������C�g�̐F�ݒ�

	for (int i = 0; i < m_pMaxParts; ++i)
	{
		CAssimpModel* pModel = CModel::GetAssimp((EModel)m_parts[i].model);
		pModel->Draw(pDC, m_parts[i].matrix, eOpacityOnly, 1);
	}

	pLight->SetRimColorReset();	// �������C�g�̐F��߂�
	pLight->SetEnable();	// ���C�e�B���O�L��
}
void CEnemy::DrawAlpha()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	CLight* pLight = CLight::Get();
	pLight->SetDisable();	// ���C�e�B���O����
	pLight->SetRimColor(m_fRimColor);	// �������C�g�̐F�ݒ�

	for (int i = 0; i < m_pMaxParts; ++i)
	{
		CAssimpModel* pModel = CModel::GetAssimp((EModel)m_parts[i].model);
		pModel->Draw(pDC, m_parts[i].matrix, eTransparentOnly, 1);
	}

	CGameObj::DrawAlpha();

	pLight->SetRimColorReset();	// �������C�g�̐F��߂�
	pLight->SetEnable();	// ���C�e�B���O�L��
}


/*������������������������������������������������������������������������������

	�ړ�

	������ : ���[�J�����W��
	���C�� : ���� �u '+' or '-' �v
	��O���� : �X�s�[�h

������������������������������������������������������������������������������*/
void CEnemy::Move(XMFLOAT3 xyz, const char dir, float speed)
{
	switch (dir)
	{
	case '+':
		m_vPos.x += xyz.x * speed;
		m_vPos.y += xyz.y * speed;
		m_vPos.z += xyz.z * speed;
		break;

	case '-':
		m_vPos.x -= xyz.x * speed;
		m_vPos.y -= xyz.y * speed;
		m_vPos.z -= xyz.z * speed;
		break;

	default:
		break;
	}
}


/*������������������������������������������������������������������������������

	little by little
	�w�肵�����W�ɏ��������炷
	������ : ���̍��W
	���C�� : �ړI�̍��W
	��O���� : �X�s�[�h

	�ړI�̍��W�ɂ�����"true"
	���ĂȂ�������"false"

������������������������������������������������������������������������������*/
bool CEnemy::lblPos(XMFLOAT3 posA, XMFLOAT3 posB, float speed)
{
	if (m_vPos.x == posB.x && m_vPos.y == posB.y && m_vPos.z == posB.z) { return true; }
	else
	{
		// �ω���
		XMFLOAT3 fDelta = XMFLOAT3(posB.x - posA.x, posB.y - posA.y, posB.z - posA.z);
		// ���K��
		XMVECTOR vNorDelta = XMLoadFloat3(&fDelta);
		vNorDelta = XMVector3Normalize(vNorDelta);
		XMFLOAT3 fNorDelta;
		XMStoreFloat3(&fNorDelta, vNorDelta);

		// �ړ�
		Move(fNorDelta, '+', speed);

		// �ڕW�̍��W���s���߂��Ȃ��悤�ɂ���
		if (fNorDelta.x < 0) { if (m_vPos.x < posB.x) { m_vPos.x = posB.x; } }
		else { if (posB.x < m_vPos.x) { m_vPos.x = posB.x; } }
		if (fNorDelta.y < 0) { if (m_vPos.y < posB.y) { m_vPos.y = posB.y; } }
		else { if (posB.y < m_vPos.y) { m_vPos.y = posB.y; } }
		if (fNorDelta.z < 0) { if (m_vPos.z < posB.z) { m_vPos.z = posB.z; } }
		else { if (posB.z < m_vPos.z) { m_vPos.z = posB.z; } }

		return false;
	}
}
// XZ�������̈ړ�
bool CEnemy::lblPosXZ(XMFLOAT2 posA, XMFLOAT2 posB, float speed)
{
	if (m_vPos.x == posB.x && m_vPos.z == posB.y) { return true; }
	else
	{
		// �ω���
		XMFLOAT2 fDelta = XMFLOAT2(posB.x - posA.x, posB.y - posA.y);
		// ���K��
		XMVECTOR vNorDelta = XMLoadFloat2(&fDelta);
		vNorDelta = XMVector2Normalize(vNorDelta);
		XMFLOAT2 fNorDelta;
		XMStoreFloat2(&fNorDelta, vNorDelta);

		// �ړ�
		Move(XMFLOAT3(fNorDelta.x, 0.0f, fNorDelta.y), '+', speed);

		// �ڕW�̍��W���s���߂��Ȃ��悤�ɂ���
		if (fNorDelta.x < 0) { if (m_vPos.x < posB.x) { m_vPos.x = posB.x; } }
		else { if (posB.x < m_vPos.x) { m_vPos.x = posB.x; } }
		if (fNorDelta.y < 0) { if (m_vPos.z < posB.y) { m_vPos.z = posB.y; } }
		else { if (posB.y < m_vPos.z) { m_vPos.z = posB.y; } }

		return false;
	}
}


/*������������������������������������������������������������������������������

	�ǂɓ���������W�����v

������������������������������������������������������������������������������*/
void CEnemy::WallJump()
{
	if (m_bJumpFlag)
	{
		if ((m_iSide == 3) || (m_iSide == 4) || (m_iSide == 5) || (m_iSide == 6))
		{
			m_fJumpStartPos.y = m_vPos.y;
			m_fJumpTime = 0.0f;
			m_bJumpFlag = false;
		}
	}
	else
	{
		// ���������グ
		m_vPos.y = m_fVelocity * m_fJumpTime - (1.0f / 2.0f) * m_fGravity * pow(m_fJumpTime, 2) + m_fJumpStartPos.y;
		m_fJumpTime++;
		if (m_iSide == 2)
		{
			if (m_fJumpTime >= 5.0f) { m_bJumpFlag = true; }
		}
	}
}


/*������������������������������������������������������������������������������

	�p�x����}�g���b�N�X���v�Z(�S�p�[�c��)

������������������������������������������������������������������������������*/
void CEnemy::CalcMatrix()
{
	for (int i = 0; i < m_pMaxParts; ++i)
	{
		XMMATRIX mtx = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(m_parts[i].angle.x),
			XMConvertToRadians(m_parts[i].angle.y),
			XMConvertToRadians(m_parts[i].angle.z)) *
			XMMatrixTranslation(m_parts[i].off.x, m_parts[i].off.y, m_parts[i].off.z);
		if (m_parts[i].parent < 0) { mtx *= XMLoadFloat4x4(&GetWorld()); }
		else { mtx *= XMLoadFloat4x4(&m_parts[m_parts[i].parent].matrix); }
		XMStoreFloat4x4(&m_parts[i].matrix, mtx);
	}
}

/*������������������������������������������������������������������������������

	�n�ʂƂ̓����蔻��

������������������������������������������������������������������������������*/
void CEnemy::GroundCollision()
{
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
		// �n�ʂɂ߂荞�܂Ȃ�
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