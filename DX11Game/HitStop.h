/*������������������������������������������������������������������������������

	�q�b�g�X�g�b�v[HitStop.h]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#pragma once
#include "main.h"

//����������������������������������������
// �q�b�g�X�g�b�v �N���X
//����������������������������������������
class CHitStop
{
private:
	static bool m_bIsHitStop;	// �q�b�g�X�g�b�v����
	static int m_iAddTime;		// �I���܂ł̎��Ԍv��
	static int m_iFrameSpeed;

public:
	static bool HitStop();
	static void Set(int time, int speed);
};