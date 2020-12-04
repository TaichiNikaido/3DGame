//=============================================================================
//
// ���f���Ǘ����� [model.h]
// Author : ��K������
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MATERIAL (30)



//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CModel
{
public:
	typedef struct
	{
		LPD3DXBUFFER pBuffMat;                        // �}�e���A�����ւ̃|�C���^
		DWORD nNumMat;                                // �}�e���A�����̐�
		LPD3DXMESH pMesh;                             // ���b�V�����ւ̃|�C���^
		LPDIRECT3DTEXTURE9 pTexture[MAX_MATERIAL];    // �e�N�X�`���ւ̃|�C���^
		D3DXMATRIX mtxWorld;                          // �A�j���[�V�������
	}MODELDATA;
	CModel();
	virtual ~CModel();
	static CModel* Create(CModel* pParentModel,MODELDATA modeldata, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void SetPos(D3DXVECTOR3 Pos);
	void SetRot(D3DXVECTOR3 Rot);
	void SetScale(D3DXVECTOR3 Scale);
	void SetAnimationPos(D3DXVECTOR3 pos);
	void SetAnimationRot(D3DXVECTOR3 rot);
	void SetAnimationSize(D3DXVECTOR3 size);
	MODELDATA GetModelData(void);
	void BindModel(MODELDATA modeldata);

private:
	CModel* m_pParentModel;
	MODELDATA m_ModelData;
	D3DXVECTOR3 m_Pos;			//���W
	D3DXVECTOR3 m_Rot;			//����
	D3DXVECTOR3 m_Scale;		//�k��
	D3DXVECTOR3 m_posAnime;
	D3DXVECTOR3 m_rotAnime;
	D3DXVECTOR3 m_sizeAnime;
};
#endif
