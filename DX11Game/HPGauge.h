//=============================================================================
//
// HPQ[W [HPGauge.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "main.h"
#include "2DObj.h"

//
// HPQ[W p³³NX
//
class CHPGauge : public C2DObj
{
protected:
	//
	// î{
	//
	XMFLOAT2 m_fDmgGaugePos;		// ÔQ[W Êu
	XMFLOAT2 m_fDmgGaugeSize;		// ÔQ[W å«³
	XMFLOAT2 m_fGaugePos;			// ÎQ[W Êu
	XMFLOAT2 m_fGaugeSize;			// ÎQ[W å«³

	//
	// »Ì¼
	//
	float	m_fLife;
	float	m_fDamage;

public:
	//
	// î{
	//
	CHPGauge(CScene* pScene);
	virtual HRESULT Init();
	virtual void Update();
	virtual void Draw();

	//
	// »Ì¼
	//
	void SetLife(int life) { m_fLife = m_fSize.x / life; }
	void SetDamage(float dmg);
};
