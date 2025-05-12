#pragma once

#include "Define.h"
#include "UI.h"

class CPlayerHp :public CUI
{
public:
	CPlayerHp();
	virtual ~CPlayerHp();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

private:
	int m_iPlayerHp;
};

