#include "Monster_Sleepy.h"
#include"ObjMgr.h"	
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "LineMgr.h"

//플레이어가 보일 떄 수면 상태 돌입 
//슬리피를 먹었을 때는 플레이어가 수면상태로 바뀌면서 체력 회복

CMonster_Sleepy::CMonster_Sleepy()
{
	m_fDistance = 0.f;
	m_bMoveStop = true;
	m_fTime = 0.f;
}

CMonster_Sleepy::~CMonster_Sleepy()
{
	Release();
}

void CMonster_Sleepy::Move()
{
	m_fDistance = abs(CObjMgr::GetInst().GetPlayerInfo()->GetInfo().fX - m_tInfo.fX);

	if (m_fDistance <= 200 && m_tFrame.iFrameStart != m_tFrame.iFrameEnd)
	{
 		__super::MoveFrame();
	}

}

void CMonster_Sleepy::Land()
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

void CMonster_Sleepy::MotionChage()
{
}


void CMonster_Sleepy::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Monster/Mon_Sleepy.bmp", L"Mon_Sleepy");
	m_pFrameKey = L"Mon_Sleepy";

	m_tInfo.fCX = 128.f;
	m_tInfo.fCY = 128.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eMonID = MON_SLEEPY;

	m_fSpeed =3.f;

	m_iHp = 1;

	m_fInhalSpeed = 5.f;

	m_eRender = RENDER_MONSTER;
}

int CMonster_Sleepy::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;


	
	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CMonster_Sleepy::LateUpdate()
{
	if (m_iHp <= 0)
	{
		m_bDead = true;
	}

	Land();
	Move();
	Inhal();
	
}

void CMonster_Sleepy::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScrollX + 150,
		m_tRect.top + 150,
		(int)(m_tInfo.fCX * 0.7f),
		(int)(m_tInfo.fCY * 0.7f),
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(144, 152, 200));
}

void CMonster_Sleepy::Release()
{
}
