//=============================================================================
//
// �^�C�g����� [Title.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "Title.h"
#include "2Dobj.h"
#include "Sound.h"
#include "Input.h"
#include "Fade.h"
#include "Manager.h"
#include "Ground.h"
#include "SwordMan.h"
#include "DebugProc.h"


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CTitle::CTitle() : CScene()
{
	m_id = SCENE_TITLE;

	m_pMouseCursor = nullptr;
	m_pTitleLogo = nullptr;
	m_pStartButton = nullptr;
	m_pExitButton = nullptr;
}


/*������������������������������������������������������������������������������

	�f�X�g���N�^

������������������������������������������������������������������������������*/
CTitle::~CTitle()
{
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
bool CTitle::Init()
{
	m_camera.Init();
	CCamera::Set(&m_camera);

	// ����
	new CGround(this);
	new CSwordMan(this);

	// ���� / �`��̏���(�オ��O)
	m_pMouseCursor = new CMouseCursor(this);
	m_pTitleLogo = new CTitleLogo(this);
	m_pStartButton = new CStartButton(this);
	m_pExitButton = new CExitButton(this);

	// �S�I�u�W�F�N�g������
	if (FAILED(CGameObj::InitAll(m_pObj))) { return false; }
	if (FAILED(C2DObj::InitAll(m_p2DObj))) { return false; }

	m_pStartButton->SetID(START_BUTTON);
	m_pExitButton->SetID(EXIT_BUTTON);
	m_iButtonID = 0;

	// BGM�Đ��J�n
	CSound::Play(BGM_2);

	return true;
}


/*������������������������������������������������������������������������������

	�I��

������������������������������������������������������������������������������*/
void CTitle::Fin()
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
void CTitle::Update()
{
	//����������������������������������������
	// �}�E�X�J�[�\����\��
	//����������������������������������������
	SetShowCursor(false);

	//����������������������������������������
	// �S�I�u�W�F�N�g�X�V
	//����������������������������������������
	CGameObj::UpdateAll(m_pObj);
	C2DObj::UpdateAll(m_p2DObj);

	//����������������������������������������
	// �V�[���ړ�
	//����������������������������������������
#pragma region �R���g���[���[
	if (0 < CInput::GetJoyCount())
	{
		// �V�[���`�F���W
		if (CInput::GetJoyTrigger(0, JOYBUTTON_A))
		{
			CSound::Play(SE_1);
			switch (m_iButtonID)
			{
			case START_BUTTON:
				CFade::Out(SCENE_HOME);
				break;
			case EXIT_BUTTON:
				exit(0);
				break;
			default:
				break;
			}
		}

		// �I�𒆂̃{�^����ς���
		if (CInput::GetJoyCrossTrigger(0, JOYCROSS_UP))
		{
			CSound::Play(SE_2);
			m_iButtonID--;
			if (m_iButtonID < 0) { m_iButtonID = MAX_BUTTON_TITLE - 1; }
		}
		if (CInput::GetJoyCrossTrigger(0, JOYCROSS_DOWN))
		{
			CSound::Play(SE_2);
			m_iButtonID++;
			if (MAX_BUTTON_TITLE - 1 < m_iButtonID) { m_iButtonID = 0; }
		}

		// StartButton�I��
		if (m_iButtonID == m_pStartButton->GetID()) { m_pStartButton->NowSelectScaleUp(); }
		else { m_pStartButton->NowSelectScaleDown(); }
		// ExitButton�I��
		if (m_iButtonID == m_pExitButton->GetID()) { m_pExitButton->NowSelectScaleUp(); }
		else { m_pExitButton->NowSelectScaleDown(); }
	}
#pragma endregion
#pragma region �}�E�X
	else
	{
		// �z�[����ʂɈړ�
		if (m_pMouseCursor->CollisionAABB(m_pMouseCursor, m_pStartButton))
		{
			m_pStartButton->NowSelectScaleUp();
			if (CInput::GetMouseRelease(MOUSEBUTTON_L))
			{
				CFade::Out(SCENE_HOME);
				CSound::Play(SE_1);
			}
		}
		else { m_pStartButton->NowSelectScaleDown(); }
		// �Q�[�����I������
		if (m_pMouseCursor->CollisionAABB(m_pMouseCursor, m_pExitButton))
		{
			m_pExitButton->NowSelectScaleUp();
			if (CInput::GetMouseRelease(MOUSEBUTTON_L))
			{
				CSound::Play(SE_1);
				exit(0);
			}
		}
		else { m_pExitButton->NowSelectScaleDown(); }
	}
#pragma endregion
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CTitle::Draw()
{
	// �`��
	CGameObj::DrawAll(m_pObj);
	C2DObj::DrawAll(m_p2DObj);
}
