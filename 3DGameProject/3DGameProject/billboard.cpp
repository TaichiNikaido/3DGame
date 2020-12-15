//=============================================================================
//
// �r���{�[�h���� [billboard.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBillboard::CBillboard()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	m_mtxWorld;		//�s��v�Z�p
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_fTexX = 0.0f;
	m_fTexY = 0.0f;
	m_fTexX2 = 0.0f;
	m_fTexY2 = 0.0f;
}

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CBillboard::~CBillboard()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBillboard::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̏����� ���ʒu�͍s��Ōv�Z���邽�ߌ��_���S��4���_���`
	pVtx[0].pos = D3DXVECTOR3(-m_Size.x / 2, m_Size.y / 2, +m_Size.z / 2);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x / 2, m_Size.y / 2, +m_Size.z / 2);
	pVtx[2].pos = D3DXVECTOR3(-m_Size.x / 2, -m_Size.y / 2, +m_Size.z / 2);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x / 2, -m_Size.y / 2, +m_Size.z / 2);

	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;

	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);

	//�A�����b�N
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CBillboard::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBillboard::Update(void)
{
	// ���_����ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_Size.x / 2, m_Size.y / 2, +m_Size.z / 2);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x / 2, m_Size.y / 2, +m_Size.z / 2);
	pVtx[2].pos = D3DXVECTOR3(-m_Size.x / 2, -m_Size.y / 2, +m_Size.z / 2);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x / 2, -m_Size.y / 2, +m_Size.z / 2);

	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;

	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CBillboard::Draw(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�s��v�Z�p�̃}�g���N�X
	D3DMATERIAL9 matDef;

	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 170);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�Z�b�g�e�N�X�`��
	pDevice->SetTexture(0, m_pTexture);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//��]�̋t�s��
	pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxRot);
	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;

	// �������f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x,
		m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld,
		&mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//�}�e���A�����
	ZeroMemory(&matDef, sizeof(matDef));
	matDef.Ambient.r = m_Color.r;
	matDef.Ambient.g = m_Color.g;
	matDef.Ambient.b = m_Color.b;
	matDef.Ambient.a = m_Color.a;
	pDevice->SetMaterial(&matDef);
	// �|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�A���t�@�e�X�g������
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	ZeroMemory(&matDef, sizeof(matDef));
	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);
}

//=============================================================================
// �ʒu�̐ݒ�֐�
//=============================================================================
void CBillboard::SetPos(D3DXVECTOR3 Pos)
{
	m_Pos = Pos;
}

//=============================================================================
// �����̐ݒ�֐�
//=============================================================================
void CBillboard::SetRot(D3DXVECTOR3 Rot)
{
}

//=============================================================================
// �g�嗦�̐ݒ�֐�
//=============================================================================
void CBillboard::SetSize(D3DXVECTOR3 Size)
{
	m_Size = Size;
}

//=============================================================================
// �F�̐ݒ�֐�
//=============================================================================
void CBillboard::SetColor(D3DXCOLOR Color)
{
	m_Color = Color;
}

//=============================================================================
// �e�N�X�`���̈ʒu�̐ݒ�֐�
//=============================================================================
void CBillboard::SetTex(float fTexX, float fTexY, float fTexX2, float fTexY2)
{
	m_fTexX = fTexX;
	m_fTexY = fTexY;
	m_fTexX2 = fTexX2;
	m_fTexY2 = fTexY2;
}

//=============================================================================
// �e�N�X�`���̊��蓖�Ċ֐�
//=============================================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

