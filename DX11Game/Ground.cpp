//=============================================================================
//
// 地面 [Ground.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "Ground.h"


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コンストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CGround::CGround(CScene* pScene) : CModel(pScene)
{
	m_id = GOT_GROUND;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT CGround::Init()
{
	HRESULT hr = CModel::Init();

	SetCenter(XMFLOAT3(0.0f, 0.0f, 0.0f));
	SetBBox(XMFLOAT3(9960.0f / 2.0f, 845.0f / 2.0f, 9960.0f / 2.0f));

	return hr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CGround::Update()
{
	// 全体のワールド マトリックス更新
	CGameObj::Update();
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	描画

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CGround::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	CLight* pLight = CLight::Get();
	pLight->SetDisable();	// ライティング無効

	CAssimpModel* pModel = CModel::GetAssimp(MODEL_GROUND);
	pModel->Draw(pDC, GetWorld(), eOpacityOnly);

	pLight->SetEnable();	// ライティング有効
}
void CGround::DrawAlpha()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	CLight* pLight = CLight::Get();
	pLight->SetDisable();	// ライティング無効

	CAssimpModel* pModel = CModel::GetAssimp(MODEL_GROUND);
	pModel->Draw(pDC, GetWorld(), eTransparentOnly);

	pLight->SetEnable();	// ライティング有効
}
