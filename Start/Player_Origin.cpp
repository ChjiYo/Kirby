#include "Player_Origin.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

#include "Inhal.h"
#include "Factory.h"
#include "StageMgr.h"


CPlayer_Origin::CPlayer_Origin()
{
	m_szInhalKeyCheck = false;
	m_bWater = false;
}

CPlayer_Origin::~CPlayer_Origin()
{
	Release();
}

void CPlayer_Origin::LRKey()
{
	if (CKeyMgr::GetInst().Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;

		m_pFrameKey = L"Player_LEFT";

		m_eCurState = WALK;
	}

	else if (CKeyMgr::GetInst().Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_pFrameKey = L"Player_RIGHT";

		m_eCurState = WALK;
	}
	else if (CKeyMgr::GetInst().Key_Pressing('Z') && !m_bInhalCheck)
	{
		//CSoundMgr::GetInst().PlaySoundW(L"04_Absorb.wav", SOUND_EFFECT, m_fVolume);

		m_szInhalKeyCheck = true;
		if (m_dwInhalTime + 500 <= (DWORD)GetTickCount64())
		{
			if (m_szMoveDir == 'R')
			{
				CObjMgr::GetInst().Add_Create(OBJ_ATTACK, CFactory<CInhal>::Create(m_tInfo.fX + 470, m_tInfo.fY + 170));
			}
			else if (m_szMoveDir == 'L' )
			{
				CObjMgr::GetInst().Add_Create(OBJ_ATTACK, CFactory<CInhal>::Create(m_tInfo.fX + 250, m_tInfo.fY + 170));
			}
			m_dwInhalTime = (DWORD)GetTickCount64();
		}
	}
}

void CPlayer_Origin::WaterMove()
{

	if (CStageMgr::GetInst().GetCurStage() == STAGE_A3 && (m_tInfo.fX < 2500.f && m_tInfo.fX > 1800.f) && m_tInfo.fY > 450.f)
	{
		m_tInfo.fY -= m_fSpeed;
	}

	if (CStageMgr::GetInst().GetCurStage() == STAGE_A3 && (m_tInfo.fX < 2500.f && m_tInfo.fX > 1850.f) && m_tInfo.fY > 340.f)
	{
		if (CKeyMgr::GetInst().Key_Pressing(VK_RIGHT))
		{
			m_eCurState = WATER_WALK;
		}
		else if (CKeyMgr::GetInst().Key_Pressing(VK_LEFT))
		{
			m_eCurState = WATER_WALK;
		}
		else if (CKeyMgr::GetInst().Key_Pressing(VK_UP))
		{
			m_bWater = true;

			m_tInfo.fY -= m_fSpeed;
			m_eCurState = WATER_UP;
		}
		else if (CKeyMgr::GetInst().Key_Pressing(VK_DOWN))
		{
			m_bWater = true;

			m_tInfo.fY += m_fSpeed;
			m_eCurState = WATER_DOWN;
		}
		else
		{
			m_eCurState = WATER_IDLE;
		}
	}
	else
	{
		m_bWater = false;
	}
}

void CPlayer_Origin::MotionChage()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case SIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 6;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;


		case FLY:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 11;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 24;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;


		case LAND:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 14;
			m_tFrame.iMotion = 7;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case INHAL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 12;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case ABSORB:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 16;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case INHALTRUE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 13;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case INHAL_FALSE:
			m_tFrame.iFrameStart = 6;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 12;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case INHAL_IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 14;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case INHAL_WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 15;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;


		case TACKLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 2;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case LAND_AIR:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 17;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case PORTAL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case WATER_IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 25;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case WATER_WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iMotion = 27;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case WATER_UP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd =11;
			m_tFrame.iMotion = 26;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case WATER_DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 28;

			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CPlayer_Origin::Initialize()
{
	m_tInfo = { SCALE_X* 0.5f ,SCALE_Y * 0.5f,32.f,35.f };
	m_bJump = false;
	m_fTime = 0.f;

	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Player/Player_Origin/Player_Origin__Left.bmp", L"Player_LEFT");
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Player/Player_Origin/Player_Origin_Right.bmp", L"Player_RIGHT");

	m_pFrameKey = L"Player_RIGHT";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_GAMEOBJECT;

	m_ePlayerID = PLAYER_CLASIC;

	m_bInhalCheck = false;
}

int CPlayer_Origin::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;


	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CPlayer_Origin::LateUpdate()
{


	LRKey();
	KeyInput();
	Hit();
	Jump();
	OffSet();
	WaterMove();
	MotionChage();
	Tackle();

	__super::MoveFrame();
}

void CPlayer_Origin::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScrollX ,
		m_tRect.top,
		(int)m_tInfo.fCX * 3,
		(int)m_tInfo.fCY * 3,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,	
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX ,
		(int)m_tInfo.fCY,
		RGB(207, 176, 255));

	//TCHAR		szHp[64] = L"";

	//swprintf_s(szHp, L"X : %f \t Y : %f , ", m_tInfo.fX, m_tInfo.fY);
	//TextOut(_hDC, 200, 500, szHp, lstrlen(szHp));
}

void CPlayer_Origin::Release()
{
}
