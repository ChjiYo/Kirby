#pragma once

#include "Define.h"
//#include "Mini.h"
#include "UI.h"

class CRSP :public CUI
{
	enum STATE{R , S , P , END};
	enum RESULT { W, L, D };

public:
	CRSP();
	virtual ~CRSP();

public:
	bool RSPSel();
	int Result();
	void ItemCreate();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

private:
	int m_iEnemyNum;
	int m_iPlayerNum;
	int m_iResult;
	bool m_bComple;
	DWORD m_dwEnd;
};

