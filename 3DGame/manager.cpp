//=============================================================================
//
// manager���� [manager.cpp]
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
#include "input.h"
#include "keyboard.h"
#include "sound.h"
#include "joystick.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CRenderer * CManager::m_pRenderer = NULL;
CKeyboard * CManager::m_pKeyboard = NULL;
CJoystick * CManager::m_pJoystick = NULL;
CSound * CManager::m_pSound = NULL;
CManager::MODE CManager::m_mode = MODE_NONE;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow)
{
	//�����_���[�̐���
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new  CRenderer;
	}
	//����������
	m_pRenderer->Init(hWnd, TRUE);

	//���͂̐���
	if (m_pKeyboard == NULL)
	{
		m_pKeyboard = new CKeyboard;
	}
	//�L�[�{�[�h�̏�����
	m_pKeyboard->Init(hInsitance, hWnd);

	//�W���C�X�e�B�b�N�̐���
	if (m_pJoystick == NULL)
	{
		m_pJoystick = new CJoystick;
	}
	//�W���C�X�e�B�b�N�̏�����
	m_pJoystick->Init(hInsitance, hWnd);

	//�T�E���h�̐���
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
	}
	//�T�E���h�̏�����
	m_pSound->Init(hWnd);

	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleaseAll();

	//�T�E���h�̒�~
	m_pSound->StopSound();

	//�T�E���h�̔j��
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	//�W���C�X�e�B�b�N�̔j��
	if (m_pJoystick != NULL)
	{
		m_pJoystick->Uninit();
		delete m_pJoystick;
		m_pJoystick = NULL;
	}

	//�L�[�{�[�h�̔j��
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	//�����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CManager::Update(void)
{
	//�L�[�{�[�h�̍X�V
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}

	//�W���C�X�e�B�b�N�̍X�V
	if (m_pJoystick != NULL)
	{
		m_pJoystick->Update();
	}

	//�`��̍X�V
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw(); // �`�揈��
}

//=============================================================================
// ���[�h�ݒ�֐�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	CScene::ReleaseAll();
	//���[�h�̊��蓖��
	m_mode = mode;
	//���[�h�̐؂�ւ�
	switch (mode)
	{
	case MODE_NONE:
		break;
	}
	//�L�[�{�[�h�̍X�V
	m_pKeyboard->Update();
	//�W���C�X�e�B�b�N�̍X�V
	m_pJoystick->Update();
}
