//=============================================================================
//
// ���f�� [Model.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "Model.h"
#include "Scene.h"


//����������������������������������������
// �O���[�o���ϐ�
//����������������������������������������
namespace 
{
	// 3D���f�� �t�@�C����
	LPCSTR g_pszModelPath[MAX_MODEL] = {
		/*-----------------------------------------
			�X�J�C�h�[��
		-----------------------------------------*/
		// ��
		"data/model/SkyDome/SkyDome.fbx",

		/*-----------------------------------------
			�n�`
		-----------------------------------------*/
		// �n��
		"data/model/Ground/Ground.fbx",
		// ���ꂽ�n��
		"data/model/BreakGround/BreakGround.fbx",

		/*-----------------------------------------
			����	
		-----------------------------------------*/
		// �،�
		"data/model/Weapon/WoodSword/WoodSword.fbx",
		// ��
		"data/model/Weapon/Axe/Axe.fbx",
		// �匕
		"data/model/Weapon/LargeSword/LargeSword.fbx",
		// ����
		"data/model/Weapon/BlackSword/BlackSword.fbx",

		/*-----------------------------------------
			�L�����N�^�[(�K�w�\��)
		-----------------------------------------*/
		"data/model/Loot/Loot.fbx",					// ���[�g
		// ���C���L�����N�^�[(���@)
		"data/model/MainCharacter/MC_Body.fbx",		// ��
		"data/model/MainCharacter/MC_Arm.fbx",		// �r
		"data/model/MainCharacter/MC_Hand.fbx",		// ��
		// �S�[����(�G)
		"data/model/Enemy/Golem/Golem_Hip.fbx",		// ��
		"data/model/Enemy/Golem/Golem_Body.fbx",	// ��
		"data/model/Enemy/Golem/Golem_Head.fbx",	// ��
		"data/model/Enemy/Golem/Golem_ArmUp.fbx",	// �r-��
		"data/model/Enemy/Golem/Golem_ArmDown.fbx",	// �r-��
		"data/model/Enemy/Golem/Golem_LegUp.fbx",	// ��-��
		"data/model/Enemy/Golem/Golem_LegDown.fbx",	// ��-��
		// SwordMan(�G)
		"data/model/Enemy/SwordMan/SM_Hip.fbx",		// ��
		"data/model/Enemy/SwordMan/SM_Body.fbx",	// ��
		"data/model/Enemy/SwordMan/SM_Head.fbx",	// ��
		"data/model/Enemy/SwordMan/SM_Arm.fbx",		// �r
		"data/model/Enemy/SwordMan/SM_Hand.fbx",	// ��
		"data/model/Enemy/SwordMan/SM_Leg.fbx",		// ��

		/*-----------------------------------------
			�p�[�e�B�N��
		-----------------------------------------*/
		"data/model/Particle/Particle.fbx",
	};
}


//����������������������������������������
// �ÓI�����o�ϐ�
//����������������������������������������
CAssimpModel* CModel::m_pModels[MAX_MODEL] = { nullptr };


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CModel::CModel(CScene* pScene) : CGameObj(pScene)
{
	m_pModel = nullptr;
}


/*������������������������������������������������������������������������������

	�f�X�g���N�^

������������������������������������������������������������������������������*/
CModel::~CModel()
{
}


/*������������������������������������������������������������������������������

	�S���f���Ǎ�

������������������������������������������������������������������������������*/
HRESULT CModel::LoadAll()
{
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// Assimp�p�V�F�[�_������
	if (!CAssimpModel::InitShader(pDevice)) { return E_FAIL; }

	// �S���f���Ǎ�
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


/*������������������������������������������������������������������������������

	�S���f�����

������������������������������������������������������������������������������*/
void CModel::ReleaseAll()
{
	// �S���f�����
	for (int i = 0; i < MAX_MODEL; ++i) 
	{
		if (m_pModels[i]) 
		{
			m_pModels[i]->Release();
			delete m_pModels[i];
			m_pModels[i] = nullptr;
		}
	}

	// Assimp�p�V�F�[�_�I������
	CAssimpModel::UninitShader();
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
HRESULT CModel::Init()
{
	HRESULT hr = CGameObj::Init();
	if (FAILED(hr)) { return hr; }

	return hr;
}


/*������������������������������������������������������������������������������

	�I��

������������������������������������������������������������������������������*/
void CModel::Fin()
{
	CGameObj::Fin();
}


/*������������������������������������������������������������������������������

	�X�V

������������������������������������������������������������������������������*/
void CModel::Update()
{
	CGameObj::Update();
}


/*������������������������������������������������������������������������������

	�`��

������������������������������������������������������������������������������*/
void CModel::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	if (m_pModel) { m_pModel->Draw(pDC, GetWorld(), eOpacityOnly); }
}


/*������������������������������������������������������������������������������

	�����������`��

������������������������������������������������������������������������������*/
void CModel::DrawAlpha()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	if (m_pModel) { m_pModel->Draw(pDC, GetWorld(), eTransparentOnly); }

	CGameObj::DrawAlpha();
}


/*������������������������������������������������������������������������������

	���f���ݒ�

������������������������������������������������������������������������������*/
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


/*������������������������������������������������������������������������������

	Assimp���f���擾

������������������������������������������������������������������������������*/
CAssimpModel* CModel::GetAssimp(EModel model)
{
	if (model < 0 || model >= MAX_MODEL) { return nullptr; }
	return m_pModels[model];
}
