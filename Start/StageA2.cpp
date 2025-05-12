#include "StageA2.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

#include "ObjMgr.h"
#include "Factory.h"
#include"Player_Origin.h"

#include "Monster_Gunter.h"

#include "Door.h"

CStageA2::CStageA2()
{
}

CStageA2::~CStageA2()
{
    Release();
}

void CStageA2::Initialize()
{  
    CBmpMgr::GetInst().InsertBmp(L"../Kirby/Map/Stage1/Map_NewStage2.bmp", L"Ground2");
    CBmpMgr::GetInst().InsertBmp(L"../Kirby/Back/Back_StageA2.bmp", L"Back_Ground2");
    
    CLineMgr::GetInst().Initialize();
    CLineMgr::GetInst().Load_Stage2();

    CObjMgr::GetInst().Add_Create(OBJ_DOOR, CFactory<CDoor>::Create(4625.f, 340.f));

    CScrollMgr::GetInst().SetScrollX();
    CScrollMgr::GetInst().SetScrollY();
}

int CStageA2::Update()
{
    CObjMgr::GetInst().Update();
    return 0;
}

void CStageA2::LateUpdate()
{
    CObjMgr::GetInst().LateUpdate();   
}

void CStageA2::Render(HDC _hDC)
{
    HDC	hBackGroundDC = CBmpMgr::GetInst().FindImage(L"Back_Ground2");
    HDC	hGroundDC = CBmpMgr::GetInst().FindImage(L"Ground2");

    int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
    int iScrollY = (int)CScrollMgr::GetInst().GetScrollY();

    BitBlt(_hDC, 0, 0, 800, 600, hBackGroundDC, 0, 0, SRCCOPY);

    GdiTransparentBlt(
        _hDC,
        iScrollX,
        iScrollY,
        4761,
        681,
        hGroundDC,
        0,
        0,
        4761,
        681,
        RGB(0, 18, 127));

    CObjMgr::GetInst().Render(_hDC);
}

void CStageA2::Release()
{
   
}
