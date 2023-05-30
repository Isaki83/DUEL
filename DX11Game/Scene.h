//=============================================================================
//
// シーン [Scene.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "main.h"


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 列挙型
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
enum EScene {
	SCENE_NONE = 0,			// (シーン無)
	SCENE_TITLE,			// タイトル画面
	SCENE_HOME,				// ホーム画面
	SCENE_WEAPON_SELECT,	// 武器選択画面
	SCENE_ENEMY_SELECT,		// 敵選択画面
	SCENE_BATTLE_GOLEM,		// バトル画面(ゴーレム)
	SCENE_BATTLE_SM,		// バトル画面(ソーダ―)

	MAX_SCENE
};


class CGameObj;
class C2DObj;
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// シーン 継承元クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
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
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
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

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 3Dオブジェクト識別用
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CGameObj* GetObj() { return m_pObj; }
	void SetObj(CGameObj* pObj) { m_pObj = pObj; }
	CGameObj* Find(int id, CGameObj* pStart = nullptr);

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 2Dオブジェクト識別用
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	C2DObj* Get2DObj() { return m_p2DObj; }
	void Set2DObj(C2DObj* pObj) { m_p2DObj = pObj; }
	C2DObj* Find2DObj(int id, C2DObj* pStart = nullptr);
};
