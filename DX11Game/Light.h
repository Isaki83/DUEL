//=============================================================================
//
// 光源 [Light.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "main.h"

class CLight
{
private:
	XMFLOAT4 m_diffuse;
	XMFLOAT4 m_ambient;
	XMFLOAT4 m_specular;
	XMFLOAT3 m_direction;
	XMFLOAT4 m_RimColor;
	bool m_bEnable;			// ライティング有効/無効

	static CLight* m_pLight;

public:
	CLight();

	void Init();
	XMFLOAT4& GetDiffuse() { return m_diffuse; }
	XMFLOAT4& GetAmbient() { return m_ambient; }
	XMFLOAT4& GetSpecular() { return m_specular; }
	XMFLOAT4& GetRimColor() { return m_RimColor; }
	XMFLOAT3& GetDir();
	void SetEnable(bool bEnable = true) { m_bEnable = bEnable; }
	void SetDisable(bool bDisable = true) { m_bEnable = !bDisable; }
	void SetRimColor(XMFLOAT4 rim) { m_RimColor = rim; }
	void SetRimColorReset(XMFLOAT4 rim = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)) { m_RimColor = rim; }

	static CLight* Get();
	static void Set(CLight* pLight = nullptr);
};
