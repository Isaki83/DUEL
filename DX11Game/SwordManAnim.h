/*������������������������������������������������������������������������������

	�\�[�h�}��
	�A�j���[�V���� �f�[�^ [SwordManAnim.h]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#pragma once
#include "Parts.h"

//����������������������������������������
// �}�N����`
//����������������������������������������
// �U���̓����蔻����Ƃ�^�C�~���O
#define SM_ATTACK1_S	(60)
#define SM_ATTACK1_E	(100)
#define SM_ATTACK2_S	(30)
#define SM_ATTACK2_E	(90)

//����������������������������������������
// �񋓌^
//����������������������������������������
// �A�j���[�V�������
enum EAnim_SwordMan {
	ANIM_SM_NONE = 0,		// �A�j���[�V������

	ANIM_SM_IDLE,			// �ҋ@
	ANIM_SM_RUN,			// ����
	ANIM_SM_JUMP,			// �W�����v

	// ���̏��2��
	ANIM_SM_ATTACK_00_01,	// 1����
	ANIM_SM_ATTACK_00_02,	// 2����

	// ��������}�ڋ߂���2�A��
	ANIM_SM_ATTACK_01_01,	// �\����
	ANIM_SM_ATTACK_01_02,	// �߂Â�
	ANIM_SM_ATTACK_01_03,	// 1����
	ANIM_SM_ATTACK_01_04,	// 2����
	ANIM_SM_ATTACK_01_05,	// �Ԑ���߂�

	// �����Ă�����x�ߕt���Ă���A�˂���Ԃŋ}�ڋ߂��ĉ񂵎a��
	ANIM_SM_ATTACK_02_01,	// �\����
	ANIM_SM_ATTACK_02_02,	// �˂�
	ANIM_SM_ATTACK_02_03,	// �񂵎a��
	ANIM_SM_ATTACK_02_04,	// �Ԑ���߂�

	// �n�ʂɌ����w���čL�͈͂ɍU��
	ANIM_SM_ATTACK_03_01,	// �h��
	ANIM_SM_ATTACK_03_02,	// �Ԑ���߂�

	MAX_SM_ANIM,
};


//����������������������������������������
// �\���̒�`
//����������������������������������������
// �L�[�t���[�����
struct TAnimData_SwordMan {
	int			m_time;					// ����(�t���[����)
	XMFLOAT3	m_angle[MAX_SM_PARTS];	// �p�x
};


//����������������������������������������
// �A�j���[�V���� �f�[�^ �N���X
//����������������������������������������
class CSwordManAnimData
{
private:
	int					m_timer;					// �t���[���ԍ�
	int					m_anim_index;				// ���݂̃L�[�t���[��
	XMFLOAT3			m_angle[MAX_SM_PARTS];	// ���݂̊p�x
	int					m_keyFrameMax;				// �L�[�t���[����
	TAnimData_SwordMan*	m_pAnimData;				// �L�[�t���[��
	bool				m_bLoop[2];					// 0:���[�v�Đ����邩
													// 1:�t���[����i�߂��悢��

public:
	CSwordManAnimData();
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
class CSwordManAnimSet
{
private:
	int					m_anim_count;	// �A�j���[�V���� �f�[�^��
	CSwordManAnimData*	m_pAnimData;	// �A�j���[�V���� �f�[�^
	int					m_anim_set;		// ���݂̃A�j���[�V���� �f�[�^
	int					m_prev_anim;
	int					m_blend_wait;

public:
	CSwordManAnimSet();
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