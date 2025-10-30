#include "StageMgr.h"

#include "StageA1.h"
#include "StageA2.h"
#include "StageA3.h"
#include "StageA4.h"

#include "ObjMgr.h"
#include "LineMgr.h"

CStageMgr::CStageMgr()
{
	m_eCurStage = STAGE_A3;
	m_ePreStage = STAGE_END;

	m_pStage = nullptr;
}

CStageMgr::~CStageMgr()
{
	Release();
}

void CStageMgr::StageChage(STAGEID eID)
{
	m_eCurStage = eID;


	if (m_ePreStage != m_eCurStage)
	{
		CObjMgr::GetInst().Delete_ID(OBJ_MONSTER);
		CObjMgr::GetInst().Delete_ID(OBJ_DOOR);
		CObjMgr::GetInst().Delete_ID(OBJ_NPC);
		CObjMgr::GetInst().Delete_ID(OBJ_ITEM);
		CLineMgr::GetInst().Release();

		if (!CObjMgr::GetInst().GetPetList().empty())
		{
			CObjMgr::GetInst().GetPetInfo()->SetObjPos(CObjMgr::GetInst().GetPlayerInfo()->GetInfo().fX - 50,
				CObjMgr::GetInst().GetPlayerInfo()->GetInfo().fY);
		}
		
		Safe_Delete(m_pStage);

		switch (m_eCurStage)
		{
		case STAGE_A1:
			m_pStage = new CStageA1;
			break;

		case STAGE_A2:
			m_pStage = new CStageA2;
			break;

		case STAGE_A3:
			m_pStage = new CStageA3;
			break;

		case STAGE_A4:
			m_pStage = new CStageA4;
			break;

		}
		m_pStage->Initialize();
		
		m_ePreStage = m_eCurStage;
	}
}

void CStageMgr::Update()
{
	m_pStage->Update();
}

void CStageMgr::LateUpdate()
{
	m_pStage->LateUpdate();
}

void CStageMgr::Render(HDC _hDC)
{
	m_pStage->Render(_hDC);
}

void CStageMgr::Release()
{
	Safe_Delete(m_pStage);
}
