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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_MATERIAL (30)



//*****************************************************************************
// クラス定義
//*****************************************************************************
class CModel
{
public:
	typedef struct
	{
		LPD3DXBUFFER pBuffMat;                        // マテリアル情報へのポインタ
		DWORD nNumMat;                                // マテリアル情報の数
		LPD3DXMESH pMesh;                             // メッシュ情報へのポインタ
		LPDIRECT3DTEXTURE9 pTexture[MAX_MATERIAL];    // テクスチャへのポインタ
		D3DXMATRIX mtxWorld;                          // アニメーション情報
	}MODELDATA;
	CModel();
	virtual ~CModel();
	static CModel* Create(CModel* pParentModel,MODELDATA modeldata, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void SetPos(D3DXVECTOR3 Pos);
	void SetRot(D3DXVECTOR3 Rot);
	void SetScale(D3DXVECTOR3 Scale);
	void SetAnimationPos(D3DXVECTOR3 pos);
	void SetAnimationRot(D3DXVECTOR3 rot);
	void SetAnimationSize(D3DXVECTOR3 size);
	MODELDATA GetModelData(void);
	void BindModel(MODELDATA modeldata);

private:
	CModel* m_pParentModel;
	MODELDATA m_ModelData;
	D3DXVECTOR3 m_Pos;			//座標
	D3DXVECTOR3 m_Rot;			//向き
	D3DXVECTOR3 m_Scale;		//縮尺
	D3DXVECTOR3 m_posAnime;
	D3DXVECTOR3 m_rotAnime;
	D3DXVECTOR3 m_sizeAnime;
};
#endif
