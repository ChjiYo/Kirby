#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CLogo::CLogo()
{

}

CLogo::~CLogo()
{
    Release();
}

void CLogo::Initialize()
{
    CBmpMgr::GetInst().InsertBmp(L"../Kirby/Scene/Scene_Logo.bmp", L"Logo");
}

int CLogo::Update()
{
    return OBJ_NOEVENT;
}

void CLogo::LateUpdate()
{
    if (CKeyMgr::GetInst().Key_Down(VK_RETURN))
    {
        CSceneMgr::GetInst().Scene_Change(SC_MENU);
        return;
    }
}

void CLogo::Render(HDC _hDC)
{
    HDC	hMemDC = CBmpMgr::GetInst().FindImage(L"Logo");

    BitBlt(_hDC,
        0, 0, SCALE_X , SCALE_Y,
        hMemDC,
        0,
        0,
        SRCCOPY);
}

void CLogo::Release()
{
}
