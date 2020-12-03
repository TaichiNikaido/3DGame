//=============================================================================
//
// �`�揈�� [scene.h]
// Author : ��K������
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SCENE		 (256)
#define PRIORITY_MAX	 (10)
#define DEFAULT_PRIORITY (3)

//*****************************************************************************
// �N���X��`
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
	static CScene * m_apTop[PRIORITY_MAX];  //�擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CScene * m_apCur[PRIORITY_MAX];	//���݂̃I�u�W�F�N�g�ւ̃|�C���^
	static int m_nNumAll;					//�V�[���̑���
	OBJTYPE m_objType;						//�I�u�W�F�N�g�^�C�v
	int m_nPriority;						//�`��D��x
	int m_nID;								//�V�[����ID
	bool m_bDeath;							//���S�t���O��������
	CScene * m_pScene;						//�V�[���ւ̃|�C���^
	CScene * m_pPrev;                       //�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene * m_pNext;						//���̃I�u�W�F�N�g�ւ̃|�C���^
};
#endif