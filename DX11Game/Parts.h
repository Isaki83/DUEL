/*������������������������������������������������������������������������������

	�p�[�c��� [Parts.h]
	Author : ISAKI SUGIURA

������������������������������������������������������������������������������*/
#pragma once
#include "main.h"

//����������������������������������������
// �}�N����`
//����������������������������������������
#define MAX_PARTS	(15)

//����������������������������������������
// �񋓌^
//����������������������������������������
// --- �p�[�c��� ---
// ���C���L�����N�^�[(���@)
enum EParts_MC
{
	PARTS_MC_LOOT = 0,		// ���[�g
	PARTS_MC_BODY,			// ��
	PARTS_MC_ARM_UP_R,		// �E�r-��
	PARTS_MC_ARM_DOWN_R,	// �E�r-��
	PARTS_MC_HAND_R,		// �E��

	MAX_MC_PARTS
};
// �S�[����(�G)
enum EParts_Golem
{
	PARTS_GOLEM_LOOT = 0,	// ���[�g
	PARTS_GOLEM_HIP,		// ��
	PARTS_GOLEM_BODY,		// ��
	PARTS_GOLEM_HEAD,		// ��
	PARTS_GOLEM_ARM_UP_R,	// �E�r-��
	PARTS_GOLEM_ARM_DOWN_R,	// �E�r-��
	PARTS_GOLEM_ARM_UP_L,	// ���r-��
	PARTS_GOLEM_ARM_DOWN_L,	// ���r-��
	PARTS_GOLEM_LEG_UP_R,	// �E��-��
	PARTS_GOLEM_LEG_DOWN_R,	// �E��-��
	PARTS_GOLEM_LEG_UP_L,	// ����-��
	PARTS_GOLEM_LEG_DOWN_L,	// ����-��
	MAX_GOLEM_PARTS,
};
// SwordMan(�G)
enum EParts_SwordMan
{
	PARTS_SM_LOOT = 0,	// ���[�g
	PARTS_SM_HIP,		// ��
	PARTS_SM_BODY,		// ��
	PARTS_SM_HEAD,		// ��
	PARTS_SM_ARM_UP_R,	// �E�r-��
	PARTS_SM_ARM_DOWN_R,// �E�r-��
	PARTS_SM_HAND_R,	// �E��
	PARTS_SM_ARM_UP_L,	// ���r-��
	PARTS_SM_ARM_DOWN_L,// ���r-��
	PARTS_SM_HAND_L,	// ����
	PARTS_SM_LEG_UP_R,	// �E��-��
	PARTS_SM_LEG_DOWN_R,// �E��-��
	PARTS_SM_LEG_UP_L,	// ����-��
	PARTS_SM_LEG_DOWN_L,// ����-��
	PARTS_BLACK_SWORD,	// ����
	MAX_SM_PARTS,
};


//����������������������������������������
// �\���̒�`
//����������������������������������������
// �p�[�c�����f�[�^
struct TPartsData
{
	int			parent;		// �e�p�[�c�ԍ�
	int			model;		// ���f���ԍ�
	XMFLOAT3	off;		// �I�t�Z�b�g�l
	float		DmgRatio;	// �_���[�W�{��
};

// �p�[�c���
struct TParts
{
	bool		use;		// �g���Ă��邩
	int			parent;		// �e�p�[�c�ԍ�
	int			model;		// ���f���ԍ�
	XMFLOAT3	off;		// �I�t�Z�b�g�l
	XMFLOAT3	angle;		// �p�x
	XMFLOAT4X4	matrix;		// ��]�}�g���b�N�X
	XMFLOAT3	center;		// ���E�{�b�N�X ���S���W
	XMFLOAT3	bbox;		// ���E�{�b�N�X �傫��
	float		DmgRatio;	// �_���[�W�{��
	bool		hitDefence;	// �������Ă��邩(��)
	bool		hitAttack;	// �������Ă��邩(�U��)
	int			num;		// �p�[�c���ʗp
};
