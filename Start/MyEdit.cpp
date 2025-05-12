#include "MyEdit.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"

CMyEdit::CMyEdit()
{
}

CMyEdit::~CMyEdit()
{
}

void CMyEdit::Initialize()
{
}

int CMyEdit::Update()
{
    return 0;
}

void CMyEdit::LateUpdate()
{
	Key_Input();
}

void CMyEdit::Render(HDC _hDC)
{
}

void CMyEdit::Release()
{
}

void CMyEdit::Key_Input()
{
	if (CKeyMgr::GetInst().Key_Pressing(VK_LEFT))
		CScrollMgr::GetInst().SetScrollX(5.f);

	if (CKeyMgr::GetInst().Key_Pressing(VK_RIGHT))
		CScrollMgr::GetInst().SetScrollX(-5.f);

	if (CKeyMgr::GetInst().Key_Pressing(VK_UP))
		CScrollMgr::GetInst().SetScrollY(5.f);

	if (CKeyMgr::GetInst().Key_Pressing(VK_DOWN))
		CScrollMgr::GetInst().SetScrollY(-5.f);
}
