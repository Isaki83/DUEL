//=============================================================================
//
// HP�Q�[�W [HPGauge.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "main.h"
#include "2DObj.h"

//����������������������������������������
// HP�Q�[�W �p�����N���X
//����������������������������������������
class CHPGauge : public C2DObj
{
protected:
	//����������������������������������������
	// ��{
	//����������������������������������������
	XMFLOAT2 m_fDmgGaugePos;		// �ԃQ�[�W �ʒu
	XMFLOAT2 m_fDmgGaugeSize;		// �ԃQ�[�W �傫��
	XMFLOAT2 m_fGaugePos;			// �΃Q�[�W �ʒu
	XMFLOAT2 m_fGaugeSize;			// �΃Q�[�W �傫��

	//����������������������������������������
	// ���̑�
	//����������������������������������������
	float	m_fLife;
	float	m_fDamage;

public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CHPGauge(CScene* pScene);
	virtual HRESULT Init();
	virtual void Update();
	virtual void Draw();

	//����������������������������������������
	// ���̑�
	//����������������������������������������
	void SetLife(int life) { m_fLife = m_fSize.x / life; }
	void SetDamage(float dmg);
};
