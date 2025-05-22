#include "KeyMgr.h"

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
	
	
}

CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::Key_Pressing(int _iKey)
{
	if (GetAsyncKeyState(_iKey) & 0x8000)
		return true;

	return false;
}


bool CKeyMgr::Key_Down(int _iKey)
{
	if ((!m_bKeyState[_iKey]) && (GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}

	return false;
}

bool CKeyMgr::Key_Up(int _iKey)
{
	if ((m_bKeyState[_iKey]) && !(GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (!m_bKeyState[i] && (GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}

	return false;
}

int CKeyMgr::GetPressingKey()
{
	for (int i = 0; i < 256; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000)
		{
			return i;
		}
	}

	return 0;
}

int CKeyMgr::GetDownKey()
{

	for (int i = 0; i < 255; i++)
	{
		if ((!m_bKeyState[i]) && (GetAsyncKeyState(i) & 0x8000))
		{
			m_bKeyState[i] = !m_bKeyState[i];
			return i;
		}
	}
	for (int i = 0; i < VK_MAX; ++i)
	{
		if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}

	return -1;
}
