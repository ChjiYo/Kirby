#pragma once

#include "Define.h"
#include "Obj.h"
#include "ObjMgr.h"

#include "Shop_Item.h"

template<typename T>
class CFactory
{
public:
	CFactory() {}
	~CFactory() {}

public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create(float _fX, float _fY)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->SetObjPos(_fX, _fY);

		return pObj;
	}

	static CObj* ItemCreate(float _fX, float _fY,ITEMID _eItemID)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->SetObjPos(_fX, _fY);
		dynamic_cast<CShop_Item*> (pObj)->SetItemID(_eItemID);

		return pObj;
	}

	static CObj* Create(float _fX, float _fY, float _fAngle)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->SetObjPos(_fX, _fY);
		pObj->SetAngle(_fAngle);

		return pObj;
	}

	static CObj* Change()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		CObjMgr::GetInst().GetPlayerInfo()->SetPlayerChange(pObj);
		return pObj;
	}
};

