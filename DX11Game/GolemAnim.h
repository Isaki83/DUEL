/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	ゴーレム
	アニメーション データ [GolemAnim.h]
	Author : ISAKI SUGIURA

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
#pragma once
#include "Parts.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// マクロ定義
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 攻撃の当たり判定をとるタイミング
#define GOLEM_ATTACK	(50)

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 列挙型
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アニメーション種類
enum EAnim_Golem {
	ANIM_GOLEM_NONE = 0,			// アニメーション無

	ANIM_GOLEM_IDLE,				// 待機状態
	ANIM_GOLEM_WALK,				// 歩く
	ANIM_GOLEM_JUMP,				// ジャンプ
	ANIM_GOLEM_ATTACK,				// 攻撃
	ANIM_GOLEM_DEATH,				// 死亡

	MAX_GOLEM_ANIM
};


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 構造体定義
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// キーフレーム情報
struct TAnimData_Golem {
	int			m_time;					// 時刻(フレーム数)
	XMFLOAT3	m_angle[MAX_GOLEM_PARTS];	// 角度
};


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アニメーション データ クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CGolemAnimData
{
private:
	int					m_timer;					// フレーム番号
	int					m_anim_index;				// 現在のキーフレーム
	XMFLOAT3			m_angle[MAX_GOLEM_PARTS];	// 現在の角度
	int					m_keyFrameMax;				// キーフレーム数
	TAnimData_Golem*	m_pAnimData;				// キーフレーム
	bool				m_bLoop[2];					// 0:ループ再生するか
													// 1:フレームを進めいよいか

public:
	CGolemAnimData();
	int Init(const char* path = nullptr);
	void Fin();
	int GetLastTime();
	XMFLOAT3 GetAngle(int partsNo);
	void SetLoop(bool loop) { m_bLoop[0] = loop; }
	void SetmAnimIndex(int index) { m_anim_index = index; }
	int SetTimer(int timer);
	XMINT2 AddTimer(int timer = 1);
	int Save(const char* path);
	int Load(const char* path);


private:
	void Lerp();
};

//=========================================================================

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アニメーション クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CGolemAnimSet
{
private:
	int					m_anim_count;	// アニメーション データ数
	CGolemAnimData*		m_pAnimData;	// アニメーション データ
	int					m_anim_set;		// 現在のアニメーション データ
	int					m_prev_anim;
	int					m_blend_wait;

public:
	CGolemAnimSet();
	int Init();
	void Fin();
	int GetCount() { return m_anim_count; }
	void Play(int animNo, bool loop = true);
	void BlendPlay(int animNo);
	int Get() { return m_anim_set; }
	int GetLastTime(int animNo = -1);
	XMFLOAT3 GetAngle(int partsNo, int animNo = -1);
	int SetTimer(int timer, int animNo = -1);
	XMINT2 AddTimer(int timer = 1, int animNo = -1);
};