#include "Player.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "Player_Origin.h"
#include "Player_Spark.h"
#include "Player_Sleepy.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "StageMgr.h"

#include "AirGun.h"
#include "Monster.h"

#include "Star.h"
#include "Inhal.h"
#include "Player_Ice.h"

#include "Ice_Block.h"

#include"StageA.h"
#include "StageMgr.h"

#include "SoundMgr.h"
#include "Change.h"

#include "Temp.h"

#include "Pet_Goust.h"
#include "Item_Now.h"

CPlayer::CPlayer()
{
	//AnimState
	ZeroMemory(&m_eCurState, sizeof(m_eCurState));
	ZeroMemory(&m_ePreState, sizeof(m_ePreState));

	//Jump
	m_bJump = false;
	m_fPower = 10.f;
	m_fTime = 0.f;
	m_fSpeed = 5.0f;
	iJumpCount = 0;

	//Dir
	m_szMoveDir = 'R';

	//Tackle
	m_bTackle = false;
	m_fTackleTimer = (DWORD)GetTickCount64();

	//Inhal
	m_dwInhalTime = (DWORD)GetTickCount64();
	m_bInhalCheck = false;

	//Hit
	m_bHitCheck = false;
	m_dwHitTimer = (DWORD)GetTickCount64();
	m_dwEpicHitTimer = (DWORD)GetTickCount64();

	//Hp
	m_iHp = 20;
	m_iNowHp = 0;

	//Sound
	m_fVolume = 1.f;
	m_bWalkTimer = (DWORD)GetTickCount64();

	//Input
	m_bInputKeyCheck = false;

	//Money
	m_iMoney = 0;
	m_iNowMoney = m_iMoney;

	//ID
	m_ePlayerID = PLAYER_CLASIC;
	m_eMonsterID = MON_NONE;

	//m_pFrameKey
	memset(szBuffer, 0, sizeof(szBuffer));
	m_pBackMontion = nullptr;

	m_bSwimming = false;
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::KeyInput()
{
	int iPressingKey = CKeyMgr::GetInst().GetPressingKey();
	int iDownKey = CKeyMgr::GetInst().GetDownKey();

	BindPressing(iPressingKey);
	BindDown(iDownKey);

	MultyBindAction(iPressingKey, iDownKey );
}

void CPlayer::Jump()
{
	float fX = 0.f;
	float fY = 0.f;

	bool bLineCol = CLineMgr::GetInst().Collision_Line(m_tInfo.fX, m_tInfo.fY, &fX, &fY);

	if (m_bJump)
	{
		m_eCurState = JUMP;

		m_tInfo.fY -= m_fPower - 9.8f * m_fTime * 0.5f;
		m_fTime += 0.1f;

		if (iJumpCount > 1)
		{
			m_eCurState = FLY;

		}
		if (bLineCol && fY < m_tInfo.fY)
		{
			m_bJump = false;
			m_fTime = 0.f;
			iJumpCount = 0;
			m_tInfo.fY = fY;
			m_eCurState = IDLE;
		}
		
	}
	else if (!m_bSwimming && bLineCol)
	{
		Land();
	}
	
	if ( fX <= m_tInfo.fX && fY < m_tInfo.fY)
	{
		if (m_szMoveDir == 'R')
 			m_tInfo.fX -= m_fSpeed;

		if (m_szMoveDir == 'L')
			m_tInfo.fX += m_fSpeed;
	}

}

void CPlayer::Land()
{
	float fX = 0.f;
	float fY = 0.f;

	bool bLineCol = CLineMgr::GetInst().Collision_Line(m_tInfo.fX, m_tInfo.fY, &fX, &fY);

	m_fTime += 0.1f;
	m_tInfo.fY -= m_fTime - 9.8f * m_fTime * m_fTime * 0.5f;

	if (bLineCol && fY -25 < m_tInfo.fY )
	{
		m_fTime = 0.f;
		m_tInfo.fY = fY -25;

	}
}

void CPlayer::OffSet()
{
	int	iOffSetMinX = 100;
	int	iOffSetMaxX = 500;

	int	iOffSetMinY = 100;
	int	iOffSetMaxY = 500;

	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	int iScrollY = (int)CScrollMgr::GetInst().GetScrollY();

	if (iOffSetMinX > m_tInfo.fX + iScrollX)
		CScrollMgr::GetInst().SetScrollX(m_fSpeed);

	if (iOffSetMaxX < m_tInfo.fX + iScrollX)
	{
		CScrollMgr::GetInst().SetScrollX(-m_fSpeed);
	}
	if (iOffSetMinY > m_tInfo.fY + iScrollY)
		CScrollMgr::GetInst().SetScrollY(m_fSpeed);

	if (iOffSetMaxY < m_tInfo.fY + iScrollY)
		CScrollMgr::GetInst().SetScrollY(-m_fSpeed);
}

void CPlayer::Hit()
{
	bool bCollMon = CCollisionMgr::GetInst().ObjectIDCollisionCheck(OBJ_PLAYER, OBJ_MONSTER);
	bool bCollMonAtt = CCollisionMgr::GetInst().ObjectIDCollisionCheck(OBJ_PLAYER, OBJ_MONATTACK);

	if (!m_bInputKeyCheck && (bCollMon || bCollMonAtt || m_bHitCheck ) )
	{
		m_eCurState = HIT;
		m_bHitCheck = true;

		if(m_szMoveDir == 'R')
			m_tInfo.fX -= m_fSpeed;

		if (m_szMoveDir == 'L')
			m_tInfo.fX += m_fSpeed;

		if (m_dwHitTimer + 800 < (DWORD)GetTickCount64() && m_bHitCheck)
		{
			dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back())->SetHp(-4);
			m_bHitCheck = false;
			m_dwHitTimer = (DWORD)GetTickCount64();
		}
	}

	if (m_dwHitTimer + 800 < (DWORD)GetTickCount64())
	{
		m_bHitCheck = false;
		m_dwHitTimer = (DWORD)GetTickCount64();
	}
}

void CPlayer::Tackle()
{

	if (m_bTackle)
	{
		m_eCurState = TACKLE;
		if (m_fTackleTimer + 350 < (DWORD)GetTickCount64())
		{
			m_bTackle = false;
			m_fTackleTimer = (DWORD)GetTickCount64();
		}

		if (m_szMoveDir == 'R')
		{
			m_tInfo.fX += m_fSpeed;
		}

		else if (m_szMoveDir == 'L')
		{
			m_tInfo.fX -= m_fSpeed;

		}

		if (CCollisionMgr::GetInst().ObjectIDCollisionCheck(OBJ_PLAYER, OBJ_MONSTER))
		{
			dynamic_cast<CMonster*>(CObjMgr::GetInst().GetObjectList(OBJ_MONSTER).back())->SetHp(-1);
		}
	}
	else
	{
		m_fTackleTimer = (DWORD)GetTickCount64();
		m_eCurState = IDLE;
	}
}

void CPlayer::BindAxis_LEFT(STATE eTpye)
{
	m_eCurState = eTpye;
	m_szMoveDir = 'L';
	m_tInfo.fX -= m_fSpeed;

	memset(szBuffer, 0, sizeof(szBuffer));
	wcscpy_s(szBuffer, m_pBackMontion);
	wcscat_s(szBuffer, L"_LEFT");

	m_pFrameKey = szBuffer;

	if (!m_bJump && ((m_bWalkTimer + 250) < (DWORD)GetTickCount64()))
	{
		CSoundMgr::GetInst().PlaySoundW(L"Walk.wav", SOUND_EFFECT, m_fVolume);
		m_bWalkTimer = (DWORD)GetTickCount64();
	}
}

void CPlayer::BindAxis_RIGHT(STATE eTpye)
{
  	m_eCurState = eTpye;
	m_szMoveDir = 'R';
	m_tInfo.fX += m_fSpeed;

	memset(szBuffer, 0, sizeof(szBuffer));
	wcscpy_s(szBuffer, m_pBackMontion);
	wcscat_s(szBuffer, L"_RIGHT");
	
	m_pFrameKey = szBuffer;

	if (!m_bJump && ((m_bWalkTimer + 250) < (DWORD)GetTickCount64()))
	{
		CSoundMgr::GetInst().PlaySoundW(L"Walk.wav", SOUND_EFFECT, m_fVolume);
		m_bWalkTimer = (DWORD)GetTickCount64();
	}
}

void CPlayer::BindAxis_DOWN()
{
	if(m_eCurState != TACKLE)
		m_eCurState = SIT;
}

void CPlayer::BindAxis_MONE(STATE eTpye)
{	
	m_bInputKeyCheck = false;
	m_eCurState = eTpye;
}


void CPlayer::BindAction_JUMP()
{
	m_fTime = 0.f;
	iJumpCount++;
	m_bJump = true;
	m_eCurState = JUMP;

	if (iJumpCount > 1)
	{
		CSoundMgr::GetInst().PlaySoundW(L"02_Fly.wav", SOUND_EFFECT, m_fVolume);
	}
	else
	{
		CSoundMgr::GetInst().PlaySoundW(L"01_Jump.wav", SOUND_EFFECT, m_fVolume);
	}
}

void CPlayer::BindAction_TACKLE()
{
	m_bTackle = true;
	m_bInputKeyCheck = true;
}

void CPlayer::BindAction_ESCAPE()
{
	//int iiDownKey = CKeyMgr::GetInst().GetPressingKey();
	//iiDownKey == VK_DOWN && 
	if (CCollisionMgr::GetInst().ObjectIDCollisionCheck(OBJ_DOOR, OBJ_PLAYER))
	{
		m_tInfo.fX = 100;
		m_tInfo.fY = 200;

		switch (CStageMgr::GetInst().GetCurStage())
		{
		case STAGE_A1:
			CStageMgr::GetInst().StageChage(STAGE_A2);
			break;

		case STAGE_A2:
			CStageMgr::GetInst().StageChage(STAGE_A3);
			break;

		case STAGE_A3:
			CStageMgr::GetInst().StageChage(STAGE_A4);
			break;

		default:
			break;
		}
		//m_eCurState = PORTAL;
	}
}

void CPlayer::BindAction_ATTACK()
{
	//m_eCurState = ATTACK;

	if (m_bJump && iJumpCount > 1)
	{
		CSoundMgr::GetInst().PlaySoundW(L"12_AirGun.wav", SOUND_EFFECT, m_fVolume);
		m_eCurState = LAND_AIR;

		if (m_szMoveDir == 'R')
		{
			CObjMgr::GetInst().Add_Create(OBJ_ATTACK, CFactory<CAirGun>::Create(m_tInfo.fX, m_tInfo.fY, 0.f));
		}
		else if (m_szMoveDir == 'L')
		{
			CObjMgr::GetInst().Add_Create(OBJ_ATTACK, CFactory<CAirGun>::Create(m_tInfo.fX, m_tInfo.fY, 180.f));
		}
		iJumpCount = 0;
	}
	
}

void CPlayer::BindAction_ITEM()
{
	//Using Item
	CObjMgr::GetInst().Add_Create(OBJ_ITEM, CFactory<CItem_Now>::Create(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back()->GetInfo().fX, 0));
	dynamic_cast<CItem_Now*>(CObjMgr::GetInst().GetObjectList(OBJ_ITEM).back())->SetItemID(ITEM_TOMATO);
}

void CPlayer::BindPressing(int _iKey)
{

	switch (_iKey)
	{
	case VK_LEFT:
		BindAxis_LEFT();
		break;

	case VK_RIGHT:
		BindAxis_RIGHT();
		break;

	case VK_DOWN:
		BindAxis_DOWN();
		break;

	default:
		BindAxis_MONE();
		break;
	}
}

void CPlayer::BindDown(int _iKey)
{
	switch (_iKey)
	{
	case VK_SPACE:
		BindAction_JUMP();
		break;

	case VK_UP:
		BindAction_ESCAPE();
		break;

	case 'C':
		BindAction_ATTACK();
		break;
	case 'J':
		BindAction_ITEM();
		break;
	default:
		break;
	}
}

void CPlayer::MultyBindAction(int _iFirstKey, int _iSecondKey)
{
	if (_iFirstKey == VK_DOWN && _iSecondKey == 'X')
	{
		BindAction_TACKLE();
	}

	if (CKeyMgr::GetInst().Key_Pressing(VK_SPACE))
	{
		if (CKeyMgr::GetInst().Key_Pressing(VK_LEFT))
		{
			m_tInfo.fX -= m_fSpeed;
		}

		else if (CKeyMgr::GetInst().Key_Pressing(VK_RIGHT))
		{
			m_tInfo.fX += m_fSpeed;
		}
	}
}


void CPlayer::MotionChange()
{
}

void CPlayer::Initialize()
{

}

int CPlayer::Update()
{	
	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate()
{
	LRKey();
	KeyInput();
	Hit();
	Jump();
	OffSet();
	WaterMove();
	MotionChange();
	Tackle();
}

void CPlayer::Render(HDC _hDC)
{
	
}

void CPlayer::Release()
{
}
