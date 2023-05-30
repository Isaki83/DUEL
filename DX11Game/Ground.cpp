//=============================================================================
//
// �n�� [Ground.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "Ground.h"


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CGround::CGround(CScene* pScene) : CModel(pScene)
{
	m_id = GOT_GROUND;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CGround::Init()
{
	HRESULT hr = CModel::Init();

	SetCenter(XMFLOAT3(0.0f, 0.0f, 0.0f));
	SetBBox(XMFLOAT3(9960.0f / 2.0f, 845.0f / 2.0f, 9960.0f / 2.0f));

	return hr;
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CGround::Update()
{
	// �S�̂̃��[���h �}�g���b�N�X�X�V
	CGameObj::Update();
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CGround::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	CLight* pLight = CLight::Get();
	pLight->SetDisable();	// ���C�e�B���O����

	CAssimpModel* pModel = CModel::GetAssimp(MODEL_GROUND);
	pModel->Draw(pDC, GetWorld(), eOpacityOnly);

	pLight->SetEnable();	// ���C�e�B���O�L��
}
void CGround::DrawAlpha()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	CLight* pLight = CLight::Get();
	pLight->SetDisable();	// ���C�e�B���O����

	CAssimpModel* pModel = CModel::GetAssimp(MODEL_GROUND);
	pModel->Draw(pDC, GetWorld(), eTransparentOnly);

	pLight->SetEnable();	// ���C�e�B���O�L��
}
