#pragma once

#include "Define.h"

class CKeyMgr
{
private:
	CKeyMgr();
	~CKeyMgr();

public:
	static CKeyMgr& GetInst()
	{
		static CKeyMgr Inst;
		return Inst;
	}

public:
	bool	KeyPressing(int _iKey);
	bool	KeyDown(int _iKey);
	bool	KeyUp(int _iKey);

private:
	bool	m_bKeyState[VK_MAX];

};

