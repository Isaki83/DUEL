//=============================================================================
//
// �����X�^�[�{�^�� [MonsterButton.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "main.h"
#include "Button.h"

//����������������������������������������
//�u�����X�^�[�v�{�^�� �N���X
//����������������������������������������
class CMonsterButton : public CButton
{
public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CMonsterButton(CScene* pScene);
	HRESULT Init();
	void Draw();
};