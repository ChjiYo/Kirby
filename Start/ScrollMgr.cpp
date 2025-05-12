#include "ScrollMgr.h"

CScrollMgr::CScrollMgr()
{
	m_fScrollX = 0.f;
	m_fScrollY = 0.f;
}

CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::ScrollLock()
{
	if (0.f < m_fScrollX)
	{
		m_fScrollX = 0.f;
	}

	if (0.f < m_fScrollY)
	{
		m_fScrollY = 0.f;
	}

	if (SCALE_X - 4761 > m_fScrollX)
		m_fScrollX = SCALE_X - 4761;

	if (SCALE_Y - 600 > m_fScrollY)
		m_fScrollY = SCALE_Y - 600;
}
