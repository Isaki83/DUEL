//=============================================================================
//
// ���f�� [Model.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "GameObj.h"
#include "AssimpModel.h"

//����������������������������������������
// �񋓌^
//����������������������������������������
enum EModel 
{
	/*-----------------------------------------
		�X�J�C�h�[��
	-----------------------------------------*/
	// ��
	MODEL_SKY = 0,

	/*-----------------------------------------
		�n�`
	-----------------------------------------*/
	// �n��
	MODEL_GROUND,
	// ���ꂽ�n��
	MODEL_BREAK_GROUND,

	/*-----------------------------------------
		����
	-----------------------------------------*/
	// �،�
	MODEL_WOOD_SWORD,
	// ��
	MODEL_AXE,
	// �匕
	MODEL_LARGE_SWORD,
	// ����
	MODEL_BLACK_SWORD,

	/*-----------------------------------------
		�L�����N�^�[(�K�w�\��)
	-----------------------------------------*/
	MODEL_LOOT,				// ���[�g
	// ���C���L�����N�^�[(���@)
	MODEL_MC_BODY,			// ��
	MODEL_MC_ARM,			// �r
	MODEL_MC_HAND,			// ��
	// �S�[����(�G)
	MODEL_GOLEM_HIP,		// ��
	MODEL_GOLEM_BODY,		// ��
	MODEL_GOLEM_HEAD,		// ��
	MODEL_GOLEM_ARM_UP,		// �r-��
	MODEL_GOLEM_ARM_DOWN,	// �r-��
	MODEL_GOLEM_LEG_UP,		// ��-��
	MODEL_GOLEM_LEG_DOWN,	// ��-��
	// SwordMan(�G)
	MODEL_SM_HIP,		// ��
	MODEL_SM_BODY,		// ��
	MODEL_SM_HEAD,		// ��
	MODEL_SM_ARM,		// �r
	MODEL_SM_HAND,		// ��
	MODEL_SM_LEG,		// ��
	
	/*-----------------------------------------
		�p�[�e�B�N��
	-----------------------------------------*/
	MODEL_PARTICLE,

	MAX_MODEL
};

//����������������������������������������
// ���f�� �N���X
//����������������������������������������
class CModel : public CGameObj
{
private:
	static CAssimpModel* m_pModels[MAX_MODEL];
	CAssimpModel* m_pModel;

public:
	CModel(CScene* pScene);
	virtual ~CModel();

	static HRESULT LoadAll();
	static void ReleaseAll();

	virtual HRESULT Init();
	virtual void Fin();
	virtual void Update();
	virtual void Draw();
	virtual void DrawAlpha();

	void SetModel(EModel model);
	static CAssimpModel* GetAssimp(EModel model);
};
