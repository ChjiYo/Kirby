#include "Shop.h"
#include "BmpMgr.h"
#include "Factory.h"
#include "ObjMgr.h"
#include "Item_Now.h"	
#include "Shop_Item.h"

#include "ScrollMgr.h"

CShop::CShop()
{
	m_iStartX = 0;
	m_iStartY = 0;

	CreateCheck = false;
}
CShop::~CShop()
{
	Release();
}

void CShop::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Interface/Inter_Shop.bmp", L"Shop");
	
	m_iStartX = 250;
	m_iStartY = 100;

	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	
	CObjMgr::GetInst().Add_Create(OBJ_ITEMLIST, CFactory<CShop_Item>::Create((float)(m_iStartX + 50), (float)(m_iStartY + 175)));
	dynamic_cast<CShop_Item*>(CObjMgr::GetInst().GetObjectList(OBJ_ITEMLIST).back())->SetItemID(ITEM_MEAT);

	CObjMgr::GetInst().Add_Create(OBJ_ITEMLIST, CFactory<CShop_Item>::Create((float)(m_iStartX+ 50 ), (float)(m_iStartY + 215)));
	dynamic_cast<CShop_Item*>(CObjMgr::GetInst().GetObjectList(OBJ_ITEMLIST).back())->SetItemID(ITEM_PET_GOUSE);

	CObjMgr::GetInst().Add_Create(OBJ_ITEMLIST, CFactory<CShop_Item>::Create((float)(m_iStartX + 50), (float)(m_iStartY + 260)));
	dynamic_cast<CShop_Item*>(CObjMgr::GetInst().GetObjectList(OBJ_ITEMLIST).back())->SetItemID(ITEM_TOMATO);

	m_eRender = RENDER_PRONTUI;
}

int CShop::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;


	return OBJ_NOEVENT;
}

void CShop::LateUpdate()
{
}

void CShop::Render(HDC _hDC)
{
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(L"Shop");

	BitBlt(_hDC, m_iStartX, m_iStartY, SCALE_X, SCALE_Y, hMemDC, 0, 0, SRCCOPY);

	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();

	/*TCHAR		aszHp[64] = L"";

	swprintf_s(aszHp, L"X: %d \t Y: %f ", m_iStartX , (float)(m_iStartY + 120));
	TextOut(_hDC, 400, 300, aszHp, lstrlen(aszHp));*/
}

void CShop::Release()
{
}
