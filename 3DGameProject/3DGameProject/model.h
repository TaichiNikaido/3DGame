//=============================================================================
//
// モデル管理処理 [model.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene3d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_MATERIAL (30)

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CModel : public CScene3d
{
public:
	typedef struct
	{
		LPD3DXBUFFER pBuffMat;                        // マテリアル情報へのポインタ
		DWORD nNumMat;                                // マテリアル情報の数
		LPD3DXMESH pMesh;                             // メッシュ情報へのポインタ
		LPDIRECT3DTEXTURE9 pTexture[MAX_MATERIAL];    // テクスチャへのポインタ
		D3DXMATRIX mtxWorld;
	}MODELDATA;

	CModel();
	virtual ~CModel();
	static CModel* Create(MODELDATA modeldata, D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	MODELDATA GetModelData(void);
	void BindModel(MODELDATA modeldata);
private:
	CModel* m_pModel;
	MODELDATA m_ModelData;
};
#endif
