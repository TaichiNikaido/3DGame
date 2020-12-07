//======================================================================
//
//	camera.h
//	Author : 管原司
//======================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
//======================================================================
//	クラス
//======================================================================
class CCamera
{
public:
	CCamera();
	~CCamera();
	void Init(void);
	void Uninit(void);
	void Update(void);

private:
	D3DXVECTOR3 posV;		// 位置
	D3DXVECTOR3 posR;		// 注視点
	D3DXVECTOR3 vecU;
	D3DXMATRIX	mtxProjection;
	D3DXMATRIX	mtxView;
	float m_fDistance;		// 距離
	float m_fPhi;			// ファイ
	float m_fTheta;			// シータ
};

#endif