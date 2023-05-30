//=============================================================================
//
// �G�I����� [EnemySelect.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "EnemySelect.h"
#include "2Dobj.h"
#include "Sound.h"
#include "Input.h"
#include "Fade.h"
#include "Manager.h"
#include "Golem.h"
#include "SwordMan.h"


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CEnemySelect::CEnemySelect() : CScene()
{
	m_id = SCENE_ENEMY_SELECT;

	m_pMouseCursor = nullptr;
	m_pReturnButton = nullptr;
	m_pDecisionButton = nullptr;
	for (int i = 0; i < _countof(m_pArrowButton); i++) { m_pArrowButton[i] = nullptr; }
	for (int i = 0; i < _countof(m_pEnemyIcon); i++) { m_pEnemyIcon[i] = nullptr; }
	m_pBG_Frame = nullptr;
	m_pNameUI = nullptr;
}


/*������������������������������������������������������������������������������

	�f�X�g���N�^

������������������������������������������������������������������������������*/
CEnemySelect::~CEnemySelect()
{
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
bool CEnemySelect::Init()
{
	m_camera.Init();
	CCamera::Set(&m_camera);

	new CGolem(this);
	new CSwordMan(this);

	m_pMouseCursor = new CMouseCursor(this);
	m_pReturnButton = new CReturnButton(this);
	m_pDecisionButton = new CDecisionButton(this);
	m_pNameUI = new CNameUI(this);
	for (int i = 0; i < 2; i++) { m_pArrowButton[i] = new CArrowButton(this); }
	for (int i = 0; i < MAX_ENEMY - 1; i++) { m_pEnemyIcon[i] = new CEnemyIcon(this); }
	m_pBG_Frame = new CBG_Frame(this);

	// �S�I�u�W�F�N�g������
	if (FAILED(CGameObj::InitAll(m_pObj))) { return false; }
	if (FAILED(C2DObj::InitAll(m_p2DObj))) { return false; }
	IconInit();

	// BGM�Đ��J�n
	CSound::Play(BGM_2);

	return true;
}


/*������������������������������������������������������������������������������

	�I��

������������������������������������������������������������������������������*/
void CEnemySelect::Fin()
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
void CEnemySelect::Update()
{
	// �}�E�X�J�[�\����\��
	SetShowCursor(false);

	// �S�I�u�W�F�N�g�X�V
	IconUpdate();
	CGameObj::UpdateAll(m_pObj);
	C2DObj::UpdateAll(m_p2DObj);

	
	//����������������������������������������
	// �z�[����ʂɈړ�
	//����������������������������������������
#pragma region �R���g���[���[
	if (0 < CInput::GetJoyCount())
	{
		if (CInput::GetJoyButton(0, JOYBUTTON_B))
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

			// �V�[���`�F���W
			CFade::Out(SCENE_HOME);
		}
	}
#pragma endregion
#pragma region �}�E�X
	else
	{
		//����������������������������������������
		// �}�E�X�Ɩ߂�{�^���̓����蔻��
		//����������������������������������������
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
				CFade::Out(SCENE_HOME);
			}
		}
		else
		{	// �F��߂�
			m_pReturnButton->SetColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
#pragma endregion
	if (CInput::GetMouseRelease(MOUSEBUTTON_L) || CInput::GetJoyRelease(0, JOYBUTTON_B))
	{	// �傫����߂�
		m_pReturnButton->SetSize(XMFLOAT2(128.0f, 64.0f));
	}
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CEnemySelect::Draw()
{
	// �S�L�����`��
	CGameObj::DrawAll(m_pObj);

	// 2DObj�`��
	C2DObj::DrawAll(m_p2DObj);
}
