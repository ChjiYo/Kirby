#pragma once

#include "Define.h"
#include "Obj.h"

class CMouse :public CObj
{
public:
	enum STATE{IDLE , CLICK , END};

public:
	CMouse();
	virtual ~CMouse();

public:
	void Motion();
	void Input();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

private:
	STATE			m_eCurState;
	STATE			m_ePreState;

	bool			m_bClickCheck;
};

