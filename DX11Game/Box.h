//=============================================================================
//
// ’¼•û‘Ì [Box.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Mesh.h"

//
// ’¼•û‘Ì ƒNƒ‰ƒX
//
class CBox : public CMesh
{
public:
	//
	// Šî–{
	//
	CBox();
	virtual ~CBox();
	HRESULT Init(XMFLOAT3 vBBox);
};
