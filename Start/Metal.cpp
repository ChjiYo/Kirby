#include "Metal.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Quest.h"

CMetal::CMetal()
{
}

CMetal::~CMetal()
{
	Release();
}

void CMetal::Inter()
{
	if (CCollisionMgr::GetInst().ObjectCollisionCheck(CObjMgr::GetInst().GetNPCList(), CObjMgr::GetInst().GetPlayerList()) && CKeyMgr::GetInst().Key_Down('Y'))
	{
		dynamic_cast<CQuest*>(CObjMgr::GetInst().GetUIInfo())->SetQuest();
	}
}

void CMetal::Initialize()
{
	m_tInfo = { SCALE_X * 0.5f,SCALE_Y * 0.5f,99.7f,69.f };

	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Npc/NPC_Metal.bmp", L"NPC_Metal");
	m_pFrameKey = L"NPC_Metal";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_GAMEOBJECT;
}

int CMetal::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;
	Inter();

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CMetal::LateUpdate()
{
	__super::MoveFrame();
}

void CMetal::Render(HDC _hDC)
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
		RGB(72, 88, 112));
}

void CMetal::Release()
{
}
