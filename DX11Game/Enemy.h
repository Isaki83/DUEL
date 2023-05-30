//=============================================================================
//
// �G [Enemy.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Model.h"
#include "Parts.h"

//����������������������������������������
// �񋓌^
//����������������������������������������
// --- ��� ---
// ��{�̏��
enum EEnemy_State {
	STATE_ENEMY_NONE,		// ��� ��

	STATE_ENEMY_IDLE,		// �ҋ@
	STATE_ENEMY_MOVE,		// �ړ�
	STATE_ENEMY_ROTATION,	// ��]
	STATE_ENEMY_ATTACK,		// �U��
	STATE_ENEMY_DEAD,		// ����

	MAX_ENEMY_STATE
};

class CGround;
class CPlayer;
class CHPGaugePlayer;
//����������������������������������������
// �G �p�����N���X
//����������������������������������������
class CEnemy : public CModel
{
protected:
	//����������������������������������������
	// �A�j���[�V�����֘A
	//����������������������������������������
	XMINT2				m_iAnimTime;			// �A�j���[�V����
												// .x : �ŏI�t���[�����ǂ��� 1 or 0
												// .y : ���t���[���ڂ�
	int					m_iAnimNum;				// ���̃A�j���[�V����
	bool				m_bNowAttack;			// �U�������ǂ���

	//����������������������������������������
	// �p�j�p
	//����������������������������������������
	EEnemy_State		BaseState;
	int					m_iStatus = 0;		// ��Ԃ̏��
	int					m_iDoTime;			// �s������
	int					m_iDirections;		// ����
	int					m_iWhatAttack;		// ���̍U�������邩
	float				m_fSpeedScale;		// �X�s�[�h�{��

	//����������������������������������������
	// �W�����v�֘A
	//����������������������������������������
	XMFLOAT3			m_fJumpStartPos;	// �W�����v�J�n���̍��W
	float				m_fJumpTime;		// �W�����v�J�n���Ă���̌o�ߎ���
	bool				m_bJumpFlag;		// �W�����v���ėǂ���

	//����������������������������������������
	// �����蔻��
	//����������������������������������������
	int					m_iSide;			// AABB�œ������Ă����

	//����������������������������������������
	// ���̑�
	//����������������������������������������
	float				m_fGravity;			// �d��
	float				m_fVelocity;		// �����x
	XMFLOAT3			m_fPrevPos;			// �O�̍��W
	XMFLOAT3			m_fPrevPlayerPos;	// �O�̃v���C���[�̍��W
	int					m_iMaxLife;			// �ő�̗�
	int					m_iLife;			// �̗�
	int					m_iTmp[5];			// �ėp
	bool				m_bOnce;			// ��񂵂���肽���Ȃ��Ƃ�
	float				m_fDist;			// �v���C���[�Ǝ����̋���
	float				m_fPrevDist;		// �O�̍��W�Ōv�Z��������
	bool				m_bSceneChengeFlag;	// �V�[���`�F���W���邩
	int					m_pMaxParts;		// �p�[�c�ő吔
	int					m_iTime;			// ����
	XMFLOAT4			m_fRimColor;		// �������C�g�̐F

	CGround*			m_pGround;			// �n��
	CPlayer*			m_pPlayer;			// ���@
	CHPGaugePlayer*		m_pHPGaugePlayer;	// HP�Q�[�W

public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CEnemy(CScene* pScene);
	virtual HRESULT Init();
	virtual void Update();
	void Draw();
	void DrawAlpha();

	//����������������������������������������
	// ����
	//����������������������������������������
	void Move(XMFLOAT3 xyz, const char dir, float speed);
	bool lblPos(XMFLOAT3 posA, XMFLOAT3 posB, float speed);
	bool lblPosXZ(XMFLOAT2 posA, XMFLOAT2 posB, float speed);
	void WallJump();

	//����������������������������������������
	// ���̑�
	//����������������������������������������
	void LifeDmg(int dmg) { m_iLife -= dmg; }		// �̗͂����炷
	int GetMaxLife() { return m_iMaxLife; }			// �ő�̗͂�n��

	void SetSceneChengeFlag(bool falg = true) { m_bSceneChengeFlag = falg; }
	bool GetSceneChengeFlag() { return m_bSceneChengeFlag; }

	//����������������������������������������
	// ���f���֘A
	//����������������������������������������
	void CalcMatrix();				// �p�x����}�g���b�N�X���v�Z(�S�p�[�c��)

	//����������������������������������������
	// �����蔻��
	//����������������������������������������
	void GroundCollision();			// �n��
};