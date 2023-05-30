//=======================================================================================
//
// �t�F�[�h �C��/�A�E�g [Fade.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "Fade.h"
#include "Polygon.h"
#include "Sound.h"

//����������������������������������������
// �ÓI�����o�ϐ�
//����������������������������������������
EFade CFade::m_fade = FADE_NONE;
EScene CFade::m_sceneNext = SCENE_TITLE;
XMFLOAT4 CFade::m_vColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
float CFade::m_fRate = 1.0f / (60.0f * 0.5f);


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
void CFade::Init()
{
	m_vColor.w = 1.0f;			// �s�����x
	m_fade = FADE_IN;			// ���
	m_sceneNext = SCENE_TITLE;	// ���̃V�[��
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CFade::Update()
{
	switch (m_fade)
	{
#pragma region �������Ă��Ȃ�
	case FADE_NONE:
		break;
#pragma endregion
#pragma region �t�F�[�h�A�E�g����
	case FADE_OUT:
		// // �s�����x���グ��
		m_vColor.w += m_fRate;
		if (m_vColor.w >= 1.0f)
		{
			// �t�F�C�h�C���Ɉړ�
			m_vColor.w = 1.0f;
			m_fade = FADE_IN;
			// �V�[���ؑ�
			CScene::Change(m_sceneNext);
		}
		// �����t�F�[�h�A�E�g
		CSound::SetVolume(1.0f - m_vColor.w);
		break;
#pragma endregion
#pragma region �t�F�[�h�C������
	case FADE_IN:
		// �s�����x��������
		m_vColor.w -= m_fRate;
		if (m_vColor.w <= 0.0f)
		{
			// �t�F�[�h�����I��
			m_vColor.w = 0.0f;
			m_fade = FADE_NONE;
		}
		// �����t�F�[�h�C��
		CSound::SetVolume(1.0f - m_vColor.w);
		break;
#pragma endregion
	}
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CFade::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	CPolygon::SetColor(m_vColor);
	CPolygon::SetTexture(nullptr);
	CPolygon::SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetPos(0.0f, 0.0f);
	CPolygon::Draw(pDC);

	CPolygon::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}


/*������������������������������������������������������������������������������

	�t�F�[�h�A�E�g�J�n

������������������������������������������������������������������������������*/
void CFade::Out(EScene scene, float fSecond)
{
	if (m_fade != FADE_OUT) 
	{
		m_fade = FADE_OUT;
		m_sceneNext = scene;
		m_fRate = 1.0f / (60.0f * fSecond);
	}
}


/*������������������������������������������������������������������������������

	�t�F�[�h�C�� �A�E�g �J���[�ݒ�

������������������������������������������������������������������������������*/
void CFade::SetColor(XMFLOAT3 vColor)
{
	m_vColor.x = vColor.x;
	m_vColor.y = vColor.y;
	m_vColor.z = vColor.z;
}
