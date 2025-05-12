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
	 CObj* GetPlayerInfo() { return m_ObjList[OBJ_PLAYER].back(); }
	 CObj* GetMonsterInfo() { return m_ObjList[OBJ_MONSTER].back(); }
	 CObj* GetMonEpickInfo() { return m_ObjList[OBJ_SPECIAL_MONSTER].back(); }
	 CObj* GetAttackInfo() { return m_ObjList[OBJ_ATTACK].back(); }
	 CObj* GetUIInfo() { return m_ObjList[OBJ_UI].back(); }
	 CObj* GetItemInfo() { return m_ObjList[OBJ_ITEM].back(); }
	 CObj* GetItemListInfo() { return m_ObjList[OBJ_ITEMLIST].back(); }
	 CObj* GetPetInfo() { return m_ObjList[OBJ_PET].back(); }

	 list<CObj*>  GetPlayerList() { return m_ObjList[OBJ_PLAYER]; }
	 list<CObj*>  GetDoorList() { return m_ObjList[OBJ_DOOR]; }
	 list<CObj*>  GetMonsterList() { return m_ObjList[OBJ_MONSTER]; }
	 list<CObj*>  GetAttackList() { return m_ObjList[OBJ_ATTACK]; }
	 list<CObj*>  GetMonAttackList() { return m_ObjList[OBJ_MONATTACK];}
	 list<CObj*>  GetMonEpickList() { return m_ObjList[OBJ_SPECIAL_MONSTER];}
	 list<CObj*>  GetNPCList() { return m_ObjList[OBJ_NPC]; }
	 list<CObj*>  GetItemList() { return m_ObjList[OBJ_ITEM]; }
	 list<CObj*> GetUIList() { return m_ObjList[OBJ_UI]; }
	 list<CObj*> GetMouseList() { return m_ObjList[OBJ_MOUSE]; }

	 list<CObj*>  GetItemListList() { return m_ObjList[OBJ_ITEMLIST]; }
	 list<CObj*>  GetPetList() { return m_ObjList[OBJ_PET]; }

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

