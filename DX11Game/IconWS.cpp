//=============================================================================
//
// ����I����� [IconWS.cpp]
// �A�C�R���֌W�̏���
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "WeaponSelect.h"
#include "Input.h"
#include "Sound.h"


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
void CWeaponSelect::IconInit()
{
	//����������������������������������������
	// �A�C�R��
	//����������������������������������������
	// �T�uID�ݒ�
	m_pWeaponIcon[0]->SetSubID(GOTSUB_WSWORD);
	m_pWeaponIcon[1]->SetSubID(GOTSUB_AXE);
	m_pWeaponIcon[2]->SetSubID(GOTSUB_LSWORD);

	// �e�N�X�`���ݒ�
	m_pWeaponIcon[0]->SetTexture(TEX_ICON_WSWORD);
	m_pWeaponIcon[1]->SetTexture(TEX_ICON_AXE);
	m_pWeaponIcon[2]->SetTexture(TEX_ICON_LSWORD);

	// �ʒu�ݒ�
	// ��{�̈ʒu
	m_pWeaponIcon[0]->SetPos(XMFLOAT2(0.0f, -285.0f));
	for (int i = 0; i < _countof(m_pWeaponIcon) - 1; i++)
	{ m_pWeaponIcon[i + 1]->SetPos(XMFLOAT2(m_pWeaponIcon[i]->GetPos().x + 130.0f, -285.0f)); }
	// ���̕���𒆉��ɍ��킹��
	m_pWeaponIcon[0]->SetPos(XMFLOAT2(0.0f - m_pWeaponIcon[CWeapon::GetWeapon() - 1]->GetPos().x, -285.0f));
	for (int i = 0; i < _countof(m_pWeaponIcon) - 1; i++)
	{ m_pWeaponIcon[i + 1]->SetPos(XMFLOAT2(m_pWeaponIcon[i]->GetPos().x + 130.0f, -285.0f)); }
	// �ړI�̈ʒu�����̈ʒu��
	for (int i = 0; i < _countof(m_pWeaponIcon); i++)
	{ m_pWeaponIcon[i]->SetTPos(m_pWeaponIcon[i]->GetPos()); }
	// �g�k�ݒ�
	for (int i = 0; i < _countof(m_pWeaponIcon); i++)
	{
		// ���S�̃A�C�R���͑傫��
		if (m_pWeaponIcon[i]->GetPos().x == 0.0f) { m_pWeaponIcon[i]->SetSize(XMFLOAT2(130.0f, 130.0f)); }
		else { m_pWeaponIcon[i]->SetSize(XMFLOAT2(70.0f, 70.0f)); }
	}
	CWeapon::SetCenterIcon(CWeapon::GetWeapon());


	//����������������������������������������
	// �A�C�R�������E�ɓ������{�^��
	//����������������������������������������
	// �T�uID�ݒ�
	m_pArrowButton[0]->SetSubID(GOTSUB_RIGHT);
	m_pArrowButton[1]->SetSubID(GOTSUB_LEFT);

	// �����ݒ�
	for (int i = 0; i < 2; i++) { m_pArrowButton[i]->SetDirection(i); }

	// �ʒu�ݒ�
	m_pArrowButton[0]->SetPos(XMFLOAT2(500.0f, -285.0f));
	m_pArrowButton[0]->SetCenter(m_pArrowButton[0]->GetPos());
	m_pArrowButton[1]->SetPos(XMFLOAT2(-500.0f, -285.0f));
	m_pArrowButton[1]->SetCenter(m_pArrowButton[1]->GetPos());
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CWeaponSelect::IconUpdate()
{
	//����������������������������������������
	//����{�^���̏���
	//����������������������������������������
#pragma region �R���g���[���[
	if (0 < CInput::GetJoyCount())
	{
		if (CInput::GetJoyButton(0, JOYBUTTON_A)) { m_pDecisionButton->NowSelectScaleUp(); }
		else { m_pDecisionButton->NowSelectScaleDown(); }
		if (CInput::GetJoyRelease(0, JOYBUTTON_A))
		{
			CSound::Play(SE_1);

			// ������m�肷��
			for (int i = 0; i < _countof(m_pWeaponIcon); ++i)
			{
				if (-30.0f <= m_pWeaponIcon[i]->GetPos().x && m_pWeaponIcon[i]->GetPos().x <= 30.0f)
				{
					switch (m_pWeaponIcon[i]->GetSubID())
					{
					case GOTSUB_WSWORD:
						CWeapon::SetWeapon(WEAPON_WOOD_SWORD);
						break;

					case GOTSUB_AXE:
						CWeapon::SetWeapon(WEAPON_AXE);
						break;

					case GOTSUB_LSWORD:
						CWeapon::SetWeapon(WEAPON_LARGE_SWORD);
						break;

					default:
						break;
					}
				}
			}
		}
	}
#pragma endregion
#pragma region �}�E�X
	else
	{
		//����������������������������������������
		// �}�E�X�ƌ���{�^���̓����蔻��
		//����������������������������������������
		if (m_pMouseCursor->CollisionAABB(m_pMouseCursor, m_pDecisionButton))
		{
			m_pDecisionButton->NowSelectScaleUp();
			if (CInput::GetMouseRelease(MOUSEBUTTON_L))
			{
				CSound::Play(SE_1);
				// ������m�肷��
				for (int i = 0; i < _countof(m_pWeaponIcon); ++i)
				{
					if (-30.0f <= m_pWeaponIcon[i]->GetPos().x && m_pWeaponIcon[i]->GetPos().x <= 30.0f)
					{
						switch (m_pWeaponIcon[i]->GetSubID())
						{
						case GOTSUB_WSWORD:
							CWeapon::SetWeapon(WEAPON_WOOD_SWORD);
							break;

						case GOTSUB_AXE:
							CWeapon::SetWeapon(WEAPON_AXE);
							break;

						case GOTSUB_LSWORD:
							CWeapon::SetWeapon(WEAPON_LARGE_SWORD);
							break;

						default:
							break;
						}
					}
				}
			}
		}
		else { m_pDecisionButton->NowSelectScaleDown(); }
	}
#pragma endregion

	for (int i = 0; i < 2; i++)
	{
		//����������������������������������������
		// ���{�^���ŃA�C�R���𓮂���
		//����������������������������������������
#pragma region �R���g���[���[
		if (0 < CInput::GetJoyCount())
		{
			switch (m_pArrowButton[i]->GetSubID())
			{
			case GOTSUB_RIGHT:	// �E
				if (CInput::GetJoyCrossTrigger(0, JOYCROSS_RIGHT))
				{
					CSound::Play(SE_2);

					//�A�C�R���̈ʒu�����炷
					int CenterIcon = CWeapon::GetCenterIcon();
					if (-30.0f <= m_pWeaponIcon[MAX_SUB_WEAPON_ICON - 2]->GetPos().x && m_pWeaponIcon[MAX_SUB_WEAPON_ICON - 2]->GetPos().x <= 30.0f)
					{	
						// �A�C�R������Ԓ[�����Ȃ甽�Α��ɍs��
						m_pWeaponIcon[0]->SetTPos(XMFLOAT2(0.0f, -285.0f));
						CenterIcon -= MAX_WEAPON - 2;
					}
					else
					{
						m_pWeaponIcon[0]->SetTPos(XMFLOAT2(m_pWeaponIcon[0]->GetTPos().x - 130.0f, -285.0f));
						CenterIcon += 1;
					}
					CWeapon::SetCenterIcon((EWeapon)CenterIcon);
				}
				break;
			case GOTSUB_LEFT:	// ��
				if (CInput::GetJoyCrossTrigger(0, JOYCROSS_LEFT))
				{
					CSound::Play(SE_2);

					//�A�C�R���̈ʒu�����炷
					int CenterIcon = CWeapon::GetCenterIcon();
					if (-30.0f <= m_pWeaponIcon[0]->GetPos().x && m_pWeaponIcon[0]->GetPos().x <= 30.0f)
					{	// �A�C�R������Ԓ[�����Ȃ甽�Α��ɍs��
						m_pWeaponIcon[0]->SetTPos(XMFLOAT2(0.0f - m_pWeaponIcon[MAX_SUB_WEAPON_ICON - 2]->GetPos().x, -285.0f));
						CenterIcon += MAX_WEAPON - 2;
					}
					else
					{
						m_pWeaponIcon[0]->SetTPos(XMFLOAT2(m_pWeaponIcon[0]->GetTPos().x + 130.0f, -285.0f));
						CenterIcon -= 1;
					}

					CWeapon::SetCenterIcon((EWeapon)CenterIcon);
				}
				break;
			default:
				break;
			}
		}
#pragma endregion
#pragma region �}�E�X
		else
		{
			//����������������������������������������
			// �}�E�X�Ɩ��{�^���̓����蔻��
			//����������������������������������������
			if (m_pMouseCursor->CollisionAABB(m_pMouseCursor, m_pArrowButton[i]))
			{
				// �F��ς���
				m_pArrowButton[i]->SetColor(XMFLOAT4(1.0f, 0.8f, 0.8f, 1.0f));
				if (CInput::GetMouseButton(MOUSEBUTTON_L) || CInput::GetJoyButton(0, JOYBUTTON_A))
				{	// �傫��������������
					m_pArrowButton[i]->SetSize(XMFLOAT2(60.0f, 60.0f));
				}
				if (CInput::GetMouseRelease(MOUSEBUTTON_L) || CInput::GetJoyRelease(0, JOYBUTTON_A))
				{
					CSound::Play(SE_2);
					//�A�C�R���̈ʒu�����炷
					int CenterIcon = CWeapon::GetCenterIcon();
					switch (m_pArrowButton[i]->GetSubID())
					{
					case GOTSUB_RIGHT:
						if (-30.0f <= m_pWeaponIcon[MAX_SUB_WEAPON_ICON - 2]->GetPos().x && m_pWeaponIcon[MAX_SUB_WEAPON_ICON - 2]->GetPos().x <= 30.0f)
						{	// �A�C�R������Ԓ[�����Ȃ甽�Α��ɍs��
							m_pWeaponIcon[0]->SetTPos(XMFLOAT2(0.0f, -285.0f));
							CenterIcon -= MAX_WEAPON - 2;
						}
						else
						{
							m_pWeaponIcon[0]->SetTPos(XMFLOAT2(m_pWeaponIcon[0]->GetTPos().x - 130.0f, -285.0f));
							CenterIcon += 1;
						}
						break;

					case GOTSUB_LEFT:
						if (-30.0f <= m_pWeaponIcon[0]->GetPos().x
							&& m_pWeaponIcon[0]->GetPos().x <= 30.0f)
						{	// �A�C�R������Ԓ[�����Ȃ甽�Α��ɍs��
							m_pWeaponIcon[0]->
								SetTPos(XMFLOAT2(0.0f - m_pWeaponIcon[MAX_SUB_WEAPON_ICON - 2]->GetPos().x, -285.0f));
							CenterIcon += MAX_WEAPON - 2;
						}
						else
						{
							m_pWeaponIcon[0]->SetTPos(XMFLOAT2(m_pWeaponIcon[0]->GetTPos().x + 130.0f, -285.0f));
							CenterIcon -= 1;
						}
						break;

					default:
						break;
					}
					CWeapon::SetCenterIcon((EWeapon)CenterIcon);
				}
			}
			else
			{	// �F��߂�
				m_pArrowButton[i]->SetColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			if (CInput::GetMouseRelease(MOUSEBUTTON_L))
			{
				// �傫����߂�
				m_pDecisionButton->SetSize(XMFLOAT2(140.0f, 70.0f));
				m_pArrowButton[i]->SetSize(XMFLOAT2(70.0f, 70.0f));
			}
		}
#pragma endregion
	}


	//����������������������������������������
	// �A�C�R��
	//����������������������������������������
	m_pWeaponIcon[0]->SetSpeed((m_pWeaponIcon[0]->GetTPos().x - m_pWeaponIcon[0]->GetPos().x) / 5.0f);
	// �ʒu
	m_pWeaponIcon[1]->SetPos(XMFLOAT2(m_pWeaponIcon[0]->GetPos().x + 130.0f, -285.0f));
	m_pWeaponIcon[2]->SetPos(XMFLOAT2(m_pWeaponIcon[1]->GetPos().x + 130.0f, -285.0f));
	// �g�k
	for (int i = 0; i < _countof(m_pWeaponIcon); ++i)
	{
		// ���S�̃A�C�R���͑傫��
		if (-30.0f <= m_pWeaponIcon[i]->GetPos().x && m_pWeaponIcon[i]->GetPos().x <= 30.0f) 
		{ m_pWeaponIcon[i]->SetSize(XMFLOAT2(130.0f, 130.0f)); }
		else { m_pWeaponIcon[i]->SetSize(XMFLOAT2(70.0f, 70.0f)); }
	}
}