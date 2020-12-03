//=============================================================================
//
// �V�[���Ǘ����� [scene.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CScene * CScene::m_apCur[PRIORITY_MAX] = {};
CScene * CScene::m_apTop[PRIORITY_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	m_nPriority = nPriority;
	m_bDeath = false;
	//���X�g�̐擪�����݂��Ȃ��ꍇ
	if (m_apTop[m_nPriority] == NULL)
	{
		//����������
		m_apTop[m_nPriority] = this;
	}
	//���݂̃I�u�W�F�N�g�����݂��Ȃ��ꍇ
	if (m_apCur[m_nPriority] == NULL)
	{
		//����������
		m_apCur[m_nPriority] = this;
	}

	//���݂̃I�u�W�F�N�g(pCur)�̎��̃I�u�W�F�N�g�������ɂ���
	m_apCur[m_nPriority]->m_pNext = this;

	//���݂̃I�u�W�F�N�g(pCur)�������̏ꍇ
	if (m_apCur[m_nPriority] == this)
	{
		//�����̑O�̃I�u�W�F�N�g��NULL�ɂ���
		this->m_pPrev = NULL;
	}
	else
	{
		//�����̑O�̃I�u�W�F�N�g�����݂̃I�u�W�F�N�g(pCur)�ɂ���
		this->m_pPrev = m_apCur[m_nPriority];
	}
	//���݂̃I�u�W�F�N�g(pCur)�������ɂ���
	m_apCur[m_nPriority] = this;
	//�����̎��̃I�u�W�F�N�g��NULL�ɂ���
	this->m_pNext = NULL;

	m_objType = OBJTYPE_NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// �S�̍X�V�֐�
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		CScene * pScene = m_apTop[nCountPriority];

		while (pScene != NULL)
		{
			CScene * pSceneNext = pScene->m_pNext;
			pScene->Update();
			pScene = pSceneNext;
		}
	}

	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		CScene * pScene = m_apTop[nCountPriority];

		while (pScene != NULL)
		{
			CScene * pSceneNext = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				//�ǂ����������Ƃ�
				if (pScene == m_apTop[nCountPriority] && pScene == m_apCur[nCountPriority])
				{
					m_apCur[nCountPriority] = NULL;
					m_apTop[nCountPriority] = NULL;
				}
				//m_Top�̏ꍇ
				if (pScene == m_apTop[nCountPriority])
				{
					m_apTop[nCountPriority] = pScene->m_pNext;
				}
				//m_pCur�̏ꍇ
				if (pScene == m_apCur[nCountPriority])
				{
					m_apCur[nCountPriority] = pScene->m_pPrev;
				}
				//m_pNext��NULL�łȂ��ꍇ
				if (pScene->m_pNext != NULL)
				{
					//m_pNext��m_pPrev�����݂�m_pPrev�ɂ���
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;

					//�������݂������ꍇ
					if (pScene->m_pPrev == m_apTop[nCountPriority])
					{
						//���̃|�C���^�̑O��擪�̃|�C���^�ɂ���
						m_apTop[nCountPriority] = pScene->m_pNext->m_pPrev;
					}
				}
				//m_pPrev��NULL�łȂ��ꍇ
				if (pScene->m_pPrev != NULL)
				{
					//m_pPrev��Next�����݂�Next�ɂ���
					pScene->m_pPrev->m_pNext = pScene->m_pNext;

					//�O�����݂������ꍇ
					if (pScene->m_pNext == m_apCur[nCountPriority])
					{
						//�O�̃|�C���^�̎���擪�ɂ���
						m_apCur[nCountPriority] = pScene->m_pPrev->m_pNext;
					}
				}
				delete pScene;
			}
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// �S�̕`��֐�
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		CScene * pScene = m_apTop[nCountPriority];
		while (pScene != NULL)
		{
			CScene * pSceneNext = pScene->m_pNext;
			pScene->Draw();
			pScene = pSceneNext;
		}
	}
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		CScene * pScene = m_apTop[nCountPriority];
		while (pScene != NULL)
		{
			CScene * pSceneNext = pScene->m_pNext;
			if (pScene->m_bDeath == true)
			{

				//�ǂ����������Ƃ�
				if (pScene == m_apTop[nCountPriority] && pScene == m_apCur[nCountPriority])
				{
					m_apCur[nCountPriority] = NULL;
					m_apTop[nCountPriority] = NULL;
				}
				//m_Top�̏ꍇ
				if (pScene == m_apTop[nCountPriority])
				{
					m_apTop[nCountPriority] = pScene->m_pNext;
				}
				//m_pCur�̏ꍇ
				if (pScene == m_apCur[nCountPriority])
				{
					m_apCur[nCountPriority] = pScene->m_pPrev;
				}

				//m_pNext��NULL�łȂ��ꍇ
				if (pScene->m_pNext != NULL)
				{
					//m_pNext��m_pPrev�����݂�m_pPrev�ɂ���
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;

					//�������݂������ꍇ
					if (pScene->m_pPrev == m_apTop[nCountPriority])
					{
						//���̃|�C���^�̑O��擪�̃|�C���^�ɂ���
						m_apTop[nCountPriority] = pScene->m_pNext->m_pPrev;
					}
				}

				//m_pPrev��NULL�łȂ��ꍇ
				if (pScene->m_pPrev != NULL)
				{
					//m_pPrev��Next�����݂�Next�ɂ���
					pScene->m_pPrev->m_pNext = pScene->m_pNext;

					//�O�����݂������ꍇ
					if (pScene->m_pNext == m_apCur[nCountPriority])
					{
						//�O�̃|�C���^�̎���擪�ɂ���
						m_apCur[nCountPriority] = pScene->m_pPrev->m_pNext;
					}
				}
				delete pScene;
			}
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// �S�̔j���֐�
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		if (m_apTop[nCountPriority] != NULL)
		{
			CScene * pScene = m_apTop[nCountPriority];
			while (pScene != NULL)
			{
				CScene * pSceneNext = pScene->m_pNext;
				pScene->Uninit();
				pScene = pSceneNext;
			}
			while (pScene != NULL)
			{
				CScene * pSceneNext = pScene->m_pNext;
				if (pScene->m_bDeath == true)
				{
					//�ǂ����������Ƃ�
					if (pScene == m_apTop[nCountPriority] && pScene == m_apCur[nCountPriority])
					{
						m_apCur[nCountPriority] = NULL;
						m_apTop[nCountPriority] = NULL;
					}
					//m_Top�̏ꍇ
					if (pScene == m_apTop[nCountPriority])
					{
						m_apTop[nCountPriority] = pScene->m_pNext;
					}
					//m_pCur�̏ꍇ
					if (pScene == m_apCur[nCountPriority])
					{
						m_apCur[nCountPriority] = pScene->m_pPrev;
					}
					//m_pNext��NULL�łȂ��ꍇ
					if (pScene->m_pNext != NULL)
					{
						//m_pNext��m_pPrev�����݂�m_pPrev�ɂ���
						pScene->m_pNext->m_pPrev = pScene->m_pPrev;
						//�������݂������ꍇ
						if (pScene->m_pPrev == m_apTop[nCountPriority])
						{
							//���̃|�C���^�̑O��擪�̃|�C���^�ɂ���
							m_apTop[nCountPriority] = pScene->m_pNext->m_pPrev;
						}
					}
					//m_pPrev��NULL�łȂ��ꍇ
					if (pScene->m_pPrev != NULL)
					{
						//m_pPrev��Next�����݂�Next�ɂ���
						pScene->m_pPrev->m_pNext = pScene->m_pNext;
						//�O�����݂������ꍇ
						if (pScene->m_pNext == m_apCur[nCountPriority])
						{
							//�O�̃|�C���^�̎���擪�ɂ���
							m_apCur[nCountPriority] = pScene->m_pPrev->m_pNext;
						}
					}
					delete pScene;
				}
				pScene = pSceneNext;
			}
		}
	}
}

//=============================================================================
// �j���֐�
//=============================================================================
void CScene::Release(void)
{
	//���S�t���O���Ă�
	if (this->m_bDeath == false)
	{
		this->m_bDeath = true;
	}
}

//=============================================================================
// �I�u�W�F�N�g�̎�ނ�ݒ�
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//=============================================================================
// �擪�̃I�u�W�F�N�g���擾
//=============================================================================
CScene ** CScene::GetTop(void)
{
	return m_apTop;
}

//=============================================================================
// ���̃I�u�W�F�N�g���擾
//=============================================================================
CScene * CScene::GetNext(void)
{
	return m_pNext;
}

//=============================================================================
// ���݂̃I�u�W�F�N�g���擾
//=============================================================================
CScene * CScene::GetPrev(void)
{
	return m_pPrev;
}

//=============================================================================
// �I�u�W�F�N�g�̎�ނ��擾
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}