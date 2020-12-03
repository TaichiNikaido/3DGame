//=============================================================================
//
// �}�l�[�W���[ [manager.h]
// Author : ��K������
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;
class CKeyboard;
class CJoystick;
class CScene2d;
class CSound;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CManager
{
public:
	typedef enum
	{
		MODE_NONE = -1,
		MODE_END
	}MODE;
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; };
	static CRenderer * GetRenderer(void) { return m_pRenderer; };
	static CKeyboard * GetInputKeyboard(void) { return m_pKeyboard; };
	static CJoystick * GetInputJoystick(void) { return m_pJoystick; };
	static CSound * GetSound(void) { return m_pSound; };
	CScene2d * GetScene2d(void) { return m_pScene2d; };
private:
	static CRenderer * m_pRenderer;
	static CKeyboard * m_pKeyboard;
	static CJoystick * m_pJoystick;
	static CSound * m_pSound;
	static MODE m_mode;
	CScene2d * m_pScene2d;
};
#endif