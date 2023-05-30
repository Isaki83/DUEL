//=============================================================================
//
// 武器アイコン [IWeaponcon.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "main.h"
#include "2DObj.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 武器アイコン クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CWeaponIcon : public C2DObj
{
private:
	int			m_iTex;			// テクスチャ―番号
	XMFLOAT2	m_fTruePos;		// 本当の位置
	float		m_fSpeed;		// スピード

public:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CWeaponIcon(CScene* pScene);
	HRESULT Init();
	void Update();
	void Draw();

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	//  テクスチャ
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	void SetTexture(int tex) { m_iTex = tex; }

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// その他
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	void SetSpeed(float speed) { m_fSpeed = speed; }
	void SetTPos(XMFLOAT2 fPos) { m_fTruePos = fPos; }
	XMFLOAT2& GetTPos() { return m_fTruePos; }
};
