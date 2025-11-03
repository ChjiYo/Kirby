#include "AbilityStar.h"
#include "BmpMgr.h"
#include "Player.h"

#include "ObjMgr.h"
#include "Monster.h"
#include "LineMgr.h"

CAbilityStar::CAbilityStar()
{
	m_dwDeltaTime = 0;
	m_iScrollX = 0;
	m_fAttackRange = 0.f;
	m_MonStarID = MON_END;

	m_bJump = false;
	m_fPower = 0.f;
	m_fTime = 0.f;
}

CAbilityStar::~CAbilityStar()
{
	Release();
}

void CAbilityStar::Move()
{
	m_bJump = true;

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
}

void CAbilityStar::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Effect/Effect_Star/EffectStar.bmp", L"Effect_Ability_Star");

	m_pFrameKey = L"Effect_Ability_Star";

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_fSpeed = 5.f;

	m_dwDeltaTime = (DWORD)(GetTickCount64() * 0.001f);

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_GAMEOBJECT;

	m_fAttackRange = 100.f;

	m_iDamage = 1;
	m_MonStarID = dynamic_cast<CMonster*>(CObjMgr::GetInst().GetObjectList(OBJ_MONSTER).back())->GetID();
}

int CAbilityStar::Update()
{
	if(m_bDead)
	return OBJ_DISTORY;

	if (dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back())->GetDir() == 'L')
	{
		m_pFrameKey = L"Effect_Star";
	}
	else if (dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back())->GetDir() == 'R')
	{
		m_pFrameKey = L"Effect_Star";
	}

	return OBJ_NOEVENT;
}

void CAbilityStar::LateUpdate()
{
}

void CAbilityStar::Render(HDC _hDC)
{
}

void CAbilityStar::Release()
{
}
