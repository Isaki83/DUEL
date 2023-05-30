/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	ヒットストップ[HitStop.cpp]
	Author : ISAKI SUGIURA

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
#include "HitStop.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 静的メンバ変数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
bool	CHitStop::m_bIsHitStop = false;
int		CHitStop::m_iAddTime = 0;
int		CHitStop::m_iFrameSpeed = 0;


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	ヒットストップ
	止まるときは	false
	動くときは	true

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
bool CHitStop::HitStop()
{
	// ヒットストップが始まってからの時間
	static int AddTime = 0;
	AddTime++;

	// 時間が終わると変数を初期値に戻して常にtrue
	if (m_iAddTime < AddTime)
	{
		m_iAddTime = 0;
		m_iFrameSpeed = 0;
		m_bIsHitStop = false;
		AddTime = 0;
	}

	// フレームがスピードより大きくなったら動く
	if (m_iFrameSpeed <= AddTime % (m_iFrameSpeed + 1)) { return true; }

	// 動かさない
	return false;
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	ヒットストップ開始
	第一引数 : 止めるフレーム数
	第二引数 : 何フレームおきに動かすか

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CHitStop::Set(int time, int speed)
{
	if (m_bIsHitStop) { return; }

	m_iAddTime = time;
	m_iFrameSpeed = speed;
	m_bIsHitStop = true;
}