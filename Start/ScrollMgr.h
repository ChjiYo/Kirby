#pragma once

#include "Define.h"
#include "Obj.h"

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
	void	ScrollLock();

public:
	const float& GetScrollX() const { return m_fScrollX; }
	const float& GetScrollY() const { return m_fScrollY; }

	void SetScrollX(){ m_fScrollX = 0; }
	void SetScrollY() { m_fScrollY = 0; }

	void SetScrollX(float _fX)
	{
		m_fScrollX += _fX;	
	}
	void SetScrollY(float _fY) { m_fScrollY += _fY; }

public:
	float m_fScrollX;
	float m_fScrollY;
};

