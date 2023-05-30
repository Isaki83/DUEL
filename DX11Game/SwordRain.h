//=============================================================================
//
// 剣の雨 [SwordRain.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Model.h"

class CPlayer;
class CHPGaugePlayer;
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ソーダ―の攻撃3エフェクト クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CSwordRain : public CModel
{
private:
	CAssimpModel*	m_pModel;
	XMFLOAT4		m_fRimColor;
	float			m_fAcssel;		// 加速度
	bool			hit;			// 一回あったたら判定を消す
	int				cnttemp;		// 汎用カウント
	int				terget;			// 消滅までの時間

	CPlayer* m_pPlayer;					// プレイヤー
	CHPGaugePlayer* m_pHPGaugePlayer;	// HPゲージ(プレイヤー)

public:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CSwordRain(CScene* pScene);
	HRESULT Init();
	void Fin();
	void Update();
	void Draw();
	void DrawAlpha();

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 生成
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	static CSwordRain* Creat(CScene* pScene, XMFLOAT4X4& mtxWorld);
};
