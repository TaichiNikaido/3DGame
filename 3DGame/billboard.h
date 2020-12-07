//=============================================================================
//
// ビルボード [billboard.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBillboard :public CScene
{
public:
	CBillboard();
	~CBillboard();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetTex(float fTexX, float fTexY, float fTexX2, float fTexY2);
	void SetColor(D3DXCOLOR col);
	D3DXVECTOR3 GetPosition() {return m_pos; }
	D3DXVECTOR3 GetSize() { return m_size; }
	D3DXCOLOR GetColor() { return m_col; }
private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld; //行列計算用
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
	D3DXCOLOR m_col;
	float m_fTexX;
	float m_fTexY;
	float m_fTexX2;
	float m_fTexY2;
};
#endif