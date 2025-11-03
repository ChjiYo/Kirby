#include "CollisionMgr.h"
#include "Monster.h"
#include "Player.h"
#include "ObjMgr.h"

#include "ScrollMgr.h"

#include "Monster_Sparky.h"

#include "Shop_Item.h"
#include "ObjMgr.h"

bool CCollisionMgr::Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
			int iScrollY = (int)CScrollMgr::GetInst().GetScrollY();

			RECT TempRect = Src->GetRect();
			TempRect.left -= iScrollX;
			TempRect.top-= iScrollY;
			TempRect.right -= iScrollX;
			TempRect.bottom -= iScrollY;

			if(IntersectRect(&rc, &(Dst->GetRect()), &(TempRect)))
			{
				

				return true;
			}
		}
	}
	return false;
}

bool CCollisionMgr::Check_Sphere(CObj* pDst, CObj* pSrc)
{
	float	fWidth = abs(pDst->GetInfo().fX - pSrc->GetInfo().fX);
	float	fHeight = abs(pDst->GetInfo().fY - pSrc->GetInfo().fY);

	float	fDiagonal = (float)sqrt(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDst->GetInfo().fCX + pSrc->GetInfo().fCX) * 0.5f;

	return fRadius >= fDiagonal;
}

bool CCollisionMgr::Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				return true;
			}
		}
	}
	return false;
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

bool CCollisionMgr::SetObjCheck(CObj* pDst, list<CObj*> _pPlayer)
{
	for (auto& Player : _pPlayer)
	{
			if (Check_Sphere(pDst, Player))
			{
				return true;
			}
		
	}
	return false;
}

bool CCollisionMgr::Check_Rect(float* pX, float* pY, CObj* pDst, CObj* pSrc)
{
	float		fDistance_W = abs(pDst->GetInfo().fX - pSrc->GetInfo().fX);
	float		fDistance_H = abs(pDst->GetInfo().fY - pSrc->GetInfo().fY);

	float		fRadiusX = (pDst->GetInfo().fCX + pSrc->GetInfo().fCX) * 0.5f;
	float		fRadiusY = (pDst->GetInfo().fCY + pSrc->GetInfo().fCY) * 0.5f;

	if ((fRadiusX >= fDistance_W) && (fRadiusY >= fDistance_H))
	{
		*pX = fRadiusX - fDistance_W;
		*pY = fRadiusY - fDistance_H;

		return true;
	}

	return false;
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src , float _fSpeed)
{
	float	fX(0.f), fY(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(&fX, &fY, Dst, Src))
			{
				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dst->GetInfo().fY < Src->GetInfo().fY)
					{
						Dst->Set_PosY(-fY);
					}

					// 하 충돌
					else
					{
						Dst->Set_PosY(fY);
					}
				}

				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (Dst->GetInfo().fX < Src->GetInfo().fX)
					{
						Dst->Set_PosX(-fX);
					}

					// 우 충돌
					else
					{
						Dst->Set_PosX(fX);
					}
				}
			}
		}
	}
}