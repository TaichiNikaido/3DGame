//====================================================================
// particle_emitter.h
// Author : ŠÇŒ´ Ži
//====================================================================
#ifndef _PARTICLE_EMITTER_H_
#define _PARTICLE_EMITTER_H_

#include "scene.h"

class CParticle_Emitter : public CScene
{
public:
	CParticle_Emitter();
	~CParticle_Emitter();
	static CParticle_Emitter *Create();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	int m_nCount;
};
#endif
