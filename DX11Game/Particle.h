//=============================================================================
//
// �p�[�e�B�N�� [Particle.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Model.h"

//����������������������������������������
// �}�N����`
//����������������������������������������
#define MAX_PARTICLE	(5)


//����������������������������������������
// �p�[�e�B�N�� �N���X
//����������������������������������������
class CParticle : public CModel
{
private:
	//����������������������������������������
	// �\���̒�`
	//����������������������������������������
	struct TParticle
	{
		XMFLOAT3	Pos;		// ���W
		XMFLOAT3	Power;		// ��
		XMFLOAT3	MinusPower;	// pPower����߂Ă�����
		int			DeleteTime;	// ������܂ł̎���
	};

	TParticle	m_particle;
	int			AddTime;

public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CParticle(CScene* pScene);

	HRESULT Init();
	void Fin();
	void Update();
	void Draw();
	void DrawAlpha();

	//����������������������������������������
	// ����
	//����������������������������������������
	static CParticle* Creat(CScene* pScene, XMFLOAT4X4& matrix, int time, XMINT3 power, XMFLOAT3 mpower);
};