//=============================================================================
//
// 2D�V�[���Ǘ����� [scene2d.h]
// Author : ��K������
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_POLYGON   (256)
#define NUM_VERTEX	  (4)
#define NUM_POLYGON	  (2)

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScene2d :public CScene
{
public:
	CScene2d(int nPriority = DEFAULT_PRIORITY);
	~CScene2d();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetPos(D3DXVECTOR3 Pos);
	void SetSize(D3DXVECTOR3 Size);
	void SetRot(D3DXVECTOR3 Rot);
	void SetVertexPosition(D3DXVECTOR3 aVtxPos[NUM_VERTEX]);
	void SetTexture(D3DXVECTOR2 aTex[NUM_VERTEX]);
	void SetColor(D3DCOLOR aCol[NUM_VERTEX]);
	void SetSize(float fSize);
	D3DXVECTOR3 GetPos(void) { return m_Pos; };
private:
	LPDIRECT3DTEXTURE9		m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_Pos;					//���W
	D3DXVECTOR3				m_Size;					//�T�C�Y
	D3DXVECTOR3				m_Rot;					//����
	D3DXVECTOR3				m_aVtxPos[NUM_VERTEX];	//���_���W
	D3DXVECTOR2				m_aTex[NUM_VERTEX];		//�e�N�X�`����UV���W
	D3DCOLOR	 			m_aCol[NUM_VERTEX];		//���_�J���[
	float					m_fScale;				//�k��
	float					m_fAngle;				//�p�x
	float					m_fLength;				//����
};
#endif