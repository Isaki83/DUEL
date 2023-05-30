//=============================================================================
//
// ���ꂽ�n�� [BreakGround.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Model.h"

class CPlayer;
class CHPGaugePlayer;
//����������������������������������������
// �S�[�����̍U���G�t�F�N�g �N���X
//����������������������������������������
class CBreakGround : public CModel
{
private:
	bool once;				// ��񂾂�
	int cnttemp;			// �ėp�J�E���g
	int terget;				// ���ł܂ł̎���

	CPlayer* m_pPlayer;					// �v���C���[
	CHPGaugePlayer* m_pHPGaugePlayer;	// HP�Q�[�W(�v���C���[)

public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CBreakGround(CScene* pScene);
	HRESULT Init();
	void Fin();
	void Update();

	//����������������������������������������
	// ����
	//����������������������������������������
	static CBreakGround* Creat(CScene* pScene, XMFLOAT4X4& mtxWorld);
};
