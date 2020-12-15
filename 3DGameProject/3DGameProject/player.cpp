//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �x������
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "model.h"
#include "player.h"
#include "keyboard.h"
#include "joystick.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CModel::MODELDATA CPlayer::m_ModelData = {};
D3DXMATERIAL * CPlayer::m_pMat = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer()
{
	m_pModel = NULL;
	m_pWeapon = NULL;
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
	m_nLife = 0;							//�̗�
	m_nAttack = 0;							//�U����
	m_nStamina = 0;							//�X�^�~�i
	m_nMP = 0;								//�}�W�b�N�|�C���g
	m_nExp = 0;								//�o���l
	m_nLevel = 0;							//���x��
	m_State = STATE_NONE;					//�v���C���[�̏��
	m_Direction = DIRECTION_NONE;			//�v���C���[�̐i�s����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CPlayer::ModelLoad(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXLoadMeshFromX("Data/Model/Player/Teisatuki.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelData.pBuffMat, NULL, &m_ModelData.nNumMat, &m_ModelData.pMesh);

	m_pMat = (D3DXMATERIAL *)m_ModelData.pBuffMat->GetBufferPointer();

	for (int nCountMat = 0; nCountMat < (int)m_ModelData.nNumMat; nCountMat++)
	{
		D3DXCreateTextureFromFile(pDevice, m_pMat[nCountMat].pTextureFilename, &m_ModelData.pTexture[nCountMat]);
	}
	return S_OK;
}

//=============================================================================
// ���f���j���֐�
//=============================================================================
void CPlayer::ModelUnload(void)
{
	if (m_ModelData.pBuffMat != NULL)
	{
		m_ModelData.pBuffMat->Release();
	}

	if (m_ModelData.pMesh != NULL)
	{
		m_ModelData.pMesh->Release();
	}

	for (int nCountTex = 0; nCountTex < MAX_MATERIAL; nCountTex++)
	{
		if (m_ModelData.pTexture[nCountTex] != NULL)
		{
			m_ModelData.pTexture[nCountTex]->Release();
		}
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CPlayer * CPlayer::Create(void)
{
	CPlayer * pPlayer;
	pPlayer = new CPlayer;
	pPlayer->Init();
	return pPlayer;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//�f�[�^�ǂݍ��݊֐��Ăяo��
	DataLoad();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPlayer::Uninit(void)
{
	//���f���̏I���֐��Ăяo��
	m_pModel->Uninit();
	//�j���֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPlayer::Update(void)
{
	//���f���̍X�V�֐��Ăяo��
	m_pModel->Update();
	//���S��Ԃ���Ȃ��Ƃ�
	if (m_State != STATE_DEATH)
	{
		//���͏����֐��Ăяo��
		Input();
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CPlayer::Draw(void)
{
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CPlayer::Input(void)
{
	//�L�[�{�[�h�̎擾
	CKeyboard *pKeyboard = CManager::GetInputKeyboard();
	//�W���C�X�e�B�b�N�̎擾
	CJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//�W���C�X�e�B�b�N�̐U���擾
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	//�ʒu���擾
	D3DXVECTOR3 Pos = m_pModel->GetPos();

	//�����_�b�V���L�[��������Ă�����
	if (pKeyboard->GetKeyboardPress(DIK_LSHIFT) && pInputJoystick->GetJoystickPress(JS_RB))
	{
		//�_�b�V����Ԃɂ���
		m_State = STATE_DASH;
	}

	//�v���C���[�̏�ړ�
	if (pKeyboard->GetKeyboardPress(DIK_W) || lpDIDevice != NULL &&js.lY == -1000)
	{
		//�����_�b�V����Ԃ���Ȃ��Ƃ�
		if (m_State != STATE_DASH)
		{
			//���s��Ԃɂ���
			m_State = STATE_WALK;
		}
		//�i�s������O���ɂ���
		m_Direction = DIRECTION_UP;
		//�ړ������֐��Ăяo��
		Move();
	}
	//�v���C���[�̉��ړ�
	if (pKeyboard->GetKeyboardPress(DIK_S) || lpDIDevice != NULL &&js.lY == 1000)
	{
		//�����_�b�V����Ԃ���Ȃ��Ƃ�
		if (m_State != STATE_DASH)
		{
			//���s��Ԃɂ���
			m_State = STATE_WALK;
		}
		//�i�s����������ɂ���
		m_Direction = DIRECTION_DOWN;
		//�ړ������֐��Ăяo��
		Move();
	}
	//�v���C���[�̍��ړ�
	if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000)
	{
		//�����_�b�V����Ԃ���Ȃ��Ƃ�
		if (m_State != STATE_DASH)
		{
			//���s��Ԃɂ���
			m_State = STATE_WALK;
		}
		//�i�s���������ɂ���
		m_Direction = DIRECTION_LEFT;
		//�ړ������֐��Ăяo��
		Move();
	}
	//�v���C���[�̉E�ړ�
	if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000)
	{
		//�����_�b�V����Ԃ���Ȃ��Ƃ�
		if (m_State != STATE_DASH)
		{
			//���s��Ԃɂ���
			m_State = STATE_WALK;
		}
		//�i�s�������E�ɂ���
		m_Direction = DIRECTION_RIGHT;
		//�ړ������֐��Ăяo��
		Move();
	}
	//�ړ��L�[�̓��͂��Ȃ��Ƃ�
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �ړ������֐�
//=============================================================================
void CPlayer::Move(void)
{
	//���f���̈ʒu���擾
	D3DXVECTOR3 Pos = m_pModel->GetPos();
	//�ړ�����
	if (m_State == STATE_WALK)
	{
		switch (m_Direction)
		{
		case DIRECTION_UP:
			break;
		case DIRECTION_DOWN:
			break;
		case DIRECTION_LEFT:
			break;
		case DIRECTION_RIGHT:
			break;
		default:
			break;
		}
	}
	else if (STATE_DASH)
	{
		switch (m_Direction)
		{
		case DIRECTION_UP:
			break;
		case DIRECTION_DOWN:
			break;
		case DIRECTION_LEFT:
			break;
		case DIRECTION_RIGHT:
			break;
		default:
			break;
		}
	}
	//�ʒu�X�V
	Pos.x += m_Move.x;
	Pos.z += m_Move.z;
	//���f���Ɉʒu��ݒ�
	m_pModel->SetPos(Pos);
}

//=============================================================================
// �U���͐ݒ�֐�
//=============================================================================
void CPlayer::SetAttack(int nAttack)
{
	//�U���͂̐ݒ�
	m_nAttack = nAttack;
}

//=============================================================================
// �U�������֐�
//=============================================================================
void CPlayer::Attack(void)
{
}

//=============================================================================
// �q�b�g�����֐�
//=============================================================================
void CPlayer::Hit(int nValue)
{
	//�G�̍U����H��������̃A�j���[�V�����Đ�
	//
	//�G�t�F�N�g�̐���
	//
	//�̗͌��Z�֐��Ăяo��
	SubLife(nValue);
}

//=============================================================================
// �̗͉��Z�֐�
//=============================================================================
void CPlayer::AddLife(int nValue)
{
	//�񕜃A�j���[�V�����̍Đ�
	//
	//�̗͂̉��Z
	m_nLife += nValue;
	//�񕜃G�t�F�N�g�̐���
	//
}

//=============================================================================
// �̗͌��Z�֐�
//=============================================================================
void CPlayer::SubLife(int nValue)
{
	//���݃A�j���[�V�����̍Đ�
	//
	//�̗͂̌��Z
	m_nLife -= nValue;
	//�G�t�F�N�g�̐���
	//
	//�������C�t��0�ȉ��ɂȂ�����
	if (m_nLife <= 0)
	{
		//���S�֐��Ăяo��
		Death();
	}
}

//=============================================================================
// �o���l���Z�֐�
//=============================================================================
void CPlayer::AddExp(int nValue)
{
	//�o���l�̉��Z
	m_nExp += nValue;
}

//=============================================================================
// ���S�֐�
//=============================================================================
void CPlayer::Death(void)
{
	//���S��Ԃɂ���
	m_State = STATE_DEATH;
	//���S�A�j���[�V�����̍Đ�
	//
	//�o���l��0�ɂ���
	m_nExp = 0;
}

//=============================================================================
// �e�L�X�g�f�[�^�ǂݍ��݊֐�
//=============================================================================
void CPlayer::DataLoad(void)
{
	FILE *pFile;

	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Rot;
	D3DXVECTOR3 Size;

	pFile = fopen("data/TEXT/Player/PlayerData.txt", "r"); //�t�@�C���̓ǂݍ���

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &m_nLife);		//���C�t�̓ǂݍ���
		fscanf(pFile, "%d", &m_nStamina);	//�X�^�~�i�̓ǂݍ���
		fscanf(pFile, "%d", &m_nMP);		//�}�W�b�N�|�C���g�̓ǂݍ���
		fscanf(pFile, "%d", &m_nExp);		//�o���l�̓ǂݍ���
		fscanf(pFile, "%d", &m_nLevel);		//���x���̓ǂݍ���
		fscanf(pFile, "%f", &m_fWalkSpeed);	//���s���x�̓ǂݍ���
		fscanf(pFile, "%f", &m_fDashSpeed);	//�_�b�V�����x�̓ǂݍ���
		fscanf(pFile, "%f", &Pos.x);		//�ʒuX
		fscanf(pFile, "%f", &Pos.y);		//�ʒuY
		fscanf(pFile, "%f", &Pos.z);		//�ʒuZ
		fscanf(pFile, "%f", &Rot.x);		//����X
		fscanf(pFile, "%f", &Rot.y);		//����Y
		fscanf(pFile, "%f", &Rot.z);		//����Z
		fscanf(pFile, "%f", &Size.x);		//�T�C�YX
		fscanf(pFile, "%f", &Size.y);		//�T�C�YY
		fscanf(pFile, "%f", &Size.z);		//�T�C�YZ
		fclose(pFile); //�t�@�C�������
	}
	//���f���̐���
	m_pModel = CModel::Create(m_ModelData, Pos, Rot, Size);
}
