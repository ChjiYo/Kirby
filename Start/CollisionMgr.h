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
	 bool	Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src);

	 bool ObjectIDCollisionCheck(OBJID _eFirstID, OBJID _eSecondID);
	 CObj* FindCollObject(OBJID _eFirstID, OBJID _eFindID);

	 int InvenCollisionCheck(list<CObj*> _pMouse, list<CObj*> _pItem);

	 bool SetObjCheck(CObj* pDst, list<CObj*> _pPlayer);

	 static bool Check_Rect(float* pX, float* pY, CObj* pDst, CObj* pSrc);
	 void Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src, float _fSpeed);
};

