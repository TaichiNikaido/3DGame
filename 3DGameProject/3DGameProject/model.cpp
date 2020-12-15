//=============================================================================
//
// モデル管理処理 [model.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene3d.h"
#include "model.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CModel::CModel()
{
	//モデルデータの初期化
	ZeroMemory(&m_ModelData, sizeof(m_ModelData));
}

//=============================================================================
// デストラクタ
//=============================================================================
CModel::~CModel()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CModel * CModel::Create(MODELDATA modeldata, D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size)
{
	// メモリの確保
	CModel* pModel;
	pModel = new CModel;
	//各種情報の設定
	pModel->m_ModelData = modeldata;
	// 初期化処理
	pModel->Init();
	pModel->SetPos(Pos);
	pModel->SetRot(Rot);
	pModel->SetSize(Size);
	return pModel;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CModel::Init(void)
{
	CScene3d::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CModel::Uninit(void)
{
	CScene3d::Uninit();
	//m_ModelData.pBuffMat = NULL;
	//m_ModelData.nNumMat = NULL;
	//m_ModelData.pMesh = NULL;
	//memset(m_ModelData.pTexture, NULL, sizeof(m_ModelData.pTexture));
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CModel::Update(void)
{
	CScene3d::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL* pMat;

	//ワールド変換行列の初期化
	D3DXMatrixIdentity(&m_ModelData.mtxWorld);

	//平行移動行列の生成と計算
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);

	//回転行列の生成と計算
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);

	//拡大縮小行列の生成と計算
	D3DXMatrixScaling(&mtxScale, GetSize().x, GetSize().y, GetSize().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxScale);

	//計算結果を適用
	pDevice->SetTransform(D3DTS_WORLD, &m_ModelData.mtxWorld);

	//マテリアル情報の取得
	pDevice->GetMaterial(&matDef);

	if (m_ModelData.pBuffMat != NULL)
	{
		pMat = (D3DXMATERIAL*)m_ModelData.pBuffMat->GetBufferPointer();
	}

	//マテリアル情報の設定とマテリアルごとに描画
	for (int nCntMat = 0; nCntMat < (int)m_ModelData.nNumMat; nCntMat++)
	{
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		pDevice->SetTexture(0, m_ModelData.pTexture[nCntMat]);
		m_ModelData.pMesh->DrawSubset(nCntMat);
	}

	//マテリアル情報のリセット
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// モデルデータ取得関数
//=============================================================================
CModel::MODELDATA CModel::GetModelData(void)
{
	return m_ModelData;
}

//=============================================================================
// モデル割り当て関数
//=============================================================================
void CModel::BindModel(MODELDATA modeldata)
{
	m_ModelData = modeldata;
}
