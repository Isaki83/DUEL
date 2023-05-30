/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	パーツ情報 [Parts.h]
	Author : ISAKI SUGIURA

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
#pragma once
#include "main.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// マクロ定義
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#define MAX_PARTS	(15)

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 列挙型
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// --- パーツ種別 ---
// メインキャラクター(自機)
enum EParts_MC
{
	PARTS_MC_LOOT = 0,		// ルート
	PARTS_MC_BODY,			// 胴
	PARTS_MC_ARM_UP_R,		// 右腕-上
	PARTS_MC_ARM_DOWN_R,	// 右腕-下
	PARTS_MC_HAND_R,		// 右手

	MAX_MC_PARTS
};
// ゴーレム(敵)
enum EParts_Golem
{
	PARTS_GOLEM_LOOT = 0,	// ルート
	PARTS_GOLEM_HIP,		// 腰
	PARTS_GOLEM_BODY,		// 胴
	PARTS_GOLEM_HEAD,		// 頭
	PARTS_GOLEM_ARM_UP_R,	// 右腕-上
	PARTS_GOLEM_ARM_DOWN_R,	// 右腕-下
	PARTS_GOLEM_ARM_UP_L,	// 左腕-上
	PARTS_GOLEM_ARM_DOWN_L,	// 左腕-下
	PARTS_GOLEM_LEG_UP_R,	// 右足-上
	PARTS_GOLEM_LEG_DOWN_R,	// 右足-下
	PARTS_GOLEM_LEG_UP_L,	// 左足-上
	PARTS_GOLEM_LEG_DOWN_L,	// 左足-下
	MAX_GOLEM_PARTS,
};
// SwordMan(敵)
enum EParts_SwordMan
{
	PARTS_SM_LOOT = 0,	// ルート
	PARTS_SM_HIP,		// 腰
	PARTS_SM_BODY,		// 胴
	PARTS_SM_HEAD,		// 頭
	PARTS_SM_ARM_UP_R,	// 右腕-上
	PARTS_SM_ARM_DOWN_R,// 右腕-下
	PARTS_SM_HAND_R,	// 右手
	PARTS_SM_ARM_UP_L,	// 左腕-上
	PARTS_SM_ARM_DOWN_L,// 左腕-下
	PARTS_SM_HAND_L,	// 左手
	PARTS_SM_LEG_UP_R,	// 右足-上
	PARTS_SM_LEG_DOWN_R,// 右足-下
	PARTS_SM_LEG_UP_L,	// 左足-上
	PARTS_SM_LEG_DOWN_L,// 左足-下
	PARTS_BLACK_SWORD,	// 黒剣
	MAX_SM_PARTS,
};


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 構造体定義
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// パーツ初期データ
struct TPartsData
{
	int			parent;		// 親パーツ番号
	int			model;		// モデル番号
	XMFLOAT3	off;		// オフセット値
	float		DmgRatio;	// ダメージ倍率
};

// パーツ情報
struct TParts
{
	bool		use;		// 使われているか
	int			parent;		// 親パーツ番号
	int			model;		// モデル番号
	XMFLOAT3	off;		// オフセット値
	XMFLOAT3	angle;		// 角度
	XMFLOAT4X4	matrix;		// 回転マトリックス
	XMFLOAT3	center;		// 境界ボックス 中心座標
	XMFLOAT3	bbox;		// 境界ボックス 大きさ
	float		DmgRatio;	// ダメージ倍率
	bool		hitDefence;	// 当たっているか(受け)
	bool		hitAttack;	// 当たっているか(攻め)
	int			num;		// パーツ判別用
};
