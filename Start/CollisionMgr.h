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

public:
	 bool Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src);

	  bool Check_Sphere(CObj* pDst, CObj* pSrc);
	 bool	Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src);
	 bool SetPlayerInhal_Check(list<CObj*> _pPlayer, list<CObj*> _pMonster);

	 bool ObjectIDCollisionCheck(OBJID _eFirstID, OBJID _eSecondID);

	 bool ObjectCollisionCheck(list<CObj*> _pPlayer, list<CObj*> _pMonster);
	 int InvenCollisionCheck(list<CObj*> _pMouse, list<CObj*> _pItem);

	 bool SetObjCheck(CObj* pDst, list<CObj*> _pPlayer);

	 static bool Check_Rect(float* pX, float* pY, CObj* pDst, CObj* pSrc);
	 void Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src, float _fSpeed);
};

