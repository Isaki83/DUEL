//=============================================================================
//
// �o�g�����(�\�[�_�\) [BattleSwordMan.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "BattleSwordMan.h"
#include "Input.h"
#include "GameObj.h"
#include "Sound.h"
#include "Ground.h"
#include "Manager.h"
#include "Fade.h"
#include "EnemyManger.h"
#include "HitStop.h"
#include "DebugProc.h"


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CBattleSwordMan::CBattleSwordMan() : CScene()
{
	m_id = SCENE_BATTLE_SM;

	m_nBoundary = 0;
	m_bBoundary = false;

	m_pPlayer = nullptr;
	m_pSwordMan = nullptr;

	m_pHPGaugePlayer = nullptr;
	m_pHPGaugeEnemy = nullptr;
	m_pWeaponIcon = nullptr;
	m_pEnemyIcon = nullptr;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
bool CBattleSwordMan::Init()
{
	m_stopFlag = false;

	m_camera.Init();
	CCamera::Set(&m_camera);

	CLight* pLight = CLight::Get();
	if (pLight) { pLight->Init(); }

	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	// �n�ʐ���
	new CGround(this);
	// ���퐶��
	m_pWeapon = new CWeapon(this);
	// �v���C���[����
	m_pPlayer = new CPlayer(this);
	// �G����
	m_pSwordMan = new CSwordMan(this);

	// HP�Q�[�W(�v���C���[)����
	m_pHPGaugePlayer = new CHPGaugePlayer(this);
	// HP�Q�[�W(�G)����
	m_pHPGaugeEnemy = new CHPGaugeEnemy(this);
	// �A�C�R������
	m_pWeaponIcon = new CWeaponIcon(this);
	m_pEnemyIcon = new CEnemyIcon(this);

	// �S�I�u�W�F�N�g������
	if (FAILED(CGameObj::InitAll(m_pObj))) { return false; }
	if (FAILED(C2DObj::InitAll(m_p2DObj))) { return false; }
	// ������
	m_pPlayer->SetPos(XMFLOAT3(0.0f, 500.0f, 3000.0f));
	m_pSwordMan->SetPos(XMFLOAT3(0.0f, 600.0f, 0.0f));
	m_pHPGaugePlayer->SetLife(m_pPlayer->GetMaxLife());
	m_pHPGaugeEnemy->SetLife(m_pSwordMan->GetMaxLife());

	m_camera.SetPlayer(m_pPlayer);

	// BGM�Đ��J�n
	CSound::Play(BGM_1);
	

	return true;
}


/*������������������������������������������������������������������������������

	�I��

������������������������������������������������������������������������������*/
void CBattleSwordMan::Fin()
{
	// BGM�Đ���~
	CSound::Stop(BGM_1);

	// �S�I�u�W�F�N�g�I������
	C2DObj::FinAll(m_p2DObj);
	CGameObj::FinAll(m_pObj);
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CBattleSwordMan::Update()
{
	// �}�E�X�J�[�\����\��
	SetShowCursor(false);

	if (CInput::GetKeyTrigger(VK_F3)) 
	{
		m_nBoundary = (m_nBoundary + 1) % 2;
		UpdateBoundary();
	}
	if (m_bBoundary)
	{
		static LPCSTR boundary[] = { "�ˮ���", "ˮ���" };
		CDebugProc::Print("\x84\xCE[F3] : ����� %s\x84\xCF\n", boundary[m_nBoundary]);
	}

	if (CInput::GetKeyRelease(VK_Q) || CInput::GetJoyRelease(0, JOYBUTTON_START))
	{
		m_stopFlag = !m_stopFlag;
	}

	if (!m_stopFlag)
	{
		// �}�E�X���E�B���h�E�̒��S�ɌŒ肷��
		SetMouseMiddlePos();

		if (CHitStop::HitStop())
		{
			// �S�L�����X�V
			CGameObj::UpdateAll(m_pObj);
			C2DObj::UpdateAll(m_p2DObj);
		}
	}

	// �G�ƃv���C���[�ǂ��炩�����񂾂�
	if (m_pSwordMan->GetSceneChengeFlag() || m_pPlayer->GetSceneChengeFlag())
	{
		CFade::Out(SCENE_HOME);
		m_pSwordMan->SetSceneChengeFlag(false);
		m_pPlayer->SetSceneChengeFlag(false);
	}
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CBattleSwordMan::Draw()
{
	// �S�L�����`��
	CGameObj::DrawAll(m_pObj);

	// 2DObj�`��
	C2DObj::DrawAll(m_p2DObj);
}


/*������������������������������������������������������������������������������

	���E�\���X�V

������������������������������������������������������������������������������*/
void CBattleSwordMan::UpdateBoundary()
{
	switch (m_nBoundary) 
	{
	case 0:	// ���E�\������
		m_pWeapon->SetBoundaryType(BT_NONE);
		m_pSwordMan->SetBoundaryType(BT_NONE);
		m_pPlayer->SetBoundaryType(BT_NONE);
		m_bBoundary = false;
		break;
	case 1:	// ���E�{�b�N�X(BT_OBB)
		m_pWeapon->SetBoundaryType(BT_OBB);
		m_pSwordMan->SetBoundaryType(BT_OBB);
		m_pPlayer->SetBoundaryType(BT_OBB);
		m_bBoundary = true;
		break;
	}
}