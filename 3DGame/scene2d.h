//=============================================================================
//
// 2Dポリゴン [scene2d.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_POLYGON   (256)
#define NUM_VERTEX	  (4)
#define NUM_POLYGON	  (2)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos; //頂点座標
	D3DXVECTOR2	tex; //テクスチャ
	D3DCOLOR	col; //頂点カラー
	float		rhw; //座標変換用紙係数
}VERTEX_2D;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CScene2d :public CScene
{
public:
	CScene2d(int nPriority = DEFAULT_PRIORITY);
	~CScene2d();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetPosition(D3DXVECTOR3 Pos);
	void SetSize(D3DXVECTOR3 Size);
	void SetRot(D3DXVECTOR3 Rot);
	void SetVertexPosition(D3DXVECTOR3 aVtxPos[NUM_VERTEX]);
	void SetTexture(D3DXVECTOR2 aTex[NUM_VERTEX]);
	void SetColor(D3DCOLOR aCol[NUM_VERTEX]);
	void SetScalse(float fScalse);
	D3DXVECTOR3 GetPosition(void) { return m_Pos; };
private:
	LPDIRECT3DTEXTURE9		m_pTexture;				//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//頂点バッファへのポインタ
	D3DXVECTOR3				m_Pos;					//座標
	D3DXVECTOR3				m_Size;					//サイズ
	D3DXVECTOR3				m_Rot;					//向き
	D3DXVECTOR3				m_aVtxPos[NUM_VERTEX];	//頂点座標
	D3DXVECTOR2				m_aTex[NUM_VERTEX];		//テクスチャのUV座標
	D3DCOLOR	 			m_aCol[NUM_VERTEX];		//頂点カラー
	float					m_fScale;				//縮尺
	float					m_fAngle;				//角度
	float					m_fLength;				//長さ
};
#endif