//=============================================================================
//
// 割れた地面 [BreakGround.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Model.h"

class CPlayer;
class CHPGaugePlayer;
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ゴーレムの攻撃エフェクト クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CBreakGround : public CModel
{
private:
	bool once;				// 一回だけ
	int cnttemp;			// 汎用カウント
	int terget;				// 消滅までの時間

	CPlayer* m_pPlayer;					// プレイヤー
	CHPGaugePlayer* m_pHPGaugePlayer;	// HPゲージ(プレイヤー)

public:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CBreakGround(CScene* pScene);
	HRESULT Init();
	void Fin();
	void Update();

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 生成
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	static CBreakGround* Creat(CScene* pScene, XMFLOAT4X4& mtxWorld);
};
