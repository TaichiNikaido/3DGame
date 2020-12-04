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
	m_Pos	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//座標
	m_Rot	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
	m_Scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//縮尺
	m_posAnime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotAnime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_sizeAnime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CModel::~CModel()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CModel * CModel::Create(CModel* pParentModel,MODELDATA modeldata, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// メモリの確保
	CModel* pModel;
	pModel = new CModel;
	//各種情報の設定
	pModel->SetPos(pos);
	pModel->SetRot(rot);
	pModel->SetScale(size);
	pModel->m_pParentModel = pParentModel;
	pModel->m_ModelData = modeldata;
	// 初期化処理
	pModel->Init();

	return pModel;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CModel::Init(void)
{
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CModel::Uninit(void)
{
	m_ModelData.pBuffMat = NULL;
	m_ModelData.nNumMat = NULL;
	m_ModelData.pMesh = NULL;
	memset(m_ModelData.pTexture, NULL, sizeof(m_ModelData.pTexture));
	m_ModelData.mtxWorld = D3DXMATRIX();
}

//=============================================================================
// 更新関数
//=============================================================================
void CModel::Update(void)
{
}

//=============================================================================
// 描画関数
//=============================================================================
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	D3DXMATRIX mtxParent;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL* pMat;
	//ワールド変換行列の初期化
	D3DXMatrixIdentity(&m_ModelData.mtxWorld);

	//拡大縮小行列の生成と計算
	D3DXMatrixScaling(&mtxScale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxScale);

	//回転行列の生成と計算
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotAnime.y, m_rotAnime.x, m_rotAnime.z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);

	//平行移動行列の生成と計算
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);
	D3DXMatrixTranslation(&mtxTrans, m_posAnime.x, m_posAnime.y, m_posAnime.z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);

	if (m_pParentModel != NULL)
	{
		mtxParent = m_pParentModel->m_ModelData.mtxWorld;
		D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxParent);
	}

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
// 座標設定関数
//=============================================================================
void CModel::SetPos(D3DXVECTOR3 Pos)
{
	m_Pos = Pos;
}

//=============================================================================
// 向き設定関数
//=============================================================================
void CModel::SetRot(D3DXVECTOR3 Rot)
{
	m_Rot = Rot;
}

//=============================================================================
// 縮尺設定関数
//=============================================================================
void CModel::SetScale(D3DXVECTOR3 Scale)
{
	m_Scale = Scale;
}

void CModel::SetAnimationPos(D3DXVECTOR3 pos)
{
}

void CModel::SetAnimationRot(D3DXVECTOR3 rot)
{
}

void CModel::SetAnimationSize(D3DXVECTOR3 size)
{
}

CModel::MODELDATA CModel::GetModelData(void)
{
	return m_ModelData;
}

void CModel::BindModel(MODELDATA modeldata)
{
	m_ModelData = modeldata;
}
