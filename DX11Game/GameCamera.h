//=============================================================================
//
// �Q�[�� �J���� [GameCamera.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Camera.h"
#include "GameObj.h"

//����������������������������������������
// �Q�[���J���� �N���X
//����������������������������������������
class CGameCamera : public CCamera
{
private:
	CGameObj* m_pPlayer;	// ���@
	float m_fRadius;		// ���@���a
	int m_nMode;			// �J�������[�h
	float m_fAngle;			// �J�����A���O��

	int m_iLookMe;			// ���_�؂�ւ��p

public:
	CGameCamera();

	void Init();
	void Update();

	// ���@�ݒ�
	void SetPlayer(CGameObj* pPlayer) { m_pPlayer = pPlayer; }
};
