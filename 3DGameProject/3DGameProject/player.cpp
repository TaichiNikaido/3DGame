//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// 警告制御
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "model.h"
#include "player.h"
#include "keyboard.h"
#include "joystick.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CModel::MODELDATA CPlayer::m_ModelData = {};
D3DXMATERIAL * CPlayer::m_pMat = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer()
{
	m_pModel = NULL;
	m_pWeapon = NULL;
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	m_nLife = 0;							//体力
	m_nAttack = 0;							//攻撃力
	m_nStamina = 0;							//スタミナ
	m_nMP = 0;								//マジックポイント
	m_nExp = 0;								//経験値
	m_nLevel = 0;							//レベル
	m_State = STATE_NONE;					//プレイヤーの状態
	m_Direction = DIRECTION_NONE;			//プレイヤーの進行方向
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CPlayer::ModelLoad(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXLoadMeshFromX("Data/Model/Player/Teisatuki.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelData.pBuffMat, NULL, &m_ModelData.nNumMat, &m_ModelData.pMesh);

	m_pMat = (D3DXMATERIAL *)m_ModelData.pBuffMat->GetBufferPointer();

	for (int nCountMat = 0; nCountMat < (int)m_ModelData.nNumMat; nCountMat++)
	{
		D3DXCreateTextureFromFile(pDevice, m_pMat[nCountMat].pTextureFilename, &m_ModelData.pTexture[nCountMat]);
	}
	return S_OK;
}

//=============================================================================
// モデル破棄関数
//=============================================================================
void CPlayer::ModelUnload(void)
{
	if (m_ModelData.pBuffMat != NULL)
	{
		m_ModelData.pBuffMat->Release();
	}

	if (m_ModelData.pMesh != NULL)
	{
		m_ModelData.pMesh->Release();
	}

	for (int nCountTex = 0; nCountTex < MAX_MATERIAL; nCountTex++)
	{
		if (m_ModelData.pTexture[nCountTex] != NULL)
		{
			m_ModelData.pTexture[nCountTex]->Release();
		}
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CPlayer * CPlayer::Create(void)
{
	CPlayer * pPlayer;
	pPlayer = new CPlayer;
	pPlayer->Init();
	return pPlayer;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//データ読み込み関数呼び出し
	DataLoad();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPlayer::Uninit(void)
{
	//モデルの終了関数呼び出し
	m_pModel->Uninit();
	//破棄関数呼び出し
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CPlayer::Update(void)
{
	//モデルの更新関数呼び出し
	m_pModel->Update();
	//死亡状態じゃないとき
	if (m_State != STATE_DEATH)
	{
		//入力処理関数呼び出し
		Input();
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CPlayer::Draw(void)
{
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CPlayer::Input(void)
{
	//キーボードの取得
	CKeyboard *pKeyboard = CManager::GetInputKeyboard();
	//ジョイスティックの取得
	CJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//ジョイスティックの振動取得
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	//位置を取得
	D3DXVECTOR3 Pos = m_pModel->GetPos();

	//もしダッシュキーが押されていたら
	if (pKeyboard->GetKeyboardPress(DIK_LSHIFT) && pInputJoystick->GetJoystickPress(JS_RB))
	{
		//ダッシュ状態にする
		m_State = STATE_DASH;
	}

	//プレイヤーの上移動
	if (pKeyboard->GetKeyboardPress(DIK_W) || lpDIDevice != NULL &&js.lY == -1000)
	{
		//もしダッシュ状態じゃないとき
		if (m_State != STATE_DASH)
		{
			//歩行状態にする
			m_State = STATE_WALK;
		}
		//進行方向を前方にする
		m_Direction = DIRECTION_UP;
		//移動処理関数呼び出し
		Move();
	}
	//プレイヤーの下移動
	if (pKeyboard->GetKeyboardPress(DIK_S) || lpDIDevice != NULL &&js.lY == 1000)
	{
		//もしダッシュ状態じゃないとき
		if (m_State != STATE_DASH)
		{
			//歩行状態にする
			m_State = STATE_WALK;
		}
		//進行方向を後方にする
		m_Direction = DIRECTION_DOWN;
		//移動処理関数呼び出し
		Move();
	}
	//プレイヤーの左移動
	if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000)
	{
		//もしダッシュ状態じゃないとき
		if (m_State != STATE_DASH)
		{
			//歩行状態にする
			m_State = STATE_WALK;
		}
		//進行方向を左にする
		m_Direction = DIRECTION_LEFT;
		//移動処理関数呼び出し
		Move();
	}
	//プレイヤーの右移動
	if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000)
	{
		//もしダッシュ状態じゃないとき
		if (m_State != STATE_DASH)
		{
			//歩行状態にする
			m_State = STATE_WALK;
		}
		//進行方向を右にする
		m_Direction = DIRECTION_RIGHT;
		//移動処理関数呼び出し
		Move();
	}
	//移動キーの入力がないとき
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// 移動処理関数
//=============================================================================
void CPlayer::Move(void)
{
	//モデルの位置を取得
	D3DXVECTOR3 Pos = m_pModel->GetPos();
	//移動処理
	if (m_State == STATE_WALK)
	{
		switch (m_Direction)
		{
		case DIRECTION_UP:
			break;
		case DIRECTION_DOWN:
			break;
		case DIRECTION_LEFT:
			break;
		case DIRECTION_RIGHT:
			break;
		default:
			break;
		}
	}
	else if (STATE_DASH)
	{
		switch (m_Direction)
		{
		case DIRECTION_UP:
			break;
		case DIRECTION_DOWN:
			break;
		case DIRECTION_LEFT:
			break;
		case DIRECTION_RIGHT:
			break;
		default:
			break;
		}
	}
	//位置更新
	Pos.x += m_Move.x;
	Pos.z += m_Move.z;
	//モデルに位置を設定
	m_pModel->SetPos(Pos);
}

//=============================================================================
// 攻撃力設定関数
//=============================================================================
void CPlayer::SetAttack(int nAttack)
{
	//攻撃力の設定
	m_nAttack = nAttack;
}

//=============================================================================
// 攻撃処理関数
//=============================================================================
void CPlayer::Attack(void)
{
}

//=============================================================================
// ヒット処理関数
//=============================================================================
void CPlayer::Hit(int nValue)
{
	//敵の攻撃を食らった時のアニメーション再生
	//
	//エフェクトの生成
	//
	//体力減算関数呼び出し
	SubLife(nValue);
}

//=============================================================================
// 体力加算関数
//=============================================================================
void CPlayer::AddLife(int nValue)
{
	//回復アニメーションの再生
	//
	//体力の加算
	m_nLife += nValue;
	//回復エフェクトの生成
	//
}

//=============================================================================
// 体力減算関数
//=============================================================================
void CPlayer::SubLife(int nValue)
{
	//怯みアニメーションの再生
	//
	//体力の減算
	m_nLife -= nValue;
	//エフェクトの生成
	//
	//もしライフが0以下になったら
	if (m_nLife <= 0)
	{
		//死亡関数呼び出し
		Death();
	}
}

//=============================================================================
// 経験値加算関数
//=============================================================================
void CPlayer::AddExp(int nValue)
{
	//経験値の加算
	m_nExp += nValue;
}

//=============================================================================
// 死亡関数
//=============================================================================
void CPlayer::Death(void)
{
	//死亡状態にする
	m_State = STATE_DEATH;
	//死亡アニメーションの再生
	//
	//経験値を0にする
	m_nExp = 0;
}

//=============================================================================
// テキストデータ読み込み関数
//=============================================================================
void CPlayer::DataLoad(void)
{
	FILE *pFile;

	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Rot;
	D3DXVECTOR3 Size;

	pFile = fopen("data/TEXT/Player/PlayerData.txt", "r"); //ファイルの読み込み

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &m_nLife);		//ライフの読み込み
		fscanf(pFile, "%d", &m_nStamina);	//スタミナの読み込み
		fscanf(pFile, "%d", &m_nMP);		//マジックポイントの読み込み
		fscanf(pFile, "%d", &m_nExp);		//経験値の読み込み
		fscanf(pFile, "%d", &m_nLevel);		//レベルの読み込み
		fscanf(pFile, "%f", &m_fWalkSpeed);	//歩行速度の読み込み
		fscanf(pFile, "%f", &m_fDashSpeed);	//ダッシュ速度の読み込み
		fscanf(pFile, "%f", &Pos.x);		//位置X
		fscanf(pFile, "%f", &Pos.y);		//位置Y
		fscanf(pFile, "%f", &Pos.z);		//位置Z
		fscanf(pFile, "%f", &Rot.x);		//向きX
		fscanf(pFile, "%f", &Rot.y);		//向きY
		fscanf(pFile, "%f", &Rot.z);		//向きZ
		fscanf(pFile, "%f", &Size.x);		//サイズX
		fscanf(pFile, "%f", &Size.y);		//サイズY
		fscanf(pFile, "%f", &Size.z);		//サイズZ
		fclose(pFile); //ファイルを閉じる
	}
	//モデルの生成
	m_pModel = CModel::Create(m_ModelData, Pos, Rot, Size);
}
