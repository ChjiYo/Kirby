#pragma once

#include "Define.h"
#include "Obj.h"

class CAbility :public CObj
{
public:
	enum STATE {CLASIC , SPARK , SLEEP , ICE ,UI_END};

public:
	CAbility();
	~CAbility();

public:
	void Change();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

private:
	STATE			m_eCurState;
	STATE			m_ePreState;

};

