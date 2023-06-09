//=======================================================================================
//
// フェード イン/アウト [Fade.cpp]
// Author : ISAKI SUGIURA
//
//=============================================================================
#include "Fade.h"
#include "Polygon.h"
#include "Sound.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 静的メンバ変数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
EFade CFade::m_fade = FADE_NONE;
EScene CFade::m_sceneNext = SCENE_TITLE;
XMFLOAT4 CFade::m_vColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
float CFade::m_fRate = 1.0f / (60.0f * 0.5f);


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	初期化

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CFade::Init()
{
	m_vColor.w = 1.0f;			// 不透明度
	m_fade = FADE_IN;			// 状態
	m_sceneNext = SCENE_TITLE;	// 次のシーン
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	更新

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CFade::Update()
{
	switch (m_fade)
	{
#pragma region 何もしていない
	case FADE_NONE:
		break;
#pragma endregion
#pragma region フェードアウト処理
	case FADE_OUT:
		// // 不透明度を上げる
		m_vColor.w += m_fRate;
		if (m_vColor.w >= 1.0f)
		{
			// フェイドインに移動
			m_vColor.w = 1.0f;
			m_fade = FADE_IN;
			// シーン切替
			CScene::Change(m_sceneNext);
		}
		// 音もフェードアウト
		CSound::SetVolume(1.0f - m_vColor.w);
		break;
#pragma endregion
#pragma region フェードイン処理
	case FADE_IN:
		// 不透明度を下げる
		m_vColor.w -= m_fRate;
		if (m_vColor.w <= 0.0f)
		{
			// フェード処理終了
			m_vColor.w = 0.0f;
			m_fade = FADE_NONE;
		}
		// 音もフェードイン
		CSound::SetVolume(1.0f - m_vColor.w);
		break;
#pragma endregion
	}
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	描画

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CFade::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	CPolygon::SetColor(m_vColor);
	CPolygon::SetTexture(nullptr);
	CPolygon::SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	CPolygon::SetUV(0.0f, 0.0f);
	CPolygon::SetFrameSize(1.0f, 1.0f);
	CPolygon::SetPos(0.0f, 0.0f);
	CPolygon::Draw(pDC);

	CPolygon::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	フェードアウト開始

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CFade::Out(EScene scene, float fSecond)
{
	if (m_fade != FADE_OUT) 
	{
		m_fade = FADE_OUT;
		m_sceneNext = scene;
		m_fRate = 1.0f / (60.0f * fSecond);
	}
}


/*＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜＜

	フェードイン アウト カラー設定

＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞＞*/
void CFade::SetColor(XMFLOAT3 vColor)
{
	m_vColor.x = vColor.x;
	m_vColor.y = vColor.y;
	m_vColor.z = vColor.z;
}
