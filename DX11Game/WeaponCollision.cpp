/*������������������������������������������������������������������������������

	����(�����蔻��) [WeaponCollision.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#include "Weapon.h"
#include "EnemyManger.h"
#include "HPGaugeEnemy.h"
#include "Golem.h"
#include "SwordMan.h"
#include "Damage.h"
#include "Particle.h"
#include "Scene.h"
#include "Sound.h"


/*������������������������������������������������������������������������������

	�G�Ƃ̓����蔻��

������������������������������������������������������������������������������*/
void CWeapon::GolemCollision(int weapon)
{
	// �p�[�c�̐����i�[
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
			// �_���[�W�������o���ʒu�̒���
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
					
					// �_���[�W(����̍U���� * �G�̕��ʂ��Ƃ̃_���[�W�{��)
					float damage = GetPower() * pObj->GetParts(i).DmgRatio;

					// �̗͂����炷
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
					// �Q�[�W�����炷
					m_pHPGaugeEnemy->SetDamage(damage);
					// �_���[�W�\�L
					CDamage::Create(m_pScene, fW, damage);
					// �p�[�e�B�N���ݒ�
					for (int j = 0; j < MAX_PARTICLE; j++)
					{ CParticle::Creat(m_pScene, fW, 60, XMINT3(10, 10, 10), XMFLOAT3(0.0f, -0.9f, 0.0f)); }
					// ��x����������A�������ĂȂ���ԂɂȂ�܂Ŕ��������
					pObj->SetPartsHitDefence(i, true);
				}
			}
			else { pObj->SetPartsHitDefence(i, false); }
		}
	}
}