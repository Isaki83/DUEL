//=============================================================================
//
// HPQ[W(G) [HPGaugeEnemy.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "HPGauge.h"

//
// GĚHPQ[W NX
//
class CHPGaugeEnemy : public CHPGauge
{
public:
	//
	// î{
	//
	CHPGaugeEnemy(CScene* pScene);
	HRESULT Init();
	void Draw();
};