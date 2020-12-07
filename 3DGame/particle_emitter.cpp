//===========================================================
// particleemitter.cpp
// Author : 管原　司
//===========================================================
//===========================================================
// インクルードファイル
//===========================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "particle_fire.h"
#include "particle_emitter.h"

#define PARTICLE__FIRE_SIZE_X (200)
#define PARTICLE__FIRE_SIZE_Y (200)

//===========================================================
// コンストラクタ
//===========================================================
CParticle_Emitter::CParticle_Emitter()
{
	m_nCount = 0;
}
//===========================================================
// デストラクタ
//===========================================================
CParticle_Emitter::~CParticle_Emitter()
{
}
//===========================================================
// 生成関数
//===========================================================
CParticle_Emitter * CParticle_Emitter::Create()
{
	// CParticle_Emitterクラスのポインタ
	CParticle_Emitter *pParticle_Emitter;

	// メモリ確保
	pParticle_Emitter = new CParticle_Emitter;

	// 初期化
	pParticle_Emitter->Init();

	return pParticle_Emitter;
}
//===========================================================
// 初期化関数
//===========================================================
HRESULT CParticle_Emitter::Init()
{
	return S_OK;
}
//===========================================================
// 終了関数
//===========================================================
void CParticle_Emitter::Uninit(void)
{
	// 終了
	Release();
}
//===========================================================
// 更新関数
//===========================================================
void CParticle_Emitter::Update(void)
{
	m_nCount++;
	// カウントが2あまり0の時
	if (m_nCount % 2 == 0)
	{
		float fAngle = float(rand() % 150 + 30);
		float fRot = float(rand() % 360 - 180);
		float fFireSpeed = float(rand() % 15);
		fFireSpeed = fFireSpeed / 10;

		// 火
		CParticle_Fire::Create(D3DXVECTOR3(-90.0f, 0.0f, -150.0f),
			D3DXVECTOR3(PARTICLE__FIRE_SIZE_X, PARTICLE__FIRE_SIZE_Y, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, sinf(fRot)),
			D3DCOLOR_RGBA(255, 0, 0, 255),
			D3DXVECTOR3(cosf(D3DXToRadian(fAngle))*fFireSpeed / 3, sinf(D3DXToRadian(fAngle))*fFireSpeed * 1.3, 0.0f),
			CParticle::TEX_TYPE_2
		);

		// 火
		CParticle_Fire::Create(D3DXVECTOR3(-90.0f, 0.0f, -150.0f),
			D3DXVECTOR3(PARTICLE__FIRE_SIZE_X, PARTICLE__FIRE_SIZE_Y, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, sinf(fRot)),
			D3DCOLOR_RGBA(255, 150, 0, 255),
			D3DXVECTOR3(cosf(D3DXToRadian(fAngle))*fFireSpeed / 3, sinf(D3DXToRadian(fAngle))*fFireSpeed * 1.3, 0.0f),
			CParticle::TEX_TYPE_2
		);
	}
}
//===========================================================
// 描画関数
//===========================================================
void CParticle_Emitter::Draw(void)
{
}