#include "Mouse.h"
#include "BmpMgr.h"
#include "KeyMgr.h"

#include "ScrollMgr.h"

CMouse::CMouse()
{
	ZeroMemory(&m_eCurState,sizeof(m_eCurState));
	ZeroMemory(&m_ePreState,sizeof(m_ePreState));

	m_bClickCheck = false;
}

CMouse::~CMouse()
{
}

void CMouse::Input()
{

	if (CKeyMgr::GetInst().Key_Down(VK_LBUTTON) || m_tFrame.iFrameStart != m_tFrame.iFrameEnd)
	{
		m_bClickCheck = true;

		if (m_bClickCheck)
		{
			m_eCurState = CLICK;
			m_bClickCheck = false;
		}


	}
	else
	{
		m_eCurState = IDLE;
	}
}

void CMouse::Motion()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case CLICK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CMouse::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Mouse_Anim.bmp", L"Mouse");

	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 60.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_UI;
}

int CMouse::Update()
{
	POINT	ptMouse{};

	GetCursorPos(&ptMouse);

	ScreenToClient(g_hWnd, &ptMouse);

	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

	ShowCursor(FALSE);

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CMouse::LateUpdate()
{
	Input();
	Motion();
	__super::MoveFrame();
}

void CMouse::Render(HDC _hDC)
{	
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(L"Mouse");

	GdiTransparentBlt(
		_hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX * 2,
		(int)m_tInfo.fCY * 2,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion ,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(0, 0, 0));

	/*TCHAR		szHp[64] = L"";

	swprintf_s(szHp, L"X: %f \t Y: %f ", m_tInfo.fX , m_tInfo.fY);
	TextOut(_hDC, 400, 100, szHp, lstrlen(szHp));*/
}

void CMouse::Release()
{
}
