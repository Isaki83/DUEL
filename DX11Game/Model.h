//=============================================================================
//
// モデル [Model.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "GameObj.h"
#include "AssimpModel.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 列挙型
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
enum EModel 
{
	/*-----------------------------------------
		スカイドーム
	-----------------------------------------*/
	// 青空
	MODEL_SKY = 0,

	/*-----------------------------------------
		地形
	-----------------------------------------*/
	// 地面
	MODEL_GROUND,
	// 割れた地面
	MODEL_BREAK_GROUND,

	/*-----------------------------------------
		武器
	-----------------------------------------*/
	// 木剣
	MODEL_WOOD_SWORD,
	// 斧
	MODEL_AXE,
	// 大剣
	MODEL_LARGE_SWORD,
	// 黒剣
	MODEL_BLACK_SWORD,

	/*-----------------------------------------
		キャラクター(階層構造)
	-----------------------------------------*/
	MODEL_LOOT,				// ルート
	// メインキャラクター(自機)
	MODEL_MC_BODY,			// 胴
	MODEL_MC_ARM,			// 腕
	MODEL_MC_HAND,			// 手
	// ゴーレム(敵)
	MODEL_GOLEM_HIP,		// 腰
	MODEL_GOLEM_BODY,		// 胴
	MODEL_GOLEM_HEAD,		// 頭
	MODEL_GOLEM_ARM_UP,		// 腕-上
	MODEL_GOLEM_ARM_DOWN,	// 腕-下
	MODEL_GOLEM_LEG_UP,		// 足-上
	MODEL_GOLEM_LEG_DOWN,	// 足-下
	// SwordMan(敵)
	MODEL_SM_HIP,		// 腰
	MODEL_SM_BODY,		// 胴
	MODEL_SM_HEAD,		// 頭
	MODEL_SM_ARM,		// 腕
	MODEL_SM_HAND,		// 手
	MODEL_SM_LEG,		// 足
	
	/*-----------------------------------------
		パーティクル
	-----------------------------------------*/
	MODEL_PARTICLE,

	MAX_MODEL
};

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// モデル クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
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
