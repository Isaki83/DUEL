//=============================================================================
//
// ����{�^�� [WeaponButton.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "main.h"
#include "Button.h"

//����������������������������������������
//�u����v�{�^�� �N���X
//����������������������������������������
class CWeaponButton : public CButton
{
public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CWeaponButton(CScene* pScene);
	HRESULT Init();
	void Draw();
};
