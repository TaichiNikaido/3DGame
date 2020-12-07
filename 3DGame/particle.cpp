//===========================================================
// particle.cpp
// Author : 管原　司
//===========================================================

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"

//===========================================================
//静的メンバ変数宣言
//===========================================================
LPDIRECT3DTEXTURE9 CParticle::m_pTexture[TEX_TYPE_MAX] = {};

//===========================================================
// コンストラクタ
//===========================================================
CParticle::CParticle()
{
}
//===========================================================
// デストラクタ
//===========================================================
CParticle::~CParticle()
{
}

//===========================================================
// テクスチャの読み込み
//===========================================================
HRESULT CParticle::Load(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/particle001.png", &m_pTexture[TEX_TYPE_1]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/particle002.png", &m_pTexture[TEX_TYPE_2]);
	return S_OK;
}

//===========================================================
// テクスチャの破棄
//===========================================================
void CParticle::Unload(void)
{
	// 3回繰り返す
	for (int nCnt = 0; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			// テクスチャRelease
			m_pTexture[nCnt]->Release();

			// m_pTextureをNULLに
			m_pTexture[nCnt] = NULL;
		}
	}
}

//===========================================================
// 初期化
//===========================================================
HRESULT CParticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TEX_TYPE TexType)
{

	// テクスチャタイプ
	m_TexType = TexType;

	// 初期化
	CBillboard::Init();

	// 位置座標設定
	SetPosition(pos);

	// サイズ設定
	SetSize(size);

	// 向き設定
	SetRotation(rot);

	// カラー設定
	SetColor(col);

	// テクスチャ受け渡し
	BindTexture(m_pTexture[m_TexType]);

	// テクスチャ設定
	SetTex(0.0f, 0.0f, 1.0f, 1.0f);

	return S_OK;
}

//===========================================================
// 終了
//===========================================================
void CParticle::Uninit(void)
{
	// 終了
	CBillboard::Uninit();
}

//===========================================================
// 更新
//===========================================================
void CParticle::Update(void)
{
	// 更新
	CBillboard::Update();
}

//===========================================================
// 描画
//===========================================================
void CParticle::Draw(void)
{
	// 描画
	CBillboard::Draw();
}