//=============================================================================
//
// �v���C���[ [player.h]
// Author : ��K������
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"
#include "model.h"
#include "weapon.h"
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
class CPlayer :public CScene
{
public:
	typedef enum
	{
		STATE_NONE = -1,
		STATE_WALK,
		STATE_DASH,
		STATE_DEATH,
		STATE_MAX
	}STATE;

	typedef enum
	{
		DIRECTION_NONE = -1,
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT,
		DIRECTION_MAX
	}DIRECTION;

	CPlayer();
	~CPlayer();
	static HRESULT ModelLoad(void);
	static void ModelUnload(void);
	static CPlayer* Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Input(void);
	void Move(void);
	void SetAttack(int nAttack);
	int GetAttack(void) { return m_nAttack; };
	void Attack(void);
	void Hit(int nValue);
	void AddLife(int nValue);
	void SubLife(int nValue);
	void AddExp(int nValue);
	void Death(void);
	void DataLoad(void);
private:
	static CModel::MODELDATA m_ModelData;
	static D3DXMATERIAL *m_pMat;
	CModel * m_pModel;
	CWeapon * m_pWeapon;
	D3DXVECTOR3 m_Move;		//�ړ���
	int m_nLife;			//�̗�
	int m_nAttack;			//�U����
	int m_nStamina;			//�X�^�~�i
	int m_nMP;				//�}�W�b�N�|�C���g
	int m_nExp;				//�o���l
	int m_nLevel;			//���x��
	float m_fWalkSpeed;		//���s�X�s�[�h
	float m_fDashSpeed;		//�_�b�V���X�s�[�h
	STATE m_State;			//�v���C���[�̏��
	DIRECTION m_Direction;	//�v���C���[�̐i�s����
};
#endif