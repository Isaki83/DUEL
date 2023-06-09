//=============================================================================
//
// J [Camera.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "Camera.h"
#include "AssimpModel.h"

//*****************************************************************************
// O[oΟ
//*****************************************************************************
namespace 
{
	const float CAM_POS_P_X = 0.0f;					// JΜ_ϊΚu(XΐW)
	const float CAM_POS_P_Y = 30.0f;				// JΜ_ϊΚu(YΐW)
	const float CAM_POS_P_Z = -150.0f;				// JΜ_ϊΚu(ZΐW)
	const float CAM_POS_R_X = 0.0f;					// JΜ_ϊΚu(XΐW)
	const float CAM_POS_R_Y = 0.0f;					// JΜ_ϊΚu(YΐW)
	const float CAM_POS_R_Z = 0.0f;					// JΜ_ϊΚu(ZΐW)
	const float VIEW_ANGLE = 70.0f;					// μp
	const float VIEW_ASPECT = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;	// AXyNgδ
	const float VIEW_NEAR_Z = 1.0f;					// NearZl
	const float VIEW_FAR_Z = 10000.0f;				// FarZl

	CCamera g_camera;								// J CX^X
}

//
// ΓIoΟ
//
CCamera* CCamera::m_pCamera = &g_camera;			// »έΜJ


/*

	RXgN^

*/
CCamera::CCamera()
{
	Init();
}


/*

	ϊ»

*/
void CCamera::Init()
{
	m_pSky = nullptr;

	m_vPos = XMFLOAT3(CAM_POS_P_X, CAM_POS_P_Y, CAM_POS_P_Z);		// _
	m_vTarget = XMFLOAT3(CAM_POS_R_X, CAM_POS_R_Y, CAM_POS_R_Z);	// _
	m_vUp = XMFLOAT3(0.0f, 1.0f, 0.0f);		// γϋxNg

	m_fAspectRatio = VIEW_ASPECT;			// c‘δ
	m_fFovY = VIEW_ANGLE;					// μp(Degree)
	m_fNearZ = VIEW_NEAR_Z;					// OϋNbv£
	m_fFarZ = VIEW_FAR_Z;					// γϋNbv£

	m_vAngle = XMFLOAT3(0.0f, 0.0f, 0.0f);
	float fVecX, fVecZ;
	fVecX = m_vPos.x - m_vTarget.x;
	fVecZ = m_vPos.z - m_vTarget.z;
	m_fLengthInterval = sqrtf(fVecX * fVecX + fVecZ * fVecZ);

	m_fShakeAmount = 1.0f;

	CalcWorldMatrix();
}


/*

	XV

*/
void CCamera::Update()
{
	// }gbNXXV
	UpdateMatrix();
}


/*

	ζΚNA

*/
void CCamera::Clear()
{
	// main.cppΜ\[XQΖ
	extern ID3D11RenderTargetView* g_pRenderTargetView;
	extern ID3D11DepthStencilView* g_pDepthStencilView;

	float ClearColor[4] = { 0.117647f, 0.254902f, 0.352941f, 1.0f };
	ID3D11DeviceContext* pDC = GetDeviceContext();
	pDC->ClearRenderTargetView(g_pRenderTargetView, ClearColor);
	pDC->ClearDepthStencilView(g_pDepthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	if (m_pSky) 
	{
		SetZBuffer(false);		// Zobt@³ψ
		CLight* pLight = CLight::Get();
		pLight->SetDisable();	// CeBO³ψ
		XMFLOAT4X4 mW;
		XMStoreFloat4x4(&mW, XMMatrixTranslation(m_vPos.x, m_vPos.y, m_vPos.z));
		m_pSky->Draw(pDC, mW);
		pLight->SetEnable();	// CeBOLψ
	}

	SetZBuffer(true);
	SetBlendState(BS_NONE);
}


/*

	r[/vWFNV }gbNXXV

*/
void CCamera::UpdateMatrix()
{
	XMStoreFloat4x4(&m_mtxView, XMMatrixLookAtLH(XMLoadFloat3(&m_vPos), XMLoadFloat3(&m_vTarget), XMLoadFloat3(&m_vUp)));
	XMStoreFloat4x4(&m_mtxProj, XMMatrixPerspectiveFovLH(XMConvertToRadians(m_fFovY), m_fAspectRatio, m_fNearZ, m_fFarZ));
}


/*

	[h }gbNXέθ

*/
void CCamera::SetWorldMatrix(XMFLOAT4X4& mtxWorld)
{
	m_mtxWorld = mtxWorld;
	m_vPos = XMFLOAT3(mtxWorld._41, mtxWorld._42, mtxWorld._43);
	m_vTarget = XMFLOAT3(mtxWorld._41 + mtxWorld._31, mtxWorld._42 + mtxWorld._32, mtxWorld._43 + mtxWorld._33);
	m_vUp = XMFLOAT3(mtxWorld._21, mtxWorld._22, mtxWorld._23);
}


/*

	_/_/γϋxNg©η[h }gbNXZo

*/
XMFLOAT4X4& CCamera::CalcWorldMatrix()
{
	XMVECTOR vecZ = XMVectorSet(m_vTarget.x - m_vPos.x, m_vTarget.y - m_vPos.y, m_vTarget.z - m_vPos.z, 0.0f);
	XMFLOAT3 vZ;
	XMStoreFloat3(&vZ, XMVector3Normalize(vecZ));
	XMVECTOR vecY = XMLoadFloat3(&m_vUp);
	XMVECTOR vecX = XMVector3Normalize(XMVector3Cross(vecY, vecZ));
	XMFLOAT3 vX;
	XMStoreFloat3(&vX, vecX);
	vecY = XMVector3Normalize(XMVector3Cross(vecZ, vecX));
	XMFLOAT3 vY;
	XMStoreFloat3(&vY, vecY);

	m_mtxWorld._11 = vX.x;
	m_mtxWorld._12 = vX.y;
	m_mtxWorld._13 = vX.z;
	m_mtxWorld._14 = 0.0f;
	m_mtxWorld._21 = vY.x;
	m_mtxWorld._22 = vY.y;
	m_mtxWorld._23 = vY.z;
	m_mtxWorld._24 = 0.0f;
	m_mtxWorld._31 = vZ.x;
	m_mtxWorld._32 = vZ.y;
	m_mtxWorld._33 = vZ.z;
	m_mtxWorld._34 = 0.0f;
	m_mtxWorld._41 = m_vPos.x;
	m_mtxWorld._42 = m_vPos.y;
	m_mtxWorld._43 = m_vPos.z;
	m_mtxWorld._44 = 1.0f;

	return m_mtxWorld;
}


/*

	J CX^Xέθ

*/
void CCamera::Set(CCamera* pCamera)
{
	m_pCamera = (pCamera) ? pCamera : &g_camera;
}
