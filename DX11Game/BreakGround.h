//=============================================================================
//
// ê½nÊ [BreakGround.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Model.h"

class CPlayer;
class CHPGaugePlayer;
//
// S[ÌUGtFNg NX
//
class CBreakGround : public CModel
{
private:
	bool once;				// êñ¾¯
	int cnttemp;			// ÄpJEg
	int terget;				// ÁÅÜÅÌÔ

	CPlayer* m_pPlayer;					// vC[
	CHPGaugePlayer* m_pHPGaugePlayer;	// HPQ[W(vC[)

public:
	//
	// î{
	//
	CBreakGround(CScene* pScene);
	HRESULT Init();
	void Fin();
	void Update();

	//
	// ¶¬
	//
	static CBreakGround* Creat(CScene* pScene, XMFLOAT4X4& mtxWorld);
};
