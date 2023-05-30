//=============================================================================
//
// �z�[����� [Home.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "Home.h"
#include "2Dobj.h"
#include "Sound.h"
#include "Input.h"
#include "Fade.h"
#include "Manager.h"
#include "EnemyManger.h"
#include "Golem.h"
#include "SwordMan.h"


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CHome::CHome() : CScene()
{
	m_id = SCENE_HOME;

	m_pWeapon = nullptr;

	m_pMouseCursor = nullptr;
	m_pBG_Frame = nullptr;
	m_pReturnButton = nullptr;
	m_pWeaponButton = nullptr;
	m_pMonsterButton = nullptr;
	m_pDuelStartButton = nullptr;
}

/*������������������������������������������������������������������������������

	�f�X�g���N�^

������������������������������������������������������������������������������*/
CHome::~CHome()
{
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
bool CHome::Init()
{
	m_camera.Init();
	CCamera::Set(&m_camera);

	// ����
	m_pWeapon = new CWeapon(this);
	switch (CEnemyManger::GetEnemy())
	{
	case ENEMY_GOLEM:
		new CGolem(this);
		break;
	case ENEMY_SWORDMAN:
		new CSwordMan(this);
		break;
	default:
		break;
	}

	m_pMouseCursor = new CMouseCursor(this);
	m_pReturnButton = new CReturnButton(this);
	m_pWeaponButton = new CWeaponButton(this);
	m_pMonsterButton = new CMonsterButton(this);
	m_pDuelStartButton = new CDuelStartButton(this);
	m_pBG_Frame = new CBG_Frame(this);

	// �S�I�u�W�F�N�g������
	if (FAILED(CGameObj::InitAll(m_pObj))) { return false; }
	if (FAILED(C2DObj::InitAll(m_p2DObj))) { return false; }

	m_pMonsterButton->SetID(MONSTER_BUTTON);
	m_pDuelStartButton->SetID(DUEL_START_BUTTON);
	m_pWeaponButton->SetID(WEAPON_BUTTON);
	m_iButtonID = DUEL_START_BUTTON;

	// BGM�Đ��J�n
	CSound::Play(BGM_2);

	return true;
}


/*������������������������������������������������������������������������������

	�I��

������������������������������������������������������������������������������*/
void CHome::Fin()
{
	// BGM�Đ���~
	CSound::Stop(BGM_2);

	// �S�I�u�W�F�N�g�I������
	C2DObj::FinAll(m_p2DObj);
	CGameObj::FinAll(m_pObj);
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CHome::Update()
{
	// �}�E�X�J�[�\����\��
	SetShowCursor(false);

	// �S�I�u�W�F�N�g�X�V
	CGameObj::UpdateAll(m_pObj);
	C2DObj::UpdateAll(m_p2DObj);

	
	//����������������������������������������
	// �V�[���ړ�
	//����������������������������������������
#pragma region �R���g���[���[
	if (0 < CInput::GetJoyCount())
	{
		//����������������������������������������
		// �^�C�g����ʂɈړ�
		//����������������������������������������
		if (CInput::GetJoyTrigger(0, JOYBUTTON_B))
		{
			// �F��ς���
			m_pReturnButton->SetColor(XMFLOAT4(1.0f, 0.8f, 0.8f, 1.0f));
			// �傫��������������
			m_pReturnButton->SetSize(XMFLOAT2(120.0f, 60.0f));
		}
		if (CInput::GetJoyRelease(0, JOYBUTTON_B))
		{
			CSound::Play(SE_1);

			// �F��߂�
			m_pReturnButton->SetColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

			// �傫����߂�
			m_pReturnButton->SetSize(XMFLOAT2(128.0f, 64.0f));

			// �V�[���`�F���W
			CFade::Out(SCENE_TITLE);
		}

		//����������������������������������������
		// ID�ɂ���Ĉړ�����V�[�����ς��
		// ����I����� / �퓬�J�n / �G�I�����
		//����������������������������������������
		// �V�[���ړ�
		if (CInput::GetJoyTrigger(0, JOYBUTTON_A))
		{
			CSound::Play(SE_1);
			switch (m_iButtonID)
			{
			case MONSTER_BUTTON:
				CFade::Out(SCENE_ENEMY_SELECT);
				break;
			case DUEL_START_BUTTON:
				switch (CEnemyManger::GetEnemy())
				{
				case ENEMY_GOLEM:
					CFade::Out(SCENE_BATTLE_GOLEM);
					break;
				case ENEMY_SWORDMAN:
					CFade::Out(SCENE_BATTLE_SM);
					break;
				default:
					break;
				}
				break;
			case WEAPON_BUTTON:
				CFade::Out(SCENE_WEAPON_SELECT);
				break;
			default:
				break;
			}
		}

		// �I�𒆂̃{�^����ς���
		if (CInput::GetJoyCrossTrigger(0, JOYCROSS_RIGHT))
		{
			CSound::Play(SE_2);
			m_iButtonID--;
			if (m_iButtonID < 0) { m_iButtonID = MAX_BUTTON_HOME - 1; }
		}
		if (CInput::GetJoyCrossTrigger(0, JOYCROSS_LEFT))
		{
			CSound::Play(SE_2);
			m_iButtonID++;
			if (MAX_BUTTON_HOME - 1 < m_iButtonID) { m_iButtonID = 0; }
		}

		// MonsterButton�I��
		if (m_iButtonID == m_pMonsterButton->GetID()) { m_pMonsterButton->NowSelectScaleUp(); }
		else { m_pMonsterButton->NowSelectScaleDown(); }
		// DuelStartButton�I��
		if (m_iButtonID == m_pDuelStartButton->GetID()) { m_pDuelStartButton->NowSelectScaleUp(); }
		else { m_pDuelStartButton->NowSelectScaleDown(); }
		// WeaponButton�I��
		if (m_iButtonID == m_pWeaponButton->GetID()) { m_pWeaponButton->NowSelectScaleUp(); }
		else { m_pWeaponButton->NowSelectScaleDown(); }
	}
#pragma endregion
#pragma region �}�E�X
	else
	{
		// �^�C�g����ʂɈړ�
		if (m_pMouseCursor->CollisionAABB(m_pMouseCursor, m_pReturnButton))
		{
			// �F��ς���
			m_pReturnButton->SetColor(XMFLOAT4(1.0f, 0.8f, 0.8f, 1.0f));
			if (CInput::GetMouseButton(MOUSEBUTTON_L))
			{	// �傫��������������
				m_pReturnButton->SetSize(XMFLOAT2(120.0f, 60.0f));
			}
			if (CInput::GetMouseRelease(MOUSEBUTTON_L))
			{
				CSound::Play(SE_1);
				// �V�[���`�F���W
				CFade::Out(SCENE_TITLE);
			}
		}
		else
		{	// �F��߂�
			m_pReturnButton->SetColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (CInput::GetMouseRelease(MOUSEBUTTON_L))
		{	// �傫����߂�
			m_pReturnButton->SetSize(XMFLOAT2(128.0f, 64.0f));
		}

		// �Q�[���V�[���Ɉړ�
		if (m_pMouseCursor->CollisionAABB(m_pMouseCursor, m_pDuelStartButton))
		{
			m_pDuelStartButton->NowSelectScaleUp();
			if (CInput::GetMouseTrigger(MOUSEBUTTON_L))
			{
				switch (CEnemyManger::GetEnemy())
				{
				case ENEMY_GOLEM:
					CFade::Out(SCENE_BATTLE_GOLEM);
					break;
				case ENEMY_SWORDMAN:
					CFade::Out(SCENE_BATTLE_SM);
					break;
				default:
					break;
				}
				CSound::Play(SE_1);
			}
		}
		else { m_pDuelStartButton->NowSelectScaleDown(); }
		// ����I���V�[���Ɉړ�
		if (m_pMouseCursor->CollisionAABB(m_pMouseCursor, m_pWeaponButton))
		{
			m_pWeaponButton->NowSelectScaleUp();
			if (CInput::GetMouseTrigger(MOUSEBUTTON_L))
			{
				CFade::Out(SCENE_WEAPON_SELECT);
				CSound::Play(SE_1);
			}
		}
		else { m_pWeaponButton->NowSelectScaleDown(); }
		// �����X�^�[�I���V�[���Ɉړ�
		if (m_pMouseCursor->CollisionAABB(m_pMouseCursor, m_pMonsterButton))
		{
			m_pMonsterButton->NowSelectScaleUp();
			if (CInput::GetMouseTrigger(MOUSEBUTTON_L))
			{
				CFade::Out(SCENE_ENEMY_SELECT);
				CSound::Play(SE_1);
			}
		}
		else { m_pMonsterButton->NowSelectScaleDown(); }
	}
#pragma endregion
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CHome::Draw()
{
	// �S�L�����`��
	CGameObj::DrawAll(m_pObj);

	// 2DObj�`��
	C2DObj::DrawAll(m_p2DObj);
}
