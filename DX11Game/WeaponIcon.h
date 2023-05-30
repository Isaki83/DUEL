//=============================================================================
//
// ����A�C�R�� [IWeaponcon.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "main.h"
#include "2DObj.h"

//����������������������������������������
// ����A�C�R�� �N���X
//����������������������������������������
class CWeaponIcon : public C2DObj
{
private:
	int			m_iTex;			// �e�N�X�`���\�ԍ�
	XMFLOAT2	m_fTruePos;		// �{���̈ʒu
	float		m_fSpeed;		// �X�s�[�h

public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CWeaponIcon(CScene* pScene);
	HRESULT Init();
	void Update();
	void Draw();

	//����������������������������������������
	//  �e�N�X�`��
	//����������������������������������������
	void SetTexture(int tex) { m_iTex = tex; }

	//����������������������������������������
	// ���̑�
	//����������������������������������������
	void SetSpeed(float speed) { m_fSpeed = speed; }
	void SetTPos(XMFLOAT2 fPos) { m_fTruePos = fPos; }
	XMFLOAT2& GetTPos() { return m_fTruePos; }
};
