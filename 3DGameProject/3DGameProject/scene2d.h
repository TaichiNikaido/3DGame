//=============================================================================
//
// 2Dシーン管理処理 [scene2d.h]
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

//*****************************************************************************
// 前方宣言
//*****************************************************************************

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
	void SetPos(D3DXVECTOR3 Pos);
	void SetSize(D3DXVECTOR3 Size);
	void SetRot(D3DXVECTOR3 Rot);
	void SetVertexPosition(D3DXVECTOR3 aVtxPos[NUM_VERTEX]);
	void SetTexture(D3DXVECTOR2 aTex[NUM_VERTEX]);
	void SetColor(D3DCOLOR aCol[NUM_VERTEX]);
	void SetSize(float fSize);
	D3DXVECTOR3 GetPos(void) { return m_Pos; };
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