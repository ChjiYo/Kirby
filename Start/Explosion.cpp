#include "Explosion.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CExplosion::CExplosion()
{
	ZeroMemory(&m_eCurState, sizeof(m_eCurState));
	ZeroMemory(&m_ePreState, sizeof(m_ePreState));
}

CExplosion::~CExplosion()
{
	Release();
}

void CExplosion::AnimInst()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case EFFECT_IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case EFFECT_BOOM:
			m_tFrame.iFrameStart = 2;
			m_tFrame.iFrameEnd = 13;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case EFFECT_DISTROY:
			m_tFrame.iFrameStart = 15;
			m_tFrame.iFrameEnd = 24;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CExplosion::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Effect/Effect_Explosion.bmp", L"Explosion");

	m_pFrameKey = L"Explosion";
	
	m_tInfo.fCX = 92.f;
	m_tInfo.fCY = 92.f;

	m_tFrame.iFrameStart = 2;
	m_tFrame.iFrameEnd = 13;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_FRONTEFFECT;

	m_iDamage = 0;
}

int CExplosion::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CExplosion::LateUpdate()
{

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_bDead = true;
	}
	__super::MoveFrame();
}

void CExplosion::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScrollX  + 50,
		m_tRect.top + 50,
		(int)(m_tInfo.fCX) * 2 ,
		(int)(m_tInfo.fCY) * 2,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(116, 154, 212));
}

void CExplosion::Release()
{
}
