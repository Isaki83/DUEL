//=============================================================================
//
// �\�[�_�\ [SwordMan.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Enemy.h"
#include "SwordManAnim.h"


//����������������������������������������
// �񋓌^
//����������������������������������������
// --- ��� ---
// MOVE �̏��
enum ESM_State_Move {
	SM_BIG_MOVE_BACK,	// ��ړ�(���)
	SM_BIG_MOVE_SIDE,	// ��ړ�(���E)
	SM_RUN_MOVE,		// �����ċߕt��

	MAX_SM_STATE_MOVE
};
// ATTACK �̏��
enum ESM_State_Attack {
	SM_ATTACK_NONE,	// ��

	SM_ATTACK_00,	// ���̏��2�A��
	SM_ATTACK_01,	// ��������}�ڋ߂���2�A��
	SM_ATTACK_02,	// �����Ă�����x�ߕt���Ă���A�˂���Ԃŋ}�ڋ߂��ĉ񂵎a��
	SM_ATTACK_03,	// �n�ʂɌ����w���čL�͈͂ɍU��

	MAX_SM_STATE_ATTACK
};


//����������������������������������������
// �\�[�_�\ �N���X
//����������������������������������������
class CSwordMan : public CEnemy
{
private:
	//����������������������������������������
	// �A�j���[�V�����֘A
	//����������������������������������������
	CSwordManAnimSet	m_AnimSet;			// �A�j���[�V���� �f�[�^ �Z�b�g

	//����������������������������������������
	// �p�j�p
	//����������������������������������������
	ESM_State_Move		SM_MoveState;
	ESM_State_Attack	SM_AttackState;

public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CSwordMan(CScene* pScene);
	HRESULT Init();
	void Update();

	//����������������������������������������
	// �p�j�p
	//����������������������������������������
	void StateIdle();
	void StateMove(XMFLOAT3 vX, XMFLOAT3 vZ);
	void StateAttack01();
	void StateAttack02(XMFLOAT3 vZ);
	void StateAttack03();
	void StateDead();
};