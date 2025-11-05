#include "DDDKing.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "Player.h"

#include "Factory.h"
#include "Hammer.h"
#include "SceneMgr.h"

/*
공격패턴
1.망치를 들고 달려오면서 찍는 공격 

2.망치가 하늘에서 소환되는 공격 

3.별이 생성되서 일직선 방향으로 날리는 능력 

*/

CDDDKing::CDDDKing()
{
	m_fTime = 0.f;
	m_bMoveStop = false;
	m_fDistance = 0.f;
	m_dwWaitTimer = (DWORD)GetTickCount64();

	m_dwAttackTimerA = (DWORD)GetTickCount64();
	m_fAttackRangeA = 0.f;

	m_dwAttackTimerB = (DWORD)GetTickCount64();
	m_fAttackRangeB = 0.f;

	m_dwDeathTimer = (DWORD)GetTickCount64();
}

CDDDKing::~CDDDKing()
{
	Release();
}

void CDDDKing::Land()
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

void CDDDKing::Move()
{
	if (m_tInfo.fX < CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back()->GetInfo().fX )
	{
		m_tInfo.fX += m_fSpeed;
		m_pFrameKey = L"DDDKING_RIGHT";
	}

	else if(m_tInfo.fX > CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back()->GetInfo().fX )
	{
		m_tInfo.fX -= m_fSpeed;
		m_pFrameKey = L"DDDKING_LEFT";
	}
	
	m_eCurState = WALK;

}

//속도상승
void CDDDKing::AttackA()
{
	if (m_dwAttackTimerA + 10000 < (DWORD)GetTickCount64())
	{
		m_eCurState = WAIT;

		if (m_fAttackRangeA > m_fDistance)
		{
			m_bMoveStop = true;
			m_eCurState = ATTACK;
			m_dwAttackTimerA = (DWORD)GetTickCount64();
		}
	}
}

void CDDDKing::AttackB()
{
	if ((m_dwAttackTimerB + 15000 < (DWORD)GetTickCount64() ) && ( m_fAttackRangeB <  m_fDistance ) )
	{
		m_bMoveStop = true;
		m_eCurState = ABILITY;

		for (int i = 1; i <= 5; i++)
			CObjMgr::GetInst().Add_Create(OBJ_MONATTACK, CFactory<CHammer>::Create(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back()->GetInfo().fX -600 + i * 200 , 100));
		
		m_dwAttackTimerB = (DWORD)GetTickCount64();
	}
}

void CDDDKing::AttackC()
{ 
}

void CDDDKing::MotionChage()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case WALK:
			m_tFrame.iFrameStart = 4;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case JUMP:
			m_tFrame.iFrameStart = 8;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case WAIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case ABILITY:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case DIE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 5
				;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CDDDKing::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Boss/Boss_DDDking_Left.bmp", L"DDDKING_LEFT");
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Boss/Boss_DDDking_Right.bmp", L"DDDKING_RIGHT");

	m_pFrameKey = L"DDDKING_LEFT";

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_fSpeed = 3.f;

	m_eRender = RENDER_MONSTER;

	m_iHp = 20;

	m_fAttackRangeA = 100.f;
	m_fAttackRangeB = 400.f;
}

int CDDDKing::Update()
{
	if(m_bDead)
		return OBJ_DISTORY;

	m_fDistance = abs(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back()->GetInfo().fX - m_tInfo.fX);

	if (m_dwWaitTimer + 1500 < (DWORD)GetTickCount64())
	{
		m_bMoveStop = false;
		m_dwWaitTimer = (DWORD)GetTickCount64();
	}

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CDDDKing::LateUpdate()
{
	if (m_iHp <= 0)
	{
		m_eCurState = DIE;
		m_bMoveStop = true;

		if (m_dwDeathTimer + 250 < (DWORD)GetTickCount64())
		{
			m_tInfo.fY += 50;

			if (m_tInfo.fY > 800.f)
			{
				CSceneMgr::GetInst().Scene_Change(SC_VEDEO);
			}
			m_dwDeathTimer = (DWORD)GetTickCount64();
		}
		m_iHp = 0;
	}
		

	MotionChage();
	Land();
	//Hit();

	if (!m_bMoveStop)
	{
		Move();
	}

	if (CCollisionMgr::GetInst().ObjectIDCollisionCheck(OBJ_PLAYER, OBJ_MONSTER))
	{
		m_bMoveStop = true;
	}

	AttackA();
	AttackB();
	AttackC();

	__super::MoveFrame();
}

void CDDDKing::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScrollX+ 50,
		m_tRect.top,
		(int)m_tInfo.fCX * 2,
		(int)m_tInfo.fCY * 2,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(12, 230, 248));

	/*TCHAR		szHp[64] = L"";

	swprintf_s(szHp, L"HP : %d", m_iHp);
	TextOut(_hDC, 200, 500, szHp, lstrlen(szHp));*/
}

void CDDDKing::Release()
{
}
