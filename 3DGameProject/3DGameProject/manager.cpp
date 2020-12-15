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
#include "camera.h"
#include "player.h"

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
CCamera *CManager::m_pCamera = NULL;
CManager::MODE CManager::m_mode = MODE_NONE;
CPlayer * CManager::m_pPlayer = NULL;

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
// �����������֐�
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow)
{
	//�����_���[�̐���
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new  CRenderer;
	}
	//�����_���[�̏�����
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

	//----------------------------------------------------------------------------------------
	// �J��������
	CreateCamera();
	//-----------------------------------------------------------------------------------------

	//�S�Ẵ��\�[�X�ǂݍ���
	LoadAll();

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create();

	return S_OK;
}

//=============================================================================
// �I�������֐�
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

	//�J�����̏I��
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	//�����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//�S�Ẵ��\�[�X�j��
	UnloadAll();
}

//=============================================================================
// �X�V�����֐�
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
	if (m_pCamera != NULL)
	{
		//�J�����̂̍X�V����
		m_pCamera->Update();
	}

	//�`��̍X�V
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}

//=============================================================================
// �S���\�[�X�ǂݍ��݊֐�
//=============================================================================
void CManager::LoadAll(void)
{
	CPlayer::ModelLoad();
}

//=============================================================================
// �S���\�[�X�j���֐�
//=============================================================================
void CManager::UnloadAll(void)
{
	CPlayer::ModelUnload();
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
	case MODE_TITLE:
		break;
	}
	//�L�[�{�[�h�̍X�V
	m_pKeyboard->Update();
	//�W���C�X�e�B�b�N�̍X�V
	m_pJoystick->Update();
}
//=============================================================================
//
//=============================================================================
void CManager::CreateCamera(void)
{
	// m_pCamera��NULL�̏ꍇ
	if (m_pCamera == NULL)
	{
		// �������m��
		m_pCamera = new CCamera;

		// m_pCamera��NULL�łȂ��ꍇ
		if (m_pCamera != NULL)
		{
			// ������
			m_pCamera->Init();
		}
	}
}
