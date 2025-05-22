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
	ZeroMemory(&m_eCurState, sizeof(m_eCurState));
	ZeroMemory(&m_ePreState, sizeof(m_ePreState));

	//Jump
	m_bJump = false;
	m_fPower = 10.f;
	m_fTime = 0.f;
	m_fSpeed = 5.0f;

	m_szMoveDir = 'R';

	//Tackle (Fix)
	m_fTackleTimer = (DWORD)GetTickCount64();

	m_iMapCount = 0;

	m_bFlyCheck = false;

	m_dwFlyTimer = (DWORD)GetTickCount64() / 1000;
	m_dwInhalTime = (DWORD)GetTickCount64();

	iJumpCount = 0;
	m_iInhalCount = 0;

	m_bMapCheck = false;

	m_dwHitTimer = (DWORD)GetTickCount64();
	m_dwEpicHitTimer = (DWORD)GetTickCount64();

	m_iHp = 20;

	m_iNowHp = 0;

	m_fVolume = 1.f;

	m_bHitCheck = false;

	m_dwHitIdleTimer = (DWORD)GetTickCount64();

	m_bInputKeyCheck = false;

	m_bWalkTimer = (DWORD)GetTickCount64();

	m_iMoney = 0;

	m_ePlayerID = PLAYER_CLASIC;

	m_dwLandTimer = (DWORD)GetTickCount64();

}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::KeyInput()
{
	int iPressingKey = CKeyMgr::GetInst().GetPressingKey();
	int iDownKey = CKeyMgr::GetInst().GetDownKey();

	BindAxis(iPressingKey);
	BindAction(iDownKey);

//기타 키들 (추후에 업데이트 필요)
	//else if (CKeyMgr::GetInst().Key_Pressing('Z'))
	//{
	//	m_iInhalCount++;
	//	Inhal();
	//	m_eCurState = INHAL;
	//	m_bInhalCheck = CCollisionMgr::GetInst().SetPlayerInhal_Check(CObjMgr::GetInst().GetPlayerList(), CObjMgr::GetInst().GetMonsterList());
	//}
	//else if (CKeyMgr::GetInst().Key_Down('L'))
	//{
	//	CObjMgr::GetInst().Add_Create(OBJ_ITEM, CFactory<CItem_Now>::Create(CObjMgr::GetInst().GetPlayerInfo()->GetInfo().fX , 0));
	//	dynamic_cast<CItem_Now*>(CObjMgr::GetInst().GetItemInfo())->SetItemID(ITEM_TOMATO);
	//	//CObjMgr::GetInst().Add_Create(OBJ_TEMP, CFactory<CTemp>::Create());
	//}
	//else if (CKeyMgr::GetInst().Key_Down('J'))
	//{
	//	dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->SetHp(-4);
	//}
}

void CPlayer::Jump()
{
	float fX = 0.f;
	float  fY = 0.f;

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
				m_tInfo.fY = fY;
				iJumpCount = 0;
				m_eCurState = IDLE;
			
			}
			
		}
		else if (bLineCol)
		{
		//	m_eCurState = LAND;

			if ( !(CStageMgr::GetInst().GetCurStage() == STAGE_A3 && (m_tInfo.fX < 2500.f && m_tInfo.fX > 1870.f) && m_tInfo.fY > 340.f) )
			{
				Land();
			}
			//m_tInfo.fY = fY;
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

		m_dwLandTimer = (DWORD)GetTickCount64();
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

void CPlayer::Inhal()
{
	m_pTarget = CObjMgr::GetInst().Get_Target(OBJ_MONSTER, this);

	if (m_pTarget)
	{
		m_bInputKeyCheck = true;
	}
	m_pTarget = CObjMgr::GetInst().Get_Target(OBJ_MONSTER, this);

	//if (m_pTarget)
	//{
	//	m_bInputKeyCheck = true;
	//	m_fWidth = (m_pTarget->GetInfo().fX - m_tInfo.fX);
	//	m_fHeight = (m_pTarget->GetInfo().fY - m_tInfo.fY);

	//	m_fDiagonal = (float)(sqrt(m_fWidth * m_fWidth + m_fHeight * m_fHeight));

	//	m_fRadian = (float)acos(m_fWidth / m_fDiagonal);

	//	if (m_pTarget->GetInfo().fY > m_tInfo.fY)
	//		m_fRadian = (2 * PI) - m_fRadian;

	//	m_fAngle = m_fRadian * (180.f / PI);

	//	CObjMgr::GetInst().GetMonsterInfo()->SetAngle(m_fAngle);
	//	//m_tInfo.fX += m_fSpeed * cos(m_fAngle * (PI / 180.f));
	//	//m_tInfo.fY -= m_fSpeed * sin(m_fAngle * (PI / 180.f));
	//}
}

void CPlayer::Hit()
{
	if ( ( CCollisionMgr::GetInst().ObjectCollisionCheck(CObjMgr::GetInst().GetPlayerList(), CObjMgr::GetInst().GetMonsterList()) ||
		CCollisionMgr::GetInst().ObjectCollisionCheck(CObjMgr::GetInst().GetPlayerList(), CObjMgr::GetInst().GetMonAttackList()) || m_bHitCheck ) && !m_bInputKeyCheck)
	{
		m_eCurState = TEST;
		m_bHitCheck = true;

		if(m_szMoveDir == 'R')
			m_tInfo.fX -= m_fSpeed;

		if (m_szMoveDir == 'L')
			m_tInfo.fX += m_fSpeed;

		if (m_dwHitTimer + 800 < (DWORD)GetTickCount64() && m_bHitCheck)
		{
			dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->SetHp(-4);
			m_bHitCheck = false;
			m_dwHitTimer = (DWORD)GetTickCount64();
		}
	}

	if (m_dwHitTimer + 800 < (DWORD)GetTickCount64())
	{
		m_bHitCheck = false;
		m_dwHitTimer = (DWORD)GetTickCount64();
	}


	//Epic
	if (CCollisionMgr::GetInst().ObjectCollisionCheck(CObjMgr::GetInst().GetPlayerList(), CObjMgr::GetInst().GetMonEpickList()))
	{
		m_eCurState = TEST;
		m_bHitCheck = true;

		if (m_szMoveDir == 'R')
			m_tInfo.fX -= m_fSpeed;

		if (m_szMoveDir == 'L')
			m_tInfo.fX += m_fSpeed;

		if (m_dwEpicHitTimer + 800 < (DWORD)GetTickCount64() && m_bHitCheck)
		{
			dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->SetHp(-4);
			m_bHitCheck = false;
			m_dwEpicHitTimer = (DWORD)GetTickCount64();
		}
	}

	if (m_dwEpicHitTimer + 800 < (DWORD)GetTickCount64())
	{
		if (CCollisionMgr::GetInst().ObjectCollisionCheck(CObjMgr::GetInst().GetPlayerList(), CObjMgr::GetInst().GetMonEpickList()) )	
		{
			dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->SetHp(-4);
		}
		m_dwEpicHitTimer = (DWORD)GetTickCount64();
	}

	if (m_dwEpicHitTimer + 800 < (DWORD)GetTickCount64())
	{
		m_bHitCheck = false;
		m_dwEpicHitTimer = (DWORD)GetTickCount64();
	}
}

void CPlayer::Tackle()
{

}

void CPlayer::BindAxis_LEFT()
{
	m_eCurState = WALK;
	m_szMoveDir = 'L';

	if (!m_bJump && ((m_bWalkTimer + 250) < (DWORD)GetTickCount64()))
	{
		//CSoundMgr::GetInst().PlaySoundW(L"Walk.wav", SOUND_EFFECT, m_fVolume);
		m_bWalkTimer = (DWORD)GetTickCount64();
	}
}

void CPlayer::BindAxis_RIGHT()
{
	m_eCurState = WALK;
	m_szMoveDir = 'R';


	if (!m_bJump && ((m_bWalkTimer + 250) < (DWORD)GetTickCount64()))
	{
		//CSoundMgr::GetInst().PlaySoundW(L"Walk.wav", SOUND_EFFECT, m_fVolume);
		m_bWalkTimer = (DWORD)GetTickCount64();
	}
}

void CPlayer::BindAxis_DOWN()
{
	m_eCurState = SIT;
	int iDownKey = CKeyMgr::GetInst().GetDownKey();
	if (iDownKey == 'X')
	{
		m_eCurState = TACKLE;
		if (m_szMoveDir == 'R')
		{
			m_tInfo.fX += m_fSpeed;
		}

		else if (m_szMoveDir == 'L')
		{
			m_tInfo.fX -= m_fSpeed;
			
		}

		if (CCollisionMgr::GetInst().ObjectCollisionCheck(CObjMgr::GetInst().GetPlayerList(), CObjMgr::GetInst().GetMonsterList()))
		{
			dynamic_cast<CMonster*>(CObjMgr::GetInst().GetMonsterInfo())->SetHp(-1);
		}

	}

}

void CPlayer::BindAxis_MONE()
{	
	m_bInputKeyCheck = false;
	m_eCurState = IDLE;
	m_iInhalCount = 0;
}


void CPlayer::BindAction_JUMP()
{
	m_fTime = 0.f;
	iJumpCount++;
	m_bJump = true;
	m_eCurState = JUMP;

	//	if (iJumpCount > 1)
	//	{
	//		//CSoundMgr::GetInst().PlaySoundW(L"02_Fly.wav", SOUND_EFFECT, m_fVolume);
	//	}
	//	else
	//	{
	//		//CSoundMgr::GetInst().PlaySoundW(L"01_Jump.wav", SOUND_EFFECT, m_fVolume);
	//	}
}

void CPlayer::BindAction_TACKLE()
{

}

void CPlayer::BindAction_ESCAPE()
{
	if (CCollisionMgr::GetInst().ObjectCollisionCheck(CObjMgr::GetInst().GetDoorList(), CObjMgr::GetInst().GetPlayerList()))
	{
		m_tInfo.fX = 100;
		m_tInfo.fY = 200;

		m_bMapCheck = true;

		switch (CStageMgr::GetInst().GetCurStage())
		{
		case STAGE_A1:
			CStageMgr::GetInst().StageChage(STAGE_A3);
			break;

			/*case STAGE_A2:
				CStageMgr::GetInst().StageChage(STAGE_A3);
				break;*/

		case STAGE_A3:
			CStageMgr::GetInst().StageChage(STAGE_A4);
			break;

		case 3:
			break;

		}
		m_iMapCount++;
		m_eCurState = PORTAL;
	}
}


void CPlayer::BindAction_ATTACK()
{
	//m_eCurState = ATTACK;

	if (m_bJump && iJumpCount > 1)
	{
		//CSoundMgr::GetInst().PlaySoundW(L"12_AirGun.wav", SOUND_EFFECT, m_fVolume);
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

void CPlayer::BindAxis(int _iKey)
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

void CPlayer::BindAction(int _iKey)
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

	default:
		break;
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
	
}

void CPlayer::Render(HDC _hDC)
{
	
}

void CPlayer::Release()
{
}
