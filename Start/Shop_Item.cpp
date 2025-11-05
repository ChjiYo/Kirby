#include "Shop_Item.h"
#include "BmpMgr.h"

#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "Player.h"

#include "Pet_Goust.h"
#include "Factory.h"

#include "ScrollMgr.h"
#include "Money.h"

CShop_Item::CShop_Item()
{
	m_eItemID = ITEM_END;
	m_hItemMemDC = 0;
	m_iPrice = 0;
}

CShop_Item::~CShop_Item()
{
	Release();
}

void CShop_Item::ClickBuy()
{
	int iFullHp = 20 - dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back())->GetHp();

	if (CKeyMgr::GetInst().Key_Down(VK_LBUTTON) && (CCollisionMgr::GetInst().ObjectIDCollisionCheck(OBJ_MOUSE, OBJ_ITEMLIST)))
	{
		switch (m_eItemID)
		{
		case ITEM_MEAT:
			if (16 < dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back())->GetHp())
				dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back())->SetHp(iFullHp);
			else
				dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back())->SetHp(4);

			break;

		case ITEM_TOMATO:
			dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back())->SetHp(iFullHp);
			break;

		case ITEM_PET_GOUSE:
			CObjMgr::GetInst().Add_Create(OBJ_PET, CFactory<CPet_Goust>::Create(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back()->GetInfo().fX - 100, CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back()->GetInfo().fY));
			break;
		}
	}
}

void CShop_Item::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Item/Item_Meat.bmp", L"Item_Meat");
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Item/Item_Tomato.bmp", L"Item_Tomato");
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Item/Item_Goust.bmp", L"Item_Goust");

	m_tInfo.fCX = 29.f;
	m_tInfo.fCY = 29.f;

	m_eRender = RENDER_ITEM;
}

int CShop_Item::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CShop_Item::LateUpdate()
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();

	ClickBuy();
}

void CShop_Item::Render(HDC _hDC)
{
	int iScroll = (int)CScrollMgr::GetInst().GetScrollX();

	if (m_eItemID == ITEM_MEAT)
	{
		m_hItemMemDC = CBmpMgr::GetInst().FindImage(L"Item_Meat");
	}
	else if (m_eItemID == ITEM_TOMATO)
	{
		m_hItemMemDC = CBmpMgr::GetInst().FindImage(L"Item_Tomato");
	}
	else if (m_eItemID == ITEM_PET_GOUSE)
	{
		m_hItemMemDC = CBmpMgr::GetInst().FindImage(L"Item_Goust");
	}

	GdiTransparentBlt(
		_hDC,
		m_tRect.left + iScroll,
		m_tRect.top,
		(int)(m_tInfo.fCX ),
		(int)(m_tInfo.fCY ),
		m_hItemMemDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(12, 230, 248));

	// 1.5น่
}

void CShop_Item::Release()
{
}
