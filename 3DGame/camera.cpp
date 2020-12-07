//======================================
//	camera.cpp
//	Author : 管原司
//======================================

//======================================
//インクルードファイル
//======================================
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "keyboard.h"
//======================================
//コンストラクタ
//======================================
CCamera::CCamera()
{
	posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	memset(mtxProjection, NULL, sizeof(mtxProjection));
	memset(mtxView, NULL, sizeof(mtxView));
	m_fPhi = 0.0f;
	m_fTheta = 0.0f;
}

//======================================
//デクリメント
//======================================
CCamera::~CCamera()
{

}

//======================================
//初期化処理
//======================================
void CCamera::Init(void)
{
	posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	memset(mtxProjection, NULL, sizeof(mtxProjection));
	memset(mtxView, NULL, sizeof(mtxView));
	m_fPhi = 1;
	m_fTheta = 1.7f;
}

//======================================
//終了処理
//======================================
void CCamera::Uninit(void)
{

}

//======================================
//更新処理
//======================================
void CCamera::Update(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//キーボードの取得
	CKeyboard *pKeyborad = CManager::GetInputKeyboard();

//======================================
//移動
//======================================		

	// 右回転
	if (pKeyborad->GetKeyboardPress(DIK_D))
	{
		m_fPhi += D3DXToRadian(1);
	}
	//左回転
	if (pKeyborad->GetKeyboardPress(DIK_A))
	{
		m_fPhi -= D3DXToRadian(1);
	}
	//上回転
	if (pKeyborad->GetKeyboardPress(DIK_W))
	{
		m_fTheta -= D3DXToRadian(1);
	}
	//下回転
	if (pKeyborad->GetKeyboardPress(DIK_S))
	{
		m_fTheta += D3DXToRadian(1);
	}

	//注視点
	//距離
	posR.x = (sinf(m_fTheta)*cosf(m_fPhi));
	posR.y = cosf(m_fTheta);
	posR.z = (sinf(m_fTheta)*sinf(m_fPhi));

	//視点	
	//距離
	m_fDistance = 40;
	posV.x = m_fDistance*(sinf(m_fTheta)*cosf(m_fPhi));
	posV.y = m_fDistance*cosf(m_fTheta);
	posV.z = m_fDistance*(sinf(m_fTheta)*sinf(m_fPhi));

//======================================
//カメラ描画
//======================================
	D3DXMatrixIdentity(&mtxView);
	D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
	D3DXMatrixIdentity(&mtxProjection);
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(90), SCREEN_WIDTH / SCREEN_HEIGHT, 10, 10000);
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}