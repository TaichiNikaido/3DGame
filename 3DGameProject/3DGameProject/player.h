//=============================================================================
//
// プレイヤー [player.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"
#include "model.h"
#include "weapon.h"
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
class CPlayer :public CScene
{
public:
	typedef enum
	{
		STATE_NONE = -1,
		STATE_WALK,
		STATE_DASH,
		STATE_DEATH,
		STATE_MAX
	}STATE;

	typedef enum
	{
		DIRECTION_NONE = -1,
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT,
		DIRECTION_MAX
	}DIRECTION;

	CPlayer();
	~CPlayer();
	static HRESULT ModelLoad(void);
	static void ModelUnload(void);
	static CPlayer* Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Input(void);
	void Move(void);
	void SetAttack(int nAttack);
	int GetAttack(void) { return m_nAttack; };
	void Attack(void);
	void Hit(int nValue);
	void AddLife(int nValue);
	void SubLife(int nValue);
	void AddExp(int nValue);
	void Death(void);
	void DataLoad(void);
private:
	static CModel::MODELDATA m_ModelData;
	static D3DXMATERIAL *m_pMat;
	CModel * m_pModel;
	CWeapon * m_pWeapon;
	D3DXVECTOR3 m_Move;		//移動量
	int m_nLife;			//体力
	int m_nAttack;			//攻撃力
	int m_nStamina;			//スタミナ
	int m_nMP;				//マジックポイント
	int m_nExp;				//経験値
	int m_nLevel;			//レベル
	float m_fWalkSpeed;		//歩行スピード
	float m_fDashSpeed;		//ダッシュスピード
	STATE m_State;			//プレイヤーの状態
	DIRECTION m_Direction;	//プレイヤーの進行方向
};
#endif