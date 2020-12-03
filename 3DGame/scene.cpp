//=============================================================================
//
// シーン管理処理 [scene.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CScene * CScene::m_apCur[PRIORITY_MAX] = {};
CScene * CScene::m_apTop[PRIORITY_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	m_nPriority = nPriority;
	m_bDeath = false;
	//リストの先頭が存在しない場合
	if (m_apTop[m_nPriority] == NULL)
	{
		//自分を入れる
		m_apTop[m_nPriority] = this;
	}
	//現在のオブジェクトが存在しない場合
	if (m_apCur[m_nPriority] == NULL)
	{
		//自分を入れる
		m_apCur[m_nPriority] = this;
	}

	//現在のオブジェクト(pCur)の次のオブジェクトを自分にする
	m_apCur[m_nPriority]->m_pNext = this;

	//現在のオブジェクト(pCur)が自分の場合
	if (m_apCur[m_nPriority] == this)
	{
		//自分の前のオブジェクトをNULLにする
		this->m_pPrev = NULL;
	}
	else
	{
		//自分の前のオブジェクトを現在のオブジェクト(pCur)にする
		this->m_pPrev = m_apCur[m_nPriority];
	}
	//現在のオブジェクト(pCur)を自分にする
	m_apCur[m_nPriority] = this;
	//自分の次のオブジェクトをNULLにする
	this->m_pNext = NULL;

	m_objType = OBJTYPE_NONE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// 全体更新関数
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		CScene * pScene = m_apTop[nCountPriority];

		while (pScene != NULL)
		{
			CScene * pSceneNext = pScene->m_pNext;
			pScene->Update();
			pScene = pSceneNext;
		}
	}

	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		CScene * pScene = m_apTop[nCountPriority];

		while (pScene != NULL)
		{
			CScene * pSceneNext = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				//どっちも同じとき
				if (pScene == m_apTop[nCountPriority] && pScene == m_apCur[nCountPriority])
				{
					m_apCur[nCountPriority] = NULL;
					m_apTop[nCountPriority] = NULL;
				}
				//m_Topの場合
				if (pScene == m_apTop[nCountPriority])
				{
					m_apTop[nCountPriority] = pScene->m_pNext;
				}
				//m_pCurの場合
				if (pScene == m_apCur[nCountPriority])
				{
					m_apCur[nCountPriority] = pScene->m_pPrev;
				}
				//m_pNextがNULLでない場合
				if (pScene->m_pNext != NULL)
				{
					//m_pNextのm_pPrevを現在のm_pPrevにする
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;

					//次が現在だった場合
					if (pScene->m_pPrev == m_apTop[nCountPriority])
					{
						//次のポインタの前を先頭のポインタにする
						m_apTop[nCountPriority] = pScene->m_pNext->m_pPrev;
					}
				}
				//m_pPrevがNULLでない場合
				if (pScene->m_pPrev != NULL)
				{
					//m_pPrevのNextを現在のNextにする
					pScene->m_pPrev->m_pNext = pScene->m_pNext;

					//前が現在だった場合
					if (pScene->m_pNext == m_apCur[nCountPriority])
					{
						//前のポインタの次を先頭にする
						m_apCur[nCountPriority] = pScene->m_pPrev->m_pNext;
					}
				}
				delete pScene;
			}
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// 全体描画関数
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		CScene * pScene = m_apTop[nCountPriority];
		while (pScene != NULL)
		{
			CScene * pSceneNext = pScene->m_pNext;
			pScene->Draw();
			pScene = pSceneNext;
		}
	}
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		CScene * pScene = m_apTop[nCountPriority];
		while (pScene != NULL)
		{
			CScene * pSceneNext = pScene->m_pNext;
			if (pScene->m_bDeath == true)
			{

				//どっちも同じとき
				if (pScene == m_apTop[nCountPriority] && pScene == m_apCur[nCountPriority])
				{
					m_apCur[nCountPriority] = NULL;
					m_apTop[nCountPriority] = NULL;
				}
				//m_Topの場合
				if (pScene == m_apTop[nCountPriority])
				{
					m_apTop[nCountPriority] = pScene->m_pNext;
				}
				//m_pCurの場合
				if (pScene == m_apCur[nCountPriority])
				{
					m_apCur[nCountPriority] = pScene->m_pPrev;
				}

				//m_pNextがNULLでない場合
				if (pScene->m_pNext != NULL)
				{
					//m_pNextのm_pPrevを現在のm_pPrevにする
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;

					//次が現在だった場合
					if (pScene->m_pPrev == m_apTop[nCountPriority])
					{
						//次のポインタの前を先頭のポインタにする
						m_apTop[nCountPriority] = pScene->m_pNext->m_pPrev;
					}
				}

				//m_pPrevがNULLでない場合
				if (pScene->m_pPrev != NULL)
				{
					//m_pPrevのNextを現在のNextにする
					pScene->m_pPrev->m_pNext = pScene->m_pNext;

					//前が現在だった場合
					if (pScene->m_pNext == m_apCur[nCountPriority])
					{
						//前のポインタの次を先頭にする
						m_apCur[nCountPriority] = pScene->m_pPrev->m_pNext;
					}
				}
				delete pScene;
			}
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// 全体破棄関数
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		if (m_apTop[nCountPriority] != NULL)
		{
			CScene * pScene = m_apTop[nCountPriority];
			while (pScene != NULL)
			{
				CScene * pSceneNext = pScene->m_pNext;
				pScene->Uninit();
				pScene = pSceneNext;
			}
			while (pScene != NULL)
			{
				CScene * pSceneNext = pScene->m_pNext;
				if (pScene->m_bDeath == true)
				{
					//どっちも同じとき
					if (pScene == m_apTop[nCountPriority] && pScene == m_apCur[nCountPriority])
					{
						m_apCur[nCountPriority] = NULL;
						m_apTop[nCountPriority] = NULL;
					}
					//m_Topの場合
					if (pScene == m_apTop[nCountPriority])
					{
						m_apTop[nCountPriority] = pScene->m_pNext;
					}
					//m_pCurの場合
					if (pScene == m_apCur[nCountPriority])
					{
						m_apCur[nCountPriority] = pScene->m_pPrev;
					}
					//m_pNextがNULLでない場合
					if (pScene->m_pNext != NULL)
					{
						//m_pNextのm_pPrevを現在のm_pPrevにする
						pScene->m_pNext->m_pPrev = pScene->m_pPrev;
						//次が現在だった場合
						if (pScene->m_pPrev == m_apTop[nCountPriority])
						{
							//次のポインタの前を先頭のポインタにする
							m_apTop[nCountPriority] = pScene->m_pNext->m_pPrev;
						}
					}
					//m_pPrevがNULLでない場合
					if (pScene->m_pPrev != NULL)
					{
						//m_pPrevのNextを現在のNextにする
						pScene->m_pPrev->m_pNext = pScene->m_pNext;
						//前が現在だった場合
						if (pScene->m_pNext == m_apCur[nCountPriority])
						{
							//前のポインタの次を先頭にする
							m_apCur[nCountPriority] = pScene->m_pPrev->m_pNext;
						}
					}
					delete pScene;
				}
				pScene = pSceneNext;
			}
		}
	}
}

//=============================================================================
// 破棄関数
//=============================================================================
void CScene::Release(void)
{
	//死亡フラグ立てる
	if (this->m_bDeath == false)
	{
		this->m_bDeath = true;
	}
}

//=============================================================================
// オブジェクトの種類を設定
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//=============================================================================
// 先頭のオブジェクトを取得
//=============================================================================
CScene ** CScene::GetTop(void)
{
	return m_apTop;
}

//=============================================================================
// 次のオブジェクトを取得
//=============================================================================
CScene * CScene::GetNext(void)
{
	return m_pNext;
}

//=============================================================================
// 現在のオブジェクトを取得
//=============================================================================
CScene * CScene::GetPrev(void)
{
	return m_pPrev;
}

//=============================================================================
// オブジェクトの種類を取得
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}