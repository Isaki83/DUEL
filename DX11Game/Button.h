//=============================================================================
//
// �{�^�� [Button.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "main.h"
#include "2DObj.h"

//����������������������������������������
// �{�^�� �p�����N���X
//����������������������������������������
class CButton : public C2DObj
{
protected:
	//����������������������������������������
	// ��{
	//����������������������������������������
	int			m_iID;					// ID
	bool		m_bIsNowSelect;			// �I�𒆂�
	XMFLOAT2	m_fNowSelectPos;		// �I�𒆂������o�[�̈ʒu
	XMFLOAT2	m_fNowSelectSize;		// �I�𒆂������o�[�̑傫��
	float		m_fNowSelectMaxSize;	// �I�𒆂������o�[�̑傫���W�i����j

public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CButton(CScene* pScene);
	virtual HRESULT Init();
	virtual void Update();
	virtual void Draw();

	//����������������������������������������
	// ���̑�
	//����������������������������������������
	int GetID() { return m_iID; }
	void SetID(int id) { m_iID = id; }
	void NowSelectScaleUp();
	void NowSelectScaleDown();
};