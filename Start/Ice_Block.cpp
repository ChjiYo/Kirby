#include "Ice_Block.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Player.h"

CIce_Block::CIce_Block()
{
	m_fTime = 0.f;
	m_bTouch = false;
}

CIce_Block::~CIce_Block()
{
	Release();
}

void CIce_Block::Land()
{
	float fX = 0.f;
	float  fY = 0.f;

	bool bLineCol = CLineMgr::GetInst().Collision_Line(m_tInfo.fX, m_tInfo.fY, &fX, &fY);
	if (bLineCol)
	{
		m_fTime += 0.2f;
		m_tInfo.fY -= m_fTime - 9.8f * m_fTime * m_fTime * 0.5f;

		if (bLineCol && fY  < m_tInfo.fY)
		{
			m_fTime = 0.f;
			m_tInfo.fY = fY +30;
		}
	}
}

void CIce_Block::Touch()
{
	if (m_bTouch)
	{

		if (dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetDir() == 'R')
		{
			m_tInfo.fX += m_fSpeed;
		}
		else if (dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetDir() == 'L')
		{
			m_tInfo.fX -= m_fSpeed;
		}
	}
}

void CIce_Block::Initialize()
{
    CBmpMgr::GetInst().InsertBmp(L"../Kirby/Effect/Effect_Ice/Effect_Ice_RectangleA.bmp", L"EFFECT_ICE_Block");

	m_pFrameKey = L"EFFECT_ICE_Block";

	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 48.f;

	m_fSpeed = 0.f;

	m_dwDeltaTime = (DWORD)(GetTickCount64() * 0.001f);

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_GAMEOBJECT;
}

int CIce_Block::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;

	__super::RectUpdate();

    return OBJ_NOEVENT;
}

void CIce_Block::LateUpdate()
{
	Land();

	/*if (CCollisionMgr::GetInst().SetCharacherHpCheck(CObjMgr::GetInst().GetAttackList(), CObjMgr::GetInst().GetPlayerList()))
	{
		m_bTouch = true;
		m_fSpeed = 5.f;
	}*/
	Touch();

}

void CIce_Block::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScrollX,
		m_tRect.top,
		(int)m_tInfo.fCX ,
		(int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(146, 196, 67));
}

void CIce_Block::Release()
{
}
