#pragma once

#include "Define.h"
#include "MyBmp.h"

class CBmpMgr
{
private:
	CBmpMgr();
	~CBmpMgr();

public:
	static CBmpMgr& GetInst()
	{
		static CBmpMgr Inst;
		return Inst;
	}

public:
	void	InsertBmp(const TCHAR* _pFilePath, const TCHAR* _pImgKey);
	HDC		FindImage(const TCHAR* _pImgKey);
	void Release();

private:
	map<const TCHAR*, CMyBmp*> m_mapBit;

};

