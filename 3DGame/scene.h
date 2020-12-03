//=============================================================================
//
// 描画処理 [scene.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SCENE		 (256)
#define PRIORITY_MAX	 (10)
#define DEFAULT_PRIORITY (3)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = -1,
		OBJTYPE_MAX
	}OBJTYPE;
	CScene(int nPriority = DEFAULT_PRIORITY);
	virtual ~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	void SetObjType(OBJTYPE pObjType);
	static CScene** GetTop(void);
	CScene* GetNext(void);
	CScene* GetPrev(void);
	OBJTYPE GetObjType(void);
protected:
	void Release(void);
private:
	static CScene * m_apTop[PRIORITY_MAX];  //先頭のオブジェクトへのポインタ
	static CScene * m_apCur[PRIORITY_MAX];	//現在のオブジェクトへのポインタ
	static int m_nNumAll;					//シーンの総数
	OBJTYPE m_objType;						//オブジェクトタイプ
	int m_nPriority;						//描画優先度
	int m_nID;								//シーンのID
	bool m_bDeath;							//死亡フラグ立ったか
	CScene * m_pScene;						//シーンへのポインタ
	CScene * m_pPrev;                       //前のオブジェクトへのポインタ
	CScene * m_pNext;						//次のオブジェクトへのポインタ
};
#endif