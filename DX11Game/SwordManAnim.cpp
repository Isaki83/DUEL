/*������������������������������������������������������������������������������

	�\�[�h�}��
	�A�j���[�V���� �f�[�^ [SwordManAnim.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "SwordManAnim.h"

namespace
{
	//����������������������������������������
	// �A�j���[�V���� �f�[�^ �t�@�C����
	//����������������������������������������
	const char* g_pathAnimData_SwordMan[] = {
		nullptr,

		"data/animdata/SwordMan/SM_Idle.bin",
		"data/animdata/SwordMan/SM_Run.bin",
		"data/animdata/SwordMan/SM_Jump.bin",

		"data/animdata/SwordMan/Attack_00/SM_Attack_00_01.bin",
		"data/animdata/SwordMan/Attack_00/SM_Attack_00_02.bin",

		"data/animdata/SwordMan/Attack_01/SM_Attack_01_01.bin",
		"data/animdata/SwordMan/Attack_01/SM_Attack_01_02.bin",
		"data/animdata/SwordMan/Attack_01/SM_Attack_01_03.bin",
		"data/animdata/SwordMan/Attack_01/SM_Attack_01_04.bin",
		"data/animdata/SwordMan/Attack_01/SM_Attack_01_05.bin",

		"data/animdata/SwordMan/Attack_02/SM_Attack_02_01.bin",
		"data/animdata/SwordMan/Attack_02/SM_Attack_02_02.bin",
		"data/animdata/SwordMan/Attack_02/SM_Attack_02_03.bin",
		"data/animdata/SwordMan/Attack_02/SM_Attack_02_04.bin",

		"data/animdata/SwordMan/Attack_03/SM_Attack_03_01.bin",
		"data/animdata/SwordMan/Attack_03/SM_Attack_03_02.bin",
	};

	const int g_BlendWait = 5;
}


/*������������������������������������������������������������������������������

	�R���X�g���N�^

������������������������������������������������������������������������������*/
CSwordManAnimData::CSwordManAnimData()
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
int CSwordManAnimData::Init(const char* path)
{
	Fin();
	int load = 0;
	if (path)
		load = Load(path);
	if (load <= 0) {
		// �ǂݍ��ݎ��s���̓_�~�[�f�[�^�Ŗ��߂�
		m_keyFrameMax = 2;
		m_pAnimData = new TAnimData_SwordMan[m_keyFrameMax];
		for (int i = 0; i < m_keyFrameMax; ++i) {
			m_pAnimData[i].m_time = i * 10;
			for (int j = 0; j < MAX_SM_PARTS; ++j) {
				m_pAnimData[i].m_angle[j] = XMFLOAT3(0, 0, 0);
			}
		}
	}
	return load;
}


/*������������������������������������������������������������������������������

	�I������

������������������������������������������������������������������������������*/
void CSwordManAnimData::Fin()
{
	SAFE_DELETE_ARRAY(m_pAnimData);
	m_keyFrameMax = 0;
}


/*������������������������������������������������������������������������������

	�A�j���[�V�����S�̃t���[�����擾

������������������������������������������������������������������������������*/
int CSwordManAnimData::GetLastTime()
{
	if (m_keyFrameMax <= 0 || !m_pAnimData) {
		return 0;
	}
	return m_pAnimData[m_keyFrameMax - 1].m_time;
}


/*������������������������������������������������������������������������������

	���݂̊p�x

������������������������������������������������������������������������������*/
XMFLOAT3 CSwordManAnimData::GetAngle(int partsNo)
{
	if (partsNo >= 0 && partsNo < MAX_SM_PARTS) {
		return m_angle[partsNo];
	}
	return XMFLOAT3(0, 0, 0);
}


/*������������������������������������������������������������������������������

	�t���[���ԍ��ݒ�

������������������������������������������������������������������������������*/
int CSwordManAnimData::SetTimer(int timer)
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
XMINT2 CSwordManAnimData::AddTimer(int timer)
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
int CSwordManAnimData::Save(const char* path)
{
	int nCount = 0;
	FILE* fp = fopen(path, "wb");
	if (fp) {
		fwrite(&m_keyFrameMax, sizeof(m_keyFrameMax), 1, fp);
		fwrite(m_pAnimData, sizeof(TAnimData_SwordMan), m_keyFrameMax, fp);
		fclose(fp);
		nCount = m_keyFrameMax;
	}
	return nCount;
}


/*������������������������������������������������������������������������������

	�A�j���[�V���� �f�[�^�ǂݍ���

������������������������������������������������������������������������������*/
int CSwordManAnimData::Load(const char* path)
{
	int nCount = 0;
	FILE* fp = fopen(path, "rb");
	if (fp) {
		if (fread(&nCount, sizeof(nCount), 1, fp) > 0 && nCount > 0) {
			SAFE_DELETE_ARRAY(m_pAnimData);
			m_pAnimData = new TAnimData_SwordMan[nCount];
			fread(m_pAnimData, sizeof(TAnimData_SwordMan), nCount, fp);
			m_keyFrameMax = nCount;
		}
		fclose(fp);
	}
	return nCount;
}


/*������������������������������������������������������������������������������

	���`���

������������������������������������������������������������������������������*/
void CSwordManAnimData::Lerp()
{
	// ���Ԃ���p�x����`��Ԃŋ��߂�
	float dt = (float)(m_timer - m_pAnimData[m_anim_index].m_time) /
		(m_pAnimData[m_anim_index + 1].m_time - m_pAnimData[m_anim_index].m_time);
	for (int i = 0; i < MAX_SM_PARTS; ++i) {
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
CSwordManAnimSet::CSwordManAnimSet()
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
int CSwordManAnimSet::Init()
{
	Fin();
	m_pAnimData = new CSwordManAnimData[_countof(g_pathAnimData_SwordMan)];
	m_anim_count = 1;
	m_pAnimData[0].Init();	// 0�����G���[�`�F�b�N����
	for (int i = 1; i < _countof(g_pathAnimData_SwordMan); ++i) {
		if (m_pAnimData[i].Init(g_pathAnimData_SwordMan[i]) <= 0) {
			break;
		}
		++m_anim_count;
	}
	return m_anim_count;	// �A�j���[�V������
}


/*������������������������������������������������������������������������������

	�I������

������������������������������������������������������������������������������*/
void CSwordManAnimSet::Fin()
{
	SAFE_DELETE_ARRAY(m_pAnimData);
	m_anim_count = 0;
}


/*������������������������������������������������������������������������������

	�A�j���[�V�����ؑ�

������������������������������������������������������������������������������*/
void CSwordManAnimSet::Play(int animNo, bool loop)
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
void CSwordManAnimSet::BlendPlay(int animNo)
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
int CSwordManAnimSet::GetLastTime(int animNo)
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
XMFLOAT3 CSwordManAnimSet::GetAngle(int partsNo, int animNo)
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
int CSwordManAnimSet::SetTimer(int timer, int animNo)
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
XMINT2 CSwordManAnimSet::AddTimer(int timer, int animNo)
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
