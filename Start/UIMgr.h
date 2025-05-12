#pragma once

#include "Define.h"
#include "Mini.h"

class CUIMgr 
{
private:
	CUIMgr();
	~CUIMgr();

public:
	static CUIMgr& GetInst()
	{
		static CUIMgr Inst;
		return Inst;
	}

public:
	void		UI_Change(UIID  eID);
	void		Update();
	void		LateUpdate();
	void		Render(HDC hDC);
	void		Release();

private:
	CMini*				m_pUI;

	UIID				m_ePreScene;
	UIID				m_eCurScene;
};

