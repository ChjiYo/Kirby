#pragma once

#include "Define.h"

class CMyBmp
{
public:
	CMyBmp();
	~CMyBmp();

public:
	HDC		GetMemDC() { return m_hMemDC; }

	void		LoadBmp(const TCHAR* pFilePath);
	void		Release();


private:
	HDC		m_hMemDC;

	HBITMAP		m_hBitMap;
	HBITMAP		m_hOldBmp;
};

