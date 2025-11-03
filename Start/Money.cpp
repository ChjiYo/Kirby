#include "Money.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Player.h"

CMoney::CMoney()
{
	m_iMoney = 0;
}

CMoney::~CMoney()
{
	Release();
}

void CMoney::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Item/Item_Candy.bmp", L"Money");

	m_tInfo.fCX = 29.f;
	m_tInfo.fCY = 29.f;

	m_eRender = RENDER_UI;
}

int CMoney::Update()
{
	if(m_bDead)
		return OBJ_DISTORY;

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CMoney::LateUpdate()
{
}

void CMoney::Render(HDC _hDC)
{
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(L"Money");

	GdiTransparentBlt(
		_hDC,
		50,
		50,
		(int)m_tInfo.fCX,
		(int)(m_tInfo.fCY),
		hMemDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(12, 230, 248));

		TCHAR		szHp[64] = L"";
		
		swprintf_s(szHp, L"%d",dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back())->GetMoney());
		TextOut(_hDC, 100, 60, szHp, lstrlen(szHp));
}

void CMoney::Release()
{
}
