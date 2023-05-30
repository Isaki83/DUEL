/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	ソードマン
	アニメーション データ [SwordManAnim.h]
	Author : ISAKI SUGIURA

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
#pragma once
#include "Parts.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// マクロ定義
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 攻撃の当たり判定をとるタイミング
#define SM_ATTACK1_S	(60)
#define SM_ATTACK1_E	(100)
#define SM_ATTACK2_S	(30)
#define SM_ATTACK2_E	(90)

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 列挙型
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アニメーション種類
enum EAnim_SwordMan {
	ANIM_SM_NONE = 0,		// アニメーション無

	ANIM_SM_IDLE,			// 待機
	ANIM_SM_RUN,			// 走る
	ANIM_SM_JUMP,			// ジャンプ

	// その場で2撃
	ANIM_SM_ATTACK_00_01,	// 1撃目
	ANIM_SM_ATTACK_00_02,	// 2撃目

	// 遠くから急接近して2連撃
	ANIM_SM_ATTACK_01_01,	// 構える
	ANIM_SM_ATTACK_01_02,	// 近づく
	ANIM_SM_ATTACK_01_03,	// 1撃目
	ANIM_SM_ATTACK_01_04,	// 2撃目
	ANIM_SM_ATTACK_01_05,	// 態勢を戻す

	// 走ってある程度近付いてから、突き状態で急接近して回し斬り
	ANIM_SM_ATTACK_02_01,	// 構える
	ANIM_SM_ATTACK_02_02,	// 突き
	ANIM_SM_ATTACK_02_03,	// 回し斬り
	ANIM_SM_ATTACK_02_04,	// 態勢を戻す

	// 地面に剣を指して広範囲に攻撃
	ANIM_SM_ATTACK_03_01,	// 刺す
	ANIM_SM_ATTACK_03_02,	// 態勢を戻す

	MAX_SM_ANIM,
};


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 構造体定義
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// キーフレーム情報
struct TAnimData_SwordMan {
	int			m_time;					// 時刻(フレーム数)
	XMFLOAT3	m_angle[MAX_SM_PARTS];	// 角度
};


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アニメーション データ クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CSwordManAnimData
{
private:
	int					m_timer;					// フレーム番号
	int					m_anim_index;				// 現在のキーフレーム
	XMFLOAT3			m_angle[MAX_SM_PARTS];	// 現在の角度
	int					m_keyFrameMax;				// キーフレーム数
	TAnimData_SwordMan*	m_pAnimData;				// キーフレーム
	bool				m_bLoop[2];					// 0:ループ再生するか
													// 1:フレームを進めいよいか

public:
	CSwordManAnimData();
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
class CSwordManAnimSet
{
private:
	int					m_anim_count;	// アニメーション データ数
	CSwordManAnimData*	m_pAnimData;	// アニメーション データ
	int					m_anim_set;		// 現在のアニメーション データ
	int					m_prev_anim;
	int					m_blend_wait;

public:
	CSwordManAnimSet();
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