/*������������������������������������������������������������������������������

	�v���C���[ [Player.h]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#pragma once
#include "Model.h"
#include "Parts.h"
#include "PlayerAnim.h"

class CGround;
class CWeapon;
class CGolem;
class CSwordMan;
//����������������������������������������
// �v���C���[ �N���X
//����������������������������������������
class CPlayer : public CModel
{
private:
	//����������������������������������������
	// �A�j���[�V�����֘A
	//����������������������������������������
	CPlayerAnimSet	m_animSet;				// �A�j���[�V���� �f�[�^ �Z�b�g
	bool			m_bIsAttack;			// �U������
	bool			m_iAnimFin;				// �A�j���[�V�������ŏI�t���[�����ǂ���

	//����������������������������������������
	// �W�����v�֘A
	//����������������������������������������
	XMFLOAT3	m_fJumpStartPos;	// �W�����v�J�n���̍��W
	float		m_fJumpTime;		// �W�����v�J�n���Ă���̌o�ߎ���
	bool		m_bJumpFlag;		// �W�����v���ėǂ���

	//����������������������������������������
	// �����蔻��
	//����������������������������������������
	int			m_iSide;			// AABB�œ������Ă����

	//����������������������������������������
	// ���̑�
	//����������������������������������������
	int			m_iLife;			// �̗�
	bool		m_bMoveFlag;		// �ړ����Ă��邩
	bool		m_bTargetEnemy;		// �G�̕�����������
	bool		m_bInvicibleFlag;	// ���G�t���O
	bool		m_bAvoidFlag;		// ����t���O
	int			m_iAvoidDir;		// ������
	int			m_iAvoidTimeCnt;	// ������ԃJ�E���g
	float		m_fSpeedScale;		// �X�s�[�h�{��
	bool		m_bSceneChengeFlag;	// �V�[���`�F���W���邩

	CGround*	m_pGround;			// �n��
	CWeapon*	m_pWeapon;			// ����
	CGolem*		m_pGolem;			// �S�[����
	CSwordMan*	m_pSwordMan;		// �\�[�_�\

public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CPlayer(CScene* pScene);
	HRESULT Init();
	void Update();
	void Draw();
	void DrawAlpha();

	//����������������������������������������
	// �A�j���[�V�����֘A
	//����������������������������������������
	int GetAnimNo() { return m_animSet.Get(); }
	int GetAnimCount() { return m_animSet.GetCount(); }

	//����������������������������������������
	// ����
	//����������������������������������������
	void Move(XMFLOAT3 xyz, const char dir, float speed);	// �ړ�
	void WallJump();										// �ǂɓ���������W�����v

	//����������������������������������������
	// ���̑�
	//����������������������������������������
	bool GetAvoidFlag() { return m_bAvoidFlag; }
	void SetSceneChengeFlag(bool falg = true) { m_bSceneChengeFlag = falg; }
	bool GetSceneChengeFlag() { return m_bSceneChengeFlag; }

	void LifeDmg(int dmg) { m_iLife -= dmg; }
	int GetMaxLife();

private:
	//����������������������������������������
	// ���f���֘A
	//����������������������������������������
	void CalcMatrix();				// �p�x����}�g���b�N�X���v�Z(�S�p�[�c��)

	//����������������������������������������
	// �����蔻��
	//����������������������������������������
	void GroundCollision();			// �n��
};
