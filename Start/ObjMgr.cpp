#include "ObjMgr.h"
#include "Player.h"

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Create(OBJID _eID, CObj* _pObj)
{
	if (_eID >= OBJ_END || _pObj == nullptr)
		return;

	m_ObjList[_eID].push_back(_pObj);
}

int CObjMgr::Update()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();
			
			if (iResult == OBJ_DISTORY)			
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	return 0;
}

void CObjMgr::LateUpdate()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->LateUpdate();

			if (m_ObjList[i].empty())
				break;

			RENDERID eID = iter->Get_RenderID();
			m_RenderList[eID].push_back(iter);
		}
	}
}

void CObjMgr::Render(HDC _hDC)
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		m_RenderList[i].sort([](CObj* pDst, CObj* pSrc)->bool
			{
				return pDst->GetInfo().fY < pSrc->GetInfo().fY;
			});

		for (auto& iter : m_RenderList[i])
		iter->Render(_hDC);

		m_RenderList[i].clear();
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj* pTarget = nullptr;
	float	fDistance(0.f);

	for (auto& iter : m_ObjList[eID])
	{
		if (iter->GetDead())
			continue;

		float	fWidth = abs(pObj->GetInfo().fX - iter->GetInfo().fX);
		float	fHeight = abs(pObj->GetInfo().fY - iter->GetInfo().fY);

		float	fDiagonal = (float)sqrt(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}

void CObjMgr::Delete_ID(OBJID _eID)
{
	for (auto& iter : m_ObjList[_eID])
	{
		Safe_Delete<CObj*>(iter);
	}
		m_ObjList[_eID].clear();

}