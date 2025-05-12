#include "Temp.h"
#include "BmpMgr.h"
#include "Factory.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

#include "Player.h"

#define TEMP_X 0
#define TEMP_Y 0

#define TEMP_CX 51
#define TEMP_CY 60

CTemp::CTemp()
{
}

CTemp::~CTemp()
{
}

void CTemp::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Pet/Pet_Goust_Left.bmp", L"TEMP_MEAT");

	m_eRender = RENDER_GAMEOBJECT;
}

int CTemp::Update()
{
	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CTemp::LateUpdate()
{
}

void CTemp::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(L"TEMP_MEAT");

	GdiTransparentBlt(
		_hDC,
		(int)CObjMgr::GetInst().GetPlayerInfo()->GetInfo().fX + 200 ,
		(int)CObjMgr::GetInst().GetPlayerInfo()->GetInfo().fY,
		TEMP_CX,
		TEMP_CY,
		hMemDC,
		TEMP_X,
		TEMP_Y,
		TEMP_CX,
		TEMP_CY,
		RGB(1, 255, 255));
}

void CTemp::Release()
{
}
