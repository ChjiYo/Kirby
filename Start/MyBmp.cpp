#include "MyBmp.h"

CMyBmp::CMyBmp()
{
	m_hMemDC = 0;
	m_hBitMap = 0;
	m_hOldBmp = 0;
}

CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::LoadBmp(const TCHAR* pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitMap = (HBITMAP)LoadImage(NULL,
		pFilePath,   
		IMAGE_BITMAP,
		0,			 
		0,			 
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
}

void CMyBmp::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}
