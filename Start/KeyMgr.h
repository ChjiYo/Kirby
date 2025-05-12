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
	bool		Key_Pressing(int _iKey);

	bool		Key_Down(int _iKey);
	bool		Key_Up(int _iKey);

private:
	bool m_bKeyState[VK_MAX];
};

