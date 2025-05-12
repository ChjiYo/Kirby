#include "Item_Now.h"
#include "BmpMgr.h"

#include "CollisionMgr.h"
#include "ObjMgr.h"

#include "Player.h"
#include "ScrollMgr.h"

#include "KeyMgr.h"
#include "LineMgr.h"

CItem_Now::CItem_Now()
{
	m_eItemID = ITEM_END;
	m_hItemMemDC = 0;

	m_fTime = 0.f;
}

CItem_Now::~CItem_Now()
{
	Release();
}

void CItem_Now::Land()
{
	float fX = 0.f;
	float fY = 0.f;

	bool bLineCol = CLineMgr::GetInst().Collision_Line(m_tInfo.fX, m_tInfo.fY, &fX, &fY);

	m_fTime += 0.1f;
	m_tInfo.fY -= m_fTime - 9.8f * m_fTime * m_fTime * 0.5f;

	if (bLineCol && fY - 25 < m_tInfo.fY)
	{
		m_fTime = 0.f;
		m_tInfo.fY = fY - 25;
	}
	
}

void CItem_Now::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Item/Item_Meat.bmp", L"Item_Meat");
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Item/Item_Tomato.bmp", L"Item_Tomato");
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Item/Item_Candy.bmp", L"Item_Candy");

	m_tInfo.fCX = 29.f;
	m_tInfo.fCY= 29.f;

	m_eRender = RENDER_ITEM;
}

int CItem_Now::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CItem_Now::LateUpdate()
{
	
	int iFullHp = 20 - dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetHp();

	if (CCollisionMgr::GetInst().ObjectCollisionCheck(CObjMgr::GetInst().GetItemList(), CObjMgr::GetInst().GetPlayerList()) )
	{
		//InvenCollisionCheck

		if (m_eItemID == ITEM_MEAT)
		{
			if (16 < dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetHp())
			{
				dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->SetHp(iFullHp);
			}
			else
			{
				dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->SetHp(4);
			}
			
			
		}
		else if (m_eItemID == ITEM_TOMATO)
		{
			dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->SetHp(iFullHp);
		}
		else if (m_eItemID == ITEM_CANDY)
		{
			dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->SetMoney(9999);
		}

		m_bDead = true;
	}


	if ( (CCollisionMgr::GetInst().Collision_Rect(CObjMgr::GetInst().GetItemListList(), CObjMgr::GetInst().GetMouseList())) && CKeyMgr::GetInst().Key_Down(VK_LBUTTON))
	{
		//InvenCollisionCheck

		if (m_eItemID == ITEM_MEAT)
		{
			if (16 < dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetHp())
			{
				dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->SetHp(iFullHp);
			}
			else
			{
				dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->SetHp(4);
			}


		}
		else if (m_eItemID == ITEM_TOMATO)
		{
			dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->SetHp(iFullHp);
		}
		else if (m_eItemID == ITEM_CANDY)
		{
			dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->SetMoney(9999);
		}
	}

	Land();
}

void CItem_Now::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();

	//m_hItemMemDC = CBmpMgr::GetInst().FindImage(L"Item_Meat");

	if (m_eItemID == ITEM_MEAT)
	{
		m_hItemMemDC = CBmpMgr::GetInst().FindImage(L"Item_Meat");
	}
	else if (m_eItemID == ITEM_TOMATO)
	{
		m_hItemMemDC = CBmpMgr::GetInst().FindImage(L"Item_Tomato");
	}
	else if (m_eItemID == ITEM_CANDY)
	{
		m_hItemMemDC = CBmpMgr::GetInst().FindImage(L"Item_Candy");
	}

		GdiTransparentBlt(
			_hDC,
			(int)m_tInfo.fX + iScrollX,
			(int)m_tInfo.fY- 25,
			(int)(m_tInfo.fCX *1.5f),
			(int)(m_tInfo.fCY * 1.5f),
			m_hItemMemDC,
			0,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(12, 230, 248));
}

void CItem_Now::Release()
{
}
