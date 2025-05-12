#include "Line.h"
#include "ScrollMgr.h"

CLine::CLine()
{

}

CLine::CLine(LINEPOINT& _tLeft, LINEPOINT& _tRight)
{
	m_tInfo.tLeft = _tLeft;
	m_tInfo.tRight = _tRight;
}

CLine::CLine(LINEINFO& _tInfo)
{
	m_tInfo = _tInfo;
}

CLine::~CLine()
{

}

void CLine::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();

	MoveToEx(_hDC, (int)m_tInfo.tLeft.fX + iScrollX, (int)m_tInfo.tLeft.fY, NULL);
	LineTo(_hDC, (int)m_tInfo.tRight.fX + iScrollX, (int)m_tInfo.tRight.fY);



}