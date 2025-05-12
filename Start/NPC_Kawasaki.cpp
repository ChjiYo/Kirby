#include "NPC_Kawasaki.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "KeyMgr.h"

#include "UIMgr.h"

#include "SceneMgr.h"

#include "Factory.h"
#include "RSP.h"

CNPC_Kawasaki::CNPC_Kawasaki()
{
}

CNPC_Kawasaki::~CNPC_Kawasaki()
{
	Release();
}

void CNPC_Kawasaki::Inter()
{
	if (CCollisionMgr::GetInst().ObjectCollisionCheck(CObjMgr::GetInst().GetNPCList(), CObjMgr::GetInst().GetPlayerList()) && CKeyMgr::GetInst().Key_Down('P'))
	{
		CObjMgr::GetInst().Add_Create(OBJ_UI, CFactory<CRSP>::Create());
	}
	else if (CKeyMgr::GetInst().Key_Down('O'))
	{
		CObjMgr::GetInst().GetUIInfo()->SetDead();
	}
}

void CNPC_Kawasaki::Initialize()
{
	m_tInfo = { SCALE_X * 0.5f,SCALE_Y * 0.5f,28.7f,35.f };

	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Npc/NPC_Kawasaki.bmp", L"NPC_Kawasaki");
	m_pFrameKey = L"NPC_Kawasaki";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_GAMEOBJECT;
}

int CNPC_Kawasaki::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CNPC_Kawasaki::LateUpdate()
{
	Inter();

	__super::MoveFrame();
}

void CNPC_Kawasaki::Render(HDC _hDC)
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
		(int)m_tInfo.fCY * m_tFrame.iMotion + 9,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(83, 139, 157));
}

void CNPC_Kawasaki::Release()
{
}
