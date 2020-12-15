//=============================================================================
//
// manager処理 [manager.cpp]
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
#include "scene2d.h"
#include "input.h"
#include "keyboard.h"
#include "sound.h"
#include "joystick.h"
#include "camera.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CRenderer * CManager::m_pRenderer = NULL;
CKeyboard * CManager::m_pKeyboard = NULL;
CJoystick * CManager::m_pJoystick = NULL;
CSound * CManager::m_pSound = NULL;
CCamera *CManager::m_pCamera = NULL;
CManager::MODE CManager::m_mode = MODE_NONE;
CPlayer * CManager::m_pPlayer = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow)
{
	//レンダラーの生成
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new  CRenderer;
	}
	//レンダラーの初期化
	m_pRenderer->Init(hWnd, TRUE);

	//入力の生成
	if (m_pKeyboard == NULL)
	{
		m_pKeyboard = new CKeyboard;
	}
	//キーボードの初期化
	m_pKeyboard->Init(hInsitance, hWnd);

	//ジョイスティックの生成
	if (m_pJoystick == NULL)
	{
		m_pJoystick = new CJoystick;
	}
	//ジョイスティックの初期化
	m_pJoystick->Init(hInsitance, hWnd);

	//サウンドの生成
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
	}
	//サウンドの初期化
	m_pSound->Init(hWnd);

	//----------------------------------------------------------------------------------------
	// カメラ生成
	CreateCamera();
	//-----------------------------------------------------------------------------------------

	//全てのリソース読み込み
	LoadAll();

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create();

	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleaseAll();

	//サウンドの停止
	m_pSound->StopSound();

	//サウンドの破棄
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	//ジョイスティックの破棄
	if (m_pJoystick != NULL)
	{
		m_pJoystick->Uninit();
		delete m_pJoystick;
		m_pJoystick = NULL;
	}

	//キーボードの破棄
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	//カメラの終了
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	//レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//全てのリソース破棄
	UnloadAll();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CManager::Update(void)
{
	//キーボードの更新
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}

	//ジョイスティックの更新
	if (m_pJoystick != NULL)
	{
		m_pJoystick->Update();
	}
	if (m_pCamera != NULL)
	{
		//カメラのの更新処理
		m_pCamera->Update();
	}

	//描画の更新
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}

//=============================================================================
// 全リソース読み込み関数
//=============================================================================
void CManager::LoadAll(void)
{
	CPlayer::ModelLoad();
}

//=============================================================================
// 全リソース破棄関数
//=============================================================================
void CManager::UnloadAll(void)
{
	CPlayer::ModelUnload();
}

//=============================================================================
// モード設定関数
//=============================================================================
void CManager::SetMode(MODE mode)
{
	CScene::ReleaseAll();
	//モードの割り当て
	m_mode = mode;
	//モードの切り替え
	switch (mode)
	{
	case MODE_TITLE:
		break;
	}
	//キーボードの更新
	m_pKeyboard->Update();
	//ジョイスティックの更新
	m_pJoystick->Update();
}
//=============================================================================
//
//=============================================================================
void CManager::CreateCamera(void)
{
	// m_pCameraがNULLの場合
	if (m_pCamera == NULL)
	{
		// メモリ確保
		m_pCamera = new CCamera;

		// m_pCameraがNULLでない場合
		if (m_pCamera != NULL)
		{
			// 初期化
			m_pCamera->Init();
		}
	}
}
