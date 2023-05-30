//=============================================================================
//
// 2DObj [2DObj.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "main.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 列挙型
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
enum ETexture
{
	TEX_MOUSECURSOR = 0,	// マウスカーソル

	TEX_BG_FRAME,			// 背景枠
	TEX_BG_SELECT,			// 背景(選択画面のパラメータ部分)

	TEX_BUTTON_NOW_SELE,	// ボタン
	TEX_BUTTON_BG_01,		// ボタン
	TEX_BUTTON_RETURN,		// 戻るボタン

	TEX_WORD_FONT,			// 文字(アルファベット大文字、数字のみ)
	TEX_WORD_DUEL,			// DUEL(文字)
	TEX_WORD_START,			// START(文字)
	TEX_WORD_WEAPON,		// 武器(文字)
	TEX_WORD_MONSTER,		// モンスター(文字)
	TEX_WORD_DUEL_START,	// 戦闘開始(文字)
	TEX_WORD_DECISION,		// 決定(文字)
	TEX_WORD_EXIT,			// 終了(文字)
	TEX_WORD_WSWORD,		// 木剣(文字)
	TEX_WORD_AXE,			// 斧(文字)
	TEX_WORD_LSWORD,		// 大剣(文字)
	TEX_WORD_GOLEM,			// ゴーレム(文字)
	TEX_WORD_SWORDER,		// ソーダ―(文字)
	TEX_WORD_POWER,			// 攻撃力(文字)
	TEX_WORD_SPEED,			// スピード(文字)

	TEX_HP_GAUGE_BG,		// HPゲージ(背景)
	TEX_HP_GAUGE_DMG,		// HPゲージ(ダメージ)
	TEX_HP_GAUGE,			// HPゲージ

	TEX_ICON_FRAME,			// フレーム
	TEX_ICON_WSWORD,		// 木剣(アイコン)
	TEX_ICON_AXE,			// 斧(アイコン)
	TEX_ICON_LSWORD,		// 大剣(アイコン)
	TEX_ICON_GOLEM,			// ゴーレム(アイコン)
	TEX_ICON_SM,			// ソードマン(アイコン)

	TEX_BARRIER,			// バリア

	MAX_TEXTURE,
};
enum E2DObjType
{	// オブジェクト型
	GOT_2DOBJ = 0,			// 型無し
	GOT_BG,
	GOT_DAMAGE,				// ダメージ
	GOT_TITLE_LOGO,			// タイトル ロゴ
	GOT_BUTTON_DECISION,	// 決定			ボタン
	GOT_BUTTON_EXIT,		// 終了			ボタン
	GOT_BUTTON_RETURN,		// 戻る			ボタン
	GOT_BUTTON_START,		// スタート		ボタン
	GOT_BUTTON_WEAPON,		// 武器			ボタン
	GOT_BUTTON_MONSTER,		// モンスター	ボタン
	GOT_BUTTON_DUEL_START,	// 戦闘開始		ボタン
	GOT_BUTTON_ARROW,		// 矢印			ボタン
	GOT_HP_GAUGE_E,			// HPゲージ
	GOT_HP_GAUGE_PLAYER,	// HPゲージ(プレイヤー)
	GOT_MOUSECURSOR,		// マウスカーソル
	GOT_ICON,				// アイコン
	GOT_BARRIER,			// バリア
	GOT_PARM,				// パラメーター

	MAX_2DOBJTYPE,
};
enum E2DObjSubType
{	// オブジェクト型
	GOT_2DOBJSUB = 0,		// 型無し

	GOTSUB_RIGHT = 1,		// 右
	GOTSUB_LEFT,			// 左

	GOTSUB_WSWORD = 1,		// 木剣
	GOTSUB_AXE,				// 斧
	GOTSUB_LSWORD,			// 大剣
	MAX_SUB_WEAPON_ICON,

	GOTSUB_GOLEM = 1,		// ゴーレム
	GOTSUB_SM,				// ソードマン
	MAX_SUB_ENEMY_ICON,
};


class CScene;
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 2Dオブジェクト 継承元クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class C2DObj
{
private:
	C2DObj* m_pBack;		// 前のオブジェクト
	C2DObj* m_pNext;		// 次のオブジェクト

protected:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// オブジェクト識別
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	E2DObjType m_id;		// オブジェクト型
	E2DObjSubType m_subid;

	CScene* m_pScene;		// 所属シーン

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	XMFLOAT2 m_fPos;		// 座標
	XMFLOAT2 m_fSize;		// 拡縮
	XMFLOAT4 m_fColor;		// 色

	XMFLOAT2 m_fCenter;		// 中心
	XMFLOAT2 m_fBBox;		// サイズ

	bool m_bVisible;		// 表示フラグ

	static ID3D11ShaderResourceView* m_pTexture[MAX_TEXTURE];

public:
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	C2DObj(CScene* pScene);
	virtual ~C2DObj(void);

	virtual HRESULT Init();		// 初期化
	virtual void Update();		// 更新
	virtual void Draw();		// 描画
	virtual void Fin();			// 終了処理

	static HRESULT InitAll(C2DObj* pTop);
	static void UpdateAll(C2DObj*& pTop);
	static void DrawAll(C2DObj* pTop);
	static void FinAll(C2DObj* pTop);


	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// オブジェクト識別
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	E2DObjType GetID() { return m_id; }
	void SetSubID(E2DObjSubType id) { m_subid = id; }
	E2DObjSubType GetSubID() { return m_subid; }
	C2DObj* GetNext() { return m_pNext; }

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 位置・拡縮・色
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 位置
	void SetPos(XMFLOAT2 fPos) { m_fPos = fPos; }
	XMFLOAT2& GetPos() { return m_fPos; }
	// 拡縮
	void SetSize(XMFLOAT2 fSize) { m_fSize = fSize; }
	XMFLOAT2& GetSize() { return m_fSize; }
	// 色
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
	// 位置(当たり判定)
	void SetCenter(XMFLOAT2 fCenter) { m_fCenter = fCenter; }
	XMFLOAT2& GetCenter() { return m_fCenter; }
	// 拡縮(当たり判定)
	void SetBBox(XMFLOAT2 fBBox) { m_fBBox = fBBox; }
	XMFLOAT2& GetBBox() { return m_fBBox; }

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 当たり判定
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	bool CollisionAABB(C2DObj* pObjA, C2DObj* pObjB);


	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// 基本
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	static HRESULT LoadAll();
	static void ReleaseAll();
};
