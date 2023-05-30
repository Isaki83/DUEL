//=============================================================================
//
// ����I����� [WeaponSelect.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "WeaponSelect.h"
#include "2Dobj.h"
#include "Sound.h"
#include "Input.h"
#include "Manager.h"


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CWeaponSelect::CWeaponSelect() : CScene()
{
	m_id = SCENE_WEAPON_SELECT;

	m_pWeapon = nullptr;

	m_pMouseCursor = nullptr;
	m_pReturnButton = nullptr;
	m_pDecisionButton = nullptr;
	for (int i = 0; i < _countof(m_pArrowButton); i++) { m_pArrowButton[i] = nullptr; }
	for (int i = 0; i < _countof(m_pWeaponIcon); i++) { m_pWeaponIcon[i] = nullptr; }
	m_pBG_Frame = nullptr;
	m_pParmBG = nullptr;
	m_pWeaponParmUI = nullptr;
	m_pNameUI = nullptr;
}


/*������������������������������������������������������������������������������

	�f�X�g���N�^

������������������������������������������������������������������������������*/
CWeaponSelect::~CWeaponSelect()
{
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
bool CWeaponSelect::Init()
{
	m_camera.Init();
	CCamera::Set(&m_camera);

	// ���퐶��
	m_pWeapon = new CWeapon(this);

	m_pMouseCursor = new CMouseCursor(this);
	m_pReturnButton = new CReturnButton(this);
	m_pNameUI = new CNameUI(this);
	m_pWeaponParmUI = new CWeaponParmUI(this);
	m_pParmBG = new CParmBG(this);
	m_pDecisionButton = new CDecisionButton(this);
	for (int i = 0; i < 2; i++) { m_pArrowButton[i] = new CArrowButton(this); }
	for (int i = 0; i < MAX_WEAPON - 1; i++) { m_pWeaponIcon[i] = new CWeaponIcon(this); }
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
void CWeaponSelect::Fin()
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
void CWeaponSelect::Update()
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
void CWeaponSelect::Draw()
{
	// �S�L�����`��
	CGameObj::DrawAll(m_pObj);

	// 2DObj�`��
	C2DObj::DrawAll(m_p2DObj);
}
