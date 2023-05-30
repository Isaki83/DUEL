//=============================================================================
//
// �X�^�[�g�{�^�� [StartButton.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "main.h"
#include "Button.h"

//����������������������������������������
//�u�J�n�v�{�^�� �N���X
//����������������������������������������
class CStartButton : public CButton
{
private:
	//����������������������������������������
	// ��{
	//����������������������������������������
	float	m_fBGPos;			// �{�^���̔w�i�̈ʒu

	//����������������������������������������
	// ���̑�
	//����������������������������������������
	int		m_iTime;
	float	m_fAdd;

public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CStartButton(CScene* pScene);
	HRESULT Init();
	void Update();
	void Draw();
};
