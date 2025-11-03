#include "Quest.h"
#include "Monster.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "Item_Now.h"

CQuest::CQuest()
{
	m_iKillCount = 0;
	m_bQuestClear = false;
	m_bQuestAccept = false;
	m_dwClearMsgTimer = (DWORD)GetTickCount64();
	m_bCreateCheck = false;
	m_bMsgCheck = false;
}

CQuest::~CQuest()
{
	Release();
}

void CQuest::KillQuest()
{
	if (m_bQuestAccept)
	{
		for (auto iter : CObjMgr::GetInst().GetObjectList(OBJ_MONSTER))
		{
			if (iter->GetDead())
			{
				m_iKillCount++;
			}
		}

		if ((m_iKillCount ) >= 5)
		{
			m_bQuestClear = true;
		}
	}
}

void CQuest::Initialize()
{
	m_tInfo = { 640,555,150,25 };

	m_eRender = RENDER_UI;
}

int CQuest::Update()
{
	
	__super::RectUpdate();

	return 0;
}

void CQuest::LateUpdate()
{
	KillQuest();
}

void CQuest::Render(HDC _hDC)
{
	if (!m_bQuestClear && m_bQuestAccept)
	{
		Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

		TCHAR szQuest[64] = L"";

		swprintf_s(szQuest, L"                    퀘스트");
		TextOut(_hDC, 500, 525, szQuest, lstrlen(szQuest));

		TCHAR szHp[64] = L"";

		swprintf_s(szHp, L"몬스터 5마리 제거하기 / 처치 수 : %d", m_iKillCount );
		TextOut(_hDC, 500, 565, szHp, lstrlen(szHp));
	}

	if (m_bQuestClear)
	{
		if (!m_bCreateCheck)
		{
			m_dwClearMsgTimer = (DWORD)GetTickCount64();
			CObjMgr::GetInst().Add_Create(OBJ_ITEM, CFactory<CItem_Now>::Create(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back()->GetInfo().fX, 0));
			dynamic_cast<CItem_Now*>(CObjMgr::GetInst().GetObjectList(OBJ_ITEM).back())->SetItemID(ITEM_TOMATO);
			m_bCreateCheck = true;
		}

		if (!m_bMsgCheck)
		{
			TCHAR szHp[64] = L"";

			swprintf_s(szHp, L"퀘스트 완료!!!");
			TextOut(_hDC, 500, 565, szHp, lstrlen(szHp));
		}

		if (m_dwClearMsgTimer + 2000 < (DWORD)GetTickCount64())
		{
			m_bMsgCheck = true;
		}

	}
}

void CQuest::Release()
{
}
