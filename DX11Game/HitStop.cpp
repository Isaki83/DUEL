/*������������������������������������������������������������������������������

	�q�b�g�X�g�b�v[HitStop.cpp]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#include "HitStop.h"

//����������������������������������������
// �ÓI�����o�ϐ�
//����������������������������������������
bool	CHitStop::m_bIsHitStop = false;
int		CHitStop::m_iAddTime = 0;
int		CHitStop::m_iFrameSpeed = 0;


/*������������������������������������������������������������������������������

	�q�b�g�X�g�b�v
	�~�܂�Ƃ���	false
	�����Ƃ���	true

������������������������������������������������������������������������������*/
bool CHitStop::HitStop()
{
	// �q�b�g�X�g�b�v���n�܂��Ă���̎���
	static int AddTime = 0;
	AddTime++;

	// ���Ԃ��I���ƕϐ��������l�ɖ߂��ď��true
	if (m_iAddTime < AddTime)
	{
		m_iAddTime = 0;
		m_iFrameSpeed = 0;
		m_bIsHitStop = false;
		AddTime = 0;
	}

	// �t���[�����X�s�[�h���傫���Ȃ����瓮��
	if (m_iFrameSpeed <= AddTime % (m_iFrameSpeed + 1)) { return true; }

	// �������Ȃ�
	return false;
}


/*������������������������������������������������������������������������������

	�q�b�g�X�g�b�v�J�n
	������ : �~�߂�t���[����
	������ : ���t���[�������ɓ�������

������������������������������������������������������������������������������*/
void CHitStop::Set(int time, int speed)
{
	if (m_bIsHitStop) { return; }

	m_iAddTime = time;
	m_iFrameSpeed = speed;
	m_bIsHitStop = true;
}