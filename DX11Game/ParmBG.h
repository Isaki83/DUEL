//=============================================================================
//
// �I�����
// �p�����[�^�[�w�i [ParmBG.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "main.h"
#include "2DObj.h"

//����������������������������������������
// �X�e�[�^�X�p�̔w�i �N���X
//����������������������������������������
class CParmBG : public C2DObj
{
public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CParmBG(CScene* pScene);
	HRESULT Init();
	void Draw();
};