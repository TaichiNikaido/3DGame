//=============================================================================
//
// 2D�V�[���Ǘ����� [scene2d.cpp]
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
#include "scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2d::CScene2d(int nPriority)
{
	m_pTexture      = NULL;								//�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff      = NULL;								//���_�o�b�t�@�ւ̃|�C���^
	m_Pos           = D3DXVECTOR3(0.0f, 0.0f,0.0f);		//���W
	m_Size			= D3DXVECTOR3(0.0f, 0.0f,0.0f);		//�T�C�Y
	m_Rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	memset(m_aVtxPos, NULL, sizeof(m_aVtxPos));			//���_���W
	memset(m_aTex,    NULL, sizeof(m_aTex));			//�e�N�X�`����UV���W
	memset(m_aCol,    NULL, sizeof(m_aCol));			//���_�J���[
	m_fScale		= 0.0f;								//�k��
	m_fAngle		= 0.0f;								//�p�x
	m_fLength		= 0.0f;								//����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2d::~CScene2d()
{
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CScene2d::Init(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�p�x�̐ݒ�
	m_fAngle = sqrtf((float)(((m_Size.x / 2) * (m_Size.x / 2)) + ((m_Size.y / 2) * (m_Size.y / 2))));

	//�����̐ݒ�
	m_fLength = atan2f((m_Size.y / 2), (m_Size.x / 2));

	//���_���W�̐ݒ�
	m_aVtxPos[0].x = m_Pos.x - cosf(m_fAngle - m_Rot.z) * m_fLength * m_fScale;
	m_aVtxPos[0].y = m_Pos.y - sinf(m_fAngle - m_Rot.z) * m_fLength * m_fScale;
	m_aVtxPos[0].z = 0.0f;

	m_aVtxPos[1].x = m_Pos.x + cosf(m_fAngle + m_Rot.z) * m_fLength * m_fScale;
	m_aVtxPos[1].y = m_Pos.y - sinf(m_fAngle + m_Rot.z) * m_fLength * m_fScale;
	m_aVtxPos[1].z = 0.0f;

	m_aVtxPos[2].x = m_Pos.x - cosf(m_fAngle + m_Rot.z) * m_fLength * m_fScale;
	m_aVtxPos[2].y = m_Pos.y + sinf(m_fAngle + m_Rot.z) * m_fLength * m_fScale;
	m_aVtxPos[2].z = 0.0f;

	m_aVtxPos[3].x = m_Pos.x + cosf(m_fAngle - m_Rot.z) * m_fLength * m_fScale;
	m_aVtxPos[3].y = m_Pos.y + sinf(m_fAngle - m_Rot.z) * m_fLength * m_fScale;
	m_aVtxPos[3].z = 0.0f;

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_aCol[0];
	pVtx[1].col = m_aCol[1];
	pVtx[2].col = m_aCol[2];
	pVtx[3].col = m_aCol[3];

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = m_aTex[0];
	pVtx[1].tex = m_aTex[1];
	pVtx[2].tex = m_aTex[2];
	pVtx[3].tex = m_aTex[3];

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CScene2d::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CScene2d::Update(void)
{
}

//=============================================================================
// �`��֐�
//=============================================================================
void CScene2d::Draw(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// �e�N�X�`���̊��蓖�Ċ֐�
//=============================================================================
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//�e�N�X�`���̊��蓖��
	m_pTexture = pTexture;
}

//=============================================================================
// ���W�ݒ�֐�
//=============================================================================
void CScene2d::SetPosition(D3DXVECTOR3 Pos)
{
	//���W�̊��蓖��
	m_Pos = Pos;
}

//=============================================================================
// �T�C�Y�ݒ�֐�
//=============================================================================
void CScene2d::SetSize(D3DXVECTOR3 Size)
{
	//�T�C�Y�̊��蓖��
	m_Size = Size;
}

//=============================================================================
// �����ݒ�֐�
//=============================================================================
void CScene2d::SetRot(D3DXVECTOR3 Rot)
{
	//�����̊��蓖��
	m_Rot = Rot;
}

//=============================================================================
// ���_���W�ݒ�֐�
//=============================================================================
void CScene2d::SetVertexPosition(D3DXVECTOR3 VtxPos[NUM_VERTEX])
{
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//�e�N�X�`����UV���W���蓖��
		m_aVtxPos[nCount] = VtxPos[nCount];
	}
}

//=============================================================================
// �e�N�X�`����UV���W�ݒ�֐�
//=============================================================================
void CScene2d::SetTexture(D3DXVECTOR2 aTex[NUM_VERTEX])
{
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//�e�N�X�`����UV���W�̊��蓖��
		m_aTex[nCount] = aTex[nCount];
	}
}

//=============================================================================
// ���_�J���[�ݒ�֐�
//=============================================================================
void CScene2d::SetColor(D3DCOLOR aCol[NUM_VERTEX])
{
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//�J���[�̊��蓖��
		m_aCol[nCount] = aCol[nCount];
	}
}

//=============================================================================
// �k�ڐݒ�֐�
//=============================================================================
void CScene2d::SetScalse(float fScalse)
{
	//�k�ڂ̊��蓖��
	m_fScale = fScalse;
}
