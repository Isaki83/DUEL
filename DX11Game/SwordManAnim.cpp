/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	ソードマン
	アニメーション データ [SwordManAnim.cpp]
	Author : ISAKI SUGIURA

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "SwordManAnim.h"

namespace
{
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	// アニメーション データ ファイル名
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	const char* g_pathAnimData_SwordMan[] = {
		nullptr,

		"data/animdata/SwordMan/SM_Idle.bin",
		"data/animdata/SwordMan/SM_Run.bin",
		"data/animdata/SwordMan/SM_Jump.bin",

		"data/animdata/SwordMan/Attack_00/SM_Attack_00_01.bin",
		"data/animdata/SwordMan/Attack_00/SM_Attack_00_02.bin",

		"data/animdata/SwordMan/Attack_01/SM_Attack_01_01.bin",
		"data/animdata/SwordMan/Attack_01/SM_Attack_01_02.bin",
		"data/animdata/SwordMan/Attack_01/SM_Attack_01_03.bin",
		"data/animdata/SwordMan/Attack_01/SM_Attack_01_04.bin",
		"data/animdata/SwordMan/Attack_01/SM_Attack_01_05.bin",

		"data/animdata/SwordMan/Attack_02/SM_Attack_02_01.bin",
		"data/animdata/SwordMan/Attack_02/SM_Attack_02_02.bin",
		"data/animdata/SwordMan/Attack_02/SM_Attack_02_03.bin",
		"data/animdata/SwordMan/Attack_02/SM_Attack_02_04.bin",

		"data/animdata/SwordMan/Attack_03/SM_Attack_03_01.bin",
		"data/animdata/SwordMan/Attack_03/SM_Attack_03_02.bin",
	};

	const int g_BlendWait = 5;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コンストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CSwordManAnimData::CSwordManAnimData()
{
	m_timer = 0;
	m_anim_index = 0;

	m_keyFrameMax = 0;
	m_pAnimData = nullptr;

	for (int i = 0; i < 2; i++) { m_bLoop[i] = true; }
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
int CSwordManAnimData::Init(const char* path)
{
	Fin();
	int load = 0;
	if (path)
		load = Load(path);
	if (load <= 0) {
		// 読み込み失敗時はダミーデータで埋める
		m_keyFrameMax = 2;
		m_pAnimData = new TAnimData_SwordMan[m_keyFrameMax];
		for (int i = 0; i < m_keyFrameMax; ++i) {
			m_pAnimData[i].m_time = i * 10;
			for (int j = 0; j < MAX_SM_PARTS; ++j) {
				m_pAnimData[i].m_angle[j] = XMFLOAT3(0, 0, 0);
			}
		}
	}
	return load;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	終了処理

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CSwordManAnimData::Fin()
{
	SAFE_DELETE_ARRAY(m_pAnimData);
	m_keyFrameMax = 0;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	アニメーション全体フレーム数取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
int CSwordManAnimData::GetLastTime()
{
	if (m_keyFrameMax <= 0 || !m_pAnimData) {
		return 0;
	}
	return m_pAnimData[m_keyFrameMax - 1].m_time;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	現在の角度

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
XMFLOAT3 CSwordManAnimData::GetAngle(int partsNo)
{
	if (partsNo >= 0 && partsNo < MAX_SM_PARTS) {
		return m_angle[partsNo];
	}
	return XMFLOAT3(0, 0, 0);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	フレーム番号設定

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
int CSwordManAnimData::SetTimer(int timer)
{
	int eoa = 0;
	// 時間とフレームを進める
	m_timer = timer;
	while (m_timer >= m_pAnimData[m_anim_index + 1].m_time) {
		// 次のフレームへ
		m_anim_index++;
		if (m_anim_index >= m_keyFrameMax - 1) {
			m_anim_index = 0;	// フレーム先頭へ
			m_timer = 0;
			return eoa = 1;
			break;
		}
	}
	Lerp();
	return eoa;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	フレーム番号更新

	戻り値1 :	0 > アニメーションが終わってない
				1 > アニメーションが終わっている
	戻り値2 :	アニメーション経過フレーム数

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
XMINT2 CSwordManAnimData::AddTimer(int timer)
{
	int eoa = 0;
	// 時間とフレームを進める
	m_timer += timer;
	while (m_timer >= m_pAnimData[m_anim_index + 1].m_time)
	{
		// 次のフレームへ
		if (m_bLoop[1]) { m_anim_index++; }
		if (m_anim_index >= m_keyFrameMax - 1) 
		{
			if (m_bLoop[0]) { m_anim_index = 0; }	// フレーム先頭へ
			else { m_bLoop[1] = false; }
			m_timer = 0;
			eoa = 1;
			return XMINT2(eoa, m_timer);
			break;
		}
	}
	Lerp();
	return XMINT2(eoa, m_timer);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	アニメーション データ書き込み

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
int CSwordManAnimData::Save(const char* path)
{
	int nCount = 0;
	FILE* fp = fopen(path, "wb");
	if (fp) {
		fwrite(&m_keyFrameMax, sizeof(m_keyFrameMax), 1, fp);
		fwrite(m_pAnimData, sizeof(TAnimData_SwordMan), m_keyFrameMax, fp);
		fclose(fp);
		nCount = m_keyFrameMax;
	}
	return nCount;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	アニメーション データ読み込み

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
int CSwordManAnimData::Load(const char* path)
{
	int nCount = 0;
	FILE* fp = fopen(path, "rb");
	if (fp) {
		if (fread(&nCount, sizeof(nCount), 1, fp) > 0 && nCount > 0) {
			SAFE_DELETE_ARRAY(m_pAnimData);
			m_pAnimData = new TAnimData_SwordMan[nCount];
			fread(m_pAnimData, sizeof(TAnimData_SwordMan), nCount, fp);
			m_keyFrameMax = nCount;
		}
		fclose(fp);
	}
	return nCount;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	線形補間

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CSwordManAnimData::Lerp()
{
	// 時間から角度を線形補間で求める
	float dt = (float)(m_timer - m_pAnimData[m_anim_index].m_time) /
		(m_pAnimData[m_anim_index + 1].m_time - m_pAnimData[m_anim_index].m_time);
	for (int i = 0; i < MAX_SM_PARTS; ++i) {
		float dg = m_pAnimData[m_anim_index + 1].m_angle[i].x - m_pAnimData[m_anim_index].m_angle[i].x;
		m_angle[i].x = m_pAnimData[m_anim_index].m_angle[i].x + dg * dt;
		dg = m_pAnimData[m_anim_index + 1].m_angle[i].y - m_pAnimData[m_anim_index].m_angle[i].y;
		m_angle[i].y = m_pAnimData[m_anim_index].m_angle[i].y + dg * dt;
		dg = m_pAnimData[m_anim_index + 1].m_angle[i].z - m_pAnimData[m_anim_index].m_angle[i].z;
		m_angle[i].z = m_pAnimData[m_anim_index].m_angle[i].z + dg * dt;
	}
}


//=========================================================================


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	コンストラクタ

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
CSwordManAnimSet::CSwordManAnimSet()
{
	m_anim_count = 0;
	m_pAnimData = nullptr;
	m_anim_set = 0;
	m_prev_anim = 0;
	m_blend_wait = 0;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
int CSwordManAnimSet::Init()
{
	Fin();
	m_pAnimData = new CSwordManAnimData[_countof(g_pathAnimData_SwordMan)];
	m_anim_count = 1;
	m_pAnimData[0].Init();	// 0だけエラーチェック無し
	for (int i = 1; i < _countof(g_pathAnimData_SwordMan); ++i) {
		if (m_pAnimData[i].Init(g_pathAnimData_SwordMan[i]) <= 0) {
			break;
		}
		++m_anim_count;
	}
	return m_anim_count;	// アニメーション数
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	終了処理

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CSwordManAnimSet::Fin()
{
	SAFE_DELETE_ARRAY(m_pAnimData);
	m_anim_count = 0;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	アニメーション切替

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CSwordManAnimSet::Play(int animNo, bool loop)
{
	if (animNo >= 0 && animNo < m_anim_count) 
	{
		if (m_anim_set != animNo) 
		{
			m_anim_set = animNo;
			m_pAnimData[m_anim_set].SetmAnimIndex(0);
			m_pAnimData[m_anim_set].SetLoop(loop);
		}
	}
}
void CSwordManAnimSet::BlendPlay(int animNo)
{
	if (animNo >= 0 && animNo < m_anim_count) {
		if (m_anim_set != animNo) {
			m_prev_anim = m_anim_set;
			m_anim_set = animNo;
			m_blend_wait = g_BlendWait;
		}
	}
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	最終フレームNo.取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
int CSwordManAnimSet::GetLastTime(int animNo)
{
	if (animNo >= 0 && animNo < m_anim_count) {
		return m_pAnimData[animNo].GetLastTime();
	}
	if (m_anim_set >= 0 && m_anim_set < m_anim_count) {
		return m_pAnimData[m_anim_set].GetLastTime();
	}
	return 0;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	パーツ毎の角度取得

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
XMFLOAT3 CSwordManAnimSet::GetAngle(int partsNo, int animNo)
{
	if (animNo >= 0 && animNo < m_anim_count) {
		return m_pAnimData[animNo].GetAngle(partsNo);
	}
	if (m_anim_set >= 0 && m_anim_set < m_anim_count) {
		//return m_pAnimData[m_anim_set].GetAngle(partsNo);
		// ここでモーション ブレンディングを行う。
		// ※ここでは角度を混ぜ合わせているが、実際に混ぜ合わせる値
		//   は、キーフレームにどのような情報を持っているかで異なる。
		XMFLOAT3 angle = m_pAnimData[m_anim_set].GetAngle(partsNo);
		if (m_blend_wait > 0) {
			XMFLOAT3 prev_angle = m_pAnimData[m_prev_anim].GetAngle(partsNo);
			float ratio = (float)m_blend_wait / g_BlendWait;
			angle.x = angle.x * (1.0f - ratio) + prev_angle.x * ratio;
			angle.y = angle.y * (1.0f - ratio) + prev_angle.y * ratio;
			angle.z = angle.z * (1.0f - ratio) + prev_angle.z * ratio;
		}
		return angle;
	}
	return XMFLOAT3(0, 0, 0);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	フレーム番号設定

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
int CSwordManAnimSet::SetTimer(int timer, int animNo)
{
	if (m_blend_wait > 0) {
		--m_blend_wait;
		m_pAnimData[m_prev_anim].SetTimer(timer);
	}
	if (animNo >= 0 && animNo < m_anim_count) {
		return m_pAnimData[animNo].SetTimer(timer);
	}
	if (m_anim_set >= 0 && m_anim_set < m_anim_count) {
		return m_pAnimData[m_anim_set].SetTimer(timer);
	}
	return 1;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	フレーム番号更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
XMINT2 CSwordManAnimSet::AddTimer(int timer, int animNo)
{
	if (m_blend_wait > 0) {
		--m_blend_wait;
		m_pAnimData[m_prev_anim].AddTimer(timer);
	}
	if (animNo >= 0 && animNo < m_anim_count) {
		return m_pAnimData[animNo].AddTimer(timer);
	}
	if (m_anim_set >= 0 && m_anim_set < m_anim_count) {
		return m_pAnimData[m_anim_set].AddTimer(timer);
	}
	return XMINT2(1, 0);
}
