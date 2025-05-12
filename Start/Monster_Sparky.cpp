#include "Monster_Sparky.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "LineMgr.h"
#include "Player.h"
#include "ObjMgr.h"

CMonster_Sparky::CMonster_Sparky()
{
	m_fPower = 0;
	m_fTime = 0;
	m_bJump = true;
	m_iHp = 0;
	m_bInhal = false;

	m_bInhalMoveStop = false;
}

CMonster_Sparky::~CMonster_Sparky()
{
	Release();
}

void CMonster_Sparky::Jump()
{
	m_bJump = true;
	m_eCurState = IDLE;

	float fX = 0.f;
	float  fY = 0.f;

	bool bLineCol = CLineMgr::GetInst().Collision_Line(m_tInfo.fX, m_tInfo.fY, &fX, &fY);

	if (m_bJump)
	{
		m_tInfo.fY -= m_fPower - 9.8f * m_fTime * 0.1f;
		m_fTime += 0.1f;

		if (bLineCol && fY < m_tInfo.fY)
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY;
		}
	}
	else if (bLineCol)
	{
		m_fTime += 0.2f;
		m_tInfo.fY -= m_fTime - 9.8f * m_fTime * m_fTime * 0.5f;

		if (bLineCol && fY - m_tInfo.fCY * 0.1f < m_tInfo.fY)
		{
			m_fTime = 0.f;
			m_tInfo.fY = fY - m_tInfo.fCY * 0.1f;
		}
	}

	if (fX <= m_tInfo.fX && fY < m_tInfo.fY)
 		m_fSpeed *= -1;

}

void CMonster_Sparky::MotionChage()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case WALK:
			m_tFrame.iFrameStart = 2;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();

		case INHAL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CMonster_Sparky::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Monster/Mon_Sparky.bmp", L"Mon_Sparky");

	m_pFrameKey = L"Mon_Sparky";

	m_tInfo.fCX = 85.f;
	m_tInfo.fCY = 80.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_fPower = 3.f;

	m_fSpeed = 3.f;

	m_eRender = RENDER_MONSTER;

	m_eMonID = MON_SPARKY;

	m_iHp = 1;

	m_fAngle = 0.f;

	m_fInhalSpeed = 5.f;
}

int CMonster_Sparky::Update()
{
	if (m_bDead)
	{
		return OBJ_DISTORY;
	}
	//m_tInfo.fX -= m_fSpeed;

		m_tInfo.fX += m_fSpeed;
	
	//xuum_tInfo.fY -= m_fSpeed * sin(m_fAngle * (PI / 180.f));
	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CMonster_Sparky::LateUpdate()
{
	if (m_iHp <= 0)
	{
		m_bDead = true;
	}
	Jump();
	//Hit();

	Inhal();

	__super::MoveFrame();
}

void CMonster_Sparky::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScrollX+100,
		m_tRect.top + 100,
		(int)m_tInfo.fCX/2 ,
		(int)m_tInfo.fCY/2,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(1, 255, 255));
}

void CMonster_Sparky::Release()
{
	
}

void CMonster_Sparky::Move()
{
	m_eCurState = WALK;
}
