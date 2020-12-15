//=============================================================================
//
// �G�̊Ǘ����� [enemy.h]
// Author : ��K������
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
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
	D3DXVECTOR3 m_DropExpSize;	//���Ƃ��o���l�̃T�C�Y
	int m_nLife;				//�̗�
	int m_nAttack;				//�U����
	int m_nDropExp;				//���Ƃ��o���l
};
#endif