#include "BossHp.h"
#include "BmpMgr.h"
#include "Player.h"
#include "ObjMgr.h"
#include "Monster.h"

CBossHp::CBossHp()
{
	m_iBossHp = 0;
}

CBossHp::~CBossHp()
{
}

void CBossHp::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/UI/BossHp.bmp", L"BossHpBar");
	m_pFrameKey = L"BossHpBar";

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 34.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = (DWORD)GetTickCount64();

	m_eRender = RENDER_UI;
}

int CBossHp::Update()
{
	m_iBossHp = dynamic_cast<CMonster*>(CObjMgr::GetInst().GetObjectList(OBJ_SPECIAL_MONSTER).back())->GetHp();

	__super::RectUpdate();
	return OBJ_NOEVENT;
}

void CBossHp::LateUpdate()
{
	

}

void CBossHp::Render(HDC _hDC)
{
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);
	HDC hCopyMemDC = CBmpMgr::GetInst().FindImage(m_pFrameKey);

	GdiTransparentBlt(
		_hDC,
		500,
		50,
		161,
		(int)(m_tInfo.fCY * 0.5f),
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion + 34,
		322,
		(int)m_tInfo.fCY,
		RGB(207, 176, 255));

	GdiTransparentBlt(
		_hDC,
		516,
		51,
		(int)  (m_iBossHp * 6.5f),
		(int)(m_tInfo.fCY * 0.5f),
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart + 32,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)(m_iBossHp * 2.5f),
		(int)m_tInfo.fCY,
		RGB(144, 152, 199));

}

void CBossHp::Release()
{
}
