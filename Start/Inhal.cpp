#include "Inhal.h"

#include "BmpMgr.h"
#include "Player.h"
#include "ObjMgr.h"

#include "ScrollMgr.h"

CInhal::CInhal()
{
}

CInhal::~CInhal()
{
}

void CInhal::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Effect/Effect_Absorbe.bmp", L"Effect_Absorbe");

	m_pFrameKey = L"Effect_Absorbe";

	m_tInfo.fCX = 280.f;
	m_tInfo.fCY = 136.f;

	m_fAttackRange = 280.f;

	m_dwDeltaTime = (DWORD)(GetTickCount64() * 0.001f);

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 8;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_GAMEOBJECT;
}

int CInhal::Update()
{
	if(m_bDead)
	return OBJ_DISTORY;

	__super::RectUpdate();
	return OBJ_NOEVENT;
}

void CInhal::LateUpdate()
{
	if (m_tFrame.iFrameStart == 8)
	{
		m_bDead = true;
	}

	

	
}

void CInhal::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScrollX,
		m_tRect.top,
		(int)(m_tInfo.fCX  * 0.5f),
		(int)(m_tInfo.fCY * 0.5f),
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(144, 152, 200));
	__super::MoveFrame();
}

void CInhal::Release()
{


}
