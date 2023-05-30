/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	武器(当たり判定) [WeaponCollision.cpp]
	Author : ISAKI SUGIURA

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
#include "Weapon.h"
#include "EnemyManger.h"
#include "HPGaugeEnemy.h"
#include "Golem.h"
#include "SwordMan.h"
#include "Damage.h"
#include "Particle.h"
#include "Scene.h"
#include "Sound.h"


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	敵との当たり判定

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CWeapon::GolemCollision(int weapon)
{
	// パーツの数を格納
	int MaxParts;
	switch (CEnemyManger::GetEnemy())
	{
	case ENEMY_GOLEM:
		MaxParts = MAX_GOLEM_PARTS;
		break;
	case ENEMY_SWORDMAN:
		MaxParts = MAX_SM_PARTS;
		break;
	default:
		MaxParts = 0;
		break;
	}

	CGameObj* pNext;
	for (CGameObj* pObj = m_pScene->GetObj(); pObj; pObj = pNext)
	{
		pNext = pObj->GetNext();
		if (pObj->GetID() != GOT_ENEMY) { continue; }
		for (int i = 0; i < MaxParts; i++)
		{
			// ダメージ数字を出す位置の調整
			XMMATRIX mW;
			mW = XMMatrixMultiply(XMLoadFloat4x4(&pObj->GetParts(i).matrix),
				XMMatrixTranslation(pObj->GetParts(i).center.x,
					pObj->GetParts(i).center.y,
					pObj->GetParts(i).center.z));
			XMFLOAT4X4 fW;
			XMStoreFloat4x4(&fW, mW);

			if (CollisionOBB(pObj, GetWorld(), GetCenter(), GetBBox(), false, i))
			{
				if (!pObj->GetParts(i).hitDefence)
				{
					CSound::Play(SE_3);
					
					// ダメージ(武器の攻撃力 * 敵の部位ごとのダメージ倍率)
					float damage = GetPower() * pObj->GetParts(i).DmgRatio;

					// 体力を減らす
					switch (CEnemyManger::GetEnemy())
					{
					case ENEMY_GOLEM:
						m_pGolem->LifeDmg(damage);
						break;
					case ENEMY_SWORDMAN:
						m_pSwordMan->LifeDmg(damage);
						break;
					default:
						break;
					}
					// ゲージを減らす
					m_pHPGaugeEnemy->SetDamage(damage);
					// ダメージ表記
					CDamage::Create(m_pScene, fW, damage);
					// パーティクル設定
					for (int j = 0; j < MAX_PARTICLE; j++)
					{ CParticle::Creat(m_pScene, fW, 60, XMINT3(10, 10, 10), XMFLOAT3(0.0f, -0.9f, 0.0f)); }
					// 一度当たったら、当たってない状態になるまで判定を消す
					pObj->SetPartsHitDefence(i, true);
				}
			}
			else { pObj->SetPartsHitDefence(i, false); }
		}
	}
}