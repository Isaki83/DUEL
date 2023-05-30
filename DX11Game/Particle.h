//=============================================================================
//
// パーティクル [Particle.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Model.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// マクロ定義
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#define MAX_PARTICLE	(5)


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーティクル クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CParticle : public CModel
{
private:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 構造体定義
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	struct TParticle
	{
		XMFLOAT3	Pos;		// 座標
		XMFLOAT3	Power;		// 力
		XMFLOAT3	MinusPower;	// pPowerを弱めていく力
		int			DeleteTime;	// 消えるまでの時間
	};

	TParticle	m_particle;
	int			AddTime;

public:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CParticle(CScene* pScene);

	HRESULT Init();
	void Fin();
	void Update();
	void Draw();
	void DrawAlpha();

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 生成
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	static CParticle* Creat(CScene* pScene, XMFLOAT4X4& matrix, int time, XMINT3 power, XMFLOAT3 mpower);
};