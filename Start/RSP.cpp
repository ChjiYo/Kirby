#include "RSP.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "Player.h"	
#include "Factory.h"
#include "Item_Now.h"

#include <iostream>

CRSP::CRSP()
{
	m_iEnemyNum = 0;
	m_iPlayerNum = 0;
	m_iResult = 0;
	m_bComple = false;

	m_dwEnd = (DWORD)GetTickCount64();
}

CRSP::~CRSP()
{
	Release();
}

bool CRSP::RSPSel()
{
	if (CKeyMgr::GetInst().Key_Down('1'))
	{
		m_iPlayerNum = 0;
		m_iEnemyNum = rand() % 3;
		m_bComple = true;	

		return true;
	}
	else if (CKeyMgr::GetInst().Key_Down('2'))
	{
		m_iPlayerNum = 1;

		m_iEnemyNum = rand() % 3;
	
		m_bComple = true;

		return true;
	}
	else if (CKeyMgr::GetInst().Key_Down('3'))
	{
		m_iPlayerNum = 2;
		m_iEnemyNum = rand() % 3;
		m_bComple = true;

		return true;

	}

	return false;
}

int CRSP::Result()
{
	m_iResult = m_iEnemyNum - m_iPlayerNum;

	if (m_iResult == 0)
	{
		return D;
	}
	else if (m_iResult == -2 || m_iResult == 1)
	{
		
		return W;
	}
	else
	{
		
		return L;
	}

	
}

void CRSP::ItemCreate()
{
	int iResult = Result();

	switch(iResult)
	{
	case W:
		CObjMgr::GetInst().Add_Create(OBJ_ITEM, CFactory<CItem_Now>::Create(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back()->GetInfo().fX - 100 , CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back()->GetInfo().fY));
		dynamic_cast<CItem_Now*>(CObjMgr::GetInst().GetObjectList(OBJ_ITEM).back())->SetItemID(ITEM_MEAT);
		break;

	case L:
		dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back())->SetHp(-4);
		break;

	case D:

		break;

	default:
		cout << "System Error" << endl;
		break;
	}
}

void CRSP::Initialize()
{
 	CBmpMgr::GetInst().InsertBmp(L"../Kirby/New_Scene_RSP.bmp", L"RSP");

	//m_iEnemyNum = rand() % 3;
	
	m_iPlayerNum = 4;
	m_iEnemyNum = 4;

	m_eRender = RENDER_UI;
}

int CRSP::Update()
{
	if (m_bDead)
		return OBJ_DISTORY;
	
	if (!m_bComple)
	{
		bool bCheck = RSPSel();

		if (bCheck)
		{
			ItemCreate();
		}
	}

	return OBJ_NOEVENT;
}

void CRSP::LateUpdate()
{
	
}

void CRSP::Render(HDC _hDC)
{
	HDC	hMemDC = CBmpMgr::GetInst().FindImage(L"RSP");


	BitBlt(_hDC, 250, 100, SCALE_X, SCALE_Y, hMemDC, 0, 0, SRCCOPY);

	GdiTransparentBlt(
		_hDC,
		250,
		280,
		100 ,
		100,
		hMemDC,
		100 * m_iEnemyNum,
		0,
		100 ,
		100,
		RGB(255, 255, 255));

	GdiTransparentBlt(
		_hDC,
		450,
		280,
		100,
		100,
		hMemDC,
		100 * m_iPlayerNum,
		0,
		100,
		100,
		RGB(255, 255, 255));
}

void CRSP::Release()
{
}
