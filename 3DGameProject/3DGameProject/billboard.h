//=============================================================================
//
// �r���{�[�h [billboard.h]
// Author : ��K������
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

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
class CBillboard :public CScene
{
public:
	CBillboard();
	~CBillboard();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 Pos);
	void SetRot(D3DXVECTOR3 Rot);
	void SetSize(D3DXVECTOR3 Size);
	void SetColor(D3DXCOLOR Color);
	void SetTex(float fTexX, float fTexY, float fTexX2, float fTexY2);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	D3DXVECTOR3 GetPos(void) { return m_Pos; };
	D3DXVECTOR3 GetRot(void) { return m_Rot; };
	D3DXVECTOR3 GetSize(void) { return m_Size; };
	D3DXCOLOR GetColor(void) { return m_Color; };
private:
	LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;					//�s��v�Z�p
	D3DXVECTOR3 m_Pos;						//�ʒu
	D3DXVECTOR3 m_Rot;						//����
	D3DXVECTOR3 m_Size;						//�T�C�Y
	D3DXCOLOR m_Color;						//�J���[
	float m_fTexX;
	float m_fTexY;
	float m_fTexX2;
	float m_fTexY2;
};
#endif