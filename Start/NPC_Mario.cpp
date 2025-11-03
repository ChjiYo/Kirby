#include "NPC_Mario.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "KeyMgr.h"

#include "Shop.h"

CNPC_Mario::CNPC_Mario()
{
}

CNPC_Mario::~CNPC_Mario()
{
	Release();
}

void CNPC_Mario::Inter()
{
	if (CCollisionMgr::GetInst().ObjectIDCollisionCheck(OBJ_NPC, OBJ_PLAYER) && CKeyMgr::GetInst().Key_Down('P'))
	{
		CObjMgr::GetInst().Add_Create(OBJ_UI, CFactory<CShop>::Create());
	}
	else if (CKeyMgr::GetInst().Key_Down('O'))
	{
		CObjMgr::GetInst().GetObjectList(OBJ_UI).back()->SetDead();
		CObjMgr::GetInst().Delete_ID(OBJ_ITEMLIST);
	}
}

void CNPC_Mario::Initialize()
{
	m_tInfo = { SCALE_X * 0.5f,SCALE_Y * 0.5f,40.7f,40.f };

	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Npc/NPC_SmallMario.bmp", L"NPC_SmallMario");
	m_pFrameKey = L"NPC_SmallMario";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_GAMEOBJECT;
}

int CNPC_Mario::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;
	Inter();

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CNPC_Mario::LateUpdate()
{
	__super::MoveFrame();
}

void CNPC_Mario::Render(HDC _hDC)
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
		RGB(255, 255, 255));
}

void CNPC_Mario::Release()
{
}
