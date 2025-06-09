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

#include "Change.h"
#include "Player_Spark.h"
#include "Player_Ice.h"
#include "Player_Sleepy.h"

CPlayer_Origin::CPlayer_Origin()
{
	m_szInhalKeyCheck = false;
	m_bWater = false;
	m_bInhalCheck = false;

	m_fInhalTimer = 0.f;
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

void CPlayer_Origin::BindPressing(int _iKey)
{
	m_bInhalCheck ? InhalAnim(_iKey) : BaseAnim(_iKey);
}

void CPlayer_Origin::BaseAnim(int _iKey)
{
	switch (_iKey)
	{
	case 'Z':
		BindAction_INHAL();
		break;
	}
}

void CPlayer_Origin::InhalAnim(int _iKey)
{
	m_fSpeed = 3.f;

	switch (_iKey)
	{
	case VK_LEFT:
		BindAxis_LEFT(static_cast<CPlayer::STATE>(INHAL_WALK));
		break;

	case VK_RIGHT:
		BindAxis_RIGHT(static_cast<CPlayer::STATE>(INHAL_WALK));
		break;

	case VK_DOWN:
		BindAction_TRANSFORM();
		break;
	default:
		BindAxis_MONE(static_cast<CPlayer::STATE>(INHAL_IDLE));
		break;
	}
}

void CPlayer_Origin::KeyInput()
{
	if(m_bInhalCheck == false)
		__super::KeyInput();
 
	int iPressingKey = CKeyMgr::GetInst().GetPressingKey();
	BindPressing(iPressingKey);
}

void CPlayer_Origin::BindAction_INHAL()
{
	m_eCurState = INHAL;
	m_pTarget = CObjMgr::GetInst().Get_Target(OBJ_MONSTER, this);

	if (m_pTarget)
		m_bInputKeyCheck = true;

	m_bInhalCheck = CCollisionMgr::GetInst().SetPlayerInhal_Check(CObjMgr::GetInst().GetPlayerList(), CObjMgr::GetInst().GetMonsterList());
}

void CPlayer_Origin::BindAction_TRANSFORM()
{
	m_eCurState = static_cast<CPlayer::STATE>(ABSORB);

	m_fInhalTimer += 0.1f;

	if (m_fInhalTimer >= 3.0f)
	{
		m_bInhalCheck = false;
		CObjMgr::GetInst().Add_Create(OBJ_ATTACK, CFactory<CChange>::Create(m_tInfo.fX, m_tInfo.fY));
		m_iNowHp = GetHp();
		m_iNowMoney = GetMoney();
		switch (m_eMonsterID)
		{
		case MON_NONE:
			break;

		case MON_SPARKY:
			CObjMgr::GetInst().GetPlayerInfo()->SetDead();
			CObjMgr::GetInst().Add_Create(OBJ_PLAYER, CFactory<CPlayer_Spark>::Create(m_tInfo.fX, m_tInfo.fY));
			break;

		case MON_GUNTER:
			CObjMgr::GetInst().GetPlayerInfo()->SetDead();
			CObjMgr::GetInst().Add_Create(OBJ_PLAYER, CFactory<CPlayer_Ice>::Create(m_tInfo.fX, m_tInfo.fY));
			break;

		case MON_SLEEPY:
			CObjMgr::GetInst().GetPlayerInfo()->SetDead();
			CObjMgr::GetInst().Add_Create(OBJ_PLAYER, CFactory<CPlayer_Sleepy>::Create(m_tInfo.fX, m_tInfo.fY));
			break;
		}
		dynamic_cast<CPlayer*> (CObjMgr::GetInst().GetPlayerInfo())->SetHpInput(m_iNowHp);
		dynamic_cast<CPlayer*> (CObjMgr::GetInst().GetPlayerInfo())->SetMoneyInput(m_iNowMoney);

		m_fInhalTimer = 0.f;
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

		case static_cast<CPlayer::STATE>(INHAL_IDLE):
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
