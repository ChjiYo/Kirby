#include "Change.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CChange::CChange()
{
}

CChange::~CChange()
{
	Release();
}

void CChange::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Effect/Effect_Change.bmp", L"Effect_Change");

	m_pFrameKey = L"Effect_Change";

	m_tInfo.fCX = 81.f;
	m_tInfo.fCY = 83.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_FRONTEFFECT;

	m_iDamage = 0;
}

int CChange::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CChange::LateUpdate()
{
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_bDead = true;
	}
	__super::MoveFrame();
}

void CChange::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScrollX,
		m_tRect.top ,
		(int)(m_tInfo.fCX) * 3,
		(int)(m_tInfo.fCY) * 3,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(210, 210, 255));
}

void CChange::Release()
{
}
