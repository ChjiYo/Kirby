#include "PlayerHp.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Factory.h"

#include "Player.h"

CPlayerHp::CPlayerHp()
{
	m_iPlayerHp = 0;
}

CPlayerHp::~CPlayerHp()
{
	Release();
}

void CPlayerHp::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/UI/PlayerHp.bmp", L"HpBar");
	m_pFrameKey = L"HpBar";

	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_UI;
}

int CPlayerHp::Update()
{
	m_iPlayerHp = dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetHp();
	
	return 0;
}

void CPlayerHp::LateUpdate()
{

}

void CPlayerHp::Render(HDC _hDC)
{
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(L"HpBar");

	GdiTransparentBlt(
		_hDC,
		150,
		550,
		(int)(388 * 0.5f),
		(int)(m_tInfo.fCY * 0.5f),
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)(m_tInfo.fCY * m_tFrame.iMotion + 64.f),
		388,
		(int)m_tInfo.fCY,
		RGB(144, 152, 200));

		GdiTransparentBlt(
		_hDC,
		150,
		550,
		(int)((m_iPlayerHp / 4 + 1) * 64 * 0.5f),
		(int)(m_tInfo.fCY * 0.5f),
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)(m_iPlayerHp / 4 + 1) * 64,
		(int)m_tInfo.fCY,
		RGB(144, 152, 200));


}

void CPlayerHp::Release()
{
}
