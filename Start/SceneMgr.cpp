#include "SceneMgr.h"
#include "StageMgr.h"

#include "Logo.h"
#include "MyMenu.h"
#include "MyEdit.h"
#include "Stage.h"
#include "Mini.h"
#include "RSP.h"
#include "Video.h"

CSceneMgr::CSceneMgr()
{
	m_eCurScene = SC_LOGO;
	m_ePreScene = (SC_END);
	m_pScene = nullptr;
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_LOGO:
			m_pScene = new CLogo;
			break;

		case SC_MENU:
			m_pScene = new CMyMenu;
			break;

		case SC_EDIT:
			m_pScene = new CMyEdit;
			break;

		case SC_STAGE:
			m_pScene = new CStage;
			break;

		case SC_UI:
			m_pScene = new CMini;
			break;

		case SC_VEDEO:
			m_pScene = new CVideo;
			break;

		}
		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}
