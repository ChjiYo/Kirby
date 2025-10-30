#include "Player_Spark.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include"CollisionMgr.h"
#include "Spark.h"
#include "AirGun.h"
#include "AbilityStar.h"
#include "Player_Origin.h"
#include "Explosion.h"

CPlayer_Spark::CPlayer_Spark()
{
	m_iCopyHp = 0;
	m_bAttackCheck = false;

	m_dwAttackTimer = (DWORD)GetTickCount64();
}

CPlayer_Spark::~CPlayer_Spark()
{
	Release();
}

void CPlayer_Spark::LRKey()
{

	if (CKeyMgr::GetInst().Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;

		m_pFrameKey = L"Player_Spark_LEFT";
		m_eCurState = WALK;
	}

	else if (CKeyMgr::GetInst().Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_pFrameKey = L"Player_Spark_RIGHT";

		m_eCurState = WALK;
	}
	else if (CKeyMgr::GetInst().Key_Pressing('F') )
	{
			CObjMgr::GetInst().Add_Create(OBJ_ATTACK, CFactory<CSpark>::Create(m_tInfo.fX, m_tInfo.fY));
			m_bAttackCheck = true;

			m_dwAttackTimer = (DWORD)GetTickCount64();
	}
	else if (CKeyMgr::GetInst().Key_Pressing('A'))
	{
		CObjMgr::GetInst().GetPlayerInfo()->SetDead();
		CObjMgr::GetInst().Add_Create(OBJ_PLAYER, CFactory<CPlayer_Origin>::Create(m_tInfo.fX, m_tInfo.fY));
		CObjMgr::GetInst().Add_Create(OBJ_ATTACK, CFactory<CExplosion>::Create(m_tInfo.fX, m_tInfo.fY));

		dynamic_cast<CPlayer*> (CObjMgr::GetInst().GetPlayerInfo())->SetHpInput(m_iNowHp);
		dynamic_cast<CPlayer*> (CObjMgr::GetInst().GetPlayerInfo())->SetMoneyInput(m_iNowMoney);
	}

}

void CPlayer_Spark::WaterMove()
{
}

void CPlayer_Spark::MotionChange()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 75;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case FLY:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 4;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case HIT:	
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 3;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 5;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CPlayer_Spark::Initialize()
{
	m_pBackMontion = L"Player_Spark";

	//30.f , 37.f
	m_tInfo = { SCALE_X * 0.5f,SCALE_Y * 0.5f,30.f,40.f };
	m_bJump = false;
	m_fTime = 0.f;

	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Player/Player_Spark/Player_Spark_Left.bmp", L"Player_Spark_LEFT");
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Player/Player_Spark/Player_Spark_Right.bmp", L"Player_Spark_RIGHT");

	m_pFrameKey = L"Player_Spark_RIGHT";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_GAMEOBJECT;

	m_ePlayerID = PLAYER_SPARK;
}

int CPlayer_Spark::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;
	
	m_iNowHp = dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetHp();
	m_iNowMoney = dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetMoney();

	__super::RectUpdate();
	return OBJ_NOEVENT;
}

void CPlayer_Spark::LateUpdate()
{
	LRKey();
	KeyInput();

	Jump();
	OffSet();
	MotionChange();
	Hit();

	if (m_eCurState == ATTACK && m_tFrame.iFrameStart != m_tFrame.iFrameEnd )
	{
		__super::MoveFrame();
	}
	else if (m_eCurState != ATTACK)
	{
		__super::MoveFrame();
	}
	
}

void CPlayer_Spark::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScrollX,
		m_tRect.top - 20,
		(int)m_tInfo.fCX * 3,
		(int)m_tInfo.fCY * 3,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion ,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 10, 255));

	//// m_tFrame.iMotion + 5
}

void CPlayer_Spark::Release()
{
}
