#include "CollisionMgr.h"
#include "Monster.h"
#include "Player.h"
#include "ObjMgr.h"

#include "ScrollMgr.h"

#include "Monster_Sparky.h"

#include "Shop_Item.h"
#include "ObjMgr.h"

bool CCollisionMgr::Check_Sphere(CObj* pDst, CObj* pSrc)
{
	float	fWidth = abs(pDst->GetInfo().fX - pSrc->GetInfo().fX);
	float	fHeight = abs(pDst->GetInfo().fY - pSrc->GetInfo().fY);

	float	fDiagonal = (float)sqrt(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDst->GetInfo().fCX + pSrc->GetInfo().fCX) * 0.5f;

	return fRadius >= fDiagonal;
}

bool CCollisionMgr::ObjectIDCollisionCheck(OBJID _eFirstID, OBJID _eSecondID)
{
	list<CObj*> pFirstObjList = CObjMgr::GetInst().GetObjectList(_eFirstID);
	list<CObj*> pSecondObjList = CObjMgr::GetInst().GetObjectList(_eSecondID);

	for (auto& pFirst : pFirstObjList)
	{
		for (auto& pSecond : pSecondObjList)
		{
			if (Check_Sphere(pFirst, pSecond))
			{
				return true;
			}
		}
	}

	return false;
}

CObj* CCollisionMgr::FindCollObject(OBJID _eFirstID, OBJID _eFindID)
{
	list<CObj*> pFirstObjList = CObjMgr::GetInst().GetObjectList(_eFirstID);
	list<CObj*> pFindObjList = CObjMgr::GetInst().GetObjectList(_eFindID);

	for (auto& pFirst : pFirstObjList)
	{
		for (auto& pFind : pFindObjList)
		{
			if (Check_Sphere(pFirst, pFind))
			{
				return pFind;
			}
		}
	}

	return nullptr;
}

int CCollisionMgr::InvenCollisionCheck(list<CObj*> _pMouse, list<CObj*> _pItem )
{
	for (auto& Mouse : _pMouse)
	{
		for (auto& Item  : _pItem)
		{
			if (Check_Sphere(Mouse, Item))
			{
				ITEMID ItemID = dynamic_cast<CShop_Item*>(Item)->GetItemID();
				int a = 10;
				switch (ItemID)
				{
				case ITEM_MEAT:
					//dynamic_cast<CShop_Item*>(Item)->SetItemID(ITEM_MEAT);
					dynamic_cast<CShop_Item*>(Item)->SetPrice(100);
					return ITEM_MEAT;

				case ITEM_TOMATO:
					//dynamic_cast<CShop_Item*>(Item)->SetItemID(ITEM_TOMATO);
					dynamic_cast<CShop_Item*>(Item)->SetPrice(200);
					return ITEM_TOMATO;

				case ITEM_PET_GOUSE:
					//dynamic_cast<CShop_Item*>(Item)->SetItemID(ITEM_PET_GOUSE);
					dynamic_cast<CShop_Item*>(Item)->SetPrice(300);
					return ITEM_PET_GOUSE;
				}
				
			}
		}
	}

	return 999;
}