#include "Polygon.h"
#include "Shader.h"
#include <dwrite.h> // DirectWritepÌwb_[t@C
#include <d3d11.h>
//#include <d3dx11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <string>
#include <fstream>
#include <vector>
#include <wchar.h>
#include <atlbase.h>
#include <atlconv.h>


//
// \¢Ìè`
//
// VF[_Én·l
struct SHADER_GLOBAL 
{
	XMMATRIX	mWorld;		// [hÏ·sñ(]usñ)
	XMMATRIX	mView;		// r[Ï·sñ(]usñ)
	XMMATRIX	mProj;		// ËeÏ·sñ(]usñ)
	XMMATRIX	mTex;		// eNX`Ï·sñ(]usñ)
};


//
// ÃIoÏ
//
ID3D11ShaderResourceView*	CPolygon::m_pTexture;				// eNX`ÖÌ|C^

VERTEX_2D					CPolygon::m_vertexWk[NUM_VERTEX];	// ¸_îñi[[N

XMFLOAT3					CPolygon::m_vPos;					// |SÌÚ®Ê
XMFLOAT3					CPolygon::m_vAngle;					// |SÌñ]Ê
XMFLOAT3					CPolygon::m_vScale;					// |SÌTCY
XMFLOAT4					CPolygon::m_vColor;					// |SÌ¸_J[
bool						CPolygon::m_bInvalidate;			// ¸_f[^XVtO

XMFLOAT2					CPolygon::m_vPosTexFrame;			// UVÀW
XMFLOAT2					CPolygon::m_vSizeTexFrame;			// eNX`oTCY

ID3D11Buffer*				CPolygon::m_pConstantBuffer;		// èobt@
ID3D11Buffer*				CPolygon::m_pVertexBuffer;			// ¸_obt@
ID3D11SamplerState*			CPolygon::m_pSamplerState;			// eNX` Tv
ID3D11VertexShader*			CPolygon::m_pVertexShader;			// ¸_VF[_
ID3D11InputLayout*			CPolygon::m_pInputLayout;			// ¸_tH[}bg
ID3D11PixelShader*			CPolygon::m_pPixelShader;			// sNZVF[_

XMFLOAT4X4					CPolygon::m_mProj;					// ËeÏ·sñ
XMFLOAT4X4					CPolygon::m_mView;					// r[Ï·sñ
XMFLOAT4X4					CPolygon::m_mWorld;					// [hÏ·sñ
XMFLOAT4X4					CPolygon::m_mTex;					// eNX`Ï·sñ


/*

	ú»

*/
HRESULT CPolygon::Init(ID3D11Device* pDevice)
{
	HRESULT hr = S_OK;

	// VF[_ú»
	static const D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,                            D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	hr = LoadShader("Vertex2D", "Pixel2D", &m_pVertexShader, &m_pInputLayout, &m_pPixelShader, layout, _countof(layout));
	if (FAILED(hr)) { return hr; }

	// èobt@¶¬
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SHADER_GLOBAL);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = pDevice->CreateBuffer(&bd, nullptr, &m_pConstantBuffer);
	if (FAILED(hr)) { return hr; }

	// eNX` Tv¶¬
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	hr = pDevice->CreateSamplerState(&sd, &m_pSamplerState);
	if (FAILED(hr)) { return hr; }

	// Ï·sñú»
	XMStoreFloat4x4(&m_mWorld, XMMatrixIdentity());
	XMStoreFloat4x4(&m_mView, XMMatrixLookAtLH(XMVectorSet(0.0f, 0.0f, -10.0f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)));
	XMStoreFloat4x4(&m_mProj, XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f, 100.0f));
	XMStoreFloat4x4(&m_mTex, XMMatrixIdentity());
	m_mTex._44 = 0.0f;

	m_vPos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_vAngle = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_vScale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_vColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_bInvalidate = false;

	m_vPosTexFrame = XMFLOAT2(0.0f, 0.0f);
	m_vSizeTexFrame = XMFLOAT2(1.0f, 1.0f);

	// ¸_îñÌì¬
	hr = MakeVertex(pDevice);

	return hr;
}


/*

	I¹

*/
void CPolygon::Fin(void)
{
	// eNX` TvÌJú
	SAFE_RELEASE(m_pSamplerState);
	// ¸_obt@Ìðú
	SAFE_RELEASE(m_pVertexBuffer);
	// èobt@Ìðú
	SAFE_RELEASE(m_pConstantBuffer);
	// sNZVF[_ðú
	SAFE_RELEASE(m_pPixelShader);
	// ¸_tH[}bgðú
	SAFE_RELEASE(m_pInputLayout);
	// ¸_VF[_ðú
	SAFE_RELEASE(m_pVertexShader);
}


/*

	`æ

*/
void CPolygon::Draw(ID3D11DeviceContext* pDeviceContext)
{
	// gk
	XMMATRIX mWorld = XMMatrixScaling(m_vScale.x, m_vScale.y, m_vScale.z);
	// ñ]
	mWorld *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_vAngle.x), XMConvertToRadians(m_vAngle.y), XMConvertToRadians(m_vAngle.z));
	// Ú®
	mWorld *= XMMatrixTranslation(m_vPos.x, m_vPos.y, m_vPos.z);
	// [h }gbNXÉÝè
	XMStoreFloat4x4(&m_mWorld, mWorld);

	if (m_pTexture) 
	{
		// gk
		mWorld = XMMatrixScaling(m_vSizeTexFrame.x, m_vSizeTexFrame.y, 1.0f);
		// Ú®
		mWorld *= XMMatrixTranslation(m_vPosTexFrame.x, m_vPosTexFrame.y, 0.0f);
		// eNX` }gbNXÉÝè
		XMStoreFloat4x4(&m_mTex, mWorld);
	}
	else 
	{
		// eNX`³µ
		m_mTex._44 = 0.0f;
	}

	// ¸_obt@XV
	SetVertex();

	pDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0);
	pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);
	pDeviceContext->IASetInputLayout(m_pInputLayout);

	UINT stride = sizeof(VERTEX_2D);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	pDeviceContext->PSSetSamplers(0, 1, &m_pSamplerState);
	pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	SHADER_GLOBAL cb;
	cb.mProj = XMMatrixTranspose(XMLoadFloat4x4(&m_mProj));
	cb.mView = XMMatrixTranspose(XMLoadFloat4x4(&m_mView));
	cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&m_mWorld));
	cb.mTex = XMMatrixTranspose(XMLoadFloat4x4(&m_mTex));
	pDeviceContext->UpdateSubresource(m_pConstantBuffer, 0, nullptr, &cb, 0, 0);
	pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	// v~eBu`óðZbg
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// |SÌ`æ
	pDeviceContext->Draw(NUM_VERTEX, 0);
}


/*

	¸_Ìì¬

*/
HRESULT CPolygon::MakeVertex(ID3D11Device* pDevice)
{
	// ¸_ÀWÌÝè
	m_vertexWk[0].vtx = XMFLOAT3(-0.5f, 0.5f, 0.0f);
	m_vertexWk[1].vtx = XMFLOAT3(0.5f, 0.5f, 0.0f);
	m_vertexWk[2].vtx = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	m_vertexWk[3].vtx = XMFLOAT3(0.5f, -0.5f, 0.0f);

	// gU½ËõÌÝè
	m_vertexWk[0].diffuse = m_vColor;
	m_vertexWk[1].diffuse = m_vColor;
	m_vertexWk[2].diffuse = m_vColor;
	m_vertexWk[3].diffuse = m_vColor;

	// eNX`ÀWÌÝè
	m_vertexWk[0].tex = XMFLOAT2(0.0f, 0.0f);
	m_vertexWk[1].tex = XMFLOAT2(1.0f, 0.0f);
	m_vertexWk[2].tex = XMFLOAT2(0.0f, 1.0f);
	m_vertexWk[3].tex = XMFLOAT2(1.0f, 1.0f);

	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = sizeof(m_vertexWk);
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = &m_vertexWk[0];

	HRESULT hr = pDevice->CreateBuffer(&vbd, &initData, &m_pVertexBuffer);

	return hr;
}


/*

	¸_ÀWÌÝè

*/
void CPolygon::SetVertex(void)
{
	if (m_bInvalidate) 
	{
		//¸_obt@Ìgðßé
		ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
		HRESULT hr = S_OK;

		// ¸_f[^ÌÍÍðbNµA¸_obt@ÖÌ|C^ðæ¾
		D3D11_MAPPED_SUBRESOURCE msr;
		hr = pDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		if (SUCCEEDED(hr)) 
		{
			// gU½ËõÌÝè
			m_vertexWk[0].diffuse = m_vColor;
			m_vertexWk[1].diffuse = m_vColor;
			m_vertexWk[2].diffuse = m_vColor;
			m_vertexWk[3].diffuse = m_vColor;
			// ¸_f[^ðã«
			memcpy_s(msr.pData, sizeof(m_vertexWk), m_vertexWk, sizeof(m_vertexWk));
			// ¸_f[^ðAbN·é
			pDeviceContext->Unmap(m_pVertexBuffer, 0);
			// tOðNA
			m_bInvalidate = false;
		}
	}
}


/*

	eNX`ÌÝè

*/
void CPolygon::SetTexture(ID3D11ShaderResourceView* pTexture)
{
	m_pTexture = pTexture;
	m_mTex._44 = (m_pTexture) ? 1.0f : 0.0f;
}


/*

	\¦ÀWÌÝè

*/
void CPolygon::SetPos(float fX, float fY)
{
	m_vPos.x = fX;
	m_vPos.y = fY;
}


/*

	\¦TCYÌÝè

*/
void CPolygon::SetSize(float fScaleX, float fScaleY)
{
	m_vScale.x = fScaleX;
	m_vScale.y = fScaleY;
}


/*

	\¦pxÌÝè(PÊ:x)

*/
void CPolygon::SetAngle(float fAngle)
{
	m_vAngle.z = fAngle;
}


/*

	¶ãeNX`ÀWÌÝè (0.0fU1.0, 0.0fV1.0)

*/
void CPolygon::SetUV(float fU, float fV)
{
	m_vPosTexFrame.x = fU;
	m_vPosTexFrame.y = fV;
}


/*

	eNX`t[TCYÌÝè (0.0fWidth1.0, 0.0fHeight1.0)

*/
void CPolygon::SetFrameSize(float fWidth, float fHeight)
{
	m_vSizeTexFrame.x = fWidth;
	m_vSizeTexFrame.y = fHeight;
}


/*

	¸_J[ÌÝè

*/
void CPolygon::SetColor(float fRed, float fGreen, float fBlue)
{
	SetColor(XMFLOAT3(fRed, fGreen, fBlue));
}
void CPolygon::SetColor(XMFLOAT3 vColor)
{
	if (vColor.x != m_vColor.x || vColor.y != m_vColor.y || vColor.z != m_vColor.z)
	{
		m_vColor.x = vColor.x;
		m_vColor.y = vColor.y;
		m_vColor.z = vColor.z;
		m_bInvalidate = true;
	}
}


/*

	s§¾xÌÝè

*/
void CPolygon::SetAlpha(float fAlpha)
{
	if (fAlpha != m_vColor.w) 
	{
		m_vColor.w = fAlpha;
		m_bInvalidate = true;
	}
}


/*

	¸_J[ÌÝè

*/
void CPolygon::SetColor(float fRed, float fGreen, float fBlue, float fAlpha)
{
	SetColor(XMFLOAT4(fRed, fGreen, fBlue, fAlpha));
}
void CPolygon::SetColor(XMFLOAT4 vColor)
{
	if (vColor.x != m_vColor.x || vColor.y != m_vColor.y || vColor.z != m_vColor.z || vColor.w != m_vColor.w) 
	{
		m_vColor = vColor;
		m_bInvalidate = true;
	}
}