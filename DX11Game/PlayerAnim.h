/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	メインキャラクター
	アニメーション データ [PlayerAnim.h]
	Author : ISAKI SUGIURA

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
#pragma once
#include "Parts.h"
#include "vector"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// マクロ定義
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 攻撃の当たり判定をとるタイミング
#define MC_ATTACK_01_START	(30)
#define MC_ATTACK_01_END	(40)

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 列挙型
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アニメーション種類
enum EAnim_MC {
	ANIM_MC_NONE = 0,			// アニメーション無

	ANIM_MC_BASE,				// ベース
	ANIM_MC_ATTACK_01,			// 攻撃01

	MAX_MC_ANIM
};


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アニメーション データ クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CPlayerAnimData
{
private:
	// キーフレーム情報
	struct TAnimData_MC {
		int			m_time;					// 時刻(フレーム数)
		XMFLOAT3	m_angle[MAX_MC_PARTS];
	};

	int				m_MaxParts;				// パーツ数
	float			m_timer;				// フレーム番号
	float			m_iTimerAddSpeed;		// フレーム番号を進める速さ
	int				m_anim_index;			// 現在のキーフレーム
	std::vector<XMFLOAT3>		m_angle;	// 現在の角度
	int				m_keyFrameMax;			// キーフレーム数
	TAnimData_MC*	m_pAnimData;			// キーフレーム
	bool			m_bLoop[2];				// 0:ループ再生するか
											// 1:フレームを進めいよいか
	std::vector<int> m_test;

public:
	CPlayerAnimData();
	int Init(const char* path = nullptr);
	void Fin();
	float GetLastTime();
	XMFLOAT3 GetAngle(int partsNo);
	void SetLoop(bool loop) { m_bLoop[0] = loop; }
	void SetmAnimIndex(int index) { m_anim_index = index; }
	void SetTimer(float timer);
	float GetTimer() { return m_timer; }
	bool AddTimer();
	void TimerAddSpeed(float timer) { m_iTimerAddSpeed = timer; }
	int Save(const char* path);
	int Load(const char* path);


private:
	void Lerp();
};

// =========================================================================

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アニメーション クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CPlayerAnimSet
{
private:
	int					m_anim_count;	// アニメーション データ数
	CPlayerAnimData*	m_pAnimData;	// アニメーション データ
	int					m_anim_set;		// 現在のアニメーション データ

public:
	CPlayerAnimSet();
	int Init();
	void Fin();
	int GetCount() { return m_anim_count; }
	void Play(int animNo, float timer = 1.0f, bool loop = true);
	int Get() { return m_anim_set; }
	int GetLastTime(int animNo = -1);
	XMFLOAT3 GetAngle(int partsNo, int animNo = -1);
	void SetTimer(int timer, int animNo = -1);
	float GetTimer(int animNo = -1);
	bool AddTimer(int animNo = -1);
};