#include "Video.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"

CVideo::CVideo()
{
	m_dwSceneChange = (DWORD)GetTickCount64();
}

CVideo::~CVideo()
{
	Release();
}

void CVideo::Initialize()
{
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Scene/Scene_EndingA.bmp", L"EndA");
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Scene/Scene_EndingB.bmp", L"EndB");
}

int CVideo::Update()
{
	return 0;
}

void CVideo::LateUpdate()
{

}

void CVideo::Render(HDC _hDC)
{
	HDC	hEndAMemDC = CBmpMgr::GetInst().FindImage(L"EndA");
	HDC	hEndBMemDC = CBmpMgr::GetInst().FindImage(L"EndB");

	if (m_dwSceneChange + 200 < (DWORD)GetTickCount64())
	{
		BitBlt(_hDC, 0, 0, SCALE_X, SCALE_Y, hEndAMemDC, 0, 0, SRCCOPY);
		m_dwSceneChange = (DWORD)GetTickCount64();
	}
	else
	{
		BitBlt(_hDC, 0, 0, SCALE_X, SCALE_Y, hEndBMemDC, 0, 0, SRCCOPY);
	}
}

void CVideo::Release()
{
	
}
