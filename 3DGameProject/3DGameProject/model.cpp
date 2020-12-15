//=============================================================================
//
// ���f���Ǘ����� [model.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene3d.h"
#include "model.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModel::CModel()
{
	//���f���f�[�^�̏�����
	ZeroMemory(&m_ModelData, sizeof(m_ModelData));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModel::~CModel()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CModel * CModel::Create(MODELDATA modeldata, D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size)
{
	// �������̊m��
	CModel* pModel;
	pModel = new CModel;
	//�e����̐ݒ�
	pModel->m_ModelData = modeldata;
	// ����������
	pModel->Init();
	pModel->SetPos(Pos);
	pModel->SetRot(Rot);
	pModel->SetSize(Size);
	return pModel;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CModel::Init(void)
{
	CScene3d::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CModel::Uninit(void)
{
	CScene3d::Uninit();
	//m_ModelData.pBuffMat = NULL;
	//m_ModelData.nNumMat = NULL;
	//m_ModelData.pMesh = NULL;
	//memset(m_ModelData.pTexture, NULL, sizeof(m_ModelData.pTexture));
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CModel::Update(void)
{
	CScene3d::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL* pMat;

	//���[���h�ϊ��s��̏�����
	D3DXMatrixIdentity(&m_ModelData.mtxWorld);

	//���s�ړ��s��̐����ƌv�Z
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);

	//��]�s��̐����ƌv�Z
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);

	//�g��k���s��̐����ƌv�Z
	D3DXMatrixScaling(&mtxScale, GetSize().x, GetSize().y, GetSize().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxScale);

	//�v�Z���ʂ�K�p
	pDevice->SetTransform(D3DTS_WORLD, &m_ModelData.mtxWorld);

	//�}�e���A�����̎擾
	pDevice->GetMaterial(&matDef);

	if (m_ModelData.pBuffMat != NULL)
	{
		pMat = (D3DXMATERIAL*)m_ModelData.pBuffMat->GetBufferPointer();
	}

	//�}�e���A�����̐ݒ�ƃ}�e���A�����Ƃɕ`��
	for (int nCntMat = 0; nCntMat < (int)m_ModelData.nNumMat; nCntMat++)
	{
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		pDevice->SetTexture(0, m_ModelData.pTexture[nCntMat]);
		m_ModelData.pMesh->DrawSubset(nCntMat);
	}

	//�}�e���A�����̃��Z�b�g
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// ���f���f�[�^�擾�֐�
//=============================================================================
CModel::MODELDATA CModel::GetModelData(void)
{
	return m_ModelData;
}

//=============================================================================
// ���f�����蓖�Ċ֐�
//=============================================================================
void CModel::BindModel(MODELDATA modeldata)
{
	m_ModelData = modeldata;
}
