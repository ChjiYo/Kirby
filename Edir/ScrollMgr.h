#pragma once

#include "Define.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	static CScrollMgr& GetInst()
	{
		static CScrollMgr Inst;
		return Inst;
	}

public:
	const float& GetScrollX() const { return m_fScrollX; }
	const float& GetScrollY() const { return m_fScrollY; }

	void SetScrollX(float _fX) { m_fScrollX += _fX; }
	void SetScrollY(float _fY) { m_fScrollY += _fY; }

private:
	float m_fScrollX;
	float m_fScrollY;

};

