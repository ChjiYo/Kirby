#include "Pet_Goust.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

#include "ObjMgr.h"
#include "Player.h"

CPet_Goust::CPet_Goust()
{
	m_fDistance = 0.f;
	m_bMoveStop = false;

	m_dwMoveTimer = (DWORD)GetTickCount64();
}

CPet_Goust::~CPet_Goust()
{
	Release();
}

void CPet_Goust::Move()
{
	m_pTarget = CObjMgr::GetInst().Get_Target(OBJ_PLAYER, this);

	if (m_pTarget)
	{
		float	fWidth(0.f), fHeight(0.f), fDiagonal(0.f);

		fWidth = m_pTarget->GetInfo().fX - m_tInfo.fX;
		fHeight = m_pTarget->GetInfo().fY - m_tInfo.fY;

		fDiagonal = (float)sqrt(fWidth * fWidth + fHeight * fHeight);

		float fRadian = (float)acos(fWidth / fDiagonal);

		if (m_pTarget->GetInfo().fY > m_tInfo.fY)
			fRadian = (2 * PI) - fRadian;

		m_fAngle = fRadian * (180.f / PI);
	}

	m_tInfo.fX += m_fSpeed * (float)cos(m_fAngle * (PI / 180.f));
	m_tInfo.fY -= m_fSpeed * (float)sin(m_fAngle * (PI / 180.f));
}

void CPet_Goust::Dir()
{
	if (dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetDir() == 'L')
	{
		m_pFrameKey = L"Pet_Goust_LEFT";
	}
	else if (dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetDir() == 'R')
	{
		m_pFrameKey = L"Pet_Goust_RIGHT";
	}
}

void CPet_Goust::Initialize()
{
	m_tInfo.fCX = 51.f;
	m_tInfo.fCY = 60.f;

	m_fSpeed = 3.f;

	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Pet/Pet_Goust_Left.bmp", L"Pet_Goust_LEFT");
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Pet/Pet_Goust_Right.bmp", L"Pet_Goust_RIGHT");

	m_pFrameKey = L"Pet_Goust_RIGHT";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_dwMoveTimer = (DWORD)GetTickCount64();

	m_eRender = RENDER_GAMEOBJECT;
}

int CPet_Goust::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;

	m_fDistance = abs(CObjMgr::CObjMgr::GetInst().GetPlayerInfo()->GetInfo().fX - m_tInfo.fX);

	if (m_fDistance <= 10)
	{
		m_bMoveStop = true;
	}

	if (m_dwMoveTimer + 500 < (DWORD)GetTickCount64())
	{
		m_bMoveStop = false;
		m_dwMoveTimer = (DWORD)GetTickCount64();
	}

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CPet_Goust::LateUpdate()
{
	if (!m_bMoveStop)
	{
		Move();
	}
	Dir();
	__super::MoveFrame();
}

void CPet_Goust::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScrollX,
		m_tRect.top,
		(int)m_tInfo.fCX ,
		(int)m_tInfo.fCY ,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(144, 152, 200));
}

void CPet_Goust::Release()
{
}
