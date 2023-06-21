/*������������������������������������������������������������������������������

	���C���L�����N�^�[
	�A�j���[�V���� �f�[�^ [PlayerAnim.h]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#pragma once
#include "Parts.h"
#include "vector"

//����������������������������������������
// �}�N����`
//����������������������������������������
// �U���̓����蔻����Ƃ�^�C�~���O
#define MC_ATTACK_01_START	(30)
#define MC_ATTACK_01_END	(40)

//����������������������������������������
// �񋓌^
//����������������������������������������
// �A�j���[�V�������
enum EAnim_MC {
	ANIM_MC_NONE = 0,			// �A�j���[�V������

	ANIM_MC_BASE,				// �x�[�X
	ANIM_MC_ATTACK_01,			// �U��01

	MAX_MC_ANIM
};


//����������������������������������������
// �A�j���[�V���� �f�[�^ �N���X
//����������������������������������������
class CPlayerAnimData
{
private:
	// �L�[�t���[�����
	struct TAnimData_MC {
		int			m_time;					// ����(�t���[����)
		XMFLOAT3	m_angle[MAX_MC_PARTS];
	};

	int				m_MaxParts;				// �p�[�c��
	float			m_timer;				// �t���[���ԍ�
	float			m_iTimerAddSpeed;		// �t���[���ԍ���i�߂鑬��
	int				m_anim_index;			// ���݂̃L�[�t���[��
	std::vector<XMFLOAT3>		m_angle;	// ���݂̊p�x
	int				m_keyFrameMax;			// �L�[�t���[����
	TAnimData_MC*	m_pAnimData;			// �L�[�t���[��
	bool			m_bLoop[2];				// 0:���[�v�Đ����邩
											// 1:�t���[����i�߂��悢��
	std::vector<int> m_test;

public:
	CPlayerAnimData();
	int Init(const char* path = nullptr);
	void Fin();
	float GetLastTime();
	XMFLOAT3 GetAngle(int partsNo);
	void SetLoop(bool loop) { m_bLoop[0] = loop; }
	void SetmAnimIndex(int index) { m_anim_index = index; }
	void SetTimer(float timer);
	float GetTimer() { return m_timer; }
	bool AddTimer();
	void TimerAddSpeed(float timer) { m_iTimerAddSpeed = timer; }
	int Save(const char* path);
	int Load(const char* path);


private:
	void Lerp();
};

// =========================================================================

//����������������������������������������
// �A�j���[�V���� �N���X
//����������������������������������������
class CPlayerAnimSet
{
private:
	int					m_anim_count;	// �A�j���[�V���� �f�[�^��
	CPlayerAnimData*	m_pAnimData;	// �A�j���[�V���� �f�[�^
	int					m_anim_set;		// ���݂̃A�j���[�V���� �f�[�^

public:
	CPlayerAnimSet();
	int Init();
	void Fin();
	int GetCount() { return m_anim_count; }
	void Play(int animNo, float timer = 1.0f, bool loop = true);
	int Get() { return m_anim_set; }
	int GetLastTime(int animNo = -1);
	XMFLOAT3 GetAngle(int partsNo, int animNo = -1);
	void SetTimer(int timer, int animNo = -1);
	float GetTimer(int animNo = -1);
	bool AddTimer(int animNo = -1);
};