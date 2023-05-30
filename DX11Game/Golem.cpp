//=============================================================================
//
// �S�[���� [Golem.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "Golem.h"
#include "BreakGround.h"
#include "Fade.h"
#include "Player.h"
#include "EnemyManger.h"
#include "HitStop.h"

//����������������������������������������
// �萔
//����������������������������������������
#define SPEED				(10)
#define MAX_LIFE			(25000)
#define SEARCH_RANGE		(4000.0f)	// ���G�͈�
#define ATTACK_RANGE		(350.0f)	// �U���͈�


//����������������������������������������
// �p�[�c�����f�[�^
//����������������������������������������
static TPartsData Golem_Data[MAX_GOLEM_PARTS] =
{ // �e�p�[�cNo.				���f���ԍ�				�I�t�Z�b�g�l						�_���[�W�{��
	{-1,					MODEL_LOOT,				{ 0.0f,		0.0f,		0.0f},	0.0f},
	{PARTS_GOLEM_LOOT,		MODEL_GOLEM_HIP,		{ 0.0f,		200.5f,		0.0f},	0.6f},
	{PARTS_GOLEM_HIP,		MODEL_GOLEM_BODY,		{ 0.0f,		23.5f,		0.0f},	1.3f},
	{PARTS_GOLEM_BODY,		MODEL_GOLEM_HEAD,		{ 0.0f,		121.6f,		0.0f},	1.0f},
	{PARTS_GOLEM_BODY,		MODEL_GOLEM_ARM_UP,		{ -106.59f,	79.343f,	0.0f},	0.4f},
	{PARTS_GOLEM_ARM_UP_R,	MODEL_GOLEM_ARM_DOWN,	{ 0.0f,		-123.589f,	0.0f},	0.2f},
	{PARTS_GOLEM_BODY,		MODEL_GOLEM_ARM_UP,		{ 106.59f,	79.343f,	0.0f},	0.4f},
	{PARTS_GOLEM_ARM_UP_L,	MODEL_GOLEM_ARM_DOWN,	{ 0.0f,		-123.589f,	0.0f},	0.2f},
	{PARTS_GOLEM_HIP,		MODEL_GOLEM_LEG_UP,		{ -33.5f,	16.8f,		0.0f},	0.4f},
	{PARTS_GOLEM_LEG_UP_R,	MODEL_GOLEM_LEG_DOWN,	{ 0.0f,		-91.1f,		0.0f},	0.2f},
	{PARTS_GOLEM_HIP,		MODEL_GOLEM_LEG_UP,		{ 33.5f,	-16.8f,		0.0f},	0.4f},
	{PARTS_GOLEM_LEG_UP_L,	MODEL_GOLEM_LEG_DOWN,	{ 0.0f,		-91.1f,		0.0f},	0.2f},
};


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CGolem::CGolem(CScene* pScene) : CEnemy(pScene)
{
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CGolem::Init()
{
	HRESULT hr = CEnemy::Init();
	if (FAILED(hr)) { return hr; }

	//����������������������������������������
	// �p�[�c�֘A
	//����������������������������������������
	m_parts.clear();
	m_pMaxParts = MAX_GOLEM_PARTS;
	TParts parts[MAX_GOLEM_PARTS];
	for (int i = 0; i < m_pMaxParts; ++i)
	{
		if (i == 0) { parts[i].use = false; }
		else { parts[i].use = true; }
		parts[i].parent = Golem_Data[i].parent;
		parts[i].model = Golem_Data[i].model;
		parts[i].off = Golem_Data[i].off;
		parts[i].angle = XMFLOAT3(0.0f, 0.0f, 0.0f);
		parts[i].DmgRatio = Golem_Data[i].DmgRatio;
		parts[i].hitDefence = false;
		parts[i].hitAttack = false;
		parts[i].num = i;
		CAssimpModel* pModel = CModel::GetAssimp((EModel)parts[i].model);
		parts[i].center = pModel->GetCenter();
		parts[i].bbox = pModel->GetBBox();

		m_parts.push_back(parts[i]);
	}
	CalcMatrix();

	SetCenter(XMFLOAT3(0.0f, 240.0f, -20.0f));
	SetBBox(XMFLOAT3(95.0f, 206.0f, 95.0f));

	BaseState = STATE_ENEMY_IDLE;

	//����������������������������������������
	// �̗�
	//����������������������������������������
	m_iMaxLife = MAX_LIFE;
	m_iLife = m_iMaxLife;

	//����������������������������������������
	// �A�j���[�V����
	//����������������������������������������
	m_AnimSet.Init();

	return hr;
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CGolem::Update()
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
	// �A�j���[�V���������邽�߂�
	//����������������������������������������
	// ���Ԃ���p�x����`��Ԃŋ��߂�
	for (int i = 0; i < m_pMaxParts; ++i) { m_parts[i].angle = m_AnimSet.GetAngle(i); }
	// ���Ԃƃt���[����i�߂�
	m_iAnimTime = m_AnimSet.AddTimer();


	// �p�x����Βl"360"�܂ł�������l��"0"�ɖ߂�
	if (m_vAngle.y <= -360.0f || m_vAngle.y >= 360.0f) { m_vAngle.y = 0.0f; }

	//����������������������������������������
	// �V�[�����Ƃ̏���
	//����������������������������������������
	switch (CFade::GetScene())
	{
#pragma region �z�[�����
	case SCENE_HOME:
		// �ҋ@�A�j���[�V�����Đ�
		m_AnimSet.Play(ANIM_GOLEM_IDLE);
		m_iAnimNum = ANIM_GOLEM_IDLE;
		break;
#pragma endregion
#pragma region �G�I�����
	case SCENE_ENEMY_SELECT:
		// �ҋ@�A�j���[�V�����Đ�
		m_AnimSet.Play(ANIM_GOLEM_IDLE);
		m_iAnimNum = ANIM_GOLEM_IDLE;

		// ���S�̃A�C�R���������Ȃ�`��
		if (CEnemyManger::GetCenterIcon() == ENEMY_GOLEM) { m_bVisible = true; }
		else { m_bVisible = false; }

		break;
#pragma endregion
#pragma region �o�g�����
	case SCENE_BATTLE_GOLEM:
		//����������������������������������������
		// �n�ʂɑ������Ă��Ȃ�������d�͂�^����
		//����������������������������������������
		if (!(m_iSide == 2))
		{
			m_AnimSet.Play(ANIM_GOLEM_JUMP);
			m_iAnimNum = ANIM_GOLEM_JUMP;

			//�W�����v������Ȃ��Ȃ痎��
			if (m_bJumpFlag) { m_vPos.y -= 15.0f; }
		}

		//����������������������������������������
		// ��Ԃ��Ƃ̏���
		//����������������������������������������
		switch (BaseState)
		{
#pragma region *-*-*- �ҋ@ -*-*-*
		case STATE_ENEMY_IDLE:
			m_AnimSet.Play(ANIM_GOLEM_IDLE);
			m_iAnimNum = ANIM_GOLEM_IDLE;
			switch (m_iStatus)
			{
			case 0:
				// �ҋ@���Ԃ����߂�
				m_iDoTime = rand() % 300;
				m_iStatus = 1;
			case 1:
				// ���Ԃ����炷
				m_iDoTime--;
				// ���Ԃ������Ȃ������]��Ԃɂ���
				if (m_iDoTime <= 0)
				{
					m_iStatus = 0;
					BaseState = STATE_ENEMY_ROTATION;
				}
				break;
			default:
				break;
			}
			break;
#pragma endregion
#pragma region *-*-*- �ړ� -*-*-*
		case STATE_ENEMY_MOVE:
			m_AnimSet.Play(ANIM_GOLEM_WALK);
			m_iAnimNum = ANIM_GOLEM_WALK;
			switch (m_iStatus)
			{
			case 0:
				// �ړ����Ԃ����߂�
				m_iDoTime = rand() % 300;
				m_iStatus = 1;
			case 1:
				// ���Ԃ����炷
				m_iDoTime--;
				// ���Ԃ�0��菬�����Ȃ�܂ňړ�����
				if (m_iDoTime > 0)
				{	// �O�i
					Move(vZ, '-', SPEED);
				}
				// ���Ԃ������Ȃ�����ҋ@��Ԃɂ���
				else
				{
					m_iStatus = 0;
					BaseState = STATE_ENEMY_IDLE;
				}
				// �����ߕt������U���I�ɂȂ�
				if (m_fDist <= SEARCH_RANGE)
				{
					m_iStatus = 0;
					BaseState = STATE_ENEMY_ATTACK;
				}
				break;
			default:
				break;
			}
			break;
#pragma endregion
#pragma region *-*-*- ��] -*-*-*
		case STATE_ENEMY_ROTATION:
			m_AnimSet.Play(ANIM_GOLEM_WALK);
			m_iAnimNum = ANIM_GOLEM_WALK;
			switch (m_iStatus)
			{
			case 0:
				// ��]���Ԃ����߂�
				m_iDoTime = rand() % 60;
				// ��]���������߂�
				m_iDirections = rand() % 2;
				m_iStatus = 1;
			case 1:
				// ���Ԃ����炷
				m_iDoTime--;
				// ���Ԃ�0��菬�����Ȃ�܂ŉ�]����
				if (m_iDoTime > 0)
				{
					if (m_iDirections == 0) { m_vAngle.y += 3; }
					else { m_vAngle.y -= 3; }
				}
				// ���Ԃ������Ȃ�����ړ���Ԃɂ���
				else
				{
					m_iStatus = 0;
					BaseState = STATE_ENEMY_MOVE;
				}
				break;
			default:
				break;
			}
			break;
#pragma endregion
#pragma region *-*-*- �U���I -*-*-*
		case STATE_ENEMY_ATTACK:
			m_AnimSet.Play(ANIM_GOLEM_WALK);
			m_iAnimNum = ANIM_GOLEM_WALK;
			// �v���C���[�̕���������
			m_vAngle.y = atan2(m_vPos.x - m_pPlayer->GetPos().x, m_vPos.z - m_pPlayer->GetPos().z) * (180.0f / 3.14f);
			if (m_vAngle.y <= -360.0f || m_vAngle.y >= 360.0f) { m_vAngle.y = 0.0f; }
			// ����藣��Ă�����ǔ��ړ�
			if (m_fDist > ATTACK_RANGE && !m_bNowAttack)
			{	// �O�i
				Move(vZ, '-', SPEED * 1.5f);
			}
			// ��苗���܂ŋߕt������U��
			else
			{
				switch (m_iStatus)
				{
				case 0:
					// �ҋ@���Ԃ����߂�
					m_iDoTime = rand() % 90 + 30;
					m_iStatus = 1;
				case 1:
					// ���Ԃ����炷
					m_iDoTime--;
					// ���Ԃ������Ȃ�����U������
					if (m_iDoTime <= 0)
					{
						m_fRimColor = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
						m_AnimSet.Play(ANIM_GOLEM_ATTACK);
						m_iAnimNum = ANIM_GOLEM_ATTACK;
						m_bNowAttack = true;
						if (m_iAnimTime.y == GOLEM_ATTACK)
						{
							CBreakGround::Creat(m_pScene, m_mWorld);
						}
						// �U���A�j���[�V�������I�������ҋ@���ɖ߂�
						if (m_iAnimTime.x)
						{
							m_fRimColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
							m_bNowAttack = false;
							m_iStatus = 0;
						}
					}
					// �ҋ@���Ԓ��̃A�j���[�V����
					else
					{
						m_AnimSet.Play(ANIM_GOLEM_IDLE);
						m_iAnimNum = ANIM_GOLEM_IDLE;
					}
					break;
				default:
					break;
				}
			}
			// ����藣�ꂽ��U���I������
			if (m_fDist > SEARCH_RANGE)
			{
				m_iStatus = 0;
				BaseState = STATE_ENEMY_ROTATION;
			}
			break;
#pragma endregion
#pragma region *-*-*- ���S - *-*-*
		case STATE_ENEMY_DEAD:
			m_AnimSet.Play(ANIM_GOLEM_DEATH, false);
			m_iAnimNum = ANIM_GOLEM_DEATH;
			// �V�[���`�F���W
			if (m_iAnimTime.x) { SetSceneChengeFlag(true); }
			break;
#pragma endregion
		default:
			break;
		}
#pragma endregion
	default:
		break;
	}

	//����������������������������������������
	// �G�S��̋��ʏ���
	//����������������������������������������
	CEnemy::Update();
}