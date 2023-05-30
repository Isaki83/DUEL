//=============================================================================
//
// ランダム [Random.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include <vector>


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 行動の重み付けを行う構造体
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
struct ActionWeight
{
	int action;		// 行動の種類
	float weight;	// 重み
};


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ランダム クラス
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class CRandom
{
public:
	CRandom();
	~CRandom();
	// 重み付きランダム選択アルゴリズム
	int WeightRandom(const std::vector<ActionWeight>& actionWeights);
};