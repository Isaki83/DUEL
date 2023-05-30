//=============================================================================
//
// 2DObj [2DObj.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "main.h"

//����������������������������������������
// �񋓌^
//����������������������������������������
enum ETexture
{
	TEX_MOUSECURSOR = 0,	// �}�E�X�J�[�\��

	TEX_BG_FRAME,			// �w�i�g
	TEX_BG_SELECT,			// �w�i(�I����ʂ̃p�����[�^����)

	TEX_BUTTON_NOW_SELE,	// �{�^��
	TEX_BUTTON_BG_01,		// �{�^��
	TEX_BUTTON_RETURN,		// �߂�{�^��

	TEX_WORD_FONT,			// ����(�A���t�@�x�b�g�啶���A�����̂�)
	TEX_WORD_DUEL,			// DUEL(����)
	TEX_WORD_START,			// START(����)
	TEX_WORD_WEAPON,		// ����(����)
	TEX_WORD_MONSTER,		// �����X�^�[(����)
	TEX_WORD_DUEL_START,	// �퓬�J�n(����)
	TEX_WORD_DECISION,		// ����(����)
	TEX_WORD_EXIT,			// �I��(����)
	TEX_WORD_WSWORD,		// �،�(����)
	TEX_WORD_AXE,			// ��(����)
	TEX_WORD_LSWORD,		// �匕(����)
	TEX_WORD_GOLEM,			// �S�[����(����)
	TEX_WORD_SWORDER,		// �\�[�_�\(����)
	TEX_WORD_POWER,			// �U����(����)
	TEX_WORD_SPEED,			// �X�s�[�h(����)

	TEX_HP_GAUGE_BG,		// HP�Q�[�W(�w�i)
	TEX_HP_GAUGE_DMG,		// HP�Q�[�W(�_���[�W)
	TEX_HP_GAUGE,			// HP�Q�[�W

	TEX_ICON_FRAME,			// �t���[��
	TEX_ICON_WSWORD,		// �،�(�A�C�R��)
	TEX_ICON_AXE,			// ��(�A�C�R��)
	TEX_ICON_LSWORD,		// �匕(�A�C�R��)
	TEX_ICON_GOLEM,			// �S�[����(�A�C�R��)
	TEX_ICON_SM,			// �\�[�h�}��(�A�C�R��)

	TEX_BARRIER,			// �o���A

	MAX_TEXTURE,
};
enum E2DObjType
{	// �I�u�W�F�N�g�^
	GOT_2DOBJ = 0,			// �^����
	GOT_BG,
	GOT_DAMAGE,				// �_���[�W
	GOT_TITLE_LOGO,			// �^�C�g�� ���S
	GOT_BUTTON_DECISION,	// ����			�{�^��
	GOT_BUTTON_EXIT,		// �I��			�{�^��
	GOT_BUTTON_RETURN,		// �߂�			�{�^��
	GOT_BUTTON_START,		// �X�^�[�g		�{�^��
	GOT_BUTTON_WEAPON,		// ����			�{�^��
	GOT_BUTTON_MONSTER,		// �����X�^�[	�{�^��
	GOT_BUTTON_DUEL_START,	// �퓬�J�n		�{�^��
	GOT_BUTTON_ARROW,		// ���			�{�^��
	GOT_HP_GAUGE_E,			// HP�Q�[�W
	GOT_HP_GAUGE_PLAYER,	// HP�Q�[�W(�v���C���[)
	GOT_MOUSECURSOR,		// �}�E�X�J�[�\��
	GOT_ICON,				// �A�C�R��
	GOT_BARRIER,			// �o���A
	GOT_PARM,				// �p�����[�^�[

	MAX_2DOBJTYPE,
};
enum E2DObjSubType
{	// �I�u�W�F�N�g�^
	GOT_2DOBJSUB = 0,		// �^����

	GOTSUB_RIGHT = 1,		// �E
	GOTSUB_LEFT,			// ��

	GOTSUB_WSWORD = 1,		// �،�
	GOTSUB_AXE,				// ��
	GOTSUB_LSWORD,			// �匕
	MAX_SUB_WEAPON_ICON,

	GOTSUB_GOLEM = 1,		// �S�[����
	GOTSUB_SM,				// �\�[�h�}��
	MAX_SUB_ENEMY_ICON,
};


class CScene;
//����������������������������������������
// 2D�I�u�W�F�N�g �p�����N���X
//����������������������������������������
class C2DObj
{
private:
	C2DObj* m_pBack;		// �O�̃I�u�W�F�N�g
	C2DObj* m_pNext;		// ���̃I�u�W�F�N�g

protected:
	//����������������������������������������
	// �I�u�W�F�N�g����
	//����������������������������������������
	E2DObjType m_id;		// �I�u�W�F�N�g�^
	E2DObjSubType m_subid;

	CScene* m_pScene;		// �����V�[��

	//����������������������������������������
	// ��{
	//����������������������������������������
	XMFLOAT2 m_fPos;		// ���W
	XMFLOAT2 m_fSize;		// �g�k
	XMFLOAT4 m_fColor;		// �F

	XMFLOAT2 m_fCenter;		// ���S
	XMFLOAT2 m_fBBox;		// �T�C�Y

	bool m_bVisible;		// �\���t���O

	static ID3D11ShaderResourceView* m_pTexture[MAX_TEXTURE];

public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	C2DObj(CScene* pScene);
	virtual ~C2DObj(void);

	virtual HRESULT Init();		// ������
	virtual void Update();		// �X�V
	virtual void Draw();		// �`��
	virtual void Fin();			// �I������

	static HRESULT InitAll(C2DObj* pTop);
	static void UpdateAll(C2DObj*& pTop);
	static void DrawAll(C2DObj* pTop);
	static void FinAll(C2DObj* pTop);


	//����������������������������������������
	// �I�u�W�F�N�g����
	//����������������������������������������
	E2DObjType GetID() { return m_id; }
	void SetSubID(E2DObjSubType id) { m_subid = id; }
	E2DObjSubType GetSubID() { return m_subid; }
	C2DObj* GetNext() { return m_pNext; }

	//����������������������������������������
	// �ʒu�E�g�k�E�F
	//����������������������������������������
	// �ʒu
	void SetPos(XMFLOAT2 fPos) { m_fPos = fPos; }
	XMFLOAT2& GetPos() { return m_fPos; }
	// �g�k
	void SetSize(XMFLOAT2 fSize) { m_fSize = fSize; }
	XMFLOAT2& GetSize() { return m_fSize; }
	// �F
	void SetColor(XMFLOAT4 fColor) { m_fColor = fColor; }
	XMFLOAT4& GetColor() { return m_fColor; }
	void SetColorR(float fR) { m_fColor.x = fR; }
	float& GetColorR() { return m_fColor.x; }
	void SetColorG(float fG) { m_fColor.y = fG; }
	float& GetColorG() { return m_fColor.y; }
	void SetColorB(float fB) { m_fColor.z = fB; }
	float& GetColorB() { return m_fColor.z; }
	void SetColorA(float fA) { m_fColor.w = fA; }
	float& GetColorA() { return m_fColor.w; }
	// �ʒu(�����蔻��)
	void SetCenter(XMFLOAT2 fCenter) { m_fCenter = fCenter; }
	XMFLOAT2& GetCenter() { return m_fCenter; }
	// �g�k(�����蔻��)
	void SetBBox(XMFLOAT2 fBBox) { m_fBBox = fBBox; }
	XMFLOAT2& GetBBox() { return m_fBBox; }

	//����������������������������������������
	// �����蔻��
	//����������������������������������������
	bool CollisionAABB(C2DObj* pObjA, C2DObj* pObjB);


	//����������������������������������������
	// ��{
	//����������������������������������������
	static HRESULT LoadAll();
	static void ReleaseAll();
};
