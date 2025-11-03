#include "StageA3.h"
#include "BmpMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"

#include "Door.h"
#include "Factory.h"

#include "Monster_Gunter.h"
#include "Monster_Sleepy.h"

#include "Player_Origin.h"
#include "PlayerHp.h"

#include "Wadle.h"

#include "Item_Now.h"

#include "NPC_Mario.h"

#include "Mouse.h"

CStageA3::CStageA3()
{
}

CStageA3::~CStageA3()
{
    Release();
}


void CStageA3::SwimmingPool()
{
    float fPlayerPosX = CObjMgr::GetInst().GetPlayerInfo()->GetInfo().fX;
    float fPlayerPosY = CObjMgr::GetInst().GetPlayerInfo()->GetInfo().fY;

    bool bSwitch = fPlayerPosX < 2500.f && fPlayerPosX > 1870.f && fPlayerPosY > 340.f;

    static_cast<CPlayer*> (CObjMgr::GetInst().GetPlayerInfo())->SetSwimming(bSwitch);
}


void CStageA3::Initialize()
{
    CBmpMgr::GetInst().InsertBmp(L"../Kirby/Map/Stage1/Map_NewStage3.bmp", L"Ground3");
    CBmpMgr::GetInst().InsertBmp(L"../Kirby/Back/Back_StageA3.bmp", L"Back_Ground3");

    CLineMgr::GetInst().Load_Stage3();

    CObjMgr::GetInst().Add_Create(OBJ_DOOR, CFactory<CDoor>::Create(4620.f, 180.f));


    CScrollMgr::GetInst().SetScrollX();
    CScrollMgr::GetInst().SetScrollY();

    CObjMgr::GetInst().Add_Create(OBJ_PLAYER, CFactory<CPlayer_Origin>::Create());
    CObjMgr::GetInst().Add_Create(OBJ_MOUSE, CFactory<CMouse>::Create());

    //CObjMgr::GetInst().Add_Create(OBJ_MONSTER, CFactory<CWadle>::Create(1000.f, 325.f));
    CObjMgr::GetInst().Add_Create(OBJ_NPC, CFactory<CNPC_Mario>::Create(1310.f, 325.f));
    CObjMgr::GetInst().Add_Create(OBJ_MONSTER, CFactory<CMonster_Sleepy>::Create(3100.f, 150.f));
    CObjMgr::GetInst().Add_Create(OBJ_MONSTER, CFactory<CWadle>::Create(3150.f, 400.f));
    CObjMgr::GetInst().Add_Create(OBJ_MONSTER, CFactory<CMonster_Gunter>::Create(4000.f, 170.f));

    CObjMgr::GetInst().Add_Create(OBJ_ITEM, CFactory<CItem_Now>::Create(600.f , 140.f));
    dynamic_cast<CItem_Now*>(CObjMgr::GetInst().GetItemInfo())->SetItemID(ITEM_CANDY);

    //4170 , 170
    //1310 , 300

    //CObjMgr::GetInst().Add_Create(OBJ_NPC, CFactory<CNPC_Mario>::Create(4170.f, 170.f));
}

int CStageA3::Update()
{
    CObjMgr::GetInst().Update();
    return 0;
}

void CStageA3::LateUpdate()
{
    CObjMgr::GetInst().LateUpdate();
    SwimmingPool();
}

void CStageA3::Render(HDC _hDC)
{
    HDC	hGroundDC = CBmpMgr::GetInst().FindImage(L"Ground3");
    HDC	hBackGroundDC = CBmpMgr::GetInst().FindImage(L"Back_Ground3");

    int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
    int iScrollY = (int)CScrollMgr::GetInst().GetScrollY();

    BitBlt(_hDC, 0, 0, 800, 600, hBackGroundDC, 0, 0, SRCCOPY);

    GdiTransparentBlt(
        _hDC,
        iScrollX,
        iScrollY,
        4761,
        612,
        hGroundDC,
        0,
        0,
        4761,
        612,
        RGB(0, 18, 127));

    /*TCHAR		szHp[64] = L"";

    swprintf_s(szHp, L"Candy : %d ", dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetMoney());
    TextOut(_hDC, 400, 100, szHp, lstrlen(szHp));*/
  
    CObjMgr::GetInst().Render(_hDC);
}

void CStageA3::Release()
{
}
