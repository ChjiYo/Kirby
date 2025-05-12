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

	m_bJump = false;
	m_fPower = 0.f;
	m_fTime = 0.f;
	m_fSpeed = 5.0f;
	m_fJumpTimer = 0.f;

	m_dwBulletTimer = (DWORD)(GetTickCount64() / 1000);

	m_bInhalCheck = false;
	m_fInhalTimer = 0.f;

	m_szLRCheck = 'R';

	m_bTackle = false;

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
	if (CKeyMgr::GetInst().Key_Pressing(VK_SPACE))
	{
		m_fJumpTimer += 0.1f;

		if (m_fJumpTimer > 7.f)
			m_fJumpTimer = 7.f;
	}

		if (CKeyMgr::GetInst().Key_Pressing(VK_LEFT))
		{
			m_eCurState = WALK;
			m_szLRCheck = 'L';
			
			if (!m_bJump && ((m_bWalkTimer + 250) < (DWORD)GetTickCount64()))
			{
				//CSoundMgr::GetInst().PlaySoundW(L"Walk.wav", SOUND_EFFECT, m_fVolume);
				m_bWalkTimer = (DWORD)GetTickCount64();
			}
		}
		else if (CKeyMgr::GetInst().Key_Pressing(VK_RIGHT))
		{
			m_eCurState = WALK;
			m_szLRCheck = 'R';

			
			if (!m_bJump && ((m_bWalkTimer + 250) < (DWORD)GetTickCount64()))
			{
				//CSoundMgr::GetInst().PlaySoundW(L"Walk.wav", SOUND_EFFECT, m_fVolume);
				m_bWalkTimer = (DWORD)GetTickCount64();
			}
			
		}

		else if (CKeyMgr::GetInst().Key_Down(VK_UP) &&
			CCollisionMgr::GetInst().ObjectCollisionCheck(CObjMgr::GetInst().GetDoorList(), CObjMgr::GetInst().GetPlayerList()))
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
		else if (CKeyMgr::GetInst().Key_Pressing(VK_DOWN))
		{
			m_eCurState = SIT;
			
			if ( (CKeyMgr::GetInst().Key_Pressing('X')) && m_fTackleTimer + 300 < (DWORD)GetTickCount64())
			{
				
				m_eCurState = TACKLE;
				if (m_szLRCheck == 'R')
				{
					m_tInfo.fX += m_fSpeed;
				}

				else if (m_szLRCheck == 'L')
				{
					m_tInfo.fX -= m_fSpeed;
				}
				if(CCollisionMgr::GetInst().ObjectCollisionCheck(CObjMgr::GetInst().GetPlayerList(), CObjMgr::GetInst().GetMonsterList()))
				{
					dynamic_cast<CMonster*>(CObjMgr::GetInst().GetMonsterInfo())->SetHp(-1);
				}
				
			}
			
		}
		
		else if ((CKeyMgr::GetInst().Key_Down(VK_SPACE)))
		{
			m_fJumpTimer = 0.f;
			m_fTime = 0.f;
			iJumpCount++;
			m_bJump = true;

			if (iJumpCount > 1)
			{
				//CSoundMgr::GetInst().PlaySoundW(L"02_Fly.wav", SOUND_EFFECT, m_fVolume);
			}
			else
			{
				//CSoundMgr::GetInst().PlaySoundW(L"01_Jump.wav", SOUND_EFFECT, m_fVolume);
			}
		}
		else if (( m_bJump))
		{
			m_bJump = true;
			m_eCurState = JUMP;
		}
		else if (CKeyMgr::GetInst().Key_Pressing('F'))
		{
			m_eCurState = ATTACK;
		}
		else if (CKeyMgr::GetInst().Key_Pressing('Z'))
		{
			m_iInhalCount++;
			Inhal();
			m_eCurState = INHAL;
			m_bInhalCheck = CCollisionMgr::GetInst().SetPlayerInhal_Check(CObjMgr::GetInst().GetPlayerList(), CObjMgr::GetInst().GetMonsterList());
		}
		else if (CKeyMgr::GetInst().Key_Down('L'))
		{
			CObjMgr::GetInst().Add_Create(OBJ_ITEM, CFactory<CItem_Now>::Create(CObjMgr::GetInst().GetPlayerInfo()->GetInfo().fX , 0));
			dynamic_cast<CItem_Now*>(CObjMgr::GetInst().GetItemInfo())->SetItemID(ITEM_TOMATO);
			//CObjMgr::GetInst().Add_Create(OBJ_TEMP, CFactory<CTemp>::Create());
		}
		else if (CKeyMgr::GetInst().Key_Down('J'))
		{
			dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->SetHp(-4);
		}

		else
		{
			m_bInputKeyCheck = false;
			m_eCurState = IDLE;
			m_iInhalCount = 0;
		}

}

void CPlayer::Jump()
{
	float fX = 0.f;
	float  fY = 0.f;

	bool bLineCol = CLineMgr::GetInst().Collision_Line(m_tInfo.fX, m_tInfo.fY, &fX, &fY);

		if (m_bJump)
		{
			m_tInfo.fY -= (m_fPower + m_fJumpTimer) - 9.8f * m_fTime * 0.5f;
			m_fTime += 0.1f;

			if (iJumpCount > 1)
			{
				
				m_eCurState = FLY;

				 if (CKeyMgr::GetInst().Key_Down('C') /*&& (m_dwBulletTimer + 0.5f) < (DWORD)(GetTickCount64() / 1000.f)*/)
				{
					 //CSoundMgr::GetInst().PlaySoundW(L"12_AirGun.wav", SOUND_EFFECT, m_fVolume);
					m_eCurState = LAND_AIR;
					
					if (m_szLRCheck == 'R')
					{
						CObjMgr::GetInst().Add_Create(OBJ_ATTACK, CFactory<CAirGun>::Create(m_tInfo.fX, m_tInfo.fY, 0.f));
					}
					else if (m_szLRCheck == 'L')
					{
						CObjMgr::GetInst().Add_Create(OBJ_ATTACK, CFactory<CAirGun>::Create(m_tInfo.fX, m_tInfo.fY, 180.f));
					}
					m_dwBulletTimer = (DWORD)(GetTickCount64() / 1000);

					iJumpCount = 0;
		
				}
			}
			if (bLineCol && fY < m_tInfo.fY)
			{
				m_bJump = false;
				m_fTime = 0.f;
				m_tInfo.fY = fY;
				m_fJumpTimer = 0;
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
		if (m_szLRCheck == 'R')
 			m_tInfo.fX -= m_fSpeed;

		if (m_szLRCheck == 'L')
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

		if(m_szLRCheck == 'R')
			m_tInfo.fX -= m_fSpeed;

		if (m_szLRCheck == 'L')
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

		if (m_szLRCheck == 'R')
			m_tInfo.fX -= m_fSpeed;

		if (m_szLRCheck == 'L')
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
