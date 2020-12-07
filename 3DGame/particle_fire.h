//====================================================================
// particle_fire.h
// Author : ä«å¥ éi
//====================================================================
#ifndef _PARTICLE_FIRE_H_
#define _PARTICLE_FIRE_H_

#include "particle.h"

class CParticle_Fire : public CParticle
{
public:
	CParticle_Fire();
	~CParticle_Fire();
	static CParticle_Fire *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move , CParticle::TEX_TYPE TexType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	D3DXVECTOR3	m_move;		//	à⁄ìÆó 
	D3DXVECTOR3 m_MinSize;	//	ÉTÉCÉYå∏éZ
	float m_fMinColor;		//	êFÇÃå∏éZíl
};
#endif