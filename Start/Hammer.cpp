#include "Hammer.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "Player.h"

CHammer::CHammer()
{
}

CHammer::~CHammer()
{
	Release();
}

void CHammer::MotionChange()
{
	
}

void CHammer::DamageHit()
{

	if (CCollisionMgr::GetInst().ObjectIDCollisionCheck(OBJ_ATTACK, OBJ_MONSTER))
	{
		dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_MONSTER).back())->SetHp(-m_iDamage);
		m_bDead = true;
	}
}

void CHammer::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Effect/Effect_Hammer.bmp", L"Effect_Hammer");
	m_pFrameKey = L"Effect_Hammer";



	m_tInfo.fCX = 83.f;
	m_tInfo.fCY = 107.f;

	m_fSpeed = 5.f;

	m_eRender = RENDER_EFFECT;

	m_iDamage = 1;
}

int CHammer::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;

	m_tInfo.fY += m_fSpeed;

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CHammer::LateUpdate()
{
	if (m_tInfo.fY > 700.f)
		m_bDead = true;

	DamageHit();

	__super::MoveFrame();
}

void CHammer::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScrollX,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(32, 32, 32));
}

void CHammer::Release()
{
}
