#pragma once

#include "Define.h"
#include "Obj.h"

class CObjMgr 
{
private:
	CObjMgr();
	~CObjMgr();

public:
	static CObjMgr& GetInst()
	{
		static CObjMgr Inst;
		return Inst;
	}

public:
	 list<CObj*> GetObjectList(OBJID eObjID) {return m_ObjList[eObjID]; }
	 CObj* Get_Target(OBJID eID, CObj* pObj);

public:
	void Add_Create(OBJID _eID,CObj* _pObj);
	int Update();
	void LateUpdate();
	void Render(HDC _hDC);
	void Release();
	void Delete_ID(OBJID _eID);

private:
	list<CObj*> m_ObjList[OBJ_END];
	list<CObj*> m_RenderList[RENDER_END];
};

