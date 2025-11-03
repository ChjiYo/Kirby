#include "Ice.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

#include "ObjMgr.h"
#include "Player_Ice.h"
#include "CollisionMgr.h"
#include "Monster.h"
#include "Factory.h"
#include "Ice_Block.h"
#include "Inhal.h"

#include "LineMgr.h"

CIce::CIce()
{
	m_dwDamageTimer = (DWORD)GetTickCount64();
}

CIce::~CIce()
{
	Release();
}

void CIce::DamageHit()
{

	if (CCollisionMgr::GetInst().ObjectIDCollisionCheck(OBJ_MONSTER, OBJ_MONSTER) && m_dwDamageTimer + 200 < (DWORD)GetTickCount64())
	{
 		dynamic_cast<CMonster*>(CObjMgr::GetInst().GetMonsterInfo())->SetHp(-m_iDamage);
		m_dwDamageTimer = (DWORD)GetTickCount64();

		if (dynamic_cast<CMonster*>(CObjMgr::GetInst().GetMonsterInfo())->GetHp() <= 0)
		{
			CObjMgr::GetInst().Add_Create(OBJ_ATTACK, CFactory<CIce_Block>::Create(CObjMgr::GetInst().GetMonsterInfo()->GetInfo().fX, CObjMgr::GetInst().GetMonsterInfo()->GetInfo().fY));
		}
	}

	if (CCollisionMgr::GetInst().ObjectIDCollisionCheck(OBJ_ATTACK, OBJ_SPECIAL_MONSTER) && (m_dwDamageTimer + 200 < (DWORD)GetTickCount64()))
	{
		dynamic_cast<CMonster*>(CObjMgr::GetInst().GetMonEpickInfo())->SetHp(-m_iDamage);
		m_dwDamageTimer = (DWORD)GetTickCount64();
	}

}

void CIce::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Effect/Effect_Ice/LIce_effect.bmp", L"EFFECT_ICE_LEFT");
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Effect/Effect_Ice/Ice_effect.bmp", L"EFFECT_ICE_RIGHT");

	m_pFrameKey = L"EFFECT_ICE_RIGHT";

	m_tInfo.fCX = 61.f;
	m_tInfo.fCY = 41.f;

	m_fSpeed = 5.f;

	m_dwDeltaTime = (DWORD)(GetTickCount64() * 0.001f);

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_GAMEOBJECT;

	m_fAttackRange = 100.f;

	m_iDamage = 1;
	
}

int CIce::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CIce::LateUpdate()
{
	if (m_tFrame.iFrameStart == 6 )
	{
		m_bDead = true;
		
	}


	MotionChange();
	DamageHit();
	__super::MoveFrame();
}

void CIce::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScrollX,
		m_tRect.top,
		(int)m_tInfo.fCX * 3,
		(int)m_tInfo.fCY * 3,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(136, 24, 192));
}

void CIce::Release()
{
}
