#include "Player_Ice.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "Player_Origin.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Ice.h"

#include "Explosion.h"
#include "SoundMgr.h"

CPlayer_Ice::CPlayer_Ice()
{
	m_dwAttackTimer = (DWORD)GetTickCount64();
}

CPlayer_Ice::~CPlayer_Ice()
{
	Release();
}

void CPlayer_Ice::LRKey()
{
	if (CKeyMgr::GetInst().Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;

		m_pFrameKey = L"Player_ICE_LEFT";
		m_eCurState = WALK;
	}

	else if (CKeyMgr::GetInst().Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_pFrameKey = L"Player_ICE_RIGHT";

		m_eCurState = WALK;
	}
	else if (CKeyMgr::GetInst().Key_Pressing('F'))
	{
		//CSoundMgr::GetInst().PlaySoundW(L"07_Ice.wav", SOUND_EFFECT, m_fVolume);
		if (m_dwAttackTimer + 100  <= (DWORD)GetTickCount64())
		{
			if(m_szLRCheck == 'L')
			{
				CObjMgr::GetInst().Add_Create(OBJ_ATTACK, CFactory<CIce>::Create(m_tInfo.fX - 110, m_tInfo.fY - 20));
			}
			else if (m_szLRCheck == 'R')
			{
				CObjMgr::GetInst().Add_Create(OBJ_ATTACK, CFactory<CIce>::Create(m_tInfo.fX + 110, m_tInfo.fY - 20));
			}
			
			m_dwAttackTimer = (DWORD)GetTickCount64();
		}
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

void CPlayer_Ice::MotionChange()
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
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case TEST:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 6;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;


		case FLY:
			m_tFrame.iFrameStart = 3;
			m_tFrame.iFrameEnd = 20;
			m_tFrame.iMotion = 7;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 5;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 9;

			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CPlayer_Ice::Initialize()
{
	m_tInfo = { SCALE_X * 0.5f,SCALE_Y * 0.5f,32.f,43.f }; 
	m_bJump = false;
	m_fTime = 0.f;
	m_fPower = 10.f;

	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Player/Player_Ice/Player_Ice_Left.bmp", L"Player_ICE_LEFT");
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Player/Player_Ice/Player_Ice_Right.bmp", L"Player_ICE_RIGHT");

	m_pFrameKey = L"Player_ICE_RIGHT";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_GAMEOBJECT;
	
	m_iHp = GetHp();

	m_ePlayerID = PLAYER_ICE;
}

int CPlayer_Ice::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;

	m_iNowHp = dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetHp();
	m_iNowMoney = dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetMoney();

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CPlayer_Ice::LateUpdate()
{
	LRKey();
	KeyInput();
	Hit();

	Jump();
	OffSet();
	MotionChange();

	if (m_eCurState == ATTACK && m_tFrame.iFrameStart != 7)
	{
		__super::MoveFrame();
	}
	else if (m_eCurState == ATTACK && m_tFrame.iFrameStart == 7)
	{
		m_tFrame.iFrameStart = 6;
		__super::MoveFrame();
	}
	else if (m_eCurState != ATTACK)
	{
		__super::MoveFrame();
	}
}

void CPlayer_Ice::Render(HDC _hDC)
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
		RGB(255, 0, 255));
}

void CPlayer_Ice::Release()
{
}
