#include "StageA4.h"
#include "BmpMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"

#include "Factory.h"
#include "Player_Origin.h"
#include "Player_Ice.h"
#include "DDDKing.h"

#include "Monster_Gunter.h"

#include "BossHp.h"

#include "SoundMgr.h"

CStageA4::CStageA4()
{
    
}

CStageA4::~CStageA4()
{
    Release();
}

void CStageA4::Initialize()
{
    m_fVolume = 1.f;

    CBmpMgr::GetInst().InsertBmp(L"../Kirby/Map/BossStage/Map_BossRoom.bmp", L"Ground4");
    CBmpMgr::GetInst().InsertBmp(L"../Kirby/Back/Back_BossStage.bmp", L"Back_Ground4");
    //CObjMgr::GetInst().Add_Create(OBJ_PLAYER, CFactory<CPlayer_Origin>::Create());

    CObjMgr::GetInst().Add_Create(OBJ_MONSTER, CFactory<CDDDKing>::Create(1250.f, 350.f));
    CObjMgr::GetInst().Add_Create(OBJ_UI, CFactory<CBossHp>::Create());

    CLineMgr::GetInst().Initialize();

    CScrollMgr::GetInst().SetScrollX();
    CScrollMgr::GetInst().SetScrollY();

    //CSoundMgr::GetInst().StopSound(SOUND_BGM);
    //CSoundMgr::GetInst().PlayBGM(L"Boss.wav", m_fVolume);
}

int CStageA4::Update()
{
    CObjMgr::GetInst().Update();
    return 0;
}

void CStageA4::LateUpdate()
{
    CObjMgr::GetInst().LateUpdate();
}

void CStageA4::Render(HDC _hDC)
{
    HDC	hGroundDC = CBmpMgr::GetInst().FindImage(L"Ground4");
    HDC	hBackGroundDC = CBmpMgr::GetInst().FindImage(L"Back_Ground4");

    int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
    int iScrollY = (int)CScrollMgr::GetInst().GetScrollY();

    BitBlt(_hDC, 0, 0, 800, 600, hBackGroundDC, 0, 0, SRCCOPY);

    GdiTransparentBlt(
        _hDC,
        iScrollX,
        iScrollY,
        1612,
        600,
        hGroundDC,
        0,
        0,
        1612,
        600,
        RGB(34, 177, 76));

    CObjMgr::GetInst().Render(_hDC);
}

void CStageA4::Release()
{
}
