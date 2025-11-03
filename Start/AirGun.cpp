#include "AirGun.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

#include "CollisionMgr.h"
#include "Monster.h"

#include "Player.h"

CAirGun::CAirGun()
{

}

CAirGun::~CAirGun()
{
	Release();
}

void CAirGun::Initialize()
{

	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Effect/Effect_AirGun/Effect_AirGun_Left.bmp", L"AirGun_LEFT");
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Effect/Effect_AirGun/Effect_AirGun_Right.bmp", L"AirGun_RIGHT");

	m_pFrameKey = L"AirGun_RIGHT";

	m_tInfo.fCX = 31.f;
	m_tInfo.fCY = 29.f;

	m_fSpeed = 5.f;

	m_dwDeltaTime = (DWORD)(GetTickCount64() * 0.001f);

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_GAMEOBJECT;

	m_iDamage = 1;
}

int CAirGun::Update()
{
	if(m_bDead)
	 return OBJ_DISTORY;

	m_tInfo.fX += m_fSpeed * (float)(cos(m_fAngle * (PI / 180.f)));
	m_tInfo.fY -= m_fSpeed * (float)(sin(m_fAngle * (PI / 180.f)));

	if (dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back())->GetDir() == 'L')
	{
		m_pFrameKey = L"AirGun_LEFT";
	}
	else if (dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back())->GetDir() == 'R')
	{
		m_pFrameKey = L"AirGun_RIGHT";
	}

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CAirGun::LateUpdate()
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();

	float PlayerPosX = CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back()->GetInfo().fX;
	float PlayerPosY = CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back()->GetInfo().fY;

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bDead = true;

	MotionChange();
	DamageHit();

	__super::MoveFrame();
}

void CAirGun::Render(HDC _hDC)
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

void CAirGun::Release()
{
}

void CAirGun::DamageHit()
{
	CMonster* pMonster = dynamic_cast<CMonster*>(CCollisionMgr::GetInst().FindCollObject(OBJ_ATTACK, OBJ_MONSTER));

	if (pMonster != nullptr)
	{
		pMonster->SetHp(-1);
		m_bDead = true;
	}


	CMonster* pEpicMonster = dynamic_cast<CMonster*>(CCollisionMgr::GetInst().FindCollObject(OBJ_ATTACK, OBJ_SPECIAL_MONSTER));

	if (pEpicMonster != nullptr)
	{
		pEpicMonster->SetHp(-1);
		m_bDead = true;
	}
}
