//=============================================================================
//
// パーティクル [Particle.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "Particle.h"
#include "DebugProc.h"


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コンストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CParticle::CParticle(CScene* pScene) : CModel(pScene)
{
	m_id = GOT_PARTICLE;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT CParticle::Init()
{
	HRESULT hr = CModel::Init();

	SetModel(MODEL_PARTICLE);

	m_particle.Pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_particle.Power = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_particle.MinusPower = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_particle.DeleteTime = 0;

	AddTime = 0;

	return hr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	終了処理

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CParticle::Fin()
{
	CModel::Fin();
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	更新処理

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CParticle::Update()
{
	m_particle.Power.x += m_particle.MinusPower.x;
	m_particle.Power.y += m_particle.MinusPower.y;
	m_particle.Power.z += m_particle.MinusPower.z;

	m_particle.Pos.x += m_particle.Power.x;
	m_particle.Pos.y += m_particle.Power.y;
	m_particle.Pos.z += m_particle.Power.z;

	m_vPos = m_particle.Pos;

	// 消去
	AddTime++;
	if (m_particle.DeleteTime < AddTime)
	{
		Fin();
		delete this;
	}

	// 全体のワールド マトリックス更新
	CGameObj::Update();

#if 0
	CDebugProc::Print("*** ﾊﾟｰﾃｨｸﾙ ***\n");
	CDebugProc::Print("[pos : %f, %f, %f]\n", m_vPos.x, m_vPos.y, m_vPos.z);
#endif
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	描画

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CParticle::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	CLight* pLight = CLight::Get();
	pLight->SetDisable();	// ライティング無効

	CAssimpModel* pModel = CModel::GetAssimp(MODEL_PARTICLE);
	pModel->Draw(pDC, GetWorld(), eOpacityOnly);

	pLight->SetEnable();	// ライティング有効
}
void CParticle::DrawAlpha()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	CLight* pLight = CLight::Get();
	pLight->SetDisable();	// ライティング無効

	CAssimpModel* pModel = CModel::GetAssimp(MODEL_PARTICLE);
	pModel->Draw(pDC, GetWorld(), eTransparentOnly);

	pLight->SetEnable();	// ライティング有効
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	生成

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CParticle* CParticle::Creat(CScene* pScene, XMFLOAT4X4& matrix, int time, XMINT3 power, XMFLOAT3 mpower)
{
	CParticle* pParticle = new CParticle(pScene);
	pParticle->Init();

	pParticle->m_particle.Pos = XMFLOAT3(matrix._41, matrix._42, matrix._43);
	pParticle->m_particle.Power = XMFLOAT3((float)(rand() % power.x), (float)(rand() % power.y), (float)(rand() % power.z));
	pParticle->m_particle.MinusPower = XMFLOAT3(mpower.x, mpower.y, mpower.z);
	pParticle->m_particle.DeleteTime = time;

	return pParticle;
}