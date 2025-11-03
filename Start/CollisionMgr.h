#pragma once

#include "Define.h"
#include "Obj.h"

class CCollisionMgr
{
private:
	CCollisionMgr(){}
	~CCollisionMgr(){}

public:
	static CCollisionMgr& GetInst()
	{
		static CCollisionMgr Inst;
		return Inst;
	}

private:
	 bool Check_Sphere(CObj* pDst, CObj* pSrc);

public:
	 bool ObjectIDCollisionCheck(OBJID _eFirstID, OBJID _eSecondID);
	 CObj* FindCollObject(OBJID _eFirstID, OBJID _eFindID);

	 int InvenCollisionCheck(list<CObj*> _pMouse, list<CObj*> _pItem);
};

