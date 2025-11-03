#include "Gunter_Ice.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "Factory.h"
#include "CollisionMgr.h"

#include "Player.h"

CGunter_Ice::CGunter_Ice()
{
	m_dwDamageTimer = (DWORD)GetTickCount64();
}

CGunter_Ice::~CGunter_Ice()
{
}

void CGunter_Ice::DamageHit()
{
	if (CCollisionMgr::GetInst().ObjectIDCollisionCheck(OBJ_ATTACK, OBJ_SPECIAL_MONSTER) && m_dwDamageTimer + 500 < (DWORD)GetTickCount64())
	{
		dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_SPECIAL_MONSTER).back())->SetHp(-m_iDamage);
		m_dwDamageTimer = (DWORD)GetTickCount64();
	}

	if (CCollisionMgr::GetInst().ObjectIDCollisionCheck(OBJ_ATTACK, OBJ_MONSTER)&& m_dwDamageTimer + 500 < (DWORD)GetTickCount64())
	{
		dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_MONSTER).back())->SetHp(-m_iDamage);
		m_dwDamageTimer = (DWORD)GetTickCount64();
	}
}


void CGunter_Ice::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Effect/Effect_Gunter/Effect_Gunter_Left.bmp", L"Effect_Gunter_LEFT");
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Effect/Effect_Gunter/Effect_Gunter_Right.bmp", L"Effect_Gunter_RIGHT");

	m_pFrameKey = L"Effect_Gunter_RIGHT";

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_dwDeltaTime = (DWORD)(GetTickCount64() * 0.001f);

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_EFFECT;

	m_iDamage = 1;
}

int CGunter_Ice::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;

	if (CObjMgr::GetInst().GetObjectList(OBJ_MONSTER).back()->GetSpeed() > 0.f)
	{
		m_pFrameKey = L"Effect_Gunter_LEFT";
	

	}
	else if(CObjMgr::GetInst().GetObjectList(OBJ_MONSTER).back()->GetSpeed() <= 0.f)
	{
		m_pFrameKey = L"Effect_Gunter_RIGHT";
		
	}

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CGunter_Ice::LateUpdate()
{
	if (m_tFrame.iFrameStart == 5)
	{
		m_bDead = true;
	}

	/*if (CCollisionMgr::GetInst().SetCharacherHpCheck(CObjMgr::GetInst().GetPlayerList(), CObjMgr::GetInst().GetMonAttackList()))
	{
		dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back())->SetHp();
	}*/
	DamageHit();
	__super::MoveFrame();
}

void CGunter_Ice::Render(HDC _hDC)
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
		RGB(0, 0, 115));
}

void CGunter_Ice::Release()
{
}

