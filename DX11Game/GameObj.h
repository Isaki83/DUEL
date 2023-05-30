//=============================================================================
//
// �I�u�W�F�N�g [GameObj.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "main.h"
#include "Parts.h"
#include "Box.h"		// �f�o�b�O�\���p
#include <vector>


//����������������������������������������
// �񋓌^
//����������������������������������������
enum EGameObjType 
{	// �I�u�W�F�N�g�^
	GOT_GAMEOBJ = 0,	// �^����
	GOT_PLAYER,			// �v���C���[
	GOT_WEAPON,			// ����
	GOT_ENEMY,			// �G�l�~�[
	GOT_GROUND,			// �n��
	GOT_BREAK_GROUND,	// ���ꂽ�n��
	GOT_SWORD_RAIN,		// ���̉J
	GOT_PARTICLE,		// �p�[�e�B�N��

	MAX_GAMEOBJTYPE
};
enum EBoundaryType 
{	// ���E���
	BT_NONE = 0,		// ��\��
	BT_OBB,				// ���E�{�b�N�X(OBB)

	MAX_BOUNDTYPE
};


class CScene;
//����������������������������������������
// 3D�I�u�W�F�N�g �p�����N���X
//����������������������������������������
class CGameObj
{
private:
	CGameObj* m_pBack;		// �O�̃I�u�W�F�N�g
	CGameObj* m_pNext;		// ���̃I�u�W�F�N�g

protected:
	//����������������������������������������
	// �I�u�W�F�N�g����
	//����������������������������������������
	EGameObjType m_id;		// �I�u�W�F�N�g�^

	CScene* m_pScene;		// �����V�[��

	//����������������������������������������
	// ��{
	//����������������������������������������
	XMFLOAT3 m_vPos;		// ���W
	XMFLOAT3 m_vVel;		// ���x
	XMFLOAT3 m_vAccel;		// �����x
	XMFLOAT3 m_vAngle;		// �p�x
	XMFLOAT3 m_vScale;		// �g�k

	//����������������������������������������
	// �K�w�\���p
	//����������������������������������������
	std::vector<TParts> m_parts;	// �p�[�c

	//����������������������������������������
	// ���̑�
	//����������������������������������������
	XMFLOAT4X4 m_mWorld;	// ���[���h�ϊ�

	bool m_bVisible;		// �\���t���O

	//����������������������������������������
	// �����蔻��p
	//����������������������������������������
	XMFLOAT3 m_vCenter;		// ���E�{�b�N�X(/��)���S���W
	XMFLOAT3 m_vBBox;		// ���E�{�b�N�X
	float m_fRadius;		// ���E�����a

	//����������������������������������������
	// �f�o�b�O �����蔻��\���p
	//����������������������������������������
	EBoundaryType m_bt;		// ���E���
	CBox* m_pBBox;			// ���E�{�b�N�X�\���p���b�V��

public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CGameObj(CScene* pScene);
	virtual ~CGameObj(void);

	virtual HRESULT Init();		// ������
	virtual void Update();		// �X�V
	virtual void Draw();		// �s���������`��
	virtual void DrawAlpha();	// �����������`��
	virtual void Fin();			// �I������

	static HRESULT InitAll(CGameObj* pTop);
	static void UpdateAll(CGameObj*& pTop);
	static void DrawAll(CGameObj* pTop);
	static void FinAll(CGameObj* pTop);

	void SetPos(XMFLOAT3 vPos) { m_vPos = vPos; }
	XMFLOAT3& GetPos() { return m_vPos; }
	void SetAngle(XMFLOAT3 vAngle) { m_vAngle = vAngle; }
	XMFLOAT3& GetAngle() { return m_vAngle; }
	void SetScale(XMFLOAT3 vScale) { m_vScale = vScale; }
	XMFLOAT3& GetScale() { return m_vScale; }
	void SetWorld(XMFLOAT4X4& mWorld) { m_mWorld = mWorld; }
	XMFLOAT4X4& GetWorld() { return m_mWorld; }
	XMFLOAT3& GetVel() { return m_vVel; }

	//����������������������������������������
	// �I�u�W�F�N�g����
	//����������������������������������������
	EGameObjType GetID() { return m_id; }
	CGameObj* GetNext() { return m_pNext; }

	//����������������������������������������
	// �\���E��\��
	//����������������������������������������
	void SetVisible(bool bVisible = true) { m_bVisible = bVisible; }
	virtual bool IsVisible() { return m_bVisible; }

	//����������������������������������������
	// �����蔻��p
	//����������������������������������������
	void SetPartsHitDefence(int parts, bool hit) { m_parts[parts].hitDefence = hit; }
	void SetPartsHitAttack(int parts, bool hit) { m_parts[parts].hitAttack = hit; }
	void SetCenter(XMFLOAT3 vCenter) { m_vCenter = vCenter; }
	XMFLOAT3& GetCenter() { return m_vCenter; }
	void SetBBox(XMFLOAT3 vBBox);
	XMFLOAT3& GetBBox() { return m_vBBox; }
	void SetRadius(float fRadius) { m_fRadius = fRadius; }
	float GetRadius() { return m_fRadius; }

	//����������������������������������������
	// �K�w�\�� ���擾
	//����������������������������������������
	TParts& GetParts(int parts) { return m_parts[parts]; }

	//����������������������������������������
	// �f�o�b�O �����蔻��\���p
	//����������������������������������������
	void SetBoundaryType(EBoundaryType bt) { m_bt = bt; }

	//����������������������������������������
	// �����蔻��
	//����������������������������������������
	bool CollisionSphere(CGameObj* pObj);
	bool CollisionAABB(CGameObj* pObj = nullptr);
	int ColliAABBSideNo(CGameObj* pObj = nullptr);	// AABB���m�̂ǂ̖ʂɓ������Ă��邩
	bool CollisionOBB(CGameObj* pObj, XMFLOAT4X4 matrix, XMFLOAT3 center, XMFLOAT3 bbox, bool parts = true, int partsNum = 0);
};
