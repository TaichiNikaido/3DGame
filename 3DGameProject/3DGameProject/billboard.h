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
// 前方宣言
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
	void SetPos(D3DXVECTOR3 Pos);
	void SetRot(D3DXVECTOR3 Rot);
	void SetSize(D3DXVECTOR3 Size);
	void SetColor(D3DXCOLOR Color);
	void SetTex(float fTexX, float fTexY, float fTexX2, float fTexY2);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	D3DXVECTOR3 GetPos(void) { return m_Pos; };
	D3DXVECTOR3 GetRot(void) { return m_Rot; };
	D3DXVECTOR3 GetSize(void) { return m_Size; };
	D3DXCOLOR GetColor(void) { return m_Color; };
private:
	LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;					//行列計算用
	D3DXVECTOR3 m_Pos;						//位置
	D3DXVECTOR3 m_Rot;						//向き
	D3DXVECTOR3 m_Size;						//サイズ
	D3DXCOLOR m_Color;						//カラー
	float m_fTexX;
	float m_fTexY;
	float m_fTexX2;
	float m_fTexY2;
};
#endif