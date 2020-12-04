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
	m_Pos	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���W
	m_Rot	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
	m_Scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�k��
	m_posAnime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotAnime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_sizeAnime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModel::~CModel()
{
}

//=============================================================================
// �����֐�
//=============================================================================
CModel * CModel::Create(CModel* pParentModel,MODELDATA modeldata, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// �������̊m��
	CModel* pModel;
	pModel = new CModel;
	//�e����̐ݒ�
	pModel->SetPos(pos);
	pModel->SetRot(rot);
	pModel->SetScale(size);
	pModel->m_pParentModel = pParentModel;
	pModel->m_ModelData = modeldata;
	// ����������
	pModel->Init();

	return pModel;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CModel::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CModel::Uninit(void)
{
	m_ModelData.pBuffMat = NULL;
	m_ModelData.nNumMat = NULL;
	m_ModelData.pMesh = NULL;
	memset(m_ModelData.pTexture, NULL, sizeof(m_ModelData.pTexture));
	m_ModelData.mtxWorld = D3DXMATRIX();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CModel::Update(void)
{
}

//=============================================================================
// �`��֐�
//=============================================================================
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	D3DXMATRIX mtxParent;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL* pMat;
	//���[���h�ϊ��s��̏�����
	D3DXMatrixIdentity(&m_ModelData.mtxWorld);

	//�g��k���s��̐����ƌv�Z
	D3DXMatrixScaling(&mtxScale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxScale);

	//��]�s��̐����ƌv�Z
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotAnime.y, m_rotAnime.x, m_rotAnime.z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);

	//���s�ړ��s��̐����ƌv�Z
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);
	D3DXMatrixTranslation(&mtxTrans, m_posAnime.x, m_posAnime.y, m_posAnime.z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);

	if (m_pParentModel != NULL)
	{
		mtxParent = m_pParentModel->m_ModelData.mtxWorld;
		D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxParent);
	}

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
// ���W�ݒ�֐�
//=============================================================================
void CModel::SetPos(D3DXVECTOR3 Pos)
{
	m_Pos = Pos;
}

//=============================================================================
// �����ݒ�֐�
//=============================================================================
void CModel::SetRot(D3DXVECTOR3 Rot)
{
	m_Rot = Rot;
}

//=============================================================================
// �k�ڐݒ�֐�
//=============================================================================
void CModel::SetScale(D3DXVECTOR3 Scale)
{
	m_Scale = Scale;
}

void CModel::SetAnimationPos(D3DXVECTOR3 pos)
{
}

void CModel::SetAnimationRot(D3DXVECTOR3 rot)
{
}

void CModel::SetAnimationSize(D3DXVECTOR3 size)
{
}

CModel::MODELDATA CModel::GetModelData(void)
{
	return m_ModelData;
}

void CModel::BindModel(MODELDATA modeldata)
{
	m_ModelData = modeldata;
}
