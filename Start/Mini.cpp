#include "Mini.h"
#include "UIMgr.h"

CMini::CMini()
{
}

CMini::~CMini()
{
	Release();
}

void CMini::Initialize()
{
	CUIMgr::GetInst().UI_Change(UI_RSP);
}

int CMini::Update()
{
	CUIMgr::GetInst().Update();

	return 0;
}

void CMini::LateUpdate()
{
	CUIMgr::GetInst().LateUpdate();
}

void CMini::Render(HDC _hDC)
{
	CUIMgr::GetInst().Render(_hDC);
}

void CMini::Release()
{
}
