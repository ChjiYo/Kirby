#include "Wadle.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"

CWadle::CWadle()
{
	m_fMoveRange = 0.f;
	m_fTime = 0.f;
}

CWadle::~CWadle()
{
	Release();
}

void CWadle::Move()
{
	if (m_fSpeed > 0)
	{
		m_pFrameKey = L"Wadle_Right";
	}
	else
	{
		m_pFrameKey = L"Wadle_Left";
	}

	m_fMoveRange += m_fSpeed;

	if (m_fMoveRange > 400.f || m_fMoveRange < -400.f)
	{
		m_fSpeed *= -1;
		m_fMoveRange = 0.f;
	}

	Land();
}

void CWadle::Land()
{
	float fX = 0.f;
	float  fY = 0.f;

	bool bLineCol = CLineMgr::GetInst().Collision_Line(m_tInfo.fX, m_tInfo.fY, &fX, &fY);

	m_fTime += 0.2f;
	m_tInfo.fY -= m_fTime - 9.8f * m_fTime * m_fTime * 0.5f;

	if (bLineCol && fY - m_tInfo.fCY * 0.1f < m_tInfo.fY)
	{
		m_fTime = 0.f;
		m_tInfo.fY = fY - m_tInfo.fCY * 0.1f;
	}
}

void CWadle::MotionChage()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;


		case INHAL:
			m_tFrame.iFrameStart = 1;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;
		}

		m_ePreState = m_eCurState;
	} 
}

void CWadle::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Monster/Monster_Wadle/Mon_BigPang_Left.bmp", L"Wadle_Left");
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Monster/Monster_Wadle/Mon_BigPang_Right.bmp", L"Wadle_Right");

	m_pFrameKey = L"Wadle_Right";

	m_tInfo.fCX = 35.f;
	m_tInfo.fCY = 35.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_MONSTER;

	m_eMonID = MON_NONE;

	m_iHp = 1;

	m_fSpeed = 3.f;
	m_fAngle = 0.f;

	m_fInhalSpeed = 5.f;
}

int CWadle::Update()
{
	if (m_bDead)
	{
		KillCount();
		return OBJ_DISTORY;
	}
	m_tInfo.fX += m_fSpeed;

	__super::RectUpdate();

	return OBJ_NOEVENT;

}

void CWadle::LateUpdate()
{
	if (m_iHp <= 0)
	{
		m_bDead = true;
		
	}
	Inhal();
	Move();

	//Hit();

	__super::MoveFrame();
}

void CWadle::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScrollX + 50,
		m_tRect.top,
		(int)m_tInfo.fCX *2,
		(int)m_tInfo.fCY * 2,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(0, 160, 80));
}

void CWadle::Release()
{
}
