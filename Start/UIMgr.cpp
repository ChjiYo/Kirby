#include "UIMgr.h"
#include "RSP.h"

CUIMgr::CUIMgr()
{
	m_eCurScene = UI_RSP;
	m_ePreScene = (UI_END);
	m_pUI = nullptr;
}

CUIMgr::~CUIMgr()
{
	Release();
}

void CUIMgr::UI_Change(UIID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pUI);

		switch (m_eCurScene)
		{
		case UI_RSP:
		//	m_pUI = new CRSP;
			break;

		}
		m_pUI->Initialize();

 		m_ePreScene = m_eCurScene;
	}
}

void CUIMgr::Update()
{
	m_pUI->Update();
}

void CUIMgr::LateUpdate()
{
	m_pUI->LateUpdate();
}

void CUIMgr::Render(HDC hDC)
{
	m_pUI->Render(hDC);
}

void CUIMgr::Release()
{
	Safe_Delete(m_pUI);
}
