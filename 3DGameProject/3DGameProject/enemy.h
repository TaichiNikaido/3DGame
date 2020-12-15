//=============================================================================
//
// 敵の管理処理 [enemy.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"
#include "model.h"

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
class CEnemy :public CScene
{
public:
	CEnemy();
	~CEnemy();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetDropExpSize(D3DXVECTOR3 DropExpSize);
	void SetLife(int nLife);
	void SetAttack(int nAttack);
	void SetDropExp(int nDropExp);
	int GetLife(void) { return m_nLife; };
	int GetAttack(void) { return m_nAttack; };
	void AddLife(int nValue);
	void SubLife(int nValue);
	void Death(void);
	void DropExp(void);
private:
	static CModel::MODELDATA m_ModelData;
	static D3DXMATERIAL *m_pMat;
	CModel* m_pModel;
	D3DXVECTOR3 m_DropExpSize;	//落とす経験値のサイズ
	int m_nLife;				//体力
	int m_nAttack;				//攻撃力
	int m_nDropExp;				//落とす経験値
};
#endif