#include "Door.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "StageMgr.h"
#include "KeyMgr.h"

CDoor::CDoor()
{
}

CDoor::~CDoor()
{
	Release();
}

void CDoor::Initialize()
{
	m_tInfo.fCX = 35.f;
	m_tInfo.fCY = 60.f;

	m_eRender = RENDER_GAMEOBJECT;
}

int CDoor::Update()
{
	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CDoor::LateUpdate()
{
	MoveToNextState();
}

void CDoor::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CDoor::Release()
{
}

void CDoor::MoveToNextState()
{
	//int iiDownKey = CKeyMgr::GetInst().GetPressingKey();
	//
	//if (iiDownKey == VK_UP && CCollisionMgr::GetInst().ObjectIDCollisionCheck(OBJ_DOOR, OBJ_PLAYER))
	//{
	//	m_tInfo.fX = 100;
	//	m_tInfo.fY = 200;
	//
	//	switch (CStageMgr::GetInst().GetCurStage())
	//	{
	//	case STAGE_A1:
	//		CStageMgr::GetInst().StageChage(STAGE_A2);
	//		m_bDead = true;
	//		break;
	//
	//	case STAGE_A2:
	//		CStageMgr::GetInst().StageChage(STAGE_A3);
	//		break;
	//
	//	case STAGE_A3:
	//		CStageMgr::GetInst().StageChage(STAGE_A4);
	//		break;
	//
	//	default:
	//		break;
	//	}
	//	//m_eCurState = PORTAL;
	//}
}
