#include "MainGame.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"

MainGame::MainGame()
{
	m_hDC = 0;

	m_iFPS = 0;
	m_dwTime = (DWORD)GetTickCount64();
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

MainGame::~MainGame()
{
	Release();
}

void MainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CLineMgr::GetInst().Initialize();
}

void MainGame::Update()
{
	CLineMgr::GetInst().Update();
}

void MainGame::LateUpdate()
{

}

void MainGame::Render()
{
	++m_iFPS;

	if (m_dwTime + 1000 < (DWORD)GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);	// 윈도우 상단에 글씨를 출력해줌

		m_iFPS = 0;
		m_dwTime = (DWORD)GetTickCount64();
	}

	Rectangle(m_hDC, 0, 0, SCALE_X, SCALE_Y);

	CLineMgr::GetInst().Render(m_hDC);
}

void MainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
}
