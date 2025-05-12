#include "MainGame.h"
#include "MainGame.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "StageMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "UIMgr.h"
#include <iostream>

MainGame::MainGame()
{
	m_hDC = 0;

	m_dwTime = (DWORD)GetTickCount64();
	m_iFPS = 0;
	ZeroMemory(&m_szFPS, sizeof(m_szFPS));
}

MainGame::~MainGame()
{
	Release();
}

void MainGame::Initialize()
{
	srand((unsigned int)time(NULL));

	m_hDC = GetDC(g_hWnd);

	CBmpMgr::GetInst().InsertBmp(L"../Kirby/BackBuffer.bmp", L"Back");

	//CSoundMgr::GetInst().Initialize();
	CSceneMgr::GetInst().Scene_Change(SC_LOGO);

//#ifdef _DEBUG
//
//	if (::AllocConsole() == TRUE)
//	{
//		FILE* nfp[3];
//		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
//		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
//		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
//		std::ios::sync_with_stdio();
//	}
//
//#endif // _DEBUG
}

void MainGame::Update()
{
	CSceneMgr::GetInst().Update();
}

void MainGame::LateUpdate()
{
	CSceneMgr::GetInst().LateUpdate();
	CScrollMgr::GetInst().ScrollLock();
}

void MainGame::Render()
{
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = (DWORD)GetTickCount64();
	}

	HDC hMemDC = CBmpMgr::GetInst().FindImage(L"Back");

	CSceneMgr::GetInst().Render(hMemDC);

	BitBlt(m_hDC,
		0, 0, SCALE_X, SCALE_Y,
		hMemDC,
		0,
		0,
		SRCCOPY);
}

void MainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
}
