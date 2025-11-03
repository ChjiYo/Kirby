#include "Monster_Gunter.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "Inhal.h"
#include "CollisionMgr.h"
#include "Inhal.h"
#include "Player_Origin.h"
#include "Gunter_Ice.h"
#include "Factory.h"

CMonster_Gunter::CMonster_Gunter()
{
	m_iHp = 0;
	m_iAttackRange = 0.f;
	m_fDistance = 0.f;
	m_bMoveStop = false;
	m_dwAttackTimer = (DWORD)GetTickCount64();
	m_fTime = 0.f;
	m_bAttackStop = false;
	m_fMoveRange = 0.f;
}

CMonster_Gunter::~CMonster_Gunter()
{
	Release();
}

void CMonster_Gunter::MotionChage()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case WALK:
			m_tFrame.iFrameStart = 1;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 3;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case INHAL:
			m_tFrame.iFrameStart = 6;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CMonster_Gunter::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Monster/Monster_Gunter/New_Mon_Gunter_Left.bmp", L"Mon_Gunter_Left");
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Monster/Monster_Gunter/New_Mon_Gunter_Right.bmp", L"Mon_Gunter_Right");

	m_pFrameKey = L"Mon_Gunter_Left";

	m_tInfo.fCX = 38.f;
	m_tInfo.fCY = 35.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_fSpeed = 3.f;

	m_eRender = RENDER_MONSTER;

	m_eMonID = MON_GUNTER;

	m_iHp = 1;

	m_iAttackRange = 100.f;

	m_fInhalSpeed = 5.f;
}

int CMonster_Gunter::Update()
{
	if (m_bDead)
	{
		return OBJ_DISTORY;
	}

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CMonster_Gunter::LateUpdate()
{
	if (m_iHp <= 0)
	{
		m_bDead = true;
	}
	m_fDistance = abs(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back()->GetInfo().fX - m_tInfo.fX);

	MotionChage();
	if(!m_bMoveStop)
	{
		Move();
	}
	Land();

	if (!m_bAttackStop)
	{
		Atttack();
	}

	//Hit();
	bool bResult = Inhal();
	if (bResult)
	{
		m_bAttackStop = true;
	}
	else

	{
		m_bAttackStop = false;
	}
	__super::MoveFrame();

}

void CMonster_Gunter::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScrollX,
		m_tRect.top,
		(int)m_tInfo.fCX * 2,
		(int)m_tInfo.fCY * 2,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(237, 28, 36));
}

void CMonster_Gunter::Release()
{
}

void CMonster_Gunter::Move()
{
	m_tInfo.fX += m_fSpeed;

	float fX = 0.f;
	float  fY = 0.f;

	bool bLineCol = CLineMgr::GetInst().Collision_Line(m_tInfo.fX, m_tInfo.fY, &fX, &fY);

	m_fMoveRange += m_fSpeed;

	if (m_fMoveRange > 180.f || m_fMoveRange < -180.f)
	{
		m_fSpeed *= -1;
		m_fMoveRange = 0.f;
	}

	if (m_fSpeed < 0.f)
	{
		m_pFrameKey = L"Mon_Gunter_Left";

	}
	else
	{
		m_pFrameKey = L"Mon_Gunter_Right";
	}

	m_eCurState = WALK;

}

void CMonster_Gunter::Land()
{
	float fX = 0.f;
	float  fY = 0.f;

	bool bLineCol = CLineMgr::GetInst().Collision_Line(m_tInfo.fX, m_tInfo.fY, &fX, &fY);
		if (bLineCol)
		{
			m_fTime += 0.2f;
			m_tInfo.fY -= m_fTime - 9.8f * m_fTime * m_fTime * 0.5f;

			if (bLineCol && fY - m_tInfo.fCY * 0.1f < m_tInfo.fY)
			{
				m_fTime = 0.f;
				m_tInfo.fY = fY - m_tInfo.fCY * 0.1f;
			}
		}
}

void CMonster_Gunter::Atttack()
{
	if (m_fDistance <= m_iAttackRange)
	{
		m_eCurState = ATTACK;
		m_bMoveStop = true;

		if (m_dwAttackTimer + 800 < (DWORD)GetTickCount64())
		{
			if (CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back()->GetInfo().fX < m_tInfo.fX)
			{
				m_pFrameKey = L"Mon_Gunter_Left";
				CObjMgr::GetInst().Add_Create(OBJ_MONATTACK, CFactory<CGunter_Ice>::Create(m_tInfo.fX - 80, m_tInfo.fY, -90.f));

			}
			else if (CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back()->GetInfo().fX > m_tInfo.fX)
			{
				m_pFrameKey = L"Mon_Gunter_Right";
				CObjMgr::GetInst().Add_Create(OBJ_MONATTACK, CFactory<CGunter_Ice>::Create(m_tInfo.fX + 80, m_tInfo.fY, -90.f));
			}

			m_dwAttackTimer = (DWORD)GetTickCount64();
		}
	}
	else
	{
		m_bMoveStop = false;
	}
}
