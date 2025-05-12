#include "Button.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "BmpMgr.h"

CButton::CButton()
{
	m_iDrawID = 0;
}

CButton::~CButton()
{
	Release();
}

void CButton::MotionChange()
{
}

void CButton::Initialize()
{
	m_tInfo.fCX = 103.f;
	m_tInfo.fCY = 106.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_BACKGROUND;
}

int CButton::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CButton::LateUpdate()
{
	POINT ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);


	if (PtInRect(&m_tRect, ptMouse))
	{
		if (CKeyMgr::GetInst().Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(L"Start", m_pFrameKey))
				CSceneMgr::GetInst().Scene_Change(SC_STAGE);
			
			/*else if (!lstrcmp(L"Edit", m_pFrameKey))
				CSceneMgr::GetInst().Scene_Change(SC_EDIT);

			else if (!lstrcmp(L"Exit", m_pFrameKey))
				DestroyWindow(g_hWnd);*/

			return;
		}

		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;


	__super::MoveFrame();
}

void CButton::Render(HDC _hDC)
{
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		m_tRect.left, 
		m_tRect.top,
		(int)m_tInfo.fCX,	
		(int)m_tInfo.fCY,
		hMemDC,		
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		0,
		(int)m_tInfo.fCX,	
		(int)m_tInfo.fCY,	
		RGB(12, 230, 248));
}

void CButton::Release()
{
}
