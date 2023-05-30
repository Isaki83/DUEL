/*������������������������������������������������������������������������������

	�S�[����
	�A�j���[�V���� �f�[�^ [GolemAnim.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "GolemAnim.h"

namespace
{
	//����������������������������������������
	// �A�j���[�V���� �f�[�^ �t�@�C����
	//����������������������������������������
	const char* g_pathAnimData_Golem[] = {
		nullptr,

		"data/animdata/Golem/Golem_Idle.bin",
		"data/animdata/Golem/Golem_Walk.bin",
		"data/animdata/Golem/Golem_Jump.bin",
		"data/animdata/Golem/Golem_Attack.bin",
		"data/animdata/Golem/Golem_Death.bin",
	};

	const int g_BlendWait = 5;
}


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CGolemAnimData::CGolemAnimData()
{
	m_timer = 0;
	m_anim_index = 0;

	m_keyFrameMax = 0;
	m_pAnimData = nullptr;

	for (int i = 0; i < 2; i++) { m_bLoop[i] = true; }
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
int CGolemAnimData::Init(const char* path)
{
	Fin();
	int load = 0;
	if (path)
		load = Load(path);
	if (load <= 0) {
		// �ǂݍ��ݎ��s���̓_�~�[�f�[�^�Ŗ��߂�
		m_keyFrameMax = 2;
		m_pAnimData = new TAnimData_Golem[m_keyFrameMax];
		for (int i = 0; i < m_keyFrameMax; ++i) {
			m_pAnimData[i].m_time = i * 10;
			for (int j = 0; j < MAX_GOLEM_PARTS; ++j) {
				m_pAnimData[i].m_angle[j] = XMFLOAT3(0, 0, 0);
			}
		}
	}
	return load;
}


/*������������������������������������������������������������������������������

	�I������

������������������������������������������������������������������������������*/
void CGolemAnimData::Fin()
{
	SAFE_DELETE_ARRAY(m_pAnimData);
	m_keyFrameMax = 0;
}


/*������������������������������������������������������������������������������

	�A�j���[�V�����S�̃t���[�����擾

������������������������������������������������������������������������������*/
int CGolemAnimData::GetLastTime()
{
	if (m_keyFrameMax <= 0 || !m_pAnimData) {
		return 0;
	}
	return m_pAnimData[m_keyFrameMax - 1].m_time;
}


/*������������������������������������������������������������������������������

	���݂̊p�x

������������������������������������������������������������������������������*/
XMFLOAT3 CGolemAnimData::GetAngle(int partsNo)
{
	if (partsNo >= 0 && partsNo < MAX_GOLEM_PARTS) {
		return m_angle[partsNo];
	}
	return XMFLOAT3(0, 0, 0);
}


/*������������������������������������������������������������������������������

	�t���[���ԍ��ݒ�

������������������������������������������������������������������������������*/
int CGolemAnimData::SetTimer(int timer)
{
	int eoa = 0;
	// ���Ԃƃt���[����i�߂�
	m_timer = timer;
	while (m_timer >= m_pAnimData[m_anim_index + 1].m_time) {
		// ���̃t���[����
		m_anim_index++;
		if (m_anim_index >= m_keyFrameMax - 1) {
			m_anim_index = 0;	// �t���[���擪��
			m_timer = 0;
			return eoa = 1;
			break;
		}
	}
	Lerp();
	return eoa;
}


/*������������������������������������������������������������������������������

	�t���[���ԍ��X�V

	�߂�l1 :	0 > �A�j���[�V�������I����ĂȂ�
				1 > �A�j���[�V�������I����Ă���
	�߂�l2 :	�A�j���[�V�����o�߃t���[����

������������������������������������������������������������������������������*/
XMINT2 CGolemAnimData::AddTimer(int timer)
{
	int eoa = 0;
	// ���Ԃƃt���[����i�߂�
	m_timer += timer;
	while (m_timer >= m_pAnimData[m_anim_index + 1].m_time)
	{
		// ���̃t���[����
		if (m_bLoop[1]) { m_anim_index++; }
		if (m_anim_index >= m_keyFrameMax - 1) 
		{
			if (m_bLoop[0]) { m_anim_index = 0; }	// �t���[���擪��
			else { m_bLoop[1] = false; }
			m_timer = 0;
			eoa = 1;
			return XMINT2(eoa, m_timer);
			break;
		}
	}
	Lerp();
	return XMINT2(eoa, m_timer);
}


/*������������������������������������������������������������������������������

	�A�j���[�V���� �f�[�^��������

������������������������������������������������������������������������������*/
int CGolemAnimData::Save(const char* path)
{
	int nCount = 0;
	FILE* fp = fopen(path, "wb");
	if (fp) {
		fwrite(&m_keyFrameMax, sizeof(m_keyFrameMax), 1, fp);
		fwrite(m_pAnimData, sizeof(TAnimData_Golem), m_keyFrameMax, fp);
		fclose(fp);
		nCount = m_keyFrameMax;
	}
	return nCount;
}


/*������������������������������������������������������������������������������

	�A�j���[�V���� �f�[�^�ǂݍ���

������������������������������������������������������������������������������*/
int CGolemAnimData::Load(const char* path)
{
	int nCount = 0;
	FILE* fp = fopen(path, "rb");
	if (fp) {
		if (fread(&nCount, sizeof(nCount), 1, fp) > 0 && nCount > 0) {
			SAFE_DELETE_ARRAY(m_pAnimData);
			m_pAnimData = new TAnimData_Golem[nCount];
			fread(m_pAnimData, sizeof(TAnimData_Golem), nCount, fp);
			m_keyFrameMax = nCount;
		}
		fclose(fp);
	}
	return nCount;
}


/*������������������������������������������������������������������������������

	���`���

������������������������������������������������������������������������������*/
void CGolemAnimData::Lerp()
{
	// ���Ԃ���p�x����`��Ԃŋ��߂�
	float dt = (float)(m_timer - m_pAnimData[m_anim_index].m_time) /
		(m_pAnimData[m_anim_index + 1].m_time - m_pAnimData[m_anim_index].m_time);
	for (int i = 0; i < MAX_GOLEM_PARTS; ++i) {
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
CGolemAnimSet::CGolemAnimSet()
{
	m_anim_count = 0;
	m_pAnimData = nullptr;
	m_anim_set = 0;
	m_prev_anim = 0;
	m_blend_wait = 0;
}


/*������������������������������������������������������������������������������

	������

������������������������������������������������������������������������������*/
int CGolemAnimSet::Init()
{
	Fin();
	m_pAnimData = new CGolemAnimData[_countof(g_pathAnimData_Golem)];
	m_anim_count = 1;
	m_pAnimData[0].Init();	// 0�����G���[�`�F�b�N����
	for (int i = 1; i < _countof(g_pathAnimData_Golem); ++i) {
		if (m_pAnimData[i].Init(g_pathAnimData_Golem[i]) <= 0) {
			break;
		}
		++m_anim_count;
	}
	return m_anim_count;	// �A�j���[�V������
}


/*������������������������������������������������������������������������������

	�I������

������������������������������������������������������������������������������*/
void CGolemAnimSet::Fin()
{
	SAFE_DELETE_ARRAY(m_pAnimData);
	m_anim_count = 0;
}


/*������������������������������������������������������������������������������

	�A�j���[�V�����ؑ�

������������������������������������������������������������������������������*/
void CGolemAnimSet::Play(int animNo, bool loop)
{
	if (animNo >= 0 && animNo < m_anim_count) 
	{
		if (m_anim_set != animNo) 
		{
			m_anim_set = animNo;
			m_pAnimData[m_anim_set].SetmAnimIndex(0);
			m_pAnimData[m_anim_set].SetLoop(loop);
		}
	}
}
void CGolemAnimSet::BlendPlay(int animNo)
{
	if (animNo >= 0 && animNo < m_anim_count) {
		if (m_anim_set != animNo) {
			m_prev_anim = m_anim_set;
			m_anim_set = animNo;
			m_blend_wait = g_BlendWait;
		}
	}
}


/*������������������������������������������������������������������������������

	�ŏI�t���[��No.�擾

������������������������������������������������������������������������������*/
int CGolemAnimSet::GetLastTime(int animNo)
{
	if (animNo >= 0 && animNo < m_anim_count) {
		return m_pAnimData[animNo].GetLastTime();
	}
	if (m_anim_set >= 0 && m_anim_set < m_anim_count) {
		return m_pAnimData[m_anim_set].GetLastTime();
	}
	return 0;
}


/*������������������������������������������������������������������������������

	�p�[�c���̊p�x�擾

������������������������������������������������������������������������������*/
XMFLOAT3 CGolemAnimSet::GetAngle(int partsNo, int animNo)
{
	if (animNo >= 0 && animNo < m_anim_count) {
		return m_pAnimData[animNo].GetAngle(partsNo);
	}
	if (m_anim_set >= 0 && m_anim_set < m_anim_count) {
		//return m_pAnimData[m_anim_set].GetAngle(partsNo);
		// �����Ń��[�V���� �u�����f�B���O���s���B
		// �������ł͊p�x���������킹�Ă��邪�A���ۂɍ������킹��l
		//   �́A�L�[�t���[���ɂǂ̂悤�ȏ��������Ă��邩�ňقȂ�B
		XMFLOAT3 angle = m_pAnimData[m_anim_set].GetAngle(partsNo);
		if (m_blend_wait > 0) {
			XMFLOAT3 prev_angle = m_pAnimData[m_prev_anim].GetAngle(partsNo);
			float ratio = (float)m_blend_wait / g_BlendWait;
			angle.x = angle.x * (1.0f - ratio) + prev_angle.x * ratio;
			angle.y = angle.y * (1.0f - ratio) + prev_angle.y * ratio;
			angle.z = angle.z * (1.0f - ratio) + prev_angle.z * ratio;
		}
		return angle;
	}
	return XMFLOAT3(0, 0, 0);
}


/*������������������������������������������������������������������������������

	�t���[���ԍ��ݒ�

������������������������������������������������������������������������������*/
int CGolemAnimSet::SetTimer(int timer, int animNo)
{
	if (m_blend_wait > 0) {
		--m_blend_wait;
		m_pAnimData[m_prev_anim].SetTimer(timer);
	}
	if (animNo >= 0 && animNo < m_anim_count) {
		return m_pAnimData[animNo].SetTimer(timer);
	}
	if (m_anim_set >= 0 && m_anim_set < m_anim_count) {
		return m_pAnimData[m_anim_set].SetTimer(timer);
	}
	return 1;
}


/*������������������������������������������������������������������������������

	�t���[���ԍ��X�V

������������������������������������������������������������������������������*/
XMINT2 CGolemAnimSet::AddTimer(int timer, int animNo)
{
	if (m_blend_wait > 0) {
		--m_blend_wait;
		m_pAnimData[m_prev_anim].AddTimer(timer);
	}
	if (animNo >= 0 && animNo < m_anim_count) {
		return m_pAnimData[animNo].AddTimer(timer);
	}
	if (m_anim_set >= 0 && m_anim_set < m_anim_count) {
		return m_pAnimData[m_anim_set].AddTimer(timer);
	}
	return XMINT2(1, 0);
}
