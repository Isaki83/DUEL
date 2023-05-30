//=============================================================================
//
// モデル [Model.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "Model.h"
#include "Scene.h"


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// グローバル変数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
namespace 
{
	// 3Dモデル ファイル名
	LPCSTR g_pszModelPath[MAX_MODEL] = {
		/*-----------------------------------------
			スカイドーム
		-----------------------------------------*/
		// 青空
		"data/model/SkyDome/SkyDome.fbx",

		/*-----------------------------------------
			地形
		-----------------------------------------*/
		// 地面
		"data/model/Ground/Ground.fbx",
		// 割れた地面
		"data/model/BreakGround/BreakGround.fbx",

		/*-----------------------------------------
			武器	
		-----------------------------------------*/
		// 木剣
		"data/model/Weapon/WoodSword/WoodSword.fbx",
		// 斧
		"data/model/Weapon/Axe/Axe.fbx",
		// 大剣
		"data/model/Weapon/LargeSword/LargeSword.fbx",
		// 黒剣
		"data/model/Weapon/BlackSword/BlackSword.fbx",

		/*-----------------------------------------
			キャラクター(階層構造)
		-----------------------------------------*/
		"data/model/Loot/Loot.fbx",					// ルート
		// メインキャラクター(自機)
		"data/model/MainCharacter/MC_Body.fbx",		// 胴
		"data/model/MainCharacter/MC_Arm.fbx",		// 腕
		"data/model/MainCharacter/MC_Hand.fbx",		// 手
		// ゴーレム(敵)
		"data/model/Enemy/Golem/Golem_Hip.fbx",		// 腰
		"data/model/Enemy/Golem/Golem_Body.fbx",	// 胴
		"data/model/Enemy/Golem/Golem_Head.fbx",	// 頭
		"data/model/Enemy/Golem/Golem_ArmUp.fbx",	// 腕-上
		"data/model/Enemy/Golem/Golem_ArmDown.fbx",	// 腕-下
		"data/model/Enemy/Golem/Golem_LegUp.fbx",	// 足-上
		"data/model/Enemy/Golem/Golem_LegDown.fbx",	// 足-下
		// SwordMan(敵)
		"data/model/Enemy/SwordMan/SM_Hip.fbx",		// 腰
		"data/model/Enemy/SwordMan/SM_Body.fbx",	// 胴
		"data/model/Enemy/SwordMan/SM_Head.fbx",	// 頭
		"data/model/Enemy/SwordMan/SM_Arm.fbx",		// 腕
		"data/model/Enemy/SwordMan/SM_Hand.fbx",	// 手
		"data/model/Enemy/SwordMan/SM_Leg.fbx",		// 足

		/*-----------------------------------------
			パーティクル
		-----------------------------------------*/
		"data/model/Particle/Particle.fbx",
	};
}


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 静的メンバ変数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CAssimpModel* CModel::m_pModels[MAX_MODEL] = { nullptr };


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コンストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CModel::CModel(CScene* pScene) : CGameObj(pScene)
{
	m_pModel = nullptr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	デストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CModel::~CModel()
{
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	全モデル読込

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT CModel::LoadAll()
{
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// Assimp用シェーダ初期化
	if (!CAssimpModel::InitShader(pDevice)) { return E_FAIL; }

	// 全モデル読込
	HRESULT hr = S_OK;
	for (int i = 0; i < MAX_MODEL; ++i) 
	{
		SAFE_DELETE(m_pModels[i]);
		m_pModels[i] = new CAssimpModel();
		if (!m_pModels[i]->Load(pDevice, pDC, g_pszModelPath[i])) 
		{
			hr = E_FAIL;
			break;
		}
	}
	return hr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	全モデル解放

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CModel::ReleaseAll()
{
	// 全モデル解放
	for (int i = 0; i < MAX_MODEL; ++i) 
	{
		if (m_pModels[i]) 
		{
			m_pModels[i]->Release();
			delete m_pModels[i];
			m_pModels[i] = nullptr;
		}
	}

	// Assimp用シェーダ終了処理
	CAssimpModel::UninitShader();
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT CModel::Init()
{
	HRESULT hr = CGameObj::Init();
	if (FAILED(hr)) { return hr; }

	return hr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	終了

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CModel::Fin()
{
	CGameObj::Fin();
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CModel::Update()
{
	CGameObj::Update();
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	描画

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CModel::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	if (m_pModel) { m_pModel->Draw(pDC, GetWorld(), eOpacityOnly); }
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	半透明部分描画

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CModel::DrawAlpha()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	if (m_pModel) { m_pModel->Draw(pDC, GetWorld(), eTransparentOnly); }

	CGameObj::DrawAlpha();
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	モデル設定

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CModel::SetModel(EModel model)
{
	if (model < 0 || model >= MAX_MODEL) 
	{
		m_pModel = nullptr;
		SetRadius(0.5f);
		SetBBox(XMFLOAT3(0.5f, 0.5f, 0.5f));
		SetCenter(XMFLOAT3(0, 0, 0));
	} 
	else 
	{
		m_pModel = m_pModels[model];
		SetRadius(m_pModel->GetRadius());
		SetBBox(m_pModel->GetBBox());
		SetCenter(m_pModel->GetCenter());
	}
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	Assimpモデル取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CAssimpModel* CModel::GetAssimp(EModel model)
{
	if (model < 0 || model >= MAX_MODEL) { return nullptr; }
	return m_pModels[model];
}
