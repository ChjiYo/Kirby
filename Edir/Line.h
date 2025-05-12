#pragma once

#include "Define.h"

class CLine
{
public:
	CLine();
	CLine(LINEPOINT& _tLeft, LINEPOINT& _tRight);
	CLine(LINEINFO& _tInfo);
	~CLine();

public:
	void	Render(HDC _hDC);

public:
	const LINEINFO& GetInfo()const { return m_tInfo; }

private:
	LINEINFO m_tInfo;
};

