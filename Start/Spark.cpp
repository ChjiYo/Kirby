#include "Spark.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

#include "Player.h"
#include "CollisionMgr.h"
#include "Monster.h"

CSpark::CSpark()
{
	m_dwDeltaTime = 0;
	m_iScrollX = 0;
	m_fAttackRange = 0.f;
	m_dwDamageTimer = (DWORD)GetTickCount64();
}

CSpark::~CSpark()
{
	Release();
}

void CSpark::DamageHit()
{
	if (CCollisionMgr::GetInst().ObjectCollisionCheck(CObjMgr::GetInst().GetAttackList(), CObjMgr::GetInst().GetMonEpickList()) )
	{
		dynamic_cast<CMonster*>(CObjMgr::GetInst().GetMonEpickInfo())->SetHp(-m_iDamage);
	}

	if (CCollisionMgr::GetInst().ObjectCollisionCheck(CObjMgr::GetInst().GetAttackList(), CObjMgr::GetInst().GetMonsterList()))
	{
		dynamic_cast<CMonster*>(CObjMgr::GetInst().GetMonsterInfo())->SetHp(-m_iDamage);

		if (dynamic_cast<CMonster*>(CObjMgr::GetInst().GetMonsterInfo())->GetHp() <= 0)
		{
			dynamic_cast<CMonster*>(CObjMgr::GetInst().GetMonsterInfo())->KillCount();
	
		}

	}
}

void CSpark::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Effect/Effect_Spark.bmp", L"Effect_Spark");
	
	m_pFrameKey = L"Effect_Spark";

	m_tInfo.fCX = 321.f;
	m_tInfo.fCY = 434.f;

	m_dwDeltaTime = (DWORD)GetTickCount64();

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_EFFECT;

	m_fAttackRange = 100.f;

	m_iDamage = 1;
}

int CSpark::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CSpark::LateUpdate()
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();

	if (m_dwDeltaTime + 250  < (DWORD)GetTickCount64() )
	{
		m_bDead = true;
		m_dwDeltaTime = (DWORD)GetTickCount64();
	}

	MotionChange();
	DamageHit();

	__super::MoveFrame();
}

void CSpark::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey); 

	GdiTransparentBlt(
		_hDC,
		(int)(m_tInfo.fX+ iScrollX - 110),
		(int)(m_tInfo.fY - 175),
		(int)(m_tInfo.fCX * 0.75f),
		(int)(m_tInfo.fCY * 0.75f),
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(0, 0, 0));
}

void CSpark::Release()
{
}
