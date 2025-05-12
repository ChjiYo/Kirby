    #include "MyMenu.h"
#include "BmpMgr.h"
#include "Obj.h"
#include "Factory.h"
#include "ObjMgr.h"
#include "Button.h"
#include "ObjMgr.h"

CMyMenu::CMyMenu()
{

}

CMyMenu::~CMyMenu()
{
    Release();
}

void CMyMenu::Initialize()
{

    CBmpMgr::GetInst().InsertBmp(L"../Kirby/Button/Btn_Start.bmp", L"Start");
    /*CBmpMgr::GetInst().InsertBmp(L"../Kirby/Button/Btn_Menu_Edit.bmp", L"Edit");
    CBmpMgr::GetInst().InsertBmp(L"../Kirby/Button/Btn_Menu_Exit.bmp", L"Exit");*/

    CBmpMgr::GetInst().InsertBmp(L"../Kirby/Scene/Scene_Menu.bmp", L"Menu");

    CObj* pObj = CFactory<CButton>::Create(500.f,400.f);
    pObj->SetFrameKey(L"Start");
    CObjMgr::GetInst().Add_Create(OBJ_UI, pObj);

   /* pObj = CFactory<CButton>::Create(400.f, 400.f);
    pObj->SetFrameKey(L"Edit");
    CObjMgr::GetInst().Add_Create(OBJ_UI, pObj);

    pObj = CFactory<CButton>::Create(650.f, 400.f);
    pObj->SetFrameKey(L"Exit");
    CObjMgr::GetInst().Add_Create(OBJ_UI, pObj);*/
       
}

int CMyMenu::Update()
{
    CObjMgr::GetInst().Update();

    return 0;
}

void CMyMenu::LateUpdate()
{
    CObjMgr::GetInst().LateUpdate();
}

void CMyMenu::Render(HDC _hDC)
{
    HDC	hMemDC = CBmpMgr::GetInst().FindImage(L"Menu");

    BitBlt(_hDC, 0, 0, SCALE_X, SCALE_Y, hMemDC, 0, 0, SRCCOPY);

    CObjMgr::GetInst().Render(_hDC);
}

void CMyMenu::Release()
{
}
    