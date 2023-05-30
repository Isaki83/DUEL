/*������������������������������������������������������������������������������

	�S�[����
	�A�j���[�V���� �f�[�^ [GolemAnim.h]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#pragma once
#include "Parts.h"

//����������������������������������������
// �}�N����`
//����������������������������������������
// �U���̓����蔻����Ƃ�^�C�~���O
#define GOLEM_ATTACK	(50)

//����������������������������������������
// �񋓌^
//����������������������������������������
// �A�j���[�V�������
enum EAnim_Golem {
	ANIM_GOLEM_NONE = 0,			// �A�j���[�V������

	ANIM_GOLEM_IDLE,				// �ҋ@���
	ANIM_GOLEM_WALK,				// ����
	ANIM_GOLEM_JUMP,				// �W�����v
	ANIM_GOLEM_ATTACK,				// �U��
	ANIM_GOLEM_DEATH,				// ���S

	MAX_GOLEM_ANIM
};


//����������������������������������������
// �\���̒�`
//����������������������������������������
// �L�[�t���[�����
struct TAnimData_Golem {
	int			m_time;					// ����(�t���[����)
	XMFLOAT3	m_angle[MAX_GOLEM_PARTS];	// �p�x
};


//����������������������������������������
// �A�j���[�V���� �f�[�^ �N���X
//����������������������������������������
class CGolemAnimData
{
private:
	int					m_timer;					// �t���[���ԍ�
	int					m_anim_index;				// ���݂̃L�[�t���[��
	XMFLOAT3			m_angle[MAX_GOLEM_PARTS];	// ���݂̊p�x
	int					m_keyFrameMax;				// �L�[�t���[����
	TAnimData_Golem*	m_pAnimData;				// �L�[�t���[��
	bool				m_bLoop[2];					// 0:���[�v�Đ����邩
													// 1:�t���[����i�߂��悢��

public:
	CGolemAnimData();
	int Init(const char* path = nullptr);
	void Fin();
	int GetLastTime();
	XMFLOAT3 GetAngle(int partsNo);
	void SetLoop(bool loop) { m_bLoop[0] = loop; }
	void SetmAnimIndex(int index) { m_anim_index = index; }
	int SetTimer(int timer);
	XMINT2 AddTimer(int timer = 1);
	int Save(const char* path);
	int Load(const char* path);


private:
	void Lerp();
};

//=========================================================================

//����������������������������������������
// �A�j���[�V���� �N���X
//����������������������������������������
class CGolemAnimSet
{
private:
	int					m_anim_count;	// �A�j���[�V���� �f�[�^��
	CGolemAnimData*		m_pAnimData;	// �A�j���[�V���� �f�[�^
	int					m_anim_set;		// ���݂̃A�j���[�V���� �f�[�^
	int					m_prev_anim;
	int					m_blend_wait;

public:
	CGolemAnimSet();
	int Init();
	void Fin();
	int GetCount() { return m_anim_count; }
	void Play(int animNo, bool loop = true);
	void BlendPlay(int animNo);
	int Get() { return m_anim_set; }
	int GetLastTime(int animNo = -1);
	XMFLOAT3 GetAngle(int partsNo, int animNo = -1);
	int SetTimer(int timer, int animNo = -1);
	XMINT2 AddTimer(int timer = 1, int animNo = -1);
};