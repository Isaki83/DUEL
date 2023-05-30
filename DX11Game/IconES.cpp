//=============================================================================
//
// �G�I����� [IconES.cpp]
// �A�C�R���֌W�̏���
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "EnemySelect.h"
#include "EnemyManger.h"
#include "Input.h"
#include "Sound.h"


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
void CEnemySelect::IconInit()
{
	//����������������������������������������
	// �A�C�R��
	//����������������������������������������
	// �T�uID�ݒ�
	m_pEnemyIcon[0]->SetSubID(GOTSUB_GOLEM);
	m_pEnemyIcon[1]->SetSubID(GOTSUB_SM);

	// �e�N�X�`���ݒ�
	m_pEnemyIcon[0]->SetTexture(TEX_ICON_GOLEM);
	m_pEnemyIcon[1]->SetTexture(TEX_ICON_SM);

	// �ʒu�ݒ�
	// ��{�̈ʒu
	m_pEnemyIcon[0]->SetPos(XMFLOAT2(0.0f, -285.0f));
	for (int i = 0; i < _countof(m_pEnemyIcon) - 1; i++)
	{ m_pEnemyIcon[i + 1]->SetPos(XMFLOAT2(m_pEnemyIcon[i]->GetPos().x + 130.0f, -285.0f)); }
	// ���̕���𒆉��ɍ��킹��
	m_pEnemyIcon[0]->SetPos(XMFLOAT2(0.0f - m_pEnemyIcon[CEnemyManger::GetEnemy() - 1]->GetPos().x, -285.0f));
	for (int i = 0; i < _countof(m_pEnemyIcon) - 1; i++)
	{ m_pEnemyIcon[i + 1]->SetPos(XMFLOAT2(m_pEnemyIcon[i]->GetPos().x + 130.0f, -285.0f)); }
	// �ړI�̈ʒu�����̈ʒu��
	for (int i = 0; i < _countof(m_pEnemyIcon); i++)
	{ m_pEnemyIcon[i]->SetTPos(m_pEnemyIcon[i]->GetPos()); }
	// �g�k�ݒ�
	for (int i = 0; i < _countof(m_pEnemyIcon); i++)
	{
		// ���S�̃A�C�R���͑傫��
		if (m_pEnemyIcon[i]->GetPos().x == 0.0f) { m_pEnemyIcon[i]->SetSize(XMFLOAT2(130.0f, 130.0f)); }
		else { m_pEnemyIcon[i]->SetSize(XMFLOAT2(70.0f, 70.0f)); }
	}
	CEnemyManger::SetCenterIcon(CEnemyManger::GetEnemy());


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
void CEnemySelect::IconUpdate()
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
			for (int i = 0; i < _countof(m_pEnemyIcon); ++i)
			{
				if (-30.0f <= m_pEnemyIcon[i]->GetPos().x && m_pEnemyIcon[i]->GetPos().x <= 30.0f)
				{
					switch (m_pEnemyIcon[i]->GetSubID())
					{
					case GOTSUB_GOLEM:
						CEnemyManger::SetEnemy(ENEMY_GOLEM);
						break;

					case GOTSUB_SM:
						CEnemyManger::SetEnemy(ENEMY_SWORDMAN);
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
				for (int i = 0; i < _countof(m_pEnemyIcon); ++i)
				{
					if (-30.0f <= m_pEnemyIcon[i]->GetPos().x && m_pEnemyIcon[i]->GetPos().x <= 30.0f)
					{
						switch (m_pEnemyIcon[i]->GetSubID())
						{
						case GOTSUB_GOLEM:
							CEnemyManger::SetEnemy(ENEMY_GOLEM);
							break;

						case GOTSUB_SM:
							CEnemyManger::SetEnemy(ENEMY_SWORDMAN);
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

					// �F��ς���
					m_pArrowButton[i]->SetColor(XMFLOAT4(1.0f, 0.8f, 0.8f, 1.0f));
					// �傫��������������
					m_pArrowButton[i]->SetSize(XMFLOAT2(60.0f, 60.0f));

					// �F��߂�
					m_pArrowButton[i]->SetColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

					//�A�C�R���̈ʒu�����炷
					int CenterIcon = CEnemyManger::GetCenterIcon();
					if (-30.0f <= m_pEnemyIcon[MAX_SUB_ENEMY_ICON - 2]->GetPos().x && m_pEnemyIcon[MAX_SUB_ENEMY_ICON - 2]->GetPos().x <= 30.0f)
					{	
						// �A�C�R������Ԓ[�����Ȃ甽�Α��ɍs��
						m_pEnemyIcon[0]->SetTPos(XMFLOAT2(0.0f, -285.0f));
						CenterIcon -= MAX_ENEMY - 2;
					}
					else
					{
						m_pEnemyIcon[0]->SetTPos(XMFLOAT2(m_pEnemyIcon[0]->GetTPos().x - 130.0f, -285.0f));
						CenterIcon += 1;
					}
					CEnemyManger::SetCenterIcon((EEnemy)CenterIcon);
				}
				break;
			case GOTSUB_LEFT:	// ��
				if (CInput::GetJoyCrossTrigger(0, JOYCROSS_LEFT))
				{
					CSound::Play(SE_2);

					// �F��ς���
					m_pArrowButton[i]->SetColor(XMFLOAT4(1.0f, 0.8f, 0.8f, 1.0f));
					// �傫��������������
					m_pArrowButton[i]->SetSize(XMFLOAT2(60.0f, 60.0f));

					// �F��߂�
					m_pArrowButton[i]->SetColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

					//�A�C�R���̈ʒu�����炷
					int CenterIcon = CEnemyManger::GetCenterIcon();
					if (-30.0f <= m_pEnemyIcon[0]->GetPos().x
						&& m_pEnemyIcon[0]->GetPos().x <= 30.0f)
					{	// �A�C�R������Ԓ[�����Ȃ甽�Α��ɍs��
						m_pEnemyIcon[0]->SetTPos(XMFLOAT2(0.0f - m_pEnemyIcon[MAX_SUB_ENEMY_ICON - 2]->GetPos().x, -285.0f));
						CenterIcon += MAX_ENEMY - 2;
					}
					else
					{
						m_pEnemyIcon[0]->SetTPos(XMFLOAT2(m_pEnemyIcon[0]->GetTPos().x + 130.0f, -285.0f));
						CenterIcon -= 1;
					}
					CEnemyManger::SetCenterIcon((EEnemy)CenterIcon);
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
				if (CInput::GetMouseButton(MOUSEBUTTON_L))
				{	// �傫��������������
					m_pArrowButton[i]->SetSize(XMFLOAT2(60.0f, 60.0f));
				}
				if (CInput::GetMouseRelease(MOUSEBUTTON_L))
				{
					CSound::Play(SE_2);

					//�A�C�R���̈ʒu�����炷
					int CenterIcon = CEnemyManger::GetCenterIcon();
					switch (m_pArrowButton[i]->GetSubID())
					{
					case GOTSUB_RIGHT:
						if (-30.0f <= m_pEnemyIcon[MAX_SUB_ENEMY_ICON - 2]->GetPos().x
							&& m_pEnemyIcon[MAX_SUB_ENEMY_ICON - 2]->GetPos().x <= 30.0f)
						{	// �A�C�R������Ԓ[�����Ȃ甽�Α��ɍs��
							m_pEnemyIcon[0]->SetTPos(XMFLOAT2(0.0f, -285.0f));
							CenterIcon -= MAX_ENEMY - 2;
						}
						else
						{
							m_pEnemyIcon[0]->SetTPos(XMFLOAT2(m_pEnemyIcon[0]->GetTPos().x - 130.0f, -285.0f));
							CenterIcon += 1;
						}
						break;

					case GOTSUB_LEFT:
						if (-30.0f <= m_pEnemyIcon[0]->GetPos().x
							&& m_pEnemyIcon[0]->GetPos().x <= 30.0f)
						{	// �A�C�R������Ԓ[�����Ȃ甽�Α��ɍs��
							m_pEnemyIcon[0]->SetTPos(XMFLOAT2(0.0f - m_pEnemyIcon[MAX_SUB_ENEMY_ICON - 2]->GetPos().x, -285.0f));
							CenterIcon += MAX_ENEMY - 2;
						}
						else
						{
							m_pEnemyIcon[0]->SetTPos(XMFLOAT2(m_pEnemyIcon[0]->GetTPos().x + 130.0f, -285.0f));
							CenterIcon -= 1;
						}
						break;

					default:
						break;
					}
					CEnemyManger::SetCenterIcon((EEnemy)CenterIcon);
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
	// �ʒu
	m_pEnemyIcon[0]->SetSpeed((m_pEnemyIcon[0]->GetTPos().x - m_pEnemyIcon[0]->GetPos().x) / 5.0f);
	m_pEnemyIcon[1]->SetPos(XMFLOAT2(m_pEnemyIcon[0]->GetPos().x + 130.0f, -285.0f));
	// �g�k
	for (int i = 0; i < _countof(m_pEnemyIcon); ++i)
	{
		// ���S�̃A�C�R���͑傫��
		if (-30.0f <= m_pEnemyIcon[i]->GetPos().x && m_pEnemyIcon[i]->GetPos().x <= 30.0f) 
		{ m_pEnemyIcon[i]->SetSize(XMFLOAT2(130.0f, 130.0f)); }
		else { m_pEnemyIcon[i]->SetSize(XMFLOAT2(70.0f, 70.0f)); }
	}
}