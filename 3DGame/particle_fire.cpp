//===========================================================
// particle_fire.cpp
// Author : 管原　司
//===========================================================

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "particle_fire.h"
//===========================================================
//	コンストラクタ
//===========================================================
CParticle_Fire::CParticle_Fire()
{
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_MinSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMinColor = 0.0f;
}
//===========================================================
//	デストラクタ
//===========================================================
CParticle_Fire::~CParticle_Fire()
{
}
//===========================================================
//	生成関数
//===========================================================
CParticle_Fire * CParticle_Fire::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType)
{
	// CParticle_Fireクラスのポインタ
	CParticle_Fire *pParticle_Fire;

	// メモリ確保
	pParticle_Fire = new CParticle_Fire;

	// 初期化
	pParticle_Fire->Init(pos, size, rot, col, move, TexType);

	// ポインタを返す
	return pParticle_Fire;
}
//===========================================================
//	初期化
//===========================================================
HRESULT CParticle_Fire::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType)
{
	// 初期化
	CParticle::Init(pos, size, rot, col, TexType);

	// 移動量
	m_move = move;

	// サイズ減算値
	m_MinSize = D3DXVECTOR3(1.0f, 1.0f, 0.0f);

	// カラー減算値
	m_fMinColor = 0.005f;

	return S_OK;

}
//===========================================================
//	終了関数
//===========================================================
void CParticle_Fire::Uninit(void)
{
	CParticle::Uninit();
}
//===========================================================
//	更新関数
//===========================================================
void CParticle_Fire::Update(void)
{
	CParticle::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();
	// サイズ取得
	D3DXVECTOR3 size = GetSize();
	// 色取得
	D3DXCOLOR col = GetColor();

	// α減算
	col.a -= m_fMinColor;

	// サイズ減算
	size -= m_MinSize;

	// サイズ設定
	SetSize(size);

	// 色設定
	SetColor(col);

	// 位置更新
	pos += m_move;

	// 位置座標設定
	SetPosition(pos);

	// αが0.0f以下の場合
	if (col.a <= 0.0f)
	{
		// 終了
		Uninit();
		return;
	}
}
//===========================================================
//	描画関数
//===========================================================
void CParticle_Fire::Draw(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画
	CParticle::Draw();

	// 元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}