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
#include "scene3d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MATERIAL (30)

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CModel : public CScene3d
{
public:
	typedef struct
	{
		LPD3DXBUFFER pBuffMat;                        // �}�e���A�����ւ̃|�C���^
		DWORD nNumMat;                                // �}�e���A�����̐�
		LPD3DXMESH pMesh;                             // ���b�V�����ւ̃|�C���^
		LPDIRECT3DTEXTURE9 pTexture[MAX_MATERIAL];    // �e�N�X�`���ւ̃|�C���^
		D3DXMATRIX mtxWorld;
	}MODELDATA;

	CModel();
	virtual ~CModel();
	static CModel* Create(MODELDATA modeldata, D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	MODELDATA GetModelData(void);
	void BindModel(MODELDATA modeldata);
private:
	CModel* m_pModel;
	MODELDATA m_ModelData;
};
#endif
