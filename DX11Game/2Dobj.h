//=============================================================================
//
// 2DObj [2DObj.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "main.h"

//
// ñ^
//
enum ETexture
{
	TEX_MOUSECURSOR = 0,	// }EXJ[\

	TEX_BG_FRAME,			// wig
	TEX_BG_SELECT,			// wi(IðæÊÌp[^ª)

	TEX_BUTTON_NOW_SELE,	// {^
	TEX_BUTTON_BG_01,		// {^
	TEX_BUTTON_RETURN,		// ßé{^

	TEX_WORD_FONT,			// ¶(At@xbgå¶AÌÝ)
	TEX_WORD_DUEL,			// DUEL(¶)
	TEX_WORD_START,			// START(¶)
	TEX_WORD_WEAPON,		// í(¶)
	TEX_WORD_MONSTER,		// X^[(¶)
	TEX_WORD_DUEL_START,	// í¬Jn(¶)
	TEX_WORD_DECISION,		// è(¶)
	TEX_WORD_EXIT,			// I¹(¶)
	TEX_WORD_WSWORD,		// Ø(¶)
	TEX_WORD_AXE,			// (¶)
	TEX_WORD_LSWORD,		// å(¶)
	TEX_WORD_GOLEM,			// S[(¶)
	TEX_WORD_SWORDER,		// \[_\(¶)
	TEX_WORD_POWER,			// UÍ(¶)
	TEX_WORD_SPEED,			// Xs[h(¶)

	TEX_HP_GAUGE_BG,		// HPQ[W(wi)
	TEX_HP_GAUGE_DMG,		// HPQ[W(_[W)
	TEX_HP_GAUGE,			// HPQ[W

	TEX_ICON_FRAME,			// t[
	TEX_ICON_WSWORD,		// Ø(ACR)
	TEX_ICON_AXE,			// (ACR)
	TEX_ICON_LSWORD,		// å(ACR)
	TEX_ICON_GOLEM,			// S[(ACR)
	TEX_ICON_SM,			// \[h}(ACR)

	TEX_BARRIER,			// oA

	MAX_TEXTURE,
};
enum E2DObjType
{	// IuWFNg^
	GOT_2DOBJ = 0,			// ^³µ
	GOT_BG,
	GOT_DAMAGE,				// _[W
	GOT_TITLE_LOGO,			// ^Cg S
	GOT_BUTTON_DECISION,	// è			{^
	GOT_BUTTON_EXIT,		// I¹			{^
	GOT_BUTTON_RETURN,		// ßé			{^
	GOT_BUTTON_START,		// X^[g		{^
	GOT_BUTTON_WEAPON,		// í			{^
	GOT_BUTTON_MONSTER,		// X^[	{^
	GOT_BUTTON_DUEL_START,	// í¬Jn		{^
	GOT_BUTTON_ARROW,		// îó			{^
	GOT_HP_GAUGE_E,			// HPQ[W
	GOT_HP_GAUGE_PLAYER,	// HPQ[W(vC[)
	GOT_MOUSECURSOR,		// }EXJ[\
	GOT_ICON,				// ACR
	GOT_BARRIER,			// oA
	GOT_PARM,				// p[^[

	MAX_2DOBJTYPE,
};
enum E2DObjSubType
{	// IuWFNg^
	GOT_2DOBJSUB = 0,		// ^³µ

	GOTSUB_RIGHT = 1,		// E
	GOTSUB_LEFT,			// ¶

	GOTSUB_WSWORD = 1,		// Ø
	GOTSUB_AXE,				// 
	GOTSUB_LSWORD,			// å
	MAX_SUB_WEAPON_ICON,

	GOTSUB_GOLEM = 1,		// S[
	GOTSUB_SM,				// \[h}
	MAX_SUB_ENEMY_ICON,
};


class CScene;
//
// 2DIuWFNg p³³NX
//
class C2DObj
{
private:
	C2DObj* m_pBack;		// OÌIuWFNg
	C2DObj* m_pNext;		// ÌIuWFNg

protected:
	//
	// IuWFNg¯Ê
	//
	E2DObjType m_id;		// IuWFNg^
	E2DObjSubType m_subid;

	CScene* m_pScene;		// ®V[

	//
	// î{
	//
	XMFLOAT2 m_fPos;		// ÀW
	XMFLOAT2 m_fSize;		// gk
	XMFLOAT4 m_fColor;		// F

	XMFLOAT2 m_fCenter;		// S
	XMFLOAT2 m_fBBox;		// TCY

	bool m_bVisible;		// \¦tO

	static ID3D11ShaderResourceView* m_pTexture[MAX_TEXTURE];

public:
	//
	// î{
	//
	C2DObj(CScene* pScene);
	virtual ~C2DObj(void);

	virtual HRESULT Init();		// ú»
	virtual void Update();		// XV
	virtual void Draw();		// `æ
	virtual void Fin();			// I¹

	static HRESULT InitAll(C2DObj* pTop);
	static void UpdateAll(C2DObj*& pTop);
	static void DrawAll(C2DObj* pTop);
	static void FinAll(C2DObj* pTop);


	//
	// IuWFNg¯Ê
	//
	E2DObjType GetID() { return m_id; }
	void SetSubID(E2DObjSubType id) { m_subid = id; }
	E2DObjSubType GetSubID() { return m_subid; }
	C2DObj* GetNext() { return m_pNext; }

	//
	// ÊuEgkEF
	//
	// Êu
	void SetPos(XMFLOAT2 fPos) { m_fPos = fPos; }
	XMFLOAT2& GetPos() { return m_fPos; }
	// gk
	void SetSize(XMFLOAT2 fSize) { m_fSize = fSize; }
	XMFLOAT2& GetSize() { return m_fSize; }
	// F
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
	// Êu(½è»è)
	void SetCenter(XMFLOAT2 fCenter) { m_fCenter = fCenter; }
	XMFLOAT2& GetCenter() { return m_fCenter; }
	// gk(½è»è)
	void SetBBox(XMFLOAT2 fBBox) { m_fBBox = fBBox; }
	XMFLOAT2& GetBBox() { return m_fBBox; }

	//
	// ½è»è
	//
	bool CollisionAABB(C2DObj* pObjA, C2DObj* pObjB);


	//
	// î{
	//
	static HRESULT LoadAll();
	static void ReleaseAll();
};
