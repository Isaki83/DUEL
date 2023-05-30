//=============================================================================
//
// 剣の雨 [SwordRain.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "SwordRain.h"
#include "Player.h"
#include "HPGaugePlayer.h"
#include "Scene.h"
#include "DebugProc.h"

#define MAX_SPEED	(100)


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コンストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CSwordRain::CSwordRain(CScene* pScene) : CModel(pScene)
{
	m_id = GOT_SWORD_RAIN;

	m_pModel = nullptr;

	m_pPlayer = nullptr;
	m_pHPGaugePlayer = nullptr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
HRESULT CSwordRain::Init()
{
	HRESULT hr = CModel::Init();

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 変数初期化
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	m_pModel = CModel::GetAssimp(MODEL_BLACK_SWORD);
	SetCenter(m_pModel->GetCenter());
	SetBBox(XMFLOAT3(m_pModel->GetBBox().x * 3.0f, m_pModel->GetBBox().y, m_pModel->GetBBox().z * 3.0f));
	m_fRimColor = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	m_fAcssel = 1.5f;
	hit = true;
	cnttemp = 0;
	terget = 60;

	m_pPlayer = (CPlayer*)m_pScene->Find(GOT_PLAYER);
	m_pHPGaugePlayer = (CHPGaugePlayer*)m_pScene->Find2DObj(GOT_HP_GAUGE_PLAYER);

	return hr;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	終了処理

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CSwordRain::Fin()
{
	CModel::Fin();
}

/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CSwordRain::Update()
{
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// モデル全体のローカル座標軸取得
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// Y軸
	XMFLOAT3 vY(m_mWorld._21, m_mWorld._22, m_mWorld._23);

	
	CGameObj* pNext;
	for (CGameObj* pObj = m_pScene->GetObj(); pObj; pObj = pNext)
	{
		pNext = pObj->GetNext();
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		// 地面との当たり判定
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		if (pObj->GetID() == GOT_GROUND)
		{
			// 当たっていない
			if (!CollisionOBB(pObj, GetWorld(), GetCenter(), GetBBox()))
			{
				m_fAcssel = pow(m_fAcssel, 1.5);
				if (MAX_SPEED < m_fAcssel) { m_fAcssel = MAX_SPEED; }
				//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
				// 剣が落ちる
				//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
				m_vPos.x -= vY.x * m_fAcssel;
				m_vPos.y -= vY.y * m_fAcssel;
				m_vPos.z -= vY.z * m_fAcssel;
			}
		}
		
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		// プレイヤーとの当たり判定
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		if (pObj->GetID() == GOT_PLAYER)
		{
			if (hit)
			{
				if (CollisionOBB(pObj, GetWorld(), GetCenter(), GetBBox()))
				{
					m_pPlayer->LifeDmg(200);
					m_pHPGaugePlayer->SetDamage(200);
					hit = false;
				}
			}
		}
	}

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 時間がたったら消滅
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	cnttemp++;
	if (cnttemp > terget)
	{
		Fin();
		delete this;
	}

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 全体のワールド マトリックス更新
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	CGameObj::Update();

#if 0
	CDebugProc::Print("*** SwordRain ***\n");
	CDebugProc::Print("[pos   : %f, %f, %f]\n", m_vPos.x, m_vPos.y, m_vPos.z);
	CDebugProc::Print("[angle : %f, %f, %f]\n", m_vAngle.x, m_vAngle.y, m_vAngle.z);
#endif
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	描画

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CSwordRain::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	CLight* pLight = CLight::Get();
	pLight->SetDisable();	// ライティング無効
	pLight->SetRimColor(m_fRimColor);	// リムライトの色設定

	if (m_pModel) { m_pModel->Draw(pDC, GetWorld(), eOpacityOnly, 1); }

	pLight->SetRimColorReset();	// リムライトの色を戻す
	pLight->SetEnable();	// ライティング有効
}
void CSwordRain::DrawAlpha()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	CLight* pLight = CLight::Get();
	pLight->SetDisable();	// ライティング無効
	pLight->SetRimColor(m_fRimColor);	// リムライトの色設定

	if (m_pModel) { m_pModel->Draw(pDC, GetWorld(), eTransparentOnly, 1); }

	pLight->SetRimColorReset();	// リムライトの色を戻す
	pLight->SetEnable();	// ライティング有効
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	生成

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CSwordRain* CSwordRain::Creat(CScene* pScene, XMFLOAT4X4& mtxWorld)
{
	CSwordRain* pSwordRain = new CSwordRain(pScene);
	pSwordRain->Init();
	// 座標(敵の少し上にXZ+-800でランダム)
	pSwordRain->SetPos(XMFLOAT3(
		mtxWorld._41 + (rand() % 1600 - 800),
		mtxWorld._42 + 1000.0f,
		mtxWorld._43 + (rand() % 1600 - 800)));
	// 角度(YZランダム)
	pSwordRain->SetAngle(XMFLOAT3(
		0.0f, 
		(float)(rand() % 180),
		(float)(rand() % 60 - 30)));

	return pSwordRain;
}