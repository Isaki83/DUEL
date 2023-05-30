//=============================================================================
//
// �V�[�� [Scene.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "main.h"


//����������������������������������������
// �񋓌^
//����������������������������������������
enum EScene {
	SCENE_NONE = 0,			// (�V�[����)
	SCENE_TITLE,			// �^�C�g�����
	SCENE_HOME,				// �z�[�����
	SCENE_WEAPON_SELECT,	// ����I�����
	SCENE_ENEMY_SELECT,		// �G�I�����
	SCENE_BATTLE_GOLEM,		// �o�g�����(�S�[����)
	SCENE_BATTLE_SM,		// �o�g�����(�\�[�_�\)

	MAX_SCENE
};


class CGameObj;
class C2DObj;
//����������������������������������������
// �V�[�� �p�����N���X
//����������������������������������������
class CScene 
{
protected:
	EScene m_id;
	CGameObj* m_pObj;
	C2DObj* m_p2DObj;

private:
	static CScene* m_pScene;
	static CScene* m_pTop;
	CScene* m_pBack;
	CScene* m_pNext;

public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CScene();
	virtual ~CScene();

	virtual bool Init();
	virtual void Fin();
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static bool InitAll();
	static void FinAll();
	static void UpdateAll();
	static void DrawAll();

	static void Change(EScene scene);
	static CScene* Get() { return m_pScene; }

	//����������������������������������������
	// 3D�I�u�W�F�N�g���ʗp
	//����������������������������������������
	CGameObj* GetObj() { return m_pObj; }
	void SetObj(CGameObj* pObj) { m_pObj = pObj; }
	CGameObj* Find(int id, CGameObj* pStart = nullptr);

	//����������������������������������������
	// 2D�I�u�W�F�N�g���ʗp
	//����������������������������������������
	C2DObj* Get2DObj() { return m_p2DObj; }
	void Set2DObj(C2DObj* pObj) { m_p2DObj = pObj; }
	C2DObj* Find2DObj(int id, C2DObj* pStart = nullptr);
};
