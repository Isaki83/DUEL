/*������������������������������������������������������������������������������

	���C���L�����N�^�[
	�A�j���[�V���� �f�[�^ [PlayerAnim.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "PlayerAnim.h"


namespace
{
	//����������������������������������������
	// �A�j���[�V���� �f�[�^ �t�@�C����
	//����������������������������������������
	const char* g_pathAnimData_MC[] = {
		nullptr,

		"data/animdata/MainCharacter/MC_Base.bin",
		"data/animdata/MainCharacter/MC_Attack_01.bin",
	};
}


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CPlayerAnimData::CPlayerAnimData()
{
	m_MaxParts = MAX_MC_PARTS;

	m_timer = 0.0f;
	m_iTimerAddSpeed = 1.0f;
	m_anim_index = 0;

	m_keyFrameMax = 0;
	m_pAnimData = nullptr;

	for (int i = 0; i < 2; i++) { m_bLoop[i] = true; }

	// �K�v�ȗv�f�����_�~�[�f�[�^�Ŗ��߂�
	for (int i = 0; i < m_MaxParts; i++) { m_angle.push_back(XMFLOAT3(0.0f, 0.0f, 0.0f)); }
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
int CPlayerAnimData::Init(const char* path)
{
	Fin();
	int load = 0;
	if (path) { load = Load(path); }
	if (load <= 0) 
	{
		// �ǂݍ��ݎ��s���̓_�~�[�f�[�^�Ŗ��߂�
		m_keyFrameMax = 2;
		m_pAnimData = new TAnimData_MC[m_keyFrameMax];
		for (int i = 0; i < m_keyFrameMax; ++i) 
		{
			m_pAnimData[i].m_time = i * 10;
			for (int j = 0; j < m_MaxParts; ++j) { m_pAnimData[i].m_angle[j] = XMFLOAT3(0.0f, 0.0f, 0.0f); }
		}
	}
	return load;
}


/*������������������������������������������������������������������������������

	�I������

������������������������������������������������������������������������������*/
void CPlayerAnimData::Fin()
{
	SAFE_DELETE_ARRAY(m_pAnimData);
	m_keyFrameMax = 0;
}


/*������������������������������������������������������������������������������

	�A�j���[�V�����S�̃t���[�����擾

������������������������������������������������������������������������������*/
float CPlayerAnimData::GetLastTime()
{
	if (m_keyFrameMax <= 0 || !m_pAnimData) { return 0.0f; }
	return (float)m_pAnimData[m_keyFrameMax - 1].m_time;
}


/*������������������������������������������������������������������������������

	���݂̊p�x

������������������������������������������������������������������������������*/
XMFLOAT3 CPlayerAnimData::GetAngle(int partsNo)
{
	if (partsNo >= 0 && partsNo < m_MaxParts) { return m_angle[partsNo]; }
	return XMFLOAT3(0, 0, 0);
}


/*������������������������������������������������������������������������������

	�t���[���ԍ��ݒ�

������������������������������������������������������������������������������*/
void CPlayerAnimData::SetTimer(float timer)
{
	m_timer = timer;
}


/*������������������������������������������������������������������������������

	�t���[���ԍ��X�V
	�ŏI�t���[���ɂȂ�����"true"��Ԃ�

������������������������������������������������������������������������������*/
bool CPlayerAnimData::AddTimer()
{
	// ���Ԃƃt���[����i�߂�
	m_timer += m_iTimerAddSpeed;
	while (m_timer >= (float)m_pAnimData[m_anim_index + 1].m_time)
	{
		// ���̃t���[����
		if (m_bLoop[1]) {m_anim_index++;}
		if (m_anim_index >= m_keyFrameMax - 1)
		{
			if (m_bLoop[0]) { m_anim_index = 0; }	// �t���[���擪��
			else { m_bLoop[1] = false; }
			m_timer = 0.0f;
			return true;
			break;
		}
	}
	Lerp();
	return false;
}


/*������������������������������������������������������������������������������

	�A�j���[�V���� �f�[�^��������

������������������������������������������������������������������������������*/
int CPlayerAnimData::Save(const char* path)
{
	int nCount = 0;
	FILE* fp = fopen(path, "wb");
	if (fp) 
	{
		fwrite(&m_keyFrameMax, sizeof(m_keyFrameMax), 1, fp);
		fwrite(m_pAnimData, sizeof(TAnimData_MC), m_keyFrameMax, fp);
		fclose(fp);
		nCount = m_keyFrameMax;
	}
	return nCount;
}


/*������������������������������������������������������������������������������

	�A�j���[�V���� �f�[�^�ǂݍ���

������������������������������������������������������������������������������*/
int CPlayerAnimData::Load(const char* path)
{
	int nCount = 0;
	FILE* fp = fopen(path, "rb");
	if (fp) 
	{
		if (fread(&nCount, sizeof(nCount), 1, fp) > 0 && nCount > 0) 
		{
			SAFE_DELETE_ARRAY(m_pAnimData);
			m_pAnimData = new TAnimData_MC[nCount];
			fread(m_pAnimData, sizeof(TAnimData_MC), nCount, fp);
			m_keyFrameMax = nCount;
		}
		fclose(fp);
	}
	return nCount;
}


/*������������������������������������������������������������������������������

	���`���

������������������������������������������������������������������������������*/
void CPlayerAnimData::Lerp()
{
	// ���Ԃ���p�x����`��Ԃŋ��߂�
	float dt = (m_timer - (float)m_pAnimData[m_anim_index].m_time) /
		((float)m_pAnimData[m_anim_index + 1].m_time - (float)m_pAnimData[m_anim_index].m_time);
	for (int i = 0; i < m_MaxParts; ++i) 
	{
		float dg = m_pAnimData[m_anim_index + 1].m_angle[i].x - m_pAnimData[m_anim_index].m_angle[i].x;
		m_angle[i].x = m_pAnimData[m_anim_index].m_angle[i].x + dg * dt;
		dg = m_pAnimData[m_anim_index + 1].m_angle[i].y - m_pAnimData[m_anim_index].m_angle[i].y;
		m_angle[i].y = m_pAnimData[m_anim_index].m_angle[i].y + dg * dt;
		dg = m_pAnimData[m_anim_index + 1].m_angle[i].z - m_pAnimData[m_anim_index].m_angle[i].z;
		m_angle[i].z = m_pAnimData[m_anim_index].m_angle[i].z + dg * dt;
	}
}


//=========================================================================


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CPlayerAnimSet::CPlayerAnimSet()
{
	m_anim_count = 0;
	m_pAnimData = nullptr;
	m_anim_set = 0;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
int CPlayerAnimSet::Init()
{
	Fin();
	m_pAnimData = new CPlayerAnimData[_countof(g_pathAnimData_MC)];
	m_anim_count = 1;
	m_pAnimData[0].Init();	// 0�����G���[�`�F�b�N����
	for (int i = 1; i < _countof(g_pathAnimData_MC); ++i) 
	{
		if (m_pAnimData[i].Init(g_pathAnimData_MC[i]) <= 0) { break; }
		++m_anim_count;
	}
	return m_anim_count;	// �A�j���[�V������
}


/*������������������������������������������������������������������������������

	�I������

������������������������������������������������������������������������������*/
void CPlayerAnimSet::Fin()
{
	SAFE_DELETE_ARRAY(m_pAnimData);
	m_anim_count = 0;
}


/*������������������������������������������������������������������������������

	�A�j���[�V�����ؑ�

������������������������������������������������������������������������������*/
void CPlayerAnimSet::Play(int animNo, float timer, bool loop)
{
	if (animNo >= 0 && animNo < m_anim_count) 
	{
		if (m_anim_set != animNo) 
		{ 
			m_anim_set = animNo; 
			m_pAnimData[m_anim_set].SetmAnimIndex(0);
			m_pAnimData[m_anim_set].TimerAddSpeed(timer);
			m_pAnimData[m_anim_set].SetLoop(loop);
		}
	}
}


/*������������������������������������������������������������������������������

	�ŏI�t���[��No.�擾

������������������������������������������������������������������������������*/
int CPlayerAnimSet::GetLastTime(int animNo)
{
	if (animNo >= 0 && animNo < m_anim_count) { return m_pAnimData[animNo].GetLastTime(); }
	if (m_anim_set >= 0 && m_anim_set < m_anim_count) { return m_pAnimData[m_anim_set].GetLastTime(); }
	return 0;
}


/*������������������������������������������������������������������������������

	�p�[�c���̊p�x�擾

������������������������������������������������������������������������������*/
XMFLOAT3 CPlayerAnimSet::GetAngle(int partsNo, int animNo)
{
	if (animNo >= 0 && animNo < m_anim_count) { return m_pAnimData[animNo].GetAngle(partsNo); }
	if (m_anim_set >= 0 && m_anim_set < m_anim_count) { return m_pAnimData[m_anim_set].GetAngle(partsNo); }
	return XMFLOAT3(0, 0, 0);
}


/*������������������������������������������������������������������������������

	�t���[���ԍ��ݒ�

������������������������������������������������������������������������������*/
void CPlayerAnimSet::SetTimer(int timer, int animNo)
{
	if (animNo >= 0 && animNo < m_anim_count) { m_pAnimData[animNo].SetTimer(timer); }
	if (m_anim_set >= 0 && m_anim_set < m_anim_count) { m_pAnimData[m_anim_set].SetTimer(timer); }
}


/*������������������������������������������������������������������������������

	�t���[���ԍ��擾

������������������������������������������������������������������������������*/
float CPlayerAnimSet::GetTimer(int animNo)
{
	if (animNo >= 0 && animNo < m_anim_count) { return m_pAnimData[animNo].GetTimer(); }
	if (m_anim_set >= 0 && m_anim_set < m_anim_count) { return m_pAnimData[m_anim_set].GetTimer(); }
}



/*������������������������������������������������������������������������������

	�t���[���ԍ��X�V

������������������������������������������������������������������������������*/
bool CPlayerAnimSet::AddTimer(int animNo)
{
	if (animNo >= 0 && animNo < m_anim_count) { return m_pAnimData[animNo].AddTimer(); }
	if (m_anim_set >= 0 && m_anim_set < m_anim_count) { return m_pAnimData[m_anim_set].AddTimer(); }
	return true;
}
