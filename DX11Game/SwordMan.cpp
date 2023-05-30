//=============================================================================
//
// �\�[�_�\ [SwordMan.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "SwordMan.h"
#include "SwordRain.h"
#include "Particle.h"
#include "HPGaugePlayer.h"
#include "Fade.h"
#include "Player.h"
#include "EnemyManger.h"
#include "Sound.h"
#include "Random.h"


//����������������������������������������
// �萔
//����������������������������������������
#define SPEED				(10)		// �ړ��X�s�[�h
#define DOWN_SPEED			(0.6f)		// �����{�� (���G�͈͓��ɂ���Ƃ�)
#define MAX_LIFE			(25000)		// �̗�
#define SEARCH_RANGE		(1000.0f)	// ���G�͈�
#define ATTACK_RANGE		(350.0f)	// �U���͈�
#define GRAVITY				(0.98f)		// �d��
#define VELOCITY			(25.0f)		// �����x


//����������������������������������������
// �p�[�c�����f�[�^
//����������������������������������������
static TPartsData SwordMan_Data[MAX_SM_PARTS] =
{ // �e�p�[�cNo.				���f���ԍ�			�I�t�Z�b�g�l						�_���[�W�{��
	{-1,					MODEL_LOOT,			{ 0.0f,		0.0f,		0.0f},	0.0f},
	{PARTS_SM_LOOT,			MODEL_SM_HIP,		{ 0.0f,		156.6f,		0.0f},	0.8f},
	{PARTS_SM_HIP,			MODEL_SM_BODY,		{ 0.0f,		17.3f,		0.0f},	1.0f},
	{PARTS_SM_BODY,			MODEL_SM_HEAD,		{ 0.0f,		123.3f,		0.0f},	1.5f},
	{PARTS_SM_BODY,			MODEL_SM_ARM,		{ -51.0f,	122.1f,		0.0f},	0.6f},
	{PARTS_SM_ARM_UP_R,		MODEL_SM_ARM,		{ 0.0f,		-101.0f,	0.0f},	0.4f},
	{PARTS_SM_ARM_DOWN_R,	MODEL_SM_HAND,		{ 0.0f,		-102.8f,	0.0f},	0.2f},
	{PARTS_SM_BODY,			MODEL_SM_ARM,		{ 51.0f,	122.1f,		0.0f},	0.6f},
	{PARTS_SM_ARM_UP_L,		MODEL_SM_ARM,		{ 0.0f,		-101.0f,	0.0f},	0.4f},
	{PARTS_SM_ARM_DOWN_L,	MODEL_SM_HAND,		{ 0.0f,		-102.8f,	0.0f},	0.2f},
	{PARTS_SM_HIP,			MODEL_SM_LEG,		{ -25.8f,	-10.2f,		0.0f},	0.6f},
	{PARTS_SM_LEG_UP_R,		MODEL_SM_LEG,		{ 0.0f,		-74.8f,		0.0f},	0.4f},
	{PARTS_SM_HIP,			MODEL_SM_LEG,		{ 25.8f,	-10.2f,		0.0f},	0.6f},
	{PARTS_SM_LEG_UP_L,		MODEL_SM_LEG,		{ 0.0f,		-74.8f,		0.0f},	0.4f},
	{PARTS_SM_HAND_R,		MODEL_BLACK_SWORD,	{ 0.0f,		-7.5f,		0.0f},	0.0f},
};

/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CSwordMan::CSwordMan(CScene* pScene) : CEnemy(pScene)
{
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CSwordMan::Init()
{
	HRESULT hr = CEnemy::Init();
	if (FAILED(hr)) { return hr; }

	//����������������������������������������
	// �p�[�c�֘A
	//����������������������������������������
	m_parts.clear();
	m_pMaxParts = MAX_SM_PARTS;
	TParts parts[MAX_SM_PARTS];
	for (int i = 0; i < m_pMaxParts; ++i)
	{
		if ((i == 0) || (i == PARTS_BLACK_SWORD)) { parts[i].use = false; }
		else { parts[i].use = true; }
		parts[i].parent = SwordMan_Data[i].parent;
		parts[i].model = SwordMan_Data[i].model;
		parts[i].off = SwordMan_Data[i].off;
		parts[i].angle = XMFLOAT3(0.0f, 0.0f, 0.0f);
		parts[i].DmgRatio = SwordMan_Data[i].DmgRatio;
		parts[i].hitDefence = false;
		parts[i].hitAttack = false;
		parts[i].num = i;
		CAssimpModel* pModel = CModel::GetAssimp((EModel)parts[i].model);
		parts[i].center = pModel->GetCenter();
		if (i == PARTS_BLACK_SWORD)
		{
			parts[i].bbox = XMFLOAT3(pModel->GetBBox().x * 1.5f, pModel->GetBBox().y * 1.5f, pModel->GetBBox().z * 1.5f);
		}
		else
		{
			parts[i].bbox = pModel->GetBBox();
		}
		m_parts.push_back(parts[i]);
	}
	CalcMatrix();

	SetCenter(XMFLOAT3(0.0f, 178.0f, 0.0f));
	SetBBox(XMFLOAT3(134.5f / 2.0f, 357.2f / 2.0f, 69.6f / 2.0f));

	BaseState = STATE_ENEMY_IDLE;
	SM_MoveState = SM_BIG_MOVE_BACK;
	SM_AttackState = SM_ATTACK_NONE;

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
void CSwordMan::Update()
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

	//����������������������������������������
	// �p�[�e�B�N�����o���ʒu�̒���
	//����������������������������������������
	XMFLOAT4X4 fW;
	fW = m_parts[PARTS_BLACK_SWORD].matrix;
	fW._41 -= fW._21 * m_parts[PARTS_BLACK_SWORD].bbox.y;
	fW._42 = m_vPos.y;
	fW._43 -= fW._23 * m_parts[PARTS_BLACK_SWORD].bbox.y;


	// �p�x����Βl"360"�܂ł�������l��"0"�ɖ߂�
	if (m_vAngle.y <= -360.0f || m_vAngle.y >= 360.0f) { m_vAngle.y = 0.0f; }

	//����������������������������������������
	// �V�[�����Ƃ̏���
	//����������������������������������������
	switch (CFade::GetScene())
	{
#pragma region �^�C�g�����
	case SCENE_TITLE:
		GroundCollision();
		//����������������������������������������
		// �n�ʂɑ������Ă��Ȃ�������d�͂�^����
		//����������������������������������������
		if (!(m_iSide == 2))
		{	//�W�����v������Ȃ��Ȃ痎��
			if (m_bJumpFlag) { m_vPos.y -= 15.0f; }
		}

		//����������������������������������������
		// ����
		//����������������������������������������
		switch (BaseState)
		{
		case STATE_ENEMY_IDLE:
			// �ҋ@�A�j���[�V�����Đ�
			m_AnimSet.Play(ANIM_SM_IDLE);
			m_iAnimNum = ANIM_SM_IDLE;
			// �ʒu�A�����ݒ�
			SetPos(XMFLOAT3(0.0f, 600.0f, 0.0f));
			SetAngle(XMFLOAT3(0.0f, 220.0f, 0.0f));
			BaseState = STATE_ENEMY_ATTACK;
			m_iStatus = 0;
		case STATE_ENEMY_ATTACK:
			m_iTime++;
			if (180 < m_iTime)
			{
				switch (m_iStatus)
				{
				case 0:
					// �U���P�A�j���[�V�����Đ�
					m_AnimSet.Play(ANIM_SM_ATTACK_00_01);
					m_iAnimNum = ANIM_SM_ATTACK_00_01;
					m_iStatus = 1;
					break;
				case 1:
					// case 0: �ōĐ������A�j���[�V�������I�������
					if (m_iAnimTime.x)
					{
						// �p�[�e�B�N������
						for (int j = 0; j < MAX_PARTICLE; j++)
						{
							CParticle::Creat(m_pScene, fW, 90, XMINT3(10, 30, 10), XMFLOAT3(0.0f, -1.0f, 0.0f));
						}
						// �U���Q�A�j���[�V�����Đ�
						m_AnimSet.Play(ANIM_SM_ATTACK_00_02);
						m_iAnimNum = ANIM_SM_ATTACK_00_02;
						m_iStatus = 2;
					}
					break;
				case 2:
					// case 1: �ōĐ������A�j���[�V�������I�������
					if (m_iAnimTime.x)
					{
						// �ҋ@�A�j���[�V�����Đ�
						m_AnimSet.Play(ANIM_SM_IDLE);
						m_iAnimNum = ANIM_SM_IDLE;
						m_iTime = 0;
						m_iStatus = 0;
					}
					break;
				}
			}
			break;
		}
		break;
#pragma endregion
#pragma region �z�[�����
	case SCENE_HOME:
		// �ҋ@�A�j���[�V�����Đ�
		m_AnimSet.Play(ANIM_SM_IDLE);
		m_iAnimNum = ANIM_SM_IDLE;
		break;
#pragma endregion
#pragma region �G�I�����
	case SCENE_ENEMY_SELECT:
		// �ҋ@�A�j���[�V�����Đ�
		m_AnimSet.Play(ANIM_SM_IDLE);
		m_iAnimNum = ANIM_SM_IDLE;

		// ���S�̃A�C�R���������Ȃ�`��
		if (CEnemyManger::GetCenterIcon() == ENEMY_SWORDMAN) { m_bVisible = true; }
		else { m_bVisible = false; }
		break;
#pragma endregion
#pragma region �Q�[�����
	case SCENE_BATTLE_SM:
		//����������������������������������������
		// �n�ʂɑ������Ă��Ȃ�������d�͂�^����
		//����������������������������������������
		if (!(m_iSide == 2))
		{	//�W�����v������Ȃ��Ȃ痎��
			if (m_bJumpFlag) { m_vPos.y -= 15.0f; }
		}

		//����������������������������������������
		// �U���̏�Ԃɂ���ĐF��ς���
		//����������������������������������������
		switch (SM_AttackState)
		{
		case SM_ATTACK_NONE:	// ���F
			m_fRimColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		case SM_ATTACK_01:		// �ԐF
			m_fRimColor = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
			break;
		case SM_ATTACK_02:		// ���F
			m_fRimColor = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);
			break;
		case SM_ATTACK_03:		// �F
			m_fRimColor = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
			break;
		}

		//����������������������������������������
		// ��Ԃ��Ƃ̏���
		//����������������������������������������
		switch (BaseState)
		{
#pragma region *-*-*- �ҋ@ -*-*-*
		case STATE_ENEMY_IDLE:
			StateIdle();
			break;
#pragma endregion
#pragma region *-*-*- �ړ� -*-*-*
		case STATE_ENEMY_MOVE:
			StateMove(vX, vZ);
			break;
#pragma endregion
#pragma region *-*-*- �U���I -*-*-*
		case STATE_ENEMY_ATTACK:
			StateAttack01();
			StateAttack02(vZ);
			StateAttack03();
			break;
#pragma endregion
#pragma region *-*-*- ���S -*-*-*
		case STATE_ENEMY_DEAD:
			StateDead();
			break;
#pragma endregion
		default:
			break;
		}

		//����������������������������������������
		// �U�����̓����蔻��
		//����������������������������������������
		if (m_pPlayer && !m_pPlayer->GetAvoidFlag())
		{
			CGameObj* pNext;
			for (CGameObj* pObj = m_pScene->GetObj(); pObj; pObj = pNext)
			{
				pNext = pObj->GetNext();
				if (pObj->GetID() != GOT_PLAYER) { continue; }

				if (CollisionOBB(pObj, GetParts(PARTS_BLACK_SWORD).matrix, GetParts(PARTS_BLACK_SWORD).center, GetParts(PARTS_BLACK_SWORD).bbox))
				{
					if ((m_iAnimNum == ANIM_SM_ATTACK_01_03) || (m_iAnimNum == ANIM_SM_ATTACK_01_04) ||
						(m_iAnimNum == ANIM_SM_ATTACK_02_02) || (m_iAnimNum == ANIM_SM_ATTACK_02_03))
					{
						// ���̃A�j���[�V�����ň�񂵂�������Ƃ�Ȃ�
						if (!GetParts(PARTS_BLACK_SWORD).hitAttack)
						{
							m_pPlayer->LifeDmg(200);
							m_pHPGaugePlayer->SetDamage(200);
							SetPartsHitAttack(PARTS_BLACK_SWORD, true);
						}
					}
				}
			}
		}

		break;
#pragma endregion
	default:
		break;
	}

	//����������������������������������������
	// �G�S��̋��ʏ���
	//����������������������������������������
	CEnemy::Update();

#if 0
	CDebugProc::Print("*** ������ ***\n");
	CDebugProc::Print("[m_vPos   : %f, %f, %f]\n", m_vPos.x, m_vPos.y, m_vPos.z);
	//	CDebugProc::Print("[AttackTime      : %d - %d]\n", 
	//		(m_iAnimNum == ANIM_SM_ATTACK_1) ? SM_ATTACK1_S : (m_iAnimNum == ANIM_SM_ATTACK_2) ? SM_ATTACK2_S : 0 ,
	//		(m_iAnimNum == ANIM_SM_ATTACK_1) ? SM_ATTACK1_E : (m_iAnimNum == ANIM_SM_ATTACK_2) ? SM_ATTACK2_E : 0);
#endif
}



/*������������������������������������������������������������������������������

	�ҋ@ ���

������������������������������������������������������������������������������*/
#pragma region �ҋ@
void CSwordMan::StateIdle()
{
	CRandom random;
	std::vector<ActionWeight> actionWeights{
		{0, 0.6f},		// �����ċߕt��
		{1, 0.4f},		// ��ړ�(���E)
	};

	switch (m_iStatus)
	{
	case 0:
		// �A�j���[�V�����Đ�
		m_AnimSet.Play(ANIM_SM_IDLE);
		m_iAnimNum = ANIM_SM_IDLE;
		// �ҋ@���Ԃ����߂�
		m_iDoTime = rand() % 20 + 20; // 20 ~ 39
		m_iStatus = 1;
		break;
	case 1:
		m_iDoTime--;
		// �ҋ@���Ԃ������Ȃ�����
		if (m_iDoTime < 0)
		{
			// �U���R����낤�Ƃ��Ă�����
			if (SM_AttackState == SM_ATTACK_03)
			{
				BaseState = STATE_ENEMY_ATTACK;
				m_iStatus = 0;
			}
			// ��������Ȃ��Ȃ烉���_���J��
			else
			{
				switch (random.WeightRandom(actionWeights))
				{
				case 0:
					// ����������Ă�����
					if (SEARCH_RANGE < m_fDist)
					{
						// �U���Q�̏�Ԃɐݒ�
						SM_AttackState = SM_ATTACK_02;
						// �����ċߕt��
						SM_MoveState = SM_RUN_MOVE;
						BaseState = STATE_ENEMY_MOVE;
						m_iStatus = 0;
					}
				case 1:
					// �ړ��̏�Ԃ��ړ�(���E)�ɕς���
					SM_MoveState = SM_BIG_MOVE_SIDE;
					BaseState = STATE_ENEMY_MOVE;
					m_iStatus = 0;
					break;
				}
			}
		}
		break;
	}
}
#pragma endregion


/*������������������������������������������������������������������������������

	�ړ� ���

������������������������������������������������������������������������������*/
#pragma region �ړ�
void CSwordMan::StateMove(XMFLOAT3 vX, XMFLOAT3 vZ)
{
	CRandom random;
	std::vector<ActionWeight> actionWeights;

	switch (SM_MoveState)
	{
#pragma region ��ړ�(���)
	case SM_BIG_MOVE_BACK:
		switch (m_iStatus)
		{
		case 0:
			// �A�j���[�V�����Đ�
			m_AnimSet.Play(ANIM_SM_JUMP);
			m_iAnimNum = ANIM_SM_JUMP;
			// �ړ����Ԃ����߂�
			m_iDoTime = rand() % 40 + 20; // 20 ~ 40
			// �X�s�[�h�{���ݒ�
			m_fSpeedScale = (float)(rand() % 20 + 30) / 10.0f;	// 3.0f ~ 5.0f
			// �������U�������߂�
			if (SM_AttackState == SM_ATTACK_NONE)
			{
				actionWeights = {
					{0, 0.3f},
					{1, 0.1f}
				};
				switch (random.WeightRandom(actionWeights))
				{
				case 0:
					SM_AttackState = SM_ATTACK_01;
					break;
				default:
					break;
				}
			}
			m_iStatus = 1;
			break;
		case 1:
			m_iDoTime--;
			// ���
			Move(vZ, '+', SPEED * m_fSpeedScale);
			// �ړ����Ԃ������Ȃ�����
			if (m_iDoTime < 0)
			{
				// �U���Q����낤�Ƃ��Ă�����
				if (SM_AttackState == SM_ATTACK_01)
				{
					// �v���C���[�Ƌ߂�������"���ɔ��"
					if (m_fDist < ATTACK_RANGE * 2)
					{
						SM_MoveState = SM_BIG_MOVE_SIDE;
						m_iStatus = 0;
					}
					// ����������Ă�����
					else
					{
						BaseState = STATE_ENEMY_ATTACK;
						m_iStatus = 0;
					}
				}
				// ��������Ȃ��Ȃ烉���_���J��
				else
				{
					actionWeights = {
						{0, 0.3f},
						{1, 0.1f}
					};
					switch (random.WeightRandom(actionWeights))
					{
					case 0:
						// ����������Ă�����
						if (SEARCH_RANGE < m_fDist)
						{
							// �U���Q�̏�Ԃɐݒ�
							SM_AttackState = SM_ATTACK_02;
							// �����ċߕt��
							SM_MoveState = SM_RUN_MOVE;
							m_iStatus = 0;
						}
						else
						{
							// �ړ��̏�Ԃ��ړ�(���E)�ɕς���
							SM_MoveState = SM_BIG_MOVE_SIDE;
							m_iStatus = 0;
						}
						break;
					case 1:
						// �ړ��̏�Ԃ��ړ�(���E)�ɕς���
						SM_MoveState = SM_BIG_MOVE_SIDE;
						m_iStatus = 0;
						break;
					}
				}
			}
			break;
		}
		break;
#pragma endregion
#pragma region ��ړ�(���E)
	case SM_BIG_MOVE_SIDE:
		switch (m_iStatus)
		{
		case 0:
			// �A�j���[�V�����Đ�
			m_AnimSet.Play(ANIM_SM_JUMP);
			m_iAnimNum = ANIM_SM_JUMP;
			// �ړ����Ԃ����߂�
			m_iDoTime = rand() % 40 + 20; // 20 ~ 40
			// �ړ����������߂�(2����)
			m_iDirections = rand() % 2;
			// �X�s�[�h�{���ݒ�
			m_fSpeedScale = (float)(rand() % 20 + 30) / 10.0f;	// 3.0f ~ 5.0f
			m_iStatus = 1;
			break;
		case 1:
			m_iDoTime--;
			if (m_pPlayer)
			{
				// �v���C���[�̕���������
				m_vAngle.y = atan2(m_vPos.x - m_pPlayer->GetPos().x, m_vPos.z - m_pPlayer->GetPos().z) * (180.0f / 3.14f);
			}
			// �ړ�����
			switch (m_iDirections)
			{
			case 0:	// �E
				Move(vX, '-', SPEED * m_fSpeedScale);
				break;
			case 1:	// ��
				Move(vX, '+', SPEED * m_fSpeedScale);
				break;
			}
			// �ړ����Ԃ������Ȃ�����
			if (m_iDoTime < 0)
			{
				// �U���P����낤�Ƃ��Ă�����"���ɔ��"
				if (SM_AttackState == SM_ATTACK_01)
				{
					SM_MoveState = SM_BIG_MOVE_BACK;
					m_iStatus = 0;
				}
				// ��������Ȃ��Ȃ烉���_���J��
				else
				{
					actionWeights = {
						{0, 0.3f},	// ��������ő����ċߕt������ړ�(���)
						{1, 0.2f},	// ��ړ�(���)
						{2, 0.1f}	// ��ړ�(���E)
					};
					switch (random.WeightRandom(actionWeights))
					{
					case 0:
						// ����������Ă�����
						if (SEARCH_RANGE < m_fDist)
						{
							// �U���Q�̏�Ԃɐݒ�
							SM_AttackState = SM_ATTACK_02;
							// �����ċߕt��
							SM_MoveState = SM_RUN_MOVE;
							m_iStatus = 0;
						}
						else
						{
							SM_MoveState = SM_BIG_MOVE_BACK;
							m_iStatus = 0;
						}
						break;
					case 1:
						SM_MoveState = SM_BIG_MOVE_BACK;
						m_iStatus = 0;
						break;
					case 2:
						m_iStatus = 0;
						break;
					}
				}
			}
		}
		break;
#pragma endregion
#pragma region �����ċߕt��
	case SM_RUN_MOVE:
		switch (m_iStatus)
		{
		case 0:
			// �A�j���[�V�����Đ�
			m_AnimSet.Play(ANIM_SM_RUN);
			m_iAnimNum = ANIM_SM_RUN;
			// �X�s�[�h�{���ݒ�
			m_fSpeedScale = 4.0f;
			m_iStatus = 1;
			break;
		case 1:
			// �v���C���[�̕���������
			m_vAngle.y = atan2(m_vPos.x - m_pPlayer->GetPos().x, m_vPos.z - m_pPlayer->GetPos().z) * (180.0f / 3.14f);
			// �O�i
			Move(vZ, '-', SPEED * m_fSpeedScale);
			// �ߕt������U��
			if (m_fDist < SEARCH_RANGE)
			{
				BaseState = STATE_ENEMY_ATTACK;
				m_iStatus = 0;
			}
			break;
		}
		break;
#pragma endregion
	}
}
#pragma endregion


/*������������������������������������������������������������������������������

	�U���P ���
	*** ��������}�ڋ߂���2�A�� ***

������������������������������������������������������������������������������*/
#pragma region �U���P
void CSwordMan::StateAttack01()
{
	if (SM_AttackState != SM_ATTACK_01) { return; }
	switch (m_iStatus)
	{
	case 0:
		// �A�j���[�V�����Đ�
		m_AnimSet.Play(ANIM_SM_ATTACK_01_01);
		m_iAnimNum = ANIM_SM_ATTACK_01_01;
		// ���̍��W��ۑ�
		m_fPrevPos = m_vPos;
		m_fPrevPlayerPos = m_pPlayer->GetPos();
		// �X�s�[�h�{���ݒ�
		m_fSpeedScale = 6.0f;
		// �v���C���[�̕���������
		m_vAngle.y = atan2(m_vPos.x - m_pPlayer->GetPos().x, m_vPos.z - m_pPlayer->GetPos().z) * (180.0f / 3.14f);
		m_iStatus = 1;
		break;
	case 1:
		// ���O�ɍĐ������A�j���[�V�������I�������
		if (m_iAnimTime.x)
		{
			// �A�j���[�V�����Đ�
			m_AnimSet.Play(ANIM_SM_ATTACK_01_02);
			m_iAnimNum = ANIM_SM_ATTACK_01_02;
			m_iStatus = 2;
		}
		break;
	case 2:
		// �ڕW�n�_�܂ňړ�
		lblPosXZ(XMFLOAT2(m_fPrevPos.x, m_fPrevPos.z), XMFLOAT2(m_fPrevPlayerPos.x, m_fPrevPlayerPos.z), SPEED * m_fSpeedScale);
		// �����v�Z
		XMVECTOR vT = XMVectorSet(m_vPos.x - m_fPrevPlayerPos.x, 0.0f, m_vPos.z - m_fPrevPlayerPos.z, 0.0f);
		XMStoreFloat(&m_fPrevDist, XMVector3Length(vT));
		// �U���͈͂܂ŋ߂Â�����
		if (m_fPrevDist < ATTACK_RANGE) { m_iStatus = 3; }
		break;
	case 3:
		CSound::Play(SM_A0101);
		// �A�j���[�V�����Đ�
		m_AnimSet.Play(ANIM_SM_ATTACK_01_03);
		m_iAnimNum = ANIM_SM_ATTACK_01_03;
		m_iStatus = 4;
		break;
	case 4:
		// ���O�ɍĐ������A�j���[�V�������I�������
		if (m_iAnimTime.x)
		{
			// �����߂�
			SetPartsHitAttack(PARTS_BLACK_SWORD, false);
			// �A�j���[�V�����Đ�
			m_AnimSet.Play(ANIM_SM_ATTACK_01_04);
			m_iAnimNum = ANIM_SM_ATTACK_01_04;
			m_iStatus = 5;
		}
		break;
	case 5:
		// ���O�ɍĐ������A�j���[�V�������I�������
		if (m_iAnimTime.x)
		{
			// �����߂�
			SetPartsHitAttack(PARTS_BLACK_SWORD, false);
			// �A�j���[�V�����Đ�
			m_AnimSet.Play(ANIM_SM_ATTACK_01_05);
			m_iAnimNum = ANIM_SM_ATTACK_01_05;
			m_iStatus = 6;
		}
		break;
	case 6:
		// ���O�ɍĐ������A�j���[�V�������I�������
		if (m_iAnimTime.x)
		{
			// ��{�̏�Ԃ�ҋ@�ɕς���
			BaseState = STATE_ENEMY_IDLE;
			m_iStatus = 0;
			SM_AttackState = SM_ATTACK_NONE;
		}
		break;
	}
}
#pragma endregion


/*������������������������������������������������������������������������������

	�U���Q ���
	*** �����Ă�����x�ߕt���Ă���A�˂���Ԃŋ}�ڋ߂��ĉ񂵎a�� ***

������������������������������������������������������������������������������*/
#pragma region �U���Q
void CSwordMan::StateAttack02(XMFLOAT3 vZ)
{
	if (SM_AttackState != SM_ATTACK_02) { return; }

	CRandom random;
	std::vector<ActionWeight> actionWeights;

	switch (m_iStatus)
	{
	case 0:
		CSound::Play(SM_A0201);
		// �A�j���[�V�����Đ�
		m_AnimSet.Play(ANIM_SM_ATTACK_02_01);
		m_iAnimNum = ANIM_SM_ATTACK_02_01;
		// �X�s�[�h�{���ݒ�
		m_fSpeedScale = 6.0f;
		// �v���C���[�̕���������
		m_vAngle.y = atan2(m_vPos.x - m_pPlayer->GetPos().x, m_vPos.z - m_pPlayer->GetPos().z) * (180.0f / 3.14f);
		m_iStatus = 1;
		break;
	case 1:
		// ���O�ɍĐ������A�j���[�V�������I�������
		if (m_iAnimTime.x)
		{
			CSound::Play(SM_A0202);
			// �A�j���[�V�����Đ�
			m_AnimSet.Play(ANIM_SM_ATTACK_02_02);
			m_iAnimNum = ANIM_SM_ATTACK_02_02;
			m_iStatus = 2;
		}
		break;
	case 2:
		// �v���C���[�̕���������
		m_vAngle.y = atan2(m_vPos.x - m_pPlayer->GetPos().x, m_vPos.z - m_pPlayer->GetPos().z) * (180.0f / 3.14f);
		// �O�i
		Move(vZ, '-', SPEED * m_fSpeedScale);
		if (m_fDist < ATTACK_RANGE)
		{
			// �����߂�
			SetPartsHitAttack(PARTS_BLACK_SWORD, false);
			m_iStatus = 3;
		}
		break;
	case 3:
		CSound::Play(SM_A0203);
		// �A�j���[�V�����Đ�
		m_AnimSet.Play(ANIM_SM_ATTACK_02_03);
		m_iAnimNum = ANIM_SM_ATTACK_02_03;
		m_iStatus = 4;
		break;
	case 4:
		// ���O�ɍĐ������A�j���[�V�������I�������
		if (m_iAnimTime.x)
		{
			// �����߂�
			SetPartsHitAttack(PARTS_BLACK_SWORD, false);
			// �A�j���[�V�����Đ�
			m_AnimSet.Play(ANIM_SM_ATTACK_02_04);
			m_iAnimNum = ANIM_SM_ATTACK_02_04;
			m_iStatus = 5;
		}
		break;
	case 5:
		// ���O�ɍĐ������A�j���[�V�������I�������
		if (m_iAnimTime.x)
		{
			// ��{�̏�Ԃ�ҋ@�ɕς���
			BaseState = STATE_ENEMY_IDLE;
			m_iStatus = 0;
			SM_AttackState = SM_ATTACK_NONE;
			// ���������U�������߂�
			if (SM_AttackState == SM_ATTACK_NONE)
			{
				actionWeights = {
					{0, 0.2f},	// �U���R
					{1, 0.1f}	// ����ȊO
				};
				switch (random.WeightRandom(actionWeights))
				{
				case 0:
					SM_AttackState = SM_ATTACK_03;
					break;
				default:
					break;
				}
			}
		}
		break;
	}
}
#pragma endregion


/*������������������������������������������������������������������������������

	�U���R ���
	*** �n�ʂɌ����w���čL�͈͂ɍU�� ***

������������������������������������������������������������������������������*/
#pragma region �U���R
void CSwordMan::StateAttack03()
{
	if (SM_AttackState != SM_ATTACK_03) { return; }
	switch (m_iStatus)
	{
	case 0:
		CSound::Play(SM_A0301);
		// �A�j���[�V�����Đ�
		m_AnimSet.Play(ANIM_SM_ATTACK_03_01);
		m_iAnimNum = ANIM_SM_ATTACK_03_01;
		m_iStatus = 1;
		break;
	case 1:
		// ���O�ɍĐ������A�j���[�V�������I�������
		if (m_iAnimTime.x)
		{
			for (int i = 0; i < 30; i++) { CSwordRain::Creat(m_pScene, m_mWorld); }
			CSound::Play(SM_A0302);
			// �A�j���[�V�����Đ�
			m_AnimSet.Play(ANIM_SM_ATTACK_03_02);
			m_iAnimNum = ANIM_SM_ATTACK_03_02;
			m_iStatus = 2;
		}
		break;
	case 2:
		// ���O�ɍĐ������A�j���[�V�������I�������
		if (m_iAnimTime.x)
		{
			// ��{�̏�Ԃ�ҋ@�ɕς���
			BaseState = STATE_ENEMY_IDLE;
			m_iStatus = 0;
			SM_AttackState = SM_ATTACK_NONE;
		}
		break;
	}
}
#pragma endregion


/*������������������������������������������������������������������������������

	���S ���

������������������������������������������������������������������������������*/
#pragma region ���S
void CSwordMan::StateDead()
{
	// �V�[���`�F���W
	SetSceneChengeFlag(true);
}
#pragma endregion
