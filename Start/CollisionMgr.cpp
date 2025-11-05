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