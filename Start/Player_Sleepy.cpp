#include "Player_Sleepy.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

#include"ObjMgr.h"
#include "Factory.h"
#include "Player_Origin.h"

CPlayer_Sleepy::CPlayer_Sleepy()
{
}

CPlayer_Sleepy::~CPlayer_Sleepy()
{
	Release();
}

void CPlayer_Sleepy::Move()
{
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_bDead = true;
		CObjMgr::GetInst().Add_Create(OBJ_PLAYER, CFactory<CPlayer_Origin>::Create(m_tInfo.fX, m_tInfo.fY));
		dynamic_cast<CPlayer*> (CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back())->SetMoneyInput(m_iNowMoney);
	}
}

void CPlayer_Sleepy::MotionChange()
{

}

void CPlayer_Sleepy::WaterMove()
{
}

void CPlayer_Sleepy::LRKey()
{
}


void CPlayer_Sleepy::Initialize()
{
	m_tInfo = { SCALE_X * 0.5f,SCALE_Y * 0.5f,128.f,128.f };

	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Player/Player_Sleep.bmp", L"Player_Sleep");

	m_pFrameKey = L"Player_Sleep";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 14;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = (DWORD)GetTickCount64() + 500;

	m_eRender = RENDER_GAMEOBJECT;

	m_ePlayerID = PLAYER_SLEEP;
}

int CPlayer_Sleepy::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;

	m_iNowMoney = dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back())->GetMoney();

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CPlayer_Sleepy::LateUpdate()
{
	Move();
	
	__super::MoveFrame();
}

void CPlayer_Sleepy::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScrollX + 128,
		m_tRect.top + 128,
		(int)m_tInfo.fCX ,
		(int)m_tInfo.fCY ,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(144, 152, 200));
}

void CPlayer_Sleepy::Release()
{
}

