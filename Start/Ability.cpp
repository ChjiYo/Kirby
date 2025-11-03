#include "Ability.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Player.h"

CAbility::CAbility()
{
	Release();
}

CAbility::~CAbility()
{
}

void CAbility::Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CLASIC:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iMotion = 0;
			break;

		case SPARK:
			m_tFrame.iFrameStart = 2;
			m_tFrame.iMotion = 0;
			break;

		case SLEEP:
			m_tFrame.iFrameStart = 4;
			m_tFrame.iMotion = 2;
			break;

		case ICE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iMotion = 3;
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CAbility::Initialize()
{
	m_tInfo = { 100.f ,500.f , 80.f, 80.f};

	CBmpMgr::GetInst().InsertBmp(L"../Kirby/UI/UI_CopyIcon.bmp", L"UI_CopyIcon");
	m_pFrameKey = L"UI_CopyIcon";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_UI;


}

int CAbility::Update()
{
	__super::RectUpdate();



	return OBJ_NOEVENT;
}

void CAbility::LateUpdate()
{
	switch (dynamic_cast<CPlayer*> (CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back())->GetPlayerID())
	{
	case PLAYER_CLASIC:
		m_eCurState = CLASIC;
		break;

	case PLAYER_SPARK:
		m_eCurState = SPARK;
		break;

	case PLAYER_ICE:
		m_eCurState = ICE;
		break;

	case PLAYER_SLEEP:
		m_eCurState = SLEEP;
		break;
	}
	Change();
}

void CAbility::Render(HDC _hDC)
{
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		50,
		525,
		(int)(m_tInfo.fCX * 0.75f),
		(int)(m_tInfo.fCY * 0.75f),
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));
}

void CAbility::Release()
{
}
