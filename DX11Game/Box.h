//=============================================================================
//
// ������ [Box.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Mesh.h"

//����������������������������������������
// ������ �N���X
//����������������������������������������
class CBox : public CMesh
{
public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CBox();
	virtual ~CBox();
	HRESULT Init(XMFLOAT3 vBBox);
};
