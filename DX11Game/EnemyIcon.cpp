/*������������������������������������������������������������������������������

	�G�A�C�R�� [EnemyIcon.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#include "EnemyIcon.h"
#include "Polygon.h"
#include "EnemyManger.h"
#include "Fade.h"


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CEnemyIcon::CEnemyIcon(CScene* pScene) : C2DObj(pScene)
{
	m_id = GOT_ICON;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CEnemyIcon::Init()
{
	HRESULT hr = C2DObj::Init();
	if (FAILED(hr)) { return hr; }

	//����������������������������������������
	// �ϐ�������
	//����������������������������������������
	m_fPos = XMFLOAT2(-350.0f, -250.0f);
	m_fSize = XMFLOAT2(70.0f, 70.0f);
	m_fColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	m_fTruePos = m_fPos;
	m_fSpeed = 0.0f;

	return hr;
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CEnemyIcon::Update()
{
	switch (CFade::GetScene())
	{
	// �G�I�����
	case SCENE_ENEMY_SELECT:
		// �A�C�R�����S�[����(���W�̎��ɂ��Ă���A�C�R��)�Ȃ�
		if (GetSubID() == GOTSUB_GOLEM)
		{
			// �ڕW�̍��W�܂ŏ����������
			if (m_fPos.x != m_fTruePos.x) { m_fPos.x += m_fSpeed; }
			else { m_fTruePos = m_fPos; }
		}

		// �I�𒆂Ȃ�Ԃ��t���[����������悤�ɂ���
		if (CEnemyManger::GetEnemy() == GetSubID()) { SetColorA(1.0f); }
		else { SetColorA(0.0f); }

		break;

	default:
		break;
	}
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CEnemyIcon::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	//����������������������������������������
	// �A�C�R��
	//����������������������������������������
	switch (CFade::GetScene())
	{
	// �G�I�����
	case SCENE_ENEMY_SELECT:
		CPolygon::SetTexture(m_pTexture[m_iTex]);
		CPolygon::SetFrameSize(1.0f, 1.0f);
		CPolygon::SetSize(m_fSize.x, m_fSize.y);
		CPolygon::SetColor(XMFLOAT4(m_fColor.x, m_fColor.y, m_fColor.z, 1.0f));
		CPolygon::SetPos(m_fPos.x, m_fPos.y);
		CPolygon::SetUV(0.0f, 0.0f);
		CPolygon::Draw(pDC);

		CPolygon::SetTexture(m_pTexture[TEX_ICON_FRAME]);
		CPolygon::SetFrameSize(1.0f, 1.0f);
		CPolygon::SetSize(m_fSize.x, m_fSize.y);
		CPolygon::SetColor(XMFLOAT4(1.0f, 0.0f, 0.0f, m_fColor.w));
		CPolygon::SetPos(m_fPos.x, m_fPos.y);
		CPolygon::SetUV(0.0f, 0.0f);
		CPolygon::Draw(pDC);
		break;

	// �o�g�����
	case SCENE_BATTLE_GOLEM:
	case SCENE_BATTLE_SM:
		switch (CEnemyManger::GetEnemy())
		{
		case ENEMY_NONE:
			break;
		case ENEMY_GOLEM:
			CPolygon::SetTexture(m_pTexture[TEX_ICON_GOLEM]);
			break;
		case ENEMY_SWORDMAN:
			CPolygon::SetTexture(m_pTexture[TEX_ICON_SM]);
			break;
		}
		CPolygon::SetFrameSize(1.0f, 1.0f);
		CPolygon::SetSize(m_fSize.x, m_fSize.y);
		CPolygon::SetColor(m_fColor);
		CPolygon::SetPos(m_fPos.x, m_fPos.y);
		CPolygon::SetUV(0.0f, 0.0f);
		CPolygon::Draw(pDC);
		break;
	}

	SetBlendState(BS_NONE);
	SetZBuffer(true);
}