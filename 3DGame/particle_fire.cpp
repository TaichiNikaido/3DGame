//===========================================================
// particle_fire.cpp
// Author : �ǌ��@�i
//===========================================================

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "particle_fire.h"
//===========================================================
//	�R���X�g���N�^
//===========================================================
CParticle_Fire::CParticle_Fire()
{
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_MinSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMinColor = 0.0f;
}
//===========================================================
//	�f�X�g���N�^
//===========================================================
CParticle_Fire::~CParticle_Fire()
{
}
//===========================================================
//	�����֐�
//===========================================================
CParticle_Fire * CParticle_Fire::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType)
{
	// CParticle_Fire�N���X�̃|�C���^
	CParticle_Fire *pParticle_Fire;

	// �������m��
	pParticle_Fire = new CParticle_Fire;

	// ������
	pParticle_Fire->Init(pos, size, rot, col, move, TexType);

	// �|�C���^��Ԃ�
	return pParticle_Fire;
}
//===========================================================
//	������
//===========================================================
HRESULT CParticle_Fire::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType)
{
	// ������
	CParticle::Init(pos, size, rot, col, TexType);

	// �ړ���
	m_move = move;

	// �T�C�Y���Z�l
	m_MinSize = D3DXVECTOR3(1.0f, 1.0f, 0.0f);

	// �J���[���Z�l
	m_fMinColor = 0.005f;

	return S_OK;

}
//===========================================================
//	�I���֐�
//===========================================================
void CParticle_Fire::Uninit(void)
{
	CParticle::Uninit();
}
//===========================================================
//	�X�V�֐�
//===========================================================
void CParticle_Fire::Update(void)
{
	CParticle::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();
	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();
	// �F�擾
	D3DXCOLOR col = GetColor();

	// �����Z
	col.a -= m_fMinColor;

	// �T�C�Y���Z
	size -= m_MinSize;

	// �T�C�Y�ݒ�
	SetSize(size);

	// �F�ݒ�
	SetColor(col);

	// �ʒu�X�V
	pos += m_move;

	// �ʒu���W�ݒ�
	SetPosition(pos);

	// ����0.0f�ȉ��̏ꍇ
	if (col.a <= 0.0f)
	{
		// �I��
		Uninit();
		return;
	}
}
//===========================================================
//	�`��֐�
//===========================================================
void CParticle_Fire::Draw(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`��
	CParticle::Draw();

	// ���ɖ߂�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}