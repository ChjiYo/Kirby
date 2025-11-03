#include "Star.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

#include "CollisionMgr.h"
#include "Monster.h"

#include "Player.h"

#include "LineMgr.h"
#include "Factory.h"

#include "Explosion.h"
#include "SoundMgr.h"

CStar::CStar()
{
	m_dwDeltaTime = 0;
	m_iScrollX = 0;
	m_fAttackRange = 0.f;
	m_fVolume = 1.f;
}

CStar::~CStar()
{
	Release();
}

void CStar::DamageHit()
{
	if (CCollisionMgr::GetInst().ObjectIDCollisionCheck(OBJ_ATTACK, OBJ_SPECIAL_MONSTER))
	{
		dynamic_cast<CMonster*>(CObjMgr::GetInst().GetMonEpickInfo())->SetHp(-m_iDamage);
		m_bDead = true;
	}

	if (CCollisionMgr::GetInst().ObjectIDCollisionCheck(OBJ_ATTACK, OBJ_MONSTER))
	{
		dynamic_cast<CMonster*>(CObjMgr::GetInst().GetMonsterInfo())->SetHp(-m_iDamage);
		m_bDead = true;
	}
}

void CStar::Distory()
{
	float fX = 0.f;
	float  fY = 0.f;

	bool bLineCol = CLineMgr::GetInst().Collision_Line(m_tInfo.fX, m_tInfo.fY, &fX, &fY);

	if (fX <= m_tInfo.fX && fY < m_tInfo.fY)
	{
		m_bDead = true;
	}


}

void CStar::Initialize()
{
	//CSoundMgr::GetInst().PlaySoundW(L"03_Star.wav", SOUND_EFFECT, m_fVolume);
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Effect/Effect_Star/EffectStar.bmp", L"Effect_Star");

	m_pFrameKey = L"Effect_Star";

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 92.f;

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
}

int CStar::Update()
{
	if (m_bDead)
	{
		CObjMgr::GetInst().Add_Create(OBJ_ATTACK, CFactory<CExplosion>::Create(m_tInfo.fX, m_tInfo.fY));
		return OBJ_DISTORY;
	}
	m_tInfo.fX += m_fSpeed * (float)cos(m_fAngle * (PI / 180.f));
	m_tInfo.fY -= m_fSpeed * (float)sin(m_fAngle * (PI / 180.f));

	if (dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetDir() == 'L')
	{
		m_pFrameKey = L"Effect_Star";
	}
	else if (dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetDir() == 'R')
	{
		m_pFrameKey = L"Effect_Star";
	}

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CStar::LateUpdate()
{
	if (CCollisionMgr::GetInst().ObjectIDCollisionCheck(OBJ_ATTACK, OBJ_MONSTER))
	{
		dynamic_cast<CMonster*>(CObjMgr::GetInst().GetMonsterInfo())->SetHp(-1);
		m_bDead = true;
	}
	//if (CCollisionMgr::GetInst().Collision_Sphere(CObjMgr::GetInst().GetAttackList(), CObjMgr::GetInst().GetMonsterList()))
	//{
	//	
	//}

	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();

	float PlayerPosX = CObjMgr::GetInst().GetPlayerInfo()->GetInfo().fX;
	float PlayerPosY = CObjMgr::GetInst().GetPlayerInfo()->GetInfo().fY;

	DamageHit();
	Distory();
	MotionChange();
	__super::MoveFrame();
}

void CStar::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScrollX + 125,
		m_tRect.top + 125,
		(int)(m_tInfo.fCX * 0.5f),
		(int)(m_tInfo.fCY * 0.5f),
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(207, 176, 254));
}

void CStar::Release()
{
}
