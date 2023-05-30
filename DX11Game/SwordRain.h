//=============================================================================
//
// ���̉J [SwordRain.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Model.h"

class CPlayer;
class CHPGaugePlayer;
//����������������������������������������
// �\�[�_�\�̍U��3�G�t�F�N�g �N���X
//����������������������������������������
class CSwordRain : public CModel
{
private:
	CAssimpModel*	m_pModel;
	XMFLOAT4		m_fRimColor;
	float			m_fAcssel;		// �����x
	bool			hit;			// ��񂠂������画�������
	int				cnttemp;		// �ėp�J�E���g
	int				terget;			// ���ł܂ł̎���

	CPlayer* m_pPlayer;					// �v���C���[
	CHPGaugePlayer* m_pHPGaugePlayer;	// HP�Q�[�W(�v���C���[)

public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CSwordRain(CScene* pScene);
	HRESULT Init();
	void Fin();
	void Update();
	void Draw();
	void DrawAlpha();

	//����������������������������������������
	// ����
	//����������������������������������������
	static CSwordRain* Creat(CScene* pScene, XMFLOAT4X4& mtxWorld);
};
