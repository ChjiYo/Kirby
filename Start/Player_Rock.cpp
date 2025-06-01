#include "Player_Rock.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"

CPlayer_Rock::CPlayer_Rock()
{
	StoneStage = false;
}

CPlayer_Rock::~CPlayer_Rock()
{
	Release();
}

void CPlayer_Rock::MotionChange()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 13;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 5;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;


		case FLY:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 7;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case V_WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 8;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CPlayer_Rock::LRKey()
{
	if (CKeyMgr::GetInst().Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;

		m_pFrameKey = L"Player_Stone_LEFT";
		m_eCurState = WALK;
	}

	else if (CKeyMgr::GetInst().Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_pFrameKey = L"Player_Stone_RIGHT";

		m_eCurState = WALK;
	}

	if ((m_eCurState == ATTACK) && m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		StoneStage = true;
	}

	if (StoneStage)
	{
		m_eCurState = ATTACK;
		m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
	}
}

void CPlayer_Rock::Initialize()
{
	m_tInfo = { SCALE_X * 0.5f,SCALE_Y * 0.5f,32.f,35.f};
	m_bJump = false;
	m_fTime = 0.f;

	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Player/Player_Stone/Last_Player_Stone_Left.bmp", L"Player_Stone_LEFT");
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Player/Player_Stone/Last_Player_Stone_Right.bmp", L"Player_Stone_RIGHT");

	m_pFrameKey = L"Player_Stone_RIGHT";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 10;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_GAMEOBJECT;

	m_iHp = GetHp();
}

int CPlayer_Rock::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;

	m_iNowHp = dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetHp();

	KeyInput();
	LRKey();
	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CPlayer_Rock::LateUpdate()
{
	Jump();
	OffSet();
	MotionChange();
	Hit();

	__super::MoveFrame();
}

void CPlayer_Rock::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScrollX ,
		m_tRect.top - 10,
		(int)m_tInfo.fCX * 3,
		(int)m_tInfo.fCY * 3,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart ,
		(int)m_tInfo.fCY * m_tFrame.iMotion ,
		(int)m_tInfo.fCX ,
		(int)m_tInfo.fCY ,
		RGB(0, 0, 128));
}

void CPlayer_Rock::Release()
{
}
