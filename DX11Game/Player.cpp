/*������������������������������������������������������������������������������

	�v���C���[ [Player.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#include "Player.h"
#include "Weapon.h"
#include "EnemyManger.h"
#include "Barrier.h"
#include "Input.h"
#include "DebugProc.h"
#include "GameCamera.h"
#include "Fade.h"
#include "Manager.h"
#include "Golem.h"
#include "SwordMan.h"


//����������������������������������������
// �萔
//����������������������������������������
#define RADIUS				(140.0f)
#define SPEED				(20.0f)
#define MAX_LIFE			(1000)
#define GRAVITY				(0.98f)		// �d��
#define VELOCITY0			(25.0f)		// �����x
#define AVOID_TIME			(10)		// ���(���G)����
#define MOUSE_SENSITIVITY	(0.1f)		// �}�E�X���x


//����������������������������������������
// �p�[�c�����f�[�^
//����������������������������������������
static TPartsData jintai_data[MAX_MC_PARTS] =
{ // �e�p�[�cNo.				���f���ԍ�		�I�t�Z�b�g�l					�_���[�W�{��
	{-1,					MODEL_LOOT,		{  0.0f,   0.0f,  0.0f},	0.0f},
	{PARTS_MC_LOOT,			MODEL_MC_BODY,	{  0.0f, 133.8f,  0.0f},	0.0f},
	{PARTS_MC_BODY,			MODEL_MC_ARM,	{ -38.1f, 59.5f,  0.0f},	0.0f},
	{PARTS_MC_ARM_UP_R,		MODEL_MC_ARM,	{  0.0f,  -55.3f, 0.0f},	0.0f},
	{PARTS_MC_ARM_DOWN_R,	MODEL_MC_HAND,	{  0.0f,  -54.4f, 0.0f},	0.0f},
};


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CPlayer::CPlayer(CScene* pScene) : CModel(pScene)
{
	m_id = GOT_PLAYER;

	m_pGround = nullptr;
	m_pWeapon = nullptr;
	m_pGolem = nullptr;
	m_pSwordMan = nullptr;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CPlayer::Init()
{
	HRESULT hr = CModel::Init();
	if (FAILED(hr)) { return hr; }


	//����������������������������������������
	// �ϐ�������
	//����������������������������������������
	TParts parts[MAX_PARTS];
	for (int i = 0; i < MAX_MC_PARTS; ++i)
	{
		if (i == 0) { parts[i].use = false; }
		else { parts[i].use = true; }
		parts[i].parent = jintai_data[i].parent;
		parts[i].model = jintai_data[i].model;
		parts[i].off = jintai_data[i].off;
		parts[i].angle = XMFLOAT3(0.0f, 0.0f, 0.0f);
		parts[i].DmgRatio = jintai_data[i].DmgRatio;
		parts[i].hitDefence = false;
		parts[i].hitAttack = false;
		parts[i].num = i;
		CAssimpModel* pModel = CModel::GetAssimp((EModel)parts[i].model);
		parts[i].center = pModel->GetCenter();
		parts[i].bbox = pModel->GetBBox();

		m_parts.push_back(parts[i]);
	}
	CalcMatrix();

	SetRadius(RADIUS);
	SetCenter(XMFLOAT3( 0.0f, 130.0f, 0.0f));
	SetBBox(XMFLOAT3(40.0f, 130.0f, 40.0f));

	m_bIsAttack = false;
	m_iAnimFin = false;

	m_fJumpStartPos = m_vPos;
	m_fJumpTime = 0.0f;
	m_bJumpFlag = true;

	m_iLife = MAX_LIFE;
	m_bMoveFlag = false;
	m_bTargetEnemy = false;
	m_bAvoidFlag = false;
	m_iAvoidDir = 0;
	m_iAvoidTimeCnt = 0;
	m_fSpeedScale = 1.0f;
	m_bSceneChengeFlag = false;

	m_vAngle = XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_pGround = (CGround*)m_pScene->Find(GOT_GROUND);
	m_pWeapon = (CWeapon*)m_pScene->Find(GOT_WEAPON);
	m_pGolem = (CGolem*)m_pScene->Find(GOT_ENEMY);
	m_pSwordMan = (CSwordMan*)m_pScene->Find(GOT_ENEMY);

	//����������������������������������������
	// �A�j���[�V���� �f�[�^�Ǎ�
	//����������������������������������������
	m_animSet.Init();


	return hr;
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CPlayer::Update()
{
	//����������������������������������������
	// �A�j���[�V���������邽�߂�
	//����������������������������������������
	// ���Ԃ���p�x����`��Ԃŋ��߂�
	for (int i = 0; i < MAX_MC_PARTS; ++i) { m_parts[i].angle = m_animSet.GetAngle(i); }
	// ���Ԃƃt���[����i�߂�
	m_iAnimFin = m_animSet.AddTimer();


	//����������������������������������������
	// ���f���S�̂̃��[�J�����W���擾
	//����������������������������������������
	// X��
	XMFLOAT3 vX(m_mWorld._11, m_mWorld._12, m_mWorld._13);
	// Z��
	XMFLOAT3 vZ(m_mWorld._31, m_mWorld._32, m_mWorld._33);


	//����������������������������������������
	// �U������
	//����������������������������������������
	if (!m_bIsAttack)
	{
		m_animSet.Play(ANIM_MC_BASE);

		if (CInput::GetMouseTrigger(MOUSEBUTTON_L) || CInput::GetJoyTrigger(0, JOYBUTTON_A))
		{
			if (CWeapon::GetWeapon()) { m_bIsAttack = !m_bIsAttack; }
		}

		//����������������������������������������
		// ���f���S�̂̈ړ�
		//����������������������������������������
		// �R���g���[���[
		if (0 < CInput::GetJoyCount())
		{
			// �ړ�
			Move(vZ, '+', CInput::GetJoyLeftStick(0).y * SPEED * CInput::GetJoyLeftSlope(0).y * m_fSpeedScale);
			Move(vX, '-', CInput::GetJoyLeftStick(0).x * SPEED * CInput::GetJoyLeftSlope(0).x * m_fSpeedScale);
			// ���
			if (!m_bAvoidFlag && CInput::GetJoyTrigger(0, JOYBUTTON_B))
			{
				CBarrier::Create(m_pScene, AVOID_TIME);
				m_bAvoidFlag = true;
			}
			// �������
			if (m_bAvoidFlag)
			{
				m_iAvoidTimeCnt++;
				m_fSpeedScale = 6.0f;

				if (CInput::GetJoyLeftStick(0).x == 0 && CInput::GetJoyLeftStick(0).y)
				{ Move(vZ, '-', SPEED * m_fSpeedScale); }

				if (AVOID_TIME < m_iAvoidTimeCnt)
				{
					m_fSpeedScale = 1.0f;
					m_iAvoidTimeCnt = 0;
					m_bAvoidFlag = false;
				}
			}
		}
		// �L�[�{�[�h
		else
		{
			// ��𒆂���Ȃ�
			if (!m_bAvoidFlag)
			{
				// �O�i
				if (CInput::GetKeyPress(VK_W))
				{
					if (CInput::GetKeyPress(VK_SHIFT)) { Move(vZ, '-', SPEED * 1.5f * m_fSpeedScale); }
					else { Move(vZ, '-', SPEED * m_fSpeedScale); }
				}
				// ��i
				else if (CInput::GetKeyPress(VK_S)) { Move(vZ, '+', SPEED * m_fSpeedScale); }
				// ��
				if (CInput::GetKeyPress(VK_A)) { Move(vX, '+', SPEED * m_fSpeedScale); }
				// �E
				if (CInput::GetKeyPress(VK_D)) { Move(vX, '-', SPEED * m_fSpeedScale); }
				// ���
				if (CInput::GetKeyTrigger(VK_SPACE))
				{
					if (CInput::GetKeyPress(VK_S)) { m_iAvoidDir = 1; }
					else if (CInput::GetKeyPress(VK_A)) { m_iAvoidDir = 2; }
					else if (CInput::GetKeyPress(VK_D)) { m_iAvoidDir = 3; }
					else { m_iAvoidDir = 0; }

					CBarrier::Create(m_pScene, AVOID_TIME);
					m_bAvoidFlag = true;
				}
			}
			else
			{
				// �������
				if (m_bAvoidFlag)
				{
					m_iAvoidTimeCnt++;
					m_fSpeedScale = 6.0f;

					switch (m_iAvoidDir)
					{
					case 0:
						Move(vZ, '-', SPEED * m_fSpeedScale);
						break;
					case 1:
						Move(vZ, '+', SPEED * m_fSpeedScale);
						break;
					case 2:
						Move(vX, '+', SPEED * m_fSpeedScale);
						break;
					case 3:
						Move(vX, '-', SPEED * m_fSpeedScale);
						break;
					default:
						break;
					}

					if (AVOID_TIME < m_iAvoidTimeCnt)
					{
						m_fSpeedScale = 1.0f;
						m_iAvoidTimeCnt = 0;
						m_bAvoidFlag = false;
					}
				}
			}
		}
	}
	else
	{
		switch (CWeapon::GetWeapon())
		{
		case WEAPON_NONE:
			m_bIsAttack = false;
			break;
		default:
			m_animSet.Play(ANIM_MC_ATTACK_01, CWeapon::GetSpeed());
			// �����蔻����Ƃ�^�C�~���O
			if ((MC_ATTACK_01_START <= m_animSet.GetTimer(ANIM_MC_ATTACK_01)) && (m_animSet.GetTimer(ANIM_MC_ATTACK_01) <= MC_ATTACK_01_END))
			{ m_pWeapon->GolemCollision(CWeapon::GetWeapon()); }
			break;
		}

		//����������������������������������������
		// �A�j���[�V�������I�������ҏW���[�h on
		//����������������������������������������
		if (m_iAnimFin) { m_bIsAttack = false; }
	}

	//����������������������������������������
	// �n�ʂɑ������Ă��Ȃ�������
	//����������������������������������������
	if (!(m_iSide == 2))
	{
		// �W�����v������Ȃ��Ȃ痎��
		if (m_bJumpFlag) { m_vPos.y -= 15.0f; }
	}
	//����������������������������������������
	// ���f���S�̂̃W�����v
	//����������������������������������������
	WallJump();


	//����������������������������������������
	// ���ȏ�O�ɂ����Ȃ��悤�ɂ���
	//����������������������������������������
	if (m_vPos.x < -4900.0f) { m_vPos.x = -4900.0f; }
	else if (4900.0f < m_vPos.x) { m_vPos.x = 4900.0f; }
	if (m_vPos.z < -4900.0f) { m_vPos.z = -4900.0f; }
	else if (4900.0f < m_vPos.z) { m_vPos.z = 4900.0f; }


	//����������������������������������������
	// �̗͂� 0 �ɂȂ�����
	//����������������������������������������
	if (m_iLife <= 0) { SetSceneChengeFlag(true); }


	switch (CFade::GetScene())
	{
	//����������������������������������������
	// �o�g�� �V�[��
	//����������������������������������������
	case SCENE_BATTLE_GOLEM:
	case SCENE_BATTLE_SM:
		//����������������������������������������
		// ���f���S�̂̉�]
		//����������������������������������������
		// �G�̕���������
		if (CInput::GetKeyTrigger(VK_E) || CInput::GetJoyButton(0, JOYBUTTON_RB))
		{
			switch (CEnemyManger::GetEnemy())
			{
			case ENEMY_GOLEM:
				m_vAngle.y = atan2(m_vPos.x - m_pGolem->GetPos().x, m_vPos.z - m_pGolem->GetPos().z) * (180.0f / 3.14f);
				break;
			case ENEMY_SWORDMAN:
				m_vAngle.y = atan2(m_vPos.x - m_pSwordMan->GetPos().x, m_vPos.z - m_pSwordMan->GetPos().z) * (180.0f / 3.14f);
				break;
			default:
				break;
			}
		}

		// �R���g���[���[
		if (0 < CInput::GetJoyCount()) { m_vAngle.y += CInput::GetJoyRightStick(0).x * CInput::GetJoyRightSlope(0).x * 2.0f; }
		// �}�E�X
		else { m_vAngle.y += GetMouseMovement().x * MOUSE_SENSITIVITY; }

		if (m_vAngle.y <= -180.0f || m_vAngle.y > 180.0f) { m_vAngle.y *= -1.0f; }
		break;

	//����������������������������������������
	// ���ȊO�̃V�[��
	//����������������������������������������
	default:
		break;
	}

#pragma region �����蔻��
	GroundCollision();
#pragma endregion

	// �S�̂̃��[���h �}�g���b�N�X�X�V
	CGameObj::Update();

	// �e�p�[�c�̊p�x����}�g���b�N�X���쐬
	CalcMatrix();
	

#if 0
	CDebugProc::Print("*** ��ڲ԰ ***\n");
	CDebugProc::Print("[Life  : (%d)]\n", m_iLife);
	CDebugProc::Print("[pos   : (%f, %f, %f)]\n", m_vPos.x, m_vPos.y, m_vPos.z);
	CDebugProc::Print("[angle : (%f)]\n", m_vAngle.y);
	CDebugProc::Print("[Avoid : (%d)]\n", m_bAvoidFlag ? 1 : 0);
#endif
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CPlayer::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	CLight* pLight = CLight::Get();

	for (int i = 0; i < MAX_MC_PARTS; ++i)
	{
		CAssimpModel* pModel = CModel::GetAssimp((EModel)m_parts[i].model);
		pModel->Draw(pDC, m_parts[i].matrix, eOpacityOnly, 1);
	}

}
void CPlayer::DrawAlpha()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	CLight* pLight = CLight::Get();

	for (int i = 0; i < MAX_MC_PARTS; ++i)
	{
		CAssimpModel* pModel = CModel::GetAssimp((EModel)m_parts[i].model);
		pModel->Draw(pDC, m_parts[i].matrix, eTransparentOnly, 1);
	}

	CGameObj::DrawAlpha();

}


/*������������������������������������������������������������������������������

	�ړ�

	������ : ���[�J�����W��
	������ : ���� �u '+' or '-' �v
	��O���� : �X�s�[�h

������������������������������������������������������������������������������*/
void CPlayer::Move(XMFLOAT3 xyz, const char dir, float speed)
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

	�ǂɓ���������W�����v

������������������������������������������������������������������������������*/
void CPlayer::WallJump()
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
		m_vPos.y = VELOCITY0 * m_fJumpTime - (1.0f / 2.0f) * GRAVITY * pow(m_fJumpTime, 2) + m_fJumpStartPos.y;
		m_fJumpTime++;
		if (m_iSide == 2)
		{
			if (m_fJumpTime >= 5.0f) { m_bJumpFlag = true; }
		}
	}
}


/*������������������������������������������������������������������������������

	�ő�̗͂�Ԃ�

������������������������������������������������������������������������������*/
int CPlayer::GetMaxLife()
{
	return MAX_LIFE;
}


/*������������������������������������������������������������������������������

	�p�x����}�g���b�N�X���v�Z(�S�p�[�c��)

������������������������������������������������������������������������������*/
void CPlayer::CalcMatrix()
{
	for (int i = 0; i < MAX_MC_PARTS; ++i)
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
