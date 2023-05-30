//=============================================================================
//
// oA [Barrier.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "main.h"
#include "2DObj.h"

//
// oA NX
//
class CBarrier : public C2DObj
{
private:
	//
	// »ΜΌ
	//
	int		m_iTime;	// DeleteάΕΜΤ

public:
	//
	// ξ{
	//
	CBarrier(CScene* pScene);
	HRESULT Init();
	void Update();
	void Draw();

	//
	// Ά¬
	//
	static CBarrier* Create(CScene* pScene, int time);
};
